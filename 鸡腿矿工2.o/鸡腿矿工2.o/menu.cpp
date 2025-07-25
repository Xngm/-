#include "menu.h"
#include <conio.h>
#include <Windows.h>

// 全局菜单实例
MenuItem menu;

void Menu_Init() {
    // 设置菜单尺寸（与屏幕尺寸相同）
    menu.width = 1080;
    menu.height = 640;

    // 加载菜单背景图
    loadimage(&menu.menu_background, L"Resource/images/menu1.png", menu.width, menu.height);

    // 初始状态为激活
    menu.state = MENU_ACTIVE;
    menu.start_time = GetTickCount();
}

void Menu_Draw() {
    // 绘制菜单背景
    putimage(0, 0, &menu.menu_background);

    //// 绘制标题
    //settextstyle(72, 0, _T("华文行楷"));
    //settextcolor(RGB(255, 215, 0)); // 金色
    //setbkmode(TRANSPARENT);

    //// 标题居中
    //const wchar_t* title = L"黄金矿工";
    /*int titleWidth = textwidth(title);
    outtextxy((menu.width - titleWidth) / 2, 100, title);*/

    // 绘制按任意键提示（闪烁效果）
    DWORD currentTime = GetTickCount();
    int blinkState = ((currentTime - menu.start_time) / 500) % 2; // 每500ms切换一次

    if (blinkState == 0) {
        settextstyle(36, 0, _T("楷体"));
        settextcolor(BLUE);

        const wchar_t* prompt = L"按任意键开始游戏";
        int promptWidth = textwidth(prompt);
        outtextxy((menu.width - promptWidth) / 2, menu.height - 150, prompt);
    }

    // 绘制操作说明
    settextstyle(24, 0, _T("宋体"));
    settextcolor(WHITE);

    const wchar_t* controls[] = {
        L"操作说明:",
        L"空格键 - 发射/收回钩子",
        L"ESC键 - 退出游戏",
        L"P键 - 暂停游戏"
    };

    for (int i = 0; i < sizeof(controls) / sizeof(controls[0]); i++) {
        outtextxy(50, menu.height - 150 + i * 30, controls[i]);
    }

    // 绘制版权信息
    settextstyle(18, 0, _T("宋体"));
    settextcolor(RGB(150, 150, 150));
    outtextxy(menu.width - 200, menu.height - 30, L"© 2023 黄金矿工");
}


void Handle_Input_Menu() {
    // 只检查可打印字符键和常用功能键
    const int keysToCheck[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        VK_SPACE, VK_RETURN, VK_ESCAPE, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT
    };

    const int keyCount = sizeof(keysToCheck) / sizeof(keysToCheck[0]);

    for (int i = 0; i < keyCount; i++) {
        int key = keysToCheck[i];
        // 检查按键是否被按下
        if (GetAsyncKeyState(key) & 0x8000) {
            // 等待按键释放
            while (GetAsyncKeyState(key) & 0x8000) {
                Sleep(10);
            }

            // 清空键盘缓冲区
            while (_kbhit()) _getch();

            printf("检测到有效按键: %d\n", key);
            Deactivate_Menu();
            return;
        }
    }
}
bool Is_Menu_Active() {
    return menu.state == MENU_ACTIVE;
}

void Activate_Menu() {
    menu.state = MENU_ACTIVE;
    menu.start_time = GetTickCount();
}

void Deactivate_Menu() {
    menu.state = MENU_INACTIVE;
}