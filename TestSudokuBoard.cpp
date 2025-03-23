#include "TestSudokuBoard.h"

void testSudokuBoard() {
    SudokuBoard sb("Random brett.txt");

    std::cout << "brett:" << std::endl;
    printBoard(sb);

    int i = 1;

    sb.improve(1);

    while (sb.improve(2) && i <= 20) {
        std::cout << i << ":" << std::endl;
        printBoard(sb);
        i++;
    }
}