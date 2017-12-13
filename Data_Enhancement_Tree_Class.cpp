#include "Data_Enhancement_Tree_Class.h"
#include "InterfaceManagerClass.h"

//static members
unordered_map <string, ENHANCEMENT_TREE> Data_Enhancement_Tree_Class::EnhancementTreeList;

//---------------------------------------------------------------------------
Data_Enhancement_Tree_Class::Data_Enhancement_Tree_Class()
	{
	}

//---------------------------------------------------------------------------
Data_Enhancement_Tree_Class::~Data_Enhancement_Tree_Class()
	{
	}

//---------------------------------------------------------------------------
void Data_Enhancement_Tree_Class::InitializeEnhancementTree(ENHANCEMENT_TREE Tree, ENHANCEMENT_TREE_TYPE Type, RACE Race, CLASS Class, string Name, bool EnhancementFlag, string Graphic, string Arrows)
	{
	size_t EndLoc;
	string Substring;
	ArrowStruct NewArrow;

	TreeIndex = Tree;
	TreeType = Type;
	TreeRace = Race;
	TreeClass = Class;
	TreeName = Name;
	HasEnhancements = EnhancementFlag;
	LoadBitmap(Graphic, "UserInterface", &TreeBackground);
	EnhancementData.clear();

	while (Arrows.find(",") != string::npos)
		{
		StripStringLeadingWhiteSpace(Arrows);
		EndLoc = Arrows.find(",");
		Substring = Arrows.substr(0, EndLoc);
		//Now that we have an individual string, lets break it down to its components.
		ArrowPlacement.push_back(NewArrow);
		ArrowPlacement[ArrowPlacement.size()-1].Level = atoi(Substring.substr(0, 1).c_str());
		ArrowPlacement[ArrowPlacement.size()-1].Slot = atoi(Substring.substr(2, 1).c_str());
		if (Substring.substr(4,1) == "U")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_UP;
		if (Substring.substr(4,1) == "L")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_LEFT;
		if (Substring.substr(4,1) == "R")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_RIGHT;
		ArrowPlacement[ArrowPlacement.size()-1].Length = atoi(Substring.substr(6,1).c_str());
		Arrows.erase(0, EndLoc +1);
		}
	if (Arrows != "")
		{
		Substring = Arrows;
		StripStringLeadingWhiteSpace(Substring);
		ArrowPlacement.push_back(NewArrow);
		ArrowPlacement[ArrowPlacement.size()-1].Level = atoi(Substring.substr(0, 1).c_str());
		ArrowPlacement[ArrowPlacement.size()-1].Slot = atoi(Substring.substr(2, 1).c_str());
		if (Substring.substr(4,1) == "U")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_UP;
		if (Substring.substr(4,1) == "L")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_LEFT;
		if (Substring.substr(4,1) == "R")
			ArrowPlacement[ArrowPlacement.size()-1].Direction = AD_RIGHT;
		ArrowPlacement[ArrowPlacement.size()-1].Length = atoi(Substring.substr(6,1).c_str());
		}
	InitHash();
	}

//---------------------------------------------------------------------------
void Data_Enhancement_Tree_Class::AddNewEnhancement(string EnhancementDataString)
	{
	Data_Enhancement_Class DummyEnhancement;

	EnhancementData.push_back(DummyEnhancement);
	EnhancementData[EnhancementData.size()-1].InitializeEnhancement(EnhancementDataString, TreeIndex, EnhancementData.size()-1);
	}

//---------------------------------------------------------------------------
bool Data_Enhancement_Tree_Class::DoesSlotHaveEnhancement(int Level, int Slot)
	{
	for (unsigned int x=0; x<EnhancementData.size(); x++)
		{
		if (Level == EnhancementData[x].GetEnhancementLevel())
			if (Slot == EnhancementData[x].GetEnhancementSlot())
				return true;
		}
	return false;
	}

//---------------------------------------------------------------------------
bool Data_Enhancement_Tree_Class::DoesTreeHaveEnhancements()
	{
	return HasEnhancements;
	}

//---------------------------------------------------------------------------
GraphicStruct Data_Enhancement_Tree_Class::GetBackgroundGraphic()
	{
	return TreeBackground;
	}

//---------------------------------------------------------------------------
ArrowStruct Data_Enhancement_Tree_Class::GetArrowPlacement(int Index)
	{
	return ArrowPlacement[Index];
	}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Tree_Class::GetArrowPlacementSize()
	{
	return ArrowPlacement.size();
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Tree_Class::GetEnhancementIndex(int Level, int Slot, unsigned int MSlot)
	{

	for (unsigned int x=0; x<EnhancementData.size(); x++)
		{
		if (Level == EnhancementData[x].GetEnhancementLevel())
			{
			if (Slot == EnhancementData[x].GetEnhancementSlot())
				{
				if (EnhancementData[x].GetEnhMultiSelection() == true)
					{
					if (MSlot == EnhancementData[x].GetEnhancementMSlot())
						return x;
					}
				else
					{
					if (MSlot == 0)
						return x;
					else 
						return -1;
					}
				}
			}
		}
	return -1;
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class* Data_Enhancement_Tree_Class::GetEnhancementPointer(unsigned int EnhancementIndex)
	{
	return EnhancementData[EnhancementIndex].GetEnhancementAddress();
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class* Data_Enhancement_Tree_Class::GetEnhancementPointer(unsigned int Level, unsigned int Slot)
	{
	int EnhancementIndex;

	EnhancementIndex = -1;
	for (unsigned int x=0; x<EnhancementData.size(); x++)
		{
		if (Level == EnhancementData[x].GetEnhancementLevel())
			{
			if (Slot == EnhancementData[x].GetEnhancementSlot())
				{
				EnhancementIndex = x;
				break;
				}
			}
		}

	if (EnhancementIndex == -1)
		return nullptr;

	return EnhancementData[EnhancementIndex].GetEnhancementAddress();
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class* Data_Enhancement_Tree_Class::GetEnhancementPointer (unsigned int Level, unsigned int Slot, unsigned int MSlot)
	{
	int EnhancementIndex;

	EnhancementIndex = -1;
	for (unsigned int x=0; x<EnhancementData.size(); x++)
		{
		if (Level == EnhancementData[x].GetEnhancementLevel())
			{
			if (Slot == EnhancementData[x].GetEnhancementSlot())
				{
				if (MSlot == EnhancementData[x].GetEnhancementMSlot())
					{
					EnhancementIndex = x;
					break;
					}
				}
			}
		}

	if (EnhancementIndex == -1)
		return nullptr;

	return EnhancementData[EnhancementIndex].GetEnhancementAddress();
	}

//---------------------------------------------------------------------------
Data_Enhancement_Tree_Class* Data_Enhancement_Tree_Class::GetEnhancementTreeAddress()
	{
	return this;
	}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Tree_Class::GetMultiEnhancementsSize(int EnhancementIndex)
	{
	int Slot;
	int Level;
	int Size = 0;

	Level = EnhancementData[EnhancementIndex].GetEnhancementLevel();
	Slot = EnhancementData[EnhancementIndex].GetEnhancementSlot();

	for (unsigned int x=0; x < EnhancementData.size(); x++)
		{
		if (EnhancementData[x].GetEnhancementLevel() == Level)
			if (EnhancementData[x].GetEnhancementSlot() == Slot)
				Size ++;
		}
	return Size;
	}

//---------------------------------------------------------------------------
CLASS Data_Enhancement_Tree_Class::GetTreeClass()
	{
	return TreeClass;
	}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE Data_Enhancement_Tree_Class::GetTreeIndex()
	{
	return TreeIndex;
	}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE Data_Enhancement_Tree_Class::GetTreeIndex(string Tree)
	{
	try 
		{
		return EnhancementTreeList.at(Tree);
		}
	catch (const std::out_of_range) 
		{
		return ENHT_UNKNOWN;
		}	
	}

//---------------------------------------------------------------------------
string Data_Enhancement_Tree_Class::GetTreeName()
	{
	return TreeName;
	}

//---------------------------------------------------------------------------
RACE Data_Enhancement_Tree_Class::GetTreeRace()
	{
	return TreeRace;
	}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE_TYPE Data_Enhancement_Tree_Class::GetTreeType()
	{
	return TreeType;
	}

//--------------------------------------------------------------------------
void Data_Enhancement_Tree_Class::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}

//--------------------------------------------------------------------------
void Data_Enhancement_Tree_Class::InitHash()
	{
	if(EnhancementTreeList.size() == 0)
		{
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Bladeforged", ENHT_BLADEFORGED));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Drow",ENHT_DROW));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Dwarf",ENHT_DWARF));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Elf",ENHT_ELF));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Halfling",ENHT_HALFLING));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Half Elf",ENHT_HALF_ELF));// Added a space in "Half-Elf" to allow for lockouts in enhancment trees
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Half Orc", ENHT_HALF_ORC));// Added a space in "Half-Orc" to allow for lockouts in enhancment trees
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Human",ENHT_HUMAN));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Morninglord",ENHT_MORNINGLORD));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Purple Dragon Knight",ENHT_PURPLE_DRAGON_KNIGHT));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Shadar Kai",ENHT_SHADAR_KAI));// Added a space in "Shadar-Kai"to allow for lockouts in enhancment trees
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Warforged",ENHT_WARFORGED));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Gnome", ENHT_GNOME));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Deep-Gnome", ENHT_DEEPGNOME));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Dragonborn", ENHT_DRAGONBORN));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Aasimar", ENHT_AASIMAR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Air Savant (Sor)", ENHT_AIR_SAVANT_SOR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Angel of Vengeance (Fvs)",ENHT_ANGEL_OF_VENGEANCE_FVS));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Arcane Archer (Elf)",ENHT_ARCANE_ARCHER_ELF));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Arcane Archer (Rgr)",ENHT_ARCANE_ARCHER_RNG));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Arcanotechnician (Art)",ENHT_ARCANOTECHNICIAN_ART));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Archmage (Wiz)",ENHT_ARCHMAGE_WIZ));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Assassin (Rog)", ENHT_ASSASSIN_ROG));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Battle Engineer (Art)",ENHT_BATTLE_ENGINEER_ART));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Deepwood Stalker (Rgr)",ENHT_DEEPWOOD_STALKER_RNG));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Divine Disciple (Clr)",ENHT_DIVINE_DISCIPLE_CLR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Earth Savant (Sor)",ENHT_EARTH_SAVANT_SOR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Eldritch Knight (Sor)",ENHT_ELDRITCH_KNIGHT_SOR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Eldritch Knight (Wiz)",ENHT_ELDRITCH_KNIGHT_WIZ));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Fire Savant (Sor)",ENHT_FIRE_SAVANT_SOR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Frenzied Berserker (Bar)", ENHT_FRENZIED_BERSERKER_BAR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Henshin Mystic (Mnk)",ENHT_HENSHIN_MYSTIC_MNK));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Kensei (Ftr)",ENHT_KENSEI_FTR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Knight of the Chalice (Pal)",ENHT_KNIGHT_OF_THE_CHALICE_PAL));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Mechanic (Rog)",ENHT_MECHANIC_ROG));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Nature's Warrior (Drd)",ENHT_NATURES_WARRIOR_DRD));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Ninja Spy (Mnk)", ENHT_NINJA_SPY_MNK));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Occult Slayer (Bar)",ENHT_OCCULT_SLAYER_BAR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Pale Master (Wiz)",ENHT_PALE_MASTER_WIZ));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Warpriest (Clr)",ENHT_WARPRIEST_CLR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Warpriest (Fvs)",ENHT_WARPRIEST_FVS));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Radiant Servant (Clr)",ENHT_RADIANT_SERVANT_CLR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Ravager (Bar)",ENHT_RAVAGER_BAR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Sacred Defender (Pal)", ENHT_SACRED_DEFENDER_PAL));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Season's Herald (Drd)",ENHT_SEASONS_HERALD_DRD));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Shintao (Mnk)",ENHT_SHINTAO_MNK));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Spellsinger (Brd)",ENHT_SPELLSINGER_BRD));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Stalwart Defender (Ftr)",ENHT_STALWART_DEFENDER_FTR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Tempest (Rgr)",ENHT_TEMPEST_RNG));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Thief Acrobat (Rog)",ENHT_THIEF_ACROBAT_ROG));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Warchanter (Brd)", ENHT_WARCHANTER_BRD));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Water Savant (Sor)",ENHT_WATER_SAVANT_SOR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Swashbuckler (Brd)",ENHT_SWASHBUCKLER_BRD));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Vanguard (Ftr)",ENHT_VANGUARD_FTR));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Vanguard (Pal)",ENHT_VANGUARD_PAL));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Harper Agent",ENHT_HARPER_AGENT));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Soul Eater (Wlk)", ENHT_SOULEATER_WLK));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Tainted Scholar (Wlk)", ENHT_TANTEDSCHOLAR_WLK));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Enlightened Spirit (Wlk)", ENHT_ENLIGHTENEDSPIRIT_WLK));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Vistani Knife Fighter", ENHT_VISTANIKNIFEFIGHTER));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Scourge", ENHT_SCOURGE));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Unknown",ENHT_UNKNOWN));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Unset",ENHT_UNSET));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("NoTree",ENHT_NOTREE));
		EnhancementTreeList.emplace(pair<string, ENHANCEMENT_TREE>("Future Tree",ENHT_FUTURETREE));
		}
	}