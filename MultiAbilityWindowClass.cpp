#include "PrintWindowClass.h"
#include "MultiAbilityWindowClass.h"
#include "InterfaceManagerClass.h"
#include "DataClass.h"
#include "CharacterClass.h"

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
	int ParentX;
	int ParentY;
	RECT ParentRect;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Ability Window";
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
	MultiAbilityHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1000, 700, Parent, NULL, Instance, NULL);
	SetClassLong(MultiAbilityHandle, 0, (long)MULTIABILITYWINDOW);
	int TopBar = 25;
	GetWindowRect(Parent, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top - TopBar;

	GetWindowRect(MultiAbilityHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiAbilityHandle, Parent, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (int)(ParentY / 2) - (WindowY / 2) + TopBar, 400, 300, SWP_NOSIZE);

	UIManager = InterfaceManager.GetUIComponents();
	//the child windows
	//MultiAbilityLabel = CreateWindowEx(NULL, "STATIC", "Select Ability Advancement", WS_CHILD, 5, 5, 300, 20, MultiAbilityHandle, (HMENU)MAB_LABEL, Instance, NULL);
	//AcceptButton = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD | BS_PUSHBUTTON, 485, 5, 50, 25, MultiAbilityHandle, (HMENU)MAB_ACCEPT, Instance, NULL);
	//CancelButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 940, 5, 50, 25, MultiAbilityHandle, (HMENU)MAB_CLOSE, Instance, NULL);
	Component = UIManager->GetComponentData("MultiAbilityText", MULTIABILITYWINDOW);
	MultiAbilityText = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CloseButton", MULTIABILITYWINDOW);
	CloseButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("CreationFrame", MULTIABILITYWINDOW);
	CreationFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationFrameLabel", MULTIABILITYWINDOW);
	CreationFrameLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationAvilablePointLabel", MULTIABILITYWINDOW);
	CreationAvilablePointLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationAvilablePoint", MULTIABILITYWINDOW);
	CreationAvilablePoint = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("PointBuild32", MULTIABILITYWINDOW);
	PointBuild32 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("BaseValueLabel", MULTIABILITYWINDOW);
	BaseValueLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ModLabel", MULTIABILITYWINDOW);
	ModLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CostLabel", MULTIABILITYWINDOW);
	CostLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationStr", MULTIABILITYWINDOW);
	CreationStr = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationDex", MULTIABILITYWINDOW);
	CreationDex = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCon", MULTIABILITYWINDOW);
	CreationCon = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationInt", MULTIABILITYWINDOW);
	CreationInt = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationWis", MULTIABILITYWINDOW);
	CreationWis = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCha", MULTIABILITYWINDOW);
	CreationCha = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("CreationStr2", MULTIABILITYWINDOW);
	CreationStr2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationDex2", MULTIABILITYWINDOW);
	CreationDex2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCon2", MULTIABILITYWINDOW);
	CreationCon2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationInt2", MULTIABILITYWINDOW);
	CreationInt2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationWis2", MULTIABILITYWINDOW);
	CreationWis2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCha2", MULTIABILITYWINDOW);
	CreationCha2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	

	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);


	//create a font
	lf.lfHeight = 20;
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
	TitleFontLarge = CreateFontIndirect(&lf);

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

	lf.lfHeight = 20;
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
	AbilityFontLarge = CreateFontIndirect(&lf);
	lf.lfHeight = 10;
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Ariel"));
	AbilityFontSmall = CreateFontIndirect(&lf);
	lf.lfHeight = 14;
	ArielFontSmall = CreateFontIndirect(&lf);


	//background color changes
	//SendMessage(DescPanel, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 0));

	//create a default font


	SendMessage(MultiAbilityText, WM_SETFONT, (WPARAM)TitleFontLarge, 0);
	SendMessage(CreationFrameLabel, WM_SETFONT, (WPARAM)TitleFontLarge, 0);
	SendMessage(CreationStr, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationDex, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationCon, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationInt, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationWis, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationCha, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationStr2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationDex2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationCon2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationInt2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationWis2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationCha2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);

	LoadGraphics(MultiAbilityHandle);


}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::Show(bool State)
{
	ostringstream Text;

	//pop it up
	ShowWindow(MultiAbilityHandle, State);
	ShowWindow(MultiAbilityText, State);
	ShowWindow(CloseButton, State);
	ShowWindow(CreationFrame, State);
	ShowWindow(CreationFrameLabel, State);
	ShowWindow(CreationAvilablePointLabel, State);
	ShowWindow(CreationAvilablePoint, State);
	ShowWindow(PointBuild32, State);
	ShowWindow(BaseValueLabel, State);
	ShowWindow(ModLabel, State);
	ShowWindow(CostLabel, State);
	ShowWindow(CreationStr, State);
	ShowWindow(CreationDex, State);
	ShowWindow(CreationCon, State);
	ShowWindow(CreationInt, State);
	ShowWindow(CreationWis, State);
	ShowWindow(CreationCha, State);
	ShowWindow(CreationStr2, State);
	ShowWindow(CreationDex2, State);
	ShowWindow(CreationCon2, State);
	ShowWindow(CreationInt2, State);
	ShowWindow(CreationWis2, State);
	ShowWindow(CreationCha2, State);
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

	DrawCreation();
}
//---------------------------------------------------------------------------
void MultiAbilityWindowClass::DrawCreation()
{
	int Ability;
	int Modifier;
	int Cost;
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	ostringstream vs;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	RECT rc;
	hdc = GetWindowDC(MultiAbilityHandle);
	string TextString, EraseString;
	EraseString = "  ";
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	for (int i = 0; i < 6; i++)
	{
		ss.str("");
		ss << "AbilityDown" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		//if (SetTotalValue[i] < 1)
			//DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
		//else
		DrawGraphic(hdc, &Minus, X, Y, Width, Height);

		ss.str("");
		ss << "AbilityUp" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		//if (SetTotalValue[i] < 1)
		//DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
		//else
		DrawGraphic(hdc, &Plus, X, Y, Width, Height);

		//Ability Value
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "AbilityValue" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		ss.str("");
		Ability = Character.GetAbility(i, 1, true, true, true);
		ss << Ability;
		TextString = ss.str();
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);

		//Ability Cost
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "CurrentCost" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		ss.str("");
		Cost = Character.GetAbilityCost(i);
		if (Cost == -1)
			TextString = "MAX";
		else
		{
			ss << Cost;
			TextString = ss.str();
		}
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);

		//Current Cost
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "CurrentMod" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		ss.str("");
		Modifier = Data.CalculateAbilityModifier(Ability);
		if (Modifier > 0)
			ss << "+" << Modifier;
		else
			ss << Modifier;
		TextString = ss.str();
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);
	}

	ReleaseDC(MultiAbilityHandle, hdc);
}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::LoadGraphics(HWND Parent)
{
	HDC hdc;

	//palette for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	//The Plus Minus
	LoadBitmap("MinusBox", "UserInterface", &Minus);
	LoadBitmap("PlusBox", "UserInterface", &Plus);


}
//---------------------------------------------------------------------------
long MultiAbilityWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	int pos;
	POINTS ps;
	POINT ps1;
	pos = GetMessagePos();
	ps = MAKEPOINTS(pos);
	ps1.x = ps.x;
	ps1.y = ps.y;
	ScreenToClient(MultiAbilityHandle, (LPPOINT)&ps1);

	switch (Message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			//if ((int)LOWORD(wParam) == MAB_ACCEPT)
			//{
			//	InterfaceManager.ShowChild(MULTIABILITYWINDOW, false);
			//	return 0;
			//}
			if ((int)LOWORD(wParam) == MAB_CLOSE)
			{
				InterfaceManager.ShowChild(MULTIABILITYWINDOW, false);
				return 0;
			}
		}
	}
	case WM_CTLCOLORSTATIC:
	{

		SetBkMode((HDC)wParam, TRANSPARENT);
		if((HWND)lParam == CreationStr || (HWND)lParam == CreationDex || (HWND)lParam == CreationCon ||
			(HWND)lParam == CreationInt || (HWND)lParam == CreationWis || (HWND)lParam == CreationCha)
		{
			SetTextColor((HDC)wParam, RGB(230, 230, 30));
		}
		else
		{
			SetTextColor((HDC)wParam, RGB(255, 255, 255));
		}



		return (long)GetStockObject(DKGRAY_BRUSH);
		break;
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
