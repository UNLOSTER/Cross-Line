#pragma once



#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <fstream>



//***** 常量 *****//

#define WIN_WIDTH			480					// 窗口宽度
#define WIN_HEIGHT			640					// 窗口高度
#define BKCOLOR				RGB(246, 231, 184)	// 背景颜色
#define GAME_NAME			TEXT("交叉线")		// 游戏名称
#define TEXT_COLOR			RGB(42, 19, 0)		// 文字颜色
#define BASE_COLOR			RGB(105, 85, 70)	// 基本颜色
#define INF					2147483647			// 无穷大
#define PAPER_POINT_WIDTH	10					// 纸横格点数
#define PAPER_POINT_HEIGHT	11					// 纸竖格点数
#define DISLEN				40					// 纸盘格点间距
#define PAPER_WIDTH			440					// 纸盘宽度
#define PAPER_HEIGHT		480					// 纸盘高度
#define BIG_POINT_R			15					// 大点半径
#define SMALL_POINT_R		7					// 小点半径
#define PAPER_POINT_R		2					// 格点半径



const double	PI		= acos(-1);							// 圆周率
const int		BEGIN_X = (WIN_WIDTH -  PAPER_WIDTH) / 2;	// 纸盘开始坐标
const int		BEGIN_Y = (WIN_HEIGHT - PAPER_HEIGHT) / 2;	// 纸盘结束坐标

//***** 常量 *****//