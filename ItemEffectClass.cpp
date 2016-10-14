#include "ItemEffectClass.h"
 
//----------------------------------------------------------------
ItemEffectClass::ItemEffectClass()
	{
	//clear out the member variables so we are not starting with garbage
	Name = "";
	SubName = "";
	DisplayName = "";
	Description = "";
	Type.clear();
	AppliedTo.clear();
	AbilityModifier.clear();
	AbilityModType.clear();
	AbilityChange.clear();
	SkillModifier.clear();
	SkillModType.clear();
	SkillChange.clear();
	SaveModifier.clear();
	SaveModType.clear();
	SaveChange.clear();
	GSElementTypes.clear();
	EpicEffectColors.clear();
	ACModType = NOMOD;
	ACChange = 0;
	HPModType = NOMOD;
	HPChange = 0;
	SPModType = NOMOD;
	SPChange = 0;
	}
 
//----------------------------------------------------------------
ItemEffectClass::~ItemEffectClass()
	{
	}

//----------------------------------------------------------------
ItemEffectClass::ItemEffectClass(const ItemEffectClass &source)
	{
	//the copy constructor. We need this because this class lives in a vector
	//and the vector may need to copy the class somewhere else...
	
	Name = source.Name;
	SubName = source.SubName;
	DisplayName = source.DisplayName;
	Description = source.Description;
	Type.clear();
	for (unsigned int i=0; i<source.Type.size(); i++)
		Type.push_back(source.Type[i]);
	AppliedTo.clear();
	for (unsigned int i=0; i<source.AppliedTo.size(); i++)
		AppliedTo.push_back(source.AppliedTo[i]);
	AbilityModifier.clear();
	for (unsigned int i=0; i<source.AbilityModifier.size(); i++)
		AbilityModifier.push_back(source.AbilityModifier[i]);
	AbilityModType.clear();
	for (unsigned int i=0; i<source.AbilityModType.size(); i++)
		AbilityModType.push_back(source.AbilityModType[i]);
	AbilityChange.clear();
	for (unsigned int i=0; i<source.AbilityChange.size(); i++)
		AbilityChange.push_back(source.AbilityChange[i]);
	SkillModifier.clear();
	for (unsigned int i=0; i<source.SkillModifier.size(); i++)
		SkillModifier.push_back(source.SkillModifier[i]);
	SkillModType.clear();
	for (unsigned int i=0; i<source.SkillModType.size(); i++)
		SkillModType.push_back(source.SkillModType[i]);
	SkillChange.clear();
	for (unsigned int i=0; i<source.SkillChange.size(); i++)
		SkillChange.push_back(source.SkillChange[i]);
	SaveModifier.clear();
	for (unsigned int i=0; i<source.SaveModifier.size(); i++)
		SaveModifier.push_back(source.SaveModifier[i]);
	SaveModType.clear();
	for (unsigned int i=0; i<source.SaveModType.size(); i++)
		SaveModType.push_back(source.SaveModType[i]);
	SaveChange.clear();
	for (unsigned int i=0; i<source.SaveChange.size(); i++)
		SaveChange.push_back(source.SaveChange[i]);
	GSElementTypes.clear();
	for (unsigned int i=0; i<source.GSElementTypes.size(); i++)
		GSElementTypes.push_back(source.GSElementTypes[i]);
	EpicEffectColors.clear();
	for (unsigned int i=0; i<source.EpicEffectColors.size(); i++)
		EpicEffectColors.push_back(source.EpicEffectColors[i]);
	ACModType = source.ACModType;
	ACChange = source.ACChange;
	HPModType = source.HPModType;
	HPChange = source.HPChange;
	SPModType = source.SPModType;
	SPChange = source.SPChange;
	}

//----------------------------------------------------------------
ItemEffectClass& ItemEffectClass::operator=(const ItemEffectClass &source)
	{
	//the = function overload. We need this because this class lives in a vector
	//and unfortunately, vectors use this function...
	Name = source.Name;
	SubName = source.SubName;
	DisplayName = source.DisplayName;
	Description = source.Description;
	Type.clear();
	for (unsigned int i=0; i<source.Type.size(); i++)
		Type.push_back(source.Type[i]);
	AppliedTo.clear();
	for (unsigned int i=0; i<source.AppliedTo.size(); i++)
		AppliedTo.push_back(source.AppliedTo[i]);
	AbilityModifier.clear();
	for (unsigned int i=0; i<source.AbilityModifier.size(); i++)
		AbilityModifier.push_back(source.AbilityModifier[i]);
	AbilityModType.clear();
	for (unsigned int i=0; i<source.AbilityModType.size(); i++)
		AbilityModType.push_back(source.AbilityModType[i]);
	AbilityChange.clear();
	for (unsigned int i=0; i<source.AbilityChange.size(); i++)
		AbilityChange.push_back(source.AbilityChange[i]);
	SkillModifier.clear();
	for (unsigned int i=0; i<source.SkillModifier.size(); i++)
		SkillModifier.push_back(source.SkillModifier[i]);
	SkillModType.clear();
	for (unsigned int i=0; i<source.SkillModType.size(); i++)
		SkillModType.push_back(source.SkillModType[i]);
	SkillChange.clear();
	for (unsigned int i=0; i<source.SkillChange.size(); i++)
		SkillChange.push_back(source.SkillChange[i]);
	SaveModifier.clear();
	for (unsigned int i=0; i<source.SaveModifier.size(); i++)
		SaveModifier.push_back(source.SaveModifier[i]);
	SaveModType.clear();
	for (unsigned int i=0; i<source.SaveModType.size(); i++)
		SaveModType.push_back(source.SaveModType[i]);
	SaveChange.clear();
	for (unsigned int i=0; i<source.SaveChange.size(); i++)
		SaveChange.push_back(source.SaveChange[i]);
	GSElementTypes.clear();
	for (unsigned int i=0; i<source.GSElementTypes.size(); i++)
		GSElementTypes.push_back(source.GSElementTypes[i]);
	EpicEffectColors.clear();
	for (unsigned int i=0; i<source.EpicEffectColors.size(); i++)
		EpicEffectColors.push_back(source.EpicEffectColors[i]);
	ACModType = source.ACModType;
	ACChange = source.ACChange;
	HPModType = source.HPModType;
	HPChange = source.HPChange;
	SPModType = source.SPModType;
	SPChange = source.SPChange;
	
	return *this;
	}
//-----------------------------------------------------------------
ItemEffectClass* const ItemEffectClass::GetItemEffectAddress()
	{
	//IMPORTANT SAFETY TIP: Never ever call this function until the entire feat
	//file has been fully loaded and stored into individual feats. Otherwise you
	//may end up with a bad pointer!
	return this;
	}
//-----------------------------------------------------------------
void ItemEffectClass::InitializeItemEffect(string ItemEffectData)
	{
    #define NUMKEYWORDS 23

	string KeywordString[NUMKEYWORDS];
	string ItemEffectLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	int Value;
	string Substring;
	int NumOfValues;
	int EndBold;
	
    //parse the ItemEffectData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "EFFECTNAME: ";
	KeywordString[1] = "EFFECTSUBNAME: ";
	KeywordString[2] = "EFFECTDISPLAYNAME: ";
	KeywordString[3] = "EFFECTDESCRIPTION: ";
	KeywordString[4] = "EFFECTTYPE: ";
	KeywordString[5] = "APPLIEDTO: ";
	KeywordString[6] = "ABILITYMODIFIER: ";
	KeywordString[7] = "ABILITYMODTYPE: ";
	KeywordString[8] = "ABILITYCHANGE: ";
	KeywordString[9] = "SKILLMODIFIER: ";
	KeywordString[10] = "SKILLMODTYPE: ";
	KeywordString[11] = "SKILLCHANGE: ";
	KeywordString[12] = "SAVEMODIFIER: ";
	KeywordString[13] = "SAVEMODTYPE: ";
	KeywordString[14] = "SAVECHANGE: ";
	KeywordString[15] = "ACMODTYPE: ";
	KeywordString[16] = "ACCHANGE: ";
	KeywordString[17] = "HPMODTYPE: ";
	KeywordString[18] = "HPCHANGE: ";
	KeywordString[19] = "SPMODTYPE: ";
	KeywordString[20] = "SPCHANGE: ";
	KeywordString[21] = "GSELEMENTTYPE: ";
	KeywordString[22] = "EPICEFFECTCOLORS: ";

    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		ItemEffectLine[i] = "";
		if (ItemEffectData.find(KeywordString[i]) != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = ItemEffectData.find(KeywordString[i]);
			EndLoc = ItemEffectData.find(";", ItemEffectData.find(KeywordString[i])); 
			ItemEffectLine[i] = ItemEffectData.substr(ItemEffectData.find(KeywordString[i]), EndLoc-StartLoc);
			//drop the keyword from the line string, we don't need it now
			ItemEffectLine[i].erase(0, KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
        switch (i)
			{
            case 0:     //the effect name
				{
                if (ItemEffectLine[i] == "")
					continue;
                Name = ItemEffectLine[i];
                break;
				}
            case 1:     //the effect subname 
				{
                if (ItemEffectLine[i] == "")
					continue;
                SubName = ItemEffectLine[i];
                break;
				}
			case 2:		// the effects Display Name if different form main name.
				{
				if (ItemEffectLine[i] == "")
					continue;
				DisplayName = ItemEffectLine[i];
				break;
				}
            case 3:     //effect description
				{  // We have to check for a line break in the Descriptor in the case of Greensteel
                NumOfValues = 0;  // If we are making Greensteel, line breaks may be denoted by a "/p" in the text file.
				StartLoc = 0;
				EndLoc = ItemEffectLine[i].size();
				EndBold = 0;

				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find("/p", StartLoc) != string::npos)  // We need to find out how many there are.
					{  // If we've found one before the end of the description,
					NumOfValues++;  // add one to the total
					StartLoc = ItemEffectLine[i].find("/p", StartLoc+2);  // and move our starting point.
					}
				if (NumOfValues > 0)  // If we've found line breaks
					{
					StartLoc = 0;  // reset the StartLoc.
					for (int x=0; x<NumOfValues; x++)  // We'll have to parse through to add our paragraphs into the description.
						{
						if (ItemEffectLine[i].find("/p", StartLoc) != string::npos)  // Make sure this isn't the last part of the description
							EndLoc = ItemEffectLine[i].find("/p", StartLoc);  // and move our EndLoc to the proper break.
						else  // Otherwise the EndLoc needs to be the end of the line.
							EndLoc = ItemEffectLine[i].npos;
						if (StartLoc == EndLoc)  // In some instances the /p will preceed the first part of the description.
							{  // If that is the case we'll need to
							Description += " \\par ";  // add our paragraph
							StartLoc += 2;  // move the starting position past the break
							EndLoc = ItemEffectLine[i].find("/p", StartLoc);  // and move the ending position to the next one.
							}
						if (ItemEffectLine[i].find("/B", StartLoc) != string::npos)
							{
							if (ItemEffectLine[i].find("/B", StartLoc) == StartLoc)
								{
								EndBold = ItemEffectLine[i].find("/ub", StartLoc);
								Description += "{\\b ";
								Description.append(ItemEffectLine[i], StartLoc+2, EndBold-StartLoc-2);
								Description += "}";
								}
							else
								{
								EndBold = ItemEffectLine[i].find("/ub", StartLoc);
								Description.append(ItemEffectLine[i], StartLoc, EndLoc-StartLoc);  // Now grab some text to add to the description,
								x++;
								Description += " \\par ";  // and add a paragraph designation.
								StartLoc = ItemEffectLine[i].find("/B", StartLoc);
								EndLoc = ItemEffectLine[i].find("/p", StartLoc);  // and move the ending position to the next one.
								Description += "{\\b ";
								Description.append(ItemEffectLine[i], StartLoc+2, EndBold-StartLoc-2);
								Description += "}";
								}
							StartLoc = EndBold+3;
							}
						Description.append(ItemEffectLine[i], StartLoc, EndLoc-StartLoc);
						Description += " \\par ";  // and add a paragraph designation.
						if (EndLoc != ItemEffectLine[i].npos)  // Make sure we're not at the end,
							StartLoc = EndLoc + 2;  // and move the starting position past the next break.
						}
					}
				else
					Description.append(ItemEffectLine[i], StartLoc, EndLoc-StartLoc);  // If it isn't Greensteel, there aren't any and we can add the whole descritpion.
                break;
				}
            case 4:     //effect Type
				{
                if (ItemEffectLine[i] == "")
					continue;
				if (ItemEffectLine[i].find("Bonus") != string::npos)
					Type.push_back(BONUS);
				if (ItemEffectLine[i].find("Prefix") != string::npos)
					Type.push_back(PREFIX);
				if (ItemEffectLine[i].find("Suffix") != string::npos)
					Type.push_back(SUFFIX);
				if (ItemEffectLine[i].find("Material") != string::npos)
					Type.push_back(MATERIAL);
				if (ItemEffectLine[i].find("Eldritch") != string::npos)
					Type.push_back(ELDRITCH);
				if (ItemEffectLine[i].find("Greensteel InvElement") != string::npos)
					Type.push_back(INVASIONELEMENT);
				if (ItemEffectLine[i].find("Greensteel Invasion") != string::npos)
					Type.push_back(GSINVASION);
				if (ItemEffectLine[i].find("Greensteel SubElement") != string::npos)
					Type.push_back(SUBJUGATIONELEMENT);
				if (ItemEffectLine[i].find("Greensteel Subjugation") != string::npos)
					Type.push_back(GSSUBJUGATION);
				if (ItemEffectLine[i].find("Greensteel DevElement") != string::npos)
					Type.push_back(DEVASTATIONELEMENT);
				if (ItemEffectLine[i].find("Greensteel Devastation") != string::npos)
					Type.push_back(GSDEVASTATION);
				if (ItemEffectLine[i].find("DTeldritch") != string::npos)
					Type.push_back(DTELDRITCH);
				if (ItemEffectLine[i].find("DT Tempest") != string::npos)
					Type.push_back(DTTEMPEST);
				if (ItemEffectLine[i].find("DT Sovereign") != string::npos)
					Type.push_back(DTSOVEREIGN);
				if (ItemEffectLine[i].find("ShavElement") != string::npos)
					Type.push_back(SHAVARATHELEMENT);
				if (ItemEffectLine[i].find("ShavEffect") != string::npos)
					Type.push_back(SHAVARATHEFFECT);
				if (ItemEffectLine[i].find("EpicEffect") != string::npos)
					Type.push_back(EPICEFFECT);
				break;
				}
			case 5:		// What items can the effect be applied to
				{
                NumOfValues = 1;
				StartLoc = 0;

				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc+1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					// Check for the various armor and shield types
					if (Substring == "Padded Armor" || Substring == "Armor")
						AppliedTo.push_back(PADDEDARMOR);
					if (Substring == "Leather Armor" || Substring == "Armor")
						AppliedTo.push_back(LEATHERARMOR);
					if (Substring == "Studded Leather Armor" || Substring == "Armor")
						AppliedTo.push_back(STUDDEDLEATHERARMOR);
					if (Substring == "Chain Shirt" || Substring == "Armor")
						AppliedTo.push_back(CHAINSHIRTARMOR);
					if (Substring == "Hide Armor" || Substring == "Armor")
						AppliedTo.push_back(HIDEARMOR);
					if (Substring == "Scalemail" || Substring == "Armor")
						AppliedTo.push_back(SCALEMAILARMOR);
					if (Substring == "Chain Mail" || Substring == "Armor")
						AppliedTo.push_back(CHAINMAILARMOR);
					if (Substring == "Breastplate" || Substring == "Armor")
						AppliedTo.push_back(BREASTPLATEARMOR);
					if (Substring == "Brigadine" || Substring == "Armor")
						AppliedTo.push_back(BRIGADINEARMOR);
					if (Substring == "Splintmail" || Substring == "Armor")
						AppliedTo.push_back(SPLINTMAILARMOR);
					if (Substring == "Banded Mail" || Substring == "Armor")
						AppliedTo.push_back(BANDEDMAILARMOR);
					if (Substring == "Half Plate" || Substring == "Armor")
						AppliedTo.push_back(HALFPLATEARMOR);
					if (Substring == "Full Plate" || Substring == "Armor")
						AppliedTo.push_back(FULLPLATEARMOR);
					if (Substring == "Docent")
						AppliedTo.push_back(DOCENT);
					if (Substring == "Robe")
						AppliedTo.push_back(ROBE);
					/*if (Substring == "Outfit")
						AppliedTo.push_back(OUTFIT);*/
					if (Substring == "Buckler" || Substring == "Shields")
						AppliedTo.push_back(BUCKLER);
					if (Substring == "Small Shield" || Substring == "Shields")
						AppliedTo.push_back(SMALLSHIELD);
					if (Substring == "Large Shield" || Substring == "Shields")
						AppliedTo.push_back(LARGESHIELD);
					if (Substring == "Tower Shield" || Substring == "Shields")
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
					if (Substring == "Bastard Sword" || Substring == "Weapons")
						AppliedTo.push_back(BASTARDSWORD);
					if (Substring == "Battle Axe" || Substring == "Weapons")
						AppliedTo.push_back(BATTLEAXE);
					if (Substring == "Club" || Substring == "Weapons")
						AppliedTo.push_back(CLUB);
					if (Substring == "Dagger" || Substring == "Weapons")
						AppliedTo.push_back(DAGGER);
					if (Substring == "Dart" || Substring == "Weapons")
						AppliedTo.push_back(DART);
					if (Substring == "Dwarven War Axe" || Substring == "Weapons")
						AppliedTo.push_back(DWARVENWARAXE);
					if (Substring == "Falchion" || Substring == "Weapons")
						AppliedTo.push_back(FALCHION);
					if (Substring == "Great Axe" || Substring == "Weapons")
						AppliedTo.push_back(GREATAXE);
					if (Substring == "Great Club" || Substring == "Weapons")
						AppliedTo.push_back(GREATCLUB);
					if (Substring == "Great Crossbow" || Substring == "Weapons")
						AppliedTo.push_back(GREATCROSSBOW);
					if (Substring == "Great Sword" || Substring == "Weapons")
						AppliedTo.push_back(GREATSWORD);
					if (Substring == "Handaxe" || Substring == "Weapons")
						AppliedTo.push_back(HANDAXE);
					if (Substring == "Handwraps" || Substring == "Weapons")
						AppliedTo.push_back(HANDWRAPS);
					if (Substring == "Heavy Crossbow" || Substring == "Weapons")
						AppliedTo.push_back(HEAVYCROSSBOW);
					if (Substring == "Heavy Mace" || Substring == "Weapons")
						AppliedTo.push_back(HEAVYMACE);
					if (Substring == "Heavy Pick" || Substring == "Weapons")
						AppliedTo.push_back(HEAVYPICK);
					if (Substring == "Kama" || Substring == "Weapons")
						AppliedTo.push_back(KAMA);
					if (Substring == "Khopesh" || Substring == "Weapons")
						AppliedTo.push_back(KHOPESH);
					if (Substring == "Kukri" || Substring == "Weapons")
						AppliedTo.push_back(KUKRI);
					if (Substring == "Light Crossbow" || Substring == "Weapons")
						AppliedTo.push_back(LIGHTCROSSBOW);
					if (Substring == "Light Hammer" || Substring == "Weapons")
						AppliedTo.push_back(LIGHTHAMMER);
					if (Substring == "Light Pick" || Substring == "Weapons")
						AppliedTo.push_back(LIGHTPICK);
					if (Substring == "Light Mace" || Substring == "Weapons")
						AppliedTo.push_back(LIGHTMACE);
					if (Substring == "Long Bow" || Substring == "Weapons")
						AppliedTo.push_back(LONGBOW);
					if (Substring == "Long Sword" || Substring == "Weapons")
						AppliedTo.push_back(LONGSWORD);
					if (Substring == "Maul" || Substring == "Weapons")
						AppliedTo.push_back(MAUL);
					if (Substring == "Morningstar" || Substring == "Weapons")
						AppliedTo.push_back(MORNINGSTAR);
					if (Substring == "Quarterstaff" || Substring == "Weapons")
						AppliedTo.push_back(QUARTERSTAFF);
					if (Substring == "Rapier" || Substring == "Weapons")
						AppliedTo.push_back(RAPIER);
					if (Substring == "Repeating Heavy Crossbow" || Substring == "Weapons")
						AppliedTo.push_back(REPEATINGHEAVYCROSSBOW);
					if (Substring == "Repeating Light Crossbow" || Substring == "Weapons")
						AppliedTo.push_back(REPEATINGLIGHTCROSSBOW);
					if (Substring == "Scimitar" || Substring == "Weapons")
						AppliedTo.push_back(SCIMITAR);
					if (Substring == "Short Bow" || Substring == "Weapons")
						AppliedTo.push_back(SHORTBOW);
					if (Substring == "Short Sword" || Substring == "Weapons")
						AppliedTo.push_back(SHORTSWORD);
					if (Substring == "Shuriken"  || Substring == "Weapons")
						AppliedTo.push_back(SHURIKEN);
					if (Substring == "Sickle" || Substring == "Weapons")
						AppliedTo.push_back(SICKLE);
					if (Substring == "Throwing Axe" || Substring == "Weapons")
						AppliedTo.push_back(THROWINGAXE);
					if (Substring == "Throwing Dagger" || Substring == "Weapons")
						AppliedTo.push_back(THROWINGDAGGER);
					if (Substring == "Throwing Hammer" || Substring == "Weapons")
						AppliedTo.push_back(THROWINGHAMMER);
					if (Substring == "War Hammer" || Substring == "Weapons")
						AppliedTo.push_back(WARHAMMER);
					}
				break;
				}
			case 6:		// Check to see if any abilities are modified.
				{
				NumOfValues = 0;
				StartLoc = 0;
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<=NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					if (Substring == "Strength")
						AbilityModifier.push_back(STRENGTH);
					if (Substring == "Dexterity")
						AbilityModifier.push_back(DEXTERITY);
					if (Substring == "Constitution")
						AbilityModifier.push_back(CONSTITUTION);
					if (Substring == "Intelligence")
						AbilityModifier.push_back(INTELLIGENCE);
					if (Substring == "Wisdom")
						AbilityModifier.push_back(WISDOM);
					if (Substring == "Charisma")
						AbilityModifier.push_back(CHARISMA);
					}
				break;
				}
			case 7: // Check for ability modifier types
				{
				NumOfValues = 0;
				StartLoc = 0;
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<=NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					if (Substring == "Alchemical")
						AbilityModType.push_back(ALCHEMICALMOD);
					if (Substring == "Competence")
						AbilityModType.push_back(COMPETENCEMOD);
					if (Substring == "Enhancement")
						AbilityModType.push_back(ENHANCEMENTMOD);
					if (Substring == "Exceptional")
						AbilityModType.push_back(EXCEPTIONALMOD);
					if (Substring == "Luck")
						AbilityModType.push_back(LUCKMOD);
					if (Substring == "Misc")
						AbilityModType.push_back(MISCMOD);
					if (Substring == "Penalty")
						AbilityModType.push_back(PENALTYMOD);
					if (Substring == "Profane")
						AbilityModType.push_back(PROFANEMOD);
					}
					break;
				}
			case 8: // Check to see the change in abilities values
				{
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",") != string::npos)
					{
					EndLoc = ItemEffectLine[i].find (",");
					Value = atoi(ItemEffectLine[i].c_str());
					AbilityChange.push_back(Value);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);
					}
				Value = atoi(ItemEffectLine[i].c_str());
				AbilityChange.push_back(Value);
				break;
				}
			case 9: // Check for Skills that are affected if any
				{
				NumOfValues = 0;
				StartLoc = 0;
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<=NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					if (Substring == "Balance")
						SkillModifier.push_back(BALANCE);
					if (Substring == "Bluff")
						SkillModifier.push_back(BLUFF);
					if (Substring == "Concentration")
						SkillModifier.push_back(CONCENTRATION);
					if (Substring == "Diplomacy")
						SkillModifier.push_back(DIPLOMACY);
					if (Substring == "Disable Device")
						SkillModifier.push_back(DISABLEDEVICE);
					if (Substring == "Haggle")
						SkillModifier.push_back(HAGGLE);
					if (Substring == "Heal")
						SkillModifier.push_back(HEAL);
					if (Substring == "Hide")
						SkillModifier.push_back(HIDE);
					if (Substring == "Intimidate")
						SkillModifier.push_back(INTIMIDATE);
					if (Substring == "Jump")
						SkillModifier.push_back(JUMP);
					if (Substring == "Listen")
						SkillModifier.push_back(LISTEN);
					if (Substring == "Move Silently")
						SkillModifier.push_back(MOVESILENTLY);
					if (Substring == "Open Lock")
						SkillModifier.push_back(OPENLOCK);
					if (Substring == "Perform")
						SkillModifier.push_back(PERFORM);
					if (Substring == "Repair")
						SkillModifier.push_back(REPAIR);
					if (Substring == "Search")
						SkillModifier.push_back(SEARCH);
					if (Substring == "Spot")
						SkillModifier.push_back(SPOT);
					if (Substring == "Swim")
						SkillModifier.push_back(SWIM);
					if (Substring == "Tumble")
						SkillModifier.push_back(TUMBLE);
					if (Substring == "Use Magic Device")
						SkillModifier.push_back(UMD);
					}
				break;
				}
			case 10: // check for skill modifier types
				{
				NumOfValues = 0;
				StartLoc = 0;
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<=NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					if (Substring == "Alchemical")
						SkillModType.push_back(ALCHEMICALMOD);
					if (Substring == "Competence")
						SkillModType.push_back(COMPETENCEMOD);
					if (Substring == "Enhancement")
						SkillModType.push_back(ENHANCEMENTMOD);
					if (Substring == "Exceptional")
						SkillModType.push_back(EXCEPTIONALMOD);
					if (Substring == "Luck")
						SkillModType.push_back(LUCKMOD);
					if (Substring == "Misc")
						SkillModType.push_back(MISCMOD);
					if (Substring == "Penalty")
						SkillModType.push_back(PENALTYMOD);
					}
					break;
				}
			case 11: // check to see the change in skill values.
				{
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",") != string::npos)
					{
					EndLoc = ItemEffectLine[i].find (",");
					Value = atoi(ItemEffectLine[i].c_str());
					SkillChange.push_back(Value);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);
					}
				Value = atoi(ItemEffectLine[i].c_str());
				SkillChange.push_back(Value);
				break;
				}
			case 12: // Check for Saves that are affected if any.
				{
				NumOfValues = 0;
				StartLoc = 0;
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<=NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					if (Substring == "Fortitude")
						SaveModifier.push_back(FORTITUDESAVE);
					if (Substring == "Reflex")
						SaveModifier.push_back(REFLEXSAVE);
					if (Substring == "Will")
						SaveModifier.push_back(WILLSAVE);
					}
				break;
				}
			case 13: // Check for the Saves modifier types
				{
				NumOfValues = 0;
				StartLoc = 0;
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",", StartLoc) != string::npos)
					{
					NumOfValues++;
					StartLoc = ItemEffectLine[i].find(",", StartLoc+1);
					}
				for (int x=0; x<=NumOfValues; x++)
					{
					if (ItemEffectLine[i].find(",") != string::npos)
						EndLoc = ItemEffectLine[i].find(",");
					else
						EndLoc = ItemEffectLine[i].size();
					Substring = ItemEffectLine[i].substr(0, EndLoc);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);

					if (Substring == "Alchemical")
						SaveModType.push_back(ALCHEMICALMOD);
					if (Substring == "Competence")
						SaveModType.push_back(COMPETENCEMOD);
					if (Substring == "Enhancement")
						SaveModType.push_back(ENHANCEMENTMOD);
					if (Substring == "Exceptional")
						SaveModType.push_back(EXCEPTIONALMOD);
					if (Substring == "Insight")
						SaveModType.push_back(INSIGHTMOD);
					if (Substring == "Luck")
						SaveModType.push_back(LUCKMOD);
					if (Substring == "Misc")
						SaveModType.push_back(MISCMOD);
					if (Substring == "Penalty")
						SaveModType.push_back(PENALTYMOD);
					if (Substring == "Resistance")
						SaveModType.push_back(RESISTANCEMOD);
					if (Substring == "Epic")
						SaveModType.push_back(EPICMOD);
					}
				break;
				}
			case 14: // Check for the value changes in the saves.
				{
				if (ItemEffectLine[i] == "")
					continue;
				while (ItemEffectLine[i].find(",") != string::npos)
					{
					EndLoc = ItemEffectLine[i].find (",");
					Value = atoi(ItemEffectLine[i].c_str());
					SaveChange.push_back(Value);
					ItemEffectLine[i].erase(0, EndLoc +1);
					StripStringLeadingWhiteSpace(ItemEffectLine[i]);
					}
				Value = atoi(ItemEffectLine[i].c_str());
				SaveChange.push_back(Value);
				break;
				}
			case 15: // Check for Armor Class modification type if any.
				{					
				if (ItemEffectLine[i] == "")
					continue;
				if (ItemEffectLine[i].find("Alchemical") != string::npos)
					ACModType = ALCHEMICALMOD;
				if (ItemEffectLine[i].find("Armor") != string::npos)
					ACModType = ARMORMOD;
				if (ItemEffectLine[i].find("Bonus") != string::npos)
					ACModType = BONUSMOD;
				if (ItemEffectLine[i].find("Competence") != string::npos)
					ACModType = COMPETENCEMOD;
				if (ItemEffectLine[i].find("Deflection") != string::npos)
					ACModType = DEFLECTIONMOD;
				if (ItemEffectLine[i].find("Dodge") != string::npos)
					ACModType = DODGEMOD;
				if (ItemEffectLine[i].find("Exceptional") != string::npos)
					ACModType = EXCEPTIONALMOD;
				if (ItemEffectLine[i].find("Insight") != string::npos)
					ACModType = INSIGHTMOD;
				if (ItemEffectLine[i].find("Luck") != string::npos)
					ACModType = LUCKMOD;
				if (ItemEffectLine[i].find("Misc") != string::npos)
					ACModType = MISCMOD;
				if (ItemEffectLine[i].find("Natural") != string::npos)
					ACModType = NATURALMOD;
				if (ItemEffectLine[i].find("Penalty") != string::npos)
					ACModType = PENALTYMOD;
				if (ItemEffectLine[i].find("Shield") != string::npos)
					ACModType = SHIELDMOD;
				break;
				}
			case 16: // Get the value for the AC change
				{
				if (ItemEffectLine[i] == "")
					continue;
				Value = atoi(ItemEffectLine[i].c_str());
				ACChange = Value;
				break;
				}
			case 17: // Check for any Hit point change type
				{
				if (ItemEffectLine[i] == "")
					continue;
				if (ItemEffectLine[i].find("Alchemical") != string::npos)
					HPModType = ALCHEMICALMOD;
				if (ItemEffectLine[i].find("Competence") != string::npos)
					HPModType = COMPETENCEMOD;
				if (ItemEffectLine[i].find("Exceptional") != string::npos)
					HPModType = EXCEPTIONALMOD;
				if (ItemEffectLine[i].find("Insight") != string::npos)
					HPModType = INSIGHTMOD;
				if (ItemEffectLine[i].find("Luck") != string::npos)
					HPModType = LUCKMOD;
				if (ItemEffectLine[i].find("Maximum") != string::npos)
					HPModType = MAXIMUMMOD;
				if (ItemEffectLine[i].find("Misc") != string::npos)
					HPModType = MISCMOD;
				if (ItemEffectLine[i].find("Penalty") != string::npos)
					HPModType = PENALTYMOD;
				if (ItemEffectLine[i].find("Toughness") != string::npos)
					HPModType = TOUGHNESSMOD;
				if (ItemEffectLine[i].find("Elemental") != string::npos)
					HPModType = ELEMENTALMOD;
				if (ItemEffectLine[i].find("ImpElemental") != string::npos)
					HPModType = IMPROVEDELEMENTALMOD;
				if (ItemEffectLine[i].find("GreatElemental") != string::npos)
					HPModType = GREATERELEMENTALMOD;
				if (ItemEffectLine[i].find("Pirate") != string::npos)
					HPModType = PIRATEMOD;
				break;
				}
			case 18: // Get the value for the HP Change
				{
				if (ItemEffectLine[i] == "")
					continue;
				Value = atoi(ItemEffectLine[i].c_str());
				HPChange = Value;
				break;
				}
			case 19: // Check for any Spell point change type
				{
				if (ItemEffectLine[i] == "")
					continue;
				if (ItemEffectLine[i].find("Alchemical") != string::npos)
					SPModType = ALCHEMICALMOD;
				if (ItemEffectLine[i].find("Competence") != string::npos)
					SPModType = COMPETENCEMOD;
				if (ItemEffectLine[i].find("Exceptional") != string::npos)
					SPModType = EXCEPTIONALMOD;
				if (ItemEffectLine[i].find("Insight") != string::npos)
					SPModType = INSIGHTMOD;
				if (ItemEffectLine[i].find("Luck") != string::npos)
					SPModType = LUCKMOD;
				if (ItemEffectLine[i].find("Maximum") != string::npos)
					SPModType = MAXIMUMMOD;
				if (ItemEffectLine[i].find("Misc") != string::npos)
					SPModType = MISCMOD;
				if (ItemEffectLine[i].find("Penalty") != string::npos)
					SPModType = PENALTYMOD;
				if (ItemEffectLine[i].find("Elemental") != string::npos)
					SPModType = ELEMENTALMOD;
				if (ItemEffectLine[i].find("ImpElemental") != string::npos)
					SPModType = IMPROVEDELEMENTALMOD;
				if (ItemEffectLine[i].find("GreatElemental") != string::npos)
					SPModType = GREATERELEMENTALMOD;
				if (ItemEffectLine[i].find("Pirate") != string::npos)
					SPModType = PIRATEMOD;
				break;
				}
			case 20: // get the value for the SP change
				{
				if (ItemEffectLine[i] == "")
					continue;
				Value = atoi(ItemEffectLine[i].c_str());
				SPChange = Value;
				break;
				}
			case 21: //get the Greensteel Element Type
				{
				if (ItemEffectLine[i] == "")
					continue;
				if (ItemEffectLine[i].find("Non Effect") != string::npos)
					GSElementTypes.push_back(NOEFFECT);
				if (ItemEffectLine[i].find("Air") != string::npos)
					GSElementTypes.push_back(AIR);
				if (ItemEffectLine[i].find("ArErt") != string::npos)
					GSElementTypes.push_back(AEARTH);
				if (ItemEffectLine[i].find("ArFr") != string::npos)
					GSElementTypes.push_back(AFIRE);
				if (ItemEffectLine[i].find("ArNeg") != string::npos)
					GSElementTypes.push_back(ANEG);
				if (ItemEffectLine[i].find("ArPos") != string::npos)
					GSElementTypes.push_back(APOS);
				if (ItemEffectLine[i].find("ArWtr") != string::npos)
					GSElementTypes.push_back(AWATER);
				if (ItemEffectLine[i].find("Earth") != string::npos)
					GSElementTypes.push_back(EARTH);
				if (ItemEffectLine[i].find("ErtAr") != string::npos)
					GSElementTypes.push_back(EAIR);
				if (ItemEffectLine[i].find("ErtFr") != string::npos)
					GSElementTypes.push_back(EFIRE);
				if (ItemEffectLine[i].find("ErtNeg") != string::npos)
					GSElementTypes.push_back(ENEG);
				if (ItemEffectLine[i].find("ErtPos") != string::npos)
					GSElementTypes.push_back(EPOS);
				if (ItemEffectLine[i].find("ErtWtr") != string::npos)
					GSElementTypes.push_back(EWATER);
				if (ItemEffectLine[i].find("Fire") != string::npos)
					GSElementTypes.push_back(FIRE);
				if (ItemEffectLine[i].find("FrAr") != string::npos)
					GSElementTypes.push_back(FAIR);
				if (ItemEffectLine[i].find("FrErt") != string::npos)
					GSElementTypes.push_back(FEARTH);
				if (ItemEffectLine[i].find("FrNeg") != string::npos)
					GSElementTypes.push_back(FNEG);
				if (ItemEffectLine[i].find("FrPos") != string::npos)
					GSElementTypes.push_back(FPOS);
				if (ItemEffectLine[i].find("FrWtr") != string::npos)
					GSElementTypes.push_back(FWATER);
				if (ItemEffectLine[i].find("Negative") != string::npos)
					GSElementTypes.push_back(NEGATIVE);
				if (ItemEffectLine[i].find("NegAr") != string::npos)
					GSElementTypes.push_back(NAIR);
				if (ItemEffectLine[i].find("NegErt") != string::npos)
					GSElementTypes.push_back(NEARTH);
				if (ItemEffectLine[i].find("NegFr") != string::npos)
					GSElementTypes.push_back(NFIRE);
				if (ItemEffectLine[i].find("NegPos") != string::npos)
					GSElementTypes.push_back(NPOS);
				if (ItemEffectLine[i].find("NegWtr") != string::npos)
					GSElementTypes.push_back(NWATER);
				if (ItemEffectLine[i].find("Positive") != string::npos)
					GSElementTypes.push_back(POSITIVE);
				if (ItemEffectLine[i].find("PosAr") != string::npos)
					GSElementTypes.push_back(PAIR);
				if (ItemEffectLine[i].find("PosErt") != string::npos)
					GSElementTypes.push_back(PEARTH);
				if (ItemEffectLine[i].find("PosFr") != string::npos)
					GSElementTypes.push_back(PFIRE);
				if (ItemEffectLine[i].find("PosNeg") != string::npos)
					GSElementTypes.push_back(PNEG);
				if (ItemEffectLine[i].find("PosWtr") != string::npos)
					GSElementTypes.push_back(PWATER);
				if (ItemEffectLine[i].find("Water") != string::npos)
					GSElementTypes.push_back(WATER);
				if (ItemEffectLine[i].find("WtrAr") != string::npos)
					GSElementTypes.push_back(WAIR);
				if (ItemEffectLine[i].find("WtrErt") != string::npos)
					GSElementTypes.push_back(WEARTH);
				if (ItemEffectLine[i].find("WtrFr") != string::npos)
					GSElementTypes.push_back(WFIRE);
				if (ItemEffectLine[i].find("WtrNeg") != string::npos)
					GSElementTypes.push_back(WNEG);
				if (ItemEffectLine[i].find("WtrPos") != string::npos)
					GSElementTypes.push_back(WPOS);
				if (ItemEffectLine[i].find("No Bonus") != string::npos)
					GSElementTypes.push_back(NOBONUS);
				if (ItemEffectLine[i].find("Ash") != string::npos)
					GSElementTypes.push_back(ASH);
				if (ItemEffectLine[i].find("BoLaS") != string::npos)
					GSElementTypes.push_back(BOLAS);
				if (ItemEffectLine[i].find("Dust") != string::npos)
					GSElementTypes.push_back(DUST);
				if (ItemEffectLine[i].find("Ice") != string::npos)
					GSElementTypes.push_back(ICE);
				if (ItemEffectLine[i].find("Lightning") != string::npos)
					GSElementTypes.push_back(LIGHTNING);
				if (ItemEffectLine[i].find("Magma") != string::npos)
					GSElementTypes.push_back(MAGMA);
				if (ItemEffectLine[i].find("Mineral") != string::npos)
					GSElementTypes.push_back(MINERAL);
				if (ItemEffectLine[i].find("Ooze") != string::npos)
					GSElementTypes.push_back(OOZE);
				if (ItemEffectLine[i].find("Radiance") != string::npos)
					GSElementTypes.push_back(RADIANCE);
				if (ItemEffectLine[i].find("Salt") != string::npos)
					GSElementTypes.push_back(SALT);
				if (ItemEffectLine[i].find("Smoke") != string::npos)
					GSElementTypes.push_back(SMOKE);
				if (ItemEffectLine[i].find("Stalemate") != string::npos)
					GSElementTypes.push_back(STALEMATE);
				if (ItemEffectLine[i].find("Steam") != string::npos)
					GSElementTypes.push_back(STEAM);
				if (ItemEffectLine[i].find("Tempered") != string::npos)
					GSElementTypes.push_back(TEMPERED);
				if (ItemEffectLine[i].find("Vacuum") != string::npos)
					GSElementTypes.push_back(VACUUM);
				break;
				}
			case 22:  // Get Epic Slot Colors
				{
				if (ItemEffectLine[i] == "")
					continue;
				if (ItemEffectLine[i].find("NonColor") != string::npos)
					EpicEffectColors.push_back(NONCOLOR);
				if (ItemEffectLine[i].find("Blue") != string::npos)
					{
					EpicEffectColors.push_back(BLUE);
					EpicEffectColors.push_back(GREEN);
					EpicEffectColors.push_back(VIOLET);
					}
				if (ItemEffectLine[i].find("Colorless") != string::npos)
					{
					EpicEffectColors.push_back(BLUE);
					EpicEffectColors.push_back(COLORLESS);
					EpicEffectColors.push_back(GREEN);
					EpicEffectColors.push_back(ORANGE);
					EpicEffectColors.push_back(RED);
					EpicEffectColors.push_back(VIOLET);
					EpicEffectColors.push_back(YELLOW);
					}
				if (ItemEffectLine[i].find("Red") != string::npos)
					{
					EpicEffectColors.push_back(ORANGE);
					EpicEffectColors.push_back(RED);
					EpicEffectColors.push_back(VIOLET);
					}
				if (ItemEffectLine[i].find("Yellow") != string::npos)
					{
					EpicEffectColors.push_back(GREEN);
					EpicEffectColors.push_back(ORANGE);
					EpicEffectColors.push_back(YELLOW);
					}
				break;
				}
			}
		}   
    return;
    #undef NUMKEYWORDS
	}
//--------------------------------------------------------------------
string ItemEffectClass::GetItemEffectName()
	{
	return Name;
	}
//--------------------------------------------------------------------
string ItemEffectClass::GetItemEffectCombinedName()
	{
	string CombinedName;
	CombinedName = Name;
	if (SubName == "")
		return CombinedName;
	CombinedName += "{";
	CombinedName += SubName;
	CombinedName += "}";
	return CombinedName;
	}
//--------------------------------------------------------------------
string ItemEffectClass::GetItemEffectDisplayName()
	{
	if (DisplayName == "")
		return Name;
	return DisplayName;
	}
//--------------------------------------------------------------------
string ItemEffectClass::GetItemEffectSubName()
	{
	return SubName;
	}
//--------------------------------------------------------------------
string ItemEffectClass::GetItemEffectDescription()
	{
	return Description;
	}
//--------------------------------------------------------------------
void ItemEffectClass::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}
//--------------------------------------------------------------------
bool ItemEffectClass::DoesTypeMatch(unsigned int EffectType)
	{
	if (Type.size() == 0)
		return false;
	for (unsigned i=0; i<Type.size(); i++)
		{
		if (Type[i] == EffectType)
			return true;
		}
	return false;
	}

//-----------------------------------------------------
bool ItemEffectClass::DoesAppliedToMatch(unsigned int AppliedToType)
	{
	if (AppliedTo.size() == 0)
		return false;
	for (unsigned i=0; i<AppliedTo.size(); i++)
		{
		if (AppliedTo[i] == AppliedToType)
			return true;
		}
	return false;
	}

//-----------------------------------------------------
bool ItemEffectClass::DoesGSElementTypeMatch(unsigned int GSElementType)
	{
	if (GSElementTypes.size() == 0)
		return false;
	for (unsigned int i=0; i<GSElementTypes.size(); i++)
		{
		if (GSElementTypes[i] == GSElementType)
			return true;
		}
	return false;
	}

//-----------------------------------------------------
int ItemEffectClass::GetItemEffectAbilityModifier(unsigned int Index, int *Modifier)
	{
	if (Index >= AbilityModifier.size())
        return -1;
    *Modifier = AbilityModifier[Index];
    return 0;
	}
//----------------------------------------------------------------------
int ItemEffectClass::GetItemEffectAbilityModType(unsigned int Index)
	{
	return AbilityModType[Index];
	}

//-----------------------------------------------------------------------
int ItemEffectClass::GetItemEffectAbilityChange(unsigned int Index)
	{
	return AbilityChange[Index];
	}

//-----------------------------------------------------------------------
int ItemEffectClass::GetItemEffectACChange()
	{
	return ACChange;
	}

//-----------------------------------------------------------------------
int ItemEffectClass::GetItemEffectACModType()
	{
	return ACModType;
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSkillModifier(unsigned int Index, int *Modifier)
	{
	if (Index >= SkillModifier.size())
		return -1;
	*Modifier = SkillModifier[Index];
	return 0;
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSkillModType(unsigned int Index)
	{
	return SkillModType[Index];
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSkillChange(unsigned int Index)
	{
	return SkillChange[Index];
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSaveModifier(unsigned int Index, int *Modifier)
	{
	if (Index >= SaveModifier.size())
		return -1;
	*Modifier = SaveModifier[Index];
	return 0;
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSaveModType(unsigned int Index)
	{
	return SaveModType[Index];
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSaveChange(unsigned int Index)
	{
	return SaveChange[Index];
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetGSElementType(unsigned int Index)
	{
	return GSElementTypes[Index];
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetGSElementTypesSize()
	{
	return GSElementTypes.size();
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetEpicEffectColor(unsigned int Index)
	{
		return EpicEffectColors[Index];
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetEpicEffectColorsSize()
	{
	return EpicEffectColors.size();
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectHPModType()
	{
	return HPModType;
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectHPChange()
	{
	return HPChange;
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSPModType()
	{
	return SPModType;
	}

//--------------------------------------------------------------------
int ItemEffectClass::GetItemEffectSPChange()
	{
	return SPChange;
	}