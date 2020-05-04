#include "EncrypterNode.h"

class Decrypter
{
public:
	FILE *treeFile;
	std::ifstream *inputFile;

	EncrypterNode *root;

	Decrypter(std::string fileName, std::string treeName);

	~Decrypter();

	void deserializeEncryptTree(EncrypterNode* &node);

	std::string Decode();
};
