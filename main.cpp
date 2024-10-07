#include "main.hpp"
#include <unordered_set>

int main()
{

    // for this test use : int ac, char **av
    // try {

    //     Parser parser = Parser(ac, av);

    //     std::vector<int> vec = parser.getPuzzle();

    //     NPuzzle puzzle(vec, MANHATTAN_DISTANCE);
    //     parser.parsing();

    //     puzzle.solve();
    //     return 0;

    // } catch (std::invalid_argument &e) {
    //     std::cout << e.what() << std::endl;
    //     return 1;
    // }

    try {

        // RandomGenerator gen;
        // gen.generateRandom(3);
        
        // for (int i : gen.getPuzzle())
        //     std::cout << i << " ";

        // std::cout << '\n';

        std::vector<int> v = {3, 1, 5, 8, 4, 0, 7, 2, 6};

        NPuzzle puzzle(v, EUCLEDIAN_DISTANCE);

        puzzle.solve();
        return 0;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
