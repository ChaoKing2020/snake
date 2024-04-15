#include <game.h>
#include <graphics.h>
#include <iostream>
#include <chrono>
#include <mmsystem.h>

Game::Game() {
    
}

void Game::init() {
    this->w = 500;
    this->h = 500;

    this->sz = 20;
    this->cnt = this->w / this->sz;

    this->grade = 0;

    this->is_running = false;
    this->frame = 10;

    this->snake = Snake();
    this->product_food();

    srand(time(0));
    // 第一个参数的格式为 "open 文件路径 alias 别名"
    mciSendString(_T("open static/snake/music.mp3 alias bg_music"), NULL, 0, NULL);
    mciSendString(_T("play bg_music"), NULL, 0, NULL);
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
        Sleep(30);
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

        IMAGE body, left, right, up, down, food;
        loadimage(&body, _T("static/snake/body.png"));
        loadimage(&left, _T("static/snake/left.png"));
        loadimage(&right, _T("static/snake/right.png"));
        loadimage(&up, _T("static/snake/up.png"));
        loadimage(&down, _T("static/snake/down.png"));
        loadimage(&food, _T("static/snake/food.png"));
        // setfillcolor(GREEN);
        for(int i = 1; i < this->snake.sn.size(); i++) {
            int x = this->snake.sn[i].x * this->sz;
            int y = this->snake.sn[i].y * this->sz;
            putimage(x, y, &body);
        }

        int hd_x = this->snake.sn[0].x * this->sz;
        int hd_y = this->snake.sn[0].y * this->sz;
        char dir = this->snake.dir;
        switch (dir)
        {
        case 'U':
            putimage(hd_x, hd_y, &up);
            break;
        case 'D':
            putimage(hd_x, hd_y, &down);
            break;
        case 'L':
            putimage(hd_x, hd_y, &left);
            break;
        case 'R':
            putimage(hd_x, hd_y, &right);
            break;
        default:
            break;
        }

        int fd_x = this->food.x * this->sz;
        int fd_y = this->food.y * this->sz;
        putimage(fd_x, fd_y, &food);

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