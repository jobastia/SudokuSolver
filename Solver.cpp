#include "Solver.h"

Solver::Solver(SudokuBoard* sudokuBoard,
               std::vector<EventListener*> eventListeners)
    : sudokuBoard{sudokuBoard}, eventListeners{eventListeners} {}

bool Solver::isSolved() {
    for (int i = 0; i < 9; i++) {
        auto row = sudokuBoard->getRow(i);
        if (!clusterIsSolved(row)) {
            return false;
        }
    }
    std::for_each(eventListeners.begin(), eventListeners.end(),
                  [](auto& listener) { listener->boardSolved(); });
    return true;
}

bool Solver::improve(int subsetSize) {
    std::for_each(eventListeners.begin(), eventListeners.end(),
                  [subsetSize](auto& listener) {
                      listener->currentSubsetSize(subsetSize);
                  });
    bool wasChanged = false;

    for (int i = 0; i < 9; i++) {
        auto row = sudokuBoard->getRow(i);
        std::for_each(eventListeners.begin(), eventListeners.end(),
                      [i](auto& listener) { listener->clusterIn("row", i); });
        if (improveCluster(row, subsetSize) && !wasChanged)
            wasChanged = true;
        else
            continue;
        if (clusterIsSolved(row)) {
            std::for_each(
                eventListeners.begin(), eventListeners.end(),
                [i](auto& listener) { listener->clusterSolved("row", i); });
        }
    }
    for (int i = 0; i < 9; i++) {
        auto col = sudokuBoard->getCol(i);
        std::for_each(eventListeners.begin(), eventListeners.end(),
                      [i](auto& listener) { listener->clusterIn("col", i); });
        if (improveCluster(col, subsetSize) && !wasChanged)
            wasChanged = true;
        else
            continue;
        if (clusterIsSolved(col)) {
            std::for_each(
                eventListeners.begin(), eventListeners.end(),
                [i](auto& listener) { listener->clusterSolved("col", i); });
        }
    }
    for (int i = 0; i < 9; i++) {
        auto box = sudokuBoard->getBox(i);
        std::for_each(eventListeners.begin(), eventListeners.end(),
                      [i](auto& listener) { listener->clusterIn("box", i); });
        if (improveCluster(box, subsetSize) && !wasChanged)
            wasChanged = true;
        else
            continue;
        if (clusterIsSolved(box)) {
            std::for_each(
                eventListeners.begin(), eventListeners.end(),
                [i](auto& listener) { listener->clusterSolved("box", i); });
        }
    }

    return wasChanged;
}

void Solver::solve() {
    int subsetSize = 1;

    while (!isSolved()) {
        int i = 0;
        while (improve(subsetSize)) {
            i++;
            std::cout << i << std::endl;
        }
        if (i == 0 || subsetSize == 1) {
            subsetSize++;
        } else {
            subsetSize = 1;
        }
        if (subsetSize == 9) {
            std::cout << "kuk!" << std::endl;
            // kall på en guess solution
            return;
        }
    }
}