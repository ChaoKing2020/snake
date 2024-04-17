#include <thread>
#include <game.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    auto game = new Game();
    
    initgraph(game->width, game->height);
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

// int main(int argc, char* args[])
// {
//     auto game = new Game();
    
//     initgraph(game->width, game->height);
//     BeginBatchDraw();
    
//     std::thread th1([game](){game->controller();});
//     std::thread th2([game](){game->draw();});
//     th1.detach();
//     th2.detach();

//     while (true)
//     {
//         while (game->is_running) {
//             game->run();
//             Sleep(1000 / game->frame);
//         }
//     }
//     return 0;
// }
