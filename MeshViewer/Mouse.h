#pragma once
class Mouse
{
private:
	static Mouse& instance_;
	bool leftButton_;
	bool rightButton_;
	bool middleButton_;

	Mouse();
	~Mouse();
public:
	static Mouse& getInstance();
};