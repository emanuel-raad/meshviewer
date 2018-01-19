#pragma once
class Mouse
{
private:
	bool buttonState_[3] = { false, false, false };
	bool log_ = false;

	Mouse();

public:
	const static int LEFT = 0;
	const static int RIGHT = 1;
	const static int MIDDLE = 2;


	static Mouse& getInstance();
	void setButtonState(int button, bool state);
	bool getButtonState(int button);
	void setLogging(bool state);

};
