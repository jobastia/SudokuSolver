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

        unsigned int fontSize = (35 * blockLength / 41);

        window.draw_text({x, y}, std::to_string(number), TDT4102::Color::black,
                         fontSize);
    }
}

void GraphicEventListener::boardCreated(std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
}
void GraphicEventListener::clusterIn(std::string clusterType, int clusterIndex,
                                     std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);

    int extraThickness = 3;
    TDT4102::Color lineColor = TDT4102::Color::orange;

    if (clusterType == "row") {
        int y = rowToY.at(clusterIndex);
        for (int pixel = -extraThickness; pixel <= extraThickness; pixel++) {
            window.draw_line({leftmostEdge, y + pixel},
                             {rightmostEdge, y + pixel}, lineColor);
            window.draw_line({leftmostEdge + pixel, y},
                             {leftmostEdge + pixel, y + blockLength},
                             lineColor);
            window.draw_line({leftmostEdge, y + blockLength + pixel},
                             {rightmostEdge, y + blockLength + pixel},
                             lineColor);
            window.draw_line({rightmostEdge + pixel, y},
                             {rightmostEdge + pixel, y + blockLength},
                             lineColor);
        }
        SDL_Delay(0);
    }
    if (clusterType == "col") {
        int x = rowToY.at(clusterIndex);
        for (int pixel = -extraThickness; pixel <= extraThickness; pixel++) {
            window.draw_line({x, topEdge+pixel}, {x + blockLength, topEdge+pixel},
                             lineColor);
            window.draw_line({x + pixel, topEdge}, {x + pixel, bottomEdge},
                             lineColor);
            window.draw_line({x, bottomEdge + pixel},
                             {x + blockLength, bottomEdge + pixel}, lineColor);
            window.draw_line({x + blockLength + pixel, topEdge},
                             {x + blockLength + pixel, bottomEdge}, lineColor);
        }
        SDL_Delay(0);
    }
    if (clusterType == "box") {
        int y = rowToY.at((clusterIndex / 3) * 3);
        int x = colToX.at((clusterIndex % 3) * 3);

        for (int pixel = -extraThickness; pixel <= extraThickness; pixel++) {
            window.draw_line({x, y + pixel}, {x + 3 * blockLength, y + pixel},
                             lineColor);
            window.draw_line({x + pixel, y}, {x + pixel, y + 3 * blockLength},
                             lineColor);
            window.draw_line({x, y + 3 * blockLength + pixel},
                             {x + 3 * blockLength, y + 3 * blockLength + pixel},
                             lineColor);
            window.draw_line({x + 3 * blockLength + pixel, y},
                             {x + 3 * blockLength + pixel, y + 3 * blockLength},
                             lineColor);
        }
        SDL_Delay(0);
    }
}
void GraphicEventListener::clusterSolved(std::string clusterType,
                                         int clusterIndex) {}
void GraphicEventListener::blockSolved(int row, int collumn, char number,
                                       std::vector<Block*>& solvedBlocks) {
    drawBoard(solvedBlocks);
    int x = colToX.at(collumn);
    int y = rowToY.at(row);

    TDT4102::Color lineColor = TDT4102::Color::light_green;

    int extraThickness = 2;

    for (int pixel = -extraThickness; pixel <= extraThickness; pixel++) {
        window.draw_line({x, y + pixel}, {x + blockLength, y + pixel},
                         lineColor);
        window.draw_line({x + pixel, y}, {x + pixel, y + blockLength},
                         lineColor);
        window.draw_line({x, y + blockLength + pixel},
                         {x + blockLength, y + blockLength + pixel}, lineColor);
        window.draw_line({x + blockLength + pixel, y},
                         {x + blockLength + pixel, y + blockLength}, lineColor);
    }

    SDL_Delay(100);
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
