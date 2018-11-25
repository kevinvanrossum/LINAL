#include "pch.h"
#include "fps.h"


fps::fps()
= default;

void fps::update()
{
	if (clock_.getElapsedTime().asSeconds() >= 1.f)
	{
		fps_ = frame_;
		frame_ = 0;
		clock_.restart();
	}
	++frame_;
}

unsigned fps::get_fps() const
{
	return fps_;
}


fps::~fps()
= default;
