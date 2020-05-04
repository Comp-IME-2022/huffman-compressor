#include <iostream>

#include "Decrypter.h"

int main(int argc, char *argv[])
{

	std::string inputFile, treeFile, outFile = "decompressed.txt";

	if(argc==1)
	{
		std::cout << "No input file passed" << std::endl;
		return 0;
	}

	else if(argc==2)
	{
		std::cout << "No tree file passed" << std::endl;
		return 0;
	}

	inputFile = argv[1];
	treeFile = argv[2];

	Decrypter *dec = new Decrypter(inputFile, treeFile);

	dec->deserializeEncryptTree(dec->root);

	std::cout << dec->Decode() << std::endl;

	return 0;
}