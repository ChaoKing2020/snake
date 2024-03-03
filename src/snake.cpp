#include <snake.h>

Snake::Snake() {}

bool Snake::eat_food(Food& food) {
    auto hd = this->sn[0];
    if(hd == food) {
        this->sn.insert(this->sn.begin(), Node(food.x, food.y));
        return true;
    }
    return false;
}


void Snake::move() {
    for(int i = this->sn.size() - 1; i > 0; i--) {
        this->sn[i] = this->sn[i - 1];
    }
    auto hd = &this->sn[0];
    switch(dir) {
        case 'U': hd->y -= speed; break;
        case 'D': hd->y += speed; break;
        case 'L': hd->x -= speed; break;
        case 'R': hd->x += speed; break;
    }
    if(hd->x < 0) hd->x = 24;
    if(hd->x > 24) hd->x = 0;
    if(hd->y < 0) hd->y = 24;
    if(hd->y > 24) hd->y = 0;
}
