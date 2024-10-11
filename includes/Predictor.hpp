#include "Abstract.hpp"

#include <vector>

// Параметры латинского алфавита
const int kAlphabetSize = 26;
const char firstSymbol = 'a';

unsigned int getNumberByChar(char symbol);

char getCharByNumber(unsigned int number);

struct Node {
  Node* parent;
  unsigned int max_frequency_under;
  unsigned int max_frequency_here;
  std::vector<Node*> children;

  Node(Node* parent);

  ~Node();
};

class TrieBasedPredictor : public Predictor {
 public:
  TrieBasedPredictor();
  TrieBasedPredictor(const std::string& word);
  TrieBasedPredictor(const std::vector<std::string>& data);

  const Node* getRoot() const { return &root_; }

  const Node* getCorrespondingNode(const std::string& word) const;

  void AddWord(const std::string& new_word);

  std::string Predict(const std::string& prefix);

 private:
  Node root_;
};