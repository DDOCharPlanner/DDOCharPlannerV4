#include "Data_Destiny_Tree_Class.h"

//---------------------------------------------------------------------------
Data_Destiny_Tree_Class::Data_Destiny_Tree_Class()
	{
	}

//---------------------------------------------------------------------------
Data_Destiny_Tree_Class::~Data_Destiny_Tree_Class()
	{
	}

//---------------------------------------------------------------------------
void Data_Destiny_Tree_Class::InitializeDestinyTree(DESTINY_TREE DTree, string Name, bool DestinyFlag, string Graphic, string Icon, string Arrows, DESTINY_SPHERE Sphere, DESTINY_TREE AdjacentDestiny1, DESTINY_TREE AdjacentDestiny2, DESTINY_TREE AdjacentSphereDestinyConnection)
	{
	size_t EndLoc;
	string Substring;
	ArrowStruct NewArrow;

	TreeIndex = DTree;
	TreeName = Name;
	DestinySphere = Sphere;
	HasDestinies = DestinyFlag;
	LoadBitmap(Graphic, "UserInterface", &TreeBackground);
	LoadBitmap(Icon, "UserInterface", &TreeIcon);
	DestinyData.clear();

	while (Arrows.find(",") != string::npos)
		{
		StripStringLeadingWhiteSpace(Arrows);
		EndLoc = Arrows.find(",");
		Substring = Arrows.substr(0, EndLoc);
		//Now that we have an individual string, lets break it down to its components.
		ArrowPlacement.push_back(NewArrow);
		ArrowPlacement[ArrowPlacement.size()-1].Level = atoi(Substring.substr(0, 1).c_str());
		ArrowPlacement[ArrowPlacement.size()-1].Slot = atoi(Substring.substr(2, 1).c_str());
		if (Substring.substr(4,1) == "U")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_UP;
		if (Substring.substr(4,1) == "L")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_LEFT;
		if (Substring.substr(4,1) == "R")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_RIGHT;
		ArrowPlacement[ArrowPlacement.size()-1].Length = atoi(Substring.substr(6,1).c_str());
		Arrows.erase(0, EndLoc +1);
		}
	if (Arrows != "")
		{
		Substring = Arrows;
		StripStringLeadingWhiteSpace(Substring);
		ArrowPlacement.push_back(NewArrow);
		ArrowPlacement[ArrowPlacement.size()-1].Level = atoi(Substring.substr(0, 1).c_str());
		ArrowPlacement[ArrowPlacement.size()-1].Slot = atoi(Substring.substr(2, 1).c_str());
		if (Substring.substr(4,1) == "U")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_UP;
		if (Substring.substr(4,1) == "L")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_LEFT;
		if (Substring.substr(4,1) == "R")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_RIGHT;
		ArrowPlacement[ArrowPlacement.size()-1].Length = atoi(Substring.substr(6,1).c_str());
		}
	AdjacentDestiny[0] = AdjacentDestiny1;
	AdjacentDestiny[1] = AdjacentDestiny2;
	AdjacentSphereDestiny = AdjacentSphereDestinyConnection;

	}

//---------------------------------------------------------------------------
void Data_Destiny_Tree_Class::AddNewDestiny(string DestinyDataString)
	{
	Data_Destiny_Class DummyDestiny;

	DestinyData.push_back(DummyDestiny);
	DestinyData[DestinyData.size()-1].InitializeDestiny(DestinyDataString, TreeIndex, DestinyData.size()-1);
	}

//---------------------------------------------------------------------------
bool Data_Destiny_Tree_Class::DoesTreeHaveDestinies()
	{
	return HasDestinies;
	}

//---------------------------------------------------------------------------
ArrowStruct Data_Destiny_Tree_Class::GetArrowPlacement(unsigned int Index)
	{
	return ArrowPlacement[Index];
	}

//---------------------------------------------------------------------------
unsigned int Data_Destiny_Tree_Class::GetArrowPlacementSize()
	{
	return ArrowPlacement.size();
	}

//---------------------------------------------------------------------------
int Data_Destiny_Tree_Class::GetDestinyIndex(int Tier, int Column, unsigned int MSlot)
	{
	ostringstream ss;
	string text;
	for (unsigned int x=0; x<DestinyData.size(); x++)
		{
		if (Tier == DestinyData[x].GetTier())
			{
			if (Column == DestinyData[x].GetSlot())
				{
				if (DestinyData[x].GetMultiSelection() == true)
					{
					if (MSlot == DestinyData[x].GetMultiSelectorSlot())
						return x;
					}
				else
					{
					if (MSlot == 0)
						return x;
					else
						return -1;
					}
				}
			}
		}
	//We shouldn't make it to here so lets output the details
	ss.str("");
	ss << "Tier: " << Tier << ", Slot: " << Column << ", MSLOT: " << MSlot;
	text = ss.str();
	OutputDebugString ("DataDestinyTree::GetDestinyIndex: Error: Could not find a destiny matching ( ");
	OutputDebugString (text.c_str());
	OutputDebugString (" )\r\n");
	return -1;
	}

//---------------------------------------------------------------------------
Data_Destiny_Class* Data_Destiny_Tree_Class::GetDestinyPointer(unsigned int DestinyIndex)
	{
	return DestinyData[DestinyIndex].GetDestinyAddress();
	}

//---------------------------------------------------------------------------
Data_Destiny_Class* Data_Destiny_Tree_Class::GetDestinyPointer(unsigned int Tier, unsigned int Column)
	{
	int DestinyIndex;

	DestinyIndex = -1;
	for (unsigned int x=0; x<DestinyData.size(); x++)
		{
		if (Tier == DestinyData[x].GetTier())
			{
			if (Column == DestinyData[x].GetSlot())
				{
				DestinyIndex = x;
				break;
				}
			}
		}
	if (DestinyIndex == -1)
		return nullptr;
	
	return DestinyData[DestinyIndex].GetDestinyAddress();
	}

//---------------------------------------------------------------------------
DESTINY_SPHERE Data_Destiny_Tree_Class::GetDestinySphere()
	{
	return DestinySphere;
	}

//---------------------------------------------------------------------------
Data_Destiny_Tree_Class* Data_Destiny_Tree_Class::GetDestinyTreeAddress()
	{
	return this;
	}

//---------------------------------------------------------------------------
unsigned int Data_Destiny_Tree_Class::GetNumofDestinies(int DestinyIndex)
	{
	int Tier;
	int Column;
	unsigned int Size = 0;

	Tier = DestinyData[DestinyIndex].GetTier();
	Column = DestinyData[DestinyIndex].GetSlot();

	for (unsigned int x=0; x <DestinyData.size(); x++)
		{
		if (DestinyData[x].GetTier() == Tier)
			if (DestinyData[x].GetSlot() == Column)
				Size++;
		}
	return Size;
	}

//---------------------------------------------------------------------------
GraphicStruct Data_Destiny_Tree_Class::GetTreeBackground()
	{
	return TreeBackground;
	}

//---------------------------------------------------------------------------
GraphicStruct Data_Destiny_Tree_Class::GetTreeIcon()
	{
	return TreeIcon;
	}

//---------------------------------------------------------------------------
DESTINY_TREE Data_Destiny_Tree_Class::GetTreeIndex()
	{
	return TreeIndex;
	}

//---------------------------------------------------------------------------
string Data_Destiny_Tree_Class::GetTreeName()
	{
	return TreeName;
	}

//---------------------------------------------------------------------------
void Data_Destiny_Tree_Class::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}

