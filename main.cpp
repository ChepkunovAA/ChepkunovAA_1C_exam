#include "Interface.hpp"


int main() {
  TrieBasedPredictor predictor;
  ConsoleInterface interface(predictor);
  interface.RequestProcessing();
  return 0;
}
