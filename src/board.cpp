#include "board.h"
#include <iostream>
#include <random>
#include <set>
#include <algorithm>

void board::Grid::SetBombs() {
    int bombs = 0;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 9);

    while (bombs < _numberOfBombs) {
        int row = distribution(generator);
        int column = distribution(generator);

        if (_fullGrid[row][column].GetType() != cellType::bomb) {
            bombs++;
            _fullGrid[row][column].SetType(cellType::bomb);
        }

    }

}

void board::Grid::CreateGrid() {
    _runningDebug = true;
    SetBombs();

    // Set states
    // Function to count bombs in the 3x3 window around a cell
    auto countBombsInWindow = [&](int row, int col) {
        int bombCount = 0;
        // Loop over a 3x3 window around the cell (row, col)
        for (int r = std::max(1, row - 1); r <= std::min(_rows, row + 1); ++r) {
            for (int c = std::max(1, col - 1); c <= std::min(_columns, col + 1); ++c) {
                bombCount += (_fullGrid[r][c].GetType() == cellType::bomb) ? 1
                                                                           : 0; // Convert bool to int (1 for true, 0 for false)
            }
        }
        return bombCount;
    };


    // Calculate the state for each cell using std::accumulate
    for (int r = 1; r <= _rows; ++r) {
        for (int c = 1; c <= _columns; ++c) {
            _fullGrid[r][c].SetState(countBombsInWindow(r, c));
        }
    }

}

void board::Grid::RevelCell(const int row, int const col) {
    // TODO: make recursive safe somehow ... (iterative method might be the best alternative)
    if (row < 1 || row > _rows || col < 1 || col > _columns || _fullGrid[row][col].WasCellReveled()) {
        return;
    }
    _fullGrid[row][col].RevelCell();
    _numberOfReveledCells++;

    // Se a célula selecionada tiver _state igual a 0, revele células vizinhas.
    if (_fullGrid[row][col].GetState() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                RevelCell(row + i, col + j);
            }
        }
    }
}


bool board::Grid::EvaluateCoordinates(const int row, const int col) {
    if (_fullGrid[row][col].GetType() == cellType::bomb) {
        _runningDebug = false;
        return false;
    }

    RevelCell(row, col);
    return true;
}

void board::Grid::Debug_PrintBoard() {
    for (int r = 1; r <= _rows; ++r) {
        for (int c = 1; c <= _columns; ++c) {
            if (_fullGrid[r][c].GetType() == board::cellType::normal) {
                std::cout << "[" << _fullGrid[r][c].GetState() << "]" << " ";
            } else std::cout << "[B]" << " ";
        }
        std::cout << "\n";
    }

}

void board::Grid::Debug_PrintGridForUser() {
    std::cout << std::endl;
    std::cout << "   A   B   C   D   E   F   G   H   I" << std::endl;
    for (int r = 1; r <= _rows; ++r) {
        std::cout << r << " ";
        for (int c = 1; c <= _columns; ++c) {
            if (!_runningDebug && _fullGrid[r][c].GetType() == board::cellType::bomb) {
                std::cout << "[B]" << " ";

            } else if (_fullGrid[r][c].GetType() == board::cellType::normal && _fullGrid[r][c].WasCellReveled() || !_runningDebug) {
                std::cout << "[" << _fullGrid[r][c].GetState() << "]" << " ";
            } else std::cout << "[X]" << " ";
        }
        std::cout << "\n";
    }
}