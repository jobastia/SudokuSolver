#include "TestSudokuBoard.h"

void testSudokuBoard() {
    LoggingEventListener logger;
    GraphicEventListener grapher(100, 100, 500, 500);

    std::vector<EventListener*> eventListeners = {&logger, &grapher};

    SudokuBoard sb(
        "C:\\Users\\jone\\OneDrive - "
        "NTNU\\Dokumenter\\Skole\\V2025\\TDT4102\\Prosjekt_1\\Random "
        "brett.txt");

    std::cout << "brett:" << std::endl;
    printBoard(sb);

    Solver solver(&sb, eventListeners);

    solver.solve();

    sb.legallySolved();

    printBoard(sb);
}