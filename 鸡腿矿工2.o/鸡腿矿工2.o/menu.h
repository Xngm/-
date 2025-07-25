#pragma once
#include <graphics.h>
#include <string>

// 菜单项状态
enum MenuState {
    MENU_ACTIVE,    // 菜单激活状态（等待输入）
    MENU_INACTIVE   // 菜单非激活状态
};

// 菜单结构体
typedef struct {
    int width;                  // 菜单宽度
    int height;                 // 菜单高度
    IMAGE menu_background;      // 菜单背景图像
    MenuState state;            // 菜单状态
    DWORD start_time;           // 菜单开始时间（用于闪烁效果）
} MenuItem;

// 全局菜单实例
extern MenuItem menu;

// 菜单功能函数
void Menu_Init();
void Menu_Draw();
void Handle_Input_Menu();
bool Is_Menu_Active();
void Activate_Menu();
void Deactivate_Menu();