#ifndef INPUTPARSER_HPP
#define INPUTPARSER_HPP

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

class InputParser{
    public:
        InputParser (int &argc, char **argv);

        // Get the value after an option like -file /path/to/file
        const std::string& getCmdFromOption(const std::string &option) const;
        // Check if option is found
        bool doesOptionExists(const std::string &option) const;
        bool isEmpty() const;
    private:
        std::vector <std::string> tokens;
};

#endif