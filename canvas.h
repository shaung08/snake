#ifndef CANVAS_H_
#define CANVAS_H
#include "snake.h"

class canvas
{
public:
    canvas();
    ~canvas();
  
    void init_canvas();
    void show_canvas();
    int height = 25;
    int width = 50;
    char background[25][50];

};


#endif