//---------------------------------------------------------------------------
#include "ControlWindowClass.h"

//---------------------------------------------------------------------------
ControlWindowClass::ControlWindowClass()
    {
    }

//---------------------------------------------------------------------------
ControlWindowClass::~ControlWindowClass()
    {
    }

//---------------------------------------------------------------------------
void ControlWindowClass::CreateControlWindow(HINSTANCE Instance, int Width, int Height)
    {
    static char AppName[] = "Dungeons & Dragons Character Planner";
	char WindowName[MAX_PATH];
    WNDCLASSEX wc;
	RECT WindowRect;

	StringCbPrintf (WindowName, MAX_PATH, "%s - Version %s", AppName, VERSION);

    //fill in the class attributes for the main window
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
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

	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    if (ScreenX < Width)
        Width = ScreenX;
    if (ScreenY < Height)
        Height = ScreenY;

    //create and center the window on screen
	ControlWindowHandle = CreateWindowEx(NULL, WindowName, WindowName, WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, 0, 0, Width, Height, NULL, (HMENU)MAINWINDOW, Instance, NULL);

	GetWindowRect(ControlWindowHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	GetClientRect(ControlWindowHandle, &WindowRect);
	ClientX = WindowRect.right - WindowRect.left;
	ClientY = WindowRect.bottom - WindowRect.top;

    SetWindowPos(ControlWindowHandle, NULL, (ScreenX/2) - (WindowX/2), (ScreenY/2) - (WindowY/2), 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    //pop it up
    ShowWindow(ControlWindowHandle, true);
    }

//---------------------------------------------------------------------------
HWND ControlWindowClass::GetControlWindowHandle()
    {
    return ControlWindowHandle;
    }

//---------------------------------------------------------------------------
RECT ControlWindowClass::GetWindowExtents()
    {
    RECT Rect;

    GetClientRect(ControlWindowHandle, &Rect);
    return Rect;
    }


