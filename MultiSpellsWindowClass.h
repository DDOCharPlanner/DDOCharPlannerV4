#pragma once

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIComponentManager.h"
#include "IconClass.h"

class MultiSpellsWindowClass : public IconClass
{
public:

	MultiSpellsWindowClass();
	~MultiSpellsWindowClass();

	void Create(HINSTANCE Instance, HWND Parent);
	void Show(bool State);
	long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	HWND GetHandle();
	HWND MultiSpellsHandle;

private:
	HFONT TitleFontLarge;
	HFONT DefaultFont;
	HWND MultiSpellsLabel;
	HWND CancelButton;
	HWND AcceptButton;
	void DrawGraphics();
	GraphicStruct Test;
	GraphicStruct Test2;
	
	
	//do not implement these two functions, instance  control!!
	MultiSpellsWindowClass(const MultiSpellsWindowClass &source);
	MultiSpellsWindowClass& operator=(const MultiSpellsWindowClass &source);
	void LoadGraphics(HDC hdc);
};