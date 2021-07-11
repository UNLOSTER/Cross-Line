#include "Game_Class.h"



extern int pasin;				// ��ǰ�ؿ�
extern MOUSEMSG msg;			// �����Ϣ
extern wchar_t best_time[100];	// ���ʱ��
extern int pass_num;			// �ؿ���



//***** ��ʼ�������Ա����ʵ�� *****//

CLevel::CLevel() {}		// ���캯��
CLevel::~CLevel() {}	// ��������



// �ؿ�����
void CLevel::inter_Face_Running()
{
	// ���úͳ�ʼ��
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

	// ������Ϸ
	while (1)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();

			// ���������Ϣ
			if (msg.uMsg == WM_MOUSEWHEEL)
			{
				wheel -= msg.wheel / 5 * 2;
				msg.wheel = 0;

				if (wheel > buffer_len - WIN_HEIGHT)
					wheel = buffer_len - WIN_HEIGHT;

				if (wheel < 0)
					wheel = 0;
			}

			// �رհ�ť
			cb = 0;
			if (close_button.if_Mouse_On(msg))
			{
				cb = 1;

				if (msg.uMsg == WM_LBUTTONUP)
					return;
			}

			// �ؿ���ť
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

		// ����������
		setfillcolor(BASE_COLOR);
		solidrectangle(	WIN_WIDTH - 5, wheel * WIN_HEIGHT / buffer_len, 
						WIN_WIDTH,		wheel * WIN_HEIGHT / buffer_len + bar_len);
		
		// �رհ�ť
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

		// �ؿ���ť
		for (int i = 1; i <= pass_num; i++)
		{
			wchar_t num[100];
			swprintf_s(num, TEXT("%d"), i);
			wchar_t app_name[100];
			swprintf_s(app_name, TEXT("Level%d"), i);			// ����ؿ����

			wchar_t time_info[100];
			GetPrivateProfileString(app_name, TEXT("Record"), TEXT("--:--:--"), best_time, 100, TEXT(".\\Level.ini"));
			swprintf_s(time_info, TEXT("��ѣ�%s"), best_time);	// �������ʱ��

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
// �ؿ�����



// ͳ�ƹؿ���
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
// ͳ�ƹؿ���

//***** ��ʼ�������Ա����ʵ�� *****//