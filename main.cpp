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
#include "food.h"
#include "food.cpp"

#define width 50
#define height 25

canvas canvdraw;
food food_(*canvdraw.background);
snake snakebody(*canvdraw.background, std::floor(height/2), std::floor(width/2), food_.is_food);
std::mutex t_mutex;
int direction;
bool alive = true;
clock_t start,end;
float speed = 1; // 0.01s move a pixel


void food_thread() {
    while (alive) {
        if (!food_.is_food)
           food_.create_food(*canvdraw.background);
    }
}

void show_canvas() {
    if(snakebody.move_snake(*canvdraw.background, direction)) {
        // put canvas background into blocking queue
        canvdraw.show_canvas();
    }
    else {
        alive = false;
        printf("----------hit the snake--------\nend\n");
    }
}

void snake_thread() {
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


void keyboard_thread() {
    keyboard userkey;
    char key;
    while (alive) {
        // get key
        key = userkey.get_keyboard();
        // get direction
        t_mutex.lock();
        direction = userkey.get_direction(&key);
        show_canvas();
        start = clock(); 
        t_mutex.unlock();
    }
}

int main () {
    start = clock(); 
    std::thread s_thread(snake_thread);
    std::thread k_thread(keyboard_thread);
    std::thread f_thread(food_thread);
    s_thread.join();
    k_thread.join();
    f_thread.join();
    return 0;
}