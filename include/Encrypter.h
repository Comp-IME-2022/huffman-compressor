#include <queue>
#include <set>
#include <unordered_map>

#include "EncrypterNode.h"

class Encrypter {
  std::ifstream *inputFile;

  std::unordered_map<char, std::string> charToEncr;

  EncrypterNode *root;

  std::priority_queue<EncrypterNode> buildFreqQueue();

  void serializeCode(std::ofstream &);

  void serializeEncryptTree(std::ofstream &);

  void serializeEncryptTree(std::ofstream &, EncrypterNode *node);

 public:
  Encrypter(std::string fileName);

  ~Encrypter();

  void buildEncryptTree();

  void buildMap();

  void buildMap(EncrypterNode *node, std::string s);

  std::string getEncryption(char value);

  void writeFile(std::ofstream &);

  float getAverageCodeLength();
};
