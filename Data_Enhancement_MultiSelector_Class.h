#pragma once
#include "stdafx.h"
#include "IconClass.h"

class Data_Enhancement_MultiSelector_Class : public IconClass
	{
	public:
		Data_Enhancement_MultiSelector_Class();
		~Data_Enhancement_MultiSelector_Class();
		//copy constructor and assignment operator
        Data_Enhancement_MultiSelector_Class(const Data_Enhancement_MultiSelector_Class &source);
        Data_Enhancement_MultiSelector_Class& operator=(const Data_Enhancement_MultiSelector_Class &source);

		void InitializeMultiSelector(string SelectorData);
		string GetName();
		string GetDescription();
		GraphicStruct GetIcon();
		Data_Enhancement_MultiSelector_Class* GetMultiEnhancementAddress();

	private:
		string Name;
		string Description;
		GraphicStruct MultiEnhancementIcon;
	};

