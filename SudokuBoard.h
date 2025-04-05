#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Block.h"
#include "ImproveCluster.h"

class SudokuBoard {
   private:
    std::vector<std::vector<Block*>> board;

   public:
    std::vector<Block*> getRow(int n) const;
    std::vector<Block*> getCol(int n) const;
    std::vector<Block*> getBox(int n) const;

    std::vector<std::vector<Block*>> getBoard() {return board;}

    friend void printBoard(SudokuBoard board);

    bool legallySolved() const;

    SudokuBoard(std::string filename);
};
