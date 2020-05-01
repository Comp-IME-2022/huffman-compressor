#include <map>
#include <set>
#include <queue>
#include "EncrypterNode.h"

class Encrypter{
public:
	FILE *inputFile, *treeFile;

	std::priority_queue<EncrypterNode> freqQueue;
	std::map<char, std::string> charToEncr;

	EncrypterNode *root;

	Encrypter(std::string fileName, std::string treeName);

	~Encrypter();

	void buildFreqSet();

	void buildEncryptTree();

	void buildMap(EncrypterNode* node, std::string s);
	
	std::string getEncryption(char value);

	void getEncryption(std::string outFile);

	void serializeEncryptTree(EncrypterNode* node);

};