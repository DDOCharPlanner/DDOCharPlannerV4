#include "PrintWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"

//---------------------------------------------------------------------------
PrintWindowClass::PrintWindowClass()
	{
	}

//---------------------------------------------------------------------------
PrintWindowClass::~PrintWindowClass()
	{
    DeleteObject(TitleFontLarge);
	}

//---------------------------------------------------------------------------
void PrintWindowClass::Create(HINSTANCE Instance, HWND Parent)
	{
    WNDCLASSEX wc;
    int ScreenX;
    int ScreenY;
    RECT WindowRect;
    int WindowX;
    int WindowY;
    static char WindowName[] = "Print Window";
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
    PrintWindowHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 400, 300, Parent, NULL, Instance, NULL);
    SetClassLong(PrintWindowHandle, 0, (long)PRINTWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(PrintWindowHandle, &WindowRect);
    WindowX = WindowRect.right - WindowRect.left;
    WindowY = WindowRect.bottom - WindowRect.top;
    SetWindowPos(PrintWindowHandle, Parent, (ScreenX/2)-(WindowX/2), (int)(ScreenY/2.5)-(WindowY/2), 400, 300, SWP_NOSIZE);

    //the child windows
	PrintLabel = CreateWindowEx(NULL, "STATIC", "CHARACTER PRINT", WS_CHILD, 15, 10, 300, 20, PrintWindowHandle, (HMENU)PW_PRINTLABEL, Instance, NULL);
    PrintButton = CreateWindowEx(NULL, "BUTTON", "Print", WS_CHILD | BS_PUSHBUTTON, 129, 262, 50, 25, PrintWindowHandle, (HMENU)PW_PRINTBUTTON, Instance, NULL);
    CancelButton = CreateWindowEx(NULL, "BUTTON", "Cancel", WS_CHILD | BS_PUSHBUTTON, 209, 262, 50, 25, PrintWindowHandle, (HMENU)PW_CANCELBUTTON, Instance, NULL);

    PrintSnapshotCheckBox = CreateWindowEx(NULL, "BUTTON", "Print Snapshot", WS_CHILD | BS_AUTOCHECKBOX, 20, 40, 150, 20, PrintWindowHandle, (HMENU)PW_PRINTSNAPSHOTCHECKBOX, Instance, NULL);
	SnapshotLevelSelectLabel = CreateWindowEx(NULL, "STATIC", "Snapshot At Level: ", WS_CHILD, 170, 40, 150, 20, PrintWindowHandle, (HMENU)PW_SNAPSHOTLEVELSELECTLABEL, Instance, NULL);
    PrintLevelGuideCheckBox = CreateWindowEx(NULL, "BUTTON", "Print Level Guide", WS_CHILD | BS_AUTOCHECKBOX, 20, 120, 145, 20, PrintWindowHandle, (HMENU)PW_PRINTLEVELGUIDECHECKBOX, Instance, NULL);
	LevelGuideLevelSelectLowLabel = CreateWindowEx(NULL, "STATIC", "Start: ", WS_CHILD, 230, 180, 150, 20, PrintWindowHandle, (HMENU)PW_LEVELGUILDLEVELSELECTLOWLABEL, Instance, NULL);
	LevelGuideLevelSelectHighLabel = CreateWindowEx(NULL, "STATIC", "End: ", WS_CHILD, 230, 210, 150, 20, PrintWindowHandle, (HMENU)PW_LEVELGUILDLEVELSELECTHIGHLABEL, Instance, NULL);

	//Radio buttons for choosing which type of items to build.
	SnapshotMaxLevelRadio = CreateWindowEx(NULL, "BUTTON", "Max Level", WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 165, 65, 120, 20, PrintWindowHandle, (HMENU)PW_PRINTSNAPSHOTMAXLEVELRADIOBUTTON, Instance, NULL);
	SnapshotOtherLevelRadio = CreateWindowEx(NULL, "BUTTON", "Other Level", WS_CHILD | BS_AUTORADIOBUTTON, 165, 90, 95, 20, PrintWindowHandle, (HMENU)PW_PRINTSNAPSHOTOTHERLEVELRADIOBUTTON, Instance, NULL);
	LevelGuideDefaultRadio = CreateWindowEx(NULL, "BUTTON", "Default Levels", WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 165, 130, 160, 20, PrintWindowHandle, (HMENU)PW_PRINTLEVELGUIDEDEFAULTLEVELSRADIOBUTTON, Instance, NULL);
	LevelGuideOtherRadio = CreateWindowEx(NULL, "BUTTON", "Other Levels", WS_CHILD | BS_AUTORADIOBUTTON, 165, 155, 95, 20, PrintWindowHandle, (HMENU)PW_PRINTLEVELGUIDEOTHERLEVELSRADIOBUTTON, Instance, NULL);

	SnapshotOtherLevelInputBox = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_BORDER | ES_NUMBER, 275, 90, 40, 20, PrintWindowHandle, (HMENU)PW_PRINTSNAPSHOTOTHERLEVELINPUTBOX, Instance, NULL);
	LevelGuideOtherLevelLowInputBox = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_BORDER | ES_NUMBER, 275, 180, 40, 20, PrintWindowHandle, (HMENU)PW_PRINTLEVELGUIDEOTHERLEVELLOWINPUTBOX, Instance, NULL);
	LevelGuideOtherLevelHighInputBox = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_BORDER | ES_NUMBER, 275, 210, 40, 20, PrintWindowHandle, (HMENU)PW_PRINTLEVELGUIDEOTHERLEVELHIGHINPUTBOX, Instance, NULL);

    GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);

    SendMessage(PrintSnapshotCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(PrintLevelGuideCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(SnapshotMaxLevelRadio, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(LevelGuideDefaultRadio, BM_SETCHECK, BST_CHECKED, 0);

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
	StringCbCopy (lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	TitleFontLarge = CreateFontIndirect(&lf);
	}

//---------------------------------------------------------------------------
void PrintWindowClass::Show(bool State)
	{
	ostringstream Text;

    //pop it up
    ShowWindow(PrintWindowHandle, State);
    ShowWindow(PrintLabel, State);
    ShowWindow(PrintButton, State);
    ShowWindow(CancelButton, State);
    ShowWindow(PrintSnapshotCheckBox, State);
    ShowWindow(SnapshotLevelSelectLabel, State);
    ShowWindow(PrintLevelGuideCheckBox, State);
    ShowWindow(LevelGuideLevelSelectLowLabel, State);
    ShowWindow(LevelGuideLevelSelectHighLabel, State);
    ShowWindow(SnapshotMaxLevelRadio, State);
    ShowWindow(SnapshotOtherLevelRadio, State);
	ShowWindow(SnapshotOtherLevelInputBox, State);
    ShowWindow(LevelGuideDefaultRadio, State);
	ShowWindow(LevelGuideOtherRadio, State);
	ShowWindow(LevelGuideOtherLevelLowInputBox, State);
	ShowWindow(LevelGuideOtherLevelHighInputBox, State);

	//reset the max level label text
    SendMessage(PrintLabel, WM_SETFONT, (WPARAM)TitleFontLarge, 0);
	Text << "Max Level (" << Character.GetHighestBuildLevel() << ")";
    SendMessage(SnapshotMaxLevelRadio, WM_SETTEXT, 0, (LPARAM)Text.str().c_str());
	Text.str("");
	Text << "Default Levels (1-" << Character.GetHighestBuildLevel() << ")";
    SendMessage(LevelGuideDefaultRadio, WM_SETTEXT, 0, (LPARAM)Text.str().c_str());


	//Center in Window

	int ParentX;
	int ParentY;

	RECT WindowRect;
	RECT ParentRect;
	int WindowX;
	int WindowY;
	HWND ParentWindow;
	ParentWindow = InterfaceManager.ControlWindow.GetControlWindowHandle();
	GetWindowRect(ParentWindow, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top;

	GetWindowRect(PrintWindowHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(PrintWindowHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2), 0, 0, SWP_NOSIZE);

	}

//---------------------------------------------------------------------------
long PrintWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
    switch (Message)
        {
        case WM_COMMAND:
            {
            if (HIWORD(wParam) == BN_CLICKED)
                {
                if ((int)LOWORD(wParam) == PW_CANCELBUTTON)
                    {
                    InterfaceManager.ShowChild(PRINTWINDOW, false);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == PW_PRINTBUTTON)
                    {
                    Print();
                    InterfaceManager.ShowChild(PRINTWINDOW, false);
                    return 0;
                    }
                }
            if ((int)HIWORD(wParam) == EN_CHANGE)
				{
				if ((int)LOWORD(wParam) == PW_PRINTSNAPSHOTOTHERLEVELINPUTBOX)
					{
				    SendMessage(PrintSnapshotCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				    SendMessage(SnapshotMaxLevelRadio, BM_SETCHECK, BST_UNCHECKED, 0);
				    SendMessage(SnapshotOtherLevelRadio, BM_SETCHECK, BST_CHECKED, 0);
					}
				if ((int)LOWORD(wParam) == PW_PRINTLEVELGUIDEOTHERLEVELLOWINPUTBOX || (int)LOWORD(wParam) == PW_PRINTLEVELGUIDEOTHERLEVELHIGHINPUTBOX)
					{
				    SendMessage(PrintLevelGuideCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				    SendMessage(LevelGuideDefaultRadio, BM_SETCHECK, BST_UNCHECKED, 0);
				    SendMessage(LevelGuideOtherRadio, BM_SETCHECK, BST_CHECKED, 0);
					}
				}
            }
        case WM_CTLCOLORSTATIC:
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            SetTextColor((HDC)wParam, RGB(255,255,255));
            return (long)GetStockObject(DKGRAY_BRUSH);
            }
        default:
            {
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
		}
	}

//---------------------------------------------------------------------------
void PrintWindowClass::Print()
	{
	PRINTDLG PrintDialog;
	unsigned int MaxLevel;
	unsigned int SnapshotLevel;
	unsigned int LevelGuideLow;
	unsigned int LevelGuideHigh;
	int Length;
	char SnapshotLevelString[5];
	char LevelGuideLevelString[5];
	stringstream ss;
	bool PrintSnapshot;
	bool PrintLevelGuide;

	//get user preferences
    ZeroMemory(&PrintDialog, sizeof(PrintDialog));
	PrintDialog.lStructSize = sizeof(PRINTDLG);
	PrintDialog.hwndOwner = PrintWindowHandle;
	PrintDialog.hDevMode = NULL;
	PrintDialog.hDevNames = NULL;
	PrintDialog.hDC = NULL;
	PrintDialog.Flags = PD_ALLPAGES | PD_RETURNDC;
	PrintDialog.nFromPage = 1;
	PrintDialog.nToPage = 2;
	PrintDialog.nMinPage = 1;
	PrintDialog.nMaxPage = 1;
	PrintDialog.nCopies = 1;
	PrintDialog.hInstance = NULL;
	PrintDialog.lCustData = 0;
	PrintDialog.lpfnSetupHook = NULL;
	PrintDialog.lpPrintTemplateName = NULL;
	PrintDialog.lpSetupTemplateName = NULL;
	PrintDialog.hPrintTemplate = NULL;
	PrintDialog.hSetupTemplate = NULL;

	if (PrintDlg(&PrintDialog) == false)
		return;

	MaxLevel = Character.GetHighestBuildLevel();
	if (SendMessage(SnapshotMaxLevelRadio, BM_GETCHECK, 0, 0) == BST_CHECKED)
		SnapshotLevel = MaxLevel;
	else
		{
        *(LPWORD)SnapshotLevelString = 5;
		Length = (int)SendMessage(SnapshotOtherLevelInputBox, EM_GETLINE, 0, (LPARAM)(LPCSTR)SnapshotLevelString);
		SnapshotLevelString[Length] = '\0';
		ss << SnapshotLevelString;
		ss >> SnapshotLevel;
		if (SnapshotLevel < 1)
			SnapshotLevel = 1;
		if (SnapshotLevel > MaxLevel)
			SnapshotLevel = MaxLevel;
		}

	if (SendMessage(LevelGuideDefaultRadio, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		LevelGuideLow = 1;
		LevelGuideHigh = MaxLevel;
		}
	else
		{
		ss.str("");
		ss.clear();
        *(LPWORD)LevelGuideLevelString = 5;
		Length = (int)SendMessage(LevelGuideOtherLevelLowInputBox, EM_GETLINE, 0, (LPARAM)(LPCSTR)LevelGuideLevelString);
		LevelGuideLevelString[Length] = '\0';
		ss << LevelGuideLevelString;
		ss >> LevelGuideLow;
		if (LevelGuideLow < 1)
			LevelGuideLow = 1;
		if (LevelGuideLow > MaxLevel)
			LevelGuideLow = MaxLevel;

		ss.str("");
		ss.clear();
        *(LPWORD)LevelGuideLevelString = 5;
		Length = (int)SendMessage(LevelGuideOtherLevelHighInputBox, EM_GETLINE, 0, (LPARAM)(LPCSTR)LevelGuideLevelString);
		LevelGuideLevelString[Length] = '\0';
		ss << LevelGuideLevelString;
		ss >> LevelGuideHigh;
		if (LevelGuideHigh < 1)
			LevelGuideHigh = MaxLevel;
		if (LevelGuideHigh < LevelGuideLow)
			LevelGuideHigh = LevelGuideLow;
		if (LevelGuideHigh > MaxLevel)
			LevelGuideHigh = MaxLevel;
		}

	PrintSnapshot = false;
	PrintLevelGuide = false;

	if (SendMessage(PrintSnapshotCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		PrintSnapshot = true;

	if (SendMessage(PrintLevelGuideCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		PrintLevelGuide = true;

	Printer.Print(PrintDialog.hDC, SnapshotLevel, LevelGuideLow, LevelGuideHigh, PrintSnapshot, PrintLevelGuide);

	DeleteDC(PrintDialog.hDC);
	}
	HWND PrintWindowClass::GetHandle()
	{
		return PrintWindowHandle;
	}
