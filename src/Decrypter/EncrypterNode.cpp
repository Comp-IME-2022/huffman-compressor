#include "EncrypterNode.h"

EncrypterNode::EncrypterNode()
{
    this->freq = 0;
    this->c = '\0';
    this->left = nullptr;
    this->right = nullptr;
}

EncrypterNode::EncrypterNode(char c, int freq)
{
    this->freq = freq;
    this->c = c;
    this->left = nullptr;
    this->right = nullptr;
}

EncrypterNode::EncrypterNode(EncrypterNode left, EncrypterNode right)
{

    this->freq = left.freq+right.freq;
    this->c = '\0';
 
    if (left.freq<right.freq){
        this->left = new EncrypterNode(left.c, left.freq);
        this->left->left = left.left;
        this->left->right = left.right;

        this->right = new EncrypterNode(right.c, right.freq);
        this->right->left = right.left;
        this->right->right = right.right;
    }

    else{
        this->left = new EncrypterNode(right.c, right.freq);
        this->left->left = right.left;
        this->left->right = right.right;

        this->right = new EncrypterNode(left.c, left.freq);
        this->right->left = left.left;
        this->right->right = left.right;
    }
}

EncrypterNode* EncrypterNode::getLeft()
{
    return this->left;
}

void EncrypterNode::setLeft(EncrypterNode* left)
{
    this->left = left;
}

EncrypterNode* EncrypterNode::getRight()
{
    return this->right;
}

void EncrypterNode::setRight(EncrypterNode* right)
{
    this->right = right;
}