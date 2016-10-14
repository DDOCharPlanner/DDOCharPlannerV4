#include "ToolTipWindowClass.h"
#include "InterfaceManagerClass.h"

//---------------------------------------------------------------------------
ToolTipWindowClass::ToolTipWindowClass()
	{
	}

//---------------------------------------------------------------------------
ToolTipWindowClass::~ToolTipWindowClass()
	{
	}	

//---------------------------------------------------------------------------
void ToolTipWindowClass::Create(HINSTANCE Instance, HWND Parent)
	{
	LRESULT Mask;
    WNDCLASSEX wc;
	static char WindowName[] = "Tooltip Window";
	int FontSize = 5;

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

	ToolTipWindow = CreateWindowEx (WS_EX_TOPMOST, WindowName, WindowName, WS_POPUP | WS_DLGFRAME, 0, 0, 200, 100, Parent, NULL, Instance, NULL);
    SetClassLong(ToolTipWindow, 0, (long)TOOLTIPWINDOW);

	ToolTipText = CreateWindowEx (NULL, "RichEdit", "RichEdit", WS_CHILD | ES_MULTILINE | ES_READONLY, 0, 0, 200, 100, ToolTipWindow, (HMENU)TTW_TOOLTIPTEXT, Instance, NULL);

	SendMessage(ToolTipText, EM_SETBKGNDCOLOR, 0, RGB(0,0,0));
	Mask = SendMessage(ToolTipText, EM_GETEVENTMASK, 0, 0);
	SendMessage(ToolTipText, EM_SETEVENTMASK, 0, Mask | ENM_REQUESTRESIZE);
	SendMessage(ToolTipText, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, (LPARAM)MAKELONG(4, 4));
	}

//---------------------------------------------------------------------------
void ToolTipWindowClass::Show(bool State)
	{
	ShowWindow(ToolTipWindow, State);
	ShowWindow(ToolTipText, State);
	}

//---------------------------------------------------------------------------
long ToolTipWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	PAINTSTRUCT ps;
	REQRESIZE *ReqResize;
	POINT CursorPoint;
	int X;
	int Y;
	RECT ConfiningRect;
	RECT ToolTipRect;

	switch (Message)
		{
		case WM_CLOSE:
			{
			InterfaceManager.ShowChild(TOOLTIPWINDOW, false);
			return 0;
			}
		case WM_NOTIFY:
			{
			ostringstream ss;
            if (wParam == TTW_TOOLTIPTEXT)
                {
                if (((NMHDR*)lParam)->code == EN_REQUESTRESIZE)
					{
					GetWindowRect(ConfiningWindow, &ConfiningRect);
                    ReqResize = (REQRESIZE*)lParam;
					GetCursorPos(&CursorPoint);
					X = CursorPoint.x + 10;
					Y = CursorPoint.y + 10;
					//don't fall off the bottom of the confining window
					if (Y + (ReqResize->rc.bottom - ReqResize->rc.top) +15 > ConfiningRect.bottom)
						Y = ConfiningRect.bottom - (ReqResize->rc.bottom - ReqResize->rc.top) - 15;
					//also, don't go past the right side of the main window
					GetWindowRect(ToolTipWindow, &ToolTipRect);
					if (X + (ToolTipRect.right - ToolTipRect.left) +15 > ConfiningRect.right)
						X = CursorPoint.x - (ToolTipRect.right - ToolTipRect.left) - 15;
					//at this point we should be entirely inside the window, unless the text is so large the tooltip is higher than the entire window itself.
					if (Y < ConfiningRect.top)
						{
						SetWindowPos(ToolTipWindow, HWND_TOPMOST, X, ConfiningRect.top+15, ReqResize->rc.right - ReqResize->rc.left+50, ConfiningRect.bottom - ConfiningRect.top-30, SWP_HIDEWINDOW);
						GetWindowRect(ToolTipWindow, &ToolTipRect);
						if (ToolTipRect.left < CursorPoint.x && ToolTipRect.right +15 > CursorPoint.x)
							{
							X = CursorPoint.x - (ToolTipRect.right - ToolTipRect.left) - 15;
							SetWindowPos(ToolTipWindow, HWND_TOPMOST, X, ConfiningRect.top+15, ReqResize->rc.right - ReqResize->rc.left+50, ConfiningRect.bottom - ConfiningRect.top-30, SWP_HIDEWINDOW);
							}
						SetWindowPos(ToolTipText, HWND_TOP, 0, 0, ToolTipRect.right - ToolTipRect.left, ToolTipRect.bottom - ToolTipRect.top, SWP_HIDEWINDOW);
						return 0;
						}  
					SetWindowPos(ToolTipWindow, HWND_TOPMOST, X, Y, ReqResize->rc.right - ReqResize->rc.left+6, ReqResize->rc.bottom - ReqResize->rc.top+6, SWP_SHOWWINDOW);
					SetWindowPos(ToolTipText, HWND_TOP, 0, 0, ReqResize->rc.right - ReqResize->rc.left, ReqResize->rc.bottom - ReqResize->rc.top, SWP_SHOWWINDOW);
					RedrawWindow(ToolTipText, nullptr, nullptr, RDW_INVALIDATE);
					return 0;
					}
				return 0;
                }
            return 0;
			}
		case WM_PAINT:
			{
			BeginPaint(Wnd, &ps);
			EndPaint(Wnd, &ps);
			return 0;
			}
		default:
			{
			return DefWindowProc(Wnd, Message, wParam, lParam);
			}
		}
	}

//---------------------------------------------------------------------------
void ToolTipWindowClass::SetToolTipText(string Text)
	{
	EDITSTREAM Stream;

	//if we are setting text, this must be a new tooltip, so reset the window size to default
	SetWindowPos(ToolTipWindow, HWND_TOPMOST, 0, 0, 200, 0, SWP_HIDEWINDOW);
	SetWindowPos(ToolTipText, HWND_TOP, 0, 0, 200, 0, SWP_HIDEWINDOW);

	Stream.dwCookie = (DWORD)(Text.c_str());
	Stream.dwError = false;
	Stream.pfnCallback = EditStreamCallback;
	SendMessage(ToolTipText, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);

	SendMessage(ToolTipText, EM_REQUESTRESIZE, 0, 0);
	}

//---------------------------------------------------------------------------
ToolTipWindowClass* ToolTipWindowClass::GetPointer()
	{
	return this;
	}

//---------------------------------------------------------------------------
void ToolTipWindowClass::SetConfiningWindow(HWND Window)
	{
	ConfiningWindow = Window;
	}

