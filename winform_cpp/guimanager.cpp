#include "guimanager.h"

GuiManager::GuiManager() {
}

GuiManager::~GuiManager() {
	for (size_t i = 0; i < _dialogvec.size(); i++) {
		auto& ptr = _dialogvec[i];
		delete ptr;
		ptr = nullptr;
	}
	_dialogvec.clear();

	for (auto iter = _dialogmap.begin(); iter != _dialogmap.end(); ++iter) {
		auto& ptr = iter->second;
		delete ptr;
		ptr = nullptr;
	}
	_dialogmap.clear();
}

void GuiManager::Run(float step) {
	Draw(step);
}

void GuiManager::Draw(float step) {
	static std::multimap<int32_t, Dialog*> zordermap{};
	zordermap.clear();

	for (auto& e : _dialogvec) {
		zordermap.insert(std::make_pair(e->GetZ(), e));
	}

	for (auto& e : _dialogmap) {
		zordermap.insert(std::make_pair(e.second->GetZ(), e.second));
	}
	for (auto& rect : zordermap) {
		Application::GetSingleton()->DrawRect(
			rect.second->GetX(),
			rect.second->GetY(),
			rect.second->GetW(),
			rect.second->GetH()
		);
	}
}

Dialog * GuiManager::AddDialog(std::string key) {
	Dialog* dialog = new Dialog();
	_dialogmap.insert(std::make_pair(key, dialog));
	return dialog;
}
