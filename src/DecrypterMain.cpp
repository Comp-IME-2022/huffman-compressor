#include <chrono>
#include <fstream>
#include <iostream>

#include "Decrypter.h"

bool file_exists(char *name) {
  std::ifstream f(name);
  return f.good() and !(f.peek() == std::ifstream::traits_type::eof());
}

bool errorHandler(int argc, char *argv[], std::string &inputFile,
                  std::string &outName) {
  if (argc == 1) {
    std::cout << "No input file passed" << std::endl;
    return 1;
  }

  else if (argc > 3) {
    std::cout << "More than 2 files passed" << std::endl;
    return 1;
  }

  else {
    if (not file_exists(argv[1])) {
      std::cout << "Input file doesn't exists or is empty" << std::endl;
      return 1;
    }

    if (argc == 2) {
      std::cout << "Output file not specified" << std::endl;
      outName = "decompressed.txt";
    }

    else {
      outName = argv[2];
    }

    std::cout << "Writing output to " << outName << std::endl;

    inputFile = argv[1];

    return 0;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  std::string inputFile, outName;

  if (errorHandler(argc, argv, inputFile, outName)) {
    return 0;
  }

  std::ofstream outFile(outName);

  Decrypter *dec = new Decrypter(inputFile);

  dec->deserializeEncryptTree();

  dec->decode(outFile);

  delete dec;

  return 0;
}
