#include "Mouse.h"


Mouse::Mouse()
{
}

Mouse & Mouse::getInstance()
{
	static Mouse instance_;
	return instance_;
}

void Mouse::setButtonState(int button, bool state)
{
	buttonState_[button] = state;
}

bool Mouse::getButtonState(int button)
{
	return buttonState_[button];
}