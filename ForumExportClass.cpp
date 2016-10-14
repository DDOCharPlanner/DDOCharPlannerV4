//---------------------------------------------------------------------------
#include "ForumExportClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "DataClass.h"

//---------------------------------------------------------------------------
ForumExportClass::ForumExportClass()
    {
    }

//---------------------------------------------------------------------------
ForumExportClass::~ForumExportClass()
    {
    }

//---------------------------------------------------------------------------
void ForumExportClass::Create(HINSTANCE Instance, HWND Parent)
    {
    WNDCLASSEX wc;
    int ScreenX;
    int ScreenY;
    RECT ParentRect;
    RECT WindowRect;
    int WindowX;
    int WindowY;
    static char WindowName[] = "Forum Export Window";

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
    ForumExportWindowHandle = CreateWindowEx(NULL, WindowName, WindowName, WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 780, 600, Parent, NULL, Instance, NULL);
    SetClassLong(ForumExportWindowHandle, 0, (long)FORUMEXPORTWINDOW);
    ParentRect = InterfaceManager.GetMainWindowExtents();
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(ForumExportWindowHandle, &WindowRect);
    WindowX = WindowRect.right - WindowRect.left;
    WindowY = WindowRect.bottom - WindowRect.top;
    SetWindowPos(ForumExportWindowHandle, Parent, (ScreenX/2) - (WindowX/2), (int)(ScreenY/2.3) - (WindowY/2), 0, 0, SWP_NOSIZE);

    //the child windows
	LevelSelectLabel = CreateWindowEx(NULL, "STATIC", "Export from Level 1 to: ", WS_CHILD, 10, 8, 150, 20, ForumExportWindowHandle, (HMENU)FE_LEVELSELECTLABEL, Instance, NULL);
    LevelSelect = CreateWindowEx(NULL, "COMBOBOX", "Close", WS_CHILD | CBS_DROPDOWNLIST, 170, 5, 50, 500, ForumExportWindowHandle, (HMENU)FE_LEVELSELECT, Instance, NULL);
    CloseButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 230, 495, 50, 20, ForumExportWindowHandle, (HMENU)FE_CLOSEBUTTON, Instance, NULL);
    CopyButton = CreateWindowEx(NULL, "BUTTON", "Copy Data to Clipboard", WS_CHILD | BS_PUSHBUTTON, 290, 495, 170, 20, ForumExportWindowHandle, (HMENU)FE_COPYBUTTON, Instance, NULL);
    PresetsLabel = CreateWindowEx(NULL, "STATIC", "Presets", WS_CHILD, 10, 455, 60, 20, ForumExportWindowHandle, (HMENU)FE_PRESETSLABEL, Instance, NULL);
    Preset1 = CreateWindowEx(NULL, "BUTTON", "Build Feedback", WS_CHILD | BS_PUSHBUTTON, 20, 475, 130, 20, ForumExportWindowHandle, (HMENU)FE_PRESET1, Instance, NULL);
    Preset2 = CreateWindowEx(NULL, "BUTTON", "Build Reproduction", WS_CHILD | BS_PUSHBUTTON, 20, 500, 130, 20, ForumExportWindowHandle, (HMENU)FE_PRESET2, Instance, NULL);
    ExampleOutputBox = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | ES_MULTILINE | ES_READONLY | WS_VSCROLL | WS_BORDER, 230, 5, 540, 485, ForumExportWindowHandle, (HMENU)FE_EXAMPLEOUTPUTBOX, Instance, NULL);

    HeaderLabel = CreateWindowEx(NULL, "STATIC", "Header", WS_CHILD, 10, 30, 60, 20, ForumExportWindowHandle, (HMENU)FE_HEADERLABEL, Instance, NULL);
    NameCheckBox = CreateWindowEx(NULL, "BUTTON", "Name", WS_CHILD | BS_AUTOCHECKBOX, 20, 50, 90, 20, ForumExportWindowHandle, (HMENU)FE_NAMECHECKBOX, Instance, NULL);

    AbilityLabel = CreateWindowEx(NULL, "STATIC", "Abilities", WS_CHILD, 10, 80, 60, 20, ForumExportWindowHandle, (HMENU)FE_ABILITYLABEL, Instance, NULL);
    StartingAbilityCheckBox = CreateWindowEx(NULL, "BUTTON", "Starting", WS_CHILD | BS_AUTOCHECKBOX, 20, 100, 90, 20, ForumExportWindowHandle, (HMENU)FE_STARTINGABILITYCHECKBOX, Instance, NULL);
    EndingAbilityCheckBox = CreateWindowEx(NULL, "BUTTON", "Ending", WS_CHILD | BS_AUTOCHECKBOX, 20, 120, 90, 20, ForumExportWindowHandle, (HMENU)FE_ENDINGABILITYCHECKBOX, Instance, NULL);
    ModifiedAbilityCheckBox = CreateWindowEx(NULL, "BUTTON", "Modified", WS_CHILD | BS_AUTOCHECKBOX, 20, 140, 90, 20, ForumExportWindowHandle, (HMENU)FE_MODIFIEDABILITYCHECKBOX, Instance, NULL);

    SkillsLabel = CreateWindowEx(NULL, "STATIC", "Skills", WS_CHILD, 10, 170, 60, 20, ForumExportWindowHandle, (HMENU)FE_SKILLSLABEL, Instance, NULL);
    StartingSkillsCheckBox = CreateWindowEx(NULL, "BUTTON", "Starting", WS_CHILD | BS_AUTOCHECKBOX, 20, 190, 90, 20, ForumExportWindowHandle, (HMENU)FE_STARTINGSKILLSCHECKBOX, Instance, NULL);
    EndingSkillsCheckBox = CreateWindowEx(NULL, "BUTTON", "Ending", WS_CHILD | BS_AUTOCHECKBOX, 20, 210, 90, 20, ForumExportWindowHandle, (HMENU)FE_ENDINGSKILLSCHECKBOX, Instance, NULL);
    ModifiedSkillsCheckBox = CreateWindowEx(NULL, "BUTTON", "Modified", WS_CHILD | BS_AUTOCHECKBOX, 20, 230, 90, 20, ForumExportWindowHandle, (HMENU)FE_MODIFIEDSKILLSCHECKBOX, Instance, NULL);

    NotableEquipmentCheckBox = CreateWindowEx(NULL, "BUTTON", "Notable Equipment", WS_CHILD | BS_AUTOCHECKBOX, 20, 270, 150, 20, ForumExportWindowHandle, (HMENU)FE_NOTABLEEQUIPMENTCHECKBOX, Instance, NULL);

	LevelBreakdownLabel = CreateWindowEx(NULL, "STATIC", "Level Breakdown", WS_CHILD, 10, 310, 150, 20, ForumExportWindowHandle, (HMENU)FE_LEVELBREAKDOWNLABEL, Instance, NULL);
	AbilityRaiseCheckBox = CreateWindowEx(NULL, "BUTTON", "Ability Raises", WS_CHILD | BS_AUTOCHECKBOX, 20, 330, 150, 20, ForumExportWindowHandle, (HMENU)FE_ABILITYRAISECHECKBOX, Instance, NULL);
	SkillsListCheckBox = CreateWindowEx(NULL, "BUTTON", "Skill Raises", WS_CHILD | BS_AUTOCHECKBOX, 20, 350, 150, 20, ForumExportWindowHandle, (HMENU)FE_SKILLSLISTCHECKBOX, Instance, NULL);
	FeatSelectedCheckBox = CreateWindowEx(NULL, "BUTTON", "Feats (Selected)", WS_CHILD | BS_AUTOCHECKBOX, 20, 370, 150, 20, ForumExportWindowHandle, (HMENU)FE_FEATSELECTEDCHECKBOX, Instance, NULL);
	FeatAutoCheckBox = CreateWindowEx(NULL, "BUTTON", "Feats (Automatic)", WS_CHILD | BS_AUTOCHECKBOX, 20, 390, 150, 20, ForumExportWindowHandle, (HMENU)FE_FEATAUTOCHECKBOX, Instance, NULL);
	SpellsListCheckBox = CreateWindowEx(NULL, "BUTTON", "Spell List", WS_CHILD | BS_AUTOCHECKBOX, 20, 410, 150, 20, ForumExportWindowHandle, (HMENU)FE_SPELLSCHECKBOX, Instance, NULL);
	EnhancementsListCheckBox = CreateWindowEx(NULL, "BUTTON", "Enhancement List", WS_CHILD | BS_AUTOCHECKBOX, 20, 430, 150, 20, ForumExportWindowHandle, (HMENU)FE_ENHANCEMENTSCHECKBOX, Instance, NULL);

	ForumBackgroundLabel = CreateWindowEx(NULL, "STATIC", "Forum Background:", WS_CHILD, 480, 495, 150, 20, ForumExportWindowHandle, (HMENU)FE_FORUMBACKGROUNDLABEL, Instance, NULL);
	ForumBackgroundDarkRadioButton = CreateWindowEx(NULL, "BUTTON", "Dark", WS_CHILD | BS_AUTORADIOBUTTON, 620, 495, 50, 20, ForumExportWindowHandle, (HMENU)FE_FORUMBACKGROUNDDARKRADIOBUTTON, Instance, NULL);
	ForumBackgroundLightRadioButton = CreateWindowEx(NULL, "BUTTON", "Light", WS_CHILD | BS_AUTORADIOBUTTON, 680, 495, 60, 20, ForumExportWindowHandle, (HMENU)FE_FORUMBACKGROUNDLIGHTRADIOBUTTON, Instance, NULL);

	//the template stuff
	TemplateSelectionLabel = CreateWindowEx(NULL, "STATIC", "Export Template", WS_CHILD, 10, 530, 150, 20, ForumExportWindowHandle, (HMENU)FE_TEMPLATESELECTLABEL, Instance, NULL);
    TemplateSelectionBox = CreateWindowEx(NULL, "COMBOBOX", "", WS_CHILD | CBS_DROPDOWNLIST, 20, 550, 140, 100, ForumExportWindowHandle, (HMENU)FE_TEMPLATESELECT, Instance, NULL);
    TemplateDesignButton = CreateWindowEx(NULL, "BUTTON", "Template Design", WS_CHILD | BS_PUSHBUTTON, 200, 550, 140, 20, ForumExportWindowHandle, (HMENU)FE_TEMPLATEDESIGNBUTTON, Instance, NULL);

	//rich edit background color
    SendMessage(ExampleOutputBox, EM_SETBKGNDCOLOR, 0, RGB(0,0,0));

    //default states for the checkboxes
    SendMessage(NameCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(StartingAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(EndingAbilityCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(ModifiedAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(StartingSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(EndingSkillsCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(ModifiedSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(NotableEquipmentCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(AbilityRaiseCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(SkillsListCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(FeatSelectedCheckBox, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(FeatAutoCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(SpellsListCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(EnhancementsListCheckBox, BM_SETCHECK, BST_CHECKED, 0);

    //increase the text buffer of the export box to default maximum
    SendMessage(ExampleOutputBox, EM_EXLIMITTEXT, 0, 0);

    //at selections to the level selector box
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"1");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"2");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"3");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"4");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"5");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"6");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"7");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"8");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"9");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"10");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"11");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"12");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"13");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"14");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"15");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"16");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"17");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"18");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"19");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"20");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"21");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"22");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"23");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"24");
    SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"25");
	SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"26");
	SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"27");
	SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"28");
	SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"29");
	SendMessage(LevelSelect, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)"30");

    AtLevel = MAXLEVEL;
	SendMessage(LevelSelect, CB_SETCURSEL, (WPARAM)AtLevel-1, 0);
	SendMessage(ForumBackgroundDarkRadioButton, BM_SETCHECK, BST_CHECKED, 0);
    }

//---------------------------------------------------------------------------
void ForumExportClass::Show(bool State)
    {
    //pop it up
    ShowWindow(ForumExportWindowHandle, State);
    ShowWindow(LevelSelectLabel, State);
    ShowWindow(LevelSelect, State);
    ShowWindow(CloseButton, State);
    ShowWindow(CopyButton, State);
    ShowWindow(PresetsLabel, State);
    ShowWindow(Preset1, State);
    ShowWindow(Preset2, State);
    ShowWindow(ExampleOutputBox, State);
    ShowWindow(HeaderLabel, State);
    ShowWindow(NameCheckBox, State);
    ShowWindow(AbilityLabel, State);
    ShowWindow(StartingAbilityCheckBox, State);
    ShowWindow(EndingAbilityCheckBox, State);
    ShowWindow(ModifiedAbilityCheckBox, State);
    ShowWindow(SkillsLabel, State);
    ShowWindow(StartingSkillsCheckBox, State);
    ShowWindow(EndingSkillsCheckBox, State);
    ShowWindow(ModifiedSkillsCheckBox, State);
    ShowWindow(NotableEquipmentCheckBox, State);
    ShowWindow(LevelBreakdownLabel, State);
    ShowWindow(AbilityRaiseCheckBox, State);
    ShowWindow(SkillsListCheckBox, State);
    ShowWindow(FeatSelectedCheckBox, State);
    ShowWindow(FeatAutoCheckBox, State);
	ShowWindow(SpellsListCheckBox, State);
	ShowWindow(EnhancementsListCheckBox, State);
	ShowWindow(ForumBackgroundLabel, State);
	ShowWindow(ForumBackgroundDarkRadioButton, State);
	ShowWindow(ForumBackgroundLightRadioButton, State);
	ShowWindow(TemplateSelectionLabel, State);
	ShowWindow(TemplateSelectionBox, State);
	ShowWindow(TemplateDesignButton, State);
	}

//---------------------------------------------------------------------------
long ForumExportClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    RECT Rect;
    
    switch (Message)
        {
		case WM_CLOSE:
            {
            InterfaceManager.ShowChild(FORUMEXPORTWINDOW, false);
            return 0;
            }
        case WM_COMMAND:
            {
            if (HIWORD(wParam) == BN_CLICKED)
                {
                if ((int)LOWORD(wParam) == FE_CLOSEBUTTON)
                    {
                    InterfaceManager.ShowChild(FORUMEXPORTWINDOW, false);
                    return 0;
                    }
                else if ((int)LOWORD(wParam) == FE_PRESET1)
                    {
                    SendMessage(StartingAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(EndingAbilityCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(ModifiedAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(StartingSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(EndingSkillsCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(ModifiedSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(NotableEquipmentCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(AbilityRaiseCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(SkillsListCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(FeatSelectedCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(FeatAutoCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(SpellsListCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(EnhancementsListCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    FillExampleExportBox();
                    return 0;
                    }
                else if ((int)LOWORD(wParam) == FE_PRESET2)
                    {
                    SendMessage(StartingAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(EndingAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(ModifiedAbilityCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(StartingSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(EndingSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(ModifiedSkillsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(NotableEquipmentCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(AbilityRaiseCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(SkillsListCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(FeatSelectedCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(FeatAutoCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(SpellsListCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(EnhancementsListCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    FillExampleExportBox();
                    return 0;
                    }
                else if ((int)LOWORD(wParam) == FE_COPYBUTTON)
                    {
                    HandleCharacterForumExport();
                    return 0;
                    }
                else if ((int)LOWORD(wParam) == FE_TEMPLATEDESIGNBUTTON)
					{
					InterfaceManager.ShowChild(FORUMEXPORTWINDOW, false);
					InterfaceManager.ShowChild(EXPORTTEMPLATEDESIGNWINDOW, true);
					return 0;
					}
                else
                    {
                    FillExampleExportBox();
                    return 0;
                    }
                }
            if (HIWORD(wParam) == CBN_SELCHANGE)
                {
                SetForumExportLevel(SendMessage(LevelSelect, CB_GETCURSEL, 0, 0)+1);
                FillExampleExportBox();
                return 0;
                }
            return 0;
            }
        case WM_CTLCOLORSTATIC:
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            SetTextColor((HDC)wParam, RGB(255,255,255));
            return (long)GetStockObject(DKGRAY_BRUSH);
            }
        case WM_MOUSEWHEEL:
            {
            GetWindowRect(ExampleOutputBox, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(ExampleOutputBox, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(ExampleOutputBox, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            return 0;
            }
        case WM_SHOWWINDOW:
            {
            if (wParam != 0)
                FillExampleExportBox();
            return 0;
            }
        default:
            {
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
        }
    }

//---------------------------------------------------------------------------
void ForumExportClass::SetForumExportLevel(int NewLevel)
    {
    AtLevel = NewLevel;
    SendMessage(LevelSelect, CB_SETCURSEL, (WPARAM)NewLevel-1, 0);
    }

//---------------------------------------------------------------------------
void ForumExportClass::FillExampleExportBox()
    {
    EDITSTREAM Stream;
    string Description;
    string rtfPrefix = "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\froman "
		"Courier;}}\n{\\colortbl\\red255\\green255\\blue255;\\red255\\green165\\blue0;"
        "\\red192\\green192\\blue192;\\red255\\green250\\blue205;"
        "\\red255\\green192\\blue203;\\red245\\green222\\blue179;"
        "\\red173\\green216\\blue230;\\red152\\green251\\blue152;}\n"
		"\\deflang1033\\pard\\plain\\f3\\fs22\\cf0 ";
	string rtfPostfix = "\n\\par }";

	Description.reserve(50000);

    Description = rtfPrefix;
    Description += FillExampleExportBoxHeader();
    Description += FillExampleExportBoxTitle();
    Description += FillExampleExportBoxAbilities();
    Description += FillExampleExportBoxSkills();
    Description += FillExampleExportBoxNotableEquipment();
    Description += FillExampleExportBoxLevelBreakdown();
    Description += rtfPostfix;

    Stream.dwCookie = (DWORD)&Description;
    Stream.dwError = false;
    Stream.pfnCallback = ExportExampleStreamCallback;
    SendMessage(ExampleOutputBox, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExampleExportBoxHeader()
    {
    string Text;
    ostringstream ss;

    ss.str("");
    ss << "{\\ul {\\b Character Plan by DDO Character Planner Version " << VERSION << " \\par ";
    ss << "{\\cf1 DDO Character Planner Home Page }}} \\par\\par ";
	Text = ss.str();

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExampleExportBoxTitle()
    {
    string Text;
    ostringstream ss;
    string FirstName;
    string Sur;
    int ClassLevel;
    bool First;
    int Value;

    ss.str("");
    if (SendMessage(NameCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        Character.GetName(&FirstName, &Sur);
        if (FirstName != "" || Sur != "")
            ss << "{\\ul {\\b " << FirstName << " " << Sur << "}} \\par ";
        }

    ss << "Level " << AtLevel << " " << Data.GetAlignmentString(Character.GetAlignment()) << " " << Data.GetRaceName((int)Character.GetRace()) << " ";
    if (Character.GetSex() == MALE)
        ss << "Male";
    else
        ss << "Female";
    ss << " \\par ";
    First = true;
    ss << "(";
	for (unsigned int i=0; i<NUMCLASSES; i++)
        {
        ClassLevel = Character.GetClassLevel((CLASS)i, AtLevel);
        if (ClassLevel > 0)
            {
            if (First == false)
                ss << " / ";
            ss << ClassLevel << " " << Data.GetClassName(i);
            First = false;
            }
        }
	if (AtLevel > HEROICLEVELS)
		ss << " / " << AtLevel-HEROICLEVELS << " Epic";
    ss << ") \\par ";

    ss << "Hit Points: " << Character.GetHitPoints(AtLevel) << " \\par ";
    ss << "Spell Points: " << Character.GetSpellPoints(AtLevel) << " \\par\\par ";
    Value = Character.CalculateBAB(AtLevel);
    ss << "BAB: " << Value;
    if (Value > 0)
        {
        ss << "/";
        ss << Value;
        }
    if (Value > 4)
        {
        ss << "/";
        ss << (Value+5);
        }
    if (Value > 9)
        {
        ss << "/";
        ss << (Value+10);
        }
    if (Value > 14)
        {
        ss << "/";
        ss << (Value+10);
        }
    ss << " \\par ";
    ss << "Fortitude: " << Character.GetSave(FORTITUDESAVE, AtLevel) << " \\par ";
    ss << "Reflex: " << Character.GetSave(REFLEXSAVE, AtLevel) << " \\par ";
    ss << "Will: " << Character.GetSave(WILLSAVE, AtLevel) << " \\par\\par ";
	Text = ss.str();

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExampleExportBoxAbilities()
    {
    string Text;
    ostringstream ss;
    unsigned int Spacer;
    bool TomesUsed;

    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";

    Spacer = 1;
    ss.str("");
    Text = "";
    ss << "{\\b";
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "     Starting";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "      Ending";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "    Feat/Enhancement";
        }
    ss << " \\par ";
    Text = ss.str();

    Spacer = 1;
    ss.str("");
    ss << "Abilities";
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Base Stats";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Base Stats";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << " Modified Stats";
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "{\\ul (" << Character.CalculateTotalAbilityPoints() << " Point)}";
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "    {\\ul (Level 1)}";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "    {\\ul (Level " << AtLevel << ")}";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "      {\\ul (Level " << AtLevel << ")}";
        }
    ss << "} \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    Text += "{\\cf2 ";
    ss << "Strength";
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(0, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(0, 1, false);
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(0, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(0, AtLevel));
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(0, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(0, AtLevel, true, true, true));
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "Dexterity";
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(1, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(1, 1, false);
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(1, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(1, AtLevel));
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(1, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(1, AtLevel, true, true, true));
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "Constitution";
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(2, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(2, 1, false);
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(2, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(2, AtLevel));
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(2, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(2, AtLevel, true, true, true));
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "Intelligence";
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(3, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(3, 1, false);
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(3, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(3, AtLevel));
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(3, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(3, AtLevel, true, true, true));
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "Wisdom";
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(4, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(4, 1, false);
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(4, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(4, AtLevel));
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(4, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(4, AtLevel, true, true, true));
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "Charisma";
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(5, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(5, 1, false);
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(5, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(5, AtLevel));
        Spacer++;
        }
    while (ss.str().size() < 15*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(5, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(5, AtLevel, true, true, true));
        }
    ss << "} \\par\\par ";
	Text += ss.str();

    //Tomes. Don't list anything here if none were used
    TomesUsed = false;
    for (unsigned int i=0; i<6; i++)
        {
        if (Character.GetAbilityMod(static_cast<ABILITIES>(i), ABMOD_INHERENT, MAXLEVEL) > 0)
            TomesUsed = true;
        }
    if (TomesUsed == false)
        return Text;

    ss.str("");
    ss << "{\\b {\\ul Tomes Used}} \\par ";
    for (unsigned int i=0; i<6; i++)
    {
		int TotalTome = 0;
		for (unsigned int j=1; j<MAXLEVEL+1; j++)
		{
			if (Character.TomeRaise[i][j-1]>0)
			{
				TotalTome += Character.TomeRaise[i][j - 1];
					ss << "+" << TotalTome << " Tome of " << Data.GetAbilityString(static_cast<ABILITIES>(i), true) << " used at level " << j << " \\par ";
			}
		}
    }
    ss << " \\par ";

	Text += ss.str();

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExampleExportBoxSkills()
    {
    string Text;
    ostringstream ss;
    unsigned int Spacer;
    bool NAFlag;

    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";

    Spacer = 1;
    ss.str("");
    Text = "";
    ss << "{\\b";
    while (ss.str().size() < 18*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Starting";
        Spacer++;
        }
    while (ss.str().size() < 16*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Ending";
        Spacer++;
        }
    while (ss.str().size() < 14*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Feat/Enhancement";
        }
    ss << " \\par ";
    Text = ss.str();

    Spacer = 1;
    ss.str("");
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Skill Ranks";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Skill Ranks";
        Spacer++;
        }
    while (ss.str().size() < 13*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Modified Skills";
        }
    ss << " \\par ";
	Text += ss.str();

    Spacer = 1;
    ss.str("");
    ss << "{\\ul Skills}";
    while (ss.str().size() < 19*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "{\\ul (Level 1)}";
        Spacer++;
        }
    while (ss.str().size() < 19*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "{\\ul (Level " << AtLevel << ")}";
        Spacer++;
        }
    while (ss.str().size() < 20*Spacer)
        {
        ss << " ";
        }
    if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "{\\ul (Level " << AtLevel << ")}";
        }
    ss << "} \\par ";
	Text += ss.str();
    Text += "{\\cf2 ";

    for (unsigned int i=0; i<NUMSKILLS; i++)
        {
        NAFlag = false;
        if (i == DISABLEDEVICE)
            NAFlag = true;
        if (i == OPENLOCK)
			NAFlag = true;
        if (i == PERFORM)
            NAFlag = true;
        if (i == TUMBLE)
            NAFlag = true;
        if (i == UMD)
            NAFlag = true;
        Spacer = 1;
        ss.str("");
        ss << Data.GetSkillName(i);
        while (ss.str().size() < 19*Spacer)
            {
            ss << " ";
            }
        if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            if (NAFlag == true && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), 1) == 0)
                ss << "n/a";
            else
                ss << Character.CalculateSkillLevel(static_cast<SKILLS>(i), 1, false);
            Spacer++;
            }
        while (ss.str().size() < 17*Spacer)
            {
            ss << " ";
            }
        if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            if (NAFlag == true && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), AtLevel) == 0)
                ss << "n/a";
            else
                ss << Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, false);
            Spacer++;
            }
        while (ss.str().size() < 17*Spacer)
            {
            ss << " ";
            }
        if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            if (NAFlag == true && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), AtLevel) == 0)
                ss << "n/a";
            else
                ss << Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, true);
            }
        ss << " \\par ";
    	Text += ss.str();
        }
	Text += "} \\par ";

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExampleExportBoxNotableEquipment()
    {
    string Text;
    ostringstream ss;
    string EquipmentTitle;
	
    if (SendMessage(NotableEquipmentCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";
	if (Character.GetCharacterItemsSize() == 0)
		return ""; 

    Text = "{\\b {\\ul Notable Equipment }} \\par ";
	for (unsigned int i=0; i<Character.GetCharacterItemsSize(); i++)
		{
		ss.str("");
		EquipmentTitle = Character.GetItemDisplayName(i);
		ss <<EquipmentTitle << " \\par ";
		Text += ss.str();
		}

    Text += " \\par ";

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExampleExportBoxLevelBreakdown()
    {
    string Text;
    ostringstream ss;
    ABILITIES AbilityRaise;
    bool AlreadyDone;
    bool DoNormal;
    string ParentHeading;
    vector <string> UsedParentHeadings;
    int Index;
    int FeatIndex;
    int Level;
    FEATSLOTTYPE AquireType;
    int SpellIndex;
    FeatDataClass *Feat;
	Character_Enhancements_Class *CharacterEnhancements;
	Data_Enhancement_Tree_Class* Tree;
	Data_Enhancement_Class* Enhancement;
	int EnhancementIndexChosen;
	int EnhancementIndex;

    if (SendMessage(AbilityRaiseCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(SkillsListCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(FeatSelectedCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(FeatAutoCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(SpellsListCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(EnhancementsListCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";

	Text.reserve(16384);
    for (int i=0; i<AtLevel; i++)
        {
        ss.str("");
		if (i > HEROICLEVELS-1)
	        ss << "{\\b {\\ul Level " << (i+1) << " (Epic)}} \\par ";
		else
	        ss << "{\\b {\\ul Level " << (i+1) << " (" << Data.GetClassName(Character.GetClass(i+1)) << ")}} \\par ";
        Text += ss.str();

        //ability up
        if (Character.GetAbilityIncrease(i+1) != ABILITYNONE && SendMessage(AbilityRaiseCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            ss.str("");
            ss << "{\\cf4 Ability Raise:} {\\cf2 ";
			AbilityRaise = Character.GetAbilityIncrease(i+1);
            if (AbilityRaise == STRENGTH)
                ss << "STR";
            if (AbilityRaise == DEXTERITY)
                ss << "DEX";
            if (AbilityRaise == CONSTITUTION)
                ss << "CON";
            if (AbilityRaise == INTELLIGENCE)
                ss << "INT";
            if (AbilityRaise == WISDOM)
                ss << "WIS";
            if (AbilityRaise == CHARISMA)
                ss << "CHA";
            ss << "} \\par ";
            Text += ss.str();
            }

        //Skills
        if (SendMessage(SkillsListCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            for (unsigned int j=0; j<NUMSKILLS; j++)
                {
                ss.str("");
                if (Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), i+1) > 0)
                    {
                    if (Data.IsSkillPrimary(Character.GetClass(i+1),j) == true)
                        ss << "{\\cf5 Skill: }{\\cf2" << Data.GetSkillName(j) << " (+" << Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), i+1) << ")} \\par ";
                    else
                        ss << "{\\cf5 Skill: }{\\cf2" << Data.GetSkillName(j) << " (+" << (Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), i+1))/2.0f << ")} \\par ";
                    }
                Text += ss.str();
                }
            }

        //feats (selected)
        if (SendMessage(FeatSelectedCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
            UsedParentHeadings.clear();
            Index = 0;
            FeatIndex = Character.GetFeat(i+1, FEATSELECTED, Index);
            while (FeatIndex != -1)
                {
                Feat = Data.GetFeatPointer(FeatIndex);
                ss.str("");
                ParentHeading = Feat->GetFeatParentHeading();
                AquireType = Character.GetFeatAquireType(FeatIndex, i+1);
                DoNormal = false;
                if (ParentHeading != "")
                    {
                    AlreadyDone = false;
                    for (unsigned int k=0; k<UsedParentHeadings.size(); k++)
                        {
                        if (UsedParentHeadings[k] == ParentHeading)
                            AlreadyDone = true;
                        }
                    if (AlreadyDone == false)
                        {
                        if (Character.HasAllFeatParentHeadings(ParentHeading, i+1) == true)
                            {
                            ss << "{\\cf6 Feat: }{\\cf2 ";
                            if (AquireType == FEATCHARACTER)
                                ss << "(Selected) ";
                            if (AquireType == FEATHUMANBONUS)
                                ss << "(Human Bonus) ";
                            if (AquireType == FEATHALFELFBONUS)
                                ss << "(Half-Elf Dilettante) ";
                            if (AquireType == FEATFIGHTERBONUS)
                                ss << "(Fighter Bonus) ";
                            if (AquireType == FEATWIZARDBONUS)
                                ss << "(Wizard Bonus) ";
                            if (AquireType == FEATARTIFICERBONUS)
                                ss << "(Artificer Bonus) ";
                            if (AquireType == FEATRANGERFAVOREDENEMY)
                                ss << "(Favored Enemy) ";
                            if (AquireType == FEATROGUEBONUS)
                                ss << "(Rogue Bonus) ";
							if (AquireType == FEATMONKBONUS)
								ss << "(Monk Bonus) ";
							if (AquireType == FEATMONKPATH)
								ss << "(Monk Path) ";
							if (AquireType == FEATDEITY)
								ss << "(Deity) ";
							if (AquireType == FEATFAVOREDSOULBONUS)
								ss << "(Favored Soul Bonus) ";
                            if (AquireType == FEATDRUIDWILDSHAPE)
                                ss << "(Druid Wild Shape) ";
							if (AquireType == FEATWARLOCKPACT)
								ss << "(Warlock Pact) ";
							if (AquireType == FEATPASTLIFE)
								ss << "(Past Life) ";
							if (AquireType == FEATDESTINY)
								ss << "(Epic Destiny) ";
							if (AquireType == FEATLEGENDARY)
								ss << "(Legendary) ";
							ss << ParentHeading << " (ALL)} \\par ";
                            UsedParentHeadings.push_back(ParentHeading);
                            }
                        else
                            DoNormal = true;
                        }
                    }
                if (ParentHeading == "" || DoNormal == true)
                    {
                    ss << "{\\cf6 Feat: }{\\cf2 ";
                    if (AquireType == FEATCHARACTER)
						ss << "(Selected) ";
                    if (AquireType == FEATHUMANBONUS)
                        ss << "(Human Bonus) ";
                    if (AquireType == FEATHALFELFBONUS)
                        ss << "(Half-Elf Dilettante) ";
                    if (AquireType == FEATFIGHTERBONUS)
						ss << "(Fighter Bonus) ";
                    if (AquireType == FEATWIZARDBONUS)
                        ss << "(Wizard Bonus) ";
                    if (AquireType == FEATARTIFICERBONUS)
                        ss << "(Artificer Bonus) ";
                    if (AquireType == FEATRANGERFAVOREDENEMY)
                        ss << "(Favored Enemy) ";
					if (AquireType == FEATROGUEBONUS)
						ss << "(Rogue Bonus) ";
					if (AquireType == FEATMONKBONUS)
						ss << "(Monk Bonus) ";
					if (AquireType == FEATMONKPATH)
						ss << "(Monk Path) ";
					if (AquireType == FEATDEITY)
						ss << "(Deity) ";
					if (AquireType == FEATFAVOREDSOULBONUS)
						ss << "(Favored Soul Bonus) ";
                    if (AquireType == FEATDRUIDWILDSHAPE)
                        ss << "(Druid Wild Shape) ";
					if (AquireType == FEATWARLOCKPACT)
						ss << "(Warlock Pact) ";
					if (AquireType == FEATPASTLIFE)
						ss << "(Past Life) ";
					if (AquireType == FEATDESTINY)
						ss << "(Epic Destiny) ";
					if (AquireType == FEATLEGENDARY)
						ss << "(Legendary) ";
					ss << Feat->GetFeatName(true) << "} \\par ";
                    }
                Text += ss.str();
                Index++;
                FeatIndex = Character.GetFeat(i+1, FEATSELECTED, Index);
                }
            }

        //feats (automatic)
        if (SendMessage(FeatAutoCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            UsedParentHeadings.clear();
            Index = 0;
            FeatIndex = Character.GetFeat(i+1, FEATAUTOMATIC, Index);
            while (FeatIndex != -1)
                {
                Feat = Data.GetFeatPointer(FeatIndex);
                ss.str("");
                ParentHeading = Feat->GetFeatParentHeading();
                DoNormal = false;
                if (ParentHeading != "")
                    {
                    AlreadyDone = false;
                    for (unsigned int k=0; k<UsedParentHeadings.size(); k++)
                        {
                        if (UsedParentHeadings[k] == ParentHeading)
                            AlreadyDone = true;
                        }
                    if (AlreadyDone == false)
                        {
                        if (Character.HasAllFeatParentHeadings(ParentHeading, i+1) == true)
                            {
                            ss << "{\\cf6 Feat: }{\\cf2 (Automatic) ";
                            ss << ParentHeading << " (ALL) }\\par ";
                            UsedParentHeadings.push_back(ParentHeading);
                            }
						else
                            DoNormal = true;
                        }
                    }
                if (ParentHeading == "" || DoNormal == true)
                    {
                    ss << "{\\cf6 Feat: }{\\cf2 (Automatic) ";
                    ss << Feat->GetFeatName(true) << "} \\par ";
                    }
                Text += ss.str();
                Index++;
                FeatIndex = Character.GetFeat(i+1, FEATAUTOMATIC, Index);
                }
            }

        //spells
        if (SendMessage(SpellsListCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            Index = 0;
            SpellIndex = Character.GetSpellByLevelAquired(i+1, Index);
            while (SpellIndex != -1)
                {
                Level = Character.GetSpellLevelAquired(SpellIndex);
                if (Level == i+1)
                    {
                    ss.str("");
                    ss << "{\\cf7 Spell (" << Data.GetSpellLevel(Character.GetClass(i+1), SpellIndex) <<"):} {\\cf2 " << Data.GetSpellName(SpellIndex) << "} \\par ";
                    Text += ss.str();
                    }
                Index++;
                SpellIndex = Character.GetSpellByLevelAquired(i+1, Index);
                }
            }

		//enhancements
		if (SendMessage(EnhancementsListCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
			for (unsigned int x=0; x<7; x++)
				{
				for (unsigned int j=0; j<6; j++)
					{
					for (unsigned int k=0; k<6; k++)
						{
						for (unsigned int Rank=0; Rank<3; Rank++)
							{
							if (CharacterEnhancements->GetLevelTaken(x, j, k, Rank) == i+1)
								{
								ss.str("");
								Tree = Data.GetEnhancementTreePointer(CharacterEnhancements->GetTreeIndex(x));
								ss << "{\\cf8 Enhancement:} {\\cf2 " << Tree->GetTreeName() << " - ";
								EnhancementIndexChosen = CharacterEnhancements->GetEnhancementIndexChosen(x, j, k);
								EnhancementIndex = CharacterEnhancements->GetEnhancementIndex(x, j, k, EnhancementIndexChosen);
								Enhancement = Tree->GetEnhancementPointer(EnhancementIndex);
								ss << Enhancement->GetEnhancementName() << " (Rank " << Rank+1 << ")} \\par";
								Text += ss.str();
								}
							}
						}
					}
				}
			}

        Text += " \\par ";
        }

    return Text;
    }

//---------------------------------------------------------------------------
void ForumExportClass::HandleCharacterForumExport()
    {
    string Text;
    HGLOBAL hMem;
    LPSTR lpMem;
    ostringstream ss;

	SetForumExportColors();
	Text.reserve(50000);

	Text = "[code]";
	Text += FillExportHeader();
	Text += FillExportTitle();
	Text += FillExportAbilities();
	Text += FillExportSkills();
	Text += FillExportNotableEquipment();
	Text += FillExportLevelBreakdown();
	Text += "[/code]";

	OpenClipboard(NULL);
	EmptyClipboard();
	hMem = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE , 50000);
	lpMem = (LPSTR)GlobalLock(hMem);
	StringCbCopy(lpMem, 50000, Text.c_str());
	GlobalUnlock(hMem);
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();       
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExportHeader()
    {
    string Text;
    ostringstream ss;

    ss.str("");
    ss << "[u][b]Character Plan by DDO Character Planner Version " << VERSION << "[/b][/u]\r\n";
    ss << "[url=http://www.rjcyberware.com/DDO]DDO Character Planner Home Page[/url]\r\n\r\n";
	Text = ss.str();

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExportTitle()
    {
    string Text;
    ostringstream ss;
    string FirstName;
    string Sur;
    bool First;
    int ClassLevel;
    int Value;

    ss.str("");
    if (SendMessage(NameCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        Character.GetName(&FirstName, &Sur);
        if (FirstName != "" || Sur != "")
            ss << "[B][U]" << FirstName << " " << Sur << "[/U][/B]\r\n";
        }

    ss << "Level " << AtLevel << " " << Data.GetAlignmentString(Character.GetAlignment()) << " " << Data.GetRaceName((int)Character.GetRace()) << " ";
    if (Character.GetSex() == MALE)
        ss << "Male";
    else
        ss << "Female";
    ss << "\r\n";
    First = true;
    ss << "(";
	for (unsigned int i=0; i<NUMCLASSES; i++)
        {
        ClassLevel = Character.GetClassLevel((CLASS)i, AtLevel);
        if (ClassLevel > 0)
			{
            if (First == false)
                ss << " \\ ";
            ss << ClassLevel << " " << Data.GetClassName(i);
            First = false;
            }
        }
	if (AtLevel > HEROICLEVELS)
		ss << " \\ " << AtLevel-HEROICLEVELS << " Epic";
    ss << ") \r\n";

    ss << "Hit Points: " << Character.GetHitPoints(AtLevel) << "\r\n";
    ss << "Spell Points: " << Character.GetSpellPoints(AtLevel) << " \r\n";
    Value = Character.CalculateBAB(AtLevel);
	ss << "BAB: " << Value;
    if (Value > 0)
        {
        ss << "\\";
        ss << Value;
        }
    if (Value > 4)
        {
        ss << "\\";
        ss << (Value+5);
        }
    if (Value > 9)
        {
        ss << "\\";
        ss << (Value+10);
        }
    if (Value > 14)
        {
        ss << "\\";
        ss << (Value+10);
        }
    ss << "\r\n";
    ss << "Fortitude: " << Character.GetSave(FORTITUDESAVE, AtLevel) << "\r\n";
    ss << "Reflex: " << Character.GetSave(REFLEXSAVE, AtLevel) << "\r\n";
    ss << "Will: " << Character.GetSave(WILLSAVE, AtLevel) << "\r\n\r\n";
	Text += ss.str();

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExportAbilities()
    {
    string Text;
    ostringstream ss;
    unsigned int Column[3];
    int ColumnIndex;
    bool TomesUsed;

    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";

    Column[0] = 17;
    Column[1] = 36;
    Column[2] = 54;

	ColumnIndex = 0;
    ss.str("");
    Text = "[B]";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << " Starting";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "  Ending";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Feat/Enhancement";
        }
    ss << "\r\n";
    Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "Abilities";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Base Stats";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
		}
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Base Stats";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << " Modified Stats";
        }
    ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "[U](" << Character.CalculateTotalAbilityPoints() << " Point)[/U]";
    while (ss.str().size() < Column[ColumnIndex]+7*(ColumnIndex+1))
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "[U](Level 1)[/U]";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex]+7*(ColumnIndex+1))
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "[U](Level " << AtLevel << ")[/U]";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex]+7*(ColumnIndex+1))
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "   [U](Level " << AtLevel << ")[/U]";
		}
    ss << "[/B]\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
	Text += ForumExportColor[0];
    ss << "Strength";
	while (ss.str().size() < Column[ColumnIndex])
        {
		ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(0, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(0, 1, false);
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(0, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(0, AtLevel));
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(0, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(0, AtLevel, true, true, true));
        }
    ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "Dexterity";
    while (ss.str().size() < Column[ColumnIndex])
        {
		ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(1, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(1, 1, false);
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(1, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(1, AtLevel));
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(1, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(1, AtLevel, true, true, true));
        }
    ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "Constitution";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(2, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(2, 1, false);
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
		{
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(2, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(2, AtLevel));
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(2, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(2, AtLevel, true, true, true));
        }
    ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "Intelligence";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(3, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(3, 1, false);
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(3, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(3, AtLevel));
        ColumnIndex++;
        }
	while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(3, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(3, AtLevel, true, true, true));
        }
    ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "Wisdom";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(4, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(4, 1, false);
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(4, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(4, AtLevel));
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(4, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(4, AtLevel, true, true, true));
        }
	ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "Charisma";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(5, 1, false) < 10)
            ss << " ";
        ss << "    " << Character.GetAbility(5, 1, false);
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(5, AtLevel) < 10)
            ss << " ";
        ss << "    " << (Character.GetAbility(5, AtLevel));
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedAbilityCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        if (Character.GetAbility(5, AtLevel, true, true, true) < 10)
            ss << " ";
        ss << "       " << (Character.GetAbility(5, AtLevel, true, true, true));
        }
    ss << "[/COLOR]\r\n\r\n";
	Text += ss.str();

    //Tomes. Don't list anything here if none were used
    TomesUsed = false;
    for (unsigned int i=0; i<6; i++)
        {
        if (Character.GetAbilityMod(static_cast<ABILITIES>(i), ABMOD_INHERENT, MAXLEVEL) > 0)
            TomesUsed = true;
        }
    if (TomesUsed == false)
        return Text;

    ss.str("");
	ss << "[B][U]Tomes Used[/U][/B]\r\n" << ForumExportColor[0];
	for (unsigned int i = 0; i<6; i++)
	{
		int TotalTome = 0;
		for (unsigned int j = 1; j<MAXLEVEL + 1; j++)
		{
			if (Character.TomeRaise[i][j - 1]>0)
			{
				TotalTome += Character.TomeRaise[i][j - 1];
				ss << "+" << TotalTome << " Tome of " << Data.GetAbilityString(static_cast<ABILITIES>(i), true) << " used at level " << j << " \\par ";
			}
		}
	}
    ss << "[/COLOR]\r\n";

	Text += ss.str();

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExportSkills()
    {
    string Text;
    ostringstream ss;
    unsigned int Column[3];
    int ColumnIndex;
    bool NAFlag;

    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";

    Column[0] = 17;
    Column[1] = 36;
    Column[2] = 54;

    ColumnIndex = 0;
    ss.str("");
    Text = "[B]";
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
	if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << " Starting";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "  Ending";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Feat/Enhancement";
        }
    ss << "\r\n";
    Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Base Skills";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
        }
    if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "Base Skills";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex])
        {
        ss << " ";
		}
    if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << " Modified Skills";
        }
    ss << "\r\n";
	Text += ss.str();

    ColumnIndex = 0;
    ss.str("");
    ss << "[U]Skills[/U]";
    while (ss.str().size() < Column[ColumnIndex]+7*(ColumnIndex+1))
        {
        ss << " ";
        }
    if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "[U](Level 1)[/U]";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex]+7*(ColumnIndex+1))
        {
        ss << " ";
        }
    if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "[U](Level " << AtLevel << ")[/U]";
        ColumnIndex++;
        }
    while (ss.str().size() < Column[ColumnIndex]+7*(ColumnIndex+1))
        {
        ss << " ";
        }
    if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
        ss << "  [U](Level " << AtLevel << ")[/U]";
        }
    ss << "[/B]\r\n";
	Text += ss.str();
    Text += ForumExportColor[0];

    for (unsigned int i=0; i<NUMSKILLS; i++)
        {
        NAFlag = false;
        if (i == DISABLEDEVICE)
            NAFlag = true;
        if (i == OPENLOCK)
            NAFlag = true;
		if (i == PERFORM)
            NAFlag = true;
        if (i == TUMBLE)
            NAFlag = true;
        if (i == UMD)
            NAFlag = true;
        ColumnIndex = 0;
        ss.str("");
        ss << Data.GetSkillName(i);
        while (ss.str().size() < Column[ColumnIndex])
            {
            ss << " ";
            }
        if (SendMessage(StartingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            ss << "    ";
            if (Character.CalculateSkillLevel(static_cast<SKILLS>(i), 1, false) >= 0 && Character.CalculateSkillLevel(static_cast<SKILLS>(i), 1, false) < 10)
                ss << " ";
            if (NAFlag == true && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), 1) == 0)
                ss << "n/a";
            else
                ss << Character.CalculateSkillLevel(static_cast<SKILLS>(i), 1, false);
            ColumnIndex++;
            }
        while (ss.str().size() < Column[ColumnIndex])
            {
            ss << " ";
            }
        if (SendMessage(EndingSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            if (Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, false) >= 0 && Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, false) < 10)
                ss << " ";
            if (NAFlag == true && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), AtLevel) == 0)
                ss << "   n/a";
            else
                ss << "    " << Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, false);
            ColumnIndex++;
            }
        while (ss.str().size() < Column[ColumnIndex])
            {
            ss << " ";
            }
        if (SendMessage(ModifiedSkillsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            if (Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, true) >= 0 && Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, true) < 10)
                ss << " ";
            if (NAFlag == true && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), AtLevel) == 0)
                ss << "       n/a";
			else
                ss << "       " << Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, true);
            }
        ss << "\r\n";
    	Text += ss.str();
        }
    Text += "[/COLOR]\r\n";

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExportNotableEquipment()
    {
    string Text;
    ostringstream ss;
    string EquipmentTitle;
	
    if (SendMessage(NotableEquipmentCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";
	if (Character.GetCharacterItemsSize() == 0)
		return ""; 

    Text = "[B][U]Notable Equipment[/B][/U]\r\n";
	for (unsigned int i=0; i<Character.GetCharacterItemsSize(); i++)
		{
		ss.str("");
		EquipmentTitle = Character.GetItemDisplayName(i);
		ss <<EquipmentTitle << " \r\n ";
		Text += ss.str();
		}

    Text += " \r\n ";

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::FillExportLevelBreakdown()
    {
    string Text;
    ostringstream ss;
    ABILITIES AbilityRaise;
    bool AlreadyDone;
    bool DoNormal;
    string ParentHeading;
    vector <string> UsedParentHeadings;
    int Index;
    int FeatIndex;
    int Level;
    FEATSLOTTYPE AquireType;
    int SpellIndex;
    FeatDataClass *Feat;
	Character_Enhancements_Class *CharacterEnhancements;
	Data_Enhancement_Tree_Class* Tree;
	Data_Enhancement_Class* Enhancement;
	int EnhancementIndexChosen;
	int EnhancementIndex;

    if (SendMessage(AbilityRaiseCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(SkillsListCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(FeatSelectedCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(FeatAutoCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(SpellsListCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED &&
            SendMessage(EnhancementsListCheckBox, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return "";

	Text.reserve(16384);
    for (int i=0; i<AtLevel; i++)
        {
        ss.str("");
		if (i > HEROICLEVELS-1)
	        ss << "[B][U]Level " << (i+1) << " (Epic)[/U][/B]\r\n";
		else
	        ss << "[B][U]Level " << (i+1) << " (" << Data.GetClassName(Character.GetClass(i+1)) << ")[/U][/B]\r\n";
        Text += ss.str();

        //ability up
        if (Character.GetAbilityIncrease(i+1) != ABILITYNONE && SendMessage(AbilityRaiseCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            ss.str("");
			ss << ForumExportColor[2] << "Ability Raise: [/COLOR]" << ForumExportColor[0];
            AbilityRaise = Character.GetAbilityIncrease(i+1);
            if (AbilityRaise == STRENGTH)
				ss << "STR";
            if (AbilityRaise == DEXTERITY)
                ss << "DEX";
            if (AbilityRaise == CONSTITUTION)
                ss << "CON";
            if (AbilityRaise == INTELLIGENCE)
				ss << "INT";
            if (AbilityRaise == WISDOM)
                ss << "WIS";
            if (AbilityRaise == CHARISMA)
                ss << "CHA";
            ss << "[/COLOR]\r\n";
            Text += ss.str();
            }

        //Skills
        if (SendMessage(SkillsListCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            for (unsigned int j=0; j<NUMSKILLS; j++)
                {
                ss.str("");
                if (Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), i+1) > 0)
                    {
                    if (Data.IsSkillPrimary(Character.GetClass(i+1),j) == true)
						ss << ForumExportColor[3] << "Skill: [/COLOR]" << ForumExportColor[0] << Data.GetSkillName(j) << " (+" << Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), i+1) << ")[/COLOR]\r\n";
                    else
                        ss << ForumExportColor[3] << "Skill: [/COLOR]" << ForumExportColor[0] << Data.GetSkillName(j) << " (+" << (Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), i+1))/2.0f << ")[/COLOR]\r\n";
                    }
				Text += ss.str();
                }
            }

        //feats (selected)
        if (SendMessage(FeatSelectedCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            UsedParentHeadings.clear();
            Index = 0;
            FeatIndex = Character.GetFeat(i+1, FEATSELECTED, Index);
            while (FeatIndex != -1)
                {
                Feat = Data.GetFeatPointer(FeatIndex);
                ss.str("");
                ParentHeading = Feat->GetFeatParentHeading();
                AquireType = Character.GetFeatAquireType(FeatIndex, i+1);
                DoNormal = false;
                if (ParentHeading != "")
                    {
                    AlreadyDone = false;
                    for (unsigned int k=0; k<UsedParentHeadings.size(); k++)
                        {
                        if (UsedParentHeadings[k] == ParentHeading)
                            AlreadyDone = true;
                        }
                    if (AlreadyDone == false)
                        {
                        if (Character.HasAllFeatParentHeadings(ParentHeading, i+1) == true)
                            {
                            ss << ForumExportColor[1] << "Feat: [/COLOR]" << ForumExportColor[0];
                            if (AquireType == FEATCHARACTER)
                                ss << "(Selected) ";
                            if (AquireType == FEATHUMANBONUS)
                                ss << "(Human Bonus) ";
                            if (AquireType == FEATHALFELFBONUS)
                                ss << "(Half-Elf Dilettante) ";
                            if (AquireType == FEATFIGHTERBONUS)
								ss << "(Fighter Bonus) ";
							if (AquireType == FEATWIZARDBONUS)
								ss << "(Wizard Bonus) ";
							if (AquireType == FEATARTIFICERBONUS)
								ss << "(Artificer Bonus) ";
							if (AquireType == FEATRANGERFAVOREDENEMY)
								ss << "(Favored Enemy) ";
							if (AquireType == FEATROGUEBONUS)
								ss << "(Rogue Bonus) ";
							if (AquireType == FEATMONKBONUS)
								ss << "(Monk Bonus) ";
							if (AquireType == FEATMONKPATH)
								ss << "(Monk Path) ";
							if (AquireType == FEATDEITY)
								ss << "(Deity) ";
							if (AquireType == FEATFAVOREDSOULBONUS)
								ss << "(Favored Soul Bonus) ";
                            if (AquireType == FEATDRUIDWILDSHAPE)
                                ss << "(Druid Wild Shape) ";
							if (AquireType == FEATWARLOCKPACT)
								ss << "(Warlock Pact) ";
							if (AquireType == FEATPASTLIFE)
								ss << "(Past Life) ";
							if (AquireType == FEATDESTINY)
								ss << "(Epic Destiny) ";
							if (AquireType == FEATLEGENDARY)
								ss << "(Legendary) ";
							ss << ParentHeading << " (ALL)[/COLOR]\r\n";
                            UsedParentHeadings.push_back(ParentHeading);
                            }
                        else
                            DoNormal = true;
						}
                    }
                if (ParentHeading == "" || DoNormal == true)
                    {
					ss << ForumExportColor[1] << "Feat: [/COLOR]" << ForumExportColor[0];
                    if (AquireType == FEATCHARACTER)
						ss << "(Selected) ";
                    if (AquireType == FEATHUMANBONUS)
                        ss << "(Human Bonus) ";
                    if (AquireType == FEATHALFELFBONUS)
                        ss << "(Half-Elf Dilettante) ";
                    if (AquireType == FEATFIGHTERBONUS)
						ss << "(Fighter Bonus) ";
					if (AquireType == FEATWIZARDBONUS)
						ss << "(Wizard Bonus) ";
					if (AquireType == FEATARTIFICERBONUS)
						ss << "(Artificer Bonus) ";
					if (AquireType == FEATRANGERFAVOREDENEMY)
						ss << "(Favored Enemy) ";
					if (AquireType == FEATROGUEBONUS)
						ss << "(Rogue Bonus) ";
					if (AquireType == FEATMONKBONUS)
						ss << "(Monk Bonus) ";
					if (AquireType == FEATMONKPATH)
						ss << "(Monk Path) ";
					if (AquireType == FEATDEITY)
						ss << "(Deity) ";
					if (AquireType == FEATFAVOREDSOULBONUS)
						ss << "(Favored Soul Bonus) ";
                    if (AquireType == FEATDRUIDWILDSHAPE)
                        ss << "(Druid Wild Shape) ";
					if (AquireType == FEATWARLOCKPACT)
						ss << "(Warlock Pact) ";
					if (AquireType == FEATPASTLIFE)
						ss << "(Past Life) ";
					if (AquireType == FEATDESTINY)
						ss << "(Epic Destiny) ";
					if (AquireType == FEATLEGENDARY)
						ss << "(Legendary) ";
					ss << Feat->GetFeatName(true) << "[/COLOR]\r\n";
                    }
                Text += ss.str();
                Index++;
                FeatIndex = Character.GetFeat(i+1, FEATSELECTED, Index);
                }
            }

        //feats (automatic)
        if (SendMessage(FeatAutoCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            UsedParentHeadings.clear();
            Index = 0;
            FeatIndex = Character.GetFeat(i+1, FEATAUTOMATIC, Index);
            while (FeatIndex != -1)
                {
                Feat = Data.GetFeatPointer(FeatIndex);
                ss.str("");
                ParentHeading = Feat->GetFeatParentHeading();
                DoNormal = false;
                if (ParentHeading != "")
                    {
                    AlreadyDone = false;
                    for (unsigned int k=0; k<UsedParentHeadings.size(); k++)
                        {
                        if (UsedParentHeadings[k] == ParentHeading)
                            AlreadyDone = true;
                        }
                    if (AlreadyDone == false)
                        {
						if (Character.HasAllFeatParentHeadings(ParentHeading, i+1) == true)
                            {
							ss << ForumExportColor[1] << "Feat: [/COLOR]" << ForumExportColor[0] << "(Automatic) ";
                            ss << ParentHeading << " (ALL)[/COLOR]\r\n";
                            UsedParentHeadings.push_back(ParentHeading);
                            }
                        else
							DoNormal = true;
                        }
                    }
                if (ParentHeading == "" || DoNormal == true)
                    {
					ss << ForumExportColor[1] << "Feat: [/COLOR]" << ForumExportColor[0] << "(Automatic) ";
                    ss << Feat->GetFeatName(true) << "[/COLOR]\r\n";
                    }
                Text += ss.str();
				Index++;
                FeatIndex = Character.GetFeat(i+1, FEATAUTOMATIC, Index);
                }
            }

        //spells
        if (SendMessage(SpellsListCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
            Index = 0;
            SpellIndex = Character.GetSpellByLevelAquired(i+1, Index);
            while (SpellIndex != -1)
                {
                Level = Character.GetSpellLevelAquired(SpellIndex);
                if (Level == i+1)
                    {
                    ss.str("");
					ss << ForumExportColor[4] << "Spell (" << Data.GetSpellLevel(Character.GetClass(i+1), SpellIndex) <<"): [/COLOR]" << ForumExportColor[0] << Data.GetSpellName(SpellIndex) << "[/COLOR]\r\n";
                    Text += ss.str();
                    }
                Index++;
                SpellIndex = Character.GetSpellByLevelAquired(i+1, Index);
                }
            }

		//enhancements
		if (SendMessage(EnhancementsListCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
			for (unsigned int x=0; x<7; x++)
				{
				for (unsigned int j=0; j<6; j++)
					{
					for (unsigned int k=0; k<6; k++)
						{
						for (unsigned int Rank=0; Rank<3; Rank++)
							{
							if (CharacterEnhancements->GetLevelTaken(x, j, k, Rank) == i+1)
								{
								ss.str("");
								Tree = Data.GetEnhancementTreePointer(CharacterEnhancements->GetTreeIndex(x));
								ss << ForumExportColor[5] << "Enhancement:[/COLOR] " << ForumExportColor[0] << Tree->GetTreeName() << " - ";
								EnhancementIndexChosen = CharacterEnhancements->GetEnhancementIndexChosen(x, j, k);
								EnhancementIndex = CharacterEnhancements->GetEnhancementIndex(x, j, k, EnhancementIndexChosen);
								Enhancement = Tree->GetEnhancementPointer(EnhancementIndex);
								ss << Enhancement->GetEnhancementName() << " (Rank " << Rank+1 << ")[/COLOR]\r\n";
								Text += ss.str();
								}
							}
						}
					}
				}
			}

        Text += "\r\n\r\n";
        }

    return Text;
    }

//---------------------------------------------------------------------------
string ForumExportClass::ConvertOrdinalNumberToRoman(int Number)
    {
    switch (Number)
        {
        case 1:
			return "I";
        case 2:
            return "II";
        case 3:
            return "III";
        case 4:
            return "IV";
        case 5:
            return "V";
        case 6:
            return "VI";
        case 7:
            return "VII";
        case 8:
            return "VIII";
        case 9:
            return "IX";
        case 10:
            return "X";
        case 11:
            return "XI";
        case 12:
            return "XII";
        case 13:
            return "XIII";
        case 14:
            return "XIV";
        case 15:
            return "XV";
        case 16:
            return "XVI";
        case 17:
            return "XVII";
        case 18:
            return "XVIII";
        case 19:
            return "XIX";
        case 20:
            return "XX";
        }
    return "";
	}

//---------------------------------------------------------------------------
void ForumExportClass::SetForumExportColors()
	{
	if (SendMessage(ForumBackgroundDarkRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ForumExportColor[0] = "[COLOR=silver]";
		ForumExportColor[1] = "[COLOR=lightblue]";
		ForumExportColor[2] = "[COLOR=pink]";
		ForumExportColor[3] = "[COLOR=wheat]";
		ForumExportColor[4] = "[COLOR=palegreen]";
		ForumExportColor[5] = "[COLOR=lemonchiffon]";
		}
	else
		{
		ForumExportColor[0] = "[COLOR=navy]";     //default colors
		ForumExportColor[1] = "[COLOR=dodgerblue]";       //feats
		ForumExportColor[2] = "[COLOR=orchid]";				//ability raise
		ForumExportColor[3] = "[COLOR=peru]";               //skills
		ForumExportColor[4] = "[COLOR=limegreen]";          //spells
		ForumExportColor[5] = "[COLOR=dimgray]";               //enhancements
		}
	}



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
DWORD CALLBACK ExportExampleStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
    {
    string &text = *(string*)dwCookie;

    //String smaller than buffer
	if( text.length() < (unsigned int)cb)
        {
		*pcb = text.length();
		memcpy(pbBuff,text.c_str(),*pcb);
	    }
	//String larger than buffer
	else
        {
		*pcb = cb;
		memcpy(pbBuff,text.c_str(),*pcb);
		text.erase(0,*pcb-1);
	    }

	return 0;
    }

