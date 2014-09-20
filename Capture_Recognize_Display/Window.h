#pragma once

//Our window
class Window
{
private:
	//Whether the window is windowed or not
	bool windowed;

	//Whether the window is fine
	bool windowOK;

public:
	//Constructor
	Window();

	//Handle window events
	void handle_events();

	//Turn fullscreen on/off
	void toggle_fullscreen();

	//Check if anything's wrong with the window
	bool error();
};