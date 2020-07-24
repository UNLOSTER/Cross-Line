#include "Game_Class.h"



int pasin;									// 当前关卡
MOUSEMSG msg;								// 鼠标消息
wchar_t best_time[100];						// 最佳时间
CPoint my_point[200], my_point_save[200];	// 点信息、点信息保存
CLine my_line[50000];						// 线信息
int my_x_flag, my_y_flag, paper[20][20];	// 纸盘信息
bool point_flag[200];						// 移动标记
int pass_num;								// 关卡数
long long times, start_time;				// 计时器



int main()
{
	srand((unsigned int)time(NULL));

	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkmode(TRANSPARENT);
	BeginBatchDraw();

	CGame *inter = new CBegin();
	inter->inter_Face_Running();	//开始游戏
	delete inter;

	EndBatchDraw();
	closegraph();

	return 0;
}