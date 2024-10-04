#include "WindowsKeyInput.h"

bool WindowsKeyInput::isButtonDown(int keycode)
{
	return GetAsyncKeyState(keycode) & 0x0001;
}

bool WindowsKeyInput::isButtonPressed(int keycode)
{
	SHORT state = GetAsyncKeyState(keycode);
	return (state & 0x8000) || (state & 0x0001);
}
