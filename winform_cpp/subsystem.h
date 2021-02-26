#pragma once

#include <cstdint>

class Subsystem {
public:
	virtual void OnStart() = 0;
	virtual void OnEnd() = 0;
	virtual void Run(uint32_t step) = 0;

	bool enabled = false;
protected:

private:
	
};
