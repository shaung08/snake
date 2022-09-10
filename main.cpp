#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <mutex>

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
std::mutex t_mutex;
int direction;
bool alive = true;

void show_canvas() {
    if(snakebody.move_snake(*canvdraw.background, direction)) {
        // put canvas background into blocking queue
        canvdraw.show_canvas();
    }
    else {
        alive = false;
        printf("----------hit the snake--------\nend\n");
    }
    // show canvas background
}

void snake_thread(char* background) {
    // set moving speed
    float speed = 0.01; // 0.01s move a pixel
    while (alive) {
        // move snake regular
        t_mutex.lock();
        direction = snakebody.snake_coor.dir_list[snakebody.snake_coor.dir_list.size()-1];
        show_canvas();
        t_mutex.unlock();
        sleep(1);
    }
}


void keyboard_thread(char* background) {
    keyboard userkey;
    char key;
    while (alive) {
        // get key
        key = userkey.get_keyboard();
        // get direction
        t_mutex.lock();
        std::cout << "key_move_snake\n";
        direction = userkey.get_direction(&key);
        show_canvas();
        t_mutex.unlock();
    }
}

int main () {
    std::thread s_thread(snake_thread, *canvdraw.background);
    std::thread k_thread(keyboard_thread, *canvdraw.background);
    s_thread.join();
    k_thread.join();
    return 0;
}