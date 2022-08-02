#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "canvas.h"
#include "canvas.cpp"
#include "snake.h"
#include "snake.cpp"
#include "keyboard.cpp"
#include "keyboard.h"

#define width 50
#define height 25

int main () {
    canvas canvdraw;
    snake snakebody(*canvdraw.background, std::floor(height/2), std::floor(width/2));
    keyboard userkey;
    canvdraw.show_canvas();

    char key;
    int direction;
    bool status;
    while (true)
    {
        key = userkey.get_keyboard();
        direction = userkey.get_direction(&key);
        if(snakebody.key_move(*canvdraw.background, direction)) {
            canvdraw.show_canvas();
            continue;
        }
        else {
            printf("----------hit the snake--------\nend\n");
            break;
        }
    }
    

    return 0;
}