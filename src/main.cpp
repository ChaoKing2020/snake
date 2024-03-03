#include <chrono>
#include <iostream>
#include <graphics.h>
#include <snake.h>
#include <cassert>
#include <thread>
#include <game.h>


void draw_snake(Game* game)
{
    setfillcolor(GREEN);
    for(int i = 1; i < game->snake->sn.size(); i++) {
        solidcircle(10 + game->snake->sn[i].x * 20, 10 + game->snake->sn[i].y * 20, 10);
    }
    setfillcolor(BLUE);
    solidcircle(10 + game->snake->sn[0].x * 20, 10 + game->snake->sn[0].y * 20, 10);
    
}

void draw_food(Game* game)
{
    setfillcolor(YELLOW);
    solidcircle(10 + game->food.x * 20, 10 + game->food.y * 20, 10);
}

void draw_map()
{
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 25; j++) {
            if((i + j) % 2 == 0) setfillcolor(RGB(170, 215, 81));
            else setfillcolor(RGB(162, 208, 72));
            solidrectangle(i * 20, j * 20, (i + 1)* 20, (j + 1) * 20);
        }
    }
}

void draw_word(Game* game)
{
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("times new roman"));

    std::string s = "grade: " + std::to_string(game->grade);
    outtextxy(game->w - 80, 0, (LPTSTR)s.c_str());

    std::string s2 = "speed: " + std::to_string(game->snake->speed);
    outtextxy(game->w - 80 , 20, (LPTSTR)s2.c_str());
}


void draw(Game* game)
{
    while (true)
    {
        cleardevice();
        draw_map();
        draw_snake(game);
        draw_food(game);
        draw_word(game);
        FlushBatchDraw();
        Sleep(10);
    }
}


// 接收来自键盘的命令
void recv_msg(Game* game)
{
    while (true)
    {
        ExMessage msg;
        while(peekmessage(&msg, EM_KEY)) {
            if(msg.message == WM_KEYDOWN) {
                auto key = msg.vkcode;
                auto dir = game->snake->dir;
                auto speed = game->snake->speed;
                if(dir == 'U' && key == VK_DOWN)  continue;
                if(dir == 'D' && key == VK_UP)    continue;
                if(dir == 'L' && key == VK_RIGHT) continue;
                if(dir == 'R' && key == VK_LEFT)  continue;
                switch(key) {
                    case VK_UP:    game->snake->dir ='U'; break;
                    case VK_DOWN:  game->snake->dir ='D'; break;
                    case VK_LEFT:  game->snake->dir ='L'; break;
                    case VK_RIGHT: game->snake->dir ='R'; break;
                    case VK_F1:    if(speed < 10)  game->snake->speed += 1; std::cout << "speed up\n"; break;
                    case VK_F2:    if(speed > 1)   game->snake->speed -= 1; std::cout << "speed dw\n"; break;
                    case VK_SPACE: game->is_running = !game->is_running; std::cout << "pause\n"; break;
                    case VK_ESCAPE: exit(0);
                }
            }
        }
        Sleep(10);
    }
}

// 程序运行
void run(Game* game)
{
    game->snake->move();
    auto flag = game->snake->eat_food(game->food);
    if(flag) {
        game->product_food();
        game->grade += 25;
    }
}

int main()
{
    using namespace std::chrono;
    auto game = new Game();
    game->init();
    initgraph(game->w, game->h);
    BeginBatchDraw();
    
    srand(time(0));
    auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    std::thread th(recv_msg, game);
    th.detach();

    std::thread th2(draw, game);
    th2.detach();

    while (true)
    {
        while (game->is_running) {
            auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            if(t2 - t1 > 1000 / 10) {
                run(game);
                t1 = t2;
            }
        }
        Sleep(10);
    }
    return 0;
}