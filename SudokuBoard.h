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
    bool isSolved;

   public:
    std::vector<Block*> getRow(int n);
    std::vector<Block*> getCol(int n);
    std::vector<Block*> getBox(int n);

    friend void printBoard(SudokuBoard board);

    SudokuBoard();
    SudokuBoard(std::string filename);
    ~SudokuBoard();
};
