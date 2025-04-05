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

   public:
    void solve();
    Solver(SudokuBoard sudokuBoard, std::vector<EventListener*> eventListeners);
};