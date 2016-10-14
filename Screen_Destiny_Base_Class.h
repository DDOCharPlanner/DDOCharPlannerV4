#pragma once
#include "stdafx.h"
#include "IconClass.h"
#include "Data_Destiny_Class.h"

struct DestinySlotStruct
	{
	bool Valid;
	bool Active;
	bool MultiSelection;
	vector <int> DestinyIndex;
	unsigned int DestinyIndexChosen;
	unsigned int Cost;
	unsigned int Ranks;
	unsigned int RanksTaken;
	unsigned int RanksTakenOld;
	};

class Screen_Destiny_Base_Class : public IconClass
	{
	public:
		Screen_Destiny_Base_Class();
		virtual ~Screen_Destiny_Base_Class();

	protected:
		static int CharacterLevel;
		static unsigned int DPSpentTree[NUM_DESTINY_TREES];
		static unsigned int DPAvailbleTree[NUM_DESTINY_TREES];
		static unsigned int DestinyTreeLevel[NUM_DESTINY_TREES];
		static DESTINY_TREE ScreenTree;
		static DestinySlotStruct ScreenTreeSlots[7][6];
		TRACKMOUSEEVENT tme;
		bool TMEFlag;

		bool AreRequirementsMet(Data_Destiny_Class *Destiny, bool flagDPointsSpent, bool flagDestinyReqs, bool flagDLevel);
		void ShowToolTipWindow(bool Show);
		void SetToolTipWindow(Data_Destiny_Class *Destiny);

	private:
		enum DESTINY_REQUIREMENT_TYPE {REQTYPE_DPSPENT, REQTYPE_DESTINY, REQTYPE_FEAT, REQTYPE_ONEOF};

		bool CheckDPointsRequirement(Data_Destiny_Class *Destiny);
		bool CheckDLevelRequirement(Data_Destiny_Class *Destiny);
		bool CheckDestinyRequirements(Data_Destiny_Class *Destiny);
		string GetRequirementText(Data_Destiny_Class *Destiny, int Rank, DESTINY_REQUIREMENT_TYPE Type, int RanksTaken);

		//do not implement these two functions, instance control!!!
		Screen_Destiny_Base_Class(const Screen_Destiny_Base_Class &source);
		Screen_Destiny_Base_Class& operator=(const Screen_Destiny_Base_Class &source);
	};