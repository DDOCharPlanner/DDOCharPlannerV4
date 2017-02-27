#include "PrintWindowClass.h"
#include "MultiSpellsWindowClass.h"
#include "InterfaceManagerClass.h"


//---------------------------------------------------------------------------
MultiSpellsWindowClass::MultiSpellsWindowClass()
{
}

//---------------------------------------------------------------------------
MultiSpellsWindowClass::~MultiSpellsWindowClass()
{
	DeleteObject(TitleFontLarge);
}

//---------------------------------------------------------------------------
void MultiSpellsWindowClass::Create(HINSTANCE Instance, HWND Parent)
{
	WNDCLASSEX wc;
	int ScreenX;
	int ScreenY;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "spells Window";
	LOGBRUSH lb;
	LOGFONT lf;
	UIComponentManager *UIManager;
	InterfaceComponentStruct *Component;

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
	MultiSpellsHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1000, 700, Parent, NULL, Instance, NULL);
	SetClassLong(MultiSpellsHandle, 0, (long)MULTISPELLSWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(MultiSpellsHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiSpellsHandle, Parent, (ScreenX / 2) - (WindowX / 2), (int)(ScreenY / 2) - (WindowY / 2), 400, 300, SWP_NOSIZE);

	//the child windows
	UIManager = InterfaceManager.GetUIComponents();
	Component = UIManager->GetComponentData("MultiSpellText", MULTISPELLSWINDOW);
	MultiSpellsLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSpellsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Close", MULTISPELLSWINDOW);
	CancelButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSpellsHandle, (HMENU)Component->WindowID, Instance, nullptr);




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

	//create a font
	lf.lfHeight = 16;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_MEDIUM;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	DefaultFont = CreateFontIndirect(&lf);
	HDC hdc;
	hdc = GetWindowDC(MultiSpellsHandle);
	LoadGraphics(hdc);
	ReleaseDC(MultiSpellsHandle, hdc);
}

//---------------------------------------------------------------------------
void MultiSpellsWindowClass::Show(bool State)
{
	ostringstream Text;

	//pop it up
	ShowWindow(MultiSpellsHandle, State);
	ShowWindow(MultiSpellsLabel, State);
	ShowWindow(CancelButton, State);


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

	GetWindowRect(MultiSpellsHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiSpellsHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2), 0, 0, SWP_NOSIZE);

	DrawGraphics();
}

//---------------------------------------------------------------------------
long MultiSpellsWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{

			if ((int)LOWORD(wParam) == MSP_CANCEL)
			{
				InterfaceManager.ShowChild(MULTISPELLSWINDOW, false);
				return 0;
			}
		}
	}
	case WM_CTLCOLORSTATIC:
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		SetTextColor((HDC)wParam, RGB(255, 255, 255));
		return (long)GetStockObject(DKGRAY_BRUSH);
	}
	default:
	{
		return DefWindowProc(Wnd, Message, wParam, lParam);
	}
	}
}
void MultiSpellsWindowClass::DrawGraphics()
{
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	ostringstream vs;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	hdc = GetWindowDC(MultiSpellsHandle);
	string TextString;
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);

	//Draw Headings
	SelectObject(hdc, TitleFontLarge);
	OldColor = SetTextColor(hdc, RGB(255, 255, 255));
	ss.str("");
	ss << "Test";
	Graphic = UIManager->GetGraphicData(ss.str(), MULTISPELLSWINDOW);
	X = static_cast<int>(Graphic->BaseLocationX);
	Y = static_cast<int>(Graphic->BaseLocationY);
	Width = static_cast<int>(Graphic->BaseWidth);
	Height = static_cast<int>(Graphic->BaseHeight);
	DrawGraphic(hdc, &Test, X, Y, Width, Height);

	OldColor = SetTextColor(hdc, RGB(255, 255, 255));
	ss.str("");
	ss << "Test2";
	Graphic = UIManager->GetGraphicData(ss.str(), MULTISPELLSWINDOW);
	X = static_cast<int>(Graphic->BaseLocationX);
	Y = static_cast<int>(Graphic->BaseLocationY);
	Width = static_cast<int>(Graphic->BaseWidth);
	Height = static_cast<int>(Graphic->BaseHeight);
	DrawGraphic(hdc, &Test2, X, Y, Width, Height);



}
void MultiSpellsWindowClass::LoadGraphics(HDC hdc)
{
	//LoadBitmap("SkillErrorBox", "UserInterface", &Test);
	LoadBitmap("SkillNormalBox", "UserInterface", &Test2);
}
HWND MultiSpellsWindowClass::GetHandle()
{
	return MultiSpellsHandle;
}
