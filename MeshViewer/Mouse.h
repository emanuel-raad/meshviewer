#pragma once
class Mouse
{
private:
	bool buttonState_[3] = { false, false, false };

	Mouse();

public:
	const static int MIDDLE = 0;
	const static int LEFT = 1;
	const static int RIGHT = 2;

	static Mouse& getInstance();
	void setButtonState(int button, bool state);
	bool getButtonState(int button);

};
