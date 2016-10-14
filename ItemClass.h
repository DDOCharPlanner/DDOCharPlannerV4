#pragma once

#include "stdafx.h"

class ItemClass
	{
	public:
		ItemClass();
		virtual ~ItemClass();
		//copy constructor and assignment operator, do not implement functions!
		ItemClass(const ItemClass &source);
		ItemClass& operator=(const ItemClass &source);

		ItemClass* const GetItemAddress();
		void InitializeItem(string ItemData);
		string GetItemName ();
		int GetItemBase();
		string GetItemFlavorText ();
		bool DoesItemFitSelectedSlot(unsigned int SelectedSlot);
		bool DoesEpicItemSlotOneColorMatch(unsigned int EpicSlotColor);
		bool DoesEpicItemSlotTwoColorMatch(unsigned int EpicSlotColor);
		int GetItemType();
		int GetItemStaticEffectIndex(unsigned int index, unsigned int *StaticEffectIndex);
		int GetItemStaticEffectsSize();
		int GetBaseAC();
		int GetMaxDex();
		int GetArmorCheckPenalty();

	private:
		//Variables for the class
		string Name;
		ITEMBASETYPE Base;
		ITEMTYPE Type;
		EPICSLOTCOLOR EpicItemSlotOne;
		EPICSLOTCOLOR EpicItemSlotTwo;
		string FlavorText; 
		vector <int> StaticEffects;
		string ClickyEffect;
		int BaseAC;
		int MaxDex;
		int ArmorCheckPenalty;
        static unordered_map<string, ITEMBASETYPE> BaseKeywords;
        static unordered_map<string, ITEMTYPE> TypeKeywords;
        static unordered_map<string, EPICSLOTCOLOR> ColorKeywords;

		//Private Functions for the class
		void StripStringLeadingWhiteSpace(string &SourceString);
		void InitHash();
        string trim(const string& str, const string& whitespace = " \t");
        void split(const string& str, const string& delimiters , vector<string>& tokens);

	};


