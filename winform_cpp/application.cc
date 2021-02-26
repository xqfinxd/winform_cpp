#include <cassert>
#include "application.h"
#include "SDL.h"
#include "input.h"
#include "general/event_type.h"

INIT_SINGLETON(Application);
extern Input* g_input = nullptr;

Application::Application() {
}

Application::~Application() {
}

void Application::OnStart() {
	_window = SDL_CreateWindow("winform_cpp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 678, SDL_WINDOW_SHOWN);
	g_input = new Input();
	Loop.push([this](uint32_t step) {
		this->InputRun(step);
	});
	Loop.push([this](uint32_t) {
		if (GetInput()->GetQuit()) {
			this->Exit();
		}

		if (GetInput()->GetKeyDown("space")) {
			printf("%d", sizeof(SDL_MouseMotionEvent));
		}
	});
}

void Application::OnEnd() {
	delete g_input;
	g_input = nullptr;
	SDL_DestroyWindow((SDL_Window*)_window);
}

int64_t Application::tick() {
	return SDL_GetTicks();
}

uint32_t Application::step() {
	return 1000 / 60;
}

void Application::delay(uint32_t d) {
	SDL_Delay(d);
}

void Application::InputRun(uint32_t step) {
	GetInput()->Run();
}
