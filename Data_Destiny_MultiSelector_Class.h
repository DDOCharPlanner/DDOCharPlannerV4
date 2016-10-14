#pragma once
#include "stdafx.h"
#include "IconClass.h"

class Data_Destiny_MultiSelector_Class : public IconClass
	{
	public:
		Data_Destiny_MultiSelector_Class();
		~Data_Destiny_MultiSelector_Class();
		//copy constructor and assignement operator
		Data_Destiny_MultiSelector_Class(const Data_Destiny_MultiSelector_Class &source);
		Data_Destiny_MultiSelector_Class& operator=(const Data_Destiny_MultiSelector_Class &source);

		void InitializeMultiSelector(string SelectorData);
		string GetName();
		string GetDescription(unsigned int Index);
		GraphicStruct GetIcon(unsigned int Index);
		Data_Destiny_MultiSelector_Class* GetMultiDestinyAddress();

	private:
		string Name;
		vector <string> Description;
		vector <GraphicStruct> MultiDestinyIcon;

		void StripStringLeadingWhiteSpace(string &SourceString);
	};
