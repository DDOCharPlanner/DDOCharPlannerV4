//---------------------------------------------------------------------------
#include "LoadWindowClass.h"
#include "InterfaceManagerClass.h"
#include "resource.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
LoadWindowClass::LoadWindowClass()
    {
    }

//---------------------------------------------------------------------------
LoadWindowClass::~LoadWindowClass()
    {
    DeleteGraphics();
    }

//---------------------------------------------------------------------------
void LoadWindowClass::Create(HINSTANCE Instance, HWND Parent)
    {
    WNDCLASSEX wc;
    int ScreenX;
    int ScreenY;
    RECT WindowRect;
    int WindowX;
    int WindowY;
    static char WindowName[] = "Load Window";
	char OutputString[MAX_PATH];
	string FullPathFile;
	GetCurrentDirectory(MAX_PATH, OutputString);
	FullPathFile = OutputString;
	FullPathFile += "\\Graphics\\DDOCP.ico";
    //fill in the class attributes for the main window
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 4;
    wc.cbWndExtra = 0;
    wc.hInstance = Instance;
	wc.hIcon = (HICON)LoadImage(NULL, FullPathFile.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	DWORD msg = GetLastError();
	//wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WindowName;
	wc.hIconSm = (HICON)LoadImage(NULL, FullPathFile.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);

    //register
    RegisterClassEx(&wc);



    //create and center the window on screen
    LoadWindowHandle = CreateWindowEx(NULL, WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 300, 240, Parent, NULL, Instance, NULL);
    SetClassLong(LoadWindowHandle, 0, (long)DATALOAD);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(LoadWindowHandle, &WindowRect);
    WindowX = WindowRect.right - WindowRect.left;
    WindowY = WindowRect.bottom - WindowRect.top;
    SetWindowPos(LoadWindowHandle, NULL, (ScreenX/2)-(WindowX/2), (int)(ScreenY/2.5f)-(WindowY/2), 0, 0, SWP_NOSIZE);
	SendMessage(Parent, WM_SETICON, ICON_BIG, (LPARAM)wc.hIcon);
	SendMessage(Parent, WM_SETICON, ICON_SMALL, (LPARAM)wc.hIconSm);

    //put up the labels
    LoadRaceLabel = CreateWindowEx(NULL, "STATIC", "Load Race File", WS_CHILD, 25, 10, 200, 20, LoadWindowHandle, (HMENU)LW_LOADRACELABEL, Instance, NULL);
    LoadClassLabel = CreateWindowEx(NULL, "STATIC", "Load Class File", WS_CHILD, 25, 30, 200, 20, LoadWindowHandle, (HMENU)LW_LOADCLASSLABEL, Instance, NULL);
    LoadFeatLabel = CreateWindowEx(NULL, "STATIC", "Load Feat File", WS_CHILD, 25, 50, 200, 20, LoadWindowHandle, (HMENU)LW_LOADFEATLABEL, Instance, NULL);
    LoadSkillLabel = CreateWindowEx(NULL, "STATIC", "Load Skill File", WS_CHILD, 25, 70, 200, 20, LoadWindowHandle, (HMENU)LW_LOADSKILLLABEL, Instance, NULL);
    LoadEnhancementLabel = CreateWindowEx(NULL, "STATIC", "Load Enhancement File", WS_CHILD, 25, 90, 200, 20, LoadWindowHandle, (HMENU)LW_LOADENHANCEMENTLABEL, Instance, NULL);
    LoadSpellLabel = CreateWindowEx(NULL, "STATIC", "Load Spell File", WS_CHILD, 25, 110, 200, 20, LoadWindowHandle, (HMENU)LW_LOADSPELLLABEL, Instance, NULL);
	LoadItemEffectLabel = CreateWindowEx (NULL, "STATIC", "Load Item Effect File", WS_CHILD, 25, 130, 200, 20, LoadWindowHandle, (HMENU)LW_LOADITEMEFFECTLABEL, Instance, NULL);
	LoadItemClickyEffectLabel = CreateWindowEx (NULL, "STATIC", "Load Clicky Item Effect File", WS_CHILD, 25, 150, 200, 20, LoadWindowHandle, (HMENU)LW_LOADITEMCLICKYEFFECTLABEL, Instance, NULL);
	LoadItemLabel = CreateWindowEx (NULL, "STATIC", "Load Item File", WS_CHILD, 25, 170, 200, 20, LoadWindowHandle, (HMENU)LW_LOADITEMLABEL, Instance, NULL);
	LoadTemplateLabel = CreateWindowEx (NULL, "STATIC", "Load Template File", WS_CHILD, 25, 190, 200, 20, LoadWindowHandle, (HMENU)LW_LOADTEMPLATELABEL, Instance, NULL);
	LoadDestinyLabel = CreateWindowEx (NULL, "STATIC", "Load Destiny File", WS_CHILD, 25, 210, 200, 20, LoadWindowHandle, (HMENU)LW_LOADDESTINYLABEL, Instance, NULL);
    //load the graphics
    LoadGraphics();

    //set up the file states
    RaceFileState = FILEPENDING;
    ClassFileState = FILEPENDING;
    FeatFileState = FILEPENDING;
    SkillFileState = FILEPENDING;
    EnhancementFileState = FILEPENDING;
    SpellFileState = FILEPENDING;
	ItemEffectFileState = FILEPENDING;
	ItemClickyEffectFileState = FILEPENDING;
	ItemFileState = FILEPENDING;
	TemplateFileState = FILEPENDING;
	DestinyFileState = FILEPENDING;
    }

//---------------------------------------------------------------------------
void LoadWindowClass::Show(bool State)
    {
    //pop it up
    ShowWindow(LoadWindowHandle, State);
    ShowWindow(LoadRaceLabel, State);
    ShowWindow(LoadClassLabel, State);
    ShowWindow(LoadFeatLabel, State);
    ShowWindow(LoadSkillLabel, State);
    ShowWindow(LoadEnhancementLabel, State);
    ShowWindow(LoadSpellLabel, State);
	ShowWindow(LoadItemEffectLabel, State);
	ShowWindow(LoadItemClickyEffectLabel, State);
	ShowWindow(LoadItemLabel, State);
	ShowWindow(LoadTemplateLabel, State);
	ShowWindow(LoadDestinyLabel, State);
    }

//---------------------------------------------------------------------------
long LoadWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    PAINTSTRUCT ps;

    switch (Message)
        {
        case WM_CTLCOLORSTATIC:
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            SetTextColor((HDC)wParam, RGB(255,255,255));
            return (long)GetStockObject(NULL_BRUSH);
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

//---------------------------------------------------------------------------
void LoadWindowClass::LoadGraphics()
    {
    LoadBitmap("Check", "UserInterface", &CheckMark);
    LoadBitmap("Diamond", "UserInterface", &Diamond);
    LoadBitmap("FilledDiamond", "UserInterface", &FilledDiamond);
    LoadBitmap("Error", "UserInterface", &Error);
    }

//---------------------------------------------------------------------------
void LoadWindowClass::DeleteGraphics()
    {
    DeleteObject(CheckMark.Graphic);
    DeleteObject(CheckMark.Mask);
    DeleteObject(Diamond.Graphic);
    DeleteObject(Diamond.Mask);
    DeleteObject(FilledDiamond.Graphic);
    DeleteObject(FilledDiamond.Mask);
    DeleteObject(Error.Graphic);
    DeleteObject(Error.Mask);
    }

//---------------------------------------------------------------------------
void LoadWindowClass::DrawGraphics(HDC hdc)
    {
    //Race File
    if (RaceFileState == FILEPENDING)
        DrawGraphic(hdc, &Diamond, 5, 10, Diamond.Width, Diamond.Height);
    else if (RaceFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 10, FilledDiamond.Width, FilledDiamond.Height);
    else if (RaceFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 10, CheckMark.Width, CheckMark.Height);
    else if (RaceFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 10, Error.Width, Error.Height);

    //Class File
    if (ClassFileState == FILEPENDING)
        DrawGraphic(hdc, &Diamond, 5, 30, Diamond.Width, Diamond.Height);
    else if (ClassFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 30, FilledDiamond.Width, FilledDiamond.Height);
    else if (ClassFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 30, CheckMark.Width, CheckMark.Height);
    else if (ClassFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 30, Error.Width, Error.Height);

    //Feat File
    if (FeatFileState == FILEPENDING)
        DrawGraphic(hdc, &Diamond, 5, 50, Diamond.Width, Diamond.Height);
    else if (FeatFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 50, FilledDiamond.Width, FilledDiamond.Height);
    else if (FeatFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 50, CheckMark.Width, CheckMark.Height);
    else if (FeatFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 50, Error.Width, Error.Height);

    //Skill File
    if (SkillFileState == FILEPENDING)
        DrawGraphic(hdc, &Diamond, 5, 70, Diamond.Width, Diamond.Height);
    else if (SkillFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 70, FilledDiamond.Width, FilledDiamond.Height);
    else if (SkillFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 70, CheckMark.Width, CheckMark.Height);
    else if (SkillFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 70, Error.Width, Error.Height);

    //Enhancement File
    if (EnhancementFileState == FILEPENDING)
        DrawGraphic(hdc, &Diamond, 5, 90, Diamond.Width, Diamond.Height);
    else if (EnhancementFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 90, FilledDiamond.Width, FilledDiamond.Height);
    else if (EnhancementFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 90, CheckMark.Width, CheckMark.Height);
    else if (EnhancementFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 90, Error.Width, Error.Height);

    //Spell File
    if (SpellFileState == FILEPENDING)
        DrawGraphic(hdc, &Diamond, 5, 110, Diamond.Width, Diamond.Height);
    else if (SpellFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 110, FilledDiamond.Width, FilledDiamond.Height);
    else if (SpellFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 110, CheckMark.Width, CheckMark.Height);
    else if (SpellFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 110, Error.Width, Error.Height);

	//Item Effect File
	if (ItemEffectFileState == FILEPENDING)
		DrawGraphic(hdc, &Diamond, 5, 130, Diamond.Width, Diamond.Height);
	else if (ItemEffectFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 130, FilledDiamond.Width, FilledDiamond.Height);
    else if (ItemEffectFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 130, CheckMark.Width, CheckMark.Height);
    else if (ItemEffectFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 130, Error.Width, Error.Height);

	//Item Clicky Effect File
	if (ItemClickyEffectFileState == FILEPENDING)
		DrawGraphic(hdc, &Diamond, 5, 150, Diamond.Width, Diamond.Height);
	else if (ItemClickyEffectFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 150, FilledDiamond.Width, FilledDiamond.Height);
    else if (ItemClickyEffectFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 150, CheckMark.Width, CheckMark.Height);
    else if (ItemClickyEffectFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 150, Error.Width, Error.Height);
	
	//Item File
	if (ItemFileState == FILEPENDING)
		DrawGraphic(hdc, &Diamond, 5, 170, Diamond.Width, Diamond.Height);
	else if (ItemFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 170, FilledDiamond.Width, FilledDiamond.Height);
    else if (ItemFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 170, CheckMark.Width, CheckMark.Height);
    else if (ItemFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 170, Error.Width, Error.Height);

	//Template File
	if (TemplateFileState == FILEPENDING)
		DrawGraphic(hdc, &Diamond, 5, 190, Diamond.Width, Diamond.Height);
	else if (TemplateFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 190, FilledDiamond.Width, FilledDiamond.Height);
    else if (TemplateFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 190, CheckMark.Width, CheckMark.Height);
    else if (TemplateFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 190, Error.Width, Error.Height);

	//Destiny File
	if (DestinyFileState == FILEPENDING)
		DrawGraphic(hdc, &Diamond, 5, 210, Diamond.Width, Diamond.Height);
	else if (DestinyFileState == FILELOADING)
        DrawGraphic(hdc, &FilledDiamond, 5, 210, FilledDiamond.Width, FilledDiamond.Height);
    else if (DestinyFileState == FILELOADED)
        DrawGraphic(hdc, &CheckMark, 5, 210, CheckMark.Width, CheckMark.Height);
    else if (DestinyFileState == FILEERROR)
        DrawGraphic(hdc, &Error, 5, 210, Error.Width, Error.Height);
    }

//---------------------------------------------------------------------------
void LoadWindowClass::UpdateLoadFileState(DATAFILE File, FILESTATE NewState)
    {
    switch (File)
        {
        case RACEFILE:
            {
            RaceFileState = NewState;
            break;
            }
        case CLASSFILE:
            {
            ClassFileState = NewState;
            break;
            }
        case FEATFILE:
            {
            FeatFileState = NewState;
            break;
            }
        case SKILLFILE:
            {
            SkillFileState = NewState;
            break;
            }
        case ENHANCEMENTFILE:
            {
            EnhancementFileState = NewState;
            break;
            }
        case SPELLFILE:
            {
            SpellFileState = NewState;
            break;
            }
		case ITEMEFFECTFILE:
			{
			ItemEffectFileState = NewState;
			break;
			}
		case ITEMCLICKYEFFECTFILE:
			{
			ItemClickyEffectFileState = NewState;
			break;
			}
		case ITEMFILE:
			{
			ItemFileState = NewState;
			break;
			}
		case TEMPLATEFILE:
			{
			TemplateFileState = NewState;
			break;
			}
		case DESTINYFILE:
			{
			DestinyFileState = NewState;
			break;
			}
        }

    RedrawWindow(LoadWindowHandle, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
    }