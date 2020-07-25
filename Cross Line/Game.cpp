#include "Game_Class.h"



extern MOUSEMSG msg;	// 鼠标消息



//***** 初始界面类成员函数实现 *****//

CGame::CGame() {}	// 构造函数
CGame::~CGame() {}	// 构析函数



// 绘制背景
void CGame::clear_Board()
{
	setbkcolor(BKCOLOR);
	cleardevice();
}
// 绘制背景

//***** 初始界面类成员函数实现 *****//
