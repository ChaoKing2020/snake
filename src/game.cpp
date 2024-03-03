#include <game.h>
#include <iostream>

Game::Game() {}

void Game::init() {
    this->w = 500;
    this->h = 500;

    this->grade = 0;

    this->is_running = false;

    this->food = Food(20, 20);
    this->snake = new Snake();
    this->snake->sn = {Node(7, 3), Node(6, 3), Node(5, 3)};
    this->snake->dir = 'R';
    this->snake->speed = 1;
}

void Game::product_food() {
    while (true)
    {
        this->food.x = rand() % 25;
        this->food.y = rand() % 25;
        bool flag = true;
        for(auto &e: this->snake->sn) {
            if(e == this->food) flag = false;
        }
        if(flag) break;
    }
    std::cout << "the food position: " << this->food.x << " " << this->food.y << "\n";
}