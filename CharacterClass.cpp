//--------------------------------------------------------------------------
#include "CharacterClass.h"
#include "DataClass.h"
#include "InterfaceManagerClass.h"
#include "MainScreenClass.h"
#include <time.h>

//---------------------------------------------------------------------------
CharacterClass Character;

//---------------------------------------------------------------------------
CharacterClass::CharacterClass()
    {
	ValidationsDisabledCount = 0;
    Reset();
    }

//---------------------------------------------------------------------------
CharacterClass::~CharacterClass()
    {
    }

//---------------------------------------------------------------------------
void CharacterClass::Reset()
    {
    EnableValidations(false); // Avoid too much UI refresh
	FirstName = "";
    SurName = "";
    SetRace(HUMAN);
    CharacterSex = MALE;
    //set the default class to level MaxLevel
    for (unsigned int i=0; i<MAXLEVEL; i++)
        ClassRecord[i] = CLASSNONE;
    ClassRecord[0] = FIGHTER;
    Alignment = LAWFULGOOD;
    for (unsigned int i=0; i<6; i++)
        AbilityRaise[i] = 0;
    for (unsigned int i=0; i<6; i++)
        for (unsigned int j=0; j<MAXLEVEL; j++)
            TomeRaise[i][j] = 0;
    AbilityRaise4 = ABILITYNONE;
    AbilityRaise8 = ABILITYNONE;
    AbilityRaise12 = ABILITYNONE;
    AbilityRaise16 = ABILITYNONE;
    AbilityRaise20 = ABILITYNONE;
    AbilityRaise24 = ABILITYNONE;
    AbilityRaise28 = ABILITYNONE;
    FavorAbilityBonusPoints = false;
	for (unsigned int i=0; i<NUMSKILLS; i++)
        for (unsigned int j=0; j<HEROICLEVELS; j++)
            SkillRaise[i][j] = 0;
    FeatList.clear();
    for (unsigned int i=0; i<NUMCLASSES; i++)
	    ReincarnationCount[i] = 0;
	for (unsigned int y = 0; y < EPICPASTLIFESPHERE; y++)
	{
		for (unsigned int x = 0; x < 3; x++)
			EpicPastLifeCount[y][x] = 0;
	}
	for (unsigned int i = 0; i < ICONICPASTLIFEFEAT; i++)
		IconicPastLifeCount[i] = 0;
	for (unsigned int i = 0; i < RACEPASTLIFE; i++)
		RacePastLifeCount[i] = 0;
	CharacterEnhancements.Clear();
	CharacterDestinies.ClearAll();
    SpellList.clear();
	ClearCharacterItems();
    AddRaceAutoFeats(1);
    AddClassAutoFeats(FIGHTER, 1, 1);
	RaceEnhancement = 0;
	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		CharacterItemsEquipped[i] = -1;
    EnableValidations(true);
	*FiletoOpen = NULL;
    }
//---------------------------------------------------------------------------
void CharacterClass::CharacterTR()
{
	EnableValidations(false); // Avoid too much UI refresh
	SetRace(HUMAN);
	CharacterSex = MALE;
	//set the default class to level MaxLevel
	for (unsigned int i = 0; i<MAXLEVEL; i++)
		ClassRecord[i] = FIGHTER;
	Alignment = LAWFULGOOD;
	for (unsigned int i = 0; i<6; i++)
		AbilityRaise[i] = 0;
	int MaxTome[6];
	for (int x = 0; x < 6; x++)
		MaxTome[x] = 0;
	// Get Max Tome
	for (int i = 0; i < 6; i++)
	{
		for (unsigned int j = 0; j<MAXLEVEL; j++)
		{
				MaxTome[i] += TomeRaise[i][j];
				TomeRaise[i][j] = 0;
		}

	}

	for (unsigned int i = 0; i < 6; i++)
			TomeRaise[i][0] = MaxTome[i];



	AbilityRaise4 = ABILITYNONE;
	AbilityRaise8 = ABILITYNONE;
	AbilityRaise12 = ABILITYNONE;
	AbilityRaise16 = ABILITYNONE;
	AbilityRaise20 = ABILITYNONE;
	AbilityRaise24 = ABILITYNONE;
	AbilityRaise28 = ABILITYNONE;
	FavorAbilityBonusPoints = false;
	for (unsigned int i = 0; i<NUMSKILLS; i++)
		for (unsigned int j = 0; j<HEROICLEVELS; j++)
			SkillRaise[i][j] = 0;
	FeatList.clear();


	
	CharacterEnhancements.Clear();
	CharacterDestinies.ClearAll();
	SpellList.clear();
	ClearCharacterItems();
	int tempcount = 0;
	for (unsigned int i = 0; i < NUMCLASSES; i++)
	{
		tempcount = ReincarnationCount[i];
		ReincarnationCount[i] = 0;
		for (int x = 0; x < tempcount; x++)
			IncreasePastLife(CLASS(i));
	}

	for (unsigned int y = 0; y < EPICPASTLIFESPHERE; y++)
	{
		for (unsigned int x = 0; x < 3; x++)
		{


			tempcount = EpicPastLifeCount[y][x];
			EpicPastLifeCount[y][x] = 0;
			for (int x = 0; x < tempcount; x++)
				IncreaseEpicFeat(DESTINY_SPHERE(y), x);
		}

	}
	for (unsigned int i = 0; i < ICONICPASTLIFEFEAT; i++)
	{

		tempcount = IconicPastLifeCount[i];
		IconicPastLifeCount[i] = 0;
		for (int x = 0; x < tempcount; x++)
			IncreaseIconicPastLife(ICONICRACES(i));
	}

	for (unsigned int i = 0; i < RACEPASTLIFE; i++)
	{

		tempcount = RacePastLifeCount[i];
		RacePastLifeCount[i] = 0;
		for (int x = 0; x < tempcount; x++)
			IncreaseRacePastLife(PAST_RACE(i));
	}
	AddRaceAutoFeats(1);
	AddClassAutoFeats(FIGHTER, 1, 1);
	RaceEnhancement = 0;
	for (unsigned int i = 0; i<NUMCHAREQUPMENTSLOTS; i++)
		CharacterItemsEquipped[i] = -1;
	EnableValidations(true);
	*FiletoOpen = NULL;
}
//---------------------------------------------------------------------------
void CharacterClass::GetName(string *First, string *Sur)
    {
    *First = FirstName;
    *Sur = SurName;
    }

//---------------------------------------------------------------------------
void CharacterClass::SetName(string First, string Sur)
    {
    FirstName = First;
    SurName = Sur;
    }

//---------------------------------------------------------------------------
RACE CharacterClass::GetRace()
    {
    return Race;
    }

//---------------------------------------------------------------------------
void CharacterClass::SetRace(RACE NewRace)
    {
    RemoveRaceAutoFeats();
    Race = NewRace;
	AddRaceAutoFeats();

	//now, becuase we may have removed some class feats that are also race
	//auto feats, we need to reset the class feats as well (only needed for
	//level 1, since that's the only level where you can change race).
	AddClassAutoFeats(ClassRecord[0], 1, 1);

	ValidateCharacterEnhancements("Race", 1);

    ValidateCharacter();
    }

//---------------------------------------------------------------------------
string CharacterClass::GetRaceString(bool GetPlural)
	{
	if (GetPlural == false)
		{
		switch (Race)
			{
			case HUMAN:
				return "Human";
			case ELF:
				return "Elf";
			case HALFLING:
				return "Halfling";
			case DWARF:
				return "Dwarf";
			case WARFORGED:
				return "Warforged";
			case DROW:
				return "Drow";
			case HALFELF:
				return "Half-Elf";
			case HALFORC:
				return "Half-Orc";
			case BLADEFORGED:
				return "Bladeforged";
			case MORNINGLORD:
				return "Morninglord";
			case PURPLEDRAGONKNIGHT:
				return "Purple Dragon Knight";
			case SHADARKAI:
				return "Shadar-Kai";
			case GNOME:
				return "Gnome";
			case DEEPGNOME:
				return "Deep-Gnome";
			case DRAGONBORN:
				return "Dragonborn";
			}
		}
	else
		{
		switch (Race)
			{
			case HUMAN:
				return "Humans";
			case ELF:
				return "Elves";
			case HALFLING:
				return "Halflings";
			case DWARF:
				return "Dwarves";
			case WARFORGED:
				return "Warforged";
			case DROW:
				return "Drow";
			case HALFELF:
				return "Half-Elves";
			case HALFORC:
				return "Half-Orcs";
			case BLADEFORGED:
				return "Bladeforged";
			case MORNINGLORD:
				return "Morninglord";
			case PURPLEDRAGONKNIGHT:
				return "Purple Dragon Knights";
			case SHADARKAI:
				return "Shadar-Kai";
			case GNOME:
				return "Gnome";
			case DEEPGNOME:
				return "Deep-Gnome";
			case DRAGONBORN:
				return "Dragonborn";
			}
		}
	return "";
	}

//---------------------------------------------------------------------------
SEX CharacterClass::GetSex()
    {
    return CharacterSex;
    }

//---------------------------------------------------------------------------
void CharacterClass::SetClass(CLASS NewClass, int AtLevel)
    {
    int ClassLevel;

    if (ClassRecord[AtLevel-1] != CLASSNONE)
        {
        ClassLevel = GetClassLevel(ClassRecord[AtLevel-1], AtLevel);
        RemoveClassAutoFeats(ClassRecord[AtLevel-1], AtLevel, ClassLevel);
        }
    ClassRecord[AtLevel-1] = NewClass;
    ClassLevel = GetClassLevel(NewClass, AtLevel);
    AddClassAutoFeats(ClassRecord[AtLevel-1], AtLevel, ClassLevel);
	RemoveAutoSpells();
	AddAutoSpells(AtLevel);

	ResetAutoFeats(AtLevel);
	ValidateCharacterEnhancements("Class", AtLevel);
    ValidateCharacter();
    }

//---------------------------------------------------------------------------
CLASS CharacterClass::GetClass(int AtLevel, bool Change)
    {
    CLASS LastClass;

	//if Change == false, we just want to return the class type, we are not setting anything
	if (!Change)
		return ClassRecord[AtLevel-1];

    //now, if the current level is set to class NONE, reset it (and any previous
    //levels that are NONE) to the last class the user chose
    if (ClassRecord[AtLevel-1] == CLASSNONE)
        {
        for (int i=1; i<AtLevel; i++)
            {
            if (ClassRecord[i-1] != CLASSNONE)
                LastClass = ClassRecord[i-1];
            }
        for (int i=1; i<=AtLevel; i++)
            {
            if (ClassRecord[i-1] == CLASSNONE)
                SetClass(LastClass, i);
            }
        }

    return ClassRecord[AtLevel-1];
    }

//---------------------------------------------------------------------------
void CharacterClass::GetMulticlassClasses(int AtLevel, CLASS *Class)
    {
	bool Classes[NUMCLASSES+1];       //add one extra for CLASS_NONE
    int Index;

    for (unsigned int i=0; i<3; i++)
        Class[i] = CLASSNONE;
	for (unsigned int i=0; i<NUMCLASSES; i++)
        Classes[i] = false;

    for (int i=0; i<AtLevel; i++)
        Classes[ClassRecord[i]] = true;

    Index = 0;

	for (int i = 0; i < AtLevel; i++)
	{
		if (Classes[ClassRecord[i]] == true)
		{
			Class[Index] = ClassRecord[i];
			Classes[ClassRecord[i]] = false;
			Index++;
			if (Index == 3)
				return;
		}
	}


    }

//---------------------------------------------------------------------------
ALIGNMENT CharacterClass::GetAlignment()
    {
    return Alignment;
    }

//---------------------------------------------------------------------------
void CharacterClass::SetAlignment(ALIGNMENT NewAlignment)
    {
    Alignment = NewAlignment;
    ValidateCharacter();
    }

//---------------------------------------------------------------------------
bool CharacterClass::IsAlignmentLegal(ALIGNMENT Test)
    {
    //only base this on the FIRST level class
    return Data.IsAlignmentCompatable(ClassRecord[0], Test);
    }

//---------------------------------------------------------------------------
int CharacterClass::GetHighestBuildLevel()
	{
	for (unsigned int i=0; i<MAXLEVEL; i++)
		if (ClassRecord[i] == CLASSNONE)
			return i;
	return MAXLEVEL;
	}

//---------------------------------------------------------------------------
int CharacterClass::GetClassLevel(int CurrentSelectedLevel)
    {
    CLASS LastClass;
    int Level;

    //return the class level of the character at the character level selected
    LastClass = GetClass(CurrentSelectedLevel);
    CurrentSelectedLevel--;     //change to 0 based
    Level = 0;
    for (int i=0; i<=CurrentSelectedLevel; i++)
        {
        if (ClassRecord[i] == LastClass)
            Level++;
        }
    return Level;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetClassLevel(CLASS ClassType, int CurrentSelectedLevel)
    {
    int Level;

    //return the class level of the character for the requested class
	//skipping the epic levels
    CurrentSelectedLevel--;     //change to 0 based
	if (CurrentSelectedLevel > 19)
		CurrentSelectedLevel = 19;
    Level = 0;
    for (int i=0; i<=CurrentSelectedLevel; i++)
        {
        if (ClassRecord[i] == ClassType)
            Level++;
        }
    return Level;
    }

//---------------------------------------------------------------------------
string CharacterClass::GetClassString(int AtLevel)
	{
	CLASS Classes[3];
	CLASS ClassHold;
	int ClassLevel[3];
	int LevelHold;
	int HeroicLevels;
	ostringstream Result;

	//only look at heroic levels for now
	HeroicLevels = AtLevel;
	if (HeroicLevels > HEROICLEVELS) 
		HeroicLevels = HEROICLEVELS;

	GetMulticlassClasses(HeroicLevels, Classes);
	for (unsigned int i=0; i<3; i++)
		{
		if (Classes[i] == CLASSNONE)
			ClassLevel[i] = 0;
		else
			ClassLevel[i] = GetClassLevel(Classes[i], HeroicLevels);
		}

	//levels and classes need to be sorted by level
	if (ClassLevel[2] > ClassLevel[1])
		{
		LevelHold = ClassLevel[1];
		ClassHold = Classes[1];
		ClassLevel[1] = ClassLevel[2];
		ClassLevel[2] = LevelHold;
		Classes[1] = Classes[2];
		Classes[2] = ClassHold;
		}
	if (ClassLevel[1] > ClassLevel[0])
		{
		LevelHold = ClassLevel[0];
		ClassHold = Classes[0];
		ClassLevel[0] = ClassLevel[1];
		ClassLevel[1] = LevelHold;
		Classes[0] = Classes[1];
		Classes[1] = ClassHold;
		}
	if (ClassLevel[2] > ClassLevel[1])
		{
		LevelHold = ClassLevel[1];
		ClassHold = Classes[1];
		ClassLevel[1] = ClassLevel[2];
		ClassLevel[2] = LevelHold;
		Classes[1] = Classes[2];
		Classes[2] = ClassHold;
		}

	//now we can put together the string
	Result.str("");
	Result << ClassLevel[0] << " " << Data.GetClassName(Classes[0]);
	if (Classes[1] != CLASSNONE)
		Result << " \\ " << ClassLevel[1] << " " << Data.GetClassName(Classes[1]);
	if (Classes[2] != CLASSNONE)
		Result << " \\ " << ClassLevel[2] << " " << Data.GetClassName(Classes[2]);

	//tack on the epic levels, if any
	if (AtLevel > HEROICLEVELS)
		Result << " \\ " << AtLevel-HEROICLEVELS << " Epic";

	return Result.str().c_str();
	}
	
//---------------------------------------------------------------------------
int CharacterClass::GetCharacterLevelAtClassLevel(CLASS ClassType, int ClassLevel)
    {
    int CharacterLevel;
    
    for (unsigned int i=0; i<MAXLEVEL; i++)
        {
        CharacterLevel = GetClassLevel(ClassType, i+1);
        if (CharacterLevel == ClassLevel)
            return i+1;
        }
    return 0;
    }

//---------------------------------------------------------------------------
void CharacterClass::SetSex(SEX NewSex)
    {
    CharacterSex = NewSex;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetHitPoints(int AtLevel)
    {
    int HitPoints;
    int TotalConAbility;
    int Modifier;
	int HeroicLevels;
	int EpicLevels;
	int ClassLevel;

	if (AtLevel < 21)
		{
		HeroicLevels = AtLevel;
		EpicLevels = 0;
		}
	else
		{
		HeroicLevels = HEROICLEVELS;
		EpicLevels = AtLevel - HEROICLEVELS;
		}

    HitPoints = 0;
    for (int i=0; i<HeroicLevels; i++)
        {
        if (ClassRecord[i] == CLASSNONE)
            continue;
        HitPoints += Data.GetHitDice(ClassRecord[i]);
        }
	HitPoints += EpicLevels*10;
    TotalConAbility = GetAbility((int)CONSTITUTION, AtLevel, false) + GetTomeRaise(CONSTITUTION, AtLevel, true)+CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY,"Constitution",AtLevel);
    Modifier = Data.CalculateAbilityModifier(TotalConAbility);
    HitPoints += Modifier * AtLevel;

    if (HasFeat("Heroic Durability", AtLevel) == true)
        HitPoints += 25;
	if (HasFeat("Past Life: Berserker's Fury", AtLevel) == true)
		HitPoints += 20;
	if (HasFeat("Epic: Epic Toughness", AtLevel) == true)
		HitPoints += 50;
	if (HasFeat("Scion of Celestia", AtLevel) == true)
		HitPoints += 150;
    HitPoints += CountFeat("Toughness", AtLevel) * (2 + AtLevel);
    HitPoints += 10 * CountFeat("Past Life: Barbarian", AtLevel);
	//Improved Heroic Durability (get 5 points per every 5 levels of each class)
    for (int i=0; i<NUMCLASSES; i++)
        {
		ClassLevel = GetClassLevel(static_cast<CLASS>(i), AtLevel);
		if (ClassLevel >= 5)
			HitPoints += 5;
		if (ClassLevel >= 10)
			HitPoints += 5;
		if (ClassLevel >= 15)
			HitPoints += 5;
        }
	HitPoints += CharacterEnhancements.GetTotalEnhancementMod(MC_ATTRIBUTE, "Hit Points", AtLevel);

    return HitPoints;
    }

//---------------------------------------------------------------------------
int CharacterClass::CalculateTotalAbilityMod(ABILITIES Ability, unsigned int CurrentSelectedLevel, bool IncludeEquipment)
	{
	int TotalAbility;
	int Modifier;

	TotalAbility = GetAbility((int)Ability, CurrentSelectedLevel, true, true, IncludeEquipment);
	Modifier = Data.CalculateAbilityModifier(TotalAbility);

	return Modifier;
	}

//---------------------------------------------------------------------------
void CharacterClass::GetKiPoints(int AtLevel, int *MaxKi, int *StableKi)
	{
	int MonkLevels;

	//get monk level
	MonkLevels = GetClassLevel(MONK, AtLevel);
	if (MonkLevels == 0)
		{
		*MaxKi = 0;
		*StableKi = 0;
		return;
		}

	*MaxKi = 10*MonkLevels + 40 + 5*Data.CalculateAbilityModifier(GetAbility(WISDOM, AtLevel, true, true, true));
	*StableKi = static_cast<int>(CalculateSkillLevel(CONCENTRATION, AtLevel, true));
	if (*StableKi < 0)
		*StableKi = 0;
	}

//---------------------------------------------------------------------------
void CharacterClass::ClearSpells()
	{
	SpellList.clear();
	}

//---------------------------------------------------------------------------
int CharacterClass::GetSpellPoints(int AtLevel)
    {
    int SpellPoints;
	int ClassLevels[NUMCLASSES+1];		//one extra for CLASSNONE
    int Ability;
    int AbilityMod;

    SpellPoints = 0;
	for (int i=0; i<NUMCLASSES; i++)
        ClassLevels[i] = 0;
    for (int i=0; i<AtLevel; i++)
        ClassLevels[ClassRecord[i]]++;
    for (int i=0; i<NUMCLASSES; i++)
        {
        SpellPoints += Data.GetSpellPoints((CLASS)i, ClassLevels[i]);
        if ((CLASS)i == PALADIN)
            {
            if (ClassLevels[i] >= 4)
                {
                Ability = GetAbility((int)WISDOM, AtLevel, true) + GetTomeRaise(WISDOM, AtLevel, true);
                AbilityMod = Data.CalculateAbilityModifier(Ability);
                SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
                }
            else if (ClassLevels[i] >= 1)
                {
                //level 1-3 pallys are a special case, they only get
                //spell points if they have a spellcasting class already
                if (GetClassLevel(RANGER, AtLevel) >= 4 || GetClassLevel(CLERIC, AtLevel) >= 1 ||
                        GetClassLevel(WIZARD, AtLevel) >= 1 || GetClassLevel(SORCERER, AtLevel) >= 1 ||
                        GetClassLevel(BARD, AtLevel) >= 1 || GetClassLevel(ARTIFICER, AtLevel) >=1 ||
						GetClassLevel(DRUID, AtLevel) >=1)
                    {
                    Ability = GetAbility((int)WISDOM, AtLevel, false) + GetTomeRaise(WISDOM, AtLevel, true);
                    AbilityMod = Data.CalculateAbilityModifier(Ability);
                    SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
                    }
                }
            }
        if ((CLASS)i == RANGER)
            {
            if (ClassLevels[i] >= 4)
                {
                Ability = GetAbility((int)WISDOM, AtLevel, false) + GetTomeRaise(WISDOM, AtLevel, true);
                AbilityMod = Data.CalculateAbilityModifier(Ability);
                SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
                }
            else if (ClassLevels[i] >= 1)
                {
                //level 1-3 rangers are a special case, they only get
                //spell points if they have a spellcasting class already
                if (GetClassLevel(PALADIN, AtLevel) >= 4 || GetClassLevel(CLERIC, AtLevel) >= 1 ||
                        GetClassLevel(WIZARD, AtLevel) >= 1 || GetClassLevel(SORCERER, AtLevel) >= 1 ||
                        GetClassLevel(BARD, AtLevel) >= 1 || GetClassLevel(ARTIFICER, AtLevel) >=1 ||
						GetClassLevel(DRUID, AtLevel >=1) || GetClassLevel(WARLOCK, AtLevel >= 1))
                    {
                    Ability = GetAbility((int)WISDOM, AtLevel, false) + GetTomeRaise(WISDOM, AtLevel, true);
                    AbilityMod = Data.CalculateAbilityModifier(Ability);
                    SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
                    }
                }
            }                                             
        if ((CLASS)i == CLERIC && ClassLevels[i] >= 1)
            {
            Ability = GetAbility((int)WISDOM, AtLevel, false) + GetTomeRaise(WISDOM, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
            }
        if ((CLASS)i == WIZARD && ClassLevels[i] >= 1)
            {
            Ability = GetAbility((int)INTELLIGENCE, AtLevel, false) + GetTomeRaise(INTELLIGENCE, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
            }
        if ((CLASS)i == ARTIFICER && ClassLevels[i] >= 1)
            {
            Ability = GetAbility((int)INTELLIGENCE, AtLevel, false) + GetTomeRaise(INTELLIGENCE, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
            }
        if ((CLASS)i == SORCERER && ClassLevels[i] >= 1)
            {
            Ability = GetAbility((int)CHARISMA, AtLevel, false) + GetTomeRaise(CHARISMA, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
            }
        if ((CLASS)i == BARD && ClassLevels[i] >= 1)
            {
            Ability = GetAbility((int)CHARISMA, AtLevel, false) + GetTomeRaise(CHARISMA, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
            }
        if ((CLASS)i == FAVORED_SOUL && ClassLevels[i] >= 1)
            {
            Ability = GetAbility((int)CHARISMA, AtLevel, false) + GetTomeRaise(CHARISMA, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
            }
		if ((CLASS)i == DRUID && ClassLevels[i] >= 1)
			{
            Ability = GetAbility((int)WISDOM, AtLevel, false) + GetTomeRaise(WISDOM, AtLevel, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod:0);
			}
		if ((CLASS)i == WARLOCK && ClassLevels[i] >= 1)
			{
			Ability = GetAbility((int)CHARISMA, AtLevel, false) + GetTomeRaise(CHARISMA, AtLevel, true);
			AbilityMod = Data.CalculateAbilityModifier(Ability);
			SpellPoints += (9 + ClassLevels[i]) * ((AbilityMod > 0) ? AbilityMod : 0);
			}
        }

    if (HasFeat("Magical Training", AtLevel) == true)
        SpellPoints += 80;
    if (HasFeat("Mental Toughness", AtLevel) == true)
        SpellPoints += 5 + 5*AtLevel;
    if (HasFeat("Improved Mental Toughness", AtLevel) == true)
        SpellPoints += 5 + 5*AtLevel;
	if (HasFeat("Past Life: Arcane Prodigy", AtLevel) == true)
		SpellPoints += 5 + 5*AtLevel;
    if (HasFeat("Epic: Epic Mental Toughness", AtLevel) == true)
        SpellPoints += 200;
	if (HasFeat("Scion of the Plane of Water", AtLevel) == true)
		SpellPoints += 200;
	if (HasFeat("Epic: Arcane Insight", AtLevel) == true)
		SpellPoints += 110;
	if (HasFeat("Epic: Embolden Spell", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Improved Augment Summoning", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Burst of Glacial Wrath", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Intensify Spell", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Wellspring of Power", AtLevel) == true)
		SpellPoints += 110;
	if (HasFeat("Epic: Master of Air", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Alignment", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Artifice", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Earth", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Fire", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Knowledge", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Light", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Music", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of Water", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of the Dead", AtLevel) == true)
		SpellPoints += 140;
	if (HasFeat("Epic: Master of the Wilds", AtLevel) == true)
		SpellPoints += 140;
	SpellPoints += CountFeat("Past Life: Sorcerer", AtLevel) * 20;
	SpellPoints += CountFeat("Past Life: Favored Soul", AtLevel) * 20;
	SpellPoints += CharacterEnhancements.GetTotalEnhancementMod(MC_ATTRIBUTE, "Spell Points", AtLevel);

    if (SpellPoints < 0)
        SpellPoints = 0;
        
    return SpellPoints;
    }

//---------------------------------------------------------------------------
unsigned int CharacterClass::GetTotalNumSpells()
	{
	return SpellList.size();
	}

//---------------------------------------------------------------------------
int CharacterClass::GetKnownSpell(unsigned int Index)
	{
	if (Index >= SpellList.size())
		return -1;

	return SpellList[Index].SpellIndex;
	}

//---------------------------------------------------------------------------
int CharacterClass::GetNumClassLevels(CLASS Class)
    {
    int Count;

    Count = 0;
	for (unsigned int i=0; i<MAXLEVEL; i++)
        {
        if (ClassRecord[i] == Class)
            Count++;
        }
    return Count;
    }

//---------------------------------------------------------------------------
int CharacterClass::CalculateTotalAbilityPoints()
	{
	int Result;
	int PastLifeCount;
	
	Result = 28;
	//32 point builds
	if (FavorAbilityBonusPoints == true && Race != DROW)
		Result = 32;
		
	//past life feats
	PastLifeCount = GetReincarnateCount();
	if (PastLifeCount == 1)
		{
		if (Race == DROW)
			Result = 30;
		else 
			Result = 34;
		}
	else if (PastLifeCount >= 2)
		{
		if (Race == DROW)
			Result = 32;
		else 
			Result = 36;
		}
	
	return Result;
	}
	
//---------------------------------------------------------------------------
int CharacterClass::GetAbility(int AbilityIndex, int AtLevel, bool IncludeTome, bool IncludeEnhancements, bool IncludeEquipment, bool IncludeFeats)
    {
    int Ability;

	Ability = GetAbilityMod(static_cast<ABILITIES>(AbilityIndex), ABMOD_BASE, AtLevel);
	
	Ability += GetAbilityMod(static_cast<ABILITIES>(AbilityIndex), ABMOD_LEVELUP, AtLevel);
	if (IncludeTome == true)
		Ability += GetAbilityMod(static_cast<ABILITIES>(AbilityIndex), ABMOD_INHERENT, AtLevel);
	if (IncludeFeats == true)
		Ability += GetAbilityMod(static_cast<ABILITIES>(AbilityIndex), ABMOD_FEATS, AtLevel);
	if (IncludeEnhancements == true)
		Ability += GetAbilityMod(static_cast<ABILITIES>(AbilityIndex), ABMOD_ENHANCEMENT, AtLevel);
	if (IncludeEquipment == true)
		Ability += GetAbilityMod(static_cast<ABILITIES>(AbilityIndex), ABMOD_ENCHANTED, AtLevel);

    return Ability;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetAbilityMod(ABILITIES Ability, ABILITYMODS ModType, int AtLevel)
	{
    int Stats[6];
	int Result;

	switch (ModType)
		{
		case ABMOD_BASE:
			{
		    Data.GetRaceBaseStats(Race, Stats);
			return Stats[Ability] + AbilityRaise[Ability];
			}
		case ABMOD_LEVELUP:
			{
			Result = 0;
		    //up 1 for ability point increases at every fourth level
		    if (AtLevel >=4)
			    {
				if ((int)AbilityRaise4 == Ability)
		            Result++;
			    }
					
		    if (AtLevel >= 8)
			    {
				if ((int)AbilityRaise8 == Ability)
				    Result++;
			    }
				
		    if (AtLevel >= 12)
			    {
				if ((int)AbilityRaise12 == Ability)
		            Result++;
			    }
					
		    if (AtLevel >= 16)
			    {
				if ((int)AbilityRaise16 == Ability)
				    Result++;
			    }
					
			if (AtLevel >= 20)
				{
				if ((int)AbilityRaise20 == Ability)
		            Result++;
			    }
					
		    if (AtLevel >= 24)
			    {
				if ((int)AbilityRaise24 == Ability)
				    Result++;
			    }
			if (AtLevel >= 28)
				{
				if ((int)AbilityRaise28 == Ability)
					Result++;
				}
			return Result;
			}
		case ABMOD_INHERENT:
			{
			return GetTomeRaise(Ability, AtLevel, true);
			}
		case ABMOD_FEATS:
			{
			Result = 0;
			//the completionist feat
			if (HasFeat("Completionist", AtLevel) == true)
				Result += 2;

			switch (Ability)
				{
				case STRENGTH:
				{
					if (CountFeat("Race Past Life: Half Orc Past Life", AtLevel) > 1)
					{
						Result++;
					}
					Result += CountFeat("Epic: Great Strength", AtLevel);
					break;
				}
					
				case DEXTERITY:
				{
					if (CountFeat("Race Past Life: Elf Past Life", AtLevel) > 1)
					{
						Result++;
					}
					if (CountFeat("Race Past Life: Halfling Past Life", AtLevel) > 1)
					{
						Result++;
					}
					Result += CountFeat("Epic: Great Dexterity", AtLevel);
					break;
				}

				case CONSTITUTION:
				{
					if (CountFeat("Race Past Life: Warforged Past Life", AtLevel) > 1)
					{
						Result++;
					}
					if (CountFeat("Race Past Life: Dwarf Past Life", AtLevel) > 1)
					{
						Result++;
					}
					Result += CountFeat("Epic: Great Constitution", AtLevel);
					break;
				}

				case INTELLIGENCE:
				{
					if (CountFeat("Race Past Life: Drow Past Life", AtLevel) > 1)
					{
						Result++;
					}
					if (CountFeat("Race Past Life: Gnome Past Life", AtLevel) > 1)
					{
						Result++;
					}
					Result += CountFeat("Epic: Great Intelligence", AtLevel);
					break;
				}

				case WISDOM:
				{
					if (CountFeat("Race Past Life: Human Past Life", AtLevel) > 1)
					{
						Result++;
					}
					Result += CountFeat("Epic: Great Wisdom", AtLevel);
					break;
				}

				case CHARISMA:
				{
					if (CountFeat("Race Past Life: Half Elf Past Life", AtLevel) > 1)
					{
						Result++;
					}
					if (CountFeat("Race Past Life: Dragonborn Past Life", AtLevel) > 1)
					{
						Result++;
					}
					Result += CountFeat("Epic: Great Charisma", AtLevel);
					break;
				}

				}
			return Result;
			}
		case ABMOD_ENHANCEMENT:
			{
			Result = 0;
			switch (Ability)
				{
				case STRENGTH:
					Result += CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY, "Strength", AtLevel);
					break;
				case DEXTERITY:
					Result += CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY, "Dexterity", AtLevel);
					break;
				case CONSTITUTION:
					Result += CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY, "Constitution", AtLevel);
					break;
				case INTELLIGENCE:
					Result += CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY, "Intelligence", AtLevel);
					break;
				case WISDOM:
					Result += CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY, "Wisdom", AtLevel);
					break;
				case CHARISMA:
					Result += CharacterEnhancements.GetTotalEnhancementMod(MC_ABILITY, "Charisma", AtLevel);
					break;
				}
			return  Result;
			}
		case ABMOD_ENCHANTED:
			{
			return GetItemAbilityChange(Ability);
			}
		case ABMOD_TOTAL:
			{
			Result = GetAbilityMod(Ability, ABMOD_BASE, AtLevel);
			Result += GetAbilityMod(Ability, ABMOD_LEVELUP, AtLevel);
			Result += GetAbilityMod(Ability, ABMOD_INHERENT, AtLevel);
			Result += GetAbilityMod(Ability, ABMOD_FEATS, AtLevel);
			Result += GetAbilityMod(Ability, ABMOD_ENHANCEMENT, AtLevel);
			Result += GetAbilityMod(Ability, ABMOD_ENCHANTED, AtLevel);
			return Result;
			}
		}

	return 0;
	}

//---------------------------------------------------------------------------
int CharacterClass::GetAbilityCost(int AbilityIndex)
    {
    if (AbilityRaise[AbilityIndex] <= 5)
        return 1;
    if (AbilityRaise[AbilityIndex] <= 7)
        return 2;
    if (AbilityRaise[AbilityIndex] < 10)
        return 3;
    return -1;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetAbilityPointsSpent(int AbilityIndex)
    {
    if (AbilityRaise[AbilityIndex] == 0)
        return 0;
    if (AbilityRaise[AbilityIndex] == 1)
        return 1;
    if (AbilityRaise[AbilityIndex] == 2)
        return 2;
    if (AbilityRaise[AbilityIndex] == 3)
        return 3;
    if (AbilityRaise[AbilityIndex] == 4)
        return 4;
    if (AbilityRaise[AbilityIndex] == 5)
        return 5;
    if (AbilityRaise[AbilityIndex] == 6)
        return 6;
    if (AbilityRaise[AbilityIndex] == 7)
        return 8;
    if (AbilityRaise[AbilityIndex] == 8)
        return 10;
    if (AbilityRaise[AbilityIndex] == 9)
        return 13;
    if (AbilityRaise[AbilityIndex] == 10)
        return 16;

    return 0;
    }

int CharacterClass::GetAbilityRaise(int AbilityIndex)
{
	return AbilityRaise[AbilityIndex];
}

//---------------------------------------------------------------------------
void CharacterClass::AdjustAbilityRaise(int AbilityIndex, int Direction)
    {
    int Cost;
    int Spent;
    int MaxPoints;

    MaxPoints = CalculateTotalAbilityPoints();

    if (Direction == -1)
        {
        if (AbilityRaise[AbilityIndex] == 0)
            return;
        AbilityRaise[AbilityIndex]--;
        ValidateCharacter();
        return;
        }
    else
        {
        if (AbilityRaise[AbilityIndex] == 10)
            return;
        Cost = GetAbilityCost(AbilityIndex);
        //calculate remaining ability points
        Spent = 0;
        for (unsigned int i=0; i<6; i++)
            Spent += GetAbilityPointsSpent(i);
        if (Cost > MaxPoints - Spent)
            return;
        AbilityRaise[AbilityIndex]++;
        ValidateCharacter();
        }
    }

//---------------------------------------------------------------------------
void CharacterClass::SetAbilityIncrease(int AtLevel, ABILITIES Ability)
    {
    if (AtLevel == 4)
        AbilityRaise4 = Ability;
    if (AtLevel == 8)
        AbilityRaise8 = Ability;
    if (AtLevel == 12)
        AbilityRaise12 = Ability;
    if (AtLevel == 16)
        AbilityRaise16 = Ability;
    if (AtLevel == 20)
        AbilityRaise20 = Ability;
    if (AtLevel == 24)
        AbilityRaise24 = Ability;
	if (AtLevel == 28)
		AbilityRaise28 = Ability;
    }

//---------------------------------------------------------------------------
ABILITIES CharacterClass::GetAbilityIncrease(int AtLevel)
    {
    if (AtLevel == 4)
        return AbilityRaise4;
    if (AtLevel == 8)
        return AbilityRaise8;
    if (AtLevel == 12)
        return AbilityRaise12;
    if (AtLevel == 16)
        return AbilityRaise16;
    if (AtLevel == 20)
        return AbilityRaise20;
    if (AtLevel == 24)
        return AbilityRaise24;
	if (AtLevel == 28)
		return AbilityRaise28;

    return ABILITYNONE;
    }

//---------------------------------------------------------------------------
void CharacterClass::SetAbilityFavorBonus(bool NewSetting)
    {
    FavorAbilityBonusPoints = NewSetting;
    }

//---------------------------------------------------------------------------
bool CharacterClass::GetAbilityFavorBonus()
    {
    return FavorAbilityBonusPoints;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetTomeRaise(ABILITIES Ability, int AtLevel, bool IncludeThisLevel , bool IncludeAllTomes)
    {
    int Raise;
	int Tomes[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int TomesLvl[7] = { 3, 7, 11, 15, 19, 23, 27 };
	int returnvalue;
	int test = 0;
	returnvalue = 0;
    Raise = 0;
    for (int i=0; i<AtLevel; i++)
        Raise += TomeRaise[Ability][i];

    if (IncludeThisLevel == false)
        Raise -= TomeRaise[Ability][AtLevel-1];

	if (Ability == 3)
		test = 1;
	if (Raise > 0 && IncludeAllTomes == false)
		
	{
		for (int i = 0; i < Raise; i++)
		{

				if (TomesLvl[i] <= AtLevel)
					returnvalue += 1;
	
		}

	}
	else
	{
		returnvalue = Raise;
	}




    return returnvalue;
    }

//---------------------------------------------------------------------------
void CharacterClass::ChangeTomeRaise(ABILITIES Ability, int AtLevel, int Change)
    {
	int CurrentTomeLevel;

	CurrentTomeLevel = GetTomeRaise(Ability, AtLevel, true,true);
	if (CurrentTomeLevel + Change > 7)
		return;
	if (CurrentTomeLevel + Change < 0)
		return;

    TomeRaise[Ability][AtLevel-1] += Change;

    ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::SetTome(ABILITIES Ability, int SetTomeRaise[6][MAXLEVEL])
{
	for (int i = 0; i < MAXLEVEL; i++)
	{
		TomeRaise[Ability][i] = SetTomeRaise[Ability][i];
	}
}
//---------------------------------------------------------------------------
void CharacterClass::AddRaceAutoFeats(int AtLevel)
    {
    int FeatIndex;
    FeatListStruct NewFeat;
	string ParentHeading;
	ostringstream ss;
	FeatDataClass *Feat;
	FeatDataClass *DerivedFeat;

    FeatIndex = Data.GetRaceAutoFeat(Race, AtLevel, 0);
    while (FeatIndex != -1)
        {
        Feat = Data.GetFeatPointer(FeatIndex);

        if (HasFeat(AtLevel, FeatIndex) == false)
            {
            NewFeat.FeatIndex = FeatIndex;
            NewFeat.Level = AtLevel;
            NewFeat.FeatAquireType = FEATAUTOMATIC;
            FeatList.push_back(NewFeat);
				
			//if the feat is a parent feat, add this feat AND all the derived feats
			if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
				{
				ParentHeading = Feat->GetFeatName();
				FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, 0);
				while (FeatIndex != -1)
					{
					DerivedFeat = Data.GetFeatPointer(FeatIndex);
					//only add the derived feat if we do not currently have it
					ss.str("");
					ss << ParentHeading << ": " << DerivedFeat->GetFeatName();
					if (HasFeat(ss.str(), AtLevel) == false)
						{
						NewFeat.Level = AtLevel;
						NewFeat.FeatIndex = FeatIndex;
						NewFeat.FeatAquireType = FEATDERIVED;
						FeatList.push_back(NewFeat);
						}
					FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, FeatIndex+1);
					}				
				}
            }
        FeatIndex = Data.GetRaceAutoFeat(Race, AtLevel, FeatIndex+1);
        }
    
    //one special case we have to hard-code, the Dwarven Waraxe
    //IF the character is a dwarf, AND they have at least one level of fighter, paladin, barbarian, or ranger
    //THEN they automatically get the dwarven waraxe as a free feat
    if (Race == DWARF)
		{
		if (GetClassLevel(FIGHTER, AtLevel) > 0 || GetClassLevel(PALADIN, AtLevel) > 0 || GetClassLevel(BARBARIAN, AtLevel) > 0 || GetClassLevel(RANGER, AtLevel) > 0)
			{
			if (HasFeat("Exotic Weapon Proficiency: Dwarven Waraxe", AtLevel) == false)
				{
				FeatIndex = Data.GetFeatIndex("Exotic Weapon Proficiency: Dwarven Waraxe");
				RemoveFeat(FeatIndex);
				NewFeat.Level = AtLevel;
				NewFeat.FeatIndex = FeatIndex;
				NewFeat.FeatAquireType = FEATAUTOMATIC;
				FeatList.push_back(NewFeat);
				}
			}
		}
        
    
    sort(FeatList.begin(), FeatList.end(), FeatCompare);
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveRaceAutoFeats()
    {
    unsigned int Index;
	int Level;
	int FeatIndex;
	FeatDataClass *Feat;

    Index = 0;
    while (Index < FeatList.size())
        {
        Feat = Data.GetFeatPointer(FeatList[Index].FeatIndex);
        if (Feat->HasRace(Race, FeatList[Index].Level) == FEATAQUIREAUTOMATIC ||
			Feat->HasRace(Race, FeatList[Index].Level) == FEATAQUIREAUTONOPREREQ)
			{
			Level = FeatList[Index].Level;
			FeatIndex = FeatList[Index].FeatIndex;
			FeatList.erase(FeatList.begin() + Index);
			if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
				RemoveFeat(Level, FEATDERIVED);
			}
		//also remove dwarven waraxe
		else if (Feat->GetFeatName() == "Dwarven Waraxe")
			{
			if (FeatList[Index].FeatAquireType == FEATAUTOMATIC)
				FeatList.erase(FeatList.begin() + Index);
			else
				Index++;
			}
        else
            Index++;
        }
    }

//---------------------------------------------------------------------------
void CharacterClass::AddClassAutoFeats(CLASS ClassType, int AtLevel, int ClassLevel)
    {
    int FeatIndex;
    FeatListStruct NewFeat;
	string ParentHeading;
	ostringstream ss;
	FeatDataClass *Feat;
	FeatDataClass *DerivedFeat;

    FeatIndex = Data.GetClassAutoFeat(ClassType, AtLevel, 0);
    while (FeatIndex != -1)
        {

        Feat = Data.GetFeatPointer(FeatIndex);

        if (HasFeat(AtLevel, FeatIndex) == false)
			{
			if (Feat->HaveAllFeatPrereqs(AtLevel) == PREREQ_PASS)
				{
			if (FeatIndex == 573)
				FeatIndex = FeatIndex;
			//make sure the feat isn't here at a higher level
		        RemoveFeat(FeatIndex);
			    NewFeat.FeatIndex = FeatIndex;
	            NewFeat.Level = AtLevel;
		        NewFeat.FeatAquireType = FEATAUTOMATIC;
			    FeatList.push_back(NewFeat);

				//if the feat is a parent feat, add this feat AND all the derived feats
			    if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
					{
					ParentHeading = Feat->GetFeatName();
					FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, 0);
					while (FeatIndex != -1)
						{
						DerivedFeat = Data.GetFeatPointer(FeatIndex);
						//only add the derived feat if we do not currently have it
						ss.str("");
						ss << ParentHeading << ": " << DerivedFeat->GetFeatName();
						if (HasFeat(ss.str(), AtLevel) == false)
							{
							NewFeat.Level = AtLevel;
							NewFeat.FeatIndex = FeatIndex;
							NewFeat.FeatAquireType = FEATDERIVED;
							FeatList.push_back(NewFeat);
							}
						FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, FeatIndex+1);
						}				
					}
				}
			}
        FeatIndex = Data.GetClassAutoFeat(ClassType, AtLevel, FeatIndex+1);
        }

    //one special case we have to hard-code, the Dwarven Waraxe
    //IF the character is a dwarf, AND they have at least one level of fighter, paladin, barbarian, or ranger
    //THEN they automatically get the dwarven waraxe as a free feat
    if (Race == DWARF)
		{
		if (GetClassLevel(FIGHTER, AtLevel) > 0 || GetClassLevel(PALADIN, AtLevel) > 0 || GetClassLevel(BARBARIAN, AtLevel) > 0 || GetClassLevel(RANGER, AtLevel) > 0)
			{
			if (HasFeat("Exotic Weapon Proficiency: Dwarven Waraxe", AtLevel) == false)
				{
				FeatIndex = Data.GetFeatIndex("Exotic Weapon Proficiency: Dwarven Waraxe");
				RemoveFeat(FeatIndex);
				NewFeat.Level = AtLevel;
				NewFeat.FeatIndex = FeatIndex;
				NewFeat.FeatAquireType = FEATAUTOMATIC;
				FeatList.push_back(NewFeat);
				}
			}
		}

    sort(FeatList.begin(), FeatList.end(), FeatCompare);
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveClassAutoFeats(CLASS ClassType, int AtLevel, int ClassLevel)
    {
    unsigned int Index;
	int FeatIndex;
	int Level;
	FeatDataClass *Feat;

    Index = 0;
    while (Index < FeatList.size())
        {
        Feat = Data.GetFeatPointer(FeatList[Index].FeatIndex);
        if (Feat->HasClass(ClassType, ClassLevel, FEATAQUIREAUTOMATIC) == true || Feat->HasClass(ClassType, ClassLevel, FEATAQUIREAUTONOPREREQ) == true)
			{
			if (FeatList[Index].Level == AtLevel)
				{
				Level = FeatList[Index].Level;
				FeatIndex = FeatList[Index].FeatIndex;
				FeatList.erase(FeatList.begin() + Index);
				if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
					RemoveFeat(Level, FEATDERIVED);
				}
			else
				{
				Index++;
				}
			}
        else
            Index++;
        }
    }

//---------------------------------------------------------------------------
int CharacterClass::GetFeat(int LevelLimit, unsigned int Index)
    {
    unsigned int LookIndex;

    LookIndex = 0;
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        if (FeatList[i].Level <= LevelLimit)
            {
            if (LookIndex == Index)
                return FeatList[i].FeatIndex;
            LookIndex++;
            }
        }

    return -1;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetFeat(int Level, FEATSLOTTYPE FeatType, unsigned int Index)
    {
    unsigned int LookIndex;

    LookIndex = 0;
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        if (FeatList[i].Level == Level)
            {
            if (FeatList[i].FeatAquireType == FeatType)
                if (LookIndex == Index)
                    return FeatList[i].FeatIndex;
                else
                    LookIndex++;
            if (FeatType == FEATSELECTED)
                {
                if ((FeatList[i].FeatAquireType == FEATCHARACTER) || (FeatList[i].FeatAquireType == FEATHUMANBONUS) ||
						(FeatList[i].FeatAquireType == FEATFIGHTERBONUS) || (FeatList[i].FeatAquireType == FEATWIZARDBONUS) ||
						(FeatList[i].FeatAquireType == FEATRANGERFAVOREDENEMY) || (FeatList[i].FeatAquireType == FEATROGUEBONUS) ||
						(FeatList[i].FeatAquireType == FEATMONKBONUS) || (FeatList[i].FeatAquireType == FEATMONKPATH) ||
						(FeatList[i].FeatAquireType == FEATDEITY) || (FeatList[i].FeatAquireType == FEATFAVOREDSOULBONUS) ||
						(FeatList[i].FeatAquireType == FEATPASTLIFE) || (FeatList[i].FeatAquireType == FEATHALFELFBONUS) || 
						(FeatList[i].FeatAquireType == FEATARTIFICERBONUS) || (FeatList[i].FeatAquireType == FEATDRUIDWILDSHAPE)  ||
						(FeatList[i].FeatAquireType == FEATDESTINY || (FeatList[i].FeatAquireType == FEATLEGENDARY)))
                    {
                    if (LookIndex == Index)
                        return FeatList[i].FeatIndex;
                    else
                        LookIndex++;
                    }
                }
            }
        }
    return -1;
    }
//---------------------------------------------------------------------------
int CharacterClass::GetFeatCountAtLevel(int Level)
{
	unsigned int FeatCount = 0;
	for (unsigned int i = 0; i < FeatList.size(); i++)
	{
		if ((FeatList[i].FeatAquireType == FEATCHARACTER) || (FeatList[i].FeatAquireType == FEATHUMANBONUS) ||
			(FeatList[i].FeatAquireType == FEATFIGHTERBONUS) || (FeatList[i].FeatAquireType == FEATWIZARDBONUS) ||
			(FeatList[i].FeatAquireType == FEATRANGERFAVOREDENEMY) || (FeatList[i].FeatAquireType == FEATROGUEBONUS) ||
			(FeatList[i].FeatAquireType == FEATMONKBONUS) || (FeatList[i].FeatAquireType == FEATMONKPATH) ||
			(FeatList[i].FeatAquireType == FEATDEITY) || (FeatList[i].FeatAquireType == FEATFAVOREDSOULBONUS) ||
			(FeatList[i].FeatAquireType == FEATPASTLIFE) || (FeatList[i].FeatAquireType == FEATHALFELFBONUS) ||
			(FeatList[i].FeatAquireType == FEATARTIFICERBONUS) || (FeatList[i].FeatAquireType == FEATDRUIDWILDSHAPE) ||
			(FeatList[i].FeatAquireType == FEATDESTINY || (FeatList[i].FeatAquireType == FEATLEGENDARY)))
		{
			if (FeatList[i].Level == Level)
				FeatCount++;
		}
	}
	return FeatCount;
}
//---------------------------------------------------------------------------
int CharacterClass::GetFeatAtLevel(int Level,int index)
{
	unsigned int FeatCount = 0;
	for (unsigned int i = 0; i < FeatList.size(); i++)
	{
		if (FeatList[i].Level == Level)
		{
			if ((FeatList[i].FeatAquireType == FEATCHARACTER) || (FeatList[i].FeatAquireType == FEATHUMANBONUS) ||
				(FeatList[i].FeatAquireType == FEATFIGHTERBONUS) || (FeatList[i].FeatAquireType == FEATWIZARDBONUS) ||
				(FeatList[i].FeatAquireType == FEATRANGERFAVOREDENEMY) || (FeatList[i].FeatAquireType == FEATROGUEBONUS) ||
				(FeatList[i].FeatAquireType == FEATMONKBONUS) || (FeatList[i].FeatAquireType == FEATMONKPATH) ||
				(FeatList[i].FeatAquireType == FEATDEITY) || (FeatList[i].FeatAquireType == FEATFAVOREDSOULBONUS) ||
				(FeatList[i].FeatAquireType == FEATPASTLIFE) || (FeatList[i].FeatAquireType == FEATHALFELFBONUS) ||
				(FeatList[i].FeatAquireType == FEATARTIFICERBONUS) || (FeatList[i].FeatAquireType == FEATDRUIDWILDSHAPE) ||
				(FeatList[i].FeatAquireType == FEATDESTINY || (FeatList[i].FeatAquireType == FEATLEGENDARY)))
			{
				if (FeatCount == index)
				{
					return FeatList[i].FeatIndex;
				}
				FeatCount++;
			}
				
		}
			
	}
}
//---------------------------------------------------------------------------
FEATSLOTTYPE CharacterClass::GetFeatAquireType(int FeatIndex, int Level)
    {
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        if (FeatList[i].FeatIndex == FeatIndex)
            {
            if (Level == FeatList[i].Level)
                {
                return FeatList[i].FeatAquireType;
                }
            }
        }
    return FEATNONE;
    }

//---------------------------------------------------------------------------
bool CharacterClass::HasFeat(string FeatName, int LevelLimit)
    {
    FeatDataClass *Feat;
	int x;
	x = 0;
	if (FeatName == "Greater Ruin")
		x = 0;
	if (FeatName == "Ruin")
		x = 0;
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
		Feat = Data.GetFeatPointer(FeatList[i].FeatIndex);
        if (Feat->GetFeatName(true) == FeatName)
            {
            if (FeatList[i].Level <= LevelLimit)
                return true;
            }
        }
    return false;
    }

//---------------------------------------------------------------------------
bool CharacterClass::HasFeat(int LevelLimit, int Index)
    {
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        if (FeatList[i].FeatIndex == Index)
            {
            if (FeatList[i].Level <= LevelLimit)
                return true;
            }
        }
    return false;
    }

//---------------------------------------------------------------------------
int CharacterClass::CountFeat(string FeatName, int LevelLimit)
    {
    int Count;
    FeatDataClass *Feat;

    //useful for feats that can be taken more than once, this routine will
    //return the number of times the character has taken the feat at or below
    //the level limit
    Count = 0;
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        Feat = Data.GetFeatPointer(FeatList[i].FeatIndex);
        if (Feat->GetFeatName(true) == FeatName)
            {
            if (FeatList[i].Level <= LevelLimit)
                Count++;
            }
        }

    return Count;
    }

//---------------------------------------------------------------------------
string CharacterClass::GetInstructionString(int CurrentSelectedLevel, int Index, int *Value)
    {
    string Instruction;
    CLASS Class;
    int Result;

    Class = GetClass(CurrentSelectedLevel);
	if (Class == CLASSNONE)
		return "";
    Instruction =  Data.GetInstructionString(CurrentSelectedLevel, (int)Race, Class, Index, &Result);

    //value needs modification in some cases
    if (Instruction.find("Ability Increase") != Instruction.npos)
        {
        Result = CalculateTotalAbilityPoints();
		//subtract out any already used
        for (unsigned int i=0; i<6; i++)
            Result -= GetAbilityPointsSpent(i);
        }
    if (Instruction.find("Spend Skill Points") != Instruction.npos)
        {
        Result = CalculateAvailableSkillPoints(CurrentSelectedLevel);
        }

    *Value = Result;
    return Instruction;
    }

//---------------------------------------------------------------------------
void CharacterClass::DetermineFeatSlots(int CurrentSelectedLevel, FEATSLOTTYPE *F1, FEATSLOTTYPE *F2, FEATSLOTTYPE *F3)
    {
    int Index;
    FEATSLOTTYPE Result[3];
    int ClassLevel;
	bool DietySelected;
	bool PactSelected;

    for (unsigned int i=0; i<3; i++)
        Result[i] = FEATNONE;
    Index = 0;
	
    //first check the basic character feat at level 1, 3, 6, 9, 12, 15, 18, 21, 24, 27, and 30
	if (CurrentSelectedLevel == 1 || CurrentSelectedLevel == 3 || CurrentSelectedLevel == 6 || CurrentSelectedLevel == 9 ||
		CurrentSelectedLevel == 12 || CurrentSelectedLevel == 15 || CurrentSelectedLevel == 18 || CurrentSelectedLevel == 21 ||
		CurrentSelectedLevel == 24 || CurrentSelectedLevel == 27 || CurrentSelectedLevel == 30)
	    {
		Result[Index] = FEATCHARACTER;
        Index++;
	    }

	//Human bonus feat
    if (CurrentSelectedLevel == 1 && (Race == HUMAN || Race == PURPLEDRAGONKNIGHT))
	    {
		Result[Index] = FEATHUMANBONUS;
        Index++;
	    }

	//Dragonborn bonus feat
	if (CurrentSelectedLevel == 1 && (Race == DRAGONBORN))
	{
		Result[Index] = FEATDRAGONBORNBONUS;
		Index++;
	}

	//Half-Elf bonus feat
	if (CurrentSelectedLevel == 1 && Race == HALFELF)
		{
		Result[Index] = FEATHALFELFBONUS;
		Index++;
		}

    //fighter bonus feats
	if (ClassRecord[CurrentSelectedLevel-1] == FIGHTER && CurrentSelectedLevel <= HEROICLEVELS)
        {
	    ClassLevel = GetClassLevel(CurrentSelectedLevel);
        if (ClassLevel == 1 || ClassLevel == 2 || ClassLevel == 4 || ClassLevel == 6 || ClassLevel == 8 || ClassLevel == 10 || 
			ClassLevel == 12 || ClassLevel == 14 || ClassLevel == 16 || ClassLevel == 18 || ClassLevel == 20)
	        {
			Result[Index] = FEATFIGHTERBONUS;
	        Index++;
		    }
		}

	//wizard bonus feats
	if (ClassRecord[CurrentSelectedLevel-1] == WIZARD && CurrentSelectedLevel <= HEROICLEVELS)
        {
	    ClassLevel = GetClassLevel(CurrentSelectedLevel);
        if (ClassLevel == 1 || ClassLevel == 5 || ClassLevel == 10 || ClassLevel == 15 || ClassLevel == 20)
	        {
		    Result[Index] = FEATWIZARDBONUS;
            Index++;
	        }
		}

	//Artificer bonus feats
	if (ClassRecord[CurrentSelectedLevel-1] == ARTIFICER && CurrentSelectedLevel <= HEROICLEVELS)
        {
	    ClassLevel = GetClassLevel(CurrentSelectedLevel);
        if (ClassLevel == 4 || ClassLevel == 8 || ClassLevel == 12 || ClassLevel == 16 || ClassLevel == 20)
	        {
		    Result[Index] = FEATARTIFICERBONUS;
            Index++;
	        }
		}

    //ranger favored enemy feat
	if (ClassRecord[CurrentSelectedLevel-1] == RANGER && CurrentSelectedLevel <= HEROICLEVELS)
        {
	    ClassLevel = GetClassLevel(CurrentSelectedLevel);
        if (ClassLevel == 1 || ClassLevel == 5 || ClassLevel == 10 || ClassLevel == 15 || ClassLevel == 20)
	        {
			Result[Index] = FEATRANGERFAVOREDENEMY;
			Index++;
		    }
		}

    //Rogue bonus feat
    if (ClassRecord[CurrentSelectedLevel-1] == ROGUE && CurrentSelectedLevel <= HEROICLEVELS)
	    {
	    ClassLevel = GetClassLevel(CurrentSelectedLevel);
		if (ClassLevel == 10 || ClassLevel == 13 || ClassLevel == 16 || ClassLevel == 19)
            {
	        Result[Index] = FEATROGUEBONUS;
		    Index++;
			}
        }

	//Monk bonus feat
	if (ClassRecord[CurrentSelectedLevel-1] == MONK && CurrentSelectedLevel <= HEROICLEVELS)
	    {
		ClassLevel = GetClassLevel(CurrentSelectedLevel);
		if (ClassLevel == 1 || ClassLevel == 2 || ClassLevel == 6)
	        {
			Result[Index] = FEATMONKBONUS;
            Index++;
	        }
		}

	//Monk path
	if (ClassRecord[CurrentSelectedLevel-1] == MONK && CurrentSelectedLevel <= HEROICLEVELS)
		{
        ClassLevel = GetClassLevel(CurrentSelectedLevel);
		if (ClassLevel == 3)
		    {
			Result[Index] = FEATMONKPATH;
	        Index++;
		    }
        }

	//Deity
	if (CurrentSelectedLevel <= HEROICLEVELS)
		{
		if (ClassRecord[CurrentSelectedLevel-1] == FAVORED_SOUL || ClassRecord[CurrentSelectedLevel-1] == PALADIN || ClassRecord[CurrentSelectedLevel-1] == CLERIC)
		    {
			ClassLevel = GetClassLevel(CurrentSelectedLevel);
			if (ClassLevel == 1)
			    {
				//don't give the user a diety if they've already had the opportunity to select
				DietySelected = false;
				for (int i=0; i<CurrentSelectedLevel-1; i++)
					{
					if (ClassRecord[i] == FAVORED_SOUL || ClassRecord[i] == PALADIN || ClassRecord[i] == CLERIC)
						DietySelected = true;
					}
				if (DietySelected == false)
					{
					Result[Index] = FEATDEITY;
					Index++;
					}
		        }
			if (ClassLevel == 20 && ClassRecord[CurrentSelectedLevel-1] == FAVORED_SOUL)
			    {
				Result[Index] = FEATDEITY;
				Index++;
			    }
			}
		}
	
    //Favored Soul Bonus
	if (ClassRecord[CurrentSelectedLevel-1] == FAVORED_SOUL && CurrentSelectedLevel <= HEROICLEVELS)
		{
        ClassLevel = GetClassLevel(CurrentSelectedLevel);
	    if (ClassLevel == 5 || ClassLevel == 10 || ClassLevel == 15)
		    {
            Result[Index] = FEATFAVOREDSOULBONUS;
	        Index++;
		    }
        }
        
    //Druid Wild Shape
	if (ClassRecord[CurrentSelectedLevel-1] == DRUID && CurrentSelectedLevel <= HEROICLEVELS)
		{
        ClassLevel = GetClassLevel(CurrentSelectedLevel);
	    if (ClassLevel == 2 || ClassLevel == 5 || ClassLevel == 8 ||
			ClassLevel == 11 || ClassLevel == 13 || ClassLevel == 17)
		    {
            Result[Index] = FEATDRUIDWILDSHAPE;
	        Index++;
		    }
        }
	//Warlock Pact
	if (CurrentSelectedLevel <= HEROICLEVELS)
	{
		if (ClassRecord[CurrentSelectedLevel - 1] == WARLOCK)
		{
			ClassLevel = GetClassLevel(CurrentSelectedLevel);
			if (ClassLevel == 1)
			{
				//don't give the user a diety if they've already had the opportunity to select
				PactSelected = false;
				for (int i = 0; i<CurrentSelectedLevel - 1; i++)
				{
					if (ClassRecord[i] == WARLOCK)
						PactSelected = true;
				}
				if (PactSelected == false)
				{
					Result[Index] = FEATWARLOCKPACT;
					Index++;
				}
			}
		}
	}

	//Epic Destiny Feats
	if (CurrentSelectedLevel == 26 || CurrentSelectedLevel == 28 || CurrentSelectedLevel == 29)
		{
		Result[Index] = FEATDESTINY;
		Index++;
		}

	//Legendary Feat
	if (CurrentSelectedLevel == 30)
	{
		Result[Index] = FEATLEGENDARY;
		Index++;
	}

	*F1 = Result[0];
    *F2 = Result[1];
    *F3 = Result[2];

    }

//---------------------------------------------------------------------------
void CharacterClass::AddFeat(int Level, int FeatIndex, FEATSLOTTYPE FeatType)
    {
    FeatListStruct NewFeat;
    string ParentHeading;
	ostringstream ss;
	FeatDataClass *Feat;
	FeatDataClass *DerivedFeat;

	//remove the feat from this level, and all subsequent levels (unless it it a 
	//feat that can be selected multiple times)
	Feat = Data.GetFeatPointer(FeatIndex);
	if (FeatType != FEATPASTLIFE)
		{
	    RemoveFeat(Level, FeatType);
		if (Feat->GetFeatTag(FEATTAGMULTIPLE) == false)
			RemoveFeat(FeatIndex);
		}
    //add the new feat
	NewFeat.Level = Level;
	NewFeat.FeatIndex = FeatIndex;
	NewFeat.FeatAquireType = FeatType;
	FeatList.push_back(NewFeat);
    //if the feat is a parent feat, add this feat AND all the derived feats
    if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
		{
		ParentHeading = Feat->GetFeatName();
		FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, 0);
		while (FeatIndex != -1)
			{
			DerivedFeat = Data.GetFeatPointer(FeatIndex);
			//only add the derived feat if we do not currently have it
			ss.str("");
			ss << ParentHeading << ": " << DerivedFeat->GetFeatName();
			if (HasFeat(ss.str(), Level) == false)
				{
				NewFeat.Level = Level;
				NewFeat.FeatIndex = FeatIndex;
				NewFeat.FeatAquireType = FEATDERIVED;
				FeatList.push_back(NewFeat);
				}
			FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, FeatIndex+1);
			}				
		}

	sort(FeatList.begin(), FeatList.end(), FeatCompare);
	ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::AddFeat(int Level, string FeatName, FEATSLOTTYPE FeatType)
    {
    int FeatIndex;

    FeatIndex = Data.GetFeatIndex(FeatName);
    if (FeatIndex != -1)
        AddFeat(Level, Data.GetFeatIndex(FeatName), FeatType);
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveFeat(int FeatIndex)
    {
    unsigned int Index;
	int Level;
	FeatDataClass *Feat;
	
	Feat = Data.GetFeatPointer(FeatIndex);
         
	Index = 0;
	Level = -1;
	while (Index < FeatList.size())
		{
        if (FeatList[Index].FeatIndex == FeatIndex)
			{
			Level = FeatList[Index].Level;
			FeatList.erase(FeatList.begin()+Index);
			}
        else
			Index++;
        }

    //if the feat is a parent feat, then we also need to delete the derived feats that go with it
    if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true && Level > 0)
		RemoveFeat(Level, FEATDERIVED);

    ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveFeatOnce(int FeatIndex)
    {
    unsigned int Index;
	int Level;
	FeatDataClass *Feat;
	
	Feat = Data.GetFeatPointer(FeatIndex);
         
	Index = 0;
	Level = -1;
	while (Index < FeatList.size())
		{
        if (FeatList[Index].FeatIndex == FeatIndex)
			{
			Level = FeatList[Index].Level;
			FeatList.erase(FeatList.begin()+Index);
			break;
			}
        else
			Index++;
        }

    //if the feat is a parent feat, then we also need to delete the derived feats that go with it
    if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true && Level > 0)
		RemoveFeat(Level, FEATDERIVED);

    ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveFeat(int Level, FEATSLOTTYPE FeatType)
    {
	unsigned int Index;
	int DeletedFeat;
	FeatDataClass *Feat;
	
	//this function removes all feats of a particular type at a particular level	
	Index = 0;
	DeletedFeat = -1;
	while (Index < FeatList.size())
		{
        if (FeatList[Index].Level == Level)
            {
            if (FeatList[Index].FeatAquireType == FeatType)
                {
                DeletedFeat = FeatList[Index].FeatIndex;
                FeatList.erase(FeatList.begin()+Index);
                }
            else
				Index++;
            }
		else
			Index++;		
		}
	
    //if the deleted feat is a parent feat, then we also need to delete the derived feats that go with it
    if (DeletedFeat == -1)
		return;
	Feat = Data.GetFeatPointer(DeletedFeat);
	if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
		RemoveFeat(Level, FEATDERIVED);

    ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::ReAddRemovedAutoFeat(int FeatIndex)
    {
    CLASS Classes[3];
    int Level;
    int ClassLevel;
    int AddedLevel;
    FeatDataClass *Feat;

    //a removed feat may be an autoclass feat later on! If it is, we need to re-add
    //it at the correct level
    AddedLevel = MAXLEVEL+1;
    GetMulticlassClasses(MAXLEVEL, Classes);
    for (unsigned int i=0; i<3; i++)
        {
        Feat = Data.GetFeatPointer(FeatIndex);
		if (Feat->GetFeatName() == "Improved Precise Shot")
			int tempx = 0;
        if (Feat->HasClass(Classes[i], MAXLEVEL, FEATAQUIREAUTOMATIC) == true  || Feat->HasClass(Classes[i], MAXLEVEL, FEATAQUIREAUTONOPREREQ) == true)
            {
            Level = Feat->GetFeatAutoClassLevel(Classes[i]);
            if (Level == -1)
				continue;
            ClassLevel = GetClassLevel(Classes[i], MAXLEVEL);
            if (ClassLevel >= Level)
                {
                Level = GetCharacterLevelAtClassLevel(Classes[i], Level);
                if (Level < AddedLevel)
                    {
                    //re-add the feat
                    AddedLevel = Level;
                    AddFeat(Level, FeatIndex, FEATAUTOMATIC);
                    }
                }
            }
        }
    }

//---------------------------------------------------------------------------
bool CharacterClass::HasAllFeatParentHeadings(string ParentHeading, int LevelLimit)
    {
    int FeatIndex;

    FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, 0);
    while (FeatIndex != -1)
        {
        if (HasFeat(LevelLimit, FeatIndex) == false)
            return false;
        FeatIndex = Data.GetFeatWithParentHeading(ParentHeading, FeatIndex+1);
        }
    return true;
	}

//---------------------------------------------------------------------------
void CharacterClass::ResetAutoFeats(unsigned int AtLevel)
	{
	//reset the race feats
	RemoveRaceAutoFeats();
	for (unsigned int i=1; i<AtLevel+1; i++)
		AddRaceAutoFeats(i);

	//reset the class feats
	for (unsigned int i=1; i<MAXLEVEL; i++)
		{
		RemoveClassAutoFeats(ClassRecord[i-1], i, GetClassLevel(ClassRecord[i-1], i));
		AddClassAutoFeats(ClassRecord[i-1], i, GetClassLevel(ClassRecord[i-1], i));
		}
	}
	
//---------------------------------------------------------------------------
int CharacterClass::GetReincarnateCount()
	{
	int Result;
	
	Result = 0;
	for (unsigned int i=0; i<NUMCLASSES; i++)
		Result += GetReincarnateCount(static_cast<CLASS>(i));
	for (unsigned int i = 0; i < RACEPASTLIFE; i++)
		Result += GetRacePastLifeCount(static_cast<PAST_RACE>(i));
	return Result;
	}

//---------------------------------------------------------------------------
int CharacterClass::GetReincarnateCount(CLASS Class)
	{
	return ReincarnationCount[Class];
	}
	
//---------------------------------------------------------------------------
void CharacterClass::IncreasePastLife(CLASS Class)
	{
		int FeatIndex;
		if (GetReincarnateCount(Class) == 3)
		return;

	ReincarnationCount[Class]++;
	FeatIndex = GetReincarnateFeatIndex(Class);
			AddFeat(1, FeatIndex, FEATPASTLIFE);

	}
	
//---------------------------------------------------------------------------
void CharacterClass::DecreasePastLife(CLASS Class)
	{
	int FeatIndex;
	
	if (GetReincarnateCount(Class) == 0)
		return;
	
	ReincarnationCount[Class]--;
	FeatIndex = GetReincarnateFeatIndex(Class);
	if (FeatIndex != -1)
		RemoveFeatOnce(FeatIndex);

		
	}
//---------------------------------------------------------------------------
	int CharacterClass::GetReincarnateFeatIndex(CLASS Class)
	{
		int FeatIndex = -1;
		switch (Class)
		{
		case FIGHTER:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Fighter");
			break;
		}
		case PALADIN:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Paladin");
			break;
		}
		case BARBARIAN:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Barbarian");
			break;
		}
		case MONK:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Monk");
			break;
		}
		case ROGUE:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Rogue");
			break;
		}
		case RANGER:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Ranger");
			break;
		}
		case CLERIC:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Cleric");
			break;
		}
		case WIZARD:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Wizard");
			break;
		}
		case SORCERER:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Sorcerer");
			break;
		}
		case BARD:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Bard");
			break;
		}
		case FAVORED_SOUL:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Favored Soul");
			break;
		}
		case ARTIFICER:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Artificer");
			break;
		}
		case DRUID:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Druid");
			break;
		}
		case WARLOCK:
		{
			FeatIndex = Data.GetFeatIndex("Past Life: Warlock");
			break;
		}
		}
		return FeatIndex;
	}
//---------------------------------------------------------------------------
int CharacterClass::GetEpicFeatCount(DESTINY_SPHERE Sphere, int feat)
	{
		return EpicPastLifeCount[Sphere][feat];
	}
//---------------------------------------------------------------------------
void CharacterClass::IncreaseEpicFeat(DESTINY_SPHERE Sphere, int feat)
	{
		int FeatIndex;
		if (EpicPastLifeCount[Sphere][feat] == 3)
			return;

		EpicPastLifeCount[Sphere][feat]++;
		FeatIndex = GetEpicFeatIndex(Sphere, feat);
		if (FeatIndex != -1)
			AddFeat(1, FeatIndex, FEATPASTLIFE);

		bool EpicComp = true;
		for (int i = 0; i < EPICPASTLIFESPHERE; i++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (GetEpicFeatCount(static_cast<DESTINY_SPHERE>(i), x) != 3)
					EpicComp = false;
			}
			if (EpicComp == false)
				break;

		}
		//AddEpic Completionist
		if (EpicComp == true)
		{
			FeatIndex = Data.GetFeatIndex("Epic Past Life: Epic Completionist");
			if (FeatIndex != -1)
			{
				AddFeat(1, FeatIndex, FEATPASTLIFE);
			}
				
		}
	}
//---------------------------------------------------------------------------
void CharacterClass::DecreaseEpicFeat(DESTINY_SPHERE Sphere, int feat)
	{
		int FeatIndex;
		if (EpicPastLifeCount[Sphere][feat] == 0)
			return;

		EpicPastLifeCount[Sphere][feat]--;
		FeatIndex = GetEpicFeatIndex(Sphere, feat);
		if (FeatIndex != -1)
			RemoveFeatOnce(FeatIndex);
		//Remove Epic Completionist
		FeatIndex = Data.GetFeatIndex("Epic Past Life: Epic Completionist");
		if (FeatIndex != -1)
			RemoveFeatOnce(FeatIndex);

	}
//---------------------------------------------------------------------------
int CharacterClass::GetEpicFeatIndex(DESTINY_SPHERE Sphere, int feat)
{	
	int FeatIndex = -1;

	switch (Sphere)
	{
		case DS_ARCANE:
		{
			switch (feat)
			{
			case ENERGY_CRITICALS:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Arcane Sphere: Energy Criticals");
				break;
			}

			case ENCH_WEAP:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Arcane Sphere: Enchant Weapon");
				break;
			}
			case ARCANE_ALACRITY:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Arcane Sphere: Arcane Alacrity");
				break;
			}
			}
			break;
		}

		case DS_DIVINE:
		{
			switch (feat)
			{
			case POWER_OLD:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Divine Sphere: Power Over Life and Death");
				break;
			}
			case BRACE:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Divine Sphere: Brace");
				break;
			}
			case BLOCK_ENERGY:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Divine Sphere: Block Energy");
				break;
			}
			}
			break;
		}

		case DS_MARTIAL:
		{
			switch (feat)
			{
			case DOUBLESTRIKE:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Martial Sphere: Doublestrike");
				break;
			}
			case SKILL_MASTERY:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Martial Sphere: Skill Mastery");
				break;
			}
			case FORT:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Martial Sphere: Fortification");
				break;
			}
			}
			break;
		}

		case DS_PRIMAL:
		{
			switch (feat)
			{
			case DOUBLE_SHOT:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Primal Sphere: Double Shot");
				break;
			}
			case FAST_HEAL:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Primal Sphere: Fast Healing");
				break;
			}
			case COLORS_QUEEN:
			{
				FeatIndex = Data.GetFeatIndex("Epic Past Life - Primal Sphere: Colors of the Queen");
				break;
			}
			}
			break;
		}

		default:
			break;
		}


	return FeatIndex;
}
//---------------------------------------------------------------------------
int CharacterClass::GetIconicPastLifeCount(ICONICRACES Race)
	{
		return IconicPastLifeCount[Race];
	}
//---------------------------------------------------------------------------
void CharacterClass::IncreaseIconicPastLife(ICONICRACES Race)
	{
		int FeatIndex;
		if (IconicPastLifeCount[Race] == 3)
			return;

		IconicPastLifeCount[Race]++;
		FeatIndex = GetIconicFeatIndex(Race);
		if (FeatIndex != -1)
			AddFeat(1, FeatIndex, FEATPASTLIFE);
		


	}
//---------------------------------------------------------------------------
void CharacterClass::DecreaseIconicPastLife(ICONICRACES Race)
	{
		int FeatIndex;
		if (IconicPastLifeCount[Race] == 0)
			return;

		IconicPastLifeCount[Race]--;
		FeatIndex = GetIconicFeatIndex(Race);
		if (FeatIndex != -1)
			RemoveFeatOnce(FeatIndex);



	}
//---------------------------------------------------------------------------
int CharacterClass::GetIconicFeatIndex(ICONICRACES Race)
{
	int FeatIndex = -1;

	switch (Race)
	{
	case FEAT_BLADEFORGED:
	{
		FeatIndex = Data.GetFeatIndex("Iconic Past Life: Bladeforged");
		break;
	}
		
	case FEAT_MORNINGLORD:
	{
		FeatIndex = Data.GetFeatIndex("Iconic Past Life: MorningLord");
		break;
	}

	case FEAT_PURPLEDRAGONKNIGHT:
	{
		FeatIndex = Data.GetFeatIndex("Iconic Past Life: Purple Dragon Knight");
		break;
	}

	case FEAT_SHADARKAI:
	{
		FeatIndex = Data.GetFeatIndex("Iconic Past Life: Shadar-Kai");
		break;
	}

	case FEAT_DEEPGNOME:
	{
		FeatIndex = Data.GetFeatIndex("Iconic Past Life: Deep Gnome");
		break;
	}

	default:
		break;
	}



	return FeatIndex;
}
//---------------------------------------------------------------------------
int CharacterClass::GetRacePastLifeCount(PAST_RACE Race)
{
	return RacePastLifeCount[Race];
}
//---------------------------------------------------------------------------
void CharacterClass::IncreaseRacePastLife(PAST_RACE Race)
{
	int FeatIndex;
	if (RacePastLifeCount[Race] == 3)
		return;
	if (RacePastLifeCount[Race] == 2)
		RaceEnhancement++;
	RacePastLifeCount[Race]++;
	FeatIndex = GetRaceFeatIndex(Race);
	if (FeatIndex != -1)
		AddFeat(1, FeatIndex, FEATPASTLIFE);



}
//---------------------------------------------------------------------------
void CharacterClass::DecreaseRacePastLife(PAST_RACE Race)
{
	int FeatIndex;
	if (RacePastLifeCount[Race] == 0)
		return;
	if (RacePastLifeCount[Race] == 3)
		RaceEnhancement--;
	RacePastLifeCount[Race]--;
	FeatIndex = GetRaceFeatIndex(Race);
	if (FeatIndex != -1)
		RemoveFeatOnce(FeatIndex);



}
//---------------------------------------------------------------------------
int CharacterClass::GetRaceFeatIndex(PAST_RACE Race)
{
	int FeatIndex = -1;

	switch (Race)
	{
	case FEAT_HUMAN:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Human Past Life");
		break;
	}

	case FEAT_ELF:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Elf Past Life");
		break;
	}

	case FEAT_HALFLING:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Halfling Past Life");
		break;
	}

	case FEAT_DWARF:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Dwarf Past Life");
		break;
	}

	case FEAT_WARFORGED:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Warforged Past Life");
		break;
	}
	case FEAT_DROW:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Drow Past Life");
		break;
	}

	case FEAT_HALFORC:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Half Orc Past Life");
		break;
	}
	case FEAT_HALFELF:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Half Elf Past Life");
		break;
	}

	case FEAT_GNOME:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Gnome Past Life");
		break;
	}

	case FEAT_DRAGONBORN:
	{
		FeatIndex = Data.GetFeatIndex("Race Past Life: Dragonborn Past Life");
		break;
	}

	default:
		break;
	}



	return FeatIndex;
}
//---------------------------------------------------------------------------
float CharacterClass::CalculateSkillLevel(SKILLS Skill, unsigned int AtLevel, bool AddMiscMod)
    {
    float Result;
	unsigned int HeroicLevel;

    //get the base number from the race and ability score
    Result = 0;

	HeroicLevel = AtLevel;
	if (HeroicLevel > HEROICLEVELS)
		HeroicLevel = HEROICLEVELS;
    for (unsigned int i=0; i<HeroicLevel; i++)
        {
        if (Data.IsSkillPrimary(ClassRecord[i], Skill) == true)
            Result += SkillRaise[Skill][i];
        else
            Result += ((float)SkillRaise[Skill][i]) / 2.0f;
        }

    if (AddMiscMod == true)
		Result += (float)Data.GetBaseSkillLevel(Skill, AtLevel);
        Result += CalculateSkillMiscMod(Skill, AtLevel);

    return Result;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetTotalSkillPointsSpent(SKILLS Skill, unsigned int AtLevel)
    {
    int Result;

	if (AtLevel > 20)
		AtLevel = 20;

    Result = 0;
    for (unsigned int i=0; i<AtLevel; i++)
        {
        Result += SkillRaise[Skill][i];
        }

    return Result;
    }

//---------------------------------------------------------------------------
float CharacterClass::GetTotalSkillPointsSpentDisplay(SKILLS Skill, unsigned int AtLevel)
    {
    float Result;

	if (AtLevel > 20)
		AtLevel = 20;

    Result = 0.0f;
    for (unsigned int i=0; i<AtLevel; i++)
        {
        if (Data.IsSkillPrimary(ClassRecord[i], Skill) == true)
            Result += SkillRaise[Skill][i];
        else
            Result += SkillRaise[Skill][i]/2.0f;
        }

    return Result;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetLevelSkillPointsSpent(SKILLS Skill, unsigned int AtLevel)
    {
	if (AtLevel > 20)
		return 0;

    return SkillRaise[Skill][AtLevel-1];
    }

//---------------------------------------------------------------------------
int CharacterClass::GetLevelSkillPointsSpent(unsigned int AtLevel)
    {
    int Result;

    Result = 0;
    for (unsigned int i=0; i<NUMSKILLS; i++)
        Result += SkillRaise[i][AtLevel-1];
    return Result;
    }

//---------------------------------------------------------------------------
float CharacterClass::GetSkillPointSpendLimit(SKILLS Skill, unsigned int AtLevel)
    {
    float SkillSpendLimit;
    bool Primary;

    Primary = false;
    for (unsigned int i=0; i<AtLevel; i++)
        {
        if (Data.IsSkillPrimary(ClassRecord[i], Skill) == true)
            {
            Primary = true;
            break;
            }
        }
    if (Primary == true)
        SkillSpendLimit = 3.0f + (float)AtLevel;
    else
        SkillSpendLimit = (float)(3.0 + (float)AtLevel)/2.0f;

    return SkillSpendLimit;
    }

//---------------------------------------------------------------------------
bool CharacterClass::HasSkill(int Skillindex, int AtLevel)
{
	bool Result;
	Result = false;
	for (int i = 0; i<AtLevel; i++)
	{
		if (Data.IsSkillPrimary(ClassRecord[i], Skillindex) == true)
		{
			Result = true;
			break;
		}
	}

	return Result;
}

//---------------------------------------------------------------------------
void CharacterClass::SpendSkillPoint(SKILLS Skill, unsigned int Level, int Point)
    {
    Level--;
    SkillRaise[Skill][Level] += Point;
    ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::SetSkillPoints(int (&PointValues)[NUMSKILLS][HEROICLEVELS])
{
	for (int i = 0; i < NUMSKILLS; i++)
	{
		for (int x = 0; x < HEROICLEVELS; x++)
		{
			SkillRaise[i][x] = PointValues[i][x];
		}
		ValidateCharacter();
	}

}

//---------------------------------------------------------------------------
int CharacterClass::CalculateAvailableSkillPoints(unsigned int AtLevel)
    {
    int Result;
	int AbilityTotal;

    if (ClassRecord[AtLevel-1] == CLASSNONE)
        return 0;

    Result = Data.GetClassSkillPoints(ClassRecord[AtLevel-1]);
	AbilityTotal = GetAbility(INTELLIGENCE, AtLevel, false,false,false,false) + GetTomeRaise(INTELLIGENCE, AtLevel, false);

	//we need to subtract 2 points of they have completionist loaded up
	//if (HasFeat("Completionist", AtLevel) == true)
	//	AbilityTotal -= 2;
    Result += Data.CalculateAbilityModifier(AbilityTotal);
    if (Race == HUMAN || Race == PURPLEDRAGONKNIGHT)
        Result++;
	//minimum of 1 point!
	if (Result < 1)
		Result = 1;
    if (AtLevel == 1)
        Result *= 4;
    Result -= GetLevelSkillPointsSpent(AtLevel);

    return Result;
    }

//---------------------------------------------------------------------------
int CharacterClass::CalculateSkillMiscMod(SKILLS Skill, unsigned int AtLevel)
    {
    int Mod;

    Mod = 0;

    if (Skill == BALANCE)
        {
        //balance
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Athletic", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Dwarven Stability", AtLevel) == true)
            Mod += 4;
        if (HasFeat("Skill Focus: Balance", AtLevel) == true)
            Mod += 3;
        if (HasFeat("Mithral Body", AtLevel) == true)
            Mod -= 2;
        if (HasFeat("Adamantine Body", AtLevel) == true)
            Mod -= 5;
        if (HasFeat("Mithral Fluidity", AtLevel) == true)
            Mod += 1;
		if (HasFeat("Least Dragonmark of Passage", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Martial Sphere: Epic Skill Focus: Balance", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Dwarf Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Balance", AtLevel);
		}
    if (Skill == BLUFF)
        {
        //bluff
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Skill Focus: Bluff", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Past Life: Bardic Dilettante", AtLevel) == true)
			Mod += 1;
		if (HasFeat("Divine Sphere: Epic Skill Focus: Bluff", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Bluff", AtLevel);
        }
    if (Skill == CONCENTRATION)
        {
        //concentration
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Discipline", AtLevel) == true)
            Mod += 2;
		if (HasFeat("Past Life: Disciple of the Fist", AtLevel) == true)
			Mod += 2;
        if (HasFeat("Skill Focus: Concentration", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Arcane Sphere: Epic Skill Focus: Concentration", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Concentration", AtLevel);
        }
    if (Skill == DIPLOMACY)
        {
        //diplomacy
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Negotiator", AtLevel) == true)
            Mod += 2;
		if (HasFeat("Past Life: Acolyte of Divine Secrets", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Past Life: Bardic Dilettante", AtLevel) == true)
			Mod += 1;
        if (HasFeat("Skill Focus: Diplomacy", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Divine Sphere: Epic Skill Focus: Diplomacy", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Half Elf Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Diplomacy", AtLevel);
        }
    if (Skill == DISABLEDEVICE)
        {
        //disable device
        Mod += CountFeat("Skill Mastery", AtLevel);
		Mod += CountFeat("Past Life: Artificer", AtLevel);
        if (HasFeat("Nimble Fingers", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Disable Device", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Arcane Sphere: Epic Skill Focus: Disable Device", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Disable Device", AtLevel);
        }
    if (Skill == HAGGLE)
        {
        //haggle
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Negotiator", AtLevel) == true)
            Mod += 2;
		if (HasFeat("Past Life: Bardic Dilettante", AtLevel) == true)
			Mod += 1;
        if (HasFeat("Skill Focus: Haggle", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Divine Sphere: Epic Skill Focus: Haggle", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Gnomish Proficiences", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Race Past Life: Human Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Haggle", AtLevel);
        }
    if (Skill == HEAL)
        {
        //heal
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Self Sufficient", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Heal", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Least Dragonmark of Healing", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Past Life: Initiate of the Faith", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Past Life: Soldier of the Faith", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Divine Sphere: Epic Skill Focus: Heal", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Heal", AtLevel);
		}
	if (Skill == HIDE)
		{
		//hide skill
		Mod += CountFeat("Skill Mastery", AtLevel);
		if (HasFeat("Halfling Size Bonus", AtLevel) == true)
			Mod += 4;
		if (HasFeat("Skill Focus: Hide", AtLevel) == true)
			Mod += 3;
		if (HasFeat("Stealthy", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Mithral Body", AtLevel) == true)
			Mod -= 2;
		if (HasFeat("Adamantine Body", AtLevel) == true)
			Mod -= 5;
		if (HasFeat("Mithral Fluidity", AtLevel) == true)
			Mod += 1;
		if (HasFeat("Least Dragonmark of Shadow", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Martial Sphere: Epic Skill Focus: Hide", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Small Size Bonus", AtLevel) == true)
			Mod += 4;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Hide", AtLevel);
		}
	if (Skill == INTIMIDATE)
		{
		//intimidate skill
		Mod += CountFeat("Skill Mastery", AtLevel);
		if (HasFeat("Bullheaded", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Past Life: Bardic Dilettante", AtLevel) == true)
			Mod += 1;
		if (HasFeat("Past Life: Berserker's Fury", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Past Life: Student of the Sword", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Skill Focus: Intimidate", AtLevel) == true)
			Mod += 3;
		if (HasFeat("Least Dragonmark of Sentinel", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Primal Sphere: Epic Skill Focus: Intimidate", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Half Orc Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Intimidate", AtLevel);
		}
    if (Skill == JUMP)
        {
        //jump skill
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Acrobatic", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Halfling Agility", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Jump", AtLevel) == true)
            Mod += 3;
        if (HasFeat("Mithral Body", AtLevel) == true)
            Mod -= 2;
        if (HasFeat("Adamantine Body", AtLevel) == true)
            Mod -= 5;
        if (HasFeat("Mithral Fluidity", AtLevel) == true)
            Mod += 1;
		if (HasFeat("Primal Sphere: Epic Skill Focus: Jump", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Jump", AtLevel);
        }
    if (Skill == LISTEN)
        {
        //listen skill
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Alertness", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Elven Keen Senses", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Halfling Keen Ears", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Listen", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Divine Sphere: Epic Skill Focus: Listen", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Listen", AtLevel);
        }
    if (Skill == MOVESILENTLY)
        {
        //move silently skill
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Halfling Agility", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Move Silently", AtLevel) == true)
            Mod += 3;
        if (HasFeat("Stealthy", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Mithral Body", AtLevel) == true)
            Mod -= 2;
        if (HasFeat("Adamantine Body", AtLevel) == true)
            Mod -= 5;
        if (HasFeat("Mithral Fluidity", AtLevel) == true)
            Mod += 1;
		if (HasFeat("Primal Sphere: Epic Skill Focus: Move Silently", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Halfling Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Move Silently", AtLevel);
        }
    if (Skill == OPENLOCK)
        {
        //open lock
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Nimble Fingers", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Open Lock", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Martial Sphere: Epic Skill Focus: Open Lock", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Open Lock", AtLevel);
        }
    if (Skill == PERFORM)
        {
        //perform
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Skill Focus: Perform", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Past Life: Bardic Dilettante", AtLevel) == true)
			Mod += 1;
		if (HasFeat("Arcane Sphere: Epic Skill Focus: Perform", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Perform", AtLevel);
        }
    if (Skill == REPAIR)
        {
        //repair
        Mod += CountFeat("Skill Mastery", AtLevel);
		Mod += CountFeat("Past Life: Artificer", AtLevel);
        if (HasFeat("Self Sufficient", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Repair", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Least Dragonmark of Making", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Arcane Sphere: Epic Skill Focus: Repair", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Warforged Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Repair", AtLevel);
		}
    if (Skill == SEARCH)
        {
        //search skill
        Mod += CountFeat("Skill Mastery", AtLevel);
		Mod += CountFeat("Past Life: Artificer", AtLevel);
        if (HasFeat("Dwarven Stonecutting", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Elven Keen Senses", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Search", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Least Dragonmark of Warding", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Martial Sphere: Epic Skill Focus: Search", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Drow Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Search", AtLevel);
		}
    if (Skill == SPELLCRAFT)
		{
        Mod += CountFeat("Skill Mastery", AtLevel);
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Spellcraft", AtLevel);
		if (HasFeat("Past Life: Delver of the Forbidden", AtLevel) == true)
			Mod += 3;
		if (HasFeat("Skill Focus: Spellcraft", AtLevel) == true)
			Mod += 3;
		if (HasFeat("Arcane Sphere: Epic Skill Focus: Spellcraft", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Dragonborn Past Life", AtLevel) == true)
			Mod += 1;
		}
    if (Skill == SPOT)
        {
        //spot skill
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Alertness", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Elven Keen Senses", AtLevel) == true)
            Mod += 2;
		if (HasFeat("Past Life: Warrior of the Wild", AtLevel) == true)
			Mod += 2;
        if (HasFeat("Skill Focus: Spot", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Primal Sphere: Epic Skill Focus: Spot", AtLevel) == true)
			Mod += 5;
		if (HasFeat("Race Past Life: Elf Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Spot", AtLevel);
        }
    if (Skill == SWIM)
        {
        //swim skill
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Athletic", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Swim", AtLevel) == true)
            Mod += 3;
        if (HasFeat("Mithral Body", AtLevel) == true)
            Mod -= 4;
        if (HasFeat("Adamantine Body", AtLevel) == true)
            Mod -= 10;
        if (HasFeat("Mithral Fluidity", AtLevel) == true)
            Mod += 2;
		if (HasFeat("Martial Sphere: Epic Skill Focus: Swim", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Swim", AtLevel);
        }
    if (Skill == TUMBLE)
        {
        //tumble skill
        Mod += CountFeat("Skill Mastery", AtLevel);
        if (HasFeat("Acrobatic", AtLevel) == true)
            Mod += 2;
        if (HasFeat("Skill Focus: Tumble", AtLevel) == true)
            Mod += 3;
        if (HasFeat("Mithral Body", AtLevel) == true)
            Mod -= 2;
        if (HasFeat("Adamantine Body", AtLevel) == true)
            Mod -= 5;
        if (HasFeat("Mithral Fluidity", AtLevel) == true)
            Mod += 1;
		if (HasFeat("Primal Sphere: Epic Skill Focus: Tumble", AtLevel) == true)
			Mod += 5;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Tumble", AtLevel);
        }
    if (Skill == UMD)
        {
        //use magic device skill
        Mod += CountFeat("Skill Mastery", AtLevel);
		Mod += CountFeat("Past Life: Artificer", AtLevel);
        if (HasFeat("Skill Focus: Use Magic Device", AtLevel) == true)
            Mod += 3;
		if (HasFeat("Past Life: Bardic Dilettante", AtLevel) == true)
			Mod += 1;
		if (HasFeat("Warlock: Deceive Item", AtLevel) == true)
			{
				if (AtLevel >= 13)
				{
					Mod += 10;
				}
					
				else
				{
					Mod += 5;
				}
			}
		if (HasFeat("Gnomish Proficiences", AtLevel) == true)
			Mod += 2;
		if (HasFeat("Race Past Life: Gnome Past Life", AtLevel) == true)
			Mod += 1;
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "Use Magic Device", AtLevel);
		Mod += CharacterEnhancements.GetTotalEnhancementMod(MC_SKILL, "UMD", AtLevel);
        }

    // add to all skills    
    if (HasFeat("Completionist", AtLevel) == true)
		Mod += 2;
	if (HasFeat("Past Life: Sneak of Shadows", AtLevel) == true)
		Mod += 1;
	if (HasFeat("Legendary: Scion of the Ethereal Plane", AtLevel) == true)
		Mod += 2;

	//add 1 per level above 20
	if (AtLevel > HEROICLEVELS)
		Mod += AtLevel - HEROICLEVELS;

    return Mod;
    }

//---------------------------------------------------------------------------
void CharacterClass::AddAutoSpells(int AtLevel)
    {
    int ClassLevel;

    ClassLevel = GetClassLevel(CLERIC, AtLevel);
    if (ClassLevel >= 1)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 1), 1);
    if (ClassLevel >= 3)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 3), 2);
    if (ClassLevel >= 5)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 5), 3);
    if (ClassLevel >= 7)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 7), 4);
    if (ClassLevel >= 9)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 9), 5);
    if (ClassLevel >= 11)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 11), 6);
    if (ClassLevel >= 13)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 13), 7);
    if (ClassLevel >= 15)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 15), 8);
    if (ClassLevel >= 17)
        AddAutoSpells(CLERIC, GetCharacterLevelAtClassLevel(CLERIC, 17), 9);

    ClassLevel = GetClassLevel(DRUID, AtLevel);
    if (ClassLevel >= 1)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 1), 1);
    if (ClassLevel >= 3)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 3), 2);
    if (ClassLevel >= 5)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 5), 3);
    if (ClassLevel >= 7)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 7), 4);
    if (ClassLevel >= 9)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 9), 5);
    if (ClassLevel >= 11)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 11), 6);
    if (ClassLevel >= 13)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 13), 7);
    if (ClassLevel >= 15)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 15), 8);
    if (ClassLevel >= 17)
        AddAutoSpells(DRUID, GetCharacterLevelAtClassLevel(DRUID, 17), 9);

    ClassLevel = GetClassLevel(PALADIN, AtLevel);
    if (ClassLevel >= 4)
        AddAutoSpells(PALADIN, GetCharacterLevelAtClassLevel(PALADIN, 4), 1);
    if (ClassLevel >= 8)
        AddAutoSpells(PALADIN, GetCharacterLevelAtClassLevel(PALADIN, 8), 2);
    if (ClassLevel >= 11)
        AddAutoSpells(PALADIN, GetCharacterLevelAtClassLevel(PALADIN, 11), 3);
    if (ClassLevel >= 14)
        AddAutoSpells(PALADIN, GetCharacterLevelAtClassLevel(PALADIN, 14), 4);

    ClassLevel = GetClassLevel(RANGER, AtLevel);
    if (ClassLevel >= 4)
        AddAutoSpells(RANGER, GetCharacterLevelAtClassLevel(RANGER, 4), 1);
    if (ClassLevel >= 8)
        AddAutoSpells(RANGER, GetCharacterLevelAtClassLevel(RANGER, 8), 2);
    if (ClassLevel >= 11)
        AddAutoSpells(RANGER, GetCharacterLevelAtClassLevel(RANGER, 11), 3);
    if (ClassLevel >= 14)
        AddAutoSpells(RANGER, GetCharacterLevelAtClassLevel(RANGER, 14), 4);
	}

//---------------------------------------------------------------------------
void CharacterClass::AddAutoSpells(CLASS Class, int AtLevel, int SpellLevel)
    {
    int Index;
    int SpellIndex;
    SpellListStruct NewSpell;

    Index = 0;
    SpellIndex = Data.GetSpellIndex(Class, SpellLevel, Index);
    while (SpellIndex != -1)
        {
        if (HasSpell(SpellIndex, AtLevel) == false)
            {
            //remove it if its at a later level
            RemoveSelectedSpell(SpellIndex);
            NewSpell.Level = AtLevel;
            NewSpell.SpellIndex = SpellIndex;
            NewSpell.SpellSlot = -1;
            NewSpell.SpellAquireType = SPELLAUTOMATIC;
            SpellList.push_back(NewSpell);
            }
        Index++;
        SpellIndex = Data.GetSpellIndex(Class, SpellLevel, Index);
        }
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveAutoSpells()
    {
    unsigned int Index;

    Index = 0;
    while (Index < SpellList.size())
        {
        if (SpellList[Index].SpellAquireType == SPELLAUTOMATIC)
            SpellList.erase(SpellList.begin() + Index);
        else
            Index++;
        }
    }

//---------------------------------------------------------------------------
int CharacterClass::GetSpellByLevelAquired(int MaxLevel, int Index)
    {
    int Count;

    Count = 0;
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].Level <= MaxLevel)
            {
            if (Index == Count)
                return SpellList[i].SpellIndex;
            else
                Count++;
            }
        }
    return -1;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetSpellLevelAquired(int Index)
    {
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellIndex == Index)
            {
            return SpellList[i].Level;
            }
        }
    return -1;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetSpellBySlot(int AtLevel, int SpellSlot)
    {
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellSlot == SpellSlot)
            {
            if (SpellList[i].Level == AtLevel)
                return SpellList[i].SpellIndex;
            }
        }
    return -1;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetSpellBySpellLevelAndClass(int AtLevel, int SpellLevel, CLASS Class, int Index)
	{
	SpellStruct *SpellData;
	int Count;
	SPELLTYPE SpellType;

	switch (Class)
		{
		case PALADIN:
		case RANGER:
		case CLERIC:
		case DRUID:
			{
			SpellType = SPELLAUTOMATIC;
			break;
			}
		case WIZARD:
		case SORCERER:
		case BARD:
		case FAVORED_SOUL:
		case ARTIFICER:
		case WARLOCK:
			{
			SpellType = SPELLSELECTED;
			break;
			}
		default:
			return -1; 
		}

	Count = 0;
    for (unsigned int i=0; i<SpellList.size(); i++)
		{
		if (SpellList[i].Level > AtLevel)
			continue;
		SpellData = Data.GetSpellData(SpellList[i].SpellIndex);
		for (unsigned int j=0; j<SpellData->ClassType.size(); j++)
			{
			if (SpellData->ClassType[j] == Class && SpellData->Level[j] == SpellLevel && SpellList[i].SpellAquireType == SpellType)
				{
				if (Index == Count)
					return SpellList[i].SpellIndex;
				Count++;
				}
			}
		}
	return -1;	
	}

//---------------------------------------------------------------------------
void CharacterClass::GetSpellSelectionSlots(int AtLevel, int *SpellLevel, int *NumSpells)
    {
    CLASS CurrentClass;
    int ClassLevel;
    int Ability;
    int AbilityModifier;

    CurrentClass = GetClass(AtLevel);
    ClassLevel = GetClassLevel(AtLevel);

    for (unsigned int i=0; i<3; i++)
        {
        SpellLevel[i] = 0;
        NumSpells[i] = 0;
        }

    if (CurrentClass == WIZARD)
        {
        if (ClassLevel == 1)
            {
            Ability = GetAbility((int)INTELLIGENCE, AtLevel, true, false, false, false);
            AbilityModifier = Data.CalculateAbilityModifier(Ability);
            if (AbilityModifier == -1)
				NumSpells[0] = 3;
			else
				NumSpells[0] = 3 + AbilityModifier;
            }
        else
            {
            NumSpells[0] = 2;
            }
        if (ClassLevel == 1 || ClassLevel == 2)
            SpellLevel[0] = 1;
        if (ClassLevel == 3 || ClassLevel == 4)
            SpellLevel[0] = 2;
        if (ClassLevel == 5 || ClassLevel == 6)
            SpellLevel[0] = 3;
        if (ClassLevel == 7 || ClassLevel == 8)
            SpellLevel[0] = 4;
        if (ClassLevel == 9 || ClassLevel == 10)
            SpellLevel[0] = 5;
        if (ClassLevel == 11 || ClassLevel == 12)
            SpellLevel[0] = 6;
        if (ClassLevel == 13 || ClassLevel == 14)
            SpellLevel[0] = 7;
        if (ClassLevel == 15 || ClassLevel == 16)
            SpellLevel[0] = 8;
        if (ClassLevel >= 17)
            SpellLevel[0] = 9;
        }
    if (CurrentClass == ARTIFICER)
        {
        if (ClassLevel == 1)
            {
            Ability = GetAbility((int)INTELLIGENCE, AtLevel, true, false, false, false);
            AbilityModifier = Data.CalculateAbilityModifier(Ability);
            if (AbilityModifier == -1)
				NumSpells[0] = 2;
			else
				NumSpells[0] = 2 + AbilityModifier;
            }
        else
            {
            NumSpells[0] = 1;
            }

        if (ClassLevel == 1 || ClassLevel == 2)
            SpellLevel[0] = 1;
        if (ClassLevel == 3 || ClassLevel == 4 || ClassLevel == 5)
            SpellLevel[0] = 2;
        if (ClassLevel == 6 || ClassLevel == 7 || ClassLevel == 8)
            SpellLevel[0] = 3;
        if (ClassLevel == 9 || ClassLevel == 10 || ClassLevel == 11)
            SpellLevel[0] = 4;
        if (ClassLevel == 12 || ClassLevel == 13 || ClassLevel == 14)
            SpellLevel[0] = 5;
        if (ClassLevel >= 15)
            SpellLevel[0] = 6;
        }


    if (CurrentClass == SORCERER)
        {
        switch (ClassLevel)
            {
            case 1:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 2;
                break;
                }
            case 2:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 3:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 4:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                break;
                }
            case 5:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                break;
                }
            case 6:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                break;
                }
            case 7:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                SpellLevel[1] = 3;
                NumSpells[1] = 1;
                break;
                }
            case 8:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                break;
                }
            case 9:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                SpellLevel[1] = 3;
                NumSpells[1] = 1;
                SpellLevel[2] = 4;
                NumSpells[2] = 1;
                break;
                }
            case 10:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                break;
                }
            case 11:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                SpellLevel[1] = 4;
                NumSpells[1] = 1;
                SpellLevel[2] = 5;
                NumSpells[2] = 1;
                break;
                }
            case 12:
                {
                SpellLevel[0] = 6;
                NumSpells[0] = 1;
                break;
                }
            case 13:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                SpellLevel[1] = 5;
                NumSpells[1] = 1;
                SpellLevel[2] = 6;
                NumSpells[2] = 1;
                break;
                }
            case 14:
                {
                SpellLevel[0] = 7;
                NumSpells[0] = 1;
                break;
                }
            case 15:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                SpellLevel[1] = 6;
                NumSpells[1] = 1;
                SpellLevel[2] = 7;
                NumSpells[2] = 1;
                break;
                }
            case 16:
                {
                SpellLevel[0] = 8;
                NumSpells[0] = 1;
                break;
                }
            case 17:
                {
                SpellLevel[0] = 7;
                NumSpells[0] = 1;
                SpellLevel[1] = 8;
                NumSpells[1] = 1;
                break;
                }
            case 18:
                {
                SpellLevel[0] = 9;
                NumSpells[0] = 1;
                break;
                }
            case 19:
                {
                SpellLevel[0] = 8;
                NumSpells[0] = 1;
                SpellLevel[1] = 9;
                NumSpells[1] = 1;
                break;
                }
            case 20:
                {
                SpellLevel[0] = 9;
                NumSpells[0] = 1;
                break;
                }
            }
        }

    if (CurrentClass == BARD)
        {
        switch (ClassLevel)
            {
            case 1:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 2:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 3:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 4:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 2;
                break;
                }
            case 5:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                SpellLevel[1] = 2;
                NumSpells[1] = 1;
                break;
                }
            case 6:
                {
                //no spells at level 6
                break;
                }
            case 7:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                SpellLevel[1] = 3;
                NumSpells[1] = 2;
                break;
                }
            case 8:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                break;
                }
            case 9:
                {
                //no spells at level 9
                break;
                }
            case 10:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                SpellLevel[1] = 4;
                NumSpells[1] = 2;
                break;
                }
            case 11:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                break;
                }
            case 12:
                {
                //no spells at level 12
                break;
                }
            case 13:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                SpellLevel[1] = 5;
                NumSpells[1] = 2;
                break;
                }
            case 14:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                break;
                }
            case 15:
                {
                //no new spells at level 15
                break;
                }
            case 16:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                SpellLevel[1] = 5;
                NumSpells[1] = 1;
                SpellLevel[2] = 6;
                NumSpells[2] = 2;
                break;
                }
            case 17:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                SpellLevel[1] = 6;
                NumSpells[1] = 1;
                break;
                }
             case 18:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                break;
                }
             case 19:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                SpellLevel[1] = 6;
                NumSpells[1] = 1;
                break;
                }
             case 20:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                break;
                }
             }
        }

	if (CurrentClass == FAVORED_SOUL)
        {
        switch (ClassLevel)
            {
            case 1:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 2;
                break;
                }
            case 2:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 3:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 4:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                break;
                }
            case 5:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                break;
                }
            case 6:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                break;
                }
            case 7:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                SpellLevel[1] = 3;
                NumSpells[1] = 1;
                break;
                }
            case 8:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                break;
                }
            case 9:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                SpellLevel[1] = 3;
                NumSpells[1] = 1;
                SpellLevel[2] = 4;
                NumSpells[2] = 1;
                break;
                }
            case 10:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                break;
                }
            case 11:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                SpellLevel[1] = 4;
                NumSpells[1] = 1;
                SpellLevel[2] = 5;
                NumSpells[2] = 1;
                break;
                }
            case 12:
                {
                SpellLevel[0] = 6;
                NumSpells[0] = 1;
                break;
                }
            case 13:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                SpellLevel[1] = 5;
                NumSpells[1] = 1;
                SpellLevel[2] = 6;
                NumSpells[2] = 1;
                break;
                }
            case 14:
                {
                SpellLevel[0] = 7;
                NumSpells[0] = 1;
                break;
                }
            case 15:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                SpellLevel[1] = 6;
                NumSpells[1] = 1;
                SpellLevel[2] = 7;
                NumSpells[2] = 1;
                break;
                }
            case 16:
                {
                SpellLevel[0] = 8;
                NumSpells[0] = 1;
                break;
                }
            case 17:
                {
                SpellLevel[0] = 7;
                NumSpells[0] = 1;
                SpellLevel[1] = 8;
                NumSpells[1] = 1;
                break;
                }
            case 18:
                {
                SpellLevel[0] = 9;
                NumSpells[0] = 1;
                break;
                }
            case 19:
                {
                SpellLevel[0] = 8;
                NumSpells[0] = 1;
                SpellLevel[1] = 9;
                NumSpells[1] = 1;
                break;
                }
            case 20:
                {
                SpellLevel[0] = 9;
                NumSpells[0] = 1;
                break;
                }
            }
        }
	if (CurrentClass == WARLOCK)
        {
        switch (ClassLevel)
            {
            case 1:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 2:
                {
                SpellLevel[0] = 1;
                NumSpells[0] = 1;
                break;
                }
            case 3:
                {
				//No spells at level 3
                break;
                }
            case 4:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                break;
                }
            case 5:
                {
				//No spells at level 5
                break;
                }
            case 6:
                {
                //no spells at level 6
                break;
                }
            case 7:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                break;
                }
            case 8:
                {
                SpellLevel[0] = 2;
                NumSpells[0] = 1;
                break;
                }
            case 9:
                {
                //no spells at level 9
                break;
                }
            case 10:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                break;
                }
            case 11:
                {
                SpellLevel[0] = 3;
                NumSpells[0] = 1;
                break;
                }
            case 12:
                {
                //no spells at level 12
                break;
                }
            case 13:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                break;
                }
            case 14:
                {
                SpellLevel[0] = 4;
                NumSpells[0] = 1;
                break;
                }
            case 15:
                {
                //no new spells at level 15
                break;
                }
            case 16:
                {
                SpellLevel[0] = 6;
                NumSpells[0] = 1;
                break;
                }
            case 17:
                {
                SpellLevel[0] = 5;
                NumSpells[0] = 1;
                break;
                }
             case 18:
                {
                //no new spells at level 18
                break;
                }
             case 19:
                {
                SpellLevel[0] = 6;
                NumSpells[0] = 1;
                break;
                }
             case 20:
                {
                //no new spells at level 20
                break;
                }
             }
        }
	}

//---------------------------------------------------------------------------
int CharacterClass::GetNumSpellsSelected(int AtLevel)
    {
    int Count;

    Count = 0;
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].Level == AtLevel)
            {
            if (SpellList[i].SpellAquireType == SPELLSELECTED)
                Count++;
            }
        }
    return Count;
    }

//---------------------------------------------------------------------------
void CharacterClass::AddSelectedSpell(int AtLevel, int SpellIndex, int SpellSlot)
    {
    SpellListStruct NewSpell;
    int OldSpell;

    OldSpell = GetSpellBySlot(AtLevel, SpellSlot);
    RemoveSelectedSpell(OldSpell);
    //make sure we aren't just moving the spell slot
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].Level == AtLevel)
            {
            if (SpellList[i].SpellIndex == SpellIndex)
                SpellList.erase(SpellList.begin() + i);
            }
        }
    RemoveSelectedSpell(SpellIndex);
    NewSpell.Level = AtLevel;
    NewSpell.SpellIndex = SpellIndex;
    NewSpell.SpellSlot = SpellSlot;
    NewSpell.SpellAquireType = SPELLSELECTED;
    SpellList.push_back(NewSpell);
    ValidateCharacter();
    }

//---------------------------------------------------------------------------
void CharacterClass::AddSelectedSpell(int AtLevel, string SpellName, int SpellSlot)
    {
    int SpellIndex;

    SpellIndex = Data.GetSpellIndex(SpellName);
    if (SpellIndex != -1)
        AddSelectedSpell(AtLevel, SpellIndex, SpellSlot);
    }

//---------------------------------------------------------------------------
void CharacterClass::RemoveSelectedSpell(int SpellIndex)
    {
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellIndex == SpellIndex)
            {
            SpellList.erase(SpellList.begin() + i);
            return;
            }
        }
    ValidateCharacter();
    }

//---------------------------------------------------------------------------
bool CharacterClass::HasSpell(int SpellIndex, int MaxLevel)
    {
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellIndex == SpellIndex)
            {
            if (SpellList[i].Level <= MaxLevel)
                return true;
            }
        }

    return false;
    }

//---------------------------------------------------------------------------
SPELLTYPE CharacterClass::GetSpellAquireType(int SpellIndex)
	{
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellIndex == SpellIndex)
            {
			return SpellList[i].SpellAquireType;
			}
		}

	return SPELLUNKNOWN;
	}
	
//---------------------------------------------------------------------------
int CharacterClass::CalculateBAB(int AtLevel)
    {
	int ClassLevel[NUMCLASSES];
    int BAB;

	for (unsigned int i=0; i<NUMCLASSES; i++)
        ClassLevel[i] = GetClassLevel(CLASS(i), AtLevel);

	BAB = 0;
	for (unsigned int i=0; i<NUMCLASSES; i++)
        BAB += Data.GetClassBAB(CLASS(i), ClassLevel[i]);

    return BAB;
    }

//---------------------------------------------------------------------------
int CharacterClass::GetSave(SAVETYPE SaveType, int AtLevel, bool IncludeEquipment)
    {
	return GetSaveMod(SaveType, SAVEMOD_TOTAL, AtLevel, IncludeEquipment);
    }

//---------------------------------------------------------------------------
int CharacterClass::GetSaveMod(SAVETYPE SaveType, SAVEMODS ModType, int AtLevel, bool IncludeEquipment)
	{
	int Result;
	int ClassLevel[NUMCLASSES];
	int TempResult;

	switch (ModType)
		{
		case SAVEMOD_BASE:
			{
			for (unsigned int i=0; i<NUMCLASSES; i++)
				ClassLevel[i] = GetClassLevel(CLASS(i), AtLevel);
			Result = 0;
			for (unsigned int i=0; i<NUMCLASSES; i++)
				{
		        switch (SaveType)
			        {
				    case FORTITUDESAVE:
					    {
					    Result += Data.GetBaseSave(FORTITUDESAVE, (CLASS)i, ClassLevel[i]);
						break;
				        }
					case REFLEXSAVE:
			            {
				        Result += Data.GetBaseSave(REFLEXSAVE, (CLASS)i, ClassLevel[i]);
						break;
					    }
		            case WILLSAVE:
			            {
				        Result += Data.GetBaseSave(WILLSAVE, (CLASS)i, ClassLevel[i]);
						break;
						}
					}
	            }
			return Result;
			}
		case SAVEMOD_ABILITY:
			{
			switch (SaveType)
				{
			    case FORTITUDESAVE:
					{
			        return CalculateTotalAbilityMod(CONSTITUTION, AtLevel, true);
					}
		        case REFLEXSAVE:
			        {
				    if (HasFeat("Insightful Reflexes", AtLevel) == true)
					    {
					    if (CalculateTotalAbilityMod(INTELLIGENCE, AtLevel) > CalculateTotalAbilityMod(DEXTERITY, AtLevel, true))
						    {
				            return CalculateTotalAbilityMod(INTELLIGENCE, AtLevel, true);
					        }
			            else
				            {
					        return CalculateTotalAbilityMod(DEXTERITY, AtLevel, true);
						    }
						}
		            else
			            {
				        return CalculateTotalAbilityMod(DEXTERITY, AtLevel, true);
					    }
					}
			    case WILLSAVE:
					{
		            if (HasFeat("Force of Personality", AtLevel) == true)
			            {
				        if (CalculateTotalAbilityMod(CHARISMA, AtLevel, true) > CalculateTotalAbilityMod(WISDOM, AtLevel, true))
					        {
						    return CalculateTotalAbilityMod(CHARISMA, AtLevel, true);
							}
		                else
			                {
				           return CalculateTotalAbilityMod(WISDOM, AtLevel, true);
					        }
						}
		            else
			            {
				        return CalculateTotalAbilityMod(WISDOM, AtLevel, true);
						}
					}
                }
			break;
			}
		case SAVEMOD_FEATS:
			{
		    switch (SaveType)
				{
		        case FORTITUDESAVE:
				    {
					Result = 0;
				    if (HasFeat("Aura of Good", AtLevel) == true)
						Result += 1;
		            if (HasFeat("Divine Grace", AtLevel) == true)
				        {
						if (CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment) > 0)
							{
				            Result += CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment);
							}
						}	
					//paladin dilettante does not stack with Divine Grace, thus the 'else if'. Also, it maxes at +2 bonus
					else if (HasFeat("Half-Elf Dilettante: Paladin", AtLevel) == true)
						{
						if (CalculateTotalAbilityMod(CHARISMA, AtLevel) > 0)
		                    TempResult = CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment);
						if (TempResult > 2)
							TempResult = 2;
						Result += TempResult;
						}
		            if (HasFeat("Great Fortitude", AtLevel) == true)
				        Result += 2;
		            if (HasFeat("Halfling Luck", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Luck of Heroes", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Bulwark of Defense", AtLevel) == true)
				        Result += 2;
					if (HasFeat("Warlock: Beguiling Defense", AtLevel) == true)
						Result += 1;
					if (HasFeat("Warlock: Dark One's Luck", AtLevel) == true)
						Result += 2;
					if (HasFeat("Scion of Arborea", AtLevel) == true)
						Result += 4;
					if (HasFeat("Scion of Limbo", AtLevel) == true)
						Result += 2;
		            return Result;
				    }
		        case REFLEXSAVE:
				    {
					Result = 0;
				    if (HasFeat("Aura of Good", AtLevel) == true)
						Result += 1;
		            if (HasFeat("Divine Grace", AtLevel) == true)
				        {
						if (CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment) > 0)
		                    Result += CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment);
						}
					else if (HasFeat("Half-Elf Dilettante: Paladin", AtLevel) == true)
						{
						if (CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment) > 0)
		                    TempResult = CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment);
						if (TempResult > 2)
							TempResult = 2;
						Result += TempResult;
						}
			        if (HasFeat("Halfling Luck", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Lightning Reflexes", AtLevel) == true)
				        Result += 2;
		            if (HasFeat("Luck of Heroes", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Snake Blood", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Bulwark of Defense", AtLevel) == true)
				        Result += 2;
					if (HasFeat("Warlock: Fiendish Resilience", AtLevel) == true)
						Result += 1;
					if (HasFeat("Warlock: Dark One's Luck", AtLevel) == true)
						Result += 2;
					if (HasFeat("Scion of Limbo", AtLevel) == true)
						Result += 2;
					if (HasFeat("Scion of the Astral Plane", AtLevel) == true)
						Result += 4;
		            return Result;
				    }
		        case WILLSAVE:
				    {
					Result = 0;
		            if (HasFeat("Aura of Good", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Bullheaded", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Discipline", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Divine Grace", AtLevel) == true)
				        {
						if (CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment) > 0)
				            Result += CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment);
						}
					else if (HasFeat("Half-Elf Dilettante: Paladin", AtLevel) == true)
						{
						if (CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment) > 0)
		                    TempResult = CalculateTotalAbilityMod(CHARISMA, AtLevel, IncludeEquipment);
						if (TempResult > 2)
							TempResult = 2;
						Result += TempResult;
						}
		            if (HasFeat("Halfling Luck", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Iron Will", AtLevel) == true)
				        Result += 2;
		            if (HasFeat("Luck of Heroes", AtLevel) == true)
				        Result += 1;
		            if (HasFeat("Bulwark of Defense", AtLevel) == true)
				        Result += 2;
					if (HasFeat("Warlock: Thought Shield", AtLevel) == true)
						Result += 1;
					if (HasFeat("Warlock: Dark One's Luck", AtLevel) == true)
						Result += 2;
					if (HasFeat("Scion of Celestia", AtLevel) == true)
						Result += 4;
					if (HasFeat("Scion of Limbo", AtLevel) == true)
						Result += 2;
		            return Result;
				    }
		        }
			}
		case SAVEMOD_ENHANCEMENT:
			{
			Result = 0;
			switch (SaveType)
				{
				case FORTITUDESAVE:
					Result = CharacterEnhancements.GetTotalEnhancementMod(MC_SAVE, "Fortitude", AtLevel);
					break;
				case REFLEXSAVE:
					Result = CharacterEnhancements.GetTotalEnhancementMod(MC_SAVE, "Reflex", AtLevel);
					break;
				case WILLSAVE:
					Result = CharacterEnhancements.GetTotalEnhancementMod(MC_SAVE, "Will", AtLevel);
					break;
				}

			return Result;
			}
		case SAVEMOD_ENCHANTED:
			{
			if (IncludeEquipment == false)
				return 0;
			return GetItemSaveChange(SaveType, AtLevel);
			}
		case SAVEMOD_TOTAL:
			{
			Result = GetSaveMod(SaveType, SAVEMOD_BASE, AtLevel); 
			Result += GetSaveMod(SaveType, SAVEMOD_ABILITY, AtLevel); 
			Result += GetSaveMod(SaveType, SAVEMOD_FEATS, AtLevel); 
			Result += GetSaveMod(SaveType, SAVEMOD_ENHANCEMENT, AtLevel); 
			Result += GetSaveMod(SaveType, SAVEMOD_ENCHANTED, AtLevel); 
			return Result;
			}
		}
	return 0;
	}

//---------------------------------------------------------------------------
bool CharacterClass::File_Exists(const std::string& name)
	{
		if (FILE *file = fopen(name.c_str(), "r")) {
			fclose(file);
			return true;
		}
		else {
			return false;
		}
	}
//---------------------------------------------------------------------------
void CharacterClass::Save(HWND hwnd, bool SaveAs)
    {
    OPENFILENAME FileOpen;
	static char FileFilter[] = "Text Files\0*.txt\0All Files\0*.*\0";
    ostringstream ss;
   	char FileName[MAX_PATH];
	char InitDirectory[MAX_PATH];
    static char TitleString[] = "Save Character";
    static char DefaultExtension[] = "txt";
    HANDLE FileHandle;
	char WriteBuffer[1024];
	DWORD BytesWritten;
	int Count;
	FeatDataClass *Feat;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	IShellItem *MyShellItem;
	string NewCombinedName;
	int len;
	int rc;
	string CombinedName;
	if (FirstName != "")
		CombinedName = FirstName;
	if (SurName != "")
		if (CombinedName != "")
			CombinedName += " " + SurName;
		else
			CombinedName = SurName;
	if (FiletoOpen[0] == NULL || SaveAs == true)
	{
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, InitDirectory);
	StringCbCat (InitDirectory, MAX_PATH, "\\SaveFiles\\");
    StringCbPrintf(FileName, MAX_PATH, "%s.txt", CombinedName.c_str());


		
	IFileDialog *pfd = NULL;
	LPCWSTR TxtStr = L".txt";
	bool xptest;
	xptest = false;
	//char *dir_org = NULL;

		HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileSaveDialog, (void**)&pfd);
		if (SUCCEEDED(hr) && xptest != true)
		{
			HRESULT hr;
			// Create a new common open file dialog.
			IFileOpenDialog *pfd = NULL;
			hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileSaveDialog, (void**)&pfd);
			rc = -1;  // Error
			if (SUCCEEDED(hr))
			{
				DWORD dwOptions;
				hr = pfd->GetOptions(&dwOptions);
				if (SUCCEEDED(hr))
					hr = pfd->SetOptions(dwOptions | FOS_STRICTFILETYPES);
				// Set the title of the dialog.
				if (SUCCEEDED(hr))
				{
					LPCWSTR szTXT = L"Text File";
					hr = pfd->SetTitle(L"Select File");
					if (SUCCEEDED(hr))
					{
						COMDLG_FILTERSPEC rgSpec[] =
						{
							{ szTXT, L"*.txt" },
						};
						hr = pfd->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
						hr = pfd->SetDefaultExtension(L"txt");
					}
					
					hr = pfd->GetFolder(&MyShellItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszPath = NULL;
						hr = MyShellItem->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
						if (SUCCEEDED(hr))
						{
							if (CombinedName != "")
							{
									int CharCount = 0;
									char Pathstring[MAX_PATH];
									string TestString;
									do	{
										
										int nlength = wcslen(pszPath);
										//Gets converted length
										int nbytes = WideCharToMultiByte(0, 0, pszPath, nlength, NULL, 0, NULL, NULL);
										WideCharToMultiByte(0, 0, pszPath, nlength, Pathstring, nbytes, NULL, NULL);
										Pathstring[nbytes] = '\0';
										if (CharCount >= 0)
											{
												ss.str("");
												ss.clear();
												time_t t = time(0);   // get time now
												struct tm * now = localtime(&t);
												ss << ' ' << (now->tm_year + 1900) << '-'
													<< (now->tm_mon + 1) << '-'
													<< now->tm_mday;

												if (CharCount > 0)
												{
													ss << ' ' << CharCount;
												}

												ss << '\0';
												string str = ss.str();
												NewCombinedName = CombinedName + str.c_str();
												StringCbPrintf(FileName, MAX_PATH, "%s.txt", NewCombinedName.c_str());
											}
										ss.str("");
										ss.clear();
										ss << Pathstring;
										StringCbCat(Pathstring, MAX_PATH, "\0");
										ss << "\\";
										ss << FileName;
										TestString = ss.str();
										CharCount += 1;
									} while (File_Exists(TestString));

									std::wstring stemp = std::wstring(NewCombinedName.begin(), NewCombinedName.end());
								LPCWSTR  DefaultName = (LPCWSTR)stemp.c_str();
								hr = pfd->SetFileName(DefaultName);
							}

						}
						





					}

				}
				// Show the open file dialog.
				if (SUCCEEDED(hr))
				{
					hr = pfd->Show(hwnd);
					if (SUCCEEDED(hr))
					{  // Get the selection from the user.
						IShellItem *psiResult = NULL;
						hr = pfd->GetResult(&psiResult);
						if (SUCCEEDED(hr))
						{
							PWSTR pszPath = NULL;
							hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);

							if (SUCCEEDED(hr))
							{
								if (0 != (len = WideCharToMultiByte(CP_ACP, 0, pszPath, -1, FiletoOpen, MAX_PATH, NULL, NULL)))
								{
									rc = 0;
									FiletoOpen[len] = '\0';

									//FileHandle = CreateFile(FiletoOpen, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
									//if (FileHandle == INVALID_HANDLE_VALUE)
										//return;
									//*FiletoOpen = NULL;
								}
								else
									rc = 1;
								CoTaskMemFree(pszPath);
							}
							psiResult->Release();
						}
					}
					else
					{
						if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
							rc = 1; // User cancelled the dialog...
					}
				}
				pfd->Release();
				if (rc == 1)
					return;
			}
		}
		else
		{
			// use GetOpenFileName() as needed...

			memset(&FileOpen, 0, sizeof(OPENFILENAME));
			FileOpen.lStructSize = sizeof(OPENFILENAME);
			FileOpen.hwndOwner = hwnd;
			FileOpen.hInstance = 0;
			FileOpen.lpstrFilter = FileFilter;
			FileOpen.lpstrCustomFilter = NULL;
			FileOpen.nMaxCustFilter = 0;
			FileOpen.nFilterIndex = 1;
			FileOpen.lpstrFile = FileName;
			FileOpen.nMaxFile = 1024;
			FileOpen.lpstrFileTitle = NULL;
			FileOpen.nMaxFileTitle = 512;
			FileOpen.lpstrInitialDir = InitDirectory;
			FileOpen.lpstrTitle = TitleString;
			FileOpen.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
			FileOpen.nFileOffset = 0;
			FileOpen.nFileExtension = 0;
			FileOpen.lpstrDefExt = DefaultExtension;
			FileOpen.lCustData = 0;
			FileOpen.lpfnHook = 0;
			FileOpen.lpTemplateName = NULL;

			if (GetSaveFileName(&FileOpen) == false)
				return;

			strcpy(FiletoOpen, FileOpen.lpstrFile);
			len = strlen(FiletoOpen);
			FiletoOpen[len] = '\0';
			//FileHandle = CreateFile(FileOpen.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			//if (FileHandle == INVALID_HANDLE_VALUE)
				//return;
		}
	}

	FileHandle = CreateFile(FiletoOpen, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE)
		return;

	StringCbPrintf(WriteBuffer, 1024, "VERSION: %s;\r\n", VERSION);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "NAME: %s, %s;\r\n", FirstName.c_str(), SurName.c_str());
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "RACE: %i;\r\n", (int)Race);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "SEX: %i;\r\n", (int)CharacterSex);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "ALIGNMENT: %i;\r\n", (int)Alignment);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "CLASSRECORD: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<MAXLEVEL; i++)
        {
		StringCbPrintf(WriteBuffer, 1024, "%s,\r\n", Data.GetClassName(ClassRecord[i]).c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
    WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	if (FavorAbilityBonusPoints == true)
        {
		StringCbPrintf(WriteBuffer, 1024, "ABILITYFAVORBONUS: ;\r\n");
	    WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, "ABILITYRAISE: ");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<5; i++)
        {
		StringCbPrintf(WriteBuffer, 1024, "%i, ", AbilityRaise[i]);
	    WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, "%i;\r\n", AbilityRaise[5]);
    WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY4: %i;\r\n", (int)AbilityRaise4);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY8: %i;\r\n", (int)AbilityRaise8);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY12: %i;\r\n", (int)AbilityRaise12);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY16: %i;\r\n", (int)AbilityRaise16);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY20: %i;\r\n", (int)AbilityRaise20);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY24: %i;\r\n", (int)AbilityRaise24);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "ABILITY28: %i;\r\n", (int)AbilityRaise28);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	StringCbPrintf(WriteBuffer, 1024, "TOMERAISE: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<6; i++)
        {
        for (unsigned int j=0; j<MAXLEVEL-1; j++)
            {
			StringCbPrintf(WriteBuffer, 1024, "%i, ", TomeRaise[i][j]);
	        WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
            }
		StringCbPrintf(WriteBuffer, 1024, "%i,\r\n", TomeRaise[i][MAXLEVEL-1]);
        WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
    WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "SKILLRAISE: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	for (unsigned int i=0; i<HEROICLEVELS; i++)
        {
		for (unsigned int j=0; j<NUMSKILLS; j++)
            {
			StringCbPrintf(WriteBuffer, 1024, "%i, ", SkillRaise[j][i]);
            WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
            }
		StringCbPrintf(WriteBuffer, 1024, "\r\n", SkillRaise[NUMSKILLS-1][i]);
        WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
    WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

    Count = 0;
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        Feat = Data.GetFeatPointer(FeatList[i].FeatIndex);
        if (FeatList[i].FeatAquireType != FEATAUTOMATIC && FeatList[i].FeatAquireType != FEATDERIVED && Feat->GetFeatTag(FEATTAGPASTLIFE) == false)
            Count++;
        }
	StringCbPrintf(WriteBuffer, 1024, "FEATLIST: %i,\r\n", Count);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<FeatList.size(); i++)
        {
        Feat = Data.GetFeatPointer(FeatList[i].FeatIndex);
        if (FeatList[i].FeatAquireType != FEATAUTOMATIC && FeatList[i].FeatAquireType != FEATDERIVED && Feat->GetFeatTag(FEATTAGPASTLIFE) == false)
            {
			StringCbPrintf(WriteBuffer, 1024, "%s, %i, %i,\r\n", Feat->GetFeatName(true).c_str(), FeatList[i].Level, (int)FeatList[i].FeatAquireType);
        	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
            }
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	CharacterEnhancements.Save(FileHandle);

    Count = 0;
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellAquireType != SPELLAUTOMATIC)
            Count++;
        }
	StringCbPrintf(WriteBuffer, 1024, "SPELLLIST: %i,\r\n", Count);
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<SpellList.size(); i++)
        {
        if (SpellList[i].SpellAquireType != SPELLAUTOMATIC)
            {
			StringCbPrintf(WriteBuffer, 1024, "%s,, %i, %i,\r\n", Data.GetSpellName(SpellList[i].SpellIndex).c_str(), SpellList[i].Level, SpellList[i].SpellSlot);
        	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
            }
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	
	//Items Section
	StringCbPrintf(WriteBuffer, 1024, "ITEMS: %i, \r\n", CharacterItems.size());
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	for (unsigned int i=0; i<CharacterItems.size(); i++)
		{
		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItem->GetItemName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
		StringCbPrintf(WriteBuffer, 1024, "%s, ", ptItemEffect->GetItemEffectCombinedName().c_str());
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		StringCbPrintf(WriteBuffer, 1024, "\r\n");
      	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
        }
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "EQUIPPED: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		StringCbPrintf(WriteBuffer, 1024, "%i, ", CharacterItemsEquipped[i]);
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		}
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "PASTLIFE: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
    for (unsigned int i=0; i<NUMCLASSES; i++)
        {
		StringCbPrintf(WriteBuffer, 1024, "%i, ", ReincarnationCount[i]);
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		}
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		
	StringCbPrintf(WriteBuffer, 1024, "ICONICPL: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	for (unsigned int i = 0; i<ICONICPASTLIFEFEAT; i++)
	{
		StringCbPrintf(WriteBuffer, 1024, "%i, ", IconicPastLifeCount[i]);
		WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	}
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

	StringCbPrintf(WriteBuffer, 1024, "EPICPL: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	for (unsigned int i = 0; i<EPICPASTLIFESPHERE; i++)
	{
		for (unsigned int x = 0; x < 3; x++)
		{
			StringCbPrintf(WriteBuffer, 1024, "%i, ", EpicPastLifeCount[i][x]);
			WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
		}
	}
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);


	StringCbPrintf(WriteBuffer, 1024, "RACEPL: \r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	for (unsigned int i = 0; i<RACEPASTLIFE; i++)
	{
			StringCbPrintf(WriteBuffer, 1024, "%i, ", RacePastLifeCount[i]);
			WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);
	}
	StringCbPrintf(WriteBuffer, 1024, ";\r\n");
	WriteFile(FileHandle, WriteBuffer, static_cast<DWORD>(strlen(WriteBuffer)), &BytesWritten, NULL);

    CloseHandle(FileHandle);
	ostringstream msg;
	msg << FiletoOpen;
	msg << " was saved.";
	string mymsg;
	mymsg = msg.str();
	MessageBox(0, mymsg.c_str() , "Save", MB_OK);
    }

//---------------------------------------------------------------------------
void CharacterClass::Load(HWND hwnd)
    {
    #define NUMKEYWORDS 27
    HANDLE FileHandle;
    char *FileData;
    DWORD FileSize;
    DWORD BytesRead;
    char *OriginalPointer;
    char *DataPointer;
    char *TempPointer[NUMKEYWORDS];
    char KeywordString[NUMKEYWORDS][256];
    vector <int> Keyword;
    int KeywordFind;
    vector <char*> KeywordLocation;
    char StringData[8192];
	char FileName[1024];
	OPENFILENAME FileOpen;
	static char FileFilter[] = "Text Files\0*.txt\0All Files\0*.*\0";
	char InitDirectory[1024];
	static char TitleString[] = "Load Character";
	static char DefaultExtension[] = "txt";
    string String1;
    string String2;
    int Count;
    int Level;
    int Slot;
    int AquireType;
    char *CommaPointer;
    char *EndPointer;
    size_t Index;
	CharacterItemStruct NewItem;
	unsigned int FileVersion = 0;
	string SearchString;
	unsigned int CommaCount;
	unsigned int Found;
	unsigned int RecordedLevels;
	HWND hWnd;
	int len;
	int rc;
	bool xptest;
	xptest = false;
	//disable validations while we load
	EnableValidations(false);
	StringCbCopy(InitDirectory, 1024, "\0");
    GetCurrentDirectory(1024, InitDirectory);
	StringCbCat (InitDirectory, 1024, "\\SaveFiles\\");
	StringCbCopy(FileName, 1024, "\0");
	IFileDialog *pfd = NULL;

	//clear the current character out
	Reset();

	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileDialog, (void**)&pfd);
	if (SUCCEEDED(hr) && xptest != true)
	{
		HRESULT hr;
		
		// Create a new common open file dialog.
		IFileOpenDialog *pfd = NULL;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
		rc = -1;  // Error
		if (SUCCEEDED(hr))
		{
			DWORD dwOptions;
			hr = pfd->GetOptions(&dwOptions);
			if (SUCCEEDED(hr))
				hr = pfd->SetOptions(dwOptions);
			// Set the title of the dialog.
			if (SUCCEEDED(hr))
			{
				LPCWSTR szTXT = L"Text File";
				hr = pfd->SetTitle(L"Select File");
				if (SUCCEEDED(hr))
				{
					COMDLG_FILTERSPEC rgSpec[] =
					{
						{ szTXT, L"*.txt" },
					};
					hr = pfd->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
				}
			}
			// Show the open file dialog.
			if (SUCCEEDED(hr))
			{
				hr = pfd->Show(hwnd);
				if (SUCCEEDED(hr))
				{  // Get the selection from the user.
					IShellItem *psiResult = NULL;
					hr = pfd->GetResult(&psiResult);
					if (SUCCEEDED(hr))
					{
						PWSTR pszPath = NULL;
						hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
						
						if (SUCCEEDED(hr))
						{
							if (0 != (len = WideCharToMultiByte(CP_ACP, 0, pszPath, -1, FiletoOpen, MAX_PATH, NULL, NULL)))
							{
								rc = 0;
								FiletoOpen[len] = '\0';


								//*FiletoOpen = NULL;
							}
							else
								rc = 1;
							CoTaskMemFree(pszPath);
						}
						psiResult->Release();
					}
				}
				else
				{
					if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
						rc = 1; // User cancelled the dialog...
				}
			}
			pfd->Release();
			if (rc == 1)
				return;
		}
	}
	else
	{
		// use GetOpenFileName() as needed...

		memset(&FileOpen, 0, sizeof(OPENFILENAME));
		FileOpen.lStructSize = sizeof(OPENFILENAME);
		FileOpen.hwndOwner = hwnd;
		FileOpen.hInstance = 0;
		FileOpen.lpstrFilter = FileFilter;
		FileOpen.lpstrCustomFilter = NULL;
		FileOpen.nMaxCustFilter = 0;
		FileOpen.nFilterIndex = 1;
		FileOpen.lpstrFile = FileName;
		FileOpen.nMaxFile = 1024;
		FileOpen.lpstrFileTitle = NULL;
		FileOpen.nMaxFileTitle = 512;
		FileOpen.lpstrInitialDir = InitDirectory;
		FileOpen.lpstrTitle = TitleString;
		FileOpen.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
		FileOpen.nFileOffset = 0;
		FileOpen.nFileExtension = 0;
		FileOpen.lpstrDefExt = DefaultExtension;
		FileOpen.lCustData = 0;
		FileOpen.lpfnHook = 0;
		FileOpen.lpTemplateName = NULL;


		if (GetOpenFileName(&FileOpen) == false)
			return;
		//FileHandle = CreateFile(FileOpen.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    //if (FileHandle == INVALID_HANDLE_VALUE)
        //return;
		
		strcpy(FiletoOpen, FileOpen.lpstrFile);
		
		len = strlen(FiletoOpen);
		if (0 != len)
		{
			rc = 0;
			FiletoOpen[len] = '\0';
			
			//*FiletoOpen = NULL;
		}
	}
	if (FiletoOpen == NULL)
		return;

	FileHandle = CreateFile(FiletoOpen, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE)
		return;

	FileSize = GetFileSize(FileHandle, NULL);
	FileData = new char[FileSize+1];
	SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
	ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
	FileData[BytesRead] = '\0';
	OriginalPointer = FileData;
	CloseHandle(FileHandle);



    //parse the file data
	StringCbCopy(KeywordString[0], 256, "VERSION: ");
	StringCbCopy(KeywordString[1], 256, "NAME: ");
	StringCbCopy(KeywordString[2], 256, "RACE: ");
	StringCbCopy(KeywordString[3], 256, "SEX: ");
	StringCbCopy(KeywordString[4], 256, "ALIGNMENT: ");
	StringCbCopy(KeywordString[5], 256, "CLASSRECORD: ");
	StringCbCopy(KeywordString[6], 256, "ABILITYFAVORBONUS: ");
	StringCbCopy(KeywordString[7], 256, "ABILITYRAISE: ");
	StringCbCopy(KeywordString[8], 256, "ABILITY4: ");
	StringCbCopy(KeywordString[9], 256, "ABILITY8: ");
	StringCbCopy(KeywordString[10], 256, "ABILITY12: ");
	StringCbCopy(KeywordString[11], 256, "ABILITY16: ");
	StringCbCopy(KeywordString[12], 256, "ABILITY20: ");
	StringCbCopy(KeywordString[13], 256, "ABILITY24: ");
	StringCbCopy(KeywordString[14], 256, "ABILITY28: ");
	StringCbCopy(KeywordString[15], 256, "TOMERAISE: ");
	StringCbCopy(KeywordString[16], 256, "SKILLRAISE: ");
	StringCbCopy(KeywordString[17], 256, "FEATLIST: ");
	StringCbCopy(KeywordString[18], 256, "ENHANCEMENTTREELIST: ");
	StringCbCopy(KeywordString[19], 256, "ENHANCEMENTLIST: ");
	StringCbCopy(KeywordString[20], 256, "SPELLLIST: ");
	StringCbCopy(KeywordString[21], 256, "ITEMS: ");
	StringCbCopy(KeywordString[22], 256, "EQUIPPED: ");
	StringCbCopy(KeywordString[23], 256, "PASTLIFE: ");
	StringCbCopy(KeywordString[24], 256, "ICONICPL:");
	StringCbCopy(KeywordString[25], 256, "EPICPL:");
	StringCbCopy(KeywordString[26], 256, "RACEPL:");
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
        TempPointer[i] = strstr(FileData, KeywordString[i]);
    while (true)
        {
		DataPointer = &OriginalPointer[BytesRead];
        for (unsigned int i=0; i<NUMKEYWORDS; i++)
            {
            if (TempPointer[i] != NULL && TempPointer[i] < DataPointer)
                {
                DataPointer = TempPointer[i];
                KeywordFind = i;
                }
            }
        if (DataPointer == &OriginalPointer[BytesRead])
            break;
        Keyword.push_back(KeywordFind);
        KeywordLocation.push_back(DataPointer);
        FileData = strstr(FileData, ";");
        if (FileData == NULL)
            break;
        FileData += 2;
        TempPointer[KeywordFind] = strstr(FileData, KeywordString[KeywordFind]);
        }

    for (unsigned int i=0; i<Keyword.size(); i++)
        {
        DataPointer = KeywordLocation[i];
        DataPointer += strlen(KeywordString[Keyword[i]]);
        strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
        StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
        switch (Keyword[i])
            {
			case 0:		//file version
				{
				//strip the periods so we can use this as an integer
                String1 = StringData;
				Index = String1.find('.');
				while (Index != string::npos)
					{
					String2 = String1;
					String1 = String2.substr(0, Index);
					String1 += String2.substr(Index+1, String2.size());
					Index = String1.find('.');
					}
				FileVersion = atoi(String1.c_str());
				break;								
				}
            case 1:     //character name
                {
                String1 = StringData;
                String1[strstr(DataPointer, ",") - DataPointer] = '\0';
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                String2 = StringData;
                SetName(String1, String2);
                break;
                }
            case 2:     //character race
                {
                SetRace((RACE)atoi(StringData));
                break;
                }
            case 3:     //character sex
                {
                SetSex((SEX)atoi(StringData));
                break;
                }
            case 4:     //alignment
                {
                SetAlignment((ALIGNMENT)atoi(StringData));
                break;
                }
            case 5:     //class record
				{
				//there are two versions, one with the name of the classes, one with
				//an index into the classes. Figure out which one we have
				if (strstr(StringData, "Fighter") == NULL && strstr(StringData, "Paladin") == NULL &&
						strstr(StringData, "Barbarian") == NULL && strstr(StringData, "Monk") == NULL &&
						strstr(StringData, "Rogue") == NULL && strstr(StringData, "Ranger") == NULL &&
						strstr(StringData, "Cleric") == NULL && strstr(StringData, "Wizard") == NULL &&
						strstr(StringData, "Sorcerer") == NULL && strstr(StringData, "Bard") == NULL &&
						strstr(StringData, "Monk") == NULL && strstr(StringData, "Favored Soul") == NULL && 
						strstr(StringData, "Artificer") == NULL && strstr(StringData, "Druid") == NULL && 
						strstr(StringData, "Warlock") == NULL)
					{
					//old version, using indeces
					Index = 14;
					for (unsigned int i=0; i<14; i++)
						{
						CommaPointer = strstr(DataPointer, ",");
						EndPointer = strstr(DataPointer, ";");
						if (EndPointer < CommaPointer)
							{
							Index = i+1;
							break;
							}
						//offset for the new monk class
						if (atoi(StringData) >= 3)
							SetClass((CLASS)(atoi(StringData)+1), i+1);
						else
							SetClass((CLASS)(atoi(StringData)), i+1);
						DataPointer = strstr(DataPointer, ",");
						DataPointer += 2;
						strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
						StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
						}
					if (atoi(StringData) >= 3)
						SetClass((CLASS)(atoi(StringData)+1), static_cast<int>(Index));
					else
						SetClass((CLASS)(atoi(StringData)), static_cast<int>(Index));
					break;
					}
				else
					{
					//new version, that actually uses the class name in the save file
					DataPointer += 2;
					for (unsigned int i=0; i<MAXLEVEL; i++)
						{
						strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
						StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
						String1 = StringData;
						SetClass(ConvertClassStringToIndex(String1.c_str()), i+1);
						DataPointer = strstr(DataPointer, ",");
						DataPointer += 3;
						}
					}
                break;
				}
			case 6:     //ability favor bonus flag
                {
                FavorAbilityBonusPoints = true;
                break;
                }
            case 7:     //ability raises at level 1
                {
                for (unsigned int i=0; i<5; i++)
                    {
                    AbilityRaise[i] = atoi(StringData);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                AbilityRaise[5] = atoi(StringData);
                break;
                }
            case 8:     //ability raised at level 4
                {
                SetAbilityIncrease(4, (ABILITIES)atoi(StringData));
                break;
                }
            case 9:     //ability raised at level 8
                {
                SetAbilityIncrease(8, (ABILITIES)atoi(StringData));
                break;
                }
            case 10:     //ability raised at level 12
                {
                SetAbilityIncrease(12, (ABILITIES)atoi(StringData));
                break;
                }
            case 11:     //ability raised at level 16
                {
                SetAbilityIncrease(16, (ABILITIES)atoi(StringData));
                break;
                }
            case 12:     //ability raised at level 20
                {
                SetAbilityIncrease(20, (ABILITIES)atoi(StringData));
                break;
                }
            case 13:     //ability raised at level 24
                {
                SetAbilityIncrease(24, (ABILITIES)atoi(StringData));
                break;
                }
            case 14:     //ability raised at level 28
                {
                SetAbilityIncrease(28, (ABILITIES)atoi(StringData));
                break;
                }
			case 15:     //tome raise record
                {
				//figure out how many levels we recorded with this save
				//to do this, we are going to count the commas in the string and divide by 6
				SearchString = StringData;
				CommaCount = 0;
				Found = SearchString.find(",");
				while (Found != string::npos)
					{
					CommaCount++;
					Found = SearchString.find(",", Found+1);
					}
				RecordedLevels = CommaCount/6;
                for (unsigned int i=0; i<6; i++)
                    {
                    if (StringData[0] == '\0')
                        break;

                    for (unsigned int j=0; j<RecordedLevels; j++)
                        {
                        TomeRaise[i][j] = atoi(StringData);
                        DataPointer = strstr(DataPointer, ",");
                        DataPointer += 2;
                        strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                        StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                        }
                    DataPointer ++;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 16:     //skill raise record
                {
				//stop at epic levels (20), as there are no skill raises beyond 20
                for (unsigned int i=0; i<HEROICLEVELS; i++)
                    {
                    if (StringData[0] == '\0')
                        break;
					if (FileVersion < 40000)
						{
						//there were 20 skills prior to version 40000
	                    for (unsigned int j=0; j<20; j++)
		                    {
			                SkillRaise[j][i] = atoi(StringData);
				            DataPointer = strstr(DataPointer, ",");
					        DataPointer += 2;
						    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
	                        StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
		                    }
						}
					else
						{
	                    for (unsigned int j=0; j<NUMSKILLS; j++)
		                    {
			                SkillRaise[j][i] = atoi(StringData);
				            DataPointer = strstr(DataPointer, ",");
					        DataPointer += 2;
						    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
	                        StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
		                    }
						}
                    DataPointer ++;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 17:     //the feat list
                {
                Count = atoi(DataPointer);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 3;
                for (int i=0; i<Count; i++)
                    {
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					String1 = StringData;
					DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
                    Level = atoi(StringData);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
                    AquireType = atoi(StringData);
                    AddFeat(Level, String1, (FEATSLOTTYPE)AquireType);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 3;
                    }
				//reset all the auto-feats
				ResetAutoFeats();
                break;
                }
			case 18:	 //the enhancement tree list
				{
				CharacterEnhancements.LoadTrees(StringData);
				break;
				}
			case 19:     //the enhancement list
                {
				//we will ignore enhancement lists if the file was saved from prior to 04.00.00 (no longer apply)
				if (FileVersion > 40000)
					{
					CharacterEnhancements.LoadEnhancements(StringData);
					}
                break;
                }
            case 20:     //the spell list
                {
				//NOTE: Change of format. Do not load spells from files before 04.19.03
				if (FileVersion < 41903)
					break;
                Count = atoi(DataPointer);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 3;
                strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                for (int i=0; i<Count; i++)
                    {
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ",,") - DataPointer);
                    StringData[strstr(DataPointer, ",,") - DataPointer] = '\0';
                    String1 = StringData;
                    DataPointer = strstr(DataPointer, ",,");
                    DataPointer += 3;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                    Level = atoi(StringData);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
                    Slot = atoi(StringData);
                    AddSelectedSpell(Level, String1, Slot);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 3;
                    }
                break;
                }
            case 21:     //the Items list
                {
				//disable this for now
				break;
                Count = atoi(DataPointer);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 4;
				for (int i=0; i<Count; i++)
					{
					CharacterItems.push_back(NewItem);
					Index = CharacterItems.size()-1;
					//Item Name
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].ItemIndex = Data.GetItemIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//Item Effect 1
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].ItemEffect1 = Data.GetItemEffectIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//Item Effect 2
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].ItemEffect2 = Data.GetItemEffectIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//Item Effect 3
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].ItemEffect3 = Data.GetItemEffectIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//Item Effect 4
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].ItemEffect4 = Data.GetItemEffectIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//Item Effect 5
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].ItemEffect5 = Data.GetItemEffectIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//Item Effect 6
					//older files do not include this 
					if (FileVersion < 30902)
						CharacterItems[Index].ItemEffect6 = Data.GetItemEffectIndex("<None>");
					else
						{
						strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
						StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
						CharacterItems[Index].ItemEffect6 = Data.GetItemEffectIndex(StringData);
						DataPointer = strstr(DataPointer, ",");
						DataPointer += 2;
						}
					//Item Eldritch Effect
					strncpy_s (StringData, DataPointer, strstr(DataPointer, ",") - DataPointer);
					StringData[strstr(DataPointer, ",") - DataPointer] = '\0';
					CharacterItems[Index].Eldritch = Data.GetItemEffectIndex(StringData);
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					//older files include a now deprecated set of entries at the end of this catagory
					if (FileVersion <= 31602)
						{
						DataPointer = strstr(DataPointer, ",");
						DataPointer += 2;
						DataPointer = strstr(DataPointer, ",");
						DataPointer += 4;
						}
					}
                break;
                }
			case 22:	//equipped items
				{
				//disable this for now
				break;
				for (int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
					{
                    CharacterItemsEquipped[i] = atoi(StringData);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
				}
            case 23:     //past lives
				{
					SearchString = StringData;
					CommaCount = 0;
					Found = SearchString.find(",");
					while (Found != string::npos)
					{
						CommaCount++;
						Found = SearchString.find(",", Found + 1);
					}
					for (int Count = 0; Count < CommaCount; Count++)
					{
					for (int i=0; i<atoi(StringData); i++)
						IncreasePastLife(static_cast<CLASS>(Count));
		            DataPointer = strstr(DataPointer, ",");
			        DataPointer += 2;
				    strncpy_s (StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
					StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
					}
				break;
				}
			case 24:     //Iconic past lives
			{
				SearchString = StringData;
				CommaCount = 0;
				Found = SearchString.find(",");
				while (Found != string::npos)
				{
					CommaCount++;
					Found = SearchString.find(",", Found + 1);
				}
				for (int Count = 0; Count < CommaCount; Count++)
				{
					for (int i = 0; i<atoi(StringData); i++)
						IncreaseIconicPastLife(static_cast<ICONICRACES>(Count));
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					strncpy_s(StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
					StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
				}
				break;
			}
			case 25:     //Epic past lives
			{
				SearchString = StringData;
				CommaCount = 0;
				Found = SearchString.find(",");
				while (Found != string::npos)
				{
					CommaCount++;
					Found = SearchString.find(",", Found + 1);
				}
				int Sphere;
				int FeatPos;
				Sphere = 0;
				FeatPos = 0;
				for (int Count = 0; Count < CommaCount; Count++)
				{
					//Sphere = Count % EPICPASTLIFESPHERE;
					//FeatPos = (Count - Sphere) / 3;

					for (int i = 0; i<atoi(StringData); i++)
						Character.IncreaseEpicFeat(static_cast<DESTINY_SPHERE>(Sphere), FeatPos);
					FeatPos++;
					if (FeatPos > 2)
					{
						FeatPos = 0;
						Sphere++;
					}
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					strncpy_s(StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
					StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
				}
				break;
			}
			case 26:     //Race past lives
			{
				SearchString = StringData;
				CommaCount = 0;
				Found = SearchString.find(",");
				while (Found != string::npos)
				{
					CommaCount++;
					Found = SearchString.find(",", Found + 1);
				}
				for (int Count = 0; Count < CommaCount; Count++)
				{
					for (int i = 0; i<atoi(StringData); i++)
						Character.IncreaseRacePastLife(static_cast<PAST_RACE>(Count));
					DataPointer = strstr(DataPointer, ",");
					DataPointer += 2;
					strncpy_s(StringData, DataPointer, strstr(DataPointer, ";") - DataPointer);
					StringData[strstr(DataPointer, ";") - DataPointer] = '\0';
				}
				break;
			}
            }
        }

    FileData = OriginalPointer;
	delete[] FileData;
    

	//reenable validations (and will automatically validate)
	EnableValidations(true);

    return;
    #undef NUMKEYWORDS
    }

//---------------------------------------------------------------------------
void CharacterClass::ValidateCharacter()
    {
    int Count;
    int Level;
    bool HasClass[NUMCLASSES];
    CLASS CurrentClass;
    ostringstream ss;
    FEATSLOTTYPE F1, F2, F3;
    int SpellLevel[3];
    int NumSpells[3];
    int SpellIndex;
    int CurrentSpellLevel;
	FeatDataClass *Feat;
	MainScreenClass *MainScreen;

	if (ValidationsDisabledCount > 0)
		return;

	ss << "Character Validating: " << ValidationsDisabledCount << "\r\n";
	OutputDebugString(ss.str().c_str());

    ValidationError.clear();

    if (Data.AllDataFilesLoaded() == false)
        return;

    for (unsigned int i=0; i<MAXLEVEL; i++)
		LevelError[i] = false;


    //check the number of classes (quick check so we don't slow down everything else)
    Count = 0;
    for (unsigned int i=0; i<NUMCLASSES-1; i++)		//don't count CLASSNONE
		{
		if (GetNumClassLevels(static_cast<CLASS>(i+1)) > 0)
			Count++;
		}
		
	if (Count > 3)
		{
		//we know we've failed, do a more detailed check now
	    //(what makes this tricky is that we want to know the level at which the player goes over 3 classes)
		for (unsigned int i=0; i<NUMCLASSES; i++)
			HasClass[i] = false;
		for (unsigned int i=0; i<MAXLEVEL; i++)
			{
			CurrentClass = GetClass(i+1);
			if (CurrentClass != CLASSNONE)
				{
				HasClass[CurrentClass] = true;
				//check to make sure we are not over 3 at this point
				Count = 0;
				for (unsigned int j=0; j<NUMCLASSES; j++)
					{
					if (HasClass[j] == true)
						Count++;
					}	
				if (Count > 3)
					{
					Level = i+1;
					LevelError[i] = true;
					break;
					}
				}
			}
				
		ss << "- Level " << Level << ": Too many classes selected."; 
		ValidationError.push_back(ss.str());
		ss.str("");
		}

    //check alignment
    for (unsigned int i=0; i<20; i++)
        {
        if (ClassRecord[i] != CLASSNONE && Data.IsAlignmentCompatable(ClassRecord[i], Alignment) == false)
            {
			LevelError[i] = true;
			ss << "- Level " << i+1 << ": Alignment Error, selected class alignments are not compatable."; 
            ValidationError.push_back(ss.str());
			ss.str("");
            }
        }

    //check the number of skill points spent
    for (unsigned int i=0; i<HEROICLEVELS; i++)
        {
        if (CalculateAvailableSkillPoints(i+1) < 0)
            {
            LevelError[i] = true;
			ss << "- Level " << i+1 << ": Too many skill points spent";
            ValidationError.push_back(ss.str());
			ss.str("");
            }
        }

    //check that the feats are still legal
    for (int i=0; i<MAXLEVEL; i++)
        {
        for (unsigned int j=0; j<FeatList.size(); j++)
            {
            if (FeatList[j].FeatAquireType == FEATAUTOMATIC || FeatList[j].FeatAquireType == FEATDERIVED || FeatList[j].FeatAquireType == FEATPASTLIFE)
                continue;
            Feat = Data.GetFeatPointer(FeatList[j].FeatIndex);
            DetermineFeatSlots(i+1, &F1, &F2, &F3);
            if (FeatList[j].FeatAquireType != F1 && FeatList[j].FeatAquireType != F2 && FeatList[j].FeatAquireType != F3)
                {
                if (FeatList[j].Level == i+1)
                    {
					LevelError[i] = true;
                    ss << "- Level " << i+1 << ": Illegal Feat Type Selected (" << Feat->GetFeatName() << ")";
                    ValidationError.push_back(ss.str());
					ss.str("");
                    }
                }
            if (Feat->HaveAllFeatPrereqs(i+1) != PREREQ_PASS)
                {
                if (FeatList[j].Level == i+1)
                    {
					LevelError[i] = true;
                    ss << "- Level " << i+1 << ": Illegal Feat Prereq error (" << Feat->GetFeatName() << ")";
                    ValidationError.push_back(ss.str());
					ss.str("");
                    }
                }
            }
        }

    //check the spells
    for (int i=0; i<MAXLEVEL; i++)
        {
        if (ClassRecord[i] == CLASSNONE)
            continue;
        GetSpellSelectionSlots(i+1, SpellLevel, NumSpells);
        //get the selected spell level at each slot
        for (int j=0; j<MAXLEVEL; j++)
            {
            SpellIndex = GetSpellBySlot(i+1, j);
            if (SpellIndex == -1)
                continue;
            CurrentSpellLevel = Data.GetSpellLevel(ClassRecord[i], SpellIndex);
            if (CurrentSpellLevel == 0)
                {
				LevelError[i] = true;
	            ss << "- Level " << i+1 << ": Illegal Spell Selection ";
		        ValidationError.push_back(ss.str());
				ss.str("");
                break;
                }
            if (ClassRecord[i] == WIZARD || ClassRecord[i] == ARTIFICER)
                {
                if (CurrentSpellLevel > SpellLevel[0])
                    {
					LevelError[i] = true;
		            ss << "- Level " << i+1 << ": Illegal Spell Selection ";
			        ValidationError.push_back(ss.str());
					ss.str("");
                    break;
                    }
                NumSpells[0]--;
                if (NumSpells[0] < 0)
                    {
					LevelError[i] = true;
		            ss << "- Level " << i+1 << ": Illegal Spell Selection ";
			        ValidationError.push_back(ss.str());
					ss.str("");
                    break;
                    }
                }
            else
                {
                if (CurrentSpellLevel != SpellLevel[0] && CurrentSpellLevel != SpellLevel[1] && CurrentSpellLevel != SpellLevel[2])
                    {
					LevelError[i] = true;
		            ss << "- Level " << i+1 << ": Illegal Spell Selection ";
			        ValidationError.push_back(ss.str());
					ss.str("");
                    break;
                    }
                if (CurrentSpellLevel == SpellLevel[0])
                    NumSpells[0]--;
                if (CurrentSpellLevel == SpellLevel[1])
                    NumSpells[1]--;
                if (CurrentSpellLevel == SpellLevel[2])
                    NumSpells[2]--;
                if (NumSpells[0] < 0 || NumSpells[1] < 0 || NumSpells[2] < 0)
                    {
					LevelError[i] = true;
		            ss << "- Level " << i+1 << ": Illegal Spell Selection ";
			        ValidationError.push_back(ss.str());
					ss.str("");
                    break;
                    }
                }
            }
        }   
        
    MainScreen = InterfaceManager.GetMainScreen();    
    
    if (ValidationError.size() > 0)
		MainScreen->EnableErrorButton(true);
	else
		MainScreen->EnableErrorButton(false);
    }

//---------------------------------------------------------------------------
string CharacterClass::GetErrorList()
	{
	string ErrorString;
	
	ErrorString = "{\\cf3 ";
	for (unsigned int i=0; i<ValidationError.size(); i++)
		{
		ErrorString += ValidationError[i];
		ErrorString += " \\par ";
		}
	ErrorString += " }";
	return ErrorString;
	}

//---------------------------------------------------------------------------
bool CharacterClass::GetLevelError(unsigned int Level)
	{
	return LevelError[Level];
	}

//---------------------------------------------------------------------------
void CharacterClass::EnableValidations(bool NewSetting)
	{
	ostringstream ss;
	
	if (NewSetting == true)
		{
		if (ValidationsDisabledCount > 0)
			ValidationsDisabledCount--;
		}
	else
		ValidationsDisabledCount++;

	ss << "Validation Change: " << ValidationsDisabledCount << "\r\n";
	OutputDebugString(ss.str().c_str());
	
	if (ValidationsDisabledCount == 0)
		ValidateCharacter();
	}

//---------------------------------------------------------------------------
void CharacterClass::SetActiveEquipment(unsigned int Index, EQUIPMENTSLOTTYPE ChosenSlot)
    {
	ItemClass *ptItem;
	ItemClass *OldptItem;
	int ChosenItemType;
	int OldItemType;

	ptItem = Data.GetItemPointer(CharacterItems[Index].ItemIndex);
	ChosenItemType = ptItem->GetItemType();
	if (ptItem->DoesItemFitSelectedSlot(ChosenSlot) == false)
		return;

	//it is possible for this item to already be equipped. If so, unequip it
	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == Index)
			CharacterItemsEquipped[i] = -1;
		}
	//equip the item
	CharacterItemsEquipped[ChosenSlot] = Index;

	//See if the item is a 2-handed melee weapon and if so we need to unequip the item in the left hand.
	//also, ensure that if we are placing the weapon in the left hand, we actually are moving it to the right hand
	if (ChosenItemType == GREATCLUB || ChosenItemType == GREATSWORD || ChosenItemType == GREATAXE || ChosenItemType == FALCHION || ChosenItemType == MAUL || ChosenItemType == QUARTERSTAFF)
		{
		CharacterItemsEquipped[RIGHTHANDSLOT] = Index;
		CharacterItemsEquipped[LEFTHANDSLOT] = -1;
		}

	//See if the item is a 2-handed Ranged Weapon and if so we need to unequip the item in the right hand.
	//also, ensure that if we are placing the weapon in the right hand, we actually are moving it to the left hand
	if (ChosenItemType == GREATCROSSBOW || ChosenItemType == HANDWRAPS || ChosenItemType == HEAVYCROSSBOW || ChosenItemType == LIGHTCROSSBOW || ChosenItemType == LONGBOW || ChosenItemType == REPEATINGHEAVYCROSSBOW || ChosenItemType == REPEATINGLIGHTCROSSBOW || ChosenItemType == SHORTBOW)
		{
		CharacterItemsEquipped[RIGHTHANDSLOT] = -1;
		CharacterItemsEquipped[LEFTHANDSLOT] = Index;
		}

    //note that if we are adding an item to the left hand and the right hand has a two handed
    //weapon, we have to deactivate it
    if (ChosenSlot == LEFTHANDSLOT)
        {
		OldptItem = Data.GetItemPointer(CharacterItems[CharacterItemsEquipped[RIGHTHANDSLOT]].ItemIndex);
		OldItemType = OldptItem->GetItemType();
		if (OldItemType == GREATCLUB || OldItemType == GREATSWORD || OldItemType == GREATAXE || OldItemType == FALCHION || OldItemType == MAUL || OldItemType == QUARTERSTAFF)
			CharacterItemsEquipped[RIGHTHANDSLOT] = -1;
		}
	
	//note that if we are adding an item to the right hand and the left hand has a two handed ranged weapon,
	//we need to deactivate it.
    if (ChosenSlot == RIGHTHANDSLOT)
        {
		OldptItem = Data.GetItemPointer(CharacterItems[CharacterItemsEquipped[LEFTHANDSLOT]].ItemIndex);
		OldItemType = OldptItem->GetItemType();
		if (OldItemType == GREATCROSSBOW || OldItemType == HANDWRAPS || OldItemType == HEAVYCROSSBOW || OldItemType == LIGHTCROSSBOW || OldItemType == LONGBOW || OldItemType == REPEATINGHEAVYCROSSBOW || OldItemType == REPEATINGLIGHTCROSSBOW || OldItemType == SHORTBOW)
			CharacterItemsEquipped[LEFTHANDSLOT] = -1;
		}
    }

//---------------------------------------------------------------------------
int CharacterClass::GetActiveEquipment(EQUIPMENTSLOTTYPE ChosenSlot)
	{
	return CharacterItemsEquipped[ChosenSlot];
	}

//---------------------------------------------------------------------------
string CharacterClass::ConvertOrdinalNumberToRoman(int Number)
    {
    switch (Number)
        {
        case 1:
            return "I";
        case 2:
            return "II";
        case 3:
            return "III";
        case 4:
            return "IV";
        case 5:
            return "V";
        case 6:
            return "VI";
        case 7:
            return "VII";
        case 8:
            return "VIII";
        case 9:
            return "IX";
        case 10:
            return "X";
        case 11:
            return "XI";
        case 12:
            return "XII";
        case 13:
            return "XIII";
        case 14:
            return "XIV";
        case 15:
            return "XV";
        case 16:
            return "XVI";
        case 17:
            return "XVII";
        case 18:
            return "XVIII";
        case 19:
            return "XIX";
        case 20:
            return "XX";
        }
    return "";
    }

//---------------------------------------------------------------------------
Character_Destinies_Class* CharacterClass::GetCharacterDestiniesPointer()
	{
	return CharacterDestinies.GetCharacterDestiniesAddress();
	}

//---------------------------------------------------------------------------
Character_Enhancements_Class* CharacterClass::GetCharacterEnhancementsPointer()
	{
	return CharacterEnhancements.GetCharacterEnhancementsAddress();
	}

//---------------------------------------------------------------------------
CLASS CharacterClass::ConvertClassStringToIndex(string ClassString)
	{
	if (ClassString == "Fighter")
		return FIGHTER;
	if (ClassString == "Paladin")
		return PALADIN;
	if (ClassString == "Barbarian")
		return BARBARIAN;
	if (ClassString == "Monk")
		return MONK;
	if (ClassString == "Rogue")
		return ROGUE;
	if (ClassString == "Ranger")
		return RANGER;
	if (ClassString == "Cleric")
		return CLERIC;
	if (ClassString == "Wizard")
		return WIZARD;
	if (ClassString == "Sorcerer")
		return SORCERER;
	if (ClassString == "Bard")
		return BARD;
	if (ClassString == "Favored Soul")
		return FAVORED_SOUL;
	if (ClassString == "Artificer")
		return ARTIFICER;
	if (ClassString == "Druid")
		return DRUID;
	if (ClassString == "Warlock")
		return WARLOCK;

	return CLASSNONE;
	}

//------------------------------------------------------------------------------------
int CharacterClass::GetItemData(unsigned int Index, unsigned int *ItemIndex, unsigned int *ItemEffect1, unsigned int *ItemEffect2, unsigned int *ItemEffect3, unsigned int *ItemEffect4, unsigned int *ItemEffect5, unsigned int *ItemEffect6, unsigned int *Eldritch)
    {
    if (Index >= CharacterItems.size())
        return -1;
    *ItemIndex = CharacterItems[Index].ItemIndex;
    *ItemEffect1 = CharacterItems[Index].ItemEffect1;
	*ItemEffect2 = CharacterItems[Index].ItemEffect2;
	*ItemEffect3 = CharacterItems[Index].ItemEffect3;
	*ItemEffect4 = CharacterItems[Index].ItemEffect4;
	*ItemEffect5 = CharacterItems[Index].ItemEffect5;
	*ItemEffect6 = CharacterItems[Index].ItemEffect6;
    *Eldritch = CharacterItems[Index].Eldritch;
    return 0;
    }

//--------------------------------------------------------------------------------------
void CharacterClass::ClearCharacterItems()
	{
	CharacterItems.clear();
	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		CharacterItemsEquipped[i] = -1;
	}

//--------------------------------------------------------------------------------------
void CharacterClass::AddItemToCharacterItems(int ItemIndex, int Effect1, int Effect2, int Effect3, int Effect4, int Effect5, int Effect6, int EldritchEffect)
	{
	CharacterItemStruct NewItem;

	NewItem.ItemIndex = ItemIndex;
	NewItem.ItemEffect1 = Effect1;
	NewItem.ItemEffect2 = Effect2;
	NewItem.ItemEffect3 = Effect3;
	NewItem.ItemEffect4 = Effect4;
	NewItem.ItemEffect5 = Effect5;
	NewItem.ItemEffect6 = Effect6;
	NewItem.Eldritch = EldritchEffect;

	CharacterItems.push_back(NewItem);
	}

//---------------------------------------------------------------------------------------
bool CharacterClass::IsItemEquipped(int Item)
	{
	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)	
		{
		if (CharacterItemsEquipped[i] == Item)
			return true;
		}

	return false;
	}

//----------------------------------------------------------------------------------------
string CharacterClass::GetItemDisplayName(int Item)
	{
	int BuildType;
	string strDisplayName;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;

	ptItem = Data.GetItemPointer(CharacterItems[Item].ItemIndex);
	BuildType = ptItem->GetItemBase();

	switch (BuildType)
		{
		case GENERIC:
			{
			if (CharacterItems[Item].ItemEffect1 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect1);
				strDisplayName = ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			if (CharacterItems[Item].ItemEffect2 != 0)
				{
				// add Effect Prefix Name
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect2);
				strDisplayName += ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			if (CharacterItems[Item].ItemEffect3 != 0)
				{
				// add material Name
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect3);
				strDisplayName += ptItemEffect->GetItemEffectDisplayName() + " ";
				}
			strDisplayName = strDisplayName + ptItem->GetItemName();
			if (CharacterItems[Item].ItemEffect4 !=0)
				{
				//add Effect Suffix Name
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect4);
				strDisplayName +=  " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			break;
			}
		case DRAGONTOUCHED:
		case EPIC:
		case NAMED:
		case SHAVARATHRING:
			{
			strDisplayName = ptItem->GetItemName();
			break;
			}
		case GREENSTEEL:
			{
			strDisplayName = ptItem->GetItemName();
			if (CharacterItems[Item].ItemEffect2 != 0 && CharacterItems[Item].ItemEffect4 == 0 && CharacterItems[Item].ItemEffect6 == 0)	//Need to figure out in-game naming conventions for single tiered GS here
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect1);
				strDisplayName += " with " + ptItemEffect->GetItemEffectDisplayName(); // because it might not include the words "Affinity of"
				}
			else if (CharacterItems[Item].ItemEffect2 != 0 && CharacterItems[Item].ItemEffect4 != 0 && CharacterItems[Item].ItemEffect6 == 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect3);
				strDisplayName.insert(0, "Great Commander ");
				strDisplayName += " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			else if (CharacterItems[Item].ItemEffect2 != 0 && CharacterItems[Item].ItemEffect4 != 0 && CharacterItems[Item].ItemEffect6 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect5);
				strDisplayName.insert(0, "Supreme Tyrant ");
				strDisplayName += " of " + ptItemEffect->GetItemEffectDisplayName();
				}
			break;
			}
		}
	return strDisplayName;
	}

//-----------------------------------------------------------------------------------
string CharacterClass::BuildCharacterItemDescription(int Item)
	{
	string strDescription;

	strDescription = "{\\b {\\cf2";
	strDescription += GetItemDisplayName(Item);
	strDescription += "\\par\\par }}";
	strDescription += GetItemStaticEffectsDescription(CharacterItems[Item].ItemIndex);
	strDescription += "\\par ";
	strDescription += GetItemChosenEffectsDescription(Item);
	strDescription += " \\par\\par {\\cf5";
	strDescription += GetItemFlavorText(CharacterItems[Item].ItemIndex);
	strDescription += "}";


	return strDescription;
	}

//-------------------------------------------------------------------------------------
string CharacterClass::GetItemStaticEffectsDescription(int ItemIndex)
	{
	string strStaticEffectDescriptions;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	unsigned int StaticEffectIndex;
	//int StaticEffectsSize;
	int Index;
    int Result;
	//int ItemBase;

	ptItem = Data.GetItemPointer(ItemIndex);
    Index = 0;
	strStaticEffectDescriptions = "";
	//ItemBase = ptItem->GetItemBase();
	Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
	//StaticEffectsSize = ptItem->GetItemStaticEffectsSize();

	//if (ItemBase != SHAVARATHRING && ItemBase != EPIC)
		//{
	    while (Result == 0)
		    {
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			if (strStaticEffectDescriptions == "")
				{
				strStaticEffectDescriptions = "{\\b {\\cf1";
				strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
				strStaticEffectDescriptions += "}}: ";
				}
			else
				{
				strStaticEffectDescriptions += " \\par {\\b {\\cf1";
				strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
				strStaticEffectDescriptions += "}}: ";
				}
			strStaticEffectDescriptions += ptItemEffect->GetItemEffectDescription();

			Index++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		//}
	/*else if (ItemBase == SHAVARATHRING)
		for (unsigned int i=0; i<CharacterItems.size(); i++)
			if (CharacterItems[i].ItemIndex == ItemIndex)
				{
				if (CharacterItems[i].ItemEffect1 == 0)
					while (Result == 0)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (strStaticEffectDescriptions == "")
							{
							strStaticEffectDescriptions = "{\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						else
							{
							strStaticEffectDescriptions += " \\par {\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						strStaticEffectDescriptions += ptItemEffect->GetItemEffectDescription();

						Index++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}
				else
					while (Index < StaticEffectsSize - 1)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (strStaticEffectDescriptions == "")
							{
							strStaticEffectDescriptions = "{\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						else
							{
							strStaticEffectDescriptions += " \\par {\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						strStaticEffectDescriptions += ptItemEffect->GetItemEffectDescription();

						Index++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}
				}
	else if (ItemBase == EPIC)
		for (unsigned int i=0; i<CharacterItems.size(); i++)
			if (CharacterItems[i].ItemIndex == ItemIndex)
				{
				if (CharacterItems[i].ItemEffect1 == 0 && CharacterItems[i].ItemEffect2 == 0)
					while (Result == 0)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (strStaticEffectDescriptions == "")
							{
							strStaticEffectDescriptions = "{\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						else
							{
							strStaticEffectDescriptions += " \\par {\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						strStaticEffectDescriptions += ptItemEffect->GetItemEffectDescription();

						Index++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}
				else if (CharacterItems[i].ItemEffect1 == 0 && CharacterItems[i].ItemEffect2 != 0)
					while (Index < StaticEffectsSize)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (strStaticEffectDescriptions == "")
							{
							strStaticEffectDescriptions = "{\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						else
							{
							strStaticEffectDescriptions += " \\par {\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						strStaticEffectDescriptions += ptItemEffect->GetItemEffectDescription();
						
						Index++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}
				else
					while (Result == 0 && Index < StaticEffectsSize-1)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (strStaticEffectDescriptions == "")
							{
							strStaticEffectDescriptions = "{\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						else
							{
							strStaticEffectDescriptions += " \\par {\\b {\\cf1";
							strStaticEffectDescriptions += ptItemEffect->GetItemEffectName();
							strStaticEffectDescriptions += "}}: ";
							}
						strStaticEffectDescriptions += ptItemEffect->GetItemEffectDescription();
					
						Index++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}																			
				}*/

	return strStaticEffectDescriptions;
	}

//---------------------------------------------------------------------------------------
string CharacterClass::GetItemChosenEffectsDescription(int Item)
	{
	string strChosenEffectDescriptions;
	ItemEffectClass *ptItemEffect;
	ItemClass *ptItem;
	int BuildType;

	ptItem = Data.GetItemPointer(CharacterItems[Item].ItemIndex);
	BuildType = ptItem->GetItemBase();

	strChosenEffectDescriptions = "";
	/*for (unsigned int i=0; i<CharacterItems[Item].ItemEffects.size(); i++)
		{
		if (CharacterItems[Item].ItemEffects[i] != 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffects[i]);
			strChosenEffectDescriptions += "{\\b {\\cf1";
			strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
			strChosenEffectDescriptions += "}}: ";
			strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
			strChosenEffectDescriptions += " \\par ";
			}
		}*/
	switch (BuildType)
		{
		case GENERIC:
		case DRAGONTOUCHED:
		case NAMED:
			{
			if (CharacterItems[Item].ItemEffect1 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect1);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			if (CharacterItems[Item].ItemEffect2 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect2);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			if (CharacterItems[Item].ItemEffect3 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect3);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			if (CharacterItems[Item].ItemEffect4 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect4);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			if (CharacterItems[Item].ItemEffect5 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect5);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			if (CharacterItems[Item].ItemEffect6 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect6);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			break;
			}
		case GREENSTEEL:
			{
			if (CharacterItems[Item].ItemEffect1 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect1);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription() + " \\par ";
				}
			if (CharacterItems[Item].ItemEffect2 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect2);
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription() + " \\par ";
				}
			if (CharacterItems[Item].ItemEffect3 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect3);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				}
			if (CharacterItems[Item].ItemEffect4 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect4);
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription() + " \\par ";
				}
			if (CharacterItems[Item].ItemEffect5 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect5);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				}
			if (CharacterItems[Item].ItemEffect6 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect6);
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription() + " \\par ";
				}
			break;
			}
		case SHAVARATHRING:
			{
			if (CharacterItems[Item].ItemEffect2 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect2);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			break;
			}
		case EPIC:
			{
			if (CharacterItems[Item].ItemEffect1 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect1);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			if (CharacterItems[Item].ItemEffect2 != 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].ItemEffect2);
				strChosenEffectDescriptions += "{\\b {\\cf1";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
				strChosenEffectDescriptions += "}}: ";
				strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
				strChosenEffectDescriptions += " \\par ";
				}
			break;
			}
		}
	if (CharacterItems[Item].Eldritch != 0)
		{
		ptItemEffect = Data.GetItemEffectPointer(CharacterItems[Item].Eldritch);
		strChosenEffectDescriptions += "{\\b {\\cf1";
		strChosenEffectDescriptions += ptItemEffect->GetItemEffectName();
		strChosenEffectDescriptions += "}}: ";
		strChosenEffectDescriptions += ptItemEffect->GetItemEffectDescription();
		strChosenEffectDescriptions += " \\par ";
		}
	return strChosenEffectDescriptions;
	}

//----------------------------------------------------------------------------------------------
string CharacterClass::GetItemFlavorText(int ItemIndex)
	{
	string strFlavorText;
	ItemClass *ptItem;

	ptItem = Data.GetItemPointer(ItemIndex);
	strFlavorText = ptItem->GetItemFlavorText();
	return strFlavorText;
	}
//------------------------------------------------------------------------------------------
int CharacterClass::GetItemAbilityChange(ABILITIES Ability)
	{
	int intAlchemicalChange;
	int intCompetenceChange;
	int intEnhancementChange;
	int intExceptionalChange[4];
	int intInsightChange;
	int intLuckChange;
	int intPenaltyChange;
	int intProfaneChange;
	int intNewValue;
	int intTotalChange;

	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	unsigned int StaticEffectIndex;
	int AbilityModifier;
	int Index;
	int Result;
	int Index2;
	int Result2;
	int ModType;

	intAlchemicalChange = 0;
	intCompetenceChange = 0;
	intEnhancementChange = 0;
	for (int i=0; i<4; i++)
		intExceptionalChange[i] = 0;
	intInsightChange = 0;
	intLuckChange = 0;
	intPenaltyChange = 0;
	intProfaneChange = 0;

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		// We need to check the static effects of item equipped for the ability we are checking.
		ptItem = Data.GetItemPointer(CharacterItems[CharacterItemsEquipped[i]].ItemIndex);
		Index = 0;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
		while (Result == 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
						}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			Index ++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		if (CharacterItems[i].ItemEffect1 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
						}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		if (CharacterItems[i].ItemEffect2 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
						}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		if (CharacterItems[i].ItemEffect3 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
						}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		if (CharacterItems[i].ItemEffect4 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
							}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		if (CharacterItems[i].ItemEffect5 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
						}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		if (CharacterItems[i].ItemEffect6 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
						}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		if (CharacterItems[i].Eldritch > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
			while (Result2 == 0)
				{
				if (AbilityModifier == Ability)
					{
					ModType = ptItemEffect->GetItemEffectAbilityModType(Index2);
					intNewValue = ptItemEffect->GetItemEffectAbilityChange(Index2);
					switch (ModType)
						{
						case ALCHEMICALMOD:
							{
							if (intNewValue > intAlchemicalChange)
								intAlchemicalChange = intNewValue;
							break;
							}
						case COMPETENCEMOD:
							{
							if (intNewValue > intCompetenceChange)
								intCompetenceChange = intNewValue;
							break;
							}
						case ENHANCEMENTMOD:
							{
							if (intNewValue > intEnhancementChange)
								intEnhancementChange = intNewValue;
							break;
							}
						case EXCEPTIONALMOD:
							{
							intExceptionalChange[intNewValue] = 1;
							break;
							}
						case INSIGHTMOD:
							{
							if (intNewValue > intInsightChange)
								intInsightChange = intNewValue;
							break;
							}
						case LUCKMOD:
							{
							if (intNewValue > intLuckChange)
								intLuckChange = intNewValue;
							break;
							}
						case PENALTYMOD:
							{
							if (intNewValue > intPenaltyChange)
								intPenaltyChange = intNewValue;
							break;
							}
						case PROFANEMOD:
							{
							if (intNewValue > intProfaneChange)
								intProfaneChange = intNewValue;
							break;
							}
							}
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectAbilityModifier(Index2, &AbilityModifier);
				}
			}
		}

	//Total up all the Values for a final Value
	intTotalChange = 0;
	intTotalChange += intAlchemicalChange;
	intTotalChange += intCompetenceChange;
	intTotalChange += intEnhancementChange;
	for (unsigned int i=0; i<4; i++)
		{
		if (intExceptionalChange[i] == 1)
			intTotalChange += i;
		}
	intTotalChange += intInsightChange;
	intTotalChange += intLuckChange;
	intTotalChange -= intPenaltyChange;
	intTotalChange += intProfaneChange;
	return intTotalChange;
	}

//------------------------------------------------------------------------------------
int CharacterClass::GetItemHitPointChange(int CurrentSelectedLevel)
	{
	int BaseStatHP;
    int ModStatHP;
    int StatChange;
    int intTotalChange;
	int intMaximumChange;
	int intToughnessChange;
	int intElementalChange;
	int intImprovedElementalChange;
	int intGreaterElementalChange;
	int intExceptionalChange[4];
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int Index;
	int Result;
	unsigned int StaticEffectIndex;
	vector <int> intHPModType;
	vector <int> intHPChange;
	int intCount;

    StatChange = 0;
	intHPModType.clear();
	intHPChange.clear();
	for (int i=0; i<4; i++)
		intExceptionalChange[i] = 0;
	intMaximumChange = 0;
	intToughnessChange = 0;
	intElementalChange = 0;
	intImprovedElementalChange = 0;
	intGreaterElementalChange = 0;
	intCount =0;

    //note that there are two possibilities here
    //the equipment could affect the hit points directly
    //or it could affect the stat that affects hit points
    BaseStatHP = Data.CalculateAbilityModifier(GetAbility((int)CONSTITUTION, CurrentSelectedLevel, true));
    ModStatHP = Data.CalculateAbilityModifier(GetAbility((int)CONSTITUTION, CurrentSelectedLevel, true) + GetItemAbilityChange(CONSTITUTION));

    StatChange += (ModStatHP - BaseStatHP) * CurrentSelectedLevel;

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		//we need to check if item has static effects that effect Hit Points.
		ptItem = Data.GetItemPointer(CharacterItems[CharacterItemsEquipped[i]].ItemIndex);
		Index = 0;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
		while (Result == 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount++;
				}
			Index ++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		// now we need to check for Chosen effects on the equipped item.
		if (CharacterItems[i].ItemEffect1 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect2 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect3 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect4 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect5 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect6 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].Eldritch > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
			if (ptItemEffect->GetItemEffectHPModType() != NOMOD)
				{
				intHPModType.push_back(ptItemEffect->GetItemEffectHPModType());
				intHPChange.push_back(ptItemEffect->GetItemEffectHPChange());
				intCount ++;
				}
			}
		}

	// Now to retrieve our values from the 2 vectors and total them up.
	for (int i=0; i<intCount; i++)
		{
		switch (intHPModType[i])
			{
			case EXCEPTIONALMOD:
				{
				intExceptionalChange[intHPChange[i]] = 1;
				break;
				}
			case MAXIMUMMOD:
				{
				if (intHPChange[i] > intMaximumChange)
					intMaximumChange = intHPChange[i];
				break;
				}
			case TOUGHNESSMOD:
				{
				if (intHPChange[i] > intToughnessChange)
					intToughnessChange = intHPChange[i];
				break;
				}
			case ELEMENTALMOD:
				{
				if (intHPChange[i] > intElementalChange)
					intElementalChange = intHPChange[i];
				break;
				}
			case IMPROVEDELEMENTALMOD:
				{
				if (intHPChange[i] > intImprovedElementalChange)
					intImprovedElementalChange = intHPChange[i];
				break;
				}
			case GREATERELEMENTALMOD:
				{
				if (intHPChange[i] > intGreaterElementalChange)
					intGreaterElementalChange = intHPChange[i];
				break;
				}
			}
		}

	intTotalChange = 0;
	for (unsigned int i=1; i<4; i++)
		{
		if (intExceptionalChange[i] == 1)
			intTotalChange += i;
		}
	intTotalChange += intMaximumChange;
	intTotalChange += intToughnessChange;
	intTotalChange += intElementalChange;
	intTotalChange += intImprovedElementalChange;
	intTotalChange += intGreaterElementalChange;
	intTotalChange += StatChange;
	return intTotalChange;
	}

//-------------------------------------------------------------------------
int CharacterClass::GetItemSpellPointChange(int CurrentSelectedLevel)
	{
	int BaseStatSP;
    int ModStatSP;
    int StatChange;
    int intTotalChange;
	int intMaximumChange;
	int intToughnessChange;
	int intElementalChange;
	int intGreaterElementalChange;
	vector <int> intExceptionalChange;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int Index;
	int Result;
	unsigned int StaticEffectIndex;
	vector <int> intSPModType;
	vector <int> intSPChange;
	int intCount;
    bool SpellUser;
	int Classes[NUMCLASSES];

    StatChange = 0;
	intSPModType.clear();
	intSPChange.clear();
	intExceptionalChange.clear();
	for (int i=0; i<4; i++)
		{
		intExceptionalChange.push_back(0);
		}
	intMaximumChange = 0;
	intToughnessChange = 0;
	intElementalChange = 0;
	intGreaterElementalChange = 0;
	intCount =0;
    SpellUser = false;
    StatChange = 0;
	for (unsigned int i=0; i<NUMCLASSES; i++)
        Classes[i] = GetClassLevel((CLASS)i, CurrentSelectedLevel);

    //note that there are two possibilities here
    //the equipment could affect the spell points directly
    //or it could affect the stat that affects the spell points
    if (Classes[PALADIN] > 0 || Classes[RANGER] > 0 || Classes[CLERIC] > 0)
        {
        BaseStatSP = Data.CalculateAbilityModifier(GetAbility((int)WISDOM, CurrentSelectedLevel, true));
        ModStatSP = Data.CalculateAbilityModifier(GetAbility((int)WISDOM, CurrentSelectedLevel, true) + GetItemAbilityChange(WISDOM));
        StatChange += (ModStatSP - BaseStatSP) * Classes[PALADIN];
        StatChange += (ModStatSP - BaseStatSP) * Classes[RANGER];
        StatChange += (ModStatSP - BaseStatSP) * Classes[CLERIC];
        SpellUser = true;
        }
    if (Classes[WIZARD] > 0 || Classes[ARTIFICER] > 0)
        {
        BaseStatSP = Data.CalculateAbilityModifier(GetAbility((int)INTELLIGENCE, CurrentSelectedLevel, true));
        ModStatSP = Data.CalculateAbilityModifier(GetAbility((int)INTELLIGENCE, CurrentSelectedLevel, true) + GetItemAbilityChange(INTELLIGENCE));
        StatChange += (ModStatSP - BaseStatSP) * Classes[WIZARD];
        StatChange += (ModStatSP - BaseStatSP) * Classes[ARTIFICER];
        SpellUser = true;
        }
	if (Classes[SORCERER] > 0 || Classes[BARD] > 0 || Classes[FAVORED_SOUL] > 0)
        {
        BaseStatSP = Data.CalculateAbilityModifier(GetAbility((int)CHARISMA, CurrentSelectedLevel, true));
        ModStatSP = Data.CalculateAbilityModifier(GetAbility((int)CHARISMA, CurrentSelectedLevel, true) + GetItemAbilityChange(CHARISMA));
        StatChange += (ModStatSP - BaseStatSP) * Classes[SORCERER];
        StatChange += (ModStatSP - BaseStatSP) * Classes[BARD];
		StatChange += (ModStatSP - BaseStatSP) * Classes[FAVORED_SOUL];
        SpellUser = true;
        }

    if (SpellUser == false)
        return 0;

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		//we need to check if item has static effects that effect Spell Points.
		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		Index = 0;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
		while (Result == 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount++;
				}
			Index ++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		// now we need to check for Chosen effects on the equipped item.
		if (CharacterItems[i].ItemEffect1 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect2 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect3 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect4 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect5 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].ItemEffect6 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		if (CharacterItems[i].Eldritch > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
			if (ptItemEffect->GetItemEffectSPModType() != NOMOD)
				{
				intSPModType.push_back(ptItemEffect->GetItemEffectSPModType());
				intSPChange.push_back(ptItemEffect->GetItemEffectSPChange());
				intCount ++;
				}
			}
		}

	// Now to retrieve our values from the 2 vectors and total them up.
	for (int i=0; i<intCount; i++)
		{
		switch (intSPModType[i])
			{
			case EXCEPTIONALMOD:
				{
				intExceptionalChange[intSPChange[i]] = 1;
				break;
				}
			case MAXIMUMMOD:
				{
				if (intSPChange[i] > intMaximumChange)
					intMaximumChange = intSPChange[i];
				break;
				}
			case TOUGHNESSMOD:
				{
				if (intSPChange[i] > intToughnessChange)
					intToughnessChange = intSPChange[i];
				break;
				}
			case ELEMENTALMOD:
				{
				if (intSPChange[i] > intElementalChange)
					intElementalChange = intSPChange[i];
				break;
				}
			case GREATERELEMENTALMOD:
				{
				if (intSPChange[i] > intGreaterElementalChange)
					intGreaterElementalChange = intSPChange[i];
				break;
				}
			}
		}

	intTotalChange = 0;
	for (unsigned int i=1; i<4; i++)
		{
		if (intExceptionalChange[i] == 1)
			intTotalChange += i;
		}
	intTotalChange += intMaximumChange;
	intTotalChange += intToughnessChange;
	intTotalChange += intElementalChange;
	intTotalChange += intGreaterElementalChange;
	//sorcerers get bonus points from equipment (up to 2x, depending on their multiclassing)
    if (Classes[SORCERER] > 0)
        {
		intTotalChange += (int)((float)Classes[SORCERER]/(float)CurrentSelectedLevel * (float)intTotalChange);
        }
	if (Classes[FAVORED_SOUL] > 0)
		{
		intTotalChange += (int)((float)Classes[FAVORED_SOUL]/(float)CurrentSelectedLevel * (float)intTotalChange);
		}
	intTotalChange += StatChange;
	return intTotalChange;
	}

//-------------------------------------------------------------------------------------------
int CharacterClass::GetItemSkillChange(int Skill, int CurrentSelectedLevel)
	{
	int intTotalChange;
	string Name;
	ABILITIES KeyAbility;
	int SkillIndex;
	int SkillKeyAbilityValue;
	int BaseAbilityModifier;
	int ModAbilityModifier;
	int intStatChange;
	int intCompetenceChange;
	int intEnhancementChange;
	vector <int> intExceptionalChange;
	int intInsightChange;
	int intLuckChange;
	int intPenaltyChange;
	int Result;
	int Index;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	unsigned int StaticEffectIndex;
	vector <int> intSkillModType;
	vector <int> intSkillChange;
	int Result2;
	int Index2;
	int SkillModifier;
	int intCount;

	SkillIndex = Skill;
	intStatChange = 0;
	intCompetenceChange = 0;
	intEnhancementChange = 0;
	intSkillModType.clear();
	intSkillChange.clear();
	intExceptionalChange.clear();
	for (int i=0; i<4; i++)
		{
		intExceptionalChange.push_back(0);
		}
	intInsightChange = 0;
	intLuckChange = 0;
	intPenaltyChange = 0;
	intTotalChange = 0;
	intCount = 0;

    //note that there are two possibilities here
    //the equipment could affect the skill directly
    //or it could affect the stat that affects the skill
    Data.GetSkillData(SkillIndex, &Name, &KeyAbility);
    SkillKeyAbilityValue = GetAbility(KeyAbility, CurrentSelectedLevel, true);
    BaseAbilityModifier = Data.CalculateAbilityModifier(SkillKeyAbilityValue);
    SkillKeyAbilityValue += GetItemAbilityChange(KeyAbility);
    ModAbilityModifier = Data.CalculateAbilityModifier(SkillKeyAbilityValue);

    intStatChange += ModAbilityModifier - BaseAbilityModifier;

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		//we need to check if item has static effects that effect Skills.
		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		Index = 0;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
		while (Result == 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			Index ++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		// now we need to check for Chosen effects on the equipped item.
		if (CharacterItems[i].ItemEffect1 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		if (CharacterItems[i].ItemEffect2 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		if (CharacterItems[i].ItemEffect3 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		if (CharacterItems[i].ItemEffect4 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		if (CharacterItems[i].ItemEffect5 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		if (CharacterItems[i].ItemEffect6 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		if (CharacterItems[i].Eldritch >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
			while (Result2 == 0)
				{
				if (SkillModifier == Skill)
					{
					intSkillModType.push_back(ptItemEffect->GetItemEffectSkillModType(Index2));
					intSkillChange.push_back(ptItemEffect->GetItemEffectSkillChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSkillModifier(Index2, &SkillModifier);
				}
			}
		}

	// Now to retrieve our values from the 2 vectors and total them up.
	for (int i=0; i<intCount; i++)
		{
		switch (intSkillModType[i])
			{
			case COMPETENCEMOD:
				{
				if (intSkillChange[i] > intCompetenceChange)
					intCompetenceChange = intSkillChange[i];
				break;
				}
			case ENHANCEMENTMOD:
				{
				if (intSkillChange[i] > intEnhancementChange)
					intEnhancementChange = intSkillChange[i];
				break;
				}
			case EXCEPTIONALMOD:
				{
				intExceptionalChange[intSkillChange[i]] = 1;
				break;
				}
			case INSIGHTMOD:
				{
				if (intSkillChange[i] >intInsightChange)
					intInsightChange = intSkillChange[i];
				break;
				}
			case LUCKMOD:
				{
				if (intSkillChange[i] > intLuckChange)
					intLuckChange = intSkillChange[i];
				break;
				}
			case PENALTYMOD:
				{
				if (intSkillChange[i] > intPenaltyChange)
					intPenaltyChange = intSkillChange[i];
				break;
				}
			}
		}

	intTotalChange = 0;
	intTotalChange += intCompetenceChange;
	intTotalChange += intEnhancementChange;
	for (unsigned int i=1; i<4; i++)
		{
		if (intExceptionalChange[i] == 1)
			intTotalChange += i;
		}
	intTotalChange += intInsightChange;
	intTotalChange += intLuckChange;
	intTotalChange += intPenaltyChange;
	intTotalChange += intStatChange;
	return intTotalChange;
	}

//--------------------------------------------------------------------------------------------
int CharacterClass::GetItemSaveChange(SAVETYPE Save, int CurrentSelectedLevel)
	{
	int intTotalChange;
	string Name;
	ABILITIES KeyAbility;
	int SaveIndex;;
	int BaseSave;
	int ModSave;
	int intStatChange;
	int intCompetenceChange;
	int intEnhancementChange;
	vector <int> intExceptionalChange;
	vector <int> intEpicChange;
	int intInsightChange;
	int intLuckChange;
	int intPenaltyChange;
	int intResistanceChange;
	int Result;
	int Index;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	unsigned int StaticEffectIndex;
	vector <int> intSaveModType;
	vector <int> intSaveChange;
	int Result2;
	int Index2;
	int SaveModifier;
	int intCount;

	SaveIndex = Save;
	intStatChange = 0;
	intCompetenceChange = 0;
	intEnhancementChange = 0;
	intSaveModType.clear();
	intSaveChange.clear();
	intExceptionalChange.clear();
	intEpicChange.clear();
	for (int i=0; i<4; i++)
		{
		intExceptionalChange.push_back(0);
		intEpicChange.push_back(0);
		}
	intInsightChange = 0;
	intLuckChange = 0;
	intPenaltyChange = 0;
	intResistanceChange = 0;
	intTotalChange = 0;
	intCount = 0;

    //note that there are two possibilities here
    //the equipment could affect the save directly
    //or it could affect the stat that affects the save
    if (Save == FORTITUDESAVE)
        KeyAbility = CONSTITUTION;
    else if (Save == REFLEXSAVE)
        KeyAbility = DEXTERITY;
    else if (Save == WILLSAVE)
        KeyAbility = WISDOM;
    BaseSave = Data.CalculateAbilityModifier(GetAbility((int)KeyAbility, CurrentSelectedLevel, true));
    ModSave = Data.CalculateAbilityModifier(GetAbility((int)KeyAbility, CurrentSelectedLevel, true) + GetItemAbilityChange(KeyAbility));

    intStatChange += ModSave - BaseSave;

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		//we need to check if item has static effects that effect Saves.
		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		Index = 0;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
		while (Result == 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			Index ++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		// now we need to check for Chosen effects on the equipped item.
		if (CharacterItems[i].ItemEffect1 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		if (CharacterItems[i].ItemEffect2 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		if (CharacterItems[i].ItemEffect3 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		if (CharacterItems[i].ItemEffect4 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		if (CharacterItems[i].ItemEffect5 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		if (CharacterItems[i].ItemEffect6 >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		if (CharacterItems[i].Eldritch >0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
			Index2 = 0;
			Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
			while (Result2 == 0)
				{
				if (SaveModifier == Save)
					{
					intSaveModType.push_back(ptItemEffect->GetItemEffectSaveModType(Index2));
					intSaveChange.push_back(ptItemEffect->GetItemEffectSaveChange(Index2));
					intCount ++;
					}
				Index2 ++;
				Result2 = ptItemEffect->GetItemEffectSaveModifier(Index2, &SaveModifier);
				}
			}
		}

	// Now to retrieve our values from the 2 vectors and total them up.
	for (int i=0; i<intCount; i++)
		{
		switch (intSaveModType[i])
			{
			case COMPETENCEMOD:
				{
				if (intSaveChange[i] > intCompetenceChange)
					intCompetenceChange = intSaveChange[i];
				break;
				}
			case ENHANCEMENTMOD:
				{
				if (intSaveChange[i] > intEnhancementChange)
					intEnhancementChange = intSaveChange[i];
				break;
				}
			case EXCEPTIONALMOD:
				{
				intExceptionalChange[intSaveChange[i]] = 1;
				break;
				}
			case INSIGHTMOD:
				{
				if (intSaveChange[i] >intInsightChange)
					intInsightChange = intSaveChange[i];
				break;
				}
			case LUCKMOD:
				{
				if (intSaveChange[i] > intLuckChange)
					intLuckChange = intSaveChange[i];
				break;
				}
			case PENALTYMOD:
				{
				if (intSaveChange[i] > intPenaltyChange)
					intPenaltyChange = intSaveChange[i];
				break;
				}
			case RESISTANCEMOD:
				{
				if (intSaveChange[i] > intResistanceChange)
					intResistanceChange = intSaveChange[i];
				break;
				}
			case EPICMOD:
				{
				intEpicChange[intSaveChange[i]] = 1;
				break;
				}
			}
		}

	intTotalChange = 0;
	intTotalChange += intCompetenceChange;
	intTotalChange += intEnhancementChange;
	for (unsigned int i=1; i<4; i++)
		{
		if (intExceptionalChange[i] == 1 || intEpicChange[i] == 1)
			intTotalChange += i;
		}
	intTotalChange += intInsightChange;
	intTotalChange += intLuckChange;
	intTotalChange += intPenaltyChange;
	intTotalChange += intResistanceChange;
	intTotalChange += intStatChange;
	return intTotalChange;
	}

//----------------------------------------------------------------------------
unsigned int CharacterClass::GetCharacterItemsSize()
	{
	return CharacterItems.size();
	}

//------------------------------------------------------------------------------
int CharacterClass::GetACMod(ACMODS ModType, int AtLevel)
	{
	int BaseAC;
	int NewAC;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int Index;
	int Result;
	unsigned int StaticEffectIndex;

	switch (ModType)
		{
		case ACMOD_BASE:
			{
			return 10;
			}

		case ACMOD_ARMOR:
			{
			BaseAC = 0;
			for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
				{
				if (CharacterItemsEquipped[i] == -1)
					continue;
				ptItem = Data.GetItemPointer(CharacterItems[CharacterItemsEquipped[i]].ItemIndex);
				//get the base AC of this item
				NewAC = ptItem->GetBaseAC();

				//TODO: This stacks everything. We need to fix it such that it does not stack
				//like bonuses.

				//get any bonus ACs from the static effects
				Index = 0;
				Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
				while (Result == 0)
					{
					ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
					NewAC += ptItemEffect->GetItemEffectACChange();
					Index ++;
					Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
					}

				//get any bonus ACs from crafted effects
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
				NewAC += ptItemEffect->GetItemEffectACChange();
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
				NewAC += ptItemEffect->GetItemEffectACChange();
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
				NewAC += ptItemEffect->GetItemEffectACChange();
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
				NewAC += ptItemEffect->GetItemEffectACChange();
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
				NewAC += ptItemEffect->GetItemEffectACChange();
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
				NewAC += ptItemEffect->GetItemEffectACChange();
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
				NewAC += ptItemEffect->GetItemEffectACChange();

				if (NewAC > BaseAC)
					BaseAC = NewAC;
				}
			return BaseAC;
			}

		case ACMOD_SHIELD:
			{
			}
		case ACMOD_DEX:
			{
			}
		case ACMOD_WIS:
			{
			}
		case ACMOD_NATURAL:
			{
			}
		case ACMOD_SIZE:
			{
			if (GetRace() == HALFLING)
				return 1;
			if (GetRace() == GNOME)
				return 1;
			if (GetRace() == DEEPGNOME)
				return 1;
			else
				return 0;
			}
		case ACMOD_LUCK:
			{
			return 0; //the only source of luck is a spell (recitation), which the planner does not deal with (temporary bonus)
			}
		case ACMOD_DEFLECTION:
			{
			}
		case ACMOD_INSIGHT:
			{
			}
		case ACMOD_CENTERED:
			{
			}
		case ACMOD_MISC:
			{
			}
		case ACMOD_DODGE:
			{
			}
		case ACMOD_TOTAL:
			{
			}
		}

	return 0;
	}

//------------------------------------------------------------------------------
int CharacterClass::GetItemBaseAC(string Type)
	{
	int BaseAC;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int Index;
	int Result;

	unsigned int StaticEffectIndex;
	BaseAC = 0;
	Index = 0;

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		if (Type == "Armor")
			{
			switch (ptItem->GetItemType())
				{
				case PADDEDARMOR:
				case LEATHERARMOR:
				case STUDDEDLEATHERARMOR:
				case CHAINSHIRTARMOR:
				case HIDEARMOR:
				case SCALEMAILARMOR:
				case CHAINMAILARMOR:
				case BREASTPLATEARMOR:
				case BRIGADINEARMOR:
				case SPLINTMAILARMOR:
				case BANDEDMAILARMOR:
				case HALFPLATEARMOR:
				case FULLPLATEARMOR:
					{
					BaseAC = ptItem->GetBaseAC();
					Index = 0;
					Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
					while (Result == 0)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (ptItemEffect->GetItemEffectACModType() == BONUSMOD)
							{
							BaseAC += ptItemEffect->GetItemEffectACChange();
							}
						Index ++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}
					if (CharacterItems[i].ItemEffect1 > 0)
						{
						ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
						if (ptItemEffect->GetItemEffectACModType() == BONUSMOD)
							{
							BaseAC += ptItemEffect->GetItemEffectACChange();
							}
						}
					return BaseAC;
					break;
					}
				}
			}
		else if (Type == "Shield")
			{ 
			switch(ptItem->GetItemType())
				{
				case SMALLSHIELD:
				case LARGESHIELD:
				case TOWERSHIELD:
				case BUCKLER:
					{
					BaseAC = ptItem->GetBaseAC();
					Index = 0;
					Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
					while (Result == 0)
						{
						ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
						if (ptItemEffect->GetItemEffectACModType() == BONUSMOD)
							{
							BaseAC += ptItemEffect->GetItemEffectACChange();
							}
						Index ++;
						Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
						}
					if (CharacterItems[i].ItemEffect1 > 0)
						{
						ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
						if (ptItemEffect->GetItemEffectACModType() == BONUSMOD)
							{
							BaseAC += ptItemEffect->GetItemEffectACChange();
							}
						}
					return BaseAC;
					break;
					}
				}
			}
		else if (Type == "Docent")
			{
			Index = 0;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			while (Result == 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
				if (ptItemEffect->GetItemEffectACModType() == BONUSMOD)
					{
					BaseAC += ptItemEffect->GetItemEffectACChange();
					}
				Index ++;
				Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
				}
			if (CharacterItems[i].ItemEffect1 > 0)
				{
				ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
				if (ptItemEffect->GetItemEffectACModType() == BONUSMOD)
					{
					BaseAC += ptItemEffect->GetItemEffectACChange();
					}
				}
			return BaseAC;
			break;
			}
		}
	return 0;
	}
			
//------------------------------------------------------------------------------
int CharacterClass::GetItemACChange(MODTYPE ACType)
	{
	int TotalACChange;
	ItemClass *ptItem;
	ItemEffectClass *ptItemEffect;
	int Index;
	int Result;
	unsigned int StaticEffectIndex;
	vector <int> ACChanges;
	vector <int> ACDodgeValues;

	TotalACChange = 0;
	Index = 0;

	ACChanges.clear();
	
	
	int WarforgedAC; //Special instances for Warforged Composite Plating and "Body" feats
	WarforgedAC = 0; // that are also used if we have a docent equipped.
	if (GetRace() == WARFORGED && ACType == ARMORMOD)
		{//These are considered Armor modifications and do not stack with equipment except docents
		if (HasFeat("Adamantine Body", 20))
			WarforgedAC = 8;
		else if (HasFeat("Mithral Body", 20))
			WarforgedAC = 5;
		else //Warforged standard Composite Plating adds +2AC but does not stack with other "Body" feats
			WarforgedAC = 2;		
		WarforgedAC += GetItemBaseAC("Docent");
		}

	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		//check if static effects of equipped item has an effect that affects AC
		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		Index = 0;
		Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
		while (Result == 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(StaticEffectIndex);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			Index ++;
			Result = ptItem->GetItemStaticEffectIndex(Index, &StaticEffectIndex);
			}
		if (CharacterItems[i].ItemEffect1 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect1);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		if (CharacterItems[i].ItemEffect2 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect2);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		if (CharacterItems[i].ItemEffect3 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect3);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		if (CharacterItems[i].ItemEffect4 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect4);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		if (CharacterItems[i].ItemEffect5 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect5);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		if (CharacterItems[i].ItemEffect6 > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].ItemEffect6);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		if (CharacterItems[i].Eldritch > 0)
			{
			ptItemEffect = Data.GetItemEffectPointer(CharacterItems[i].Eldritch);
			if (ptItemEffect->GetItemEffectACModType() == ACType)
				{
				ACChanges.push_back(ptItemEffect->GetItemEffectACChange());
				}
			}
		}

	// Now to retreive our values from the vector and total them up.
	if (ACType == DODGEMOD) //dodge bonuses are calculated differently.
		{
		for (int i=0; i<10; i++)
			{
			ACDodgeValues.push_back(0);
			}
		for (unsigned int j=0; j<ACChanges.size(); j++)
			{
			if (ACDodgeValues[ACChanges[j]] == 0)
				{
				TotalACChange += ACChanges[j];
				ACDodgeValues[ACChanges[j]] = 1;
				}
			}
		}
	else // All other bonus types.
		{
		TotalACChange += WarforgedAC; //We have already set this to zero and only increase it if we're warforged, which we checked
		for (unsigned int i=0; i<ACChanges.size(); i++)
			{
			if (ACChanges[i] > TotalACChange)
				TotalACChange = ACChanges[i];
			}
		}

	return TotalACChange;
	}

//----------------------------------------------------------------------------
int CharacterClass::GetArmorClassFeats(unsigned int CurrentSelectedLevel)
	{
	int FeatBonus;
	ItemClass *ptItem;
	bool MonkItemsEquipped;
	int MonkLevels;

	FeatBonus = 0;
	if (HasFeat("Dodge", CurrentSelectedLevel) == true)
        FeatBonus++;
	if (HasFeat("Halfling Size Bonus", CurrentSelectedLevel) == true)
		FeatBonus++;
	if (HasFeat("Bulwark of Defense", CurrentSelectedLevel) == true)
		FeatBonus += 4;

	//There is a special case for the automatic Monk AC Bonus Feat as long as we aren't wearing cumbersome stuff
	MonkLevels = GetNumClassLevels(MONK); // because the bonus AC for Monks is incremented.
	//To be "centered" we have to check that we don't have more than Cloth Armor equipped...
	if (MonkLevels >= 1) //Are we really a monk?
		{
		MonkItemsEquipped = true; //Set it to true in case we have nothing equipped.
		if (HasFeat("Adamantine Body", CurrentSelectedLevel) == true || HasFeat("Mithral Body", CurrentSelectedLevel) == true)
			MonkItemsEquipped = false; //Warforged don't get the bonus if they have either of the "Body" feats, as those count as heavier armor types.

			for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
				{
				if (CharacterItemsEquipped[i] == -1)
					continue;

				ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
					switch (ptItem->GetItemType())
						{// as long as it isn't one of these:
						case PADDEDARMOR:
						case LEATHERARMOR:
						case STUDDEDLEATHERARMOR:
						case CHAINSHIRTARMOR:
						case HIDEARMOR:
						case SCALEMAILARMOR:
						case CHAINMAILARMOR:
						case BREASTPLATEARMOR:
						case BRIGADINEARMOR:
						case SPLINTMAILARMOR:
						case BANDEDMAILARMOR:
						case HALFPLATEARMOR:
						case FULLPLATEARMOR:
						case BUCKLER:
						case SMALLSHIELD:
						case LARGESHIELD:
						case TOWERSHIELD:
							{
							MonkItemsEquipped = false;
							break;
							}
						}
				}

		//If we've varified that we are wearing the right stuff we can then add the correct amount of AC based on our MonkLevels
		if (MonkItemsEquipped == true)
			{// at a rate of +1 every fifth level and starting at +1 at 1st level.
			if (MonkLevels < 5)
				FeatBonus += 1;
			else if (MonkLevels >=5 && MonkLevels < 10)
				FeatBonus += 2;
			else if (MonkLevels >=10 && MonkLevels < 15)
				FeatBonus += 3;
			else if (MonkLevels >=15 && MonkLevels < 20)
				FeatBonus += 4;
			else if (MonkLevels ==20)
				FeatBonus += 5;
			}
		}
		
	return FeatBonus;
	}

//----------------------------------------------------------------------------
int CharacterClass::GetACDexBonus()
	{
	int MaxDexBonus;
	int MaxDexArmorBonus;
	int MaxDexShieldBonus;
	int DexBonus;
	ItemClass *ptItem;
	int Index;
	int Ability;
	int EquipAbility;
	int Modifier;

	Index = 0;
	MaxDexShieldBonus = 99;
	DexBonus = 0;
	//Warforged "Body" feats have max dex bonuses
	if (HasFeat("Adamantine Body", 20) == true)
		MaxDexArmorBonus = 1;
	else if (HasFeat("Mithral Body", 20) == true)
		MaxDexArmorBonus = 5;
	else
		MaxDexArmorBonus = 99;
	
	for (unsigned int i=0; i<NUMCHAREQUPMENTSLOTS; i++)
		{
		if (CharacterItemsEquipped[i] == -1)
			continue;

		ptItem = Data.GetItemPointer(CharacterItems[i].ItemIndex);
		switch (ptItem->GetItemType())
			{
			case PADDEDARMOR:
			case LEATHERARMOR:
			case STUDDEDLEATHERARMOR:
			case CHAINSHIRTARMOR:
			case HIDEARMOR:
			case SCALEMAILARMOR:
			case CHAINMAILARMOR:
			case BREASTPLATEARMOR:
			case BRIGADINEARMOR:
			case SPLINTMAILARMOR:
			case BANDEDMAILARMOR:
			case HALFPLATEARMOR:
			case FULLPLATEARMOR:
				{
				MaxDexArmorBonus = ptItem->GetMaxDex();
				break;
				}
			case SMALLSHIELD:
			case LARGESHIELD:
			case TOWERSHIELD:
			case BUCKLER:
				{
				MaxDexShieldBonus = ptItem->GetMaxDex();
				break;
				}
			}
		}
	//Compare Max Dex bonus for Shields & Armor and take the lesser one.
	if (MaxDexArmorBonus < MaxDexShieldBonus)
		MaxDexBonus = MaxDexArmorBonus;
	else 
		MaxDexBonus = MaxDexShieldBonus;
	//Now we need to compare this to how much Dex Bonus the Character has
	Ability = GetAbility((int)DEXTERITY, 20, true) + GetTomeRaise(DEXTERITY, 20, true);
	EquipAbility = GetItemAbilityChange(DEXTERITY);
	Modifier = Data.CalculateAbilityModifier((Ability + EquipAbility));
	if (Modifier < MaxDexBonus)
		DexBonus = Modifier;
	else 
		DexBonus = MaxDexBonus;

	return DexBonus;
	}

//----------------------------------------------------------------------------
int CharacterClass::GetPaladinAuraAC(unsigned int CurrentSelectedLevel)
	{
	int PaladinAuraAC; //An integer to hold the total AC Mod from our Paladin Aura
	PaladinAuraAC = 0; // initialized to zero in case we don't have one.
	if (HasFeat("Aura of Good", CurrentSelectedLevel) == true)
		{
		PaladinAuraAC +=1;
		}

	return PaladinAuraAC;
	}

//---------------------------------------------------------------------------
void CharacterClass::GetRageData(unsigned int CurrentSelectedLevel, int *RagesPerDay, int *Duration, int *StrBonus, int *ConBonus, int *WillBonus, int *ACPenalty)
	{
	int BarbarianLevel;
	int Con;
	int ConMod;
	float Multiplier;

	BarbarianLevel = GetClassLevel(BARBARIAN, CurrentSelectedLevel);

	if (BarbarianLevel == 0)
		{
		*RagesPerDay = 0;
		*Duration = 0;
		*StrBonus = 0;
		*ConBonus = 0;
		*WillBonus = 0;
		*ACPenalty = 0;
		return;
		}

	//number of rages per day
	*RagesPerDay = (BarbarianLevel / 4) + 1;
	if (HasFeat("Past Life: Berserker's Fury", CurrentSelectedLevel))
		*RagesPerDay++;

	//str bonus
	if (HasFeat("Rage", CurrentSelectedLevel))
		*StrBonus = 4;
	if (HasFeat("Greater Rage", CurrentSelectedLevel))
		*StrBonus = 6;
	if (HasFeat("Mighty Rage", CurrentSelectedLevel))
		*StrBonus = 8;
 
	//con bonus
	if (HasFeat("Rage", CurrentSelectedLevel))
		*ConBonus = 4;
	if (HasFeat("Greater Rage", CurrentSelectedLevel))
		*ConBonus = 6;
	if (HasFeat("Mighty Rage", CurrentSelectedLevel))
		*ConBonus = 8;

	//duration
	//first figure out our rage enhanced con
	Con = GetAbility(CONSTITUTION, CurrentSelectedLevel, true, true, true);
	Con += *ConBonus;
	ConMod = Data.CalculateAbilityModifier(Con);
	*Duration = 18 + 6 * ConMod;
	Multiplier = 1.00;
	*Duration = static_cast<int>(*Duration * Multiplier);

	//will bonus
	if (HasFeat("Rage", CurrentSelectedLevel))
		*WillBonus = 2;
	if (HasFeat("Greater Rage", CurrentSelectedLevel))
		*WillBonus = 3;
	if (HasFeat("Mighty Rage", CurrentSelectedLevel))
		*WillBonus = 4;

	//AC Penalty
	if (HasFeat("Rage", CurrentSelectedLevel))
		*ACPenalty = -2;
	}
	
//---------------------------------------------------------------------------
void CharacterClass::GetTurnData(unsigned int CurrentSelectedLevel, int *TurnsPerDay, int *Check, int *Damage)
	{
	int EffectiveClericLevel;
	int PaladinLevel;

	if (!HasFeat("Turn Undead", CurrentSelectedLevel))
		{
		*TurnsPerDay = 0;
		*Check = 0;
		*Damage = 0;
		return;
		}

	//turns per day
	*TurnsPerDay = 3 + CalculateTotalAbilityMod(CHARISMA, CurrentSelectedLevel);

	//check (the actual value is 1D20 + charisma modifier. We are only going to return the modifier)
	*Check = CalculateTotalAbilityMod(CHARISMA, CurrentSelectedLevel);

	//damage (the actual value is 2D6 + charasma modifier + effective cleric level. We will return the sum of the last two)
	EffectiveClericLevel = GetClassLevel(CLERIC, CurrentSelectedLevel);
	PaladinLevel = GetClassLevel(PALADIN, CurrentSelectedLevel);
	if (PaladinLevel > 3)
		EffectiveClericLevel += PaladinLevel - 3;
	*Damage = EffectiveClericLevel + *Check;
	if (HasFeat("Improved Turning", CurrentSelectedLevel))
		*Damage++;
	}

//---------------------------------------------------------------------------
void CharacterClass::ValidateCharacterEnhancements(string ActionType, int atLevel)
	{
	bool FeatChange;
	bool RemoveAAElf;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	Data_Enhancement_Class *Enhancement2;
	CLASS ClassList[3];
	int MaxLevel;
	bool ValidTree;
	int PossibleTreesCount;
	bool EnhancementsUnselected;
	int EnhancementIndex;
	int APSpent;
	int RequiredLevel;
	int RequiredSlot;
	int RequiredRank;
	string RequiredName;
	bool RemoveEnhancement;
	bool DeselectEnhancement;

	//Lets see if Enhancements even need to be changed.
	if (CharacterEnhancements.GetTreeIndex(0) == ENHT_NOTREE)
		return;

	FeatChange = false;
	RemoveAAElf = false;
	MaxLevel = 0;
	EnhancementsUnselected = false;
	RequiredLevel = 0;
	RequiredSlot = 0;
	RequiredRank = 0;
	RequiredName = "";
	RemoveEnhancement = false;
	DeselectEnhancement = false;

	if (ActionType == "Race")
		{
		EnhancementTree = Data.GetEnhancementTreePointer(CharacterEnhancements.GetTreeIndex(0));
		if (EnhancementTree->GetTreeRace() != GetRace())
			{
			//Lets check to see if we will need to remove any speical trees
			if (EnhancementTree->GetTreeIndex() == ENHT_ELF || EnhancementTree->GetTreeIndex() == ENHT_HALF_ELF || EnhancementTree->GetTreeIndex() == ENHT_MORNINGLORD)
				RemoveAAElf = true;
			
			//Lets change our race tree now.
			CharacterEnhancements.ClearCharacterEnhancementSlots(0);
			CharacterEnhancements.SetTreeIndex(0, Data.GetRacialTree(GetRace()));
			EnhancementsUnselected = true; //since we changed races, some feats could of changed.
			}
		}
	if (ActionType == "Class" || RemoveAAElf == true)
		{
		//lets get our Class list and max Level
		ClassList[0] = ClassRecord[0];
		ClassList[1] = CLASSNONE;
		ClassList[2] = CLASSNONE;
		for (unsigned int i=1; i<20; i++)
			{
			if (ClassRecord[i] == CLASSNONE)
				{
				MaxLevel = i;
				break;
				}
			if (i == 19)
				MaxLevel = 20;
			for (unsigned int j=0; j<3; j++)
				{
				if (ClassList[j] == ClassRecord[i])
					break;
				else if (ClassList[j] == CLASSNONE)
					{
					ClassList[j] = ClassRecord[i];
					break;
					}
				}
			}
		//ok lets find out if we need to remove any Trees
		ValidTree = false;
		for (unsigned int i=0; i<7; i++)
			{
			EnhancementTree = Data.GetEnhancementTreePointer(CharacterEnhancements.GetTreeIndex(i));
			//check to see if tree is a Class Tree, if it is then check to see if it needs to be removed.
			if (EnhancementTree->GetTreeType() == ENHTT_CLASS || EnhancementTree->GetTreeType() == ENHTT_SPECIAL)
				{
				for (unsigned int j=0; j<3; j++)
					{
					if (EnhancementTree->GetTreeClass() == ClassList[j])
						{
						ValidTree = true;
						break;
						}
					}
				if (RemoveAAElf == true && EnhancementTree->GetTreeIndex() == ENHT_ARCANE_ARCHER_ELF)
					ValidTree = false;
				if (RemoveAAElf == false && EnhancementTree->GetTreeIndex() == ENHT_ARCANE_ARCHER_ELF)
					ValidTree = true;

				if (ValidTree == false)
					{
					//we need to remove this tree
					PossibleTreesCount = 1;
					for (int k=0; k<3; k++)
						{
						PossibleTreesCount += Data.GetClassEnhancementTreeCount(ClassList[k]);
						}
					if (PossibleTreesCount  > 6)
						{
						//Set Tree to Unset Tree
						CharacterEnhancements.SetTreeIndex(i, ENHT_UNSET);
						CharacterEnhancements.ClearCharacterEnhancementSlots(i);
						}
					else
						{
						// we need to move trees
						for (int x=i; x<7; x++)
							{
							if (x !=6)
								{
								CharacterEnhancements.SetTreeIndex(x, CharacterEnhancements.GetTreeIndex(x+1));
								CharacterEnhancements.ClearCharacterEnhancementSlots(x);
								CharacterEnhancements.CopyCharacterEnhancementSlots(x, x+1);
								}
							else
								{
								CharacterEnhancements.ClearCharacterEnhancementSlots(x);
								CharacterEnhancements.SetTreeIndex(x, ENHT_NOTREE);
								}
							}
						}
					//ok now that we have moved trees, we need to check this tree again unless we were in last tree.
					if (i !=6)
						i--;
					}
				}
			}
		//Need to remove any enhancements that don't meet Class Level Requirements anymore.
		//We only need to check class trees so we can skip the Race Tree which should always
		//be in the '0' location of trees.
		for (unsigned int xtree=1; xtree<7; xtree++)
			{
			EnhancementTree = Data.GetEnhancementTreePointer(CharacterEnhancements.GetTreeIndex(xtree));
			for (unsigned int xlevel=0; xlevel<6; xlevel++)
				{
				for (unsigned int xslot=0; xslot<6; xslot++)
					{
					if (CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot) > 0)
						{
						//ok this enhancements has ranks in it so we need to verify that we meet the class level
						//of this enhancement requirement at the levels the ranks were taken.
						EnhancementIndex = CharacterEnhancements.GetEnhancementIndex(xtree, xlevel, xslot, CharacterEnhancements.GetEnhancementIndexChosen(xtree, xlevel, xslot));
						Enhancement = EnhancementTree->GetEnhancementPointer(EnhancementIndex);
						for (unsigned int x=CharacterEnhancements.GetRanksTaken(xtree,xlevel,xslot); x>0; x--)
							{
							if (Enhancement->GetClassLevelRequirement() > GetClassLevel(EnhancementTree->GetTreeClass(), CharacterEnhancements.GetLevelTaken(xtree,xlevel,xslot,x-1)))
								{
								//ok we didn't meet the class level requirements for this rank so we need deselect this rank.
								EnhancementsUnselected = true;
								CharacterEnhancements.SetLevelTaken(xtree,xlevel,xslot, x-1, 0);
								CharacterEnhancements.SetRanksTaken(xtree, xlevel, xslot, CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot)-1);
								if (CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot) == 0)
									CharacterEnhancements.SetEnhancementIndexChosen(xtree, xlevel, xslot, 0);
								}
							}
						}
					} //end for xslot
				} //end for xlevel
			} // end for xtree
		}

		if (EnhancementsUnselected == true || ActionType == "Feat")
		{
		//since we unselected enhancement because of Class or Feat changes we need to see if other enhancements
		//need to be unselected because of those changes.
		for (int xtree=0; xtree<7; xtree++)
			{
			while (EnhancementsUnselected)
				{
				//Ok lets check the AP Requirements of this tree's Enhancements.
				EnhancementsUnselected = false;
				APSpent = 0;
				EnhancementTree = Data.GetEnhancementTreePointer(CharacterEnhancements.GetTreeIndex(xtree));
				for (int xlevel=0; xlevel<6; xlevel++)
					{
					for (int xslot=0; xslot<6; xslot++)
						{
						if (CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot) > 0)
							{
							//ok we have points spent into the enhancements so lets get the point cost
							EnhancementIndex = CharacterEnhancements.GetEnhancementIndex(xtree,xlevel,xslot,CharacterEnhancements.GetEnhancementIndexChosen(xtree,xlevel,xslot));
							Enhancement = EnhancementTree->GetEnhancementPointer(EnhancementIndex);
							if (Enhancement->GetAPRequirement() > APSpent)
								{
								//Ok lets remove all ranks from this enhancements as it doesn't meet requirements
								CharacterEnhancements.SetEnhancementIndexChosen(xtree, xlevel, xslot,0);
								CharacterEnhancements.SetRanksTaken(xtree, xlevel, xslot, 0);
								CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, 0, 0);
								CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, 1, 0);
								CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, 2, 0);
								}
							else
								APSpent = APSpent + (Enhancement->GetEnhancementCost() * CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot));
							}
						}
					}
				//ok lets check our Enhancement Requirements now.
				for (int xlevel=0; xlevel<6; xlevel++)
					{
					for (int xslot=0; xslot<6; xslot ++)
						{
						if (CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot) > 0)
							{
							EnhancementIndex = CharacterEnhancements.GetEnhancementIndex(xtree, xlevel, xslot, CharacterEnhancements.GetEnhancementIndexChosen(xtree, xlevel, xslot));
							Enhancement = EnhancementTree->GetEnhancementPointer(EnhancementIndex);
							// Lets check to see if we meet our Requirement Criteria
							for (unsigned int i=0; i<Enhancement->GetRequirementSize(CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot)); i++)
								{
								switch (Enhancement->GetRequirementType(CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot), i))
									{
									RequiredLevel = Enhancement->GetRequirementLevel(CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot), i);
									RequiredSlot = Enhancement->GetRequirementSlot(CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot), i);
									RequiredRank = Enhancement->GetRequirementRank(CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot), i);
									RequiredName = Enhancement->GetRequirementName(CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot), i);
									case ENH_ENHANCEMENT:
										{
										if (CharacterEnhancements.GetRanksTaken(xtree, RequiredLevel, RequiredSlot) > 0)
											{
											EnhancementIndex = CharacterEnhancements.GetEnhancementIndex(xtree, RequiredLevel, RequiredSlot, CharacterEnhancements.GetEnhancementIndexChosen(xtree, RequiredLevel, RequiredSlot));
											Enhancement2 = EnhancementTree->GetEnhancementPointer(EnhancementIndex);
											if (Enhancement2->GetEnhancementName() == RequiredName)
												{
												if (CharacterEnhancements.GetRanksTaken(xtree, RequiredLevel, RequiredSlot) < RequiredRank)
													DeselectEnhancement = true;
												}
											else
												RemoveEnhancement = true;
												break;
											}
										else
											RemoveEnhancement = true;
										break;
										}
									case ENH_MULTIENHANCEMENT:
										{
										if (CharacterEnhancements.GetEnhancementIndexChosen(xtree, RequiredLevel, RequiredSlot) == 0)
											RemoveEnhancement = true;
										else
											{
											if (CharacterEnhancements.GetRanksTaken(xtree, RequiredLevel, RequiredSlot) < RequiredRank)
												DeselectEnhancement = true;
											}
										break;
										}
									case ENH_FEAT:
										{
										if (!HasFeat(RequiredName, CharacterEnhancements.GetLevelTaken(xtree, xlevel, xslot, CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot)-1)))
											DeselectEnhancement = true;
										break;
										}
									default:
										break;
									} //end switch
								if (DeselectEnhancement)
									{
									if (CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot) > 1)
										{
										//Deselect a rank
										CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot)-1, 0);
										CharacterEnhancements.SetRanksTaken(xtree, xlevel, xslot, CharacterEnhancements.GetRanksTaken(xtree, xlevel, xslot)-1);
										//since we only deselected a rank in this enhancement, we need to recheck this enhancement again.
										i--;
										continue;
										}
									else
										RemoveEnhancement = true;
									}
								if (RemoveEnhancement)
									{
									//Remove Enhancement
									CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, 0, 0);
									CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, 1, 0);
									CharacterEnhancements.SetLevelTaken(xtree, xlevel, xslot, 2, 0);
									CharacterEnhancements.SetRanksTaken(xtree, xlevel, xslot, 0);
									CharacterEnhancements.SetEnhancementIndexChosen(xtree, xlevel, xslot, 0);
									//since we removed an enhancement, we will need to run through the while loop again.
									EnhancementsUnselected = true;
									break;
									}
								}//end for loop - Requirement check

							}// end if RanksTaken > 0
						}//end for xslot loop

					}//end for xlevel loop

				} // end while loop
			}// end for xtree

		}//end if enhancementunselected = true
	}

//---------------------------------------------------------------------------
bool FeatCompare(FeatListStruct F1, FeatListStruct F2)
    {
    return F1.FeatIndex < F2.FeatIndex;
    }
//---------------------------------------------------------------------------
int CharacterClass::GetRaceEnhancement()
{
	return RaceEnhancement;
}
