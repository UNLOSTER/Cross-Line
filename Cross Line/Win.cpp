#include "Game_Class.h"



extern int pasin;				// 当前关卡
extern MOUSEMSG msg;			// 鼠标消息
extern wchar_t best_time[100];	// 最佳时间
extern int pass_num;			// 关卡数
extern long long times;			// 计时器



//***** 初始界面类成员函数实现 *****//

CWin::CWin() {}		// 构造函数
CWin::~CWin() {}	// 构析函数



// 过关界面
void CWin::inter_Face_Running()
{
	// 设置和初始化
	CButton_Image image;
	bool rb = 0, ab = 0, nb = 0;
	CButton return_button, again_button, next_button;
	return_button.set_Image(image.return_Button(RGB(224, 197, 150)));
	again_button.set_Image(image.again_Button(RGB(224, 197, 150)));
	next_button.set_Image(image.next_Button(RGB(224, 197, 150)));
	return_button.set_X_Y(	 BEGIN_X + PAPER_WIDTH / 3 - return_button.get_Image().getwidth(),
							WIN_HEIGHT / 7 * 5);
	again_button.set_X_Y(	(WIN_WIDTH  - again_button.get_Image().getwidth()) / 2,
							WIN_HEIGHT / 7 * 5);
	next_button.set_X_Y(	BEGIN_X + PAPER_WIDTH / 3 * 2,
							WIN_HEIGHT / 7 * 5);

	// 修改最佳时间
	if (wcscmp(best_time, TEXT("--:--:--")) == 0)
		this->change_Best_Time();
	else
	{
		int hour = 0, minute = 0, second = 0;
		swscanf_s(best_time, TEXT("%d:%d:%d"), &hour, &minute, &second);
		long long hms = hour * 3600 + minute * 60 + second;

		if (hms > times)
			this->change_Best_Time();
	}
	
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
				{
					pasin = 0;
					return;
				}
			}
			else
				rb = 0;

			// 重来按钮
			if (again_button.if_Mouse_On(msg))
			{
				ab = 1;

				if (msg.uMsg == WM_LBUTTONUP)
					return;
			}
			else
				ab = 0;

			// 下一关按钮
			if (next_button.if_Mouse_On(msg))
			{
				nb = 1;

				if (msg.uMsg == WM_LBUTTONUP)
				{
					pasin++;
					if (pasin > pass_num)
						pasin = pass_num;
					return;
				}
			}
			else
				nb = 0;
		}

		this->clear_Board();
		this->draw_Title();

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

		// 重来按钮
		if (ab)
		{
			again_button.set_Image(image.again_Button(RGB(224 + 15, 197 + 15, 150 + 15)));
			again_button.draw_Button();
		}
		else
		{
			again_button.set_Image(image.again_Button(RGB(224, 197, 150)));
			again_button.draw_Button();
		}

		// 下一关按钮
		if (nb)
		{
			next_button.set_Image(image.next_Button(RGB(224 + 15, 197 + 15, 150 + 15)));
			next_button.draw_Button();
		}
		else
		{
			next_button.set_Image(image.next_Button(RGB(224, 197, 150)));
			next_button.draw_Button();
		}

		FlushBatchDraw();
		Sleep(1);
	}
}
// 过关界面



// 修改最佳时间
void CWin::change_Best_Time()
{
	// 初始化
	wchar_t app_name[100];
	swprintf_s(app_name, TEXT("Level%d"), pasin);
	wchar_t mfo[100];
	swprintf_s(mfo, TEXT("%lld:%lld:%lld"), times / 3600, times / 60, times % 60);
	WritePrivateProfileString(app_name, TEXT("Record"), mfo, TEXT(".\\Level.ini"));
}
// 修改最佳时间



// 绘制标题
void CWin::draw_Title()
{
	// 初始化
	setbkmode(TRANSPARENT);
	LOGFONT font;
	gettextstyle(&font);
	font.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("微软雅黑"));

	// 大标题
	font.lfHeight = 75;
	settextstyle(&font);

	if (wcscmp(best_time, TEXT("--:--:--")) == 0)
	{
		settextcolor(TEXT_COLOR);
		outtextxy(	(WIN_WIDTH		- textwidth(TEXT("新纪录"))) / 2,
					 WIN_HEIGHT / 3 - textheight(TEXT("新纪录")), TEXT("新纪录"));
	}
	else
	{
		int hour = 0, minute = 0, second = 0;
		swscanf_s(best_time, TEXT("%d:%d:%d"), &hour, &minute, &second);
		long long hms = hour * 3600 + minute * 60 + second;

		if (hms <= times)
		{
			settextcolor(TEXT_COLOR);
			outtextxy(	(WIN_WIDTH		- textwidth(TEXT("过关了"))) / 2,
						 WIN_HEIGHT / 3 - textheight(TEXT("过关了！")), TEXT("过关了"));
		}
		else
		{
			settextcolor(TEXT_COLOR);
			outtextxy(	(WIN_WIDTH		- textwidth(TEXT("新纪录"))) / 2,
						 WIN_HEIGHT / 3 - textheight(TEXT("新纪录")), TEXT("新纪录"));
		}
	}

	// 副标题
	font.lfHeight = 35;
	settextstyle(&font);
	wchar_t info[100];
	swprintf_s(	info, TEXT("用时：%lld:%lld:%lld"), times / 3600, times / 60, times % 60);
	outtextxy(	(WIN_WIDTH - textwidth(info)) / 2,
				 WIN_HEIGHT / 3 + textheight(info), info);
}
// 绘制标题

//***** 初始界面类成员函数实现 *****//