#include "pch.h"
#include "GameManager.h"

GameManager::GameManager() {
	initValue();
}

void GameManager::initValue() {
	isGameStart = false;
	dead = false;
	dir = NULL;
	playerWorm = NULL;
	food = NULL;
	map = NULL;

}
void GameManager::initGame() {
	initValue();

	map = new Map(30, 30);
	Block centerBlock = map->getCenterBlock();

	food = new Food(map);
	food->randomCreate(); // ���� ����

	playerWorm = new Worm(centerBlock.leftTop, centerBlock.rightBottom); // ���� ���� ��ġ
}