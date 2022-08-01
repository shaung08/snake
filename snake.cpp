#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

snake::snake(char* background, int height, int width)
:snake_coor{height, width, height, width, 3, {}}
{
    init_snake(background);
};

snake::~snake()
{
};


void snake::init_snake(char* background) {
    set_head(MoveHead::TAIL);
    plt_snake(background);
    int x, dir;
    srand(time(NULL));
    for (int i = 1; i < snake_coor.body_len; i++) {
        x = rand();
        dir = x % 4;
        move(dir);
        if (check_body(background)) {
            i--;
        }
        else {
            snake_coor.dir_list.push_back(dir);
            plt_snake(background);
        }
    }
};

bool snake::check_body(char* background) {
    if (*(background+50*(*row-1)+*col) == '*')
        return true;
    else 
        return false;
};

void snake::plt_snake(char* background) {
    *(background+50*(*row-1)+*col) = '*';
};

void snake::update_tail() {
    it = snake_coor.dir_list.begin();
    switch (snake_coor.dir_list[0])
    {
        case Direction::UP:
            snake_coor.tail_row--;
            break;
        case Direction::DOWN:
            snake_coor.tail_row++;
            break;
        case Direction::LEFT:
            snake_coor.tail_col--;
            break;
        case Direction::RIGHT:
            snake_coor.tail_col++;
            break;
    }
    snake_coor.dir_list.erase(it);
};

void snake::clear_tail(char* background) {
    *(background+50*(snake_coor.tail_row-1)+snake_coor.tail_col) = ' ';
};

int snake::move(int dir) {
    switch (dir)
    {
        case Direction::UP:
            *row -= 1;
            break;
        case Direction::DOWN:
            *row += 1;
            break;
        case Direction::LEFT:
            *col -= 1;
            break;
        case Direction::RIGHT: 
            *col += 1;
            break;

        default:
            break;
    }
};

void snake::set_head(MoveHead head) {
    switch (head)
    {
        case MoveHead::HEAD:
            row = &snake_coor.head_row;
            col = &snake_coor.head_col;
            break;
        case MoveHead::TAIL:
            row = &snake_coor.tail_row;
            col = &snake_coor.tail_col;
            break;
    }
}

bool snake::key_move(char* background, int dir) {
    set_head(MoveHead::HEAD);
    move(dir);
    if(check_body(background))
        return false;
    else {
        snake_coor.dir_list.push_back(dir);
        plt_snake(background);
        update_tail();
        clear_tail(background);
        return true;
    }

}