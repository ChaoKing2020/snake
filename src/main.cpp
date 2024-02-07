#include <chrono>
#include <iostream>

#include <graphics.h>
#include <snake.h>
#include <win.h>
#include <glob.h>

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
    snake.sn = {Node(110, 70), Node(90, 70), Node(70, 70)};
    dir = 'R';

    grade = 0;

    w = 500;
    h = 500;

    is_running = false;
    speed = 10;

    product_food();
}

void controller()
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
                case VK_UP:    dir ='U'; break;
                case VK_DOWN:  dir ='D'; break;
                case VK_LEFT:  dir ='L'; break;
                case VK_RIGHT: dir ='R'; break;
                case VK_F1:    if(speed < 100) speed += 1; break;
                case VK_F2:    if(speed > 1)   speed -= 1; break;
                case VK_SPACE: is_running = !is_running; break;
                case VK_ESCAPE: exit(0);
            }
        }
    }
}

void recv_msg()
{
    ExMessage msg;
    while(peekmessage(&msg, EM_KEY)) {
        if(msg.message == WM_KEYDOWN) {
            auto key = msg.vkcode;
            switch(key) {
                case VK_SPACE: is_running = !is_running; break;
                case VK_ESCAPE: exit(0);
            }
        }
    }
}

int main()
{
    init();
    initgraph(w, h);
    BeginBatchDraw();
    draw();
    
    srand(time(0));
    auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    while (true)
    {
        recv_msg();
        while (is_running) {
            draw();
            controller();
            auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            if(t2 - t1 > 1000 / speed) {
                move();
                eat_food();
                t1 = t2;
            }
        }
        Sleep(10);
    }
    return 0;
}