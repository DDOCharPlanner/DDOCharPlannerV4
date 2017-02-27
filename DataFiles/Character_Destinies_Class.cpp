#include "Character_Destinies_Class.h"

//---------------------------------------------------------------------------
Character_Destinies_Class::Character_Destinies_Class()
	{
	}

//---------------------------------------------------------------------------
Character_Destinies_Class::~Character_Destinies_Class()
	{
	}

//---------------------------------------------------------------------------
Character_Destinies_Class::Character_Destinies_Class(const Character_Destinies_Class &source)
	{
	DEBUG("Copy Constructor");
	}

//---------------------------------------------------------------------------
Character_Destinies_Class& Character_Destinies_Class::operator=(const Character_Destinies_Class &source)
	{
	DEBUG("Assignment Operator");
	return *this;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::ClearAll()
	{
	CurrentActiveDestiny = DT_NONE;
	LevelEnforcement = true;
	ProgressEnforcement = true;
	for (unsigned int x=0; x<NUM_DESTINY_TREES; x++)
		{
		for (unsigned int y=0; y<7; y++)
			{
			for (unsigned int z=0; z<6; z++)
				{
				CharacterDestinySlots[x][y][z].Valid = false;
				CharacterDestinySlots[x][y][z].DestinyIndex.clear();
				CharacterDestinySlots[x][y][z].DestinyIndexChosen = 0;
				CharacterDestinySlots[x][y][z].RanksTaken  = 0;
				CharacterDestinySlots[x][y][z].LevelTaken[0] = 0;
				CharacterDestinySlots[x][y][z].LevelTaken[1] = 0;
				CharacterDestinySlots[x][y][z].LevelTaken[2] = 0;
				}
			}
		for (unsigned int j=0; j<MAXLEVEL-HEROICLEVELS; j++)
			SelectedDestinyLevel[x][j] = -1;
		}
	for (unsigned int k=0; k<3; k++)
		{
		TwistLevel[k] = 0;
		TwistedDestinySelected[k].TreeSelected = DT_NONE;
		TwistedDestinySelected[k].DestinySelected = -1;
		}
	}

//---------------------------------------------------------------------------
Character_Destinies_Class* Character_Destinies_Class::GetCharacterDestiniesAddress()
	{
	return this;
	}

//---------------------------------------------------------------------------
DESTINY_TREE Character_Destinies_Class::GetCurrentActiveDestiny()
	{
	return CurrentActiveDestiny;
	}

//---------------------------------------------------------------------------
int Character_Destinies_Class::GetDestinyIndex(int DestinyTree, int Tier, int Column, int Index)
	{
	return CharacterDestinySlots[DestinyTree][Tier][Column].DestinyIndex[Index];
	}
//---------------------------------------------------------------------------
int Character_Destinies_Class::GetDestinyIndexChosen(int DestinyTree, int Tier, int Column)
	{
	return CharacterDestinySlots[DestinyTree][Tier][Column].DestinyIndexChosen;
	}

//---------------------------------------------------------------------------
unsigned int Character_Destinies_Class::GetDestinyIndexSize(int DestinyTree, int Tier, int Column)
	{
	return CharacterDestinySlots[DestinyTree][Tier][Column].DestinyIndex.size();
	}

//---------------------------------------------------------------------------
bool Character_Destinies_Class::GetLevelEnforcement()
	{
	return LevelEnforcement;
	}

//---------------------------------------------------------------------------
int Character_Destinies_Class::GetLevelTaken(int DestinyTree, int Tier, int Column, int Rank)
	{
	return CharacterDestinySlots[DestinyTree][Tier][Column].LevelTaken[Rank];
	}

//---------------------------------------------------------------------------
bool Character_Destinies_Class::GetProgressEnforcement()
	{
	return ProgressEnforcement;
	}

//---------------------------------------------------------------------------
int Character_Destinies_Class::GetRanksTaken(int DestinyTree, int Tier, int Column)
	{
	return CharacterDestinySlots[DestinyTree][Tier][Column].RanksTaken;
	}

//---------------------------------------------------------------------------
int Character_Destinies_Class::GetSelectedDestinyLevel (int DestinyTree, int CharacterLevel)
	{
	return SelectedDestinyLevel[DestinyTree][CharacterLevel-HEROICLEVELS];
	}

//---------------------------------------------------------------------------
int Character_Destinies_Class::GetTwistedDestinySelectedDestinyIndex(int TwistSlot)
	{
	return TwistedDestinySelected[TwistSlot].DestinySelected;
	}

//---------------------------------------------------------------------------
DESTINY_TREE Character_Destinies_Class::GetTwistedDestinySelectedTree(int TwistSlot)
	{
	return TwistedDestinySelected[TwistSlot].TreeSelected;
	}

//---------------------------------------------------------------------------
int Character_Destinies_Class::GetTwistLevel(int TwistSlot)
	{
	return TwistLevel[TwistSlot];
	}

//---------------------------------------------------------------------------
bool Character_Destinies_Class::GetValid(int DestinyTree, int Tier, int Column)
	{
	return CharacterDestinySlots[DestinyTree][Tier][Column].Valid;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetValid(int DestinyTree, int Tier, int Column, bool NewValue)
	{
	CharacterDestinySlots[DestinyTree][Tier][Column].Valid = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetDestinyIndex(int DestinyTree, int Tier, int Column, int NewIndex)
	{
	CharacterDestinySlots[DestinyTree][Tier][Column].DestinyIndex.push_back(NewIndex);
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetDestinyIndexChosen(int DestinyTree, int Tier, int Column, int NewIndex)
	{
	CharacterDestinySlots[DestinyTree][Tier][Column].DestinyIndexChosen = NewIndex;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetRanksTaken(int DestinyTree, int Tier, int Column, int NewRank)
	{
	CharacterDestinySlots[DestinyTree][Tier][Column].RanksTaken = NewRank;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetLevelTaken(int DestinyTree, int Tier, int Column, int Rank, int NewLevel)
	{
	CharacterDestinySlots[DestinyTree][Tier][Column].LevelTaken[Rank] = NewLevel;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetSelectedDestinyLevel (int DestinyTree, int CharacterLevel, int NewLevel)
	{
	SelectedDestinyLevel[DestinyTree][CharacterLevel-HEROICLEVELS] = NewLevel;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetCurrentActiveDestiny(DESTINY_TREE NewDestinyTree)
	{
	CurrentActiveDestiny = NewDestinyTree;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetLevelEnforcement(bool NewValue)
	{
	LevelEnforcement = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetProgressEnforcement(bool NewValue)
	{
	ProgressEnforcement = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetTwistLevel(int TwistSlot, int NewValue)
	{
	TwistLevel[TwistSlot] = NewValue;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetTwistedDestinySelectedTree(int TwistSlot, DESTINY_TREE NewDestinyTree)
	{
	TwistedDestinySelected[TwistSlot].TreeSelected = NewDestinyTree;
	}

//---------------------------------------------------------------------------
void Character_Destinies_Class::SetTwistedDestinySelectedDestinyIndex(int TwistSlot, int NewIndex)
	{
	TwistedDestinySelected[TwistSlot].DestinySelected = NewIndex;
	}

//---------------------------------------------------------------------------
		
		
		
		
		
		