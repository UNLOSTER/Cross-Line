#include "Game_Class.h"



extern int pasin;				// ��ǰ�ؿ�
extern MOUSEMSG msg;			// �����Ϣ
extern wchar_t best_time[100];	// ���ʱ��
extern int pass_num;			// �ؿ���
extern long long times;			// ��ʱ��



//***** ��ʼ�������Ա����ʵ�� *****//

CWin::CWin() {}		// ���캯��
CWin::~CWin() {}	// ��������



// ���ؽ���
void CWin::inter_Face_Running()
{
	// ���úͳ�ʼ��
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

	// �޸����ʱ��
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
	
	// ������Ϸ
	while (1)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();

			// ���ذ�ť
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

			// ������ť
			if (again_button.if_Mouse_On(msg))
			{
				ab = 1;

				if (msg.uMsg == WM_LBUTTONUP)
					return;
			}
			else
				ab = 0;

			// ��һ�ذ�ť
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

		// ���ذ�ť
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

		// ������ť
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

		// ��һ�ذ�ť
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
// ���ؽ���



// �޸����ʱ��
void CWin::change_Best_Time()
{
	// ��ʼ��
	wchar_t app_name[100];
	swprintf_s(app_name, TEXT("Level%d"), pasin);
	wchar_t mfo[100];
	swprintf_s(mfo, TEXT("%lld:%lld:%lld"), times / 3600, times / 60, times % 60);
	WritePrivateProfileString(app_name, TEXT("Record"), mfo, TEXT(".\\Level.ini"));
}
// �޸����ʱ��



// ���Ʊ���
void CWin::draw_Title()
{
	// ��ʼ��
	setbkmode(TRANSPARENT);
	LOGFONT font;
	gettextstyle(&font);
	font.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("΢���ź�"));

	// �����
	font.lfHeight = 75;
	settextstyle(&font);

	if (wcscmp(best_time, TEXT("--:--:--")) == 0)
	{
		settextcolor(TEXT_COLOR);
		outtextxy(	(WIN_WIDTH		- textwidth(TEXT("�¼�¼"))) / 2,
					 WIN_HEIGHT / 3 - textheight(TEXT("�¼�¼")), TEXT("�¼�¼"));
	}
	else
	{
		int hour = 0, minute = 0, second = 0;
		swscanf_s(best_time, TEXT("%d:%d:%d"), &hour, &minute, &second);
		long long hms = hour * 3600 + minute * 60 + second;

		if (hms <= times)
		{
			settextcolor(TEXT_COLOR);
			outtextxy(	(WIN_WIDTH		- textwidth(TEXT("������"))) / 2,
						 WIN_HEIGHT / 3 - textheight(TEXT("�����ˣ�")), TEXT("������"));
		}
		else
		{
			settextcolor(TEXT_COLOR);
			outtextxy(	(WIN_WIDTH		- textwidth(TEXT("�¼�¼"))) / 2,
						 WIN_HEIGHT / 3 - textheight(TEXT("�¼�¼")), TEXT("�¼�¼"));
		}
	}

	// ������
	font.lfHeight = 35;
	settextstyle(&font);
	wchar_t info[100];
	swprintf_s(	info, TEXT("��ʱ��%lld:%lld:%lld"), times / 3600, times / 60, times % 60);
	outtextxy(	(WIN_WIDTH - textwidth(info)) / 2,
				 WIN_HEIGHT / 3 + textheight(info), info);
}
// ���Ʊ���

//***** ��ʼ�������Ա����ʵ�� *****//