#include "EventListener.h"

void LoggingEventListener::boardCreated(std::vector<Block*>& SolvedBlocks) {
    std::cout << "Board Created!" << std::endl;
    for (auto block : SolvedBlocks) {
        int number = static_cast<int>(*((block->possibleNumbers).begin()));
        std::cout << "row: " << block->rowPos << " col: " << block->colPos
                  << " Number: " << number << std::endl;
    }
}
void LoggingEventListener::clusterIn(std::string clusterType, int clusterIndex) {
    std::cout << "Cluster In: " << clusterType << " at index "
              << clusterIndex << std::endl;
}

void LoggingEventListener::clusterSolved(std::string clusterType, int clusterIndex)  {
    std::cout << "Cluster Solved: " << clusterType << " at index "
              << clusterIndex << std::endl;
}

void LoggingEventListener::blockSolved(int row, int column, char number)  {
    std::cout << "Block Solved: (" << row << ", " << column << ") "
              << "Set to: " << static_cast<int>(number) << std::endl;
}

void LoggingEventListener::currentSubsetSize(int n)  {
    std::cout << "Current Subset Size: " << n << std::endl;
}

void LoggingEventListener::boardSolved() { std::cout << "Board solved!" << std::endl; }