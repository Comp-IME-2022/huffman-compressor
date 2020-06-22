#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define MARKER -1

#include "Decrypter.h"

Decrypter::Decrypter(std::string fileName) {
  this->inputFile = new std::ifstream(fileName.c_str(), std::ios_base::binary);

  this->root = nullptr;
}

Decrypter::~Decrypter() {
  (*this->inputFile).close();

  delete this->inputFile;
}

void Decrypter::deserializeEncryptTree(std::ifstream& iFile) {
  deserializeEncryptTree(iFile, this->root);
}

void Decrypter::deserializeEncryptTree(std::ifstream& iFile,
                                       EncrypterNode*& node) {
  int val;

  iFile >> val;

  if (iFile.eof() || val == MARKER) {
    return;
  }

  node = new EncrypterNode((char)val, 0);

  deserializeEncryptTree(iFile, node->left);
  deserializeEncryptTree(iFile, node->right);
}

void Decrypter::decode(std::ofstream& outFile) {
  int val;
  std::vector<int> v;
  std::string s;
  auto errorCode = [&outFile]() {
    std::cerr << "Error while decoding!" << std::endl;

    outFile << "Error";

    outFile.close();
  };

  EncrypterNode* node = this->root;

  while (true) {
    val = (*(this->inputFile)).get();

    if (val == EOF) {
      break;
    }

    v.push_back(val);
  }

  for (unsigned int i = 0; i < v.size() - 1; i++) {
    int end = i == v.size() - 2 ? *v.rbegin() : 8;

    for (int place = 0; place < end; place++) {
      if (v[i] & (1 << place)) {
        if (node->right == nullptr) {
          errorCode();
          return;
        }

        node = node->right;

      }

      else {
        if (node->left == nullptr) {
          errorCode();
          return;
        }

        node = node->left;
      }

      if (node->left == nullptr and node->right == nullptr) {
        s += node->c;
        node = this->root;
      }
    }
  }

  outFile << s;

  outFile.close();
}
