#pragma once

#include "widgets/TextInput.h"
#include "widgets/Button.h"
#include "AnimationWindow.h"
#include <vector>

class InputWindow{
    private:
    TDT4102::AnimationWindow window;
    std::vector<TDT4102::TextInput> textBoxes;
    TDT4102::Button solveButton;

    int width = 500;
    int height = 500;

    void initSolve();

    public:
    InputWindow();

};