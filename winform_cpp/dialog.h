#pragma once

#include <cstdint>
#include <memory>

struct DialogData;

class Dialog {
	friend class GuiManager;
public:
	typedef std::shared_ptr<DialogData> Data;

	void Draw(float step);
	void Hide();
	void Show();
	void Close();

	int32_t GetZ() const;
	int32_t GetX() const;
	int32_t GetY() const;
	uint32_t GetW() const;
	uint32_t GetH() const;

	void SetZ(int32_t z);
	void SetX(int32_t x);
	void SetY(int32_t y);
	void SetW(uint32_t w);
	void SetH(uint32_t h);
private:
	Dialog();
	~Dialog();
	Data _data = nullptr;
};
