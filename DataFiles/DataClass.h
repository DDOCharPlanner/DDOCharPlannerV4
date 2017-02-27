//---------------------------------------------------------------------------
#pragma once

#include "stdafx.h"
#include "FeatDataClass.h"
#include "Data_Enhancement_MultiSelector_Class.h"
#include "Data_Enhancement_Class.h"
#include "Data_Enhancement_Tree_Class.h"
#include "Data_Destiny_MultiSelector_Class.h"
#include "Data_Destiny_Tree_Class.h"
#include "Data_Destiny_Class.h"
#include "ItemEffectClass.h"
#include "ItemClickyEffectClass.h"
#include "ItemClass.h"
#include <unordered_map>

//---------------------------------------------------------------------------
struct AdvancementStruct
    {
    unsigned int Level;
    string Instruction;
    ADVANCEMENTTYPE AdvancementType;
    int Value;
    bool Automatic;
    };

struct RaceStruct
    {
    string Name;
    string Description;
    int BaseStr;
    int BaseDex;
    int BaseCon;
    int BaseInt;
    int BaseWis;
    int BaseCha;
    vector <AdvancementStruct> Advancement;
    };

struct ClassStruct
    {
    string Name;
    string Description;
    int HitDice;
    int SkillPoints;
    int SpellPoints[MAXLEVEL];
    int BAB[MAXLEVEL];
    int FortitudeSave[MAXLEVEL];
    int ReflexSave[MAXLEVEL];
    int WillSave[MAXLEVEL];
	DESTINY_SPHERE StartingDestinySphere;
    vector <ALIGNMENT> Alignment;
    vector <AdvancementStruct> Advancement;
    };

struct SkillStruct
    {
    string Name;
    string Description;
    ABILITIES KeyAbility;
    vector <CLASS> PrimaryClass;
    vector <CLASS> CrossClass;
    };

struct SpellStruct
    {
    string Name;
    string Description;
    vector <CLASS> ClassType;
    vector <unsigned int> Level;
	string Target;
	string Cooldown;
	string Duration;
	string Cost;
	string Components;
	string School;
	string Meta;
	string Range;
	string Save;
	string Resist;
    unsigned int GraphicIconIndex;
    };

//---------------------------------------------------------------------------
class DataClass
    {
    public:
        DataClass();
        virtual ~DataClass();

        void LoadDataFiles();
        bool AllDataFilesLoaded();
        int GetNumRaces();
        string GetRaceName(int Index);
        string GetRaceDescription(int Index);
        void GetRaceBaseStats(int Index, int *Stats);
        string GetAlignmentString(ALIGNMENT Alignment);
        bool IsAlignmentCompatable(CLASS Class, ALIGNMENT Alignment);
        int GetNumClasses();
        string GetClassName(int Index);
		CLASS GetClassIndex(string ClassName);
        string GetClassDescription(int Index);
        string GetInstructionString(unsigned int Level, unsigned int RaceNum, unsigned int ClassNum, unsigned int Index, int *Value);
        ADVANCEMENTTYPE GetAdvancementType(unsigned int Level, unsigned int RaceNum, unsigned int ClassNum, unsigned int Index, int *Value);
		DESTINY_SPHERE GetDestinySphere(CLASS ClassIndex);

        //ability stuff
        string GetAbilityString(ABILITIES Ability, bool Full);

        //ability stat stuff
        int CalculateAbilityModifier(int AbilityValue);
        int GetHitDice(int ClassType);
        int GetClassBAB(CLASS ClassType, int AtLevel);
        int GetBaseSave(SAVETYPE SaveType, CLASS ClassType, int AtLevel);

        //feat stuff
        FeatDataClass* GetFeatPointer (int FeatIndex);
        FeatDataClass* GetFeatPointer (string FeatName);
        int GetFeatIndex(string FeatName);
        int GetFeatWithParentHeading(string ParentHeading, int StartFeat);
        int GetRaceAutoFeat(RACE RaceType, unsigned int AtLevel, unsigned int StartFeat);
        int GetRaceFeat(RACE RaceType, unsigned int AtLevel, unsigned int StartFeat);
        int GetClassAutoFeat(CLASS ClassType, unsigned int Level, unsigned int StartFeat);
        int GetClassFeat(CLASS ClassType, unsigned int Level, unsigned int StartFeat);
        
        //skill stuff
        int GetClassSkillPoints(CLASS ClassType);
        int GetBaseSkillLevel(int SkillIndex, int AtLevel);
        bool IsSkillPrimary(CLASS ClassType, int SkillIndex);
        bool IsSkillCross(CLASS ClassType, int SkillIndex);
		void GetSkillData(int SkillIndex, string *Name, ABILITIES *KeyAbility);
        string GetSkillName (int SkillIndex);
        string GetSkillDescription (int SkillIndex);

        //enhancement stuff	
        //TODO: See if we can remove these?
		ENHANCEMENT_TREE GetEnhTreeIndex(string TreeName);
		string GetEnhMultiName(int MultiIndex);
		string GetEnhMultiDescription(int MultiIndex);

		//Enhancement MultiSelector Stuff
		Data_Enhancement_MultiSelector_Class* GetMultiEnhancementPointer (int MultiIndex);
		int GetEnhMultiSelectorIndex(string MultiName);

		//Enhancement Tree Stuff
		Data_Enhancement_Tree_Class* GetEnhancementTreePointer (ENHANCEMENT_TREE Tree);
		Data_Enhancement_Tree_Class* GetEnhancementTreePointer (string TreeName);
		ENHANCEMENT_TREE GetRacialTree(RACE CurrentRace);
		void GetClassTrees(vector <ENHANCEMENT_TREE>& rClassTrees, CLASS CurrentClass);
		int GetClassEnhancementTreeCount(CLASS CurrentClass);

		//Destiny MultiSelector Stuff
		Data_Destiny_MultiSelector_Class* GetMultiDestinyPointer(int MultiIndex);
		int GetDestinyMultiSelectorIndex(string MultiName);

		//Destiny Tree Stuff
		Data_Destiny_Tree_Class* GetDestinyTreePointer (DESTINY_TREE DestinyTree);
		DESTINY_TREE GetDestinyTreeIndex(string TreeName);

		//Destiny Stuff

        //spell stuff
		SpellStruct* GetSpellData(int Index);
        string GetSpellName(int Index);
        int GetSpellPoints(CLASS ClassType, int Level);
        int GetSpellIndex(CLASS ClassType, unsigned int Level, unsigned int Index);
        int GetSpellIndex(string SpellName);
        int GetSpellLevel(CLASS ClassType, unsigned int Index);
        unsigned int GetSpellIconIndex(unsigned int Index);

		//Item Stuff
		ItemClass* GetItemPointer(int ItemIndex);
		ItemEffectClass* GetItemEffectPointer(int ItemEffectIndex);
		int GetItemIndex(string strItemName);
		int GetItemSize();
		int GetItemEffectSize();
		int GetItemEffectIndex(string strEffectName, string strEffectSubName);
		int GetItemEffectIndex(string strCombinedEffectName);

    private:
        bool DataFilesLoaded[NUMDATAFILES];
        vector <RaceStruct> Race;
        vector <ClassStruct> Class;
        vector <SkillStruct> Skill;
        vector <FeatDataClass> FeatData;
		Data_Enhancement_Tree_Class EnhancementTreeData[NUM_ENHANCEMENT_TREES];
		vector <Data_Enhancement_MultiSelector_Class> EnhancementMultiSelector;
		vector <Data_Destiny_MultiSelector_Class> DestinyMultiSelector;
		Data_Destiny_Tree_Class DestinyTreeData[NUM_DESTINY_TREES];
        vector <SpellStruct> Spell;
		vector <ItemEffectClass> ItemEffect;
		vector <ItemClickyEffectClass> ItemClickyEffect;
		vector <ItemClass> Item;
		unordered_map<string, int> ItemEffectIndex;
        
        FILESTATE LoadRaceFile();
        FILESTATE LoadClassFile();
        FILESTATE LoadFeatFile();
        FILESTATE LoadSkillFile();
        FILESTATE LoadEnhancementFile();
		FILESTATE LoadDestinyFile();
        FILESTATE LoadSpellFile();
		FILESTATE LoadItemEffectFile();
		FILESTATE LoadItemClickyEffectFile();
		FILESTATE LoadItemFile();
		FILESTATE LoadTemplateFiles();

		void InitializeEnhancementTrees();
		void InitializeDestinyTrees();

        //do not implement these two functions, instance  control!!
        DataClass(const DataClass &source);
        DataClass& operator=(const DataClass &source);
    };

extern DataClass Data;
  
