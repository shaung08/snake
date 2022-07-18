#ifndef KEYBOARD_H_
#define KEYBOARD_H_

enum Keyboard {
    W = 0,
    A = 1,
    S = 2,
    D = 3
};

class keyboard
{
public:
    keyboard();
    ~keyboard();

    int kbhit(void);
    char get_keyboard();
    int get_direction(char* key);
};

#endif