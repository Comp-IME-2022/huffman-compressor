class EncrypterNode {
 public:
  int freq;

  char c;

  EncrypterNode *left, *right;

  EncrypterNode(const EncrypterNode &);

  EncrypterNode(char c, int freq);

  EncrypterNode(EncrypterNode left, EncrypterNode right);
};
