#include "application.h"
#include "applicationdata.h"


Application::Application() {
	_data = std::make_unique<ApplicationData>();
}

Application::~Application() {

}

void Application::Run() {
	_data->running = true;
	do {
		RefreshEvents(true);
		auto eventnums = CollectEvents();
		OnEvent();
		
	} while (_data->running);
}

void Application::RefreshEvents(bool clear) {
	SDL_PumpEvents();
	if (clear) {
		_data->events.clear();
	}
}

size_t Application::CollectEvents() {
#define TEMP_EVENT_NUM 16
	static SDL_Event tempEvents[TEMP_EVENT_NUM];
	size_t totaleventnums = 0;
	do {
		int eventnums = SDL_PeepEvents(tempEvents, TEMP_EVENT_NUM, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
		if (eventnums <= 0) {
			break;
		}
		for (size_t i = 0; i < (size_t)eventnums; i++) {
			_data->events.push_back(tempEvents[i]);
		}
		totaleventnums += eventnums;
	} while (true);
	return totaleventnums;
}

void Application::OnEvent() {
	for (const auto& e : _data->events) {
		if (e.type == SDL_QUIT) {
			_data->running = false;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			_data->mouse.x = e.button.x;
			_data->mouse.y = e.button.y;
			_data->mouse.state = e.button.state;
			_data->mouse.clicks = e.button.clicks;
			_data->mouse.button = e.button.button;
			OnMouse(e.type, e.button.button, e.button.clicks);
		}
		else if (e.type == SDL_MOUSEMOTION) {
			_data->mouse.x = e.motion.x;
			_data->mouse.y = e.motion.y;
			_data->mouse.state = e.motion.state;
		}

		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			OnKeyboard(e.type, e.key.keysym.scancode, e.key.repeat);
		}
	}
}

void Application::OnMouse(uint32_t type, uint32_t button, uint8_t clicks) {
	printf("mouse click %d %d\n", button, clicks);
}

void Application::OnKeyboard(uint32_t type, uint32_t button, uint8_t repeat) {
	printf("keyboard click %d %d\n", button, repeat);
}
