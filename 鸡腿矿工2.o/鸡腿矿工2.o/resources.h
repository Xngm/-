#pragma once
#include <string>

// 使用宽字符字符串
const std::wstring IMG_BACKGROUND = L"Resource/images/bk.jpg";
const std::wstring IMG_YAYA_UP = L"Resource/images/yayaup.png";
const std::wstring IMG_YAYA_DOWN = L"Resource/images/yayadown.png";

//菜单背景图
const std::wstring IMG_MENU_BACKGROUND = L"Resource/images/menu1.png";

//胜利画面
const std::wstring IMG_VICTORY = L"Resource/images/victory.png";

const std::wstring IMG_MINERALS[] = {
    L"Resource/images/0.png",    // SMALLSTONE
    L"Resource/images/0.png",    // BIGSTONE
    L"Resource/images/1.png",    // MONEY
    L"Resource/images/2.png",    // SMALLGOLD
    L"Resource/images/2.png",    // BIGGOLD
    L"Resource/images/3.png"     // LEG
};

// 游戏常量
constexpr int MINE_NUM = 1;
constexpr int SCREEN_WIDTH = 1080;
constexpr int SCREEN_HEIGHT = 640;

// 钩子速度
constexpr float FAST =4;
constexpr float NORMAL = 1.5;
constexpr float SLOW = 0.5;

// 音乐和音效开关
extern bool musicOn;          // 音乐开关 
constexpr bool playSoundEffectOn = true; // 音效开关

//胜利判断
extern bool isVictory;