#include "EnhancementWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "DataClass.h"
#include "ToolTipWindowClass.h"
#include "MainScreenClass.h"


//---------------------------------------------------------------------------
EnhancementWindowClass::EnhancementWindowClass()
	{
	//set our coordinates for placeing our graphics and handling mouse clicks.
	BackgroundLeft[0] = 30;
	BackgroundLeft[1] = 340;
	BackgroundLeft[2] = 650;
	BackgroundTop = 10;
	BackgroundWidth = 299;		//old value 305;
	BackgroundHeight = 466;		//old value 430;
	SlotCoreLeft[0][0] = 45;
	SlotCoreLeft[0][1] = 90;
	SlotCoreLeft[0][2] = 135;
	SlotCoreLeft[0][3] = 180;
	SlotCoreLeft[0][4] = 225;
	SlotCoreLeft[0][5] = 270;
	SlotCoreLeft[1][0] = 355;
	SlotCoreLeft[1][1] = 400;
	SlotCoreLeft[1][2] = 445;
	SlotCoreLeft[1][3] = 490;
	SlotCoreLeft[1][4] = 535;
	SlotCoreLeft[1][5] = 580;
	SlotCoreLeft[2][0] = 665;
	SlotCoreLeft[2][1] = 710;
	SlotCoreLeft[2][2] = 755;
	SlotCoreLeft[2][3] = 800;
	SlotCoreLeft[2][4] = 845;
	SlotCoreLeft[2][5] = 890;
	SlotLeft[0][0] = 40;
	SlotLeft[0][1] = 100;
	SlotLeft[0][2] = 160;
	SlotLeft[0][3] = 220;
	SlotLeft[0][4] = 280;
	SlotLeft[1][0] = 350;
	SlotLeft[1][1] = 410;
	SlotLeft[1][2] = 470;
	SlotLeft[1][3] = 530;
	SlotLeft[1][4] = 590;
	SlotLeft[2][0] = 660;
	SlotLeft[2][1] = 720;
	SlotLeft[2][2] = 780;
	SlotLeft[2][3] = 840;
	SlotLeft[2][4] = 900;
	SlotTop[0] = 375;
	SlotTop[1] = 300;
	SlotTop[2] = 230;
	SlotTop[3] = 160;
	SlotTop[4] = 90;
	SlotTop[5] = 20;
	SlotWidth = 43;
	SlotHeight = 53;
	SlotCoreWidth = 38;
	SlotCoreHeight = 38;
	APSpentLeft[0] = 260;
	APSpentLeft[1] = 570;
	APSpentLeft[2] = 880;
	APSpentTop = 430;
	}

//---------------------------------------------------------------------------
EnhancementWindowClass::~EnhancementWindowClass()
	{
	DeleteGraphics();
	DeSubclassChildWindows();
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::Create(HINSTANCE Instance, HWND Parent)
	{
	WNDCLASSEX wc;
	int ScreenX;
	int ScreenY;
	RECT WindowRect;
	RECT ParentRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Enhancements Window";
	LOGFONT lf;
	ParentWindow = Parent;
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

	//create and place the window of bottom half of Enhancement Window
	
	EnhancementWindowHandle = CreateWindowEx (NULL, WindowName, WindowName, WS_POPUP | WS_DLGFRAME, 0, 0, 1000, 570, Parent, NULL, Instance, NULL);
	SetClassLong(EnhancementWindowHandle, 0, (long)ENHANCEMENTWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(Parent, &ParentRect);
	GetWindowRect(EnhancementWindowHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(EnhancementWindowHandle, Parent, (ScreenX/2)-(WindowX/2), (ScreenY/2)-(WindowY/2), 0, 0, SWP_NOSIZE);
	
	//the child windows
	APTomeButton = CreateWindowEx(NULL, "BUTTON", "AP Tome", WS_CHILD | BS_AUTOCHECKBOX, 580, 480, 150, 20, EnhancementWindowHandle, (HMENU)EW_APTOME, Instance, NULL);
	APRemainingLabel = CreateWindowEx(NULL, "STATIC", "Action Points Remaining,", WS_CHILD | SS_CENTER, 450, 505, 340, 20, EnhancementWindowHandle, (HMENU)EW_APREMAININGLABEL, Instance, NULL);
	APSpentLabel = CreateWindowEx(NULL, "STATIC", "0 Spent", WS_CHILD | SS_CENTER, 450, 530, 340, 20, EnhancementWindowHandle, (HMENU)EW_APSPENTLABEL, Instance, NULL);
	Respec = CreateWindowEx(NULL, "BUTTON", "Respec From This Level", WS_CHILD, 820, 480, 170, 20, EnhancementWindowHandle, (HMENU)EW_RESPEC, Instance, NULL);

	ResetAllTreesButton = CreateWindowEx(NULL, "BUTTON", "Reset All Trees", WS_CHILD, 820, 505, 170, 20, EnhancementWindowHandle, (HMENU)EW_RESETALLTREESBUTTON, Instance, NULL);
	CancelButton = CreateWindowEx(NULL, "BUTTON", "Cancel", WS_CHILD, 820, 530, 80, 20, EnhancementWindowHandle, (HMENU)EW_CANCELBUTTON, Instance, NULL);
	AcceptButton = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD, 910, 530, 80, 20, EnhancementWindowHandle, (HMENU)EW_ACCEPTBUTTON, Instance, NULL);
	TreeFrame1 = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 29, 9, 301, 468, EnhancementWindowHandle, (HMENU)EW_TREEFRAME1, Instance, NULL);
	TreeFrame2 = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 339, 9, 301, 468, EnhancementWindowHandle, (HMENU)EW_TREEFRAME2, Instance, NULL);
	TreeFrame3 = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | SS_GRAYFRAME, 649, 9, 301, 468, EnhancementWindowHandle, (HMENU)EW_TREEFRAME3, Instance, NULL);
	SelectTreeList = CreateWindowEx(NULL, "LISTBOX", "AvailableTreeList", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 365, 466, 162, 60, EnhancementWindowHandle, (HMENU)EW_SELECTTREELIST, Instance, NULL);
																		
	//Set item height of our Listboxes
	SendMessage(SelectTreeList, LB_SETITEMHEIGHT, 0, MAKELPARAM(20, 0));

	//Create our fonts to be used
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

	LoadGraphics(EnhancementWindowHandle);
	SubclassChildWindows();
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::Show(bool State)
	{
	//show Enhancement window
	ShowWindow(EnhancementWindowHandle, State);
	ShowWindow(APRemainingLabel, State);
	ShowWindow(APSpentLabel, State);
	ShowWindow(Respec, State);
	ShowWindow(ResetAllTreesButton, State);
	ShowWindow(CancelButton, State);
	ShowWindow(AcceptButton, State);
	ShowWindow(TreeFrame1, State);
	ShowWindow(TreeFrame2, State);
	ShowWindow(TreeFrame3, State);
	ShowWindow(APTomeButton, State);


	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::ActivateEnhancementWindow()
	{
	
	string Text;
	ostringstream ss;
	ToolTipWindowClass *ToolTipWindow;

	//Center in current MainScreen
	int ParentX;
	int ParentY;

	RECT WindowRect;
	RECT ParentRect;
	int WindowX;
	int WindowY;

	GetWindowRect(ParentWindow, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top;
	GetWindowRect(EnhancementWindowHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(EnhancementWindowHandle, ParentWindow, ParentRect.left+(ParentX / 2) - (WindowX / 2), ParentRect.top+(ParentY / 2) - (WindowY / 2), 0, 0, SWP_NOSIZE);

	//


	ResetEnhancementWindow();	//lets clear all the variables
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	//set our total AP  vairables based on characterlevel
	if (CharacterLevel <21)
		LevelAP = CharacterLevel *4;
	else
		LevelAP = 80; //this is max attainable action points
	//Check for Race Past Life Action Points
	RaceAP = Character.GetRaceEnhancement();
	
	if (CharacterEnhancements->GetAPTome())
		RaceAP += 1;

	if (RaceAP > 0)
	{
		RaceAPAvailable = RaceAP;
	}
	else
	{
		RaceAPAvailable = 0;
	}
	LevelAPAvailable = LevelAP;
	LevelAPAvailable += RaceAPAvailable;
	TotalAPSpent = 0;

	//Lets set our ClassProgression so we know what classes player took at what levels
	for (int x=0; x<CharacterLevel; x++)
		{
		ClassProgression.push_back(Character.GetClass(x + 1, false));
		}

	//Get Character Info

	FirstTime = true;
	for (int i=0; i<7; i++)
		{
		if (CharacterEnhancements->GetTreeIndex(i) != ENHT_NOTREE)
			FirstTime = false;
		}

	if (FirstTime == true)
		SetChosenEnhancementsNew();
	else
		SetChosenEnhancementsExisting();

	//Set the Current trees to the first 3 Chosen Trees.
	UpdateCurrentTrees("New");
	
	//Set the APRemaing & APSpent Labels
	if (RaceAP < APSpentTree[0])
		RaceAPSpent = RaceAPAvailable;
	else
		RaceAPSpent = APSpentTree[0];
	
	RaceAPAvailable -= RaceAPSpent;
	for (unsigned int i=0; i<7; i++)
		{
		TotalAPSpent += APSpentTree[i];
		}
	LevelAPAvailable -= TotalAPSpent;

	if (Character.GetRaceEnhancement() > 0)
	{
		UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
		UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
	}
	else
	{
		UpdateAPSpentLabel(TotalAPSpent);
		UpdateAPAvailableLabel(LevelAPAvailable);
	}

	SessionAPSpentTotal = 0;
	for (int i=0; i<7; i++)
		SessionAPSpentTree[i] = 0;

	//LoadGraphics(EnhancementWindowHandle);

	EnableWindow(AcceptButton, false);

	//set the confining window for the tooltips
	ToolTipWindow = InterfaceManager.GetToolTipWindowPointer();
	ToolTipWindow->SetConfiningWindow(EnhancementWindowHandle);

	ToolTipTree = -1;
	ToolTipLevel = -1;
	ToolTipSlot = -1;
	if (CharacterEnhancements->GetAPTome())
		SendMessage(APTomeButton, BM_SETCHECK, BST_CHECKED, 1);
	else
		SendMessage(APTomeButton, BM_SETCHECK, BST_UNCHECKED, 1);
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::ActivateMultiWindow(int Tree, int Level, int Slot)
	{
	ShowTooTipWindow(false);
	UpdateWindow(EnhancementWindowHandle);
	InterfaceManager.ActivateMultiEnhancementWindow(Tree, Level, Slot, LevelAPAvailable);
	InterfaceManager.ShowChild(MULTIENHANCEMENTWINDOW, true);
	MultiEnhancementWindowVisible = true;
	UpdateWindow(EnhancementWindowHandle);
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::Accept()
	{
	if (FirstTime == true)
		SaveCharacterEnhancementsNew();
	else
		SaveCharacterEnhancementsExisting();
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::CalculateAPSpentInTree(int Tree)
	{
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::ChangeTree(int TreeIndex)
	{
	Character_Enhancements_Class *CharacterEnhancements;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	int NumofMultiEnhancements;
	HDC hdc;
	int Tree;
	int xTree;

	Tree = TreeChanging;
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	hdc = GetDC(EnhancementWindowHandle);

	//Lets Change our Trees
	ChosenTrees[CurrentStartingTree + Tree] = ENHANCEMENT_TREE(TreeIndex);
	CurrentTree[Tree] = ENHANCEMENT_TREE(TreeIndex);
	if (FirstTime != true)
		CharacterEnhancements->SetTreeIndex(CurrentStartingTree+Tree, ENHANCEMENT_TREE(TreeIndex));

	//Lets Clear our TreeSlotData
	for (unsigned int y=0; y<6; y++)
		{
		for (unsigned int z=0; z<6; z++)
			{
			CurrentTreeSlots[Tree][y][z].Valid = false;
			CurrentTreeSlots[Tree][y][z].Active = false;
			CurrentTreeSlots[Tree][y][z].MultiSelection = false;
			CurrentTreeSlots[Tree][y][z].EnhancementIndex.clear();
			CurrentTreeSlots[Tree][y][z].EnhancementIndexChosen = 0;
			CurrentTreeSlots[Tree][y][z].Cost = 0;
			CurrentTreeSlots[Tree][y][z].Ranks = 0;
			CurrentTreeSlots[Tree][y][z].RanksTaken = 0;
			CurrentTreeSlots[Tree][y][z].RanksTakenOld = 0;
			
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].Valid = false;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].Active = false;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].MultiSelection = false;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].EnhancementIndex.clear();
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].EnhancementIndexChosen = 0;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].Cost = 0;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].Ranks = 0;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].RanksTaken = 0;
			ChosenTreeSlots[CurrentStartingTree + Tree][y][z].RanksTakenOld = 0;
			}
		}

	//Lets change our slots now
	EnhancementTree = Data.GetEnhancementTreePointer(ENHANCEMENT_TREE(TreeIndex));
	if (EnhancementTree->DoesTreeHaveEnhancements() == true)
		{
		//Lets set up our Current and Chosen Tree slots
		for (int xLevel=0; xLevel<6; xLevel++)
			{
			for (int xSlot=0; xSlot<6; xSlot++)
				{
				CurrentTreeSlots[Tree][xLevel][xSlot].Valid = EnhancementTree->DoesSlotHaveEnhancement(xLevel, xSlot);
				ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].Valid = EnhancementTree->DoesSlotHaveEnhancement(xLevel, xSlot);
				if (CurrentTreeSlots[Tree][xLevel][xSlot].Valid == true)
					{
					Enhancement = EnhancementTree->GetEnhancementPointer(xLevel, xSlot);
					CurrentTreeSlots[Tree][xLevel][xSlot].Active = Enhancement->GetEnhTypeActive();
					ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].Active = Enhancement->GetEnhTypeActive();
					if (Enhancement->GetEnhMultiSelection() == true)
						{
						CurrentTreeSlots[Tree][xLevel][xSlot].MultiSelection = true;
						ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].MultiSelection = true;
						CurrentTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.push_back(Data.GetEnhMultiSelectorIndex(Enhancement->GetEnhMultiName()));
						ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].EnhancementIndex.push_back(Data.GetEnhMultiSelectorIndex(Enhancement->GetEnhMultiName()));
						NumofMultiEnhancements = EnhancementTree->GetMultiEnhancementsSize(Enhancement->GetEnhancementIndex());
						for (int x=1; x<=NumofMultiEnhancements; x++)
							{
							CurrentTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.push_back(EnhancementTree->GetEnhancementIndex(xLevel, xSlot, x));
							ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].EnhancementIndex.push_back(EnhancementTree->GetEnhancementIndex(xLevel, xSlot, x));
							}
						}
					else
						{
						CurrentTreeSlots[Tree][xLevel][xSlot].MultiSelection = false;
						ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].MultiSelection = false;
						CurrentTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.push_back(Enhancement->GetEnhancementIndex());
						ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].EnhancementIndex.push_back(Enhancement->GetEnhancementIndex());
						}
					CurrentTreeSlots[Tree][xLevel][xSlot].EnhancementIndexChosen = 0;
					ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].EnhancementIndexChosen = 0;
					CurrentTreeSlots[Tree][xLevel][xSlot].Cost = Enhancement->GetEnhancementCost();
					ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].Cost = Enhancement->GetEnhancementCost();
					CurrentTreeSlots[Tree][xLevel][xSlot].Ranks = Enhancement->GetEnhancementRanks();
					ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].Ranks = Enhancement->GetEnhancementRanks();
					CurrentTreeSlots[Tree][xLevel][xSlot].RanksTaken = 0;
					ChosenTreeSlots[CurrentStartingTree + Tree][xLevel][xSlot].RanksTaken = 0;
					}
				}
			}
		//ok lets setup our Character Slots if not New Enhancements
		if (FirstTime == false)
			{
			xTree = (CurrentStartingTree + Tree);
			for (int xLevel=0; xLevel<6; xLevel++)
				{
				for (int xSlot=0; xSlot<6; xSlot++)
					{
					CharacterEnhancements->SetValid(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].Valid);
					for (unsigned int index=0; index<ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndex.size(); index++)
						{
						CharacterEnhancements->SetEnhancementIndex(xTree, xLevel, xSlot, index, ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndex[index]);
						}
					CharacterEnhancements->SetEnhancementIndexChosen(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen);
					CharacterEnhancements->SetRanksTaken(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken);
					for (int index=0; index<ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken; index++)
						{
						CharacterEnhancements->SetLevelTaken(xTree, xLevel, xSlot, index, 0);
						}
					}
				}
			}
		}

	DrawTree(hdc, Tree);
	UpdateWindow(EnhancementWindowHandle);
	ReleaseDC(EnhancementWindowHandle, hdc);
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::ClearCurrentTreeSlots(int Tree)
	{
	for (int xLevel = 0; xLevel<6; xLevel++)
		{
		for (int xSlot = 0; xSlot<6; xSlot++)
			{
			CurrentTreeSlots[Tree][xLevel][xSlot].Valid = false;
			CurrentTreeSlots[Tree][xLevel][xSlot].Active = false;
			CurrentTreeSlots[Tree][xLevel][xSlot].MultiSelection = false;
			CurrentTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.clear();
			CurrentTreeSlots[Tree][xLevel][xSlot].EnhancementIndexChosen = 0;
			CurrentTreeSlots[Tree][xLevel][xSlot].Ranks = 0;
			CurrentTreeSlots[Tree][xLevel][xSlot].RanksTaken = 0;
			CurrentTreeSlots[Tree][xLevel][xSlot].RanksTakenOld = 0;
			}
		}
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::ClearChosenTreeSlots(int Tree)
	{
	for (int xLevel = 0; xLevel<6; xLevel++)
		{
		for (int xSlot = 0; xSlot<6; xSlot++)
			{
			ChosenTreeSlots[Tree][xLevel][xSlot].Valid = false;
			ChosenTreeSlots[Tree][xLevel][xSlot].Active = false;
			ChosenTreeSlots[Tree][xLevel][xSlot].MultiSelection = false;
			ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.clear();
			ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndexChosen = 0;
			ChosenTreeSlots[Tree][xLevel][xSlot].Ranks = 0;
			ChosenTreeSlots[Tree][xLevel][xSlot].RanksTaken = 0;
			ChosenTreeSlots[Tree][xLevel][xSlot].RanksTakenOld = 0;
			}
		}
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::CopyChosenTreeSlots(int DestTree, int TreetoCopy)
	{
	for (int xLevel = 0; xLevel<6; xLevel++)
		{
		for (int xSlot = 0; xSlot<6; xSlot++)
			{
			ChosenTreeSlots[DestTree][xLevel][xSlot].Valid = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].Valid;
			ChosenTreeSlots[DestTree][xLevel][xSlot].Active = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].Active;
			ChosenTreeSlots[DestTree][xLevel][xSlot].MultiSelection = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].MultiSelection;
			for (unsigned int xIndex = 0; xIndex<ChosenTreeSlots[TreetoCopy][xLevel][xSlot].EnhancementIndex.size(); xIndex++)
				{
				ChosenTreeSlots[DestTree][xLevel][xSlot].EnhancementIndex.push_back(ChosenTreeSlots[TreetoCopy][xLevel][xSlot].EnhancementIndex[xIndex]);
				}
			ChosenTreeSlots[DestTree][xLevel][xSlot].EnhancementIndexChosen = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].EnhancementIndexChosen;
			ChosenTreeSlots[DestTree][xLevel][xSlot].Ranks = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].Ranks;
			ChosenTreeSlots[DestTree][xLevel][xSlot].RanksTaken = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].RanksTaken;
			ChosenTreeSlots[DestTree][xLevel][xSlot].RanksTakenOld = ChosenTreeSlots[TreetoCopy][xLevel][xSlot].RanksTakenOld;
			}
		}
	}

//-------------------------------------------------------------------------------------
void EnhancementWindowClass::FillSelectTreeList(int Tree)
	{
	Data_Enhancement_Tree_Class *EnhancementTree;
	bool AddtoList;
	ShowWindow(SelectTreeList, false);
	EnhancementTree = Data.GetEnhancementTreePointer(CurrentTree[Tree]);
	//Lets make sure what we clicked on is Valid
	if (APSpentTree[CurrentStartingTree + Tree] == 0 && (CurrentStartingTree + Tree )!=0 && EnhancementTree->GetTreeIndex() != ENHT_NOTREE)
		{
		SendMessage(SelectTreeList, LB_RESETCONTENT, 0, 0);
		for (unsigned int i=0; i<PossibleTrees.size(); i++)
			{
			AddtoList = true;
			for (int j=0; j<7; j++)
				{
				if (ChosenTrees[j] == PossibleTrees[i])
					{
					AddtoList = false;
					break;
					}
				}
			if (AddtoList == true)
				SendMessage(SelectTreeList, LB_ADDSTRING, 0, PossibleTrees[i]);
			}
		if (EnhancementTree->GetTreeIndex() != ENHT_UNSET)
			SendMessage(SelectTreeList, LB_ADDSTRING, 0, ENHT_UNSET);
		if (Tree == 0)
			MoveWindow(SelectTreeList, 55, 466, 162, 60, false);
		else if (Tree == 1)
			MoveWindow(SelectTreeList, 365, 466, 162, 60, false);
		else
			MoveWindow(SelectTreeList, 675, 466, 162, 60, false);
		ShowWindow(SelectTreeList, true);
		EnableWindow(Respec, false);
		EnableWindow(ResetAllTreesButton, false);
		EnableWindow(CancelButton, false);
		EnableWindow(AcceptButton, false);
		EnableWindow(APTomeButton, false);
		}
	else
	{
		ShowWindow(SelectTreeList, false);
		EnableWindow(Respec, true);
		EnableWindow(ResetAllTreesButton, true);
		EnableWindow(CancelButton, true);
		EnableWindow(AcceptButton, true);
		EnableWindow(APTomeButton, true);
	}

	}

//-------------------------------------------------------------------------------------
bool EnhancementWindowClass::FindPossibleTree(ENHANCEMENT_TREE EnhancementTree)
	{
	for (unsigned int i=0; i<PossibleTrees.size(); i++)
		{
		if (EnhancementTree == PossibleTrees[i])
			return true;
		}
	return false;
	}

//-------------------------------------------------------------------------------------
unsigned int EnhancementWindowClass::GetCurrentStartingTree()
	{
	return CurrentStartingTree;
	}

//-------------------------------------------------------------------------------------
ENHANCEMENT_TREE EnhancementWindowClass::GetCurrentTreeEnhancementTree(int Tree)
	{
	return CurrentTree[Tree];
	}

//-------------------------------------------------------------------------------------

unsigned int EnhancementWindowClass::GetCurrentTreeSlotsEnhancementIndex(int Tree, int Level, int Slot, unsigned int Index)
	{
	return CurrentTreeSlots[Tree][Level][Slot].EnhancementIndex[Index];
	}

//-------------------------------------------------------------------------------------
unsigned int EnhancementWindowClass::GetCurrentTreeSlotsEnhancementIndexSize(int tree, int level, int slot)
	{
	return CurrentTreeSlots[tree][level][slot].EnhancementIndex.size();
	}

//---------------------------------------------------------------------------
EnhancementWindowClass* EnhancementWindowClass::GetPointer()
	{
	return this;
	}

//---------------------------------------------------------------------------
HWND EnhancementWindowClass::GetHandle()
	{
	return EnhancementWindowHandle;
	}

//---------------------------------------------------------------------------
bool EnhancementWindowClass::IsChildWindowVisible()
	{
	return MultiEnhancementWindowVisible;
	}

//---------------------------------------------------------------------------
bool EnhancementWindowClass::IsSlotSelected(int x, int y, int *rTree, int *rLevel, int *rSlot)
	{
	bool SlotSelected;

	SlotSelected = false;

	for (int xtree=0; xtree<3; xtree++)
		{
		if (x > BackgroundLeft[xtree] && x < (BackgroundLeft[xtree]+BackgroundWidth) && y > BackgroundTop && y < (BackgroundTop + BackgroundHeight))
			{
			// ok we are in a tree, so lets get our level now
			*rTree = xtree;
			for (int xlevel=0; xlevel<6; xlevel++)
				{
				if (xlevel == 0)
					{
					if (y > SlotTop[xlevel] && y < (SlotTop[xlevel]+SlotCoreHeight))
						{ // ok we are in a core level so lets get our slot now
						*rLevel = 0;
						for (int xslot=0; xslot<6; xslot++)
							{
							if (x > SlotCoreLeft[xtree][xslot] && x < (SlotCoreLeft[xtree][xslot]+SlotCoreWidth))
								// ok we find our slot location
								{
								SlotSelected = true;
								*rSlot = xslot;
								break;
								}
							}
						break;
						}
					}
				else
					{
					if (y >SlotTop[xlevel] && y <(SlotTop[xlevel]+SlotHeight))
						{  // ok were in Level 1-5, so lets get our slot now
						*rLevel = xlevel;
						for (int xslot=0; xslot<5; xslot++)
							{
							if (x > SlotLeft[xtree][xslot] && x < (SlotLeft[xtree][xslot]+SlotWidth))
								//ok we found our slot location
								{
								SlotSelected = true;
								*rSlot = xslot;
								break;
								}
							}
						break;
						}
					}
				}
			}
		}
	return SlotSelected;
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::LoadGraphics(HWND Parent)
	{
	HDC hdc;

	//palteee for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	LoadBitmap("EmptyActiveCore", "UserInterface", &EmptyActiveCore);
	LoadBitmap("EmptyPassiveCore", "UserInterface", &EmptyPassiveCore);
	LoadBitmap("EmptyActiveTree", "UserInterface", &EmptyActiveTree);
	LoadBitmap("EmptyPassiveTree", "UserInterface", &EmptyPassiveTree);
	LoadBitmap("ScrollRight", "UserInterface", &ScrollRight);
	LoadBitmap("ScrollLeft", "UserInterface", &ScrollLeft);
	LoadBitmap("SlotActiveAvailable", "UserInterface", &IconActiveAvailable);
	LoadBitmap("SlotActiveNotAvailable", "UserInterface", &IconActiveUnavailable);
	LoadBitmap("SlotPassiveAvailable", "UserInterface", &IconPassiveAvailable);
	LoadBitmap("SlotPassiveNotAvailable", "UserInterface", &IconPassiveUnavailable);
	LoadBitmap("EnhancementActiveNotAllowed", "UserInterface", &SlotActiveNotAllowed);
	LoadBitmap("EnhancementPassiveNotAllowed", "UserInterface", &SlotPassiveNotAllowed);
	LoadBitmap("EnhancementArrowLeft", "UserInterface", &ArrowLeft);
	LoadBitmap("EnhancementArrowRight", "UserInterface", &ArrowRight);
	LoadBitmap("EnhancementArrowUp", "UserInterface", &ArrowUp1);
	LoadBitmap("EnhancementArrowUpLong", "UserInterface", &ArrowUp2);
	LoadBitmap("DropDownFrame", "UserInterface", &DropDownFrame);
	LoadBitmap("CoreEnhancement", "UserInterface", &CoreEnhancementFrame);
	LoadBitmap("ResetTreeOn", "UserInterface", &ResetTreeButtonOn);
	LoadBitmap("ResetTreeOff", "UserInterface", &ResetTreeButtonOff);
	LoadBitmap("LevelBoxBlue", "UserInterface", &BlueLevelBox);
	LoadBitmap("LevelBoxGreen", "UserInterface", &GreenLevelBox);
	LoadBitmap("LevelBoxRed", "UserInterface", &RedLevelBox);
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::DeleteGraphics()
    {
    DeleteObject(EmptyActiveCore.Graphic);
    DeleteObject(EmptyActiveCore.Mask);
	DeleteObject(EmptyActiveTree.Graphic);
    DeleteObject(EmptyActiveTree.Mask);
    DeleteObject(EmptyPassiveCore.Graphic);
    DeleteObject(EmptyPassiveCore.Mask);
    DeleteObject(EmptyPassiveTree.Graphic);
    DeleteObject(EmptyPassiveTree.Mask);
	DeleteObject(ScrollRight.Graphic);
    DeleteObject(ScrollRight.Mask);
    DeleteObject(ScrollLeft.Graphic);
    DeleteObject(ScrollLeft.Mask);
	DeleteObject(IconActiveAvailable.Graphic);
	DeleteObject(IconActiveAvailable.Mask);
	DeleteObject(IconActiveUnavailable.Graphic);
	DeleteObject(IconActiveUnavailable.Mask);
	DeleteObject(IconPassiveAvailable.Graphic);
	DeleteObject(IconPassiveAvailable.Mask);
	DeleteObject(IconPassiveUnavailable.Graphic);
	DeleteObject(IconPassiveUnavailable.Mask);
	DeleteObject(SlotActiveNotAllowed.Graphic);
	DeleteObject(SlotActiveNotAllowed.Mask);
	DeleteObject(SlotPassiveNotAllowed.Graphic);
	DeleteObject(SlotPassiveNotAllowed.Mask);
	DeleteObject(ArrowLeft.Graphic);
	DeleteObject(ArrowLeft.Mask);
	DeleteObject(ArrowRight.Graphic);
	DeleteObject(ArrowRight.Mask);
	DeleteObject(ArrowUp1.Graphic);
	DeleteObject(ArrowUp1.Mask);
	DeleteObject(ArrowUp2.Graphic);
	DeleteObject(ArrowUp2.Mask);
	DeleteObject(DropDownFrame.Graphic);
	DeleteObject(DropDownFrame.Mask);
	DeleteObject(CoreEnhancementFrame.Graphic);
	DeleteObject(CoreEnhancementFrame.Mask);
	DeleteObject(ResetTreeButtonOn.Graphic);
	DeleteObject(ResetTreeButtonOn.Mask);
	DeleteObject(ResetTreeButtonOff.Graphic);
	DeleteObject(ResetTreeButtonOff.Mask);

    DeleteObject(Palette);
    }

//---------------------------------------------------------------------------
void EnhancementWindowClass::ResetEnhancementWindow()
	{
	for (unsigned int i=0; i<7; i++)
		APSpentTree[i] = 0;
	ClassProgression.clear();
	for (unsigned int i=0; i<3; i++)
		{
		CurrentTree[i] = ENHT_UNKNOWN;
		CurrentLevel5TreeLock[i] = false;
		}
	for (unsigned int i=0; i<7; i++)
		{
		ChosenTrees[i] = ENHT_NOTREE;
		ChosenLevel5TreeLock[i] = false;
		}
	PossibleTrees.clear();
	CurrentStartingTree = 0;
	for (unsigned int x=0; x<3; x++)
		{
		for (unsigned int y=0; y<6; y++)
			{
			for (unsigned int z=0; z<6; z++)
				{
				CurrentTreeSlots[x][y][z].Valid = false;
				CurrentTreeSlots[x][y][z].Active = false;
				CurrentTreeSlots[x][y][z].MultiSelection = false;
				CurrentTreeSlots[x][y][z].EnhancementIndex.clear();
				CurrentTreeSlots[x][y][z].EnhancementIndexChosen = 0;
				CurrentTreeSlots[x][y][z].Cost = 0;
				CurrentTreeSlots[x][y][z].Ranks = 0;
				CurrentTreeSlots[x][y][z].RanksTaken = 0;
				CurrentTreeSlots[x][y][z].RanksTakenOld = 0;
				}
			}
		}
	for (unsigned int x=0; x<7; x++)
		{
		for (unsigned int y=0; y<6; y++)
			{
			for (unsigned int z=0; z<6; z++)
				{
				ChosenTreeSlots[x][y][z].Valid = false;
				ChosenTreeSlots[x][y][z].Active = false;
				ChosenTreeSlots[x][y][z].MultiSelection = false;
				ChosenTreeSlots[x][y][z].EnhancementIndex.clear();
				ChosenTreeSlots[x][y][z].EnhancementIndexChosen = 0;
				ChosenTreeSlots[x][y][z].Cost = 0;
				ChosenTreeSlots[x][y][z].Ranks = 0;
				ChosenTreeSlots[x][y][z].RanksTaken = 0;
				ChosenTreeSlots[x][y][z].RanksTakenOld = 0;
				}
			}
		}
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::RemoveSpecialTree(ENHANCEMENT_TREE ENHT_Tree)
	{
	int Tree;
	int ChosenTree;
	int CharacterTree;
	Character_Enhancements_Class *CharacterEnhancements;

	//Lets delete this tree from our PossibleTrees List
	for (unsigned int i=0; i<PossibleTrees.size(); i++)
		{
		if (PossibleTrees[i] == ENHT_Tree)
			{
			PossibleTrees.erase(PossibleTrees.begin()+i);
			break;
			}
		}
	//Lets get our Local variables
	ChosenTree = -1;
	for (int i=0; i<7; i++)
		{
		if (ChosenTrees[i] == ENHT_Tree)
			{
			ChosenTree = i;
			break;
			}
		}
	Tree = -1;
	for (int i=0; i<3; i++)
		{
		if (CurrentTree[i] == ENHT_Tree)
			{
			Tree = i;
			break;
			}
		}
	CharacterTree = -1;
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	for (int i=0; i<7; i++)
		{
		if (CharacterEnhancements->GetTreeIndex(i) == ENHT_Tree)
			{
			CharacterTree = i;
			break;
			}
		}
	//Reset our Chosen Treeslots where needed.
	if (ChosenTree != -1)
		{
		if (PossibleTrees.size() > 6)
			{
			//Set Tree to Unset Tree
			ChosenTrees[ChosenTree] = ENHT_UNSET;
			ClearChosenTreeSlots(ChosenTree);
			LoadChosenTreeSlots(ChosenTree, true);
			}
		else
			{
			// we need to move trees.
			for (int x=ChosenTree; x<7; x++)
				{
				if (x != 6)
					{
					ChosenTrees[x] = ChosenTrees[x+1];
					ClearChosenTreeSlots(x);
					CopyChosenTreeSlots(x, x+1);
					}
				else
					{
					ClearChosenTreeSlots(x);
					ChosenTrees[x] = ENHT_NOTREE;
					LoadChosenTreeSlots(x, true);
					}
				}
			}
		}
	//Reset our CharacterTreeSlots where needed
	if (CharacterTree != -1)
		{
		if (PossibleTrees.size() > 6)
			{
			//Set Tree to Unset Tree
			CharacterEnhancements->SetTreeIndex(CharacterTree, ENHT_UNSET);
			CharacterEnhancements->ClearCharacterEnhancementSlots(CharacterTree);
			}
		else
			{
			// we need to move trees.
			for (int x=CharacterTree; x<7; x++)
				{
				if (x !=6)
					{
					CharacterEnhancements->SetTreeIndex(x, CharacterEnhancements->GetTreeIndex(x+1));
					CharacterEnhancements->ClearCharacterEnhancementSlots(x);
					CharacterEnhancements->CopyCharacterEnhancementSlots(x, x+1);
					}
				else
					{
					CharacterEnhancements->ClearCharacterEnhancementSlots(x);
					CharacterEnhancements->SetTreeIndex(x, ENHT_NOTREE);
					}
				}
			}
		}
	//Reset Current Trees if needed
	if (Tree != -1)
		UpdateCurrentTrees("New");

	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::ResetAllTrees()
	{
	//This is for resetting the points spent for All trees, not just this
	//session. so we need to change the Current, Chosen & Character info.
	Character_Enhancements_Class *CharacterEnhancements;
	HDC hdc;

	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	hdc = GetDC(EnhancementWindowHandle);
	//We need to remove any special trees
	if (ChosenTrees[0] == ENHT_ELF || ChosenTrees[0] == ENHT_HALF_ELF || ChosenTrees[0] == ENHT_MORNINGLORD)
		{
		if(FindPossibleTree(ENHT_ARCANE_ARCHER_ELF) == true)
			RemoveSpecialTree(ENHT_ARCANE_ARCHER_ELF);
		}

	//Lets modify our Total Variables
	LevelAPAvailable = LevelAP;
	RaceAPAvailable = RaceAP;
	RaceAPSpent = 0;
	TotalAPSpent = 0;
	SessionAPSpentTotal = 0;
	//lets reset our Tree stuff
	for (int xTree=0; xTree<7; xTree++)
		{
		APSpentTree[xTree] = 0;
		SessionAPSpentTree[xTree] = 0;
		if (xTree<3)
			CurrentLevel5TreeLock[xTree] = false;
		ChosenLevel5TreeLock[xTree] = false;
		CharacterEnhancements->SetLevel5Lock(xTree, false);
		for (int xLevel=0; xLevel<6; xLevel++)
			{
			for (int xSlot=0; xSlot<6; xSlot++)
				{
				//Current Tree Stuff
				if (xTree <3)
					{
					CurrentTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen =0;
					CurrentTreeSlots[xTree][xLevel][xSlot].RanksTaken =0;
					CurrentTreeSlots[xTree][xLevel][xSlot].RanksTakenOld =0;
					}
				//Chosen Tree stuff
				ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen = 0;
				ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken = 0;
				ChosenTreeSlots[xTree][xLevel][xSlot].RanksTakenOld = 0;
				//Character Stuff
				CharacterEnhancements->SetEnhancementIndexChosen(xTree, xLevel, xSlot, 0);
				CharacterEnhancements->SetRanksTaken(xTree, xLevel, xSlot, 0);
				for (int i=0; i<3; i++)
					CharacterEnhancements->SetLevelTaken(xTree, xLevel, xSlot, i, 0);
				}
			}
		}
	
	//Update our Labels and graphics
	if (RaceAP > 0)
	{
		UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
		UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
	}
	else
	{
		UpdateAPAvailableLabel(LevelAPAvailable);
		UpdateAPSpentLabel(TotalAPSpent);
	}
	EnableWindow(AcceptButton, false);
	DrawGraphics(hdc);
	UpdateWindow(EnhancementWindowHandle);
	ReleaseDC(EnhancementWindowHandle, hdc);

	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::ResetAllAtLvlTrees(int CurrentLvl)
{


	Character_Enhancements_Class *CharacterEnhancements;
	HDC hdc;
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	hdc = GetDC(EnhancementWindowHandle);

	//We need to remove any special trees
	if (ChosenTrees[0] == ENHT_ELF)
	{
		if(CharacterEnhancements->GetRanksTaken(ENHT_ELF,3,4))
			if (CharacterEnhancements->GetLevelTaken(ENHT_ELF,3,4,1)>=CurrentLvl)
					RemoveSpecialTree(ENHT_ARCANE_ARCHER_ELF);
	}
	if (ChosenTrees[0] == ENHT_HALF_ELF)
	{
		if (CharacterEnhancements->GetRanksTaken(ENHT_HALF_ELF, 3, 4))
			if (CharacterEnhancements->GetLevelTaken(ENHT_HALF_ELF, 3, 4, 1) >= CurrentLvl)
				RemoveSpecialTree(ENHT_ARCANE_ARCHER_ELF);
	}
	if (ChosenTrees[0] == ENHT_MORNINGLORD)
	{
		if (CharacterEnhancements->GetRanksTaken(ENHT_MORNINGLORD, 3, 4))
			if (CharacterEnhancements->GetLevelTaken(ENHT_MORNINGLORD, 3, 4, 1) >= CurrentLvl)
				RemoveSpecialTree(ENHT_ARCANE_ARCHER_ELF);
	}
	//Lets modify our Total Variables
	LevelAPAvailable = LevelAP;
	RaceAPAvailable = RaceAP;
	RaceAPSpent = 0;
	TotalAPSpent = 0;
	SessionAPSpentTotal = 0;
	//lets reset our Character Tree stuff
	for (int xTree = 0; xTree < 7; xTree++)
	{

		CharacterEnhancements->SetLevel5Lock(xTree, false);
		for (int xLevel = 0; xLevel < 6; xLevel++)
		{
			for (int xSlot = 0; xSlot < 6; xSlot++)
			{
				for (int i = 2; i >=0; i--)
					//Character Stuff
					if (CharacterEnhancements->GetLevelTaken(xTree, xLevel, xSlot, i) >= CurrentLvl)
					{

						CharacterEnhancements->SetLevelTaken(xTree, xLevel, xSlot, i, 0);
						CharacterEnhancements->SetRanksTaken(xTree, xLevel, xSlot, i);
						if (i == 0)
						{
							CharacterEnhancements->SetEnhancementIndexChosen(xTree, xLevel, xSlot, 0);
						}
					}
			}
		}
	}
	//lets reset Visible trees based on Character Trees
	int TempEnhancementIndexChosen;
	int TempRanksTaken;

	for (int xTree = 0; xTree < 7; xTree++)
	{
		if (xTree < 3)
			CurrentLevel5TreeLock[xTree] = false;
		ChosenLevel5TreeLock[xTree] = false;
		for (int xLevel = 0; xLevel <6; xLevel++)
		{
			for (int xSlot = 0; xSlot < 6; xSlot++)
			{
				TempEnhancementIndexChosen = CharacterEnhancements->GetEnhancementIndexChosen(xTree, xLevel, xSlot);
				TempRanksTaken = CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot);
				//Current Tree Stuff
				if (xTree < 3)
				{
					if (xLevel == 5 && TempEnhancementIndexChosen > 0)
						CurrentLevel5TreeLock[xTree] = true;
					CurrentTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen = TempEnhancementIndexChosen;
					CurrentTreeSlots[xTree][xLevel][xSlot].RanksTaken = TempRanksTaken;
					CurrentTreeSlots[xTree][xLevel][xSlot].RanksTakenOld = TempRanksTaken;
				}
				//Chosen Tree stuff
				if (xLevel == 5 && TempEnhancementIndexChosen > 0)
					ChosenLevel5TreeLock[xTree] = true;
				ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen = TempEnhancementIndexChosen;
				ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken = TempRanksTaken;
				ChosenTreeSlots[xTree][xLevel][xSlot].RanksTakenOld = TempRanksTaken;
			}
		}
	}
	
	//lets Recalculate the points for spent
	int RankValue;
	int APTree;
	for (int xTree = 0; xTree < 7; xTree++)
	{
		APTree = 0;
		APSpentTree[xTree] = 0;
		SessionAPSpentTree[xTree] = 0;
		for (int xLevel = 0; xLevel < 6; xLevel++)
		{
			for (int xSlot = 0; xSlot < 6; xSlot++)
			{
				RankValue = CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot);
				
				if (CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot) > 0)
				{
					TempRanksTaken = CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot);
					RankValue = CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot);
					APTree += ChosenTreeSlots[xTree][xLevel][xSlot].Cost * RankValue;
					TotalAPSpent += ChosenTreeSlots[xTree][xLevel][xSlot].Cost * RankValue;
				}

			}
			APSpentTree[xTree] = APTree;
		}
		if (xTree == 0)
		{
			RaceAPSpent = TotalAPSpent;
			if (RaceAPSpent >= RaceAP)
				RaceAPSpent = RaceAP;
			RaceAPAvailable = RaceAP - RaceAPSpent;
		}
	}
	LevelAPAvailable = LevelAP + RaceAPSpent - TotalAPSpent;
	//Update our Labels and graphics
	if (RaceAP > 0)
	{
		UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
		UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
	}
	else
	{
		UpdateAPAvailableLabel(LevelAPAvailable);
		UpdateAPSpentLabel(TotalAPSpent);
	}
	EnableWindow(AcceptButton, false);
	DrawGraphics(hdc);
	UpdateWindow(EnhancementWindowHandle);
	ReleaseDC(EnhancementWindowHandle, hdc);

}

//---------------------------------------------------------------------------

void EnhancementWindowClass::ResetCurrentTree(int CurrentTree)
	{
	//This is for resetting the points spent for the whole tree, not just this
	//session. so we need to change the Current, Chosen & Character info.
	Character_Enhancements_Class *CharacterEnhancements;
	HDC hdc;
	bool TreeLock;
	bool DrawAllTrees;

	DrawAllTrees = false;
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	hdc = GetDC(EnhancementWindowHandle);
	//Lets see if we need to remove any special trees that added because of this tree
	if (CurrentTree == 0 && CurrentStartingTree == 0)
		{
		if (ChosenTrees[0] == ENHT_ELF || ChosenTrees[0] == ENHT_HALF_ELF || ChosenTrees[0] == ENHT_MORNINGLORD)
			{
			if(FindPossibleTree(ENHT_ARCANE_ARCHER_ELF) == true)
				RemoveSpecialTree(ENHT_ARCANE_ARCHER_ELF);
			}
		}

	//Lets modify our AP Variable before resetting the tree
	if ((CurrentStartingTree + CurrentTree) == 0)
	{
		LevelAPAvailable += RaceAP;
		RaceAPAvailable = RaceAP;
		RaceAPSpent = 0;
	}

	LevelAPAvailable += APSpentTree[CurrentStartingTree + CurrentTree];
	TotalAPSpent -= APSpentTree[CurrentStartingTree + CurrentTree];
	APSpentTree[CurrentStartingTree + CurrentTree] = 0;
	//lets see if we need to reset Tier 5 locks.
	TreeLock = false;
	for (int x=0; x<7; x++)
		{
		if (ChosenLevel5TreeLock[x] == true)
			TreeLock = true;
		}
	if (TreeLock == true)
		{
		if (CurrentLevel5TreeLock[CurrentTree] == false)
			{
			DrawAllTrees = true;
			for (int x=0; x<7; x++)
				{
				if (x<3)
					CurrentLevel5TreeLock[x] = false;
				ChosenLevel5TreeLock[x] = false;
				CharacterEnhancements->SetLevel5Lock(x, false);
				}
			}
		}

	//ok now lets reset our slot variables
	for (int xLevel=0; xLevel<6; xLevel++)
		{
		for (int xSlot=0; xSlot<6; xSlot++)
			{
			//Current Tree Stuff
			CurrentTreeSlots[CurrentTree][xLevel][xSlot].EnhancementIndexChosen =0;
			CurrentTreeSlots[CurrentTree][xLevel][xSlot].RanksTaken =0;
			CurrentTreeSlots[CurrentTree][xLevel][xSlot].RanksTakenOld =0;
			//Chosen Tree stuff
			ChosenTreeSlots[CurrentStartingTree + CurrentTree][xLevel][xSlot].EnhancementIndexChosen = 0;
			ChosenTreeSlots[CurrentStartingTree + CurrentTree][xLevel][xSlot].RanksTaken = 0;
			ChosenTreeSlots[CurrentStartingTree + CurrentTree][xLevel][xSlot].RanksTakenOld = 0;
			//Character Stuff
			CharacterEnhancements->SetEnhancementIndexChosen(CurrentStartingTree + CurrentTree, xLevel, xSlot, 0);
			CharacterEnhancements->SetRanksTaken(CurrentStartingTree + CurrentTree, xLevel, xSlot, 0);
			for (int i=0; i<3; i++)
				CharacterEnhancements->SetLevelTaken(CurrentStartingTree + CurrentTree, xLevel, xSlot, i, 0);
			}
		}
	//change our Session Variables
	SessionAPSpentTotal -= SessionAPSpentTree[CurrentStartingTree + CurrentTree];
	SessionAPSpentTree[CurrentStartingTree + CurrentTree] = 0;
	if((CurrentStartingTree + CurrentTree) == 0)
		SessionRaceSpent = 0;
	//Update our Labels and graphics
	if (RaceAP > 0)
	{
		UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
		UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
	}
	else
	{
		UpdateAPAvailableLabel(LevelAPAvailable);
		UpdateAPSpentLabel(TotalAPSpent);
	}

	if (DrawAllTrees == true)
		DrawGraphics(hdc);
	else
		DrawTree(hdc, CurrentTree);
	UpdateWindow(EnhancementWindowHandle);
	ReleaseDC(EnhancementWindowHandle, hdc);			
	}

//---------------------------------------------------------------------------
	bool EnhancementWindowClass::GetCurrentTreeLvl5Lockout(int CurrentTreeIndex)
	{
		return CurrentLevel5TreeLock[CurrentTreeIndex];
	}
//---------------------------------------------------------------------------
void EnhancementWindowClass::LoadChosenTreeSlots(int Tree, bool New)
	{
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Character_Enhancements_Class *CharacterEnhancements;
	int NumofMultiEnhancements;
	int RanksTaken;

	EnhancementTree = Data.GetEnhancementTreePointer(ChosenTrees[Tree]);
	if (New == false)
		CharacterEnhancements = Character.GetCharacterEnhancementsPointer();

	//Lets fill the Chosen Tree Slots now.
	if (EnhancementTree->DoesTreeHaveEnhancements() == true)
		{
		for (int xLevel=0; xLevel<6; xLevel++)
			{
			for (int xSlot=0; xSlot<6; xSlot++)
				{
				ChosenTreeSlots[Tree][xLevel][xSlot].Valid = EnhancementTree->DoesSlotHaveEnhancement(xLevel, xSlot);
				if (ChosenTreeSlots[Tree][xLevel][xSlot].Valid == true)
					{
					Enhancement = EnhancementTree->GetEnhancementPointer(xLevel, xSlot);
					ChosenTreeSlots[Tree][xLevel][xSlot].Active = Enhancement->GetEnhTypeActive();
					if (Enhancement->GetEnhMultiSelection() == true)
						{
						ChosenTreeSlots[Tree][xLevel][xSlot].MultiSelection = true;
						ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.push_back(Data.GetEnhMultiSelectorIndex(Enhancement->GetEnhMultiName()));
						NumofMultiEnhancements = EnhancementTree->GetMultiEnhancementsSize(Enhancement->GetEnhancementIndex());
						for (int x=1; x<=NumofMultiEnhancements; x++)
							{
							ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.push_back(EnhancementTree->GetEnhancementIndex(xLevel, xSlot, x));
							}
						}
					else
						{
						ChosenTreeSlots[Tree][xLevel][xSlot].MultiSelection = false;
						ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndex.push_back(Enhancement->GetEnhancementIndex());
						}
					ChosenTreeSlots[Tree][xLevel][xSlot].Cost = Enhancement->GetEnhancementCost();
					ChosenTreeSlots[Tree][xLevel][xSlot].Ranks = Enhancement->GetEnhancementRanks();
					if (New == false)
						{
						ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndexChosen = 0;
						ChosenTreeSlots[Tree][xLevel][xSlot].RanksTaken = 0;
						ChosenTreeSlots[Tree][xLevel][xSlot].RanksTakenOld = 0;
						}
					else
						{
						if ((RanksTaken = CharacterEnhancements->GetRanksTaken(Tree, xLevel, xSlot)) > 0)
							{
							for (int xRank=0; xRank<RanksTaken; xRank++)
								{
								if (CharacterEnhancements->GetLevelTaken(Tree, xLevel, xSlot, xRank) <= CharacterLevel)
									ChosenTreeSlots[Tree][xLevel][xSlot].RanksTaken ++;
								}
							if (ChosenTreeSlots[Tree][xLevel][xSlot].RanksTaken > 0)
								{
								ChosenTreeSlots[Tree][xLevel][xSlot].RanksTakenOld = ChosenTreeSlots[Tree][xLevel][xSlot].RanksTaken;
								ChosenTreeSlots[Tree][xLevel][xSlot].EnhancementIndexChosen = CharacterEnhancements->GetEnhancementIndexChosen(Tree, xLevel, xSlot);
								}
							}
						}
					}
				}
			}
		}
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::MultiEnhancementSelected(int Tree, int Level, int Slot, int Selection)
	{
	HDC hdc;
	int Cost;
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_Tree_Class *EnhancementTree;

	hdc = GetDC(EnhancementWindowHandle);

	EnhancementTree = Data.GetEnhancementTreePointer(ChosenTrees[CurrentStartingTree + Tree]);
	Enhancement = EnhancementTree->GetEnhancementPointer(CurrentTreeSlots[Tree][Level][Slot].EnhancementIndex[Selection]);
	if (Selection > 0)
		{
		CurrentTreeSlots[Tree][Level][Slot].EnhancementIndexChosen = Selection;
		CurrentTreeSlots[Tree][Level][Slot].RanksTaken = 1;
		//Cost = CurrentTreeSlots[Tree][Level][Slot].Cost;
		Cost = Enhancement->GetEnhancementCost();
		ChosenTreeSlots[CurrentStartingTree + Tree][Level][Slot].EnhancementIndexChosen = Selection;
		ChosenTreeSlots[CurrentStartingTree + Tree][Level][Slot].RanksTaken = 1;
		APSpentTree[CurrentStartingTree + Tree] += Cost;
		SessionAPSpentTree[CurrentStartingTree + Tree] += Cost;
		SessionAPSpentTotal += Cost;
		if ((CurrentStartingTree + Tree) == 0)
		{
			if (RaceAPAvailable > Cost)
			{
				RaceAPSpent += Cost;
			}
			else
			{
				if (RaceAPAvailable > 0)
				{
					RaceAPSpent = RaceAP;
				}

			}
			RaceAPAvailable = RaceAP - RaceAPSpent;
		}

		LevelAPAvailable -= Cost;
		TotalAPSpent += Cost;

		if (Level == 5)
			{
			//Since we are spending a point in a level 5 Slot, we need to lock out all other Level 5 Tree slots
			for (int x=0; x<3; x++)
				{
				if (x == Tree)
					CurrentLevel5TreeLock[x] = false;
				else
					CurrentLevel5TreeLock[x] = true;
				}
			for (int x=0; x<7; x++)
				{
				if (x == (CurrentStartingTree + Tree))
					ChosenLevel5TreeLock[x] = false;
				else 
					ChosenLevel5TreeLock[x] = true;
				}
			}
		if (RaceAP > 0)
		{
			UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
			UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
		}
		else
		{
			UpdateAPAvailableLabel(LevelAPAvailable);
			UpdateAPSpentLabel(TotalAPSpent);
		}

		if (Level == 5)
			DrawGraphics(hdc);
		else
			DrawTree(hdc, Tree);
		UpdateWindow(EnhancementWindowHandle);
		EnableWindow(AcceptButton, true);

		}

	ReleaseDC(EnhancementWindowHandle, hdc);
	}

//---------------------------------------------------------------------------
EnhancementSlotStruct* EnhancementWindowClass::GetEnhancementSlotData(int Tree, int Level, int Slot)
	{
	return &CurrentTreeSlots[Tree][Level][Slot];
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::SetChildWindowFlag(bool State)
	{
	MultiEnhancementWindowVisible = State;
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::SetChosenEnhancementsNew()
	{
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	int NumofMultiEnhancements;

	//Setup our PossibleTrees
	SetPossibleTrees();

	//lets take the first 7 possibletrees and add them to the ChosenTrees
	for (unsigned int i=0; i<7; i++)
		{
		if (i<PossibleTrees.size())
			{
			ChosenTrees[i] = PossibleTrees[i];
			//ChosenTree.push_back(PossibleTrees[i]);
			}
		else
			ChosenTrees[i] = ENHT_NOTREE;
		}

	//Lets fill the Chosen Tree Slots now.
	for (unsigned int xtree=0; xtree<7; xtree++)
		{
		APSpentTree[xtree] = 0;
		EnhancementTree = Data.GetEnhancementTreePointer(ChosenTrees[xtree]);
		for (int xlevel=0; xlevel<6; xlevel++)
			{
			if (xtree == 0 && xlevel == 5)	//race trees don't have 6 levels (Race tree is always chosen tree 0)
				break;
			for (int xslot=0; xslot<6; xslot++)
				{
				if (xlevel > 0 && xslot == 5) //levels 1-5 doesn't have 6 slots
					break;
				ChosenTreeSlots[xtree][xlevel][xslot].Valid = EnhancementTree->DoesSlotHaveEnhancement(xlevel, xslot);
				if (ChosenTreeSlots[xtree][xlevel][xslot].Valid == true)
					{
					Enhancement = EnhancementTree->GetEnhancementPointer(xlevel, xslot);
					ChosenTreeSlots[xtree][xlevel][xslot].Active = Enhancement->GetEnhTypeActive();
					if (Enhancement->GetEnhMultiSelection() == true)
						{
						ChosenTreeSlots[xtree][xlevel][xslot].MultiSelection = true;
						ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(Data.GetEnhMultiSelectorIndex(Enhancement->GetEnhMultiName()));
						NumofMultiEnhancements = EnhancementTree->GetMultiEnhancementsSize(Enhancement->GetEnhancementIndex());
						for (int x=1; x<=NumofMultiEnhancements; x++)
							{
							ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(EnhancementTree->GetEnhancementIndex(xlevel, xslot, x));
							}
						}
					else
						{
						ChosenTreeSlots[xtree][xlevel][xslot].MultiSelection = false;
						ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(Enhancement->GetEnhancementIndex());
						}
					ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndexChosen = 0;
					ChosenTreeSlots[xtree][xlevel][xslot].Cost = Enhancement->GetEnhancementCost();
					ChosenTreeSlots[xtree][xlevel][xslot].Ranks = Enhancement->GetEnhancementRanks();
					ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken = 0;
					APSpentTree[xtree] += (ChosenTreeSlots[xtree][xlevel][xslot].Cost * ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken);
					}
				}
			}
		}
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::SetChosenEnhancementsExisting()
	{
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	Character_Enhancements_Class *CharacterEnhancements;
	int NumofMultiEnhancements;
	ENHANCEMENT_TREE ENHT_Tree;
	int tempRanksTaken;
	int Cost;

	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();

	//Let set get our PossibleTrees
	SetPossibleTrees();

	//ok lets set up our ChosenTrees variable
	for (unsigned int i=0; i<7; i++)
		{
		ENHT_Tree = CharacterEnhancements->GetTreeIndex(i);
		if (ENHT_Tree != ENHT_NOTREE)
			{
			if (FindPossibleTree(ENHT_Tree))
				ChosenTrees[i] = ENHT_Tree;
			else
				{
				if (ENHT_Tree == ENHT_UNSET)
					ChosenTrees[i] = ENHT_Tree;
				else
					ChosenTrees[i] = ENHT_FUTURETREE;
				}
			}
		else
			{
			if (i>= PossibleTrees.size())
				ChosenTrees[i] = ENHT_NOTREE;
			else
				ChosenTrees[i] = ENHT_UNSET;
			}
		ChosenLevel5TreeLock[i] = CharacterEnhancements->GetLevel5Lock(i);
		}
	
	//ok now we can set up our ChosenTreeSlots
	for (unsigned int xtree=0; xtree<7; xtree++)
		{
		APSpentTree[xtree] = 0;
		EnhancementTree = Data.GetEnhancementTreePointer(ChosenTrees[xtree]);
		for (int xlevel=0; xlevel<6; xlevel++)
			{
			if (xtree == 0 && xlevel == 5)	//race trees don't have 6 levels (Race tree is always chosen tree 0)
				break;
			for (int xslot=0; xslot<6; xslot++)
				{
				if (xlevel > 0 && xslot == 5) //levels 1-5 doesn't have 6 slots
					break;
				ChosenTreeSlots[xtree][xlevel][xslot].Valid = EnhancementTree->DoesSlotHaveEnhancement(xlevel, xslot);
				if (ChosenTreeSlots[xtree][xlevel][xslot].Valid == true)
					{
					Enhancement = EnhancementTree->GetEnhancementPointer(xlevel, xslot);
					ChosenTreeSlots[xtree][xlevel][xslot].Active = Enhancement->GetEnhTypeActive();
					if (Enhancement->GetEnhMultiSelection() == true)
						{
						ChosenTreeSlots[xtree][xlevel][xslot].MultiSelection = true;
						ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(Data.GetEnhMultiSelectorIndex(Enhancement->GetEnhMultiName()));
						NumofMultiEnhancements = EnhancementTree->GetMultiEnhancementsSize(Enhancement->GetEnhancementIndex());
						for (int x=1; x<=NumofMultiEnhancements; x++)
							{
							ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(EnhancementTree->GetEnhancementIndex(xlevel, xslot, x));
							}
						}
					else
						{
						ChosenTreeSlots[xtree][xlevel][xslot].MultiSelection = false;
						ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(Enhancement->GetEnhancementIndex());
						}
					ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndexChosen = 0;
					ChosenTreeSlots[xtree][xlevel][xslot].Cost = Enhancement->GetEnhancementCost();
					ChosenTreeSlots[xtree][xlevel][xslot].Ranks = Enhancement->GetEnhancementRanks();
					ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken = 0;
					

					//Lets get our character data for this slot.
					if ((tempRanksTaken = CharacterEnhancements->GetRanksTaken(xtree, xlevel, xslot)) > 0)
						{
						for (int xRank=0; xRank <tempRanksTaken; xRank++)
							{
							if (CharacterEnhancements->GetLevelTaken(xtree, xlevel, xslot, xRank) <= CharacterLevel)
								ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken ++;
							}
						if (ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken > 0)
							{
							ChosenTreeSlots[xtree][xlevel][xslot].RanksTakenOld = ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken;
							ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndexChosen = CharacterEnhancements->GetEnhancementIndexChosen(xtree, xlevel, xslot);
							}
						}
					//now that we have our chosen slot set up we need to get the cost of the chosen enhancement if one was selected.
					if (ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndexChosen > 0)
						{
						Enhancement = EnhancementTree->GetEnhancementPointer(ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndex[ChosenTreeSlots[xtree][xlevel][xslot].EnhancementIndexChosen]);
						Cost = Enhancement->GetEnhancementCost();
						}
					else
						Cost = ChosenTreeSlots[xtree][xlevel][xslot].Cost;
					APSpentTree[xtree] += Cost * ChosenTreeSlots[xtree][xlevel][xslot].RanksTaken;
					}
				}
			}
		}
	}
//---------------------------------------------------------------------------

void EnhancementWindowClass::SetPossibleTrees()
	{
	CLASS ClassID[3];
	int ClassCount[3];
	vector <ENHANCEMENT_TREE> ClassTrees;
	Character_Enhancements_Class *CharacterEnhancements;

	//Lets add the Race Tree to PossibleTrees
	PossibleTrees.push_back(Data.GetRacialTree(Character.GetRace()));

	//Now lets add the class trees based on classes chosen
	ClassID[0] = ClassProgression[0];
	ClassCount[0] = 1;
	ClassCount[1] = 0;
	ClassCount[2] = 0;
	for (int x=1; x<CharacterLevel; x++)
		{
		for (int y=0; y<3; y++)
			{
			if (ClassCount[y] == 0)
				{
				ClassID[y] = ClassProgression[x];
				ClassCount[y]++;
				break;
				}
			else
				{
				if (ClassID[y] == ClassProgression[x])
					{
					ClassCount[y]++;
					break;
					}
				}
			}
		}

	for (unsigned int i=0; i<3; i++)
		{
		if (ClassCount[i] > 0)
			{
			ClassTrees.clear();
			Data.GetClassTrees(ClassTrees, ClassID[i]);
			for (unsigned int j=0; j<ClassTrees.size(); j++)
				{
				PossibleTrees.push_back(ClassTrees[j]);
				}
			}
		}
	//Ok we need to add any special trees if this is an exisiting character.
	if (FirstTime == false)
		{
		CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
		if (PossibleTrees[0] == ENHT_ELF || PossibleTrees[0] == ENHT_HALF_ELF || PossibleTrees[0] == ENHT_MORNINGLORD)  //Arcane Archer (Elf)
			{
			if (CharacterEnhancements->GetRanksTaken(0,3,4) > 0 && CharacterEnhancements->GetLevelTaken(0,3,4,0) <= CharacterLevel)
				PossibleTrees.push_back(ENHT_ARCANE_ARCHER_ELF);
			}
		}// AA ELF
		PossibleTrees.push_back(ENHT_HARPER_AGENT);// Add Harper Agent to List
		PossibleTrees.push_back(ENHT_VISTANIKNIFEFIGHTER); // Add Vistani Knife Fighter to List
	}

//-----------------------------------------------------------------------------------
void EnhancementWindowClass::UpdateAPAvailableLabel(int NewValue, int RaceAPValue)
	{
	string Text;
	ostringstream ss;
	ss.str("");

	if (RaceAPValue != -1)
	{
		ss << NewValue - RaceAPValue;
		ss << " AP Remaining,";
		ss << " ";
		ss << RaceAPValue;
		ss << " RP Remaining";
	}
	else
	{
		ss << NewValue;
		ss << " Action Points Remaining,";
	}


	Text = ss.str();
	SendMessage(APRemainingLabel, WM_SETTEXT, 0, (LPARAM)Text.c_str());
	}

//-----------------------------------------------------------------------------------
void EnhancementWindowClass::UpdateAPSpentLabel(int NewValue, int RaceAPValue)
	{
	string Text;
	ostringstream ss;
	
	ss.str("");

	if (RaceAPValue != -1)
	{
		ss << NewValue - RaceAPValue;
		ss << " AP Spent";
		ss << ", ";
		ss << RaceAPValue;
		ss << " RP Spent.";
	}
	else
	{
		ss << NewValue;
		ss << " Action Points Spent";
	}
	Text = ss.str();
	SendMessage(APSpentLabel, WM_SETTEXT, 0, (LPARAM)Text.c_str());
	}

//-----------------------------------------------------------------------------------
void EnhancementWindowClass::SaveCharacterEnhancementsExisting()
	{
	Character_Enhancements_Class *CharacterEnhancements;

	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();

	for (int xTree=0; xTree<7; xTree++)
		{
		CharacterEnhancements->SetLevel5Lock(xTree, ChosenLevel5TreeLock[xTree]);
		for (int xLevel=0; xLevel<6; xLevel++)
			{
			for (int xSlot=0; xSlot<6; xSlot++)
				{
				//Lets see if we spent points on this slot this time around
				if (ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken > ChosenTreeSlots[xTree][xLevel][xSlot].RanksTakenOld)
					{
					CharacterEnhancements->SetEnhancementIndexChosen(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen);
					//Lets set the Character Ranks Taken if it is lower than what we've chosen.
					if (ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken > CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot))
						CharacterEnhancements->SetRanksTaken(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken);
					//now we set the levels that took ranks at to CharacterLevel.
					for (int i=0; i<ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken; i++)
						{
						//only change the Levels for the Ranks we took this time around
						if (i >= ChosenTreeSlots[xTree][xLevel][xSlot].RanksTakenOld)
							{
							CharacterEnhancements->SetLevelTaken(xTree, xLevel, xSlot, i, CharacterLevel);
							}
						}
					}
				}  //end for xSlot
			} // end for xLevel
		}  //end for xtree
	}

//-----------------------------------------------------------------------------------
void EnhancementWindowClass::SaveCharacterEnhancementsNew()
	{
	//Since this is first time enhancements have been touched for this toon
	//we just need to do a simple copy of enhancement from here to the 
	//Character_Enhancements_Class.

	Character_Enhancements_Class *CharacterEnhancements;

	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	CharacterEnhancements->Clear();

	for (int xTree=0; xTree<7; xTree++)
		{
		CharacterEnhancements->SetTreeIndex(xTree, ChosenTrees[xTree]);
		CharacterEnhancements->SetLevel5Lock(xTree, ChosenLevel5TreeLock[xTree]);
		for (int xLevel=0; xLevel<6; xLevel++)
			{
			for (int xSlot=0; xSlot<6; xSlot++)
				{
				CharacterEnhancements->SetValid(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].Valid);
				for (unsigned int index=0; index<ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndex.size(); index++)
					{
					CharacterEnhancements->SetEnhancementIndex(xTree, xLevel, xSlot, index, ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndex[index]);
					}
				CharacterEnhancements->SetEnhancementIndexChosen(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].EnhancementIndexChosen);
				CharacterEnhancements->SetRanksTaken(xTree, xLevel, xSlot, ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken);
				for (int index=0; index<ChosenTreeSlots[xTree][xLevel][xSlot].RanksTaken; index++)
					{
					CharacterEnhancements->SetLevelTaken(xTree, xLevel, xSlot, index, CharacterLevel);
					}
				}
			}

		}
	}

//-----------------------------------------------------------------------------------
void EnhancementWindowClass::UpdateCurrentTrees(string Direction)
	{
	
	HDC ParentDC;

	ParentDC = GetDC(EnhancementWindowHandle);
	
	//lets Clear our Current Variables
	CurrentTree[0] = ENHT_UNKNOWN;
	CurrentTree[1] = ENHT_UNKNOWN;
	CurrentTree[2] = ENHT_UNKNOWN;
	for (int x=0; x<3; x++)
		{
		for (int y=0; y<6; y++)
			{
			for (int z=0; z<6; z++)
				{
				CurrentTreeSlots[x][y][z].Active = false;
				CurrentTreeSlots[x][y][z].Cost = 0;
				CurrentTreeSlots[x][y][z].EnhancementIndex.clear();
				CurrentTreeSlots[x][y][z].EnhancementIndexChosen =0;
				CurrentTreeSlots[x][y][z].MultiSelection = false;
				CurrentTreeSlots[x][y][z].Ranks = 0;
				CurrentTreeSlots[x][y][z].RanksTaken = 0;
				CurrentTreeSlots[x][y][z].RanksTakenOld = 0;
				CurrentTreeSlots[x][y][z].Valid = false;
				}
			}
		}

	if (Direction == "Right")	// Our trees are moving to the right
		CurrentStartingTree ++;
	if (Direction == "Left")	// Our trees are moving to the left
		CurrentStartingTree --;
	if (Direction == "New")		// First time window is open so set starting tree to 0;
		CurrentStartingTree = 0;

	//Now that we have our Starting Tree. lets fill the Currenttrees and slots
	CurrentTree[0] = ChosenTrees[CurrentStartingTree];
	CurrentTree[1] = ChosenTrees[CurrentStartingTree +1];
	CurrentTree[2] = ChosenTrees[CurrentStartingTree +2];
	//lets get our Level5 Lock values
	CurrentLevel5TreeLock[0] = ChosenLevel5TreeLock[CurrentStartingTree];
	CurrentLevel5TreeLock[1] = ChosenLevel5TreeLock[CurrentStartingTree +1];
	CurrentLevel5TreeLock[2] = ChosenLevel5TreeLock[CurrentStartingTree +2];

	for (int xtree=0; xtree<3; xtree++)
		{
		for (int xlevel=0; xlevel<6; xlevel++)
			{
			if (xtree == 0 && xlevel == 5 && CurrentStartingTree == 0) // we don't need to fill slot for the 6 level of race trees, which are always 0
				break;
			for (int xslot=0; xslot<6; xslot++)
				{
				if (xlevel > 0 && xslot == 5)
					break;
				CurrentTreeSlots[xtree][xlevel][xslot].Valid = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].Valid;
				CurrentTreeSlots[xtree][xlevel][xslot].Active = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].Active;
				CurrentTreeSlots[xtree][xlevel][xslot].MultiSelection = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].MultiSelection;
				for (unsigned int i=0; i<ChosenTreeSlots[xtree+CurrentStartingTree][xlevel][xslot].EnhancementIndex.size(); i++)
					{
					CurrentTreeSlots[xtree][xlevel][xslot].EnhancementIndex.push_back(ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].EnhancementIndex[i]);
					}

				CurrentTreeSlots[xtree][xlevel][xslot].EnhancementIndexChosen = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].EnhancementIndexChosen;
				CurrentTreeSlots[xtree][xlevel][xslot].Cost = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].Cost;
				CurrentTreeSlots[xtree][xlevel][xslot].Ranks = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].Ranks;
				CurrentTreeSlots[xtree][xlevel][xslot].RanksTaken = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].RanksTaken;
				CurrentTreeSlots[xtree][xlevel][xslot].RanksTakenOld = ChosenTreeSlots[xtree + CurrentStartingTree][xlevel][xslot].RanksTakenOld;
				}
			}
		}

	// ok now lets redraw all trees and associated graphics
	DrawGraphics(ParentDC);

	ReleaseDC(EnhancementWindowHandle, ParentDC);
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::DrawGraphics(HDC hdc)
	{
	DrawTree(hdc, 0);
	DrawTree(hdc, 1);
	DrawTree(hdc, 2);

	if (CurrentStartingTree < 4)
		DrawGraphic(hdc, &ScrollRight, 949, 200, 22, 90);
	
	if (CurrentStartingTree > 0)
		DrawGraphic(hdc, &ScrollLeft, 6, 200, 22, 90);

	DrawLevelBars(hdc);
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::DrawLevelBars(HDC hdc)
{
	COLORREF OldColor;
	ostringstream ss;
	UIComponentManager *UIManager;
	//InterfaceGraphicStruct *Graphic;
	int X, Y;

	int ButtonSpacing = 42;
	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER);
	X = 30;
	Y = 482;
	UIManager = InterfaceManager.GetUIComponents();
	for (unsigned int i = 0; i<30; i++)
	{

		EnhLevelX[i] = X;
		EnhLevelY[i] = Y;
		EnhLevelWidth = 40;
		EnhLevelHeight = 25;
		if (CharacterLevel == i + 1)
			DrawGraphic(hdc, &GreenLevelBox, X, Y, EnhLevelWidth, EnhLevelHeight);
		else
			DrawGraphic(hdc, &BlueLevelBox, X, Y, EnhLevelWidth, EnhLevelHeight);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "L" << i + 1;
		TextOut(hdc, X + 20, Y + 6, ss.str().c_str(), ss.str().size());
		SetTextColor(hdc, OldColor);
		if ((i+1)%10== 0)
		{
			X = 30;
			Y += 25;
		}
		else
		{
			X += ButtonSpacing;
		}
	}
	SetTextAlign(hdc, TA_LEFT);
}



//---------------------------------------------------------------------------
void EnhancementWindowClass::DrawSelectTreeListItem(HDC hdc, DWORD Item, long Top, long Left)
	{
	string Text;
	COLORREF OriginalColor;
	Data_Enhancement_Tree_Class *EnhancementTree;

	OriginalColor = SetTextColor(hdc, RGB(255, 255, 255));
	EnhancementTree = Data.GetEnhancementTreePointer(ENHANCEMENT_TREE(Item));
	Text = EnhancementTree->GetTreeName();

	TextOut(hdc, Left+10, Top+6, Text.c_str(), Text.size());
	SetTextColor(hdc, OriginalColor);
	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::DrawTree(HDC hdc, int tree)
	{
	COLORREF OldColor;
	HFONT OldFont;
	ostringstream ss;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_MultiSelector_Class *MultiEnhancement;
	GraphicStruct TempGraphic;
	GraphicStruct BorderGraphic;
	GraphicStruct IconGraphic;
	GraphicStruct SlotGraphic;
	bool tempFlag;
	int tempIndex;
	enum BorderColor {NoBorder, WhiteBorder, RedBorder, LockedBorder};
	BorderColor SlotBorderColor;
	ArrowStruct Arrow;
	int ArrowUp_Left[3][5] = {{55, 115, 175, 235, 295},
							  {365, 425, 485, 545, 605},
							  {675, 735, 795, 855, 915}};
	int ArrowUp_Top[5] = {358, 283, 213, 143, 73};
	int ArrowWidth = 14;
	int ArrowUp1Height = 15 + 2;
	int ArrowUp2Height = 86;
	int ArrowLRWidth = 13+2;
	int ArrowLRHeight = 14;
	int ArrowLRTop[6] = {395, 320, 250, 180, 110, 40};
	int ArrowLeft_Left[3][5] = {{24, 84, 144, 204, 264},
								{334, 394, 454, 514, 574},
								{644, 704, 764, 824, 884}};
	int ArrowRight_Left[3][5] = {{84, 144, 204, 264, 324},
								{394, 454, 514, 574, 634},
								{704, 764, 824, 884, 944}};
	int TreeAPAvailable;

	if (tree == 0)
	{
		TreeAPAvailable = LevelAPAvailable;
	}
	else
	{
		TreeAPAvailable = LevelAPAvailable - RaceAPAvailable;
	}
		
	//Draw the background image for the tree
	EnhancementTree = Data.GetEnhancementTreePointer(CurrentTree[tree]);
	DrawGraphic(hdc, &EnhancementTree->GetBackgroundGraphic(), BackgroundLeft[tree], BackgroundTop, BackgroundWidth, BackgroundHeight);

	//Draw the Arrows for the Tree
	for (unsigned int i=0; i<EnhancementTree->GetArrowPlacementSize(); i++)
		{
		Arrow = EnhancementTree->GetArrowPlacement(i);
		if (Arrow.Direction == AD_UP && Arrow.Length == 1)
			DrawGraphic(hdc, &ArrowUp1, ArrowUp_Left[tree][Arrow.Slot], ArrowUp_Top[Arrow.Level], ArrowWidth, ArrowUp1Height);
		if (Arrow.Direction == AD_UP && Arrow.Length == 2)
			DrawGraphic(hdc, &ArrowUp2, ArrowUp_Left[tree][Arrow.Slot], ArrowUp_Top[Arrow.Level+1], ArrowWidth, ArrowUp2Height);
		if (Arrow.Direction == AD_UP && Arrow.Length == 3)
			DrawGraphic(hdc, &ArrowUp2, ArrowUp_Left[tree][Arrow.Slot], ArrowUp_Top[Arrow.Level+2], ArrowWidth, ArrowUp2Height + 72);
		if (Arrow.Direction == AD_LEFT)
			DrawGraphic(hdc, &ArrowLeft, ArrowLeft_Left[tree][Arrow.Slot], ArrowLRTop[Arrow.Level], ArrowLRWidth, ArrowLRHeight);
		if (Arrow.Direction == AD_RIGHT)
			DrawGraphic(hdc, &ArrowRight, ArrowRight_Left[tree][Arrow.Slot], ArrowLRTop[Arrow.Level], ArrowLRWidth, ArrowLRHeight);
		}

	//Draw the Core Enhancement Frame
	if (EnhancementTree->DoesTreeHaveEnhancements() == true)
		DrawGraphic(hdc, &CoreEnhancementFrame, BackgroundLeft[tree]+5, BackgroundTop+356, 290, 71);
	
	SetBkMode(hdc, TRANSPARENT);
	OldFont = (HFONT)SelectObject(hdc, ArielFontSmall);

	//Draw our Icons
	for (int xlevel=0; xlevel<6; xlevel++)
		{
		for (int xslot=0; xslot<6; xslot++)
			{
			if (CurrentTreeSlots[tree][xlevel][xslot].Valid == true)
				{  //Ok lets get our IconGraphic & SlotBorderColor information
				if (CurrentTreeSlots[tree][xlevel][xslot].MultiSelection == true && CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndexChosen == 0)
					{  //this is a Multi-Enhancement Slot that hasnt' been chosen yet.
					MultiEnhancement = Data.GetMultiEnhancementPointer(CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndex[0]);
					IconGraphic = MultiEnhancement->GetIcon();
					//Lets find out what color border our Multi Enhancement Icon gets (Red, White, NoBorder)
					tempFlag = false;
					for (unsigned int j=1; j<CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndex.size(); j++)
						{
						Enhancement = EnhancementTree->GetEnhancementPointer(CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndex[j]);
						if (AreAllRequirementsMet(Enhancement) == true)
							{    //All the Requirements for an Enhancement were met so set out border color to White.
							if (CurrentTreeSlots[tree][xlevel][xslot].Cost <= TreeAPAvailable)
								{
								SlotBorderColor = WhiteBorder;
								tempFlag = true;
								break;
								}
							}
						}
					if (tempFlag == false)
						{     //None of our Enhancements met all the Requirements
						for (unsigned int k=1; k<CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndex.size(); k++)
							{
							Enhancement = EnhancementTree->GetEnhancementPointer(CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndex[k]);
							if (AreEnhancementReqsMet(Enhancement) == true)
								{  //At least one of the Requirements meets the Enhancent/Feat Reqs, but not points/level so border color is NoBorder
								tempFlag = true;
								SlotBorderColor = NoBorder;
								break;
								}
							}
						if (tempFlag == false)
							SlotBorderColor = RedBorder;   //None of our enhancements met the Enhancement/Feat Reqs so Border Color is Red
						}
					}
				else 
					{   // This is for Single enhancements or a Multi-Enhancement Slot that has been Chosen Already.
					tempIndex = CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndexChosen;
					Enhancement = EnhancementTree->GetEnhancementPointer(CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndex[tempIndex]);
					IconGraphic = Enhancement->GetEnhancementIcon();
					//Lets find out what color border our Enhancement Icon gets (RedBorder, WhiteBorder, NoBorder)
					SlotBorderColor = NoBorder;
					if (AreAllRequirementsMet(Enhancement) == true)
						{
						if (CurrentTreeSlots[tree][xlevel][xslot].Cost <= TreeAPAvailable)
							SlotBorderColor = WhiteBorder;   // All Requirments were met for this enhancement
						}
					else
						{
						if (AreEnhancementReqsMet(Enhancement) == false)
							SlotBorderColor = RedBorder;  // Feat/Enhancement Reqs were not met for this Enhancement.
						if (IsEnhancementLocked(Enhancement) == true)
							SlotBorderColor = RedBorder; //Another Enhancement is selected that locks this one out.
						}
					}
				//one last check for border color, if Slot is already at max ranks, then NoBorder is needed.
				if (CurrentTreeSlots[tree][xlevel][xslot].RanksTaken == CurrentTreeSlots[tree][xlevel][xslot].Ranks)
					SlotBorderColor = NoBorder;
				//check to see if Level 5 Slots are locked due to another Tree having level 5 enhancement selected.
				if (xlevel == 5 && CurrentLevel5TreeLock[tree] == true)
					SlotBorderColor = LockedBorder;
				//we need to check a specific enhancement "Energy of the wild" from arcane archer trees
				//if the player has the feat Magical training already, then we need to lock this enhancement 
				//at Rank 3.
				if (EnhancementTree->GetTreeIndex() == ENHT_ARCANE_ARCHER_ELF || EnhancementTree->GetTreeIndex() == ENHT_ARCANE_ARCHER_RNG)
					{
					if (xlevel == 1 && xslot == 2 && CurrentTreeSlots[tree][xlevel][xslot].RanksTaken == 2)
						{
						if (Character.HasFeat("Magical Training", CharacterLevel))
							SlotBorderColor = LockedBorder;
						}
					}
				//Need to check a Bard enhancement
				if (EnhancementTree->GetTreeIndex() == ENHT_SPELLSINGER_BRD)
					{
					if (xlevel == 1 && xslot == 1 && CurrentTreeSlots[tree][xlevel][xslot].RanksTaken == 2)
						{
						if (Character.HasFeat("Magical Training", CharacterLevel))
							if (CurrentTreeSlots[tree][xlevel][xslot].EnhancementIndexChosen != 2)
								SlotBorderColor = LockedBorder;
						}
					}
				//Need to check a Halfling Herioc Companion enhancement
				if (EnhancementTree->GetTreeIndex() == ENHT_HALFLING)
					{
					if (xlevel == 2 && xslot == 4)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_HARPER_AGENT)
								{
									//Check if Harper Agent Herioc Companion enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
							}
						}
					}
				//Need to check a Harper Agent Herioc Companion enhancement
				if (EnhancementTree->GetTreeIndex() == ENHT_HARPER_AGENT)
					{
					if (xlevel == 2 && xslot == 0)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_HALFLING)
								{
									//Check if Halfling Herioc Companion enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][4].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
							}
						}
					}
				//Need to check Harper Agent Know the Angles enhancement
				if (EnhancementTree->GetTreeIndex() == ENHT_HARPER_AGENT)
					{
					if (xlevel == 2 && xslot == 3)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_WARPRIEST_CLR || ChosenTrees[xtree] == ENHT_WARPRIEST_FVS)
								{
									//Check if Cleric Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][1][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
									if(ChosenTrees[xtree] == ENHT_KNIGHT_OF_THE_CHALICE_PAL)
								{
									//Check if Paladin Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][1].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}

							}
						}
					}
				//Need to check Warpriest enhancement tree Divine Might
				if (EnhancementTree->GetTreeIndex() == ENHT_WARPRIEST_CLR)
					{
					if (xlevel == 1 && xslot == 0)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_HARPER_AGENT)
								{
									//Check if Harper Agent Know the Angles enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][3].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
									if(ChosenTrees[xtree] == ENHT_KNIGHT_OF_THE_CHALICE_PAL)
								{
									//Check if Paladin Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][1].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
								if(ChosenTrees[xtree] == ENHT_WARPRIEST_FVS)
								{
									//Check if Favored Soul Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][1][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
							}
						}
					}
				//Need to check Warpriest Favored Soul enhancement tree Divine Might
				if (EnhancementTree->GetTreeIndex() == ENHT_WARPRIEST_FVS)
					{
					if (xlevel == 1 && xslot == 0)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_HARPER_AGENT)
								{
									//Check if Harper Agent Know the Angles enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][3].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
									if(ChosenTrees[xtree] == ENHT_KNIGHT_OF_THE_CHALICE_PAL)
								{
									//Check if Paladin Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][1].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
								if(ChosenTrees[xtree] == ENHT_WARPRIEST_CLR)
								{
									//Check if Cleric Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][1][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
							}
						}
					}
				//Need to check Paladin enhancement tree Divine Might
				if (EnhancementTree->GetTreeIndex() == ENHT_KNIGHT_OF_THE_CHALICE_PAL)
					{
					if (xlevel == 2 && xslot == 1)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_WARPRIEST_CLR || ChosenTrees[xtree] == ENHT_WARPRIEST_FVS)
								{
									//Check if Cleric Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][1][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
								if(ChosenTrees[xtree] == ENHT_HARPER_AGENT)
								{
									//Check if Harper Agent Know the Angles enhacement has been Taken
									if(ChosenTreeSlots[xtree][2][3].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}

							}
						}
					}
				//Need to check Eldrich Knight Sorc
				if (EnhancementTree->GetTreeIndex() == ENHT_ELDRITCH_KNIGHT_SOR)
					{
					if (xlevel == 0 && xslot == 0)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_ELDRITCH_KNIGHT_WIZ)
								{
									//Check if Cleric Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][0][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
							}
						}
					}				
				//Need to check Eldrich Knight Wiz
				if (EnhancementTree->GetTreeIndex() == ENHT_ELDRITCH_KNIGHT_WIZ)
					{
					if (xlevel == 0 && xslot == 0)
						{
							for (unsigned int xtree=0; xtree<7; xtree++)
							{
								if(ChosenTrees[xtree] == ENHT_ELDRITCH_KNIGHT_SOR)
								{
									//Check if Cleric Divine Might enhacement has been Taken
									if(ChosenTreeSlots[xtree][0][0].RanksTaken > 0)
										SlotBorderColor = LockedBorder;
								}
							}
						}
					}
				//ok lets set our SlotGraphic and BorderGraphic now
				if (CurrentTreeSlots[tree][xlevel][xslot].Active == true)
					{
					if (xlevel == 0)
						SlotGraphic = EmptyActiveCore;
					else
						SlotGraphic = EmptyActiveTree;
					switch (SlotBorderColor)
						{
						case WhiteBorder:
							BorderGraphic = IconActiveAvailable;
							break;
						case RedBorder:
							BorderGraphic = IconActiveUnavailable;
							break;
						case LockedBorder:
							BorderGraphic = SlotActiveNotAllowed;
							break;
						}
					}
				else
					{
					if (xlevel == 0)
						SlotGraphic = EmptyPassiveCore;
					else
						SlotGraphic = EmptyPassiveTree;
					switch (SlotBorderColor)
						{
						case WhiteBorder:
							BorderGraphic = IconPassiveAvailable;
							break;
						case RedBorder:
							BorderGraphic = IconPassiveUnavailable;
							break;
						case LockedBorder:
							BorderGraphic = SlotPassiveNotAllowed;
							break;
						}
					}
				// ok now that we have our graphics to draw lets draw them and set the RankTaken/Max Ranks textout messages.
				ss.str("");
				ss << CurrentTreeSlots[tree][xlevel][xslot].RanksTaken << "/" << CurrentTreeSlots[tree][xlevel][xslot].Ranks;
				if (xlevel == 0)
					{
					if (CurrentTreeSlots[tree][xlevel][xslot].RanksTaken == 0)
						DrawGraphicGreyscale(hdc, &IconGraphic, SlotCoreLeft[tree][xslot], SlotTop[xlevel], 36, 36);
					else
						DrawGraphic(hdc, &IconGraphic, SlotCoreLeft[tree][xslot], SlotTop[xlevel], 36, 36);
					DrawGraphic(hdc, &SlotGraphic, SlotCoreLeft[tree][xslot], SlotTop[xlevel], SlotCoreWidth, SlotCoreHeight);
					if (SlotBorderColor != NoBorder)
						DrawGraphic(hdc, &BorderGraphic, SlotCoreLeft[tree][xslot]-3, SlotTop[xlevel]-4, SlotWidth, SlotHeight);
					OldColor = SetTextColor(hdc, RGB(255,255,255));
					TextOut(hdc, SlotCoreLeft[tree][xslot]+12, SlotTop[xlevel]+(SlotCoreHeight-3), ss.str().c_str(), ss.str().size());
					}
				else
					{
					if (CurrentTreeSlots[tree][xlevel][xslot].RanksTaken == 0)
						DrawGraphicGreyscale(hdc, &IconGraphic, SlotLeft[tree][xslot]+3, SlotTop[xlevel]+5, 36, 36);
					else
						DrawGraphic(hdc, &IconGraphic, SlotLeft[tree][xslot]+3, SlotTop[xlevel]+5, 36, 36);
					DrawGraphic(hdc, &SlotGraphic, SlotLeft[tree][xslot], SlotTop[xlevel], SlotWidth, SlotHeight);
					if (SlotBorderColor != NoBorder)
						DrawGraphic(hdc, &BorderGraphic, SlotLeft[tree][xslot], SlotTop[xlevel], SlotWidth, SlotHeight);
					if (xlevel == 5)
						{
						if (CurrentLevel5TreeLock[tree] == false)
							{
							OldColor = SetTextColor(hdc, RGB(255,255,255));
							TextOut(hdc, SlotLeft[tree][xslot]+13, SlotTop[xlevel]+(SlotHeight-14), ss.str().c_str(), ss.str().size());
							}
						}
					else
						{
						OldColor = SetTextColor(hdc, RGB(255,255,255));
						TextOut(hdc, SlotLeft[tree][xslot]+13, SlotTop[xlevel]+(SlotHeight-14), ss.str().c_str(), ss.str().size());
						}
					}
				//we need to switch the color back for the next round of icons.
				SetTextColor(hdc, OldColor);
				} // End of If Valid=true.
			} // end of For Slot loop
		} //end of For Level Loop

	//Draw Tree Name Frames
	if (APSpentTree[tree+ CurrentStartingTree] == 0 && (CurrentStartingTree + tree )!=0 && EnhancementTree->GetTreeIndex() != ENHT_NOTREE)
		DrawGraphic(hdc, &DropDownFrame, APSpentLeft[tree]-205, APSpentTop +15, 162, 21);

	//Tree Name
	ss.str("");
	ss << EnhancementTree->GetTreeName();
	OldColor = SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, APSpentLeft[tree]-200, APSpentTop + 20, ss.str().c_str(), ss.str().size());
	SetTextColor(hdc, OldColor);

	//Tree AP Spent
	ss.str("");
	ss << APSpentTree[tree + CurrentStartingTree] << " AP Spent";
	OldColor = SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, APSpentLeft[tree], APSpentTop, ss.str().c_str(), ss.str().size());
	SetTextColor(hdc, OldColor);

	//Draw ResetTree Button
	if (APSpentTree[tree + CurrentStartingTree])
		DrawGraphic(hdc, &ResetTreeButtonOn, APSpentLeft[tree]-15, APSpentTop +15, 79, 24);
	else
		DrawGraphic(hdc, &ResetTreeButtonOff, APSpentLeft[tree]-15, APSpentTop +15, 79, 24);

	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::HandleLeftMouseButtonClick(int x, int y)
	{
	HDC ParentDC;
	bool SlotSelected;
	bool RequirementsMet;
	int Level;
	int Tree;
	int Slot;
	int Cost;
	bool treesRedraw;
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_Tree_Class *EnhancementTree;
	int TreeAPAvailable;


	ParentDC = GetDC(EnhancementWindowHandle);
	RequirementsMet = false;

	//Lets find out if user clicked on a slot
	SlotSelected = IsSlotSelected(x, y, &Tree, &Level, &Slot);

	if (Tree == 0)
	{
		TreeAPAvailable = LevelAPAvailable;
	}
	else
	{
		TreeAPAvailable = LevelAPAvailable - RaceAPAvailable;
	}

	if (SlotSelected == true)
		{   // Ok a slot was clicked, let see if its a valid slot
		if (CurrentTreeSlots[Tree][Level][Slot].Valid == true)
			{
			EnhancementTree = Data.GetEnhancementTreePointer(CurrentTree[Tree]);
			if (CurrentTreeSlots[Tree][Level][Slot].MultiSelection == true && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
				{
				ActivateMultiWindow(Tree, Level, Slot);				
				Enhancement = nullptr;
				}
			else if (CurrentTreeSlots[Tree][Level][Slot].MultiSelection == true && CurrentTreeSlots[Tree][Level][Slot].RanksTaken > 0)
				Enhancement = EnhancementTree->GetEnhancementPointer(Level, Slot, CurrentTreeSlots[Tree][Level][Slot].EnhancementIndexChosen);
			else
				Enhancement = EnhancementTree->GetEnhancementPointer(Level, Slot);

			if (Enhancement != nullptr)
				{
				if (CurrentTreeSlots[Tree][Level][Slot].RanksTaken < CurrentTreeSlots[Tree][Level][Slot].Ranks && CurrentTreeSlots[Tree][Level][Slot].Cost <= TreeAPAvailable)
					{
					RequirementsMet = AreAllRequirementsMet(Enhancement);
					}
				//see if this slot is locked out due to 1 (Level 5 Tree) Lock enforcement.
				if (Level == 5 && CurrentLevel5TreeLock[Tree] == true)
					RequirementsMet = false;
				//Lets see if slot is locked out due to another selected enhancement.
				if (IsEnhancementLocked(Enhancement) == true)
					RequirementsMet = false;
				//we need to check a specific enhancement "Energy of the wild" from arcane archer trees
				//if the player has the feat Magical training already, then we need to lock this enhancement 
				//at Rank 3.
				if (EnhancementTree->GetTreeIndex() == ENHT_ARCANE_ARCHER_ELF || EnhancementTree->GetTreeIndex() == ENHT_ARCANE_ARCHER_RNG)
					{
					if (Level == 1 && Slot == 2 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 2)
						{
						if (Character.HasFeat("Magical Training", CharacterLevel))
							RequirementsMet = false;
						}
					}
				//Need to check Magical Studies for Bards
				if (EnhancementTree->GetTreeIndex() == ENHT_SPELLSINGER_BRD)
					{
					if (Level == 1 && Slot == 1 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 2)
						{
						if (Character.HasFeat("Magical Training", CharacterLevel))
							if (CurrentTreeSlots[Tree][Level][Slot].EnhancementIndexChosen != 2)
								RequirementsMet = false;
						}
					}

				if (RequirementsMet == true)
					{
					//Cost = CurrentTreeSlots[Tree][Level][Slot].Cost;    //This didn't allow for multi cost enhancements
					Cost = Enhancement->GetEnhancementCost();
					CurrentTreeSlots[Tree][Level][Slot].RanksTaken ++;
					ChosenTreeSlots[CurrentStartingTree + Tree][Level][Slot].RanksTaken ++;
					APSpentTree[CurrentStartingTree + Tree] += Cost;
					SessionAPSpentTree[CurrentStartingTree + Tree] += Cost;
					SessionAPSpentTotal += Cost;
					if ((CurrentStartingTree + Tree) == 0)
					{
						if (RaceAPAvailable > Cost)
						{

							RaceAPSpent += Cost;
						}
						else
						{
							if (RaceAPAvailable > 0)
							{
								RaceAPSpent = RaceAP;
							}

						}
						RaceAPAvailable = RaceAP - RaceAPSpent;
					}


					LevelAPAvailable -= Cost;
					TotalAPSpent += Cost;
					if (Level == 5)
						{
						//Since we are spending a point in a level 5 Slot, we need to lock out all other Level 5 Tree slots
						for (int x=0; x<3; x++)
							{
							if (x == Tree)
								CurrentLevel5TreeLock[x] = false;
							else
								CurrentLevel5TreeLock[x] = true;
							}
						for (int x=0; x<7; x++)
							{
							if (x == (CurrentStartingTree + Tree))
								ChosenLevel5TreeLock[x] = false;
							else 
								ChosenLevel5TreeLock[x] = true;
							}
						}
					if (RaceAP > 0)
					{
						UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
						UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
					}
					else
					{
						UpdateAPAvailableLabel(LevelAPAvailable);
						UpdateAPSpentLabel(TotalAPSpent);
					}
					EnableWindow(AcceptButton, true);
					//check Divine Might and Know the Angles
					treesRedraw = false;
					if (EnhancementTree->GetTreeIndex() == ENHT_HARPER_AGENT)
						{
						if (Level == 2 && Slot == 3 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_KNIGHT_OF_THE_CHALICE_PAL)
						{
						if (Level == 2 && Slot == 1 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_WARPRIEST_CLR)
						{
						if (Level == 1 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_WARPRIEST_FVS)
						{
						if (Level == 1 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
							{	
								treesRedraw = true;
							}
						}
					//check Herioc Champion
					if (EnhancementTree->GetTreeIndex() == ENHT_HARPER_AGENT)
						{
						if (Level == 2 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_HALFLING)
						{
						if (Level == 2 && Slot == 4 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
							{
								treesRedraw = true;
							}
						}
				//Need to check Eldrich Knight Sorc
				if (EnhancementTree->GetTreeIndex() == ENHT_ELDRITCH_KNIGHT_SOR)
					{
					if (Level == 0 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
						{
							treesRedraw = true;
						}
					}				
				//Need to check Eldrich Knight Wiz
				if (EnhancementTree->GetTreeIndex() == ENHT_ELDRITCH_KNIGHT_WIZ)
					{
					if (Level == 0 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken >= 1)
						{
							treesRedraw = true;
						}
					}





					if (Level == 5||treesRedraw)
						DrawGraphics(ParentDC);
					else
						DrawTree(ParentDC, Tree);
					}

				}
			//we clicked on a tree, reset the hover
			ToolTipTree = -1;
			ToolTipLevel = -1;
			ToolTipSlot = -1;
			}
		}
		////check the level bars
		unsigned int OldSelectedLevel;
		UIComponentManager *UIManager;

		int X, Y;
		int Width, Height;


		ostringstream ss;



		UIManager = InterfaceManager.GetUIComponents();
		OldSelectedLevel = CharacterLevel;
		for (unsigned int i = 0; i<30; i++)
		{

			X = EnhLevelX[i];
			Y = EnhLevelY[i];
			Width = EnhLevelWidth;
			Height = EnhLevelHeight;
			if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
			{
				if (i + 1 == (int)CharacterLevel)
					return;
				Accept();
				CharacterLevel = i + 1;
				ActivateEnhancementWindow();
				//DrawGraphics(ParentDC);
				////set our total AP  vairables based on characterlevel
				//if (CharacterLevel <21)
				//	TotalAP = CharacterLevel * 4;
				//else
				//	TotalAP = 80; //this is max attainable action points
				//TotalAPAvailable = TotalAP;
				//TotalAPSpent = 0;
				////Set the APRemaing & APSpent Labels
				//for (unsigned int i = 0; i<7; i++)
				//{
				//	TotalAPSpent += APSpentTree[i];
				//}
				//TotalAPAvailable -= TotalAPSpent;

				//UpdateAPSpentLabel(TotalAPSpent);
				//UpdateAPAvailableLabel(TotalAPAvailable);
				//DrawLevelBars(ParentDC);

			}
		}
	ReleaseDC(EnhancementWindowHandle, ParentDC);

	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::HandleRightMouseButtonClick(int x, int y)
	{
	HDC ParentDC;
	bool SlotSelected;
	int Level;
	int Tree;
	int Slot;
	int Cost;
	bool LockFlag;
	bool treesRedraw;
	EnhancementSlotStruct SelectedSlot;
	EnhancementSlotStruct SlotBeingChecked;
	bool AnotherSlotRequires;
	int NewAPSpent;
	Data_Enhancement_Class *EnhancementBeingChecked;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	AnotherSlotRequires = false;
	LockFlag = true;


	ParentDC = GetDC(EnhancementWindowHandle);

	//Lets find out if user clicked on a slot
	SlotSelected = IsSlotSelected(x, y, &Tree, &Level, &Slot);


	if (SlotSelected == true)
		{//ok a Slot was clicked on, lets see if its valid
		SelectedSlot = CurrentTreeSlots[Tree][Level][Slot];
		if (SelectedSlot.Valid == true && SelectedSlot.RanksTaken > SelectedSlot.RanksTakenOld)
			{
			EnhancementTree = Data.GetEnhancementTreePointer(ChosenTrees[CurrentStartingTree+Tree]);
			Enhancement = EnhancementTree->GetEnhancementPointer(SelectedSlot.EnhancementIndex[SelectedSlot.EnhancementIndexChosen]);
			//Lets check to see if any enhancement requires this enhancement to remain selected.
			NewAPSpent = APSpentTree[CurrentStartingTree + Tree];
			NewAPSpent -= SelectedSlot.Cost;
			for (int checklevel=Level; checklevel<6; checklevel++)
				{
				for (int checkslot=0; checkslot<6; checkslot++)
					{
					SlotBeingChecked = CurrentTreeSlots[Tree][checklevel][checkslot];
					if (SlotBeingChecked.Valid == true && SlotBeingChecked.RanksTaken > SlotBeingChecked.RanksTakenOld)
						{
						if (SlotBeingChecked.MultiSelection == true)
							EnhancementBeingChecked = EnhancementTree->GetEnhancementPointer(SlotBeingChecked.EnhancementIndex[SlotBeingChecked.EnhancementIndexChosen]);
						else
							EnhancementBeingChecked = EnhancementTree->GetEnhancementPointer(SlotBeingChecked.EnhancementIndex[0]);
						//Check Core Requirement
						if (Level == 0 && Slot == 0 && checklevel >0)
							{
							AnotherSlotRequires = true;
							break;
							}
						
						//Check AP Requirements
						if (EnhancementBeingChecked->GetAPRequirement() >= NewAPSpent && checklevel > Level)
							{
							AnotherSlotRequires = true;
							break;
							}
						//Check Enhancmenet Requirements
						for (int i=0; i<SlotBeingChecked.RanksTaken; i++)
							{
							for (unsigned int j=0; j<EnhancementBeingChecked->GetRequirementSize(i); j++)
								{
								if (EnhancementBeingChecked->GetRequirementType(i,j) == ENH_ENHANCEMENT || EnhancementBeingChecked->GetRequirementType(i,j) == ENH_MULTIENHANCEMENT)
									{
									if (EnhancementBeingChecked->GetRequirementLevel(i, j) == Level && EnhancementBeingChecked->GetRequirementSlot(i,j) == Slot)
										{
										if (EnhancementBeingChecked->GetRequirementRank(i, j) >= SelectedSlot.RanksTaken)
											{
											AnotherSlotRequires = true;
											break;
											}
										}
									}
								}
							if (AnotherSlotRequires == true)
								break;
							}
						}
					}
				if (AnotherSlotRequires == true)
					break;
				}


			if (AnotherSlotRequires == false)
				{
				//Cost = CurrentTreeSlots[Tree][Level][Slot].Cost;
				Cost = Enhancement->GetEnhancementCost();
				CurrentTreeSlots[Tree][Level][Slot].RanksTaken --;
				ChosenTreeSlots[CurrentStartingTree + Tree][Level][Slot].RanksTaken --;
				APSpentTree[CurrentStartingTree + Tree] -= Cost;
				SessionAPSpentTree[CurrentStartingTree + Tree] -= Cost;
				SessionAPSpentTotal -= Cost;
				
				if (SelectedSlot.MultiSelection == true)
					{
					if (SelectedSlot.RanksTaken-1 == 0)
						{
						CurrentTreeSlots[Tree][Level][Slot].EnhancementIndexChosen = 0;
						ChosenTreeSlots[CurrentStartingTree + Tree][Level][Slot].EnhancementIndexChosen = 0;
						}
					}
				//ok we need to see if we need to disable the Level 5 Locks.
				if (Level==5)
					{
					LockFlag = false;
					for (int i=0; i<6; i++)
						{
						if (CurrentTreeSlots[Tree][Level][i].RanksTaken != 0)
							{
							//ok we still have points in a Level 5 Slot, so we can leave lock in place
							LockFlag = true;
							break;
							}
						}
					if (LockFlag == false)
						{
						for (int x=0; x<3; x++)
							CurrentLevel5TreeLock[x] = false;
						for (int x=0; x<7; x++)
							ChosenLevel5TreeLock[x] = false;
						}
					}
				if ((CurrentStartingTree + Tree) == 0)
				{
					if (RaceAP > 0 )
					{
						if ((APSpentTree[0] - RaceAP) < Cost)
						{
							if ((APSpentTree[0] - RaceAP) > 0)
							{
								RaceAPSpent += Cost - (APSpentTree[0] - RaceAP);
							}
							else
							{
								RaceAPSpent -= Cost;
							}
						}
						RaceAPAvailable = RaceAP - RaceAPSpent;
					}

					
				}
				LevelAPAvailable += Cost;
				TotalAPSpent -= Cost;
				if (RaceAP > 0)
				{
					UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
					UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
				}
				else
				{
					UpdateAPAvailableLabel(LevelAPAvailable);
					UpdateAPSpentLabel(TotalAPSpent);
				}
				//Check Divine Might
									treesRedraw = false;
					if (EnhancementTree->GetTreeIndex() == ENHT_HARPER_AGENT)
						{
						if (Level == 2 && Slot == 3 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_KNIGHT_OF_THE_CHALICE_PAL)
						{
						if (Level == 2 && Slot == 1 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_WARPRIEST_CLR)
						{
						if (Level == 1 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_WARPRIEST_FVS)
						{
						if (Level == 1 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
							{	
								treesRedraw = true;
							}
						}
					//check Herioc Champion
					if (EnhancementTree->GetTreeIndex() == ENHT_HARPER_AGENT)
						{
						if (Level == 2 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
							{
								treesRedraw = true;
							}
						}
					if (EnhancementTree->GetTreeIndex() == ENHT_HALFLING)
						{
						if (Level == 2 && Slot == 4 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
							{
								treesRedraw = true;
							}
						}
									//Need to check Eldrich Knight Sorc
				if (EnhancementTree->GetTreeIndex() == ENHT_ELDRITCH_KNIGHT_SOR)
					{
					if (Level == 0 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
						{
							treesRedraw = true;
						}
					}				
				//Need to check Eldrich Knight Wiz
				if (EnhancementTree->GetTreeIndex() == ENHT_ELDRITCH_KNIGHT_WIZ)
					{
					if (Level == 0 && Slot == 0 && CurrentTreeSlots[Tree][Level][Slot].RanksTaken == 0)
						{
							treesRedraw = true;
						}
					}
				if (SessionAPSpentTotal == 0)
					EnableWindow(AcceptButton, false);
				
				if (LockFlag == false||treesRedraw)
					DrawGraphics(ParentDC);
				else
					DrawTree(ParentDC, Tree);
				}

			//we clicked on a tree, reset the hover
			ToolTipTree = -1;
			ToolTipLevel = -1;
			ToolTipSlot = -1;
			}
		}

	ReleaseDC(EnhancementWindowHandle, ParentDC);

	}

//---------------------------------------------------------------------------
void EnhancementWindowClass::HandleMouseHover(int x, int y)
	{
	bool SlotSelected;
	int Tree;
	int Level;
	int Slot;
	Data_Enhancement_Tree_Class *TreeData;
	Data_Enhancement_Class *Enhancement;

	//Lets find out if our user is hovering on a slot
	SlotSelected = IsSlotSelected(x, y, &Tree, &Level, &Slot);

	//stop here if the slot is the same as the old slot, don't keep redrawing!
	if (SlotSelected == true && Tree == ToolTipTree && Level == ToolTipLevel && Slot == ToolTipSlot)
		return;
	
	ToolTipTree = Tree;
	ToolTipLevel = Level;
	ToolTipSlot = Slot;
	
	// Ok lets set Slot information if a slot was Highlighted
	if (SlotSelected == true)
		{
		if (CurrentTreeSlots[Tree][Level][Slot].Valid == true)
			{
			TreeData = Data.GetEnhancementTreePointer(CurrentTree[Tree]);
			if (CurrentTreeSlots[Tree][Level][Slot].MultiSelection == true)
				{
				if (CurrentTreeSlots[Tree][Level][Slot].EnhancementIndexChosen == 0)
					{
					Enhancement = TreeData->GetEnhancementPointer(Level, Slot);
					SetToolTipWindow(Enhancement);
					}
				else
					{
					Enhancement = TreeData->GetEnhancementPointer(Level, Slot, CurrentTreeSlots[Tree][Level][Slot].EnhancementIndexChosen);
					SetToolTipWindow(Enhancement);
					}
				}
			else
				{
				Enhancement = TreeData->GetEnhancementPointer(Level, Slot);
				SetToolTipWindow(Enhancement);
				}
			
			ShowTooTipWindow(true);
			}
		else
			{
			ShowTooTipWindow(false);
			ToolTipTree = -1;
			ToolTipLevel = -1;
			ToolTipSlot = -1;
			}
		}
	else
		{
		ShowTooTipWindow(false);
		ToolTipTree = -1;
		ToolTipLevel = -1;
		ToolTipSlot = -1;
		}
	}

//---------------------------------------------------------------------------
long EnhancementWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	PAINTSTRUCT ps;
	RECT Rect;

	switch (Message)
		{
		case WM_CLOSE:
			{
			InterfaceManager.ShowChild(ENHANCEMENTWINDOW, false);
			return 0;
			}
		case WM_COMMAND:
			{
				if (HIWORD(wParam) == BN_CLICKED)
				{

						if ((int)LOWORD(wParam) == EW_ACCEPTBUTTON)
						{
							Accept();
							ShowWindow(SelectTreeList, false);
							InterfaceManager.ShowChild(ENHANCEMENTWINDOW, false);
							return 0;
						}
						if ((int)LOWORD(wParam) == EW_CANCELBUTTON)
						{
							ShowWindow(SelectTreeList, false);
							InterfaceManager.ShowChild(ENHANCEMENTWINDOW, false);
							return 0;
						}
						if ((int)LOWORD(wParam) == EW_RESETALLTREESBUTTON)
						{
							if (!IsWindowVisible(SelectTreeList))
							{
								ResetAllTrees();
								return 0;
							}
						}
						if ((int)LOWORD(wParam) == EW_RESPEC)
						{
							if (!IsWindowVisible(SelectTreeList))
							{
								ResetAllAtLvlTrees(CharacterLevel);
								return 0;
							}
						}
						if ((int)LOWORD(wParam) == EW_APTOME)
						{
							if (!IsWindowVisible(SelectTreeList))
							{

								if (SendMessage(APTomeButton, BM_GETCHECK, 0, 0) == BST_CHECKED)
								{

									CharacterEnhancements->SetAPTome(true);
									LevelAPAvailable += 1;
									RaceAPAvailable += 1;
									RaceAP += 1;

									UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
									UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
									EnableWindow(AcceptButton, true);
								}

								else
								{
									CharacterEnhancements->SetAPTome(false);
									RaceAPAvailable -= 1;
									LevelAPAvailable -= 1;
									RaceAP -= 1;
									if (RaceAPAvailable < RaceAPSpent)
										RaceAPSpent = RaceAPAvailable;
									UpdateAPAvailableLabel(LevelAPAvailable, RaceAPAvailable);
									UpdateAPSpentLabel(TotalAPSpent, RaceAPSpent);
									EnableWindow(AcceptButton, true);
								}

								return 0;
							}
						}
					}

			return 0;
			}
		case WM_LBUTTONDOWN:
			{
			if (IsChildWindowVisible() == false)
				{
				if (LOWORD(lParam) >949 && LOWORD(lParam) < 971 && HIWORD(lParam) > 200 && HIWORD(lParam) < 290)
					{
					if (CurrentStartingTree < 4)
						UpdateCurrentTrees("Right");
					ShowWindow(SelectTreeList, false);
					EnableWindow(Respec, true);
					EnableWindow(ResetAllTreesButton, true);
					EnableWindow(CancelButton, true);
					EnableWindow(AcceptButton, true);
					EnableWindow(APTomeButton, true);
					}
				else if (LOWORD(lParam) >6 && LOWORD(lParam) <28 && HIWORD(lParam) >200 && HIWORD(lParam) <290)
					{
					if (CurrentStartingTree > 0)
						UpdateCurrentTrees("Left");
					ShowWindow(SelectTreeList, false);
					EnableWindow(Respec, true);
					EnableWindow(ResetAllTreesButton, true);
					EnableWindow(CancelButton, true);
					EnableWindow(AcceptButton, true);
					EnableWindow(APTomeButton, true);
					}
				else if (LOWORD(lParam) >55 && LOWORD(lParam) <217 && HIWORD(lParam) >445 && HIWORD(lParam) <466)
					{
					TreeChanging = 0;
					FillSelectTreeList(0);
					}
				else if (LOWORD(lParam) >365 && LOWORD(lParam) <527 && HIWORD(lParam) >445 && HIWORD(lParam) <466)
					{
					TreeChanging = 1;
					FillSelectTreeList(1);
					}
				else if (LOWORD(lParam) >675 && LOWORD(lParam) <837 && HIWORD(lParam) >445 && HIWORD(lParam) <466)
					{
					TreeChanging = 2;
					FillSelectTreeList(2);
					}
				else if (LOWORD(lParam) >245 && LOWORD(lParam) <324 && HIWORD(lParam) >445 && HIWORD(lParam) <469)
					{
					ResetCurrentTree(0);
					}
				else if (LOWORD(lParam) >555 && LOWORD(lParam) <634 && HIWORD(lParam) >445 && HIWORD(lParam) <469)
					{
					ResetCurrentTree(1);
					}
				else if (LOWORD(lParam) >865 && LOWORD(lParam) <944 && HIWORD(lParam) >445 && HIWORD(lParam) <469)
					{
					ResetCurrentTree(2);
					}
				else
					{
					HandleLeftMouseButtonClick(LOWORD(lParam), HIWORD(lParam));
					ShowWindow(SelectTreeList,false);
					EnableWindow(Respec, true);
					EnableWindow(ResetAllTreesButton, true);
					EnableWindow(CancelButton, true);
					EnableWindow(AcceptButton, true);
					EnableWindow(APTomeButton, true);
					}
				ShowTooTipWindow(false);
				}
			return 0;
			}
		case WM_RBUTTONDOWN:
			{
			if (IsChildWindowVisible() == false)
				HandleRightMouseButtonClick(LOWORD(lParam), HIWORD(lParam));
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
				tme.hwndTrack = EnhancementWindowHandle;
				TrackMouseEvent(&tme);
				TMEFlag = true;
				}
			return 0;
			}
		case WM_MOUSELEAVE:
			{
			ShowTooTipWindow(false);
			TMEFlag = false;
			ToolTipTree = -1;
			ToolTipLevel = -1;
			ToolTipSlot = -1;
			return 0;
			}
		case WM_CTLCOLORLISTBOX:
			{
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (long)GetStockObject(DKGRAY_BRUSH);
			}
		case WM_CTLCOLORSTATIC:
			{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(255,255,255));
			return (long)GetStockObject(DKGRAY_BRUSH);
			}
		case WM_DRAWITEM:
			{
			if ((unsigned int)wParam == EW_SELECTTREELIST)
				{
				DrawSelectTreeListItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
			return false;
			}
		case WM_MOUSEWHEEL:
            {
            GetWindowRect(SelectTreeList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(SelectTreeList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(SelectTreeList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
			return 0;
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

//---------------------------------------------------------------------
long EnhancementWindowClass::HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	WNDPROC OriginalProc;
	DWORD Selection;
	int IconDrag;

	switch (Message)
		{
		case WM_LBUTTONDBLCLK:
			{ 
			if (Wnd == SelectTreeList)
				return 0;
			break;
			}
		case WM_LBUTTONDOWN:
			{
			if (Wnd == SelectTreeList)
				{
				Selection = SendMessage(SelectTreeList, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(SelectTreeList, LB_GETITEMDATA, Selection, 0);
				if (IconDrag == -1)
					return 0;
				ChangeTree(IconDrag);
				ShowWindow(SelectTreeList, false);
				EnableWindow(Respec, true);
				EnableWindow(ResetAllTreesButton, true);
				EnableWindow(CancelButton, true);
				EnableWindow(AcceptButton, true);
				EnableWindow(APTomeButton, true);
				return 0;
				}
			break;
			}
		}
	
	OriginalProc = GetOriginalWinProc(Wnd);
	return CallWindowProc(OriginalProc, Wnd, Message, wParam, lParam);
	}


//---------------------------------------------------------------------
WNDPROC EnhancementWindowClass::GetOriginalWinProc(HWND Window)
	{
	for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
		{
		if (SubclassHWNDs[i] == Window)
			return OriginalProcs[i];
		}
	return 0;
	}

//---------------------------------------------------------------------
void EnhancementWindowClass::SubclassChildWindows()
	{
	WNDPROC OriginalProc;

	SubclassHWNDs.clear();
	OriginalProcs.clear();

	OriginalProc = (WNDPROC)SetWindowLong(SelectTreeList, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(SelectTreeList);
	OriginalProcs.push_back(OriginalProc);

	}

//---------------------------------------------------------------------
void EnhancementWindowClass::DeSubclassChildWindows()
	{
	for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
		SetWindowLongPtr(SubclassHWNDs[i], GWL_WNDPROC, static_cast<__int3264>(reinterpret_cast<LONG_PTR>(OriginalProcs[i])));
	}

