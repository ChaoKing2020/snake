#include <iostream>
#include <graphics.h>

#include <win.h>
#include <glob.h>

void draw()
{
    cleardevice();

    draw_map();
    draw_snake();
    draw_food();
    draw_word();

    FlushBatchDraw();
}

void draw_snake()
{
    setfillcolor(GREEN);
    for(int i = 1; i < snake.sn.size(); i++) {
        solidcircle(snake.sn[i].x, snake.sn[i].y, 10);
    }
    setfillcolor(BLUE);
    solidcircle(snake.sn[0].x, snake.sn[0].y, 10);
    
}

void draw_food()
{
    setfillcolor(YELLOW);
    solidcircle(food.x, food.y, 10);
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

void draw_word()
{
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("times new roman"));

    std::string s = "grade: " + std::to_string(grade);
    outtextxy(w - 80, 0, (LPTSTR)s.c_str());

    std::string s2 = "speed: " + std::to_string(speed);
    outtextxy(w - 80 , 20, (LPTSTR)s2.c_str());
}
