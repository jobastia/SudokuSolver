#include "EventListener.h"

GraphicEventListener::GraphicEventListener(int x, int y, int width, int height)
    : window{x, y, width, height, "Sudoku :)"},
      windowWidth{width},
      windowHeight{height} {
    blockLength = (6 * std::min(height, width) / 8) / 9;
    topEdge = static_cast<int>(height / 2 - blockLength * 4.5);
    bottomEdge = static_cast<int>(height / 2 + blockLength * 4.5);
    leftmostEdge = static_cast<int>(width / 2 - blockLength * 4.5);
    rightmostEdge = static_cast<int>(width / 2 + blockLength * 4.5);

    int row = 0;
    for (int y = topEdge; y <= bottomEdge; y += blockLength) {
        rowToY[row] = y;
        row++;
    }
    int col = 0;
    for (int x = leftmostEdge; x <= rightmostEdge; x += blockLength) {
        colToX[col] = x;
        col++;
    }
}

void GraphicEventListener::drawBoard(std::vector<Block*>& solvedBlocks) {
    window.next_frame();

    for (int y = topEdge; y <= bottomEdge; y += blockLength) {
        window.draw_line({leftmostEdge, y}, {rightmostEdge, y});
    }
    for (int x = leftmostEdge; x <= rightmostEdge; x += blockLength) {
        window.draw_line({x, topEdge}, {x, bottomEdge});
    }

    for (auto block : solvedBlocks) {
        int x = colToX.at(block->colPos);
        int y = rowToY.at(block->rowPos);

        int number = static_cast<int>(*((block->possibleNumbers).begin()));

        window.draw_text({x, y}, std::to_string(number));
    }
}

void GraphicEventListener::boardCreated(std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
}
void GraphicEventListener::clusterIn(std::string clusterType, int clusterIndex,
                                     std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
    // Funksjonalitet som tegner rundt clusteren oransj?
}
void GraphicEventListener::clusterSolved(std::string clusterType,
                                         int clusterIndex) {}
void GraphicEventListener::blockSolved(int row, int collumn, char number,
                                       std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
    int x = colToX.at(collumn);
    int y = rowToY.at(row);

    TDT4102::Color lineColor = TDT4102::Color::green;

    window.draw_line({x, y}, {x + blockLength, y}, lineColor);
    window.draw_line({x, y}, {x, y + blockLength}, lineColor);
    window.draw_line({x, y + blockLength}, {x + blockLength, y + blockLength},
                     lineColor);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
void GraphicEventListener::currentSubsetSize(int n) {}
void GraphicEventListener::boardSolved(std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
    window.wait_for_close();
}

void drawEmptyBoard(TDT4102::AnimationWindow& window, int width, int height) {
    int blockLength = (6 * std::min(height, width) / 8) / 9;

    int topEdge = static_cast<int>(height / 2 - blockLength * 4.5);
    int bottomEdge = static_cast<int>(height / 2 + blockLength * 4.5);

    int leftmostEdge = static_cast<int>(width / 2 - blockLength * 4.5);
    int rightmostEdge = static_cast<int>(width / 2 + blockLength * 4.5);

    for (int y = topEdge; y <= bottomEdge; y += blockLength) {
        window.draw_line({leftmostEdge, y}, {rightmostEdge, y});
    }
    for (int x = leftmostEdge; x <= rightmostEdge; x += blockLength) {
        window.draw_line({x, topEdge}, {x, bottomEdge});
    }
}
