#include <string>

class Predictor {
 public:
  virtual void AddWord(const std::string& new_word) = 0;

  virtual std::string Predict(const std::string& prefix) = 0;
};

class Interface{
 public:
  Interface(Predictor& predictor);
  virtual void RequestProcessing() = 0;
 protected:
  Predictor* predictor_ptr_;
};