#include <iostream>
#include "application.h"

extern void CheckEventSize();

#undef main

int main(int* argc, char*argv[])
{
	CheckEventSize();
	Application app{};
	app.Run();
	return 0;
}
