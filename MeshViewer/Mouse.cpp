#include "Mouse.h"


Mouse::Mouse()
{
	leftButton_ = false;
	rightButton_ = false;
	middleButton_ = false;
}

Mouse & Mouse::getInstance()
{
	if (instance_ == 0)
		static Mouse instance_;
	return instance_;
}


Mouse::~Mouse()
{
}