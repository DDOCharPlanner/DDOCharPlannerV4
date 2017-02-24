//---------------------------------------------------------------------------
#pragma once

#include "stdafx.h"
#include "Character_Enhancements_Class.h"
#include "Character_Destinies_Class.h"

struct FeatListStruct
    {
    int Level;
    int FeatIndex;
    FEATSLOTTYPE FeatAquireType;
    };

struct SpellListStruct
    {
    int Level;
    int SpellIndex;
    int SpellSlot;
    SPELLTYPE SpellAquireType;
    };

//---------------------------------------------------------------------------
class CharacterClass
    {
    public:
        CharacterClass();
        virtual ~CharacterClass();

        void Reset();
        string GetInstructionString(int CurrentSelectedLevel, int Index, int *Value);
        void Save(HWND hwnd);
        void Load(HWND hwnd);
		string GetErrorList();
		bool GetLevelError(unsigned int Level);
		void EnableValidations(bool NewSetting);
		int GetHighestBuildLevel();
		
		//name/sex/race/alignment
        void GetName(string *First, string *Sur);
        void SetName(string First, string Sur);
        RACE GetRace();
        void SetRace(RACE NewRace);
		string GetRaceString(bool GetPlural=false);
		SEX GetSex();
        void SetSex(SEX NewSex);
        ALIGNMENT GetAlignment();
        void SetAlignment(ALIGNMENT NewAlignment);
        bool IsAlignmentLegal(ALIGNMENT Test);

		//class
        CLASS GetClass(int AtLevel, bool Change = true);
        void SetClass(CLASS NewClass, int AtLevel);
        void GetMulticlassClasses(int AtLevel, CLASS *Class);
        int GetNumClassLevels(CLASS Class);
        int GetClassLevel(int CurrentSelectedLevel);
        int GetClassLevel(CLASS ClassType, int CurrentSelectedLevel);
        int GetCharacterLevelAtClassLevel(CLASS ClassType, int ClassLevel);
		string GetClassString(int AtLevel);
		
        //ability stuff
        int CalculateTotalAbilityPoints();
        int GetAbility(int AbilityIndex, int AtLevel, bool IncludeTome = true, bool IncludeEnhancements = false, bool IncludeEquipment = false, bool IncludeFeats = true);
		int GetAbilityMod(ABILITIES Ability, ABILITYMODS ModType, int AtLevel);
        int GetAbilityCost(int AbilityIndex);
        int GetAbilityPointsSpent(int AbilityIndex);
        void AdjustAbilityRaise(int AbilityIndex, int Direction);
		int GetAbilityRaise(int AbilityIndex);
        void SetAbilityIncrease(int AtLevel, ABILITIES Ability);
        ABILITIES GetAbilityIncrease(int AtLevel);
        void SetAbilityFavorBonus(bool NewSetting);
        bool GetAbilityFavorBonus();
        void ChangeTomeRaise(ABILITIES Ability, int AtLevel, int Change);
		int GetTomeRaise(ABILITIES Ability, int AtLevel, bool IncludeThisLevel, bool IncludeAllTomes=false);
		void SetTome(ABILITIES Ability, int SetTomeRaise[6][MAXLEVEL]);

        //ability stat stuff
        int GetHitPoints(int AtLevel);
        int CalculateBAB(int AtLevel);
        int GetSave(SAVETYPE SaveType, int AtLevel, bool IncludeEquipment=true);
		int GetSaveMod(SAVETYPE SaveType, SAVEMODS ModType, int AtLevel, bool IncludeEquipment=true);
		int CalculateTotalAbilityMod(ABILITIES Ability, unsigned int CurrentSelectedLevel,  bool IncludeEquipment=true);
		void GetKiPoints(int AtLevel, int *MaxKi, int *StableKi);

        //feat stuff
        int GetFeat(int LevelLimit, unsigned int Index);
        int GetFeat(int Level, FEATSLOTTYPE FeatType, unsigned int Index);
        FEATSLOTTYPE GetFeatAquireType(int FeatIndex, int Level);
        bool HasFeat(string FeatName, int LevelLimit);
        bool HasFeat(int LevelLimit, int Index);
        int CountFeat(string FeatName, int LevelLimit);
        void DetermineFeatSlots(int CurrentSelectedLevel, FEATSLOTTYPE *F1, FEATSLOTTYPE *F2, FEATSLOTTYPE *F3);
        void AddFeat(int Level, int FeatIndex, FEATSLOTTYPE FeatType);
        void AddFeat(int Level, string FeatName, FEATSLOTTYPE FeatType);
        void RemoveFeat(int FeatIndex);
        void RemoveFeatOnce(int FeatIndex);
        void RemoveFeat(int Level, FEATSLOTTYPE FeatType);
        void ReAddRemovedAutoFeat(int FeatIndex);
		bool HasAllFeatParentHeadings(string ParentHeading, int LevelLimit);
		void ResetAutoFeats(unsigned int AtLevel=1);
		int GetReincarnateCount(CLASS Class);
		int GetReincarnateCount();
		int GetReincarnateFeatIndex(CLASS Class);
		void IncreasePastLife(CLASS Class);
		void DecreasePastLife(CLASS Class);
		int GetEpicFeatCount(DESTINY_SPHERE Sphere, int feat);
		void IncreaseEpicFeat(DESTINY_SPHERE Sphere, int feat);
		void DecreaseEpicFeat(DESTINY_SPHERE Sphere, int feat);
		int GetEpicFeatIndex(DESTINY_SPHERE Sphere, int feat);
		int GetIconicPastLifeCount(ICONICRACES Race);
		void IncreaseIconicPastLife(ICONICRACES Race);
		void DecreaseIconicPastLife(ICONICRACES Race);
		int GetIconicFeatIndex(ICONICRACES Race);
		int GetFeatCountAtLevel(int Level);
		int GetFeatAtLevel(int Level,int index);
		
        //skill stuff
        float CalculateSkillLevel(SKILLS Skill, unsigned int AtLevel, bool AddMiscMod);
        int GetTotalSkillPointsSpent(SKILLS Skill, unsigned int AtLevel);
        float GetTotalSkillPointsSpentDisplay(SKILLS Skill, unsigned int AtLevel);
        int GetLevelSkillPointsSpent(SKILLS Skill, unsigned int AtLevel);
        int GetLevelSkillPointsSpent(unsigned int AtLevel);
        void SpendSkillPoint(SKILLS Skill, unsigned int AtLevel, int Point);
        int CalculateAvailableSkillPoints(unsigned int AtLevel);
        int CalculateSkillMiscMod(SKILLS Skill, unsigned int AtLevel);
        float GetSkillPointSpendLimit(SKILLS Skill, unsigned int AtLevel);
		void SetSkillPoints(int (&PointValues)[NUMSKILLS][HEROICLEVELS]);
		bool HasSkill(int Skillindex, int Level);

        //enhancement stuff
		Character_Enhancements_Class* GetCharacterEnhancementsPointer();
		void ValidateCharacterEnhancements(string ActionType, int atLevel);

		//Destiny Stuff
		Character_Destinies_Class* GetCharacterDestiniesPointer();

        //spell stuff
		void ClearSpells();
        int GetSpellPoints(int AtLevel);
		unsigned int GetTotalNumSpells();
		int GetKnownSpell(unsigned int Index);
        int GetSpellByLevelAquired(int MaxLevel, int Index);
        int GetSpellLevelAquired(int Index);
        int GetSpellBySlot(int AtLevel, int SpellSlot);
        int GetSpellBySpellLevelAndClass(int AtLevel, int SpellLevel, CLASS Class, int Index);
		void GetSpellSelectionSlots(int AtLevel, int *SpellLevel, int *NumSpells);
        int GetNumSpellsSelected(int AtLevel);
        void AddSelectedSpell(int AtLevel, int SpellIndex, int SpellSlot);
        void AddSelectedSpell(int AtLevel, string SpellName, int SpellSlot);
        void RemoveSelectedSpell(int SpellIndex);
        bool HasSpell(int SpellIndex, int MaxLevel);
		SPELLTYPE GetSpellAquireType(int SpellIndex);

		//Item Stuff
        void SetActiveEquipment(unsigned int Index, EQUIPMENTSLOTTYPE ChosenSlot);
		int GetActiveEquipment(EQUIPMENTSLOTTYPE ChosenSlot);
		//int GetItemData(unsigned int Index, unsigned int *ItemIndex, unsigned int *ItemEffectsVector);
		int GetItemData(unsigned int Index, unsigned int *ItemIndex, unsigned int *ItemEffect1, unsigned int *ItemEffect2, unsigned int *ItemEffect3, unsigned int *ItemEffect4, unsigned int *ItemEffect5, unsigned int *ItemEffect6, unsigned int *Eldritch);
		void ClearCharacterItems();
		void AddItemToCharacterItems(int ItemIndex, int Effect1, int Effect2, int Effect3, int Effect4, int Effect5, int Effect6, int EldritchEffect);
		bool IsItemEquipped(int Item);
		string GetItemDisplayName(int Item);
		string BuildCharacterItemDescription(int Item);
		string GetItemStaticEffectsDescription (int ItemIndex);
		string GetItemChosenEffectsDescription (int Item);
		string GetItemFlavorText(int ItemIndex);
		int GetItemAbilityChange(ABILITIES Ability);
		int GetItemHitPointChange(int CurrentSelectedLevel);
		int GetItemSpellPointChange(int CurrentSelectedLevel);
		int GetItemSkillChange(int Skill, int CurrentSelectedLevel);
		int GetItemSaveChange(SAVETYPE Save, int CurrentSelectedLevel);
		unsigned int GetCharacterItemsSize();

		//Additional Stat Stuff
		int GetACMod(ACMODS ModType, int AtLevel);
		int GetItemACChange(MODTYPE ACType);
		int GetItemBaseAC(string Type);
		int GetArmorClassFeats(unsigned int CurrentSelectedLevel);
		int GetACDexBonus();
		int GetPaladinAuraAC(unsigned int CurrentSelectedLevel);
		void GetRageData(unsigned int CurrentSelectedLevel, int *RagesPerDay, int *Duration, int *StrBonus, int *ConBonus, int *WillBonus, int *ACPenalty);
		void GetTurnData(unsigned int CurrentSelectedLevel, int *TurnsPerDay, int *Check, int *Damage);
		/*bool IsMonkCentered(unsigned int CurrentSelectedLevel);*/
		int TomeRaise[6][MAXLEVEL];

    private:
        string FirstName;
        string SurName;
        RACE Race;
        SEX CharacterSex;
        ALIGNMENT Alignment;
        CLASS ClassRecord[MAXLEVEL];
        int AbilityRaise[6];
        
        ABILITIES AbilityRaise4;
        ABILITIES AbilityRaise8;
        ABILITIES AbilityRaise12;
        ABILITIES AbilityRaise16;
        ABILITIES AbilityRaise20;
        ABILITIES AbilityRaise24;
		ABILITIES AbilityRaise28;
        int SkillRaise[NUMSKILLS][HEROICLEVELS];
        vector <FeatListStruct> FeatList;
        int ReincarnationCount[NUMCLASSES];
		int EpicPastLifeCount[EPICPASTLIFESPHERE][3];
		int IconicPastLifeCount[ICONICPASTLIFEFEAT];
        vector <SpellListStruct> SpellList;
        vector <string> ValidationError;
		bool LevelError[MAXLEVEL];
        bool FavorAbilityBonusPoints;
		vector <CharacterItemStruct> CharacterItems;
		int CharacterItemsEquipped[NUMCHAREQUPMENTSLOTS];
		unsigned int ValidationsDisabledCount;

		//Enhancement Variables
		Character_Enhancements_Class CharacterEnhancements;

		//Destiny Variables
		Character_Destinies_Class CharacterDestinies;


        void AddRaceAutoFeats(int AtLevel=1);
        void RemoveRaceAutoFeats();
        void AddClassAutoFeats(CLASS ClassType, int AtLevel, int ClassLevel);
        void RemoveClassAutoFeats(CLASS ClassType, int AtLevel, int ClassLevel);
        void AddAutoSpells(int AtLevel);
        void AddAutoSpells(CLASS Class, int AtLevel, int SpellLevel);
        void RemoveAutoSpells();
        void ValidateCharacter();
		string ConvertOrdinalNumberToRoman(int Number);
		CLASS ConvertClassStringToIndex(string ClassString);
    };

extern CharacterClass Character;
extern bool FeatCompare(FeatListStruct F1, FeatListStruct F2);
 