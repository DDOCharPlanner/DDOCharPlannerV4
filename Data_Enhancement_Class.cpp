#include "Data_Enhancement_Class.h"
#include "InterfaceManagerClass.h"

//---------------------------------------------------------------------------
Data_Enhancement_Class::Data_Enhancement_Class()
	{
	TreeIndex = ENHT_UNKNOWN;
	EnhancementIndex = 0;
	MultiSelection = false;
	MultiSelectorName = "";
	MultiSelectorSlot = 0;
	Name = "";
	Tree = "";
	RaceTree = false;
	RaceAATree = false;
	Race = RACENONE;
	Class = CLASSNONE;
	Level = 0;
	Slot = 0;
	Ranks = 0;
	TypeActive = false;
	APCost = 0;
	for (unsigned int i=0; i<3; i++)
		{
		Description[i] = "";
		Requirement[i].clear();
		RequirementOne[i].clear();
		Lock[i].clear();
		Mod[i].clear();
		ModName[i].clear();
		ModValue[i].clear();
		}
	EnhancementIcon.Name = "";
	EnhancementIcon.Graphic = nullptr;
	EnhancementIcon.Mask = nullptr;
	EnhancementIcon.Width = 0;
	EnhancementIcon.Height = 0;
	APRequirement = 0;
	ClassLevelRequirement = 0;
	CharacterLevelRequirement = 0;
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class::~Data_Enhancement_Class()
	{
    DeleteObject(EnhancementIcon.Graphic);
    DeleteObject(EnhancementIcon.Mask);
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class::Data_Enhancement_Class(const Data_Enhancement_Class &source)
	{
	TreeIndex = source.TreeIndex;
	EnhancementIndex = source.EnhancementIndex;
	MultiSelection = source.MultiSelection;
	MultiSelectorName = source.MultiSelectorName;
	MultiSelectorSlot = source.MultiSelectorSlot;
	Name = source.Name;
	Tree = source.Tree;
	RaceTree = source.RaceTree;
	RaceAATree = source.RaceAATree;
	Race = source.Race;
	Class = source.Class;
	Level = source.Level;
	Slot = source.Slot;
	Ranks = source.Ranks;
	TypeActive = source.TypeActive;
	APCost = source.APCost;
	for (unsigned int i=0; i<3; i++)
		{
		Description[i] = source.Description[i];
		for (unsigned int j=0; j<source.Requirement[i].size(); j++)
			Requirement[i].push_back(source.Requirement[i][j]);
		for (unsigned int j=0; j<source.RequirementOne[i].size(); j++)
			RequirementOne[i].push_back(source.RequirementOne[i][j]);
		for (unsigned int j=0; j<source.Lock[i].size(); j++)
			Lock[i].push_back(source.Lock[i][j]);
		for (unsigned int j=0; j<source.Mod[i].size(); j++)
			Mod[i].push_back(source.Mod[i][j]);
		for (unsigned int j=0; j<source.ModName[i].size(); j++)
			ModName[i].push_back(source.ModName[i][j]);
		for (unsigned int j=0; j<source.ModValue[i].size(); j++)
			ModValue[i].push_back(source.ModValue[i][j]);
		}
	EnhancementIcon.Name = source.EnhancementIcon.Name;
	EnhancementIcon.Graphic = (HBITMAP)CopyImage(source.EnhancementIcon.Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	EnhancementIcon.Mask = (HBITMAP)CopyImage(source.EnhancementIcon.Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	EnhancementIcon.Width = source.EnhancementIcon.Width;
	EnhancementIcon.Height = source.EnhancementIcon.Height;
	APRequirement = source.APRequirement;
	ClassLevelRequirement = source.ClassLevelRequirement;
	CharacterLevelRequirement = source.CharacterLevelRequirement;
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class& Data_Enhancement_Class::operator=(const Data_Enhancement_Class &source)
	{
	TreeIndex = source.TreeIndex;
	EnhancementIndex = source.EnhancementIndex;
	MultiSelection = source.MultiSelection;
	MultiSelectorName = source.MultiSelectorName;
	MultiSelectorSlot = source.MultiSelectorSlot;
	Name = source.Name;
	Tree = source.Tree;
	RaceTree = source.RaceTree;
	RaceAATree = source.RaceAATree;
	Race = source.Race;
	Class = source.Class;
	Level = source.Level;
	Slot = source.Slot;
	APCost = source.APCost;
	for (unsigned int i=0; i<3; i++)
		{
		Description[i] = source.Description[i];
		for (unsigned int j=0; j<source.Requirement[i].size(); j++)
			Requirement[i].push_back(source.Requirement[i][j]);
		for (unsigned int j=0; j<source.RequirementOne[i].size(); j++)
			RequirementOne[i].push_back(source.RequirementOne[i][j]);
		for (unsigned int j=0; j<source.Lock[i].size(); j++)
			Lock[i].push_back(source.Lock[i][j]);
		for (unsigned int j=0; j<source.Mod[i].size(); j++)
			Mod[i].push_back(source.Mod[i][j]);
		for (unsigned int j=0; j<source.ModName[i].size(); j++)
			ModName[i].push_back(source.ModName[i][j]);
		for (unsigned int j=0; j<source.ModValue[i].size(); j++)
			ModValue[i].push_back(source.ModValue[i][j]);
		}
	EnhancementIcon.Name = source.EnhancementIcon.Name;
	EnhancementIcon.Graphic = (HBITMAP)CopyImage(source.EnhancementIcon.Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	EnhancementIcon.Mask = (HBITMAP)CopyImage(source.EnhancementIcon.Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	EnhancementIcon.Width = source.EnhancementIcon.Width;
	EnhancementIcon.Height = source.EnhancementIcon.Height;
	APRequirement = source.APRequirement;
	ClassLevelRequirement = source.ClassLevelRequirement;
	CharacterLevelRequirement = source.CharacterLevelRequirement;

	return *this;
	}

//---------------------------------------------------------------------------
void Data_Enhancement_Class::InitializeEnhancement(string Data, ENHANCEMENT_TREE TIndex, unsigned int EIndex)
	{
    #define NUMKEYWORDS 31

	string KeywordString[NUMKEYWORDS];
	string EnhancementLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	string Substring;
	size_t MSLOTLoc;
	ENH_Requirement NewRequirement;
	string Reqstring;
	size_t ReqEndLoc;

	TreeIndex = TIndex;
	EnhancementIndex = EIndex;
	Race = SetTreeRace(TreeIndex);
	Class = SetTreeClass(TreeIndex);

	NewRequirement.ReqType = ENH_UNKNOWN;
	NewRequirement.ReqName = "";
	NewRequirement.ReqTree = "";
	NewRequirement.ReqRank = 0;
	NewRequirement.ReqLevel = 0;
	NewRequirement.ReqSlot = 0;
	
    //parse the SelectorData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "MULTI: ";
	KeywordString[1] = "MSLOT: ";
	KeywordString[2] = "NAME: ";
	KeywordString[3] = "TREE: ";
	KeywordString[4] = "LEVEL: ";
	KeywordString[5] = "SLOT: ";
	KeywordString[6] = "RANKS: ";
	KeywordString[7] = "TYPE: ";
	KeywordString[8] = "COST: ";
	KeywordString[9] = "DESC1: ";
	KeywordString[10] = "REQ1: ";
	KeywordString[11] = "REQONE1: ";
	KeywordString[12] = "LOCK1: ";
	KeywordString[13] = "MOD1: ";
	KeywordString[14] = "MODNAME1: ";
	KeywordString[15] = "MODVALUE1: ";
	KeywordString[16] = "DESC2: ";
	KeywordString[17] = "REQ2: ";
	KeywordString[18] = "REQONE2: ";
	KeywordString[19] = "LOCK2: ";
	KeywordString[20] = "MOD2: ";
	KeywordString[21] = "MODNAME2: ";
	KeywordString[22] = "MODVALUE2: ";
	KeywordString[23] = "DESC3: ";
	KeywordString[24] = "REQ3: ";
	KeywordString[25] = "REQONE3: ";
	KeywordString[26] = "LOCK3: ";
	KeywordString[27] = "MOD3: ";
	KeywordString[28] = "MODNAME3: ";
	KeywordString[29] = "MODVALUE3: ";
	KeywordString[30] = "ICON: ";

	MSLOTLoc = 0;
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		EnhancementLine[i] = "";
		if (Data.find(KeywordString[i], MSLOTLoc) != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = Data.find(KeywordString[i], MSLOTLoc);
			EndLoc = Data.find(";", StartLoc);
			//EndLoc = Data.find(";", Data.find(KeywordString[i])); 
			EnhancementLine[i] = Data.substr(Data.find(KeywordString[i], MSLOTLoc), EndLoc-StartLoc);
			if (i == 1)
				MSLOTLoc = EndLoc + 1;	//we need to mark this location when we have the keyword MSLOT:
			//drop the keyword from the line string, we don't need it now
			EnhancementLine[i].erase(0, KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
        {
        switch (i)
            {
            case 0:     //part of a multi-selector?
				{
				if (EnhancementLine[i] != "")
					{
					MultiSelection = true;
					MultiSelectorName = EnhancementLine[i];
					}
				break;
				}
            case 1:     //multi-selector slot
				{
                MultiSelectorSlot = atoi(EnhancementLine[i].c_str());
				break;
				}
            case 2:     //the name
				{
                Name = EnhancementLine[i];
				break;
				}
			case 3:		//the tree
				{
                Tree = EnhancementLine[i];
				RaceTree = IsRaceTree();
				RaceAATree = IsRaceAATree();
				break;
				}
			case 4:		//the level
				{
                Level = atoi(EnhancementLine[i].c_str());
				break;
				}
			case 5:		//the slot
				{
                Slot = atoi(EnhancementLine[i].c_str());
				APRequirement = CalculateAPRequirement();
				ClassLevelRequirement = CalculateClassLevelRequirement();
				CharacterLevelRequirement = CalculateCharacterLevelRequirement();
				break;
				}
			case 6:		//number of ranks
				{
                Ranks = atoi(EnhancementLine[i].c_str());
				break;
				}
			case 7:		//active or passive?
				{
                if (EnhancementLine[i].find("Active") != string::npos)
					TypeActive = true;
				break;
				}
			case 8:		//AP Cost
				{
                APCost = atoi(EnhancementLine[i].c_str());
				break;
				}
			case 9:		//the description 1
				{
				Description[0] = EnhancementLine[i];
				break;
				}
			case 10:		//the requirement list 1
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					Requirement[0].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqRank = atoi(Reqstring.c_str());

							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;
							Substring.erase(0, ReqEndLoc+2);
							
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqLevel = atoi(Reqstring.c_str());
							Substring.erase(0, ReqEndLoc+1);
							
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqSlot = atoi(Reqstring.c_str());
							Substring.erase(0, ReqEndLoc + 1);

							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;
						}
					if (Substring.find("Class: ") != string::npos)
						{
						//normally class requirement is determined by the slot position, but in a few cases, there is a class requirement in some race trees
						// (e.g. Half-Orc Power Rage)
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_CLASS;
						Substring.erase(0, 7);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqLevel = atoi(Reqstring.c_str());
							}
						}	
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Requirement[0].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;
						}
					if (Substring.find("Class: ") != string::npos)
						{
						//normally class requirement is determined by the slot position, but in a few cases, there is a class requirement in some race trees
						// (e.g. Half-Orc Power Rage)
						Requirement[0][Requirement[0].size()-1].ReqType = ENH_CLASS;
						Substring.erase(0, 7);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[0][Requirement[0].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[0][Requirement[0].size()-1].ReqLevel = atoi(Reqstring.c_str());
							}
						}	
					}
				break;
				}
			case 11:		//the require one list 1
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					RequirementOne[0].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[0][RequirementOne[0].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[0][RequirementOne[0].size()-1].ReqName = Reqstring;
							Substring.erase(0, ReqEndLoc+2);

							if (Substring.find("Tree:") != string::npos)
							{
								Substring.erase(0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								RequirementOne[0][RequirementOne[0].size() - 1].ReqTree = Reqstring;	//tree
								Substring.erase(0, ReqEndLoc + 1);

							}

							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqLevel = atoi(Reqstring.c_str());
							Substring.erase(0, ReqEndLoc+1);

							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqSlot = atoi(Reqstring.c_str());
							Substring.erase(0, ReqEndLoc+1);

							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[0][RequirementOne[0].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[0][RequirementOne[0].size()-1].ReqName = Reqstring;

							if (Substring.find("Tree:") != string::npos)
							{
								Substring.erase(0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								RequirementOne[0][RequirementOne[0].size() - 1].ReqTree = Reqstring;	//tree
								Substring.erase(0, ReqEndLoc + 1);

							}

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[0][RequirementOne[0].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[0][RequirementOne[0].size()-1].ReqName = Reqstring;
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					RequirementOne[0].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[0][RequirementOne[0].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[0][RequirementOne[0].size()-1].ReqName = Reqstring;	//Name
							Substring.erase(0, ReqEndLoc+2);

							if (Substring.find("Tree:") != string::npos)
							{
								Substring.erase(0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								RequirementOne[0][RequirementOne[0].size() - 1].ReqTree = Reqstring;	//tree
								Substring.erase(0, ReqEndLoc + 1);
								
							}
							
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level
							Substring.erase(0, ReqEndLoc+1);

							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot
							Substring.erase(0, ReqEndLoc+1);

							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[0][RequirementOne[0].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[0][RequirementOne[0].size()-1].ReqName = Reqstring;		//Name
							Substring.erase(0, ReqEndLoc+2);
							
							if (Substring.find("Tree:") != string::npos)
							{
								Substring.erase(0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								RequirementOne[0][RequirementOne[0].size() - 1].ReqTree = Reqstring;	//tree
								Substring.erase(0, ReqEndLoc + 1);

							}

							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level
							Substring.erase(0, ReqEndLoc+1);

							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot
							Substring.erase(0, ReqEndLoc+1);
							
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[0][RequirementOne[0].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[0][RequirementOne[0].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[0][RequirementOne[0].size()-1].ReqName = Reqstring;
						}
					}
				break;
				}
			case 12:		//the lock list 1
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					Lock[0].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[0][Lock[0].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[0][Lock[0].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);	
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[0][Lock[0].size()-1].ReqTree = Reqstring;
								Substring.erase(0, ReqEndLoc+1);
								}

							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[0][Lock[0].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[0][Lock[0].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[0][Lock[0].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Lock[0].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[0][Lock[0].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[0][Lock[0].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[0][Lock[0].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[0][Lock[0].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[0][Lock[0].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[0][Lock[0].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[0][Lock[0].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					}
				break;
				}
			case 13:		//the modification list 1
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					Mod[0].push_back(Substring);
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Mod[0].push_back(Substring);
					}
				break;
				}
			case 14:		//the modification name 1
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					ModName[0].push_back(Substring);
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					ModName[0].push_back(Substring);
					}
				break;
				}
			case 15:		//the modification value 1
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					ModValue[0].push_back(atoi(Substring.c_str()));
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					ModValue[0].push_back(atoi(Substring.c_str()));
					}
				break;
				}
			case 16:		//the description 2
				{
				Description[1] = EnhancementLine[i];
				break;
				}
			case 17:		//the requirement list 2
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					Requirement[1].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;
						}
					if (Substring.find("Class: ") != string::npos)
						{
						//normally class requirement is determined by the slot position, but in a few cases, there is a class requirement in some race trees
						// (e.g. Half-Orc Power Rage)
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_CLASS;
						Substring.erase(0, 7);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqLevel = atoi(Reqstring.c_str());
							}
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Requirement[1].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;
						}
					if (Substring.find("Class: ") != string::npos)
						{
						//normally class requirement is determined by the slot position, but in a few cases, there is a class requirement in some race trees
						// (e.g. Half-Orc Power Rage)
						Requirement[1][Requirement[1].size()-1].ReqType = ENH_CLASS;
						Substring.erase(0, 7);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[1][Requirement[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[1][Requirement[1].size()-1].ReqLevel = atoi(Reqstring.c_str());
							}
						}
					}
				break;
				}
			case 18:		//the require one list 2
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					RequirementOne[1].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[1][RequirementOne[1].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[1][RequirementOne[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[1][RequirementOne[1].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[1][RequirementOne[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[1][RequirementOne[1].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[1][RequirementOne[1].size()-1].ReqName = Reqstring;
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					RequirementOne[1].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[1][RequirementOne[1].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[1][RequirementOne[1].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[1][RequirementOne[1].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[1][RequirementOne[1].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[1][RequirementOne[1].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[1][RequirementOne[1].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[1][RequirementOne[1].size()-1].ReqName = Reqstring;
						}
					}
				break;
				}
			case 19:		//the lock list 2
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					Lock[1].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[1][Lock[1].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[1][Lock[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[1][Lock[1].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[1][Lock[1].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[1][Lock[1].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[1][Lock[1].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Lock[1].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[1][Lock[1].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[1][Lock[1].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[1][Lock[1].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[1][Lock[1].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[1][Lock[1].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[1][Lock[1].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[1][Lock[1].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					}
				break;
				}
			case 20:		//the modification list 2
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					Mod[1].push_back(Substring);
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Mod[1].push_back(Substring);
					}
				break;
				}
			case 21:		//the modification name 2
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					ModName[1].push_back(Substring);
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					ModName[1].push_back(Substring);
					}
				break;
				}
			case 22:		//the modification value 2
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					ModValue[1].push_back(atoi(Substring.c_str()));
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					ModValue[1].push_back(atoi(Substring.c_str()));
					}
				break;
				}
			case 23:		//the description 3
				{
				Description[2] = EnhancementLine[i];
				break;
				}
			case 24:		//the requirement list 3
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					Requirement[2].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;
						}
					if (Substring.find("Class: ") != string::npos)
						{
						//normally class requirement is determined by the slot position, but in a few cases, there is a class requirement in some race trees
						// (e.g. Half-Orc Power Rage)
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_CLASS;
						Substring.erase(0, 7);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqLevel = atoi(Reqstring.c_str());
							}
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Requirement[2].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;
						}
					if (Substring.find("Class: ") != string::npos)
						{
						//normally class requirement is determined by the slot position, but in a few cases, there is a class requirement in some race trees
						// (e.g. Half-Orc Power Rage)
						Requirement[2][Requirement[2].size()-1].ReqType = ENH_CLASS;
						Substring.erase(0, 7);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[2][Requirement[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[2][Requirement[2].size()-1].ReqLevel = atoi(Reqstring.c_str());
							}
						}
					}
				break;
				}
			case 25:		//the require one list 3
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					RequirementOne[2].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[2][RequirementOne[2].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[2][RequirementOne[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[2][RequirementOne[2].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[2][RequirementOne[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[2][RequirementOne[2].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[2][RequirementOne[2].size()-1].ReqName = Reqstring;
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					RequirementOne[2].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[2][RequirementOne[2].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[2][RequirementOne[2].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[2][RequirementOne[2].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[2][RequirementOne[2].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[2][RequirementOne[2].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[2][RequirementOne[2].size()-1].ReqType = ENH_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[2][RequirementOne[2].size()-1].ReqName = Reqstring;
						}
					}
				break;
				}
			case 26:		//the lock list 3
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					//now that we have individual string, lets break it down to its components
					Lock[2].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[2][Lock[2].size()-1].ReqType = ENH_ENHANCEMENT;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[2][Lock[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[2][Lock[2].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[2][Lock[2].size()-1].ReqType = ENH_MULTIENHANCEMENT;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[2][Lock[2].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[2][Lock[2].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqLevel = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Lock[2].push_back(NewRequirement);
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[2][Lock[2].size()-1].ReqType = ENH_ENHANCEMENT;  //Type
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[2][Lock[2].size()-1].ReqName = Reqstring;	//Name

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[2][Lock[2].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqLevel = atoi(Reqstring.c_str());  //Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[2][Lock[2].size()-1].ReqType = ENH_MULTIENHANCEMENT;	//Type
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[2][Lock[2].size()-1].ReqName = Reqstring;		//Name

							Substring.erase(0, ReqEndLoc+2);
							if (Substring.find("Tree:") != string::npos)
								{
								Substring.erase (0, 5);
								StripStringLeadingWhiteSpace(Substring);
								ReqEndLoc = Substring.find("-");
								Reqstring = Substring.substr(0, ReqEndLoc);
								Lock[2][Lock[2].size()-1].ReqTree = Reqstring; //Tree
								Substring.erase(0, ReqEndLoc+1);
								}
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqLevel = atoi(Reqstring.c_str());	//Level

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqSlot = atoi(Reqstring.c_str());	//Slot

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[2][Lock[2].size()-1].ReqRank = atoi(Reqstring.c_str());	//Rank
							}
						}
					}
				break;
				}
			case 27:		//the modification list 3
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					Mod[2].push_back(Substring);
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					Mod[2].push_back(Substring);
					}
				break;
				}
			case 28:		//the modification name 3
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					ModName[2].push_back(Substring);
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					ModName[2].push_back(Substring);
					}
				break;
				}
			case 29:		//the modification value 3
				{
                while (EnhancementLine[i].find(",") != string::npos)
					{
	                StripStringLeadingWhiteSpace(EnhancementLine[i]);
	                EndLoc = EnhancementLine[i].find(",");
	                Substring = EnhancementLine[i].substr(0, EndLoc);
					ModValue[2].push_back(atoi(Substring.c_str()));
					EnhancementLine[i].erase(0, EndLoc+1);
					}                
                StripStringLeadingWhiteSpace(EnhancementLine[i]);
                if (EnhancementLine[i] != "")
					{
	                Substring = EnhancementLine[i];
					ModValue[2].push_back(atoi(Substring.c_str()));
					}
				break;
				}
			case 30:		//the Icon
				{
	            LoadBitmap(EnhancementLine[i], "Enhancements", &EnhancementIcon);
				break;
				}
			}
		}

    return;
    #undef NUMKEYWORDS
	}

//---------------------------------------------------------------------------
Data_Enhancement_Class* Data_Enhancement_Class::GetEnhancementAddress()
	 {
	 return this;
	 }

//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class* Data_Enhancement_Class::GetMultiSelectorPointer()
	{
	if (MultiSelection == false)
		return nullptr;

	return Data.GetMultiEnhancementPointer(Data.GetEnhMultiSelectorIndex(MultiSelectorName));
	}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE Data_Enhancement_Class::GetTreeIndex()
	{
	return TreeIndex;
	}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::GetEnhancementIndex()
	{
	return EnhancementIndex;
	}

//---------------------------------------------------------------------------
bool Data_Enhancement_Class::IsRaceTree()
	{
	if (Tree == "Bladeforged")
		return true;
	if (Tree == "Deep Gnome")
		return true;
	if (Tree == "Drow")
		return true;
	if (Tree == "Dwarf")
		return true;
	if (Tree == "Elf")
		return true;
	if (Tree == "Gnome")
		return true;
	if (Tree == "Halfling")
		return true;
	if (Tree == "Half Elf")
		return true;
	if (Tree == "Half Orc")
		return true;
	if (Tree == "Human")
		return true;
	if (Tree == "Morninglord")
		return true;
	if (Tree == "Purple Dragon Knight")
		return true;
	if (Tree == "Shadar Kai")
		return true;
	if (Tree == "Warforged")
		return true;
	if (Tree == "Dragonborn")
		return true;
	if (Tree == "Aasimar")
		return true;

	return false;
	}

//---------------------------------------------------------------------------
bool Data_Enhancement_Class::IsRaceAATree()
	{
	if (Tree == "Arcane Archer (Elf)")
		return true;

	return false;
	}


//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::CalculateAPRequirement()
	{
	int APRequirementRaceTree[6] = {0, 1, 5, 10, 15, 20};
	int APRequirementRaceTreeZero[6] = {0, 0, 0, 0, 0, 0};
	int APRequirementClassTree[6] = {0, 1, 5, 10, 20, 30};
	int APRequirementClassTreeZero[6] = {0, 5, 10, 20, 30, 40};

	if (RaceTree==true)
		{
		if (Level == 0)
			return APRequirementRaceTreeZero[Slot];
		else
			return APRequirementRaceTree[Level];
		}
	else
		{
		if (Level == 0)
			return APRequirementClassTreeZero[Slot];
		else
			return APRequirementClassTree[Level];
		}
	}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::CalculateClassLevelRequirement()
	{
	int LevelClassTreeZero[6] = {0, 3, 6, 12, 18, 20};

	if (RaceTree == true || RaceAATree == true)
		{
		return 0;
		}
	else
		{
		if (Level == 0)
			return LevelClassTreeZero[Slot];
		else
			return Level;
		}		
	}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::CalculateCharacterLevelRequirement()
	{
	int LevelRaceTreeZero[6] = {0, 4, 7, 11, 16, 20};
	int LevelAARaceTreeZero[6] = {0, 4, 8, 15, 22, 25};

	if (RaceTree == true)
		{
		if (Level == 0)
			return LevelRaceTreeZero[Slot];
		return 0;
		}
	else
		{
		if (Level == 0 && RaceAATree == true)
			return LevelAARaceTreeZero[Slot];
		if (Level == 5)
			return 12;
		return 0;
		}
	}

//---------------------------------------------------------------------------
void Data_Enhancement_Class::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetEnhancementLevel()
	{
	return Level;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetEnhancementSlot()
	{
	return Slot;
	}

//---------------------------------------------------------------------------
bool Data_Enhancement_Class::GetEnhTypeActive()
	{
	return TypeActive;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetEnhancementCost()
	{
	return APCost;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetEnhancementRanks()
	{
	return Ranks;
	}

//---------------------------------------------------------------------------
bool Data_Enhancement_Class::GetEnhMultiSelection()
	{
	return MultiSelection;
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetEnhMultiName()
	{
	return MultiSelectorName;
	}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::GetEnhancementMSlot()
	{
	return MultiSelectorSlot;
	}

//---------------------------------------------------------------------------
GraphicStruct Data_Enhancement_Class::GetEnhancementIcon()
	{
	return EnhancementIcon;
	}

//---------------------------------------------------------------------------
string Data_Enhancement_Class::GetEnhancementName()
	{
	return Name;
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetDescription(int Rank)
	{
	return Description[Rank-1];
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetCharacterLevelRequirement()
	{
	return CharacterLevelRequirement;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetClassLevelRequirement()
	{
	return ClassLevelRequirement;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetAPRequirement()
	{
	return APRequirement;
	}

//----------------------------------------------------------------------------
int Data_Enhancement_Class::GetRequirementLevel(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqLevel;
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetRequirementName(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqName;
	}


//----------------------------------------------------------------------------
int Data_Enhancement_Class::GetRequirementRank(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqRank;
	}

//----------------------------------------------------------------------------
CLASS Data_Enhancement_Class::GetTreeClass()
	{
	return Class;
	}

//----------------------------------------------------------------------------
RACE Data_Enhancement_Class::GetTreeRace()
	{
	return Race;
	}

//----------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::GetLockSize(int Rank)
	{
	return Lock[Rank].size();
	}

//----------------------------------------------------------------------------
ENH_REQTYPE Data_Enhancement_Class::GetLockType(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqType;
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetLockName(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqName;
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetLockTreeName(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqTree;
	}

//----------------------------------------------------------------------------
int Data_Enhancement_Class::GetLockLevel(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqLevel;
	}

//----------------------------------------------------------------------------
int Data_Enhancement_Class::GetLockSlot(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqSlot;
	}

//----------------------------------------------------------------------------
int Data_Enhancement_Class::GetLockRank(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqRank;
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetModType(int Index, int Rank)
	{
	return Mod[Rank][Index];
	}

//----------------------------------------------------------------------------
string Data_Enhancement_Class::GetModName(int Index, int Rank)
	{
	return ModName[Rank][Index];
	}

//----------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::GetModSize(int Rank)
	{
	return Mod[Rank].size();
	}

//----------------------------------------------------------------------------
int Data_Enhancement_Class::GetModValue(int Index, int Rank)
	{
	return ModValue[Rank][Index];
	}

//----------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::GetRequirementSize(int Rank)
	{
	return Requirement[Rank].size();
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetRequirementSlot(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqSlot;
	}

//---------------------------------------------------------------------------
ENH_REQTYPE Data_Enhancement_Class::GetRequirementType(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqType;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetRequirementOneLevel(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqLevel;
	}

//---------------------------------------------------------------------------
string Data_Enhancement_Class::GetRequirementOneName(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqName;
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetRequirementOneRank(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqRank;
	}

string Data_Enhancement_Class::GetRequirementOneTree(int Rank, int Index)
{
	return RequirementOne[Rank][Index].ReqTree;
}

//---------------------------------------------------------------------------
unsigned int Data_Enhancement_Class::GetRequirementOneSize(int Rank)
	{
	return RequirementOne[Rank].size();
	}

//---------------------------------------------------------------------------
int Data_Enhancement_Class::GetRequirementOneSlot(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqSlot;
	}

ENH_REQTYPE Data_Enhancement_Class::GetRequirementOneType(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqType;
	}

//---------------------------------------------------------------------------
CLASS Data_Enhancement_Class::SetTreeClass(ENHANCEMENT_TREE EnhancementTree)
	{
	switch (EnhancementTree)
		{
		//Class Trees grouped by Classes
		case ENHT_ARCANOTECHNICIAN_ART:
		case ENHT_BATTLE_ENGINEER_ART:
			return ARTIFICER;
		case ENHT_FRENZIED_BERSERKER_BAR:
		case ENHT_OCCULT_SLAYER_BAR:
		case ENHT_RAVAGER_BAR:
			return BARBARIAN;
		case ENHT_SPELLSINGER_BRD:
		case ENHT_SWASHBUCKLER_BRD:
		case ENHT_WARCHANTER_BRD:
			return BARD;
		case ENHT_DIVINE_DISCIPLE_CLR:
		case ENHT_WARPRIEST_CLR:
		case ENHT_RADIANT_SERVANT_CLR:
			return CLERIC;
		case ENHT_NATURES_WARRIOR_DRD:
		case ENHT_SEASONS_HERALD_DRD:
			return DRUID;
		case ENHT_ANGEL_OF_VENGEANCE_FVS:
		case ENHT_WARPRIEST_FVS:
			return FAVORED_SOUL;
		case ENHT_KENSEI_FTR:
		case ENHT_STALWART_DEFENDER_FTR:
		case ENHT_VANGUARD_FTR:
			return FIGHTER;
		case ENHT_HENSHIN_MYSTIC_MNK:
		case ENHT_NINJA_SPY_MNK:
		case ENHT_SHINTAO_MNK:
			return MONK;
		case ENHT_KNIGHT_OF_THE_CHALICE_PAL:
		case ENHT_SACRED_DEFENDER_PAL:
		case ENHT_VANGUARD_PAL:
			return PALADIN;
		case ENHT_ARCANE_ARCHER_RNG:
		case ENHT_DEEPWOOD_STALKER_RNG:
		case ENHT_TEMPEST_RNG:
			return RANGER;
		case ENHT_ASSASSIN_ROG:
		case ENHT_MECHANIC_ROG:
		case ENHT_THIEF_ACROBAT_ROG:
			return ROGUE;
		case ENHT_AIR_SAVANT_SOR:
		case ENHT_EARTH_SAVANT_SOR:
		case ENHT_FIRE_SAVANT_SOR:
		case ENHT_WATER_SAVANT_SOR:
		case ENHT_ELDRITCH_KNIGHT_SOR:
			return SORCERER;
		case ENHT_ARCHMAGE_WIZ:
		case ENHT_PALE_MASTER_WIZ:
		case ENHT_ELDRITCH_KNIGHT_WIZ:
			return WIZARD;
		case ENHT_SOULEATER_WLK:
		case ENHT_TANTEDSCHOLAR_WLK:
		case ENHT_ENLIGHTENEDSPIRIT_WLK:
			return WARLOCK;
		}
	return CLASSNONE;

	}

//---------------------------------------------------------------------------
RACE Data_Enhancement_Class::SetTreeRace(ENHANCEMENT_TREE EnhancementTree)
	{
	switch (EnhancementTree)
		{
		case ENHT_BLADEFORGED:
			return BLADEFORGED;
		case ENHT_DROW:
			return DROW;
		case ENHT_DWARF:
			return DWARF;
		case ENHT_ELF:
			return ELF;
		case ENHT_HALFLING:
			return HALFLING;
		case ENHT_HALF_ELF:
			return HALFELF;
		case ENHT_HALF_ORC:
			return HALFORC;
		case ENHT_HUMAN:
			return HUMAN;
		case ENHT_MORNINGLORD:
			return MORNINGLORD;
		case ENHT_PURPLE_DRAGON_KNIGHT:
			return PURPLEDRAGONKNIGHT;
		case ENHT_SHADAR_KAI:
			return SHADARKAI;
		case ENHT_WARFORGED:
			return WARFORGED;
		case ENHT_GNOME:
			return GNOME;
		case ENHT_DEEPGNOME:
			return DEEPGNOME;
		case ENHT_DRAGONBORN:
			return DRAGONBORN;
		case ENHT_AASIMAR:
			return AASIMAR;
		}
	return RACENONE;
	}

//---------------------------------------------------------------------------
string Data_Enhancement_Class::GetRaceName()
	{
	switch (TreeIndex)
		{
		case ENHT_BLADEFORGED:
			return "Bladforged";
		case ENHT_DROW:
			return "Drow";
		case ENHT_DWARF:
			return "Dwarf";
		case ENHT_ELF:
			return "Elf";
		case ENHT_HALFLING:
			return "Halfling";
		case ENHT_HALF_ELF:
			return "Half-Elf";
		case ENHT_HALF_ORC:
			return "Half-Orc";
		case ENHT_HUMAN:
			return "Human";
		case ENHT_MORNINGLORD:
			return "Morninglord";
		case ENHT_PURPLE_DRAGON_KNIGHT:
			return "Purple Dragon Knight";
		case ENHT_SHADAR_KAI:
			return "Shadar-Kai";
		case ENHT_WARFORGED:
			return "Warforged";
		case ENHT_GNOME:
			return "Gnome";
		case ENHT_DEEPGNOME:
			return "Deep Gnome";
		case ENHT_DRAGONBORN:
			return "Dragonborn";
		case ENHT_AASIMAR:
			return "Aasimar";
		}
	return "";
	}

//---------------------------------------------------------------------------
string Data_Enhancement_Class::GetClassName()
	{
	switch (TreeIndex)
		{
		//Class Trees grouped by Classes
		case ENHT_ARCANOTECHNICIAN_ART:
		case ENHT_BATTLE_ENGINEER_ART:
			return "Artificer";
		case ENHT_FRENZIED_BERSERKER_BAR:
		case ENHT_OCCULT_SLAYER_BAR:
		case ENHT_RAVAGER_BAR:
			return "Barbarian";
		case ENHT_SPELLSINGER_BRD:
		case ENHT_SWASHBUCKLER_BRD:
		case ENHT_WARCHANTER_BRD:
			return "Bard";
		case ENHT_DIVINE_DISCIPLE_CLR:
		case ENHT_WARPRIEST_CLR:
		case ENHT_RADIANT_SERVANT_CLR:
			return "Cleric";
		case ENHT_NATURES_WARRIOR_DRD:
		case ENHT_SEASONS_HERALD_DRD:
			return "Druid";
		case ENHT_ANGEL_OF_VENGEANCE_FVS:
		case ENHT_WARPRIEST_FVS:
			return "Favored Soul";
		case ENHT_KENSEI_FTR:
		case ENHT_STALWART_DEFENDER_FTR:
		case ENHT_VANGUARD_FTR:
			return "Fighter";
		case ENHT_HENSHIN_MYSTIC_MNK:
		case ENHT_NINJA_SPY_MNK:
		case ENHT_SHINTAO_MNK:
			return "Monk";
		case ENHT_KNIGHT_OF_THE_CHALICE_PAL:
		case ENHT_SACRED_DEFENDER_PAL:
		case ENHT_VANGUARD_PAL:
			return "Paladin";
		case ENHT_ARCANE_ARCHER_RNG:
		case ENHT_DEEPWOOD_STALKER_RNG:
		case ENHT_TEMPEST_RNG:
			return "Ranger";
		case ENHT_ASSASSIN_ROG:
		case ENHT_MECHANIC_ROG:
		case ENHT_THIEF_ACROBAT_ROG:
			return "Rogue";
		case ENHT_AIR_SAVANT_SOR:
		case ENHT_EARTH_SAVANT_SOR:
		case ENHT_FIRE_SAVANT_SOR:
		case ENHT_WATER_SAVANT_SOR:
		case ENHT_ELDRITCH_KNIGHT_SOR:
			return "Sorcerer";
		case ENHT_ARCHMAGE_WIZ:
		case ENHT_PALE_MASTER_WIZ:
		case ENHT_ELDRITCH_KNIGHT_WIZ:
			return "Wizard";
		case ENHT_SOULEATER_WLK:
		case ENHT_TANTEDSCHOLAR_WLK:
		case ENHT_ENLIGHTENEDSPIRIT_WLK:
			return "Warlock";
		}
	return "";
	}
