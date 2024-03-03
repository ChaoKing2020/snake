#include <game.h>
#include <graphics.h>
#include <iostream>
#include <chrono>

Game::Game() {
    srand(time(0));
}

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

void Game::run()
{
    this->snake->move();
    auto flag = this->snake->eat_food(this->food);
    if(flag) {
        this->product_food();
        this->grade += 25;
    }
}

void Game::controller()
{
    while (true)
    {
        ExMessage msg;
        while(peekmessage(&msg, EM_KEY)) {
            if(msg.message == WM_KEYDOWN) {
                auto key = msg.vkcode;
                auto dir = this->snake->dir;
                auto speed = this->snake->speed;
                if(dir == 'U' && key == VK_DOWN)  continue;
                if(dir == 'D' && key == VK_UP)    continue;
                if(dir == 'L' && key == VK_RIGHT) continue;
                if(dir == 'R' && key == VK_LEFT)  continue;
                switch(key) {
                    case VK_UP:    this->snake->dir ='U'; break;
                    case VK_DOWN:  this->snake->dir ='D'; break;
                    case VK_LEFT:  this->snake->dir ='L'; break;
                    case VK_RIGHT: this->snake->dir ='R'; break;
                    case VK_F1:    if(speed < 10)  this->snake->speed += 1; std::cout << "speed up\n"; break;
                    case VK_F2:    if(speed > 1)   this->snake->speed -= 1; std::cout << "speed dw\n"; break;
                    case VK_SPACE: this->is_running = !this->is_running; std::cout << "pause\n"; break;
                    case VK_ESCAPE: exit(0);
                }
            }
        }
        Sleep(10);
    }
}

void Game::draw()
{
    while (true)
    {
        cleardevice();

        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 25; j++) {
                if((i + j) % 2 == 0) setfillcolor(RGB(170, 215, 81));
                else setfillcolor(RGB(162, 208, 72));
                solidrectangle(i * 20, j * 20, (i + 1)* 20, (j + 1) * 20);
            }
        }

        setfillcolor(GREEN);
        for(int i = 1; i < this->snake->sn.size(); i++) {
            solidcircle(10 + this->snake->sn[i].x * 20, 10 + this->snake->sn[i].y * 20, 10);
        }
        setfillcolor(BLUE);
        solidcircle(10 + this->snake->sn[0].x * 20, 10 + this->snake->sn[0].y * 20, 10);

        setfillcolor(YELLOW);
        solidcircle(10 + this->food.x * 20, 10 + this->food.y * 20, 10);

        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("times new roman"));

        std::string s = "grade: " + std::to_string(this->grade);
        outtextxy(this->w - 80, 0, (LPTSTR)s.c_str());

        std::string s2 = "speed: " + std::to_string(this->snake->speed);
        outtextxy(this->w - 80 , 20, (LPTSTR)s2.c_str());

        FlushBatchDraw();
        Sleep(10);
    }
}