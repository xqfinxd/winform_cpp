#include "base.h"

Rect::Rect(Position pos, Size size) : 
	x(pos.x), 
	y(pos.y),
	w(size.w),
	h(size.h) {
}

Rect::Rect(RectX rect) :
	x(rect.left),
	y(rect.top),
	w(rect.right - rect.left),
	h(rect.buttom - rect.top) {
}

RectX::RectX(Rect rect) :
	left(rect.x),
	right(rect.x + rect.w),
	top(rect.y),
	buttom(rect.y + rect.h) {
}
