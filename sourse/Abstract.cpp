#include "Abstract.hpp"

/*void Predictor::AddWord(const std::string& new_word) = delete;

std::string Predictor::Predict(const std::string& prefix) = delete;*/

Interface::Interface(Predictor& predictor) : predictor_ptr_(&predictor) {}

//void Interface::RequestProcessing() = delete;