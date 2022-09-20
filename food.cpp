#include "food.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

food::food(char* background) {
    init_food(background);
};

food::~food() {
};

void food::init_food(char* background) {
    create_food(background);
    is_food = true;
};

void food::create_food(char* background) {
    int width;
    int height;
    width = (rand() % (50-1))+ 1;
    height = (rand() % (25-1))+ 1;
    if (check_food(background, width, height)) {
        *(background+50*(height-1)+width) = '+';
        is_food = true;
        return;
    }
    else {
        is_food = false;
        create_food(background);
    }
};

bool food::check_food(char* background, int w, int h) {
    if (*(background+50*(h-1)+w) != '*')
        return true;
    else {
        return false;
    }
};