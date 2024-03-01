#include <chrono>
#include <iostream>
#include <graphics.h>

#include <snake.h>
#include <glob.h>


void product_food()
{
    while (true)
    {
        food.x = rand() % 25;
        food.y = rand() % 25;
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
        case 'U': hd->y -= speed; break;
        case 'D': hd->y += speed; break;
        case 'L': hd->x -= speed; break;
        case 'R': hd->x += speed; break;
    }
    if(hd->x < 0) hd->x = 24;
    if(hd->x > 24) hd->x = 0;
    if(hd->y < 0) hd->y = 24;
    if(hd->y > 24) hd->y = 0;
}
