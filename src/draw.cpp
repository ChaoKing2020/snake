#include <game.h>

// 界面渲染，使用一个独立的线程操作
void Game::draw()
{
    while (true)
    {
        cleardevice();
        
        // 描绘背景
        putimage(0, 0, &this->bg);

        // 描绘蛇身
        for(int i = 1; i < this->snake.sn.size(); i++) {
            int x = this->snake.sn[i].x * this->unit;
            int y = this->snake.sn[i].y * this->unit;
            putimage(x, y, &this->body);
        }

        // 描绘蛇头
        int hd_x = this->snake.sn[0].x * this->unit;
        int hd_y = this->snake.sn[0].y * this->unit;
        switch (this->snake.dir)
        {
        case 'U':
            putimage(hd_x, hd_y, &this->up);
            break;
        case 'D':
            putimage(hd_x, hd_y, &this->down);
            break;
        case 'L':
            putimage(hd_x, hd_y, &this->left);
            break;
        case 'R':
            putimage(hd_x, hd_y, &this->right);
            break;
        default:
            break;
        }

        // 描绘食物
        int fd_x = this->food.x * this->unit;
        int fd_y = this->food.y * this->unit;
        putimage(fd_x, fd_y, &this->img_food);

        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("times new roman"));

        std::string s = "grade: " + std::to_string(this->grade);
        outtextxy(this->width - 80, 0, (LPTSTR)s.c_str());

        std::string s2 = "speed: " + std::to_string(this->frame);
        outtextxy(this->width - 80 , 20, (LPTSTR)s2.c_str());

        FlushBatchDraw();
        Sleep(10);
    }
}