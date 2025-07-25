#pragma once
#include <graphics.h>
#include "mine.h"

// 钩子摆动方向
enum SwingDir { Left, Right };

// 钩子状态
enum State { Normal, Long, Short };

// 钩子结构体
struct Hook {
    int x;
    int y;
    double endx;
    double endy;
    int len;
    float radian;        // 弧度 
    SwingDir swingDir;   // 摆动方向
    float dx;
    float dy;
    float speed;
    State state;
    Mine* caughtMine;    // 捕获的矿物
};

// 钩子系统函数
void hook_init(Hook* hook);
void hook_draw(const Hook* hook);
void hook_swing(Hook* hook);
void hook_control(Hook* hook, Mine mines[], int mineCount);
bool check_collision(const Hook* hook, const Mine* mine);