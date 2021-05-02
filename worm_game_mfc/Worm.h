#pragma once
#include "WormBody.h"
class Worm
{
private:
	CList<WormBody> worm;
	bool food;
public:
	Worm(CPoint leftTop, CPoint rightBottom);
	WormBody getHead();
	void eat(); // 성장
	void move(CPoint leftTop, CPoint rightBottom); // 해당 위치로 꼬리 위치 이동
	void draw(CDC* dc);
	bool isCollision(CPoint leftTop, CPoint rightBottom); // 자기 자신과 부딫혔는지 검사
};