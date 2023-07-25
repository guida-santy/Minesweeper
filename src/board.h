#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include <iostream>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

namespace board {
    enum cellType {
        normal = 0,
        bomb = 1,
    };

    class Cell {
    public:
        Cell(std::pair<u_int, u_int> pos, cellType t) : _globalPos(std::move(pos)), _type(t), _state(0) {}

        std::pair<u_int, u_int> GetGlobalPos() const { return _globalPos; }

        cellType GetType() { return _type; }

        int GetState() { return _state; }

        static void SetState(Cell cell);

        void RevelCell () {_reveled = true;}

        bool WasCellReveled () {return _reveled;}


    private:
        const std::pair<u_int, u_int> _globalPos{}; //board pos
        const cellType _type{}; // bomb or save
        int _state{}; // how close to bomb
        bool _reveled = false;
    };

    class Grid {
    public:
        void CreateGrid();

        void SetBombs();

        void Debug_PrintBoard();

        void Debug_PrintGridForUser();

        bool EvaluateCoordinates(std::pair<u_int, u_int> coord);

        std::vector<Cell> GetCurrentReveledCells() { return _reveledCells; }

    private:
        int _size = 9 * 9;
        int _rows = 9;
        int _columns = 9;
        std::vector<Cell> _fullGrid;
        std::vector<Cell> _reveledCells;
        std::vector<Cell> _bombIngrid;
        int _numberOfBombs = 10;
        bool _runningDebug = false;

        bool checkIfBomb(std::pair<u_int, u_int> coord);
    };


}
#endif //MINESWEEPER_BOARD_H
