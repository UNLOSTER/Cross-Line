#include "Game_Class.h"



extern int pasin;				// 当前关卡
extern MOUSEMSG msg;			// 鼠标消息
extern wchar_t best_time[100];	// 最佳时间
extern int pass_num;			// 关卡数



//***** 初始界面类成员函数实现 *****//

CLevel::CLevel() {}		// 构造函数
CLevel::~CLevel() {}	// 构析函数



// 关卡界面
void CLevel::inter_Face_Running()
{
	// 设置和初始化
	CGame *in;
	pass_num = stat();
	static int wheel = 0;
	CButton_Image image;
	bool cb = 0, lb[100] = {0};
	int buffer_len = 50 * 2 + pass_num * image.level_Button(TEXT("0"),
					TEXT("--:--"), RGB(0, 0, 0)).getheight() + (pass_num - 1) * 15;
	int bar_len = WIN_HEIGHT * WIN_HEIGHT / buffer_len;
	CButton close_button, level_button[100];
	close_button.set_Image(image.close_Button(BASE_COLOR));
	close_button.set_X_Y(25, 25);

	// 进入游戏
	while (1)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();

			// 处理滚轮消息
			if (msg.uMsg == WM_MOUSEWHEEL)
			{
				wheel -= msg.wheel / 5 * 2;
				msg.wheel = 0;

				if (wheel > buffer_len - WIN_HEIGHT)
					wheel = buffer_len - WIN_HEIGHT;

				if (wheel < 0)
					wheel = 0;
			}

			// 关闭按钮
			cb = 0;
			if (close_button.if_Mouse_On(msg))
			{
				cb = 1;

				if (msg.uMsg == WM_LBUTTONUP)
					return;
			}

			// 关卡按钮
			for (int i = 1; i <= pass_num; i++)
			{
				lb[i] = 0;

				if (level_button[i].if_Mouse_On(msg))
				{
					lb[i] = 1;

					if (msg.uMsg == WM_LBUTTONUP)
					{
						pasin = i;
						in = new CPlay();
						in->inter_Face_Running();
						delete in;
						in = NULL;
						lb[i] = 0;
					}
				}
			}
		}

		this->clear_Board();

		// 滚动条处理
		setfillcolor(BASE_COLOR);
		solidrectangle(	WIN_WIDTH - 5, wheel * WIN_HEIGHT / buffer_len, 
						WIN_WIDTH,		wheel * WIN_HEIGHT / buffer_len + bar_len);
		
		// 关闭按钮
		if (cb)
		{
			close_button.set_Image(image.close_Button(RGB(125, 125, 125)));
			close_button.draw_Button();
		}
		else
		{
			close_button.set_Image(image.close_Button(TEXT_COLOR));
			close_button.draw_Button();
		}

		// 关卡按钮
		for (int i = 1; i <= pass_num; i++)
		{
			wchar_t num[100];
			swprintf_s(num, TEXT("%d"), i);
			wchar_t app_name[100];
			swprintf_s(app_name, TEXT("Level%d"), i);			// 导入关卡编号

			wchar_t time_info[100];
			GetPrivateProfileString(app_name, TEXT("Record"), TEXT("--:--:--"), best_time, 100, TEXT(".\\Level.ini"));
			swprintf_s(time_info, TEXT("最佳：%s"), best_time);	// 导入最佳时间

			level_button[i].set_X_Y(WIN_WIDTH / 2 - level_button[i].get_Image().getwidth() / 2,
				50 - wheel + (level_button[i].get_Image().getheight() + 15) * (i - 1));

			if (lb[i])
			{
				if (i % 2 == 1)
					level_button[i].set_Image(image.level_Button(num, time_info, RGB(206 + 15, 207 + 15, 141 + 15)));
				else
					level_button[i].set_Image(image.level_Button(num, time_info, RGB(223 + 15, 195 + 15, 123 + 15)));
			}
			else
			{
				if (i % 2 == 1)
					level_button[i].set_Image(image.level_Button(num, time_info, RGB(206, 207, 141)));
				else
					level_button[i].set_Image(image.level_Button(num, time_info, RGB(223, 195, 123)));
			}

			level_button[i].draw_Button();
		}
		

		FlushBatchDraw();
		Sleep(1);
	}
}
// 关卡界面



// 统计关卡数
int CLevel::stat()
{
	wchar_t app_name_all[1000] = { 0 };
	int count = 0;
	GetPrivateProfileSectionNames(app_name_all, 1000, TEXT(".\\Level.ini"));
	for (int i = 0; i < 1000; i++)
	{
		if (app_name_all[0] == '\0')
			break;
		if (app_name_all[i] == '\0')
		{
			count++;
			if (app_name_all[i + 1] == '\0')
				break;
		}
	}
	return count;
}
// 统计关卡数

//***** 初始界面类成员函数实现 *****//