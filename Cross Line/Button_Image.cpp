#include "Game_Class.h"



extern MOUSEMSG msg;	// 鼠标消息



//***** 按钮图形类成员函数实现 *****//

CButton_Image::CButton_Image() {}	// 构造函数
CButton_Image::~CButton_Image() {}	// 构析函数



// 开始按钮图形
IMAGE CButton_Image::start_Button(COLORREF color)
{
	const int width = 150, height = 50;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);	// 绘制方框

	setfillcolor(RGB(225, 225, 225));
	POINT p[3] = {	int(width * ((9 - sqrt(3)) / 18)), height / 6,
					int(width * ((9 - sqrt(3)) / 18)), height / 6 * 5,
					int(width * ((9 + sqrt(3)) / 18)), height / 2, };
	solidpolygon(p, 3);						// 绘制开始图标
	SetWorkingImage(NULL);

	return button;
}
// 开始按钮图形



// 帮助按钮图形
IMAGE CButton_Image::help_Button(COLORREF color)
{
	const int width = 150, height = 50;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);						// 绘制方框

	setfillcolor(RGB(225, 225, 225));
	solidrectangle(	width / 2 - height / 3, height / 6, 
					width / 2 + height / 3, height / 6 * 5);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(color);
	line(	width / 2 - height / 9 * 2, height / 3, 
			width / 2 + height / 9 * 2, height / 3);
	line(	width / 2 - height / 9 * 2, height / 2,
			width / 2 + height / 9 * 2, height / 2);
	line(	width / 2 - height / 9 * 2, height / 3 * 2 + 1,
			width / 2 + height / 9 * 2, height / 3 * 2 + 1);	// 绘制帮助图标
	SetWorkingImage(NULL);

	return button;
}
// 帮助按钮图形



// 关闭按钮图形
IMAGE CButton_Image::close_Button(COLORREF color)
{
	const int width = 25, height = 25;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setfillcolor(BKCOLOR);
	solidrectangle(0, 0, width, height);	// 绘制方框

	setlinestyle(PS_SOLID, 3);
	setlinecolor(color);
	line(width - 5, 5, 5, height - 5);
	line(5, 5, width - 5, height - 5);		// 绘制关闭图标
	SetWorkingImage(NULL);

	return button;
}
// 关闭按钮图形



// 关卡按钮图形
IMAGE CButton_Image::level_Button(const wchar_t num[], const wchar_t tim[], COLORREF color)
{
	const int width = WIN_WIDTH - 75 * 2, height = 64;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setbkmode(TRANSPARENT);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);	// 绘制方框

	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight	= 35;
	font.lfQuality	= ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("微软雅黑"));
	settextstyle(&font);
	settextcolor(RGB(0, 0, 0));
	outtextxy(10, height / 2 - textheight(num) / 2, num);
	outtextxy(width - 10 - textwidth(tim), height / 2 - textheight(tim) / 2, tim);	// 输出文字
	SetWorkingImage(NULL);

	return button;
}
// 关卡按钮图形



// 返回按钮图形
IMAGE CButton_Image::return_Button(COLORREF color)
{
	const int width = 110, height = 50;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);	// 绘制方框

	setfillcolor(BASE_COLOR);
	int rx = width - (width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 - (10 + 5) * 2;
	int ry = (height - (10 + 10 + 10)) / 2;
	setfillcolor(BASE_COLOR);
	solidpie(rx, ry, rx + (10 + 5) * 2, ry + (10 + 5) * 2, PI / 2 * 3, PI / 2);
	setfillcolor(color);
	solidpie(rx + 10, ry + 10, rx + (10 + 5) * 2 - 10, ry + (10 + 5) * 2 - 10, PI / 2 * 3, PI / 2);
	setfillcolor(BASE_COLOR);
	solidrectangle(	(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 + 10 * (int)sqrt(3),		ry,
					(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 + 10 * (int)sqrt(3) + 20,	ry + 10);
	solidrectangle(	(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 + 5  * (int)sqrt(3),		ry + 20,
					(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 + 10 * (int)sqrt(3) + 20,	ry + 30);
	POINT p[3] = {	(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 + 10 * (int)sqrt(3),		ry - 5,
					(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2 + 10 * (int)sqrt(3),		ry + 10 + 5, 
					(width - (10 * (int)sqrt(3) + 20 + 10 + 5)) / 2					   ,		ry + 5 };
	solidpolygon(p, 3);						// 绘制返回图标
	SetWorkingImage(NULL);

	return button;
}
// 返回按钮图形



// 重来按钮图形
IMAGE CButton_Image::again_Button(COLORREF color)
{
	const int width = 110, height = 50;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);	// 绘制方框

	setfillcolor(BASE_COLOR);
	int rx = (width - 10 * 4) / 2;
	int ry = (height - 10 * 4) / 2;
	setfillcolor(BASE_COLOR);
	solidpie(rx, ry, rx + 10 * 4, ry + 10 * 4, PI / 2 * 3, PI);
	setfillcolor(color);
	solidpie(rx + 10, ry + 10, rx + 10 * 4 - 10, ry + 10 * 4 - 10, PI / 2 * 3, PI);
	setfillcolor(BASE_COLOR);
	POINT p[3] = {	rx - 5,			ry + 10 * 2,
					rx + 10 + 5,	ry + 10 * 2,
					rx + 5,			ry + 10 * 2 + 10 * (int)sqrt(3) };
	solidpolygon(p, 3);						// 绘制返回图标
	SetWorkingImage(NULL);

	return button;
}
// 重来按钮图形



// 下一关按钮图形
IMAGE CButton_Image::next_Button(COLORREF color)
{
	const int width = 110, height = 50;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);	// 绘制方框

	setfillcolor(BASE_COLOR);
	POINT p1[3] = {	int(width * ((9 - sqrt(3)) / 18)) - 5, height / 6,
					int(width * ((9 - sqrt(3)) / 18)) - 5, height / 6 * 5,
					int(width * ((9 + sqrt(3)) / 18)) - 5, height / 2, };
	solidpolygon(p1, 3);
	POINT p2[3] = { int(width * ((9 - sqrt(3)) / 18)) + 5, height / 6,
					int(width * ((9 - sqrt(3)) / 18)) + 5, height / 6 * 5,
					int(width * ((9 + sqrt(3)) / 18)) + 5, height / 2, };
	solidpolygon(p2, 3);					// 绘制下关图标
	SetWorkingImage(NULL);

	return button;
}
// 下关按钮图形



// O K 按钮图形
IMAGE CButton_Image::ok_Button(COLORREF color)
{
	const int width = 75, height = 50;
	IMAGE button(width, height);

	SetWorkingImage(&button);
	setbkmode(TRANSPARENT);
	setfillcolor(color);
	solidrectangle(0, 0, width, height);							// 绘制方框

	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight = 35;
	font.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("微软雅黑"));
	settextstyle(&font);
	settextcolor(RGB(225, 225, 225));
	outtextxy(	(width  - textwidth( TEXT("OK"))) / 2,
				(height - textheight(TEXT("OK"))) / 2, TEXT("OK"));	// 输出文字
	SetWorkingImage(NULL);

	return button;
}
// O K 按钮图形

//***** 按钮图形类成员函数实现 *****//
