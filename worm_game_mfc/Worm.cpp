#include "pch.h"
#include "Worm.h"
Worm::Worm(CPoint leftTop, CPoint rightBottom) {
	//벌레의 시작 위치
	food = false;
	WormBody body(leftTop, rightBottom);
	worm.AddHead(body);
}
WormBody Worm::getHead() {
	return worm.GetHead();
}

void Worm::eat() { // 성장
	// 먹은 상태라면 flag true, true인 경우 move 호출 시 꼬리를 이동시키지 않고 head에 추가
	food = true;
}
void Worm::move(CPoint leftTop, CPoint rightBottom) {
	if (food) {
		// 새로운 위치에 body 추가
		food = false;

		WormBody body(leftTop, rightBottom);
		worm.AddHead(body);
	}
	else {
		// 해당 위치로 꼬리 위치 이동
		WormBody body = worm.GetTail();
		body.leftTop = leftTop;
		body.rightBottom = rightBottom;
		worm.RemoveTail();
		worm.AddHead(body);
	}
}


void Worm::draw(CDC* dc) {

	POSITION pos = worm.GetHeadPosition(); // 시작 위치
	int color = 0;
	while (pos != NULL) {
		WormBody body = worm.GetNext(pos);
		CBrush brush(RGB(0, color, 0));
		dc->SelectObject(brush);
		dc->Rectangle(body.leftTop.x, body.leftTop.y, body.rightBottom.x, body.rightBottom.y);

		if (color + 20 <= 255) {
			color += 20;
		}
	}
}

bool Worm::isCollision(CPoint leftTop, CPoint rightBottom) {
	// head 제외하고 몸이랑 충돌여부 검사

	POSITION pos = worm.GetHeadPosition(); // 시작 위치

	worm.GetNext(pos); // head는 통과
	while (pos != NULL) {
		WormBody body = worm.GetNext(pos);
		if (body.leftTop == leftTop && body.rightBottom == rightBottom) {
			// 몸이랑 충돌했을 경우
			return true;
		}
	}
	return false;
}