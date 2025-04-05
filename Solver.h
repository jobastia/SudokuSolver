#pragma once

#include <vector>

#include "EventListener.h"
#include "SudokuBoard.h"

class Solver {
   private:
    std::vector<EventListener*> eventListeners;
    SudokuBoard* sudokuBoard;

    bool improve(int subsetSize);
    bool isSolved();
    void updateSolvedBlocks();

   public:
    std::vector<Block*> solvedBlocks;

    void solve();
    Solver(SudokuBoard* sudokuBoard, std::vector<EventListener*> eventListeners);
};