#include "mine.h"
#include <stdlib.h>
#include <time.h>
#include "resources.h"
#include"tools.hpp"

void mine_init(Mine* mine, int screenWidth, int screenHeight) {
    mine->x = rand() % (screenWidth - 200);
    mine->y = rand() % (screenHeight - 161 - 120) + 150;
    mine->isCatch = false;
    mine->type = static_cast<MineralType>(rand() % 6);

    // 根据矿物类型设置尺寸和价值
    switch (mine->type) {
    case SMALLSTONE:
        mine->width = 80;
        mine->height = 80;
        mine->value = 10;
        break;
    case BIGSTONE:
        mine->width = 120;
        mine->height = 120;
        mine->value = 20;
        break;
    case MONEY:
        mine->width = 60;
        mine->height = 60;
        mine->value = 30;
        break;
    case SMALLGOLD:
        mine->width = 80;
        mine->height = 80;
        mine->value = 40;
        break;
    case BIGGOLD:
        mine->width = 120;
        mine->height = 120;
        mine->value = 70;
        break;
    case LEG:
        mine->width = 70;
        mine->height = 70;
        mine->value = 100;
        break;
    }
}

void mine_draw(const Mine* mine,const IMAGE *mineralImages) {
    if (!mine->isCatch) {
        drawImage(mine->x, mine->y, &(mineralImages[mine->type]));
    }
}