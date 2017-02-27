#pragma once

#include "stdafx.h"
#include "IconClass.h"
#include "Data_Enhancement_MultiSelector_Class.h"

struct ENH_Requirement
	{
	ENH_REQTYPE ReqType;
	string ReqName;
	string ReqTree;
	int ReqLevel;
	int ReqSlot;
	int ReqMSlot;
	int ReqRank;
	};
	
class Data_Enhancement_Class : public IconClass
	{
	public:
		Data_Enhancement_Class();
		virtual ~Data_Enhancement_Class();
		//copy constructor and assignment operator
        Data_Enhancement_Class(const Data_Enhancement_Class &source);
        Data_Enhancement_Class& operator=(const Data_Enhancement_Class &source);

		void InitializeEnhancement(string Data, ENHANCEMENT_TREE TIndex, unsigned int EIndex);
		Data_Enhancement_Class* GetEnhancementAddress();
		Data_Enhancement_MultiSelector_Class* GetMultiSelectorPointer();
		ENHANCEMENT_TREE GetTreeIndex();
		unsigned int GetEnhancementIndex();
		int GetEnhancementLevel();
		int GetEnhancementSlot();
		bool GetEnhTypeActive();
		int GetEnhancementCost();
		int GetEnhancementRanks();
		bool GetEnhMultiSelection();
		unsigned int GetEnhancementMSlot();
		GraphicStruct GetEnhancementIcon();
		string GetEnhMultiName();
		string GetEnhancementName();
		string GetDescription(int Rank);
		int GetCharacterLevelRequirement();
		int GetClassLevelRequirement();
		int GetAPRequirement();	
		unsigned int GetLockSize(int Rank);
		ENH_REQTYPE GetLockType(int Rank, int Index);
		string GetLockName(int Rank, int Index);
		string GetLockTreeName(int Rank, int Index);
		int GetLockLevel(int Rank, int Index);
		int GetLockSlot(int Rank, int Index);
		int GetLockRank(int Rank, int Index);
		unsigned int GetRequirementSize(int Rank);
		ENH_REQTYPE GetRequirementType(int Rank, int Index);
		string GetRequirementName(int Rank, int Index);
		int GetRequirementLevel(int Rank, int Index);
		int GetRequirementSlot(int Rank, int Index);
		int GetRequirementRank(int Rank, int Index);
		unsigned int GetRequirementOneSize(int Rank);
		ENH_REQTYPE GetRequirementOneType(int Rank, int Index);
		int GetRequirementOneLevel(int Rank, int Index);
		int GetRequirementOneSlot(int Rank, int Index);
		int GetRequirementOneRank(int Rank, int Index);
		string GetRequirementOneTree(int Rank, int Index);
		string GetRequirementOneName(int Rank, int Index);
		CLASS GetTreeClass();
		RACE GetTreeRace();
		string GetRaceName();
		string GetClassName();
		string GetModType(int Index, int Rank);
		string GetModName(int Index, int Rank);
		int GetModValue(int Index, int Rank);
		unsigned int GetModSize(int Rank);

	private:	
		ENHANCEMENT_TREE TreeIndex;
		unsigned int EnhancementIndex;
		bool MultiSelection;
		string MultiSelectorName;
		unsigned int MultiSelectorSlot;
		string Name;
		string Tree;
		bool RaceTree;
		bool RaceAATree;
		RACE Race;
		CLASS Class;
		unsigned int Level;
		unsigned int Slot;
		unsigned int Ranks;
		bool TypeActive;
		unsigned int APCost;
		string Description[3];
		vector <ENH_Requirement> Requirement[3];
		vector <ENH_Requirement> RequirementOne[3];
		vector <ENH_Requirement> Lock[3];
		vector <string> Mod[3];
		vector <string> ModName[3];
		vector <int> ModValue[3];
        GraphicStruct EnhancementIcon;
		unsigned int APRequirement;
		unsigned int ClassLevelRequirement;
		unsigned int CharacterLevelRequirement;

		bool IsRaceTree();
		bool IsRaceAATree();
		unsigned int CalculateClassLevelRequirement();
		unsigned int CalculateCharacterLevelRequirement();
		unsigned int CalculateAPRequirement();
		CLASS SetTreeClass(ENHANCEMENT_TREE EnhancementTree);
		RACE SetTreeRace(ENHANCEMENT_TREE EnhancementTree);
		void StripStringLeadingWhiteSpace(string &SourceString);
	};
