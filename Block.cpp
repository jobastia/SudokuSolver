#include "Block.h"

Block::Block() : isSolved{false} {
    possibleNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

Block::Block(char solution) : isSolved{true} { possibleNumbers = {solution}; }
