#include "main.hpp"

int main(int ac, char **av)
{
    
	std::ifstream inputFile;
    inputFile.open(av[1]);
	if (inputFile.fail()) {
		
		throw std::invalid_argument("Wrong number of argument");
	}

    Parser parser = Parser(ac, av);
    
}
