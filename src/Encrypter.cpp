#include "Encrypter.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

Encrypter::Encrypter(std::string inputName) {
  this->inputFile = new std::ifstream(inputName.c_str(), std::ios_base::in);
  std::noskipws(*this->inputFile);
}

Encrypter::~Encrypter() {
  (*this->inputFile).close();

  delete this->inputFile;
}

std::priority_queue<EncrypterNode> Encrypter::buildFreqQueue() {
  std::unordered_map<char, int> freqMap;
  std::priority_queue<EncrypterNode> freqQueue;

  std::string inputContent{std::istreambuf_iterator<char>{*this->inputFile},
                           {}};

  std::for_each(inputContent.begin(), inputContent.end(), [&freqMap](char c) {
    freqMap.find(c) == freqMap.end() ? freqMap[c] = 1 : freqMap[c]++;
  });

  std::for_each(freqMap.begin(), freqMap.end(), [&freqQueue](auto x) {
    freqQueue.push(EncrypterNode(x.first, x.second));
  });

  return freqQueue;
}

void Encrypter::buildEncryptTree() {
  auto freqQueue = this->buildFreqQueue();

  auto top_and_pop = [](std::priority_queue<EncrypterNode>& pq) {
    auto t = pq.top();
    pq.pop();
    return t;
  };

  while (freqQueue.size() > 1)
    freqQueue.push(top_and_pop(freqQueue) + top_and_pop(freqQueue));

  this->root = new EncrypterNode(freqQueue.top());
}

void Encrypter::buildMap() { buildMap(this->root, ""); }

void Encrypter::buildMap(EncrypterNode* node, std::string s) {
  if (node->left == nullptr and node->right == nullptr) {
    this->charToEncr[node->c] = s;
    return;
  }

  buildMap(node->left, s + "0");
  buildMap(node->right, s + "1");
}

std::string Encrypter::getEncryption(char value) {
  return this->charToEncr[value];
}

void Encrypter::getEncryption(std::string outFile) {
  (*this->inputFile).clear();
  (*this->inputFile).seekg(0);

  std::ofstream savefile(outFile, std::ios_base::binary);

  char c;

  uint8_t carry = 0, place = 0;
  while ((*this->inputFile) >> c) {
    for (char e : this->getEncryption(c)) {
      if (place == 8) {
        savefile << carry;
        carry = 0;
        place = 0;
      }
      carry += ((e == '1') << place);
      place++;
    }
  }

  savefile << carry;
  savefile << place;

  savefile.close();
}

void Encrypter::serializeEncryptTree(std::ofstream& oFile) {
  serializeEncryptTree(oFile, this->root);
}

void Encrypter::serializeEncryptTree(std::ofstream& oFile,
                                     EncrypterNode* node) {
  if (node->left == nullptr and node->right == nullptr) {
    oFile << 1;
    oFile << (uint8_t)node->c;
    return;
  }
  oFile << 0;
  serializeEncryptTree(oFile, node->left);
  serializeEncryptTree(oFile, node->right);
}
