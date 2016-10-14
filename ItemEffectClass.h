#include "stdafx.h"

class ItemEffectClass
{
public:
	ItemEffectClass();
	virtual ~ItemEffectClass();
	ItemEffectClass(const ItemEffectClass &source);
	ItemEffectClass& operator=(const ItemEffectClass &source);

	ItemEffectClass* const GetItemEffectAddress();
	void InitializeItemEffect(string ItemEffectData);
	string GetItemEffectName();
	string GetItemEffectSubName();
	string GetItemEffectCombinedName();
	string GetItemEffectDisplayName();
	string GetItemEffectDescription();
	bool DoesTypeMatch(unsigned int EffectType);
	bool DoesAppliedToMatch(unsigned int AppliedToType);
	bool DoesGSElementTypeMatch(unsigned int GSElement);
	int GetItemEffectAbilityModifier(unsigned int Index, int *Modifier);
	int GetItemEffectAbilityModType(unsigned int Index);
	int GetItemEffectAbilityChange(unsigned int Index);
	int GetItemEffectSkillModifier(unsigned int Index, int *Modifier);
	int GetItemEffectSkillModType(unsigned int Index);
	int GetItemEffectSkillChange(unsigned int Index);
	int GetItemEffectSaveModifier(unsigned int Index, int *Modifier);
	int GetItemEffectSaveModType(unsigned int Index);
	int GetItemEffectSaveChange(unsigned int Index);
	int GetGSElementType(unsigned int Index);
	int GetGSElementTypesSize();
	int GetEpicEffectColor(unsigned int Index);
	int GetEpicEffectColorsSize();
	int GetItemEffectHPModType();
	int GetItemEffectHPChange();
	int GetItemEffectSPModType();
	int GetItemEffectSPChange();
	int GetItemEffectACModType();
	int GetItemEffectACChange();

private:
	
	//Variables for the class
	string Name;
	string SubName;
	string DisplayName;
	string Description;
	vector <EFFECTTYPE> Type;
	vector <ITEMTYPE> AppliedTo;
	vector <ABILITIES> AbilityModifier;
	vector <MODTYPE> AbilityModType;
	vector <int> AbilityChange;
	vector <SKILLS> SkillModifier;
	vector <MODTYPE> SkillModType;
	vector <int> SkillChange;
	vector <SAVETYPE> SaveModifier;
	vector <MODTYPE> SaveModType;
	vector <int> SaveChange;
	vector <GSELEMENTTYPE> GSElementTypes;
	vector <EPICSLOTCOLOR> EpicEffectColors;
	MODTYPE ACModType;
	int ACChange;
	MODTYPE HPModType;
	int HPChange;
	MODTYPE SPModType;
	int SPChange;

	//Private Functions for the class
	void StripStringLeadingWhiteSpace(string &SourceString);
};