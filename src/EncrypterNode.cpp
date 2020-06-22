#include "EncrypterNode.h"

#include <algorithm>

EncrypterNode::EncrypterNode(char c, int freq) {
  this->freq = freq;
  this->c = c;
  this->left = nullptr;
  this->right = nullptr;
}

EncrypterNode::EncrypterNode(const EncrypterNode& node) {
  this->freq = node.freq;
  this->c = node.c;
  this->left = node.left;
  this->right = node.right;
}

EncrypterNode::EncrypterNode(EncrypterNode left, EncrypterNode right) {
  this->freq = left.freq + right.freq;
  this->c = '\0';

  if (right.freq >= left.freq) std::swap(left, right);

  this->left = new EncrypterNode(left);

  this->right = new EncrypterNode(right);
}
