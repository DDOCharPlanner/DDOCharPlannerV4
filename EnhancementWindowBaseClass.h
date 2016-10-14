#pragma once
#include "stdafx.h"
#include "IconClass.h"
#include "Data_Enhancement_Class.h"

struct EnhancementSlotStruct
	{
	bool Valid;
	bool Active;
	bool MultiSelection;
	vector <int> EnhancementIndex;
	int EnhancementIndexChosen;
	int Cost;
	int Ranks;
	int RanksTaken;
	int RanksTakenOld;
	};

class EnhancementWindowBaseClass : public IconClass
	{
	public:
		EnhancementWindowBaseClass();
		virtual ~EnhancementWindowBaseClass();
		void SetCharacterLevel(int Level);

	protected:
		void SetToolTipWindow(Data_Enhancement_Class *Enhancement);
		void ShowTooTipWindow(bool Show);
		bool AreAllRequirementsMet(Data_Enhancement_Class *Enhancement);
		bool AreEnhancementReqsMet(Data_Enhancement_Class* Enhancement);
		bool IsEnhancementLocked(Data_Enhancement_Class* Enhancement);

		static int CharacterLevel;
		static int APSpentTree[7];
		static ENHANCEMENT_TREE CurrentTree[3];
		static EnhancementSlotStruct CurrentTreeSlots[3][6][6];
		static EnhancementSlotStruct ChosenTreeSlots[7][6][6];
		static ENHANCEMENT_TREE ChosenTrees[7];
		bool CurrentLevel5TreeLock[3];
		bool ChosenLevel5TreeLock[7];
		int SessionAPSpentTotal;
		int SessionAPSpentTree[7];
		TRACKMOUSEEVENT tme;
		bool TMEFlag;
		unsigned int CurrentStartingTree;
		string ConvertEnhancementTreeToString(ENHANCEMENT_TREE Tree);
		ENHANCEMENT_TREE ConvertStringToEnhancementTree(string Tree);
	private:
		enum ENHANCEMENT_REQUIREMENT_TYPE {REQTYPE_APSPENT, REQTYPE_CLASSLEVEL, REQTYPE_CHARACTERLEVEL, REQTYPE_ENHANCEMENT, REQTYPE_FEAT, REQTYPE_ONEOF};
		
		string GetRequirementText(Data_Enhancement_Class *Enhancement, int Rank, ENHANCEMENT_REQUIREMENT_TYPE Type, int RanksTaken);
		bool AreAPRequirementsMet(Data_Enhancement_Class* Enhancement);
		bool AreLevelRequirementsMet(Data_Enhancement_Class* Enhancement, bool ClassLevel);
		int ConvertTreeToChosenTree(ENHANCEMENT_TREE Tree);
		int ConvertTreeToChosenTree(string Tree);

		//do not implement these two functions, instance  control!!
		EnhancementWindowBaseClass(const EnhancementWindowBaseClass &source);
	    EnhancementWindowBaseClass& operator=(const EnhancementWindowBaseClass &source);
	};	
