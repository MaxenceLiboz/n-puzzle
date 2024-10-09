#include "main.hpp"
#include <unordered_set>

int main()
{

    // for this test use : int ac, char **av
    // try {

    //     Parser parser = Parser(ac, av);

    //     std::vector<int> vec = parser.getPuzzle();

    //     AStar puzzle(vec, MANHATTAN_DISTANCE);
    //     parser.parsing();

    //     puzzle.solve();
    //     return 0;

    // } catch (std::invalid_argument &e) {
    //     std::cout << e.what() << std::endl;
    //     return 1;
    // }

    try {
        // IDA puzzle(3, EUCLEDIAN_DISTANCE);

        std::vector<int> v = {2, 3, 0, 1, 6, 4, 8, 7, 5};
        IDA puzzle1(v, MANHATTAN_DISTANCE);
        // IDA puzzle2(v, EUCLEDIAN_DISTANCE);
        // IDA puzzle3(v, MISPLACED_TILES);

        // puzzle.solve();
        puzzle1.solve();
        // puzzle2.solve();
        // puzzle3.solve();
        return 0;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
