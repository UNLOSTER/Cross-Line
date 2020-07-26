#pragma once



#include "Head.h"



//***** 类 *****//

// 游戏总类
class CGame
{
public:
	CGame();								// 构造函数
	~CGame();								// 构析函数

	virtual void inter_Face_Running() = 0;	// 界面接口
	
protected:
	void clear_Board();						// 绘制背景
};
// 游戏总类



// 初始界面类
class CBegin : public CGame
{
public:
	CBegin();					// 构造函数
	~CBegin();					// 构析函数

	void inter_Face_Running();	// 初始界面

private:
	void draw_Title();			// 绘制标题
};
// 初始界面类



// 关于界面类
class CAbout : public CGame
{
public:
	CAbout();					// 构造函数
	~CAbout();					// 构析函数

	void inter_Face_Running();	// 关于界面

private:
	void draw_Text();			// 输出文字
};
// 关于界面类



// 关卡界面类
class CLevel : public CGame
{
public:
	CLevel();					// 构造函数
	~CLevel();					// 构析函数

	void inter_Face_Running();	// 关卡界面

private:
	int stat();					// 统计关卡
};
// 关卡界面类



// 游戏界面类
class CPlay : public CGame
{
public:
	CPlay();						// 构造函数
	~CPlay();						// 构析函数

	void inter_Face_Running();		// 游戏界面
	void read_Level();				// 读取关卡
	void draw_Title();				// 绘制标题
	void draw_Paper();				// 绘制纸盘
	void draw_Graph();				// 绘制图
	void point_Move(int point_id);	// 移动点
	void clear();					// 清空
	bool if_Win();					// 胜利判定
	
	static int point_num, line_num;	// 点数、线数
};
// 游戏界面类



// 过关界面类
class CWin : public CGame
{
public:
	CWin();						// 构造函数
	~CWin();					// 构析函数

	void inter_Face_Running();	// 过关界面

private:
	void change_Best_Time();	// 修改最佳时间
	void draw_Title();			// 绘制标题
};
// 过关界面类



// 点类
class CPoint
{
public:
	CPoint( int x = 0, int y = 0, 
			bool move = 1, bool moving = 0);	// 构造函数
	~CPoint();									// 构析函数

	int x, y;									// 坐标
	bool move;									// 是否可移动、是否正在移动
};
// 点类



// 线类
class CLine
{
public:
	CLine(int a = 0, int b = 0);				// 构造函数
	~CLine();									// 构析函数

	double vector_Mult(int a, int b, int c);	// 向量叉乘
	bool line_Cross(CLine l);					// 判断线段是否交叉

	int a, b;									// 编号
};
// 线类



// 按钮类
class CButton
{
public:
	CButton();								// 构造函数
	~CButton();								// 构析函数

	void set_X_Y(int x, int y);				// 设置坐标
	void set_Image(IMAGE image);			// 设置外表
	int get_X() const; int get_Y() const;	// 获取坐标
	IMAGE get_Image() const;				// 获取外表
	void draw_Button() const;				// 绘制按钮
	bool if_Mouse_On(MOUSEMSG &m) const;	// 按钮获焦

private:
	int x, y;								// 按钮坐标
	IMAGE image;							// 按钮外表
};
// 按钮类



// 按钮图形类
class CButton_Image
{
public:
	CButton_Image();																// 构造函数
	~CButton_Image();																// 构析函数

	IMAGE start_Button(COLORREF color);												// 开始按钮图形
	IMAGE help_Button(COLORREF color);												// 帮助按钮图形
	IMAGE close_Button(COLORREF color);												// 关闭按钮图形
	IMAGE level_Button(const wchar_t num[], const wchar_t tim[], COLORREF color);	// 关卡按钮图形
	IMAGE return_Button(COLORREF color);											// 返回按钮图形
	IMAGE again_Button(COLORREF color);												// 重来按钮图形
	IMAGE next_Button(COLORREF color);												// 下一关按钮图形
	IMAGE ok_Button(COLORREF color);												// O K 按钮图形
};
// 按钮图形类

//***** 类 *****//