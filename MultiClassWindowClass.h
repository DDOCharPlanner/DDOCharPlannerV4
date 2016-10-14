#pragma once

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIComponentManager.h"
#include "IconClass.h"

class MultiClassWindowClass : public IconClass
{
public:

	MultiClassWindowClass();
	~MultiClassWindowClass();

	void Create(HINSTANCE Instance, HWND Parent);
	void Show(bool State);
	long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	long HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	HWND GetHandle();
	HWND MultiClassHandle;

private:
	HFONT TitleFontLarge;
	HFONT DefaultFont;
	HWND MultiClassText;
	HWND Close;
	HWND ClassString;
	HWND DescriptionWindow;
	HWND ClassListFrame;
	HWND SelectionFrame;
	HWND LevelLabel;
	HWND ClassLabel;
	HWND ClassLevelLabel;
	HWND BABLabel;
	HPALETTE Palette;
	RichEditBitmapClass RichEditBitmap;
	bool AlignmentValid[NUMCLASSES];
	void HandleLeftMouseButtonClick(int x, int y);
	void HandleRightMouseButtonClick(int x, int y);
	void LoadGraphics(HWND Parent);
	GraphicStruct ClassIcon[NUMCLASSES];
	GraphicStruct emptyclass;
	GraphicStruct UnclaimedClassSlot;
	CLASS ClassSlot[NUMCLASSES];
	void SetCharClassText();
	void FillClassList();
	void FillSelectList();
	CLASS ClassAtLevel[20];
	CLASS SelectedClassIcons[3];
	void FillDesc(string Description, HBITMAP Bitmap);
	HCURSOR Cursor;
	bool Dragging;
	int DragIcon;

	void ClearSelectionFrame(HDC hdc);
	void EndDragAndDropOperation(int x, int y);
	void DeleteGraphics();

	//do not implement these two functions, instance  control!!
	MultiClassWindowClass(const MultiClassWindowClass &source);
	MultiClassWindowClass& operator=(const MultiClassWindowClass &source);

};