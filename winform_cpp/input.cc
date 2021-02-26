#include "input.h"
#include <vector>
#include <map>
#include <algorithm>
#include "SDL.h"

struct InputData {
	std::vector<SDL_Event> events{};
	std::multimap<uint32_t, const SDL_Event*> eventmap{};
	std::map<uint32_t, std::string> keymap {
		{ SDL_SCANCODE_A, "A" },
		{ SDL_SCANCODE_B, "B" },
		{ SDL_SCANCODE_C, "C" },
		{ SDL_SCANCODE_D, "D" },
		{ SDL_SCANCODE_E, "E" },
		{ SDL_SCANCODE_F, "F" },
		{ SDL_SCANCODE_G, "G" },
		{ SDL_SCANCODE_H, "H" },
		{ SDL_SCANCODE_I, "I" },
		{ SDL_SCANCODE_J, "J" },
		{ SDL_SCANCODE_K, "K" },
		{ SDL_SCANCODE_L, "L" },
		{ SDL_SCANCODE_M, "M" },
		{ SDL_SCANCODE_N, "N" },
		{ SDL_SCANCODE_O, "O" },
		{ SDL_SCANCODE_P, "P" },
		{ SDL_SCANCODE_Q, "Q" },
		{ SDL_SCANCODE_R, "R" },
		{ SDL_SCANCODE_S, "S" },
		{ SDL_SCANCODE_T, "T" },
		{ SDL_SCANCODE_U, "U" },
		{ SDL_SCANCODE_V, "V" },
		{ SDL_SCANCODE_W, "W" },
		{ SDL_SCANCODE_X, "X" },
		{ SDL_SCANCODE_Y, "Y" },
		{ SDL_SCANCODE_Z, "Z" },
		{ SDL_SCANCODE_1, "1" },
		{ SDL_SCANCODE_2, "2" },
		{ SDL_SCANCODE_3, "3" },
		{ SDL_SCANCODE_4, "4" },
		{ SDL_SCANCODE_5, "5" },
		{ SDL_SCANCODE_6, "6" },
		{ SDL_SCANCODE_7, "7" },
		{ SDL_SCANCODE_8, "8" },
		{ SDL_SCANCODE_9, "9" },
		{ SDL_SCANCODE_0, "0" },

		{ SDL_SCANCODE_RETURN, "RETURN" },
		{ SDL_SCANCODE_ESCAPE, "ESCAPE" },
		{ SDL_SCANCODE_BACKSPACE, "BACKSPACE" },
		{ SDL_SCANCODE_TAB, "TAB" },
		{ SDL_SCANCODE_SPACE, "SPACE" },
		{ SDL_SCANCODE_MINUS, "MINUS" },
		{ SDL_SCANCODE_EQUALS, "EQUALS" },
		{ SDL_SCANCODE_LEFTBRACKET, "LEFTBRACKET" },
		{ SDL_SCANCODE_RIGHTBRACKET, "RIGHTBRACKET" },
		{ SDL_SCANCODE_BACKSLASH, "BACKSLASH" },
		{ SDL_SCANCODE_LCTRL , "LCTRL"},
		{ SDL_SCANCODE_LSHIFT, "LSHIFT"},
		{ SDL_SCANCODE_LALT, "LALT"},
		{ SDL_SCANCODE_LGUI, "LGUI"},
		{ SDL_SCANCODE_RCTRL , "RCTRL"},
		{ SDL_SCANCODE_RSHIFT, "RSHIFT"},
		{ SDL_SCANCODE_RALT, "RALT"},
		{ SDL_SCANCODE_RGUI, "RGUI"},
		{ SDL_SCANCODE_CAPSLOCK, "CAPSLOCK"},
		{ SDL_SCANCODE_F1, "F1"},
		{ SDL_SCANCODE_F2, "F2"},
		{ SDL_SCANCODE_F3, "F3"},
		{ SDL_SCANCODE_F4, "F4"},
		{ SDL_SCANCODE_F5, "F5"},
		{ SDL_SCANCODE_F6, "F6"},
		{ SDL_SCANCODE_F7, "F7"},
		{ SDL_SCANCODE_F8, "F8"},
		{ SDL_SCANCODE_F9, "F9"},
		{ SDL_SCANCODE_F10, "F10"},
		{ SDL_SCANCODE_F11, "F11"},
		{ SDL_SCANCODE_F12, "F12"},
		{ SDL_SCANCODE_PRINTSCREEN, "PRINTSCREEN"},
		{ SDL_SCANCODE_SCROLLLOCK, "SCROLLLOCK"},
		{ SDL_SCANCODE_PAUSE, "PAUSE"},
		{ SDL_SCANCODE_INSERT, "INSERT"},
		{ SDL_SCANCODE_HOME, "HOME"},
		{ SDL_SCANCODE_PAGEUP, ""},
		{ SDL_SCANCODE_DELETE, "DELETE"},
		{ SDL_SCANCODE_END, "END"},
		{ SDL_SCANCODE_PAGEDOWN, "PAGEDOWN"},
		{ SDL_SCANCODE_RIGHT, "RIGHT"},
		{ SDL_SCANCODE_LEFT, "LEFT"},
		{ SDL_SCANCODE_DOWN, "DOWN"},
		{ SDL_SCANCODE_UP, "UP"},
		{ SDL_SCANCODE_NUMLOCKCLEAR, "NUMLOCK"},
		{ SDL_SCANCODE_KP_DIVIDE, "DIVIDE"},
		{ SDL_SCANCODE_KP_MULTIPLY, "MULTIPLY"},
		{ SDL_SCANCODE_KP_MINUS, "MINUS"},
		{ SDL_SCANCODE_KP_PLUS, "PLUS"},
		{ SDL_SCANCODE_KP_ENTER, "ENTER"},
		{ SDL_SCANCODE_KP_1, "1"},
		{ SDL_SCANCODE_KP_2, "2"},
		{ SDL_SCANCODE_KP_3, "3"},
		{ SDL_SCANCODE_KP_4, "4"},
		{ SDL_SCANCODE_KP_5, "5"},
		{ SDL_SCANCODE_KP_6, "6"},
		{ SDL_SCANCODE_KP_7, "7"},
		{ SDL_SCANCODE_KP_8, "8"},
		{ SDL_SCANCODE_KP_9, "9"},
		{ SDL_SCANCODE_KP_0, "0"},
		{ SDL_SCANCODE_KP_PERIOD, "PERIOD"},
	};
	
	void reflect() {
		eventmap.clear();
		for (const auto& e : events) {
			eventmap.insert(std::make_pair(e.type, &e));
		}
	}

	bool comparekey(uint32_t scancode, const char* key) {
		static char tempkey[MAX_KEYCODE_SIZE];
		strcpy_s<MAX_KEYCODE_SIZE>(tempkey, key);
		_strupr_s<MAX_KEYCODE_SIZE>(tempkey);
		const char* keycode = keymap[scancode].c_str();
		return strcmp(tempkey, keycode) == 0;
	}
};

Input::Input() {
	data = std::make_unique<InputData>();
}

Input::~Input() {

}

void Input::Run() {
	SDL_PumpEvents();
	Refresh(false);
}

uint32_t Input::Refresh(bool append) {
#define TEMP_EVENT_ARRAY_SIZE 8
	SDL_Event tempEventArray[TEMP_EVENT_ARRAY_SIZE];
	uint32_t totalEventNums = 0;
	if (append) {
		totalEventNums = data->events.size();
	} else {
		data->events.clear();
	}
	do {
		auto eventNums = SDL_PeepEvents(tempEventArray, TEMP_EVENT_ARRAY_SIZE, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
		if (eventNums <= 0) {
			break;
		}
		data->events.resize(totalEventNums + eventNums);
		memcpy(&data->events[totalEventNums], tempEventArray, eventNums * sizeof(SDL_Event));
		totalEventNums += eventNums;
	} while (true);
	data->reflect();
	return totalEventNums;
}

void Input::SyncState() {
	for (const auto& e : data->events) {
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			strcpy_s<MAX_KEYCODE_SIZE>(keyboard.key, data->keymap[e.key.keysym.scancode].c_str());
			keyboard.state = static_cast<KeyboardState>(e.key.state);
			keyboard.repeat = e.key.repeat;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			mouse.button = static_cast<MouseButton>(e.button.button);
			mouse.state = static_cast<MouseState>(e.button.state);
			mouse.pos.x = e.button.x;
			mouse.pos.y = e.button.y;
		}

		if (e.type == SDL_MOUSEMOTION) {
			mouse.button = MouseButton::NONE;
			mouse.state = MouseState::NONE;
			mouse.pos.x = e.motion.x;
			mouse.pos.y = e.motion.y;
		}
	}
}

bool Input::GetEvent(uint32_t eventid) {
	return data->eventmap.find(eventid) != data->eventmap.end();
}

bool Input::GetQuit() {
	return GetEvent(SDL_QUIT);
}

bool Input::GetMouse(MouseButton mouse, uint8_t clicks) {
	for (const auto& e : data->eventmap) {
		if (e.first != SDL_MOUSEBUTTONDOWN 
			&& e.first != SDL_MOUSEBUTTONUP) {
			continue;
		}
		if (Enum2Num(mouse) == e.second->button.button 
			&& e.second->button.clicks == clicks) {
			return true;
		}
	}
	return false;
}

bool Input::GetMouseDown() {
	return GetEvent(SDL_MOUSEBUTTONDOWN);
}

bool Input::GetMouseDown(MouseButton mouse) {
	auto needEvent = SDL_MOUSEBUTTONDOWN;
	auto beg = data->eventmap.lower_bound(needEvent);
	auto end = data->eventmap.upper_bound(needEvent);
	for (auto iter = beg; iter != end; iter++) {
		if (Enum2Num(mouse) == iter->second->button.button) {
			return true;
		}
	}
	return false;
}

bool Input::GetMouseUp() {
	return GetEvent(SDL_MOUSEBUTTONUP);
}

bool Input::GetMouseUp(MouseButton mouse) {
	auto needEvent = SDL_MOUSEBUTTONUP;
	auto beg = data->eventmap.lower_bound(needEvent);
	auto end = data->eventmap.upper_bound(needEvent);
	for (auto iter = beg; iter != end; iter++) {
		if (Enum2Num(mouse) == iter->second->button.button) {
			return true;
		}
	}
	return false;
}

bool Input::GetKey(const char * key, uint8_t repeat) {
	for (const auto& e : data->eventmap) {
		if (e.first != SDL_KEYDOWN
			&& e.first != SDL_KEYUP) {
			continue;
		}
		if (data->comparekey(e.second->key.keysym.scancode, key)
			&& e.second->key.repeat == repeat) {
			return true;
		}
	}
	return false;
}

bool Input::GetKeyDown() {
	return GetEvent(SDL_KEYDOWN);
}

bool Input::GetKeyDown(const char * key) {
	auto needEvent = SDL_KEYDOWN;
	auto beg = data->eventmap.lower_bound(needEvent);
	auto end = data->eventmap.upper_bound(needEvent);
	for (auto iter = beg; iter != end; iter++) {
		if (data->comparekey(iter->second->key.keysym.scancode, key)) {
			return true;
		}
	}
	return false;
}

bool Input::GetKeyUp() {
	return GetEvent(SDL_KEYUP);
}

bool Input::GetKeyUp(const char * key) {
	auto needEvent = SDL_KEYUP;
	auto beg = data->eventmap.lower_bound(needEvent);
	auto end = data->eventmap.upper_bound(needEvent);
	for (auto iter = beg; iter != end; iter++) {
		if (data->comparekey(iter->second->key.keysym.scancode, key)) {
			return true;
		}
	}
	return false;
}

bool Input::GetMouseMove() {
	return GetEvent(SDL_MOUSEMOTION);
}
