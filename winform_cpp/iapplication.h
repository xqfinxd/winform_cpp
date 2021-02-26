#pragma once

#include <cstdint>
#include <functional>
#include <vector>

class IApplication {
public:
	void Run() {
		OnStart();
		while (_running) {
			auto begin = tick();
			Loop(step());
			auto end = tick();
			int64_t delta = end - begin;
			if (delta < (int64_t)step()) {
				delay((uint32_t)(step() - delta));
			}
		}
		OnEnd();
	}

	void Exit() {
		_running = false;
	}

	virtual void OnStart() = 0;

	virtual void OnEnd() = 0;

	struct {
		typedef std::function<void(uint32_t)> Delegate;
		void operator()(uint32_t delta) {
			for (auto& d : _delegate) {
				d(delta);
			}
		}

		void reset() {
			_delegate.clear();
		}

		void push(Delegate d) {
			_delegate.push_back(d);
		}

	private:
		std::vector<Delegate> _delegate{};
	} Loop;

protected:
	virtual int64_t tick() = 0;
	virtual uint32_t step() = 0;
	virtual void delay(uint32_t) = 0;
private:
	bool _running = true;
};