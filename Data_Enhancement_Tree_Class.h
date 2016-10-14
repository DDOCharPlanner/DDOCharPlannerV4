#pragma once

#include "stdafx.h"
#include "IconClass.h"
#include "Data_Enhancement_Class.h"

class Data_Enhancement_Tree_Class : public IconClass
	{
	public:
		Data_Enhancement_Tree_Class();
		virtual ~Data_Enhancement_Tree_Class();

		void InitializeEnhancementTree(ENHANCEMENT_TREE Tree, ENHANCEMENT_TREE_TYPE Type, RACE Race, CLASS Class, string Name, bool EnhancementFlag, string Graphic, string Arrows);
		void AddNewEnhancement(string EnhancementDataString);

		Data_Enhancement_Tree_Class* GetEnhancementTreeAddress();
		GraphicStruct GetBackgroundGraphic();
		ENHANCEMENT_TREE GetTreeIndex();
		static ENHANCEMENT_TREE GetTreeIndex(string Tree);
		ENHANCEMENT_TREE_TYPE GetTreeType();
		RACE GetTreeRace();
		CLASS GetTreeClass();
		string GetTreeName();
		bool DoesSlotHaveEnhancement (int Level, int Slot);
		unsigned int GetArrowPlacementSize();
		ArrowStruct GetArrowPlacement(int Index);
		bool DoesTreeHaveEnhancements();

		//EnhancementData Stuff
		Data_Enhancement_Class* GetEnhancementPointer (unsigned int EnhancementIndex);
		Data_Enhancement_Class* GetEnhancementPointer (unsigned int Level, unsigned int Slot);
		Data_Enhancement_Class* GetEnhancementPointer (unsigned int Level, unsigned int Slot, unsigned int MSlot);
		int GetEnhancementIndex(int Level, int Slot, unsigned int MSlot);
		unsigned int GetMultiEnhancementsSize(int EnhancementIndex);

	private:
		ENHANCEMENT_TREE TreeIndex;
		ENHANCEMENT_TREE_TYPE TreeType;
		RACE TreeRace;
		CLASS TreeClass;
		string TreeName;
		bool HasEnhancements;
		GraphicStruct TreeBackground;
		vector <ArrowStruct> ArrowPlacement;
		vector <Data_Enhancement_Class> EnhancementData;
		static unordered_map <string, ENHANCEMENT_TREE> EnhancementTreeList;

		void StripStringLeadingWhiteSpace(string &SourceString);
		void InitHash();

		//copy construct and assignment operator
		Data_Enhancement_Tree_Class(const Data_Enhancement_Tree_Class &source);
		Data_Enhancement_Tree_Class& operator=(const Data_Enhancement_Tree_Class &source);
	};
