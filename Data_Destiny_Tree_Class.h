#pragma once

#include "stdafx.h"
#include "IconClass.h"
#include "Data_Destiny_Class.h"

class Data_Destiny_Tree_Class : public IconClass
	{
	public:	
		Data_Destiny_Tree_Class();
		virtual ~Data_Destiny_Tree_Class();

		void InitializeDestinyTree(DESTINY_TREE DTree, string Name, bool DestinyFlag, string Graphic, string Icon, string Arrows, DESTINY_SPHERE Sphere ,DESTINY_TREE AdjacentDestiny1 = DT_NONE,
			DESTINY_TREE AdjacentDestiny2 = DT_NONE, DESTINY_TREE AdjacentSphereDestinyConnection = DT_NONE);
		void AddNewDestiny(string DestinyDataString);

		Data_Destiny_Tree_Class* GetDestinyTreeAddress();

		unsigned int GetArrowPlacementSize();
		ArrowStruct GetArrowPlacement(unsigned int Index);
		bool DoesTreeHaveDestinies();
		GraphicStruct GetTreeBackground();
		DESTINY_TREE GetTreeIndex();
		string GetTreeName();
		GraphicStruct GetTreeIcon();
		DESTINY_SPHERE GetDestinySphere();

		//DestinyData Stuff
		Data_Destiny_Class* GetDestinyPointer (unsigned int DestinyIndex);
		Data_Destiny_Class* GetDestinyPointer (unsigned int Tier, unsigned int Column);
		unsigned int GetNumofDestinies(int DestinyIndex);
		int GetDestinyIndex(int Tier, int column, unsigned int MSlot);


	private:
		DESTINY_TREE TreeIndex;
		string TreeName;
		DESTINY_SPHERE DestinySphere;
		bool HasDestinies;
		GraphicStruct TreeIcon;
		GraphicStruct TreeBackground;
		vector <ArrowStruct> ArrowPlacement;
		vector <Data_Destiny_Class> DestinyData;
		DESTINY_TREE AdjacentDestiny[2];
		DESTINY_TREE AdjacentSphereDestiny;

		void StripStringLeadingWhiteSpace(string &SourceString);

		//copy construct and assignement operator
		Data_Destiny_Tree_Class(const Data_Destiny_Tree_Class &source);
		Data_Destiny_Tree_Class& operator=(const Data_Destiny_Tree_Class &source);
	};
