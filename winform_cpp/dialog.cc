#include "dialog.h"
#include "dialogdata.h"

Dialog::Dialog() {
	_data = Data(new DialogData());
}

Dialog::~Dialog() {
	_data.reset();
}

void Dialog::Draw(float step) {
}

void Dialog::Hide() {
	_data->ishide = true;
}

void Dialog::Show() {
	_data->ishide = false;
	_data->isclose = false;
}

void Dialog::Close() {
	_data->isclose = true;
}

int32_t Dialog::GetZ() const {
	return _data->zorder;
}

int32_t Dialog::GetX() const {
	return _data->x;
}

int32_t Dialog::GetY() const {
	return _data->y;
}

uint32_t Dialog::GetW() const {
	return _data->w;
}

uint32_t Dialog::GetH() const {
	return _data->h;
}

void Dialog::SetZ(int32_t z) {
	_data->zorder = z;
}

void Dialog::SetX(int32_t x) {
	_data->x = x;
}

void Dialog::SetY(int32_t y) {
	_data->y = y;
}

void Dialog::SetW(uint32_t w) {
	_data->w = w;
}

void Dialog::SetH(uint32_t h) {
	_data->h = h;
}
