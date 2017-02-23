//---------------------------------------------------------------------------
#include "InterfaceManagerClass.h"
//---------------------------------------------------------------------------
InterfaceManagerClass InterfaceManager;

//---------------------------------------------------------------------------
InterfaceManagerClass::InterfaceManagerClass()
    {
	//grab the initial directory path
	StringCbCopy(PathName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, PathName);
    }

//---------------------------------------------------------------------------
InterfaceManagerClass::~InterfaceManagerClass()
    {
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::CreateMainWindow(HINSTANCE Instance, int Width, int Height, bool UseSystemFont, string FontName, long FontHeight, long FontWeight)
    {
    HWND Parent;
    
    ProgramInstance = Instance;
	UIComponents.InitializeUI();
    ControlWindow.CreateControlWindow(Instance, Width, Height);
    Parent = ControlWindow.GetControlWindowHandle();
    MainScreen.Create(ProgramInstance, Parent, UseSystemFont, FontName, FontHeight, FontWeight, &UIComponents);
    DataLoadVisible = false;
    AboutWindowVisible = false;
    ForumExportWindowVisible = false;
	ItemBuilderWindowVisible = false;
	ExportTemplateDesignWindowVisible = false;
	PrintWindowVisible = false;
	EnhancementWindowVisible = false;
	MultiEnhancementWindowVisible = false;
	DestinyWindowVisible = false;
	MultiFeatWindowVisible = false;
	MultiClassWindowVisible = false;
	MultiAbilityWindowVisible = false;
	MultiSkillsWindowVisible = false;
	MultiSpellsWindowVisible = false;
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::CreateChildWindows()
    {
    HWND Parent;

    Parent = ControlWindow.GetControlWindowHandle();
    LoadWindow.Create(ProgramInstance, Parent);
    AboutWindow.Create(ProgramInstance, Parent);
    ForumExportWindow.Create(ProgramInstance, Parent);
	ItemBuilderWindow.Create(ProgramInstance, Parent);
	ExportTemplateDesignWindow.Create(ProgramInstance, Parent);
	PrintWindow.Create(ProgramInstance, Parent);
	EnhancementWindow.Create(ProgramInstance, Parent);
	MultiEnhancementWindow.Create(ProgramInstance, Parent);
	ToolTipWindow.Create(ProgramInstance, Parent);
	DestinyWindow.Create(ProgramInstance, Parent);
	MultiFeatWindow.Create(ProgramInstance, Parent);
	MultiClassWindow.Create(ProgramInstance, Parent);
	MultiAbilityWindow.Create(ProgramInstance, Parent);
	MultiSkillsWindow.Create(ProgramInstance, Parent);
	MultiSpellsWindow.Create(ProgramInstance, Parent);
    }

//---------------------------------------------------------------------------
RECT InterfaceManagerClass::GetMainWindowExtents()
    {
    RECT Rect;

    Rect = ControlWindow.GetWindowExtents();
    return Rect;
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::ShowChild(CHILDWINDOW Child, bool State)
{
	switch (Child)
	{
		case MAINWINDOW:
		{
			MainScreen.Show(State);
			break;
		}
		case DATALOAD:
		{
			LoadWindow.Show(State);
			DataLoadVisible = State;
			break;
		}
		case ABOUTWINDOW:
		{
			AboutWindow.Show(State);
			AboutWindowVisible = State;
			break;
		}
		case FORUMEXPORTWINDOW:
		{
			ForumExportWindow.Show(State);
			ForumExportWindowVisible = State;
			break;
		}
		case ITEMBUILDERWINDOW:
		{
			ItemBuilderWindow.Show(State);
			ItemBuilderWindowVisible = State;
			if (State == false)
				MainScreen.ResetItemList();
			break;
		}
		case PRINTWINDOW:
		{
			PrintWindow.Show(State);
			PrintWindowVisible = State;
			break;
		}
		case EXPORTTEMPLATEDESIGNWINDOW:
		{
			ExportTemplateDesignWindow.Show(State);
			ExportTemplateDesignWindowVisible = State;
			break;
		}
		case ENHANCEMENTWINDOW:
		{
			EnhancementWindow.Show(State);
			EnhancementWindowVisible = State;
			if (State == false)
				MainScreen.RefreshMainScreen();
			break;
		}
		case MULTIENHANCEMENTWINDOW:
		{
			MultiEnhancementWindow.Show(State);
			MultiEnhancementWindowVisible = State;
			break;
		}
		case TOOLTIPWINDOW:
		{
			ToolTipWindow.Show(State);
			ToolTipWindowVisible = State;
			break;
		}
		case DESTINYWINDOW:
		{
			DestinyWindow.Show(State);
			DestinyWindowVisible = State;
			if (State == false)
				MainScreen.RefreshMainScreen();
			break;
		}
		case MULTIFEATWINDOW:
		{
			MultiFeatWindow.Show(State);
			MultiFeatWindowVisible = State;
			if (State == false)
			{
				MainScreen.RefreshInstructionWindow();
				MainScreen.RefreshMainScreen();
			}

			break;
		}
		case MULTICLASSWINDOW:
		{
			MultiClassWindow.Show(State);
			MultiClassWindowVisible = State;
			if (State == false)
			{
				MainScreen.RefreshInstructionWindow();
				MainScreen.RefreshMainScreen();
			}

			break;
		}
		case MULTIABILITYWINDOW:
		{
			MultiAbilityWindow.Show(State);
			MultiAbilityWindowVisible = State;
			if (State == false)
			{
				//MainScreen.RefreshInstructionWindow();
				MainScreen.RefreshMainScreen();
			}
		}
		case MULTISKILLSWINDOW:
		{
			MultiSkillsWindow.Show(State);
			MultiSkillsWindowVisible = State;
			if (State == false)
			{
				MainScreen.RefreshInstructionWindow();
				MainScreen.RefreshMainScreen();
			}
				
			break;
		}
		case MULTISPELLSWINDOW:

		{
			MultiSpellsWindow.Show(State);
			MultiSpellsWindowVisible = State;
			if (State == false)
				MainScreen.RefreshMainScreen();
			break;
		}
	}
}

//---------------------------------------------------------------------------
long InterfaceManagerClass::ForwardWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    WINDOWID WindowID;

    WindowID = (WINDOWID)GetClassLong(Wnd, 0);
    switch (WindowID)
        {
        case ABOUTWINDOW:
            return AboutWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
        case PRINTWINDOW:
            return PrintWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
        case DATALOAD:
            return LoadWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case EXPORTTEMPLATEDESIGNWINDOW:
			return ExportTemplateDesignWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
        case FORUMEXPORTWINDOW:
            return ForumExportWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case ITEMBUILDERWINDOW:
			return ItemBuilderWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case ENHANCEMENTWINDOW:
			return EnhancementWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case MULTIENHANCEMENTWINDOW:
			return MultiEnhancementWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case TOOLTIPWINDOW:
			return ToolTipWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case DESTINYWINDOW:
			return DestinyWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
        case MAINWINDOW:
            return MainScreen.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case MULTIFEATWINDOW:
			return MultiFeatWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case MULTICLASSWINDOW:
			return MultiClassWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case MULTIABILITYWINDOW:
			return MultiAbilityWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case MULTISKILLSWINDOW:
			return MultiSkillsWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		case MULTISPELLSWINDOW:
			return MultiSpellsWindow.HandleWindowsMessage(Wnd, Message, wParam, lParam);
		default:
            return DefWindowProc(Wnd, Message, wParam, lParam);
        }
    }

//---------------------------------------------------------------------------
long InterfaceManagerClass::ForwardSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    WINDOWID WindowID;

    WindowID = (WINDOWID)GetDlgCtrlID(Wnd);
    switch (WindowID)
        {
		case MS_ADVWINFIRSTNAMEINPUT:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_ADVWINSURNAMEINPUT:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_ABILITYSTATBOX:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_SPELLLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_SKILLSLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_ENHANCEMENTLIST:
			return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_FEATSLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_IW_LIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_ADVWINFEATSLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_ADVWINSKILLSPEND:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_ADVWINSPELLLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_DESCRIPTIONWINDOW:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_LOADBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_SAVEBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_CLEARBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_PRINTBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_FORUMEXPORTBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_DESTINYPANELBUTTON:
			return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_FEATSPANELBUTTON:
			return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_SPELLSPANELBUTTON:
			return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_ENHPANELBUTTON:
			return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_EQUIPMENTSCREENBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_ITEMBUILDERBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_DISPLAYERRORBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_ABOUTBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_QUITBUTTON:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_EQUIPMENTSELECTLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
        case MS_EQUIPMENTDISPLAYSELECTLIST:
            return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MS_ASLIST:
			return MainScreen.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_CURRENTITEMSLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_BASETYPELIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_BONUSEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_PREFIXEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_MATERIALEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_SUFFIXEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_ELDRITCHEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_GSINVASIONELEMENTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_GSINVASIONEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_GSSUBJUGATIONELEMENTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_GSSUBJUGATIONEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_GSDEVASTATIONELEMENTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_GSDEVASTATIONEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_DTELDRITCHEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_DTTEMPESTEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_DTSOVEREIGNEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_SHAVARATHELEMENTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_SHAVARATHEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_EPICFIRSTEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_EPICSECONDEFFECTLIST:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_CURRENTDESCRIPTIONWINDOW:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case IB_BUILDDESCRIPTIONWINDOW:
			return ItemBuilderWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case EW_SELECTTREELIST:
			return EnhancementWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case DW_DESTINIESLIST:
			return DestinyWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case DW_ABILITIESLIST:
			return DestinyWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MFW_SELECTEDPANELLIST:
			return MultiFeatWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MFW_FEATLISTPANELLIST:
			return MultiFeatWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MFW_FEATWISHPANELLIST:
			return MultiFeatWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		case MFW_DESCPANEL:
			return MultiFeatWindow.HandleSubclassedMessage(Wnd, Message, wParam, lParam);
		default:
            return DefWindowProc(Wnd, Message, wParam, lParam);
        }
    }

//---------------------------------------------------------------------------
	void InterfaceManagerClass::CenterChildWindow(CHILDWINDOW Child)
	{
		HWND Parent;
		Parent = ControlWindow.GetControlWindowHandle();
		HWND ChildWindow;
		ChildWindow = EnhancementWindow.GetHandle();
		//Center in current MainScreen
		int ParentX;
		int ParentY;

		RECT WindowRect;
		RECT ParentRect;
		int WindowX;
		int WindowY;
		int TopBar = 25;
		GetWindowRect(Parent, &ParentRect);
		ParentX = ParentRect.right - ParentRect.left;
		ParentY = ParentRect.bottom - ParentRect.top - TopBar;

		switch (Child)
		{
		case MAINWINDOW:
			break;
		case DATALOAD:
			break;
		case ABOUTWINDOW:
			ChildWindow = AboutWindow.GetHandle();
			break;
		case FORUMEXPORTWINDOW:
			break;
		case ITEMBUILDERWINDOW:
			break;
		case EXPORTTEMPLATEDESIGNWINDOW:
			break;
		case PRINTWINDOW:
			ChildWindow = PrintWindow.GetHandle();
			break;
		case ENHANCEMENTWINDOW:
			ChildWindow = EnhancementWindow.GetHandle();
			break;
		case MULTIENHANCEMENTWINDOW:
			ChildWindow = MultiEnhancementWindow.GetHandle();
			break;
		case TOOLTIPWINDOW:
			break;
		case DESTINYWINDOW:
			ChildWindow = DestinyWindow.GetHandle();
			break;
		case MULTIDESTINYWINDOW:
			break;
		case MULTIFEATWINDOW:
			ChildWindow = MultiFeatWindow.GetHandle();
			break;
		case MULTICLASSWINDOW:
			ChildWindow = MultiClassWindow.GetHandle();
			break;
		case MULTIABILITYWINDOW:
			ChildWindow = MultiAbilityWindow.GetHandle();
			break;
		case MULTISKILLSWINDOW:
			ChildWindow = MultiSkillsWindow.GetHandle();
			break;
		case MULTISPELLSWINDOW:
			ChildWindow = MultiSpellsWindow.GetHandle();
			break;
		default:
			break;
		}
		
		GetWindowRect(ChildWindow, &WindowRect);
		WindowX = WindowRect.right - WindowRect.left;
		WindowY = WindowRect.bottom - WindowRect.top;
		SetWindowPos(ChildWindow, Parent, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2) + TopBar, 0, 0, SWP_NOSIZE);
	}
	
//---------------------------------------------------------------------------
bool InterfaceManagerClass::ChildWindowVisible()
    {
    if (DataLoadVisible == false && AboutWindowVisible == false && ForumExportWindowVisible == false && 
			ItemBuilderWindowVisible == false && PrintWindowVisible == false && EnhancementWindowVisible == false
			&& MultiEnhancementWindowVisible == false && DestinyWindowVisible == false)
        return false;
    return true;
    }

//---------------------------------------------------------------------------
bool InterfaceManagerClass::ChildWindowVisible(CHILDWINDOW Child)
	{
	switch (Child)
		{
		case DATALOAD:
			return DataLoadVisible;
		case ABOUTWINDOW:
			return AboutWindowVisible;
		case FORUMEXPORTWINDOW:
			return ForumExportWindowVisible;
		case ITEMBUILDERWINDOW:
			return ItemBuilderWindowVisible;
		case EXPORTTEMPLATEDESIGNWINDOW:
			return DataLoadVisible;
		case PRINTWINDOW:
			return PrintWindowVisible;
		case ENHANCEMENTWINDOW:
			return EnhancementWindowVisible;
		case MULTIENHANCEMENTWINDOW:
			return MultiEnhancementWindowVisible;
		case TOOLTIPWINDOW:
			return ToolTipWindowVisible;
		case DESTINYWINDOW:
			return DestinyWindowVisible;
		case MULTIFEATWINDOW:
			return MultiFeatWindowVisible;
		case MULTICLASSWINDOW:
			return MultiClassWindowVisible;
		case MULTIABILITYWINDOW:
			return MultiAbilityWindowVisible;
		case MULTISKILLSWINDOW:
			return MultiSkillsWindowVisible;
		case MULTISPELLSWINDOW:
			return MultiSpellsWindowVisible;
		}
	return false;
	}

//---------------------------------------------------------------------------
void InterfaceManagerClass::UpdateLoadFileStatus(DATAFILE File, FILESTATE NewState)
    {
    LoadWindow.UpdateLoadFileState(File, NewState);
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::SetMainToDefaults()
    {
    MainScreen.SetToDefault();
    }

//---------------------------------------------------------------------------
unsigned int InterfaceManagerClass::LoadIcon(ICONTYPE IconType, string Name)
    {
    
	return MainScreen.LoadIcon(IconType, Name);
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::DisplayLastError(string Class, string Function, string Command)
    {
	ostringstream OutputString;
	ostringstream TitleString;
    DWORD ErrorCode;
    char *ErrorString;

    //handle any function that requires a GetLastError call
    ErrorCode = GetLastError();
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &ErrorString, 0, NULL);

	OutputString << "Error in Class " << Class << " (Function " << Function << ") - Command " << Command << ", " << ErrorString << " (code " << ErrorCode << ")";
	TitleString << "Error in " << Class << "::" << Function;
	MessageBox(NULL, OutputString.str().c_str(), TitleString.str().c_str(), MB_OK);

    LocalFree(ErrorString);
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::SetForumExportLevel(int NewLevel)
    {
    ForumExportWindow.SetForumExportLevel(NewLevel);
    }

//---------------------------------------------------------------------------
void InterfaceManagerClass::ActivateItemBuilderWindow()
	{
	ItemBuilderWindow.ActivateItemBuilderWindow();
	}

//---------------------------------------------------------------------------
void InterfaceManagerClass::ActivateDestinyWindow(int Level)
	{
	DestinyWindow.ActivateDestinyWindow(Level);
	}

//---------------------------------------------------------------------------
void InterfaceManagerClass::MultiFeatWindowSetLevel(int Level)
{
	MultiFeatWindow.MultiFeatWindowSetLevel(Level);

}
//---------------------------------------------------------------------------
void InterfaceManagerClass::MultiFeatWindowSetIcons(vector <GraphicStruct> FeatIcons)
{
	MultiFeatWindow.SetIcons(FeatIcons);
}

//---------------------------------------------------------------------------
void InterfaceManagerClass::ActivateEnhancementWindow()
	{

	
	EnhancementWindow.ActivateEnhancementWindow();
	}

//---------------------------------------------------------------------------
void InterfaceManagerClass::ActivateMultiEnhancementWindow(int Tree, int Level, int Slot, int APAvailable)
	{
	MultiEnhancementWindow.ActivateMultiEnhancementWindow(Tree, Level, Slot, APAvailable);
	}

//---------------------------------------------------------------------------
void InterfaceManagerClass::SetEnhancementWindowLevel(int Level)
	{
	EnhancementWindow.SetCharacterLevel(Level);
	}

//---------------------------------------------------------------------------
void InterfaceManagerClass::SetEnhancementChildWindowFlag(bool State)
	{
	EnhancementWindow.SetChildWindowFlag(State);
	}

//---------------------------------------------------------------------------
EnhancementWindowClass* InterfaceManagerClass::GetEnhancementWindowPointer()
	{
	return EnhancementWindow.GetPointer();
	}

//---------------------------------------------------------------------------
ToolTipWindowClass* InterfaceManagerClass::GetToolTipWindowPointer()
	{
	return ToolTipWindow.GetPointer();
	}

//---------------------------------------------------------------------------
MainScreenClass* InterfaceManagerClass::GetMainScreen()
	{
	return &MainScreen;
	}

//---------------------------------------------------------------------------
UIComponentManager* InterfaceManagerClass::GetUIComponents()
	{
	return &UIComponents;
	}

//---------------------------------------------------------------------------
char* InterfaceManagerClass::GetInitialDirectory()
	{
	return PathName;
	}











