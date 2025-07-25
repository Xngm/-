#include "game.h"
#include "menu.h" // 包含菜单头文件
#include <conio.h>
#include"settings.h"
bool isVictory = false; // 全局变量，表示游戏是否胜利
int main() {
    // 初始化图形窗口
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, EX_SHOWCONSOLE);
    setbkmode(TRANSPARENT);

    // 初始化菜单
    Menu_Init();

    // 初始化游戏
    Game game;
    game_init(&game);

    // 初始为菜单状态
    bool inMenu = true;

    // 游戏主循环
    while (true) {
        // 双缓冲绘图
        if (isVictory)
        {
            victory_draw(&game);
			//system("pause"); // 等待用户按任意键
            continue;
        }
        BeginBatchDraw();
        cleardevice();


        if (inMenu) {
            // 菜单状态
            Menu_Draw();
            Handle_Input_Menu();

            // 检查是否要退出菜单
            if (!Is_Menu_Active()) {
                inMenu = false;
                // 可以在这里添加游戏开始的音效
            }
        }
        else {
            // 游戏状态
            game_update(&game);
            game_draw(&game);

			//调用音乐函数
			musicOn = true; // 确保音乐开启
            Music();
			playSoundEffect();
            // 检查ESC键退出
            if (GetAsyncKeyState(VK_ESCAPE) /*& 0x8000*/) {
				//inMenu = true;
                break;
            }

            //检查游戏是否结束
            if (check_game_over(&game))
            {
				isVictory = true; // 设置胜利状态
            }

            // 检查P键暂停（返回菜单）
            if (GetAsyncKeyState('P') /*& 0x8000*/) {
                inMenu = true;
                closeMusic();
                Activate_Menu();
                // 添加暂停音效
                Sleep(200); // 防止连续检测
            }
        }

        EndBatchDraw();
        Sleep(10);  // 控制游戏速度
    }

    closegraph();
    return 0;
}