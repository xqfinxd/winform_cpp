#pragma once

#include <map>
#include <string>
#include "iapplication.h"
#include "general/singleton.h"

class Application final : public IApplication, public Singleton<Application> {
public:
	Application();
	~Application();
	void OnStart() override;
	void OnEnd() override;

	void* GetWndPtr() {
		return _window;
	}

protected:
	int64_t tick() override;
	uint32_t step() override;
	void delay(uint32_t) override;
	void InputRun(uint32_t step);
private:
	void* _window = nullptr;
};