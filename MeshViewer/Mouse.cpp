#include "Mouse.h"

#include <iostream>

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
	if (log_)
		std::cout << "Button: " << button << " State: " << state << std::endl;
}

bool Mouse::getButtonState(int button)
{
	return buttonState_[button];
}

void Mouse::setLogging(bool state)
{
	log_ = state;
}
