#include <game.h>
#include <util.h>

extern void play_bg_music();

Game::Game() {
    // 窗口宽和高
    this->width = w2;
    this->height = h2;
    // 网格大小
    this->unit = unit2;
    this->cnt = width / unit;
    // 得分
    this->grade = grade2;
    // 游戏运行状态
    this->is_running = false;
    // 游戏运行步长
    this->frame = frame2;
    //初始化贪吃蛇
    this->snake = Snake();
    this->fd_idx = rand() % 4;

    this->food_urls.push_back(food1);
    this->food_urls.push_back(food2);
    this->food_urls.push_back(food3);
    this->food_urls.push_back(food4);
    this->bg_str = bg_str2;
    this->bd_str = bd_str2;
    this->lf_str = lf_str2;
    this->rt_str = rt_str2;
    this->up_str = up_str2;
    this->dw_str = dw_str2;
    // 在地图上随机生成食物
    this->produce_food();
    // 加载游戏图片
    this->load_image();
    // 加载背景音乐
    play_bg_music();
    // 随机种子初始化
    srand(time(0));
}

// 加载图片
void Game::load_image()
{
    loadimage(&this->bg_img, (LPCTSTR)this->bg_str.c_str());

    loadimage(&this->bd_img, (LPCTSTR)this->bd_str.c_str());

    loadimage(&this->lf_img, (LPCTSTR)this->lf_str.c_str());
    loadimage(&this->rt_img, (LPCTSTR)this->rt_str.c_str());
    loadimage(&this->up_img, (LPCTSTR)this->up_str.c_str());
    loadimage(&this->dw_img, (LPCTSTR)this->dw_str.c_str());
}

void Game::update_fd()
{
    this->fd_idx = rand() % 4;
    loadimage(&this->fd_img, (LPCTSTR)this->food_urls[this->fd_idx].c_str());
}

// 生成食物
void Game::produce_food() {
    // 设置食物样式
    this->update_fd();
    // 设置食物位置
    while (true)
    {
        this->food.x = rand() % this->cnt;
        this->food.y = rand() % this->cnt;
        bool is_ok = true;
        for(auto &e: this->snake.sn) {
            if(this->food == e) {
                is_ok = false;
                break;
            }
        }
        if(is_ok) break;
    }
    std::cout << "The food position: " << this->food.x << " " << this->food.y << "\n";
}

// 主逻辑运行
void Game::run()
{
    this->snake.move();
    auto flag = this->snake.eat_food(this->food);
    if(flag) {
        this->produce_food();
        this->grade += 25;
    }
}
