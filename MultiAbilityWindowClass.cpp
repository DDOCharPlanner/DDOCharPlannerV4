#include "PrintWindowClass.h"
#include "MultiAbilityWindowClass.h"
#include "InterfaceManagerClass.h"


//---------------------------------------------------------------------------
MultiAbilityWindowClass::MultiAbilityWindowClass()
{
}

//---------------------------------------------------------------------------
MultiAbilityWindowClass::~MultiAbilityWindowClass()
{
	DeleteObject(TitleFontLarge);
}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::Create(HINSTANCE Instance, HWND Parent)
{
	WNDCLASSEX wc;
	int ScreenX;
	int ScreenY;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Ability Window";
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
	MultiAbilityHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 600, 700, Parent, NULL, Instance, NULL);
	SetClassLong(MultiAbilityHandle, 0, (long)MULTIABILITYWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(MultiAbilityHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiAbilityHandle, Parent, (ScreenX / 2) - (WindowX / 2), (int)(ScreenY / 2) - (WindowY / 2), 400, 300, SWP_NOSIZE);

	//the child windows
	MultiAbilityLabel = CreateWindowEx(NULL, "STATIC", "Select Ability Advancement", WS_CHILD, 5, 5, 300, 20, MultiAbilityHandle, (HMENU)MAB_LABEL, Instance, NULL);
	AcceptButton = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD | BS_PUSHBUTTON, 485, 5, 50, 25, MultiAbilityHandle, (HMENU)MAB_ACCEPT, Instance, NULL);
	CancelButton = CreateWindowEx(NULL, "BUTTON", "Cancel", WS_CHILD | BS_PUSHBUTTON, 540, 5, 50, 25, MultiAbilityHandle, (HMENU)MAB_CANCEL, Instance, NULL);
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
}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::Show(bool State)
{
	ostringstream Text;

	//pop it up
	ShowWindow(MultiAbilityHandle, State);
	ShowWindow(MultiAbilityLabel, State);
	ShowWindow(AcceptButton, State);
	ShowWindow(CancelButton, State);
	EnableWindow(AcceptButton, false);

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

	GetWindowRect(MultiAbilityHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiAbilityHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2), 0, 0, SWP_NOSIZE);

}

//---------------------------------------------------------------------------
long MultiAbilityWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if ((int)LOWORD(wParam) == MAB_ACCEPT)
			{
				InterfaceManager.ShowChild(MULTIABILITYWINDOW, false);
				return 0;
			}
			if ((int)LOWORD(wParam) == MAB_CANCEL)
			{
				InterfaceManager.ShowChild(MULTIABILITYWINDOW, false);
				return 0;
			}
		}
	}
	case WM_CTLCOLORSTATIC:
	{
		//SetBkMode((HDC)wParam, TRANSPARENT);
		//SetTextColor((HDC)wParam, RGB(255, 255, 255));
		//return (long)GetStockObject(DKGRAY_BRUSH);
	}
	default:
	{
		return DefWindowProc(Wnd, Message, wParam, lParam);
	}
	}
}
HWND MultiAbilityWindowClass::GetHandle()
{
	return MultiAbilityHandle;
}
