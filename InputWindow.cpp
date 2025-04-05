#include "InputWindow.h"

InputWindow::InputWindow()
    : window{100, 100, width, height, "Input window"},
      solveButton{{width / 2, height - 50}, 100, 50, "Solve!"} {
        
      }