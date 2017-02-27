#include "Character_Enhancements_Class.h"
#include "DataClass.h"
#include "EnhancementWindowClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"

//---------------------------------------------------------------------------
Character_Enhancements_Class::Character_Enhancements_Class()
	{
	}

//---------------------------------------------------------------------------
Character_Enhancements_Class::~Character_Enhancements_Class()
	{
	}

//---------------------------------------------------------------------------
Character_Enhancements_Class::Character_Enhancements_Class(const Character_Enhancements_Class &source)
	{
	for (unsigned int x=0; x<7; x++)
		{
		CharacterEnhancementTreeList[x] = source.CharacterEnhancementTreeList[x];
		CharacterLevel5Lock[x] = source.CharacterLevel5Lock[x];
		for (unsigned int y=0; y<6; y++)
			{
			for (unsigned int z=0; z<6; z++)
				{
				CharacterEnhancementSlots[x][y][z].Valid = source.CharacterEnhancementSlots[x][y][z].Valid;
				for (unsigned int i=0; i<source.CharacterEnhancementSlots[x][y][z].EnhancementIndex.size(); i++)
					CharacterEnhancementSlots[x][y][z].EnhancementIndex.push_back(source.CharacterEnhancementSlots[x][y][z].EnhancementIndex[i]);
				CharacterEnhancementSlots[x][y][z].EnhancementIndexChosen = source.CharacterEnhancementSlots[x][y][z].EnhancementIndexChosen;
				CharacterEnhancementSlots[x][y][z].RanksTaken = source.CharacterEnhancementSlots[x][y][z].RanksTaken;
				for (unsigned int i=0; i<3; i++)
					CharacterEnhancementSlots[x][y][z].LevelTaken[i] = source.CharacterEnhancementSlots[x][y][z].LevelTaken[i];
				}
			}
		}
	}

//---------------------------------------------------------------------------
Character_Enhancements_Class& Character_Enhancements_Class::operator=(const Character_Enhancements_Class &source)
	{
	for (unsigned int x=0; x<7; x++)
		{
		CharacterEnhancementTreeList[x] = source.CharacterEnhancementTreeList[x];
		CharacterLevel5Lock[x] = source.CharacterLevel5Lock[x];
		for (unsigned int y=0; y<6; y++)
			{
			for (unsigned int z=0; z<6; z++)
				{
				CharacterEnhancementSlots[x][y][z].Valid = source.CharacterEnhancementSlots[x][y][z].Valid;
				for (unsigned int i=0; i<source.CharacterEnhancementSlots[x][y][z].EnhancementIndex.size(); i++)
					CharacterEnhancementSlots[x][y][z].EnhancementIndex.push_back(source.CharacterEnhancementSlots[x][y][z].EnhancementIndex[i]);
				CharacterEnhancementSlots[x][y][z].EnhancementIndexChosen = source.CharacterEnhancementSlots[x][y][z].EnhancementIndexChosen;
				CharacterEnhancementSlots[x][y][z].RanksTaken = source.CharacterEnhancementSlots[x][y][z].RanksTaken;
				for (unsigned int i=0; i<3; i++)
					CharacterEnhancementSlots[x][y][z].LevelTaken[i] = source.CharacterEnhancementSlots[x][y][z].LevelTaken[i];
				}
			}
		}
	return *this;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::Clear()
	{
	for (unsigned int x=0; x<7; x++)
		{
		CharacterEnhancementTreeList[x] = ENHT_NOTREE;
		CharacterLevel5Lock[x] = false;
		for (unsigned int y=0; y<6; y++)
			{
			for (unsigned int z=0; z<6; z++)
				{
				CharacterEnhancementSlots[x][y][z].Valid = false;
				CharacterEnhancementSlots[x][y][z].EnhancementIndex.clear();
				CharacterEnhancementSlots[x][y][z].EnhancementIndexChosen = 0;
				CharacterEnhancementSlots[x][y][z].RanksTaken  = 0;
				CharacterEnhancementSlots[x][y][z].LevelTaken[0] = 0;
				CharacterEnhancementSlots[x][y][z].LevelTaken[1] = 0;
				CharacterEnhancementSlots[x][y][z].LevelTaken[2] = 0;
				}
			}
		}
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::ClearCharacterEnhancementSlots(int Tree)
	{
	for (int xLevel = 0; xLevel<6; xLevel++)
		{
		for (int xSlot = 0; xSlot<6; xSlot++)
			{
			CharacterEnhancementSlots[Tree][xLevel][xSlot].Valid = false;
			CharacterEnhancementSlots[Tree][xLevel][xSlot].EnhancementIndex.clear();
			CharacterEnhancementSlots[Tree][xLevel][xSlot].EnhancementIndexChosen = 0;
			CharacterEnhancementSlots[Tree][xLevel][xSlot].RanksTaken = 0;
			CharacterEnhancementSlots[Tree][xLevel][xSlot].LevelTaken[0] = 0;
			CharacterEnhancementSlots[Tree][xLevel][xSlot].LevelTaken[1] = 0;
			CharacterEnhancementSlots[Tree][xLevel][xSlot].LevelTaken[2] = 0;
			}
		}
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::CopyCharacterEnhancementSlots(int DestTree, int TreetoCopy)
	{
	for (int xLevel = 0; xLevel<6; xLevel++)
		{
		for (int xSlot = 0; xSlot<6; xSlot++)
			{
			CharacterEnhancementSlots[DestTree][xLevel][xSlot].Valid = CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].Valid;
			for (unsigned int xIndex = 0; xIndex<CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].EnhancementIndex.size(); xIndex++)
				{
				CharacterEnhancementSlots[DestTree][xLevel][xSlot].EnhancementIndex.push_back(CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].EnhancementIndex[xIndex]);
				}
			CharacterEnhancementSlots[DestTree][xLevel][xSlot].EnhancementIndexChosen = CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].EnhancementIndexChosen;
			CharacterEnhancementSlots[DestTree][xLevel][xSlot].RanksTaken = CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].RanksTaken;
			CharacterEnhancementSlots[DestTree][xLevel][xSlot].LevelTaken[0] = CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].LevelTaken[0];
			CharacterEnhancementSlots[DestTree][xLevel][xSlot].LevelTaken[1] = CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].LevelTaken[1];
			CharacterEnhancementSlots[DestTree][xLevel][xSlot].LevelTaken[2] = CharacterEnhancementSlots[TreetoCopy][xLevel][xSlot].LevelTaken[2];
			}
		}
	}

//---------------------------------------------------------------------------
Character_Enhancements_Class* Character_Enhancements_Class::GetCharacterEnhancementsAddress()
	{
	return this;
	}

//---------------------------------------------------------------------------
int Character_Enhancements_Class::GetEnhancementIndex(int Tree, int Level, int Slot, int Index)
	{
	return CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndex[Index];
	}

//---------------------------------------------------------------------------
unsigned int Character_Enhancements_Class::GetEnhancementIndexSize(int Tree, int Level, int Slot)
	{
	return CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndex.size();
	}

//----------------------------------------------------------------------------
int Character_Enhancements_Class::GetEnhancementIndexChosen(int Tree, int Level, int Slot)
	{
	return CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndexChosen;
	}

//---------------------------------------------------------------------------
bool Character_Enhancements_Class::GetLevel5Lock(int Index)
	{
	return CharacterLevel5Lock[Index];
	}

//---------------------------------------------------------------------------
int Character_Enhancements_Class::GetLevelTaken(int Tree, int Level, int Slot, int Index)
	{
	return CharacterEnhancementSlots[Tree][Level][Slot].LevelTaken[Index];
	}

//---------------------------------------------------------------------------
int Character_Enhancements_Class::GetRanksTaken(int Tree, int Level, int Slot)
	{
	return CharacterEnhancementSlots[Tree][Level][Slot].RanksTaken;
	}

//---------------------------------------------------------------------------
int Character_Enhancements_Class::GetTotalEnhancementMod(MODCATEGORY Mod, string ModName, int SelectedLevel)
	{
	int TotalMod;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	CharacterEnhancementSlot SlotData;
	string Category;
	int MonkLevel;

	switch (Mod)
		{
		case MC_ABILITY:
			{
			Category = "Ability";
			break;
			}
		case MC_ATTRIBUTE:
			{
			Category = "Attribute";
			break;
			}
		case MC_RESISTANCE:
			{
			Category = "Resistance";
			break;
			}
		case MC_SAVE:
			{
			Category = "Save";
			break;
			}
		case MC_SKILL:
			{
			Category = "Skill";
			break;
			}
		default:
			{
			return 0;
			}
		}

	TotalMod = 0;
	for (int x=0; x<7; x++)
		{
		for (int y=0; y<6; y++)
			{
			for (int z=0; z<6; z++)
				{
				SlotData = CharacterEnhancementSlots[x][y][z];
				if (SlotData.RanksTaken > 0)
					{
					if (SlotData.LevelTaken[SlotData.RanksTaken-1] <= SelectedLevel)
						{
						EnhancementTree = Data.GetEnhancementTreePointer(CharacterEnhancementTreeList[x]);
						Enhancement = EnhancementTree->GetEnhancementPointer(SlotData.EnhancementIndex[SlotData.EnhancementIndexChosen]);
						for (unsigned int i=0; i<Enhancement->GetModSize(SlotData.RanksTaken-1); i++)
							{
							if (Enhancement->GetModType(i, SlotData.RanksTaken-1) == Category)
								{
								if (Enhancement->GetModName(i, SlotData.RanksTaken-1) == ModName)
									{
									TotalMod += Enhancement->GetModValue(i, SlotData.RanksTaken-1);
									}
								}
							}
						//We need to check special cases for stuff
						//Hit Points
						if (EnhancementTree->GetTreeIndex() == ENHT_STALWART_DEFENDER_FTR && ModName == "Hit Points")
							TotalMod += 1;
						if (Enhancement->GetEnhancementName() == "Way of the Patient Tortoise" && ModName == "Hit Points")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod +=5;
							if (MonkLevel >= 3)
								TotalMod +=5;
							if (MonkLevel >= 9)
								TotalMod +=5;
							if (MonkLevel >= 15)
								TotalMod +=5;
							}
						//Concentration skill
						if (Enhancement->GetEnhancementName() == "Way of the Patient Tortoise" && ModName == "Concentration")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod +=1;
							if (MonkLevel >= 3)
								TotalMod +=1;
							if (MonkLevel >= 9)
								TotalMod +=1;
							if (MonkLevel >= 15)
								TotalMod +=1;
							}
						//Diplomacy skill
						if (Enhancement->GetEnhancementName() == "Way of the Elegant Crane" && ModName == "Diplomacy")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod +=1;
							if (MonkLevel >= 3)
								TotalMod +=1;
							if (MonkLevel >= 9)
								TotalMod +=1;
							if (MonkLevel >= 15)
								TotalMod +=1;
							}
						//Haggle skill
						if (Enhancement->GetEnhancementName() == "Way of the Clever Monkey" && ModName == "Haggle")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod +=1;
							if (MonkLevel >= 3)
								TotalMod +=1;
							if (MonkLevel >= 9)
								TotalMod +=1;
							if (MonkLevel >= 15)
								TotalMod +=1;
							}
						//Intimidate skill
						if (Enhancement->GetEnhancementName() == "Way of the Tenacious Badger" && ModName == "Intimidate")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod +=1;
							if (MonkLevel >= 3)
								TotalMod +=1;
							if (MonkLevel >= 9)
								TotalMod +=1;
							if (MonkLevel >= 15)
								TotalMod +=1;
							}
						//Listen skill
						if (Enhancement->GetEnhancementName() == "Way of the Faithful Hound" && ModName == "Listen")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod +=1;
							if (MonkLevel >= 3)
								TotalMod +=1;
							if (MonkLevel >= 9)
								TotalMod +=1;
							if (MonkLevel >= 15)
								TotalMod +=1;
							}
						//Fortitude Save
						if (Enhancement->GetEnhancementName() == "Way of the Elegant Crane" && ModName == "Fortitude")
							{
							MonkLevel = Character.GetClassLevel(MONK, SelectedLevel);
							if (MonkLevel >= 1)
								TotalMod -=1;
							if (MonkLevel >= 3)
								TotalMod -=1;
							if (MonkLevel >= 9)
								TotalMod -=1;
							if (MonkLevel >= 15)
								TotalMod -=1;
							}
						}
					}
				} //end for z
			}// end for y
		}// end for x
		
	return TotalMod;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::AutoDistribute()
	{
		//Function Dropped unsure of character benifite jonesth3
		return;
	struct EnhancementListStruct
		{
		EnhancementListStruct(){};
		//requires a copy constructor
        EnhancementListStruct(const EnhancementListStruct &source)
			{
			Tree = source.Tree;
			Level = source.Level;
			Slot = source.Slot;
			Rank = source.Rank;
			OutputDebugString("Copy constructor\r\n");
			}
        EnhancementListStruct& operator=(const EnhancementListStruct &source)
			{
			Tree = source.Tree;
			Level = source.Level;
			Slot = source.Slot;
			Rank = source.Rank;
			OutputDebugString("Assignment Operator\r\n");
			return *this;
			}
		ENHANCEMENT_TREE Tree;
		unsigned int Level;
		unsigned int Slot;
		int Rank;
		};

	vector <EnhancementListStruct> EnhancementList;
	vector <unsigned int> ValidEnhancementList;
	EnhancementListStruct NewEnhancementList;
	int CharacterLevelToFill;
	int CharacterAP;
	Data_Enhancement_Tree_Class* CurrentTree;
	Data_Enhancement_Class* CurrentEnhancement;
	ostringstream ss;

	//step 0: dump all the current LevelTaken entries. We're going to overwrite them anyway
	//  and setting them to 0 now will make validation of what we've already moved easier
	for (unsigned int Tree=0; Tree<7; Tree++)
		{
		for (unsigned int Level=0; Level<6; Level++)
			{
			for (unsigned int Slot=0; Slot<6; Slot++)
				{
				for (int Rank=0; Rank<3; Rank++)
					{
					CharacterEnhancementSlots[Tree][Level][Slot].LevelTaken[Rank] = 0;
					}
				}
			}
		}

	//step 1: get a copy of the list of all current enhancements at all levels
	//  this is what we will draw from as we are moving enhancements around
	for (unsigned int Tree=0; Tree<7; Tree++)
		{
		for (unsigned int Level=0; Level<6; Level++)
			{
			for (unsigned int Slot=0; Slot<6; Slot++)
				{
				for (int Rank=0; Rank<CharacterEnhancementSlots[Tree][Level][Slot].RanksTaken; Rank++)
					{
					//if we are here, the enhancement is valid, and the user has selected at least one rank
					NewEnhancementList.Tree = CharacterEnhancementTreeList[Tree];
					NewEnhancementList.Level = Level;
					NewEnhancementList.Slot = Slot;
					NewEnhancementList.Rank = Rank;
					EnhancementList.push_back(NewEnhancementList);
					ss.str("");
					ss << "Enhancement List Size " << EnhancementList.size() << "\r\n";
					OutputDebugString(ss.str().c_str());
					}
				}
			}
		}
	ss.str("");
	ss << "Enhancement List Final Size " << EnhancementList.size() << "\r\n";
	OutputDebugString(ss.str().c_str());

	for (unsigned int i=0; i<EnhancementList.size(); i++)
		{
		ss.str("");
		ss << EnhancementList[i].Tree << ", " << EnhancementList[i].Level << ", " << EnhancementList[i].Slot << ", " << EnhancementList[i].Rank << "\r\n";
		OutputDebugString(ss.str().c_str());
		}
		
	//initial values
	CharacterLevelToFill = 1;
	CharacterAP = 4;

	//from here, we simply iterate until our list size is zero
	while (EnhancementList.size() > 0)
		{
		//step 2: Get a list of all enhancements that are currently valid and store their index
		//clear the list and start over every time we are looking to place an enhancement
		ValidEnhancementList.clear();
		for (unsigned int i=0; i<EnhancementList.size(); i++)
			{
			//Validate the individual enhancements against the character/class level, AP, and prereqs. Those that pass, store in ValidEnhancementList
			if (ValidateEnhancement(EnhancementList[i].Tree, EnhancementList[i].Level, EnhancementList[i].Slot, EnhancementList[i].Rank, CharacterLevelToFill, CharacterAP) == true)
				{
				ValidEnhancementList.push_back(i);
				}
			}
		//step 3(a): Any valid enhancements? Yes: Pick one and modify the LevelTaken entry
		if (ValidEnhancementList.size() > 0)
			{
			//which one do we pick? The first one? Sure, why not.
			// set the characters LevelTaken field.
			CharacterEnhancementSlots[EnhancementList[ValidEnhancementList[0]].Tree][EnhancementList[ValidEnhancementList[0]].Level][EnhancementList[ValidEnhancementList[0]].Slot].LevelTaken[EnhancementList[ValidEnhancementList[0]].Rank] = CharacterLevelToFill;
			//remove it from the list and reduce our available AP
			CurrentTree = Data.GetEnhancementTreePointer(EnhancementList[ValidEnhancementList[0]].Tree);
			CurrentEnhancement = CurrentTree->GetEnhancementPointer(EnhancementList[ValidEnhancementList[0]].Level, EnhancementList[ValidEnhancementList[0]].Slot, CharacterEnhancementSlots[EnhancementList[ValidEnhancementList[0]].Tree][EnhancementList[ValidEnhancementList[0]].Level][EnhancementList[ValidEnhancementList[0]].Slot].EnhancementIndexChosen);
			EnhancementList.erase(EnhancementList.begin() + ValidEnhancementList[0]);
			CharacterAP -= CurrentEnhancement->GetEnhancementCost();
			}
		//step 3(b): Any valid enhancement? No: Move to the next level
		else
			{
			CharacterLevelToFill++;
			CharacterAP += 4;
			//avoid infinite loop syndrome!
			if (CharacterLevelToFill > HEROICLEVELS)
				{
				OutputDebugString("Error in Auto Distribute Routine: Unable to fully distribute enhancements!\r\n");
				break;
				}
			}
		}
	}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE Character_Enhancements_Class::GetTreeIndex(int Index)
	{
	return CharacterEnhancementTreeList[Index];
	}

//---------------------------------------------------------------------------
bool Character_Enhancements_Class::GetValid(int Tree, int Level, int Slot)
	{
	return CharacterEnhancementSlots[Tree][Level][Slot].Valid;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetEnhancementIndex(int Tree, int Level, int Slot, unsigned int Index, int NewValue)
	{
	if (Index < CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndex.size())
		CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndex[Index] = NewValue;
	else
		CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndex.push_back(NewValue);
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetEnhancementIndexChosen(int Tree, int Level, int Slot, int NewValue)
	{
	CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndexChosen = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetLevel5Lock(int Index, bool Flag)
	{
	CharacterLevel5Lock[Index] = Flag;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetLevelTaken(int Tree, int Level, int Slot, int Index, int NewValue)
	{
	CharacterEnhancementSlots[Tree][Level][Slot].LevelTaken[Index] = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetRaceEnhancements(RACE NewRace)
	{
	if (CharacterEnhancementTreeList[0] != ENHT_NOTREE)
		{
		//CharacterEnhancementTreeList[0] = Character GetRaceTree(NewRace);
		}
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::Save(HANDLE FileHandle)
	{
	char WriteBuffer[1024];
	DWORD BytesWritten;
	string EnhancementString;

	StringCbPrintf(WriteBuffer, 1024, "ENHANCEMENTTREELIST: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<7; i++)
        {
		StringCbPrintf(WriteBuffer, 1024, ConvertEnhancementTreeToString(CharacterEnhancementTreeList[i]).c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		StringCbPrintf(WriteBuffer, 1024, ",\r\n");
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "ENHANCEMENTLIST: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<7; i++)
		{
	    for (unsigned int j=0; j<6; j++)
			{
			for (unsigned int k=0; k<6; k++)
				{
				if (CharacterEnhancementSlots[i][j][k].Valid == true)
					{
					for (int l=0; l<CharacterEnhancementSlots[i][j][k].RanksTaken; l++)
						{
						EnhancementString = ConvertEnhancementDataToString(i, j, k, l);
						StringCbPrintf(WriteBuffer, 1024, EnhancementString.c_str());
						WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
						}
					}
				}
			}
		}
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::LoadTrees(char *StringData)
	{
    char *DataPointer;
	char SubString[256];
    string String1;
	Data_Enhancement_Tree_Class* EnhancementTree;
	Data_Enhancement_Class* Enhancement;
	int NumofMultiEnhancements;
	int hyphenloc;
	Clear();
    DataPointer = StringData;
    DataPointer += 2;
    for (int i=0; i<7; i++)
		{
		strncpy_s (SubString, DataPointer, strstr(DataPointer, ",") - DataPointer);
		SubString[strstr(DataPointer, ",") - DataPointer] = '\0';
		String1 = SubString;
		//remove hypen from name
		hyphenloc = String1.find("-");
		if (hyphenloc > 0)
		{
			String1[hyphenloc] = ' ';
		}
		CharacterEnhancementTreeList[i] = Data.GetEnhTreeIndex(String1);
		DataPointer = strstr(DataPointer, ",");
	    DataPointer += 3;
		}

	//we need to set the Valid and EnhancementIndex entries for the CharacterEnhancementSlots structure
    for (unsigned int i=0; i<7; i++)
		{
		EnhancementTree = Data.GetEnhancementTreePointer (CharacterEnhancementTreeList[i]);	
	    for (unsigned int j=0; j<6; j++)
			{
			for (unsigned int k=0; k<6; k++)
				{
				CharacterEnhancementSlots[i][j][k].Valid = EnhancementTree->DoesSlotHaveEnhancement(j, k);
				if (CharacterEnhancementSlots[i][j][k].Valid == false)
					continue;
				Enhancement = EnhancementTree->GetEnhancementPointer (j, k);
				if (Enhancement->GetEnhMultiSelection() == true)
					{
					CharacterEnhancementSlots[i][j][k].EnhancementIndex.push_back(Data.GetEnhMultiSelectorIndex(Enhancement->GetEnhMultiName()));
					NumofMultiEnhancements = EnhancementTree->GetMultiEnhancementsSize(Enhancement->GetEnhancementIndex());
					for (int x=1; x<=NumofMultiEnhancements; x++)
						{
						CharacterEnhancementSlots[i][j][k].EnhancementIndex.push_back(EnhancementTree->GetEnhancementIndex(j, k, x));
						}
					}
				else
					{
					CharacterEnhancementSlots[i][j][k].EnhancementIndex.push_back(Enhancement->GetEnhancementIndex());
					}
				}
			}
		}
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::LoadEnhancements(char *StringData)
	{
	string String1;
	string TextLine;
	string TreeString;
	string EnhancementString;
	Data_Enhancement_Tree_Class *Tree;
	Data_Enhancement_Class *Enhancement;
	int EnhancementLevel;
	int EnhancementSlot;
	int MultiSlot;
	int TreeIndex;
	int CurrentRank;
	int hyphenloc;

    String1 = StringData;
	String1 = String1.substr(2, String1.size());
	while (String1.find(",") != string::npos)
		{
		TextLine = String1.substr(0, String1.find(","));
		TreeString = TextLine.substr(0, TextLine.find("::"));
		//remove hypen from name
		hyphenloc = TreeString.find("-");
		if (hyphenloc > 0)
		{
			TreeString[hyphenloc] = ' ';
		}
		Tree = Data.GetEnhancementTreePointer (TreeString);
		TextLine = TextLine.substr(TextLine.find("::")+2, TextLine.size());
		EnhancementString = TextLine.substr(0, TextLine.find("[")-1);
		TextLine = TextLine.substr(TextLine.find("[")+1, TextLine.size());
		EnhancementLevel = atoi(TextLine.c_str());
		TextLine = TextLine.substr(TextLine.find("-")+1, TextLine.size());
		EnhancementSlot = atoi(TextLine.c_str());
		TextLine = TextLine.substr(TextLine.find("-")+1, TextLine.size());
		MultiSlot = atoi(TextLine.c_str());
		TextLine = TextLine.substr(TextLine.find("-")+1, TextLine.size());
		
		//sanity check. Make sure the loaded enhancement is still in the tree at the same place (otherwise, we ignore this entry)
		if (MultiSlot == 0)
			Enhancement = Tree->GetEnhancementPointer (EnhancementLevel, EnhancementSlot);
		else
			Enhancement = Tree->GetEnhancementPointer (EnhancementLevel, EnhancementSlot, MultiSlot);
		if (Enhancement->GetEnhancementName() == EnhancementString)
			{
			//okay, we're good, this is a valid enhancement
			//figure out our tree 
			TreeIndex = ConvertEnhancementTreeToIndex(Tree->GetTreeIndex());
			if (TreeIndex != -1)
				{
				CharacterEnhancementSlots[TreeIndex][EnhancementLevel][EnhancementSlot].EnhancementIndexChosen = MultiSlot;
				CurrentRank = atoi(TextLine.c_str());
				CharacterEnhancementSlots[TreeIndex][EnhancementLevel][EnhancementSlot].RanksTaken = CurrentRank;
				TextLine = TextLine.substr(TextLine.find("-")+1, TextLine.size());
				CharacterEnhancementSlots[TreeIndex][EnhancementLevel][EnhancementSlot].LevelTaken[CurrentRank-1] = atoi(TextLine.c_str());
				}
			}
		String1 = String1.substr(String1.find(",")+3, String1.size());
		}
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetRanksTaken(int Tree, int Level, int Slot, int NewValue)
	{
	CharacterEnhancementSlots[Tree][Level][Slot].RanksTaken = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetTreeIndex(int Index, ENHANCEMENT_TREE NewTree)
	{
	CharacterEnhancementTreeList[Index] = NewTree;
	}

//---------------------------------------------------------------------------
void Character_Enhancements_Class::SetValid(int Tree, int Level, int Slot, bool NewValue)
	{
	CharacterEnhancementSlots[Tree][Level][Slot].Valid = NewValue;
	}

//---------------------------------------------------------------------------
string Character_Enhancements_Class::ConvertEnhancementTreeToString(ENHANCEMENT_TREE Tree)
	{
	Data_Enhancement_Tree_Class *TreeData;

	TreeData = Data.GetEnhancementTreePointer(Tree);
	return TreeData->GetTreeName();
	}

//---------------------------------------------------------------------------
int Character_Enhancements_Class::ConvertEnhancementTreeToIndex(ENHANCEMENT_TREE Tree)
	{
	for (unsigned int i=0; i<7; i++)
		if (CharacterEnhancementTreeList[i] == Tree)
			return i;

	return -1;
	}

//---------------------------------------------------------------------------
string Character_Enhancements_Class::ConvertEnhancementDataToString(int Tree, int Level, int Slot, int Rank)
	{
	ostringstream Result;
	Data_Enhancement_Tree_Class* EnhancementTree;
	Data_Enhancement_Class* Enhancement;

	Result << ConvertEnhancementTreeToString(CharacterEnhancementTreeList[Tree]);
	Result << "::";
	
	//grab an enhancement pointer
	EnhancementTree = Data.GetEnhancementTreePointer (CharacterEnhancementTreeList[Tree]);	
	if (CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndexChosen > 0)
		Enhancement = EnhancementTree->GetEnhancementPointer(Level, Slot, CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndexChosen);
	else
		Enhancement = EnhancementTree->GetEnhancementPointer(Level, Slot);

	Result << Enhancement->GetEnhancementName();
	Result << " [" << Level << "-" << Slot << "-" << CharacterEnhancementSlots[Tree][Level][Slot].EnhancementIndexChosen;
	Result << "-" << Rank+1 << "-" << CharacterEnhancementSlots[Tree][Level][Slot].LevelTaken[Rank] << "],\r\n";
	return Result.str(); 
	}

//---------------------------------------------------------------------------
bool Character_Enhancements_Class::ValidateEnhancement(ENHANCEMENT_TREE Tree, int Level, int Slot, int Rank, int CharacterLevel, int CharacterAP)
	{
	Data_Enhancement_Tree_Class* CurrentTree;
	Data_Enhancement_Class* CurrentEnhancement;
	Data_Enhancement_Class* BoughtEnhancement;
	int APSpent;
	int APRequired;
	int ChosenTree;

	//we need to find the correct tree we are working with
	for (int i=0; i<7; i++)
		{
		if (CharacterEnhancementTreeList[i] == Tree)
			ChosenTree = i;
		}

	CurrentTree = Data.GetEnhancementTreePointer(Tree);
	CurrentEnhancement = CurrentTree->GetEnhancementPointer(CharacterEnhancementSlots[ChosenTree][Level][Slot].EnhancementIndex[CharacterEnhancementSlots[ChosenTree][Level][Slot].EnhancementIndexChosen]);
	
	//do we have enough AP to buy this?
	if (CurrentEnhancement->GetEnhancementCost() > CharacterAP)
		return false;

	//have we spent enough AP in the tree to buy this?
	APSpent = 0;
	APRequired = CurrentEnhancement->GetAPRequirement();
	for (unsigned int i=0; i<6; i++)
		{
		for (unsigned int j=0; j<6; j++)
			{
			for (unsigned int k=0; k<3; k++)
				{
				if (CharacterEnhancementSlots[ChosenTree][i][j].LevelTaken[k] > 0 && CharacterEnhancementSlots[ChosenTree][i][j].LevelTaken[k] <= CharacterLevel)
					{
					BoughtEnhancement = CurrentTree->GetEnhancementPointer(CharacterEnhancementSlots[ChosenTree][i][j].EnhancementIndex[CharacterEnhancementSlots[ChosenTree][i][j].EnhancementIndexChosen]);
					APSpent += BoughtEnhancement->GetEnhancementCost();
					}
				}
			}
		}
	if (APSpent < APRequired)
		return false;


	
	return true;
	}

