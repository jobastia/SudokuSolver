#pragma once
#include <iostream>
#include <string>

#include "AnimationWindow.h"
#include "Block.h"

struct Block;

class EventListener {
   private:
   public:
    virtual void boardCreated(std::vector<std::vector<Block*>>& board) = 0;
    virtual void clusterIn(std::string clusterType, int clusterIndex) = 0;
    virtual void clusterSolved(std::string clusterType, int clusterIndex) = 0;
    virtual void blockSolved(int row, int collumn, char number) = 0;
    virtual void currentSubsetSize(int n) = 0;
    virtual void boardSolved() = 0;
};

class LoggingEventListener : public EventListener {
   public:
    void boardCreated(std::vector<std::vector<Block*>>& board) override {
        std::cout << "Board Created!" << std::endl;
    }
    void clusterIn(std::string clusterType, int clusterIndex) override {
        std::cout << "Cluster In: " << clusterType << " at index "
                  << clusterIndex << std::endl;
    }

    void clusterSolved(std::string clusterType, int clusterIndex) override {
        std::cout << "Cluster Solved: " << clusterType << " at index "
                  << clusterIndex << std::endl;
    }

    void blockSolved(int row, int column, char number) override {
        std::cout << "Block Solved: (" << row << ", " << column << ") "
                  << "Set to: " << static_cast<int>(number) << std::endl;
    }

    void currentSubsetSize(int n) override {
        std::cout << "Current Subset Size: " << n << std::endl;
    }

    void boardSolved() override { std::cout << "Board solved!" << std::endl; }
};

class GraphicEventListener : public EventListener {
   private:
    TDT4102::AnimationWindow window;

   public:
    void boardCreated(std::vector<std::vector<Block*>>& board) override;
    void clusterIn(std::string clusterType, int clusterIndex) override;
    void clusterSolved(std::string clusterType, int clusterIndex) override;
    void blockSolved(int row, int collumn, char number) override;
    void currentSubsetSize(int n) override;
    void boardSolved() override;

    GraphicEventListener();
};