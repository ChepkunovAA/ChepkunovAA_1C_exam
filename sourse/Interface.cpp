#include "Interface.hpp"

ConsoleInterface::ConsoleInterface(Predictor& predictor) :  Interface{predictor} {
  std::cout << "Введите слова языка Na'vi латиницей через пробел\n";
  std::string input;
  std::getline(std::cin, input);

  std::istringstream iss(input);
  std::vector<std::string> words;
  std::string word;
  while (iss >> word) {
      try {
        predictor.AddWord(word);
      } catch (const char* error_message) {
        std::cout << "Ошибка при записи слова " << word << "! " << error_message;
      }
  }
}

void ConsoleInterface::RequestProcessing() {
  std::string prefix = "";
  std::cout << "Введите префикс. Далее, для добавления нового слова введите перед ним +, "
                        "для сброса текущего префикса нажмите -, для дополнения текущего префикса "
                        "введите символы дополнения. Для выхода введите 0.\n";
  Mode mode = Mode::AddToPrefix;
  while(true) {
    std::string input, word;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    iss >> word;
    if (word == "0") {
      break;
    }
    if (word == "-") {
      mode =  Mode::AddToPrefix;
      prefix = "";
      std::cout << "Префикс сброшен\n";
      continue;
    }
    if (word == "+") {
      mode = Mode::NewWord;
      iss >> word;
    }
    try {
      if (mode ==  Mode::AddToPrefix) {
        std::string prediction = predictor_ptr_->Predict(prefix + word);
        std::cout << "Вероятно это " << prediction << '\n';
        prefix += word;
      } else {
          predictor_ptr_->AddWord(word);
          mode = Mode::AddToPrefix;
          std::cout << "Слово \"" << word << "\" добавлено!\n";
      }
    } catch (const char* error_message) {
        std::cout << "Ошибка! " << error_message;
    }
    std::cout << "Текущий префикс - \"" << prefix << "\". Дополнить префикс?\n";
  }
}