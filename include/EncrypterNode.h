class EncrypterNode {
 public:
  int freq;

  char c;

  EncrypterNode *left, *right;

  EncrypterNode(const EncrypterNode&);

  EncrypterNode(char c, int freq);

  EncrypterNode(EncrypterNode left, EncrypterNode right);

  friend bool operator<(const EncrypterNode& x, const EncrypterNode& y) {
    return x.freq > y.freq;
  }

  friend EncrypterNode operator+(const EncrypterNode& x,
                                 const EncrypterNode& y) {
    EncrypterNode sum(x, y);
    return sum;
  }
};
