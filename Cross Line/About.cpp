#include "Game_Class.h"



extern MOUSEMSG msg;	// �����Ϣ



//***** ��ʼ�������Ա����ʵ�� *****//

CAbout::CAbout() {}		// ���캯��
CAbout::~CAbout() {}	// ��������



// ���ڽ���
void CAbout::inter_Face_Running()
{
	// ���úͳ�ʼ��
	CButton_Image image;
	bool rb = 0;
	CButton return_button;
	return_button.set_Image(image.return_Button(RGB(224, 197, 150)));
	return_button.set_X_Y((WIN_WIDTH - return_button.get_Image().getwidth()) / 2, 558);

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
					return;
			}
			else
				rb = 0;
		}

		this->clear_Board();
		this->draw_Text();

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

		FlushBatchDraw();
		Sleep(1);
	}
}
// ���ڽ���



// ���Ʊ���
void CAbout::draw_Text()
{
	// ��ʼ����
	setbkmode(TRANSPARENT);
	LOGFONT font;
	gettextstyle(&font);
	font.lfQuality	= ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("΢���ź�"));

	// ���Ʊ���
	font.lfHeight = 75;
	settextstyle(&font);
	settextcolor(TEXT_COLOR);
	outtextxy(	(WIN_WIDTH		- textwidth(TEXT("����")))	/ 2,
				 WIN_HEIGHT / 7 - textheight(TEXT("����")) + 10, TEXT("����"));

	// ���Ʊ߿�
	setfillcolor(RGB(215, 196, 137));
	solidrectangle(50, 130, 430, 525);

	// ��Ϣ���
	font.lfHeight = 25;
	settextstyle(&font);
	settextcolor(TEXT_COLOR);
	outtextxy(70, 150, TEXT("���ƣ�������"));
	outtextxy(70, 180, TEXT("�汾��V1.0"));
	outtextxy(70, 210, TEXT("���ߣ�Lost(QQ:2931404870)"));
	outtextxy(70, 240, TEXT("ʱ�䣺2020-7-23"));
	outtextxy(70, 270, TEXT("��飺��������С��Ϸ"));
	outtextxy(70, 300, TEXT("�淨���ܼ򵥣�������϶����Ƶ㣬ʹ��"));
	outtextxy(70, 330, TEXT("�����߶θ������棬��Ϊ���أ������в�"));
	outtextxy(70, 360, TEXT("ͬ���ĵ㣬�����ƣ�С��̶�����һ"));
	outtextxy(70, 390, TEXT("�߶β��������߶ν��棬���԰�ɫ������"));
	outtextxy(70, 420, TEXT("ƫ��ɫ����һ���Ƶ������߶ζ���������"));
	outtextxy(70, 450, TEXT("�߶ν��棬��õ��԰�ɫ������ƫ��ɫ��"));
	outtextxy(70, 480, TEXT("�̶���ʼ��ƫ��ɫ��"));
}
// ���Ʊ���

//***** ��ʼ�������Ա����ʵ�� *****//