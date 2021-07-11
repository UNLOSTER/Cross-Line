#include "Game_Class.h"



extern int pasin;									// ��ǰ�ؿ�
int CPlay::point_num, CPlay::line_num;				// ����������
extern MOUSEMSG msg;								// �����Ϣ
extern wchar_t best_time[100];						// ���ʱ��
extern CPoint my_point[200], my_point_save[200];	// ����Ϣ������Ϣ����
extern CLine my_line[50000];						// ����Ϣ
extern int my_x_flag, my_y_flag, paper[20][20];		// ֽ����Ϣ
extern bool point_flag[200];						// �ƶ����
extern int pass_num;								// �ؿ���
extern long long times, start_time;					// ��ʱ��



//***** ��Ϸ�������Ա����ʵ�� *****//

CPlay::CPlay()	{}	// ���캯��
CPlay::~CPlay()	{}	// ��������



// ��Ϸ����
void CPlay::inter_Face_Running()
{
	// ���úͳ�ʼ��
	CGame *in;
	clear();
	read_Level();
	CButton_Image image;
	bool rb = 0, ab = 0, nb = 0, ob = 0;
	CButton return_button, again_button, next_button, ok_button;
	return_button.set_Image(image.return_Button(RGB(224, 197, 150)));
	again_button.set_Image(image.again_Button(RGB(224, 197, 150)));
	next_button.set_Image(image.next_Button(RGB(224, 197, 150)));
	ok_button.set_Image(image.ok_Button(RGB(66, 202, 184)));
	return_button.set_X_Y(	 BEGIN_X + PAPER_WIDTH / 3 - return_button.get_Image().getwidth(),
							(WIN_HEIGHT + BEGIN_Y + PAPER_HEIGHT - return_button.get_Image().getheight()) / 2);
	again_button.set_X_Y(	(WIN_WIDTH  - again_button.get_Image().getwidth()) / 2,
							(WIN_HEIGHT + BEGIN_Y + PAPER_HEIGHT - again_button.get_Image().getheight())  / 2);
	next_button.set_X_Y(	BEGIN_X + PAPER_WIDTH / 3 * 2,
							(WIN_HEIGHT + BEGIN_Y + PAPER_HEIGHT - next_button.get_Image().getheight())  / 2);
	ok_button.set_X_Y(		(WIN_WIDTH  - ok_button.get_Image().getwidth()) / 2,
							(WIN_HEIGHT + BEGIN_Y + PAPER_HEIGHT - ok_button.get_Image().getheight())  / 2);
	start_time = int(time(NULL));

	// ������Ϸ
	while (1)
	{
		if (if_Win())
		{
			while (MouseHit())
			{
				msg = GetMouseMsg();

				// O K ��ť
				if (ok_button.if_Mouse_On(msg))
				{
					ob = 1;

					if (msg.uMsg == WM_LBUTTONUP)
					{
						in = new CWin();
						in->inter_Face_Running();
						delete in;
						in = NULL;
						if (!pasin)
							return;
						clear();
						read_Level();
					}
				}
				else
					ob = 0;
			}

			this->clear_Board();
			this->draw_Title();
			this->draw_Paper();
			this->draw_Graph();

			if (ob)
			{
				ok_button.set_Image(image.ok_Button(RGB(66 + 15, 202 + 15, 184 + 15)));
				ok_button.draw_Button();
			}
			else
			{
				ok_button.set_Image(image.ok_Button(RGB(66, 202, 184)));
				ok_button.draw_Button();
			}
		}
		else
		{
			while (MouseHit())
			{
				msg = GetMouseMsg();

				// �ƶ���
				for (int i = 1; i <= point_num; i++)
					this->point_Move(i);

				// ���ذ�ť
				if (return_button.if_Mouse_On(msg))
				{
					rb = 1;

					if (msg.uMsg == WM_LBUTTONUP)
					{
						msg.uMsg = NULL;
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
					{
						clear();
						read_Level();
					}
				}
				else
					ab = 0;

				// ��һ�ذ�ť
				if (next_button.if_Mouse_On(msg))
				{
					nb = 1;

					if (msg.uMsg == WM_LBUTTONUP)
					{
						clear();
						pasin++;
						if (pasin > pass_num)
							pasin = pass_num;
						read_Level();
					}
				}
				else
					nb = 0;
			}

			times = int(time(NULL)) - start_time;

			this->clear_Board();
			this->draw_Title();
			this->draw_Paper();
			this->draw_Graph();

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
		}

		FlushBatchDraw();
		Sleep(1);
	}
}
// ��Ϸ����



// ��ȡ�ؿ�
void CPlay::read_Level()
{
	// ���ļ�
	wchar_t app_name[100];
	swprintf_s(app_name, TEXT("Level%d"), pasin);

	GetPrivateProfileString(app_name, TEXT("Record"), TEXT("--:--:--"), best_time, 100, TEXT(".\\Level.ini"));

	// ��ȡ����Ϣ
	this->point_num = GetPrivateProfileInt(app_name, TEXT("DotCount"), 0, TEXT(".\\Level.ini"));
	for (int i = 1; i <= this->point_num; i++)
	{
		wchar_t name[100];
		swprintf_s(name, TEXT("DotData%d"), i);
		wchar_t dot_data[100];
		GetPrivateProfileString(app_name, name, TEXT("0,0,0"), dot_data, 100, TEXT(".\\Level.ini"));
		int m = 0;
		swscanf_s(dot_data, TEXT("%d,%d,%d"), &my_point[i].x, &my_point[i].y, &m);
		my_point[i].move = m;
		if (my_point[i].x == 0)
			my_point[i].x = rand() % PAPER_POINT_HEIGHT + 1;
		if (my_point[i].y == 0)
			my_point[i].y = rand() % PAPER_POINT_WIDTH + 1;
		while (1)
		{
			if (!paper[my_point[i].x][my_point[i].y])
				break;

			my_point[i].x = rand() % PAPER_POINT_HEIGHT + 1;
			my_point[i].y = rand() % PAPER_POINT_WIDTH + 1;
		}
		paper[my_point[i].x][my_point[i].y] = i;
		my_point[i].x = my_point[i].x * DISLEN + BEGIN_Y;
		my_point[i].y = my_point[i].y * DISLEN + BEGIN_X;
		my_point_save[i].x = my_point[i].x;
		my_point_save[i].y = my_point[i].y;
	}

	// ��ȡ����Ϣ
	this->line_num = GetPrivateProfileInt(app_name, TEXT("LineCount"), 0, TEXT(".\\Level.ini"));
	for (int i = 1; i <= this->line_num; i++)
	{
		wchar_t name[100];
		swprintf_s(name, TEXT("LineData%d"), i);
		wchar_t line_data[100];
		GetPrivateProfileString(app_name, name, TEXT("0,0"), line_data, 100, TEXT(".\\Level.ini"));
		swscanf_s(line_data, TEXT("%d,%d"), &my_line[i].a, &my_line[i].b);
	}
}
// ��ȡ�ؿ�



// ���Ʊ���
void CPlay::draw_Title()
{
	setbkmode(TRANSPARENT);
	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight	= 35;
	font.lfQuality	= ANTIALIASED_QUALITY;
	wcscpy_s(font.lfFaceName, TEXT("΢���ź�"));
	settextstyle(&font);
	settextcolor(TEXT_COLOR);

	wchar_t info[100];
	swprintf_s( info, TEXT("�ؿ�-%d    %lld:%lld:%lld    ��ѣ�%s"),
				pasin, times / 3600, times / 60, times % 60, best_time);
	outtextxy(	(WIN_WIDTH - textwidth(info))  / 2,
				(BEGIN_Y   - textheight(info)) / 2, info);
}
// ���Ʊ���



// ����ֽ��
void CPlay::draw_Paper()
{
	// ������
	setfillcolor(RGB(215, 196, 137));
	solidrectangle(BEGIN_X, BEGIN_Y, BEGIN_X + PAPER_WIDTH, BEGIN_Y + PAPER_HEIGHT);

	// �����
	setfillcolor(TEXT_COLOR);
	for (int i = 1; i <= PAPER_POINT_HEIGHT; i++)
		for (int j = 1; j <= PAPER_POINT_WIDTH; j++)
			solidcircle(j * DISLEN + BEGIN_X, i * DISLEN + BEGIN_Y, PAPER_POINT_R);
}
// ����ֽ��



// ����ͼ
void CPlay::draw_Graph()
{
	// ������
	setlinestyle(PS_SOLID, 3);
	for (int i = 1; i <= this->line_num; i++)
	{
		bool cross = 0;
		for (int j = 1; j <= this->line_num; j++)
		{
			if (j == i)
				continue;

			if (my_line[i].line_Cross(my_line[j]))
			{
				cross = 1;
				break;
			}
		}

		if (cross)
			setlinecolor(BASE_COLOR);
		else
			setlinecolor(RGB(225, 225, 225));

		line(my_point[my_line[i].a].y, my_point[my_line[i].a].x, 
			 my_point[my_line[i].b].y, my_point[my_line[i].b].x);
	}

	// ���ƹ̶���
	for (int i = 1; i <= this->point_num; i++)
		if (!my_point[i].move)
		{
			setfillcolor(BASE_COLOR);
			solidcircle(my_point[i].y, my_point[i].x, SMALL_POINT_R);
		}

	// ���ƿ����Ҳ������ƶ���
	for (int i = 1; i <= this->point_num; i++)
		if (my_point[i].move && !point_flag[i])
		{
			for (int j = 1; j <= this->line_num; j++)
			{
				if (my_line[j].a != i && my_line[j].b != i)
					continue;

				bool cross = 0;

				for (int k = 1; k <= this->line_num; k++)
				{
					if (j == k)
						continue;

					if (my_line[k].line_Cross(my_line[j]))
					{
						cross = 1;
						break;
					}
				}

				if (cross)
				{
					setfillcolor(BASE_COLOR);
					break;
				}
				else
					setfillcolor(RGB(225, 225, 225));
			}
			solidcircle(my_point[i].y, my_point[i].x, BIG_POINT_R);
		}

	// ���������ƶ���
	for (int i = 1; i <= this->point_num; i++)
		if (point_flag[i])
		{
			for (int j = 1; j <= this->line_num; j++)
			{
				if (my_line[j].a != i && my_line[j].b != i)
					continue;

				bool cross = 0;

				for (int k = 1; k <= this->line_num; k++)
				{
					if (j == k)
						continue;

					if (my_line[k].line_Cross(my_line[j]))
					{
						cross = 1;
						break;
					}
				}

				if (cross)
				{
					setfillcolor(BASE_COLOR);
					break;
				}
				else
					setfillcolor(RGB(225, 225, 225));
			}
			solidcircle(my_point[i].y, my_point[i].x, BIG_POINT_R);
		}
}
// ����ͼ



// �ƶ���
void CPlay::point_Move(int point_id)
{
	// ���㲻���ƶ�������
	if (!my_point[point_id].move)
		return;

	int save_x = (my_point_save[point_id].x - BEGIN_Y + DISLEN / 2) / 40;
	int save_y = (my_point_save[point_id].y - BEGIN_X + DISLEN / 2) / 40;
	int my_x = (my_point[point_id].x - BEGIN_Y + DISLEN / 2) / 40;
	int my_y = (my_point[point_id].y - BEGIN_X + DISLEN / 2) / 40;
	if (my_x < 1) my_x = save_x;
	if (my_y < 1) my_y = save_y;
	if (my_x > PAPER_POINT_HEIGHT) my_x = save_x;
	if (my_y > PAPER_POINT_WIDTH)  my_y = save_y;

	// ���ݴ˴����޵㴦������Ϣ
	if (paper[my_x][my_y] && my_point[paper[my_x][my_y]].move && point_flag[point_id])
	{
		my_point[paper[my_x_flag][my_y_flag]].x = my_point_save[paper[my_x_flag][my_y_flag]].x;
		my_point[paper[my_x_flag][my_y_flag]].y = my_point_save[paper[my_x_flag][my_y_flag]].y;
		my_point[paper[my_x][my_y]].x = my_point_save[point_id].x;
		my_point[paper[my_x][my_y]].y = my_point_save[point_id].y;
		my_x_flag = my_x;
		my_y_flag = my_y;
	}
	else if (point_flag[point_id])
	{
		my_point[paper[my_x_flag][my_y_flag]].x = my_point_save[paper[my_x_flag][my_y_flag]].x;
		my_point[paper[my_x_flag][my_y_flag]].y = my_point_save[paper[my_x_flag][my_y_flag]].y;
		my_x_flag = 0;
		my_y_flag = 0;
	}

	// �����������������Ϣ
	if (msg.uMsg == WM_LBUTTONUP && point_flag[point_id])
	{
		point_flag[point_id] = 0;

		// ���ݴ˴����޵㴦������Ϣ
		if (paper[my_x][my_y])
		{
			if (!my_point[paper[my_x][my_y]].move)
			{
				my_x = save_x;
				my_y = save_y;
			}
			else
			{
				my_point_save[paper[my_x][my_y]].x = my_point_save[point_id].x;
				my_point_save[paper[my_x][my_y]].y = my_point_save[point_id].y;
				my_point[paper[my_x][my_y]].x = my_point_save[point_id].x;
				my_point[paper[my_x][my_y]].y = my_point_save[point_id].y;

				paper[save_x][save_y] = paper[my_x][my_y];
				paper[my_x][my_y] = point_id;
			}
		}
		else
		{
			paper[save_x][save_y] = 0;
			paper[my_x][my_y] = point_id;
		}

		my_point[point_id].x = my_x * 40 + BEGIN_Y;
		my_point[point_id].y = my_y * 40 + BEGIN_X;

		my_point_save[point_id].x = my_point[point_id].x;
		my_point_save[point_id].y = my_point[point_id].y;
	}

	// ������Ҽ����»������ƶ������ƶ��������λ��
	if (msg.x >= my_point[point_id].y - BIG_POINT_R &&
		msg.x <= my_point[point_id].y + BIG_POINT_R &&
		msg.y >= my_point[point_id].x - BIG_POINT_R &&
		msg.y <= my_point[point_id].x + BIG_POINT_R)
	{
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			point_flag[point_id] = 1;
			my_point[point_id].x = msg.y;
			my_point[point_id].y = msg.x;
		}
	}
	else if (point_flag[point_id])
	{
		my_point[point_id].x = msg.y;
		my_point[point_id].y = msg.x;
	}

	// Խ��������
	HWND hwnd = GetHWnd();
	RECT rect; POINT up, dp, mp;
	GetClientRect(hwnd, &rect);
	up.x = rect.left; up.y = rect.top;
	dp.x = rect.right; dp.y = rect.bottom;
	ClientToScreen(hwnd, &up); ClientToScreen(hwnd, &dp);
	rect.left = up.x; rect.top = up.y;
	rect.right = dp.x; rect.bottom = dp.y;
	GetCursorPos(&mp);
	if (!PtInRect(&rect, mp))
	{
		my_point[point_id].x = my_point_save[point_id].x;
		my_point[point_id].y = my_point_save[point_id].y;
		point_flag[point_id] = 0;
	}
}
// �ƶ���



// ���
void CPlay::clear()
{
	for (int i = 0; i < 200; i++)
	{
		my_point[i].move = 0;
		my_point[i].x = 0;
		my_point[i].y = 0;
		my_point_save[i].move = 0;
		my_point_save[i].x = 0;
		my_point_save[i].y = 0;
		my_line[i].a = 0;
		my_line[i].b = 0;
		point_flag[i] = 0;
	}
	my_x_flag = 0;
	my_y_flag = 0;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			paper[i][j] = 0;
	start_time = int(time(NULL));
	times = 0;
}
// ���



// ʤ���ж�
bool CPlay::if_Win()
{
	for (int i = 1; i <= this->point_num; i++)
		if (my_point[i].move)
		{
			if (point_flag[i])
				return 0;

			for (int j = 1; j <= this->line_num; j++)
				for (int k = 1; k <= this->line_num; k++)
				{
					if (j == k)
						continue;

					if (my_line[k].line_Cross(my_line[j]))
						return 0;
				}
		}

	return 1;
}
// ʤ���ж�

//***** ��Ϸ�������Ա����ʵ�� *****//