#include <unordered_map>
#include <set>
#include <queue>
#include "EncrypterNode.h"

class Encrypter
{

	std::ifstream *inputFile;
	std::ofstream *treeFile;

	std::priority_queue<EncrypterNode> freqQueue;
	
	std::unordered_map<char, std::string> charToEncr;

	EncrypterNode *root;

public:

	Encrypter(std::string fileName, std::string treeName);

	~Encrypter();

	void buildFreqSet();

	void buildEncryptTree();

	void buildMap();

	void buildMap(EncrypterNode* node, std::string s);
	
	std::string getEncryption(char value);

	void getEncryption(std::string outFile);

	void serializeEncryptTree();

	void serializeEncryptTree(EncrypterNode* node);

};