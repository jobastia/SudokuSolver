#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "AnimationWindow.h"
#include "Block.h"

struct Block;

class EventListener {
   private:
   public:
    virtual void boardCreated(std::vector<Block*>& solvedBlocks) = 0;
    virtual void clusterIn(std::string clusterType, int clusterIndex) = 0;
    virtual void clusterSolved(std::string clusterType, int clusterIndex) = 0;
    virtual void blockSolved(int row, int collumn, char number) = 0;
    virtual void currentSubsetSize(int n) = 0;
    virtual void boardSolved() = 0;
};

class LoggingEventListener : public EventListener {
   public:
    void boardCreated(std::vector<Block*>& solvedBlocks) override; 
    void clusterIn(std::string clusterType, int clusterIndex) override; 
    void clusterSolved(std::string clusterType, int clusterIndex) override; 
    void blockSolved(int row, int column, char number) override; 
    void currentSubsetSize(int n) override; 
    void boardSolved() override; 
};

class GraphicEventListener : public EventListener {
   private:
    TDT4102::AnimationWindow window;
    int windowWidth;
    int windowHeight;

    std::map<int, int> colToX;
    std::map<int, int> rowToY;

    std::vector<Block*> solvedBlocks;

    void drawCurrentBoard();

   public:
    void boardCreated(std::vector<Block*>& solvedBlocks) override;
    void clusterIn(std::string clusterType, int clusterIndex) override;
    void clusterSolved(std::string clusterType, int clusterIndex) override;
    void blockSolved(int row, int collumn, char number) override;
    void currentSubsetSize(int n) override;
    void boardSolved() override;

    GraphicEventListener(int x = 100, int y = 100, int width = 500,
                         int height = 500);
};

void drawEmptyBoard(TDT4102::AnimationWindow& window, int width, int height);