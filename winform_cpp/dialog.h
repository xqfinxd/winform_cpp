#pragma once

#include <cstdint>
#include <memory>

struct DialogData;

class Dialog : std::enable_shared_from_this<Dialog> {
public:
	typedef std::unique_ptr<DialogData> Data;

	void Draw(float step);
	void Hide();
	void Show();
	void Close();
private:
	Data _data = nullptr;
};