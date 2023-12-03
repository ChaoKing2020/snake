#include <thread>
#include "header/snake.h"
#include "header/controller.h"
#include "header/win.h"


int main()
{
    init();
    std::thread t1(draw);
    std::thread t2(controller);
    std::thread t3(play);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}