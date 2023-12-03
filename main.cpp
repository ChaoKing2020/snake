#include <thread>
#include "headers/snake.h"
#include "headers/controller.h"
#include "headers/win.h"


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