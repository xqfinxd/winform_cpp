#pragma once

#include <memory>
#include "general/base.h"
#include "general/singleton.h"

class Application;
struct InputData;
#define MAX_KEYCODE_SIZE 14

class Input final {
	friend class Application;
public:
#pragma region Struct Define
	enum class MouseButton : uint8_t {
		LEFT	= 1,
		MIDDLE	= 2,
		RIGHT   = 3,
		X1      = 4,
		X2      = 5,
		NONE	= 0xFF,
	};

	enum class MouseState : uint8_t {
		RELEASE = 0,
		PRESSED = 1,
		NONE	= 0xFF,
	};

	struct {
		Position pos{ 0, 0 };
		MouseButton button = MouseButton::NONE;
		MouseState state = MouseState::NONE;
	} mouse;

	enum class KeyboardState : uint8_t {
		RELEASE = 0,
		PRESSED = 1,
		NONE	= 0xFF,
	};

	struct {
		char key[MAX_KEYCODE_SIZE]{};
		KeyboardState state = KeyboardState::NONE;
		uint8_t repeat = 0;
	} keyboard;
#pragma endregion

#pragma region Event
	bool GetEvent(uint32_t eventid);
	bool GetQuit();
	bool GetMouse(MouseButton mouse, uint8_t clicks);
	bool GetMouseDown();
	bool GetMouseDown(MouseButton mouse);
	bool GetMouseUp();
	bool GetMouseUp(MouseButton mouse);
	bool GetKey(const char* key, uint8_t repeat);
	bool GetKeyDown();
	bool GetKeyDown(const char* key);
	bool GetKeyUp();
	bool GetKeyUp(const char* key);
	bool GetMouseMove();

#pragma endregion

private:
	Input();
	~Input();

	void Run();
	uint32_t Refresh(bool append = false);
	void SyncState();

	std::unique_ptr<InputData> data = nullptr;
};

extern Input* g_input;

inline extern Input* GetInput() {
	return g_input;
}