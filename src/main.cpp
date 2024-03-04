#include <cassert>
#include <thread>
#include <graphics.h>
#include <game.h>

int main()
{
    using namespace std::chrono;
    auto game = new Game();
    game->init();
    
    initgraph(game->w, game->h);
    BeginBatchDraw();
    
    // auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    std::thread th([game](){game->controller();});
    std::thread th2([game](){game->draw();});
    th.detach();
    th2.detach();

    while (true)
    {
        while (game->is_running) {
            // auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            // if(t2 - t1 > 1000 / 10) {
            //     game->run();
            //     t1 = t2;
            // }
            game->run();
            Sleep(1000 / game->frame);
        }
    }
    return 0;
}