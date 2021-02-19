#pragma once

#include <cstdint>

struct Size {
	uint32_t w = 0, h = 0;
};

struct Position {
	int32_t x = 0, y = 0;
};

struct Rect {
	int32_t x = 0, y = 0;
	uint32_t w = 0, h = 0;
};

struct RectX {
	int32_t left = 0;
	int32_t right = 0;
	int32_t top = 0;
	int32_t buttom = 0;
};

struct Color {
	uint8_t r = 0, g = 0, b = 0, a = 0;
};

struct MouseState {
	Position pos{};
	uint8_t state = 0;
	uint8_t button = 0;
};