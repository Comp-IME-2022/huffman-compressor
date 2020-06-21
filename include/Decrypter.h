#include "EncrypterNode.h"

class Decrypter {
  // File where the huffman tree is stored
  // Binary file compressed by the encrypter
  std::ifstream *inputFile, *treeFile;

  // Root of the huffman tree
  EncrypterNode *root;

 public:
  Decrypter(std::string fileName, std::string treeName);

  ~Decrypter();

  void deserializeEncryptTree();

  void deserializeEncryptTree(EncrypterNode *&node);

  void decode(std::string outName);
};
