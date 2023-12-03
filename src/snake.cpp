#include <chrono>
#include <cmath>
#include <iostream>
#include <graphics.h>

#include "../header/snake.h"
#include "../header/glob.h"

void init()
{
    snake.sn = {Node(110, 70), Node(90, 70), Node(70, 70)};
    dir = 'R';

    grade = 0;

    w = 500;
    h = 500;

    is_running = false;
    speed = 10;

    product_food();
}

void product_food()
{
    while (true)
    {
        food.x = 10 + (rand() % 25) * 20;
        food.y = 10 + (rand() % 25) * 20;
        bool flag = true;
        for(auto &e: snake.sn) {
            if(e == food) flag = false;
        }
        if(flag) break;
    }
    std::cout << "the food position: " << food.x << " " << food.y << "\n";
}

void eat_food()
{
    auto hd = snake.sn[0];
    if(hd == food) {
        snake.sn.insert(snake.sn.begin(), Node(food.x, food.y));
        product_food();
        grade += 25;
    }
}

void move()
{
    for(int i = snake.sn.size() - 1; i > 0; i--) {
        snake.sn[i] = snake.sn[i - 1];
    }
    auto hd = &snake.sn[0];
    switch(dir) {
        case 'U': hd->y -= 20; break;
        case 'D': hd->y += 20; break;
        case 'L': hd->x -= 20; break;
        case 'R': hd->x += 20; break;
    }
    if(hd->x < 0) hd->x = w - 10;
    if(hd->x > w) hd->x = 0 + 10;
    if(hd->y < 0) hd->y = h - 10;
    if(hd->y > h) hd->y = 0 + 10;
}

void play()
{
    using namespace std::chrono;
    srand(time(0));
    auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    while (true)
    {
        if(is_running) {
            auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            if(t2 - t1 > 1000 / speed) {
                move();
                eat_food();
                t1 = t2;
            }
        } else {
            Sleep(10);
        }
    }
}
