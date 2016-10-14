#include "stdafx.h"

class ItemClickyEffectClass
{
public:
	ItemClickyEffectClass();
	virtual ~ItemClickyEffectClass();
	//copy constructor and assignment operator, do not implement functions!
	ItemClickyEffectClass(const ItemClickyEffectClass &source);
	ItemClickyEffectClass& operator=(const ItemClickyEffectClass &source);

	ItemClickyEffectClass* const GetItemClickyEffectAddress();
	void InitializeItemClickyEffect(string ItemClickyEffectData);
	string GetItemClickyEffectName ();
	string GetItemClickyEffectDescription ();

private:
	
	//Variables for the class
	string Name;
	string Description;
	vector <EFFECTTYPE> Type;
	vector <ITEMTYPE> AppliedTo;

	//Private Functions for the class
	void StripStringLeadingWhiteSpace(string &SourceString);
};