#include "Predictor.hpp"

unsigned int getNumberByChar(char symbol) {
  if (symbol < firstSymbol || symbol >= firstSymbol + kAlphabetSize) {
    throw "Символ не из алфавита\n" ;
  }
  return symbol - firstSymbol;
}

char getCharByNumber(unsigned int number) {
  return char(firstSymbol + number);
}

Node::Node(Node* parent) : parent(parent),  max_frequency_under(1),
                          max_frequency_here(0)  {
  children.assign(kAlphabetSize, nullptr);
}

Node::~Node() {
  for (auto child : children) {
    delete child;
  }
}

TrieBasedPredictor::TrieBasedPredictor() : root_(Node(nullptr)) {
  root_.max_frequency_under = 0;
}

TrieBasedPredictor::TrieBasedPredictor(const std::string& word) : root_(Node(nullptr)) {
  root_.max_frequency_under = 0;
  AddWord(word);
}

TrieBasedPredictor::TrieBasedPredictor(const std::vector<std::string>& data) : root_(Node(nullptr)) {
  root_.max_frequency_under = 0;
  for (auto word : data) {
    AddWord(word);
  }
}

const Node* TrieBasedPredictor::getCorrespondingNode(const std::string& word) const {
  const Node* current = &root_;
  unsigned int position = 0;
  while (position < word.size() && current != nullptr) {
    current = current->children[getNumberByChar(word[position])];
    ++position;
  }
  return current;
}

void TrieBasedPredictor::AddWord(const std::string& new_word) {
  Node* current = &root_;
  unsigned int position = 0;
  while (position < new_word.size() &&
         current->children[getNumberByChar(new_word[position])] != nullptr) {
    current = current->children[getNumberByChar(new_word[position])];
    ++position;
  }
  while (position < new_word.size()) {
    current->children[getNumberByChar(new_word[position])] =
        new Node(current);
    current = current->children[getNumberByChar(new_word[position])];
    ++position;
  }
  current->max_frequency_here += 1;
  unsigned int updated_frequency = current->max_frequency_here;
  for (Node* node = current->parent; node != nullptr; node = node->parent) {
    if (node->max_frequency_under >= updated_frequency) {
      break;
    }
    node->max_frequency_under = updated_frequency;
  }
}

std::string TrieBasedPredictor::Predict(const std::string& prefix) {
  std::string prediction(prefix);
  const Node* prefixNode = getCorrespondingNode(prefix);
  if (prefixNode == nullptr) {
    throw "Невозможно продолжить полученный префикс\n";
  }
  while(true) {
    unsigned int current_max_frequency = prefixNode->max_frequency_here;
    int next_number = -1;
    for (unsigned int number = 0; number < prefixNode->children.size(); number++) {
      const Node* child = prefixNode->children[number];
      if (child == nullptr) {
        continue;
      }
      if (child->max_frequency_under > current_max_frequency) {
        current_max_frequency = child->max_frequency_under;
        next_number = number;
      }
    }
    if (next_number == -1) {
      break;
    }
    prediction += getCharByNumber(next_number);
    prefixNode = prefixNode->children[next_number];
  }
  return prediction;
}