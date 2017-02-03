#include "Screen_Destiny_Class.h"
#include "InterfaceManagerClass.h"
#include "ToolTipWindowClass.h"
#include "Character_Destinies_Class.h"
#include "CharacterClass.h"

//--------------------------------------------------------------------------
Screen_Destiny_Class::Screen_Destiny_Class()
	{
	int SlotWidth = 43;
	int SlotHeight = 53;
	int SlotTop[7] = {505, 437, 367, 297, 227, 157, 87};
	int SlotTier0Left[6] = {260, 308, 356, 404, 452, 501};
	int SlotLeft[6] = {257, 317, 377, 437, 498, 498};
	int IconWidth = 36;
	int IconHeight = 36;
	int IconTop[7] = {505, 441, 371, 301, 231, 161, 91};
	int IconTier0Left[6] = {261, 309, 357, 405, 453, 502};
	int IconLeft[6] = {261, 321, 381, 441, 502, 502};
	int CoreBorderWidth = 38;
	int CoreBorderHeight = 38;
	int CoreBorderLeft[6] = {260, 308, 356, 404, 452, 501};
	int CoreBorderTop = 505;

	//Lets set our coordinates for placing our graphics and handling mouse clicks.

	//Destiny Header Location
	DestinyHeaderLocation.Left = 256;
	DestinyHeaderLocation.Top = 5;
	DestinyHeaderLocation.Width = 288;
	DestinyHeaderLocation.Height = 57;

	//Destiny Header xp bar
	DestinyHeaderXPLocation.Left = 312;
	DestinyHeaderXPLocation.Top = 37;
	DestinyHeaderXPLocation.Width = 160;
	DestinyHeaderXPLocation.Height = 12;

	//Destiny Header Rank Button 1
	DestinyHeaderRank1Location.Left = 478;
	DestinyHeaderRank1Location.Top = 37;
	DestinyHeaderRank1Location.Width = 12;
	DestinyHeaderRank1Location.Height = 12;

	//Destiny Header Rank Button 2
	DestinyHeaderRank2Location.Left = 494;
	DestinyHeaderRank2Location.Top = 37;
	DestinyHeaderRank2Location.Width = 12;
	DestinyHeaderRank2Location.Height = 12;

	//Destiny Header Rank Button 1
	DestinyHeaderRank3Location.Left = 509;
	DestinyHeaderRank3Location.Top = 37;
	DestinyHeaderRank3Location.Width = 12;
	DestinyHeaderRank3Location.Height = 12;

	//Destiny Header Rank Button 1
	DestinyHeaderRank4Location.Left = 524;
	DestinyHeaderRank4Location.Top = 37;
	DestinyHeaderRank4Location.Width = 12;
	DestinyHeaderRank4Location.Height = 12;

	//Claim Destiny Button
	ClaimDestinyLocation.Left = 405;
	ClaimDestinyLocation.Top = 53;
	ClaimDestinyLocation.Width = 141;
	ClaimDestinyLocation.Height = 22;

	//MakeActive Button
	MakeActiveLocation.Left = 461;
	MakeActiveLocation.Top = 53;
	MakeActiveLocation.Width = 95;
	MakeActiveLocation.Height = 22;

	//Header Rect Info
	rectHeader.left = 256;
	rectHeader.right = 544;
	rectHeader.top = 5;
	rectHeader.bottom = 80;

	//Background Location
	DestinyBackground.Left = 250;
	DestinyBackground.Top = 78;
	DestinyBackground.Width = 300;
	DestinyBackground.Height = 526;

	//CoreDestinyFrame
	DestinyCoreFrame.Left = 254;
	DestinyCoreFrame.Top = 500;
	DestinyCoreFrame.Width = 291;
	DestinyCoreFrame.Height = 54;

	//Footer Rect Info
	rectFooter.left = 250;
	rectFooter.right = 550;
	rectFooter.top = 600;
	rectFooter.bottom = 655;

	//Level Selector Graphics
	LevelSelectorLeft.Left = 250;
	LevelSelectorLeft.Top = 630;
	LevelSelectorLeft.Width = 23;
	LevelSelectorLeft.Height = 21;

	LevelSelectorRight.Left = 365;
	LevelSelectorRight.Top = 630;
	LevelSelectorRight.Width = 23;
	LevelSelectorRight.Height = 21;

	//Slot, Border & Icon Locations
	for (int x=0; x<7; x++)
		{
		for (int y=0; y<6; y++)
			{
			if (x==0)
				{
				SlotLocation[x][y].Left = SlotTier0Left[y];
				IconLocation[x][y].Left = IconTier0Left[y];
				CoreBorderLocation[y].Left = CoreBorderLeft[y];
				CoreBorderLocation[y].Top = CoreBorderTop;
				CoreBorderLocation[y].Width = CoreBorderWidth;
				CoreBorderLocation[y].Height = CoreBorderHeight;
				}
			else
				{
				SlotLocation[x][y].Left = SlotLeft[y];
				IconLocation[x][y].Left = IconLeft[y];
				}
			SlotLocation[x][y].Top = SlotTop[x];
			SlotLocation[x][y].Width = SlotWidth;
			SlotLocation[x][y].Height = SlotHeight;
			IconLocation[x][y].Top = IconTop[x];
			IconLocation[x][y].Width = IconWidth;
			IconLocation[x][y].Height = IconHeight;
			}
		}

	//button graphic locations
	ResetTreeLocation.Left = 466;
	ResetTreeLocation.Top = 575;
	ResetTreeLocation.Width = 79;
	ResetTreeLocation.Height = 24;

	//Lets set our DestinyTreeRanks Structure
	for (int x=0; x<30; x++)
		{
		if (x == 0)
			{
			DestinyTreeRanks[x].DestinyLevel = 0;
			DestinyTreeRanks[x].DestinyRank = 1;
			DestinyTreeRanks[x].RankXP = 36000;
			DestinyTreeRanks[x].TotalAP = 0;
			}
		if (x > 0 && x < 5)
			{
			DestinyTreeRanks[x].DestinyLevel = 0;
			DestinyTreeRanks[x].DestinyRank = x+1;
			DestinyTreeRanks[x].RankXP = 36000;
			DestinyTreeRanks[x].TotalAP = x;
			}
		else if (x > 4 && x < 10)
			{
			DestinyTreeRanks[x].DestinyLevel = 1;
			DestinyTreeRanks[x].DestinyRank = x;
			DestinyTreeRanks[x].RankXP = 48000;
			DestinyTreeRanks[x].TotalAP = x-1;
			}
		else if (x > 9 && x < 15)
			{
			DestinyTreeRanks[x].DestinyLevel = 2;
			DestinyTreeRanks[x].DestinyRank = x-1;
			DestinyTreeRanks[x].RankXP = 60000;
			DestinyTreeRanks[x].TotalAP = x-2;
			}
		else if (x > 14 && x < 20)
			{
			DestinyTreeRanks[x].DestinyLevel = 3;
			DestinyTreeRanks[x].DestinyRank = (x-2);
			DestinyTreeRanks[x].RankXP = 72000;
			DestinyTreeRanks[x].TotalAP = x-3;
			}
		else if (x > 19 && x < 25)
			{
			DestinyTreeRanks[x].DestinyLevel = 4;
			DestinyTreeRanks[x].DestinyRank = (x-3);
			DestinyTreeRanks[x].RankXP = 84000;
			DestinyTreeRanks[x].TotalAP = x-4;
			}
		else if (x >=25 && x <=29)
			{
			DestinyTreeRanks[x].DestinyLevel = 5;
			DestinyTreeRanks[x].DestinyRank = (x-4);
			DestinyTreeRanks[x].RankXP = 96000;
			DestinyTreeRanks[x].TotalAP = x-5;
			}
		}
	}

//--------------------------------------------------------------------------
Screen_Destiny_Class::~Screen_Destiny_Class()
	{
	DeleteGraphics();
	DeSubclassChildWindows();
	}

//---------------------------------------------------------------------------
void Screen_Destiny_Class::ActivateDestiny()
	{
	//TODO: Code to activate Destiny
	}

//---------------------------------------------------------------------------
void Screen_Destiny_Class::ActivateDestinyWindow(int Level)
	{
	HDC ParentDC;
	Character_Destinies_Class *CharacterDestinies;
	ToolTipWindowClass *ToolTipWindow;
	vector <CLASS> ClassProgression;

	ClaimDestinyWindowVisible = false;

	ParentDC = GetDC(DestinyWindowHandle);
	if (ParentDC == nullptr)
		DEBUG("GetDC Fail");

	CharacterDestinies = Character.GetCharacterDestiniesPointer();
	if (CharacterDestinies == nullptr)
		DEBUG("GetCharacterDestiniesPointer Fail");

	//let set our variables
	CharacterLevel = Level;

	if (CharacterDestinies->GetCurrentActiveDestiny() == DT_NONE)
		ScreenTree = DT_DRACONIC_INCARNATION;
	else
		ScreenTree = CharacterDestinies->GetCurrentActiveDestiny();
	SelectedDestiny = ScreenTree;

	for (int x=0; x<20; x++)
		ClassProgression.push_back(Character.GetClass(x+1, false));
	ClassID[0] = ClassProgression[0];
	ClassLevel[0] = 1;
	ClassLevel[1] = 0;
	ClassLevel[2] = 0;
	for (int y=1; y<20; y++)
		{
		for (int z=0; z<3; z++)
			{
			if (ClassLevel[z] == 0)
				{
				ClassID[z] = ClassProgression[y];
				ClassLevel[z]++;
				break;
				}
			else
				{
				if (ClassID[z] == ClassProgression[y])
					{
					ClassLevel[z]++;
					break;
					}
				}
			}
		}
	//Set the confining window for the Tooltips
	ToolTipWindow = InterfaceManager.GetToolTipWindowPointer();
	ToolTipWindow->SetConfiningWindow(DestinyWindowHandle);

	//Let see if we need to uncheck our Enforcement Checkboxes
	if (CharacterDestinies->GetLevelEnforcement() == false)
		SendMessage(EnforceLevelCheckBoxHandle, BM_SETCHECK, BST_UNCHECKED, 0);
	if (CharacterDestinies->GetProgressEnforcement() == false)
		SendMessage(EnforceDestinyProgressCheckBoxHandle, BM_SETCHECK, BST_UNCHECKED, 0);
	
	
	//Fill our list boxes and DestinyTree
	FillDestiniesList();
	UpdateScreenTree(ScreenTree);
	DrawScreenTree(ParentDC);

	MultiDestinyWindowvisible = false;

	ReleaseDC(DestinyWindowHandle, ParentDC);

	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::ChangeDestinyTreeRanks(bool flagIncrease)
	{
	int SelectedDestinyTreeRank;
	Character_Destinies_Class *CharacterDestinies;
	HDC ParentDC;

	ParentDC = GetDC(DestinyWindowHandle);
	CharacterDestinies = Character.GetCharacterDestiniesPointer();
	SelectedDestinyTreeRank = CharacterDestinies->GetSelectedDestinyLevel(ScreenTree, CharacterLevel);
	
	if (flagIncrease == true)
		{
		SelectedDestinyTreeRank ++;
		DestinyTreeLevel[ScreenTree] ++;
		if (DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel != DestinyTreeRanks[DestinyTreeLevel[ScreenTree]-1].DestinyLevel)
		//if (SelectedDestinyTreeRank % 5 == 0)
			{
			CharacterDestinies->SetRanksTaken(ScreenTree, 0, DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel, 1);
			CharacterDestinies->SetLevelTaken(ScreenTree, 0, DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel, 0, CharacterLevel);
			ScreenTreeSlots[0][DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel].RanksTaken = 1;
			FillDestiniesList();
			}
		else 
			DPAvailbleTree[ScreenTree] ++;
		}
	else
		{
		SelectedDestinyTreeRank --;
		DestinyTreeLevel[ScreenTree] --;
		if (DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel != DestinyTreeRanks[DestinyTreeLevel[ScreenTree]+1].DestinyLevel)
		//if ((SelectedDestinyTreeRank+1) %5 == 0)
			{
			CharacterDestinies->SetRanksTaken(ScreenTree, 0, DestinyTreeRanks[DestinyTreeLevel[ScreenTree]+1].DestinyLevel, 0);
			CharacterDestinies->SetLevelTaken(ScreenTree, 0, DestinyTreeRanks[DestinyTreeLevel[ScreenTree]+1].DestinyLevel, 0, 0);
			ScreenTreeSlots[0][DestinyTreeRanks[DestinyTreeLevel[ScreenTree]+1].DestinyLevel].RanksTaken = 0;
			FillDestiniesList();
			}
		else
			DPAvailbleTree[ScreenTree] --;

		}
		CharacterDestinies->SetSelectedDestinyLevel(ScreenTree, CharacterLevel, SelectedDestinyTreeRank);

		RedrawWindow(DestinyWindowHandle, &rectFooter, NULL, RDW_ERASE | RDW_INVALIDATE);
		UpdateWindow(DestinyWindowHandle);
		DrawScreenTree(ParentDC);

	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::ClaimDestiny()
	{
	ostringstream ss;
	string text;
	Data_Destiny_Tree_Class *DestinyTree;
	Character_Destinies_Class *CharacterDestinies;
	HDC ParentDC;

	ParentDC = GetDC(DestinyWindowHandle);

	DestinyTree = Data.GetDestinyTreePointer(ScreenTree);
	ss.str("");
	ss << "Choose the " << DestinyTree->GetTreeName() << " Epic Destiny?";
	text = ss.str();
	ClaimDestinyWindowVisible = true;
	//if (MessageBox(NULL, text.c_str(), "", MB_YESNO | MB_TOPMOST) == IDYES)
		//{
		CharacterDestinies = Character.GetCharacterDestiniesPointer();
		CharacterDestinies->SetCurrentActiveDestiny((DESTINY_TREE)ScreenTree);
		CharacterDestinies->SetSelectedDestinyLevel(ScreenTree, CharacterLevel, 0);

		//Add rank to first core destiny.
		CharacterDestinies->SetRanksTaken((int)ScreenTree, 0, 0, 1);
		CharacterDestinies->SetLevelTaken(ScreenTree, 0, 0, 0, CharacterLevel);
		ScreenTreeSlots[0][0].RanksTaken = 1;
		
		//Lets redraw the center section
		RedrawWindow(DestinyWindowHandle, &rectHeader, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_INTERNALPAINT);
		UpdateWindow(DestinyWindowHandle);
		DrawScreenTree(ParentDC);
		FillDestiniesList();

		//Enable the Level selectors

		//}
	ClaimDestinyWindowVisible = false;
	ReleaseDC(DestinyWindowHandle, ParentDC);
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::Create(HINSTANCE Instance, HWND Parent)
	{
	WNDCLASSEX wc;
	HWND ParentWindow;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Destinies Window";
	LOGFONT lf;

	//Fill in the class attributes for the Main window
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

	//register the window
	RegisterClassEx(&wc);

	//create and place the window in Center of MainWindow
	int ParentX;
	int ParentY;
	RECT ParentRect;
	int TopBar = 25;
	DestinyWindowHandle = CreateWindowEx (NULL, WindowName, WindowName, WS_POPUP | WS_DLGFRAME, 0, 0, 815, 665, Parent, NULL, Instance, NULL);
	SetClassLong(DestinyWindowHandle, 0, (long)DESTINYWINDOW);
	ParentWindow = InterfaceManager.ControlWindow.GetControlWindowHandle();
	GetWindowRect(ParentWindow, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top - TopBar;
	GetWindowRect(DestinyWindowHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(DestinyWindowHandle, Parent, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2) + TopBar, 0, 0, SWP_NOSIZE);

	//the child windows
	DestiniesLabelHandle = CreateWindowEx(NULL, "STATIC", "Destinies", WS_CHILD, 10, 10, 230, 20, DestinyWindowHandle, (HMENU)DW_DESTINIESLABEL, Instance, NULL);
	DestiniesFrameHandle = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 10, 30, 230, 570, DestinyWindowHandle, (HMENU)DW_DESTINIESFRAME, Instance, NULL);
	DestiniesListHandle = CreateWindowEx(NULL, "LISTBOX", "Destinies List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 11, 31, 228, 565, DestinyWindowHandle, (HMENU)DW_DESTINIESLIST, Instance, NULL);
	EnforceLevelCheckBoxHandle = CreateWindowEx(NULL, "BUTTON", "Enforce Destiny Level/Character Level", WS_CHILD | BS_AUTOCHECKBOX, 10, 610, 200, 20, DestinyWindowHandle, (HMENU)DW_ENFORCELEVELCHECKBOX, Instance, NULL);
	EnforceDestinyProgressCheckBoxHandle = CreateWindowEx(NULL, "BUTTON", "Enforce Destiny Progression", WS_CHILD | BS_AUTOCHECKBOX, 10, 630, 200, 20, DestinyWindowHandle, (HMENU)DW_ENFORCEDESTINYPROGRESSCHECKBOX, Instance, NULL);
	AbilitiesLabelHandle = CreateWindowEx(NULL, "STATIC", "Abilities", WS_CHILD, 560, 10, 240, 20, DestinyWindowHandle, (HMENU)DW_ABILITIESLABEL, Instance, NULL);
	AbilitiesFrameHandle = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 560, 30, 240, 420, DestinyWindowHandle, (HMENU)DW_ABILITIESFRAME, Instance, NULL);
	AbilitiesListHandle = CreateWindowEx(NULL, "LISTBOX", "Abilities List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 561, 31, 238, 418, DestinyWindowHandle, (HMENU)DW_ABILITIESLIST, Instance, NULL);
	ShowAllCheckBoxHandle = CreateWindowEx(NULL, "BUTTON", "Show All", WS_CHILD | BS_AUTOCHECKBOX, 705, 455, 80, 20, DestinyWindowHandle, (HMENU)DW_SHOWALLCHECKBOX, Instance, NULL);
	TwistsofFateLabelHandle = CreateWindowEx(NULL, "STATIC", "Twists of Fate", WS_CHILD, 560, 480, 240, 20, DestinyWindowHandle, (HMENU)DW_TWISTSOFFATELABEL, Instance, NULL);
	TwistsofFateFrameHandle = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 560, 500, 240, 150, DestinyWindowHandle, (HMENU)DW_TWISTSOFFATEFRAME, Instance, NULL);

	CancelButtonHandle = CreateWindowEx(NULL, "BUTTON", "Cancel", WS_CHILD, 480, 630, 60, 20, DestinyWindowHandle, (HMENU)DW_CANCELBUTTON, Instance, NULL);
	AcceptButtonHandle = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD, 400, 630, 60, 20, DestinyWindowHandle, (HMENU)DW_ACCEPTBUTTON, Instance, NULL);

	//Set Item Heights for our ListBoxes
	SendMessage(AbilitiesListHandle, LB_SETITEMHEIGHT, 0, MAKELPARAM(40, 0));
	SendMessage(DestiniesListHandle, LB_SETITEMHEIGHT, 0, MAKELPARAM(48, 0));

	//Set the default states of checkboxes
	SendMessage(EnforceDestinyProgressCheckBoxHandle, BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(EnforceLevelCheckBoxHandle, BM_SETCHECK, BST_CHECKED, 0);

	//Create some fonts to be used
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
	StringCbCopy (lf.lfFaceName, LF_FACESIZE, TEXT("ARIEL"));
	ArielFontSmall = CreateFontIndirect(&lf);

	lf.lfHeight = 18;
	ArielFontNormal = CreateFontIndirect(&lf);

	LoadGraphics(DestinyWindowHandle);
	SubclassChildWindows();
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::DeleteGraphics()
	{
	DeleteObject(CoreSlotBackgroundActive.Graphic);
	DeleteObject(CoreSlotBackgroundActive.Mask);
	DeleteObject(CoreSlotBackgroundPassive.Graphic);
	DeleteObject(CoreSlotBackgroundPassive.Mask);
	DeleteObject(TreeSlotBackgroundActive.Graphic);
	DeleteObject(TreeSlotBackgroundActive.Mask);
	DeleteObject(TreeSlotBackgroundPassive.Graphic);
	DeleteObject(TreeSlotBackgroundPassive.Mask);

	DeleteObject(SlotBorderAvailableActive.Graphic);
	DeleteObject(SlotBorderAvailableActive.Mask);
	DeleteObject(SlotBorderAvailablePassive.Graphic);
	DeleteObject(SlotBorderAvailablePassive.Mask);
	DeleteObject(SlotBorderNotAvailableActive.Graphic);
	DeleteObject(SlotBorderNotAvailableActive.Mask);
	DeleteObject(SlotBorderNotAvailablePassive.Graphic);
	DeleteObject(SlotBorderNotAvailablePassive.Mask);

	DeleteObject(SlotBorderNotAllowedActive.Graphic);
	DeleteObject(SlotBorderNotAllowedActive.Mask);
	DeleteObject(SlotBorderNotAllowedPassive.Graphic);
	DeleteObject(SlotBorderNotAllowedPassive.Mask);

	DeleteObject(ResetTreeOn.Graphic);
	DeleteObject(ResetTreeOn.Mask);
	DeleteObject(ResetTreeOff.Graphic);
	DeleteObject(ResetTreeOff.Mask);

	DeleteObject(LevelArrowLeft.Graphic);
	DeleteObject(LevelArrowLeft.Mask);
	DeleteObject(LevelArrowRight.Graphic);
	DeleteObject(LevelArrowRight.Mask);

	DeleteObject(DestinyIconRingAvailable.Graphic);
	DeleteObject(DestinyIconRingAvailable.Mask);
	DeleteObject(DestinyIconRingNotClaimed.Graphic);
	DeleteObject(DestinyIconRingNotClaimed.Mask);
	DeleteObject(DestinyIconRingSelected.Graphic);
	DeleteObject(DestinyIconRingSelected.Mask);
	DeleteObject(ClaimDestinyOn.Graphic);
	DeleteObject(ClaimDestinyOn.Mask);
	DeleteObject(ClaimDestinyOff.Graphic);
	DeleteObject(ClaimDestinyOff.Mask);
	DeleteObject(MakeActiveButton.Graphic);
	DeleteObject(MakeActiveButton.Mask);
	DeleteObject(LevelCircle.Graphic);
	DeleteObject(LevelCircle.Mask);

	DeleteObject(Palette);
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::DeSubclassChildWindows()
	{
	for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
		SetWindowLongPtr(SubclassHWNDs[i], GWL_WNDPROC, static_cast<__int3264>(reinterpret_cast<LONG_PTR>(OriginalProcs[i])));
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::DrawLevelSelectors(HDC hdc)
	{
	DrawGraphic(hdc, &LevelArrowLeft, LevelSelectorLeft.Left, LevelSelectorLeft.Top, LevelSelectorLeft.Width, LevelSelectorLeft.Height);
	DrawGraphic(hdc, &LevelArrowRight, LevelSelectorRight.Left, LevelSelectorRight.Top, LevelSelectorRight.Width, LevelSelectorRight.Height);
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::DrawScreenTree(HDC hdc)
	{
	COLORREF OldColor;
	HFONT OldFont;
	ostringstream ss;
	Data_Destiny_Tree_Class *DestinyTree;
	Data_Destiny_Class *Destiny;
	Data_Destiny_MultiSelector_Class *MultiDestiny;
	GraphicStruct TempGraphic;
	GraphicStruct BorderGraphic;
	GraphicStruct IconGraphic;
	GraphicStruct SlotGraphic;
	bool tempFlag;
	int tempIndex;
	enum BorderColor {NoBorder, WhiteBorder, RedBorder, LockedBorder};
	BorderColor SlotBorderColor;
	ArrowStruct Arrow;
	Character_Destinies_Class *CharacterDestinies;
	int SelectedDestinyRank;

	CharacterDestinies = Character.GetCharacterDestiniesPointer();
	DestinyTree = Data.GetDestinyTreePointer(ScreenTree);

	SetBkMode(hdc, HALFTONE);
		//Lets Draw the Header section
	DrawGraphic(hdc, &DestinyTree->GetTreeIcon(), DestinyHeaderLocation.Left+4, DestinyHeaderLocation.Top+4, 50, 50);
	DrawGraphic(hdc, &DestinyHeader, DestinyHeaderLocation.Left, DestinyHeaderLocation.Top, DestinyHeaderLocation.Width, DestinyHeaderLocation.Height);

	
	
	ss.str("");
	ss << DestinyTree->GetTreeName();
	OldColor = SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, DestinyHeaderLocation.Left+60, DestinyHeaderLocation.Top+5, ss.str().c_str(), ss.str().size());
	SetTextColor(hdc, OldColor);

	ClaimDestinyFlag = false;
	ActivateDestinyFlag = false;
	if (CharacterDestinies->GetCurrentActiveDestiny() == DT_NONE)	//We need to draw the Claim Destiny Buttons.
		{
		for (int x=0; x<3; x++)
			{
			if (SendMessage(EnforceDestinyProgressCheckBoxHandle, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					if (ClassID[x] != CLASSNONE)
					{
						if (ClassLevel[x] > 5 && Data.GetDestinySphere(ClassID[x]) == DestinyTree->GetDestinySphere())
							{
							DrawGraphic(hdc, &ClaimDestinyOn, ClaimDestinyLocation.Left, ClaimDestinyLocation.Top, ClaimDestinyLocation.Width, ClaimDestinyLocation.Height);
							ClaimDestinyFlag = true;
							break;
							}
					}

				if (x == 2)
					DrawGraphic(hdc, &ClaimDestinyOff, ClaimDestinyLocation.Left, ClaimDestinyLocation.Top, ClaimDestinyLocation.Width, ClaimDestinyLocation.Height);
				}
			else
				{
				DrawGraphic(hdc, &ClaimDestinyOn, ClaimDestinyLocation.Left, ClaimDestinyLocation.Top, ClaimDestinyLocation.Width, ClaimDestinyLocation.Height);
				ClaimDestinyFlag = true;
				}
			}
		}
	else //See if we need to draw the MakeActive Button or Active Destiny Text
		{
		if (ScreenTree == CharacterDestinies->GetCurrentActiveDestiny())
			{
			ss.str("Active Destiny");
			OldColor = SetTextColor(hdc, RGB(255,255,255));
			TextOut(hdc, ClaimDestinyLocation.Left, ClaimDestinyLocation.Top, ss.str().c_str(), ss.str().size());
			SetTextColor(hdc, OldColor);
			}
		}

	//Draw the Background image for the tree
	DrawGraphic(hdc, &DestinyTree->GetTreeBackground(), DestinyBackground.Left, DestinyBackground.Top, DestinyBackground.Width, DestinyBackground.Height);

	//Draw the Arrows for the Tree
	for (unsigned int i=0; i<DestinyTree->GetArrowPlacementSize(); i++)
		{
		Arrow = DestinyTree->GetArrowPlacement(i);
		if (Arrow.Direction == AD_UP && Arrow.Length == 1)
			DrawGraphic(hdc, &ArrowUp1, SlotLocation[Arrow.Level][Arrow.Slot].Left+15, SlotLocation[Arrow.Level][Arrow.Slot].Top-15, 14, 15);
		if (Arrow.Direction == AD_UP && Arrow.Length == 2)
			DrawGraphic(hdc, &ArrowUp2, SlotLocation[Arrow.Level][Arrow.Slot].Left+15, SlotLocation[Arrow.Level+1][Arrow.Slot].Top-15, 14, 86); 
		if (Arrow.Direction == AD_UP && Arrow.Length == 3)
			DrawGraphic(hdc, &ArrowUp1, SlotLocation[Arrow.Level][Arrow.Slot].Left+15, SlotLocation[Arrow.Level+2][Arrow.Slot].Top-15, 14, 158);
		if (Arrow.Direction == AD_LEFT)
			DrawGraphic(hdc, &ArrowLeft, SlotLocation[Arrow.Level][Arrow.Slot].Left-14, SlotLocation[Arrow.Level][Arrow.Slot].Top+20,15, 14);
		if (Arrow.Direction == AD_RIGHT)
			DrawGraphic(hdc, &ArrowLeft, SlotLocation[Arrow.Level][Arrow.Slot].Left+53, SlotLocation[Arrow.Level][Arrow.Slot].Top+20,15, 14);
		}

	//Draw the Core Destiny Frame
	DrawGraphic(hdc, &CoreDestinyFrame, DestinyCoreFrame.Left, DestinyCoreFrame.Top, DestinyCoreFrame.Width, DestinyCoreFrame.Height);

	SetBkMode(hdc, TRANSPARENT);
	OldFont = (HFONT)SelectObject(hdc, ArielFontSmall);

	//Draw our Slots & Icons
	for (int xtier=0; xtier<7; xtier++)
		{
		for (int xcolumn=0; xcolumn<6; xcolumn++)
			{
			if (ScreenTreeSlots[xtier][xcolumn].Valid == true)	//Slot is valid, lets get out Icon & slot graphics
				{
				if (ScreenTreeSlots[xtier][xcolumn].MultiSelection == true && ScreenTreeSlots[xtier][xcolumn].DestinyIndexChosen ==0)
					{
					//this is a multiSelection Slot and a Destiny hasn't been chosen yet.
					MultiDestiny = Data.GetMultiDestinyPointer(ScreenTreeSlots[xtier][xcolumn].DestinyIndex[0]);
					Destiny = DestinyTree->GetDestinyPointer(ScreenTreeSlots[xtier][xcolumn].DestinyIndex[1]);
					IconGraphic = MultiDestiny->GetIcon(Destiny->GetMultiIconIndex());
					//lets get our border color for this multiSelect Slot
					tempFlag = false;
					for (unsigned int j=1; j<ScreenTreeSlots[xtier][xcolumn].DestinyIndex.size(); j++)
						{
						Destiny = DestinyTree->GetDestinyPointer(ScreenTreeSlots[xtier][xcolumn].DestinyIndex[j]);
						if (AreRequirementsMet(Destiny, true, true, true) == true)
							{
							if (ScreenTreeSlots[xtier][xcolumn].Cost <=  24)  //TODO: Need to change this to a dynamic value DPAvailable
								{
								SlotBorderColor = WhiteBorder;
								tempFlag = true;
								break;
								}
							}
						}
					if (tempFlag == false)	//None of our destinies met all the requirements
						{
						for (unsigned int k=1; k<ScreenTreeSlots[xtier][xcolumn].DestinyIndex.size(); k++)
							{
							Destiny = DestinyTree->GetDestinyPointer(ScreenTreeSlots[xtier][xcolumn].DestinyIndex[k]);
							if (AreRequirementsMet(Destiny, false, true, false) == true) //We met the Destiny Requirement, just not points/level so set border color to NoBorder
								{
								tempFlag = true;
								SlotBorderColor = NoBorder;
								break;
								}
							}
						if (tempFlag == false)
							SlotBorderColor = RedBorder; //none of destinies met the Destiny Requirments
						}
					}
				else   //this is for a Single Destiny or a Multi-Destiny that has been chosen already.
					{
					tempIndex = ScreenTreeSlots[xtier][xcolumn].DestinyIndexChosen;
					Destiny = DestinyTree->GetDestinyPointer(ScreenTreeSlots[xtier][xcolumn].DestinyIndex[tempIndex]);
					IconGraphic = Destiny->GetDestinyIcon();
					//Lets find out what color border our destiny gets (Red, White, None)
					SlotBorderColor = NoBorder;
					if (AreRequirementsMet(Destiny, true, true, true) == true)
						{
						if (ScreenTreeSlots[xtier][xcolumn].Cost <= 24)	//TODO: Need to change this to a dynamic value DPAvailable
							{
							SlotBorderColor = WhiteBorder;		//All Requirements were met
							}
						else
							{
							if (AreRequirementsMet(Destiny, false, true, false) == false)
								SlotBorderColor = RedBorder;	//Destiny Requirements were not met.
							}
						}
					// check to see if we slot is already maxed out, if so NoBorder is needed.
					if (ScreenTreeSlots[xtier][xcolumn].RanksTaken == ScreenTreeSlots[xtier][xcolumn].Ranks)
						SlotBorderColor = NoBorder;
					}

				//Alright now lets set our SlotGraphic and BorderGraphic
				if (ScreenTreeSlots[xtier][xcolumn].Active == true)
					{
					if (xtier == 0)
						SlotGraphic = CoreSlotBackgroundActive;
					else
						SlotGraphic = TreeSlotBackgroundActive;
					switch (SlotBorderColor)
						{
						case WhiteBorder:
							BorderGraphic = SlotBorderAvailableActive;
							break;
						case RedBorder:
							BorderGraphic = SlotBorderNotAvailableActive;
							break;
						case LockedBorder:
							BorderGraphic = SlotBorderNotAllowedActive;
							break;
						}
					}
				else
					{
					if (xtier == 0)
						SlotGraphic = CoreSlotBackgroundPassive;
					else
						SlotGraphic = TreeSlotBackgroundPassive;
					switch (SlotBorderColor)
						{
						case WhiteBorder:
							BorderGraphic = SlotBorderAvailablePassive;
							break;
						case RedBorder:
							BorderGraphic = SlotBorderNotAvailablePassive;
							break;
						case LockedBorder:
							BorderGraphic = SlotBorderNotAllowedPassive;
							break;
						}
					}
				//ok now that we have our graphics, lets draw them & set the RanksTaken/MaxRanks textout messages.
				ss.str("");
				ss << ScreenTreeSlots[xtier][xcolumn].RanksTaken << "/" << ScreenTreeSlots[xtier][xcolumn].Ranks;
				if (xtier == 0)
					{
					if (ScreenTreeSlots[xtier][xcolumn].RanksTaken == 0)
						DrawGraphicGreyscale(hdc, &IconGraphic, IconLocation[xtier][xcolumn].Left, IconLocation[xtier][xcolumn].Top, IconLocation[xtier][xcolumn].Width, IconLocation[xtier][xcolumn].Height);
					else
						DrawGraphic(hdc, &IconGraphic, IconLocation[xtier][xcolumn].Left, IconLocation[xtier][xcolumn].Top, IconLocation[xtier][xcolumn].Width, IconLocation[xtier][xcolumn].Height);
					DrawGraphic(hdc, &SlotGraphic, CoreBorderLocation[xcolumn].Left, CoreBorderLocation[xcolumn].Top, CoreBorderLocation[xcolumn].Width, CoreBorderLocation[xcolumn].Height);
					ss.str("");
					ss << xcolumn;
					OldColor = SetTextColor(hdc, RGB(255,255,255));
					TextOut(hdc, CoreBorderLocation[xcolumn].Left+16, CoreBorderLocation[xcolumn].Top + 35, ss.str().c_str(), ss.str().size());
					}
				else
					{
					if (ScreenTreeSlots[xtier][xcolumn].RanksTaken == 0)
						DrawGraphicGreyscale(hdc, &IconGraphic, IconLocation[xtier][xcolumn].Left, IconLocation[xtier][xcolumn].Top, IconLocation[xtier][xcolumn].Width, IconLocation[xtier][xcolumn].Height);
					else
						DrawGraphic(hdc, &IconGraphic, IconLocation[xtier][xcolumn].Left, IconLocation[xtier][xcolumn].Top, IconLocation[xtier][xcolumn].Width, IconLocation[xtier][xcolumn].Height);
					DrawGraphic(hdc, &SlotGraphic, SlotLocation[xtier][xcolumn].Left, SlotLocation[xtier][xcolumn].Top, SlotLocation[xtier][xcolumn].Width, SlotLocation[xtier][xcolumn].Height);
					}



				//Lets Draw the Rank buttons
				int CurrentLevel;
					CurrentLevel = DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel;
				
				int RanksAtLevel = 0;

				RanksAtLevel = DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyRank - CurrentLevel * 5;

					
				if (RanksAtLevel >= 2)
				{
					DrawGraphic(hdc, &DestinyHeaderRank, DestinyHeaderRank1Location.Left, DestinyHeaderRank1Location.Top, DestinyHeaderRank1Location.Width, DestinyHeaderRank1Location.Height);
				}
				else
				{
					DrawGraphic(hdc, &DestinyHeaderRankBlank, DestinyHeaderRank1Location.Left, DestinyHeaderRank1Location.Top, DestinyHeaderRank1Location.Width, DestinyHeaderRank1Location.Height);

				}


				if (RanksAtLevel >= 3)
				{

				DrawGraphic(hdc, &DestinyHeaderRank, DestinyHeaderRank2Location.Left, DestinyHeaderRank2Location.Top, DestinyHeaderRank2Location.Width, DestinyHeaderRank2Location.Height);
				}
				else
				{
					DrawGraphic(hdc, &DestinyHeaderRankBlank, DestinyHeaderRank2Location.Left, DestinyHeaderRank3Location.Top, DestinyHeaderRank3Location.Width, DestinyHeaderRank3Location.Height);
				}
				if (RanksAtLevel >= 4)
				{
					DrawGraphic(hdc, &DestinyHeaderRank, DestinyHeaderRank3Location.Left, DestinyHeaderRank3Location.Top, DestinyHeaderRank3Location.Width, DestinyHeaderRank3Location.Height);

				}
				else
				{
					DrawGraphic(hdc, &DestinyHeaderRankBlank, DestinyHeaderRank3Location.Left, DestinyHeaderRank3Location.Top, DestinyHeaderRank3Location.Width, DestinyHeaderRank3Location.Height);

				}
				if (RanksAtLevel >= 5)
				{
					DrawGraphic(hdc, &DestinyHeaderRank, DestinyHeaderRank4Location.Left, DestinyHeaderRank4Location.Top, DestinyHeaderRank4Location.Width, DestinyHeaderRank4Location.Height);

				}
				else
				{
					DrawGraphic(hdc, &DestinyHeaderRankBlank, DestinyHeaderRank4Location.Left, DestinyHeaderRank4Location.Top, DestinyHeaderRank4Location.Width, DestinyHeaderRank4Location.Height);

				}

				//Lets Draw the Header xp bar if needed
				if (DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyRank == 25)
				{
					DrawGraphic(hdc, &DestinyHeaderXP, DestinyHeaderXPLocation.Left, DestinyHeaderXPLocation.Top, DestinyHeaderXPLocation.Width, DestinyHeaderXPLocation.Height);

				}
				else
				{
					DrawGraphic(hdc, &DestinyHeaderXPBlank, DestinyHeaderXPLocation.Left, DestinyHeaderXPLocation.Top, DestinyHeaderXPLocation.Width, DestinyHeaderXPLocation.Height);

				}



				// we need to switch the text color back for the next round of icons
				SetTextColor(hdc, OldColor);
				}
			}
		}

	//Draw ResetTree Button
	DrawGraphic(hdc, &ResetTreeOff, ResetTreeLocation.Left, ResetTreeLocation.Top, ResetTreeLocation.Width, ResetTreeLocation.Height);

	SelectedDestinyRank = CharacterDestinies->GetSelectedDestinyLevel(DestinyTree->GetTreeIndex(), CharacterLevel);
	//Text out the Availble/Spent Text
	if (SelectedDestinyRank !=-1)
		{
		ss.str("");
		ss << DPAvailbleTree[ScreenTree] << " Points Available for This Tree (" << DPSpentTree[ScreenTree] << " Spent)";
		OldColor = SetTextColor(hdc, RGB(255,255,255));
		TextOut(hdc, DestinyBackground.Left, DestinyBackground.Top + DestinyBackground.Height +5, ss.str().c_str(), ss.str().size());
		SetTextColor(hdc, OldColor);
		}


	//Draw the Rank selectors if needed
	if (SelectedDestinyRank != -1)
		{
		if (SelectedDestinyRank > 0)
			DrawGraphic(hdc, &LevelArrowLeft, LevelSelectorLeft.Left, LevelSelectorLeft.Top, LevelSelectorLeft.Width, LevelSelectorLeft.Height);
		if (SelectedDestinyRank < 29)
			DrawGraphic(hdc, &LevelArrowRight, LevelSelectorRight.Left, LevelSelectorRight.Top, LevelSelectorRight.Width, LevelSelectorRight.Height);
		ss.str("");
		ss << "Level " << DestinyTreeRanks[SelectedDestinyRank].DestinyLevel << " (Rank " << DestinyTreeRanks[SelectedDestinyRank].DestinyRank << ")";
		OldColor = SetTextColor(hdc, RGB(255,255,255));
		TextOut(hdc, LevelSelectorLeft.Left + LevelSelectorLeft.Width + 2, LevelSelectorLeft.Top+3, ss.str().c_str(), ss.str().size());
		SetTextColor(hdc, OldColor);
		}

	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::DrawDestinyListItem(HDC hdc, DWORD Item, long Top, long Left)
	{
	string Text;
	COLORREF OriginalColor;
	Data_Destiny_Tree_Class *DestinyTree;
	GraphicStruct DestinyIcon;
	Character_Destinies_Class *CharacterDestinies;
	DESTINY_SPHERE Sphere;
	ostringstream ss;

	CharacterDestinies = Character.GetCharacterDestiniesPointer();
	DestinyTree = Data.GetDestinyTreePointer(DESTINY_TREE(Item));
	DestinyIcon = DestinyTree->GetTreeIcon();
	Sphere = DestinyTree->GetDestinySphere();

	Text = DestinyTree->GetTreeName();

	if (Sphere == DS_ARCANE)
		{
		if (ScreenTree == DestinyTree->GetTreeIndex())
			DrawGraphic(hdc, &ColorBarArcaneSelected, Left+32, Top+4, 180, 38);
		else
			DrawGraphic(hdc, &ColorBarArcane, Left+32, Top+4, 180, 38);
		}
	else if (Sphere == DS_DIVINE)
		{
		if (ScreenTree == DestinyTree->GetTreeIndex())
			DrawGraphic(hdc, &ColorBarDivineSelected, Left+32, Top+4, 180, 38);
		else
			DrawGraphic(hdc, &ColorBarDivine, Left+32, Top+4, 180, 38);
		}
	else if (Sphere == DS_MARTIAL)
		{
		if (ScreenTree == DestinyTree->GetTreeIndex())
			DrawGraphic(hdc, &ColorBarMartialSelected, Left+32, Top+4, 180, 38);
		else
			DrawGraphic(hdc, &ColorBarMartial, Left+32, Top+4, 180, 38);
		}
	else
		{
		if (ScreenTree == DestinyTree->GetTreeIndex())
			DrawGraphic(hdc, &ColorBarPrimalSelected, Left+32, Top+4, 180, 38);
		else
			DrawGraphic(hdc, &ColorBarPrimal, Left+32, Top+4, 180, 38);
		}

	if (CharacterDestinies->GetSelectedDestinyLevel(DestinyTree->GetTreeIndex(), CharacterLevel) == -1)
	//if (CharacterDestinies->GetCurrentActiveDestiny() == DT_NONE)
		DrawGraphicGreyscale(hdc, &DestinyIcon, Left+6, Top+4, 36, 36);
	else
		DrawGraphic(hdc, &DestinyIcon, Left+6, Top+4, 36, 36);

	//Let see if we need to draw our Not Claimed Destiny Rings
	if (CharacterDestinies->GetCurrentActiveDestiny() == DT_NONE)
		{
		for (int x=0; x<3; x++)
			{
			if (SendMessage(EnforceDestinyProgressCheckBoxHandle, BM_GETCHECK, 0, 0) == TRUE)
				{
					if (ClassID[x] != CLASSNONE)
					{
						if (ClassLevel[x] > 5 && Data.GetDestinySphere(ClassID[x]) == DestinyTree->GetDestinySphere())
							{
							DrawGraphic(hdc, &DestinyIconRingNotClaimed, Left, Top, 48, 48);
							break;
							}
						}
					}

			else
				{
				DrawGraphic(hdc, &DestinyIconRingNotClaimed, Left, Top, 48, 48);
				break;
				}
			}
		}
	if (CharacterDestinies->GetCurrentActiveDestiny() == DestinyTree->GetTreeIndex())
		DrawGraphic(hdc, &DestinyIconRingSelected, Left, Top, 48, 48);
	else if (CharacterDestinies->GetSelectedDestinyLevel(DestinyTree->GetTreeIndex(),CharacterLevel) >= 0)
		DrawGraphic(hdc, &DestinyIconRingAvailable, Left, Top, 48, 48);

	//Draw Level Circle if needed
	if (CharacterDestinies->GetSelectedDestinyLevel(DestinyTree->GetTreeIndex(), CharacterLevel) >= 0)
		{
		DrawGraphic(hdc, &LevelCircle, Left+28, Top+25, 22, 23);
		OriginalColor = SetTextColor(hdc, RGB(255,255,255));
		ss.str("");
		ss << DestinyTreeRanks[DestinyTreeLevel[ScreenTree]].DestinyLevel;
		TextOut(hdc, Left+35, Top+27, ss.str().c_str(), ss.str().size());
		SetTextColor(hdc, OriginalColor);
		}

	//Text out the Tree Name
	OriginalColor = SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, Left+47, Top+15, Text.c_str(), Text.size());
	SetTextColor(hdc, OriginalColor);

	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::FillDestiniesList()
	{
	Data_Destiny_Tree_Class *DestinyTree;
	vector <DestinySortStruct> DestinyTreeListSort;
	DestinySortStruct NewDestinyTree;
	Character_Destinies_Class *CharacterDestinies;

	CharacterDestinies = Character.GetCharacterDestiniesPointer();

	SendMessage(DestiniesListHandle, LB_RESETCONTENT, 0, 0);

	DestinyTreeListSort.clear();

	for (unsigned int i=0; i<NUM_DESTINY_TREES; i++)
		{
		DestinyTree = Data.GetDestinyTreePointer((DESTINY_TREE)i);
		if (DestinyTree->DoesTreeHaveDestinies())
			{
			if (CharacterDestinies->GetSelectedDestinyLevel(DestinyTree->GetTreeIndex(), CharacterLevel) != -1)
				NewDestinyTree.DestinyLevel = 0;
			else
				NewDestinyTree.DestinyLevel = 1;
			NewDestinyTree.DestinyTreeName = DestinyTree->GetTreeName();
			NewDestinyTree.DestinyTreeIndex = (DESTINY_TREE)i;
			DestinyTreeListSort.push_back(NewDestinyTree);
			}
		}
	sort(DestinyTreeListSort.begin(), DestinyTreeListSort.end(), DestinyCompareLevel);

	for (unsigned int i=0; i<DestinyTreeListSort.size(); i++)
		{
			SendMessage(DestiniesListHandle, LB_ADDSTRING, 0, DestinyTreeListSort[i].DestinyTreeIndex);
		}

	}

//--------------------------------------------------------------------------
WNDPROC Screen_Destiny_Class::GetOriginalWinProc(HWND Window)
	{
	for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
		{
		if (SubclassHWNDs[i] == Window)
			return OriginalProcs[i];
		}
	return 0;
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::HandleMouseHover(int x, int y)
	{
	bool SlotSelected;
	int Tier;
	int Column;
	Data_Destiny_Tree_Class *DestinyTree;
	Data_Destiny_Class *Destiny;

	//Lets find out if our user is hovering on a slot
	SlotSelected = IsSlotSelected(x, y, &Tier, &Column);

	//Stop here if the slot is the same as the old slot, don't keep redrawing it!
	if (SlotSelected == true && Tier == ToolTipTier && Column == ToolTipColumn)
		return;

	ToolTipTier = Tier;
	ToolTipColumn = Column;

	//Ok lets set Slot information if the slot was highlighted
	if (SlotSelected == true)
		{
		if (ScreenTreeSlots[Tier][Column].Valid == true)
			{
			DestinyTree = Data.GetDestinyTreePointer(ScreenTree);
			if (ScreenTreeSlots[Tier][Column].MultiSelection == true)
				{
				if (ScreenTreeSlots[Tier][Column].DestinyIndexChosen == 0)
					Destiny = DestinyTree->GetDestinyPointer(Tier, Column);
				else
					Destiny = DestinyTree->GetDestinyPointer(ScreenTreeSlots[Tier][Column].DestinyIndex[ScreenTreeSlots[Tier][Column].DestinyIndexChosen]);
				}
			else
				{
				Destiny = DestinyTree->GetDestinyPointer(ScreenTreeSlots[Tier][Column].DestinyIndex[0]);
				}
			SetToolTipWindow(Destiny);
			ShowToolTipWindow(true);
			}
		else
			{
			ShowToolTipWindow(false);
			ToolTipTier = -1;
			ToolTipColumn = -1;
			}
		}
	else
		{
		ShowToolTipWindow(false);
		ToolTipTier = -1;
		ToolTipColumn = -1;
		}
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::HandleLeftMouseButtonClick(int x, int y)
	{
	HDC ParentDC;

	Character_Destinies_Class *CharacterDestinies;
	int SelectedDestinyRanks;
	string textout;
	//textout = "x: " + x + ' y: ' + y;
	//DEBUG(textout);
	ParentDC = GetDC(DestinyWindowHandle);
	CharacterDestinies = Character.GetCharacterDestiniesPointer();
	SelectedDestinyRanks = CharacterDestinies->GetSelectedDestinyLevel(ScreenTree, CharacterLevel);

	//Header Section (ClaimDestiny or ActivateDestinyButton)
	if (x > ClaimDestinyLocation.Left && x < (ClaimDestinyLocation.Left + ClaimDestinyLocation.Width) &&
		y > ClaimDestinyLocation.Top && y < (ClaimDestinyLocation.Top + ClaimDestinyLocation.Height))
		{
		if (ClaimDestinyFlag == true)
			{
			if (ClaimDestinyWindowVisible == false)
				{

				ClaimDestiny();
				}
			}
		else if (ActivateDestinyFlag == true)
			ActivateDestiny();
		}

	//Footer Section (Destiny Rank Selectors)
	//Lower Destinyy Level
	if (x > LevelSelectorLeft.Left && x < (LevelSelectorLeft.Left + LevelSelectorLeft.Width) &&
		y > LevelSelectorLeft.Top && y < (LevelSelectorLeft.Top + LevelSelectorLeft.Height))
		{
		if (SelectedDestinyRanks > 0)
			{
			ChangeDestinyTreeRanks(false);
			}
		}
	//Raise Destiny Level
	if (x > LevelSelectorRight.Left && x < (LevelSelectorRight.Left + LevelSelectorRight.Width) &&
		y > LevelSelectorRight.Top && y < (LevelSelectorRight.Top + LevelSelectorRight.Height))
		{
		if (SelectedDestinyRanks != -1 && SelectedDestinyRanks <29)
			{
			ChangeDestinyTreeRanks(true);
			}
		}

	ReleaseDC(DestinyWindowHandle, ParentDC);

	}

//--------------------------------------------------------------------------
long Screen_Destiny_Class::HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	WNDPROC OriginalProc;
	DWORD Selection;
	int IconDrag;
	HDC ParentDC;

	ParentDC = GetDC(DestinyWindowHandle);

	switch (Message)
		{
		case WM_LBUTTONDBLCLK:
			{
			if (Wnd == DestiniesListHandle)
				return 0;
			break;
			}
		case WM_LBUTTONDOWN:
			{
			if (Wnd == DestiniesListHandle)
				{
				Selection = SendMessage(DestiniesListHandle, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(DestiniesListHandle, LB_GETITEMDATA, Selection, 0);
				if (IconDrag == -1)
					return 0;
				UpdateScreenTree((DESTINY_TREE)IconDrag);
				RedrawWindow(DestinyWindowHandle, &rectHeader, NULL, RDW_ERASE | RDW_INVALIDATE);
				RedrawWindow(DestinyWindowHandle, &rectFooter, NULL, RDW_ERASE | RDW_INVALIDATE);
				UpdateWindow(DestinyWindowHandle);
				ClaimDestinyFlag = false;
				DrawScreenTree(ParentDC);
				FillDestiniesList();
				return 0;
				}
			break;
			}
		}
	ReleaseDC(DestinyWindowHandle, ParentDC);

	OriginalProc = GetOriginalWinProc(Wnd);
	return CallWindowProc(OriginalProc, Wnd, Message, wParam, lParam);
	}

//--------------------------------------------------------------------------
long Screen_Destiny_Class::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	PAINTSTRUCT ps;
	//RECT Rect;
	//DWORD Selection;
	//int IconDrag;
	Character_Destinies_Class *CharacterDestinies;
	//HDC ParentDC;

	//ParentDC = GetDC(DestinyWindowHandle);
	//if (ParentDC == nullptr)
	//	DEBUG("GetDC Fail");

	CharacterDestinies = Character.GetCharacterDestiniesPointer();

	switch (Message)
		{
		case WM_CLOSE:
			{
			InterfaceManager.ShowChild(DESTINYWINDOW, false);
			return 0;
			}
		case WM_COMMAND:
			{
			if (HIWORD(wParam) == BN_CLICKED)
				{
				if ((int)LOWORD(wParam) == DW_ACCEPTBUTTON)
					{
					return 0;
					}
				if ((int)LOWORD(wParam) == DW_CANCELBUTTON)
					{
					InterfaceManager.ShowChild(DESTINYWINDOW, false);
					return 0;
					}
				if ((int)LOWORD(wParam) == DW_ENFORCEDESTINYPROGRESSCHECKBOX)
					{
					if (SendMessage(EnforceDestinyProgressCheckBoxHandle, BM_GETCHECK, 0, 0) == BST_CHECKED)
						CharacterDestinies->SetProgressEnforcement(true);
					else
						CharacterDestinies->SetProgressEnforcement(false);
					FillDestiniesList();
					}

				}
			return 0;
			}
		case WM_LBUTTONDOWN:
			{
			if (IsChildWindowVisible() == false)
				{
				HandleLeftMouseButtonClick(LOWORD(lParam), HIWORD(lParam));
				}
			return 0;
			}
		case WM_MOUSEHOVER:
			{
			if (IsChildWindowVisible() == false)
				{
				HandleMouseHover(LOWORD(lParam), HIWORD(lParam));
				TrackMouseEvent(&tme);
				}
			else
				TrackMouseEvent(&tme);
			return 0;
			}
		case WM_MOUSEMOVE:
			{
			if (!TMEFlag)
				{
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_LEAVE | TME_HOVER;
				tme.dwHoverTime = 400;
				tme.hwndTrack = DestinyWindowHandle;
				TrackMouseEvent(&tme);
				TMEFlag = true;
				}
			return 0;
			}
		case WM_MOUSELEAVE:
			{
			ShowToolTipWindow(false);
			TMEFlag = false;
			ToolTipColumn = -1;
			ToolTipTier = -1;
			return 0;
			}

		case WM_CTLCOLORLISTBOX:
			{
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (long)GetStockObject(BLACK_BRUSH);
			//return (long)GetStockObject(DKGRAY_BRUSH);
			}
		case WM_CTLCOLORSTATIC:
			{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(255,255,255));
			return (long)GetStockObject(DKGRAY_BRUSH);
			}
		case WM_DRAWITEM:
			{
			if ((unsigned int)wParam == DW_DESTINIESLIST)
				{
				DrawDestinyListItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			return false;
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

	//ReleaseDC(DestinyWindowHandle, ParentDC);
	}

//--------------------------------------------------------------------------
bool Screen_Destiny_Class::IsChildWindowVisible()
	{
	if (ClaimDestinyWindowVisible == true)
		return true;
	if (MultiDestinyWindowvisible == true)
		return true;
	return false;
	}
//--------------------------------------------------------------------------
HWND Screen_Destiny_Class::GetHandle()
{


	return DestinyWindowHandle;

}

//--------------------------------------------------------------------------
bool Screen_Destiny_Class::IsSlotSelected(int x, int y, int *rTier, int *rColumn)
	{
	bool SlotSelected;

	SlotSelected = false;

	if (x > DestinyBackground.Left && x < (DestinyBackground.Left+DestinyBackground.Width) && y > DestinyBackground.Top && y < (DestinyBackground.Top+DestinyBackground.Height))
		{
		for (int xTier = 0; xTier<7; xTier++)
			{
			for (int xColumn=0; xColumn<6; xColumn++)
				{
				if (x > SlotLocation[xTier][xColumn].Left && x < (SlotLocation[xTier][xColumn].Left + SlotLocation[xTier][xColumn].Width) &&
					y > SlotLocation[xTier][xColumn].Top && y < (SlotLocation[xTier][xColumn].Top + SlotLocation[xTier][xColumn].Height))
					{
					SlotSelected = true;
					*rTier = xTier;
					*rColumn = xColumn;
					break;
					}
				}
			}
		}
	return SlotSelected;
	}

//--------------------------------------------------------------------------
void Screen_Destiny_Class::LoadGraphics(HWND Parent)
	{
	//HDC hdc;

	//palette for halftone work
	//hdc = GetDC(Parent);
	//Palette = CreateHalftonePalette(hdc);
	//ReleaseDC(Parent, hdc);

	LoadBitmap("EmptyActiveCore", "UserInterface", &CoreSlotBackgroundActive);
	LoadBitmap("EmptyPassiveCore", "UserInterface", &CoreSlotBackgroundPassive);
	LoadBitmap("EmptyActiveTree", "UserInterface", &TreeSlotBackgroundActive);
	LoadBitmap("EmptyPassiveTree", "UserInterface", &TreeSlotBackgroundPassive);

	LoadBitmap("EnhancementActiveAvailable", "UserInterface", &SlotBorderAvailableActive);
	LoadBitmap("EnhancementPassiveAvailable", "UserInterface", &SlotBorderAvailablePassive);
	LoadBitmap("EnhancementActiveNotAvailable", "UserInterface", &SlotBorderNotAvailableActive);
	LoadBitmap("EnhancementPassiveNotAvailable", "UserInterface", &SlotBorderNotAvailablePassive);

	LoadBitmap("EnhancementActiveNotAllowed", "UserInterface", &SlotBorderNotAllowedActive);
	LoadBitmap("EnhancementPassiveNotAllowed", "UserInterface", &SlotBorderNotAllowedPassive);

	LoadBitmap("ResetTreeOn", "UserInterface", &ResetTreeOn);
	LoadBitmap("ResetTreeOff", "UserInterface", &ResetTreeOff);

	LoadBitmap("ArrowLeft", "UserInterface", &LevelArrowLeft);
	LoadBitmap("ArrowRight", "UserInterface", &LevelArrowRight);

	LoadBitmap("DestinyBarArcane", "UserInterface", &ColorBarArcane);
	LoadBitmap("DestinyBarDivine", "UserInterface", &ColorBarDivine);
	LoadBitmap("DestinyBarMartial", "UserInterface", &ColorBarMartial);
	LoadBitmap("DestinyBarPrimal", "UserInterface", &ColorBarPrimal);

	LoadBitmap("DestinyBarArcaneSelected", "UserInterface", &ColorBarArcaneSelected);
	LoadBitmap("DestinyBarDivineSelected", "UserInterface", &ColorBarDivineSelected);
	LoadBitmap("DestinyBarMartialSelected", "UserInterface", &ColorBarMartialSelected);
	LoadBitmap("DestinyBarPrimalSelected", "UserInterface", &ColorBarPrimalSelected);

	LoadBitmap("EnhancementArrowLeft", "UserInterface", &ArrowLeft);
	LoadBitmap("EnhancementArrowRight", "UserInterface", &ArrowRight);
	LoadBitmap("EnhancementArrowUp", "UserInterface", &ArrowUp1);
	LoadBitmap("EnhancementArrowUpLong", "UserInterface", &ArrowUp2);
	LoadBitmap("DestinyCoreFrame", "UserInterface", &CoreDestinyFrame);

	LoadBitmap("DestinyIconRingAvailable", "UserInterface", &DestinyIconRingAvailable);
	LoadBitmap("DestinyIconRingNotClaimed", "UserInterface", &DestinyIconRingNotClaimed);
	LoadBitmap("DestinyIconRingSelected", "UserInterface", &DestinyIconRingSelected);
	LoadBitmap("DestinyHeader", "UserInterface", &DestinyHeader);
	LoadBitmap("DestinyHeaderXP", "UserInterface", &DestinyHeaderXP);
	LoadBitmap("DestinyHeaderXPBlank", "UserInterface", &DestinyHeaderXPBlank);
	LoadBitmap("DestinyHeaderRank", "UserInterface", &DestinyHeaderRank);
	LoadBitmap("DestinyHeaderRankBlank", "UserInterface", &DestinyHeaderRankBlank);
	LoadBitmap("ClaimDestinyOn", "UserInterface", &ClaimDestinyOn);
	LoadBitmap("ClaimDestinyOff", "UserInterface", &ClaimDestinyOff);
	LoadBitmap("MakeActive", "UserInterface", &MakeActiveButton);
	LoadBitmap("DestinyLevelCircle", "UserInterface", &LevelCircle);
	}

//---------------------------------------------------------------------------
void Screen_Destiny_Class::Show(bool State)
	{
	//Show DestinyWindow
	ShowWindow(DestinyWindowHandle, State);
	ShowWindow(DestiniesFrameHandle, State);
	ShowWindow(AbilitiesFrameHandle, State);
	ShowWindow(ShowAllCheckBoxHandle, State);
	ShowWindow(AbilitiesListHandle, State);
	ShowWindow(AcceptButtonHandle, State);
	ShowWindow(CancelButtonHandle, State);
	ShowWindow(AbilitiesLabelHandle, State);
	ShowWindow(DestiniesLabelHandle, State);
	ShowWindow(TwistsofFateFrameHandle, State);
	ShowWindow(TwistsofFateLabelHandle, State);
	ShowWindow(DestiniesListHandle, State);
	ShowWindow(EnforceLevelCheckBoxHandle, State);
	ShowWindow(EnforceDestinyProgressCheckBoxHandle, State);
	}

//---------------------------------------------------------------------------
void Screen_Destiny_Class::SubclassChildWindows()
	{
	WNDPROC OriginalProc;

	SubclassHWNDs.clear();
	OriginalProcs.clear();

	OriginalProc = (WNDPROC)SetWindowLong(AbilitiesListHandle, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(AbilitiesListHandle);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(DestiniesListHandle, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(DestiniesListHandle);
	OriginalProcs.push_back(OriginalProc);

	}

//-------------------------------------------------------------------------
void Screen_Destiny_Class::UpdateScreenTree(DESTINY_TREE DTree)
	{
	Data_Destiny_Tree_Class *DestinyTree;
	Data_Destiny_Class *Destiny;
	Character_Destinies_Class *CharacterDestinies;
	unsigned int NumofDestinies;
	int tempRanksTaken;



	//Lets clear our Screen Tree Variables
	for (int tier=0; tier<7; tier++)
		{
		for (int slot=0; slot<6; slot++)
			{
			ScreenTreeSlots[tier][slot].Active = false;
			ScreenTreeSlots[tier][slot].Cost = 0;
			ScreenTreeSlots[tier][slot].DestinyIndex.clear();
			ScreenTreeSlots[tier][slot].DestinyIndexChosen = 0;
			ScreenTreeSlots[tier][slot].MultiSelection = false;
			ScreenTreeSlots[tier][slot].Ranks = 0;
			ScreenTreeSlots[tier][slot].RanksTaken = 0;
			ScreenTreeSlots[tier][slot].RanksTakenOld = 0;
			ScreenTreeSlots[tier][slot].Valid = false;
			}
		}

	ScreenTree = DTree;

	CharacterDestinies = Character.GetCharacterDestiniesPointer();
	DestinyTree = Data.GetDestinyTreePointer(ScreenTree);

	for (unsigned int tier=0; tier<7; tier++)
		{
		for (unsigned int column=0; column<6; column++)
			{
			if (tier > 0 && column == 6) //Tiers 1-6 don't have 6 columns
				break;
			Destiny = DestinyTree->GetDestinyPointer(tier, column);
			if (Destiny != nullptr)
				{
				ScreenTreeSlots[tier][column].Valid = true;
				ScreenTreeSlots[tier][column].Active = Destiny->GetActive();
				if (Destiny->GetMultiSelection() == true)
					{
					ScreenTreeSlots[tier][column].MultiSelection = true;
					ScreenTreeSlots[tier][column].DestinyIndex.push_back(Data.GetDestinyMultiSelectorIndex(Destiny->GetMultiSelectorName()));
					NumofDestinies = DestinyTree->GetNumofDestinies(Destiny->GetDestinyIndex());
					for (unsigned int x=1; x<=NumofDestinies; x++)
						ScreenTreeSlots[tier][column].DestinyIndex.push_back(DestinyTree->GetDestinyIndex(tier, column, x));
					}
				else
					{
					ScreenTreeSlots[tier][column].MultiSelection = false;
					ScreenTreeSlots[tier][column].DestinyIndex.push_back(Destiny->GetDestinyIndex());
					}
				ScreenTreeSlots[tier][column].Cost = Destiny->GetDPCost();
				ScreenTreeSlots[tier][column].Ranks = Destiny->GetRanks();

				//Retrieve character info
				ScreenTreeSlots[tier][column].DestinyIndexChosen = CharacterDestinies->GetDestinyIndexChosen(ScreenTree, tier, column);
				if ((tempRanksTaken = CharacterDestinies->GetRanksTaken(ScreenTree, tier, column)) > 0)
					{
					for (int xRank = 0; xRank<tempRanksTaken; xRank++)
						{
						if (CharacterDestinies->GetLevelTaken(ScreenTree, tier, column, xRank) <= CharacterLevel)
							{
							ScreenTreeSlots[tier][column].RanksTaken++;
						    ScreenTreeSlots[tier][column].RanksTakenOld++;
							}
						}
					}
				}
			}
		}
	}

//-------------------------------------------------------------------------
bool DestinyCompareLevel(DestinySortStruct E1, DestinySortStruct E2)
	{
	//Sort DestinyTree by Level then by Name
	if (E1.DestinyLevel != E2.DestinyLevel)
		return E1.DestinyLevel < E2.DestinyLevel;
	return E1.DestinyTreeName < E2.DestinyTreeName;
	}


