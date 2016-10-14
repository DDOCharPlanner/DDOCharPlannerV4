#include "ItemClass.h"
#include "DataClass.h"
#include "CharacterClass.h"

//static members
unordered_map<string, ITEMBASETYPE> ItemClass::BaseKeywords;
unordered_map<string, ITEMTYPE> ItemClass::TypeKeywords;
unordered_map<string, EPICSLOTCOLOR> ItemClass::ColorKeywords;

//----------------------------------------------------------------
ItemClass::ItemClass()
	{	
	//clear out the member variables so we are not starting with garbage
	Name = "";
	Base = GENERIC;
	Type = PADDEDARMOR;
	FlavorText = "";
	StaticEffects.clear();
	EpicItemSlotOne = NONCOLOR;
	EpicItemSlotTwo = NONCOLOR;
	ClickyEffect = "";
	BaseAC = 0;
	MaxDex = 99;
	ArmorCheckPenalty = 0;
	InitHash();
	}
 
//----------------------------------------------------------------
ItemClass::~ItemClass()
	{
	}

//----------------------------------------------------------------
ItemClass::ItemClass(const ItemClass &source)
	{
	//the copy constructor. We need this because this class lives in a vector
	//and the vector may need to copy the class somewhere else...
	
	Name = source.Name;
	Base = source.Base;
	Type = source.Type;
	FlavorText = source.FlavorText;
	StaticEffects.clear();
	for (unsigned int i=0; i<source.StaticEffects.size(); i++)
		StaticEffects.push_back(source.StaticEffects[i]);
	EpicItemSlotOne = source.EpicItemSlotOne;
	EpicItemSlotTwo = source.EpicItemSlotTwo;
	ClickyEffect = source.ClickyEffect;
	BaseAC = source.BaseAC;
	MaxDex = source.MaxDex;
	ArmorCheckPenalty = source.ArmorCheckPenalty;
	}

//----------------------------------------------------------------
ItemClass& ItemClass::operator=(const ItemClass &source)
	{
	//the = function overload. We need this because this class lives in a vector
	//and unfortunately, vectors use this function...
	Name = source.Name;
	Base = source.Base;
	Type = source.Type;
	FlavorText = source.FlavorText;
	StaticEffects.clear();
	for (unsigned int i=0; i<source.StaticEffects.size(); i++)
		StaticEffects.push_back(source.StaticEffects[i]);
	EpicItemSlotOne = source.EpicItemSlotOne;
	EpicItemSlotTwo = source.EpicItemSlotTwo;
	ClickyEffect = source.ClickyEffect;
	BaseAC = source.BaseAC;
	MaxDex = source.MaxDex;
	ArmorCheckPenalty = source.ArmorCheckPenalty;
	
	return *this;
	}

//-----------------------------------------------------------------
ItemClass* const ItemClass::GetItemAddress()
	{
	//IMPORTANT SAFETY TIP: Never ever call this function until the entire feat
	//file has been fully loaded and stored into individual feats. Otherwise you
	//may end up with a bad pointer!
	return this;
	}

//-----------------------------------------------------------------
void ItemClass::InitializeItem(string ItemData)
	{
    #define NUMKEYWORDS 11

	string KeywordString[NUMKEYWORDS];
	string ItemLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	string Substring;
	
    //parse the ItemData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "ITEMNAME: ";
	KeywordString[1] = "ITEMBASE: ";
	KeywordString[2] = "ITEMTYPE: ";
	KeywordString[3] = "FLAVORTEXT: ";
	KeywordString[4] = "STATICEFFECTS: ";
	KeywordString[5] = "CLICKYEFFECT: ";
	KeywordString[6] = "BASEAC: ";
	KeywordString[7] = "MAXDEX: ";
	KeywordString[8] = "ARMORCHECKPENALTY: ";
	KeywordString[9] = "EPICITEMSLOTONE: ";
	KeywordString[10] = "EPICITEMSLOTTWO: ";

    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		ItemLine[i] = "";
		StartLoc = ItemData.find(KeywordString[i]);
		if (StartLoc != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			EndLoc = ItemData.find(";", StartLoc); 
			ItemLine[i] = ItemData.substr(StartLoc + KeywordString[i].size(), EndLoc-StartLoc-KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
	    if (!ItemLine[i].size())
			continue;
        switch (i)
			{
            case 0:     //The Item Name
				{
				Name = ItemLine[i];
				//DEBUG("Item Name: " + Name +  " IN"); 

                break;
				}
            case 1:     //The Item Base (Generic, Named, Greensteel, Dragontouched, Shavarath Ring)
				{
				Base = BaseKeywords.at(ItemLine[i]);
                break;
				}
            case 2:     //Item Type
				{
				Type = TypeKeywords.at(ItemLine[i]);
				break;
				}
			case 3:		// Flavor Text
				{
				FlavorText = ItemLine[i];
                break;
				}
			case 4:		// Static Effects.
				{
				vector<string> tokens;
				split(ItemLine[i], ",", tokens);
				for (unsigned int i=0; i<tokens.size(); i++)
					{
					string strEffectName =  tokens[i];
					string strEffectSubName;
					// Check to see if a Subeffectname exists and if so seperate the string value.
					StartLoc = strEffectName.find('{');
					if (StartLoc != string::npos)
						{
						EndLoc = strEffectName.find('}', StartLoc); //Substring.size();
						strEffectSubName = strEffectName.substr(StartLoc + 1, EndLoc - StartLoc - 1);
						strEffectName.erase(StartLoc);
						}
					//Ok we need to convert an effect to the proper spelling
					if (strEffectName == "Silver Alchemical") {
						strEffectName = "Silver";						
						strEffectSubName = "Silver, Alchemical";
					}

					int index = Data.GetItemEffectIndex(strEffectName, strEffectSubName);
					if(index == 0)
					{
						//DEBUG("ERROR: Item " + Name + " Unknown Effect: " + strEffectName + " " + strEffectSubName);
					}
					StaticEffects.push_back(index);				
					}
				break;
				}
			case 5: // Clicky Effect
				{
				ClickyEffect = ItemLine[i];
				break;
				}
			case 6: // Base AC - Only applies to Armors and Shields.
				{
				BaseAC = atoi(ItemLine[i].c_str());
				break;
				}
			case 7: // Maximum Dex Bonus - Only applies to armors and shields.
				{
				MaxDex = atoi(ItemLine[i].c_str());
				break;
				}
			case 8: // Armor Check Penalty - Applies to Armors and shield. this is also needed to calculate skills correctly
				{
				ArmorCheckPenalty = atoi(ItemLine[i].c_str());
				break;
				}
			case 9:  // Epic Slot Colors - Only applies to Epic Base items
				{
				EpicItemSlotOne = ColorKeywords.at(ItemLine[i]);
				break;
				}
			case 10:  // Epic Slot Colors - Only applies to Epic Base items
				{
				EpicItemSlotTwo = ColorKeywords.at(ItemLine[i]);
				break;
				}
			}
		} 

	//DEBUG("Item Name: " + Name +  " OUT"); 
    #undef NUMKEYWORDS
	}
	
//--------------------------------------------------------------------
int ItemClass::GetArmorCheckPenalty()
	{
	return ArmorCheckPenalty;
	}

//--------------------------------------------------------------------
int ItemClass::GetBaseAC()
	{
	return BaseAC;
	}

//--------------------------------------------------------------------
string ItemClass::GetItemName()
	{
	return Name;
	}
	
//--------------------------------------------------------------------
int ItemClass::GetItemBase()
	{
	return Base;
	}

//---------------------------------------------------------------------
int ItemClass::GetItemStaticEffectIndex(unsigned int Index, unsigned int *StaticEffectIndex)
	{
    if (Index >= StaticEffects.size())
        return -1;
    *StaticEffectIndex = StaticEffects[Index];
    return 0;
	}

//---------------------------------------------------------------------
int ItemClass::GetItemStaticEffectsSize()
	{
	return StaticEffects.size();
	}

//---------------------------------------------------------------------
int ItemClass::GetItemType()
	{
	return Type;
	}

//---------------------------------------------------------------------
string ItemClass::GetItemFlavorText()
	{
	return FlavorText;
	}

//----------------------------------------------------------------------
int ItemClass::GetMaxDex()
	{
	return MaxDex;
	}

//-------------------------------------------------------------------------
bool ItemClass::DoesItemFitSelectedSlot(unsigned int SelectedSlot)
	{
	switch (SelectedSlot)
		{
		case RIGHTHANDSLOT:
			{
			if (Type == BASTARDSWORD)
				return true;
			else if (Type == BATTLEAXE)
				return true;
			else if (Type == CLUB)
				return true;
			else if (Type == DAGGER)
				return true;
			else if (Type == DART)
				return true;
			else if (Type == DWARVENWARAXE)
				return true;
			else if (Type == FALCHION)
				return true;
			else if (Type == GREATAXE)
				return true;
			else if (Type == GREATCLUB)
				return true;
			else if (Type == GREATSWORD)
				return true;
			else if (Type == HANDAXE)
				return true;
			else if (Type == HANDWRAPS)
				return true;
			else if (Type == HEAVYMACE)
				return true;
			else if (Type == HEAVYPICK)
				return true;
			else if (Type == KAMA)
				return true;
			else if (Type == KHOPESH)
				return true;
			else if (Type == KUKRI)
				return true;
			else if (Type == LIGHTHAMMER)
				return true;
			else if (Type == LIGHTMACE)
				return true;
			else if (Type == LIGHTPICK)
				return true;
			else if (Type == LONGSWORD)
				return true;
			else if (Type == MAUL)
				return true;
			else if (Type == MORNINGSTAR)
				return true;
			else if (Type == QUARTERSTAFF)
				return true;
			else if (Type == RAPIER)
				return true;
			else if (Type == SCIMITAR)
				return true;
			else if (Type == SHORTSWORD)
				return true;
			else if (Type == SHURIKEN)
				return true;
			else if (Type == SICKLE)
				return true;
			else if (Type == THROWINGAXE)
				return true;
			else if (Type == THROWINGDAGGER)
				return true;
			else if (Type == THROWINGHAMMER)
				return true;
			else if (Type == WARHAMMER)
				return true;
			else
				return false;
			}
		case LEFTHANDSLOT:
			{
			if (Type == BASTARDSWORD)
				return true;
			else if (Type == BATTLEAXE)
				return true;
			else if (Type == CLUB)
				return true;
			else if (Type == DAGGER)
				return true;
			else if (Type == DWARVENWARAXE)
				return true;
			else if (Type == HANDAXE)
				return true;
			else if (Type == GREATCROSSBOW)
				return true;
			else if (Type == HEAVYCROSSBOW)
				return true;
			else if (Type == HEAVYMACE)
				return true;
			else if (Type == HEAVYPICK)
				return true;
			else if (Type == KAMA)
				return true;
			else if (Type == KHOPESH)
				return true;
			else if (Type == KUKRI)
				return true;
			else if (Type == LIGHTCROSSBOW)
				return true;
			else if (Type == LIGHTHAMMER)
				return true;
			else if (Type == LIGHTMACE)
				return true;
			else if (Type == LIGHTPICK)
				return true;
			else if (Type == LONGBOW)
				return true;
			else if (Type == LONGSWORD)
				return true;
			else if (Type == MORNINGSTAR)
				return true;
			else if (Type == RAPIER)
				return true;
			else if (Type == REPEATINGHEAVYCROSSBOW)
				return true;
			else if (Type == REPEATINGLIGHTCROSSBOW)
				return true;
			else if (Type == SCIMITAR)
				return true;
			else if (Type == SHORTBOW)
				return true;
			else if (Type == SHORTSWORD)
				return true;
			else if (Type == SICKLE)
				return true;
			else if (Type == BUCKLER)
				return true;
			else if (Type == SMALLSHIELD)
				return true;
			else if (Type == LARGESHIELD)
				return true;
			else if (Type == TOWERSHIELD)
				return true;
			else if (Type == WARHAMMER)
				return true;
			else
				return false;
			}
		case AMMOSLOT:
			{
			if (Type == ARROW)
				return true;
			else if (Type == BOLT)
				return true;
			else 
				return false;
			break;
			}
		case FACESLOT:
			{
			if (Type == GOGGLES)
				return true;
			break;
			}
		case ARMORSLOT:
			{
			if (Character.GetRace() != WARFORGED)
				{
				if (Type == PADDEDARMOR)
					return true;
				else if (Type == LEATHERARMOR)
					return true;
				else if (Type == STUDDEDLEATHERARMOR)
					return true;
				else if (Type == CHAINSHIRTARMOR)
					return true;
				else if (Type == HIDEARMOR)
					return true;
				else if (Type == SCALEMAILARMOR)
					return true;
				else if (Type == CHAINMAILARMOR)
					return true;
				else if (Type == BREASTPLATEARMOR)
					return true;
				else if (Type == BRIGADINEARMOR)
					return true;
				else if (Type == SPLINTMAILARMOR)
					return true;
				else if (Type == BANDEDMAILARMOR)
					return true;
				else if (Type == HALFPLATEARMOR)
					return true;
				else if (Type == FULLPLATEARMOR)
					return true;
				else if (Type == ROBE)
					return true;
				/*else if (Type == OUTFIT)
				return true;*/
				}
			else if (Type == DOCENT)
				return true;
			else 
				return false;
			break;
			}
		case BRACERSLOT:
			{
			if (Type == BRACERS)
				return true;
			break;
			}
		case LEFTRINGSLOT:
		case RIGHTRINGSLOT:
			{
			if (Type == RING)
				return true;
			break;
			}
		case HEADSLOT:
			{
			if (Type == HELMET)
				return true;
			break;
			}
		case FEETSLOT:
			{
			if (Type == BOOTS)
				return true;
			break;
			}
		case NECKSLOT:
			{
			if (Type == NECKLACE)
				return true;
			break;
			}
		case GLOVESSLOT:
			{
			if (Type == GLOVESITEM)
				return true;
			break;
			}
		case TRINKETSLOT:
			{
			if (Type == TRINKETITEM)
				return true;
			break;
			}
		case BACKSLOT:
			{
			if (Type == CLOAK)
				return true;
			break;
			}
		case WAISTSLOT:
			{
			if (Type == BELT)
				return true;
			break;
			}
		case QUIVERSLOT:
			{
			if (Type == QUIVER)
				return true;
			break;
			}
		}
		return false;
	}

//-------------------------------------------------------------------------
bool ItemClass::DoesEpicItemSlotOneColorMatch(unsigned int EpicSlotColor)
	{
	if (EpicItemSlotOne == EpicSlotColor)
		return true;
	else
		return false;
	}

//-------------------------------------------------------------------------
bool ItemClass::DoesEpicItemSlotTwoColorMatch(unsigned int EpicSlotColor)
	{
	if (EpicItemSlotTwo == EpicSlotColor)
		return true;
	else
		return false;
	}

//-------------------------------------------------------------------------
string  ItemClass::trim(const string& str, const string& whitespace)
	{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
	}

//-------------------------------------------------------------------------
void  ItemClass::split(const string& str, const string& delimiters , vector<string>& tokens)
	{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
		{
        tokens.push_back(trim(str.substr(lastPos, pos - lastPos)));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
		}
	}

//----------------------------------------------------------------------
void ItemClass::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}

//----------------------------------------------------------------
void ItemClass::InitHash()
	{
	if(BaseKeywords.size() == 0)
		{
		// The Item Base (Generic, Named, Greensteel, Dragontouched, Shavarath Ring)
		BaseKeywords.emplace(pair<string, ITEMBASETYPE>("Generic", GENERIC));
		BaseKeywords.emplace(pair<string, ITEMBASETYPE>("Named",NAMED));
		BaseKeywords.emplace(pair<string, ITEMBASETYPE>("Green Steel",GREENSTEEL));
		BaseKeywords.emplace(pair<string, ITEMBASETYPE>("Dragontouched",DRAGONTOUCHED));
		BaseKeywords.emplace(pair<string, ITEMBASETYPE>("Shavarath Ring",SHAVARATHRING));
		BaseKeywords.emplace(pair<string, ITEMBASETYPE>("Epic",EPIC));
		}

	if(TypeKeywords.size() == 0)
		{
		// Check for the various armor and shield types
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Padded",PADDEDARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Padded Armor",PADDEDARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Leather Armor",LEATHERARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Leather",LEATHERARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Studded Leather Armor",STUDDEDLEATHERARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Studded",STUDDEDLEATHERARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Chain Shirt",CHAINSHIRTARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Hide Armor",HIDEARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Scale Mail",SCALEMAILARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Chainmail",CHAINMAILARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Breastplate",BREASTPLATEARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Brigatine",BRIGADINEARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Brigandine",BRIGADINEARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Splintmail",SPLINTMAILARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Splint Mail",SPLINTMAILARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Banded Mail",BANDEDMAILARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Banded",BANDEDMAILARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Half Plate",HALFPLATEARMOR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Full Plate",FULLPLATEARMOR));

		TypeKeywords.emplace(pair<string, ITEMTYPE>("Docent",DOCENT));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Robe",ROBE));
		/*TypeKeywords.emplace(pair<string, ITEMTYPE>("Outfit",OUTFIT));*/
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Buckler",BUCKLER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Small Shield",SMALLSHIELD));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Large Shield",LARGESHIELD));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Tower Shield",TOWERSHIELD));

		// check for the regular clothing & jewelry types.
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Goggles",GOGGLES));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Helmet",HELMET));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Necklace",NECKLACE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Trinket",TRINKETITEM));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Cloak",CLOAK));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Belt",BELT));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Ring",RING));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Gloves",GLOVESITEM));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Boots",BOOTS));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Bracers",BRACERS));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Quiver",QUIVER));

		// check for the regular weapon types.
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Bastard Sword",BASTARDSWORD));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Battle Axe",BATTLEAXE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Club",CLUB));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Dagger",DAGGER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Dart",DART));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Dwarven War Axe",DWARVENWARAXE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Falchion",FALCHION));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Great Axe",GREATAXE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Great Club",GREATCLUB));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Great Crossbow",GREATCROSSBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Great Sword",GREATSWORD));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Handaxe",HANDAXE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Handwraps",HANDWRAPS));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Heavy Crossbow",HEAVYCROSSBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Heavy Mace",HEAVYMACE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Heavy Pick",HEAVYPICK));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Kama",KAMA));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Khopesh",KHOPESH));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Kukri",KUKRI));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Light Crossbow",LIGHTCROSSBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Light Hammer",LIGHTHAMMER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Light Pick",LIGHTPICK));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Light Mace",LIGHTMACE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Long Bow",LONGBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Long Sword",LONGSWORD));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Maul",MAUL));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Morningstar",MORNINGSTAR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Quarterstaff",QUARTERSTAFF));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Rapier",RAPIER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Repeating Heavy Crossbow",REPEATINGHEAVYCROSSBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Repeating Light Crossbow",REPEATINGLIGHTCROSSBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Scimitar",SCIMITAR));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Short Bow",SHORTBOW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Short Sword",SHORTSWORD));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Shuriken",SHURIKEN));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Sickle",SICKLE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Throwing Axe",THROWINGAXE));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Throwing Dagger",THROWINGDAGGER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Throwing Hammer",THROWINGHAMMER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("War Hammer",WARHAMMER));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Arrow",ARROW));
		TypeKeywords.emplace(pair<string, ITEMTYPE>("Bolt",BOLT));
		}

	if(ColorKeywords.size() == 0)
		{
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("NonColor", NONCOLOR));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Noncolor", NONCOLOR));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Blue",BLUE));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Colorless",COLORLESS));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Green",GREEN));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Orange",ORANGE));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Red",RED));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Violet",VIOLET));
		ColorKeywords.emplace(pair<string, EPICSLOTCOLOR>("Yellow",YELLOW));
		}
	}
