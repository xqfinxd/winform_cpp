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

private:
	Data _data = nullptr;
};