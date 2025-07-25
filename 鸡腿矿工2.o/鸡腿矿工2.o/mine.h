#pragma once
#include <graphics.h>
#include"tools.hpp"
// 矿物类型
enum MineralType {
    SMALLSTONE,
    BIGSTONE,
    MONEY,
    SMALLGOLD,
    BIGGOLD,
    LEG
};

// 矿物结构体
struct Mine {
    int x;
    int y;
    int width;      // 矿物宽度
    int height;     // 矿物高度
    MineralType type;
    int value;
    bool isCatch;   // 是否被钩子抓住
};

// 矿物系统函数
void mine_init(Mine* mine, int screenWidth, int screenHeight);
void mine_draw(const Mine* mine, const IMAGE* mineralImages);