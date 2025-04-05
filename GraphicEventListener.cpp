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

    window.draw_rectangle({0, 0}, windowWidth, windowHeight, bgColor);

    for (int y = topEdge; y <= bottomEdge; y += blockLength) {
        window.draw_line({leftmostEdge, y}, {rightmostEdge, y}, lineColor);
    }
    for (int x = leftmostEdge; x <= rightmostEdge; x += blockLength) {
        window.draw_line({x, topEdge}, {x, bottomEdge}, lineColor);
    }

    for (auto block : solvedBlocks) {
        int x = colToX.at(block->colPos);
        int y = rowToY.at(block->rowPos);

        int number = static_cast<int>(*((block->possibleNumbers).begin()));

        unsigned int fontSize = (35 * blockLength / 41);

        window.draw_text({x, y}, std::to_string(number), numberColor, fontSize,
                         font);
    }
}

void GraphicEventListener::boardCreated(std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
}
void GraphicEventListener::clusterIn(std::string clusterType, int clusterIndex,
                                     std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);

    if (clusterType == "row") {
        int y = rowToY.at(clusterIndex);

        drawFatRectangle(window, {leftmostEdge, y}, blockLength * 9,
                         blockLength, clusterInColor, 3);
    }
    if (clusterType == "col") {
        int x = rowToY.at(clusterIndex);

        drawFatRectangle(window, {x, topEdge}, blockLength, blockLength * 9,
                         clusterInColor, 3);
    }
    if (clusterType == "box") {
        int y = rowToY.at((clusterIndex / 3) * 3);
        int x = colToX.at((clusterIndex % 3) * 3);

        drawFatRectangle(window, {x, y}, blockLength * 3, blockLength * 3,
                         clusterInColor, 3);
    }
}

void GraphicEventListener::clusterSolved(std::string clusterType,
                                         int clusterIndex) {}
void GraphicEventListener::blockSolved(int row, int collumn, char number,
                                       std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
    int x = colToX.at(collumn);
    int y = rowToY.at(row);

    int extraThickness = 2;

    drawFatRectangle(window, {x, y}, blockLength, blockLength, blockSolvedColor,
                     2);

    SDL_Delay(100);
}
void GraphicEventListener::currentSubsetSize(int n) {}
void GraphicEventListener::boardSolved(std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);

    window.wait_for_close();
}

void drawFatRectangle(TDT4102::AnimationWindow& window, TDT4102::Point point,
                      int width, int height, TDT4102::Color color,
                      int extraThickness) {
    for (int pixel = -extraThickness; pixel <= extraThickness; pixel++) {
        window.draw_line({point.x, point.y + pixel},
                         {point.x + width, point.y + pixel}, color);
        window.draw_line({point.x + pixel, point.y},
                         {point.x + pixel, point.y + height}, color);
        window.draw_line({point.x, point.y + height + pixel},
                         {point.x + width, point.y + height + pixel}, color);
        window.draw_line({point.x + width + pixel, point.y},
                         {point.x + width + pixel, point.y + height}, color);
    }
}