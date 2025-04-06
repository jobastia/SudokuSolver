#pragma once
#include <SDL.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>

#include "AnimationWindow.h"
#include "Block.h"

struct Block;

class EventListener {
   private:
   public:
    virtual void boardCreated(std::vector<Block*>& solvedBlocks) = 0;
    virtual void clusterIn(std::string clusterType, int clusterIndex,
                           std::vector<Block*>& solvedBlocks) = 0;
    virtual void clusterSolved(std::string clusterType, int clusterIndex) = 0;
    virtual void blockSolved(int row, int collumn, char number,
                             std::vector<Block*>& solvedBlocks) = 0;
    virtual void currentSubsetSize(int n) = 0;
    virtual void boardSolved(std::vector<Block*>& solvedBlocks) = 0;
    virtual void solveFailed(std::vector<Block*>& solvedBlocks) = 0;
};

class LoggingEventListener : public EventListener {
   public:
    void boardCreated(std::vector<Block*>& solvedBlocks) override;
    void clusterIn(std::string clusterType, int clusterIndex,
                   std::vector<Block*>& solvedBlocks) override;
    void clusterSolved(std::string clusterType, int clusterIndex) override;
    void blockSolved(int row, int column, char number,
                     std::vector<Block*>& solvedBlocks) override;
    void currentSubsetSize(int n) override;
    void boardSolved(std::vector<Block*>& solvedBlocks) override;
    void solveFailed(std::vector<Block*>& solvedBlocks) override;
};

class GraphicEventListener : public EventListener {
   private:
    TDT4102::AnimationWindow window;
    int windowWidth;
    int windowHeight;
    int blockLength;
    int topEdge;
    int bottomEdge;
    int leftmostEdge;
    int rightmostEdge;

    TDT4102::Color bgColor = TDT4102::Color::black;
    TDT4102::Color lineColor = TDT4102::Color::white;
    TDT4102::Color numberColor = TDT4102::Color::lime;
    TDT4102::Color blockSolvedColor = TDT4102::Color::light_green;
    TDT4102::Color clusterInColor = TDT4102::Color::red;

    TDT4102::Font font = TDT4102::Font::courier;

    std::map<int, int> colToX;
    std::map<int, int> rowToY;

    void drawBoard(std::vector<Block*>& solvedBlocks);

   public:
    void boardCreated(std::vector<Block*>& solvedBlocks) override;
    void clusterIn(std::string clusterType, int clusterIndex,
                   std::vector<Block*>& solvedBlocks) override;
    void clusterSolved(std::string clusterType, int clusterIndex) override;
    void blockSolved(int row, int collumn, char number,
                     std::vector<Block*>& solvedBlocks) override;
    void currentSubsetSize(int n) override;
    void boardSolved(std::vector<Block*>& solvedBlocks) override;
    void solveFailed(std::vector<Block*>& solvedBlocks) override;

    GraphicEventListener(int x = 100, int y = 100, int width = 500,
                         int height = 500);
};

void drawFatRectangle(TDT4102::AnimationWindow& window, TDT4102::Point topLeft, int width, int height, TDT4102::Color color, int extraThickness = 2);

