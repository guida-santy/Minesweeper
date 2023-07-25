#include <iostream>
#include <algorithm>
#include "src/board.h"

int main() {
    using namespace board;
    board::Grid world;
    world.CreateGrid();

    world.Debug_PrintBoard();
    world.Debug_PrintGridForUser();
    std::string userInput{};
    bool running = true;
    while (running) {
        std::cout << "Please choose a coordinate to reveal (A1,B7,I8,etc)." << std::endl;
        std::cout << "Write it on the terminal and press enter." << std::endl;
        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
        world.Debug_PrintGridForUser();

        if (userInput == "Q") {
            std::cout << "\n End game" << std::endl;
            break;
        }

        if (userInput[0] >= 'A' && userInput[0] <= 'I' && userInput[1] >= '1' && userInput[1] <= '9') {
            const u_int colum = static_cast<int>(userInput[0]) - static_cast<int>('A') + 1;
            const u_int row = userInput[1] - '0';

            const std::vector<Cell>& revealedCells = world.GetCurrentReveledCells();
            const auto it = std::find_if(revealedCells.begin(), revealedCells.end(), [&](const Cell& cell) {
                return cell.GetGlobalPos() == std::make_pair(row, colum);
            });

            if (it != revealedCells.end()) {
                std::cout << "Coordinates already revealed." << std::endl;
                continue;
            } else {
                if(!world.EvaluateCoordinates(std::make_pair(row, colum))){
                    running = false;
                    std::cout << "Game lost :(" << std::endl;

                }
            }


        } else std::cout << "Invalid coordinates. Try again." << std::endl;

        world.Debug_PrintGridForUser();

    }

    return 0;
}
