#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <thread>

#include "canvas.h"
#include "canvas.cpp"
#include "snake.h"
#include "snake.cpp"
#include "keyboard.cpp"
#include "keyboard.h"

#define width 50
#define height 25

void snake_thread(*canvdraw.background) {
    // set moving speed
    speed = 0.01 // 0.01s move a pixel
    while (true) {
        // move snake regular

        // put canvas background into blocking queue

        // set delay time
    }
}

void keyboard_thread() {
    keyboard userkey;
    char key;
    while (true) {
        // get key
        key = userkey.get_keyboard();
        // get direction
        direction = userkey.get_direction(&key);
        // save direction to blocking queue
        if(snakebody.key_move(*canvdraw.background, direction)) {
            // put canvas background into blocking queue

            continue;
        }
        else {
            printf("----------hit the snake--------\nend\n");
            break;
        }
    }

}

void canvas_thread() {
  while(true) {
    // get canvas background blocking queue

    // show canvas background
    canvdraw.show_canvas();
  }
}


int main () {
    canvas canvdraw;
  
    std::thread snake_thread(*canvdraw.background);
    std::thread keyboard_thread(*canvdraw.background);
    std::thread canvas_thread();

    /*
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
    */
    

    return 0;
}