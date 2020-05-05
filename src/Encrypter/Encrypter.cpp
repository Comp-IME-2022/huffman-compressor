#include <fstream>
#include <iostream>
#include <map>
#include <string>
#define MARKER -1

#include "Encrypter.h"

Encrypter::Encrypter(std::string inputName, std::string treeName)
{
    this->inputFile = new std::ifstream(inputName.c_str(), std::ios_base::in);
    this->treeFile = new std::ofstream(treeName.c_str(), std::ios_base::out);
}

Encrypter::~Encrypter()
{
    (*this->inputFile).close();
    (*this->treeFile).close();

    delete this->inputFile;
    delete this->treeFile;
}

void Encrypter::buildFreqSet()
{

    char c;
    std::map<char, int> freqMap;
    std::map<char, int>::iterator mapItr;

    while(true)
    {

        (*this->inputFile) >> c;
     
        if((*this->inputFile).eof()){
            break;
        }

        if(freqMap.find(c) == freqMap.end())
        {
            freqMap[c] = 1;
        }
        else
        {
            freqMap[c]++;
        }

    }

    for(mapItr = freqMap.begin(); mapItr != freqMap.end(); mapItr++)
    {
        this->freqQueue.push(EncrypterNode(mapItr->first, mapItr->second));
    }


}

bool operator<(const EncrypterNode& x,const EncrypterNode& y){
    return x.freq>y.freq;
}

void Encrypter::buildEncryptTree()
{
    while(this->freqQueue.size()>1){

        EncrypterNode a = this->freqQueue.top();
        this->freqQueue.pop();

        EncrypterNode b = this->freqQueue.top();
        this->freqQueue.pop();

        EncrypterNode* sum = new EncrypterNode(a, b);


        this->freqQueue.push(*sum);
    }

    this->root = new EncrypterNode(*this->freqQueue.top().left, *this->freqQueue.top().right);
    this->root->freq = this->freqQueue.top().freq;
    this->root->c = this->freqQueue.top().c;

}

void Encrypter::buildMap()
{
    buildMap(this->root, "");
}

void Encrypter::buildMap(EncrypterNode* node, std::string s){

    if(node->left==nullptr and node->right==nullptr){
        this->charToEncr[node->c] = s;
        return;
    }

    buildMap(node->left, s+"0");
    buildMap(node->right, s+"1");

}

std::string Encrypter::getEncryption(char value){
    return this->charToEncr[value];
}

void Encrypter::getEncryption(std::string outFile){

    (*this->inputFile).clear();
    (*this->inputFile).seekg(0);
    
    std::ofstream savefile(outFile, std::ios_base::binary);

    char c;
    std::map<char, int> freqMap;
    std::map<char, int>::iterator mapItr;

    uint8_t carry=0, place = 0;
    while(true)
    {

        (*this->inputFile) >> c;

        if((*this->inputFile).eof()){
            break;
        }

        for(char e: this->getEncryption(c))
        {
            
            if(place==8)
            {
                savefile.write((char*)&carry, sizeof(carry));
                carry=0;
                place=0;
            }
            carry += ((e=='1')<<place);
            place++;
        }
    }
    
    savefile.write((char*)&carry, sizeof(carry));
    savefile.write((char*)&place, sizeof(place));
    
    savefile.close();
}

void Encrypter::serializeEncryptTree()
{
    serializeEncryptTree(this->root);
}

void Encrypter::serializeEncryptTree(EncrypterNode* node)
{

    if(node == nullptr)
    {
        (*this->treeFile) << MARKER;
        (*this->treeFile) << " ";
        return;
    }

    (*this->treeFile) <<  (int)node->c;
    (*this->treeFile) << " ";
    serializeEncryptTree(node->left);
    serializeEncryptTree(node->right);
}