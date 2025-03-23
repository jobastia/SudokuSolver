#pragma once
#include <algorithm>
#include <set>
#include <vector>

struct Block {
    std::set<char> possibleNumbers;
    bool isSolved;

    Block();
    Block(char solution);
};
