#pragma once

#include "stdafx.h"
#include "IconClass.h"
#include "Data_Destiny_MultiSelector_Class.h"

struct Destiny_Requirement
	{
	DESTINY_REQTYPE ReqType;
	string ReqName;
	int ReqTier;
	int ReqSlot;
	int ReqRank;
	};

class Data_Destiny_Class : public IconClass
	{
	public:
		Data_Destiny_Class();
		virtual ~Data_Destiny_Class();
		//copy constructor and assignment operator
		Data_Destiny_Class(const Data_Destiny_Class &source);
		Data_Destiny_Class& operator=(const Data_Destiny_Class &source);

		void InitializeDestiny(string Data, DESTINY_TREE DTIndex, unsigned int DIndex);
		Data_Destiny_Class* GetDestinyAddress();
		
		bool GetActive();
		string GetDescription(int Rank);
		GraphicStruct GetDestinyIcon();
		unsigned int GetDestinyIndex();
		unsigned int GetDLevelRequirement();
		unsigned int GetDPCost();
		unsigned int GetDPRequirement();
		unsigned int GetTier();
		int GetLockTier(int Rank, int Index);
		string GetLockName(int Rank, int Index);
		int GetLockRank(int Rank, int Index);
		unsigned int GetLockSize(int Rank);
		int GetLockSlot(int Rank, int Index);
		DESTINY_REQTYPE GetLockType (int Rank, int Index);
		MODCATEGORY GetModCategory(int Rank, int Index);
		string GetModName(int Rank, int Index);
		unsigned int GetModSize(int Rank);
		int GetModValue(int Rank, int Index);
		bool GetMultiSelection();
		string GetMultiSelectorName();
		unsigned int GetMultiDescriptionIndex();
		unsigned int GetMultiIconIndex();
		unsigned int GetMultiSelectorSlot();
		string GetName();
		unsigned int GetRanks();
		int GetRequirementTier(int Rank, int Index);
		string GetRequirementName(int Rank, int Index);
		int GetRequirementRank(int Rank, int Index);
		unsigned int GetRequirementSize(int Rank);
		int GetRequirementSlot(int Rank, int Index);
		DESTINY_REQTYPE GetRequirementType (int Rank, int Index);
		int GetRequirementOneTier(int Rank, int Index);
		string GetRequirementOneName(int Rank, int Index);
		int GetRequirementOneRank(int Rank, int Index);
		unsigned int GetRequirementOneSize(int Rank);
		int GetRequirementOneSlot(int Rank, int Index);
		DESTINY_REQTYPE GetRequirementOneType (int Rank, int Index);
		unsigned int GetSlot();
		DESTINY_TREE GetTreeIndex();
		string GetTreeName();

	private:
		DESTINY_TREE TreeIndex;
		unsigned int DestinyIndex;
		bool MultiSelection;
		string MultiSelectorName;
		unsigned int MultiSelectorSlot;
		unsigned int MultiDescriptionIndex;
		unsigned int MultiIconIndex;
		string Name;
		string TreeName;
		unsigned int Tier;
		unsigned int Slot;
		unsigned int Ranks;
		bool Active;
		unsigned int DPCost;
		string Description[3];
		vector <Destiny_Requirement> Requirement[3];
		vector <Destiny_Requirement> RequirementOne[3];
		vector <Destiny_Requirement> Lock[3];
		vector <MODCATEGORY> ModCategory[3];
		vector <string> ModName[3];
		vector <int> ModValue[3];
		GraphicStruct DestinyIcon;
		unsigned int DPRequirement;
		unsigned int DLevelRequirement;

		unsigned int CalculateDPRequirement();
		unsigned int CalculateDLevelRequirement();
		void StripStringLeadingWhiteSpace(string &SourceString);
	};

