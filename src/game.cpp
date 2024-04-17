#include <game.h>

Game::Game() {
    // 窗口宽和高
    this->width = 500;
    this->height = 500;
    // 网格大小
    this->unit = 20;
    // 网格个数
    this->cnt = this->width / this->unit;
    // 得分
    this->grade = 0;
    // 游戏运行状态
    this->is_running = false;
    // 游戏运行步长
    this->frame = 10;
    //初始化贪吃蛇
    this->snake = Snake();

    this->food_idx = 0;
    std::string base = "static/snake/";
    this->food_urls = {base + "food/food1.jpg", 
                       base + "food/food2.jpg",
                       base + "food/food3.jpg", 
                       base + "food/food4.jpg"};
    this->body_str = base + "body.png";
    this->bg_str =   base + "bg.png";
    this->left_str = base + "left.png";
    this->right_str = base + "right.png";
    this->up_str =   base + "up.png";
    this->down_str = base + "down.png";
    // // 在地图上随机生成食物
    this->produce_food();
    // 加载游戏图片
    this->load_image();
    // 加载背景音乐
    // this->play_bg_music();
    play_bg_music();
    // 随机种子初始化
    srand(time(0));
}

// 播放背景音乐
// void Game::play_bg_music()
// {
//     // 第一个参数的格式为 "open 文件路径 alias 别名"
//     mciSendString(_T("open static/snake/music.mp3 alias bg_music"), NULL, 0, NULL);
//     mciSendString(_T("play bg_music repeat"), NULL, 0, NULL);
// }

// 加载图片
void Game::load_image()
{
    loadimage(&this->body, (LPCTSTR)this->body_str.c_str());

    loadimage(&this->left, (LPCTSTR)this->left_str.c_str());
    loadimage(&this->right, (LPCTSTR)this->right_str.c_str());
    loadimage(&this->up, (LPCTSTR)this->up_str.c_str());
    loadimage(&this->down, (LPCTSTR)this->down_str.c_str());

    loadimage(&this->img_food, (LPCTSTR)this->food_urls[this->food_idx].c_str());
    
    loadimage(&this->bg, (LPCTSTR)this->bg_str.c_str());
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
    std::cout << "The food position: " << this->food.x << " " << this->food.y << "\n";
}

// 主逻辑运行
void Game::run()
{
    this->snake.move(this->cnt);
    auto flag = this->snake.eat_food(this->food);
    if(flag) {
        this->food_idx = rand() % 4;
        std::cout << this->food_idx << std::endl;
        loadimage(&this->img_food, (LPCTSTR)this->food_urls[this->food_idx].c_str());
        this->produce_food();
        this->grade += 25;
    }
}
