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
    int fd_idx;
    IMAGE bd_img, lf_img, rt_img, up_img, dw_img, fd_img, bg_img;
    std::vector<std::string> food_urls;
    std::string bd_str, lf_str, rt_str, up_str, dw_str, bg_str;

    Game();
    void produce_food();
    void run();
    void controller();
    void draw();
    void load_image();
    void update_fd();
};

// void play_bg_music();
// void play_food_music();
