#pragma once

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIcomponentManager.h"
#include "IconClass.h"

class MultiAbilityWindowClass
{
public:

	MultiAbilityWindowClass();
	~MultiAbilityWindowClass();

	void Create(HINSTANCE Instance, HWND Parent);
	void Show(bool State);
	long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	HWND GetHandle();
	HWND MultiAbilityHandle;

private:
	HFONT TitleFontLarge;
	HFONT DefaultFont;
	HWND MultiAbilityLabel;
	HWND CancelButton;
	HWND AcceptButton;


	//do not implement these two functions, instance  control!!
	MultiAbilityWindowClass(const MultiAbilityWindowClass &source);
	MultiAbilityWindowClass& operator=(const MultiAbilityWindowClass &source);

};