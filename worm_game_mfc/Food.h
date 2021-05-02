#pragma once
#include <math.h>
#include <time.h>
#include "Map.h"
class Food
{
private:
	Map* map;
public:
	CPoint leftTop;
	CPoint rightBottom;
	void draw(CDC* dc);
	Food(Map* map);
	void randomCreate();
	bool isCollision(CPoint leftTop, CPoint rightBottom);
};

