#include <iostream>
#include <algorithm>
#include "src/board.h"

int main() {
    using namespace board;
    board::Grid world;
    world.CreateGrid();

    world.Debug_PrintBoard();

    std::string userInput{};
    bool running = true;
    std::cout << "Please choose a coordinate to reveal (A1,B7,I8,etc) or 'Q' to quit game." << std::endl;
    std::cout << "Write it on the terminal and press enter." << std::endl;
    world.Debug_PrintGridForUser();

    while (running) {
        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

        if (userInput == "Q") {
            std::cout << "\n End game" << std::endl;
            break;
        }

        if (userInput[0] >= 'A' && userInput[0] <= 'I' && userInput[1] >= '1' && userInput[1] <= '9') {
            const int colum = static_cast<int>(userInput[0]) - static_cast<int>('A') + 1;
            const int row = userInput[1] - '0';

            if (world.CellAlreadyReveled(row, colum)) {
                std::cout << "Coordinates already revealed.Please enter new coordinates." << std::endl;
                continue;
            }
            else {
                if (!world.EvaluateCoordinates(row, colum)) {
                    running = false;
                    std::cout << "Game lost :(" << std::endl;

                } else {
                    auto totalCells = world.GetColumns() * world.GetRows() - world.GetNumberCellsReveled() - world.GetNumberOfBombs();
                    if (totalCells == 0) {
                        std::cout << std::endl;
                        std::cout << "***********************" << std::endl;
                        std::cout << "  >>>>> YOU WIN <<<<<" << std::endl;
                        std::cout << "***********************" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                }
            }
        } else std::cout << "Invalid coordinates. Try again." << std::endl;

        world.Debug_PrintGridForUser();
    }

    return 0;
}
