#include <chrono>
#include <iostream>

#include <graphics.h>
#include <snake.h>
#include <win.h>
#include <glob.h>
#include <cassert>
#include <thread>

using namespace std::chrono;

Snake snake;      // snake
Node food;        // food
int grade;        // total grade
bool is_running;  // whetehr start game or not
int w, h;         // the width and hight of game window
int speed;        // frame rate
char dir;         // the way of snake header

void init()
{
    snake.sn = {Node(7, 3), Node(6, 3), Node(5, 3)};
    dir = 'R';

    grade = 0;

    w = 500;
    h = 500;

    is_running = false;
    speed = 1;

    food.x = 20;
    food.y = 20;
}

void recv_msg()
{
    while (true)
    {
        ExMessage msg;
        while(peekmessage(&msg, EM_KEY)) {
            if(msg.message == WM_KEYDOWN) {
                auto key = msg.vkcode;
                if(dir == 'U' && key == VK_DOWN)  continue;
                if(dir == 'D' && key == VK_UP)    continue;
                if(dir == 'L' && key == VK_RIGHT) continue;
                if(dir == 'R' && key == VK_LEFT)  continue;
                switch(key) {
                    case VK_UP:    dir ='U'; std::cout << "up\n"; break;
                    case VK_DOWN:  dir ='D'; std::cout << "dw\n"; break;
                    case VK_LEFT:  dir ='L'; std::cout << "lf\n"; break;
                    case VK_RIGHT: dir ='R'; std::cout << "rt\n"; break;
                    case VK_F1:    if(speed < 10)  speed += 1; std::cout << "speed up\n"; break;
                    case VK_F2:    if(speed > 1)   speed -= 1; std::cout << "speed dw\n"; break;
                    case VK_SPACE: is_running = !is_running; std::cout << "pause\n"; break;
                    case VK_ESCAPE: exit(0);
                }
            }
        }
        Sleep(10);
    }
}

void run()
{
    move();
    eat_food();
}

int main()
{
    init();
    initgraph(w, h);
    BeginBatchDraw();
    
    srand(time(0));
    auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    std::thread th(recv_msg);
    th.detach();

    std::thread th2(draw);
    th2.detach();

    std::cout << "1";
    while (true)
    {
        while (is_running) {
            auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            if(t2 - t1 > 1000 / 10) {
                run();
                t1 = t2;
            }
        }
        Sleep(10);
    }
    return 0;
}