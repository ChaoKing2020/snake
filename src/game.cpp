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

    this->sz = 20;
    this->cnt = this->w / this->sz;

    this->grade = 0;

    this->is_running = false;
    this->frame = 30;

    this->snake = Snake();
    this->product_food();
}

void Game::product_food() {
    while (true)
    {
        this->food.x = rand() % this->cnt;
        this->food.y = rand() % this->cnt;
        bool flag = true;
        for(auto &e: this->snake.sn) {
            if(e == this->food) {
                flag = false;
                break;
            }
        }
        if(flag) break;
    }
    std::cout << "the food position: " << this->food.x << " " << this->food.y << "\n";
}

void Game::run()
{
    this->snake.move(this->cnt);
    auto flag = this->snake.eat_food(this->food);
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
                auto dir = this->snake.dir;
                auto speed = this->snake.speed;
                if(dir == 'L' && key == VK_RIGHT) continue;
                if(dir == 'U' && key == VK_DOWN)  continue;
                if(dir == 'R' && key == VK_LEFT)  continue;
                if(dir == 'D' && key == VK_UP)    continue;
                switch(key) {
                    case VK_UP:
                        this->snake.dir ='U';
                        break;
                    case VK_DOWN:
                        this->snake.dir ='D';
                        break;
                    case VK_LEFT:
                        this->snake.dir ='L';
                        break;
                    case VK_RIGHT:
                        this->snake.dir ='R';
                        break;
                    case VK_F1:
                        if(this->frame < 100) {
                            this->frame++;
                            std::cout << "speed up\n";
                        }
                        break;
                    case VK_F2:
                        if(this->frame > 1) {
                            this->frame--;
                            std::cout << "speed dw\n";
                        }
                        break;
                    case VK_SPACE: 
                        this->is_running = !this->is_running;
                        std::cout << "pause\n";
                        break;
                    case VK_ESCAPE:
                        exit(0);
                    default:
                        break;
                }
            }
        }
        Sleep(1);
    }
}

void Game::draw()
{
    while (true)
    {
        cleardevice();

        for(int i = 0; i < this->cnt; i++) {
            for(int j = 0; j < this->cnt; j++) {
                if((i + j) % 2 == 0) {
                    setfillcolor(RGB(170, 215, 81));
                }
                else {
                    setfillcolor(RGB(162, 208, 72));
                }
                solidrectangle(i * this->sz, j * this->sz, (i + 1)* this->sz, (j + 1) * this->sz);
            }
        }

        setfillcolor(GREEN);
        for(int i = 1; i < this->snake.sn.size(); i++) {
            solidcircle(this->sz / 2 + this->snake.sn[i].x * this->sz, this->sz / 2 + this->snake.sn[i].y * this->sz, this->sz / 2);
        }
        setfillcolor(BLUE);
        solidcircle(this->sz / 2 + this->snake.sn[0].x * this->sz, this->sz / 2 + this->snake.sn[0].y * this->sz, this->sz / 2);

        setfillcolor(YELLOW);
        solidcircle(this->sz / 2 + this->food.x * this->sz, this->sz / 2 + this->food.y * this->sz, this->sz / 2);

        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("times new roman"));

        std::string s = "grade: " + std::to_string(this->grade);
        outtextxy(this->w - 80, 0, (LPTSTR)s.c_str());

        std::string s2 = "speed: " + std::to_string(this->frame);
        outtextxy(this->w - 80 , 20, (LPTSTR)s2.c_str());

        FlushBatchDraw();
        Sleep(1);
    }
}