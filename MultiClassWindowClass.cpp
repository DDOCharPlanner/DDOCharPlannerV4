#include "PrintWindowClass.h"
#include "MultiClassWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "DataClass.h"
#include <time.h> 

//---------------------------------------------------------------------------
MultiClassWindowClass::MultiClassWindowClass()
{
	Dragging = false;
}

//---------------------------------------------------------------------------
MultiClassWindowClass::~MultiClassWindowClass()
{
	DeleteObject(TitleFontLarge);
	DeleteObject(DefaultFont);
	DeleteGraphics();
}

//---------------------------------------------------------------------------
void MultiClassWindowClass::Create(HINSTANCE Instance, HWND Parent)
{
	InterfaceComponentStruct *Component;
	WNDCLASSEX wc;
	int ScreenX;
	int ScreenY;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Class Window";
	LOGBRUSH lb;
	LOGFONT lf;
	UIComponentManager *UIManager;

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
	MultiClassHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1000, 730, Parent, NULL, Instance, NULL);
	SetClassLong(MultiClassHandle, 0, (long)MULTICLASSWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(MultiClassHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiClassHandle, Parent, (ScreenX / 2) - (WindowX / 2), (int)(ScreenY / 2) - (WindowY / 2), 400, 300, SWP_NOSIZE);
	
	
	UIManager = InterfaceManager.GetUIComponents();
	//the child windows
	Component = UIManager->GetComponentData("MultiClassText", MULTICLASSWINDOW);
	MultiClassText = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("Close", MULTICLASSWINDOW);
	Close = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("ClassString", MULTICLASSWINDOW);
	ClassString = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("DescriptionWindow", MULTICLASSWINDOW);
	DescriptionWindow = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("ClassListFrame", MULTICLASSWINDOW);
	ClassListFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("SelectionFrame", MULTICLASSWINDOW);
	SelectionFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("LevelLabel", MULTICLASSWINDOW);
	LevelLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("ClassLabel", MULTICLASSWINDOW);
	ClassLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("ClassLevelLabel", MULTICLASSWINDOW);
	ClassLevelLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("BABLabel", MULTICLASSWINDOW);
	BABLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiClassHandle, (HMENU)Component->WindowID, Instance, nullptr);


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
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Ariel"));
	DefaultFont = CreateFontIndirect(&lf);
	TitleFontLarge = CreateFontIndirect(&lf);
	

	//background color changes
	SendMessage(DescriptionWindow, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 0));
	
	LoadGraphics(MultiClassHandle);
}

//---------------------------------------------------------------------------
void MultiClassWindowClass::Show(bool State)
{
	ostringstream Text;

	//pop it up
	ShowWindow(MultiClassHandle, State);
	ShowWindow(MultiClassText, State);
	ShowWindow(Close, State);
	ShowWindow(ClassString, State);
	ShowWindow(DescriptionWindow, State);
	ShowWindow(ClassListFrame, State);
	ShowWindow(SelectionFrame, State);
	ShowWindow(LevelLabel, State);
	ShowWindow(ClassLabel, State);
	ShowWindow(ClassLevelLabel, State);
	ShowWindow(BABLabel, State);


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

	GetWindowRect(MultiClassHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiClassHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2)+15, 0, 0, SWP_NOSIZE);
	
	string String1;
	String1 = "{\\b Drag Class Icon to the Top Row\\par ";
	String1 += "Left click Icon below at level to add class\\par ";
	String1 += "Right click Icon to remove class from level}\\par ";

	//Clear out SelectedClassIcons
	for (int i = 0; i < 3; i++)
		SelectedClassIcons[i] = CLASSNONE;	
	FillSelectList();
	FillDesc(String1, NULL);
	SetCharClassText();
	FillClassList();



}

//---------------------------------------------------------------------------
long MultiClassWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

	//RECT Rect;
	int pos;
	POINTS ps;
	POINT ps1;
	pos = GetMessagePos();
	ps = MAKEPOINTS(pos);
	ps1.x = ps.x;
	ps1.y = ps.y;
	ScreenToClient(MultiClassHandle, (LPPOINT)&ps1);
	switch (Message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if ((int)LOWORD(wParam) == MCL_CLOSE)
			{
				InterfaceManager.ShowChild(MULTICLASSWINDOW, false);
				return 0;
			}
		}
	}
	case WM_LBUTTONDOWN:
	{

		HandleLeftMouseButtonClick(ps1.x, ps1.y);
		return 0;
	}
	case WM_LBUTTONUP:
	{

		EndDragAndDropOperation(ps1.x, ps1.y);

		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		HandleRightMouseButtonClick(ps1.x, ps1.y);
		return 0;
	}





	case WM_CTLCOLORSTATIC:
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		SetTextColor((HDC)wParam, RGB(255, 255, 255));
		return (long)GetStockObject(DKGRAY_BRUSH);
	}
	case WM_SETCURSOR:
	{
		if (Dragging == true)
		{
			SetCursor(Cursor);
			return 1;
		}
		if ((HWND)wParam == DescriptionWindow)
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return 1;
		}
		return DefWindowProc(Wnd, Message, wParam, lParam);
	}
	case WM_DRAWITEM:
	{
		if (InterfaceManager.ChildWindowVisible() == true)
			return true;
	}
	case WM_PAINT:
	{
		FillSelectList();
		SetCharClassText();
		FillClassList();
	}

	default:
	{
		return DefWindowProc(Wnd, Message, wParam, lParam);
	}
	}
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::HandleLeftMouseButtonClick(int x, int y)
{

	string Description;
	int Index;
	int Width;
	int Height;
	int X, Y;
	//int Position;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	RECT Frame;
	int Level;

	UIManager = InterfaceManager.GetUIComponents();
	//Check Class Panel
	GetWindowRect(ClassListFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiClassHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		Index = -1;
		for (unsigned int i = 0; i<NUMCLASSES; i++)
		{
			ss.str("");
			ss << "ClassIcon" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX)+Frame.left;
			Y = static_cast<int>(Graphic->BaseLocationY)+Frame.top;
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}
				
		}
		if (Index != -1)
		{
			DragIcon = Index;
			Description = "{\\b ";
			Description += Data.GetClassNameA(Index);
			Description += "} \\par\\par ";
			Description += Data.GetClassDescription(Index);
			while (Description.find("$RACE") != std::string::npos)
				Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
			//add in the prereqs lists
			Description += " \\par\\par ";
			FillDesc(Description, ClassIcon[Index].Graphic);
			if (AlignmentValid[Index])
			{
				Dragging = true;
				Cursor = CreateCursorFromBitmap(MultiClassHandle, Palette, &ClassIcon[Index], RGB(0, 0, 0), 16, 16);
				SetCursor(Cursor);
			}
			return;
		}



	}
	//Check Selection Frame
	GetWindowRect(SelectionFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiClassHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Check Selection Box
		Index = -1;
		for (unsigned int i = 0; i < 3; i++)
		{
			ss.str("");
			ss << "SelectClassIcon" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX) + Frame.left;
			Y = static_cast<int>(Graphic->BaseLocationY) + Frame.top;
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}

		}
		if (Index != -1)
		{
			if (SelectedClassIcons[Index] != CLASSNONE)
				DragIcon = (int)SelectedClassIcons[Index];
			else
				return;



			Description = "{\\b ";
			Description += Data.GetClassNameA(DragIcon);
			Description += "} \\par\\par ";
			Description += Data.GetClassDescription(DragIcon);
			while (Description.find("$RACE") != std::string::npos)
				Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
			//add in the prereqs lists
			Description += " \\par\\par ";
			FillDesc(Description, ClassIcon[DragIcon].Graphic);
			if (AlignmentValid[DragIcon])
			{
				Dragging = true;
				Cursor = CreateCursorFromBitmap(MultiClassHandle, Palette, &ClassIcon[DragIcon], RGB(0, 0, 0), 16, 16);
				SetCursor(Cursor);
			}


			return;
		}

		//Check Level Boxes
		Index = -1;
		Level = -1;
		for (unsigned int i = 0; i < 3; i++)
		{
			for (int l = 0; l < 20; l++)
			{
				ss.str("");
				ss << "Class" << i + 1 << "Icon" << l;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX) + Frame.left;
				Y = static_cast<int>(Graphic->BaseLocationY) + Frame.top;
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Index = i;
					Level = l;
					break;
				}
			}
		}
		if (Index != -1)
		{
			if (SelectedClassIcons[Index] == CLASSNONE)
				return;
			DragIcon = (int)SelectedClassIcons[Index];

			Description = "{\\b ";
			Description += Data.GetClassNameA(DragIcon);
			Description += "} \\par\\par ";
			Description += Data.GetClassDescription(DragIcon);
			while (Description.find("$RACE") != std::string::npos)
				Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
			//add in the prereqs lists
			Description += " \\par\\par ";
			FillDesc(Description, ClassIcon[DragIcon].Graphic);


			//Change Class and Add Icon to list
			if (Level != 0)
			{
			
				Character.EnableValidations(false);
			Character.SetClass(SelectedClassIcons[Index], Level + 1);
			Character.EnableValidations(true);
			ClassAtLevel[Level] = SelectedClassIcons[Index];
			FillSelectList();
			}

			return;
		}

	}
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::HandleRightMouseButtonClick(int x, int y)
{

	string Description;
	int Index;
	int Width;
	int Height;
	int X, Y;
	//int Position;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	RECT Frame;
	int Level;
	bool ClassChanged;
	CLASS NewClassAtLevel[20];
	for (int i = 0; i < 20; i++)
	{
		NewClassAtLevel[i] = ClassAtLevel[i];
	}
	UIManager = InterfaceManager.GetUIComponents();
	//Check Selection Frame
	GetWindowRect(SelectionFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiClassHandle, (LPPOINT)&Frame, 2);
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Check Selection Box
		Index = -1;
		for (unsigned int i = 0; i < 3; i++)
		{
			ss.str("");
			ss << "SelectClassIcon" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX) + Frame.left;
			Y = static_cast<int>(Graphic->BaseLocationY) + Frame.top;
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}

		}
		if (Index != -1)
		{
			CLASS TempClass1;
			ClassChanged = false;
			if (SelectedClassIcons[Index] != CLASSNONE)
			{
				//DragIcon = (int)SelectedClassIcons[Index];
				switch (Index)
				{
				case 0:
				{
					if (SelectedClassIcons[1] != CLASSNONE)
					{
						TempClass1 = SelectedClassIcons[1];
						for (int i = 0; i < 20; i++)
						{
							if (NewClassAtLevel[i] == SelectedClassIcons[Index])
							{
								NewClassAtLevel[i] = SelectedClassIcons[1];
								ClassChanged = true;
							}
								
						}
						SelectedClassIcons[0] = SelectedClassIcons[1];
						SelectedClassIcons[1] = SelectedClassIcons[2];
						SelectedClassIcons[2] = CLASSNONE;
					}
					break;
				}
				case 1:
				{
					for (int i = 0; i < 20; i++)
					{
						if (NewClassAtLevel[i] == SelectedClassIcons[Index])
						{
							NewClassAtLevel[i] = SelectedClassIcons[0];
							ClassChanged = true;
						}
					}
					SelectedClassIcons[1] = SelectedClassIcons[2];
					SelectedClassIcons[2] = CLASSNONE;
					break;
				}
				case 2:
				{
					for (int i = 0; i < 20; i++)
					{
						if (NewClassAtLevel[i] == SelectedClassIcons[Index])
						{
							NewClassAtLevel[i] = SelectedClassIcons[0];
							ClassChanged = true;
						}
					}
					SelectedClassIcons[2] = CLASSNONE;
					break;
				}
				}


				if (ClassChanged)
				{

					for (int i = 0; i < 20; i++)
					{
						if (ClassAtLevel[i] != NewClassAtLevel[i])
						{
							Character.EnableValidations(false);
							Character.SetClass(NewClassAtLevel[i], i + 1);
							Character.EnableValidations(true);
						}
							

					}

					
				}
				FillSelectList();
				return;
			}
			else
				return;



		}

		//Check Level Boxes
		Index = -1;
		Level = -1;
		for (unsigned int i = 0; i < 3; i++)
		{
			for (int l = 0; l < 20; l++)
			{
				ss.str("");
				ss << "Class" << i + 1 << "Icon" << l;
				Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX) + Frame.left;
				Y = static_cast<int>(Graphic->BaseLocationY) + Frame.top;
				Width = static_cast<int>(Graphic->BaseWidth);
				Height = static_cast<int>(Graphic->BaseHeight);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Index = i;
					Level = l;
					break;
				}
			}
		}
		if (Index > 0)
		{
			
			if (SelectedClassIcons[Index] == CLASSNONE)
				return;

			//Change Class and Add Icon to list
			Character.EnableValidations(false);
			Character.SetClass(SelectedClassIcons[0], Level + 1);
			Character.EnableValidations(true);
			ClassAtLevel[Level] = SelectedClassIcons[Index];

			FillSelectList();
			return;
		}

	}
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::EndDragAndDropOperation(int x, int y)
{
	string Description;
	int Index;
	int Width;
	int Height;
	int X, Y;
	//int Position;
	ostringstream ss;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	RECT Frame;
	bool ClassChanged;
	//int Level;
	CLASS NewClassAtLevel[20];
	for (int i = 0; i < 20; i++)
	{
	NewClassAtLevel[i] = ClassAtLevel[i];
	}
	
	UIManager = InterfaceManager.GetUIComponents();
	//Check Selection Frame
	GetWindowRect(SelectionFrame, &Frame);
	MapWindowPoints(HWND_DESKTOP, MultiClassHandle, (LPPOINT)&Frame, 2);
	ClassChanged = false;
	if (x >= Frame.left && x <= Frame.right && y >= Frame.top && y <= Frame.bottom)
	{
		//Check is Class is already selected
		for (int i = 0; i < 3; i++)
		{
			if (SelectedClassIcons[i] == (CLASS)DragIcon)
			{
				Dragging = false;
				return;
			}
				
		}
		//Check Selection Box
		Index = -1;
		for (unsigned int i = 0; i < 3; i++)
		{
			ss.str("");
			ss << "SelectClassIcon" << i + 1;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX) + Frame.left;
			Y = static_cast<int>(Graphic->BaseLocationY) + Frame.top;
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
			{
				Index = i;
				break;
			}

		}
		if (Index != -1)
		{
			if (SelectedClassIcons[Index] == CLASSNONE)
			{
				SelectedClassIcons[Index] = ClassSlot[DragIcon];
			}
			else
			{
				if (SelectedClassIcons[Index] == ClassSlot[DragIcon])
					return;
				for (int i = 0; i < 20; i++)
				{
					if (NewClassAtLevel[i] == SelectedClassIcons[Index])
					{
						NewClassAtLevel[i] = ClassSlot[DragIcon];
						ClassChanged = true;
					}
				}
				SelectedClassIcons[Index] = ClassSlot[DragIcon];
			}
			if (ClassChanged)
			{
				FillSelectList();

				for (int i = 0; i < 20; i++)
				{
					Character.EnableValidations(false);
					Character.SetClass(NewClassAtLevel[i], i + 1);
					Character.EnableValidations(false);
				}
				
			}
				
			FillSelectList();
		}
	}
	Dragging = false;
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::LoadGraphics(HWND Parent)
{
	HDC hdc;

	//palette for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	//the class icons (14 of these)
	LoadBitmap("Fighter", "Classes", &ClassIcon[0]);
	LoadBitmap("Paladin", "Classes", &ClassIcon[1]);
	LoadBitmap("Barbarian", "Classes", &ClassIcon[2]);
	LoadBitmap("Monk", "Classes", &ClassIcon[3]);
	LoadBitmap("Rogue", "Classes", &ClassIcon[4]);
	LoadBitmap("Ranger", "Classes", &ClassIcon[5]);
	LoadBitmap("Cleric", "Classes", &ClassIcon[6]);
	LoadBitmap("Wizard", "Classes", &ClassIcon[7]);
	LoadBitmap("Sorcerer", "Classes", &ClassIcon[8]);
	LoadBitmap("Bard", "Classes", &ClassIcon[9]);
	LoadBitmap("Favored Soul", "Classes", &ClassIcon[10]);
	LoadBitmap("Artificer", "Classes", &ClassIcon[11]);
	LoadBitmap("Druid", "Classes", &ClassIcon[12]);
	LoadBitmap("Warlock", "Classes", &ClassIcon[13]);
	LoadBitmap("EmptyClassSlot", "UserInterface", &emptyclass);
	LoadBitmap("UnclaimedClassSlot", "Userinterface", &UnclaimedClassSlot);
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::SetCharClassText()
{
	string Text;
	ostringstream ss;
	int ClassLevel[NUMCLASSES];
	//bool First;

	for (unsigned int i = 0; i<NUMCLASSES; i++)
		ClassLevel[i] = Character.GetClassLevel(CLASS(i), 20);
	ss.str("");
	ss << Data.GetAlignmentString(Character.GetAlignment()) << " ";
	ss << Character.GetRaceString();
	if (Character.GetSex() == MALE)
		ss << " Male (";
	else
		ss << " Female (";

	ss << Character.GetClassString(20);
	ss << ")";

	Text = ss.str();
	SendMessage(ClassString, WM_SETTEXT, 0, (LPARAM)Text.c_str());
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::FillClassList()
{
	ALIGNMENT Alignment;

	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	SIZE size;
	int textshift;
	string TextString;
	hdc = GetWindowDC(ClassListFrame);
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	//get Valid Alignment
	Alignment = Character.GetAlignment();
	for (unsigned int i = 0; i<NUMCLASSES; i++)
	{
		ClassSlot[i] = (CLASS)i;
		AlignmentValid[i] = false;
		if (Data.IsAlignmentCompatable((CLASS)i, Alignment) == true)
		{
			AlignmentValid[i] = true;
		}
	}
	//draw the class icons
	for (unsigned int i = 0; i<NUMCLASSES; i++)
	{
		if (ClassSlot[i] == CLASSNONE)
			break;
		ss.str("");
		ss << "ClassIcon" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);

		if (AlignmentValid[i])
			DrawGraphic(hdc, &ClassIcon[ClassSlot[i]], X, Y, Width, Height);
		else
			DrawGraphicGreyscale(hdc, &ClassIcon[ClassSlot[i]], X, Y, Width, Height);

		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "ClassText" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);

		TextString = Data.GetClassNameA(i);
		if (TextString == "Favored Soul")
			TextString = "Fav Soul";
		GetTextExtentPoint32(hdc, TextString.c_str(), TextString.size(), &size);
		textshift = static_cast<int>(Graphic->BaseWidth / 2) - static_cast<int>(size.cx / 2);
		TextOut(hdc, X + textshift, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);
		

	}
	ReleaseDC(ClassListFrame, hdc);
}

void MultiClassWindowClass::FillSelectList()
{
	//ShowWindow(SelectionFrame, false);
	//ShowWindow(SelectionFrame, true);
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	hdc = GetWindowDC(SelectionFrame);
	string TextString;

	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	ClearSelectionFrame(hdc);
	CLASS CharClasses[3];

	//Get Selected Classes
	for (int i = 0; i < 20; i++)
	{
		ClassAtLevel[i] = Character.GetClass(i + 1, false);
	}
	Character.GetMulticlassClasses(20, CharClasses);
	for (int i = 0; i < 3; i++)
	{
		if (CharClasses[i] != CLASSNONE)
		{
			if (SelectedClassIcons[i] == CLASSNONE)
				SelectedClassIcons[i] = CharClasses[i];
		}
	}



	//Set all levels with out a class to first class
	for (int i = 0; i < 20; i++)
	{			
		if (ClassAtLevel[i] == CLASSNONE)
		{
			Character.EnableValidations(false);
			Character.SetClass(ClassAtLevel[0], i + 1);
			Character.EnableValidations(true);
			ClassAtLevel[i] = ClassAtLevel[0];
		}
	}

	//Draw Selection Bar with known and empty Class boxes
	for (int i = 0; i < 3; i++)
	{
		ss.str("");
		ss << "SelectClassIcon" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		DrawGraphic(hdc, &emptyclass, X, Y, Width, Height);
		if (SelectedClassIcons[i] != CLASSNONE)
			DrawGraphic(hdc, &ClassIcon[SelectedClassIcons[i]], X, Y, Width, Height);

	}

	//Fill in table

	for(int i = 0; i < 20; i++)
	{


		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "LevelText" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = to_string(i+1);
		TextOut(hdc, X+18, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);

		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "ClassTextAtLevel" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = Data.GetClassNameA((int)Character.GetClass(i + 1,false));
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);

		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "ClassLevelText" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = to_string(Character.GetClassLevel(Character.GetClass(i + 1, false), i + 1));
		TextOut(hdc, X + 18, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);
		
		//OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "Class1Icon" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		DrawGraphic(hdc, &UnclaimedClassSlot, X, Y, Width, Height);
		if (ClassAtLevel[i] == SelectedClassIcons[0])
			DrawGraphic(hdc, &ClassIcon[SelectedClassIcons[0]], X, Y, Width, Height);
		//SetTextColor(hdc, OldColor);
		if (i != 0)
		{
			//OldColor = SetTextColor(hdc, RGB(255, 255, 255));
			ss.str("");
			ss << "Class2Icon" << i;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			DrawGraphic(hdc, &UnclaimedClassSlot, X, Y, Width, Height);
			if (ClassAtLevel[i] == SelectedClassIcons[1])
				DrawGraphic(hdc, &ClassIcon[SelectedClassIcons[1]], X, Y, Width, Height);
			//SetTextColor(hdc, OldColor);

			//OldColor = SetTextColor(hdc, RGB(255, 255, 255));
			ss.str("");
			ss << "Class3Icon" << i;
			Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX);
			Y = static_cast<int>(Graphic->BaseLocationY);
			Width = static_cast<int>(Graphic->BaseWidth);
			Height = static_cast<int>(Graphic->BaseHeight);
			DrawGraphic(hdc, &UnclaimedClassSlot, X, Y, Width, Height);
			if (ClassAtLevel[i] == SelectedClassIcons[2])
				DrawGraphic(hdc, &ClassIcon[SelectedClassIcons[2]], X, Y, Width, Height);
			//SetTextColor(hdc, OldColor);
		}
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "BABText" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTICLASSWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		TextString = to_string(Character.CalculateBAB(i+1));
		TextOut(hdc, X+18, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);	
	}

	ReleaseDC(SelectionFrame, hdc);
	SetCharClassText();
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::FillDesc(string Description, HBITMAP Bitmap)
{
	EDITSTREAM Stream;
	SendMessage(DescriptionWindow, LB_RESETCONTENT, 0, 0);
	Stream.dwCookie = (DWORD)Description.c_str();
	Stream.dwError = false;
	Stream.pfnCallback = EditStreamCallback;
	SendMessage(DescriptionWindow, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);

	//test the rich edit box graphics drawer
	if (Bitmap != NULL)
		RichEditBitmap.InsertBitmap(DescriptionWindow, Bitmap);
}
//---------------------------------------------------------------------------
HWND MultiClassWindowClass::GetHandle()
{
	return MultiClassHandle;
}
//---------------------------------------------------------------------------
void MultiClassWindowClass::ClearSelectionFrame(HDC hdc)
{
	RECT rc;
	LOGBRUSH lb;
	// Erase the whole bitmap background.
	GetClientRect(SelectionFrame, &rc);
	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	rc.top += 50;
	rc.left += 5;
	rc.right -= 5;
	rc.bottom -= 5;
	FillRect(hdc, &rc, hbrBkGnd);
}
void MultiClassWindowClass::DeleteGraphics()
{
	
	DeleteObject(emptyclass.Mask);
	DeleteObject(emptyclass.Graphic);
	DeleteObject(UnclaimedClassSlot.Mask);
	DeleteObject(UnclaimedClassSlot.Graphic);
	for (int i = 0; i < NUMCLASSES; i++)
	{
		DeleteObject(ClassIcon[i].Graphic);
		DeleteObject(ClassIcon[i].Mask);
	}
}