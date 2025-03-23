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
            if (value != 0)
                row.push_back(new Block(value));
            else
                row.push_back(new Block);
        }
        board.push_back(row);
    }
    ifs.close();
}

std::vector<Block*> SudokuBoard::getRow(int n) const { return board.at(n); }

std::vector<Block*> SudokuBoard::getCol(int n) const {
    std::vector<Block*> col;
    for (int i = 0; i < board.size(); i++) {
        col.push_back(board.at(i).at(n));
    }
    return col;
}

std::vector<Block*> SudokuBoard::getBox(int n) const {
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

bool SudokuBoard::improve(int n) {
    bool wasChanged = false;

    for (int i = 0; i < 9; i++) {
        auto row = getRow(i);
        if (improveCluster(row, n) && !wasChanged) wasChanged = true;
    }
    for (int i = 0; i < 9; i++) {
        auto col = getCol(i);
        if (improveCluster(col, n) && !wasChanged) wasChanged = true;
    }
    for (int i = 0; i < 9; i++) {
        auto box = getBox(i);
        if (improveCluster(box, n) && !wasChanged) wasChanged = true;
    }

    return wasChanged;
}