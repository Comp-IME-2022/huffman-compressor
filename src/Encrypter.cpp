#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#define MARKER -1

#include "Encrypter.h"

Encrypter::Encrypter(std::string inputName) {
  this->inputFile = new std::ifstream(inputName.c_str(), std::ios_base::in);
  std::noskipws(*this->inputFile);
}

Encrypter::~Encrypter() {
  (*this->inputFile).close();

  delete this->inputFile;
}

void Encrypter::buildFreqSet() {
  std::unordered_map<char, int> freqMap;

  std::string inputContent{std::istreambuf_iterator<char>{*this->inputFile},
                           {}};

  std::for_each(inputContent.begin(), inputContent.end(), [&freqMap](char c) {
    freqMap.find(c) == freqMap.end() ? freqMap[c] = 1 : freqMap[c]++;
  });

  std::for_each(freqMap.begin(), freqMap.end(), [this](auto x) {
    this->freqQueue.push(EncrypterNode(x.first, x.second));
  });
}

bool operator<(const EncrypterNode& x, const EncrypterNode& y) {
  return x.freq > y.freq;
}

void Encrypter::buildEncryptTree() {
  while (this->freqQueue.size() > 1) {
    EncrypterNode a = this->freqQueue.top();
    this->freqQueue.pop();

    EncrypterNode b = this->freqQueue.top();
    this->freqQueue.pop();

    EncrypterNode* sum = new EncrypterNode(a, b);

    this->freqQueue.push(*sum);
  }

  this->root = new EncrypterNode(*this->freqQueue.top().left,
                                 *this->freqQueue.top().right);
  this->root->freq = this->freqQueue.top().freq;
  this->root->c = this->freqQueue.top().c;
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
        savefile.write((char*)&carry, sizeof(carry));
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
  if (node == nullptr) {
    oFile << MARKER;
    oFile << " ";
    return;
  }

  oFile << (int)node->c;
  oFile << " ";
  serializeEncryptTree(oFile, node->left);
  serializeEncryptTree(oFile, node->right);
}
