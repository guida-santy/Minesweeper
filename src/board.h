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
        explicit Cell(std::pair<u_int, u_int> pos) : _globalPos(std::move(pos)) {}

        cellType GetType() { return _type; }

        [[nodiscard]] u_int GetState() const { return _state; }

        void SetType(cellType t) { _type = t; }

        void SetFlag() { _flag = true; }

        void RemoveFlag() { _flag = false; }

        void SetState(int s) { _state = s; }

        void RevelCell() { _reveled = true; }

        bool WasCellReveled() const { return _reveled; }

        bool GetFlag() const { return _flag; }

    private:
        const std::pair<u_int, u_int> _globalPos{}; //board pos (r,c)
        cellType _type = cellType::normal;
        u_int _state = 0; // how close to bomb
        bool _reveled = false;
        bool _flag = false;
    };

    class Grid {
    public:
        Grid() : _fullGrid(_rows + 1, std::vector<Cell>(_columns + 1, Cell(std::make_pair(1, 1)))) {}

        void CreateGrid();

        void SetBombs();

        void Debug_PrintBoard();

        void Debug_PrintGridForUser();

        void RevelCell(int row, int col);

        bool EvaluateCoordinates(int row, int col);

        bool CellAlreadyReveled(const int row, const int col) { return _fullGrid[row][col].WasCellReveled(); }

        [[nodiscard]] bool GetRows() const { return _rows; }

        [[nodiscard]] bool GetColumns() const { return _columns; }

        [[nodiscard]] bool GetNumberOfBombs() const { return _numberOfBombs; }

        [[nodiscard]] int GetNumberCellsReveled() const { return _numberOfReveledCells; }

    private:
        const int _rows = 9;

        const int _columns = 9;

        const int _numberOfBombs = 10;

        int _numberOfReveledCells = 0;

        bool _runningDebug = false;

        std::vector<std::vector<Cell>> _fullGrid{};

    };


}
#endif //MINESWEEPER_BOARD_H
