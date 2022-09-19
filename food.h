#ifndef FOOD_H_
#define FOOD_H_

class food
{
private:
public:
    food(char* background);
    ~food();

    void init_food(char* background);
    void create_food(char* background);
    bool check_food(char* background, int w, int h);

    bool is_food;
};


#endif