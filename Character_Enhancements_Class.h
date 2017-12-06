#pragma once

#include "stdafx.h"
#include "Data_Enhancement_Class.h"

struct CharacterEnhancementSlot
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
	vector <int> EnhancementIndex;
	int EnhancementIndexChosen;
	int RanksTaken;
	int LevelTaken[3];	//the max ranks that can be taken is 3 so we only need 3 of these
	};

class Character_Enhancements_Class
	{
	public:
		Character_Enhancements_Class();
		~Character_Enhancements_Class();
		//copy constructor and assignment operator
        Character_Enhancements_Class(const Character_Enhancements_Class &source);
        Character_Enhancements_Class& operator=(const Character_Enhancements_Class &source);

		void Clear();
		Character_Enhancements_Class* GetCharacterEnhancementsAddress();
		ENHANCEMENT_TREE GetTreeIndex(int Index);
		bool GetValid(int Tree, int Level, int Slot);
		unsigned int GetEnhancementIndexSize(int Tree, int Level, int Slot);
		int GetEnhancementIndex(int Tree, int Level, int Slot, int Index);
		int GetEnhancementIndexChosen(int Tree, int Level, int Slot);
		int GetRanksTaken(int Tree, int Level, int Slot);
		int GetLevelTaken(int Tree, int Level, int Slot, int Index);
		ENHANCEMENT_TREE SetTreeIndex(int Index);
		void SetValid(int Tree, int Level, int Slot, bool NewValue);
		void SetEnhancementIndex(int Tree, int Level, int Slot, unsigned int Index, int NewValue);
		void SetEnhancementIndexChosen(int Tree, int Level, int Slot, int NewValue);
		void SetRanksTaken(int Tree, int Level, int Slot, int NewValue);
		void SetLevelTaken(int Tree, int Level, int Slot, int Index, int NewValue);
		void SetTreeIndex(int Index, ENHANCEMENT_TREE NewTree);
		bool GetLevel5Lock(int Index);
		void SetLevel5Lock(int Index, bool Flag);
		void SetRaceEnhancements(RACE Race);
		void Save(HANDLE FileHandle);
		void LoadTrees(char* StringData);
		void LoadEnhancements(char* StringData);
		void ClearCharacterEnhancementSlots(int Tree);
		void CopyCharacterEnhancementSlots(int DestTree, int TreetobeCopied);
		int GetTotalEnhancementMod(MODCATEGORY Mod, string ModName, int SelectedLevel);
		void AutoDistribute();
		bool GetAPTome();
		void SetAPTome(bool state);		

	private:
		CharacterEnhancementSlot CharacterEnhancementSlots[7][6][6];
		ENHANCEMENT_TREE CharacterEnhancementTreeList[7];
		bool CharacterLevel5Lock[7];

		string ConvertEnhancementTreeToString(ENHANCEMENT_TREE Tree);
		int ConvertEnhancementTreeToIndex(ENHANCEMENT_TREE Tree);
		string ConvertEnhancementDataToString(int Tree, int Level, int Slot, int Rank);
		bool ValidateEnhancement(ENHANCEMENT_TREE Tree, int Level, int Slot, int Rank, int CharacterLevel, int CharacterAP);
		bool APTome;
	};

