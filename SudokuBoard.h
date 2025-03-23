#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"
#include "ImproveCluster.h"

class SudokuBoard {
   private:
    std::vector<std::vector<Block*>> board;

   public:
    bool isSolved() const;
    std::vector<Block*> getRow(int n) const;
    std::vector<Block*> getCol(int n) const;
    std::vector<Block*> getBox(int n) const;

    bool improve(int n);

    friend void printBoard(SudokuBoard board);

    // SudokuBoard();
    SudokuBoard(std::string filename);
};
