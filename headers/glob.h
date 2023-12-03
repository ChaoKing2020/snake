#pragma once

#include <vector>

struct Node
{
    int x, y;
    Node(int xx, int yy):x(xx), y(yy){}
};
struct Snake
{
    std::vector<Node> sn;
};
struct Food
{
    int x, y;
};

extern Snake snake;
extern Food food;
extern int grade;
extern bool is_running;
extern int w, h;
extern int speed;
extern char dir;
