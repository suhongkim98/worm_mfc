#include "pch.h"
#include "Map.h"

Map::Map(int xBlockCount, int yBlockCount) {
	this->xBlockCount = xBlockCount;
	this->yBlockCount = yBlockCount;
}

Block Map::getCenterBlock() {
	int x = (xBlockCount / 2) * BLOCK_WIDTH;
	int y = (yBlockCount / 2) * BLOCK_WIDTH;

	CPoint leftTop(x, y);
	CPoint rightBottom(x + BLOCK_WIDTH, y + BLOCK_WIDTH);

	Block block(leftTop, rightBottom);
	return block;
}

void Map::drawMap(CDC* dc) {
	CBrush marginBrush(RGB(255,0,0));
	dc->SelectObject(marginBrush);
	dc->Rectangle(0, 0, (xBlockCount + 2) * BLOCK_WIDTH, (yBlockCount + 2) * BLOCK_WIDTH); // 바깥

	CBrush mainBrush(RGB(255, 255, 255));
	dc->SelectObject(mainBrush);
	dc->Rectangle(BLOCK_WIDTH, BLOCK_WIDTH, (xBlockCount + 1) * BLOCK_WIDTH, (yBlockCount + 1) * BLOCK_WIDTH);
}

bool Map::isCollision(CPoint leftTop, CPoint rightBottom) { // 위치를 받아서 충돌여부 검사
	const int xMin = 0;
	const int xMax = (xBlockCount + 2) * BLOCK_WIDTH;
	const int yMin = 0;
	const int yMax = (yBlockCount + 2) * BLOCK_WIDTH;

	if (leftTop.x <= xMin) return true;
	if (leftTop.y <= yMin) return true;
	if (rightBottom.x >= xMax) return true;
	if (rightBottom.y >= yMax) return true;

	return false;
}

