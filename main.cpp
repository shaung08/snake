#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <time.h>

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
clock_t start,end;
float speed = 1; // 0.01s move a pixel

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
    while (alive) {
        if (double(clock() - start )/CLOCKS_PER_SEC > 1.0) {
            t_mutex.lock();
            // move snake regular
            direction = snakebody.snake_coor.dir_list[snakebody.snake_coor.dir_list.size()-1];
            show_canvas();
            t_mutex.unlock();
            sleep(speed);
        }
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
        start = clock(); 
        t_mutex.unlock();
    }
}

int main () {
    start = clock(); 
    std::thread s_thread(snake_thread, *canvdraw.background);
    std::thread k_thread(keyboard_thread, *canvdraw.background);
    s_thread.join();
    k_thread.join();
    return 0;
}