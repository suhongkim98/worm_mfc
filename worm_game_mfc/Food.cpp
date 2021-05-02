#include "pch.h"
#include "Food.h"

Food::Food(Map* map) {
	this->map = map;
}

void Food::draw(CDC* dc) {
	CBrush brush(RGB(0, 0, 255));
	dc->SelectObject(brush);
	dc->Ellipse(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);
}

void Food::randomCreate() {
	int x = (rand() % (map->xBlockCount * map->BLOCK_WIDTH - map->BLOCK_WIDTH)) + map->BLOCK_WIDTH;
	int y = (rand() % (map->yBlockCount * map->BLOCK_WIDTH - map->BLOCK_WIDTH)) + map->BLOCK_WIDTH;

	x -= x % map->BLOCK_WIDTH; // �� ����� �°� �������� ������
	y -= y % map->BLOCK_WIDTH;

	this->leftTop = CPoint(x, y);
	this->rightBottom = CPoint(x + map->BLOCK_WIDTH, y + map->BLOCK_WIDTH);
}


bool Food::isCollision(CPoint leftTop, CPoint rightBottom) {
	// ���İ� �浹�ߴ��� ����
	if (this->leftTop == leftTop && this->rightBottom == rightBottom)
		return true;
	return false;
}