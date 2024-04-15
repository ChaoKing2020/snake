#pragma once

#include <node.h>
#include <food.h>
#include <vector>
#include <graphics.h>

class Snake: public Node
{
public:
    char dir;
    char speed;
    std::vector<Node> sn;
    
    void move(int cnt);
    bool eat_food(Food& food);

    Snake();
};