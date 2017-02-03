#include "PrintWindowClass.h"
#include "MultiSkillsWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include <iomanip>


//---------------------------------------------------------------------------
MultiSkillsWindowClass::MultiSkillsWindowClass()
{
	SkillsChanged = false;
	for (int x = 0; x < NUMSKILLS; x++)
	{
		for (int y = 0; y < HEROICLEVELS; y++)
		{
			SkillsValue[x][y] = 0;
		}
	}
		
}

//---------------------------------------------------------------------------
MultiSkillsWindowClass::~MultiSkillsWindowClass()
{
	DeleteObject(TitleFontLarge);
	DeleteObject(SmallFont);
	DeleteObject(DefaultFont);
	DeleteGraphics();
}

//---------------------------------------------------------------------------
void MultiSkillsWindowClass::Create(HINSTANCE Instance, HWND Parent)
{
	WNDCLASSEX wc;
	int ScreenX;
	int ScreenY;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Skills Window";
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
	MultiSkillsHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1000, 720, Parent, NULL, Instance, NULL);
	SetClassLong(MultiSkillsHandle, 0, (long)MULTISKILLSWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(MultiSkillsHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiSkillsHandle, Parent, (ScreenX / 2) - (WindowX / 2), (int)(ScreenY / 2) - (WindowY / 2), 400, 300, SWP_NOSIZE);
	
	UIManager = InterfaceManager.GetUIComponents();
	//the child windows
	Component = UIManager->GetComponentData("MultiSkillText", MULTISKILLSWINDOW);
	MultiSkillsLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Reset", MULTISKILLSWINDOW);
	Reset = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Accept", MULTISKILLSWINDOW);
	AcceptButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Close", MULTISKILLSWINDOW);
	CancelButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("MultiSkillFrame", MULTISKILLSWINDOW);
	SkillFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("SKILLLABEL", MULTISKILLSWINDOW);
	SkillLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("TOTALLABEL", MULTISKILLSWINDOW);
	TotalLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("SKILLSpentLevel", MULTISKILLSWINDOW);
	SkillSpentLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("SkillAvalibleLevel", MULTISKILLSWINDOW);
	SKillAvalibleLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("AutoSkillFrame", MULTISKILLSWINDOW);
	AutoSkillFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("AutoFill", MULTISKILLSWINDOW);
	AutoFill = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ResetAuto", MULTISKILLSWINDOW);
	ResetAuto = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ClassFirstCheckBox", MULTISKILLSWINDOW);
	ClassFirstCheckBox = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("SetTotal", MULTISKILLSWINDOW);
	SetTotal = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Priority", MULTISKILLSWINDOW);
	Priority = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiSkillsHandle, (HMENU)Component->WindowID, Instance, nullptr);








	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);


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



	//create a font
	lf.lfHeight = 18;
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
	lf.lfHeight = 14;
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
	SmallFont = CreateFontIndirect(&lf);

	LoadGraphics(MultiSkillsHandle);
	ResetAutoValues();



}

//---------------------------------------------------------------------------
void MultiSkillsWindowClass::Show(bool State)
{
	ostringstream Text;

	//pop it up
	ShowWindow(MultiSkillsHandle, State);
	ShowWindow(MultiSkillsLabel, State);
	ShowWindow(AcceptButton, State);
	ShowWindow(CancelButton, State);
	ShowWindow(SkillFrame, State);
	ShowWindow(SkillLabel, State);
	ShowWindow(TotalLabel, State);
	ShowWindow(SkillSpentLabel, State);
	ShowWindow(SKillAvalibleLabel, State);
	ShowWindow(AutoFill, State);
	ShowWindow(ResetAuto, State);
	ShowWindow(ClassFirstCheckBox, State);
	ShowWindow(SetTotal, State);
	ShowWindow(Priority, State);
	ShowWindow(AutoSkillFrame, State);
	ShowWindow(Reset, State);
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

	GetWindowRect(MultiSkillsHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiSkillsHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2), 0, 0, SWP_NOSIZE);


	for (int x = 0; x < NUMSKILLS; x++)
	{
		for (int y = 0; y < HEROICLEVELS; y++)
		{
			SkillsValue[x][y] = Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(x),y+1);
		}
	}

	UpdateAll = true;
	SkillChange = true;
	CurrentSkill = BALANCE;
	CurrentLevel = 1;
	DrawSkillTable();
	DrawAutoRank();
}

//---------------------------------------------------------------------------
void MultiSkillsWindowClass::LoadGraphics(HWND Parent)
{
	HDC hdc;

	//palette for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	//The Skill Boxes
	LoadBitmap("SkillClassBox", "UserInterface", &SkillClassBox);
	LoadBitmap("SkillNormalBox", "UserInterface", &SkillNormalBox);
	LoadBitmap("SkillErrorBox", "UserInterface", &SkillErrorBox);
	LoadBitmap("ArrowRight", "UserInterface", &RightArrow);
	LoadBitmap("ArrowLeft", "UserInterface", &LeftArrow);


}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::ResetAutoValues()
{
	for (int i = 0; i < NUMSKILLS; i++)
	{
		SetTotalValue[i] = 0;
		PriorityValue[i] = 5;
	}
	SendMessage(ClassFirstCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
	DrawAutoRank();
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::ResetSkillValues()
{
	for (int i = 0; i < NUMSKILLS; i++)
	{
		for (int x = 0; x < HEROICLEVELS; x++)
		{
			SkillsValue[i][x] = 0;
		}
	}
}




//---------------------------------------------------------------------------
void MultiSkillsWindowClass::DrawSkillTable()
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
	RECT rc;
	hdc = GetWindowDC(MultiSkillsHandle);
	string TextString;
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	bool oldError = ErrorFound;
	ErrorFound = false;
	if (UpdateAll || oldError)
	{
		for (int i = 0; i < HEROICLEVELS; i++)
		{

			//Draw Headings
			SelectObject(hdc, TitleFontLarge);
			OldColor = SetTextColor(hdc, RGB(255, 255, 255));
			ss.str("");
			ss << "LevelLabel" << i;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			if (i < 10)
				X += 5;
			TextString = to_string(i + 1);
			TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
			SetTextColor(hdc, OldColor);
		}
	}
		//Draw Skills
		for (int x = 0; x < NUMSKILLS; x++)
		{
			if (UpdateAll || oldError)
			{
				SelectObject(hdc, TitleFontLarge);
				//Draw Skill Label
				OldColor = SetTextColor(hdc, RGB(255, 255, 255));
				ss.str("");
				ss << "SkillLabel" << x;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX);
				Y = static_cast<int>(Graphic->BaseLocationY);
				TextString = Data.GetSkillName(x);
				TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
				SetTextColor(hdc, OldColor);


				for (int i = 0; i < HEROICLEVELS; i++)
				{

					//Draw Skill Level Box
					ss.str("");
					ss << "SkillBox" << x << "_" << i;
					Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX);
					Y = static_cast<int>(Graphic->BaseLocationY);
					Width = static_cast<int>(Graphic->BaseWidth);
					Height = static_cast<int>(Graphic->BaseHeight);
					//Set Skill Box for Primary or Error
					if (CheckPointsSpent(static_cast<SKILLS>(x), i + 1) || CheckPointsSpent(i + 1))
					{
						DrawGraphic(hdc, &SkillErrorBox, X, Y, Width, Height);
						//EnableWindow(AcceptButton, false);
						ErrorFound = true;
					}
					else
					{
						if (Data.IsSkillPrimary(Character.GetClass(i + 1, false), x))
						{
							DrawGraphic(hdc, &SkillClassBox, X, Y, Width, Height);
						}
						else
						{
							DrawGraphic(hdc, &SkillNormalBox, X, Y, Width, Height);
						}
					}



					SelectObject(hdc, DefaultFont);
					//Draw Skill Level Text
					OldColor = SetTextColor(hdc, RGB(255, 255, 255));
					ss.str("");
					ss << "SkillValue" << x << "_" << i;
					Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX);
					Y = static_cast<int>(Graphic->BaseLocationY);
					vs.str("");
					vs << fixed << setprecision(1) << GetLevelSkillPointsSpentDisplay(static_cast<SKILLS>(x), i + 1);
					TextString = vs.str();
					string test;
					test = TextString.back();
					if (TextString.back() == '0')
					{
						TextString.pop_back();
						TextString.pop_back();
					}
					if (TextString.length() == 1)
						X += 7;
					TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
					SetTextColor(hdc, OldColor);

				}
			}
			else
			{
				if (CurrentLevel != -1)
				{
					for (int i = 0; i < HEROICLEVELS; i++)
					{
						if (i+1 == CurrentLevel || x == static_cast<int>(CurrentSkill))
						{
							//Draw Skill Level Box
							ss.str("");
							ss << "SkillBox" << x << "_" << i;
							Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX);
							Y = static_cast<int>(Graphic->BaseLocationY);
							Width = static_cast<int>(Graphic->BaseWidth);
							Height = static_cast<int>(Graphic->BaseHeight);
							//Set Skill Box for Primary or Error
							if (CheckPointsSpent(static_cast<SKILLS>(x), i + 1) || CheckPointsSpent(i + 1))
							{
								DrawGraphic(hdc, &SkillErrorBox, X, Y, Width, Height);
								ErrorFound = true;
							}
							else
							{
								if (Data.IsSkillPrimary(Character.GetClass(i + 1, false), x))
								{
									DrawGraphic(hdc, &SkillClassBox, X, Y, Width, Height);
								}
								else
								{
									DrawGraphic(hdc, &SkillNormalBox, X, Y, Width, Height);
								}
							}



							SelectObject(hdc, DefaultFont);
							//Draw Skill Level Text
							OldColor = SetTextColor(hdc, RGB(255, 255, 255));
							ss.str("");
							ss << "SkillValue" << x << "_" << i;
							Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX);
							Y = static_cast<int>(Graphic->BaseLocationY);
							vs.str("");
							vs << fixed << setprecision(1) << GetLevelSkillPointsSpentDisplay(static_cast<SKILLS>(x), i + 1);
							TextString = vs.str();
							string test;
							test = TextString.back();
							if (TextString.back() == '0')
							{
								TextString.pop_back();
								TextString.pop_back();
							}
							if (TextString.length() == 1)
								X += 7;
							TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
							SetTextColor(hdc, OldColor);
						}
					}
				}
			}
			if (UpdateAll || x == static_cast<int>(CurrentSkill))
			{
				SelectObject(hdc, DefaultFont);
				OldColor = SetTextColor(hdc, RGB(255, 255, 255));
				ss.str("");
				ss << "SkillTotal" << x;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX);
				Y = static_cast<int>(Graphic->BaseLocationY);
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				rc.left = X;
				rc.top = Y;
				rc.right = X + Width;
				rc.bottom = Y + Height;
				ClearRect(hdc, rc);
				//add Total count
				vs.str("");
				vs << fixed << setprecision(1) << GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(x));
				TextString = vs.str();
				if (GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(x)) < 10)
					X += 10;
				TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
				SetTextColor(hdc, OldColor);
			}
		}
		for (int i = 0; i < HEROICLEVELS; i++)
		{
			if (i+1 == CurrentLevel || UpdateAll)
			{
				SelectObject(hdc, DefaultFont);
				OldColor = SetTextColor(hdc, RGB(255, 255, 255));
				ss.str("");
				ss << "SkillSpentLevel" << i;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX);
				Y = static_cast<int>(Graphic->BaseLocationY);
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				rc.left = X;
				rc.top = Y;
				rc.right = X + Width;
				rc.bottom = Y + Height;
				ClearRect(hdc, rc);
				//add Total count
				TextString = to_string(GetLevelSkillPointsSpent(i + 1));
				if (TextString.length() < 2)
					X += 5;
				TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
				SetTextColor(hdc, OldColor);

				OldColor = SetTextColor(hdc, RGB(255, 255, 255));
				ss.str("");
				ss << "SkillAvalibleLevel" << i;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX);
				Y = static_cast<int>(Graphic->BaseLocationY);
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				rc.left = X;
				rc.top = Y;
				rc.right = X + Width;
				rc.bottom = Y + Height;
				ClearRect(hdc, rc);
				//add Total count
				TextString = to_string(CalculateAvailableSkillPoints(i + 1));
				if (TextString.length() < 2)
					X += 5;
				TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
				SetTextColor(hdc, OldColor);
			}
		}
		ReleaseDC(MultiSkillsHandle, hdc);
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::DrawAutoRank()
{
	HDC hdc;
	hdc = GetWindowDC(MultiSkillsHandle);
	ClearAutoFillFrame(hdc);
	ostringstream ss;
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	int X, Y, Width, Height;
	COLORREF OldColor;
	string TextString;
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	for (int i = 0; i < NUMSKILLS; i++)
	{
		//LeftArrow Desired Ranks
		ss.str("");
		ss << "SkillAutoTextLeftArrow" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		if (SetTotalValue[i] < 1)
			DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
		else
			DrawGraphic(hdc, &LeftArrow, X, Y, Width, Height);

		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "SkillAutoText" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = to_string(SetTotalValue[i]);
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);


		//RightArrow Desired Ranks
		ss.str("");
		ss << "SkillAutoTextRightArrow" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		if (SetTotalValue[i] > 22)
			DrawGraphicGreyscale(hdc, &RightArrow, X, Y, Width, Height);
		else
			DrawGraphic(hdc, &RightArrow, X, Y, Width, Height);

		//LeftArrow Priority
		ss.str("");
		ss << "SkillAutoRankLeftArrow" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		if (PriorityValue[i] < 2)
			DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
		else
			DrawGraphic(hdc, &LeftArrow, X, Y, Width, Height);

		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "SkillAutoRank" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = to_string(PriorityValue[i]);
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);


		//RightArrow Priority
		ss.str("");
		ss << "SkillAutoRankRightArrow" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		if (PriorityValue[i] > 4)
			DrawGraphicGreyscale(hdc, &RightArrow, X, Y, Width, Height);
		else
			DrawGraphic(hdc, &RightArrow, X, Y, Width, Height);

	}

	ReleaseDC(MultiSkillsHandle, hdc);
}



//---------------------------------------------------------------------------
void MultiSkillsWindowClass::DrawSkills(SKILLS Skill)
{
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	ostringstream vs;
	int X, Y;
	//int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	hdc = GetWindowDC(MultiSkillsHandle);
	string TextString;
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);

	for (int x = 0; x < NUMSKILLS; x++)
	{
		SelectObject(hdc, TitleFontLarge);
		//Draw Skill Label
		if (x == Skill)
		{
			OldColor = SetTextColor(hdc, RGB(255, 255, 0));
		}
		else
		{
			OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		}
		ss.str("");
		ss << "SkillLabel" << x;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = Data.GetSkillName(x);
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);
	}
	ReleaseDC(MultiSkillsHandle, hdc);
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::SpendSkillPoint(SKILLS Skill, unsigned int Level, int Point)
{
	Level--;
	SkillsValue[Skill][Level] += Point;
}
//---------------------------------------------------------------------------
int MultiSkillsWindowClass::CalculateAvailableSkillPoints(unsigned int AtLevel)
{
	int Result;
	int AbilityTotal;
	CLASS CurrentClass;
	RACE CurrentRace;
	CurrentClass = Character.GetClass(AtLevel, false);
	CurrentRace = Character.GetRace();

	if (CurrentClass == CLASSNONE)
		return 0;

	Result = Data.GetClassSkillPoints(CurrentClass);
	AbilityTotal = Character.GetAbility(INTELLIGENCE, AtLevel, false) + Character.GetTomeRaise(INTELLIGENCE, AtLevel, false);
	//we need to subtract 2 points of they have completionist loaded up
	if (Character.HasFeat("Completionist", AtLevel) == true)
		AbilityTotal -= 2;
	Result += Data.CalculateAbilityModifier(AbilityTotal);
	if (CurrentRace == HUMAN || CurrentRace == PURPLEDRAGONKNIGHT)
		Result++;
	//minimum of 1 point!
	if (Result < 1)
		Result = 1;
	if (AtLevel == 1)
		Result *= 4;
	Result -= GetLevelSkillPointsSpent(AtLevel);

	return Result;
}
//---------------------------------------------------------------------------
int MultiSkillsWindowClass::GetLevelSkillPointsSpent(SKILLS Skill, unsigned int AtLevel)
{
	if (AtLevel > 20)
		return 0;

	return SkillsValue[Skill][AtLevel - 1];
}
//---------------------------------------------------------------------------
int	MultiSkillsWindowClass::GetLevelSkillPointsSpent(unsigned int AtLevel)
{
	int Result;

	Result = 0;
	for (unsigned int i = 0; i<NUMSKILLS; i++)
		Result += SkillsValue[i][AtLevel - 1];
	return Result;
}
//---------------------------------------------------------------------------
int	MultiSkillsWindowClass::GetSkillPointsSpent(SKILLS Skill, unsigned int AtLevel)
{
	int Result;

	Result = 0;
	for (unsigned int i = 0; i<AtLevel; i++)
		Result += SkillsValue[Skill][i];
	return Result;
}
//---------------------------------------------------------------------------
float MultiSkillsWindowClass::GetTotalSkillPointsSpentDisplay(SKILLS Skill)
{
	float Result;
	CLASS CurrentClass;

	
	int	AtLevel = 20;

	Result = 0.0f;
	for (int i = 0; i<AtLevel; i++)
	{
		CurrentClass = Character.GetClass(i+1, false);
		if (Data.IsSkillPrimary(CurrentClass, Skill) == true)
			Result += SkillsValue[Skill][i];
		else
			Result += SkillsValue[Skill][i] / 2.0f;
	}

	return Result;
}
//---------------------------------------------------------------------------
float MultiSkillsWindowClass::GetTotalSkillPointsSpentDisplay(SKILLS Skill, int AtLevel)
{
	float Result;
	CLASS CurrentClass;

	if (AtLevel > 20)
		AtLevel = 20;

	Result = 0.0f;
	for (int i = 0; i < AtLevel; i++)
	{
		CurrentClass = Character.GetClass(i+1, false);
		if (Data.IsSkillPrimary(CurrentClass, Skill) == true)
			Result += SkillsValue[Skill][i];
		else
			Result += SkillsValue[Skill][i] / 2.0f;
	}

	return Result;
}//---------------------------------------------------------------------------
float MultiSkillsWindowClass::GetLevelSkillPointsSpentDisplay(SKILLS Skill, int AtLevel)
{
	float Result;
	CLASS CurrentClass;

	if (AtLevel > 20)
		AtLevel = 20;

	Result = 0.0f;
		CurrentClass = Character.GetClass(AtLevel, false);
		if (Data.IsSkillPrimary(CurrentClass, Skill) == true)
			Result += SkillsValue[Skill][AtLevel - 1];
		else
			Result += SkillsValue[Skill][AtLevel - 1] / 2.0f;

	return Result;
}

//---------------------------------------------------------------------------
float MultiSkillsWindowClass::GetSkillPointSpendLimit(SKILLS Skill, unsigned int AtLevel)
{
	float SkillSpendLimit;
	bool Primary;
	CLASS CurrentClass;

	Primary = false;
	for (unsigned int i = 0; i<AtLevel; i++)
	{
		CurrentClass = Character.GetClass(i+1, false);
		if (Data.IsSkillPrimary(CurrentClass, Skill) == true)
		{
			Primary = true;
			break;
		}
	}
	if (Primary == true)
		SkillSpendLimit = 3.0f + (float)AtLevel;
	else
		SkillSpendLimit = (float)(3.0 + (float)AtLevel) / 2.0f;

	return SkillSpendLimit;
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::AcceptSkillPoints()
{
	//int point;
	if (SkillChange)
	{


		Character.SetSkillPoints(SkillsValue);

	}
}
//---------------------------------------------------------------------------
bool MultiSkillsWindowClass::CheckPointsSpent(SKILLS Skill, int AtLevel)
{
	bool Result;
	Result = false;
	float test1, test2;
	test1 = GetTotalSkillPointsSpentDisplay(Skill, AtLevel);
	test2 = GetSkillPointSpendLimit(Skill, AtLevel);
	if (GetTotalSkillPointsSpentDisplay(Skill, AtLevel) > GetSkillPointSpendLimit(Skill, AtLevel))
		Result = true;
	return Result;
}
//---------------------------------------------------------------------------
bool MultiSkillsWindowClass::CheckPointsSpent(int AtLevel)
{
	bool Result;
	Result = false;
	if (CalculateAvailableSkillPoints(AtLevel)<0)
		Result = true;

	return Result;
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::ClearSkillFrame(HDC hdc)
{
	RECT rc;
	LOGBRUSH lb;
	// Erase the whole bitmap background.
	GetClientRect(SkillFrame, &rc);
	MapWindowPoints(SkillFrame, MultiSkillsHandle, (LPPOINT)&rc, 2);
	
	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	rc.top += 25;
	rc.left += 120;
	rc.right -= 5;
	rc.bottom -= 5;
	FillRect(hdc, &rc, hbrBkGnd);
	
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::ClearRect(HDC hdc, RECT rc)
{

	LOGBRUSH lb;

	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	rc.top -= 2;
	rc.left -= 2;
	rc.right += 2;
	rc.bottom += 2;
	FillRect(hdc, &rc, hbrBkGnd);

}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::ClearAutoFillFrame(HDC hdc)
{
	RECT rc;
	LOGBRUSH lb;
	// Erase the whole bitmap background.
	GetClientRect(AutoSkillFrame, &rc);
	MapWindowPoints(AutoSkillFrame, MultiSkillsHandle, (LPPOINT)&rc, 2);

	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	rc.top += 25;
	rc.left += 5;
	rc.right -= 5;
	rc.bottom -= 50;
	FillRect(hdc, &rc, hbrBkGnd);

}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::ClearSkillFrameTotals(HDC hdc)
{
	RECT rc;
	RECT ClearRC;
	LOGBRUSH lb;
	// Erase the whole bitmap background.
	GetClientRect(SkillFrame, &rc);
	MapWindowPoints(SkillFrame, MultiSkillsHandle, (LPPOINT)&rc, 2);

	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	rc.top += 25;
	rc.left += 120;
	rc.right -= 5;
	rc.bottom -= 5;

	ClearRC.top = rc.top;
	ClearRC.left = rc.right - 50;
	ClearRC.right = rc.right;
	ClearRC.bottom = rc.bottom;
	FillRect(hdc, &ClearRC, hbrBkGnd);

	ClearRC.top = rc.bottom - 60;
	ClearRC.left = rc.left;
	ClearRC.right = rc.right;
	ClearRC.bottom = rc.bottom;
	FillRect(hdc, &ClearRC, hbrBkGnd);


}
//---------------------------------------------------------------------------

long MultiSkillsWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

	static bool TrackingMouse = false;
	//RECT Rect;
	int pos;
	POINTS ps;
	POINT ps1;
	pos = GetMessagePos();
	ps = MAKEPOINTS(pos);
	ps1.x = ps.x;
	ps1.y = ps.y;
	ScreenToClient(MultiSkillsHandle, (LPPOINT)&ps1);
	SKILLS OldSkill;

	switch (Message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if ((int)LOWORD(wParam) == MSK_CANCEL)
			{
				InterfaceManager.ShowChild(MULTISKILLSWINDOW, false);
				return 0;
			}
			if ((int)LOWORD(wParam) == MSK_ACCEPT)
			{
				if (ErrorFound)
					return 0;
				AcceptSkillPoints();
				InterfaceManager.ShowChild(MULTISKILLSWINDOW, false);
				return 0;
			}
			if ((int)LOWORD(wParam) == MSK_AUTOSKILLCLASSFIRST)
			{
				if (SendMessage(ClassFirstCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
					UseClassFirst = true;
				else
					UseClassFirst = false;
				return 0;
			}
			if ((int)LOWORD(wParam) == MSK_AUTOSKILLRESET)
			{
				ResetAutoValues();
			}
			if ((int)LOWORD(wParam) == MSK_AUTOSKILLSET)
			{
				AutoSetRanks();
			}
			if ((int)LOWORD(wParam) == MSK_RESET)
			{
				ResetSkillValues();
				UpdateAll = true;
				DrawSkillTable();
			}
		}
	}
	case WM_LBUTTONDOWN:
	{

		HandleLeftMouseButtonClick(ps1.x, ps1.y);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		HandleRightMouseButtonClick(ps1.x, ps1.y);
		return 0;
	}
	case WM_MOUSEHOVER:
	{
		HandleMouseHover(ps1.x, ps1.y);
		DrawSkills(CurrentSkill);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		OldSkill = CurrentSkill;
		HandleMouseHover(ps1.x, ps1.y);
		if (CurrentSkill != OldSkill)
			TrackingMouse = false;

		if (!TrackingMouse)
		{
			TrackMouse(Wnd);
			TrackingMouse = true;
		}
		return 0;
	}

	case WM_CTLCOLORSTATIC:
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		SetTextColor((HDC)wParam, RGB(255, 255, 255));
		return (long)GetStockObject(DKGRAY_BRUSH);
	}
	case WM_PAINT:
	{
		DrawSkillTable();
	}
	default:
	{
		return DefWindowProc(Wnd, Message, wParam, lParam);
	}
	}
}

//---------------------------------------------------------------------------
void MultiSkillsWindowClass::TrackMouse(HWND hwnd)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE; //Type of events to track & trigger.
	tme.dwHoverTime = 50; //How long the mouse has to be in the window to trigger a hover event.
	tme.hwndTrack = hwnd;
	TrackMouseEvent(&tme);
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::HandleLeftMouseButtonClick(int x, int y)
{
	string Description;
	//int Index;
	int Width;
	int Height;
	int X, Y;
	//int Position;
	float PointsSpent;
	float PointLimit;
	float PointRaise;
	int PointsRemain;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	RECT Frame;
	UIManager = InterfaceManager.GetUIComponents();
	//Check Skills Frame
	GetWindowRect(SkillFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiSkillsHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Find Skill First
		int Index = -1;
		for (int i = 0; i < NUMSKILLS; i++)
		{
			ss.str("");
			ss << "SkillBox" << i << "_1";
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}

		}
		if (Index != -1)
		{
			for (unsigned int i = 0; i < HEROICLEVELS; i++)
			{
				ss.str("");
				ss << "SkillBox" << Index << "_" << i;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX);
				Y = static_cast<int>(Graphic->BaseLocationY);
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				if (x >= X && x <= X + Width)
				{
					PointsSpent = GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(Index), i+1);
					if (Data.IsSkillPrimary(Character.GetClass(i+1), Index) == true)
						PointRaise = 1.0f;
					else
						PointRaise = 0.5f;
					PointLimit = GetSkillPointSpendLimit(static_cast<SKILLS>(Index), i + 1);
					PointsRemain = CalculateAvailableSkillPoints(i+1);
					if ((PointsSpent + PointRaise) <= PointLimit && PointsRemain > 0)
					{
						SpendSkillPoint(static_cast<SKILLS>(Index), i + 1, 1);
						UpdateAll = false;
						SkillChange = true;
						CurrentSkill = static_cast<SKILLS>(Index);
						CurrentLevel = i + 1;
						DrawSkillTable();
						EnableWindow(AcceptButton, true);
						UpdateAll = true;
						break;
					}
				}

			}
		}
	}
	//Check Auto Fill Frame
	GetWindowRect(AutoSkillFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiSkillsHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{

		//Find Skill First
		int Index = -1;
		for (int i = 0; i < NUMSKILLS; i++)
		{
			ss.str("");
			ss << "SkillAutoText" << i;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}
		}
		if (Index != -1)
		{
			//Check Skill Rank Decrease
			ss.str("");
			ss << "SkillAutoTextLeftArrow" << Index;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width)
			{
				if (SetTotalValue[Index] > 0)
				{
					SetTotalValue[Index] -= 1;
					DrawAutoRank();
				}

			}


			//Check SkillRank Increase
			ss.str("");
			ss << "SkillAutoTextRightArrow" << Index;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width)
			{
				if (SetTotalValue[Index] < 23)
				{
					SetTotalValue[Index] += 1;
					DrawAutoRank();
				}
			}

			//Check Priority Decrease
			ss.str("");
			ss << "SkillAutoRankLeftArrow" << Index;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width)
			{
				if (PriorityValue[Index] > 1)
				{
					PriorityValue[Index] -= 1;
					DrawAutoRank();
				}
			}
			//check Priority Increase
			ss.str("");
			ss << "SkillAutoRankRightArrow" << Index;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width)
			{
				if (PriorityValue[Index] < 5)
				{
					PriorityValue[Index] += 1;
					DrawAutoRank();
				}
			}

		}

	}

}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::AutoSetRanks()
{
	//int TempSkills[NUMSKILLS][HEROICLEVELS];
	vector<int> PriorityList[6];
	vector<int> tempPriorityList;
	bool skillrankchanged;
	CLASS currentClass;
	float PointsSpent, PointRaise, PointLimit;
	int PointsRemain;
	bool CrossSkill, PrimeSkill, ClassOnlySkill;
	//Reset Skill Table
	ResetSkillValues();

	//Get PriorityList
	for (int x = 1; x <= 5; x++)
	{
		
		for (int i = 0; i < NUMSKILLS; i++)
		{
			if (PriorityValue[i] == x)
				PriorityList[x].push_back(i);
		}
	}
	//Check each Priority
	for (int iPriority = 1; iPriority <= 5; iPriority++)
	{
		for (int currentLevel = 1; currentLevel <= HEROICLEVELS; currentLevel++)
		{
			currentClass = Character.GetClass(currentLevel, false);
			tempPriorityList = PriorityList[iPriority];
			//Check if Priority has Count
			if (tempPriorityList.size() > 0)
			{
				do
				{
					skillrankchanged = false;
					//cycle though the skills for current Priority
					for (int cPriority = 0; cPriority < static_cast<int>(tempPriorityList.size()); cPriority++)
					{

						if (Data.IsSkillPrimary(currentClass, tempPriorityList[cPriority]) && UseClassFirst)
						{
							float CurrentSkillValue = GetTotalSkillPointsSpentDisplay(static_cast<SKILLS> (tempPriorityList[cPriority]));
							if (CurrentSkillValue < SetTotalValue[tempPriorityList[cPriority]] && CurrentSkillValue <= currentLevel + 3)
							{
								PointsSpent = GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(tempPriorityList[cPriority]), currentLevel);
								if (Data.IsSkillPrimary(Character.GetClass(currentLevel), tempPriorityList[cPriority]) == true)
									PointRaise = 1.0f;
								else
									PointRaise = 0.5f;
								PointLimit = GetSkillPointSpendLimit(static_cast<SKILLS>(tempPriorityList[cPriority]), currentLevel);
								PointsRemain = CalculateAvailableSkillPoints(currentLevel);
								if ((PointsSpent + PointRaise) <= PointLimit && PointsRemain > 0)
								{
									SpendSkillPoint(static_cast<SKILLS>(tempPriorityList[cPriority]), currentLevel, 1);
									skillrankchanged = true;
									DEBUG(to_string(static_cast<SKILLS>(tempPriorityList[cPriority])) + " Class Skill");
								}
							}
						}
						
					}
					
				} while (skillrankchanged && CalculateAvailableSkillPoints(CurrentLevel) > 0);
			}
		}
		//fill non class skills
		for (int currentLevel = 1; currentLevel <= HEROICLEVELS; currentLevel++)
		{
			currentClass = Character.GetClass(currentLevel, false);
			tempPriorityList = PriorityList[iPriority];
			//check if Priory has a Skill listed
			{
				if (tempPriorityList.size() > 0)
				{
					do
					{
						skillrankchanged = false;
						//cycle throu skills at priority level
						for (int cPriority = 0; cPriority < static_cast<int>(tempPriorityList.size()); cPriority++)
						{
							//Check for Classonly or if skill has been taken
							CrossSkill = Data.IsSkillCross(currentClass, tempPriorityList[cPriority]);
							PrimeSkill = Data.IsSkillPrimary(currentClass, tempPriorityList[cPriority]);
							ClassOnlySkill = !(CrossSkill || PrimeSkill);

							if (!ClassOnlySkill || Character.HasSkill(tempPriorityList[cPriority], currentLevel))
							{
								float CurrentSkillValue = GetTotalSkillPointsSpentDisplay(static_cast<SKILLS> (tempPriorityList[cPriority]));
								if (CurrentSkillValue < SetTotalValue[tempPriorityList[cPriority]] && CurrentSkillValue <= currentLevel + 3)
								{
									PointsSpent = GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(tempPriorityList[cPriority]), currentLevel);
									if (Data.IsSkillPrimary(Character.GetClass(currentLevel ), tempPriorityList[cPriority]) == true)
										PointRaise = 1.0f;
									else
										PointRaise = 0.5f;
									PointLimit = GetSkillPointSpendLimit(static_cast<SKILLS>(tempPriorityList[cPriority]), currentLevel);
									PointsRemain = CalculateAvailableSkillPoints(currentLevel );
									if ((PointsSpent + PointRaise) <= PointLimit && PointsRemain > 0)
									{
										SpendSkillPoint(static_cast<SKILLS>(tempPriorityList[cPriority]), currentLevel, 1);
										skillrankchanged = true;
										DEBUG(to_string(static_cast<SKILLS>(tempPriorityList[cPriority])) + " non Class Skill");
									}
								}
							}
						}

						DEBUG(skillrankchanged);
					} while (skillrankchanged);
				}
			}
		}






	}

	UpdateAll = true;
	HDC hdc;
	hdc = GetDC(MultiSkillsHandle);
	ClearSkillFrame(hdc);
	ReleaseDC(MultiSkillsHandle, hdc);
	DrawSkillTable();
	EnableWindow(AcceptButton, true);

}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::HandleRightMouseButtonClick(int x, int y)
{


	string Description;
	//int Index;
	int Width;
	int Height;
	int X, Y;
	//int Position;
	float PointsSpent;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	RECT Frame;
	UIManager = InterfaceManager.GetUIComponents();
	//Check Selection Frame
	GetWindowRect(SkillFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiSkillsHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Find Skill First
		int Index = -1;
		for (int i = 0; i < NUMSKILLS; i++)
		{
			ss.str("");
			ss << "SkillBox" << i << "_1";
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}

		}
		if (Index != -1)
		{
			for (unsigned int i = 0; i < HEROICLEVELS; i++)
			{
				ss.str("");
				ss << "SkillBox" << Index << "_" << i;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX);
				Y = static_cast<int>(Graphic->BaseLocationY);
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				if (x >= X && x <= X + Width)
				{
					PointsSpent = (float)GetLevelSkillPointsSpent(static_cast<SKILLS>(Index), i+1);
					if (PointsSpent > 0)
					{
						SpendSkillPoint(static_cast<SKILLS>(Index), i + 1, -1);

						UpdateAll = false;
						SkillChange = true;
						CurrentSkill = static_cast<SKILLS>(Index);
						CurrentLevel = i + 1;
						DrawSkillTable();
						EnableWindow(AcceptButton, true);				
						break;
					}
				}

			}
		}
	}
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::HandleMouseHover(int x, int y)
{
	string Description;
	int Index = -1;
	int Width;
	int Height;
	int X, Y;
	//int Position;
	//float PointsSpent;
	//float PointLimit;
	//float PointRaise;
	//int PointsRemain;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	RECT Frame;
	UIManager = InterfaceManager.GetUIComponents();
	//Check Selection Frame
	GetWindowRect(SkillFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiSkillsHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Find Skill First
		for (int i = 0; i < NUMSKILLS; i++)
		{
			ss.str("");
			ss << "SkillBox" << i << "_1";
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}
		}
	}
	GetWindowRect(AutoSkillFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiSkillsHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Find Skill First
		for (int i = 0; i < NUMSKILLS; i++)
		{
			ss.str("");
			ss << "SkillAutoText" << i;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTISKILLSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}
		}
	}
	if (Index >= 0)
		CurrentSkill = static_cast<SKILLS>(Index);
}

//---------------------------------------------------------------------------
HWND MultiSkillsWindowClass::GetHandle()
{
	return MultiSkillsHandle;
}
//---------------------------------------------------------------------------
void MultiSkillsWindowClass::DeleteGraphics()
{
	DeleteObject(SkillClassBox.Graphic);
	DeleteObject(SkillClassBox.Mask);
	DeleteObject(SkillNormalBox.Graphic);
	DeleteObject(SkillNormalBox.Mask);
	DeleteObject(SkillErrorBox.Graphic);
	DeleteObject(SkillErrorBox.Mask);
	DeleteObject(RightArrow.Graphic);
	DeleteObject(RightArrow.Mask);
	DeleteObject(LeftArrow.Graphic);
	DeleteObject(LeftArrow.Mask);


	DeleteObject(Palette);
}