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
        NPuzzle puzzle(3, MANHATTAN_DISTANCE);

        // std::vector<int> v = {7, 8, 2, 6, 4, 5, 1, 3, 0};
        // std::vector<int> v = {0, 2, 4, 8, 1, 3, 7, 6, 5};
        // std::vector<int> v = {1, 6, 3, 4, 8, 0, 7, 2, 5};

        // 1, 2, 3, 8, 0, 4, 7, 6, 5
        // std::vector<int> v;
        // int num;
        // while (std::cin >> num) {
        //     std::cout << num << ", ";
        //     v.push_back(num);
        // }
        // std::cout << std::endl;
        // NPuzzle puzzle(v, MANHATTAN_DISTANCE);

        puzzle.solve();
        return 0;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
