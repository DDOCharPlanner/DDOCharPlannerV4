#include "Screen_Destiny_Base_Class.h"
#include "CharacterClass.h"
#include "InterfaceManagerClass.h"

//static members
int Screen_Destiny_Base_Class::CharacterLevel;
unsigned int Screen_Destiny_Base_Class::DPSpentTree[NUM_DESTINY_TREES];
unsigned int Screen_Destiny_Base_Class::DPAvailbleTree[NUM_DESTINY_TREES];
unsigned int Screen_Destiny_Base_Class::DestinyTreeLevel[NUM_DESTINY_TREES];
DESTINY_TREE Screen_Destiny_Base_Class::ScreenTree;
DestinySlotStruct Screen_Destiny_Base_Class::ScreenTreeSlots[7][6];

//--------------------------------------------------------------------
Screen_Destiny_Base_Class::Screen_Destiny_Base_Class()
	{
	}

//--------------------------------------------------------------------
Screen_Destiny_Base_Class::~Screen_Destiny_Base_Class()
	{
	}

//--------------------------------------------------------------------
bool Screen_Destiny_Base_Class::AreRequirementsMet(Data_Destiny_Class *Destiny, bool flagDPointsSpent, bool flagDestinyReqs, bool flagDLevel)
	{
	if (flagDPointsSpent)
		if (!CheckDPointsRequirement(Destiny))
			return false;
	if (flagDLevel)
		if (!CheckDLevelRequirement(Destiny))
			return false;
	if (flagDestinyReqs)
		if (!CheckDestinyRequirements(Destiny))
			return false;

	//if we made it this far then return true
	return true;
	}

//--------------------------------------------------------------------
bool Screen_Destiny_Base_Class::CheckDestinyRequirements(Data_Destiny_Class *Destiny)
	{
	unsigned int DestinyTier;
	unsigned int DestinySlot;
	DestinySlotStruct SlotData;
	string RequiredName;
	unsigned int RequiredTier;
	unsigned int RequiredSlot;
	unsigned int RequiredRank;
	DestinySlotStruct ReqSlotData;
	Data_Destiny_Class *ReqDestiny;
	Data_Destiny_Tree_Class *DestinyTree;

	//Lets grab our slot info for the destiny we are checking
	DestinyTier = Destiny->GetTier();
	DestinySlot = Destiny->GetSlot();
	SlotData = ScreenTreeSlots[DestinyTier][DestinySlot];

	DestinyTree = Data.GetDestinyTreePointer(Destiny->GetTreeIndex());

	//Lets check the Requirement Fields, This for loop should never return true if requirements are met in here as we
	//will still need to check RequirementOne Fields
	for (unsigned int i=0; i<Destiny->GetRequirementSize(SlotData.RanksTaken); i++)
		{
		switch (Destiny->GetRequirementType(SlotData.RanksTaken, i))
			{
			case ENH_ENHANCEMENT:
				{
				RequiredTier = Destiny->GetRequirementTier(SlotData.RanksTaken, i);
				RequiredSlot = Destiny->GetRequirementSlot(SlotData.RanksTaken, i);
				RequiredRank = Destiny->GetRequirementRank(SlotData.RanksTaken, i);
				RequiredName = Destiny->GetRequirementName(SlotData.RanksTaken, i);
				ReqSlotData = ScreenTreeSlots[RequiredTier][RequiredSlot];
				if (ReqSlotData.MultiSelection == true)
					{
					if (ReqSlotData.DestinyIndexChosen == 0)
						return false;
					else
						{
						ReqDestiny = DestinyTree->GetDestinyPointer(ReqSlotData.DestinyIndex[ReqSlotData.DestinyIndexChosen]);
						if (ReqDestiny->GetName() == RequiredName)
							{
							if (ReqSlotData.RanksTaken < RequiredRank)
								return false;
							}
						else
							return false;
						}
					}
				else
					{
					if (ReqSlotData.RanksTaken < RequiredRank)
						return false;
					}
				break;
				}
			case ENH_MULTIENHANCEMENT:
				{
				RequiredTier = Destiny->GetRequirementTier(SlotData.RanksTaken, i);
				RequiredSlot = Destiny->GetRequirementSlot(SlotData.RanksTaken, i);
				RequiredRank = Destiny->GetRequirementRank(SlotData.RanksTaken, i);
				ReqSlotData = ScreenTreeSlots[RequiredTier][RequiredSlot];
				if (ReqSlotData.DestinyIndexChosen == 0)
					return false;
				else
					{
					if (ReqSlotData.RanksTaken < RequiredRank)
						return false;
					}
				break;
				}
			case ENH_FEAT:
				{
				RequiredName = Destiny->GetRequirementName(SlotData.RanksTaken, i);
				if (!Character.HasFeat(RequiredName, MAXLEVEL))
					return false;
				break;
				}
			default:
				break;
			}
		}
	
	//Ok we made it past the Requirement Fields, now lets check the RequirementOne Fields
	//We need to return true if any one of these checks are true, otherwise return false at the end
	for (unsigned int i=0; i<Destiny->GetRequirementOneSize(SlotData.RanksTaken); i++)
		{
		switch (Destiny->GetRequirementOneType(SlotData.RanksTaken, i))
			{
			case ENH_ENHANCEMENT:
				{
				RequiredTier = Destiny->GetRequirementTier(SlotData.RanksTaken, i);
				RequiredSlot = Destiny->GetRequirementSlot(SlotData.RanksTaken, i);
				RequiredRank = Destiny->GetRequirementRank(SlotData.RanksTaken, i);
				RequiredName = Destiny->GetRequirementName(SlotData.RanksTaken, i);
				ReqSlotData = ScreenTreeSlots[RequiredTier][RequiredSlot];
				if (ReqSlotData.MultiSelection == true)
					{
					if (ReqSlotData.DestinyIndexChosen != 0)
						{
						ReqDestiny = DestinyTree->GetDestinyPointer(ReqSlotData.DestinyIndex[ReqSlotData.DestinyIndexChosen]);
						if (ReqDestiny->GetName() == RequiredName)
							{
							if (ReqSlotData.RanksTaken >= RequiredRank)
								return true;
							}
						}
					}
				else
					{
					if (ReqSlotData.RanksTaken >= RequiredRank)
						return true;
					}
				break;
				}
			case ENH_MULTIENHANCEMENT:
				{
				RequiredTier = Destiny->GetRequirementTier(SlotData.RanksTaken, i);
				RequiredSlot = Destiny->GetRequirementSlot(SlotData.RanksTaken, i);
				RequiredRank = Destiny->GetRequirementRank(SlotData.RanksTaken, i);
				ReqSlotData = ScreenTreeSlots[RequiredTier][RequiredSlot];
				if (ReqSlotData.DestinyIndexChosen != 0)
					{
					if (ReqSlotData.RanksTaken >= RequiredRank)
						return true;
					}
				break;
				}
			case ENH_FEAT:
				{
				RequiredName = Destiny->GetRequirementName(SlotData.RanksTaken, i);
				if (Character.HasFeat(RequiredName, MAXLEVEL))
					return true;
				break;
				}
			default:
				break;
			}
		//we need to check if this is the last loop, if so return false as no results were true.
		if ((i+1) == Destiny->GetRequirementOneSize(SlotData.RanksTaken))
			return false;
		}
	//if we made it this far, then we need to return True as all requirements were met.
	return true;
	}

//-------------------------------------------------------------------
bool Screen_Destiny_Base_Class::CheckDLevelRequirement(Data_Destiny_Class *Destiny)
	{
	if (DestinyTreeLevel[ScreenTree] >= Destiny->GetDLevelRequirement())
		return true;
	return false;
	}

//-------------------------------------------------------------------
bool Screen_Destiny_Base_Class::CheckDPointsRequirement(Data_Destiny_Class *Destiny)
	{
	if (DPSpentTree[ScreenTree] >= Destiny->GetDPRequirement())
		return true;
	return false;
	}

//-------------------------------------------------------------------
string Screen_Destiny_Base_Class::GetRequirementText(Data_Destiny_Class *Destiny, int Rank, DESTINY_REQUIREMENT_TYPE Type, int RanksTaken)
	{
	ostringstream ss;
	unsigned int ReqSize;
	Data_Destiny_Class *Destiny2;
	int RequiredTier;
	int RequiredColumn;
	unsigned int RequiredRank;
	string RequiredName;
	Data_Destiny_Tree_Class *DestinyTree;
	DestinySlotStruct SlotData;

	DestinyTree = Data.GetDestinyTreePointer(ScreenTree);
	switch (Type)
		{
		case REQTYPE_DPSPENT:
			{
			if (Destiny->GetDPRequirement() == 0)
				return "";
			if (AreRequirementsMet(Destiny, true, false, false) == true)
				ss << "{\\cf4 ";
			else
				ss << "{\\cf3 ";
			ss << "Requires " << Destiny->GetDPRequirement() << " DP Spent in Tree{\\par}}";
			return ss.str();
			}
		case REQTYPE_DESTINY:
			{
			ss.str("");
			ReqSize = Destiny->GetRequirementSize(Rank-1);
			for (unsigned int i=0; i<ReqSize; i++)
				{
				if (Destiny->GetRequirementType(Rank-1, i) == ENH_ENHANCEMENT)
					{
					//grab the slot data
					SlotData = ScreenTreeSlots[Destiny->GetRequirementTier(Rank-1, i)][Destiny->GetRequirementSlot(Rank-1, i)];
					if (SlotData.MultiSelection == true)
						{
						for (unsigned int j=1; j<SlotData.DestinyIndex.size(); j++)
							{
							Destiny2 = DestinyTree->GetDestinyPointer(SlotData.DestinyIndex[j]);
							if (Destiny2->GetName() == Destiny->GetRequirementName(Rank-1, i))
								{
								RequiredTier = Destiny->GetRequirementTier(Rank-1, i);
								RequiredColumn = Destiny->GetRequirementSlot(Rank-1, i);
								RequiredRank = Destiny->GetRequirementRank(Rank-1, i);
								if (ScreenTreeSlots[RequiredTier][RequiredColumn].DestinyIndexChosen != j)
									ss << "{\\cf3 ";
								else
									{
									if (ScreenTreeSlots[RequiredTier][RequiredColumn].RanksTaken < RequiredRank)
										ss << "{\\cf3 ";
									else
										ss << "{\\cf4 ";
									}
								}
							}
						}
					else
						{
						Destiny2 = DestinyTree->GetDestinyPointer(Destiny->GetRequirementTier(Rank-1, i), Destiny->GetRequirementSlot(Rank-1, i));
						if (Destiny2->GetName() == Destiny->GetRequirementName(Rank-1, i))
							{
							RequiredTier = Destiny->GetRequirementTier(Rank-1, i);
							RequiredColumn = Destiny->GetRequirementSlot(Rank-1, i);
							RequiredRank = Destiny->GetRequirementRank(Rank-1, i);
							if (ScreenTreeSlots[RequiredTier][RequiredColumn].RanksTaken < RequiredRank)
								ss << "{\\cf3 ";
						    else
								ss << "{\\cf4 ";
							}
						}
					ss << "Requires: " << Destiny->GetRequirementName(Rank-1, i) << " (Rank " << Destiny->GetRequirementRank(Rank-1, i) << ") {\\par}}";
					}
				if (Destiny->GetRequirementType(Rank-1, i) == ENH_MULTIENHANCEMENT)
					{
					RequiredTier = Destiny->GetRequirementTier(Rank-1, i);
					RequiredColumn = Destiny->GetRequirementSlot(Rank-1, i);
					RequiredRank = Destiny->GetRequirementRank(Rank-1, i);
					if (ScreenTreeSlots[RequiredTier][RequiredColumn].DestinyIndexChosen == 0)
							ss << "{\\cf3 ";
					else
						{
						if (ScreenTreeSlots[RequiredTier][RequiredColumn].RanksTaken < RequiredRank)
							ss << "{\\cf3 ";
						else
							ss << "{\\cf4 ";
						}
					ss << "Requires: " << Destiny->GetRequirementName(Rank-1, i) << " (Rank " << Destiny->GetRequirementRank(Rank-1, i) << ") {\\par}}";
					}
				}
			return ss.str();
			}
		case REQTYPE_FEAT:
			{
			ss.str("");
			ReqSize = Destiny->GetRequirementSize(Rank-1);
			for (unsigned int i=0; i<ReqSize; i++)
				{
				if (Destiny->GetRequirementType(Rank-1, i) == ENH_FEAT)
					{
					if (Character.HasFeat(Destiny->GetRequirementName(Rank-1, i), CharacterLevel) == true)
						ss << "{\\cf4 ";
					else
						ss << "{\\cf3 ";
					ss << "Requires Feat: " << Destiny->GetRequirementName(Rank-1, i) << " {\\par}}";
					}
				}
			return ss.str();
			}
		default:
			return "";
		}
	}

//-------------------------------------------------------------------
void Screen_Destiny_Base_Class::SetToolTipWindow(Data_Destiny_Class *Destiny)
	{
	ostringstream strDescription;
	int TotalRanks;
	Data_Destiny_MultiSelector_Class *MultiSelector;
	DestinySlotStruct SlotData;
	int DestinyTier;
	int DestinyColumn;
	ToolTipWindowClass *Tooltip;

	//Grab the slot data
	DestinyTier = Destiny->GetTier();
	DestinyColumn = Destiny->GetSlot();
	SlotData = ScreenTreeSlots[DestinyTier][DestinyColumn];
	TotalRanks = SlotData.Ranks;

	if (SlotData.MultiSelection == true && InterfaceManager.ChildWindowVisible(MULTIDESTINYWINDOW) == false && SlotData.RanksTaken == 0)
		{
		strDescription << "{\\fs18";
		MultiSelector = Data.GetMultiDestinyPointer(SlotData.DestinyIndex[0]);
		strDescription << "Multiple Enhancement Selector \\par";
		strDescription << "{\\b {\\cf2";
		strDescription << Destiny->GetMultiSelectorName();
		strDescription << " \\par\\par}}";
		strDescription << MultiSelector->GetDescription(Destiny->GetMultiDescriptionIndex());
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
				strDescription << Destiny->GetName();
				strDescription << " \\par}}";
				strDescription << "DP Cost: " << Destiny->GetDPCost();
				strDescription << " \\par";
				strDescription << GetRequirementText(Destiny, 0, REQTYPE_DPSPENT, 0);
				strDescription << " \\par";
				//rank 1
				strDescription << "{\\cf1 Rank 1: \\par}";
				strDescription << GetRequirementText(Destiny, 1, REQTYPE_DESTINY, 0);
				strDescription << GetRequirementText(Destiny, 1, REQTYPE_FEAT, 0);
				strDescription << GetRequirementText(Destiny, 1, REQTYPE_ONEOF, 0);
				strDescription << Destiny->GetDescription(1);
				strDescription << "{\\par\\par}";
				break;
				}
			case 1:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Destiny->GetName();
				strDescription << " \\par}}";
				strDescription << "DP Cost: " << Destiny->GetDPCost();
				strDescription << " \\par\\par";
				//rank 1
				strDescription << "{\\cf1 Rank 1: \\par}";
				strDescription << Destiny->GetDescription(1);
				strDescription << "{\\par\\par}";
				if (TotalRanks > 1)
					{
					//rank 2
					strDescription << "{\\cf1 Rank 2: \\par}";
					strDescription << GetRequirementText(Destiny, 2, REQTYPE_DESTINY, 1);
					strDescription << GetRequirementText(Destiny, 2, REQTYPE_FEAT, 1);
					strDescription << GetRequirementText(Destiny, 2, REQTYPE_ONEOF, 1);
					strDescription << Destiny->GetDescription(2);
					strDescription << "{\\par\\par}";
					}
				break;
				}
			case 2:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Destiny->GetName();
				strDescription << " \\par}}";
				strDescription << "DP Cost: " << Destiny->GetDPCost();
				strDescription << " \\par\\par";
				//rank 2
				strDescription << "{\\cf1 Rank 2: \\par}";
				strDescription << Destiny->GetDescription(2);
				strDescription << "{\\par\\par}";
				if (TotalRanks > 2)
					{
					//rank 3
					strDescription << "{\\cf1 Rank 3: \\par}";
					strDescription << GetRequirementText(Destiny, 3, REQTYPE_DESTINY, 2);
					strDescription << GetRequirementText(Destiny, 3, REQTYPE_FEAT, 2);
					strDescription << GetRequirementText(Destiny, 3, REQTYPE_ONEOF, 2);
					strDescription << Destiny->GetDescription(3);
					strDescription << "{\\par\\par}";
					}
				break;
				}
			case 3:
				{
				strDescription << "{\\b {\\cf2";
				strDescription << Destiny->GetName();
				strDescription << " \\par}}";
				strDescription << "DP Cost: " << Destiny->GetDPCost();
				strDescription << " \\par\\par";
				//rank 3
				strDescription << "{\\cf1 Rank 3: \\par}";
				strDescription << Destiny->GetDescription(3);
				strDescription << "{\\par\\par}";
				break;
				}
			}
		strDescription << "}";
		}

	Tooltip = InterfaceManager.GetToolTipWindowPointer();
	Tooltip->SetToolTipText(strDescription.str());
	}

//-------------------------------------------------------------------
void Screen_Destiny_Base_Class::ShowToolTipWindow(bool Show)
	{
	ToolTipWindowClass *Tooltip;

	Tooltip = InterfaceManager.GetToolTipWindowPointer();
	Tooltip->Show(Show);

	if (Show == true)
		tme.dwHoverTime = 200;
	else 
		tme.dwHoverTime = 400;
	}



