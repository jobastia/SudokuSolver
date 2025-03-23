#include "Block.h"

Block::Block() { possibleNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9}; }

Block::Block(char solution) { possibleNumbers = {solution}; }

bool Block::isSolved() { return possibleNumbers.size() == 1; }
