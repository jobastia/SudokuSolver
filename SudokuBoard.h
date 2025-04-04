#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Block.h"
#include "EventListener.h"
#include "ImproveCluster.h"

class SudokuBoard {
   private:
    std::vector<std::vector<Block*>> board;
    std::vector<EventListener*> eventListeners;

   public:
    bool isSolved() const;
    std::vector<Block*> getRow(int n) const;
    std::vector<Block*> getCol(int n) const;
    std::vector<Block*> getBox(int n) const;

    bool improve(int n);

    void addEventListener(EventListener* eventListener);

    void solve();

    friend void printBoard(SudokuBoard board);

    bool legallySolved() const;

    // SudokuBoard();
    SudokuBoard(std::string filename, std::vector<EventListener*> eventListeners);
};
