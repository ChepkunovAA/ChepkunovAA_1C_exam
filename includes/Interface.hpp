#include "Predictor.hpp"

#include <iostream>
#include <sstream>
#include <vector>

enum class Mode {AddToPrefix, NewWord};

class ConsoleInterface : public Interface {
 public:
  ConsoleInterface(Predictor& predictor);
  void RequestProcessing() override;
};