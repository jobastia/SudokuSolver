#pragma once
#include <iostream>
#include <string>

class EventListener {
   private:
   public:
    virtual void clusterIn(std::string clusterType, int clusterIndex) = 0;
    virtual void clusterSolved(std::string clusterType, int clusterIndex) = 0;
    virtual void blockSolved(int row, int collumn, char number) = 0;
    virtual void currentSubsetSize(int n) = 0;
    virtual void boardSolved() = 0;
};

class LoggingEventListener : public EventListener {
   public:
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

    void boardSolved() { std::cout << "Board solved!" << std::endl; }
};

class GraphicEventListener : public EventListener {
    virtual void clusterIn(std::string clusterType, int clusterIndex);
    virtual void clusterSolved(std::string clusterType, int clusterIndex);
    virtual void blockSolved(int row, int collumn, char number);
    virtual void currentSubsetSize(int n);
    virtual void boardSolved();
};