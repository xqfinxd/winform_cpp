#pragma once

#include <cstdint>
#include <string>
#include <type_traits>

//按键名称
extern const std::string keyname[259];
//按键的映射码
extern const uint32_t keycode[259];
//按键的硬件码
extern const uint32_t scancode[259];

//自定义事件类型
enum class EventType : uint32_t {
	UNKNOWN,
	WINDOW,
	KEYUP,
	KEYDOWN,
	MOUSEMOTION,
	MOUSEBUTTONDOWN,
	MOUSEBUTTONUP,
	MOUSEWHEEL,
	QUIT,
	USEREVENT,
};

//将自定义事件类型转为SDL2的事件类型枚举
extern uint32_t EventTypeCast(EventType type);
//将SDL2事件类型枚举转为自定义事件类型
extern EventType EventTypeCast(uint32_t type);

//事件的基类，将SDL_Event由union形式转换为继承形式
struct BaseEvent {
	explicit BaseEvent(EventType e) : type(EventTypeCast(e)) {}
	uint32_t type = 0;
	uint32_t timestamp = 0;
};

//对应SDL_WindowEvent
struct WindowEvent : public BaseEvent {
	WindowEvent() : BaseEvent(EventType::WINDOW) {}
	uint32_t windowID = 0;
	uint8_t event = 0;
	int32_t data1 = 0;
	int32_t data2 = 0;
};

//对应SDL_Keysym
struct KeySym {
	uint32_t scancode = 0;
	uint32_t keycode = 0;
	uint16_t mod = 0;
	uint32_t unused = 0;
};

//对应SDL_RELEASE或SDL_PRESSED
enum class KeyState : uint8_t {
	RELEASE = 0,
	PRESSED = 1,
	NONE = 0xFF,
};

//对应SDL_KeyboardEvent
struct KeyUpEvent : public BaseEvent {
	KeyUpEvent() : BaseEvent(EventType::KEYUP) {}
	uint32_t windowID = 0;
	KeyState state = KeyState::NONE;
	uint8_t repeat = 0;
	uint8_t padding2 = 0;
	uint8_t padding3 = 0;
	KeySym keysym{};
};

//对应SDL_KeyboardEvent
struct KeyDownEvent : public BaseEvent {
	KeyDownEvent() : BaseEvent(EventType::KEYDOWN) {}
	uint32_t windowID = 0;
	KeyState state = KeyState::NONE;
	uint8_t repeat = 0;
	uint8_t padding2 = 0;
	uint8_t padding3 = 0;
	KeySym keysym{};
};

//对应SDL_MouseMotionEvent
struct MouseMotionEvent : public BaseEvent {
	MouseMotionEvent() : BaseEvent(EventType::MOUSEMOTION) {}
	uint32_t windowID = 0;
	uint32_t which = 0;
	uint32_t state = 0;
	int32_t x = 0;
	int32_t y = 0;
	int32_t xrel = 0;
	int32_t yrel = 0;
};

//鼠标按键
enum class MouseButton : uint8_t {
	NONE = 0,
	LEFT = 1,
	MIDDLE = 2,
	RIGHT = 3,
	X1 = 4,
	X2 = 5,
};

//对应SDL_RELEASE或SDL_PRESSED
enum class MouseState : uint8_t {
	RELEASE = 0,
	PRESSED = 1,
	NONE = 0xFF,
};

//对应SDL_MouseButtonEvent
struct MouseButtonDownEvent : public BaseEvent {
	MouseButtonDownEvent() : BaseEvent(EventType::MOUSEBUTTONDOWN) {}
	uint32_t windowID = 0;
	uint32_t which = 0;
	MouseButton button = MouseButton::NONE;
	MouseState state = MouseState::NONE;
	uint8_t clicks = 0;
	uint8_t padding1 = 0;
	int32_t x = 0;
	int32_t y = 0;
};

//对应SDL_MouseButtonEvent
struct MouseButtonUpEvent : public BaseEvent {
	MouseButtonUpEvent() : BaseEvent(EventType::MOUSEBUTTONUP) {}
	uint32_t windowID = 0;
	uint32_t which = 0;
	MouseButton button = MouseButton::NONE;
	MouseState state = MouseState::NONE;
	uint8_t clicks = 0;
	uint8_t padding1 = 0;
	int32_t x = 0;
	int32_t y = 0;
};

//对应SDL_MOUSEWHEEL_NORMAL或SDL_MOUSEWHEEL_FLIPPED 
enum class MouseWheelDirect : uint32_t {
	NORMAL = 0,
	FLIPPED = 1,
};

//对应SDL_MouseWheelEvent
struct MouseWheelEvent : public BaseEvent {
	MouseWheelEvent() : BaseEvent(EventType::MOUSEBUTTONUP) {}
	uint32_t windowID = 0;
	uint32_t which = 0;
	int32_t x = 0;
	int32_t y = 0;
	MouseWheelDirect direction = MouseWheelDirect::NORMAL;
};

//对应SDL_QuitEvent
struct QuitEvent : public BaseEvent {
	QuitEvent() : BaseEvent(EventType::QUIT) {}
};

//对应SDL_UserEvent
struct UserEvent : public BaseEvent {
	UserEvent() : BaseEvent(EventType::USEREVENT) {}
	uint32_t windowID = 0;
	int32_t code = 0;
	void* data1 = nullptr;
	void* data2 = nullptr;
};

//断言：对应的事件结构体应该具有相同的大小
void CheckEventSize();

//extern BaseEvent* EventCast(void* ptr);

//将SDL_Event*转换为对应的事件结构体（ptr为SDL_Event*）
template<typename Event_t>
Event_t* EventCast(void* ptr) {
	if (!std::is_base_of<BaseEvent, Event_t>::value) {
		return nullptr;
	}
	if (ptr == nullptr) {
		return nullptr;
	}
	return reinterpret_cast<Event_t*>(ptr);
}