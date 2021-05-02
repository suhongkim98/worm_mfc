#include "pch.h"
#include "Worm.h"
Worm::Worm(CPoint leftTop, CPoint rightBottom) {
	//������ ���� ��ġ
	food = false;
	WormBody body(leftTop, rightBottom);
	worm.AddHead(body);
}
WormBody Worm::getHead() {
	return worm.GetHead();
}

void Worm::eat() { // ����
	// ���� ���¶�� flag true, true�� ��� move ȣ�� �� ������ �̵���Ű�� �ʰ� head�� �߰�
	food = true;
}
void Worm::move(CPoint leftTop, CPoint rightBottom) {
	if (food) {
		// ���ο� ��ġ�� body �߰�
		food = false;

		WormBody body(leftTop, rightBottom);
		worm.AddHead(body);
	}
	else {
		// �ش� ��ġ�� ���� ��ġ �̵�
		WormBody body = worm.GetTail();
		body.leftTop = leftTop;
		body.rightBottom = rightBottom;
		worm.RemoveTail();
		worm.AddHead(body);
	}
}


void Worm::draw(CDC* dc) {

	POSITION pos = worm.GetHeadPosition(); // ���� ��ġ
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
	// head �����ϰ� ���̶� �浹���� �˻�

	POSITION pos = worm.GetHeadPosition(); // ���� ��ġ

	worm.GetNext(pos); // head�� ���
	while (pos != NULL) {
		WormBody body = worm.GetNext(pos);
		if (body.leftTop == leftTop && body.rightBottom == rightBottom) {
			// ���̶� �浹���� ���
			return true;
		}
	}
	return false;
}