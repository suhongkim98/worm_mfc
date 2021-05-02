#pragma once
#include "Worm.h"
#include "Map.h"
#include "Food.h"
class GameManager
{
private:
	void initValue();
public:
	Map* map;
	Worm* playerWorm;
	Food* food;
	CPoint* dir;
	bool isGameStart;
	bool dead;
	GameManager();
	void initGame();
};

