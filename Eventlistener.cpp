#include "EventListener.h"

GraphicEventListener::GraphicEventListener(int x, int y, int width, int height)
    : window{x, y, width, height, "Sudoku :)"},
      windowWidth{width},
      windowHeight{height} {
    int blockLength = (6 * std::min(height, width) / 8) / 9;
    int topEdge = static_cast<int>(height / 2 - blockLength * 4.5);
    int bottomEdge = static_cast<int>(height / 2 + blockLength * 4.5);
    int leftmostEdge = static_cast<int>(width / 2 - blockLength * 4.5);
    int rightmostEdge = static_cast<int>(width / 2 + blockLength * 4.5);
    int row = 0;
    for (int y = topEdge; y <= bottomEdge; y += blockLength) {
        window.draw_line({leftmostEdge, y}, {rightmostEdge, y});
        rowToY[row] = y;
        row++;
    }
    int col = 0;
    for (int x = leftmostEdge; x <= rightmostEdge; x += blockLength) {
        window.draw_line({x, topEdge}, {x, bottomEdge});
        colToX[col] = x;
        col++;
    }
}

void GraphicEventListener::boardCreated(std::vector<Block*>& SolvedBlocks) {
    for (auto block : SolvedBlocks) {
        int x = colToX.at(block->colPos);
        int y = rowToY.at(block->rowPos);

        int number = static_cast<int>(*((block->possibleNumbers).begin()));

        window.draw_text({x, y}, std::to_string(number));
    }
    window.wait_for_close();
}
void GraphicEventListener::clusterIn(std::string clusterType,
                                     int clusterIndex) {}
void GraphicEventListener::clusterSolved(std::string clusterType,
                                         int clusterIndex) {}
void GraphicEventListener::blockSolved(int row, int collumn, char number) {}
void GraphicEventListener::currentSubsetSize(int n) {}
void GraphicEventListener::boardSolved() {}

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
