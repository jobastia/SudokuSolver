#include "ImproveCluster.h"

bool clusterIsSolved(std::vector<Block*>& cluster) {
    for (Block* block : cluster) {
        if (!block->isSolved()) return false;
    }
    return true;
}

std::set<char> unionOfBlocks(std::vector<Block*>& blocks) {
    std::set<char> unionSet;
    for (Block* block : blocks) {
        unionSet.insert(block->possibleNumbers.begin(),
                        block->possibleNumbers.end());
    }
    return unionSet;
}

bool eraseImpossibleNumbers(Block* block, std::set<char>& impossibleNumbers) {
    bool wasChanged = false;

    for (char c : impossibleNumbers) {
        if (std::find(block->possibleNumbers.begin(),
                      block->possibleNumbers.end(),
                      c) != block->possibleNumbers.end())
            block->possibleNumbers.erase(c);
        wasChanged = true;
        if (block->isSolved()) {
            std::for_each(block->eventListeners.begin(),
                          block->eventListeners.end(),
                          [](auto& listener) { listener->blockSolved(0, 0); });
        }
    }
    return wasChanged;
}

// Rekursiv hjelpefunksjon som skal returnere alle mulige subsets av en cluster
// av en gitt størrelse
void generateSubsets(const std::vector<Block*>& cluster, int n,
                     std::vector<Block*>& currentSubset,
                     std::vector<std::vector<Block*>>& allSubsets,
                     std::vector<Block*>::iterator it) {
    if (currentSubset.size() == n) {
        allSubsets.push_back(currentSubset);
        return;
    }

    for (auto i = it; i != cluster.end(); i++) {
        currentSubset.push_back(*i);
        generateSubsets(cluster, n, currentSubset, allSubsets, std::next(i));
        currentSubset.pop_back();
    }
}

std::vector<std::vector<Block*>> getSubsets(std::vector<Block*> cluster,
                                            int n) {
    std::vector<std::vector<Block*>> allSubsets;
    std::vector<Block*> currentSubset;

    generateSubsets(cluster, n, currentSubset, allSubsets, cluster.begin());
    return allSubsets;
}

bool improveCluster(std::vector<Block*>& cluster, int n) {
    if (clusterIsSolved(cluster)) return false;

    bool wasChanged = false;

    auto allSubsets = getSubsets(cluster, n);
    for (auto subSet : allSubsets) {
        std::set<char> unionSet = unionOfBlocks(subSet);
        if (unionSet.size() == n) {
            for (Block* block : cluster) {
                if (std::find(subSet.begin(), subSet.end(), block) ==
                    subSet.end()) {
                    if (eraseImpossibleNumbers(block, unionSet))
                        wasChanged = true;
                }
            }
        }
    }
    return wasChanged;
}

void simpleImproveCluster(std::vector<Block*>& cluster) {
    for (Block* block : cluster) {
        if (block->isSolved()) {
            std::for_each(cluster.begin(), cluster.end(), [block](Block* b) {
                if (b != block) {
                    eraseImpossibleNumbers(b, block->possibleNumbers);
                }
            });
        }
    }
}