#include <iostream>

#include "Block.h"
#include "ImproveCluster.h"

void printSet(std::set<char> s) {
    for (char c : s) std::cout << static_cast<int>(c);
    std::cout << std::endl;
}

void printCluster(std::vector<Block*> cluster) {
    for (Block* b : cluster) printSet(b->possibleNumbers);
    std::cout << std::endl;
}

int main() {
    Block b1;
    Block b2;
    Block b3;
    Block b4;

    b1.possibleNumbers = {1, 2, 3};
    b2.possibleNumbers = {2, 3};
    b3.possibleNumbers = {1, 2};
    b4.possibleNumbers = {1, 3};

    std::vector<Block*> cluster = {&b1, &b2, &b3, &b4};

    printCluster(cluster);

    improveCluster(cluster, 2);

    printCluster(cluster);

    improveCluster(cluster, 1);

    printCluster(cluster);

    return 0;
}
