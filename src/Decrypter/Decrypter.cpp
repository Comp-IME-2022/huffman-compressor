#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define MARKER -1

#include "Decrypter.h"


Decrypter::Decrypter(std::string fileName, std::string treeName)
{
	this->inputFile = new std::ifstream(fileName.c_str(), std::ios_base::binary);
    this->treeFile = fopen(treeName.c_str(), "r");
    this->root = nullptr;
}

Decrypter::~Decrypter()
{
	free(this->inputFile);
	fclose(this->treeFile);
}

void Decrypter::deserializeEncryptTree()
{
	deserializeEncryptTree(this->root);
}

void Decrypter::deserializeEncryptTree(EncrypterNode *&node)
{
	int val;

	if(!fscanf(this->treeFile, "%d ", &val) || val==MARKER)
	{
		return;
	}

	node = new EncrypterNode((char) val, 0);

	deserializeEncryptTree(node->left);
	deserializeEncryptTree(node->right);
}


void Decrypter::decode(std::string outName)
{

	std::ofstream outFile(outName.c_str(), std::ios_base::out);

	int val, carry;
	std::vector<int> v;

	EncrypterNode* node = this->root;

	std::string s;
	
	while(true)
	{
		val = (*(this->inputFile)).get();
		
		if(val==EOF)
		{
			break;
		}

		v.push_back(val); 
	}

	for(int i=0;i<v.size()-1;i++)
	{
		int end = 8;

		if(i==v.size()-2)
		{
			end = *v.rbegin();
		}

		for(int place=0;place<end;place++)
		{
			if(v[i]&(1<<place))
			{
				if(node->right==nullptr)
				{
					std::cerr << "Error while decoding!" << std::endl;
					s = "Error";

					outFile << s;

					outFile.close();

					return;
				}

				node = node->right;

			}

			else
			{
				if(node->left==nullptr)
				{
					std::cerr << "Error while decoding!" << std::endl;
					s = "Error";

					outFile << s;

					outFile.close();
					
					return;
				}

				node = node->left;
			}

			if(node->left==nullptr and node->right==nullptr)
			{
				s+=node->c;
				node = this->root;
			}
		}
	}

	outFile << s;

	outFile.close();
}
