#include "Game_Class.h"



extern MOUSEMSG msg;	// 鼠标消息



//***** 按钮类成员函数实现 *****//

CButton::CButton() {}															// 构造函数
CButton::~CButton() {}															// 构析函数
void CButton::set_X_Y(int x, int y) { this->x = x;	this->y = y; }				// 设置坐标
void CButton::set_Image(IMAGE image) { this->image = image; }					// 设置外表
int CButton::get_X() const { return this->x; }									// 获取X坐标
int CButton::get_Y() const { return this->y; }									// 获取Y坐标
IMAGE CButton::get_Image() const { return this->image; }							// 获取外表
void CButton::draw_Button() const { putimage(this->x, this->y, &this->image); }	// 绘制按钮



// 按钮获焦
bool CButton::if_Mouse_On(MOUSEMSG &m) const
{
	if (m.x > this->x && m.x < this->x + this->image.getwidth() &&
		m.y > this->y && m.y < this->y + this->image.getheight())
		return true;
	return false;
}
// 按钮获焦

//***** 按钮类成员函数实现 *****//
