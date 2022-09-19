#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

snake::snake(char* background, int height, int width, bool& is_food_)
:snake_coor{height, width, height, width, 3, {}}
{
    init_snake(background, is_food_);
};

snake::~snake()
{
};


void snake::init_snake(char* background, bool& is_food_) {
    is_food = &is_food_;
    set_head(MoveHead::TAIL);
    plt_snake(background);
    int x, dir;
    std::vector<int> tail_l{};
    srand(time(NULL));
    for (int i = 1; i < snake_coor.body_len; i++) {
        x = rand();
        dir = x % 4;
        move(dir);

        if (check_body(background)) {
            undo_move(dir);
            i--;
        }
        else {
            dir = adjust_direction(dir);
            tail_l.push_back(dir);
            plt_snake(background);
        }
    }
    snake_coor.dir_list.insert(snake_coor.dir_list.end(), {tail_l[1], tail_l[0]});
};

int snake::adjust_direction(int dir) {
    switch (dir)
    {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        default:
          break;
    }
}


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
    std::vector<int>::iterator it = snake_coor.dir_list.begin();
    switch (snake_coor.dir_list[0])
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
    }
    snake_coor.dir_list.erase(it);
};

void snake::clear_tail(char* background) {
    *(background+50*(snake_coor.tail_row-1)+snake_coor.tail_col) = ' ';
};

void snake::add_tail(char* background) {
    *(background+50*(snake_coor.tail_row-1)+snake_coor.tail_col) = '*';
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

int snake::undo_move(int dir) {
    switch (dir)
    {
        case Direction::UP:
            *row += 1;
            break;
        case Direction::DOWN:
            *row -= 1;
            break;
        case Direction::LEFT:
            *col += 1;
            break;
        case Direction::RIGHT: 
            *col -= 1;
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

bool snake::move_snake(char* background, int dir) {
    set_head(MoveHead::HEAD);
    move(dir);
    if(check_body(background))
        return false;
    else {
        snake_coor.dir_list.push_back(dir);
        if (eat_food(background)) {
            *is_food = false;
            plt_snake(background);
            set_head(MoveHead::TAIL);
            add_tail(background);
        }
        else {
            plt_snake(background);
            set_head(MoveHead::TAIL);
            clear_tail(background);
            update_tail();
        }

        return true;
    }

}

bool snake::eat_food(char* background) {
    if (*(background+50*(snake_coor.head_row-1)+snake_coor.head_col) == '+') {
        return true;
    }
    else {
        return false;
    }
}
