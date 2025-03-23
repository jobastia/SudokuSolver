#include "TestSudokuBoard.h"

void testSudokuBoard() {
    SudokuBoard sb("Random brett.txt");

    std::cout << "brett:" << std::endl;
    printBoard(sb);

    int i = 0;

    while (sb.improve(1) && i <= 20) {
        std::cout << i << ":" << std::endl;
        printBoard(sb);
        i++;
    }
}