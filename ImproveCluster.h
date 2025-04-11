#pragma once
#include <iterator>

#include "Block.h"

bool clusterIsSolved(std::vector<Block*>& cluster);

std::set<char> unionOfBlocks(std::vector<Block*>& blocks);

bool eraseImpossibleNumbers(Block* block, std::set<char>& impossibleNumbers);

void generateSubsets(const std::vector<Block*>& cluster, int n,
                     std::vector<Block*>& currentSubset,
                     std::vector<std::vector<Block*>>& allSubsets,
                     std::vector<Block*>::iterator it);

std::vector<std::vector<Block*>> getSubsets(std::vector<Block*> cluster, int n);

bool improveCluster(std::vector<Block*>& cluster, int n);

bool ClusterLegallySolved(std::vector<Block*>& cluster);
