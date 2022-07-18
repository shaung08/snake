#include <stdio.h> 
#include <termios.h> 
#include <unistd.h> 
#include <fcntl.h>
#include "keyboard.h"
#include "snake.h"

keyboard::keyboard() {}

keyboard::~keyboard() {}

int keyboard::kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

char keyboard::get_keyboard() {
    while(!kbhit())
        continue;

    char key = getchar();
    return key;
}

int keyboard::get_direction(char* key) {
    if (*key == 'w')
        return Direction::UP;
    else if(*key == 's')
        return Direction::DOWN;
    else if(*key == 'a')
        return Direction::LEFT;
    else if(*key == 'd')
        return Direction::RIGHT;
}