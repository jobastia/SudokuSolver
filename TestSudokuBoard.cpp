#include "TestSudokuBoard.h"

void testSudokuBoard() {
    LoggingEventListener logger;
    GraphicEventListener grapher;

    std::vector<EventListener*> eventListeners = {&logger, &grapher};
    
    SudokuBoard sb(
        "C:\\Users\\jone\\OneDrive - "
        "NTNU\\Dokumenter\\Skole\\V2025\\TDT4102\\Prosjekt_1\\Random "
        "brett.txt", eventListeners);

    std::cout << "brett:" << std::endl;
    printBoard(sb);

    sb.solve();
    sb.legallySolved();

    printBoard(sb);
}