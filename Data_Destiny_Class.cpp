#include "Data_Destiny_Class.h"

//-------------------------------------------------------------------
Data_Destiny_Class::Data_Destiny_Class()
	{
	TreeIndex = DT_UNKNOWN;
	DestinyIndex = 0;
	MultiSelection = false;
	MultiSelectorName = "";
	MultiSelectorSlot = 0;
	MultiDescriptionIndex = 0;
	MultiIconIndex = 0;
	Name = "";
	TreeName = "";
	Tier = 0;
	Slot = 0;
	Ranks = 0;
	Active = false;
	DPCost = 0;
	for (unsigned int i=0; i<3; i++)
		{
		Description[i] = "";
		Requirement[i].clear();
		RequirementOne[i].clear();
		Lock[i].clear();
		ModCategory[i].clear();
		ModName[i].clear();
		ModValue[i].clear();
		}
	DestinyIcon.Name = "";
	DestinyIcon.Graphic = nullptr;
	DestinyIcon.Mask = nullptr;
	DestinyIcon.Width = 0;
	DestinyIcon.Height = 0;
	DPRequirement = 0;
	DLevelRequirement = 0;
	}

//--------------------------------------------------------------------
Data_Destiny_Class::~Data_Destiny_Class()
	{
	DeleteObject(DestinyIcon.Graphic);
	DeleteObject(DestinyIcon.Mask);
	}

//--------------------------------------------------------------------
Data_Destiny_Class::Data_Destiny_Class(const Data_Destiny_Class &source)
	{
	TreeIndex = source.TreeIndex;
	DestinyIndex = source.DestinyIndex;
	MultiSelection = source.MultiSelection;
	MultiSelectorName = source.MultiSelectorName;
	MultiSelectorSlot = source.MultiSelectorSlot;
	MultiDescriptionIndex = source.MultiDescriptionIndex;
	MultiIconIndex = source.MultiIconIndex;
	Name = source.Name;
	TreeName = source.TreeName;
	Tier = source.Tier;
	Slot = source.Slot;
	Ranks = source.Ranks;
	Active = source.Active;
	DPCost = source.DPCost;
	for (unsigned int i=0; i<3; i++)
		{
		Description[i] = source.Description[i];
		for (unsigned int j=0; j<source.Requirement[i].size(); j++)
			Requirement[i].push_back(source.Requirement[i][j]);
		for (unsigned int j=0; j<source.RequirementOne[i].size(); j++)
			RequirementOne[i].push_back(source.RequirementOne[i][j]);
		for (unsigned int j=0; j<source.Lock[i].size(); j++)
			Lock[i].push_back(source.Lock[i][j]);
		for (unsigned int j=0; j<source.ModCategory[i].size(); j++)
			ModCategory[i].push_back(source.ModCategory[i][j]);
		for (unsigned int j=0; j<source.ModName[i].size(); j++)
			ModName[i].push_back(source.ModName[i][j]);
		for (unsigned int j=0; j<source.ModValue[i].size(); j++)
			ModValue[i].push_back(source.ModValue[i][j]);
		}
	DestinyIcon.Name = source.DestinyIcon.Name;
	DestinyIcon.Graphic = (HBITMAP)CopyImage(source.DestinyIcon.Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	DestinyIcon.Mask = (HBITMAP)CopyImage(source.DestinyIcon.Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	DestinyIcon.Width = source.DestinyIcon.Width;
	DestinyIcon.Height = source.DestinyIcon.Height;
	DPRequirement = source.DPRequirement;
	DLevelRequirement = source.DLevelRequirement;
	}

//--------------------------------------------------------------------
Data_Destiny_Class& Data_Destiny_Class::operator=(const Data_Destiny_Class &source)
	{
	TreeIndex = source.TreeIndex;
	DestinyIndex = source.DestinyIndex;
	MultiSelection = source.MultiSelection;
	MultiSelectorName = source.MultiSelectorName;
	MultiSelectorSlot = source.MultiSelectorSlot;
	MultiDescriptionIndex = source.MultiDescriptionIndex;
	MultiIconIndex = source.MultiIconIndex;
	Name = source.Name;
	TreeName = source.TreeName;
	Tier = source.Tier;
	Slot = source.Slot;
	Ranks = source.Ranks;
	Active = source.Active;
	DPCost = source.DPCost;
	for (unsigned int i=0; i<3; i++)
		{
		Description[i] = source.Description[i];
		for (unsigned int j=0; j<source.Requirement[i].size(); j++)
			Requirement[i].push_back(source.Requirement[i][j]);
		for (unsigned int j=0; j<source.RequirementOne[i].size(); j++)
			RequirementOne[i].push_back(source.RequirementOne[i][j]);
		for (unsigned int j=0; j<source.Lock[i].size(); j++)
			Lock[i].push_back(source.Lock[i][j]);
		for (unsigned int j=0; j<source.ModCategory[i].size(); j++)
			ModCategory[i].push_back(source.ModCategory[i][j]);
		for (unsigned int j=0; j<source.ModName[i].size(); j++)
			ModName[i].push_back(source.ModName[i][j]);
		for (unsigned int j=0; j<source.ModValue[i].size(); j++)
			ModValue[i].push_back(source.ModValue[i][j]);
		}
	DestinyIcon.Name = source.DestinyIcon.Name;
	DestinyIcon.Graphic = (HBITMAP)CopyImage(source.DestinyIcon.Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	DestinyIcon.Mask = (HBITMAP)CopyImage(source.DestinyIcon.Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	DestinyIcon.Width = source.DestinyIcon.Width;
	DestinyIcon.Height = source.DestinyIcon.Height;
	DPRequirement = source.DPRequirement;
	DLevelRequirement = source.DLevelRequirement;

	return *this;
	}

//-----------------------------------------------------------------
void Data_Destiny_Class::InitializeDestiny(string Data, DESTINY_TREE DTIndex, unsigned int DIndex)
	{
	#define NUMKEYWORDS 33

	string KeywordString[NUMKEYWORDS];
	string DestinyLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	string Substring;
	size_t MSLOTLoc;
	Destiny_Requirement NewRequirement;
	string Reqstring;
	size_t ReqEndLoc;
	unsigned int Index;

	Index = 0;

	TreeIndex = DTIndex;
	DestinyIndex = DIndex;

	NewRequirement.ReqType = D_UNKNOWN;
	NewRequirement.ReqName = "";
	NewRequirement.ReqRank = 0;
	NewRequirement.ReqTier = 0;
	NewRequirement.ReqSlot = 0;

	//Parse the Data string, storing each line of the string
	//into its appropriate individual line
	KeywordString[0] = "MULTI: ";
	KeywordString[1] = "MSLOT: ";
	KeywordString[2] = "MDINDEX: ";
	KeywordString[3] = "MIINDEX: ";
	KeywordString[4] = "NAME: ";
	KeywordString[5] = "TREE: ";
	KeywordString[6] = "TIER: ";
	KeywordString[7] = "SLOT: ";
	KeywordString[8] = "RANKS: ";
	KeywordString[9] = "TYPE: ";
	KeywordString[10] = "COST: ";
	KeywordString[11] = "DESC1: ";
	KeywordString[12] = "REQ1: ";
	KeywordString[13] = "REQONE1: ";
	KeywordString[14] = "LOCK1: ";
	KeywordString[15] = "MOD1: ";
	KeywordString[16] = "MODNAME1: ";
	KeywordString[17] = "MODVALUE1: ";
	KeywordString[18] = "DESC2: ";
	KeywordString[19] = "REQ2: ";
	KeywordString[20] = "REQONE2: ";
	KeywordString[21] = "LOCK2: ";
	KeywordString[22] = "MOD2: ";
	KeywordString[23] = "MODNAME2: ";
	KeywordString[24] = "MODVALUE2: ";
	KeywordString[25] = "DESC3: ";
	KeywordString[26] = "REQ3: ";
	KeywordString[27] = "REQONE3: ";
	KeywordString[28] = "LOCK3: ";
	KeywordString[29] = "MOD3: ";
	KeywordString[30] = "MODNAME3: ";
	KeywordString[31] = "MODVALUE3: ";
	KeywordString[32] = "ICON: ";

	MSLOTLoc = 0;
	for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		DestinyLine[i] = "";
		if (Data.find(KeywordString[i], MSLOTLoc) != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = Data.find(KeywordString[i], MSLOTLoc);
			EndLoc = Data.find(";", StartLoc);
			//EndLoc = Data.find(";", Data.find(KeywordString[i])); 
			DestinyLine[i] = Data.substr(Data.find(KeywordString[i], MSLOTLoc), EndLoc-StartLoc);
			if (i == 1)
				MSLOTLoc = EndLoc + 1;	//we need to mark this location when we have the keyword MSLOT:
			//drop the keyword from the line string, we don't need it now
			DestinyLine[i].erase(0, KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
	for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		switch (i)
			{
			case 0:		//part of a multiSelector?
				{
				if (DestinyLine[i] != "")
					{
					MultiSelection = true;
					MultiSelectorName = DestinyLine[i];
					}
				break;
				}
			case 1:		//Multi-Selector Slot
				{
				MultiSelectorSlot = atoi(DestinyLine[i].c_str());
				break;
				}
			case 2:		//Multi Description Selection
				{
				MultiDescriptionIndex = atoi(DestinyLine[i].c_str());
				break;
				}
			case 3:		//Multi Icon Selection
				{
				MultiIconIndex = atoi(DestinyLine[i].c_str());
				break;
				}
			case 4:		//Name of Destiny
				{
				Name = DestinyLine[i];
				break;
				}
			case 5:		//Name Destiny Tree
				{
				TreeName = DestinyLine[i];
				break;
				}
			case 6:		//Tier of Destiny
				{
				Tier = atoi(DestinyLine[i].c_str());
				break;
				}
			case 7:		//Slot of Destiny
				{
				Slot = atoi(DestinyLine[i].c_str());
				DPRequirement = CalculateDPRequirement();
				DLevelRequirement = CalculateDLevelRequirement();
				break;
				}
			case 8:		//Number of Ranks for this Destiny
				{
				Ranks = atoi(DestinyLine[i].c_str());
				break;
				}
			case 9:		//is this an Active Destiny
				{
				if (DestinyLine[i].find("Active") != string::npos)
					Active = true;
				break;
				}
			case 10:		//Destiny Cost
				{
				DPCost = atoi(DestinyLine[i].c_str());
				break;
				}
			case 11:	//Description 1
			case 18:	//Description 2
			case 25:	//Description 3
				{
				if (i == 11)
					Description[0] = DestinyLine[i];
				if (i == 18)
					Description[1] = DestinyLine[i];
				if (i == 25)
					Description[2] = DestinyLine[i];
				break;
				}
			case 12:	//Requirement List 1
			case 19:	//Requirement List 2
			case 26:	//Requirement List 3
				{
				if (i == 12)
					Index = 0;
				if (i == 19)
					Index = 1;
				if (i == 26)
					Index = 2;
				while (DestinyLine[i] != "")
					{
					StripStringLeadingWhiteSpace(DestinyLine[i]);
					if (DestinyLine[i].find(",,") != string::npos)
						{
						EndLoc = DestinyLine[i].find(",,");
						Substring = DestinyLine[i].substr(0, EndLoc);
						}
					else
						{
						EndLoc = 0;
						Substring = DestinyLine[i];
						}
					//now that we have an individual string. lets break it down to its components
					Requirement[Index].push_back(NewRequirement);
					//Check for Destiny Requirement
					if (Substring.find("EH: ") != string::npos)
						{
						Requirement[Index][Requirement[Index].size()-1].ReqType = D_DESTINY;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[Index][Requirement[Index].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[Index][Requirement[Index].size()-1].ReqTier = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[Index][Requirement[Index].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[Index][Requirement[Index].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					//Check for MultiDestiny Requirement
					if (Substring.find("EHM: ") != string::npos)
						{
						Requirement[Index][Requirement[Index].size()-1].ReqType = D_MULTIDESTINY;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Requirement[Index][Requirement[Index].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[Index][Requirement[Index].size()-1].ReqTier = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[Index][Requirement[Index].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Requirement[Index][Requirement[Index].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					//Check for Feat Requirement
					if (Substring.find("Feat: ") != string::npos)
						{
						Requirement[Index][Requirement[Index].size()-1].ReqType = D_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Requirement[Index][Requirement[Index].size()-1].ReqName = Reqstring;
						}
					//we need to erase the requirement we just processed
					if (EndLoc > 0)
						DestinyLine[i].erase(0, EndLoc+2);
					else
						DestinyLine[i] = "";
					}
				break;
				}
			case 13:	//RequirementOne List 1
			case 20:	//RequirementOne List 2
			case 27:	//RequirementOne List 3
				{
				if (i == 13)
					Index = 0;
				if (i == 20)
					Index = 1;
				if (i == 27)
					Index = 2;
				while (DestinyLine[i] != "")
					{
					StripStringLeadingWhiteSpace(DestinyLine[i]);
					if (DestinyLine[i].find(",,") != string::npos)
						{
						EndLoc = DestinyLine[i].find(",,");
						Substring = DestinyLine[i].substr(0, EndLoc);
						}
					else
						{
						EndLoc = 0;
						Substring = DestinyLine[i];
						}
					//now that we have an individual string. lets break it down to its components
					RequirementOne[Index].push_back(NewRequirement);
					//Check for Destiny Requirement
					if (Substring.find("EH: ") != string::npos)
						{
						RequirementOne[Index][RequirementOne[Index].size()-1].ReqType = D_DESTINY;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqTier = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					//Check for MultiDestiny Requirement
					if (Substring.find("EHM: ") != string::npos)
						{
						RequirementOne[Index][RequirementOne[Index].size()-1].ReqType = D_MULTIDESTINY;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqTier = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							RequirementOne[Index][RequirementOne[Index].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					//Check for Feat Requirement
					if (Substring.find("Feat: ") != string::npos)
						{
						RequirementOne[Index][RequirementOne[Index].size()-1].ReqType = D_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						RequirementOne[Index][RequirementOne[Index].size()-1].ReqName = Reqstring;
						}
					//we need to erase the requirement we just processed
					if (EndLoc > 0)
						DestinyLine[i].erase(0, EndLoc+2);
					else
						DestinyLine[i] = "";
					}
				break;
				}
			case 14:	//Lock List 1
			case 21:
			case 28:
				{
				if (i == 14)
					Index = 0;
				if (i == 21)
					Index = 1;
				if (i == 28)
					Index = 2;
				while (DestinyLine[i] != "")
					{
					StripStringLeadingWhiteSpace(DestinyLine[i]);
					if (DestinyLine[i].find(",,") != string::npos)
						{
						EndLoc = DestinyLine[i].find(",,");
						Substring = DestinyLine[i].substr(0, EndLoc);
						}
					else
						{
						EndLoc = 0;
						Substring = DestinyLine[i];
						}
					//now that we have an individual string. lets break it down to its components
					Lock[Index].push_back(NewRequirement);
					//Check for Destiny Requirement
					if (Substring.find("EH: ") != string::npos)
						{
						Lock[Index][Lock[Index].size()-1].ReqType = D_DESTINY;
						Substring.erase (0, 4);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[Index][Lock[Index].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[Index][Lock[Index].size()-1].ReqTier = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[Index][Lock[Index].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[Index][Lock[Index].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					//Check for MultiDestiny Requirement
					if (Substring.find("EHM: ") != string::npos)
						{
						Lock[Index][Lock[Index].size()-1].ReqType = D_MULTIDESTINY;
						Substring.erase (0, 5);
						if (Substring.find(" [") != string::npos)
							{
							ReqEndLoc = Substring.find(" [");
							Reqstring = Substring.substr(0, ReqEndLoc);
							StripStringLeadingWhiteSpace(Reqstring);
							Lock[Index][Lock[Index].size()-1].ReqName = Reqstring;

							Substring.erase(0, ReqEndLoc+2);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[Index][Lock[Index].size()-1].ReqTier = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("-");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[Index][Lock[Index].size()-1].ReqSlot = atoi(Reqstring.c_str());

							Substring.erase(0, ReqEndLoc+1);
							ReqEndLoc = Substring.find("]");
							Reqstring = Substring.substr(0, ReqEndLoc);
							Lock[Index][Lock[Index].size()-1].ReqRank = atoi(Reqstring.c_str());
							}
						}
					//Check for Feat Requirement
					if (Substring.find("Feat: ") != string::npos)
						{
						Lock[Index][Lock[Index].size()-1].ReqType = D_FEAT;
						Reqstring = Substring;
						Reqstring.erase(0, 6);
						Lock[Index][Lock[Index].size()-1].ReqName = Reqstring;
						}
					//we need to erase the requirement we just processed
					if (EndLoc > 0)
						DestinyLine[i].erase(0, EndLoc+2);
					else
						DestinyLine[i] = "";
					}
				break;
				}
			case 15:	//ModCategory List
			case 22:
			case 29:
				{
				if (i == 15)
					Index = 0;
				if (i == 22)
					Index = 1;
				if (i == 29)
					Index = 2;
				while (DestinyLine[i].find(",,") != string::npos)
					{
					StripStringLeadingWhiteSpace(DestinyLine[i]);
					EndLoc = DestinyLine[i].find(",,");
					Substring = DestinyLine[i].substr(0, EndLoc);
					if (Substring == "Ability")
						ModCategory[Index].push_back(MC_ABILITY);
					else if (Substring == "Attribute")
						ModCategory[Index].push_back(MC_ATTRIBUTE);
					else if (Substring == "Resistance")
						ModCategory[Index].push_back(MC_RESISTANCE);
					else if (Substring == "Save")
						ModCategory[Index].push_back(MC_SAVE);
					else if (Substring == "Skill")
						ModCategory[Index].push_back(MC_SKILL);
					else
						ModCategory[Index].push_back(MC_UNKNOWN);
					DestinyLine[i].erase(0, EndLoc+2);
					}
				StripStringLeadingWhiteSpace(DestinyLine[i]);
				if (DestinyLine[i] != "")
					{
					Substring = DestinyLine[i];
					if (Substring == "Ability")
						ModCategory[Index].push_back(MC_ABILITY);
					else if (Substring == "Attribute")
						ModCategory[Index].push_back(MC_ATTRIBUTE);
					else if (Substring == "Resistance")
						ModCategory[Index].push_back(MC_RESISTANCE);
					else if (Substring == "Save")
						ModCategory[Index].push_back(MC_SAVE);
					else if (Substring == "Skill")
						ModCategory[Index].push_back(MC_SKILL);
					else
						ModCategory[Index].push_back(MC_UNKNOWN);
					}
				break;
				}
			case 16:	//Modification name list
			case 23:
			case 30:
				{
				if (i == 16)
					Index = 0;
				if (i == 23)
					Index = 1;
				if (i == 30)
					Index = 2;
				while (DestinyLine[i].find(",,") != string::npos)
					{
	                StripStringLeadingWhiteSpace(DestinyLine[i]);
	                EndLoc = DestinyLine[i].find(",,");
	                Substring = DestinyLine[i].substr(0, EndLoc);
					ModName[Index].push_back(Substring);
					DestinyLine[i].erase(0, EndLoc+2);
					}                
                StripStringLeadingWhiteSpace(DestinyLine[i]);
                if (DestinyLine[i] != "")
					{
	                Substring = DestinyLine[i];
					ModName[Index].push_back(Substring);
					}
				break;
				}
			case 17:	//Modification Value List
			case 24:
			case 31:
				{
				if (i == 18)
					Index = 0;
				if (i == 24)
					Index = 1;
				if (i == 31)
					Index = 2;
				while (DestinyLine[i].find(",,") != string::npos)
					{
	                StripStringLeadingWhiteSpace(DestinyLine[i]);
	                EndLoc = DestinyLine[i].find(",,");
	                Substring = DestinyLine[i].substr(0, EndLoc);
					ModValue[Index].push_back(atoi(Substring.c_str()));
					DestinyLine[i].erase(0, EndLoc+2);
					}                
                StripStringLeadingWhiteSpace(DestinyLine[i]);
                if (DestinyLine[i] != "")
					{
	                Substring = DestinyLine[i];
					ModValue[Index].push_back(atoi(Substring.c_str()));
					}
				break;
				}
			case 32:	//the Destiny's Icon
				{
				LoadBitmap(DestinyLine[i], "Destinies", &DestinyIcon);
				break;
				}
			}
		}

	return;
	#undef NUMKEYWORDS
	}

//-----------------------------------------------------------------
Data_Destiny_Class* Data_Destiny_Class::GetDestinyAddress()
	{
	return this;
	}

//-----------------------------------------------------------------
bool Data_Destiny_Class::GetActive()
	{
	return Active;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetDescription(int Rank)
	{
	return Description[Rank];
	}

//-----------------------------------------------------------------
GraphicStruct Data_Destiny_Class::GetDestinyIcon()
	{
	return DestinyIcon;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetDestinyIndex()
	{
	return DestinyIndex;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetDLevelRequirement()
	{
	return DLevelRequirement;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetDPCost()
	{
	return DPCost;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetDPRequirement()
	{
	return DPRequirement;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetTier()
	{
	return Tier;
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetLockTier(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqTier;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetLockName(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqName;
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetLockRank(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqRank;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetLockSize(int Rank)
	{
	return Lock[Rank].size();
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetLockSlot(int Rank, int Index)
	{
	return Lock[Rank][Index].ReqSlot;
	}

//-----------------------------------------------------------------
DESTINY_REQTYPE Data_Destiny_Class::GetLockType (int Rank, int Index)
	{
	return Lock[Rank][Index].ReqType;
	}

//-----------------------------------------------------------------
MODCATEGORY Data_Destiny_Class::GetModCategory(int Rank, int Index)
	{
	return ModCategory[Rank][Index];
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetModName(int Rank, int Index)
	{
	return ModName[Rank][Index];
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetModSize(int Rank)
	{
	return ModCategory[Rank].size();
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetModValue(int Rank, int Index)
	{
	return ModValue[Rank][Index];
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetMultiDescriptionIndex()
	{
	return MultiDescriptionIndex;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetMultiIconIndex()
	{
	return MultiIconIndex;
	}

//-----------------------------------------------------------------
bool Data_Destiny_Class::GetMultiSelection()
	{
	return MultiSelection;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetMultiSelectorName()
	{
	return MultiSelectorName;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetMultiSelectorSlot()
	{
	return MultiSelectorSlot;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetName()
	{
	return Name;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetRanks()
	{
	return Ranks;
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetRequirementTier(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqTier;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetRequirementName(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqName;
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetRequirementRank(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqRank;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetRequirementSize(int Rank)
	{
	return Requirement[Rank].size();
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetRequirementSlot(int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqSlot;
	}

//-----------------------------------------------------------------
DESTINY_REQTYPE Data_Destiny_Class::GetRequirementType (int Rank, int Index)
	{
	return Requirement[Rank][Index].ReqType;
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetRequirementOneTier(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqTier;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetRequirementOneName(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqName;
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetRequirementOneRank(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqRank;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetRequirementOneSize(int Rank)
	{
	return RequirementOne[Rank].size();
	}

//-----------------------------------------------------------------
int Data_Destiny_Class::GetRequirementOneSlot(int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqSlot;
	}

//-----------------------------------------------------------------
DESTINY_REQTYPE Data_Destiny_Class::GetRequirementOneType (int Rank, int Index)
	{
	return RequirementOne[Rank][Index].ReqType;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::GetSlot()
	{
	return Slot;
	}

//-----------------------------------------------------------------
DESTINY_TREE Data_Destiny_Class::GetTreeIndex()
	{
	return TreeIndex;
	}

//-----------------------------------------------------------------
string Data_Destiny_Class::GetTreeName()
	{
	return TreeName;
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::CalculateDPRequirement()
	{
	int DPRequirementTree[7] = {0, 0, 4, 8, 12, 16, 20};

	return DPRequirementTree[Tier];
	}

//-----------------------------------------------------------------
unsigned int Data_Destiny_Class::CalculateDLevelRequirement()
	{
	int LevelRequirement[7] = {0, 0, 1, 2, 3, 4, 5};
	int LevelRequirementInnate[6] = {0, 1, 2, 3, 4, 5};

	if (Tier == 0)
		return LevelRequirementInnate[Slot];
	else
		return LevelRequirement[Tier];

	}

//-----------------------------------------------------------------
void Data_Destiny_Class::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}
