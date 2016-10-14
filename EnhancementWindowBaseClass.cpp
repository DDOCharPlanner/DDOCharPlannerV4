#include "EnhancementWindowBaseClass.h"
#include "MainScreenClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "MultiEnhancementWindowClass.h"

//static members
int EnhancementWindowBaseClass::CharacterLevel;
int EnhancementWindowBaseClass::APSpentTree[7];
ENHANCEMENT_TREE EnhancementWindowBaseClass::CurrentTree[3];
EnhancementSlotStruct EnhancementWindowBaseClass::CurrentTreeSlots[3][6][6];
EnhancementSlotStruct EnhancementWindowBaseClass::ChosenTreeSlots[7][6][6];
ENHANCEMENT_TREE EnhancementWindowBaseClass::ChosenTrees[7];

//---------------------------------------------------------------------------
EnhancementWindowBaseClass::EnhancementWindowBaseClass()
	{
	}

//---------------------------------------------------------------------------
EnhancementWindowBaseClass::~EnhancementWindowBaseClass()
	{
	}

//---------------------------------------------------------------------------
void EnhancementWindowBaseClass::SetToolTipWindow(Data_Enhancement_Class *Enhancement)
	{
	ostringstream strDescription;
	int TotalRanks;
	Data_Enhancement_MultiSelector_Class *MultiSelector;
	EnhancementSlotStruct SlotData; 
	int intTree;
	int EnhancementLevel;
	int EnhancementSlot;
	ToolTipWindowClass *Tooltip;


	//grab the slot data
	intTree = ConvertTreeToChosenTree(Enhancement->GetTreeIndex());
	EnhancementLevel = Enhancement->GetEnhancementLevel();
	EnhancementSlot = Enhancement->GetEnhancementSlot();
	SlotData = ChosenTreeSlots[intTree][EnhancementLevel][EnhancementSlot];
	TotalRanks = SlotData.Ranks;

	if (SlotData.MultiSelection == true && InterfaceManager.ChildWindowVisible(MULTIENHANCEMENTWINDOW) == false && SlotData.RanksTaken == 0)
		{
		strDescription << "{\\fs18";
		MultiSelector = Enhancement->GetMultiSelectorPointer();
		strDescription << "Multiple Enhancement Selector \\par";
		strDescription << "{\\b {\\cf2";
		strDescription << Enhancement->GetEnhMultiName();
		strDescription << " \\par\\par}}";
		strDescription << MultiSelector->GetDescription();
		strDescription << "}";
		}
	else
		{
		strDescription << "{\\fs18";
		switch (SlotData.RanksTaken)
			{
			case 0:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Enhancement->GetEnhancementName();
				strDescription << " \\par}}";
				strDescription << "AP Cost: " << Enhancement->GetEnhancementCost();
				strDescription << " \\par";
				strDescription << GetRequirementText(Enhancement, 0, REQTYPE_APSPENT, 0);
				strDescription << GetRequirementText(Enhancement, 0, REQTYPE_CLASSLEVEL, 0);
				strDescription << GetRequirementText(Enhancement, 0, REQTYPE_CHARACTERLEVEL, 0);
				strDescription << " \\par";
				//rank 1
				strDescription << "{\\cf1 Rank 1: \\par}";
				strDescription << GetRequirementText(Enhancement, 1, REQTYPE_ENHANCEMENT, 0);
				strDescription << GetRequirementText(Enhancement, 1, REQTYPE_FEAT, 0);
				strDescription << GetRequirementText(Enhancement, 1, REQTYPE_ONEOF, 0);
				strDescription << Enhancement->GetDescription(1);
				strDescription << "{\\par\\par}";
				break;
				}
			case 1:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Enhancement->GetEnhancementName();
				strDescription << " \\par}}";
				strDescription << "AP Cost: " << Enhancement->GetEnhancementCost();
				strDescription << " \\par\\par";
				//rank 1
				strDescription << "{\\cf1 Rank 1: \\par}";
				strDescription << Enhancement->GetDescription(1);
				strDescription << "{\\par\\par}";
				if (TotalRanks > 1)
					{
					//rank 2
					strDescription << "{\\cf1 Rank 2: \\par}";
					strDescription << GetRequirementText(Enhancement, 2, REQTYPE_ENHANCEMENT, 1);
					strDescription << GetRequirementText(Enhancement, 2, REQTYPE_FEAT, 1);
					strDescription << GetRequirementText(Enhancement, 2, REQTYPE_ONEOF, 1);
					strDescription << Enhancement->GetDescription(2);
					strDescription << "{\\par\\par}";
					}
				break;
				}
			case 2:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Enhancement->GetEnhancementName();
				strDescription << " \\par}}";
				strDescription << "AP Cost: " << Enhancement->GetEnhancementCost();
				strDescription << " \\par\\par";
				//rank 2
				strDescription << "{\\cf1 Rank 2: \\par}";
				strDescription << Enhancement->GetDescription(2);
				strDescription << "{\\par\\par}";
				if (TotalRanks > 2)
					{
					//rank 3
					strDescription << "{\\cf1 Rank 3: \\par}";
					strDescription << GetRequirementText(Enhancement, 3, REQTYPE_ENHANCEMENT, 2);
					strDescription << GetRequirementText(Enhancement, 3, REQTYPE_FEAT, 2);
					strDescription << GetRequirementText(Enhancement, 3, REQTYPE_ONEOF, 2);
					strDescription << Enhancement->GetDescription(3);
					strDescription << "{\\par\\par}";
					}
				break;
				}
			case 3:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Enhancement->GetEnhancementName();
				strDescription << " \\par}}";
				strDescription << "AP Cost: " << Enhancement->GetEnhancementCost();
				strDescription << " \\par\\par";
				//rank 3
				strDescription << "{\\cf1 Rank 3: \\par}";
				strDescription << Enhancement->GetDescription(3);
				strDescription << "{\\par\\par}";
				break;
				}
			}
		strDescription << "}";
		}

	Tooltip = InterfaceManager.GetToolTipWindowPointer();
	Tooltip->SetToolTipText(strDescription.str());
	}

//---------------------------------------------------------------------------
void EnhancementWindowBaseClass::ShowTooTipWindow(bool Show)
	{
	ToolTipWindowClass *Tooltip;

	Tooltip = InterfaceManager.GetToolTipWindowPointer();
	Tooltip->Show(Show);

	if (Show == true)
		tme.dwHoverTime = 200;
	else
		tme.dwHoverTime = 400;
	}

//-------------------------------------------------------------------------------------
bool EnhancementWindowBaseClass::AreAllRequirementsMet(Data_Enhancement_Class *Enhancement)
	{
	if (AreAPRequirementsMet(Enhancement) == false)
		return false;
	if (AreEnhancementReqsMet(Enhancement) == false)
		return false;
	if (AreLevelRequirementsMet(Enhancement, false) == false)
		return false;
	if (AreLevelRequirementsMet(Enhancement, true) == false)
		return false;

	//if we made it this far then reqs are met
	return true;
	}

//---------------------------------------------------------------------------
void EnhancementWindowBaseClass::SetCharacterLevel(int Level)
	{
	CharacterLevel = Level;
	}

//-------------------------------------------------------------------------------------
bool EnhancementWindowBaseClass::AreAPRequirementsMet(Data_Enhancement_Class* Enhancement)
	{
	ENHANCEMENT_TREE Tree;
	int TreeIndex;

	//determine the AP spent in this tree
	Tree = Enhancement->GetTreeIndex();
	TreeIndex = ConvertTreeToChosenTree(Tree);

	if (APSpentTree[TreeIndex] >= Enhancement->GetAPRequirement())
		return true;
	return false;
	}

//-------------------------------------------------------------------------------------
bool EnhancementWindowBaseClass::AreEnhancementReqsMet(Data_Enhancement_Class* Enhancement)
	{
	int intTree;
	int EnhancementLevel;
	int EnhancementSlot;
	EnhancementSlotStruct SlotData; 
	int RequiredLevel;
	int RequiredSlot;
	int RequiredRank;
	string RequiredName;
	string RequiredTree;
	//int RequiredIndex;
	Data_Enhancement_Class *Enhancement2;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Tree_Class *EnhancementTree2;
	int indexChosen;
	CLASS SelectedClass;

	//grab the slot data
	intTree = (ConvertTreeToChosenTree(Enhancement->GetTreeIndex())-CurrentStartingTree);
	EnhancementLevel = Enhancement->GetEnhancementLevel();
	EnhancementSlot = Enhancement->GetEnhancementSlot();
	SlotData = CurrentTreeSlots[intTree][EnhancementLevel][EnhancementSlot];

	EnhancementTree = Data.GetEnhancementTreePointer(Enhancement->GetTreeIndex());
	// lets check the Requirement Field, This for loop should never return true, if requirements are met in here
	// we need to continue on to RequirementOne checks.
	for (unsigned int i=0; i<Enhancement->GetRequirementSize(SlotData.RanksTaken); i++)
		{
		switch (Enhancement->GetRequirementType(SlotData.RanksTaken, i))
			{
			case ENH_ENHANCEMENT:
				{
				RequiredLevel = Enhancement->GetRequirementLevel(SlotData.RanksTaken, i);
				RequiredSlot = Enhancement->GetRequirementSlot(SlotData.RanksTaken, i);
				RequiredRank = Enhancement->GetRequirementRank(SlotData.RanksTaken, i);
				RequiredName = Enhancement->GetRequirementName(SlotData.RanksTaken, i);
				if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].MultiSelection == true)
					{
					if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndexChosen == 0)
						return false;
					else
						{
						indexChosen = CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndexChosen;
						Enhancement2 = EnhancementTree->GetEnhancementPointer(CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndex[indexChosen]);
						if (Enhancement2->GetEnhancementName() == RequiredName)
							{
							if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
								return false;
							}
						else
							return false;
						}
					}
				else
					{
					if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
						return false;
					}
				break;
				}
			case ENH_MULTIENHANCEMENT:
				{
				RequiredLevel = Enhancement->GetRequirementLevel(SlotData.RanksTaken, i);
				RequiredSlot = Enhancement->GetRequirementSlot(SlotData.RanksTaken, i);
				RequiredRank = Enhancement->GetRequirementRank(SlotData.RanksTaken, i);
				if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndexChosen == 0)
						return false;
				else
					{
					if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
						return false;
					}
				break;
				}
			case ENH_FEAT:
				{
				RequiredName = Enhancement->GetRequirementName(SlotData.RanksTaken, i);
				if (!Character.HasFeat(RequiredName, CharacterLevel))
					return false;
				break;
				}
			case ENH_CLASS:
				{
				RequiredName = Enhancement->GetRequirementName(SlotData.RanksTaken, i);
				RequiredLevel = Enhancement->GetRequirementLevel(SlotData.RanksTaken, i);
				for (int i=1; i<=CharacterLevel; i++)
					{
					if (Data.GetClassName(Character.GetClass(i, false)) == RequiredName)
						{
						SelectedClass = Character.GetClass(i, false);
						if (Character.GetClassLevel(SelectedClass, CharacterLevel) < RequiredLevel)
							return false;
						break;
						}
					if (i == CharacterLevel)
						return false;
					}
				break;
				}
			default:
				break;
			}
		}
	//lets Check the Requirement One Field, unlike the Requirement Field we need to return true if any one these are true, otherwise return false.
	for (unsigned int i=0; i<Enhancement->GetRequirementOneSize(SlotData.RanksTaken); i++)
		{
		switch (Enhancement->GetRequirementOneType(SlotData.RanksTaken, i))
			{
			case ENH_ENHANCEMENT:						
				{
				RequiredLevel = Enhancement->GetRequirementOneLevel(SlotData.RanksTaken, i);
				RequiredSlot = Enhancement->GetRequirementOneSlot(SlotData.RanksTaken, i);
				RequiredRank = Enhancement->GetRequirementOneRank(SlotData.RanksTaken, i);
				RequiredName = Enhancement->GetRequirementOneName(SlotData.RanksTaken, i);
				RequiredTree = Enhancement->GetRequirementOneTree(SlotData.RanksTaken, i);
				if (RequiredTree != "")
				{
					for (int x = 0; x < 7;x++)
					{
						
						if (ConvertEnhancementTreeToString(ChosenTrees[x]) == RequiredTree)
						{
							EnhancementTree2 = Data.GetEnhancementTreePointer(ChosenTrees[x]);
							if (ChosenTreeSlots[x][RequiredLevel][RequiredSlot].MultiSelection == true)
							{
								if (ChosenTreeSlots[x][RequiredLevel][RequiredSlot].EnhancementIndexChosen != 0)
								{
									indexChosen = ChosenTreeSlots[x][RequiredLevel][RequiredSlot].EnhancementIndexChosen;

										Enhancement2 = EnhancementTree2->GetEnhancementPointer(ChosenTreeSlots[x][RequiredLevel][RequiredSlot].EnhancementIndex[indexChosen]);
										if (Enhancement2->GetEnhancementName() == RequiredName)
										{
											if (ChosenTreeSlots[x][RequiredLevel][RequiredSlot].RanksTaken >= RequiredRank)
												return true;
										}

								}
							}
							else
							{
								if (ChosenTreeSlots[x][RequiredLevel][RequiredSlot].RanksTaken >= RequiredRank)
									return true;
							}




						}

							
					}
					

				}
				else
				{
					if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].MultiSelection == true)
					{
						if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndexChosen != 0)
						{
							indexChosen = CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndexChosen;
							Enhancement2 = EnhancementTree->GetEnhancementPointer(CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndex[indexChosen]);
							if (Enhancement2->GetEnhancementName() == RequiredName)
							{
								if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].RanksTaken >= RequiredRank)
									return true;
							}
						}
					}
					else
					{
						if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].RanksTaken >= RequiredRank)
							return true;
					}
				}
				break;
				}
			case ENH_MULTIENHANCEMENT:
				{
				RequiredLevel = Enhancement->GetRequirementOneLevel(SlotData.RanksTaken, i);
				RequiredSlot = Enhancement->GetRequirementOneSlot(SlotData.RanksTaken, i);
				RequiredRank = Enhancement->GetRequirementOneRank(SlotData.RanksTaken, i);
				if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].EnhancementIndexChosen != 0)
					{
					if (CurrentTreeSlots[intTree][RequiredLevel][RequiredSlot].RanksTaken >= RequiredRank)
						return true;
					}
				break;
				}
			case ENH_FEAT:
				{
				RequiredName = Enhancement->GetRequirementOneName(SlotData.RanksTaken, i);
				if (Character.HasFeat(RequiredName, CharacterLevel))
					return true;
				break;
				}
			default:
				break;
			}
		// we need to check if this is the last loop, if so return false as no results were true.
		if ((i+1) == Enhancement->GetRequirementOneSize(SlotData.RanksTaken))
			return false;
		}
	//if we made it this far, then we need to return True as all requirements were met.
	return true;
	}

//-------------------------------------------------------------------------------------
bool EnhancementWindowBaseClass::AreLevelRequirementsMet(Data_Enhancement_Class* Enhancement, bool ClassLevel)
	{
	CLASS TreeClass;

	if (ClassLevel == true)
		{
		TreeClass = Enhancement->GetTreeClass();
		if (TreeClass == CLASSNONE)
			return true;
		if (Character.GetClassLevel(TreeClass, CharacterLevel) >= Enhancement->GetClassLevelRequirement())
			return true;
		return false;
		}
	else
		{
		if (CharacterLevel >= Enhancement->GetCharacterLevelRequirement())
			return true;
		return false;
		}
	}

//---------------------------------------------------------------------
string EnhancementWindowBaseClass::GetRequirementText(Data_Enhancement_Class *Enhancement, int Rank, ENHANCEMENT_REQUIREMENT_TYPE Type, int RanksTaken)
	{
	ostringstream ss;
	unsigned int ReqSize;
	Data_Enhancement_Class *Enhancement2;
	int RequiredLevel;
	int RequiredSlot;
	int RequiredRank;
	string RequiredTree;
	string RequiredName;
	ENHANCEMENT_TREE CurrentTree;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Tree_Class *EnhancementTree2;
	EnhancementSlotStruct SlotData;

	EnhancementTree = Data.GetEnhancementTreePointer(Enhancement->GetTreeIndex());
	switch (Type)
		{
		case REQTYPE_APSPENT:
			{
			if (Enhancement->GetAPRequirement() == 0)
				return "";
			if (AreAPRequirementsMet(Enhancement) == true)
				ss << "{\\cf4 ";
	        else
				ss << "{\\cf3 ";
			ss << "Requires " << Enhancement->GetAPRequirement() << " AP Spent in Tree{\\par}}";
			return ss.str();
			}
		case REQTYPE_CLASSLEVEL:
			{
			if (Enhancement->GetClassLevelRequirement() == 0)
				return "";
			if (AreLevelRequirementsMet(Enhancement, true) == true)
				ss << "{\\cf4 ";
	        else
				ss << "{\\cf3 ";
			ss << "Requires Level " << Enhancement->GetClassLevelRequirement() << " " << Enhancement->GetClassName() <<"{\\par}}";
			return ss.str();
			}
		case REQTYPE_CHARACTERLEVEL:
			{
			if (Enhancement->GetCharacterLevelRequirement() == 0)
				return "";
			if (AreLevelRequirementsMet(Enhancement, false) == true)
				ss << "{\\cf4 ";
	        else
				ss << "{\\cf3 ";
			ss << "Requires Character Level " << Enhancement->GetCharacterLevelRequirement() << "{\\par}}";
			return ss.str();
			}
		case REQTYPE_ENHANCEMENT:
			{
			CurrentTree = Enhancement->GetTreeIndex();
			ss.str("");
			ReqSize = Enhancement->GetRequirementSize(Rank-1);
			for (unsigned int i=0; i<ReqSize; i++)
				{
				if (Enhancement->GetRequirementType(Rank-1, i) == ENH_ENHANCEMENT)
					{
					//grab the slot data
					SlotData = ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][Enhancement->GetRequirementLevel(Rank-1, i)][Enhancement->GetRequirementSlot(Rank-1, i)];
					if (SlotData.MultiSelection == true)
						{
						for (unsigned int j=1; j<SlotData.EnhancementIndex.size(); j++)
							{
							Enhancement2 = EnhancementTree->GetEnhancementPointer(SlotData.EnhancementIndex[j]);
							if (Enhancement2->GetEnhancementName() == Enhancement->GetRequirementName(Rank-1, i))
								{
								RequiredLevel = Enhancement->GetRequirementLevel(Rank-1, i);
								RequiredSlot = Enhancement->GetRequirementSlot(Rank-1, i);
								RequiredRank = Enhancement->GetRequirementRank(Rank-1, i);
								if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].EnhancementIndexChosen != j)
									ss << "{\\cf3 ";
								else
									{
									if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
										ss << "{\\cf3 ";
									else
										ss << "{\\cf4 ";
									}
								}
							}
						}
					else
						{
						Enhancement2 = EnhancementTree->GetEnhancementPointer(Enhancement->GetRequirementLevel(Rank-1, i), Enhancement->GetRequirementSlot(Rank-1, i));
						if (Enhancement2->GetEnhancementName() == Enhancement->GetRequirementName(Rank-1, i))
							{
							RequiredLevel = Enhancement->GetRequirementLevel(Rank-1, i);
							RequiredSlot = Enhancement->GetRequirementSlot(Rank-1, i);
							RequiredRank = Enhancement->GetRequirementRank(Rank-1, i);
							if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
								ss << "{\\cf3 ";
						    else
								ss << "{\\cf4 ";
							}
						}
					ss << "Requires Enhancement: " << Enhancement->GetRequirementName(Rank-1, i) << " (Rank " << Enhancement->GetRequirementRank(Rank-1, i) << ") {\\par}}";
					}
				if (Enhancement->GetRequirementType(Rank-1, i) == ENH_MULTIENHANCEMENT)
					{
					RequiredLevel = Enhancement->GetRequirementLevel(Rank-1, i);
					RequiredSlot = Enhancement->GetRequirementSlot(Rank-1, i);
					RequiredRank = Enhancement->GetRequirementRank(Rank-1, i);
					if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].EnhancementIndexChosen == 0)
							ss << "{\\cf3 ";
					else
						{
						if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
							ss << "{\\cf3 ";
						else
							ss << "{\\cf4 ";
						}
					ss << "Requires Enhancement: " << Enhancement->GetRequirementName(Rank-1, i) << " (Rank " << Enhancement->GetRequirementRank(Rank-1, i) << ") {\\par}}";
					}
				}
			return ss.str();
			}
		case REQTYPE_FEAT:
			{
			ss.str("");
			ReqSize = Enhancement->GetRequirementSize(Rank-1);
			for (unsigned int i=0; i<ReqSize; i++)
				{
				if (Enhancement->GetRequirementType(Rank-1, i) == ENH_FEAT)
					{
					if (Character.HasFeat(Enhancement->GetRequirementName(Rank-1, i), CharacterLevel) == true)
						ss << "{\\cf4 ";
					else
						ss << "{\\cf3 ";
					ss << "Requires Feat: " << Enhancement->GetRequirementName(Rank-1, i) << " {\\par}}";
					}
				}
			return ss.str();
			}
		case REQTYPE_ONEOF:
			{
			ss.str("");
			if (Enhancement->GetRequirementOneSize(Rank-1) == 0)
				return "";
			ss << "Requires one of: \\par";
			for (unsigned int i=0; i<Enhancement->GetRequirementOneSize(Rank-1); i++)
				{
				if (Enhancement->GetRequirementOneType(Rank-1, i) == ENH_FEAT)
					{
					if (Character.HasFeat(Enhancement->GetRequirementOneName(Rank-1, i), CharacterLevel) == true)
						ss << "{\\cf4 ";
					else
						ss << "{\\cf3 ";
					ss << "  Feat: " << Enhancement->GetRequirementOneName(Rank-1, i) << " {\\par}}";
					}
				if (Enhancement->GetRequirementOneType(Rank-1, i) == ENH_ENHANCEMENT)
					{
					CurrentTree = Enhancement->GetTreeIndex();
					RequiredLevel = Enhancement->GetRequirementOneLevel(Rank - 1, i);
					RequiredSlot = Enhancement->GetRequirementOneSlot(Rank - 1, i);
					RequiredRank = Enhancement->GetRequirementOneRank(Rank - 1, i);
					RequiredTree = Enhancement->GetRequirementOneTree(Rank - 1, i);
					EnhancementTree2 = Data.GetEnhancementTreePointer(ConvertStringToEnhancementTree(RequiredTree));
					
					//check if required Tree is Selecteded
					if (EnhancementTree2->GetTreeIndex() == ENHT_NOTREE)
					{
						ss << "{\\cf3 ";
					}
					else
					{
						//grab the slot data for required slot
						SlotData = ChosenTreeSlots[ConvertTreeToChosenTree(RequiredTree)][Enhancement->GetRequirementOneLevel(Rank - 1, i)][Enhancement->GetRequirementOneSlot(Rank - 1, i)];
						if (SlotData.MultiSelection == true)
						{
							for (unsigned int j = 1; j < SlotData.EnhancementIndex.size(); j++)
							{



								Enhancement2 = EnhancementTree2->GetEnhancementPointer(SlotData.EnhancementIndex[j]);
								if (Enhancement2->GetEnhancementName() == Enhancement->GetRequirementOneName(Rank - 1, i))
								{
									DEBUG(ConvertTreeToChosenTree(RequiredTree));
									if (ChosenTreeSlots[ConvertTreeToChosenTree(RequiredTree)][RequiredLevel][RequiredSlot].EnhancementIndexChosen != j)
										ss << "{\\cf3 ";
									else
									{


										if (ChosenTreeSlots[ConvertTreeToChosenTree(RequiredTree)][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
											ss << "{\\cf3 ";
										else
											ss << "{\\cf4 ";
									}
								}

							}
						}
						else
						{
							Enhancement2 = EnhancementTree2->GetEnhancementPointer(Enhancement->GetRequirementOneLevel(Rank - 1, i), Enhancement->GetRequirementOneSlot(Rank - 1, i));
							if (Enhancement2->GetEnhancementName() == Enhancement->GetRequirementOneName(Rank - 1, i))
							{
								if (ChosenTreeSlots[ConvertTreeToChosenTree(RequiredTree)][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
									ss << "{\\cf3 ";
								else
									ss << "{\\cf4 ";
							}
						}
					}
					ss << "  Enhancement: " << Enhancement->GetRequirementOneName(Rank-1, i) << "{\\par}}";
					}
				if (Enhancement->GetRequirementOneType(Rank-1, i) == ENH_MULTIENHANCEMENT)
					{
					RequiredLevel = Enhancement->GetRequirementOneLevel(Rank-1, i);
					RequiredSlot = Enhancement->GetRequirementOneSlot(Rank-1, i);
					RequiredRank = Enhancement->GetRequirementOneRank(Rank-1, i);
					if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].EnhancementIndexChosen == 0)
							ss << "{\\cf3 ";
					else
						{
						if (ChosenTreeSlots[ConvertTreeToChosenTree(CurrentTree)][RequiredLevel][RequiredSlot].RanksTaken < RequiredRank)
							ss << "{\\cf3 ";
						else
							ss << "{\\cf4 ";
						}
					ss << "  Enhancement: " << Enhancement->GetRequirementOneName(Rank-1, i) << " (Rank " << Enhancement->GetRequirementOneRank(Rank-1, i) << ") {\\par}}";
					}
				}
			return ss.str();
			}
		default:
			return "";
		}
	}

//---------------------------------------------------------------------
bool EnhancementWindowBaseClass::IsEnhancementLocked(Data_Enhancement_Class* Enhancement)
	{
	int intTree;
	int EnhancementLevel;
	int EnhancementSlot;
	EnhancementSlotStruct SlotData; 
	int LockedLevel;
	int LockedSlot;
	int LockedRank;
	string LockedName;
	string LockedTreeName;
	Data_Enhancement_Class *Enhancement2;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Tree_Class *EnhancementTree2;
	int indexChosen;
	int LockedTree;

	//grab the slot data
	intTree = (ConvertTreeToChosenTree(Enhancement->GetTreeIndex())-CurrentStartingTree);
	EnhancementLevel = Enhancement->GetEnhancementLevel();
	EnhancementSlot = Enhancement->GetEnhancementSlot();
	SlotData = CurrentTreeSlots[intTree][EnhancementLevel][EnhancementSlot];

	EnhancementTree = Data.GetEnhancementTreePointer(Enhancement->GetTreeIndex());

	for (unsigned int i=0; i<Enhancement->GetLockSize(SlotData.RanksTaken); i++)
		{
		switch (Enhancement->GetLockType(SlotData.RanksTaken, i))
			{
			case ENH_ENHANCEMENT:
				{
				LockedName = Enhancement->GetLockName(SlotData.RanksTaken, i);
				LockedLevel = Enhancement->GetLockLevel(SlotData.RanksTaken, i);
				LockedSlot = Enhancement->GetLockSlot(SlotData.RanksTaken, i);
				LockedRank = Enhancement->GetLockRank(SlotData.RanksTaken, i);
				LockedTreeName = Enhancement->GetLockTreeName(SlotData.RanksTaken, i);
				LockedTree = -1;
				if (LockedTreeName != "")
					{
					EnhancementTree2 = Data.GetEnhancementTreePointer(LockedTreeName);
					for (int i=0; i<7; i++)
						{
						if (ChosenTrees[i] == EnhancementTree2->GetTreeIndex())
							{
							LockedTree = i;
							break;
							}
						}
					//Check to see if tree was not found, if so then exit this case as this tree was not selected.
					if (LockedTree == -1)
						break;
					}
				else
					LockedTree = (intTree + CurrentStartingTree);

				if (ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].MultiSelection == true)
					{
					if (ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].EnhancementIndexChosen != 0)
						{
						indexChosen = ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].EnhancementIndexChosen;
						EnhancementTree2 = Data.GetEnhancementTreePointer(ChosenTrees[LockedTree]);
						Enhancement2 = EnhancementTree2->GetEnhancementPointer(ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].EnhancementIndex[indexChosen]);
						if (Enhancement2->GetEnhancementName() == LockedName)
							{
							if (ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].RanksTaken > 0)  //>= Locked Rank
								return true;
							}
						}
					}
				else
					{
					if (ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].RanksTaken > 0) //>= LockedRank)
						return true;
					}
				break;
				}
			case ENH_MULTIENHANCEMENT:
				{
				LockedName = Enhancement->GetLockName(SlotData.RanksTaken, i);
				LockedLevel = Enhancement->GetLockLevel(SlotData.RanksTaken, i);
				LockedSlot = Enhancement->GetLockSlot(SlotData.RanksTaken, i);
				LockedRank = Enhancement->GetLockRank(SlotData.RanksTaken, i);
				LockedTreeName = Enhancement->GetLockTreeName(SlotData.RanksTaken, i);
				LockedTree = -1;
				if (LockedTreeName != "")
					{
					EnhancementTree2 = Data.GetEnhancementTreePointer(LockedTreeName);
					for (int i=0; i<7; i++)
						{
						if (ChosenTrees[i] == EnhancementTree2->GetTreeIndex())
							{
							LockedTree = i;
							break;
							}
						}
					//Check to see if tree was not found, if so then exit this case as this tree was not selected.
					if (LockedTree == -1)
						break;
					}
				else
					LockedTree = (intTree + CurrentStartingTree);

				if (ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].EnhancementIndexChosen != 0)
					{
					if (ChosenTreeSlots[LockedTree][LockedLevel][LockedSlot].RanksTaken > 0) // >=LockedRank
						return true;
					}
				break;
				}
			default:
				break;
			}
		//We need to check if this is the last loop, if so return false as no results were true.
		//if ((i+1) == Enhancement->GetRequirementSize(SlotData.RanksTaken-1))
			//return false;
		}
	return false;
	}

//---------------------------------------------------------------------
int EnhancementWindowBaseClass::ConvertTreeToChosenTree(ENHANCEMENT_TREE Tree)
	{
	for (unsigned int i=0; i<7; i++)
		{
		if (ChosenTrees[i] == Tree)
			return i;
		}
	//this will cause a crash, so we better never be here.
	DEBUG("Cannot convert from Enhancement Tree Enum to Chosen Tree Index");
	return -1;
	}
int EnhancementWindowBaseClass::ConvertTreeToChosenTree(string Tree)
{
	for (unsigned int i = 0; i<7; i++)
	{
		if (ConvertEnhancementTreeToString(ChosenTrees[i]) == Tree)
			return i;
	}
	//this will cause a crash, so we better never be here.
	DEBUG("Cannot convert string to Enhancement Tree Enum");
	return -1;
}
string EnhancementWindowBaseClass::ConvertEnhancementTreeToString(ENHANCEMENT_TREE Tree)
{
	Data_Enhancement_Tree_Class *TreeData;

	TreeData = Data.GetEnhancementTreePointer(Tree);
	return TreeData->GetTreeName();
}
ENHANCEMENT_TREE EnhancementWindowBaseClass::ConvertStringToEnhancementTree(string Tree)
{
	for (unsigned int i = 0; i<7; i++)
	{
		if (ConvertEnhancementTreeToString(ChosenTrees[i]) == Tree)
			return ChosenTrees[i];
	}
	//this will cause a crash, so we better never be here.
	DEBUG(Tree + " not Found");
	return ENHT_NOTREE;
}

