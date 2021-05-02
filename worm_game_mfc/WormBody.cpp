#include "pch.h"
#include "WormBody.h"



WormBody::WormBody(CPoint leftTop, CPoint rightBottom) {
	this->leftTop = leftTop;
	this->rightBottom = rightBottom;
}
WormBody::WormBody() {
	this->leftTop = CPoint(0, 0);
	this->rightBottom = CPoint(0, 0);
}