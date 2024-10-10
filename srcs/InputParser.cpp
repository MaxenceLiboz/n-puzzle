#include "InputParser.hpp"

InputParser::InputParser(int &argc, char **argv) {
    for (int i=1; i < argc; ++i) {
        this->tokens.push_back(std::string(argv[i]));
    }
}

const std::string& InputParser::getCmdFromOption(const std::string &option) const {
    std::vector<std::string>::const_iterator itr;
    itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
    }
    // static const is used so it is created only once for the class and address can be returned.
    static const std::string empty_string("");
    return empty_string;
}

bool InputParser::doesOptionExists(const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}

bool InputParser::isEmpty() const {
    return tokens.empty();
}

