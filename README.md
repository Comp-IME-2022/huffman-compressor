# Huffman Compressor

This repository is an implementation of a Huffman Compressor based on [this](youtube.com/watch?v=JsTptu56GM8) video by Tom Scott.

## Usage

To build the encrypter and decrypter executables:

```
make -f MakefileEncrypter
make -f MakefileDecrypter
```
This commands will create 2 executables in the `/bin` folder.

The usage of the `Encrypter`is as follows:

- If 1 parameter is passed, then it compresses this file to output.bin and stores the Huffman tree at treeStore.txt;

- Else if 2 parameters are passed, then it compresses the first file into the second one and stores the tree at treeFile.txt;

- Else if 3 parameters are passed, then it compresses the first file into the second one and stores the three at the third;

- Else raises error.

The `Decrypter` can be used with 2 to 3 parameters:

- If 2 parameters are passed, then it decompresses the first file using the second one as the tree file and writes the output to decompressed.txt;

- Else if 3 parameters are passed, then it decompressed the first file using the second one as the tree file and writes the output to the third file;

- Else raises error.

