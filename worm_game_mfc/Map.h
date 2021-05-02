#pragma once
#include "Block.h"
class Map
{
public:
	const static int BLOCK_WIDTH = 20;
	int xBlockCount, yBlockCount;
	Map(int xBlockCount, int yBlockCount);
	void drawMap(CDC* dc);
	bool isCollision(CPoint leftTop, CPoint rightBottom);
	Block getCenterBlock();
};
