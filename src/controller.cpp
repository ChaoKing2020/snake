#include <chrono>
#include <iostream>
#include <graphics.h>

#include "../header/glob.h"

void controller()
{
    while (true)
    {
        ExMessage msg;
        while(peekmessage(&msg, EM_KEY)) {
            if(msg.message == WM_KEYDOWN) {
                auto key = msg.vkcode;
                auto hd = &snake.sn[0];
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
        Sleep(10);
    }
}