#include "Block.h"

Block::Block(int rowPos, int colPos) : rowPos{rowPos}, colPos{colPos} {
    possibleNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

Block::Block(char solution, int rowPos, int colPos)
    : rowPos{rowPos}, colPos{colPos} {
    possibleNumbers = {solution};
}

bool Block::isSolved() { return possibleNumbers.size() == 1; }

bool Block::eraseNumbers(std::set<char>& eraser) {
    bool wasChanged = false;

    if (isSolved()) return wasChanged;

    for (char c : eraser) {
        if (std::find(possibleNumbers.begin(), possibleNumbers.end(), c) !=
            possibleNumbers.end())
            possibleNumbers.erase(c);
        wasChanged = true;
        if (isSolved()) {
            std::for_each(eventListeners.begin(), eventListeners.end(),
                          [*this](auto& listener) {
                              listener->blockSolved(rowPos, colPos);
                          });
        }
    }
    return wasChanged;
}