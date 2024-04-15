#include <thread>
#include <game.h>

int main()
{
    auto game = new Game();
    game->init();
    
    initgraph(game->w, game->h);
    BeginBatchDraw();
    
    std::thread th1([game](){game->controller();});
    std::thread th2([game](){game->draw();});
    th1.detach();
    th2.detach();

    while (true)
    {
        while (game->is_running) {
            game->run();
            Sleep(1000 / game->frame);
        }
    }
    return 0;
}