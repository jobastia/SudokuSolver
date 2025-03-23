
#include "TestImproveCluster.h"

void printSet(std::set<char> s) {
    for (char c : s) std::cout << static_cast<int>(c);
    std::cout << std::endl;
}

void printCluster(std::vector<Block*>& cluster) {
    for (Block* b : cluster) printSet(b->possibleNumbers);
    std::cout << std::endl;
}

void testUnionOfBlocks(std::vector<Block*>& cluster) {
    std::cout << "Cluster: " << std::endl;
    printCluster(cluster);

    std::cout << "Union: " << std::endl;
    printSet(unionOfBlocks(cluster));
}

void testEraseimpossibleNumbers(Block* block, std::set<char> eraser) {
    std::cout << "Block: " << std::endl;
    printSet(block->possibleNumbers);
    std::cout << "Eraser: " << std::endl;
    printSet(eraser);

    eraseImpossibleNumbers(block, eraser);

    std::cout << "Cluster after erasing: " << std::endl;
    printSet(block->possibleNumbers);
}

void testGetSubsets(std::vector<Block*>& cluster) {
    for (int i = 1; i <= cluster.size(); i++) {
        std::cout << "Subsets of size " << i << ": " << std::endl;
        auto allSubsets = getSubsets(cluster, i);
        for (auto subset : allSubsets) {
            printCluster(subset);
        }
    }
}

void testImproveCluster(std::vector<Block*>& cluster) {
    printCluster(cluster);
    for (int i = 0; i <= cluster.size(); i++) {
        std::cout << "Improved with subsets of size " << i << ": " << std::endl;
        improveCluster(cluster, i);
        printCluster(cluster);
    }
}

void fullImproveClusterTest() {
    Block b1;
    Block b2;
    Block b3;
    Block b4;
    Block b5;
    Block b6;
    Block b7;
    Block b8;
    Block b9;

    b3.possibleNumbers = {3,1,6,7};
    b4.possibleNumbers = {3,1,6,7};
    b5.possibleNumbers = {3,1,6,7};
    b6.possibleNumbers = {3,1,6,7};

    std::vector<Block*> cluster = {&b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9};

    testUnionOfBlocks(cluster);

    testGetSubsets(cluster);

    // testEraseimpossibleNumbers(&b1, b4.possibleNumbers);

    testImproveCluster(cluster);
}