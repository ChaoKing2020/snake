#pragma once

#include <snake.h>
#include <food.h>

class Game
{
public:
    int w, h;
    Snake snake;
    Food food;
    int grade;
    bool is_running;
    int frame;

    void init();
    void product_food();
    void run();
    void controller();
    void draw();

    Game();

};