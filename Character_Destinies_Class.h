# pragma once

#include "stdafx.h"

struct CharacterDestinySlot
	{
	bool Valid;
		//-- Explanation for the following 2 variables---------------------------------------------------
		//----- EnhancementIndex is used for holding the index to Enhancments and MultiEnhancements, ----
		//----- for a Single enhancement put the index in the 0 position, for multi enhancements, the ---
		//----- 0 position will hold the MultiEnhancement Index, the rest will hold the Enhancment indexes
		//----- that are part of the multi.
		//----- EnhancementIndexChosen Controls what EnhancementIndex is chosen. For a single Enhancement-
		//----- this will always be 0, for Multi Enhancements, it will be 0 if an enhancement wasn't -----
		//----- chosen yet, otherwise it will show the chosen index (1 to Infinity)
	vector <int> DestinyIndex;
	int DestinyIndexChosen;
	int RanksTaken;
	int LevelTaken[3];	//the max ranks that can be taken is 3 so we only need 3 of these
	};

struct TwistedSlot
	{
	DESTINY_TREE TreeSelected;
	int DestinySelected;
	};

class Character_Destinies_Class
	{
	public:
		Character_Destinies_Class();
		~Character_Destinies_Class();
		//copy constructor and assignment operator
        Character_Destinies_Class(const Character_Destinies_Class &source);
        Character_Destinies_Class& operator=(const Character_Destinies_Class &source);

		void ClearAll();
		Character_Destinies_Class* GetCharacterDestiniesAddress();

		//Get private variable functions
		bool GetValid(int DestinyTree, int Tier, int Column);
		unsigned int GetDestinyIndexSize(int DestinyTree, int Tier, int Column);
		int GetDestinyIndex(int DestinyTree, int Tier, int Column, int Index);
		int GetDestinyIndexChosen(int DestinyTree, int Tier, int Column);
		int GetRanksTaken(int DestinyTree, int Tier, int Column);
		int GetLevelTaken(int DestinyTree, int Tier, int Column, int Rank);
		int GetSelectedDestinyLevel (int DestinyTree, int CharacterLevel);
		DESTINY_TREE GetCurrentActiveDestiny();
		bool GetLevelEnforcement();
		bool GetProgressEnforcement();
		int GetTwistLevel(int TwistSlot);
		DESTINY_TREE GetTwistedDestinySelectedTree(int TwistSlot);
		int GetTwistedDestinySelectedDestinyIndex(int TwistSlot);

		//Set private variable functions
		void SetValid(int DestinyTree, int Tier, int Column, bool NewValue);
		void SetDestinyIndex(int DestinyTree, int Tier, int Column, int NewIndex);
		void SetDestinyIndexChosen(int DestinyTree, int Tier, int Column, int NewIndex);
		void SetRanksTaken(int DestinyTree, int Tier, int Column, int NewRank);
		void SetLevelTaken(int DestinyTree, int Tier, int Column, int Rank, int NewLevel);
		void SetSelectedDestinyLevel (int DestinyTree, int CharacterLevel, int NewLevel);
		void SetCurrentActiveDestiny(DESTINY_TREE NewDestinyTree);
		void SetLevelEnforcement(bool NewValue);
		void SetProgressEnforcement(bool NewValue);
		void SetTwistLevel(int TwistSlot, int NewValue);
		void SetTwistedDestinySelectedTree(int TwistSlot, DESTINY_TREE NewDestinyTree);
		void SetTwistedDestinySelectedDestinyIndex(int TwistSlot, int NewIndex);

	private:
		CharacterDestinySlot CharacterDestinySlots[NUM_DESTINY_TREES][7][6];
		DESTINY_TREE CurrentActiveDestiny;
		int SelectedDestinyLevel[NUM_DESTINY_TREES][MAXLEVEL-HEROICLEVELS];
		bool LevelEnforcement;
		bool ProgressEnforcement;
		int TwistLevel[3];
		TwistedSlot TwistedDestinySelected[3];
	};

