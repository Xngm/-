#pragma once
#include "hook.h"
#include "mine.h"
#include "resources.h"

// 游戏状态
struct Game {
    int gold;
    Hook hook;
    Mine mines[MINE_NUM];
    IMAGE mineralImages[6];
    IMAGE yayaImages[2];
    IMAGE background;
	IMAGE victoryImage; // 胜利画面
};

// 游戏系统函数
void game_init(Game* game);
void game_draw(const Game* game);
void game_update(Game* game);
bool check_game_over(const Game* game);
//void handle_Menu(const Game* game);
void victory_music();
void victory_draw(const Game *game);