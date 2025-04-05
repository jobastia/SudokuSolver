#include "SudokuBoard.h"

SudokuBoard::SudokuBoard(std::string filename) {

    board.reserve(9);
    for (auto row : board) row.reserve(9);

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (int i = 0; i < 9; i++) {
        std::vector<Block*> row;
        for (int j = 0; j < 9; ++j) {
            int value;
            ifs >> value;
            if (value != 0) {
                Block* solvedBlock = new Block(value, i, j);
                row.push_back(solvedBlock);
            } else
                row.push_back(new Block(i, j));
        }
        board.push_back(row);
    }
    ifs.close();
}

std::vector<Block*> SudokuBoard::getRow(int n) const {
    if (n < 0 || n >= 9) {
        throw std::out_of_range("Index out of bounds in getRow/getCol/getBox");
    }
    return board.at(n);
}

std::vector<Block*> SudokuBoard::getCol(int n) const {
    if (n < 0 || n >= 9) {
        throw std::out_of_range("Index out of bounds in getRow/getCol/getBox");
    }
    std::vector<Block*> col;
    for (int i = 0; i < board.size(); i++) {
        col.push_back(board.at(i).at(n));
    }
    return col;
}

std::vector<Block*> SudokuBoard::getBox(int n) const {
    if (n < 0 || n >= 9) {
        throw std::out_of_range("Index out of bounds in getRow/getCol/getBox");
    }
    std::vector<Block*> box;
    int startrow = (n / 3) * 3;
    int startcol = (n % 3) * 3;

    for (int row = startrow; row < startrow + 3; row++) {
        for (int col = startcol; col < startcol + 3; col++) {
            box.push_back(board.at(row).at(col));
        }
    }
    return box;
}

void printBoard(SudokuBoard sb) {
    for (auto row : sb.board) {
        for (auto block : row) {
            if (block->isSolved()) {
                std::cout << static_cast<int>(*block->possibleNumbers.begin())
                          << " ";
            } else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool SudokuBoard::legallySolved() const {
    bool legallySolved = true;

    for (int i = 0; i < 9; i++) {
        auto box = getBox(i);
        auto row = getRow(i);
        auto col = getCol(i);

        if (!ClusterLegallySolved(box)) {
            legallySolved = false;
            std::cout << "Box at " << i << " illegally solved" << std::endl;
        }
        if (!ClusterLegallySolved(row)) {
            legallySolved = false;
            std::cout << "Row at " << i << " illegally solved" << std::endl;
        }
        if (!ClusterLegallySolved(col)) {
            legallySolved = false;
            std::cout << "Column at " << i << " illegally solved" << std::endl;
        }
    }
    if (legallySolved) std::cout << "Board legally solved!" << std::endl;

    return legallySolved;
}