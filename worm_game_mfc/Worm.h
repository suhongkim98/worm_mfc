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
	void eat(); // ����
	void move(CPoint leftTop, CPoint rightBottom); // �ش� ��ġ�� ���� ��ġ �̵�
	void draw(CDC* dc);
	bool isCollision(CPoint leftTop, CPoint rightBottom); // �ڱ� �ڽŰ� �΋H������ �˻�
};