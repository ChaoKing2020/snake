#include <snake.h>

Snake::Snake() {
    this->speed = 1;
    this->sn = {Node(7, 3), Node(6, 3), Node(5, 3)};
    this->dir = 'R';
}

bool Snake::eat_food(Food& food) {
    auto hd = this->sn[0];
    if(hd == food) {
        mciSendString(_T("close food_music"), NULL, 0, NULL); // 关闭音乐
        mciSendString(_T("open static/snake/music-food.mp3 alias food_music"), NULL, 0, NULL);
        mciSendString(_T("play food_music"), NULL, 0, NULL);
        this->sn.insert(this->sn.begin(), Node(food.x, food.y));
        return true;
    }
    return false;
}


void Snake::move(int cnt) {
    for(int i = this->sn.size() - 1; i > 0; i--) {
        this->sn[i] = this->sn[i - 1];
    }
    auto hd = &this->sn[0];
    switch(dir) {
        case 'U': 
            hd->y -= this->speed; 
            break;
        case 'D': 
            hd->y += this->speed;
            break;
        case 'L': 
            hd->x -= this->speed;
            break;
        case 'R':
            hd->x += this->speed;
            break;
    }
    cnt -= 1;
    if(hd->x < 0) hd->x = cnt;
    if(hd->x > cnt) hd->x = 0;
    if(hd->y < 0) hd->y = cnt;
    if(hd->y > cnt) hd->y = 0;
}
