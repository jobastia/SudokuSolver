#include "TestSudokuBoard.h"

void testSudokuBoard() {
    SudokuBoard sb(
        "C:\\Users\\jone\\OneDrive - "
        "NTNU\\Dokumenter\\Skole\\V2025\\TDT4102\\Prosjekt_1\\Random "
        "brett.txt");

    std::cout << "brett:" << std::endl;
    printBoard(sb);

    int i = 1;

    sb.improve(1);

    while (sb.improve(2) && i <= 20);
    
    printBoard(sb);
}