#include <snake.h>

Snake::Snake() {
    this->speed = 1;
    this->sn = {Node(7, 3), Node(6, 3), Node(5, 3)};
    this->dir = 'R';
}

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
        case 'U': hd->y -= this->speed; break;
        case 'D': hd->y += this->speed; break;
        case 'L': hd->x -= this->speed; break;
        case 'R': hd->x += this->speed; break;
    }
    if(hd->x < 0) hd->x = 24;
    if(hd->x > 24) hd->x = 0;
    if(hd->y < 0) hd->y = 24;
    if(hd->y > 24) hd->y = 0;
}
