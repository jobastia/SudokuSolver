#include "SudokuBoard.h"

SudokuBoard::SudokuBoard(std::string filename, std::vector<EventListener*> eventListeners): eventListeners{eventListeners} {
    std::vector<Block*> solvedBlocks;

    board.reserve(9);
    for (auto row : board) row.reserve(9);

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (int i = 0; i < 9; i++) {
        std::vector<Block*> row;
        for (int j = 0; j < 9; ++j) {
            int value;
            ifs >> value;
            if (value != 0) {
                Block* solvedBlock = new Block(value, i, j);
                solvedBlocks.push_back(solvedBlock);
                row.push_back(solvedBlock);
            } else
                row.push_back(new Block(i, j));
        }
        board.push_back(row);
    }
    ifs.close();

    for (auto row : board) {
        for (auto block : row) {
            block->eventListeners = eventListeners;
        }
    }

    std::for_each(eventListeners.begin(), eventListeners.end(),
                  [&solvedBlocks](auto listener) {
                      listener->boardCreated(solvedBlocks);
                  });
}

bool SudokuBoard::isSolved() const {
    for (auto row : board) {
        if (!clusterIsSolved(row)) {
            return false;
        }
    }
    std::for_each(eventListeners.begin(), eventListeners.end(),
                  [](auto& listener) { listener->boardSolved(); });
    return true;
}

std::vector<Block*> SudokuBoard::getRow(int n) const { return board.at(n); }

std::vector<Block*> SudokuBoard::getCol(int n) const {
    std::vector<Block*> col;
    for (int i = 0; i < board.size(); i++) {
        col.push_back(board.at(i).at(n));
    }
    return col;
}

std::vector<Block*> SudokuBoard::getBox(int n) const {
    std::vector<Block*> box;
    int startrow = (n / 3) * 3;
    int startcol = (n % 3) * 3;

    for (int row = startrow; row < startrow + 3; row++) {
        for (int col = startcol; col < startcol + 3; col++) {
            box.push_back(board.at(row).at(col));
        }
    }
    return box;
}

void printBoard(SudokuBoard sb) {
    for (auto row : sb.board) {
        for (auto block : row) {
            if (block->isSolved()) {
                std::cout << static_cast<int>(*block->possibleNumbers.begin())
                          << " ";
            } else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}

void SudokuBoard::addEventListener(EventListener* eventListener) {
    eventListeners.push_back(eventListener);
    for (auto row : board) {
        for (auto block : row) {
            block->eventListeners.push_back(eventListener);
        }
    }
}

bool SudokuBoard::improve(int subsetSize) {
    std::for_each(eventListeners.begin(), eventListeners.end(),
                  [subsetSize](auto& listener) { listener->currentSubsetSize(subsetSize); });
    bool wasChanged = false;

    for (int i = 0; i < 9; i++) {
        auto row = getRow(i);
        std::for_each(eventListeners.begin(), eventListeners.end(),
                      [i](auto& listener) { listener->clusterIn("row", i); });
        if (improveCluster(row, subsetSize) && !wasChanged)
            wasChanged = true;
        else
            continue;
        if (clusterIsSolved(row)) {
            std::for_each(
                eventListeners.begin(), eventListeners.end(),
                [i](auto& listener) { listener->clusterSolved("row", i); });
        }
    }
    for (int i = 0; i < 9; i++) {
        auto col = getCol(i);
        std::for_each(eventListeners.begin(), eventListeners.end(),
                      [i](auto& listener) { listener->clusterIn("col", i); });
        if (improveCluster(col, subsetSize) && !wasChanged)
            wasChanged = true;
        else
            continue;
        if (clusterIsSolved(col)) {
            std::for_each(
                eventListeners.begin(), eventListeners.end(),
                [i](auto& listener) { listener->clusterSolved("col", i); });
        }
    }
    for (int i = 0; i < 9; i++) {
        auto box = getBox(i);
        std::for_each(eventListeners.begin(), eventListeners.end(),
                      [i](auto& listener) { listener->clusterIn("box", i); });
        if (improveCluster(box, subsetSize) && !wasChanged)
            wasChanged = true;
        else
            continue;
        if (clusterIsSolved(box)) {
            std::for_each(
                eventListeners.begin(), eventListeners.end(),
                [i](auto& listener) { listener->clusterSolved("box", i); });
        }
    }

    return wasChanged;
}

void SudokuBoard::solve() {
    int subsetSize = 1;

    while (!isSolved()) {
        int i = 0;
        while (improve(subsetSize)) {
            i++;
            std::cout << i << std::endl;
        }
        if (i == 0 || subsetSize == 1) {
            subsetSize++;
        } else {
            subsetSize = 1;
        }
        if (subsetSize == 9) {
            std::cout << "kuk!" << std::endl;
            // kall på en guess solution
            return;
        }
    }
}

bool SudokuBoard::legallySolved() const {
    bool legallySolved = true;

    for (int i = 0; i < 9; i++) {
        auto box = getBox(i);
        auto row = getRow(i);
        auto col = getCol(i);

        if (!ClusterLegallySolved(box)) {
            legallySolved = false;
            std::cout << "Box at " << i << " illegally solved" << std::endl;
        }
        if (!ClusterLegallySolved(row)) {
            legallySolved = false;
            std::cout << "Row at " << i << " illegally solved" << std::endl;
        }
        if (!ClusterLegallySolved(col)) {
            legallySolved = false;
            std::cout << "Column at " << i << " illegally solved" << std::endl;
        }
    }
    if (legallySolved) std::cout << "Board legally solved!" << std::endl;

    return legallySolved;
}