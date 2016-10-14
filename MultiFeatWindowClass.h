#pragma once

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIcomponentManager.h"
#include "IconClass.h"


class MultiFeatWindowClass  : public IconClass
{

public:

	MultiFeatWindowClass();
	~MultiFeatWindowClass();

	void Create(HINSTANCE Instance, HWND Parent);
	void Show(bool State);
	long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	long HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	HWND GetHandle();
	HWND MultiFeatHandle;
	void MultiFeatWindowSetLevel(int Level);
	unsigned int LoadIcons(ICONTYPE IconType, string Name);
	void SetIcons(vector <GraphicStruct> MainFeatIcons);

private:
	int CurrentSelectedLevel;
	HFONT TitleFontLarge;
	HFONT DefaultFont;
	HWND MultiFeatLabel;
	HWND CancelButton;
	HWND AcceptButton;
	HWND SelectedPanel;
	HWND SelectedPanelList;
	HWND SelectedPanelLabel;
	HWND FeatListPanel;
	HWND FeatListPanelList;
	HWND FeatListPanelLabel;
	HWND FeatWishPanel;
	HWND FeatWishPanelList;
	HWND FeatWishPanelLabel;
	HWND DescPanel;
	HWND SelectPanel;
	HWND CharClassText;
	//HWND AddButton;
	//HWND RemoveButton;
	void AddFeatWishListItem(int FeatIndex);
	void RemoveFeatWishListItem(int FeatIndex);
	vector <unsigned int> FeatWishList;
	void fillDescPanel(string Desc, HBITMAP Bitmap = NULL);
	void FillSelectedPanel();
	void FillFeatSelectPanel();
	void FillFeatWishPanel();
	void LoadGraphics(HWND Parent);
	FEATSLOTTYPE FeatSlot[3];
	RichEditBitmapClass RichEditBitmap;
	void DrawSelectedFeatBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
	void DrawFeatSelectBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
	void DrawFeatWishBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
	void DrawSelectPanel(HDC hdc);
	void DrawLevelBars(HDC hdc);
	vector <GraphicStruct> FeatIcon;
	vector <ParentHeadingStruct> FeatListParentHeading;
	vector <ParentHeadingStruct> FeatListSelectParentHeading;
	vector <ParentHeadingStruct> FeatWishListParentHeading;
	GraphicStruct PlusBox;
	GraphicStruct MinusBox;
	GraphicStruct BlueLevelBox;
	GraphicStruct GreenLevelBox;
	GraphicStruct RedLevelBox;
	GraphicStruct GreyLevelBox;
	GraphicStruct YellowLevelBox;
	GraphicStruct EmptyFeatSlot;
	void HandleLeftMouseButtonClick(int x, int y);
	void HandleRightMouseButtonClick(int x, int y);
	bool Dragging;
	void EndDragAndDropOperation(int x, int y);
	void SubclassChildWindows();
	void DesubclassChildWindows();
	vector <HWND> SubclassHWNDs;
	vector <WNDPROC> OriginalProcs;
	WNDPROC GetOriginalWinProc(HWND Window);
	int IconDrag;
	HCURSOR Cursor;
	HPALETTE Palette;
	int LevelX[30];
	int LevelY[30];
	int LevelWidth;
	int LevelHeight;
	void DeleteGraphics();
	void SetCharClassText();




	//do not implement these two functions, instance  control!!
	MultiFeatWindowClass(const MultiFeatWindowClass &source);
	MultiFeatWindowClass& operator=(const MultiFeatWindowClass &source);

};

//extern DWORD CALLBACK EditStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb);