#include "EventListener.h"

GraphicEventListener::GraphicEventListener(int x = 100, int y = 100, int width = 500, int height = 500)
    : window{x, y, width, height, "Sudoku :)"}, windowWidth{width}, windowHeight{height} {
    
    drawEmptyBoard(window, width, height);

    window.wait_for_close();
}

void GraphicEventListener::boardCreated(std::vector<Block*>& SolvedBlocks) {}
void GraphicEventListener::clusterIn(std::string clusterType,
                                     int clusterIndex) {}
void GraphicEventListener::clusterSolved(std::string clusterType,
                                         int clusterIndex) {}
void GraphicEventListener::blockSolved(int row, int collumn, char number) {}
void GraphicEventListener::currentSubsetSize(int n) {}
void GraphicEventListener::boardSolved() {}



void drawEmptyBoard(TDT4102::AnimationWindow& window, int windowWidth, int windowHeight){
    int blockLength = (6 * std::min(windowHeight, windowWidth) / 8) / 9;

    int topEdge = static_cast<int>(windowHeight / 2 - blockLength * 4.5);
    int bottomEdge = static_cast<int>(windowHeight / 2 + blockLength * 4.5);

    int leftmostEdge = static_cast<int>(windowWidth / 2 - blockLength * 4.5);
    int rightmostEdge = static_cast<int>(windowWidth / 2 + blockLength * 4.5);

    for (int y = topEdge; y <= bottomEdge; y += blockLength) {
        window.draw_line({leftmostEdge, y}, {rightmostEdge, y});
    }
    for (int x = leftmostEdge; x <= rightmostEdge; x += blockLength) {
        window.draw_line({x, topEdge}, {x, bottomEdge});
    }
}