#include "hook.h"
#include <math.h>
#include <Windows.h>
#include "resources.h"

void hook_init(Hook* hook) {
    hook->x = SCREEN_WIDTH / 2;
    hook->y = 55;
    hook->len = 50; // 钩子长度
    hook->endx = hook->x;
    hook->endy = hook->y + 50;
    hook->radian = 0;
    hook->swingDir = Right; // 初始摆动方向
    hook->dx = 0;
    hook->dy = 0;
    hook->speed = FAST;
    hook->state = Normal;
    hook->caughtMine = nullptr; // 初始未抓住矿物
}

void hook_draw(const Hook* hook) {
    setlinestyle(PS_SOLID, 3);
    setlinecolor(BROWN);
    line(hook->x, hook->y, hook->endx, hook->endy);
}

void hook_swing(Hook* hook) {
    if (hook->state == Normal) {
        // 摆动角度
        if (hook->swingDir == Right) {
            hook->radian += 0.007; // 向右摆动
            if (hook->radian > (3.14159f / 180 * 80)) { // 到达最大角度
                hook->swingDir = Left; // 改变方向
            }
        }
        else if (hook->swingDir == Left) {
            hook->radian -= 0.007; // 向左摆动
            if (hook->radian < -(3.14159f / 180 * 80)) { // 到达最小角度
                hook->swingDir = Right; // 改变方向
            }
        }
        // 计算摆动位置
        hook->endx = hook->x + hook->len * sin(hook->radian);
        hook->endy = hook->y + hook->len * cos(hook->radian);
    }
}

bool check_collision(const Hook* hook, const Mine* mine) {
    // 矿物中心坐标
    int mineCenterX = mine->x + mine->width / 2;
    int mineCenterY = mine->y + mine->height / 2;

    // 钩子末端坐标
    float hookX = hook->endx;
    float hookY = hook->endy;

    // 计算距离平方
    float dx = hookX - mineCenterX;
    float dy = hookY - mineCenterY;
    float distanceSquared = dx * dx + dy * dy;

    // 碰撞半径（取矿物宽高的最小值作为直径）
    int collisionRadius = (mine->width < mine->height) ? mine->width / 2 : mine->height / 2;

    // 检查是否在碰撞范围内
    return distanceSquared < (collisionRadius * collisionRadius);
}

void hook_control(Hook* hook, Mine mines[], int mineCount) {
    // 钩子移动速度
    float speed = hook->speed;

    if (hook->state == Normal && GetAsyncKeyState(VK_SPACE) /*& 0x8000*/) {
        hook->state = Long;
        hook->speed = FAST; // 默认快速
    }

    if (hook->state == Long) {
        hook->endx += sin(hook->radian) * speed;
        hook->endy += cos(hook->radian) * speed;

        // 碰撞检测
        if (hook->caughtMine == nullptr) {
            for (int i = 0; i < mineCount; i++) {
                if (!mines[i].isCatch && check_collision(hook, &mines[i])) {
                    hook->caughtMine = &mines[i];
                    //mines[i].isCatch = true;避免一抓上就消失
                    hook->state = Short;

                    // 根据矿物类型设置速度
                    switch (hook->caughtMine->type) {
                    case SMALLSTONE:
                    case SMALLGOLD:
                    case MONEY:
                    case LEG:
                        hook->speed = NORMAL;
                        break;
                    case BIGSTONE:
                    case BIGGOLD:
                        hook->speed = SLOW;
                        break;
                    }
                    break;
                }
            }
        }
    }
    else if (hook->state == Short) {
        hook->endx -= sin(hook->radian) * hook->speed;
        hook->endy -= cos(hook->radian) * hook->speed;

        // 检查是否回到起点
        float dx = hook->endx - hook->x;
        float dy = hook->endy - hook->y;
        if (dx * dx + dy * dy < hook->len * hook->len) {
            hook->state = Normal;
        }


     /*   if (hook->state == Normal && hook->caughtMine != NULL)
        {
            
            hook->caughtMine->isCatch = 1;
            hook->caughtMine = NULL;
        }*/

        // 更新被抓矿物的位置
        if (hook->caughtMine != nullptr) {
            hook->caughtMine->x =/* static_cast<int>*/(hook->endx - hook->caughtMine->width / 2);
            hook->caughtMine->y =/* static_cast<int>*/(hook->endy - hook->caughtMine->height / 2);
        }
    }

    // 边界检查
    if (hook->endx < 0 || hook->endx > SCREEN_WIDTH || hook->endy > SCREEN_HEIGHT) {
        hook->state = Short;
    }
}