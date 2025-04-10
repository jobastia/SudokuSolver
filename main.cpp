#include <iostream>
#include <string>

#include "Eventlistener.h"
#include "Solver.h"
#include "SudokuBoard.h"

int main() {
    std::string runWithLogger;
    std::string runWithWindow;
    std::string ingenting;

    std::string filePath;
    std::vector<EventListener*> eventListeners;

    std::cout << "Filepath: ";
    std::getline(std::cin, filePath);
    std::cout << std::endl;

    while (runWithLogger != "Y" && runWithLogger != "N") {
        std::cout << "Run with Logger? (Y/N): ";
        std::cin >> runWithLogger;;
    }

    while (runWithWindow != "Y" && runWithWindow != "N") {
        std::cout << "Run in animationWindow? (Y/N)";
        std::cin >> runWithWindow;
    }

    if (runWithLogger == "Y") {
        eventListeners.push_back(new LoggingEventListener);
    }

    if (runWithWindow == "Y") {
        int width;
        int height;
        std::cout << "Window width: ";
        std::cin >> width;
        std::cout << "Window height: ";
        std::cin >> height;

        eventListeners.push_back(
            new GraphicEventListener(50, 50, width, height));
    }

    SudokuBoard sb(filePath);
    Solver solver(&sb, eventListeners);
    solver.solve();

    printBoard(sb);
    return 0;
}
