#pragma once

#include <cstdint>
#include <memory>

struct ApplicationData;

class Application {
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

private:
	Data _data = nullptr;
};