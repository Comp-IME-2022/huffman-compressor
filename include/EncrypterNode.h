class EncrypterNode {
 public:
  int freq;

  char c;

  EncrypterNode *left, *right;

  EncrypterNode();

  EncrypterNode(char c, int freq);

  EncrypterNode(EncrypterNode left, EncrypterNode right);

  EncrypterNode* getLeft();

  void setLeft(EncrypterNode* left);

  EncrypterNode* getRight();

  void setRight(EncrypterNode* right);

  EncrypterNode* operator+(EncrypterNode x);
};