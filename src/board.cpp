#include "board.h"
#include <iostream>
#include <random>
#include <set>
#include <algorithm>

void board::Grid::SetBombs() {
    std::set<std::pair<int, int>> bombs;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 9);

    while (bombs.size() < _numberOfBombs) {
        int row = distribution(generator);
        int column = distribution(generator);

        if (bombs.find(std::make_pair(row, column)) == bombs.end()) {
            bombs.insert(std::make_pair(row, column));
            Cell newCell(std::make_pair(row, column), board::cellType::bomb);
            _bombIngrid.push_back(newCell);
        }
    }


}

void board::Cell::SetState(Cell cell) {
    cell._state = 0;
}

void board::Grid::CreateGrid() {
    _runningDebug = true;
    SetBombs();
    for (u_int r = 1; r <= _columns; r++) {
        for (u_int c = 1; c <= _rows; c++) {
            const auto cellIter = std::find_if(_bombIngrid.begin(), _bombIngrid.end(), [&](Cell &cell) {
                return cell.GetGlobalPos() == std::make_pair(r, c);
            });
            if (cellIter == _bombIngrid.end()) {
                const Cell normCell(std::make_pair(r, c), board::cellType::normal);
                board::Cell::SetState(normCell);
                _fullGrid.push_back(normCell);
            } else {

                _fullGrid.push_back(*cellIter);
            }

        }
    }


}

bool board::Grid::checkIfBomb(std::pair<u_int, u_int> coord) {
    return std::any_of(_bombIngrid.begin(), _bombIngrid.end(), [&](Cell &cell) {
        return cell.GetGlobalPos() == coord;
    });
}

bool board::Grid::EvaluateCoordinates(std::pair<u_int, u_int> coord) {
    if (checkIfBomb(coord)) {
        _runningDebug = false;
        return false;
    }

    //update reveled cells state
    const auto it = std::find_if(_fullGrid.begin(), _fullGrid.end(), [&](Cell &cell) {
        return cell.GetGlobalPos() == coord;
    });

    if (it != _fullGrid.end()) {
        it->RevelCell();
        Cell newRevel = *it;
        _reveledCells.push_back(newRevel);
    } else {
        std::cout << "Exception error ! Out of grid" << std::endl;
        return false;
    }

    return true;
}

void board::Grid::Debug_PrintBoard() {

    int c = 1;
    for (auto it = _fullGrid.begin(); it != _fullGrid.end(); ++it) {
        if (it->GetType() == board::cellType::normal) {
            std::cout << "[" << it->GetGlobalPos().first << " , " << it->GetGlobalPos().second << "]";
        } else {
            std::cout << "[BOMB!]";
        }
        std::cout << " ";
        if (c == 9) {
            std::cout << std::endl;
            c = 1;
        } else c++;

    }

}

void board::Grid::Debug_PrintGridForUser() {

    int c = 0;
    int currentLine = 1;
    std::cout << "\n\n" << std::endl;
    std::cout << "    A    B    C    D    E    F    G    H    I" << std::endl;
    for (auto it = _fullGrid.begin(); it != _fullGrid.end(); ++it) {
        if (c == 0) {
            std::cout << currentLine;
            c++;
            currentLine++;
        }

        if ((it->GetType() == board::cellType::bomb) && !_runningDebug) {
            std::cout << "  *B*";
        } else if (it->WasCellReveled()) {
            std::cout << "  [" << it->GetState() << "]";
        } else {
            std::cout << "  [X]";
        }


        if (c == 9) {
            std::cout << std::endl;
            c = 0;
        } else c++;

    }
    std::cout << "\n\n" << std::endl;
}