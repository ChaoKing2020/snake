#include <game.h>

Game::Game() {
    
}

// 播放背景音乐
void Game::play_bg_music()
{
    // 第一个参数的格式为 "open 文件路径 alias 别名"
    mciSendString(_T("open static/snake/music.mp3 alias bg_music"), NULL, 0, NULL);
    mciSendString(_T("play bg_music repeat"), NULL, 0, NULL);
}

// 加载图片
void Game::load_image()
{
    loadimage(&this->body, _T("static/snake/body.png"));
    loadimage(&this->left, _T("static/snake/left.png"));
    loadimage(&this->right, _T("static/snake/right.png"));
    loadimage(&this->up, _T("static/snake/up.png"));
    loadimage(&this->down, _T("static/snake/down.png"));
    loadimage(&this->img_food, _T("static/snake/food.png"));
}

// 初始化
void Game::init() {
    // 窗口宽和高
    this->w = 500;
    this->h = 500;
    // 网格大小
    this->sz = 20;
    // 网格个数
    this->cnt = this->w / this->sz;
    // 得分
    this->grade = 0;
    // 游戏运行状态
    this->is_running = false;
    // 游戏运行步长
    this->frame = 10;
    //初始化贪吃蛇
    this->snake = Snake();
    // 在地图上随机生成食物
    this->produce_food();
    // 加载游戏图片
    this->load_image();
    // 加载背景音乐
    this->play_bg_music();
    // 随机种子初始化
    srand(time(0));
}

// 生成食物
void Game::produce_food() {
    while (true)
    {
        this->food.x = rand() % this->cnt;
        this->food.y = rand() % this->cnt;
        bool flag = true;
        for(auto &e: this->snake.sn) {
            if(e == this->food) {
                flag = false;
                break;
            }
        }
        if(flag) break;
    }
    std::cout << "the food position: " << this->food.x << " " << this->food.y << "\n";
}

// 主逻辑运行
void Game::run()
{
    this->snake.move(this->cnt);
    auto flag = this->snake.eat_food(this->food);
    if(flag) {
        this->produce_food();
        this->grade += 25;
    }
}

// 指令处理，使用一个独立的线程操作
void Game::controller()
{
    while (true)
    {
        ExMessage msg;
        while(peekmessage(&msg, EM_KEY)) {
            if(msg.message == WM_KEYDOWN) {
                auto key = msg.vkcode;
                auto dir = this->snake.dir;
                auto speed = this->snake.speed;
                if(dir == 'L' && key == VK_RIGHT) continue;
                if(dir == 'U' && key == VK_DOWN)  continue;
                if(dir == 'R' && key == VK_LEFT)  continue;
                if(dir == 'D' && key == VK_UP)    continue;
                switch(key) {
                    case VK_UP:
                        this->snake.dir ='U';
                        break;
                    case VK_DOWN:
                        this->snake.dir ='D';
                        break;
                    case VK_LEFT:
                        this->snake.dir ='L';
                        break;
                    case VK_RIGHT:
                        this->snake.dir ='R';
                        break;
                    case VK_F1:
                        if(this->frame < 100) {
                            this->frame++;
                            std::cout << "speed up\n";
                        }
                        break;
                    case VK_F2:
                        if(this->frame > 1) {
                            this->frame--;
                            std::cout << "speed dw\n";
                        }
                        break;
                    case VK_SPACE: 
                        this->is_running = !this->is_running;
                        if(!this->is_running) {
                            std::cout << "pause\n";
                        } else{
                            std::cout << "begin\n";
                        }
                        break;
                    case VK_ESCAPE:
                        exit(0);
                    default:
                        break;
                }
            }
        }
        Sleep(30);
    }
}

// 界面渲染，使用一个独立的线程操作
void Game::draw()
{
    while (true)
    {
        cleardevice();

        for(int i = 0; i < this->cnt; i++) {
            for(int j = 0; j < this->cnt; j++) {
                if((i + j) % 2 == 0) {
                    setfillcolor(RGB(170, 215, 81));
                }
                else {
                    setfillcolor(RGB(162, 208, 72));
                }
                solidrectangle(i * this->sz, j * this->sz, (i + 1)* this->sz, (j + 1) * this->sz);
            }
        }

        for(int i = 1; i < this->snake.sn.size(); i++) {
            int x = this->snake.sn[i].x * this->sz;
            int y = this->snake.sn[i].y * this->sz;
            putimage(x, y, &this->body);
        }

        int hd_x = this->snake.sn[0].x * this->sz;
        int hd_y = this->snake.sn[0].y * this->sz;
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

        int fd_x = this->food.x * this->sz;
        int fd_y = this->food.y * this->sz;
        putimage(fd_x, fd_y, &this->img_food);

        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("times new roman"));

        std::string s = "grade: " + std::to_string(this->grade);
        outtextxy(this->w - 80, 0, (LPTSTR)s.c_str());

        std::string s2 = "speed: " + std::to_string(this->frame);
        outtextxy(this->w - 80 , 20, (LPTSTR)s2.c_str());

        FlushBatchDraw();
        Sleep(10);
    }
}