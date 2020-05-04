# Huffman Compressor

This repository is an implementation of a Huffman Compressor based on [this](youtube.com/watch?v=JsTptu56GM8) video by Tom Scott: 

## Usage

Run the command `make` using the `-f` flag to specify which makefile to build (MakefileEncrypter or MakefileDecrypter) in the project directory to compile either the encrypter or the decrypter, it will create executables called Encrypter and Decrypter at `/bin`. The Ecnrypter can be used with 1 to 3 parameters:

- If 1 parameter is passed, then it compresses this file to output.bin and stores the Huffman tree at treeStore.txt

- If 2 parameters are passed, then it compresses the first file into the second one and stores the tree at treeStore.txt

- If 3 parameters are passed, then it compresses the first file into the second one and stores the three at the third



