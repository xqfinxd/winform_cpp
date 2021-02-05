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
		for (const auto& e : _data->events) {
			if (e.type == SDL_QUIT) {
				_data->running = false;
			}

			
		}
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
		for (size_t i = 0; i < eventnums; i++) {
			_data->events.push_back(tempEvents[i]);
		}
		totaleventnums += eventnums;
	} while (true);
	return totaleventnums;
}
