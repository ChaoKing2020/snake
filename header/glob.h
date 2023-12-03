#pragma once

#include <vector>

struct Node
{
    int x, y;
    Node(int xx, int yy):x(xx), y(yy){}
    const Node operator=(const Node& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    const bool operator==(const Node& p) {
        return x == p.x && y == p.y;
    }
};
struct Snake
{
    std::vector<Node> sn;
};

extern Snake snake;
extern Node food;
extern int grade;
extern bool is_running;
extern int w, h;
extern int speed;
extern char dir;
