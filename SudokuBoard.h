#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Block.h"
#include "ImproveCluster.h"

class SudokuBoard {
   private:
    std::vector<std::vector<Block*>> board;
    bool isSolved();

   public:
    std::vector<Block*> getRow(int n) const;
    std::vector<Block*> getCol(int n) const;
    std::vector<Block*> getBox(int n) const;

    void improve(int n);

    friend void printBoard(SudokuBoard board);

    // SudokuBoard();
    SudokuBoard(std::string filename);
};
