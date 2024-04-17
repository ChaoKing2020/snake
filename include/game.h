#pragma once

#include <snake.h>
#include <food.h>
#include <graphics.h>
#include <chrono>
#include <iostream>

class Game
{
public:
    int width, height;
    Snake snake;
    Food food;
    int grade;
    bool is_running;
    int frame;
    int unit;
    int cnt;
    IMAGE body, left, right, up, down, img_food, bg;
    std::vector<std::string> food_urls;
    std::string body_str, left_str, right_str, up_str, down_str, bg_str;

    Game();
    void produce_food();
    void run();
    void controller();
    void draw();
    void load_image();
};

void play_bg_music();
void play_food_music();
