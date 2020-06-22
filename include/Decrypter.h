#include "EncrypterNode.h"

class Decrypter {
  // File where the huffman tree is stored
  // Binary file compressed by the encrypter
  std::ifstream *inputFile;

  // Root of the huffman tree
  EncrypterNode *root;

 public:
  Decrypter(std::string fileName);

  ~Decrypter();

  void deserializeEncryptTree(std::ifstream &);

  void deserializeEncryptTree(std::ifstream &, EncrypterNode *&);

  void decode(std::ofstream &);
};
