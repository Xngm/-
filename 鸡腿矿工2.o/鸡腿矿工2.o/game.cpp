#include "game.h"
#include "resources.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include"settings.h"
#include"Menu.h"
//#include"menu.h"
//void drawImage(int x, int y, const IMAGE* img) {
//    putimage(x, y, img);
//}

void game_init(Game* game) {
    game->gold = 0;

    // 初始化钩子
    hook_init(&game->hook);

    // 加载图片资源 - 使用宽字符串
    loadimage(&game->background, IMG_BACKGROUND.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT - 120);
    loadimage(game->yayaImages + 0, IMG_YAYA_UP.c_str());
    loadimage(game->yayaImages + 1, IMG_YAYA_DOWN.c_str());
    loadimage(&game->victoryImage, IMG_VICTORY.c_str(),SCREEN_WIDTH,SCREEN_HEIGHT);
    
    for (int i = 0; i < 6; i++) {
        int width = 80;
        int height = 80;

        // 根据矿物类型设置不同尺寸
        if (i == BIGSTONE || i == BIGGOLD) {
            width = height = 120;
        }
        else if (i == MONEY || i == LEG) {
            // 使用原始尺寸
            loadimage(game->mineralImages + i, IMG_MINERALS[i].c_str());
            continue;
        }

        loadimage(game->mineralImages + i, IMG_MINERALS[i].c_str(), width, height);
    }

    // 初始化矿物
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < MINE_NUM; i++) {
        mine_init(&game->mines[i], SCREEN_WIDTH, SCREEN_HEIGHT);
    }
	musicOn = true; // 启用音乐;
	isVictory = false;// 初始化胜利状态
}

void game_draw(const Game* game) {
    // 绘制背景
    putimage(0, 120, &game->background);

    // 绘制顶部区域
    setfillcolor(RGB(184, 156, 48));
    solidrectangle(0, 0, SCREEN_WIDTH, 120);

    // 绘制角色
    static DWORD lastTick = GetTickCount();
    static int frameIndex = 0;
	
    if(game->hook.state == Normal||game->hook.state==Long) {
        // 如果钩子处于正常状态，使用上半身图片
        frameIndex = 0;
    } else {
        // 如果钩子处于伸缩状态，使用变化图片
        if (GetTickCount() - lastTick > 500) { // 0.5秒切换一次
            frameIndex = 1 - frameIndex;
            lastTick = GetTickCount();
        }
	}
    drawImage((SCREEN_WIDTH - game->yayaImages[0].getwidth()) / 2,
        0,
        &game->yayaImages[frameIndex]);


    // 绘制钩子
    hook_draw(&game->hook);
    
    // 绘制矿物
    for (int i = 0; i < MINE_NUM; i++) {
        mine_draw(&game->mines[i], game->mineralImages);
    }


    // 绘制分数
    settextstyle(36, 0, _T("楷体"));
    TCHAR str[50];
    _stprintf_s(str, _T("分数:%d"), game->gold);
    outtextxy(20, 20, str);
}

void game_update(Game* game) {
    hook_swing(&game->hook);
    hook_control(&game->hook, game->mines, MINE_NUM);

    // 检查钩子是否带着矿物回到起点
    if (game->hook.state == Normal && game->hook.caughtMine != nullptr) {
        // 增加分数
        game->gold += game->hook.caughtMine->value;

        // 重置矿物状态
        game->hook.caughtMine->isCatch = true;

        // 重置钩子状态
        game->hook.caughtMine = nullptr;

        //mciSendString(_T("")
        //mciSendString(_T("stop victory"), NULL, 0, NULL);
        //mciSendString(_T("seek victory to start"), NULL, 0, NULL);
		//mciSendString(_T("play victory"),NULL,0,NULL); // 播放胜利音效
        //mciSendString(_T("setaudio victory volume to 100"),NULL, 0, NULL);
    }

}

bool check_game_over(const Game * game){
    // 检查是否有矿物被抓住
    for (int i = 0; i < MINE_NUM; i++) {
        if (!game->mines[i].isCatch) {
			return false; // 只要有一个矿物未被抓住，游戏继续
        }
    }
    //mciSendString(_T("stop victory"), NULL, 0, NULL);
    //mciSendString(_T("seek victory to start"), NULL, 0, NULL);
    //mciSendString(_T("play victory"),NULL,0,NULL); // 播放胜利音效
    //mciSendString(_T("setaudio victory volume to 200"),NULL, 0, NULL);
    //

    //settextstyle(48, 0, _T("楷体"));
    //outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, _T("游戏结束！"));
    //outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 10, _T("按任意键退出"));
	return true; // 所有矿物都被抓住，游戏结束
}

void victory_music()
{
    mciSendString(_T("play victory"), NULL, 0, NULL); // 播放胜利音效
    mciSendString(_T("setaudio victory volume to 200"), NULL, 0, NULL);
}

void victory_draw(const Game *game) {
    mciSendString(_T("stop bgm"), NULL, 0, NULL);
    victory_music();
    // 绘制胜利画面
    //settextstyle(48, 0, _T("楷体"));
    //settextcolor(GREEN);
    //outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, _T("游戏胜利！"));
    //outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 10, _T("按任意键退出"));
    putimage(0, 0, &game->victoryImage);
	//printf("打印胜利画面\n");
    // 停止音乐
}

void Handle_Input_Victory(const Game* game)
{
    //打印胜利界面
    victory_draw(game);
    //鼠标信息
	MOUSEMSG msg = GetMouseMsg();
    // 鼠标悬浮退出游戏上时给予反馈（放大字体）
	//printf("%d %d\n", msg.x, msg.y);
    if (msg.x > 470 && msg.x < 610 && msg.y > 415 && msg.y < 445) {
        settextstyle(46, 0, _T("楷体"));
        settextcolor(BROWN);
        //printf("准备退出游戏");
        if(msg.uMsg == WM_LBUTTONDOWN) {
            exit(0); // 退出游戏
			//isVictory= false; // 重置胜利状态
            //Activate_Menu();
		}
    }
    else {
        settextstyle(36, 0, _T("楷体"));
        settextcolor(BROWN);
    }

    // 绘制退出游戏按钮
    const wchar_t* prompt = L"退出游戏";
    int promptWidth = textwidth(prompt);
    outtextxy((SCREEN_WIDTH - promptWidth) / 2, SCREEN_HEIGHT - 230, prompt);
   

}