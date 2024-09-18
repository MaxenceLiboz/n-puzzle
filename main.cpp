#include "main.hpp"
#include <unordered_set>

int main(int ac, char **av)
{

    std::priority_queue<Node *, std::vector<Node*>, CmpNodePtr> openList;
    std::unordered_set<std::vector<int>, HashNode> closedList;

    Parser parser = Parser(ac, av);

    try {

        parser.parsing();

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

	std::vector<int> vec = parser.getPuzzle();

	for (int i : vec)
		std::cout << i << ' ';

    NPuzzle puzzle(parser.getPuzzle(), MANHATTAN_DISTANCE);

    try {
        puzzle.solve();
        return 0;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
