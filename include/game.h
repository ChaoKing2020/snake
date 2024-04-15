#pragma once

#include <snake.h>
#include <food.h>
#include <graphics.h>
#include <chrono>
#include <iostream>

class Game
{
public:
    int w, h;
    Snake snake;
    Food food;
    int grade;
    bool is_running;
    int frame;
    int sz;
    int cnt;
    IMAGE body, left, right, up, down, img_food;

    Game();
    void init();
    void produce_food();
    void run();
    void controller();
    void draw();
    void play_bg_music();
    void load_image();
};
