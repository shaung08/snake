#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#include "canvas.h"
#include "canvas.cpp"
#include "snake.h"
#include "snake.cpp"
#include "keyboard.cpp"
#include "keyboard.h"

#define width 50
#define height 25

canvas canvdraw;
snake snakebody(*canvdraw.background, std::floor(height/2), std::floor(width/2));

void snake_thread(char* background) {
    // set moving speed
    float speed = 0.01; // 0.01s move a pixel
    int dir;
    while (true) {
        // move snake regular
        dir = snakebody.snake_coor.dir_list[snakebody.snake_coor.dir_list.size()-1];
        if (snakebody.move_snake(background, dir)) {
            // set delay time
            sleep(1);
            continue;
        }
        else {
            printf("----------hit the snake--------\nend\n");
            break;
        }
    }
}


void keyboard_thread(char* background) {
    keyboard userkey;
    char key;
    int direction;
    while (true) {
        // get key
        key = userkey.get_keyboard();
        // get direction
        direction = userkey.get_direction(&key);
        // save direction to blocking queue
        if(snakebody.move_snake(background, direction)) {
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
        // show canvas background
        canvdraw.show_canvas();
        sleep(1);
    }
}


int main () {
    std::thread s_thread(snake_thread, *canvdraw.background);
    std::thread k_thread(keyboard_thread, *canvdraw.background);
    std::thread c_thread(canvas_thread);
    s_thread.join();
    k_thread.join();
    c_thread.join();
    return 0;
}