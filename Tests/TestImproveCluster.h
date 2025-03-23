#pragma once

#include <iostream>

#include "ImproveCluster.h"

void printSet(std::set<char> s);

void printCluster(std::vector<Block*>& cluster);

void testUnionOfBlocks(std::vector<Block*>& cluster);

void testEraseimpossibleNumbers(Block* block, std::set<char> eraser);

void testGetSubsets(std::vector<Block*>& cluster);

void testImproveCluster(std::vector<Block*>& cluster);

void fullImproveClusterTest();