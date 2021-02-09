#pragma once

#include <cstdint>
#include <memory>

#include "singleton.h"

struct ApplicationData;

class Application : public Singleton<Application> {
public:
	typedef std::unique_ptr<ApplicationData> Data;
	Application();
	~Application();

	void Run();
	void RefreshEvents(bool clear);
	size_t CollectEvents();
	void OnEvent();

	void OnMouse(uint32_t type, uint32_t button, uint8_t clicks);
	void OnKeyboard(uint32_t type, uint32_t button, uint8_t repeat);

	void DrawRect(int32_t x, int32_t y, uint32_t w, uint32_t h);

private:
	Data _data = nullptr;
};