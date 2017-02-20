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

	HWND LevelUpFrame;
	HWND LevelUpLabel;
	HWND LevelLabel;
	HWND TotalLabel;
	HWND LevelUpStr;
	HWND LevelUpStr2;
	HWND LevelUpDex;
	HWND LevelUpDex2;
	HWND LevelUpCon;
	HWND LevelUpCon2;
	HWND LevelUpInt;
	HWND LevelUpInt2;
	HWND LevelUpWis;
	HWND LevelUpWis2;
	HWND LevelUpCha;
	HWND LevelUpCha2;
	HWND Level4;
	HWND Level8;
	HWND Level12;
	HWND Level6;
	HWND Level20;
	HWND Level24;
	HWND Level28;
	HWND StrRadio4;
	HWND StrRadio8;
	HWND StrRadio12;
	HWND StrRadio16;
	HWND StrRadio20;
	HWND StrRadio24;
	HWND StrRadio28;
	HWND StrTotal;




	HPALETTE Palette;
	GraphicStruct Minus;
	GraphicStruct Plus;
	void DrawCreation();
	//do not implement these two functions, instance  control!!
	MultiAbilityWindowClass(const MultiAbilityWindowClass &source);
	MultiAbilityWindowClass& operator=(const MultiAbilityWindowClass &source);
	void LoadGraphics(HWND Parent);

};