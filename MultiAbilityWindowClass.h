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

	HWND DexRadio4;
	HWND DexRadio8;
	HWND DexRadio12;
	HWND DexRadio16;
	HWND DexRadio20;
	HWND DexRadio24;
	HWND DexRadio28;
	HWND DexTotal;

	HWND ConRadio4;
	HWND ConRadio8;
	HWND ConRadio12;
	HWND ConRadio16;
	HWND ConRadio20;
	HWND ConRadio24;
	HWND ConRadio28;
	HWND ConTotal;

	HWND IntRadio4;
	HWND IntRadio8;
	HWND IntRadio12;
	HWND IntRadio16;
	HWND IntRadio20;
	HWND IntRadio24;
	HWND IntRadio28;
	HWND IntTotal;

	HWND WisRadio4;
	HWND WisRadio8;
	HWND WisRadio12;
	HWND WisRadio16;
	HWND WisRadio20;
	HWND WisRadio24;
	HWND WisRadio28;
	HWND WisTotal;

	HWND ChaRadio4;
	HWND ChaRadio8;
	HWND ChaRadio12;
	HWND ChaRadio16;
	HWND ChaRadio20;
	HWND ChaRadio24;
	HWND ChaRadio28;
	HWND ChaTotal;

	HWND CurrentFrame;
	HWND CurrentLabel;
	HWND CurrentStr;
	HWND CurrentStr2;
	HWND CurrentDex;
	HWND CurrentDex2;
	HWND CurrentCon;
	HWND CurrentCon2;
	HWND CurrentInt;
	HWND CurrentInt2;
	HWND CurrentWis;
	HWND CurrentWis2;
	HWND CurrentCha;
	HWND CurrentCha2;
	HWND CurrentValue;
	HWND CurrentMod;

	HWND	TomeFrame;
	HWND	TomeLabel;
	HWND	TomeStr;
	HWND	TomeDex;
	HWND	TomeCon;
	HWND	TomeInt;
	HWND	TomeWis;
	HWND	TomeCha;
	HWND	TomeStr2;
	HWND	TomeDex2;
	HWND	TomeCon2;
	HWND	TomeInt2;
	HWND	TomeWis2;
	HWND	TomeCha2;

	HWND	TomeLabel1;
	HWND	TomeLabel2;
	HWND	TomeLabel3;
	HWND	TomeLabel4;
	HWND	TomeLabel5;
	HWND	TomeLabel6;
	HWND	TomeLabel7;

	int CurrentLevel;

	int RadioButtonID[6][7];

	HPALETTE Palette;
	GraphicStruct Minus;
	GraphicStruct Plus;
	GraphicStruct BlueLevelBox;
	GraphicStruct GreenLevelBox;
	GraphicStruct Spinner;
	GraphicStruct Spinnerwithcover;
	void DrawCreation();
	void DrawLevelUp();
	void LevelUpAbility(int Button);
	void LevelUpAllAbilities(int AbilityIndex);
	void LevelUpClear();
	void ClearRect(HDC hdc, RECT rc);
	void DrawCurrent();
	void DrawLevelBars();
	void DrawTome();
	int TomeLevel[6][7];
	void HandleLeftMouseButtonClick(int x, int y);
	//do not implement these two functions, instance  control!!
	MultiAbilityWindowClass(const MultiAbilityWindowClass &source);
	MultiAbilityWindowClass& operator=(const MultiAbilityWindowClass &source);
	void LoadGraphics(HWND Parent);

};