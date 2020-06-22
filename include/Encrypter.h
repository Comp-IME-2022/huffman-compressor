#include <queue>
#include <set>
#include <unordered_map>

#include "EncrypterNode.h"

class Encrypter {
  std::ifstream *inputFile;

  std::priority_queue<EncrypterNode> freqQueue;

  std::unordered_map<char, std::string> charToEncr;

  EncrypterNode *root;

 public:
  Encrypter(std::string fileName);

  ~Encrypter();

  void buildFreqSet();

  void buildEncryptTree();

  void buildMap();

  void buildMap(EncrypterNode *node, std::string s);

  std::string getEncryption(char value);

  void getEncryption(std::string outFile);

  void serializeEncryptTree(std::ofstream &);

  void serializeEncryptTree(std::ofstream &, EncrypterNode *node);
};
