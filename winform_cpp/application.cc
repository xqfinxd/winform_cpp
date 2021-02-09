#include "application.h"
#include "applicationdata.h"
#include "guimanager.h"

INIT_SINGLETON(Application);

Application::Application() {
	_data = std::make_unique<ApplicationData>();
}

Application::~Application() {

}

void Application::Run() {
	auto guimanager = std::make_unique<GuiManager>();
	_data->running = true;
	int64_t delay = 1000 / _data->framenrate;
	do {
		int64_t begintime = SDL_GetTicks();
		RefreshEvents(true);
		auto eventnums = CollectEvents();
		OnEvent();

		SDL_SetRenderDrawColor(_data->renderer.get(), 255, 255, 255, 255);
		SDL_RenderClear(_data->renderer.get());
		guimanager->Run(delay / 1000.f);
		int64_t endtime = SDL_GetTicks();
		if (endtime - begintime < delay) {
			uint32_t delta = (uint32_t)(delay - (endtime - begintime));
			SDL_Delay(delta);
		}
		SDL_RenderPresent(_data->renderer.get());
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
	if (button == SDL_SCANCODE_O) {
		auto dialog = GuiManager::GetSingleton()->AddDialog("o");
		dialog->SetX(0);
		dialog->SetY(0);
		dialog->SetW(100);
		dialog->SetH(100);
	}
	if (button == SDL_SCANCODE_C) {
		auto dialog = GuiManager::GetSingleton()->AddDialog("c");
		dialog->SetX(200);
		dialog->SetY(200);
		dialog->SetW(100);
		dialog->SetH(100);
	}
}

void Application::DrawRect(int32_t x, int32_t y, uint32_t w, uint32_t h) {
	SDL_Rect rect{ x, y, (int)w, (int)h };
	SDL_SetRenderDrawColor(_data->renderer.get(), 255, 0, 0, 0);
	SDL_RenderDrawRect(_data->renderer.get(), &rect);
}
