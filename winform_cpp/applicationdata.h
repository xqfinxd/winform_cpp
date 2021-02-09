#pragma once

#include <memory>
#include <functional>
#include <vector>
#include "SDL.h"

struct ApplicationData {
	typedef std::function<void(SDL_Window*)> WindowDeleter;
	typedef std::function<void(SDL_Renderer*)> RendererDeleter;
	typedef std::unique_ptr<SDL_Window, WindowDeleter> Window;
	typedef std::unique_ptr<SDL_Renderer, RendererDeleter> Renderer;
	typedef std::vector<SDL_Event> EventQueue;
	Window window = nullptr;
	Renderer renderer = nullptr;
	EventQueue events{};
	bool running = false;
	uint32_t framenrate = 60;
	struct {
		int x = 0, y = 0;
		uint8_t clicks = 0;
		uint8_t state = 0;
		uint8_t button = 0;
	} mouse;

	ApplicationData() {
		WindowDeleter windowdeleter = [](SDL_Window* win) { SDL_DestroyWindow(win); };
		window = Window(SDL_CreateWindow("winform_cpp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN), windowdeleter);

		RendererDeleter rendererdeleter = [](SDL_Renderer* ren) { SDL_DestroyRenderer(ren); };
		renderer = Renderer(SDL_CreateRenderer(window.get(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED), rendererdeleter);
	}

	~ApplicationData() {
		events.clear();
	}
};