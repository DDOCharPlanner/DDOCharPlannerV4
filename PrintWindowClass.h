#pragma once

#include "stdafx.h"
#include "PrintClass.h"

//---------------------------------------------------------------------------
class PrintWindowClass
	{
	public:
		PrintWindowClass();
		virtual ~PrintWindowClass();

        void Create(HINSTANCE Instance, HWND Parent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		HWND GetHandle();
		HWND PrintWindowHandle;
    private:

		HWND PrintLabel;
        HWND PrintButton;
        HWND CancelButton;
		HWND PrintSnapshotCheckBox;
		HWND SnapshotLevelSelectLabel;
		HWND SnapshotMaxLevelRadio;
		HWND SnapshotOtherLevelRadio;
		HWND SnapshotOtherLevelInputBox;

		HWND PrintLevelGuideCheckBox;
		HWND LevelGuideLevelSelectLowLabel;
		HWND LevelGuideLevelSelectHighLabel;
		HWND LevelGuideDefaultRadio;
		HWND LevelGuideOtherRadio;
		HWND LevelGuideOtherLevelLowInputBox;
		HWND LevelGuideOtherLevelHighInputBox;

        HFONT TitleFontLarge;

		PrintClass Printer;

        //do not implement these two functions, instance  control!!
        PrintWindowClass(const PrintWindowClass &source);
        PrintWindowClass& operator=(const PrintWindowClass &source);

		void Print();
	};

