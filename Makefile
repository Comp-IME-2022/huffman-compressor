CC := clang++ # This is the main compiler
SRCDIR := src
INCDIR := include
CFLAGS := -Wall -std=c++14
BUILDDIR := build
TARGETENC := bin/Encrypter
TARGETDEC := bin/Decrypter
 
SRCEXT := cpp
SOURCESENC := $(shell find $(SRCDIR) -type f -name Encrypter*.$(SRCEXT))
SOURCESDEC := $(shell find $(SRCDIR) -type f -name Decrypter*.$(SRCEXT) && echo $(SRCDIR)/"EncrypterNode.cpp")

.PHONY: all
all: format test encrypter decrypter

.PHONY: format
format:	
	clang-format $(SRCDIR)/* $(INCDIR)/* -i

.PHONY: test
test:
	cd test && bash test1.sh && bash test2.sh

.PHONY: encrypter
encrypter: $(SOURCESENC)
	mkdir -p bin
	$(CC) -o $(TARGETENC) $(SOURCESENC) -I$(INCDIR) $(CFLAGS)

.PHONY: decrypter
decrypter: $(SOURCESDEC)
	mkdir -p bin
	$(CC) -o $(TARGETDEC) $(SOURCESDEC) -I$(INCDIR) $(CFLAGS)


