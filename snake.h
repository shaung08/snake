#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>

enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

enum MoveHead {
    HEAD,
    TAIL
};

struct snakecoor {
    int head_row;
    int head_col;
    int tail_row;
    int tail_col;
    int body_len;
    std::vector<int> dir_list;
};

class snake
{
private:
    int* row;
    int* col;
    
public:
    snake(char* background, int height, int width);
    ~snake();

    bool check_body(char* background);
    bool move_snake(char* background, int dir);

    int move(int dir);
    int undo_move(int dir);
    int adjust_direction(int dir);
    
    void init_snake(char* background);
    void plt_snake(char* background);
    void update_tail();
    void clear_tail(char* background);
    void set_head(MoveHead head);
    
    snakecoor snake_coor;
};

#endif