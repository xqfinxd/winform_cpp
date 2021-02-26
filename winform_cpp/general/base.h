#pragma once

#include <cstdint>
#include <type_traits>

struct Size;
struct Position;
struct Rect;
struct RectX;
struct Color;

template<class Enum>
auto Enum2Num(Enum e) -> typename std::underlying_type_t<Enum> {
	return static_cast<typename std::underlying_type_t<Enum>>(e);
}

struct Size {
	uint32_t w = 0, h = 0;
};

struct Position {
	int32_t x = 0, y = 0;
};

struct Rect {
	int32_t x = 0, y = 0;
	uint32_t w = 0, h = 0;
	Rect(Position pos, Size size);
	Rect(RectX rect);
};

struct RectX {
	int32_t left = 0;
	int32_t right = 0;
	int32_t top = 0;
	int32_t buttom = 0;
	RectX(Rect rect);
};

struct Color {
	uint8_t r = 0, g = 0, b = 0, a = 0;
};
