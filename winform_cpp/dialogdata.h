#pragma once

#include <cstdint>

struct DialogData {
	int32_t x = 0, y = 0;
	uint32_t w = 0, h = 0;
	int32_t zorder = 0;
	bool ishide = false;
	bool isclose = false;
	bool isdeleting = false;
	bool isdeleted = false;
};