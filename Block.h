#pragma once
#include <algorithm>
#include <set>
#include <vector>

#include "EventListener.h"

class EventListener;

struct Block {
    std::set<char> possibleNumbers;

    int rowPos;
    int colPos;

    std::vector<EventListener*> eventListeners;

    bool isSolved();

    bool eraseNumbers(std::set<char>& eraser);

    Block(int rowPos, int colPos);
    Block(char solution, int rowPos, int colPos);
};
