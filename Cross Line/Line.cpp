#include "Game_Class.h"



extern CPoint my_point[200];	// 点信息



//***** 线类成员函数实现 *****//

// 构造函数
CLine::CLine(int a, int b)
{
	this->a = a;
	this->b = b;
}
// 构造函数



CLine::~CLine() {}	// 构析函数



// 向量叉乘
double CLine::vector_Mult(int a, int b, int c)
{
	return	(my_point[a].x - my_point[b].x) * (my_point[a].y - my_point[c].y) -
			(my_point[a].y - my_point[b].y) * (my_point[a].x - my_point[c].x);
}
// 向量叉乘



// 判断线段是否交叉
bool CLine::line_Cross(CLine l)
{
	if (vector_Mult(this->a, l.a, this->b) == 0 && vector_Mult(this->a, this->b, l.b) == 0)
	{
		if (max(my_point[this->a].x, my_point[this->b].x) >= max(my_point[l.a].x, my_point[l.b].x) && 
			max(my_point[this->a].y, my_point[this->b].y) >= max(my_point[l.a].y, my_point[l.b].y) &&
			min(my_point[l.a].x, my_point[l.b].x) >= min(my_point[this->a].x, my_point[this->b].x) && 
			min(my_point[l.a].y, my_point[l.b].y) >= min(my_point[this->a].y, my_point[this->b].y))
			return true;
	}
	if (vector_Mult(this->a, l.a, this->b)	* vector_Mult(this->a, this->b, l.b)	<= 0)	return false;
	if (vector_Mult(l.a, this->a, l.b)		* vector_Mult(l.a, l.b, this->b)		<= 0)	return false;
	return true;
}
// 判断线段是否交叉

//***** 线类成员函数实现 *****//