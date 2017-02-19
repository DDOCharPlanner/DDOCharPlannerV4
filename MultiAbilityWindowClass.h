#pragma once

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIComponentManager.h"
#include "IconClass.h"

class MultiAbilityWindowClass : public IconClass
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
	HFONT LargeFont;
	HFONT AbilityFontLarge;
	HFONT AbilityFontSmall;
	HFONT ArielFontSmall;

	//HWND MultiAbilityLabel;
	//HWND CancelButton;
	//HWND AcceptButton;

	HWND MultiAbilityText;
	HWND CloseButton;
	HWND CreationFrame;
	HWND	CreationFrameLabel;
	HWND	CreationAvilablePointLabel;
	HWND	CreationAvilablePoint;
	HWND	PointBuild32;
	HWND	BaseValueLabel;
	HWND	ModLabel;
	HWND	CostLabel;
	HWND	CreationStr;
	HWND	CreationDex;
	HWND	CreationCon;
	HWND	CreationInt;
	HWND	CreationWis;
	HWND	CreationCha;
	HWND	CreationStr2;
	HWND	CreationDex2;
	HWND	CreationCon2;
	HWND	CreationInt2;
	HWND	CreationWis2;
	HWND	CreationCha2;
	HPALETTE Palette;
	GraphicStruct Minus;
	GraphicStruct Plus;
	void DrawCreation();
	//do not implement these two functions, instance  control!!
	MultiAbilityWindowClass(const MultiAbilityWindowClass &source);
	MultiAbilityWindowClass& operator=(const MultiAbilityWindowClass &source);
	void LoadGraphics(HWND Parent);

};