//---------------------------------------------------------------------------
#pragma once

#include "stdafx.h"

class FeatDataClass
	{
	public:
		FeatDataClass();
		virtual ~FeatDataClass();
		//copy constructor and assignment operator
        FeatDataClass(const FeatDataClass &source);
        FeatDataClass& operator=(const FeatDataClass &source);
		
		FeatDataClass* const GetFeatAddress();
		void InitializeFeat(string FeatData);
		bool GetFeatTag(FEATTAG Tag);
        string GetFeatName(bool PrependParentHeading = false);
		string GetFeatParentHeading();
        string GetFeatDescription();
		unsigned int GetFeatIconIndex();
		PREREQRESULT HaveAllFeatPrereqs(unsigned int AtLevel);
        FEATAQUIRETYPE HasRace(RACE Race, unsigned int AtLevel);
        bool HasClass(CLASS Class, unsigned int AtLevel, FEATAQUIRETYPE Type);
        int GetFeatAutoClassLevel(CLASS Class);
		string GetPrereqString(int CharacterLevel);

	private:
	    string Name;
		string Description;
	    vector <string> NeedsAll;
		vector <string> NeedsOne;
	    string PrereqDescription;
		string ParentHeading;
	    vector <RACE> RaceType;
		vector <CLASS> ClassType;
	    vector <unsigned int> Level;
		vector <FEATAQUIRETYPE> AquireType;
	    vector <string> LockFeat;
		bool Metamagic;
	    bool FighterBonus;
	    bool ArtificerBonus;
		bool FavoredEnemy;
		bool RogueBonus;
		bool MonkBonus;
		bool MonkPath;
		bool Deity;
		bool FavoredSoulBonus;
		bool Multiple;
	    bool ParentFeat;
	    bool PastLife;
		bool HalfElfBonus;
		bool MonkExclusive;
		bool DruidWildShape;
		bool WarlockPact;
		bool Destiny;
		bool DestinyNotExclusive;
		bool Legendary;
	    bool NoFeatTag;
		bool DragonbornBonus;
		unsigned int GraphicIconIndex;
		
		void StripStringLeadingWhiteSpace(string &SourceString);
		string ConvertRaceTypeToString(RACE Race);
		string ConvertClassTypeToString(CLASS Class);
		string ConvertAquireTypeToString(FEATAQUIRETYPE Type, int Level);
		string GetPrereqColorCode(string Requirement, int CharacterLevel, bool RequireAll);
	};
