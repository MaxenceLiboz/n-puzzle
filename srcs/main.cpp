#include "main.hpp"
#include <unordered_set>

int main(int argc, char **argv)
{
    try {

        InputParser input = InputParser(argc, argv);

        if ( input.isEmpty() || input.doesOptionExists("-h")) {
            std::cout << "Multiple options are available :" << std::endl;
            std::cout << "-a to chose between the two algorithm : Astar: 0 or IDA: 1" << std::endl;
            std::cout << "-hx to chose the heuristic : MANHATTAN_DISTANCE: 0, EUCLEDIAN_DISTANCE: 1, MISPLACED_TILES: 2" <<std::endl;
            std::cout << "-g in order to generate a random solvable puzzle, enter the dimention next : [3-n]." << std::endl;
            std::cout << "-f in order to chose a file for the puzzle, enter the file path next : /path/to/file." << std::endl;
            return 0;
        } else {
            const std::string algo = input.getCmdFromOption("-a");
            Heuristic heuristic = getHeuristicFromValue(input.getCmdFromOption("-hx"));
            const std::string generator = input.getCmdFromOption("-g");
            const std::string file = input.getCmdFromOption("-f");

            if (algo == "0" && !generator.empty()) {
                NPuzzle aStar = NPuzzle(std::atoi(generator.data()), heuristic);
                aStar.solve();
                return 0;
            } else if (algo == "0" && !file.empty()) {
                Parser parser = Parser(file, heuristic);
                parser.parsing();

                NPuzzle puzzle(parser.getPuzzle(), MANHATTAN_DISTANCE);
                puzzle.solve();
                return 0;
            } else if (algo == "1" && !generator.empty()) {
                return 0;
            } else if (algo == "1" && !file.empty()) {
                Parser parser = Parser(file, heuristic);                
                parser.parsing();
                return 0;
            }
            else {
                std::cout << "Multiple options are available:" << std::endl;
                std::cout << "-a to chose between the two algorithm: Astar: 0 or IDA: 1" << std::endl;
                std::cout << "-hx to chose the heuristic: MANHATTAN_DISTANCE: 0, EUCLEDIAN_DISTANCE: 1, MISPLACED_TILES: 2" <<std::endl;
                std::cout << "-g in order to generate a random solvable puzzle, enter the dimention next: [3-n]." << std::endl;
                std::cout << "-f in order to chose a file for the puzzle, enter the file path next: /path/to/file." << std::endl;
                return 0;
            }
        }
    } catch (std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Use -h for help" << std::endl;
        return 1;
    } catch (std::exception &e) {
        std::cout << "Use -h for help" << std::endl;
    }
}
