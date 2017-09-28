//---------------------------------------------------------------------------
#include "FeatDataClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
#include "DataClass.h"

//---------------------------------------------------------------------------
FeatDataClass::FeatDataClass()
	{
	//clear out the member variables so we are not starting with garbage
	Name = "";
	Description = "";
	NeedsAll.clear();
	NeedsOne.clear();
	PrereqDescription = "";
	ParentHeading = "";
	RaceType.clear();
	ClassType.clear();
	Level.clear();
	AquireType.clear();
	LockFeat.clear();
	Metamagic = false;
	FighterBonus = false;
	ArtificerBonus = false;
	FavoredEnemy = false;
	RogueBonus = false;
	MonkBonus = false;
	MonkPath = false;
	Deity = false;
	FavoredSoulBonus = false;
	Multiple = false;
	ParentFeat = false;
	PastLife = false;
	HalfElfBonus = false;
	MonkExclusive = false;
	DruidWildShape = false;
	WarlockPact = false;
	Destiny = false;
	DestinyNotExclusive = false;
	Legendary = false;
	DragonbornBonus = false;
	ClericBonus = false;
	NoFeatTag = true;
	GraphicIconIndex = 0;
	}
	
//---------------------------------------------------------------------------
FeatDataClass::~FeatDataClass()
	{
	}
	
//---------------------------------------------------------------------------
FeatDataClass::FeatDataClass(const FeatDataClass &source)
	{
	//the copy constructor. We need this because this class lives in a vector
	//and the vector may need to copy the class somewhere else...
	
	Name = source.Name;
	Description = source.Description;
	for (unsigned int i=0; i<source.NeedsAll.size(); i++)
		NeedsAll.push_back(source.NeedsAll[i]);
	for (unsigned int i=0; i<source.NeedsOne.size(); i++)
		NeedsOne.push_back(source.NeedsOne[i]);
	PrereqDescription = source.PrereqDescription;
	ParentHeading = source.ParentHeading;
	RaceType.clear();
	for (unsigned int i=0; i<source.RaceType.size(); i++)
		RaceType.push_back(source.RaceType[i]);
	ClassType.clear();
	for (unsigned int i=0; i<source.ClassType.size(); i++)
		ClassType.push_back(source.ClassType[i]);
	Level.clear();
	for (unsigned int i=0; i<source.Level.size(); i++)
		Level.push_back(source.Level[i]);
	AquireType.clear();
	for (unsigned int i=0; i<source.AquireType.size(); i++)
		AquireType.push_back(source.AquireType[i]);
	LockFeat.clear();
	for (unsigned int i=0; i<source.LockFeat.size(); i++)
		LockFeat.push_back(source.LockFeat[i]);
	Metamagic = source.Metamagic;
	FighterBonus = source.FighterBonus;
	ArtificerBonus = source.ArtificerBonus;
	FavoredEnemy = source.FavoredEnemy;
	RogueBonus = source.RogueBonus;
	MonkBonus = source.MonkBonus;
	MonkPath = source.MonkPath;
	Deity = source.Deity;
	FavoredSoulBonus = source.FavoredSoulBonus;
	Multiple = source.Multiple;
	ParentFeat = source.ParentFeat;
	PastLife = source.PastLife;
	HalfElfBonus = source.HalfElfBonus;
	MonkExclusive = source.MonkExclusive;
	DruidWildShape = source.DruidWildShape;
	WarlockPact = source.WarlockPact;
	Destiny = source.Destiny;
	DestinyNotExclusive = source.DestinyNotExclusive;
	Legendary = source.Legendary;
	DragonbornBonus = source.DragonbornBonus;
	ClericBonus = source.ClericBonus;
	NoFeatTag = source.NoFeatTag;
	GraphicIconIndex = source.GraphicIconIndex;
	}
	
//---------------------------------------------------------------------------
FeatDataClass& FeatDataClass::operator=(const FeatDataClass &source)
	{
	//the = function overload. We need this because this class lives in a vector
	//and unfortunately, vectors use this function...
	Name = source.Name;
	Description = source.Description;
	for (unsigned int i=0; i<source.NeedsAll.size(); i++)
		NeedsAll.push_back(source.NeedsAll[i]);
	for (unsigned int i=0; i<source.NeedsOne.size(); i++)
		NeedsOne.push_back(source.NeedsOne[i]);
	PrereqDescription = source.PrereqDescription;
	ParentHeading = source.ParentHeading;
	RaceType.clear();
	for (unsigned int i=0; i<source.RaceType.size(); i++)
		RaceType.push_back(source.RaceType[i]);
	ClassType.clear();
	for (unsigned int i=0; i<source.ClassType.size(); i++)
		ClassType.push_back(source.ClassType[i]);
	Level.clear();
	for (unsigned int i=0; i<source.Level.size(); i++)
		Level.push_back(source.Level[i]);
	AquireType.clear();
	for (unsigned int i=0; i<source.AquireType.size(); i++)
		AquireType.push_back(source.AquireType[i]);
	LockFeat.clear();
	for (unsigned int i=0; i<source.LockFeat.size(); i++)
		LockFeat.push_back(source.LockFeat[i]);
	Metamagic = source.Metamagic;
	FighterBonus = source.FighterBonus;
	ArtificerBonus = source.ArtificerBonus;
	FavoredEnemy = source.FavoredEnemy;
	RogueBonus = source.RogueBonus;
	MonkBonus = source.MonkBonus;
	MonkPath = source.MonkPath;
	Deity = source.Deity;
	FavoredSoulBonus = source.FavoredSoulBonus;
	Multiple = source.Multiple;
	ParentFeat = source.ParentFeat;
	PastLife = source.PastLife;
	HalfElfBonus = source.HalfElfBonus;
	MonkExclusive = source.MonkExclusive;
	DruidWildShape = source.DruidWildShape;
	WarlockPact = source.WarlockPact;
	Destiny = source.Destiny;
	DestinyNotExclusive = source.DestinyNotExclusive;
	Legendary = source.Legendary;
	DragonbornBonus = source.DragonbornBonus;
	ClericBonus = source.ClericBonus;
	NoFeatTag = source.NoFeatTag;
	GraphicIconIndex = source.GraphicIconIndex;
	
	return *this;
	}
	
//---------------------------------------------------------------------------
FeatDataClass* const FeatDataClass::GetFeatAddress()
	{
	//IMPORTANT SAFETY TIP: Never ever call this function until the entire feat
	//file has been fully loaded and stored into individual feats. Otherwise you
	//may end up with a bad pointer!
	return this;
	}
	
//---------------------------------------------------------------------------
void FeatDataClass::InitializeFeat(string FeatData)
	{
    #define NUMKEYWORDS 12

	string KeywordString[NUMKEYWORDS];
	string FeatLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	int Value;
	string Substring;
	
    //parse the FeatData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "PARENTHEADING: ";
	KeywordString[1] = "FEATNAME: ";
	KeywordString[2] = "FEATDESCRIPTION: ";
	KeywordString[3] = "FEATTAG: ";
	KeywordString[4] = "RACELIST:";	//leaving the start space so we can distinguish between elf and half-elf
	KeywordString[5] = "CLASSLIST: ";
	KeywordString[6] = "LEVEL: ";
	KeywordString[7] = "ACQUIRE: ";
	KeywordString[8] = "NEEDSALL: ";
	KeywordString[9] = "NEEDSONE: ";
	KeywordString[10] = "LOCK: ";
	KeywordString[11] = "ICON: ";
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		FeatLine[i] = "";
		if (FeatData.find(KeywordString[i]) != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = FeatData.find(KeywordString[i]);
			EndLoc = FeatData.find(";", FeatData.find(KeywordString[i])); 
			FeatLine[i] = FeatData.substr(FeatData.find(KeywordString[i]), EndLoc-StartLoc);
			//drop the keyword from the line string, we don't need it now
			FeatLine[i].erase(0, KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
        {
        switch (i)
            {
            case 0:     //the parent heading
                {
                if (FeatLine[i] == "")
					continue;
                ParentHeading = FeatLine[i];
                break;
                }
            case 1:     //the feat name
                {
                if (FeatLine[i] == "")
					continue;
                Name = FeatLine[i];
                break;
                }
            case 2:     //feat description
                {
                if (FeatLine[i] == "")
					continue;
                Description = FeatLine[i];
                break;
                }
            case 3:     //special tags
                {
                if (FeatLine[i] == "")
					{
					NoFeatTag = true;
					continue;
					}
				if (FeatLine[i].find("Metamagic") != string::npos)
					{
					Metamagic = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Fighter Bonus") != string::npos)
					{
                    FighterBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Artificer Bonus") != string::npos)
					{
                    ArtificerBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Favored Enemy") != string::npos)
					{
                    FavoredEnemy = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Rogue Bonus") != string::npos)
					{
                    RogueBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Monk Bonus") != string::npos)
					{
					MonkBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Monk Path") != string::npos)
					{
					MonkPath = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Divine") != string::npos)
					{
					Deity = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Favored Soul Bonus") != string::npos)
					{
					FavoredSoulBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Multiple") != string::npos)
					{
					Multiple = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Parent Feat") != string::npos)
					{
					ParentFeat = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Past Life") != string::npos)
					{
					PastLife = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Half-Elf Bonus") != string::npos)
					{
					HalfElfBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Monk Exclusive") != string::npos)
					{
					MonkExclusive = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Druid Shape") != string::npos)
					{
					DruidWildShape = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Warlock Pact") != string::npos)
				{
					WarlockPact = true;
					NoFeatTag = false;
				}
				if (FeatLine[i].find("Destiny") != string::npos)
					{
					Destiny = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("DestinyNotExclusive") != string::npos)
					{
					DestinyNotExclusive = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Dragonborn Bonus") != string::npos)
					{
					DragonbornBonus = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Legendary") != string::npos)
					{
					Legendary = true;
					NoFeatTag = false;
					}
				if (FeatLine[i].find("Cleric Bonus") != string::npos)
				{
					ClericBonus = true;
					NoFeatTag = false;
				}

				break;
                }
            case 4:     //the race list
                {
                if (FeatLine[i] == "")
					continue;
				if (FeatLine[i].find("Human") != string::npos)
                    RaceType.push_back(HUMAN);
				if (FeatLine[i].find(" Elf") != string::npos) //don't grab Half-Elf here
                    RaceType.push_back(ELF);
				if (FeatLine[i].find("Halfling") != string::npos)
                    RaceType.push_back(HALFLING);
				if (FeatLine[i].find("Dwarf") != string::npos)
                    RaceType.push_back(DWARF);
				if (FeatLine[i].find("Warforged") != string::npos)
                    RaceType.push_back(WARFORGED);
				if (FeatLine[i].find("Drow") != string::npos)
                    RaceType.push_back(DROW);
				if (FeatLine[i].find("Half-Elf") != string::npos)
                    RaceType.push_back(HALFELF);
				if (FeatLine[i].find("Half-Orc") != string::npos)
                    RaceType.push_back(HALFORC);
				if (FeatLine[i].find("Bladeforged") != string::npos)
					RaceType.push_back(BLADEFORGED);
				if (FeatLine[i].find("Morninglord") != string::npos)
					RaceType.push_back(MORNINGLORD);
				if (FeatLine[i].find("Purple Dragon Knight") != string::npos)
					RaceType.push_back(PURPLEDRAGONKNIGHT);
				if (FeatLine[i].find("Shadar-Kai") != string::npos)
					RaceType.push_back(SHADARKAI);
				if (FeatLine[i].find(" Gnome") != string::npos) //don't grab Deep Gnome here
					RaceType.push_back(GNOME);
				if (FeatLine[i].find("Deep-Gnome") != string::npos)
					RaceType.push_back(DEEPGNOME);
				if (FeatLine[i].find("Dragonborn") != string::npos)
					RaceType.push_back(DRAGONBORN);
                break;
                }
            case 5:     //the class list
                {
                if (FeatLine[i] == "")
					continue;
                while (FeatLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(FeatLine[i]);
	                EndLoc = FeatLine[i].find(",");
	                Substring = FeatLine[i].substr(0, EndLoc);
	                if (Substring == "Fighter")
	                    ClassType.push_back(FIGHTER);
					if (Substring == "Paladin")
	                    ClassType.push_back(PALADIN);
					if (Substring == "Barbarian")
	                    ClassType.push_back(BARBARIAN);
					if (Substring == "Monk")
	                    ClassType.push_back(MONK);
					if (Substring == "Rogue")
	                    ClassType.push_back(ROGUE);
					if (Substring == "Ranger")
	                    ClassType.push_back(RANGER);
					if (Substring == "Cleric")
	                    ClassType.push_back(CLERIC);
					if (Substring == "Wizard")
	                    ClassType.push_back(WIZARD);
					if (Substring == "Sorcerer")
	                    ClassType.push_back(SORCERER);
					if (Substring == "Bard")
	                    ClassType.push_back(BARD);
					if (Substring == "Favored Soul")
	                    ClassType.push_back(FAVORED_SOUL);
					if (Substring == "Artificer")
	                    ClassType.push_back(ARTIFICER);
					if (Substring == "Druid")
	                    ClassType.push_back(DRUID);
					if (Substring == "Warlock")
						ClassType.push_back(WARLOCK);
					FeatLine[i].erase(0, EndLoc+1);
					}                
	            StripStringLeadingWhiteSpace(FeatLine[i]);
	            EndLoc = FeatLine[i].find(",");
	            Substring = FeatLine[i];
	            if (Substring == "Fighter")
	                ClassType.push_back(FIGHTER);
				if (Substring == "Paladin")
	                ClassType.push_back(PALADIN);
				if (Substring == "Barbarian")
	                ClassType.push_back(BARBARIAN);
				if (Substring == "Monk")
	                ClassType.push_back(MONK);
				if (Substring == "Rogue")
	                ClassType.push_back(ROGUE);
				if (Substring == "Ranger")
	                ClassType.push_back(RANGER);
				if (Substring == "Cleric")
	                ClassType.push_back(CLERIC);
				if (Substring == "Wizard")
	                ClassType.push_back(WIZARD);
				if (Substring == "Sorcerer")
	                ClassType.push_back(SORCERER);
				if (Substring == "Bard")
	                ClassType.push_back(BARD);
				if (Substring == "Favored Soul")
	                ClassType.push_back(FAVORED_SOUL);
				if (Substring == "Artificer")
	                ClassType.push_back(ARTIFICER);
				if (Substring == "Druid")
	                ClassType.push_back(DRUID);
				if (Substring == "Warlock")
					ClassType.push_back(WARLOCK);
                break;
                }
            case 6:     //required level list
                {
                if (FeatLine[i] == "")
					continue;
                while (1)
                    {
                    StripStringLeadingWhiteSpace(FeatLine[i]);
                    Value = atoi(FeatLine[i].c_str());
                    Level.push_back(Value);
					if (FeatLine[i].find(",") == string::npos)
                        break;
					EndLoc = FeatLine[i].find(",");
					FeatLine[i].erase(0, EndLoc+1);	
                    }
                break;
                }
            case 7:     //method of aquirement
                {
                if (FeatLine[i] == "")
					continue;
                while (FeatLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(FeatLine[i]);
	                EndLoc = FeatLine[i].find(",");
	                Substring = FeatLine[i].substr(0, EndLoc);
	                if (Substring == "Automatic")
						AquireType.push_back(FEATAQUIREAUTOMATIC);
					else if (Substring == "AutoNoPrereq")
						AquireType.push_back(FEATAQUIREAUTONOPREREQ);
					else		
						AquireType.push_back(FEATAQUIRETRAIN);
					FeatLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(FeatLine[i]);
                Substring = FeatLine[i];
                if (Substring == "Automatic")
					AquireType.push_back(FEATAQUIREAUTOMATIC);
				else if (Substring == "AutoNoPrereq")
					AquireType.push_back(FEATAQUIREAUTONOPREREQ);
				else		
					AquireType.push_back(FEATAQUIRETRAIN);
                break;
                }
            case 8:     //the prereq list (Needs all)
                {
                if (FeatLine[i] == "")
					continue;
                while (FeatLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(FeatLine[i]);
	                EndLoc = FeatLine[i].find(",");
	                NeedsAll.push_back("");
	                NeedsAll[NeedsAll.size()-1] = FeatLine[i].substr(0, EndLoc);
					FeatLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(FeatLine[i]);
                NeedsAll.push_back("");
                NeedsAll[NeedsAll.size()-1] = FeatLine[i];
                break;
                }
            case 9:     //the prereq list (Needs one)
                {
                if (FeatLine[i] == "")
					continue;
                while (FeatLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(FeatLine[i]);
	                EndLoc = FeatLine[i].find(",");
	                NeedsOne.push_back("");
	                NeedsOne[NeedsOne.size()-1] = FeatLine[i].substr(0, EndLoc);
					FeatLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(FeatLine[i]);
                NeedsOne.push_back("");
                NeedsOne[NeedsOne.size()-1] = FeatLine[i];
                break;
                }
            case 10:     //the feat lock list
                {
                if (FeatLine[i] == "")
					continue;
                while (FeatLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(FeatLine[i]);
	                EndLoc = FeatLine[i].find(",");
	                LockFeat.push_back("");
	                LockFeat[LockFeat.size()-1] = FeatLine[i].substr(0, EndLoc);
					FeatLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(FeatLine[i]);
                LockFeat.push_back("");
                LockFeat[LockFeat.size()-1] = FeatLine[i];
                break;
				}
            case 11:     //the graphic icon
                {
                if (FeatLine[i] == "")
					continue;
                GraphicIconIndex = InterfaceManager.LoadIcon(FEATICON, FeatLine[i]);
                break;
                }
            }
        }
        
    return;
    #undef NUMKEYWORDS
	}
	
//---------------------------------------------------------------------------
bool FeatDataClass::GetFeatTag(FEATTAG Tag)
	{
	switch (Tag)
		{
		case FEATTAGMETAMAGIC:
			return Metamagic;
		case FEATTAGFIGHTERBONUS:
			return FighterBonus;
		case FEATTAGARTIFICERBONUS:
			return ArtificerBonus;
		case FEATTAGFAVOREDENEMY:
			return FavoredEnemy;
		case FEATTAGROGUEBONUS:
			return RogueBonus;
		case FEATTAGMONKBONUS:
			return MonkBonus;
		case FEATTAGMONKPATH:
			return MonkPath;
		case FEATTAGDEITY:
			return Deity;
		case FEATTAGFAVOREDSOULBONUS:
			return FavoredSoulBonus;
		case FEATTAGMULTIPLE:
			return Multiple;
		case FEATTAGPARENTFEAT:
			return ParentFeat;
		case FEATTAGPASTLIFE:
			return PastLife;
		case FEATTAGHALFELFBONUS:
			return HalfElfBonus;
		case FEATTAGMONKEXCLUSIVE:
			return MonkExclusive;
		case FEATTAGDRUIDWILDSHAPE:
			return DruidWildShape;
		case FEATTAGWARLOCKPACT:
			return WarlockPact;
		case FEATTAGDESTINY:
			return Destiny;
		case FEATTAGDESTINYNOTEXCLUSIVE:
			return DestinyNotExclusive;
		case FEATTAGLEGENDARY:
			return Legendary;
		case FEATTAGDRAGONBORNBONUS:
			return DragonbornBonus;
		case FEATTAGCLERICBONUS:
			return ClericBonus;
		case FEATTAGNONE:
			return NoFeatTag;
		default:
			return false;
		}
	}
	
//---------------------------------------------------------------------------
string FeatDataClass::GetFeatName(bool PrependParentHeading)
    {
    string Result;

    Result = "";
    if (ParentHeading != "" && PrependParentHeading == true)
        {
        Result += ParentHeading;
        Result += ": ";
        }
    Result += Name;
    return Result;
    }

//---------------------------------------------------------------------------
string FeatDataClass::GetFeatParentHeading()
    {
    return ParentHeading;
    }

//---------------------------------------------------------------------------
string FeatDataClass::GetFeatDescription()
    {
    return Description;
    }
    
//---------------------------------------------------------------------------
unsigned int FeatDataClass::GetFeatIconIndex()
	{
	return GraphicIconIndex;
	}
    
//---------------------------------------------------------------------------
PREREQRESULT FeatDataClass::HaveAllFeatPrereqs(unsigned int AtLevel)
    {
    RACE CharacterRace;
	ALIGNMENT CharacterAlignment;
	unsigned int ClassLevel[NUMCLASSES];
    int Offset;
    bool FeatQualify;
    string PrereqList;
    string Substring;
    int ReqAbility;
    int Index;
    int FeatCheckIndex;
	bool HasRequiredRaceLevel;
	bool HasRequiredClassLevel;
	FeatDataClass *CheckFeat;
	int Levels;
	int RequiredLevel;
	if (Name == "Improved Precise Shot")
		int xtemp = 0;
	//get the character race and class levels and Alignment
    CharacterRace = Character.GetRace();
	CharacterAlignment = Character.GetAlignment();
	for (unsigned int i=0; i<NUMCLASSES; i++)
        ClassLevel[i] = Character.GetClassLevel((CLASS)i, AtLevel);

	//first let's see if the character can even get this feat based on their 
	//race and classes (they don't need to have the level requirement satisfied)
	FeatQualify = false;
    for (unsigned int i=0; i<RaceType.size(); i++)
        {
        if (RaceType[i] == CharacterRace)
			{
			FeatQualify = true;
			break;
			}
		}
	Offset = RaceType.size();
	for (unsigned int i=0; i<ClassType.size(); i++)
	    {
	    if (FeatQualify == true)
			break;
		for (unsigned int j=0; j<NUMCLASSES; j++)
			{
			if (ClassType[i] == (CLASS)j)
				{
				if (ClassLevel[j] > 0)
					{
	                FeatQualify = true;
					break;
					}
                }
            }
		}

	//if the character has neither the race nor any of the classes
	//associated with this feat, then they don't qualify for it at all
	//and we're done
    if (FeatQualify == false)
        return PREREQ_DISQUALIFY;

	//all feats, no matter their type, MUST satisfy their level requirement
	//check the race level requirement, if any
	HasRequiredRaceLevel = false;
    for (unsigned int i=0; i<RaceType.size(); i++)
        {
        if (RaceType[i] == CharacterRace)
			{
			if (Level[i] <= AtLevel)
				{
				HasRequiredRaceLevel = true;
				//but wait, if this feat is one that ignores prereqs
				//then we are done, we automatically qualify for this feat
				if (AquireType[i] == FEATAQUIREAUTONOPREREQ)
					return PREREQ_PASS;
				break;
				}
			}
		}
		
	//Check the class level requirements, if any
	HasRequiredClassLevel = false;
	Offset = RaceType.size();
    for (unsigned int i=0; i<ClassType.size(); i++)
        {
		for (unsigned int j=0; j<NUMCLASSES; j++)
            {
            if (ClassType[i] == (CLASS)j)
                {
				if (Level[i+Offset] <= ClassLevel[j])
					{
					HasRequiredClassLevel = true;
					//but wait, if this feat is one that ignores prereqs
					//then we are done, we automatically qualify for this feat
					if (AquireType[i+Offset] == FEATAQUIREAUTONOPREREQ)
						return PREREQ_PASS;
					}
                }
            }
        }

	//check the level requirements
	if (HasRequiredRaceLevel == false && HasRequiredClassLevel == false)
		return PREREQ_FAIL;
		
	//note that some class restricted feats are also race restricted (such as the FvS divine feats)
	//make sure we don't disqualify due to race
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
	    PrereqList = NeedsAll[i];
		while (PrereqList.find("Race ") != string::npos)
			{
		    Substring = PrereqList.substr(PrereqList.find("Race "));
			Substring.replace(Substring.find("Race "), 5, "");
	        if (Substring.find(",") != string::npos)
		        Substring.erase(Substring.find(","), Substring.size()-Substring.find(","));
			if (Character.GetRaceString() != Substring)
	            return PREREQ_DISQUALIFY;
			PrereqList.replace(PrereqList.find("Race "), 5, "");
			}
		}

	//Similarly, some race restricted feats are also class restricted (such as Improved Sneak Attack)
	//make sure we don't disqualify due to class
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
	    PrereqList = NeedsAll[i];
		while (PrereqList.find("Class ") != string::npos)
			{
		    Substring = PrereqList.substr(PrereqList.find("Class "));
			Substring.replace(Substring.find("Class "), 6, "");
	        if (Substring.find(",") != string::npos)
		        Substring.erase(Substring.find(","), Substring.size()-Substring.find(","));
			if (Substring.find_last_of(" ") != string::npos)
				{
				RequiredLevel = atoi(Substring.substr(Substring.find_last_of(" ")).c_str());
				Substring.erase(Substring.find_last_of(" "), Substring.size()-Substring.find_last_of(" "));
				}
			Levels = Character.GetClassLevel(Data.GetClassIndex(Substring), AtLevel);
			if (Levels < RequiredLevel)
	            return PREREQ_FAIL;
			PrereqList.replace(PrereqList.find("Class "), 6, "");
			}
		}

    //we passed race and class level restrictions, now onto the feat requirements
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
	    PrereqList = NeedsAll[i];
		while (PrereqList.find("Feat ") != string::npos)
			{
	        Substring = PrereqList.substr(PrereqList.find("Feat "));
		    Substring.replace(Substring.find("Feat "), 5, "");
			if (Substring.find(",") != string::npos)
	            Substring.erase(Substring.find(","), Substring.size()-Substring.find(","));
		    if (Character.HasFeat(Substring, AtLevel) == false)
			    return PREREQ_FAIL;
	        PrereqList.replace(PrereqList.find("Feat "), 5, "");
		    }
		}

    //we passeed the feat test. What about the ability test?
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
	    PrereqList = NeedsAll[i];
		while (PrereqList.find("Ability ") != string::npos)
	        {
		    Substring = PrereqList.substr(PrereqList.find("Ability "));
			Substring.replace(Substring.find("Ability "), 8, "");
			if (Substring.find(",") != string::npos)
				Substring.erase(Substring.find(","), Substring.size()-Substring.find(","));
			if (Substring.find("Strength ") != string::npos)
				{
				Substring.replace(Substring.find("Strength "), 9, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetAbility((int)STRENGTH, AtLevel, true, false, false, false))
					return PREREQ_FAIL;
				}
			if (Substring.find("Dexterity ") != string::npos)
				{
	            Substring.replace(Substring.find("Dexterity "), 10, "");
		        ReqAbility = atoi(Substring.c_str());
			    if (ReqAbility > Character.GetAbility((int)DEXTERITY, AtLevel, true, false, false, false))
				    return PREREQ_FAIL;
	            }
		    if (Substring.find("Constitution ") != string::npos)
			    {
				Substring.replace(Substring.find("Constitution "), 13, "");
	            ReqAbility = atoi(Substring.c_str());
		        if (ReqAbility > Character.GetAbility((int)CONSTITUTION, AtLevel, true, false, false, false))
			        return PREREQ_FAIL;
				}
	        if (Substring.find("Intelligence ") != string::npos)
		        {
			    Substring.replace(Substring.find("Intelligence "), 13, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetAbility((int)INTELLIGENCE, AtLevel, true, false, false, false))
	                return PREREQ_FAIL;
		        }
			if (Substring.find("Wisdom ") != string::npos)
	            {
		        Substring.replace(Substring.find("Wisdom "), 7, "");
			    ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetAbility((int)WISDOM, AtLevel, true, false, false, false))
	                return PREREQ_FAIL;
		        }
			if (Substring.find("Charisma ") != string::npos)
				{
	            Substring.replace(Substring.find("Charisma "), 9, "");
		        ReqAbility = atoi(Substring.c_str());
			    if (ReqAbility > Character.GetAbility((int)CHARISMA, AtLevel, true, false, false, false))
				    return PREREQ_FAIL;
	            }
		    PrereqList.replace(PrereqList.find("Ability "), 8, "");
			}
		}

    //we passeed the ability test. What about the BAB test?
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
	    PrereqList = NeedsAll[i];
	    if (PrereqList.find("BAB ") != string::npos)
		    {
	        Substring = PrereqList.substr(PrereqList.find("BAB "));
		    Substring.replace(Substring.find("BAB "), 4, "");
			ReqAbility = atoi(Substring.c_str());
	        if (ReqAbility > Character.CalculateBAB(AtLevel))
		        return PREREQ_FAIL;
			}
		}

    //we passeed the BAB test. What about the creation test?
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
	    PrereqList = NeedsAll[i];
		if (PrereqList.find("Creation") != string::npos)
			if (AtLevel != 1)
				return PREREQ_FAIL;
		}
	//Check if Favored Soul Bonus Feat is Absorption type or Other
	if (FavoredSoulBonus == true)
	{
		if (ParentHeading == "Energy Absorption")
		{
			if (AtLevel == 2 || AtLevel == 7)
				return PREREQ_FAIL;
		}
	}





	// we passed the creation test. What about the Skill Requirement test?
	for (unsigned int i = 0; i<NeedsAll.size(); i++)
	{
		PrereqList = NeedsAll[i];
		while (PrereqList.find("Skill ") != string::npos)
		{
			Substring = PrereqList.substr(PrereqList.find("Skill "));
			Substring.replace(Substring.find("Skill "), 6, "");
			if (Substring.find(",") != string::npos)
				Substring.erase(Substring.find(","), Substring.size() - Substring.find(","));
			if (Substring.find("Balance ") != string::npos)
			{
				Substring.replace(Substring.find("Balance "), 8, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)BALANCE, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Bluff ") != string::npos)
			{
				Substring.replace(Substring.find("Bluff "), 6, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)BLUFF, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Concentration ") != string::npos)
			{
				Substring.replace(Substring.find("Concentration "), 14, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)CONCENTRATION, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Diplomacy ") != string::npos)
			{
				Substring.replace(Substring.find("Diplomacy "), 10, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)DIPLOMACY, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Disable Device ") != string::npos)
			{
				Substring.replace(Substring.find("Disable Device "), 15, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)DISABLEDEVICE, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Haggle ") != string::npos)
			{
				Substring.replace(Substring.find("Haggle "), 7, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)HAGGLE, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Heal ") != string::npos)
			{
				Substring.replace(Substring.find("Heal "), 5, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)HEAL, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Hide ") != string::npos)
			{
				Substring.replace(Substring.find("Hide "), 5, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)HIDE, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Intimidate ") != string::npos)
			{
				Substring.replace(Substring.find("Intimidate "), 11, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)INTIMIDATE, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Jump ") != string::npos)
			{
				Substring.replace(Substring.find("Jump "), 5, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)JUMP, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Listen ") != string::npos)
			{
				Substring.replace(Substring.find("Listen "), 7, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)LISTEN, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Move Silently ") != string::npos)
			{
				Substring.replace(Substring.find("Move Silently "), 14, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)MOVESILENTLY, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Open Lock ") != string::npos)
			{
				Substring.replace(Substring.find("Open Lock "), 10, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)OPENLOCK, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Perform ") != string::npos)
			{
				Substring.replace(Substring.find("Perform "), 8, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)PERFORM, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Repair ") != string::npos)
			{
				Substring.replace(Substring.find("Repair "), 7, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)REPAIR, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Search ") != string::npos)
			{
				Substring.replace(Substring.find("Search "), 7, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SEARCH, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Spellcraft ") != string::npos)
			{
				Substring.replace(Substring.find("Spellcraft "), 11, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SPELLCRAFT, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Spot ") != string::npos)
			{
				Substring.replace(Substring.find("Spot "), 5, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SPOT, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Swim ") != string::npos)
			{
				Substring.replace(Substring.find("Swim "), 5, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SWIM, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Tumble ") != string::npos)
			{
				Substring.replace(Substring.find("Tumble "), 7, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)TUMBLE, AtLevel))
					return PREREQ_FAIL;
			}
			if (Substring.find("Use Magic Device ") != string::npos)
			{
				Substring.replace(Substring.find("Use Magic Device "), 17, "");
				ReqAbility = atoi(Substring.c_str());
				if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)UMD, AtLevel))
					return PREREQ_FAIL;
			}
			PrereqList.replace(PrereqList.find("Skill "), 6, "");
		}
	}

    //Certain feats lock out other lines of feats.
    //check the player's selected feats and see if any of them cause this feat to become illegal
    Index = 0;
    FeatCheckIndex = Character.GetFeat(AtLevel, Index);
    while (FeatCheckIndex != -1)
        {
        CheckFeat = Data.GetFeatPointer(FeatCheckIndex);
        for (unsigned int i=0; i<CheckFeat->LockFeat.size(); i++)
            {
            if (CheckFeat->LockFeat[i] == Name)
                return PREREQ_FAIL;
            }
        Index++;
        FeatCheckIndex = Character.GetFeat(AtLevel, Index);
        }

    //last check, look at the NeedsOne catagory (only one of these needs to come up true to pass)
    if (NeedsOne.size() == 0)
        return PREREQ_PASS;

	for (unsigned int i=0; i<NeedsOne.size(); i++)
		{
	    PrereqList = NeedsOne[i];
		while (PrereqList.find("Feat ") != string::npos)
			{
	        Substring = PrereqList.substr(PrereqList.find("Feat "));
		    Substring.replace(Substring.find("Feat "), 5, "");
	        if (Substring.find(",") != string::npos)
		        Substring.erase(Substring.find(","), Substring.size()-Substring.find(","));
			if (Character.HasFeat(Substring, AtLevel) == true)
	            return PREREQ_PASS;
		    PrereqList.replace(PrereqList.find("Feat "), 5, "");
			}
		}

    //check the player's race (NeedsOne)
    for (unsigned int i=0; i<NeedsOne.size(); i++)
        {
        if (NeedsOne[i].find("Race ") != string::npos)
            {
            Substring = NeedsOne[i];
            Substring.replace(Substring.find("Race"), 4, "");
            if (Substring.find("Drow") != string::npos)
                {
                if (CharacterRace == DROW)
                    return PREREQ_PASS;
                }
            if (Substring.find("Dwarf") != string::npos)
                {
                if (CharacterRace == DWARF)
                    return PREREQ_PASS;
                }
            if (Substring.find(" Elf") != string::npos)
                {
                if (CharacterRace == ELF)
                    return PREREQ_PASS;
                }
            if (Substring.find("Halfling") != string::npos)
                {
                if (CharacterRace == HALFLING)
                    return PREREQ_PASS;
                }
            if (Substring.find("Human") != string::npos)
                {
                if (CharacterRace == HUMAN)
                    return PREREQ_PASS;
                }
            if (Substring.find("Warforged") != string::npos)
                {
                if (CharacterRace == WARFORGED)
                    return PREREQ_PASS;
                }
            if (Substring.find("Half-Elf") != string::npos)
                {
                if (CharacterRace == HALFELF)
                    return PREREQ_PASS;
                }
            if (Substring.find("Half-Orc") != string::npos)
                {
                if (CharacterRace == HALFORC)
                    return PREREQ_PASS;
                }
            if (Substring.find("Bladeforged") != string::npos)
                {
                if (CharacterRace == BLADEFORGED)
                    return PREREQ_PASS;
                }
            if (Substring.find("Morninglord") != string::npos)
                {
                if (CharacterRace == MORNINGLORD)
                    return PREREQ_PASS;
                }
            if (Substring.find("Purple Dragon Knight") != string::npos)
                {
                if (CharacterRace == PURPLEDRAGONKNIGHT)
                    return PREREQ_PASS;
                }
			if (Substring.find("Shadar-Kai") != string::npos)
				{
				if (CharacterRace == SHADARKAI)
					return PREREQ_PASS;
				}
			if (Substring.find(" Gnome") != string::npos)
			{
				if (CharacterRace == GNOME)
					return PREREQ_PASS;
				}
			if (Substring.find("Deep-Gnome") != string::npos)
				{
				if (CharacterRace == DEEPGNOME)
					return PREREQ_PASS;
                }
			if (Substring.find("Dragonborn") != string::npos)
			{
				if (CharacterRace == DRAGONBORN)
					return PREREQ_PASS;
			}
            }
        }

    //check the player's class (NeedsOne)
	for (unsigned int i=0; i<NeedsOne.size(); i++)
		{
	    PrereqList = NeedsOne[i];
		while (PrereqList.find("Class ") != string::npos)
			{
		    Substring = PrereqList.substr(PrereqList.find("Class "));
			Substring.replace(Substring.find("Class "), 6, "");
	        if (Substring.find(",") != string::npos)
		        Substring.erase(Substring.find(","), Substring.size()-Substring.find(","));
			if (Substring.find_last_of(" ") != string::npos)
				{
				RequiredLevel = atoi(Substring.substr(Substring.find_last_of(" ")).c_str());
				Substring.erase(Substring.find_last_of(" "), Substring.size()-Substring.find_last_of(" "));
				}
			Levels = Character.GetClassLevel(Data.GetClassIndex(Substring), AtLevel);
			if (Levels >= RequiredLevel)
	            return PREREQ_PASS;
			PrereqList.replace(PrereqList.find("Class "), 6, "");
			}
		}
	//check the player's Alignment (NeedsOne)
	for (unsigned int i = 0; i<NeedsOne.size(); i++)
	{
		if (NeedsOne[i].find("Alignment ") != string::npos)
		{
			Substring = NeedsOne[i];
			Substring.replace(Substring.find("Alignment"), 9, "");
			if (Substring.find("Lawful Good") != string::npos)
			{
				if (CharacterAlignment == LAWFULGOOD)
					return PREREQ_PASS;
			}
			if (Substring.find("Neutral Good") != string::npos)
			{
				if (CharacterAlignment == NEUTRALGOOD)
					return PREREQ_PASS;
			}
			if (Substring.find("Chaotic Good") != string::npos)
			{
				if (CharacterAlignment == CHAOTICGOOD)
					return PREREQ_PASS;
			}
			if (Substring.find("Lawful Neutral") != string::npos)
			{
				if (CharacterAlignment == LAWFULNEUTRAL)
					return PREREQ_PASS;
			}
			if (Substring.find("True Neutral") != string::npos)
			{
				if (CharacterAlignment == TRUENEUTRAL)
					return PREREQ_PASS;
			}
			if (Substring.find("Chaotic Neutral") != string::npos)
			{
				if (CharacterAlignment == CHAOTICNEUTRAL)
					return PREREQ_PASS;
			}
		}
	}

    return PREREQ_FAIL;
    }
    
//---------------------------------------------------------------------------
FEATAQUIRETYPE FeatDataClass::HasRace(RACE Race, unsigned int AtLevel)
    {
    for (unsigned int i=0; i<RaceType.size(); i++)
        {
        if (RaceType[i] == Race && AtLevel >= Level[i])
            return AquireType[i];
        }
    return FEATNOAQUIRE;
    }

//---------------------------------------------------------------------------
bool FeatDataClass::HasClass(CLASS Class, unsigned int AtLevel, FEATAQUIRETYPE Type)
    {
    int RaceOffset;

    RaceOffset = RaceType.size();
    for (unsigned int i=0; i<ClassType.size(); i++)
        {
        if (ClassType[i] == Class && AtLevel >= Level[RaceOffset+i])
            {
            if (AquireType[RaceOffset+i] == Type)
				return true;
			if (Type == FEATAQUIREANY)	
				return true;
            }
        }
    return false;
    }
    
//---------------------------------------------------------------------------
int FeatDataClass::GetFeatAutoClassLevel(CLASS Class)
    {
    int Offset;

    for (unsigned int i=0; i<ClassType.size(); i++)
        {
        if (ClassType[i] == Class)
            {
            Offset = RaceType.size();
            if (AquireType[i+Offset] == FEATAQUIREAUTOMATIC || AquireType[i+Offset] == FEATAQUIREAUTONOPREREQ)
                {
                return Level[i+Offset];
                }
            }
        }
    return -1;
    }

//---------------------------------------------------------------------------
string FeatDataClass::GetPrereqString(int CharacterLevel)
	{
    ostringstream ss;
    string Color;
	int RaceOffset;
	bool HasRace;
	bool HasClass;
	bool ReqOneMet;
	HasRace = false;
	HasClass = false;
	ReqOneMet = false;
    
    //start off with the race/class list
    ss << "{\\ul Race and Class Requirements:} \\par ";
	for (unsigned int i = 0; i < RaceType.size(); i++)
	{
		if (Character.GetRace() == RaceType[i])
			HasRace = true;
	}
	RaceOffset = RaceType.size();
	for (unsigned int i = 0; i < ClassType.size(); i++)
	{
		if (Character.GetClassLevel(ClassType[i], CharacterLevel) >= static_cast<int>(Level[i + RaceOffset]))
			HasClass = true;
	}	
	for (unsigned int i=0; i<RaceType.size(); i++)
		{
        if (Character.GetRace() == RaceType[i])
            Color = "{\\cf4 ";
        else
			if (HasRace || HasClass)
				Color = "{\\cf6 ";
			else
				Color = "{\\cf1 ";
		ss << Color;
		ss << ConvertRaceTypeToString(RaceType[i]) << " Level ";
		ss << Level[i] << " (";
		ss << ConvertAquireTypeToString(AquireType[i], Level[i]);
		ss << ")} \\par ";
		}


	for (unsigned int i=0; i<ClassType.size(); i++)
		{
        if (Character.GetClassLevel(ClassType[i], CharacterLevel) >= static_cast<int>(Level[i+RaceOffset]))
            Color = "{\\cf4 ";
        else
			if(HasClass || HasRace)
				Color = "{\\cf6 ";
			else
				Color = "{\\cf1 ";
		ss << Color;
		ss << ConvertClassTypeToString(ClassType[i]) << " Level ";
		ss << Level[i+RaceOffset] << " (";
		ss << ConvertAquireTypeToString(AquireType[i+RaceOffset], Level[i+RaceOffset]);
		ss << ")} \\par ";
		}
		
	//add in the required (NEEDSALL) prereqs
	ss << " \\par ";
	for (unsigned int i=0; i<NeedsAll.size(); i++)
		{
		Color = GetPrereqColorCode(NeedsAll[i], CharacterLevel, true);
        ss << Color << "Requires: " << NeedsAll[i] << "} \\par ";
		}
    
	//add in the required (NEEDSONE) prereqs
	for (unsigned int i=0; i<NeedsOne.size(); i++)
		{
		Color = GetPrereqColorCode(NeedsOne[i], CharacterLevel, false);
        ss << Color << "Requires one of: " << NeedsOne[i] << "} \\par ";
		}

	return ss.str();
	}
	
//---------------------------------------------------------------------------
string FeatDataClass::GetPrereqColorCode(string Requirement, int CharacterLevel, bool RequireAll)
	{
	string FailColor;
	string PassColor;
	string Substring;
	int ReqAbility;
	int Levels;
	int RequiredLevel;

	if (RequireAll == true)
		FailColor = "{\\cf3 ";
	else
		FailColor = "{\\cf1 ";
	PassColor = "{\\cf4 ";	

	//feat requirements
	if (Requirement.find("Feat ") != string::npos)
		{
        Substring = Requirement;
        Substring.replace(Substring.find("Feat "), 5, "");
        if (Character.HasFeat(Substring, CharacterLevel) == false)
            return FailColor;
        else
			return PassColor;
		}

	//race requirements
	if (Requirement.find("Race ") != string::npos)
		{
        Substring = Requirement;
        Substring.replace(Substring.find("Race "), 5, "");
        if (Character.GetRaceString() != Substring)
            return FailColor;
        else
            return PassColor;
		}
		
	//class requirements
	if (Requirement.find("Class ") != string::npos)
		{
	    Substring = Requirement;
		Substring.replace(Substring.find("Class "), 6, "");
		if (Substring.find_last_of(" ") != string::npos)
			{
			RequiredLevel = atoi(Substring.substr(Substring.find_last_of(" ")).c_str());
			Substring.erase(Substring.find_last_of(" "), Substring.size()-Substring.find_last_of(" "));
			}
		Levels = Character.GetClassLevel(Data.GetClassIndex(Substring), CharacterLevel);
		if (Levels < RequiredLevel)
            return FailColor;
        else
	        return PassColor;
		}

	//creation requirement
	if (Requirement.find("Creation") != string::npos)
		{
		if (CharacterLevel == 1)
			return PassColor;
		else
			return FailColor;
		}
		
	//ability requirement
	if (Requirement.find("Ability ") != string::npos)
		{
        Substring = Requirement;
        Substring.replace(Substring.find("Ability "), 8, "");
		if (Substring.find("Strength ") != string::npos)
			{
			Substring.replace(Substring.find("Strength "), 9, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetAbility((int)STRENGTH, CharacterLevel))
				return FailColor;
			else
				return PassColor;
			}
		if (Substring.find("Dexterity ") != string::npos)
			{
            Substring.replace(Substring.find("Dexterity "), 10, "");
	        ReqAbility = atoi(Substring.c_str());
		    if (ReqAbility > Character.GetAbility((int)DEXTERITY, CharacterLevel))
				return FailColor;
			else
				return PassColor;
            }
	    if (Substring.find("Constitution ") != string::npos)
		    {
			Substring.replace(Substring.find("Constitution "), 13, "");
            ReqAbility = atoi(Substring.c_str());
	        if (ReqAbility > Character.GetAbility((int)CONSTITUTION, CharacterLevel))
				return FailColor;
			else
				return PassColor;
			}
        if (Substring.find("Intelligence ") != string::npos)
	        {
		    Substring.replace(Substring.find("Intelligence "), 13, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetAbility((int)INTELLIGENCE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
	        }
		if (Substring.find("Wisdom ") != string::npos)
            {
	        Substring.replace(Substring.find("Wisdom "), 7, "");
		    ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetAbility((int)WISDOM, CharacterLevel))
				return FailColor;
			else
				return PassColor;
	        }
		if (Substring.find("Charisma ") != string::npos)
			{
            Substring.replace(Substring.find("Charisma "), 9, "");
	        ReqAbility = atoi(Substring.c_str());
		    if (ReqAbility > Character.GetAbility((int)CHARISMA, CharacterLevel))
				return FailColor;
			else
				return PassColor;
            }
		}
		
	//BAB requirement
	if (Requirement.find("BAB ") != string::npos)
		{
        Substring = Requirement;
        Substring.replace(Substring.find("BAB "), 4, "");
	    ReqAbility = atoi(Substring.c_str());
		if (Character.CalculateBAB(CharacterLevel) < ReqAbility)
			return FailColor;
		else
			return PassColor;
		}

	//Skill requirement
	if (Requirement.find("Skill ") != string::npos)
	{
		Substring = Requirement;
		Substring.replace(Substring.find("Skill "), 6, "");
		if (Substring.find("Balance ") != string::npos)
		{
			Substring.replace(Substring.find("Balance "), 8, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)BALANCE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Bluff ") != string::npos)
		{
			Substring.replace(Substring.find("Bluff "), 10, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)BLUFF, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Concentration ") != string::npos)
		{
			Substring.replace(Substring.find("Concentration "), 14, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)CONCENTRATION, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Diplomacy ") != string::npos)
		{
			Substring.replace(Substring.find("Diplomacy "), 10, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)DIPLOMACY, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Disable Device ") != string::npos)
		{
			Substring.replace(Substring.find("Disable Device "), 15, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)DISABLEDEVICE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Haggle ") != string::npos)
		{
			Substring.replace(Substring.find("Haggle "), 7, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)HAGGLE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Heal ") != string::npos)
		{
			Substring.replace(Substring.find("Heal "), 5, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)HEAL, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Hide ") != string::npos)
		{
			Substring.replace(Substring.find("Hide "), 5, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)HIDE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Intimidate ") != string::npos)
		{
			Substring.replace(Substring.find("Intimidate "), 11, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)INTIMIDATE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Jump ") != string::npos)
		{
			Substring.replace(Substring.find("Jump "), 5, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)JUMP, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Listen ") != string::npos)
		{
			Substring.replace(Substring.find("Listen "), 7, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)LISTEN, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Move Silently ") != string::npos)
		{
			Substring.replace(Substring.find("Move Silently "), 14, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)MOVESILENTLY, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Open Lock ") != string::npos)
		{
			Substring.replace(Substring.find("Open Lock "), 10, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)OPENLOCK, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Perform ") != string::npos)
		{
			Substring.replace(Substring.find("Perform "), 8, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)PERFORM, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Repair ") != string::npos)
		{
			Substring.replace(Substring.find("Repair "), 7, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)REPAIR, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Search ") != string::npos)
		{
			Substring.replace(Substring.find("Search "), 7, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SEARCH, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Spellcraft ") != string::npos)
		{
			Substring.replace(Substring.find("Spellcraft "), 11, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SPELLCRAFT, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Spot ") != string::npos)
		{
			Substring.replace(Substring.find("Spot "), 5, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SPOT, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Swim ") != string::npos)
		{
			Substring.replace(Substring.find("Swim "), 5, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)SWIM, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Tumble ") != string::npos)
		{
			Substring.replace(Substring.find("Tumble "), 7, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)TUMBLE, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
		if (Substring.find("Use Magic Device ") != string::npos)
		{
			Substring.replace(Substring.find("Use Magic Device "), 17, "");
			ReqAbility = atoi(Substring.c_str());
			if (ReqAbility > Character.GetTotalSkillPointsSpentDisplay((SKILLS)UMD, CharacterLevel))
				return FailColor;
			else
				return PassColor;
		}
	}

	return FailColor;
	}
	
//---------------------------------------------------------------------------
void FeatDataClass::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}
	
//---------------------------------------------------------------------------
string FeatDataClass::ConvertRaceTypeToString(RACE Race)
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
		default:
			return "Unknown Race";
		}
	}

//---------------------------------------------------------------------------
string FeatDataClass::ConvertClassTypeToString(CLASS Class)
	{
	switch (Class)
		{
		case FIGHTER:
			return "Fighter";
		case PALADIN:
			return "Paladin";
		case BARBARIAN:
			return "Barbarian";
		case MONK:
			return "Monk";
		case ROGUE:
			return "Rogue";
		case RANGER:
			return "Ranger";
		case CLERIC:
			return "Cleric";
		case WIZARD:
			return "Wizard";
		case SORCERER:
			return "Sorcerer";
		case BARD:
			return "Bard";
		case FAVORED_SOUL:
			return "Favored Soul";
		case ARTIFICER:
			return "Artificer";
		case DRUID:
			return "Druid";
		case WARLOCK:
			return "Warlock";
		default:
			return "Unknown Class";
		}
	}

//---------------------------------------------------------------------------
string FeatDataClass::ConvertAquireTypeToString(FEATAQUIRETYPE Type, int Level)
	{
	switch (Type)
		{
		case FEATAQUIREAUTOMATIC:
			{
			if (Level != 1)
				return "Automatic with prereqs";
			else
				return "Automatic";
			}
		case FEATAQUIREAUTONOPREREQ:
			return "Automatic ignore prereqs";
		case FEATAQUIRETRAIN:
			return "Trainable";
		default:
			return "Unknown Aquire Type";
		}
	}

