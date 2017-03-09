#include "MultiFeatWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "DataClass.h"
#include "MainScreenClass.h"


//---------------------------------------------------------------------------
MultiFeatWindowClass::MultiFeatWindowClass()
{
	Dragging = false;
}
//---------------------------------------------------------------------------
MultiFeatWindowClass::~MultiFeatWindowClass()
{
		DeleteGraphics();
}
//---------------------------------------------------------------------------
void MultiFeatWindowClass::Create(HINSTANCE Instance, HWND Parent)
{
	WNDCLASSEX wc;
	int ParentX;
	int ParentY;
	RECT ParentRect;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Feat Window";
	LOGBRUSH lb;
	LOGFONT lf;


	//fill in the class attributes for the main window
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 4;
	wc.cbWndExtra = 0;
	wc.hInstance = Instance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register
	RegisterClassEx(&wc);

	//create and center the window on screen
	MultiFeatHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1000, 720, Parent, NULL, Instance, NULL);
	SetClassLong(MultiFeatHandle, 0, (long)MULTIFEATWINDOW);
	//ScreenX = GetSystemMetrics(SM_CXSCREEN);
	//ScreenY = GetSystemMetrics(SM_CYSCREEN);
	int TopBar = 25;
	GetWindowRect(Parent, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top-TopBar;

	GetWindowRect(MultiFeatHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiFeatHandle, Parent, ParentRect.left +(ParentX / 2) - (WindowX / 2), ParentRect.top +(int)(ParentY / 2) - (WindowY / 2) + TopBar, 400, 300, SWP_NOSIZE);

	//the child windows
	MultiFeatLabel = CreateWindowEx(NULL, "STATIC", "Select Feats", WS_CHILD, 5, 5, 100, 20, MultiFeatHandle, (HMENU)MFW_LABEL, Instance, NULL);
	CharClassText = CreateWindowEx(NULL, "STATIC", "Class", WS_CHILD, 5 + 120, 5, 700, 20, MultiFeatHandle, (HMENU)MFW_CLASSTEXT, Instance, NULL);
	//AddButton = CreateWindowEx(NULL, "BUTTON", "Add", WS_CHILD | BS_PUSHBUTTON, 700, 5, 50, 25, MultiFeatHandle, (HMENU)MFW_Add, Instance, NULL);
	//RemoveButton = CreateWindowEx(NULL, "BUTTON", "Remove", WS_CHILD | BS_PUSHBUTTON, 760, 5, 50, 25, MultiFeatHandle, (HMENU)MFW_Remove, Instance, NULL);

	AcceptButton = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD | BS_PUSHBUTTON, 885, 5, 50, 25, MultiFeatHandle, (HMENU)MFW_ACCEPT, Instance, NULL);
	CancelButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 940, 5, 50, 25, MultiFeatHandle, (HMENU)MFW_CANCEL, Instance, NULL);
	int basex = 10;
	int basey = 30;
	int currentx = basex;
	int currenty = basey;
	int width = 270;
	int height = 675;
	SelectedPanel = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, currentx, currenty, width, height, MultiFeatHandle, (HMENU)MFW_SELECTEDPANEL, Instance, NULL);
	SelectedPanelLabel = CreateWindowEx(NULL, "STATIC", "Selected Feats", WS_CHILD, currentx + 5, currenty + 5, width - 10, 20, MultiFeatHandle, (HMENU)MFW_SELECTEDPANELLABEL, Instance, NULL);
	SelectedPanelList = CreateWindowEx(NULL, "LISTBOX", "Feat List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, currentx + 5, currenty + 25, width - 10, height - 35, MultiFeatHandle, (HMENU)MFW_SELECTEDPANELLIST, Instance, NULL);
	currentx += 280;
	FeatListPanel = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, currentx, currenty, width, height, MultiFeatHandle, (HMENU)MFW_FEATLISTPANEL, Instance, NULL);
	FeatListPanelLabel = CreateWindowEx(NULL, "STATIC", "Feat List", WS_CHILD, currentx + 5, currenty + 5, width - 10, 20, MultiFeatHandle, (HMENU)MFW_FEATLISTPANELLABEL, Instance, NULL);
	FeatListPanelList = CreateWindowEx(NULL, "LISTBOX", "Feat List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, currentx + 5, currenty + 25, width - 10, height - 35, MultiFeatHandle, (HMENU)MFW_FEATLISTPANELLIST, Instance, NULL);
	currentx += 280;
	height = 225;
	width = 280;
	DescPanel = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_READONLY, currentx, currenty, width, height, MultiFeatHandle, (HMENU)MFW_DESCPANEL, Instance, NULL);
	currenty += height + 10;
	height = 110;
	SelectPanel = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, currentx, currenty, width, height, MultiFeatHandle, (HMENU)MFW_SELECTPANEL, Instance, NULL);
	currenty += height + 10;
	height = 320;
	FeatWishPanel = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, currentx, currenty, width, height, MultiFeatHandle, (HMENU)MFW_FEATWISHPANEL, Instance, NULL);
	FeatWishPanelLabel = CreateWindowEx(NULL, "STATIC", "Wish List", WS_CHILD, currentx + 5, currenty + 5, width - 10, 20, MultiFeatHandle, (HMENU)MFW_FEATWISHPANELLIST, Instance, NULL);
	FeatWishPanelList = CreateWindowEx(NULL, "LISTBOX", "Feat List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, currentx + 5, currenty + 25, width - 10, height - 35, MultiFeatHandle, (HMENU)MFW_FEATWISHPANELLIST, Instance, NULL);
	ClearButton = CreateWindowEx(NULL, "BUTTON", "Reset Level Feats", WS_CHILD | BS_PUSHBUTTON, 860, 550, 125, 60, MultiFeatHandle, (HMENU)MFW_CLEAR , Instance, NULL);
	
	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);


	//create a font
	lf.lfHeight = 20;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_MEDIUM;
	lf.lfItalic = false;
	lf.lfUnderline = true;
	lf.lfStrikeOut = false;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	TitleFontLarge = CreateFontIndirect(&lf);
	
	//background color changes
	SendMessage(DescPanel, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 0));

	//create a default font
 



	SendMessage(DescPanel, WM_SETFONT, (WPARAM)DefaultFont, 0);
	SendMessage(SelectedPanelList, WM_SETFONT, (WPARAM)DefaultFont, 0);
	SendMessage(SelectedPanelList, LB_SETITEMHEIGHT, 0, MAKELPARAM(35, 0));
	SendMessage(FeatListPanelList, WM_SETFONT, (WPARAM)DefaultFont, 0);
	SendMessage(FeatListPanelList, LB_SETITEMHEIGHT, 0, MAKELPARAM(35, 0));
	SendMessage(FeatWishPanelList, WM_SETFONT, (WPARAM)DefaultFont, 0);
	SendMessage(FeatWishPanelList, LB_SETITEMHEIGHT, 0, MAKELPARAM(35, 0));

	//subclass windows so we can catch messages
	

	LoadGraphics(MultiFeatHandle);
	SubclassChildWindows();

}
//---------------------------------------------------------------------------
void MultiFeatWindowClass::MultiFeatWindowSetLevel(int Level)
{
	CurrentSelectedLevel = Level;
}
//---------------------------------------------------------------------------
void MultiFeatWindowClass::Show(bool State)
{

	ostringstream Text;
	//pop it up
	ShowWindow(MultiFeatHandle, State);
	ShowWindow(MultiFeatLabel, State);
	//ShowWindow(AcceptButton, State);
	ShowWindow(CancelButton, State);
	ShowWindow(SelectedPanel, State);
	ShowWindow(SelectedPanelList, State);
	ShowWindow(FeatListPanel, State);
	ShowWindow(FeatListPanelList, State);
	ShowWindow(FeatWishPanel, State);
	ShowWindow(FeatWishPanelList, State);
	ShowWindow(DescPanel, State);
	ShowWindow(SelectPanel, State);
	ShowWindow(FeatListPanelLabel, State);
	ShowWindow(SelectedPanelLabel, State);
	ShowWindow(FeatWishPanelLabel, State);
	ShowWindow(CharClassText, State);
	ShowWindow(ClearButton, State);
	//ShowWindow(AddButton, State);
	//ShowWindow(RemoveButton, State);

	EnableWindow(AcceptButton, false);

	//Center in Window
	HDC ParentDC;
	int ParentX;
	int ParentY;
	RECT ParentRect;
	RECT WindowRect;

	int WindowX;
	int WindowY;
	HWND ParentWindow;
	int TopBar = 25;
	ParentWindow = InterfaceManager.ControlWindow.GetControlWindowHandle();
	GetWindowRect(ParentWindow, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top-TopBar;

	GetWindowRect(MultiFeatHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiFeatHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2)+TopBar, 0, 0, SWP_NOSIZE);


	string String1;
	String1 = "{\\b Levels that have Feats to select are Blue\\par ";
	String1 += "Levels with no Feats are Gray\\par ";
	String1 += "Current level is Green\\par ";
	String1 += "Add Feat to Wishlist to add at a later level\\par ";
	String1 += "If you attempt to add a feat with out the requirements it will be added to the wish list.}\\par ";
	
	fillDescPanel(String1);
	FillSelectedPanel();
	FillFeatSelectPanel();
	FillFeatWishPanel();
	ParentDC = GetDC(MultiFeatHandle);

	DrawSelectPanel(ParentDC);
	DrawLevelBars(ParentDC);
	ReleaseDC(MultiFeatHandle, ParentDC);
	SetCharClassText();


}
//---------------------------------------------------------------------------
long MultiFeatWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	int pos;
	POINTS ps;
	POINT ps1;
	pos = GetMessagePos();
	ps = MAKEPOINTS(pos);
	ps1.x = ps.x;
	ps1.y = ps.y;
	ScreenToClient(MultiFeatHandle, (LPPOINT)&ps1);

	switch (Message)
	{
		case WM_CLOSE:
		{
			InterfaceManager.ShowChild(MULTIFEATWINDOW, false);
			return 0;
			break;
		}
		case WM_COMMAND:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if ((int)LOWORD(wParam) == MFW_ACCEPT)
				{
					InterfaceManager.ShowChild(MULTIFEATWINDOW, false);
					return 0;
				}
				if ((int)LOWORD(wParam) == MFW_CANCEL)
				{
					InterfaceManager.ShowChild(MULTIFEATWINDOW, false);
					return 0;
				}
				if ((int)LOWORD(wParam) == MFW_CLEAR)
				{
					ClearFeats();
					return 0;
				}
				//if ((int)LOWORD(wParam) == MFW_Remove)
				//{

				//	return 0;
				//}
				//return 0;

			}
			break;

		}
		case WM_MOUSEWHEEL:
		{
			GetWindowRect(SelectedPanelList, &Rect);
			if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
			{
				if ((short)HIWORD(wParam) > 0)
					SendMessage(SelectedPanelList, WM_VSCROLL, SB_LINEUP, 0);
				else
					SendMessage(SelectedPanelList, WM_VSCROLL, SB_LINEDOWN, 0);
			}
			GetWindowRect(FeatListPanelList, &Rect);
			if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
			{
				if ((short)HIWORD(wParam) > 0)
					SendMessage(FeatListPanelList, WM_VSCROLL, SB_LINEUP, 0);
				else
					SendMessage(FeatListPanelList, WM_VSCROLL, SB_LINEDOWN, 0);
			}
			GetWindowRect(FeatWishPanelList, &Rect);
			if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
			{
				if ((short)HIWORD(wParam) > 0)
					SendMessage(FeatWishPanelList, WM_VSCROLL, SB_LINEUP, 0);
				else
					SendMessage(FeatWishPanelList, WM_VSCROLL, SB_LINEDOWN, 0);
			}
			GetWindowRect(DescPanel, &Rect);
			if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
			{
				if ((short)HIWORD(wParam) > 0)
					SendMessage(DescPanel, WM_VSCROLL, SB_LINEUP, 0);
				else
					SendMessage(DescPanel, WM_VSCROLL, SB_LINEDOWN, 0);
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{

			HandleLeftMouseButtonClick(ps1.x, ps1.y);
			return 0;
			break;
		}
		case WM_LBUTTONUP:
		{
			if (Dragging == true)
			{
				//Character.EnableValidations(false); // CDE: Avoid too many redraw of UI
				EndDragAndDropOperation((int)LOWORD(lParam), (int)HIWORD(lParam));
				//Character.EnableValidations(true);
			}
			return 0;
			break;
		}
		case WM_RBUTTONDOWN:
		{
			HandleRightMouseButtonClick(ps1.x, ps1.y);
			return 0;
			break;
		}


		case WM_CTLCOLORLISTBOX:
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (long)GetStockObject(DKGRAY_BRUSH);
			break;
		}
		case WM_CTLCOLORSTATIC:
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(255, 255, 255));
			return (long)GetStockObject(DKGRAY_BRUSH);
			break;
		}
		case WM_DRAWITEM:
		{
			if (InterfaceManager.ChildWindowVisible() == true)
				return true;
			if ((unsigned int)wParam == MFW_SELECTEDPANELLIST)
			{
				DrawSelectedFeatBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
			}
			if ((unsigned int)wParam == MFW_FEATLISTPANELLIST)
			{
				DrawFeatSelectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
			}
			if ((unsigned int)wParam == MFW_FEATWISHPANELLIST)
			{
				DrawFeatWishBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
			}
			break;
		}
		case WM_SETCURSOR:
		{
			if (Dragging == true)
			{
				SetCursor(Cursor);
				return 1;
			}
			if ((HWND)wParam == DescPanel)
			{
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				return 1;
			}
			return DefWindowProc(Wnd, Message, wParam, lParam);
			break;
		}
		default:
		{
			return DefWindowProc(Wnd, Message, wParam, lParam);
		}
	}
	return DefWindowProc(Wnd, Message, wParam, lParam);
}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::ClearFeats()
{
	HDC hdc;
	int FeatCount = Character.GetFeatCountAtLevel(CurrentSelectedLevel);
	if (FeatCompare > 0)
	{
		for (int i = 0; i<FeatCount; i++)
		{
			Character.RemoveFeat(Character.GetFeatAtLevel(CurrentSelectedLevel,0));
		}
		hdc = GetDC(MultiFeatHandle);
		DrawSelectPanel(hdc);
		ReleaseDC(MultiFeatHandle, hdc);
	}
	
}
//--------------------------------------------------------------------------
long MultiFeatWindowClass::HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	WNDPROC OriginalProc;
	DWORD Selection;
	string Description;

	string Text;
	int Position;
	ostringstream ss;
	FeatDataClass *Feat;
	int FeatCount;
	int pos;
	POINTS ps;
	pos = GetMessagePos();
	ps = MAKEPOINTS(pos);
	switch (Message)
	{
		case WM_CHAR:
		{
			if (LOWORD(wParam) == VK_TAB)
				return 0;		//prevent the annoying 'ding' sound when tabbing
			break;
		}
		case WM_KEYDOWN:
		{
			break;
		}
		case WM_LBUTTONDBLCLK:
		{
			if (Wnd == SelectedPanelList)
				return 0;
			break;
			if (Wnd == FeatListPanelList)
				return 0;
			break;
			if (Wnd == FeatWishPanelList)
				return 0;
			break;
			if (Wnd == DescPanel)
				return 0;
			break;
		}
		case WM_LBUTTONDOWN:
		{
			if (Wnd == DescPanel)
				return 0;
			if (Wnd == SelectedPanelList)
			{	
				FeatCount = 0;
				Selection = SendMessage(SelectedPanelList, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(SelectedPanelList, LB_GETITEMDATA, Selection, 0);
				if (IconDrag == -1)
					return 0;
				if (IconDrag == 999999)
				{
					//click on a parent heading. change the collapse state
					for (unsigned int i = 0; i < FeatListParentHeading.size(); i++)
					{
						if (FeatListParentHeading[i].ListIndex == Selection)
						{
							FeatListParentHeading[i].Collapsed = !FeatListParentHeading[i].Collapsed;
							break;
						}
					}
					Position = SendMessage(SelectedPanelList, LB_GETTOPINDEX, 0, 0);
					FillSelectedPanel();
					SendMessage(SelectedPanelList, LB_SETTOPINDEX, (WPARAM)Position, 0);
					IconDrag = -1;
					return 0;
				}
				if (IconDrag > 999999)
					IconDrag -= 1000000;
				Feat = Data.GetFeatPointer(IconDrag);
				Description = "{\\b ";
				Description += Feat->GetFeatName(true);
				Description += "} \\par";
				FeatCount = Character.CountFeat(Feat->GetFeatName(true), CurrentSelectedLevel);
				if (FeatCount > 1)
				{
					Description += " {\\b Aquired: ";
					Description += to_string(FeatCount);
					Description += " times} \\par\\par ";
				}
				else
					Description += "\\par ";
				Description += Feat->GetFeatDescription();
				while (Description.find("$RACE") != std::string::npos)
					Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
				//add in the prereqs lists
				Description += " \\par\\par ";
				Description += Feat->GetPrereqString(CurrentSelectedLevel);
				fillDescPanel(Description, FeatIcon[Feat->GetFeatIconIndex()].Graphic);
				return 0;
			}
			if (Wnd == FeatListPanelList)
			{
				Selection = SendMessage(FeatListPanelList, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(FeatListPanelList, LB_GETITEMDATA, Selection, 0);
				if (IconDrag == -1)
					return 0;
				if (IconDrag == 999999)
				{
					//click on a parent heading. change the collapse state
					for (unsigned int i = 0; i < FeatListSelectParentHeading.size(); i++)
					{
						if (FeatListSelectParentHeading[i].ListIndex == Selection)
						{
							FeatListSelectParentHeading[i].Collapsed = !FeatListSelectParentHeading[i].Collapsed;
							break;
						}
					}
					Position = SendMessage(FeatListPanelList, LB_GETTOPINDEX, 0, 0);
					FillFeatSelectPanel();
					SendMessage(FeatListPanelList, LB_SETTOPINDEX, (WPARAM)Position, 0);
					IconDrag = -1;
					return 0;
				}
				if (IconDrag > 999999)
					IconDrag -= 1000000;
				Feat = Data.GetFeatPointer(IconDrag);
				Description = "{\\b ";
				Description += Feat->GetFeatName(true);
				Description += "} \\par\\par ";
				Description += Feat->GetFeatDescription();
				while (Description.find("$RACE") != std::string::npos)
					Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
				//add in the prereqs lists
				Description += " \\par\\par ";
				Description += Feat->GetPrereqString(CurrentSelectedLevel);
				fillDescPanel(Description, FeatIcon[Feat->GetFeatIconIndex()].Graphic);
				Dragging = true;
				Cursor = CreateCursorFromBitmap(MultiFeatHandle, Palette, &FeatIcon[Feat->GetFeatIconIndex()], RGB(0, 0, 0), 16, 16);
				SetCursor(Cursor);
				return 0;
			}
			if (Wnd == FeatWishPanelList)
			{
				Selection = SendMessage(FeatWishPanelList, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(FeatWishPanelList, LB_GETITEMDATA, Selection, 0);
				if (IconDrag == -1)
					return 0;
				if (IconDrag > 999999)
					IconDrag -= 1000000;
				Feat = Data.GetFeatPointer(IconDrag);
				Description = "{\\b ";
				Description += Feat->GetFeatName(true);
				Description += "} \\par\\par ";
				Description += Feat->GetFeatDescription();
				while (Description.find("$RACE") != std::string::npos)
					Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
				//add in the prereqs lists
				Description += " \\par\\par ";
				Description += Feat->GetPrereqString(CurrentSelectedLevel);
				fillDescPanel(Description, FeatIcon[Feat->GetFeatIconIndex()].Graphic);
				Dragging = true;
				Cursor = CreateCursorFromBitmap(MultiFeatHandle, Palette, &FeatIcon[Feat->GetFeatIconIndex()], RGB(0, 0, 0), 16, 16);
				SetCursor(Cursor);
				return 0;
			}
		
			break;
		}
		case WM_RBUTTONDOWN:
		{
			if (Wnd == FeatWishPanelList)
			{
				Selection = SendMessage(FeatWishPanelList, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(FeatWishPanelList, LB_GETITEMDATA, Selection, 0);
				RemoveFeatWishListItem(IconDrag);
			}
			break;
		}
		case WM_LBUTTONUP:
			{
				if (Dragging == true)
				{

					EndDragAndDropOperation(ps.x, ps.y);
				}
				break;
			}
	}
	OriginalProc = GetOriginalWinProc(Wnd);
	return CallWindowProc(OriginalProc, Wnd, Message, wParam, lParam);
	
}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::HandleLeftMouseButtonClick(int x, int y)
{
		HDC  ParentDC;
		string Description;
		int Index;
		int Width;
		int Height;
		int X, Y;
		//int Position;
		ostringstream ss;
		UIComponentManager *UIManager;
		InterfaceGraphicStruct *Graphic;
		FeatDataClass *Feat;
		RECT Frame;
		int OldSelectedLevel;

		UIManager = InterfaceManager.GetUIComponents();
		//Check SelectPanel
		GetWindowRect(SelectPanel, &Frame);
		MapWindowPoints(HWND_DESKTOP, MultiFeatHandle, (LPPOINT)&Frame, 2);
		int FrameBottom = Frame.bottom;
		Index = -1;
		for (unsigned int i = 0; i<3; i++)
		{
			ss.str("");
			ss << "FeatSlot" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = FrameBottom - 90;
			Width = 45;
			Height = 45;
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				Index = i;
		}

		if (Index != -1)
		{

			IconDrag = Character.GetFeat(CurrentSelectedLevel, FeatSlot[Index], 0);
			if (IconDrag == -1)
				return ;
			Feat = Data.GetFeatPointer(IconDrag);

			Description = "{\\b ";
			Description += Feat->GetFeatName(true);
			Description += "} \\par\\par ";
			Description += Feat->GetFeatDescription();
			while (Description.find("$RACE") != std::string::npos)
				Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
			//add in the prereqs lists
			Description += " \\par\\par ";
			Description += Feat->GetPrereqString(CurrentSelectedLevel);
			fillDescPanel(Description, FeatIcon[Feat->GetFeatIconIndex()].Graphic);
			Dragging = true;
			Cursor = CreateCursorFromBitmap(MultiFeatHandle, Palette, &FeatIcon[Feat->GetFeatIconIndex()], RGB(0, 0, 0), 16, 16);
			SetCursor(Cursor);

			return;
		}

		OldSelectedLevel = CurrentSelectedLevel;
		for (int i = 0; i < 30; i++)
		{
			ss.str("");
			ss << "FeatLevelBar" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			LevelWidth = static_cast<int>(Graphic->BaseWidth);
			LevelHeight = static_cast<int>(Graphic->BaseHeight);
				if (x >= X && x <= X + LevelWidth && y >= Y && y <= Y + LevelHeight)
				{

					if (i + 1 == (int)CurrentSelectedLevel)
						return;
					CurrentSelectedLevel = i + 1;
				}
				
				if (CurrentSelectedLevel != OldSelectedLevel)
				{
					//Character.EnableValidations(false);
					FillSelectedPanel();
					FillFeatSelectPanel();
					FillFeatWishPanel();
					ParentDC = GetDC(MultiFeatHandle);
					DrawLevelBars(ParentDC);
					DrawSelectPanel(ParentDC);
					ReleaseDC(MultiFeatHandle, ParentDC);
					SetCharClassText();
					//Character.EnableValidations(true);
					return;
				}
		}




}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::HandleRightMouseButtonClick(int x, int y)
{
	HDC ParentDC;
	int Index;
	int Width;
	int Height;
	int X, Y;
	int Position;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	//FeatDataClass *Feat;
	RECT Frame;
	UIManager = InterfaceManager.GetUIComponents();
	//Check SelectPanel
	GetWindowRect(SelectPanel, &Frame);
	MapWindowPoints(HWND_DESKTOP, GetParent(SelectPanel), (LPPOINT)&Frame, 2);
	int FrameBottom = Frame.bottom;
	Index = -1;
	for (unsigned int i = 0; i<3; i++)
	{
		ss.str("");
		ss << "FeatSlot" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = FrameBottom - 90;
		Width = 45;
		Height = 45;
		if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
			Index = i;
	}

	if (Index != -1)
	{
		IconDrag = Character.GetFeat(CurrentSelectedLevel, FeatSlot[Index], 0);
		Character.RemoveFeat(IconDrag);
		Character.ResetAutoFeats(CurrentSelectedLevel);
		ParentDC = GetDC(MultiFeatHandle);
		DrawLevelBars(ParentDC);
		Position = SendMessage(FeatListPanelList, LB_GETTOPINDEX, 0, 0);
		FillFeatSelectPanel();
		SendMessage(FeatListPanelList, LB_SETTOPINDEX, (WPARAM)Position, 0);
		Position = SendMessage(SelectedPanelList, LB_GETTOPINDEX, 0, 0);
		FillSelectedPanel();
		SendMessage(SelectedPanelList, LB_SETTOPINDEX, (WPARAM)Position, 0);
		DrawSelectPanel(ParentDC);
		ReleaseDC(MultiFeatHandle, ParentDC);
	}

}

//--------------------------------------------------------------------------
void MultiFeatWindowClass::EndDragAndDropOperation(int x, int y)
{
	HDC ParentDC;
	FeatDataClass *Feat;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	ICONINFO IconInfo;
	RECT ScreenRect;
	SIZE ScreenSize;
	RACE CurrentRace;
	CLASS CurrentClass;
		int Index;
		int Width;
		int Height;
		int X, Y;
		ostringstream ss;
	RECT Frame;
		int Position;

	GetClientRect(MultiFeatHandle, &ScreenRect);
	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;
	UIManager = InterfaceManager.GetUIComponents();
	//figure out what we are dragging
	CurrentRace = Character.GetRace();
	CurrentClass = Character.GetClass(CurrentSelectedLevel);
	//Determin Frame Dropped in
	
	GetWindowRect(FeatWishPanel, &Frame);
	//WishList
	if (x<Frame.right && x> Frame.left && y > Frame.top && y < Frame.bottom)
	{
		AddFeatWishListItem(IconDrag);
	}
	else
	//checkslot
	{
		GetWindowRect(SelectPanel, &Frame);
		MapWindowPoints(HWND_DESKTOP, GetParent(SelectPanel), (LPPOINT)&Frame, 2);
		int FrameBottom = Frame.bottom;
		Index = -1;
		for (unsigned int i = 0; i<3; i++)
		{
			ss.str("");
			ss << "FeatSlot" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = FrameBottom - 90;
			Width = 45;
			Height = 45;
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				Index = i;
		}
		if (Index != -1)
		{ 
			Feat = Data.GetFeatPointer(IconDrag);
			if (Feat->HaveAllFeatPrereqs(CurrentSelectedLevel)!= PREREQ_PASS)
			{ 
				AddFeatWishListItem(IconDrag);
			}
			else{
				//grab a pointer to the feat being dropped
				
				boolean valid = false;
				//note that favored enemy, deity, favored soul bonus, rogue bonus, half-elf dilettante, and druid wild shape feats are exclusive to their particular slots
				//do not allow them to be placed in other slot types
				if (FeatSlot[Index] == FEATCHARACTER || FeatSlot[Index] == FEATHUMANBONUS)
				{
					valid = Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == false && Feat->GetFeatTag(FEATTAGMONKPATH) == false && Feat->GetFeatTag(FEATTAGDEITY) == false && Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == false && Feat->GetFeatTag(FEATTAGROGUEBONUS) == false && Feat->GetFeatTag(FEATTAGHALFELFBONUS) == false && Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == false && Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == false && Feat->GetFeatTag(FEATTAGLEGENDARY) == false;
				}
				else switch (FeatSlot[Index])
				{
				case FEATHALFELFBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true;
					break;
				}
				case FEATFIGHTERBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGFIGHTERBONUS) == true;
					break;
				}
				case FEATWIZARDBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGMETAMAGIC) == true;
					break;
				}
				case FEATARTIFICERBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGMETAMAGIC) == true || Feat->GetFeatTag(FEATTAGARTIFICERBONUS) == true;
					break;
				}
				case FEATRANGERFAVOREDENEMY:
				{
					valid = Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true;
					break;
				}
				case FEATROGUEBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGROGUEBONUS) == true;
					break;
				}
				case FEATMONKBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGMONKBONUS) == true || Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true;
					break;
				}
				case FEATMONKPATH:
				{
					valid = Feat->GetFeatTag(FEATTAGMONKPATH) == true;
					break;
				}
				case FEATDEITY:
				{
					valid = Feat->GetFeatTag(FEATTAGDEITY) == true;
					break;
				}
				case FEATFAVOREDSOULBONUS:
				{
					valid = Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true;
					break;
				}
				case FEATDRUIDWILDSHAPE:
				{
					valid = Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true;
					break;
				}
				case FEATWARLOCKPACT:
				{
					valid = Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true;
					break;
				}
				case FEATDESTINY:
				{
					valid = Feat->GetFeatTag(FEATTAGDESTINY) == true || Feat->GetFeatTag(FEATTAGDESTINYNOTEXCLUSIVE) == true;
					break;
				}
				case FEATLEGENDARY:
				{
					valid = Feat->GetFeatTag(FEATTAGLEGENDARY) == true;
					break;
				}
				case DRAGONBORN:
				{
					valid = Feat->GetFeatTag(FEATTAGDRAGONBORNBONUS) == true;
					break;
				}
				default:
					// Not valid
					break;
				}
				if (valid)
				{
					RemoveFeatWishListItem(IconDrag);
					Character.AddFeat(CurrentSelectedLevel, IconDrag, FeatSlot[Index]);
					ParentDC = GetDC(MultiFeatHandle);
					DrawLevelBars(ParentDC);
					//because some automatic feats are now prereqs for other feats, do an auto feat reset
					Character.ResetAutoFeats(CurrentSelectedLevel);
					Position = SendMessage(FeatListPanelList, LB_GETTOPINDEX, 0, 0);
					FillFeatSelectPanel();
					SendMessage(FeatListPanelList, LB_SETTOPINDEX, (WPARAM)Position, 0);
					Position = SendMessage(SelectedPanelList, LB_GETTOPINDEX, 0, 0);
					FillSelectedPanel();
					SendMessage(SelectedPanelList, LB_SETTOPINDEX, (WPARAM)Position, 0);
					DrawSelectPanel(ParentDC);
					ReleaseDC(MultiFeatHandle, ParentDC);
				}
			}
		}






	}
		//reset
	GetIconInfo((HICON)IDC_ARROW, &IconInfo);
	IconInfo.fIcon = false;
	IconInfo.xHotspot = 0;
	IconInfo.yHotspot = 0;
	CreateIconIndirect(&IconInfo);
	SetCursor(CreateIconIndirect(&IconInfo));
	Dragging = false;
	IconDrag = -1;

}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::SubclassChildWindows()
{
	WNDPROC OriginalProc;

	SubclassHWNDs.clear();
	OriginalProcs.clear();

	OriginalProc = (WNDPROC)SetWindowLong(SelectedPanelList, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(SelectedPanelList);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(FeatListPanelList, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(FeatListPanelList);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(FeatWishPanelList, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(FeatWishPanelList);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(DescPanel, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(DescPanel);
	OriginalProcs.push_back(OriginalProc);

}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::DesubclassChildWindows()
{
	for (unsigned int i = 0; i<SubclassHWNDs.size(); i++)
		SetWindowLongPtr(SubclassHWNDs[i], GWL_WNDPROC, static_cast<__int3264>(reinterpret_cast<LONG_PTR>(OriginalProcs[i])));
}
//--------------------------------------------------------------------------
WNDPROC MultiFeatWindowClass::GetOriginalWinProc(HWND Window)
{
	for (unsigned int i = 0; i<SubclassHWNDs.size(); i++)
	{
		if (SubclassHWNDs[i] == Window)
			return OriginalProcs[i];
	}
	return 0;
}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::LoadGraphics(HWND Parent)
{
	HDC hdc;
	//palette for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	LoadBitmap("PlusBox", "UserInterface", &PlusBox);
	LoadBitmap("MinusBox", "UserInterface", &MinusBox);

	//the level boxes
	LoadBitmap("LevelBoxBlue", "UserInterface", &BlueLevelBox);
	LoadBitmap("LevelBoxGreen", "UserInterface", &GreenLevelBox);
	LoadBitmap("LevelBoxRed", "UserInterface", &RedLevelBox);
	LoadBitmap("LevelBoxGrey", "UserInterface", &GreyLevelBox);
	LoadBitmap("LevelBoxYellow", "UserInterface", &YellowLevelBox);
	LoadBitmap("EmptyFeatSlot", "UserInterface", &EmptyFeatSlot);
}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::SetCharClassText()
{
	string Text;
	ostringstream ss;
	int ClassLevel[NUMCLASSES];
	//bool First;

	for (unsigned int i = 0; i<NUMCLASSES; i++)
		ClassLevel[i] = Character.GetClassLevel(CLASS(i), CurrentSelectedLevel);
	ss.str("");
	ss << "Level " << CurrentSelectedLevel << " ";
	ss << Data.GetAlignmentString(Character.GetAlignment()) << " ";
	ss << Character.GetRaceString();
	if (Character.GetSex() == MALE)
		ss << " Male (";
	else
		ss << " Female (";

	ss << Character.GetClassString(CurrentSelectedLevel);
	ss << ")";


	ss << " Class this Level ";

	ss << Data.GetClassNameA(Character.GetClass(CurrentSelectedLevel,FALSE));
	Text = ss.str();
	SendMessage(CharClassText, WM_SETTEXT, 0, (LPARAM)Text.c_str());
}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::DrawSelectedFeatBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
{
	string Text;
	COLORREF OriginalColor;
	int XOffset;
	FeatDataClass *Feat;

	if (Item == 999999)
	{
		for (unsigned int i = 0; i<FeatListParentHeading.size(); i++)
		{
			if (FeatListParentHeading[i].ListIndex == Index)
			{
				if (FeatListParentHeading[i].Collapsed == true)
					DrawGraphic(hDC, &PlusBox, left, top + 4, 18, 18);
				else
					DrawGraphic(hDC, &MinusBox, left, top + 4, 18, 18);
				Text = FeatListParentHeading[i].ParentHeading;
				OriginalColor = SetTextColor(hDC, RGB(255, 255, 255));
				TextOut(hDC, left + 25, top + 3, Text.c_str(), Text.size());
				SetTextColor(hDC, OriginalColor);
				return;
			}
		}
	}

	XOffset = 0;
	if (Item > 999999)
	{
		XOffset = 15;
		Item -= 1000000;
	}

	Feat = Data.GetFeatPointer(Item);
	DrawGraphic(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left + XOffset, top, 30, 30);
	Text = Feat->GetFeatName();
	OriginalColor = SetTextColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, left + 35 + XOffset, top + 6, Text.c_str(), Text.size());
	SetTextColor(hDC, OriginalColor);
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::DrawFeatSelectBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
{
	string Text;
	COLORREF OriginalColor;
	bool Metamagic;
	bool FighterBonus;
	bool ArtificerBonus;
	bool FavoredEnemy;
	bool RogueBonus;
	bool MonkBonus;
	bool MonkPath;
	bool Deity;
	bool FavoredSoulBonus;
	bool HalfElfBonus;
	bool DruidWildShape;
	bool WarlockPact;
	bool Destiny;
	bool Legendary;
	bool Dragonborn;

	int XOffset;
	PREREQRESULT FeatPrereqStatus;
	FeatDataClass *Feat;
	Character.DetermineFeatSlots(CurrentSelectedLevel, &FeatSlot[0], &FeatSlot[1], &FeatSlot[2]);
	if (Item == 999999)
	{
		for (unsigned int i = 0; i<FeatListSelectParentHeading.size(); i++)
		{
			if (FeatListSelectParentHeading[i].ListIndex == Index)
			{
				if (FeatListSelectParentHeading[i].Collapsed == true)
					DrawGraphic(hDC, &PlusBox, left, top + 4, 18, 18);
				else
					DrawGraphic(hDC, &MinusBox, left, top + 4, 18, 18);
				Text = FeatListSelectParentHeading[i].ParentHeading;
				OriginalColor = SetTextColor(hDC, RGB(255, 255, 255));
				TextOut(hDC, left + 25, top + 6, Text.c_str(), Text.size());
				SetTextColor(hDC, OriginalColor);
				return;
			}
		}
	}

	XOffset = 0;
	if (Item > 999999)
	{
		XOffset = 15;
		Item -= 1000000;
	}

	FighterBonus = false;
	ArtificerBonus = false;
	Metamagic = false;
	FavoredEnemy = false;
	RogueBonus = false;
	MonkBonus = false;
	MonkPath = false;
	Deity = false;
	FavoredSoulBonus = false;
	DruidWildShape = false;
	HalfElfBonus = false;
	WarlockPact = false;
	Destiny = false;
	Legendary = false;
	Dragonborn = false;

	for (unsigned int i = 0; i<3; i++)
	{
		if (FeatSlot[i] == FEATFIGHTERBONUS)
			FighterBonus = true;
		if (FeatSlot[i] == FEATWIZARDBONUS)
			Metamagic = true;
		if (FeatSlot[i] == FEATARTIFICERBONUS)
			ArtificerBonus = true;
		if (FeatSlot[i] == FEATRANGERFAVOREDENEMY)
			FavoredEnemy = true;
		if (FeatSlot[i] == FEATROGUEBONUS)
			RogueBonus = true;
		if (FeatSlot[i] == FEATMONKBONUS)
			MonkBonus = true;
		if (FeatSlot[i] == FEATMONKPATH)
			MonkPath = true;
		if (FeatSlot[i] == FEATDEITY)
			Deity = true;
		if (FeatSlot[i] == FEATFAVOREDSOULBONUS)
			FavoredSoulBonus = true;
		if (FeatSlot[i] == FEATHALFELFBONUS)
			HalfElfBonus = true;
		if (FeatSlot[i] == FEATDRUIDWILDSHAPE)
			DruidWildShape = true;
		if (FeatSlot[i] == FEATWARLOCKPACT)
			WarlockPact = true;
		if (FeatSlot[i] == FEATDESTINY)
			Destiny = true;
		if (FeatSlot[i] == FEATLEGENDARY)
			Legendary = true;
		if (FeatSlot[i] == FEATDRAGONBORNBONUS)
			Dragonborn = true;
	}

	//grab a pointer to the feat
	Feat = Data.GetFeatPointer(Item);

	FeatPrereqStatus = Feat->HaveAllFeatPrereqs(CurrentSelectedLevel);
	if (FeatPrereqStatus == PREREQ_PASS)
	{
		DrawGraphic(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left + XOffset, top, 30, 30);
		Text = Feat->GetFeatName();
		if (Metamagic == true && Feat->GetFeatTag(FEATTAGMETAMAGIC) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (FighterBonus == true && Feat->GetFeatTag(FEATTAGFIGHTERBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (ArtificerBonus == true && Feat->GetFeatTag(FEATTAGARTIFICERBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (FavoredEnemy == true && Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (RogueBonus == true && Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (MonkBonus == true && Feat->GetFeatTag(FEATTAGMONKBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (MonkPath == true && Feat->GetFeatTag(FEATTAGMONKPATH) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Deity == true && Feat->GetFeatTag(FEATTAGDEITY) == true)
			OriginalColor = SetTextColor(hDC, RGB(100, 255, 0));
		else if (FavoredSoulBonus == true && Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (HalfElfBonus == true && Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(255, 0, 155));
		else if (MonkBonus == true && Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (DruidWildShape == true && Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (WarlockPact == true && Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Destiny == true && Feat->GetFeatTag(FEATTAGDESTINY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Destiny == true && Feat->GetFeatTag(FEATTAGDESTINYNOTEXCLUSIVE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Legendary == true && Feat->GetFeatTag(FEATTAGLEGENDARY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (HalfElfBonus == true && Feat->GetFeatTag(FEATTAGDRAGONBORNBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(255, 0, 155));
		else
			OriginalColor = SetTextColor(hDC, RGB(255, 255, 255));
		TextOut(hDC, left + 35 + XOffset, top + 10, Text.c_str(), Text.size());
		SetTextColor(hDC, OriginalColor);
	}
	else if (FeatPrereqStatus == PREREQ_FAIL)
	{
		DrawGraphicGreyscale(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left + XOffset, top, 30, 30);
		Text = Feat->GetFeatName();
		OriginalColor = SetTextColor(hDC, RGB(150, 150, 150));
		TextOut(hDC, left + 35 + XOffset, top + 10, Text.c_str(), Text.size());
		SetTextColor(hDC, OriginalColor);
	}


}
//--------------------------------------------------------------------------
void MultiFeatWindowClass::DrawFeatWishBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
{
	string Text;
	COLORREF OriginalColor;
	FeatDataClass *Feat;
	bool Metamagic;
	bool FighterBonus;
	bool ArtificerBonus;
	bool FavoredEnemy;
	bool RogueBonus;
	bool MonkBonus;
	bool MonkPath;
	bool Deity;
	bool FavoredSoulBonus;
	bool HalfElfBonus;
	bool DruidWildShape;
	bool WarlockPact;
	bool Destiny;
	bool Legendary;
	bool Dragonborn;

	PREREQRESULT FeatPrereqStatus;

	FighterBonus = false;
	ArtificerBonus = false;
	Metamagic = false;
	FavoredEnemy = false;
	RogueBonus = false;
	MonkBonus = false;
	MonkPath = false;
	Deity = false;
	FavoredSoulBonus = false;
	DruidWildShape = false;
	HalfElfBonus = false;
	WarlockPact = false;
	Destiny = false;
	Legendary = false;
	Dragonborn = false;

	for (unsigned int i = 0; i<3; i++)
	{
		if (FeatSlot[i] == FEATFIGHTERBONUS)
			FighterBonus = true;
		if (FeatSlot[i] == FEATWIZARDBONUS)
			Metamagic = true;
		if (FeatSlot[i] == FEATARTIFICERBONUS)
			ArtificerBonus = true;
		if (FeatSlot[i] == FEATRANGERFAVOREDENEMY)
			FavoredEnemy = true;
		if (FeatSlot[i] == FEATROGUEBONUS)
			RogueBonus = true;
		if (FeatSlot[i] == FEATMONKBONUS)
			MonkBonus = true;
		if (FeatSlot[i] == FEATMONKPATH)
			MonkPath = true;
		if (FeatSlot[i] == FEATDEITY)
			Deity = true;
		if (FeatSlot[i] == FEATFAVOREDSOULBONUS)
			FavoredSoulBonus = true;
		if (FeatSlot[i] == FEATHALFELFBONUS)
			HalfElfBonus = true;
		if (FeatSlot[i] == FEATDRUIDWILDSHAPE)
			DruidWildShape = true;
		if (FeatSlot[i] == FEATWARLOCKPACT)
			WarlockPact = true;
		if (FeatSlot[i] == FEATDESTINY)
			Destiny = true;
		if (FeatSlot[i] == FEATLEGENDARY)
			Legendary = true;
		if (FeatSlot[i] == FEATDRAGONBORNBONUS)
			Dragonborn = true;
	}

	//grab a pointer to the feat
	Feat = Data.GetFeatPointer(Item);

	FeatPrereqStatus = Feat->HaveAllFeatPrereqs(CurrentSelectedLevel);
	if (FeatPrereqStatus == PREREQ_PASS)
	{
		DrawGraphic(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left, top, 30, 30);
		Text = Feat->GetFeatName();
		if (Metamagic == true && Feat->GetFeatTag(FEATTAGMETAMAGIC) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (FighterBonus == true && Feat->GetFeatTag(FEATTAGFIGHTERBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (ArtificerBonus == true && Feat->GetFeatTag(FEATTAGARTIFICERBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (FavoredEnemy == true && Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (RogueBonus == true && Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (MonkBonus == true && Feat->GetFeatTag(FEATTAGMONKBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (MonkPath == true && Feat->GetFeatTag(FEATTAGMONKPATH) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Deity == true && Feat->GetFeatTag(FEATTAGDEITY) == true)
			OriginalColor = SetTextColor(hDC, RGB(100, 255, 0));
		else if (FavoredSoulBonus == true && Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (HalfElfBonus == true && Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(255, 0, 155));
		else if (MonkBonus == true && Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (DruidWildShape == true && Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (WarlockPact == true && Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Destiny == true && Feat->GetFeatTag(FEATTAGDESTINY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Destiny == true && Feat->GetFeatTag(FEATTAGDESTINYNOTEXCLUSIVE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Legendary == true && Feat->GetFeatTag(FEATTAGLEGENDARY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (HalfElfBonus == true && Feat->GetFeatTag(FEATTAGDRAGONBORNBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(255, 0, 155));
		else

		OriginalColor = SetTextColor(hDC, RGB(255, 255, 255));
		TextOut(hDC, left + 35, top + 10, Text.c_str(), Text.size());
		SetTextColor(hDC, OriginalColor);
	}
	else if (FeatPrereqStatus == PREREQ_FAIL)
	{
		DrawGraphicGreyscale(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left, top, 30, 30);
		Text = Feat->GetFeatName();
		OriginalColor = SetTextColor(hDC, RGB(150, 150, 150));
		TextOut(hDC, left + 35, top + 10, Text.c_str(), Text.size());
		SetTextColor(hDC, OriginalColor);
	}
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::DrawLevelBars(HDC hdc)
{
	COLORREF OldColor;
	ostringstream ss;
	int X, Y;
	//FeatDataClass *Feat;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	//RECT Frame;
	int ButtonSpacing = 30;
	int feat;

	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER);
	//InvalidateRect(MultiFeatHandle, NULL, FALSE);
	//UpdateWindow(MultiFeatHandle);
	UIManager = InterfaceManager.GetUIComponents();

	for (unsigned int i = 0; i<30; i++)
	{
		ss.str("");
		ss << "FeatLevelBar" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		LevelWidth = static_cast<int>(Graphic->BaseWidth);
		LevelHeight = static_cast<int>(Graphic->BaseHeight);

		if (CurrentSelectedLevel == i + 1)
			DrawGraphic(hdc, &YellowLevelBox, X, Y, LevelWidth, LevelHeight);
		else
		{
			Character.DetermineFeatSlots(i + 1, &FeatSlot[0], &FeatSlot[1], &FeatSlot[2]);
			if (FeatSlot[0] == FEATNONE)
				DrawGraphic(hdc, &GreyLevelBox, X, Y, LevelWidth, LevelHeight);
			else
			{
			
				bool FeatFilled;
				FeatFilled = TRUE;
				for (int x = 0; x < 3; x++)
				{

					feat = Character.GetFeat(i+1, FeatSlot[x], 0);
					//check if eachslot has feat assigned
					if (feat != -1 || FeatSlot[x] == FEATNONE)
						FeatFilled = TRUE && FeatFilled;
					else
						FeatFilled = FALSE && FeatFilled;

				}
				if (FeatFilled)
					DrawGraphic(hdc, &BlueLevelBox, X, Y, LevelWidth, LevelHeight);
				else
					DrawGraphic(hdc, &GreenLevelBox, X, Y, LevelWidth, LevelHeight);
			}
		}
			
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "L" << i + 1;
		TextOut(hdc, X + 20, Y + 6, ss.str().c_str(), ss.str().size());
		SetTextColor(hdc, OldColor);
	}
	SetTextAlign(hdc, TA_LEFT);
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::DrawSelectPanel(HDC hdc)
{
	string OutputString;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	FeatDataClass *Feat;
	//SIZE ScreenSize;
	ostringstream ss;
	int X, Y;
	int Width, Height;
	int FeatIndex;
	COLORREF OldColor;
	RECT Frame;
	

	Character.DetermineFeatSlots(CurrentSelectedLevel, &FeatSlot[0], &FeatSlot[1], &FeatSlot[2]);
	GetWindowRect(SelectPanel, &Frame);

	
	SetBkMode(hdc, TRANSPARENT);
	MapWindowPoints(HWND_DESKTOP, GetParent(SelectPanel), (LPPOINT)&Frame, 2);
	RedrawWindow(MultiFeatHandle, &Frame, NULL, RDW_ERASE | RDW_INVALIDATE);
	UpdateWindow(MultiFeatHandle);
	int FrameBottom = Frame.bottom;
	UIManager = InterfaceManager.GetUIComponents();
	for (unsigned int i = 0; i < 3; i++)
	{
		if (FeatSlot[i] == FEATNONE)
			break;
		ss.str("");
		ss << "FeatSlot" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(FrameBottom - 90);
		Width = 45; // CDE: Avoid zomming slot box
		Height = 45; // CDE: Avoid zomming slot box
		DrawGraphic(hdc, &EmptyFeatSlot, X, Y, Width, Height);
		FeatIndex = Character.GetFeat(CurrentSelectedLevel, FeatSlot[i], 0);
		if (FeatIndex != -1)
		{
			Feat = Data.GetFeatPointer(FeatIndex);
			ss.str("");
			ss << "FeatFilled" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTIFEATWINDOW);
			X = static_cast<int>(X + 3);
			Y = static_cast<int>(Y + 2);
			Width = 40; // CDE: Avoid zomming filled feat
			Height = 40; // CDE: Avoid zomming filled feat
			DrawGraphic(hdc, &FeatIcon[Feat->GetFeatIconIndex()], X, Y, Width, Height);
		}

		//Set Text Color
		if (FeatSlot[i] == FEATCHARACTER || FeatSlot[i] == FEATHUMANBONUS)
			OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		if (FeatSlot[i] == FEATFIGHTERBONUS || FeatSlot[i] == FEATWIZARDBONUS || FeatSlot[i] == FEATARTIFICERBONUS || FeatSlot[i] == FEATROGUEBONUS || FeatSlot[i] == FEATMONKBONUS ||
			FeatSlot[i] == FEATFAVOREDSOULBONUS || FeatSlot[i] == FEATRANGERFAVOREDENEMY || FeatSlot[i] == FEATMONKPATH || FeatSlot[i] == FEATDRUIDWILDSHAPE || FeatSlot[i] == FEATDESTINY || FeatSlot[i] == FEATLEGENDARY)
			OldColor = SetTextColor(hdc, RGB(230, 230, 30));
		if (FeatSlot[i] == FEATHALFELFBONUS || FeatSlot[i] == FEATDRAGONBORNBONUS)
			OldColor = SetTextColor(hdc, RGB(255, 0, 155));
		if (FeatSlot[i] == FEATDEITY || FeatSlot[i] == FEATWARLOCKPACT)
			OldColor = SetTextColor(hdc, RGB(100, 255, 0));


		if (FeatSlot[i] == FEATCHARACTER)
		{
			Graphic = UIManager->GetGraphicData("FeatTextFeat1", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Feat";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATHUMANBONUS)
		{
			Graphic = UIManager->GetGraphicData("FeatTextHuman", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Human";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextBonusFeat", MULTIFEATWINDOW);
			X = static_cast<int>(X - 15); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Bonus Feat";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATFIGHTERBONUS || FeatSlot[i] == FEATWIZARDBONUS || FeatSlot[i] == FEATARTIFICERBONUS || FeatSlot[i] == FEATROGUEBONUS || FeatSlot[i] == FEATMONKBONUS ||
			FeatSlot[i] == FEATDEITY || FeatSlot[i] == FEATFAVOREDSOULBONUS)
		{
			Graphic = UIManager->GetGraphicData("FeatTextClass", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Class";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextFeat2", MAINWINDOW);
			X = static_cast<int>(X + 4); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Feat";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATRANGERFAVOREDENEMY)
		{
			Graphic = UIManager->GetGraphicData("FeatTextFavored", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Favored";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextEnemy", MAINWINDOW);
			X = static_cast<int>(X + 5); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Enemy";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATWARLOCKPACT)
		{
			Graphic = UIManager->GetGraphicData("FeatTextWarlockPact", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Warlock";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextWarlockPact2", MULTIFEATWINDOW);
			X = static_cast<int>(X + 15); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Pact";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATDRAGONBORNBONUS)
		{
			Graphic = UIManager->GetGraphicData("FeatTextDragonborn", MULTIFEATWINDOW);
			X = static_cast<int>((Graphic->BaseLocationX + 100.0*i));
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Dragonborn";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextBonusFeat", MULTIFEATWINDOW);
			X = static_cast<int>(X-5); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Bonus Feat";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATMONKPATH)
		{
			Graphic = UIManager->GetGraphicData("FeatTextMonk", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Monk";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextPath", MULTIFEATWINDOW);
			X = static_cast<int>(X + 4); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Path";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATHALFELFBONUS)
		{
			Graphic = UIManager->GetGraphicData("FeatTextHalfElf", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Half-Elf";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextDilettante", MULTIFEATWINDOW);
			X = static_cast<int>(X - 7); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Dilettante";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATDRUIDWILDSHAPE)
		{
			Graphic = UIManager->GetGraphicData("FeatTextDruid", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Druid";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextWildShape", MULTIFEATWINDOW);
			X = static_cast<int>(X - 13); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Wild Shape";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATDESTINY)
		{
			Graphic = UIManager->GetGraphicData("FeatTextEpic", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Epic";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextDestiny", MULTIFEATWINDOW);
			X = static_cast<int>(X - 13); // CDE: Keep second word aligned below
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Destiny";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}
		if (FeatSlot[i] == FEATLEGENDARY)
		{
			Graphic = UIManager->GetGraphicData("FeatTextLegendary", MULTIFEATWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX + 100.0*i);
			Y = static_cast<int>(FrameBottom - 35);
			OutputString = "Legendary";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("FeatTextLegendaryFeat", MULTIFEATWINDOW);
			X = static_cast<int>(X + 20);
			Y = static_cast<int>(FrameBottom - 20);
			OutputString = "Feat";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
		}

		SetTextColor(hdc, OldColor);

	}
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::FillSelectedPanel()
{
	int Index;
	int FeatIndex;
	int LastFeatIndex;
	int ParentHeadingIndex;
	bool Used;
	string ParentHeading;
	vector <string> UsedParentHeadings;
	ParentHeadingStruct NewParentHeading;
	vector <string> OldParentHeading;
	vector <bool> OldParentCollapse;
	FeatDataClass *Feat;

	//before we start, save the parent headings
	for (unsigned int i = 0; i<FeatListParentHeading.size(); i++)
	{
		OldParentHeading.push_back(FeatListParentHeading[i].ParentHeading);
		OldParentCollapse.push_back(FeatListParentHeading[i].Collapsed);
	}
	FeatListParentHeading.clear();

	Index = 0;
	UsedParentHeadings.clear();
	SendMessage(SelectedPanelList, LB_RESETCONTENT, 0, 0);
	FeatIndex = Character.GetFeat(CurrentSelectedLevel, Index);
	while (FeatIndex != -1)
	{
		LastFeatIndex = FeatIndex;
		Feat = Data.GetFeatPointer(FeatIndex);
		//do not display Parent Feats that only control derived feats (like Simple Weapon Proficiency)
		if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
		{
			Index++;
			FeatIndex = Character.GetFeat(CurrentSelectedLevel, Index);
			continue;
		}

		ParentHeading = Feat->GetFeatParentHeading();
		if (ParentHeading != "")
		{
			//find the parentheading index, or create it if not found
			ParentHeadingIndex = -1;
			for (unsigned int i = 0; i<FeatListParentHeading.size(); i++)
			{
				if (FeatListParentHeading[i].ParentHeading == ParentHeading)
				{
					ParentHeadingIndex = i;
					break;
				}
			}
			if (ParentHeadingIndex == -1)
			{
				FeatListParentHeading.push_back(NewParentHeading);
				ParentHeadingIndex = FeatListParentHeading.size() - 1;
				FeatListParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
				FeatListParentHeading[ParentHeadingIndex].Collapsed = false;
				for (unsigned int j = 0; j<OldParentHeading.size(); j++)
				{
					if (FeatListParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
					{
						FeatListParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
						break;
					}
				}
			}
			Used = false;
			for (unsigned int i = 0; i<UsedParentHeadings.size(); i++)
			{
				if (UsedParentHeadings[i] == ParentHeading)
				{
					Used = true;
					break;
				}
			}
			if (Used == false)
			{
				FeatListParentHeading[ParentHeadingIndex].ListIndex = SendMessage(SelectedPanelList, LB_ADDSTRING, 0, 999999);
				UsedParentHeadings.push_back(ParentHeading);
			}
		}
		if (ParentHeading == "")
			SendMessage(SelectedPanelList, LB_ADDSTRING, 0, FeatIndex);
		else
		{
			if (FeatListParentHeading[ParentHeadingIndex].Collapsed == false)
			{
				SendMessage(SelectedPanelList, LB_ADDSTRING, 0, FeatIndex + 1000000);
			}
		}
		while (FeatIndex == LastFeatIndex)
		{
		Index++;
		FeatIndex = Character.GetFeat(CurrentSelectedLevel, Index);
		}

	}
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::AddFeatWishListItem(int FeatIndex)
{
	HDC hdc;
	if(Character.HasFeat(CurrentSelectedLevel,FeatIndex))
	{
		Character.RemoveFeat(FeatIndex);
		hdc = GetDC(MultiFeatHandle);
		DrawSelectPanel(hdc);
		ReleaseDC(MultiFeatHandle, hdc);

	}
	
	unsigned int Index1, Index2, CurrentFeatIndex;
	FeatWishList.push_back(FeatIndex);
	//make the list entries unique, then sort it
	Index1 = 0;
	while (Index1 < FeatWishList.size())
	{
		CurrentFeatIndex = FeatWishList[Index1];
		Index2 = Index1 + 1;
		while (Index2 < FeatWishList.size())
		{
			if (FeatWishList[Index2] == CurrentFeatIndex)
				FeatWishList.erase(FeatWishList.begin() + Index2);
			else
				Index2++;
		}
		Index1++;
	}
	sort(FeatWishList.begin(), FeatWishList.end());
	FillFeatWishPanel();
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::RemoveFeatWishListItem(int FeatIndex)
{
	unsigned int Index1;
	Index1 = 0;
	if (FeatWishList.size() == 0)
		return;
	while (Index1 < FeatWishList.size())
	{
		if (FeatWishList[Index1] == FeatIndex)
			FeatWishList.erase(FeatWishList.begin() + Index1);
		Index1++;
	}
	FillFeatWishPanel();
}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::FillFeatSelectPanel()
{

	int FeatIndex;
	RACE CurrentRace;
	CLASS CurrentClass;
	vector <unsigned int> FeatVector;
	FEATSLOTTYPE F1, F2, F3;
	unsigned int Index1, Index2;
	unsigned int CurrentFeatIndex;
	int ClassLevel[NUMCLASSES];
	int ParentHeadingIndex;
	bool Used;
	string ParentHeading;
	vector <string> UsedParentHeadings;
	ParentHeadingStruct NewParentHeading;
	vector <string> OldParentHeading;
	vector <bool> OldParentCollapse;
	FeatDataClass *Feat;

	//before we start, save the parent heading settings so that we can restore them again
	for (unsigned int i = 0; i<FeatListSelectParentHeading.size(); i++)
	{
		OldParentHeading.push_back(FeatListSelectParentHeading[i].ParentHeading);
		OldParentCollapse.push_back(FeatListSelectParentHeading[i].Collapsed);
	}
	FeatListSelectParentHeading.clear();

	//figure out what slots are available to the player
	CurrentRace = Character.GetRace();
	CurrentClass = Character.GetClass(CurrentSelectedLevel);
	Character.DetermineFeatSlots(CurrentSelectedLevel, &F1, &F2, &F3);

	//get all the feats that are race related
	FeatVector.clear();
	SendMessage(FeatListPanelList, LB_RESETCONTENT, 0, 0);
	FeatIndex = Data.GetRaceFeat(CurrentRace, CurrentSelectedLevel, 0);
	while (FeatIndex != -1)
	{
		Feat = Data.GetFeatPointer(FeatIndex);
		//don't show feats tagged as past life here
		if (Feat->GetFeatTag(FEATTAGPASTLIFE) == false)
		{
			if (Character.HasFeat(CurrentSelectedLevel, FeatIndex) == false && Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_DISQUALIFY)
			{
				//exclude feats that are particular to a slot type if that slot type is not up
				if (Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true)
				{
					if (F1 == FEATHALFELFBONUS || F2 == FEATHALFELFBONUS || F3 == FEATHALFELFBONUS)
						FeatVector.push_back(FeatIndex);
				}
				if (Feat->GetFeatTag(FEATTAGDESTINY) == true)
				{
					if (F1 == FEATDESTINY || F2 == FEATDESTINY || F3 == FEATDESTINY)
						FeatVector.push_back(FeatIndex);
				}
				if (Feat->GetFeatTag(FEATTAGLEGENDARY) == true)
				{
					if (F1 == FEATLEGENDARY || F2 == FEATLEGENDARY || F3 == FEATLEGENDARY)
						FeatVector.push_back(FeatIndex);
				}
				if (Feat->GetFeatTag(FEATTAGDRAGONBORNBONUS) == true)
				{
					if (F1 == FEATDRAGONBORNBONUS || F2 == FEATDRAGONBORNBONUS || F3 == FEATDRAGONBORNBONUS)
						FeatVector.push_back(FeatIndex);
				}
				else
					FeatVector.push_back(FeatIndex);
			}
			else if (Feat->GetFeatTag(FEATTAGMULTIPLE) == true)
				FeatVector.push_back(FeatIndex);
		}
		FeatIndex = Data.GetRaceFeat(CurrentRace, CurrentSelectedLevel, FeatIndex + 1);
	}

	//get all the feats that are class related
	for (unsigned int i = 0; i<NUMCLASSES; i++)
		ClassLevel[i] = Character.GetClassLevel((CLASS)i, CurrentSelectedLevel);
	for (unsigned int i = 0; i<NUMCLASSES; i++)
	{
		if (ClassLevel[i] == 0)
			continue;
		FeatIndex = Data.GetClassFeat((CLASS)i, CurrentSelectedLevel, 0);
		while (FeatIndex != -1)
		{
			Feat = Data.GetFeatPointer(FeatIndex);
			if (Character.HasFeat(CurrentSelectedLevel, FeatIndex) == false && Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_DISQUALIFY)
			{
				//exclude feats that are particular to a slot type if that slot type is not up
				if (Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
				{
					if (F1 == FEATRANGERFAVOREDENEMY || F2 == FEATRANGERFAVOREDENEMY || F3 == FEATRANGERFAVOREDENEMY)
						FeatVector.push_back(FeatIndex);
				}
				else if (Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
				{
					if (F1 == FEATROGUEBONUS || F2 == FEATROGUEBONUS || F3 == FEATROGUEBONUS)
						FeatVector.push_back(FeatIndex);
				}
				else if (Feat->GetFeatTag(FEATTAGMONKPATH) == true)
				{
					if (F1 == FEATMONKPATH || F2 == FEATMONKPATH || F3 == FEATMONKPATH)
						FeatVector.push_back(FeatIndex);
				}
				else if (Feat->GetFeatTag(FEATTAGDEITY) == true)
				{
					if (F1 == FEATDEITY || F2 == FEATDEITY || F3 == FEATDEITY)
						FeatVector.push_back(FeatIndex);
				}
				else if (Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true)
				{
					if (F1 == FEATFAVOREDSOULBONUS || F2 == FEATFAVOREDSOULBONUS || F3 == FEATFAVOREDSOULBONUS)
						FeatVector.push_back(FeatIndex);
				}
				else if (Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true)
				{
					if (F1 == FEATMONKBONUS || F2 == FEATMONKBONUS || F3 == FEATMONKBONUS)
						FeatVector.push_back(FeatIndex);
				}
				if (Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true)
				{
					if (F1 == FEATDRUIDWILDSHAPE || F2 == FEATDRUIDWILDSHAPE || F3 == FEATDRUIDWILDSHAPE)
						FeatVector.push_back(FeatIndex);
				}
				if (Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true)
				{
					if (F1 == FEATWARLOCKPACT || F2 == FEATWARLOCKPACT || F3 == FEATWARLOCKPACT)
						FeatVector.push_back(FeatIndex);
				}
				else
					FeatVector.push_back(FeatIndex);
			}
			else if (Feat->GetFeatTag(FEATTAGMULTIPLE) == true && Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_DISQUALIFY)
			{
				if (Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
				{
					if (F1 == FEATRANGERFAVOREDENEMY || F2 == FEATRANGERFAVOREDENEMY || F3 == FEATRANGERFAVOREDENEMY)
						FeatVector.push_back(FeatIndex);
				}
				else if (Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
				{
					if (F1 == FEATROGUEBONUS || F2 == FEATROGUEBONUS || F3 == FEATROGUEBONUS)
						FeatVector.push_back(FeatIndex);
				}
				else
					FeatVector.push_back(FeatIndex);
			}
			FeatIndex = Data.GetClassFeat((CLASS)i, CurrentSelectedLevel, FeatIndex + 1);
		}
	}

	//make the list entries unique, then sort it
	Index1 = 0;
	while (Index1 < FeatVector.size())
	{
		CurrentFeatIndex = FeatVector[Index1];
		Index2 = Index1 + 1;
		while (Index2 < FeatVector.size())
		{
			if (FeatVector[Index2] == CurrentFeatIndex)
				FeatVector.erase(FeatVector.begin() + Index2);
			else
				Index2++;
		}
		Index1++;
	}
	sort(FeatVector.begin(), FeatVector.end());

	//add the list to the listbox
	for (unsigned int i = 0; i<FeatVector.size(); i++)
	{
		Feat = Data.GetFeatPointer(FeatVector[i]);
		ParentHeading = Feat->GetFeatParentHeading();
		if (ParentHeading != "")
		{
			//find the parentheading index, or create it if not found
			ParentHeadingIndex = -1;
			for (unsigned int i = 0; i<FeatListSelectParentHeading.size(); i++)
			{
				if (FeatListSelectParentHeading[i].ParentHeading == ParentHeading)
				{
					ParentHeadingIndex = i;
					break;
				}
			}
			if (ParentHeadingIndex == -1)
			{
				FeatListSelectParentHeading.push_back(NewParentHeading);
				ParentHeadingIndex = FeatListSelectParentHeading.size() - 1;
				FeatListSelectParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
				FeatListSelectParentHeading[ParentHeadingIndex].Collapsed = false;
				for (unsigned int j = 0; j<OldParentHeading.size(); j++)
				{
					if (FeatListSelectParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
					{
						FeatListSelectParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
						break;
					}
				}
			}
			Used = false;
			for (unsigned int i = 0; i<UsedParentHeadings.size(); i++)
			{
				if (UsedParentHeadings[i] == ParentHeading)
				{
					Used = true;
					break;
				}
			}
			if (Used == false)
			{
				FeatListSelectParentHeading[ParentHeadingIndex].ListIndex = SendMessage(FeatListPanelList, LB_ADDSTRING, 0, 999999);
				UsedParentHeadings.push_back(ParentHeading);
			}
		}
		if (ParentHeading == "")
			SendMessage(FeatListPanelList, LB_ADDSTRING, 0, FeatVector[i]);
		else
		{
			if (FeatListSelectParentHeading[ParentHeadingIndex].Collapsed == false)
			{
				SendMessage(FeatListPanelList, LB_ADDSTRING, 0, FeatVector[i] + 1000000);
			}
		}
	}

}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::FillFeatWishPanel()
{
	unsigned int index;
	index = 0;
	SendMessage(FeatWishPanelList, LB_RESETCONTENT, 0, 0);
	if (FeatWishList.size() != 0)
	{
		while (index < FeatWishList.size())
		{
			
			SendMessage(FeatWishPanelList, LB_ADDSTRING, 0, FeatWishList[index]);

			index++;
		}


	}


}
//-------------------------------------------------------------------------
void MultiFeatWindowClass::fillDescPanel(string Description, HBITMAP Bitmap)
{
	EDITSTREAM Stream;
	SendMessage(DescPanel, LB_RESETCONTENT, 0, 0);
	Stream.dwCookie = (DWORD)Description.c_str();
	Stream.dwError = false;
	Stream.pfnCallback = EditStreamCallback;
	SendMessage(DescPanel, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);

	//test the rich edit box graphics drawer
	if (Bitmap != NULL)
		RichEditBitmap.InsertBitmap(DescPanel, Bitmap);
}
//-------------------------------------------------------------------------
HWND MultiFeatWindowClass::GetHandle()
{
	return MultiFeatHandle;
}
void MultiFeatWindowClass::SetIcons(vector <GraphicStruct> MainFeatIcons)
{
	FeatIcon = MainFeatIcons;
	return;
}
void MultiFeatWindowClass::DeleteGraphics()
{

	DeleteObject(TitleFontLarge);
	DeleteObject(PlusBox.Graphic);
	DeleteObject(MinusBox.Graphic);
	DeleteObject(BlueLevelBox.Graphic);
	DeleteObject(GreenLevelBox.Graphic);
	DeleteObject(RedLevelBox.Graphic);
	DeleteObject(GreyLevelBox.Graphic);
	DeleteObject(YellowLevelBox.Graphic);
	DeleteObject(EmptyFeatSlot.Graphic);
	DeleteObject(PlusBox.Mask);
	DeleteObject(MinusBox.Mask);
	DeleteObject(BlueLevelBox.Mask);
	DeleteObject(GreenLevelBox.Mask);
	DeleteObject(RedLevelBox.Mask);
	DeleteObject(GreyLevelBox.Mask);
	DeleteObject(YellowLevelBox.Mask);
	DeleteObject(EmptyFeatSlot.Mask);

	DeleteObject(Palette);
	for (unsigned int i = 0; i<FeatIcon.size(); i++)
	{
		DeleteObject(FeatIcon[i].Graphic);
		DeleteObject(FeatIcon[i].Mask);
	}





}

