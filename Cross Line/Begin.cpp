#include "Game_Class.h"



extern MOUSEMSG msg;	// �����Ϣ



//***** ��ʼ�������Ա����ʵ�� *****//

CBegin::CBegin() {}		// ���캯��
CBegin::~CBegin() {}	// ��������



// ��ʼ����
void CBegin::inter_Face_Running()
{
	// ���úͳ�ʼ��
	CGame *in;
	CButton_Image image;
	bool sb = 0, hb = 0;
	CButton start_button, help_button;
	start_button.set_Image(image.start_Button(RGB(189, 160, 97)));
	help_button.set_Image(image.help_Button(RGB(149, 186, 122)));
	start_button.set_X_Y(	WIN_WIDTH / 2 - start_button.get_Image().getwidth() / 2,
							WIN_HEIGHT / 7 * 3);
	help_button.set_X_Y(	WIN_WIDTH / 2 - help_button.get_Image().getwidth() / 2,
							WIN_HEIGHT / 7 * 4);

	// ������Ϸ
	while (1)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();

			// ��ʼ��ť
			if (start_button.if_Mouse_On(msg))
			{
				sb = 1;

				if (msg.uMsg == WM_LBUTTONUP)
				{
					in = new CLevel();
					in->inter_Face_Running();
					delete in;
					in = NULL;
				}
			}
			else
				sb = 0;

			// ������ť
			if (help_button.if_Mouse_On(msg))
			{
				hb = 1;

				if (msg.uMsg == WM_LBUTTONUP)
				{
					in = new CAbout();
					in->inter_Face_Running();
					delete in;
					in = NULL;
				}
			}
			else
				hb = 0;
		}

		this->clear_Board();
		this->draw_Title();

		// ��ʼ��ť
		if (sb)
		{
			start_button.set_Image(image.start_Button(RGB(189 + 15, 160 + 15, 97 + 15)));
			start_button.draw_Button();
		}
		else
		{
			start_button.set_Image(image.start_Button(RGB(189, 160, 97)));
			start_button.draw_Button();
		}

		// ������ť
		if (hb)
		{
			help_button.set_Image(image.help_Button(RGB(149 + 15, 186 + 15, 122 + 15)));
			help_button.draw_Button();
		}
		else
		{
			help_button.set_Image(image.help_Button(RGB(149, 186, 122)));
			help_button.draw_Button();
		}

		FlushBatchDraw();
		Sleep(1);
	}
}
// ��ʼ����



// ���Ʊ���
void CBegin::draw_Title()
{
	setbkmode(TRANSPARENT);
	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight	= 75;
	font.lfQuality	= ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("΢���ź�"));
	settextstyle(&font);
	settextcolor(TEXT_COLOR);
	outtextxy(	(WIN_WIDTH		- textwidth(	GAME_NAME))	/ 2, 
				 WIN_HEIGHT / 3 - textheight(	GAME_NAME), GAME_NAME);
}
// ���Ʊ���

//***** ��ʼ�������Ա����ʵ�� *****//