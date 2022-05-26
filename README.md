# Huffman Compressor

This repository is an implementation of a Huffman Compressor based on [this](youtube.com/watch?v=JsTptu56GM8) video by Tom Scott.

## Usage

To build the encrypter and decrypter executables:

```
make
```
This commands will create 2 executables in the `/bin` folder.

The usage of the `Encrypter`is as follows, if you are in root directory of the project:

```
bin/Encrypter in.txt [out.bin]
```

- If 1 parameter is passed, then it compresses this file to output.bin;

- Else if 2 parameters are passed, then it compresses the first file into the second one;

- Else raises error.

The `Decrypter` can be used with 1 to 2 parameters:

```
bin/Decrypter out.bin [in.txt]
```

- If 1 parameter is passed, then it decompresses the file to decompressed.txt;

- Else if 2 parameters are passed, then it decompressed the first file to the second one;

- Else raises error.
