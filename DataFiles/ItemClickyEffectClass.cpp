#include "ItemClickyEffectClass.h"
 
//----------------------------------------------------------------
ItemClickyEffectClass::ItemClickyEffectClass()
{
	//clear out the member variables so we are not starting with garbage
	Name = "";
	Description = "";
	Type.clear();
	AppliedTo.clear();
}
 
//----------------------------------------------------------------
ItemClickyEffectClass::~ItemClickyEffectClass()
{
}

//----------------------------------------------------------------
ItemClickyEffectClass::ItemClickyEffectClass(const ItemClickyEffectClass &source)
	{
	//the copy constructor. We need this because this class lives in a vector
	//and the vector may need to copy the class somewhere else...
	
	Name = source.Name;
	Description = source.Description;
	Type.clear();
	for (unsigned int i=0; i<source.Type.size(); i++)
		Type.push_back(source.Type[i]);
	AppliedTo.clear();
	for (unsigned int i=0; i<source.AppliedTo.size(); i++)
		AppliedTo.push_back(source.AppliedTo[i]);
}

//----------------------------------------------------------------
ItemClickyEffectClass& ItemClickyEffectClass::operator=(const ItemClickyEffectClass &source)
	{
	//the = function overload. We need this because this class lives in a vector
	//and unfortunately, vectors use this function...
	Name = source.Name;
	Description = source.Description;
	Type.clear();
	for (unsigned int i=0; i<source.Type.size(); i++)
		Type.push_back(source.Type[i]);
	AppliedTo.clear();
	for (unsigned int i=0; i<source.AppliedTo.size(); i++)
		AppliedTo.push_back(source.AppliedTo[i]);
	
	return *this;
	}
//-----------------------------------------------------------------
ItemClickyEffectClass* const ItemClickyEffectClass::GetItemClickyEffectAddress()
	{
	//IMPORTANT SAFETY TIP: Never ever call this function until the entire feat
	//file has been fully loaded and stored into individual feats. Otherwise you
	//may end up with a bad pointer!
	return this;
	}
//-----------------------------------------------------------------
void ItemClickyEffectClass::InitializeItemClickyEffect(string ItemClickyEffectData)
{
    #define NUMKEYWORDS 4

	string KeywordString[NUMKEYWORDS];
	string ItemClickyEffectLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	string Substring;
	int NumOfValues;
	
    //parse the ItemClickyEffectData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "EFFECTNAME: ";
	KeywordString[1] = "EFFECTDESCRIPTION: ";
	KeywordString[2] = "EFFECTTYPE: ";
	KeywordString[3] = "APPLIEDTO: ";

    for (unsigned int i=0; i<NUMKEYWORDS; i++)
	{
		ItemClickyEffectLine[i] = "";
		if (ItemClickyEffectData.find(KeywordString[i]) != string::npos)
		{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = ItemClickyEffectData.find(KeywordString[i]);
			EndLoc = ItemClickyEffectData.find(";", ItemClickyEffectData.find(KeywordString[i])); 
			ItemClickyEffectLine[i] = ItemClickyEffectData.substr(ItemClickyEffectData.find(KeywordString[i]), EndLoc-StartLoc);
			//drop the keyword from the line string, we don't need it now
			ItemClickyEffectLine[i].erase(0, KeywordString[i].size());
		}
	}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
    {
        switch (i)
        {
            case 0:     //the effect name
            {
                if (ItemClickyEffectLine[i] == "")
					continue;
                Name = ItemClickyEffectLine[i];
                break;
            }
            case 1:		//effect description
            {
                if (ItemClickyEffectLine[i] == "")
					continue;
                Description = ItemClickyEffectLine[i];
                break;
            }
            case 2:     //effect Type
            {
                if (ItemClickyEffectLine[i] == "")
					continue;
				if (ItemClickyEffectLine[i].find("Bonus") != string::npos)
					Type.push_back(BONUS);
				if (ItemClickyEffectLine[i].find("Prefix") != string::npos)
					Type.push_back(PREFIX);
				if (ItemClickyEffectLine[i].find("Suffix") != string::npos)
					Type.push_back(SUFFIX);
				if (ItemClickyEffectLine[i].find("Material") != string::npos)
					Type.push_back(MATERIAL);
				if (ItemClickyEffectLine[i].find("Eldritch") != string::npos)
					Type.push_back(ELDRITCH);
				if (ItemClickyEffectLine[i].find("GSInvasion Element") != string::npos)
					Type.push_back(INVASIONELEMENT);
				if (ItemClickyEffectLine[i].find("Greensteel Invasion") != string::npos)
					Type.push_back(GSINVASION);
				if (ItemClickyEffectLine[i].find("GSSubjugation Element") != string::npos)
					Type.push_back(SUBJUGATIONELEMENT);
				if (ItemClickyEffectLine[i].find("Greensteel Subjugation") != string::npos)
					Type.push_back(GSSUBJUGATION);
				if (ItemClickyEffectLine[i].find("GSDevastation Element") != string::npos)
					Type.push_back(DEVASTATIONELEMENT);
				if (ItemClickyEffectLine[i].find("Greensteel Devastation") != string::npos)
					Type.push_back(GSDEVASTATION);
				if (ItemClickyEffectLine[i].find("DT Eldritch") != string::npos)
					Type.push_back(DTELDRITCH);
				if (ItemClickyEffectLine[i].find("DT Tempest") != string::npos)
					Type.push_back(DTTEMPEST);
				if (ItemClickyEffectLine[i].find("DT Sovereign") != string::npos)
					Type.push_back(DTSOVEREIGN);
				break;
            }
			case 3:		// What items can the effect be applied to
			{
                NumOfValues = 0;
				StartLoc = 0;

				if (ItemClickyEffectLine[i] == "")
					continue;
				while (ItemClickyEffectLine[i].find(",", StartLoc) != string::npos)
				{
					NumOfValues++;
					StartLoc = ItemClickyEffectLine[i].find(",", StartLoc+1);
				}
				for (int x=0; x<NumOfValues; x++)
				{
					if (ItemClickyEffectLine[i].find(",") != string::npos)
						EndLoc = ItemClickyEffectLine[i].find(",");
					else
						EndLoc = ItemClickyEffectLine[i].size();
					Substring = ItemClickyEffectLine[i].substr(0, EndLoc);
					ItemClickyEffectLine[i].erase(0, EndLoc+1);
					StripStringLeadingWhiteSpace(ItemClickyEffectLine[i]);

					// Check for the various armor and shield types
					if (Substring == "Padded Armor")
						AppliedTo.push_back(PADDEDARMOR);
					if (Substring == "Leather Armor")
						AppliedTo.push_back(LEATHERARMOR);
					if (Substring == "Studded Leather Armor")
						AppliedTo.push_back(STUDDEDLEATHERARMOR);
					if (Substring == "Chain Shirt")
						AppliedTo.push_back(CHAINSHIRTARMOR);
					if (Substring == "Hide Armor")
						AppliedTo.push_back(HIDEARMOR);
					if (Substring == "Scalemail")
						AppliedTo.push_back(SCALEMAILARMOR);
					if (Substring == "Chain Mail")
						AppliedTo.push_back(CHAINMAILARMOR);
					if (Substring == "Breastplate")
						AppliedTo.push_back(BREASTPLATEARMOR);
					if (Substring == "Brigadine")
						AppliedTo.push_back(BRIGADINEARMOR);
					if (Substring == "Splintmail")
						AppliedTo.push_back(SPLINTMAILARMOR);
					if (Substring == "Banded Mail")
						AppliedTo.push_back(BANDEDMAILARMOR);
					if (Substring == "Half Plate")
						AppliedTo.push_back(HALFPLATEARMOR);
					if (Substring == "Full Plate")
						AppliedTo.push_back(FULLPLATEARMOR);
					if (Substring == "Docent")
						AppliedTo.push_back(DOCENT);
					if (Substring == "Robe")
						AppliedTo.push_back(ROBE);
					if (Substring == "Buckler")
						AppliedTo.push_back(BUCKLER);
					if (Substring == "Small Shield")
						AppliedTo.push_back(SMALLSHIELD);
					if (Substring == "Large Shield")
						AppliedTo.push_back(LARGESHIELD);
					if (Substring == "Tower Shield")
						AppliedTo.push_back(TOWERSHIELD);

					// check for the regular clothing & jewelry types.
					if (Substring == "Goggles")
						AppliedTo.push_back(GOGGLES);
					if (Substring == "Helmet")
						AppliedTo.push_back(HELMET);
					if (Substring == "Necklace")
						AppliedTo.push_back(NECKLACE);
					if (Substring == "Trinket")
						AppliedTo.push_back(TRINKETITEM);
					if (Substring == "Cloak")
						AppliedTo.push_back(CLOAK);
					if (Substring == "Belt")
						AppliedTo.push_back(BELT);
					if (Substring == "Ring")
						AppliedTo.push_back(RING);
					if (Substring == "Gloves")
						AppliedTo.push_back(GLOVESITEM);
					if (Substring == "Boots")
						AppliedTo.push_back(BOOTS);
					if (Substring == "Bracers")
						AppliedTo.push_back(BRACERS);
					if (Substring == "Quiver")
						AppliedTo.push_back(QUIVER);

					// check for the regular weapon types.
					if (Substring == "Bastard Sword")
						AppliedTo.push_back(BASTARDSWORD);
					if (Substring == "Battle Axe")
						AppliedTo.push_back(BATTLEAXE);
					if (Substring == "Club")
						AppliedTo.push_back(CLUB);
					if (Substring == "Dagger")
						AppliedTo.push_back(DAGGER);
					if (Substring == "Dart")
						AppliedTo.push_back(DART);
					if (Substring == "Dwarven War Axe")
						AppliedTo.push_back(DWARVENWARAXE);
					if (Substring == "Falchion")
						AppliedTo.push_back(FALCHION);
					if (Substring == "Great Axe")
						AppliedTo.push_back(GREATAXE);
					if (Substring == "Great Club")
						AppliedTo.push_back(GREATCLUB);
					if (Substring == "Great Crossbow")
						AppliedTo.push_back(GREATCROSSBOW);
					if (Substring == "Great Sword")
						AppliedTo.push_back(GREATSWORD);
					if (Substring == "Handaxe")
						AppliedTo.push_back(HANDAXE);
					if (Substring == "Handwraps")
						AppliedTo.push_back(HANDWRAPS);
					if (Substring == "Heavy Crossbow")
						AppliedTo.push_back(HEAVYCROSSBOW);
					if (Substring == "Heavy Mace")
						AppliedTo.push_back(HEAVYMACE);
					if (Substring == "Heavy Pick")
						AppliedTo.push_back(HEAVYPICK);
					if (Substring == "Kama")
						AppliedTo.push_back(KAMA);
					if (Substring == "Khopesh")
						AppliedTo.push_back(KHOPESH);
					if (Substring == "Kukri")
						AppliedTo.push_back(KUKRI);
					if (Substring == "Light Crossbow")
						AppliedTo.push_back(LIGHTCROSSBOW);
					if (Substring == "Light Hammer")
						AppliedTo.push_back(LIGHTHAMMER);
					if (Substring == "Light Pick")
						AppliedTo.push_back(LIGHTPICK);
					if (Substring == "Light Mace")
						AppliedTo.push_back(LIGHTMACE);
					if (Substring == "Long Bow")
						AppliedTo.push_back(LONGBOW);
					if (Substring == "Long Sword")
						AppliedTo.push_back(LONGSWORD);
					if (Substring == "Maul")
						AppliedTo.push_back(MAUL);
					if (Substring == "Morningstar")
						AppliedTo.push_back(MORNINGSTAR);
					if (Substring == "Quarterstaff")
						AppliedTo.push_back(QUARTERSTAFF);
					if (Substring == "Rapier")
						AppliedTo.push_back(RAPIER);
					if (Substring == "Repeating Heavy Crossbow")
						AppliedTo.push_back(REPEATINGHEAVYCROSSBOW);
					if (Substring == "Repeating Light Crossbow")
						AppliedTo.push_back(REPEATINGLIGHTCROSSBOW);
					if (Substring == "Scimitar")
						AppliedTo.push_back(SCIMITAR);
					if (Substring == "Short Bow")
						AppliedTo.push_back(SHORTBOW);
					if (Substring == "Short Sword")
						AppliedTo.push_back(SHORTSWORD);
					if (Substring == "Shuriken")
						AppliedTo.push_back(SHURIKEN);
					if (Substring == "Sickle")
						AppliedTo.push_back(SICKLE);
					if (Substring == "Throwing Axe")
						AppliedTo.push_back(THROWINGAXE);
					if (Substring == "Throwing Dagger")
						AppliedTo.push_back(THROWINGDAGGER);
					if (Substring == "Throwing Hammer")
						AppliedTo.push_back(THROWINGHAMMER);
					if (Substring == "War Hammer")
						AppliedTo.push_back(WARHAMMER);
				}
				break;
			}
		}
    }   
    return;
    #undef NUMKEYWORDS
}

string ItemClickyEffectClass::GetItemClickyEffectName()
{
	return Name;
}

string ItemClickyEffectClass::GetItemClickyEffectDescription()
{
	return Description;
}
void ItemClickyEffectClass::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
}