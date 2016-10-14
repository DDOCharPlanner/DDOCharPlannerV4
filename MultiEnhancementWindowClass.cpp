#include "MultiEnhancementWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "DataClass.h"

//---------------------------------------------------------------------------
MultiEnhancementWindowClass::MultiEnhancementWindowClass()
	{
	IconLeft = 30;
	IconTop = 20;
	Spacer = 15;
	IconWidth = 36;
	IconHeight = 36;
	ToolTipEnhancement = nullptr;
	}

//---------------------------------------------------------------------------
MultiEnhancementWindowClass::~MultiEnhancementWindowClass()
	{
	DeleteGraphics();
	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::Create(HINSTANCE Instance, HWND Parent)
	{
	WNDCLASSEX wc;
	int ScreenX;
	int ScreenY;
	RECT WindowRect;
	RECT ParentRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Multi Enhancement Window";

	ParentWindow = Parent;	//this is used for later
	
	//Fill in the class attributes for the Window
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

	//register the window
	RegisterClassEx(&wc);

	//create and place the window Multi Enhancement Window
	MultiEnhancementWindowHandle = CreateWindowEx (WS_EX_TOPMOST, WindowName, WindowName, WS_POPUP | WS_DLGFRAME, 200, 100, 225, 100, Parent, NULL, Instance, NULL);
	SetClassLong(MultiEnhancementWindowHandle, 0, (long)MULTIENHANCEMENTWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(Parent, &ParentRect);
	GetWindowRect(MultiEnhancementWindowHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiEnhancementWindowHandle, Parent, (ScreenX/2)-(WindowX/2), (ScreenY/2)-(WindowY/2), 0, 0, SWP_NOSIZE);

	//the child windows
	MultiEnhanceAcceptHandle = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD, 30, 70, 60, 20, MultiEnhancementWindowHandle, (HMENU)MEW_ACCEPTBUTTON, Instance, NULL);
	MultiEnhanceCancelHandle = CreateWindowEx(NULL, "BUTTON", "Cancel", WS_CHILD, 130, 70, 60, 20, MultiEnhancementWindowHandle, (HMENU)MEW_CANCELBUTTON, Instance, NULL);
	MultiSelectionFrameHandle = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_WHITEFRAME, 10, 10, 45, 45, MultiEnhancementWindowHandle, (HMENU)MEW_SELECTIONFRAME, Instance, NULL);

	LoadGraphics(Parent);
	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::Show(bool State)
	{
	ShowWindow(MultiEnhancementWindowHandle, State);
	ShowWindow(MultiEnhanceAcceptHandle, State);
	ShowWindow(MultiEnhanceCancelHandle, State);
	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::ActivateMultiEnhancementWindow(int Tree, int Level, int Slot, int AvailableAP)
	{
	int ParentX;
	int ParentY;
	RECT WindowRect;
	RECT ParentRect;
	int WindowX;
	int WindowY;

	CurrentTree = Tree;
	CurrentLevel = Level;
	CurrentSlot = Slot;
	APAvailable = AvailableAP;
	Selection = 0;

	EnhancementWindow = InterfaceManager.GetEnhancementWindowPointer();
	CurrentStartingTree = EnhancementWindow->GetCurrentStartingTree();
	Num_Slots = EnhancementWindow->GetCurrentTreeSlotsEnhancementIndexSize(Tree, Level, Slot);

	//ok lets resize our window to fit the Enhancements
	GetWindowRect(ParentWindow, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top;
	GetWindowRect(MultiEnhancementWindowHandle, &WindowRect);
	if (Num_Slots > 4)
		WindowX = (IconLeft + ((IconWidth+Spacer)*(Num_Slots-1)));
	else 
		WindowX = 245;
	if (Num_Slots > 4)
		WindowX += (IconLeft - Spacer);
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiEnhancementWindowHandle, ParentWindow, (ParentX / 2) - (WindowX / 2)+ParentRect.left, (ParentY/ 2) - (WindowY / 2)+ParentRect.top, WindowX, 100, SWP_SHOWWINDOW);

	EnableWindow(MultiEnhanceAcceptHandle, false);
	ShowWindow(MultiSelectionFrameHandle, false);
	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::DeleteGraphics()
	{
	DeleteObject(IconPassiveBorder.Graphic);
    DeleteObject(IconPassiveBorder.Mask);
	DeleteObject(IconActiveBorder.Graphic);
	DeleteObject(IconActiveBorder.Mask);
	DeleteObject(IconActiveNotAvailable.Graphic);
	DeleteObject(IconActiveNotAvailable.Mask);
	DeleteObject(IconPassiveNotAvailable.Graphic);
	DeleteObject(IconPassiveNotAvailable.Mask);

    DeleteObject(Palette);
	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::DrawGraphics(HDC hdc)
	{
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_Tree_Class *EnhancementTree;
	GraphicStruct TempGraphic;
	ENHANCEMENT_TREE ENHTTree;
	unsigned int EnhancementIndex;
	GraphicStruct BorderGraphic;
	GraphicStruct NotAvailableGraphic;
	bool RequirementsMet;
	EnhancementSlotStruct *EnhancementSlotData;

	ENHTTree = EnhancementWindow->GetCurrentTreeEnhancementTree(CurrentTree);
	EnhancementSlotData = EnhancementWindow->GetEnhancementSlotData(CurrentTree, CurrentLevel, CurrentSlot);	
	EnhancementTree = Data.GetEnhancementTreePointer(ENHTTree);
	for (unsigned int i=1; i<Num_Slots; i++)
		{
		EnhancementIndex = EnhancementWindow->GetCurrentTreeSlotsEnhancementIndex(CurrentTree, CurrentLevel, CurrentSlot, i);
		Enhancement = EnhancementTree->GetEnhancementPointer(EnhancementIndex);

		//Show our selected Frame if an enhancement has been chosen.
		if (i == Selection)
			{
			MoveWindow(MultiSelectionFrameHandle, (IconLeft + ((IconWidth + Spacer)*(i-1)))-5, IconTop -5, 45, 45, true);
			ShowWindow(MultiSelectionFrameHandle, true);
			}
		//Let set if requirements are met for this enhancement.
		RequirementsMet = AreAllRequirementsMet(Enhancement);

		//Lets see if our enhancement is locked out
		if (IsEnhancementLocked(Enhancement) == true)
			RequirementsMet = false;

		//Set our Icon border to Active or Passive
		if (Enhancement->GetEnhTypeActive() == false)
			{
			BorderGraphic = IconPassiveBorder;
			NotAvailableGraphic = IconPassiveNotAvailable;
			}
		else 
			{
			BorderGraphic = IconActiveBorder;
			NotAvailableGraphic = IconActiveNotAvailable;
			}
		//Lets draw our icons and borders based on location
		TempGraphic = Enhancement->GetEnhancementIcon();
		if (i == 1)
			{
			DrawGraphic(hdc, &TempGraphic, IconLeft, IconTop, IconWidth, IconHeight);
			DrawGraphic(hdc, &BorderGraphic, IconLeft-1, IconTop-1, IconWidth, IconHeight);
			if (!RequirementsMet)
				DrawGraphic(hdc, &NotAvailableGraphic, IconLeft-1, IconTop-1, 38, 38);
			}
		else
			{
			DrawGraphic(hdc, &TempGraphic, (IconLeft + ((IconWidth + Spacer)*(i-1))), IconTop, IconWidth, IconHeight);
			DrawGraphic(hdc, &BorderGraphic, (IconLeft + ((IconWidth + Spacer)*(i-1)))-1, IconTop-1, 38, 38);
			if (!RequirementsMet)
				DrawGraphic(hdc, &NotAvailableGraphic, (IconLeft + ((IconWidth + Spacer)*(i-1)))-1, IconTop-1, 38, 38);
			}	
		}

	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::LoadGraphics(HWND Parent)
	{
	HDC hdc;

	//palteee for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	LoadBitmap("EmptyPassiveCore", "UserInterface", &IconPassiveBorder);
	LoadBitmap("EmptyActiveCore", "UserInterface", &IconActiveBorder);
	LoadBitmap("IconActiveNotAvailable", "UserInterface", &IconActiveNotAvailable);
	LoadBitmap("IconPassiveNotAvailable", "UserInterface", &IconPassiveNotAvailable);
	}

//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::HandleLeftMouseButtonClick(unsigned int x, unsigned int y)
	{
	HDC hdc;
	ENHANCEMENT_TREE ENHTTree;
	unsigned int EnhancementIndex;
	EnhancementSlotStruct *EnhancementSlotData;
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_Tree_Class *EnhancementTree;

	EnhancementSlotData = EnhancementWindow->GetEnhancementSlotData(CurrentTree, CurrentLevel, CurrentSlot);	
	
	hdc = GetDC(MultiEnhancementWindowHandle);

	//Ok we need to see if we clicked on an enhancement
	for (unsigned int i=1; i<Num_Slots; i++)
		{
		if (x > (IconLeft + ((IconWidth + Spacer)*(i-1))) && x < ((IconLeft + ((IconWidth + Spacer)*(i-1)))+IconWidth) && y > IconTop && y < (IconTop + IconHeight))
			{
			//ok we have selected an enhancement
			EnhancementWindow = InterfaceManager.GetEnhancementWindowPointer();
			ENHTTree = EnhancementWindow->GetCurrentTreeEnhancementTree(CurrentTree);
			EnhancementTree = Data.GetEnhancementTreePointer(ENHTTree);
			EnhancementIndex = EnhancementWindow->GetCurrentTreeSlotsEnhancementIndex(CurrentTree, CurrentLevel, CurrentSlot, i);
			Enhancement = EnhancementTree->GetEnhancementPointer(EnhancementIndex);
			if (AreAllRequirementsMet(Enhancement) == true)
				{
				if (IsEnhancementLocked(Enhancement) == false)
					{
					if (APAvailable < Enhancement->GetEnhancementCost())
						{
						ReleaseDC(MultiEnhancementWindowHandle, hdc);
						return;
						}
					//ok our selection is valid
					Selection = i;
					DrawGraphics(hdc);
					EnableWindow(MultiEnhanceAcceptHandle, true);
					}
				}
			}
		}
	ReleaseDC(MultiEnhancementWindowHandle, hdc);
	}

//---------------------------------------------------------------------------
long MultiEnhancementWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	PAINTSTRUCT ps;
	EnhancementWindowClass *EnhancementWindow;

	switch (Message)
		{
		case WM_CLOSE:
			{
			InterfaceManager.ShowChild(MULTIENHANCEMENTWINDOW, false);
			return 0;
			}
		case WM_COMMAND:
			{
			if (HIWORD(wParam) == BN_CLICKED)
				{
				if ((int)LOWORD(wParam) == MEW_ACCEPTBUTTON)
					{
					if (Selection > 0)
						{
						EnhancementWindow = InterfaceManager.GetEnhancementWindowPointer();
						EnhancementWindow->MultiEnhancementSelected(CurrentTree, CurrentLevel, CurrentSlot, Selection);
						}
					InterfaceManager.ShowChild(MULTIENHANCEMENTWINDOW, false);
					InterfaceManager.SetEnhancementChildWindowFlag(false);
					return 0;
					}
				if ((int)LOWORD(wParam) == MEW_CANCELBUTTON)
					{
					InterfaceManager.ShowChild(MULTIENHANCEMENTWINDOW, false);
					InterfaceManager.SetEnhancementChildWindowFlag(false);
					return 0;
					}
				}
			return 0;
			}
		case WM_MOUSEHOVER:
			{
			HandleMouseHover(LOWORD(lParam), HIWORD(lParam));
			TrackMouseEvent(&tme);
			return 0;
			}
		case WM_MOUSEMOVE:
			{
			if (!TMEFlag)
				{
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_LEAVE | TME_HOVER;
				tme.dwHoverTime = 400;
				tme.hwndTrack = MultiEnhancementWindowHandle;
				TrackMouseEvent(&tme);
				TMEFlag = true;
				}
			return 0;
			}
		case WM_MOUSELEAVE:
			{
			ShowTooTipWindow(false);
			TMEFlag = false;
			ToolTipEnhancement = nullptr;
			return 0;
			}
		case WM_LBUTTONDOWN:
			{
			HandleLeftMouseButtonClick(LOWORD(lParam), HIWORD(lParam));
			return 0;
			}
		case WM_CTLCOLORSTATIC:
			{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(255,255,255));
			return (long)GetStockObject(DKGRAY_BRUSH);
			}
		case WM_PAINT:
			{
			BeginPaint(Wnd, &ps);
			DrawGraphics(ps.hdc);
			EndPaint(Wnd, &ps);
			return 0;
			}
		default:
			{
			return DefWindowProc(Wnd, Message, wParam, lParam);
			}
		}
	}
//-------------------------------------------------------------------------
HWND MultiEnhancementWindowClass::GetHandle()
{

		return MultiEnhancementWindowHandle;
	
}
//---------------------------------------------------------------------------
void MultiEnhancementWindowClass::HandleMouseHover(unsigned int x, unsigned int y)
	{
	int Icon;
	ostringstream ss;
	Data_Enhancement_Tree_Class *Tree;
	Data_Enhancement_Class *Enhancement;

	//determine which (if any) icon we are hovering over
	Icon = -1;
	if (y > IconTop && y < IconTop + IconHeight)
		{
		if (x > IconLeft && x < IconLeft + (Num_Slots*(IconWidth+Spacer)))
			{
			Icon = (x - IconLeft)/(IconWidth+Spacer);
			}
		//make sure we are not in between
		if (x > ((Icon+1)*(IconWidth)+(Icon*Spacer))+IconLeft)
			Icon = -1;
		}

	//what enhancement is this?
	Tree = Data.GetEnhancementTreePointer(EnhancementWindowBaseClass::CurrentTree[CurrentTree]);
	Enhancement = Tree->GetEnhancementPointer(CurrentLevel, CurrentSlot, Icon+1);

	//stop here if the slot is the same as the old slot, don't keep redrawing!
	if (Enhancement == ToolTipEnhancement)
		return;

	if (Icon != -1)
		{
		ShowTooTipWindow(true);
		SetToolTipWindow(Enhancement);
		ToolTipEnhancement = Enhancement;
		}
	else
		{
		ShowTooTipWindow(false);
		ToolTipEnhancement = nullptr;
		}	
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class* MultiEnhancementWindowClass::GetEnhancement(unsigned int Index)
	{
	Data_Enhancement_Tree_Class *Tree;
	Data_Enhancement_Class *Enhancement;

	if (Index >= Num_Slots)
		return nullptr;

	Tree = Data.GetEnhancementTreePointer(ChosenTrees[CurrentTree]);
	Enhancement = Tree->GetEnhancementPointer(CurrentLevel, CurrentSlot, Index);

	return Enhancement;
	}


