//---------------------------------------------------------------------------
#include "ItemBuilderClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h" 
#include "DataClass.h"

//---------------------------------------------------------------------------
ItemBuilderClass::ItemBuilderClass()
    {
    CharacterDollPanelCurrentSelectedSlot = NOSLOT;
    }

//---------------------------------------------------------------------------
ItemBuilderClass::~ItemBuilderClass()
    {
    DeleteGraphics();
    DesubclassChildWindows();
    }

//---------------------------------------------------------------------------
void ItemBuilderClass::Create(HINSTANCE Instance, HWND Parent)
    {
    WNDCLASSEX wc;
    int ScreenX;
    int ScreenY;
    RECT ParentRect;
    RECT WindowRect;
    int WindowX;
    int WindowY;
    static char WindowName[] = "Item Builder Window";

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
    ItemBuilderWindowHandle = CreateWindowEx(NULL, WindowName, WindowName, WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 1024, 768, Parent, NULL, Instance, NULL);
    SetClassLong(ItemBuilderWindowHandle, 0, (long)ITEMBUILDERWINDOW);
    ParentRect = InterfaceManager.GetMainWindowExtents();
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(ItemBuilderWindowHandle, &WindowRect);
    WindowX = WindowRect.right - WindowRect.left;
    WindowY = WindowRect.bottom - WindowRect.top;
    SetWindowPos(ItemBuilderWindowHandle, Parent, (ScreenX/2) - (WindowX/2), (ScreenY/2) - (WindowY/2), 0, 0, SWP_NOSIZE);

    //the child windows
    CloseButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 940, 10, 50, 20, ItemBuilderWindowHandle, (HMENU)IB_CLOSEBUTTON, Instance, NULL);
    AddButton = CreateWindowEx(NULL, "BUTTON", "Add", WS_CHILD | BS_PUSHBUTTON, 870, 330, 50, 20, ItemBuilderWindowHandle, (HMENU)IB_ADDBUTTON, Instance, NULL);
    RemoveButton = CreateWindowEx(NULL, "BUTTON", "Remove", WS_CHILD | BS_PUSHBUTTON, 940, 330, 60, 20, ItemBuilderWindowHandle, (HMENU)IB_REMOVEBUTTON, Instance, NULL);
    TitleLabel = CreateWindowEx(NULL, "STATIC", "The Item Builder Screen", WS_CHILD, 380, 10, 300, 20, ItemBuilderWindowHandle, (HMENU)IB_TITLELABEL, Instance, NULL);
	
	//Select Slot Type Box
	SlotTypeFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 10, 40, 290, 270, ItemBuilderWindowHandle, (HMENU)IB_SLOTTYPEFRAME, Instance, NULL);
	SlotTypeLabel = CreateWindowEx(NULL, "STATIC", "Step 1: Choose A Slot", WS_CHILD, 20, 30, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_SLOTTYPELABEL, Instance, NULL);

	// Current Items in Inventory Box
	CurrentItemsFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 320, 40, 400, 270, ItemBuilderWindowHandle, (HMENU)IB_CURRENTITEMSFRAME, Instance, NULL);
	CurrentItemsLabel = CreateWindowEx(NULL, "STATIC", "Current Items in Inventory", WS_CHILD, 330, 30, 200, 20, ItemBuilderWindowHandle, (HMENU)IB_CURRENTITEMSLABEL, Instance, NULL);
	CurrentItemsList = CreateWindowEx(NULL, "LISTBOX", "Current Items List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 321, 45, 398, 263, ItemBuilderWindowHandle, (HMENU)IB_CURRENTITEMSLIST, Instance, NULL);

	// Select a Build Type Box
	BuildTypeFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 10, 340, 800, 40, ItemBuilderWindowHandle, (HMENU)IB_BUILDTYPEFRAME, Instance, NULL);
	BuildTypeLabel = CreateWindowEx(NULL, "STATIC", "Step 2: Choose a Build Type", WS_CHILD, 20, 330, 200, 20, ItemBuilderWindowHandle, (HMENU)IB_BUILDTYPELABEL, Instance, NULL);

	//Radio buttons for choosing which type of items to build.
	GenericSelectBox = CreateWindowEx(NULL, "BUTTON", "Generic", WS_CHILD | BS_AUTORADIOBUTTON, 20, 355, 90, 20, ItemBuilderWindowHandle, (HMENU)IB_GISELECTBOX, Instance, NULL);
	NamedSelectBox = CreateWindowEx(NULL, "BUTTON", "Named", WS_CHILD | BS_AUTORADIOBUTTON, 155, 355, 90, 20, ItemBuilderWindowHandle, (HMENU)IB_NISELECTBOX, Instance, NULL);
	GreenSteelSelectBox = CreateWindowEx(NULL, "BUTTON", "Green Steel", WS_CHILD | BS_AUTORADIOBUTTON, 290, 355, 100, 20, ItemBuilderWindowHandle, (HMENU)IB_GSSELECTBOX, Instance, NULL);
	DragontouchedSelectBox = CreateWindowEx(NULL, "BUTTON", "Dragontouched", WS_CHILD | BS_AUTORADIOBUTTON, 420, 355, 120, 20, ItemBuilderWindowHandle, (HMENU)IB_DTSELECTBOX, Instance, NULL);
	ShavarathRingSelectBox = CreateWindowEx(NULL, "BUTTON", "Shavarath Rings", WS_CHILD | BS_AUTORADIOBUTTON, 560, 355, 150, 20, ItemBuilderWindowHandle, (HMENU)IB_SRSELECTBOX, Instance, NULL);
	EpicSelectBox = CreateWindowEx(NULL, "BUTTON", "Epic", WS_CHILD | BS_AUTORADIOBUTTON, 720, 355, 50, 20, ItemBuilderWindowHandle, (HMENU)IB_EPICSELECTBOX, Instance, NULL);

	//default state for the radio buttons
	SendMessage(GenericSelectBox, BM_SETCHECK, BST_CHECKED, 0);

	// Select a Base Type Box
	BaseTypeFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 10, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_BASETYPEFRAME, Instance, NULL);
	BaseTypeLabel = CreateWindowEx(NULL, "STATIC", "Step 3: Choose A Base", WS_CHILD, 20, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_BASETYPELABEL, Instance, NULL);
    BaseTypeList = CreateWindowEx(NULL, "LISTBOX", "Base Type", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 11, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_BASETYPELIST, Instance, NULL);
	
	//Select a Bonus Effect Box
	BonusEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 200, 400, 180, 100, ItemBuilderWindowHandle, (HMENU)IB_BONUSEFFECTFRAME, Instance, NULL);
	BonusEffectLabel = CreateWindowEx(NULL, "STATIC", "Bonus Effect", WS_CHILD, 210, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_BONUSEFFECTLABEL, Instance, NULL);
    BonusEffectList = CreateWindowEx(NULL, "LISTBOX", "Bonus Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 201, 405, 178, 93, ItemBuilderWindowHandle, (HMENU)IB_BONUSEFFECTLIST, Instance, NULL);

	//Select a Prefix Effect Box
	PrefixEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 390, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_PREFIXEFFECTFRAME, Instance, NULL);
	PrefixEffectLabel = CreateWindowEx(NULL, "STATIC", "Prefix Effect", WS_CHILD, 400, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_PREFIXEFFECTLABEL, Instance, NULL);
    PrefixEffectList = CreateWindowEx(NULL, "LISTBOX", "Prefix Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_PREFIXEFFECTLIST, Instance, NULL);

	//Select a Material Effect Box
	MaterialEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 200, 520, 180, 100, ItemBuilderWindowHandle, (HMENU)IB_MATERIALEFFECTFRAME, Instance, NULL);
	MaterialEffectLabel = CreateWindowEx(NULL, "STATIC", "Material Effect", WS_CHILD, 210, 510, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_MATERIALEFFECTLABEL, Instance, NULL);
    MaterialEffectList = CreateWindowEx(NULL, "LISTBOX", "Material Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 201, 525, 178, 93, ItemBuilderWindowHandle, (HMENU)IB_MATERIALEFFECTLIST, Instance, NULL);

	//Select a Suffix Effect Box
	SuffixEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 580, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_SUFFIXEFFECTFRAME, Instance, NULL);
	SuffixEffectLabel = CreateWindowEx(NULL, "STATIC", "Suffix Effect", WS_CHILD, 590, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_SUFFIXEFFECTLABEL, Instance, NULL);
    SuffixEffectList = CreateWindowEx(NULL, "LISTBOX", "Suffix Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 581, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_SUFFIXEFFECTLIST, Instance, NULL);

	//Select an Eldritch Effect Box
	EldritchEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 200, 640, 180, 100, ItemBuilderWindowHandle, (HMENU)IB_ELDRITCHEFFECTFRAME, Instance, NULL);
	EldritchEffectLabel = CreateWindowEx(NULL, "STATIC", "Eldritch Effect", WS_CHILD, 210, 630, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_ELDRITCHEFFECTLABEL, Instance, NULL);
    EldritchEffectList = CreateWindowEx(NULL, "LISTBOX", "Eldritch Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 201, 645, 178, 93, ItemBuilderWindowHandle, (HMENU)IB_ELDRITCHEFFECTLIST, Instance, NULL);

	//Select Greensteel Effect Boxes
	GSInvasionElementFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 200, 400, 180, 100, ItemBuilderWindowHandle, (HMENU)IB_GSINVASIONELEMENTFRAME, Instance, NULL);
	GSInvasionElementLabel = CreateWindowEx(NULL, "STATIC", "Invasion Element", WS_CHILD, 210, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_GSINVASIONELEMENTLABEL, Instance, NULL);
    GSInvasionElementList = CreateWindowEx(NULL, "LISTBOX", "Invasion Element", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 201, 405, 178, 93, ItemBuilderWindowHandle, (HMENU)IB_GSINVASIONELEMENTLIST, Instance, NULL);
	GSInvasionEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 200, 520, 180, 110, ItemBuilderWindowHandle, (HMENU)IB_GSINVASIONEFFECTFRAME, Instance, NULL);
	GSInvasionEffectLabel = CreateWindowEx(NULL, "STATIC", "Invasion Effect", WS_CHILD, 210, 510, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_GSINVASIONEFFECTLABEL, Instance, NULL);
    GSInvasionEffectList = CreateWindowEx(NULL, "LISTBOX", "Invasion Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 201, 525, 178, 103, ItemBuilderWindowHandle, (HMENU)IB_GSINVASIONEFFECTLIST, Instance, NULL);
	
	GSSubjugationElementFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 390, 400, 180, 100, ItemBuilderWindowHandle, (HMENU)IB_GSSUBJUGATIONELEMENTFRAME, Instance, NULL);
	GSSubjugationElementLabel = CreateWindowEx(NULL, "STATIC", "Subjugation Element", WS_CHILD, 400, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_GSSUBJUGATIONELEMENTLABEL, Instance, NULL);
    GSSubjugationElementList = CreateWindowEx(NULL, "LISTBOX", "Subjugation Element", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 405, 178, 93, ItemBuilderWindowHandle, (HMENU)IB_GSSUBJUGATIONELEMENTLIST, Instance, NULL);
	GSSubjugationEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 390, 520, 180, 220, ItemBuilderWindowHandle, (HMENU)IB_GSSUBJUGATIONEFFECTFRAME, Instance, NULL);
	GSSubjugationEffectLabel = CreateWindowEx(NULL, "STATIC", "Subjugation Effect", WS_CHILD, 400, 510, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_GSSUBJUGATIONEFFECTLABEL, Instance, NULL);
    GSSubjugationEffectList = CreateWindowEx(NULL, "LISTBOX", "Subjugation Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 525, 178, 213, ItemBuilderWindowHandle, (HMENU)IB_GSSUBJUGATIONEFFECTLIST, Instance, NULL);
	
	GSDevastationElementFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 580, 400, 180, 100, ItemBuilderWindowHandle, (HMENU)IB_GSDEVASTATIONELEMENTFRAME, Instance, NULL);
	GSDevastationElementLabel = CreateWindowEx(NULL, "STATIC", "Devastation Element", WS_CHILD, 590, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_GSDEVASTATIONELEMENTLABEL, Instance, NULL);
    GSDevastationElementList = CreateWindowEx(NULL, "LISTBOX", "Devastation Element", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 581, 405, 178, 93, ItemBuilderWindowHandle, (HMENU)IB_GSDEVASTATIONELEMENTLIST, Instance, NULL);
	GSDevastationEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 580, 520, 180, 220, ItemBuilderWindowHandle, (HMENU)IB_GSDEVASTATIONEFFECTFRAME, Instance, NULL);
	GSDevastationEffectLabel = CreateWindowEx(NULL, "STATIC", "Devastation Effect", WS_CHILD, 590, 510, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_GSDEVASTATIONEFFECTLABEL, Instance, NULL);
    GSDevastationEffectList = CreateWindowEx(NULL, "LISTBOX", "Devastation Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 581, 525, 178, 213, ItemBuilderWindowHandle, (HMENU)IB_GSDEVASTATIONEFFECTLIST, Instance, NULL);

	//Select Dragontouched Effect Boxes
	DTEldritchEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 200, 400, 180, 220, ItemBuilderWindowHandle, (HMENU)IB_DTELDRITCHEFFECTFRAME, Instance, NULL);
	DTEldritchEffectLabel = CreateWindowEx(NULL, "STATIC", "Eldritch Rune", WS_CHILD, 210, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_DTELDRITCHEFFECTLABEL, Instance, NULL);
    DTEldritchEffectList = CreateWindowEx(NULL, "LISTBOX", "Eldritch Rune", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 201, 405, 178, 213, ItemBuilderWindowHandle, (HMENU)IB_DTELDRITCHEFFECTLIST, Instance, NULL);
	DTTempestEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 390, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_DTTEMPESTEFFECTFRAME, Instance, NULL);
	DTTempestEffectLabel = CreateWindowEx(NULL, "STATIC", "Tempest Rune", WS_CHILD, 400, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_DTTEMPESTEFFECTLABEL, Instance, NULL);
    DTTempestEffectList = CreateWindowEx(NULL, "LISTBOX", "Tempest Rune", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_DTTEMPESTEFFECTLIST, Instance, NULL);
	DTSovereignEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 580, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_DTSOVEREIGNEFFECTFRAME, Instance, NULL);
	DTSovereignEffectLabel = CreateWindowEx(NULL, "STATIC", "Sovereign Rune", WS_CHILD, 590, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_DTSOVEREIGNEFFECTLABEL, Instance, NULL);
    DTSovereignEffectList = CreateWindowEx(NULL, "LISTBOX", "Sovereign Rune", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 581, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_DTSOVEREIGNEFFECTLIST, Instance, NULL);

	//Select Shavarath Ring Effect Boxes
	ShavarathElementFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 390, 400, 180, 140, ItemBuilderWindowHandle, (HMENU)IB_SHAVARATHELEMENTFRAME, Instance, NULL);
	ShavarathElementLabel = CreateWindowEx(NULL, "STATIC", "Shavarath Element", WS_CHILD, 400, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_SHAVARATHELEMENTLABEL, Instance, NULL);
	ShavarathElementList = CreateWindowEx(NULL, "LISTBOX", "Shavarath Element", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 405, 178, 133, ItemBuilderWindowHandle, (HMENU)IB_SHAVARATHELEMENTLIST, Instance, NULL);
	ShavarathEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 390, 580, 180, 140, ItemBuilderWindowHandle, (HMENU)IB_SHAVARATHEFFECTFRAME, Instance, NULL);
	ShavarathEffectLabel = CreateWindowEx(NULL, "STATIC", "Shavarath Effect", WS_CHILD, 400, 570, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_SHAVARATHEFFECTLABEL, Instance, NULL);
	ShavarathEffectList = CreateWindowEx(NULL, "LISTBOX", "Shavarath Effect", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 585, 178, 133, ItemBuilderWindowHandle, (HMENU)IB_SHAVARATHEFFECTLIST, Instance, NULL);

	//Select Epic Effect Boxes
	EpicFirstEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME,  390, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_EPICFIRSTEFFECTFRAME, Instance, NULL);
	EpicFirstEffectLabel = CreateWindowEx(NULL, "STATIC", "First Slot", WS_CHILD, 400, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_EPICFIRSTEFFECTLABEL, Instance, NULL);
    EpicFirstEffectList = CreateWindowEx(NULL, "LISTBOX", "First Slot", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 391, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_EPICFIRSTEFFECTLIST, Instance, NULL);
	EpicSecondEffectFrame = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME,  580, 400, 180, 350, ItemBuilderWindowHandle, (HMENU)IB_EPICSECONDEFFECTFRAME, Instance, NULL);
	EpicSecondEffectLabel = CreateWindowEx(NULL, "STATIC", "Second Slot", WS_CHILD, 590, 390, 160, 20, ItemBuilderWindowHandle, (HMENU)IB_EPICSECONDEFFECTLABEL, Instance, NULL);
    EpicSecondEffectList = CreateWindowEx(NULL, "LISTBOX", "Second Slot", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 581, 405, 178, 343, ItemBuilderWindowHandle, (HMENU)IB_EPICSECONDEFFECTLIST, Instance, NULL);

	CurrentDescriptionWindow = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_READONLY, 770, 40, 240, 270, ItemBuilderWindowHandle, (HMENU)IB_CURRENTDESCRIPTIONWINDOW, Instance, NULL);
	BuildDescriptionWindow = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_READONLY, 770, 400, 240, 350, ItemBuilderWindowHandle, (HMENU)IB_BUILDDESCRIPTIONWINDOW, Instance, NULL);
	
	SendMessage(CurrentDescriptionWindow, EM_SETBKGNDCOLOR, 0, RGB(0,0,0));
	SendMessage(BuildDescriptionWindow, EM_SETBKGNDCOLOR, 0, RGB(0,0,0));

    SendMessage(CurrentItemsList, LB_SETITEMHEIGHT, 0, MAKELPARAM(20, 0));

	LoadGraphics(ItemBuilderWindowHandle);
    SubclassChildWindows();
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::Show(bool State)
    {
    //pop it up
    ShowWindow(ItemBuilderWindowHandle, State);
    ShowWindow(CloseButton, State);
	ShowWindow(AddButton, State);
	ShowWindow(RemoveButton, State);
	ShowWindow(TitleLabel, State);
	ShowWindow(SlotTypeFrame, State);
	ShowWindow(CurrentItemsLabel, State);
	ShowWindow(CurrentItemsFrame, State);
	ShowWindow(CurrentItemsList, State);
	ShowWindow(BuildTypeFrame, State);
	ShowWindow(SlotTypeLabel, State);
	ShowWindow(GenericSelectBox, State);
	ShowWindow(NamedSelectBox, State);
	ShowWindow(GreenSteelSelectBox, State);
	ShowWindow(DragontouchedSelectBox, State);
	ShowWindow(ShavarathRingSelectBox, State);
	ShowWindow(EpicSelectBox, State);
	ShowWindow(BaseTypeFrame, State);
	ShowWindow(BuildTypeLabel, State);
	ShowWindow(BaseTypeList, State);
	ShowWindow(BaseTypeLabel, State);
	ShowWindow(CurrentDescriptionWindow, State);
	ShowWindow(BuildDescriptionWindow, State);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::ShowEffectWindows(string strBuildType)
	{
	if (strBuildType == "Generic")
		{
		ShowWindow(BonusEffectFrame, true);
		ShowWindow(BonusEffectLabel, true);
		ShowWindow(BonusEffectList, true);
		ShowWindow(PrefixEffectFrame, true);
		ShowWindow(PrefixEffectLabel, true);
		ShowWindow(PrefixEffectList, true);
		ShowWindow(MaterialEffectFrame, true);
		ShowWindow(MaterialEffectLabel, true);
		ShowWindow(MaterialEffectList, true);
		ShowWindow(SuffixEffectFrame, true);
		ShowWindow(SuffixEffectLabel, true);
		ShowWindow(SuffixEffectList, true);
		ShowWindow(EldritchEffectFrame, true);
		ShowWindow(EldritchEffectLabel, true);
		ShowWindow(EldritchEffectList, true);
		ShowWindow(GSInvasionElementFrame, false);
		ShowWindow(GSInvasionElementLabel, false);
		ShowWindow(GSInvasionElementList, false);
		ShowWindow(GSInvasionEffectFrame, false);
		ShowWindow(GSInvasionEffectLabel, false);
		ShowWindow(GSInvasionEffectList, false);
		ShowWindow(GSSubjugationElementFrame, false);
		ShowWindow(GSSubjugationElementLabel, false);
		ShowWindow(GSSubjugationElementList, false);
		ShowWindow(GSSubjugationEffectFrame, false);
		ShowWindow(GSSubjugationEffectLabel, false);
		ShowWindow(GSSubjugationEffectList, false);
		ShowWindow(GSDevastationElementFrame, false);
		ShowWindow(GSDevastationElementLabel, false);
		ShowWindow(GSDevastationElementList, false);
		ShowWindow(GSDevastationEffectFrame, false);
		ShowWindow(GSDevastationEffectLabel, false);
		ShowWindow(GSDevastationEffectList, false);
		ShowWindow(DTEldritchEffectFrame, false);
		ShowWindow(DTEldritchEffectLabel, false);
		ShowWindow(DTEldritchEffectList, false);
		ShowWindow(DTTempestEffectFrame, false);
		ShowWindow(DTTempestEffectLabel, false);
		ShowWindow(DTTempestEffectList, false);
		ShowWindow(DTSovereignEffectFrame, false);
		ShowWindow(DTSovereignEffectLabel, false);
		ShowWindow(DTSovereignEffectList, false);
		ShowWindow(ShavarathElementFrame, false);
		ShowWindow(ShavarathElementLabel, false);
		ShowWindow(ShavarathElementList, false);
		ShowWindow(ShavarathEffectFrame, false);
		ShowWindow(ShavarathEffectLabel, false);
		ShowWindow(ShavarathEffectList, false);
		ShowWindow(EpicFirstEffectFrame, false);
		ShowWindow(EpicFirstEffectLabel, false);
		ShowWindow(EpicFirstEffectList, false);
		ShowWindow(EpicSecondEffectFrame, false);
		ShowWindow(EpicSecondEffectLabel, false);
		ShowWindow(EpicSecondEffectList, false);
		}
	if (strBuildType == "Named")
		{
		ShowWindow(BonusEffectFrame, false);
		ShowWindow(BonusEffectLabel, false);
		ShowWindow(BonusEffectList, false);
		ShowWindow(PrefixEffectFrame, false);
		ShowWindow(PrefixEffectLabel, false);
		ShowWindow(PrefixEffectList, false);
		ShowWindow(MaterialEffectFrame, false);
		ShowWindow(MaterialEffectLabel, false);
		ShowWindow(MaterialEffectList, false);
		ShowWindow(SuffixEffectFrame, false);
		ShowWindow(SuffixEffectLabel, false);
		ShowWindow(SuffixEffectList, false);
		ShowWindow(EldritchEffectFrame, true);
		ShowWindow(EldritchEffectLabel, true);
		ShowWindow(EldritchEffectList, true);
		ShowWindow(GSInvasionElementFrame, false);
		ShowWindow(GSInvasionElementLabel, false);
		ShowWindow(GSInvasionElementList, false);
		ShowWindow(GSInvasionEffectFrame, false);
		ShowWindow(GSInvasionEffectLabel, false);
		ShowWindow(GSInvasionEffectList, false);
		ShowWindow(GSSubjugationElementFrame, false);
		ShowWindow(GSSubjugationElementLabel, false);
		ShowWindow(GSSubjugationElementList, false);
		ShowWindow(GSSubjugationEffectFrame, false);
		ShowWindow(GSSubjugationEffectLabel, false);
		ShowWindow(GSSubjugationEffectList, false);
		ShowWindow(GSDevastationElementFrame, false);
		ShowWindow(GSDevastationElementLabel, false);
		ShowWindow(GSDevastationElementList, false);
		ShowWindow(GSDevastationEffectFrame, false);
		ShowWindow(GSDevastationEffectLabel, false);
		ShowWindow(GSDevastationEffectList, false);
		ShowWindow(DTEldritchEffectFrame, false);
		ShowWindow(DTEldritchEffectLabel, false);
		ShowWindow(DTEldritchEffectList, false);
		ShowWindow(DTTempestEffectFrame, false);
		ShowWindow(DTTempestEffectLabel, false);
		ShowWindow(DTTempestEffectList, false);
		ShowWindow(DTSovereignEffectFrame, false);
		ShowWindow(DTSovereignEffectLabel, false);
		ShowWindow(DTSovereignEffectList, false);
		ShowWindow(ShavarathElementFrame, false);
		ShowWindow(ShavarathElementLabel, false);
		ShowWindow(ShavarathElementList, false);
		ShowWindow(ShavarathEffectFrame, false);
		ShowWindow(ShavarathEffectLabel, false);
		ShowWindow(ShavarathEffectList, false);
		ShowWindow(EpicFirstEffectFrame, false);
		ShowWindow(EpicFirstEffectLabel, false);
		ShowWindow(EpicFirstEffectList, false);
		ShowWindow(EpicSecondEffectFrame, false);
		ShowWindow(EpicSecondEffectLabel, false);
		ShowWindow(EpicSecondEffectList, false);
		}
	if (strBuildType == "Green Steel")
		{
		ShowWindow(BonusEffectFrame, false);
		ShowWindow(BonusEffectLabel, false);
		ShowWindow(BonusEffectList, false);
		ShowWindow(PrefixEffectFrame, false);
		ShowWindow(PrefixEffectLabel, false);
		ShowWindow(PrefixEffectList, false);
		ShowWindow(MaterialEffectFrame, false);
		ShowWindow(MaterialEffectLabel, false);
		ShowWindow(MaterialEffectList, false);
		ShowWindow(SuffixEffectFrame, false);
		ShowWindow(SuffixEffectLabel, false);
		ShowWindow(SuffixEffectList, false);
		ShowWindow(EldritchEffectFrame, true);
		ShowWindow(EldritchEffectLabel, true);
		ShowWindow(EldritchEffectList, true);
		ShowWindow(GSInvasionElementFrame, true);
		ShowWindow(GSInvasionElementLabel, true);
		ShowWindow(GSInvasionElementList, true);
		ShowWindow(GSInvasionEffectFrame, true);
		ShowWindow(GSInvasionEffectLabel, true);
		ShowWindow(GSInvasionEffectList, true);
		ShowWindow(GSSubjugationElementFrame, true);
		ShowWindow(GSSubjugationElementLabel, true);
		ShowWindow(GSSubjugationElementList, true);
		ShowWindow(GSSubjugationEffectFrame, true);
		ShowWindow(GSSubjugationEffectLabel, true);
		ShowWindow(GSSubjugationEffectList, true);
		ShowWindow(GSDevastationElementFrame, true);
		ShowWindow(GSDevastationElementLabel, true);
		ShowWindow(GSDevastationElementList, true);
		ShowWindow(GSDevastationEffectFrame, true);
		ShowWindow(GSDevastationEffectLabel, true);
		ShowWindow(GSDevastationEffectList, true);
		ShowWindow(DTEldritchEffectFrame, false);
		ShowWindow(DTEldritchEffectLabel, false);
		ShowWindow(DTEldritchEffectList, false);
		ShowWindow(DTTempestEffectFrame, false);
		ShowWindow(DTTempestEffectLabel, false);
		ShowWindow(DTTempestEffectList, false);
		ShowWindow(DTSovereignEffectFrame, false);
		ShowWindow(DTSovereignEffectLabel, false);
		ShowWindow(DTSovereignEffectList, false);
		ShowWindow(ShavarathElementFrame, false);
		ShowWindow(ShavarathElementLabel, false);
		ShowWindow(ShavarathElementList, false);
		ShowWindow(ShavarathEffectFrame, false);
		ShowWindow(ShavarathEffectLabel, false);
		ShowWindow(ShavarathEffectList, false);
		ShowWindow(EpicFirstEffectFrame, false);
		ShowWindow(EpicFirstEffectLabel, false);
		ShowWindow(EpicFirstEffectList, false);
		ShowWindow(EpicSecondEffectFrame, false);
		ShowWindow(EpicSecondEffectLabel, false);
		ShowWindow(EpicSecondEffectList, false);
		}
	if (strBuildType == "Dragontouched")
		{
		ShowWindow(BonusEffectFrame, false);
		ShowWindow(BonusEffectLabel, false);
		ShowWindow(BonusEffectList, false);
		ShowWindow(PrefixEffectFrame, false);
		ShowWindow(PrefixEffectLabel, false);
		ShowWindow(PrefixEffectList, false);
		ShowWindow(MaterialEffectFrame, false);
		ShowWindow(MaterialEffectLabel, false);
		ShowWindow(MaterialEffectList, false);
		ShowWindow(SuffixEffectFrame, false);
		ShowWindow(SuffixEffectLabel, false);
		ShowWindow(SuffixEffectList, false);
		ShowWindow(EldritchEffectFrame, true);
		ShowWindow(EldritchEffectLabel, true);
		ShowWindow(EldritchEffectList, true);
		ShowWindow(GSInvasionElementFrame, false);
		ShowWindow(GSInvasionElementLabel, false);
		ShowWindow(GSInvasionElementList, false);
		ShowWindow(GSInvasionEffectFrame, false);
		ShowWindow(GSInvasionEffectLabel, false);
		ShowWindow(GSInvasionEffectList, false);
		ShowWindow(GSSubjugationElementFrame, false);
		ShowWindow(GSSubjugationElementLabel, false);
		ShowWindow(GSSubjugationElementList, false);
		ShowWindow(GSSubjugationEffectFrame, false);
		ShowWindow(GSSubjugationEffectLabel, false);
		ShowWindow(GSSubjugationEffectList, false);
		ShowWindow(GSDevastationElementFrame, false);
		ShowWindow(GSDevastationElementLabel, false);
		ShowWindow(GSDevastationElementList, false);
		ShowWindow(GSDevastationEffectFrame, false);
		ShowWindow(GSDevastationEffectLabel, false);
		ShowWindow(GSDevastationEffectList, false);
		ShowWindow(DTEldritchEffectFrame, true);
		ShowWindow(DTEldritchEffectLabel, true);
		ShowWindow(DTEldritchEffectList, true);
		ShowWindow(DTTempestEffectFrame, true);
		ShowWindow(DTTempestEffectLabel, true);
		ShowWindow(DTTempestEffectList, true);
		ShowWindow(DTSovereignEffectFrame, true);
		ShowWindow(DTSovereignEffectLabel, true);
		ShowWindow(DTSovereignEffectList, true);
		ShowWindow(ShavarathElementFrame, false);
		ShowWindow(ShavarathElementLabel, false);
		ShowWindow(ShavarathElementList, false);
		ShowWindow(ShavarathEffectFrame, false);
		ShowWindow(ShavarathEffectLabel, false);
		ShowWindow(ShavarathEffectList, false);
		ShowWindow(EpicFirstEffectFrame, false);
		ShowWindow(EpicFirstEffectLabel, false);
		ShowWindow(EpicFirstEffectList, false);
		ShowWindow(EpicSecondEffectFrame, false);
		ShowWindow(EpicSecondEffectLabel, false);
		ShowWindow(EpicSecondEffectList, false);
		}
	if (strBuildType == "Shavarath")
		{
		ShowWindow(BonusEffectFrame, false);
		ShowWindow(BonusEffectLabel, false);
		ShowWindow(BonusEffectList, false);
		ShowWindow(PrefixEffectFrame, false);
		ShowWindow(PrefixEffectLabel, false);
		ShowWindow(PrefixEffectList, false);
		ShowWindow(MaterialEffectFrame, false);
		ShowWindow(MaterialEffectLabel, false);
		ShowWindow(MaterialEffectList, false);
		ShowWindow(SuffixEffectFrame, false);
		ShowWindow(SuffixEffectLabel, false);
		ShowWindow(SuffixEffectList, false);
		ShowWindow(EldritchEffectFrame, true);
		ShowWindow(EldritchEffectLabel, true);
		ShowWindow(EldritchEffectList, true);
		ShowWindow(GSInvasionElementFrame, false);
		ShowWindow(GSInvasionElementLabel, false);
		ShowWindow(GSInvasionElementList, false);
		ShowWindow(GSInvasionEffectFrame, false);
		ShowWindow(GSInvasionEffectLabel, false);
		ShowWindow(GSInvasionEffectList, false);
		ShowWindow(GSSubjugationElementFrame, false);
		ShowWindow(GSSubjugationElementLabel, false);
		ShowWindow(GSSubjugationElementList, false);
		ShowWindow(GSSubjugationEffectFrame, false);
		ShowWindow(GSSubjugationEffectLabel, false);
		ShowWindow(GSSubjugationEffectList, false);
		ShowWindow(GSDevastationElementFrame, false);
		ShowWindow(GSDevastationElementLabel, false);
		ShowWindow(GSDevastationElementList, false);
		ShowWindow(GSDevastationEffectFrame, false);
		ShowWindow(GSDevastationEffectLabel, false);
		ShowWindow(GSDevastationEffectList, false);
		ShowWindow(DTEldritchEffectFrame, false);
		ShowWindow(DTEldritchEffectLabel, false);
		ShowWindow(DTEldritchEffectList, false);
		ShowWindow(DTTempestEffectFrame, false);
		ShowWindow(DTTempestEffectLabel, false);
		ShowWindow(DTTempestEffectList, false);
		ShowWindow(DTSovereignEffectFrame, false);
		ShowWindow(DTSovereignEffectLabel, false);
		ShowWindow(DTSovereignEffectList, false);
		ShowWindow(ShavarathElementFrame, true);
		ShowWindow(ShavarathElementLabel, true);
		ShowWindow(ShavarathElementList, true);
		ShowWindow(ShavarathEffectFrame, true);
		ShowWindow(ShavarathEffectLabel, true);
		ShowWindow(ShavarathEffectList, true);
		ShowWindow(EpicFirstEffectFrame, false);
		ShowWindow(EpicFirstEffectLabel, false);
		ShowWindow(EpicFirstEffectList, false);
		ShowWindow(EpicSecondEffectFrame, false);
		ShowWindow(EpicSecondEffectLabel, false);
		ShowWindow(EpicSecondEffectList, false);
		}
	if (strBuildType == "Epic")
		{
		ShowWindow(BonusEffectFrame, false);
		ShowWindow(BonusEffectLabel, false);
		ShowWindow(BonusEffectList, false);
		ShowWindow(PrefixEffectFrame, false);
		ShowWindow(PrefixEffectLabel, false);
		ShowWindow(PrefixEffectList, false);
		ShowWindow(MaterialEffectFrame, false);
		ShowWindow(MaterialEffectLabel, false);
		ShowWindow(MaterialEffectList, false);
		ShowWindow(SuffixEffectFrame, false);
		ShowWindow(SuffixEffectLabel, false);
		ShowWindow(SuffixEffectList, false);
		ShowWindow(EldritchEffectFrame, true);
		ShowWindow(EldritchEffectLabel, true);
		ShowWindow(EldritchEffectList, true);
		ShowWindow(GSInvasionElementFrame, false);
		ShowWindow(GSInvasionElementLabel, false);
		ShowWindow(GSInvasionElementList, false);
		ShowWindow(GSInvasionEffectFrame, false);
		ShowWindow(GSInvasionEffectLabel, false);
		ShowWindow(GSInvasionEffectList, false);
		ShowWindow(GSSubjugationElementFrame, false);
		ShowWindow(GSSubjugationElementLabel, false);
		ShowWindow(GSSubjugationElementList, false);
		ShowWindow(GSSubjugationEffectFrame, false);
		ShowWindow(GSSubjugationEffectLabel, false);
		ShowWindow(GSSubjugationEffectList, false);
		ShowWindow(GSDevastationElementFrame, false);
		ShowWindow(GSDevastationElementLabel, false);
		ShowWindow(GSDevastationElementList, false);
		ShowWindow(GSDevastationEffectFrame, false);
		ShowWindow(GSDevastationEffectLabel, false);
		ShowWindow(GSDevastationEffectList, false);
		ShowWindow(DTEldritchEffectFrame, false);
		ShowWindow(DTEldritchEffectLabel, false);
		ShowWindow(DTEldritchEffectList, false);
		ShowWindow(DTTempestEffectFrame, false);
		ShowWindow(DTTempestEffectLabel, false);
		ShowWindow(DTTempestEffectList, false);
		ShowWindow(DTSovereignEffectFrame, false);
		ShowWindow(DTSovereignEffectLabel, false);
		ShowWindow(DTSovereignEffectList, false);
		ShowWindow(ShavarathElementFrame, false);
		ShowWindow(ShavarathElementLabel, false);
		ShowWindow(ShavarathElementList, false);
		ShowWindow(ShavarathEffectFrame, false);
		ShowWindow(ShavarathEffectLabel, false);
		ShowWindow(ShavarathEffectList, false);
		ShowWindow(EpicFirstEffectFrame, true);
		ShowWindow(EpicFirstEffectLabel, true);
		ShowWindow(EpicFirstEffectList, true);
		ShowWindow(EpicSecondEffectFrame, true);
		ShowWindow(EpicSecondEffectLabel, true);
		ShowWindow(EpicSecondEffectList, true);
		}
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::HandleLeftMouseButtonClick(int x, int y)
    {
    if (x >= 28 && x <= 73 && y >= 71 && y <= 118)
        {
        CharacterDollPanelCurrentSelectedSlot = RIGHTHANDSLOT;
        SetWindowText(CurrentItemsLabel, "Right Hand");
        ChangeSlotTypeSelection();
        }
    else if (x >= 28 && x <= 73 && y >= 124 && y <= 171)
        {
        CharacterDollPanelCurrentSelectedSlot = LEFTHANDSLOT;
        SetWindowText(CurrentItemsLabel, "Left Hand");
        ChangeSlotTypeSelection();
        }
    else if (x >= 28 && x <= 73 && y >= 186 && y <= 228)
        {
        CharacterDollPanelCurrentSelectedSlot = AMMOSLOT;
        SetWindowText(CurrentItemsLabel, "Ammunition");
        ChangeSlotTypeSelection();
        }
	else if (x >= 28 && x <= 73 && y >= 234 && y <= 281)
		{
		CharacterDollPanelCurrentSelectedSlot = QUIVERSLOT;
		SetWindowText(CurrentItemsLabel, "Current Quivers in Inventory");
		ChangeSlotTypeSelection();
		}
    else if (x >= 84 && x <= 129 && y >= 72 && y <= 119)
        {
        CharacterDollPanelCurrentSelectedSlot = FACESLOT;
        SetWindowText(CurrentItemsLabel, "Current Goggles in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 84 && x <= 129 && y >= 125 && y <= 172)
        {
        CharacterDollPanelCurrentSelectedSlot = ARMORSLOT;
        SetWindowText(CurrentItemsLabel, "Current Armor in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 84 && x <= 129 && y >= 182 && y <= 229)
        {
        CharacterDollPanelCurrentSelectedSlot = BRACERSLOT;
        SetWindowText(CurrentItemsLabel, "Current Bracers in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 84 && x <= 129 && y >= 237 && y <= 284)
        {
        CharacterDollPanelCurrentSelectedSlot = LEFTRINGSLOT;
        SetWindowText(CurrentItemsLabel, "Current Rings in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 134 && x <= 179 && y >= 59 && y <= 106)
        {
        CharacterDollPanelCurrentSelectedSlot = HEADSLOT;
        SetWindowText(CurrentItemsLabel, "Current Helms in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 134 && x <= 179 && y >= 252 && y <= 299)
        {
        CharacterDollPanelCurrentSelectedSlot = FEETSLOT;
        SetWindowText(CurrentItemsLabel, "Current Boots in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 186 && x <= 231 && y >= 59 && y <= 106)
        {
        CharacterDollPanelCurrentSelectedSlot = NECKSLOT;
        SetWindowText(CurrentItemsLabel, "Curren Necklaces in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 186 && x <= 231 && y >= 252 && y <= 299)
        {
        CharacterDollPanelCurrentSelectedSlot = GLOVESSLOT;
        SetWindowText(CurrentItemsLabel, "Current Gloves in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 244 && x <= 289 && y >= 71 && y <= 118)
        {
        CharacterDollPanelCurrentSelectedSlot = TRINKETSLOT;
        SetWindowText(CurrentItemsLabel, "Current Trinkets in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 244 && x <= 289 && y >= 125 && y <= 182)
        {
        CharacterDollPanelCurrentSelectedSlot = BACKSLOT;
        SetWindowText(CurrentItemsLabel, "Current Cloaks in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 244 && x <= 289 && y >= 182 && y <= 229)
        {
        CharacterDollPanelCurrentSelectedSlot = WAISTSLOT;
        SetWindowText(CurrentItemsLabel, "Current Belts in Inventory");
        ChangeSlotTypeSelection();
        }
    else if (x >= 244 && x <= 289 && y >= 237 && y <= 284)
        {
        CharacterDollPanelCurrentSelectedSlot = RIGHTRINGSLOT;
        SetWindowText(CurrentItemsLabel, "Current Rings in Inventory");
        ChangeSlotTypeSelection();
        }
	else if (x >= 140 && x <= 230 && y >= 120 && y <= 240)
		{
		CharacterDollPanelCurrentSelectedSlot = NOSLOT;
		SetWindowText(CurrentItemsLabel, "Current Items in Inventory");
		ChangeSlotTypeSelection();
		}
    }
    
//----------------------------------------------------------------------------
long ItemBuilderClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    PAINTSTRUCT ps;

    switch (Message)
        {
        case WM_CLOSE:
	        {
			SendCurrentItemsData();
            InterfaceManager.ShowChild(ITEMBUILDERWINDOW, false);
            return 0;
            }
        case WM_COMMAND:
            {
            if (HIWORD(wParam) == BN_CLICKED)
                {
                if ((int)LOWORD(wParam) == IB_CLOSEBUTTON)
                    {
					SendCurrentItemsData();
                    InterfaceManager.ShowChild(ITEMBUILDERWINDOW, false);
                    return 0;
                    }
				if ((int)LOWORD(wParam) == IB_GISELECTBOX)
					{
					ChangeBuildTypeSelection(GENERIC);
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_NISELECTBOX)
					{
					ChangeBuildTypeSelection(NAMED);
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_GSSELECTBOX)
					{
					ChangeBuildTypeSelection(GREENSTEEL);
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_DTSELECTBOX)
					{
					ChangeBuildTypeSelection(DRAGONTOUCHED);
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_SRSELECTBOX)
					{
					ChangeBuildTypeSelection(SHAVARATHRING);
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_EPICSELECTBOX)
					{
					ChangeBuildTypeSelection(EPIC);
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_REMOVEBUTTON)
					{
					RemoveCurrentItem();
					return 0;
					}
				if ((int)LOWORD(wParam) == IB_ADDBUTTON)
					{
					AddBuildItem();
					return 0;
					}
                }
            return 0;
            }
        case WM_KEYDOWN:
            {
            if ((int)wParam == VK_ESCAPE)
                {
                InterfaceManager.ShowChild(ITEMBUILDERWINDOW, false);
                return 0;
                }
            }
        case WM_LBUTTONDOWN:
			{
			HandleLeftMouseButtonClick(LOWORD(lParam), HIWORD(lParam));
			return 0;
			}
		case WM_CTLCOLORLISTBOX:
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            return (long)GetStockObject(DKGRAY_BRUSH);
            }
		case WM_CTLCOLORSTATIC: // controls the colors for the controls
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            SetTextColor((HDC)wParam, RGB(255,255,255));
            return (long)GetStockObject(DKGRAY_BRUSH);
            }
        case WM_DRAWITEM:
            {
            if ((unsigned int)wParam == IB_CURRENTITEMSLIST)
                {
                DrawCurrentItemsBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
			if ((unsigned int)wParam == IB_BASETYPELIST)
				{
				DrawBaseTypesBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_BONUSEFFECTLIST)
				{
				DrawBonusEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_PREFIXEFFECTLIST)
				{
				DrawPrefixEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_MATERIALEFFECTLIST)
				{
				DrawMaterialEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_SUFFIXEFFECTLIST)
				{
				DrawSuffixEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_ELDRITCHEFFECTLIST)
				{
				DrawEldritchEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_GSINVASIONELEMENTLIST)
				{
				DrawGSInvasionElementBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_GSINVASIONEFFECTLIST)
				{
				DrawGSInvasionEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_GSSUBJUGATIONELEMENTLIST)
				{
				DrawGSSubjugationElementBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_GSSUBJUGATIONEFFECTLIST)
				{
				DrawGSSubjugationEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_GSDEVASTATIONELEMENTLIST)
				{
				DrawGSDevastationElementBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_GSDEVASTATIONEFFECTLIST)
				{
				DrawGSDevastationEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_DTELDRITCHEFFECTLIST)
				{
				DrawDTEldritchEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_DTTEMPESTEFFECTLIST)
				{
				DrawDTTempestEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_DTSOVEREIGNEFFECTLIST)
				{
				DrawDTSovereignEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_SHAVARATHELEMENTLIST)
				{
				DrawShavarathElementBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_SHAVARATHEFFECTLIST)
				{
				DrawShavarathEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_EPICFIRSTEFFECTLIST)
				{
				DrawEpicFirstEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			if ((unsigned int)wParam == IB_EPICSECONDEFFECTLIST)
				{
				DrawEpicSecondEffectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
            return false;
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
long ItemBuilderClass::HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    WNDPROC OriginalProc;
    DWORD Selection;
    int IconDrag;

    switch (Message)
        {
        case WM_LBUTTONDBLCLK:
            {
            if (Wnd == CurrentItemsList)
                return 0;
            break;
            }
        case WM_LBUTTONDOWN:
            {
            if (Wnd == CurrentItemsList)
                {
                Selection = SendMessage(CurrentItemsList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(CurrentItemsList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeItemCurrentlySelected(IconDrag);
                return 0;
                }
            if (Wnd == BaseTypeList)
                {
                Selection = SendMessage(BaseTypeList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(BaseTypeList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeBaseTypeCurrentlySelected(IconDrag);
                return 0;
                }
			if (Wnd == BonusEffectList)
				{
                Selection = SendMessage(BonusEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(BonusEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeBonusEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == PrefixEffectList)
				{
                Selection = SendMessage(PrefixEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(PrefixEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangePrefixEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == MaterialEffectList)
				{
                Selection = SendMessage(MaterialEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(MaterialEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeMaterialEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == SuffixEffectList)
				{
                Selection = SendMessage(SuffixEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(SuffixEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeSuffixEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == EldritchEffectList)
				{
                Selection = SendMessage(EldritchEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(EldritchEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeEldritchEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == GSInvasionElementList)
				{
                Selection = SendMessage(GSInvasionElementList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(GSInvasionElementList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeGSInvasionElementCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == GSInvasionEffectList)
				{
                Selection = SendMessage(GSInvasionEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(GSInvasionEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeGSInvasionEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == GSSubjugationElementList)
				{
                Selection = SendMessage(GSSubjugationElementList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(GSSubjugationElementList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeGSSubjugationElementCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == GSSubjugationEffectList)
				{
                Selection = SendMessage(GSSubjugationEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(GSSubjugationEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeGSSubjugationEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == GSDevastationElementList)
				{
                Selection = SendMessage(GSDevastationElementList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(GSDevastationElementList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeGSDevastationElementCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == GSDevastationEffectList)
				{
                Selection = SendMessage(GSDevastationEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(GSDevastationEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeGSDevastationEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == DTEldritchEffectList)
				{
                Selection = SendMessage(DTEldritchEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(DTEldritchEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeDTEldritchEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == DTTempestEffectList)
				{
                Selection = SendMessage(DTTempestEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(DTTempestEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeDTTempestEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == DTSovereignEffectList)
				{
                Selection = SendMessage(DTSovereignEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(DTSovereignEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeDTSovereignEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == ShavarathElementList)
				{
                Selection = SendMessage(ShavarathElementList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(ShavarathElementList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeShavarathElementCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == ShavarathEffectList)
				{
                Selection = SendMessage(ShavarathEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(ShavarathEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeShavarathEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == EpicFirstEffectList)
				{
                Selection = SendMessage(EpicFirstEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(EpicFirstEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeEpicFirstEffectCurrentlySelected(IconDrag);
                return 0;
				}
			if (Wnd == EpicSecondEffectList)
				{
                Selection = SendMessage(EpicSecondEffectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(EpicSecondEffectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeEpicSecondEffectCurrentlySelected(IconDrag);
                return 0;
				}
			break;
            }
        }

    OriginalProc = GetOriginalWinProc(Wnd);
    return CallWindowProc(OriginalProc, Wnd, Message, wParam, lParam);
    }
    
//------------------------------------------------------------------------------------------------
void ItemBuilderClass::DrawGraphics(HDC hdc)
    {
    DrawGraphic(hdc, &CharacterDollPanel, 20, 50, 270, 250);
    if (CharacterDollPanelCurrentSelectedSlot == RIGHTHANDSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 27, 70, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == LEFTHANDSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 27, 123, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == AMMOSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 27, 185, 45, 47);
	if (CharacterDollPanelCurrentSelectedSlot == QUIVERSLOT)
		DrawGraphic(hdc, &CharacterDollPanelHighlight, 27, 229, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == FACESLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 82, 70, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == ARMORSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 82, 123, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == BRACERSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 82, 180, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == LEFTRINGSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 82, 235, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == HEADSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 132, 57, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == FEETSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 132, 250, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == NECKSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 184, 57, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == GLOVESSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 184, 250, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == TRINKETSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 240, 69, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == BACKSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 240, 123, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == WAISTSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 240, 180, 45, 47);
    if (CharacterDollPanelCurrentSelectedSlot == RIGHTRINGSLOT)
        DrawGraphic(hdc, &CharacterDollPanelHighlight, 240, 235, 45, 47);
    }
    
//-------------------------------------------------------------------------------------------------
void ItemBuilderClass::ActivateItemBuilderWindow()
    {
    GetCurrentItemsData();
	FillCurrentItemsBox();
	ItemCurrentlySelected = -1;
	FillDescriptionBox("Current");
//	EnableWindow(GreenSteelSelectBox, false);
//	EnableWindow(DragontouchedSelectBox, false);
//	EnableWindow(ShavarathRingSelectBox, false);
//	EnableWindow(EpicSelectBox, false);
	EnableWindow(AddButton, false);
	EnableWindow(RemoveButton, false);
    }

//---------------------------------------------------------------------------
void ItemBuilderClass::SubclassChildWindows()
    {
    WNDPROC OriginalProc;

    SubclassHWNDs.clear();
    OriginalProcs.clear();

    OriginalProc = (WNDPROC)SetWindowLong(CurrentItemsList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(CurrentItemsList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(BaseTypeList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(BaseTypeList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(BonusEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(BonusEffectList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(PrefixEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(PrefixEffectList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(MaterialEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(MaterialEffectList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(SuffixEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(SuffixEffectList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(EldritchEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(EldritchEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(GSInvasionElementList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(GSInvasionElementList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(GSInvasionEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(GSInvasionEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(GSSubjugationElementList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(GSSubjugationElementList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(GSSubjugationEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(GSSubjugationEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(GSDevastationElementList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(GSDevastationElementList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(GSDevastationEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(GSDevastationEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(DTEldritchEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(DTEldritchEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(DTTempestEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(DTTempestEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(DTSovereignEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(DTSovereignEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(ShavarathElementList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(ShavarathElementList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(ShavarathEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(ShavarathEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(EpicFirstEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(EpicFirstEffectList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(EpicSecondEffectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(EpicSecondEffectList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(CurrentDescriptionWindow, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(CurrentDescriptionWindow);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(BuildDescriptionWindow, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(BuildDescriptionWindow);
    OriginalProcs.push_back(OriginalProc);
    }

//---------------------------------------------------------------------------
void ItemBuilderClass::LoadGraphics(HWND Parent)
    {
    HDC hdc;

    //palette for halftone work
    hdc = GetDC(Parent);
    Palette = CreateHalftonePalette(hdc);
    ReleaseDC(Parent, hdc);

    //Character Doll screen
    LoadBitmap("CharacterDollScreen", "UserInterface", &CharacterDollPanel);
    LoadBitmap("EquipmentSlotHighlight", "UserInterface", &CharacterDollPanelHighlight, NULL, 20, 20);
    }
    
//---------------------------------------------------------------------------
void ItemBuilderClass::DesubclassChildWindows()
    {
    for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
		SetWindowLongPtr(SubclassHWNDs[i], GWL_WNDPROC, static_cast<__int3264>(reinterpret_cast<LONG_PTR>(OriginalProcs[i]))); 
	}

//---------------------------------------------------------------------------
WNDPROC ItemBuilderClass::GetOriginalWinProc(HWND Window)
    {
    for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
        {
        if (SubclassHWNDs[i] == Window)
            return OriginalProcs[i];
	}
    return 0;
    }
    
//-----------------------------------------------------------------------------
void ItemBuilderClass::DeleteGraphics()
    {
    DeleteObject(CharacterDollPanel.Graphic);
    DeleteObject(CharacterDollPanel.Mask);
    DeleteObject(CharacterDollPanelHighlight.Graphic);
    DeleteObject(CharacterDollPanelHighlight.Mask);
    DeleteObject(Palette);
    }
    
//---------------------------------------------------------------------------
void ItemBuilderClass::ChangeBuildTypeSelection(unsigned int BuildType)
	{
	SetAllEffectVariablesToZero();
	BaseTypeCurrentlySelected = -1;
	EnableWindow(AddButton, false);

	if (SendMessage(GenericSelectBox, BM_GETCHECK, 0, 0) ==  BST_CHECKED)
		{
		ShowEffectWindows("Generic");
		FillBonusEffectBox();
		FillPrefixEffectBox();
		FillMaterialEffectBox();
		FillSuffixEffectBox();
		}
	if (SendMessage(NamedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Named");
		}
	if (SendMessage(GreenSteelSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Green Steel");
		FillGSInvasionElementBox();
		FillGSInvasionEffectBox();
		FillGSSubjugationElementBox();
		FillGSSubjugationEffectBox();
		FillGSDevastationElementBox();
		FillGSDevastationEffectBox();
		}
	if (SendMessage(DragontouchedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Dragontouched");
		FillDTEldritchEffectBox();
		FillDTTempestEffectBox();
		FillDTSovereignEffectBox();
		}
	if (SendMessage(ShavarathRingSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Shavarath");
		FillShavarathElementBox();
		FillShavarathEffectBox();
		}
	if (SendMessage(EpicSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Epic");
		FillEpicFirstEffectBox();
		FillEpicSecondEffectBox();
		}

	FillBaseTypesBox();
	FillEldritchEffectBox();
	FillDescriptionBox("Build");

	}
	
//---------------------------------------------------------------------------
void ItemBuilderClass::ChangeSlotTypeSelection()
    {
    HDC hdc;

	ItemCurrentlySelected = -1; // set this to unselect the previous item selected.
	EnableWindow(RemoveButton, false);
	SetAllEffectVariablesToZero();
	FillDescriptionBox("Current");
	BaseTypeCurrentlySelected = -1;
	FillDescriptionBox("Build");
	EnableWindow(AddButton, false);

	if (SendMessage(GenericSelectBox, BM_GETCHECK, 0, 0) ==  BST_CHECKED)
		{
		ShowEffectWindows("Generic");
		FillPrefixEffectBox();
		FillMaterialEffectBox();
		FillBonusEffectBox();
		FillSuffixEffectBox();
		}
	if (SendMessage(NamedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Named");
		}
	if (SendMessage(GreenSteelSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Green Steel");
		FillGSInvasionElementBox();
		FillGSInvasionEffectBox();
		FillGSSubjugationElementBox();
		FillGSSubjugationEffectBox();
		FillGSDevastationElementBox();
		FillGSDevastationEffectBox();
		}
	if (SendMessage(DragontouchedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Dragontouched");
		FillDTEldritchEffectBox();
		FillDTTempestEffectBox();
		FillDTSovereignEffectBox();
		}
	if (SendMessage(ShavarathRingSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Shavarath");
		FillShavarathElementBox();
		FillShavarathEffectBox();
		}
	if (SendMessage(EpicSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		ShowEffectWindows("Epic");
		FillEpicFirstEffectBox();
		FillEpicSecondEffectBox();
		}

    FillCurrentItemsBox();
	FillBaseTypesBox();
	FillEldritchEffectBox();

    hdc = GetDC(ItemBuilderWindowHandle);
    DrawGraphics(hdc);
    ReleaseDC(ItemBuilderWindowHandle, hdc);
    }

//---------------------------------------------------------------------------
void ItemBuilderClass::GetCurrentItemsData()
    {
    int Index;
    int ItemCount;
    int Result;
	CharacterItemStruct NewItem;
	unsigned int ItemIndex;
	//vector <unsigned int> NumOfEffects;
	unsigned int ItemEffect1;
	unsigned int ItemEffect2;
	unsigned int ItemEffect3;
	unsigned int ItemEffect4;
	unsigned int ItemEffect5;
	unsigned int ItemEffect6;
	unsigned int Eldritch;

	ItemIndex = 0;
/*	for(unsigned int i = 0; i<CurrentItems[ItemIndex].ItemEffects.size(); i++)
		{
		NumOfEffects.push_back(0);
		}
*/	ItemEffect1 = 0;
	ItemEffect2 = 0;
	ItemEffect3 = 0;
	ItemEffect4 = 0;
	ItemEffect5 = 0;
	ItemEffect6 = 0;
	Eldritch = 0;

	NewItem.ItemIndex = 0;
/*	for(unsigned int i = 0; i<NumOfEffects.size(); i++)
		{
		NewItem.ItemEffects.push_back(0);
		}
*/	NewItem.ItemEffect1 = 0;
	NewItem.ItemEffect2 = 0;
	NewItem.ItemEffect3 = 0;
	NewItem.ItemEffect4 = 0;
	NewItem.ItemEffect5 = 0;
	NewItem.ItemEffect6 = 0;
	NewItem.Eldritch = 0;

    CurrentItems.clear();
    Index = 0;
	//Result = Character.GetItemData(Index, &ItemIndex, &NumOfEffects);
    Result = Character.GetItemData(Index, &ItemIndex, &ItemEffect1, &ItemEffect2, &ItemEffect3, &ItemEffect4, &ItemEffect5, &ItemEffect6, &Eldritch);
    while (Result == 0)
        {
        CurrentItems.push_back(NewItem);
        ItemCount = CurrentItems.size()-1;
        CurrentItems[ItemCount].ItemIndex = ItemIndex;
/*		for (unsigned int i=0; i<CurrentItems[ItemIndex].ItemEffects.size(); i++)
			{
			CurrentItems[ItemCount].ItemEffects[i] = NumOfEffects[i];
			}*/
        CurrentItems[ItemCount].ItemEffect1 = ItemEffect1;
        CurrentItems[ItemCount].ItemEffect2 = ItemEffect2;
        CurrentItems[ItemCount].ItemEffect3 = ItemEffect3;
        CurrentItems[ItemCount].ItemEffect4 = ItemEffect4;
        CurrentItems[ItemCount].ItemEffect5 = ItemEffect5;
        CurrentItems[ItemCount].ItemEffect6 = ItemEffect6;
        CurrentItems[ItemCount].Eldritch = Eldritch;
        Index++;
/*		NumOfEffects.clear();
		for (unsigned int i=0; i<CurrentItems[Index].ItemEffects.size(); i++)
			{
			NumOfEffects.push_back(0);
			}
		Result = Character.GetItemData(Index, &ItemIndex, &NumOfEffects);*/
		Result = Character.GetItemData(Index, &ItemIndex, &ItemEffect1, &ItemEffect2, &ItemEffect3, &ItemEffect4, &ItemEffect5, &ItemEffect6, &Eldritch);

        }
	/* Temporary Data fill for testing
	CurrentItems.push_back(NewItem);
	ItemCount = CurrentItems.size()-1;
	CurrentItems[ItemCount].ItemIndex = 1;
	ItemCount++;
	CurrentItems.push_back(NewItem);
	ItemCount = CurrentItems.size()-1;
	CurrentItems[ItemCount].ItemIndex = 3;
	ItemCount++;
	CurrentItems.push_back(NewItem);
	ItemCount = CurrentItems.size()-1;
	CurrentItems[ItemCount].ItemIndex = 3;
	CurrentItems[ItemCount].ItemEffect1 = 1; 
	*/
    }

//---------------------------------------------------------------------------
void ItemBuilderClass::FillCurrentItemsBox()
	{
	SendMessage(CurrentItemsList, LB_RESETCONTENT, 0, 0);

    for (unsigned int i=0; i<CurrentItems.size(); i++)
		{
		if (CharacterDollPanelCurrentSelectedSlot == NOSLOT)
			SendMessage(CurrentItemsList, LB_ADDSTRING, 0, i);
		else if (DoesItemFitSelectedSlot(CurrentItems[i].ItemIndex))
			SendMessage(CurrentItemsList, LB_ADDSTRING, 0, i);
        }
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::FillBaseTypesBox()
	{
	ItemClass *ptItem;
	int ItemSize;

	SendMessage(BaseTypeList, LB_RESETCONTENT, 0, 0);
	
	ItemSize = Data.GetItemSize();
	for (int i=0; i<ItemSize; i++)
		{
		ptItem = Data.GetItemPointer(i);
		if (SendMessage(GenericSelectBox, BM_GETCHECK, 0, 0) ==  BST_CHECKED)
			{
			if (ptItem->GetItemBase() == GENERIC)
				if (DoesItemFitSelectedSlot(i))
					SendMessage(BaseTypeList, LB_ADDSTRING, 0, i);
			}
		else if (SendMessage(NamedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			if (ptItem->GetItemBase() == NAMED)
				if (DoesItemFitSelectedSlot(i))
					SendMessage(BaseTypeList, LB_ADDSTRING, 0, i);
			}
		else if (SendMessage(GreenSteelSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			if (ptItem->GetItemBase() == GREENSTEEL)
				if(DoesItemFitSelectedSlot(i))
					SendMessage(BaseTypeList, LB_ADDSTRING, 0, i);
			}
		else if (SendMessage(DragontouchedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			if (ptItem->GetItemBase() == DRAGONTOUCHED)
				if(DoesItemFitSelectedSlot(i))
					SendMessage(BaseTypeList, LB_ADDSTRING, 0, i);
			}
		else if (SendMessage(ShavarathRingSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			if (ptItem->GetItemBase() == SHAVARATHRING)
				if(DoesItemFitSelectedSlot(i))
					SendMessage(BaseTypeList, LB_ADDSTRING, 0, i);
			}
		else if (SendMessage(EpicSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
			if (ptItem->GetItemBase() == EPIC)
				if(DoesItemFitSelectedSlot(i))
					SendMessage(BaseTypeList, LB_ADDSTRING, 0, i);
			}
		}
	}
	
//---------------------------------------------------------------------------
void ItemBuilderClass::FillBonusEffectBox()
	{
	SendMessage(BonusEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(BonusEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(BONUS))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(BonusEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillPrefixEffectBox()
	{
	SendMessage(PrefixEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(PrefixEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(PREFIX))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(PrefixEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillMaterialEffectBox()
	{
	SendMessage(MaterialEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(MaterialEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(MATERIAL))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(MaterialEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}
	
//---------------------------------------------------------------------------
void ItemBuilderClass::FillSuffixEffectBox()
	{
	SendMessage(SuffixEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(SuffixEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();
	
		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(SUFFIX))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(SuffixEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillEldritchEffectBox()
	{
	SendMessage(EldritchEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(EldritchEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(ELDRITCH))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(EldritchEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillGSInvasionElementBox()
	{
	SendMessage(GSInvasionElementList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(GSInvasionElementList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(INVASIONELEMENT))
					SendMessage(GSInvasionElementList, LB_ADDSTRING, 0, i);
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillGSInvasionEffectBox()
	{
	SendMessage(GSInvasionEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemEffectClass *ptGSInvasionElement;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;
	unsigned int GSInvasionElement;

	ptGSInvasionElement = Data.GetItemEffectPointer(GSInvasionElementCurrentlySelected);
	GSInvasionElement = ptGSInvasionElement->GetGSElementType(0);
	ItemEffectSize = Data.GetItemEffectSize();

	if (BaseTypeCurrentlySelected == -1)
		SendMessage(GSInvasionEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(GSINVASION))
				{
				if (ptItemEffect->GetGSElementType(0) == NOEFFECT)
					SendMessage(GSInvasionEffectList, LB_ADDSTRING, 0, i);
				else if (ptItemEffect->DoesGSElementTypeMatch(GSInvasionElement) && GSInvasionElementCurrentlySelected != 0)
					SendMessage(GSInvasionEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillGSSubjugationElementBox()
	{
	SendMessage(GSSubjugationElementList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;  // a pointer to the Effects that will populate our list
	ItemEffectClass *ptGSInvasionEffect;  // a pointer to the InvasionElement so we can test for congruency
	ItemClass *ptItem; // holder for the Base Type of the item we're adding effects to
	int ItemEffectSize;  // the size or number of entries in the ItemEffectsFile
	int intAppliedTo;  // which item bases we can apply the effects to
	vector <unsigned int> GSInvasionEffectElementTypes;  // the specific GSElement we want to test for
	int GSInvasionEffectElementsSize;

	ItemEffectSize = Data.GetItemEffectSize();  // get the size of the ItemEffectsFile
	ptGSInvasionEffect = Data.GetItemEffectPointer(GSInvasionEffectCurrentlySelected);  // grab the Invasion Element we've already selected as the first ItemEffectIndex
	GSInvasionEffectElementsSize = ptGSInvasionEffect->GetGSElementTypesSize();  // find the size of our vector

	if (BaseTypeCurrentlySelected == -1)  // check to make sure we've selected an item type
		SendMessage(GSSubjugationElementList, LB_ADDSTRING, 0, 0);  // so we don't add any effects at all yet
	else
		{//otherwise
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected); // we get to the item we're adding to
		intAppliedTo = ptItem->GetItemType(); // and find it's base type

		for (int i=0; i<ItemEffectSize; i++) // parse through the whole ItemEffectFile
			{
			ptItemEffect = Data.GetItemEffectPointer(i); // checking each Effect
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(SUBJUGATIONELEMENT)) // to see if it fits the selected item and is a GS Subjugation Element
				{
				if (ptItemEffect->GetGSElementType(0) == NOEFFECT)
					SendMessage(GSSubjugationElementList, LB_ADDSTRING, 0, i);
				for (int j=0; j<GSInvasionEffectElementsSize; j++)  // parse through it
					{
					GSInvasionEffectElementTypes.push_back(ptGSInvasionEffect->GetGSElementType(j));  // adding the Element Types
					if (ptItemEffect->DoesGSElementTypeMatch(GSInvasionEffectElementTypes[j]) && GSInvasionEffectCurrentlySelected != 0)  // if the effect we're currently looking at in our parse has a same Element as our Invasion Effect's Element
						SendMessage(GSSubjugationElementList, LB_ADDSTRING, 0, i);  // we add it to the SubjugationElement list we're trying to populate
					}
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillGSSubjugationEffectBox()
	{
	SendMessage(GSSubjugationEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemEffectClass *ptGSInvasionEffect;
	ItemEffectClass *ptGSSubjugationElement;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;
	vector <unsigned int> GSInvasionEffectElements;
	int GSInvasionEffectElementsSize;
	vector <unsigned int> GSSubjugationElements;
	int GSSubjugationElementsSize;

	ItemEffectSize = Data.GetItemEffectSize();
	ptGSInvasionEffect = Data.GetItemEffectPointer(GSInvasionEffectCurrentlySelected);
	GSInvasionEffectElementsSize = ptGSInvasionEffect->GetGSElementTypesSize();  // find the size of our vector
	ptGSSubjugationElement = Data.GetItemEffectPointer(GSSubjugationElementCurrentlySelected);
	GSSubjugationElementsSize = ptGSSubjugationElement->GetGSElementTypesSize();

	if (BaseTypeCurrentlySelected == -1)
		SendMessage(GSSubjugationEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(GSSUBJUGATION))
				{
				if (ptItemEffect->GetGSElementType(0) == NOEFFECT)
					SendMessage(GSSubjugationEffectList, LB_ADDSTRING, 0, i);
				for (int j=0; j<GSInvasionEffectElementsSize; j++)
					{
					GSInvasionEffectElements.push_back(ptGSInvasionEffect->GetGSElementType(j));
					if (ptItemEffect->DoesGSElementTypeMatch(GSInvasionEffectElements[j]))
						for (int k=0; k<GSSubjugationElementsSize; k++)
							{
							GSSubjugationElements.push_back(ptGSSubjugationElement->GetGSElementType(k));
							if(ptItemEffect->DoesGSElementTypeMatch(GSSubjugationElements[k]) && GSInvasionEffectElements[j] == GSSubjugationElements[k] && GSSubjugationElementCurrentlySelected != 0)
								SendMessage(GSSubjugationEffectList, LB_ADDSTRING, 0, i);
							}
					}
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillGSDevastationElementBox()
	{
	SendMessage(GSDevastationElementList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemEffectClass *ptGSSubjugationElement;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;
	vector <unsigned int> GSSubjugationElements;
	int GSSubjugationElementsSize;

	ItemEffectSize = Data.GetItemEffectSize();
	ptGSSubjugationElement = Data.GetItemEffectPointer(GSSubjugationElementCurrentlySelected);
	GSSubjugationElementsSize = ptGSSubjugationElement->GetGSElementTypesSize();

	if (BaseTypeCurrentlySelected == -1)
		SendMessage(GSDevastationElementList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(DEVASTATIONELEMENT))
				{
				if (ptItemEffect->GetGSElementType(0) == NOEFFECT)
					SendMessage(GSDevastationElementList, LB_ADDSTRING, 0, i);
				for (int j=0; j<GSSubjugationElementsSize; j++)
					{
					GSSubjugationElements.push_back(ptGSSubjugationElement->GetGSElementType(j));
					if (ptItemEffect->DoesGSElementTypeMatch(GSSubjugationElements[j]) && GSSubjugationEffectCurrentlySelected != 0)
						SendMessage(GSDevastationElementList, LB_ADDSTRING, 0, i);
					}
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillGSDevastationEffectBox()
	{
	SendMessage(GSDevastationEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemEffectClass *ptGSDevastationElement;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;
	int ItemEffectElementsSize;
	int GSDevastationElementsSize;

	ItemEffectSize = Data.GetItemEffectSize();
	ptGSDevastationElement = Data.GetItemEffectPointer(GSDevastationElementCurrentlySelected);
	GSDevastationElementsSize = ptGSDevastationElement->GetGSElementTypesSize();

	if (BaseTypeCurrentlySelected == -1)
		SendMessage(GSDevastationEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(GSDEVASTATION))
					{
					if (ptItemEffect->GetGSElementType(0) == NOEFFECT)
						SendMessage(GSDevastationEffectList, LB_ADDSTRING, 0, i);
					ItemEffectElementsSize = ptItemEffect->GetGSElementTypesSize();
					for (int j=0; j<GSDevastationElementsSize; j++)
						for (int k=0; k<ItemEffectElementsSize; k++)
							if (ptItemEffect->GetGSElementType(k) == ptGSDevastationElement->GetGSElementType(j) && GSDevastationElementCurrentlySelected != 0)
								SendMessage(GSDevastationEffectList, LB_ADDSTRING, 0, i);
					}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillDTEldritchEffectBox()
	{
	SendMessage(DTEldritchEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(DTEldritchEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(DTELDRITCH))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(DTEldritchEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillDTTempestEffectBox()
	{
	SendMessage(DTTempestEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(DTTempestEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(DTTEMPEST))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(DTTempestEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillDTSovereignEffectBox()
	{
	SendMessage(DTSovereignEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(DTSovereignEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(DTSOVEREIGN))
				{
				if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
					SendMessage(DTSovereignEffectList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillShavarathElementBox()
	{
	SendMessage(ShavarathElementList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(ShavarathElementList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo))
				{
				if (ptItemEffect->DoesTypeMatch(SHAVARATHELEMENT))
					SendMessage(ShavarathElementList, LB_ADDSTRING, 0, i);
				}
			}
		}
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::FillShavarathEffectBox()
	{
	SendMessage(ShavarathEffectList, LB_RESETCONTENT, 0, 0);

	ItemEffectClass *ptItemEffect;
	ItemEffectClass *ptShavarathElement;
	ItemClass *ptItem;
	int ItemEffectSize;
	int intAppliedTo;
	int ShavarathElementsSize;
	int ShavarathEffectElementsSize;

	ItemEffectSize = Data.GetItemEffectSize();
	ptShavarathElement = Data.GetItemEffectPointer(ShavarathElementCurrentlySelected);
	ShavarathElementsSize = ptShavarathElement->GetGSElementTypesSize();

	if (BaseTypeCurrentlySelected == -1)
		SendMessage(ShavarathEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		intAppliedTo = ptItem->GetItemType();

		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesAppliedToMatch(intAppliedTo) && ptItemEffect->DoesTypeMatch(SHAVARATHEFFECT))
					{
					ShavarathEffectElementsSize = ptItemEffect->GetGSElementTypesSize();
					for (int j=0; j<ShavarathElementsSize; j++)
						for (int k=0; k<ShavarathEffectElementsSize; k++)
							if (ptShavarathElement->GetGSElementType(j) == ptItemEffect->GetGSElementType(k))
								SendMessage(ShavarathEffectList, LB_ADDSTRING, 0, i);
					}
			}
		}
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::FillEpicFirstEffectBox()
	{
	SendMessage(EpicFirstEffectList, LB_RESETCONTENT, 0, 0);

	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int ItemEffectSize;
	int EpicEffectColorsSize;
	int EpicEffectColor;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(EpicFirstEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
		for (int i=0; i<ItemEffectSize; i++)
			{
			ptItemEffect = Data.GetItemEffectPointer(i);
			if (ptItemEffect->DoesTypeMatch(EPICEFFECT))
				{
				EpicEffectColorsSize = ptItemEffect->GetEpicEffectColorsSize();
				for (int j=0; j<EpicEffectColorsSize; j++)
					{
					EpicEffectColor = ptItemEffect->GetEpicEffectColor(j);
					if (ptItem->DoesEpicItemSlotOneColorMatch(EpicEffectColor))
						SendMessage(EpicFirstEffectList, LB_ADDSTRING, 0, i);
					}
				}
			}
		}

	}

//----------------------------------------------------------------------------
void ItemBuilderClass::FillEpicSecondEffectBox()
	{
	SendMessage(EpicSecondEffectList, LB_RESETCONTENT, 0, 0);

	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int ItemEffectSize;
	int EpicSlotColorsSize;
	int EpicSlotColor;

	ItemEffectSize = Data.GetItemEffectSize();
	if (BaseTypeCurrentlySelected == -1)
		SendMessage(EpicSecondEffectList, LB_ADDSTRING, 0, 0);
	else
		{
		ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
			for (int i=0; i<ItemEffectSize; i++)
				{
				ptItemEffect = Data.GetItemEffectPointer(i);
				if (ptItemEffect->DoesTypeMatch(EPICEFFECT))
					{
					EpicSlotColorsSize = ptItemEffect->GetEpicEffectColorsSize();
					for (int j=0; j<EpicSlotColorsSize; j++)
						{
						EpicSlotColor = ptItemEffect->GetEpicEffectColor(j);
						if (ptItem->DoesEpicItemSlotTwoColorMatch(EpicSlotColor))
							SendMessage(EpicSecondEffectList, LB_ADDSTRING, 0, i);
						}
					}
				}
		}

	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawBonusEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (BonusEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawPrefixEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (PrefixEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawMaterialEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (MaterialEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}
	
//----------------------------------------------------------------------------
void ItemBuilderClass::DrawSuffixEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (SuffixEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawEldritchEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (EldritchEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawGSInvasionElementBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (GSInvasionElementCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawGSInvasionEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (GSInvasionEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawGSSubjugationElementBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (GSSubjugationElementCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawGSSubjugationEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (GSSubjugationEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawGSDevastationElementBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (GSDevastationElementCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawGSDevastationEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (GSDevastationEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawDTEldritchEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (DTEldritchEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawDTTempestEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (DTTempestEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawDTSovereignEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (DTSovereignEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawShavarathElementBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (ShavarathElementCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawShavarathEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (ShavarathEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawEpicFirstEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (EpicFirstEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//----------------------------------------------------------------------------
void ItemBuilderClass::DrawEpicSecondEffectBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;

	if (EpicSecondEffectCurrentlySelected == Item)
		OriginalColor = SetTextColor (hDC, RGB(230,230,0));
	else 
		OriginalColor = SetTextColor (hDC, RGB(255,255,255));

	Text = GetEffectName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor (hDC, OriginalColor);
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::DrawBaseTypesBoxItem(HDC hDC, DWORD Item, long top, long left)
	{
	string Text;
	ostringstream Charges;
	COLORREF OriginalColor;
	
	if (BaseTypeCurrentlySelected == Item)
		OriginalColor = SetTextColor(hDC, RGB(230,230,0));
	else
		OriginalColor = SetTextColor(hDC, RGB(255,255,255));

	Text = GetItemName(Item);
	TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
	SetTextColor(hDC, OriginalColor);
	}

//---------------------------------------------------------------------------
void ItemBuilderClass::DrawCurrentItemsBoxItem(HDC hDC, DWORD Item, long top, long left)
    {
    string Text;
    ostringstream Charges;
    COLORREF OriginalColor;
	if (ItemCurrentlySelected == Item)
		OriginalColor = SetTextColor(hDC, RGB(230,230,0));
	else
		OriginalColor = SetTextColor(hDC, RGB(255,255,255));

    Text = GetItemDisplayName(Item);
    //we have to strip out the control codes, since they're meant for the description box, and don't work in the selection boxes!
    //if (Text.find("{\\b ") != string::npos)
    //    Text.replace(Text.find("{\\b "), 4, "");
    //if (Text.find("} ") != string::npos)
    //    Text.replace(Text.find("} "), 2, "");

    TextOut(hDC, left+10, top+6, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }
    
//---------------------------------------------------------------------------------------
bool ItemBuilderClass::DoesItemFitSelectedSlot(unsigned int Item)
	{
	ItemClass *ptItem;

	ptItem = Data.GetItemPointer(Item);
	if (ptItem->DoesItemFitSelectedSlot(CharacterDollPanelCurrentSelectedSlot))
		return true;
	else
		return false;
	}
	
//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetItemName(unsigned int Item)
	{
	string strName;
	ItemClass *ptItem;
	
	//ptItem = Data.GetItemPointer(CurrentItems[Item].ItemIndex);
	ptItem = Data.GetItemPointer(Item);
	strName = ptItem->GetItemName();
	return strName;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetItemStaticEffectsDescription(int ItemIndex)
	{
	string strStaticEffectDescriptions;
	ItemClass *ptItem;
	unsigned int StaticEffectIndex;
	int Index;
    int Result;

	ptItem = Data.GetItemPointer(ItemIndex);
    Index = 0;
	strStaticEffectDescriptions = "";

	Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
    while (Result == 0)
        {
		if (strStaticEffectDescriptions == "")
			{
			strStaticEffectDescriptions = "{\\b {\\cf1";
			strStaticEffectDescriptions += GetEffectName(StaticEffectIndex);
			strStaticEffectDescriptions += "}}: ";
			}
		else
			{
			strStaticEffectDescriptions += " \\par {\\b {\\cf1";
			strStaticEffectDescriptions += GetEffectName(StaticEffectIndex);
			strStaticEffectDescriptions += "}}: ";
			}
		strStaticEffectDescriptions += GetEffectDescription(StaticEffectIndex);

        Index++;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
        }
	return strStaticEffectDescriptions;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetItemChosenEffectsDescription(int CurrentItem)
	{
	string strChosenEffectDescriptions;
	
	strChosenEffectDescriptions = "";
/*	for (unsigned int i=0; i<CurrentItems[CurrentItem].ItemEffects.size(); i++)
		{
		if (CurrentItems[CurrentItem].ItemEffects[i] != 0)
			{
			strChosenEffectDescriptions = "{\\b {\\cf1";
			strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffects[i]);
			strChosenEffectDescriptions += "}}: ";
			strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffects[i]);
			strChosenEffectDescriptions += " \\par ";
			}
		}*/
	if (CurrentItems[CurrentItem].ItemEffect1 != 0)
		{
		strChosenEffectDescriptions = "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffect1);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffect1);
		strChosenEffectDescriptions += " \\par ";
		}
	if (CurrentItems[CurrentItem].ItemEffect2 != 0)
		{
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffect2);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffect2);
		strChosenEffectDescriptions += " \\par ";
		}
	if (CurrentItems[CurrentItem].ItemEffect3 != 0)
		{
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffect3);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffect3);
		strChosenEffectDescriptions += " \\par ";
		}
	if (CurrentItems[CurrentItem].ItemEffect4 != 0)
		{
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffect4);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffect4);
		strChosenEffectDescriptions += " \\par ";
		}
	if (CurrentItems[CurrentItem].ItemEffect5 != 0)
		{
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffect5);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffect5);
		strChosenEffectDescriptions += " \\par ";
		}
	if (CurrentItems[CurrentItem].ItemEffect6 != 0)
		{
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].ItemEffect6);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].ItemEffect6);
		strChosenEffectDescriptions += " \\par ";
		}
	if (CurrentItems[CurrentItem].Eldritch != 0)
		{
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += GetEffectName(CurrentItems[CurrentItem].Eldritch);
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += GetEffectDescription(CurrentItems[CurrentItem].Eldritch);
		strChosenEffectDescriptions += " \\par ";
		}
	return strChosenEffectDescriptions;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetItemFlavorText(int ItemIndex)
	{
	string strFlavorText;
	ItemClass *ptItem;

	ptItem = Data.GetItemPointer(ItemIndex);
	strFlavorText = ptItem->GetItemFlavorText();
	return strFlavorText;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetEffectName(unsigned int Item)
	{
	string strName;
	ItemEffectClass *ptItemEffect;

	ptItemEffect = Data.GetItemEffectPointer(Item);
	strName = ptItemEffect->GetItemEffectName();
	return strName;
	}

//--------------------------------------------------------------------------------------
string ItemBuilderClass::GetBuildEffectNameAndDescription(int EffectIndex)
	{
	string strNameAndDescription;
	
	strNameAndDescription = "{\\b {\\cf1";
	strNameAndDescription += GetEffectName(EffectIndex);
	strNameAndDescription += "}}: ";
	strNameAndDescription += GetEffectDescription(EffectIndex);
	strNameAndDescription += "\\par";
	return strNameAndDescription;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetEffectDescription(unsigned int EffectIndex)
	{
	string strDescription;
	ItemEffectClass *ptItemEffect;

	ptItemEffect = Data.GetItemEffectPointer(EffectIndex);
	strDescription = ptItemEffect->GetItemEffectDescription();
	return strDescription;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetItemDisplayName(unsigned int Item)
	{
	int BuildType;
	string strDisplayName;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;

	ptItem = Data.GetItemPointer(CurrentItems[Item].ItemIndex);
	BuildType = ptItem->GetItemBase();
	
	switch (BuildType)
		{
		case GENERIC:
			{
			if (CurrentItems[Item].ItemEffect1 != 0)
				{
				// add Bonus Name to the Item Display Name
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect1);
				strDisplayName = ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			if (CurrentItems[Item].ItemEffect2 != 0)
				{
				// add Effect Prefix Name
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect2);
				strDisplayName += ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			if (CurrentItems[Item].ItemEffect3 != 0)
				{
				// add material Name
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect3);
				strDisplayName += ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			strDisplayName = strDisplayName + ptItem->GetItemName();
			if (CurrentItems[Item].ItemEffect4 !=0)
				{
				//add Effect Suffix Name
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect4);
				strDisplayName +=  " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			break;
			}
		case DRAGONTOUCHED:
		case EPIC:
		case NAMED:
		case SHAVARATHRING:
			{
			strDisplayName = ptItem->GetItemName();
			break;
			}
		case GREENSTEEL:
			{
			strDisplayName = ptItem->GetItemName();
			if (CurrentItems[Item].ItemEffect1 != 0 && CurrentItems[Item].ItemEffect4 == 0 && CurrentItems[Item].ItemEffect6 == 0)//Need to figure out in-game naming conventions for single tiered GS here
				{
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect1);
				strDisplayName += " with " + ptItemEffect->GetItemEffectDisplayName(); // because it might not include the words "Affinity of"
				}
			else if (CurrentItems[Item].ItemEffect4 != 0 && CurrentItems[Item].ItemEffect6 == 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect3);
				strDisplayName.insert(0, "Great Commander ");
				strDisplayName += " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			else if (CurrentItems[Item].ItemEffect6 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CurrentItems[Item].ItemEffect5);
				strDisplayName.insert(0, "Supreme Tyrant ");
				strDisplayName += " of " + ptItemEffect->GetItemEffectName();
				}
			break;
			}
		}
	return strDisplayName;
	}

//---------------------------------------------------------------------------------------
string ItemBuilderClass::GetBuildDisplayName()
	{	
	int BuildType;
	string strBuildDisplayName;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;

	ptItem = Data.GetItemPointer(BaseTypeCurrentlySelected);
	BuildType = ptItem->GetItemBase();
	
	switch (BuildType)
		{
		case GENERIC:
			{
			if (BonusEffectCurrentlySelected != 0)
				{
				// add Bonus Name to the Item Display Name
				ptItemEffect = Data.GetItemEffectPointer(BonusEffectCurrentlySelected);
				strBuildDisplayName = ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			if (PrefixEffectCurrentlySelected != 0)
				{
				// add Effect Prefix Name
				ptItemEffect = Data.GetItemEffectPointer(PrefixEffectCurrentlySelected);
				strBuildDisplayName += ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			if (MaterialEffectCurrentlySelected != 0)
				{
				// add material Name
				ptItemEffect = Data.GetItemEffectPointer(MaterialEffectCurrentlySelected);
				strBuildDisplayName += ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			strBuildDisplayName = strBuildDisplayName + ptItem->GetItemName();
			if (SuffixEffectCurrentlySelected !=0)
				{
				//add Effect Suffix Name
				ptItemEffect = Data.GetItemEffectPointer(SuffixEffectCurrentlySelected);
				strBuildDisplayName +=  " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			break;
			}
		case DRAGONTOUCHED:
		case EPIC:
		case NAMED:
		case SHAVARATHRING:
			{
			strBuildDisplayName = ptItem->GetItemName();
			break;
			}
		case GREENSTEEL:
			{
			strBuildDisplayName = ptItem->GetItemName();
			if (GSInvasionEffectCurrentlySelected != 0 && GSSubjugationEffectCurrentlySelected == 0 && GSDevastationEffectCurrentlySelected == 0)	//Need to figure out in-game naming conventions for single tiered GS here
				{
				ptItemEffect = Data.GetItemEffectPointer(GSInvasionElementCurrentlySelected);
				strBuildDisplayName += " with " + ptItemEffect->GetItemEffectDisplayName(); // it might not include the words "Affinity of"
				}
			else if (GSSubjugationEffectCurrentlySelected != 0 && GSDevastationEffectCurrentlySelected == 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(GSSubjugationElementCurrentlySelected);
				strBuildDisplayName.insert(0, "Great Commander ");
				strBuildDisplayName += " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			else if (GSDevastationEffectCurrentlySelected != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(GSDevastationElementCurrentlySelected);
				strBuildDisplayName.insert(0, "Supreme Tyrant ");
				strBuildDisplayName += " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			break;
			}
		}
	return strBuildDisplayName;
	}
//---------------------------------------------------------------------------------------
void ItemBuilderClass::ChangeItemCurrentlySelected(unsigned int NewItem)
	{
	string strDescription;

	ItemCurrentlySelected = NewItem;
	RedrawWindow(CurrentItemsList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Current");
	EnableWindow(RemoveButton, true);
	}
	
//---------------------------------------------------------------------------------------
void ItemBuilderClass::ChangeBaseTypeCurrentlySelected(unsigned int NewItem)
	{
	BaseTypeCurrentlySelected = NewItem;
	EnableWindow(AddButton, true);
	SetAllEffectVariablesToZero();
	RedrawWindow(BaseTypeList, NULL, NULL, RDW_INVALIDATE);
	FillBonusEffectBox();
	FillPrefixEffectBox();
	FillMaterialEffectBox();
	FillSuffixEffectBox();
	FillEldritchEffectBox();
	FillGSInvasionElementBox();
	FillGSInvasionEffectBox();
	FillGSSubjugationElementBox();
	FillGSSubjugationEffectBox();
	FillGSDevastationElementBox();
	FillGSDevastationEffectBox();
	FillDTEldritchEffectBox();
	FillDTTempestEffectBox();
	FillDTSovereignEffectBox();
	FillShavarathElementBox();
	FillShavarathEffectBox();
	FillEpicFirstEffectBox();
	FillEpicSecondEffectBox();
	FillDescriptionBox("Build");
	}
	
//-------------------------------------------------------------------
void ItemBuilderClass::ChangeBonusEffectCurrentlySelected(unsigned int NewItem)
	{
	BonusEffectCurrentlySelected = NewItem;
	RedrawWindow(BonusEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}
	
//-------------------------------------------------------------------
void ItemBuilderClass::ChangePrefixEffectCurrentlySelected(unsigned int NewItem)
	{
	PrefixEffectCurrentlySelected = NewItem;
	RedrawWindow(PrefixEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeMaterialEffectCurrentlySelected(unsigned int NewItem)
	{
	MaterialEffectCurrentlySelected = NewItem;
	RedrawWindow(MaterialEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}
	
//-------------------------------------------------------------------
void ItemBuilderClass::ChangeSuffixEffectCurrentlySelected(unsigned int NewItem)
	{
	SuffixEffectCurrentlySelected = NewItem;
	RedrawWindow(SuffixEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeEldritchEffectCurrentlySelected(unsigned int NewItem)
	{
	EldritchEffectCurrentlySelected = NewItem;
	RedrawWindow(EldritchEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeGSInvasionElementCurrentlySelected(unsigned int NewItem)
	{
	GSInvasionElementCurrentlySelected = NewItem;
	RedrawWindow(GSInvasionElementList, NULL, NULL, RDW_INVALIDATE);
	GSInvasionEffectCurrentlySelected = 0;
	GSSubjugationElementCurrentlySelected = 0;
	GSSubjugationEffectCurrentlySelected = 0;
	GSDevastationElementCurrentlySelected = 0;
	GSDevastationEffectCurrentlySelected = 0;
	FillGSInvasionEffectBox();
	FillGSSubjugationElementBox();
	FillGSSubjugationEffectBox();
	FillGSDevastationElementBox();
	FillGSDevastationEffectBox();
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeGSInvasionEffectCurrentlySelected(unsigned int NewItem)
	{
	GSInvasionEffectCurrentlySelected = NewItem;
	RedrawWindow(GSInvasionEffectList, NULL, NULL, RDW_INVALIDATE);
	GSSubjugationElementCurrentlySelected = 0;
	GSSubjugationEffectCurrentlySelected = 0;
	GSDevastationElementCurrentlySelected = 0;
	GSDevastationEffectCurrentlySelected = 0;
	FillGSSubjugationElementBox();
	FillGSSubjugationEffectBox();
	FillGSDevastationElementBox();
	FillGSDevastationEffectBox();
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeGSSubjugationElementCurrentlySelected(unsigned int NewItem)
	{
	GSSubjugationElementCurrentlySelected = NewItem;
	RedrawWindow(GSSubjugationElementList, NULL, NULL, RDW_INVALIDATE);
	GSSubjugationEffectCurrentlySelected = 0;
	GSDevastationElementCurrentlySelected = 0;
	GSDevastationEffectCurrentlySelected = 0;
	FillGSSubjugationEffectBox();
	FillGSDevastationElementBox();
	FillGSDevastationEffectBox();
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeGSSubjugationEffectCurrentlySelected(unsigned int NewItem)
	{
	GSSubjugationEffectCurrentlySelected = NewItem;
	RedrawWindow(GSSubjugationEffectList, NULL, NULL, RDW_INVALIDATE);
	GSDevastationElementCurrentlySelected = 0;
	GSDevastationEffectCurrentlySelected = 0;
	FillGSDevastationElementBox();
	FillGSDevastationEffectBox();
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeGSDevastationElementCurrentlySelected(unsigned int NewItem)
	{
	GSDevastationElementCurrentlySelected = NewItem;
	RedrawWindow(GSDevastationElementList, NULL, NULL, RDW_INVALIDATE);
	GSDevastationEffectCurrentlySelected = 0;
	FillGSDevastationEffectBox();
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeGSDevastationEffectCurrentlySelected(unsigned int NewItem)
	{
	GSDevastationEffectCurrentlySelected = NewItem;
	RedrawWindow(GSDevastationEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeDTEldritchEffectCurrentlySelected(unsigned int NewItem)
	{
	DTEldritchEffectCurrentlySelected = NewItem;
	RedrawWindow(DTEldritchEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeDTTempestEffectCurrentlySelected(unsigned int NewItem)
	{
	DTTempestEffectCurrentlySelected = NewItem;
	RedrawWindow(DTTempestEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeDTSovereignEffectCurrentlySelected(unsigned int NewItem)
	{
	DTSovereignEffectCurrentlySelected = NewItem;
	RedrawWindow(DTSovereignEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeShavarathElementCurrentlySelected(unsigned int NewItem)
	{
	ShavarathElementCurrentlySelected = NewItem;
	ShavarathEffectCurrentlySelected = 0;
	RedrawWindow(ShavarathElementList, NULL, NULL, RDW_INVALIDATE);
	FillShavarathEffectBox();
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeShavarathEffectCurrentlySelected(unsigned int NewItem)
	{
	ShavarathEffectCurrentlySelected = NewItem;
	RedrawWindow(ShavarathEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeEpicFirstEffectCurrentlySelected(unsigned int NewItem)
	{
	EpicFirstEffectCurrentlySelected = NewItem;
	RedrawWindow(EpicFirstEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::ChangeEpicSecondEffectCurrentlySelected(unsigned int NewItem)
	{
	EpicSecondEffectCurrentlySelected = NewItem;
	RedrawWindow(EpicSecondEffectList, NULL, NULL, RDW_INVALIDATE);
	FillDescriptionBox("Build");
	}

//-------------------------------------------------------------------
void ItemBuilderClass::FillDescriptionBox(string DescriptionBox)
    {
    EDITSTREAM Stream;
	string strDescription;
	
	if (DescriptionBox == "Current")
		{
		if (ItemCurrentlySelected == -1)
			{
			strDescription = "{\\b {\\cf2 No Item Currently Selected}}";
			strDescription += " \\par\\par ";
			strDescription += "Select an item to the left to view its properties";
			}
		else
			{
			strDescription = "{\\b {\\cf2";
			strDescription += GetItemDisplayName(ItemCurrentlySelected);
			strDescription += " \\par\\par }}";
			strDescription += GetItemStaticEffectsDescription(CurrentItems[ItemCurrentlySelected].ItemIndex);
			strDescription += " \\par ";
			strDescription += GetItemChosenEffectsDescription(ItemCurrentlySelected);
			strDescription += " \\par {\\cf5";
			strDescription += GetItemFlavorText(CurrentItems[ItemCurrentlySelected].ItemIndex);
			strDescription += "}";
			}
		}
	else // - this is the build description box
		{
		if (BaseTypeCurrentlySelected == -1)
			{
			strDescription = "{\\b {\\cf2 No Item Currently Being Built}}";
			}
		else
			{
			strDescription = "{\\b {\\cf2";
			strDescription += GetBuildDisplayName();
			strDescription += "\\par\\par }}";
			strDescription += GetItemStaticEffectsDescription(BaseTypeCurrentlySelected);
			strDescription += "\\par";
			if (BonusEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(BonusEffectCurrentlySelected);
			if (PrefixEffectCurrentlySelected !=0)
				strDescription += GetBuildEffectNameAndDescription(PrefixEffectCurrentlySelected);
			if (MaterialEffectCurrentlySelected !=0)
				strDescription += GetBuildEffectNameAndDescription(MaterialEffectCurrentlySelected);
			if (SuffixEffectCurrentlySelected !=0)
				strDescription += GetBuildEffectNameAndDescription(SuffixEffectCurrentlySelected);
			if (EldritchEffectCurrentlySelected !=0)
				strDescription += GetBuildEffectNameAndDescription(EldritchEffectCurrentlySelected);
			if (GSInvasionElementCurrentlySelected != 0)
				strDescription += " \\par " + GetBuildEffectNameAndDescription(GSInvasionElementCurrentlySelected);
			if (GSInvasionEffectCurrentlySelected != 0)
				strDescription += GetEffectDescription(GSInvasionEffectCurrentlySelected) + " \\par ";
			if (GSSubjugationElementCurrentlySelected != 0)
				strDescription += " \\par " + GetBuildEffectNameAndDescription(GSSubjugationElementCurrentlySelected);
			if (GSSubjugationEffectCurrentlySelected != 0)
				strDescription += GetEffectDescription(GSSubjugationEffectCurrentlySelected) + " \\par ";
			if (GSDevastationElementCurrentlySelected != 0)
				strDescription += " \\par " + GetBuildEffectNameAndDescription(GSDevastationElementCurrentlySelected);
			if (GSDevastationEffectCurrentlySelected != 0)
				strDescription += GetEffectDescription(GSDevastationEffectCurrentlySelected) + " \\par ";
			if (DTEldritchEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(DTEldritchEffectCurrentlySelected);
			if (DTTempestEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(DTTempestEffectCurrentlySelected);
			if (DTSovereignEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(DTSovereignEffectCurrentlySelected);
			if (ShavarathElementCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(ShavarathElementCurrentlySelected);
			if (ShavarathEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(ShavarathEffectCurrentlySelected);
			if (EpicFirstEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(EpicFirstEffectCurrentlySelected);
			if (EpicSecondEffectCurrentlySelected != 0)
				strDescription += GetBuildEffectNameAndDescription(EpicSecondEffectCurrentlySelected);
			}
		}

    Stream.dwCookie = (DWORD)strDescription.c_str();
    Stream.dwError = false;
    Stream.pfnCallback = EditStreamCallback;
	if (DescriptionBox == "Current")
		SendMessage(CurrentDescriptionWindow, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);
	else 
		SendMessage(BuildDescriptionWindow, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);
    }

//------------------------------------------------------------------------
string ItemBuilderClass::GetFullItemDescription(int CurrentItem)
	{
	return "Testing";
	}

//--------------------------------------------------------------------------
void ItemBuilderClass::SetAllEffectVariablesToZero()
	{
	BonusEffectCurrentlySelected = 0;
	MaterialEffectCurrentlySelected = 0;
	PrefixEffectCurrentlySelected = 0;
	SuffixEffectCurrentlySelected = 0;
	EldritchEffectCurrentlySelected = 0;
	GSInvasionElementCurrentlySelected = 0;
	GSInvasionEffectCurrentlySelected = 0;
	GSSubjugationElementCurrentlySelected = 0;
	GSSubjugationEffectCurrentlySelected = 0;
	GSDevastationElementCurrentlySelected = 0;
	GSDevastationEffectCurrentlySelected = 0;
	DTEldritchEffectCurrentlySelected = 0;
	DTTempestEffectCurrentlySelected = 0;
	DTSovereignEffectCurrentlySelected = 0;
	ShavarathElementCurrentlySelected = 0;
	ShavarathEffectCurrentlySelected = 0;
	EpicFirstEffectCurrentlySelected = 0;
	EpicSecondEffectCurrentlySelected = 0;
	}

//--------------------------------------------------------------------
void ItemBuilderClass::SendCurrentItemsData()
	{
	Character.ClearCharacterItems();
	for (unsigned int i=0; i<CurrentItems.size(); i++)
		Character.AddItemToCharacterItems(CurrentItems[i].ItemIndex, CurrentItems[i].ItemEffect1, CurrentItems[i].ItemEffect2, CurrentItems[i].ItemEffect3, CurrentItems[i].ItemEffect4, CurrentItems[i].ItemEffect5, CurrentItems[i].ItemEffect6, CurrentItems[i].Eldritch);
	}

//--------------------------------------------------------------------
void ItemBuilderClass::AddBuildItem()
	{
    int ItemCount;
	CharacterItemStruct NewItem;

	NewItem.ItemIndex = BaseTypeCurrentlySelected;
	NewItem.ItemEffect1 = 0;
	NewItem.ItemEffect2 = 0;
	NewItem.ItemEffect3 = 0;
	NewItem.ItemEffect4 = 0;
	NewItem.ItemEffect5 = 0;
	NewItem.ItemEffect6 = 0;
	NewItem.Eldritch = EldritchEffectCurrentlySelected;
	if (SendMessage(GenericSelectBox, BM_GETCHECK, 0, 0) ==  BST_CHECKED)
		{
		NewItem.ItemEffect1 = BonusEffectCurrentlySelected;
		NewItem.ItemEffect2 = PrefixEffectCurrentlySelected;
		NewItem.ItemEffect3 = MaterialEffectCurrentlySelected;
		NewItem.ItemEffect4 = SuffixEffectCurrentlySelected;
		NewItem.ItemEffect5 = 0;
		NewItem.ItemEffect6 = 0;
		}
	if (SendMessage(GreenSteelSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		if (GSInvasionElementCurrentlySelected != 0)
			NewItem.ItemEffect1 = GSInvasionElementCurrentlySelected;
		else
			NewItem.ItemEffect1 = 0;
		if (GSInvasionEffectCurrentlySelected != 0)
			NewItem.ItemEffect2 = GSInvasionEffectCurrentlySelected;
		else
			NewItem.ItemEffect2 = 0;
		if (GSSubjugationElementCurrentlySelected != 0)
			NewItem.ItemEffect3 = GSSubjugationElementCurrentlySelected;
		else
			NewItem.ItemEffect3 =0;
		if (GSSubjugationEffectCurrentlySelected != 0)
			NewItem.ItemEffect4 = GSSubjugationEffectCurrentlySelected;
		else
			NewItem.ItemEffect4 =0;
		if (GSDevastationElementCurrentlySelected != 0)
			NewItem.ItemEffect5 = GSDevastationElementCurrentlySelected;
		else
			NewItem.ItemEffect5 =0;
		if (GSDevastationEffectCurrentlySelected != 0)
			NewItem.ItemEffect6 = GSDevastationEffectCurrentlySelected;
		else
			NewItem.ItemEffect6 =0;
		}
	if (SendMessage(DragontouchedSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		NewItem.ItemEffect1 = DTEldritchEffectCurrentlySelected;
		NewItem.ItemEffect2 = DTTempestEffectCurrentlySelected;
		NewItem.ItemEffect3 = DTSovereignEffectCurrentlySelected;
		NewItem.ItemEffect4 = 0;
		NewItem.ItemEffect5 = 0;
		NewItem.ItemEffect6 = 0;
		}
	if (SendMessage(ShavarathRingSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		NewItem.ItemEffect1 = ShavarathElementCurrentlySelected;
		NewItem.ItemEffect2 = ShavarathEffectCurrentlySelected;
		NewItem.ItemEffect3 = 0;
		NewItem.ItemEffect4 = 0;
		NewItem.ItemEffect5 = 0;
		NewItem.ItemEffect6 = 0;
		}
	if (SendMessage(EpicSelectBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
		NewItem.ItemEffect1 = EpicFirstEffectCurrentlySelected;
		NewItem.ItemEffect2 = EpicSecondEffectCurrentlySelected;
		NewItem.ItemEffect3 = 0;
		NewItem.ItemEffect4 = 0;
		NewItem.ItemEffect5 = 0;
		NewItem.ItemEffect6 = 0;
		}
	
	CurrentItems.push_back(NewItem);
	ItemCount = CurrentItems.size()-1;
	FillCurrentItemsBox();
	}

//-------------------------------------------------------------------
void ItemBuilderClass::RemoveCurrentItem()
	{
	CurrentItems.erase(CurrentItems.begin() + ItemCurrentlySelected);
	ItemCurrentlySelected = -1;
	FillCurrentItemsBox();
	FillDescriptionBox("Current");
	EnableWindow(RemoveButton, false);
	}