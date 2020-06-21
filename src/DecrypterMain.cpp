#include <chrono>
#include <fstream>
#include <iostream>

#include "Decrypter.h"

bool file_exists(char *name) {
  std::ifstream f(name);
  return f.good() and !(f.peek() == std::ifstream::traits_type::eof());
}

bool errorHandler(int argc, char *argv[], std::string &inputFile,
                  std::string &treeFile, std::string &outName) {
  if (argc == 1) {
    std::cout << "No input file passed" << std::endl;
    return 1;
  }

  else if (argc == 2) {
    std::cout << "No tree file passed" << std::endl;
    return 1;
  }

  else if (argc > 4) {
    std::cout << "More than 3 files passed" << std::endl;
    return 1;
  }

  else {
    if (not file_exists(argv[1])) {
      std::cout << "Input file doesn't exists or is empty" << std::endl;
      return 1;
    }

    if (not file_exists(argv[2])) {
      std::cout << "Tree file doesn't exists or is empty" << std::endl;
      return 1;
    }

    if (argc == 3) {
      std::cout << "Output file not specified" << std::endl;
      outName = "decompressed.txt";
    }

    else {
      outName = argv[3];
    }

    std::cout << "Writing output to " << outName << std::endl;

    inputFile = argv[1];
    treeFile = argv[2];

    return 0;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  std::string inputFile, treeFile, outName;

  if (errorHandler(argc, argv, inputFile, treeFile, outName)) {
    return 0;
  }

  Decrypter *dec = new Decrypter(inputFile, treeFile);

  dec->deserializeEncryptTree();

  dec->decode(outName);

  delete dec;

  return 0;
}