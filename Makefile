CC := g++ # This is the main compiler
SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGETENC := bin/Encrypter
TARGETDEC := bin/Decrypter
 
SRCEXT := cpp
SOURCESENC := $(shell find $(SRCDIR) -type f -name Encrypter*.$(SRCEXT))
SOURCESDEC := $(shell find $(SRCDIR) -type f -name Decrypter*.$(SRCEXT) && echo $(SRCDIR)/"EncrypterNode.cpp")

.PHONY: all
all: format encrypter decrypter

.PHONY: format
format:	
	clang-format $(SRCDIR)/* $(INCDIR)/* -i

.PHONY: encrypter
encrypter: $(SOURCESENC)
	mkdir -p bin
	$(CC) -o $(TARGETENC) $(SOURCESENC) -I$(INCDIR)

.PHONY: decrypter
decrypter: $(SOURCESDEC)
	mkdir -p bin
	$(CC) -o $(TARGETDEC) $(SOURCESDEC) -I$(INCDIR)


