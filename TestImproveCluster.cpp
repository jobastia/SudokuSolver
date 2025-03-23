
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
    Block b1(1,1);
    Block b2(1,1);
    Block b3(1,1);
    Block b4(1,1);
    Block b5(1,1);
    Block b6(1,1);
    Block b7(1,1);
    Block b8(1,1);
    Block b9(1,1);

    b3.possibleNumbers = {3,1,6,7};
    b4.possibleNumbers = {3,1,6,7};
    b5.possibleNumbers = {3,1,6,7};
    b6.possibleNumbers = {3,1,6,7};

    std::vector<Block*> cluster = {&b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9};

    testUnionOfBlocks(cluster);

    testGetSubsets(cluster);

    testImproveCluster(cluster);
}