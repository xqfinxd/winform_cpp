#pragma once

#include <map>
#include <vector>
#include "singleton.h"
#include "dialog.h"
#include "application.h"

class GuiManager : public Singleton<GuiManager> {
public:
	GuiManager();

	~GuiManager();

	void Run(float step);

	void Draw(float step);

	Dialog* AddDialog(std::string key);
	
private:
	typedef std::vector<Dialog*> DialogVec;
	typedef std::map<std::string, Dialog*> DialogMap;
	DialogVec _dialogvec{};
	DialogMap _dialogmap{};
};

INIT_SINGLETON(GuiManager);