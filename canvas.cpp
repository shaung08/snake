#include <iostream>
#include "snake.h"
#include "canvas.h"

canvas::canvas() {
    init_canvas();
}

canvas::~canvas() {
}

void canvas::init_canvas() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height-1 || j == 0 || j == width-1) {
                background[i][j] = '*';
            }
            else {
                background[i][j] = ' ';
            }
        }
    }
}

void canvas::show_canvas() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            std::cout << *(*(background+i)+j);
        }
        std::cout << std::endl;
    }
}