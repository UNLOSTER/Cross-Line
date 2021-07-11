#include "Game_Class.h"



extern MOUSEMSG msg;	// 鼠标消息



//***** 初始界面类成员函数实现 *****//

CAbout::CAbout() {}		// 构造函数
CAbout::~CAbout() {}	// 构析函数



// 关于界面
void CAbout::inter_Face_Running()
{
	// 设置和初始化
	CButton_Image image;
	bool rb = 0;
	CButton return_button;
	return_button.set_Image(image.return_Button(RGB(224, 197, 150)));
	return_button.set_X_Y((WIN_WIDTH - return_button.get_Image().getwidth()) / 2, 558);

	// 进入游戏
	while (1)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();

			// 返回按钮
			if (return_button.if_Mouse_On(msg))
			{
				rb = 1;

				if (msg.uMsg == WM_LBUTTONUP)
					return;
			}
			else
				rb = 0;
		}

		this->clear_Board();
		this->draw_Text();

		// 返回按钮
		if (rb)
		{
			return_button.set_Image(image.return_Button(RGB(224 + 15, 197 + 15, 150 + 15)));
			return_button.draw_Button();
		}
		else
		{
			return_button.set_Image(image.return_Button(RGB(224, 197, 150)));
			return_button.draw_Button();
		}

		FlushBatchDraw();
		Sleep(1);
	}
}
// 关于界面



// 绘制标题
void CAbout::draw_Text()
{
	// 初始设置
	setbkmode(TRANSPARENT);
	LOGFONT font;
	gettextstyle(&font);
	font.lfQuality	= ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("微软雅黑"));

	// 绘制标题
	font.lfHeight = 75;
	settextstyle(&font);
	settextcolor(TEXT_COLOR);
	outtextxy(	(WIN_WIDTH		- textwidth(TEXT("关于")))	/ 2,
				 WIN_HEIGHT / 7 - textheight(TEXT("关于")) + 10, TEXT("关于"));

	// 绘制边框
	setfillcolor(RGB(215, 196, 137));
	solidrectangle(50, 130, 430, 525);

	// 信息输出
	font.lfHeight = 25;
	settextstyle(&font);
	settextcolor(TEXT_COLOR);
	outtextxy(70, 150, TEXT("名称：交叉线"));
	outtextxy(70, 180, TEXT("版本：V1.0"));
	outtextxy(70, 210, TEXT("作者：Lost(QQ:2931404870)"));
	outtextxy(70, 240, TEXT("时间：2020-7-23"));
	outtextxy(70, 270, TEXT("简介：简洁的益智小游戏"));
	outtextxy(70, 300, TEXT("玩法：很简单，用鼠标拖动可移点，使得"));
	outtextxy(70, 330, TEXT("所有线段各不交叉，则为过关，其中有不"));
	outtextxy(70, 360, TEXT("同类别的点，大点可移，小点固定，若一"));
	outtextxy(70, 390, TEXT("线段不与其他线段交叉，则显白色，否则"));
	outtextxy(70, 420, TEXT("偏棕色，若一可移点所连线段都不与其他"));
	outtextxy(70, 450, TEXT("线段交叉，则该点显白色，否则偏棕色，"));
	outtextxy(70, 480, TEXT("固定点始终偏棕色。"));
}
// 绘制标题

//***** 初始界面类成员函数实现 *****//