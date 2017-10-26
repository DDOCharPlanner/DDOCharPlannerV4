//---------------------------------------------------------------------------
#include "DataClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
//---------------------------------------------------------------------------
DataClass Data;

//---------------------------------------------------------------------------
DataClass::DataClass()
    {
    Race.clear();
    Class.clear();
    Skill.clear();
    Spell.clear();
    for (int i=0; i<NUMDATAFILES; i++)
        DataFilesLoaded[i] = false;
    }

//---------------------------------------------------------------------------
DataClass::~DataClass()
    {
    }

//---------------------------------------------------------------------------
void DataClass::LoadDataFiles()
    {
    InterfaceManager.UpdateLoadFileStatus(RACEFILE, FILELOADING);
    InterfaceManager.UpdateLoadFileStatus(RACEFILE, LoadRaceFile());
    InterfaceManager.UpdateLoadFileStatus(CLASSFILE, FILELOADING);
    InterfaceManager.UpdateLoadFileStatus(CLASSFILE, LoadClassFile());
    InterfaceManager.UpdateLoadFileStatus(FEATFILE, FILELOADING);
    InterfaceManager.UpdateLoadFileStatus(FEATFILE, LoadFeatFile());
    InterfaceManager.UpdateLoadFileStatus(SKILLFILE, FILELOADING);
    InterfaceManager.UpdateLoadFileStatus(SKILLFILE, LoadSkillFile());
    InterfaceManager.UpdateLoadFileStatus(ENHANCEMENTFILE, FILELOADING);
    InterfaceManager.UpdateLoadFileStatus(ENHANCEMENTFILE, LoadEnhancementFile());
    InterfaceManager.UpdateLoadFileStatus(SPELLFILE, FILELOADING);
    InterfaceManager.UpdateLoadFileStatus(SPELLFILE, LoadSpellFile());
	InterfaceManager.UpdateLoadFileStatus(ITEMEFFECTFILE, FILELOADING);
	InterfaceManager.UpdateLoadFileStatus(ITEMEFFECTFILE, LoadItemEffectFile());
	InterfaceManager.UpdateLoadFileStatus(ITEMCLICKYEFFECTFILE, FILELOADING);
	InterfaceManager.UpdateLoadFileStatus(ITEMCLICKYEFFECTFILE, LoadItemClickyEffectFile());
	InterfaceManager.UpdateLoadFileStatus(ITEMFILE, FILELOADING);
	InterfaceManager.UpdateLoadFileStatus(ITEMFILE, LoadItemFile());
	InterfaceManager.UpdateLoadFileStatus(TEMPLATEFILE, FILELOADING);
	InterfaceManager.UpdateLoadFileStatus(TEMPLATEFILE, LoadTemplateFiles());
	InterfaceManager.UpdateLoadFileStatus(DESTINYFILE, FILELOADING);
	InterfaceManager.UpdateLoadFileStatus(DESTINYFILE, LoadDestinyFile());
    }

//---------------------------------------------------------------------------
bool DataClass::AllDataFilesLoaded()
    {
    for (int i=0; i<NUMDATAFILES; i++)
        if (DataFilesLoaded[i] == false)
            return false;

    return true;
    }

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadRaceFile()
    {
    #define NUMKEYWORDS 4
    char FileName[MAX_PATH];
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
    char Data[4096];
    RaceStruct NewRace;
    unsigned int Index;
    AdvancementStruct NewAdvancement;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\RaceFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    OriginalPointer = FileData;
    CloseHandle(FileHandle);

    //parse the file data
	StringCbCopy(KeywordString[0], 256, "RACENAME: ");
	StringCbCopy(KeywordString[1], 256, "DESCRIPTION: ");
	StringCbCopy(KeywordString[2], 256, "BASESTATS: ");
	StringCbCopy(KeywordString[3], 256, "ADVANCEMENT: ");
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
        strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
        Data[strstr(DataPointer, ";") - DataPointer] = '\0';
        switch (Keyword[i])
            {
            case 0:     //race name
                {
                Race.push_back(NewRace);
                Index = Race.size()-1;
                Race[Index].Name = Data;
                break;
                }
            case 1:     //race description
                {
                Race[Index].Description = Data;
                break;
                }
            case 2:     //base statistics
                {
                Race[Index].BaseStr = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                Race[Index].BaseDex = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                Race[Index].BaseCon = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                Race[Index].BaseInt = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                Race[Index].BaseWis = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                Race[Index].BaseCha = atoi(Data);
                break;
                }
            case 3:     //advancement
                {
                NewAdvancement.Level = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ",") - DataPointer);
                Data[strstr(DataPointer, ",") - DataPointer] = '\0';
                if (strcmp(Data, "RACEANDSEX") == 0)
                    NewAdvancement.AdvancementType = ADV_RACEANDSEX;
                else if (strcmp(Data, "CLASS") == 0)
                    NewAdvancement.AdvancementType = ADV_CLASS;
                else if (strcmp(Data, "NAMEANDALIGNMENT") == 0)
                    NewAdvancement.AdvancementType = ADV_NAMEANDALIGNMENT;
                else if (strcmp(Data, "REINCARNATION") == 0)
                    NewAdvancement.AdvancementType = ADV_REINCARNATE;
                else if (strcmp(Data, "ABILITYPOINT") == 0)
                    NewAdvancement.AdvancementType = ADV_ABILITYPOINT;
                else if (strcmp(Data, "ABILITYINCREASE") == 0)
                    NewAdvancement.AdvancementType = ADV_ABILITYINCREASE;
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                if (strstr(DataPointer, ",") != NULL)
                    Data[strstr(DataPointer, ",") - DataPointer] = '\0';
                NewAdvancement.Instruction = Data;
                DataPointer += NewAdvancement.Instruction.size();
                if (DataPointer[0] == ';')
                    {
                    NewAdvancement.Value = 0;
                    NewAdvancement.Automatic = false;
                    }
                else
                    {
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    NewAdvancement.Value = atoi(Data);
                    }
                NewAdvancement.Automatic = false;
                Race[Index].Advancement.push_back(NewAdvancement);
                break;
                }
            }
        }

    FileData = OriginalPointer;
    delete[] FileData;

    DataFilesLoaded[RACEFILE] = true;

    return FILELOADED;
    #undef NUMKEYWORDS
    }

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadClassFile()
    {
    #define NUMKEYWORDS 12
    char FileName[MAX_PATH];
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
    char Data[4096];
    ClassStruct NewClass;
    unsigned int Index;
    AdvancementStruct NewAdvancement;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\ClassFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    OriginalPointer = FileData;
    CloseHandle(FileHandle);

    //parse the file data
	StringCbCopy(KeywordString[0], 256, "CLASSNAME: ");
	StringCbCopy(KeywordString[1], 256, "DESCRIPTION: ");
	StringCbCopy(KeywordString[2], 256, "HITDIE: ");
	StringCbCopy(KeywordString[3], 256, "SKILLPOINTS: ");
	StringCbCopy(KeywordString[4], 256, "BAB: ");
	StringCbCopy(KeywordString[6], 256, "REFSAVE: ");
	StringCbCopy(KeywordString[5], 256, "FORTSAVE: ");
	StringCbCopy(KeywordString[7], 256, "WILLSAVE: ");
	StringCbCopy(KeywordString[8], 256, "ALIGNMENT: ");
	StringCbCopy(KeywordString[9], 256, "SPELLPOINTS: ");
	StringCbCopy(KeywordString[10], 256, "ADVANCEMENT: ");
	StringCbCopy(KeywordString[11], 256, "STARTINGSPHERE: ");
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
        strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
        Data[strstr(DataPointer, ";") - DataPointer] = '\0';
        switch (Keyword[i])
            {
            case 0:     //class name
                {
                Class.push_back(NewClass);
                Index = Class.size()-1;
                Class[Index].Name = Data;
                for (unsigned int i=0; i<20; i++)
                    Class[Index].SpellPoints[i] = 0;
                break;
                }
            case 1:     //class description
                {
                Class[Index].Description = Data;
                break;
                }
            case 2:     //Hit Die
                {
                Class[Index].HitDice = atoi(Data);
                break;
                }
            case 3:     //Skill Points
                {
                Class[Index].SkillPoints = atoi(Data);
                break;
                }
            case 4:     //Base Attack Bonus
                {
                for (unsigned int i=0; i<MAXLEVEL; i++)
                    {
                    Class[Index].BAB[i] = atoi(Data);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 5:     //Fortitude Save
                {
                for (unsigned int i=0; i<MAXLEVEL; i++)
                    {
                    Class[Index].FortitudeSave[i] = atoi(Data);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 6:     //Reflex Save
                {
                for (unsigned int i=0; i<MAXLEVEL; i++)
                    {
                    Class[Index].ReflexSave[i] = atoi(Data);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 7:     //Will Save
                {
                for (unsigned int i=0; i<MAXLEVEL; i++)
                    {
                    Class[Index].WillSave[i] = atoi(Data);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 8:     //Legal Alignments
                {
                if (strstr(Data, "Lawful Good") != NULL)
                    Class[Index].Alignment.push_back(LAWFULGOOD);
                if (strstr(Data, "Lawful Neutral") != NULL)
                    Class[Index].Alignment.push_back(LAWFULNEUTRAL);
                if (strstr(Data, "Neutral Good") != NULL)
                    Class[Index].Alignment.push_back(NEUTRALGOOD);
                if (strstr(Data, "True Neutral") != NULL)
                    Class[Index].Alignment.push_back(TRUENEUTRAL);
                if (strstr(Data, "Chaotic Good") != NULL)
                    Class[Index].Alignment.push_back(CHAOTICGOOD);
                if (strstr(Data, "Chaotic Neutral") != NULL)
                    Class[Index].Alignment.push_back(CHAOTICNEUTRAL);
                break;
                }
            case 9:     //spell point progression
                {
                for (unsigned int i=0; i<MAXLEVEL; i++)
                    {
                    Class[Index].SpellPoints[i] = atoi(Data);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 10:     //advancement
                {
                NewAdvancement.Level = atoi(Data);
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ",") - DataPointer);
                Data[strstr(DataPointer, ",") - DataPointer] = '\0';
                if (strcmp(Data, "SKILLS") == 0)
                    NewAdvancement.AdvancementType = ADV_SKILLS;
                else if (strcmp(Data, "FEATS") == 0)
                    NewAdvancement.AdvancementType = ADV_FEATS;
                else if (strcmp(Data, "SPELLS") == 0)
                    NewAdvancement.AdvancementType = ADV_SPELLS;
                else if (strcmp(Data, "TOME") == 0)
                    NewAdvancement.AdvancementType = ADV_TOME;
                else if (strcmp(Data, "ENHANCEMENTS") == 0)
                    NewAdvancement.AdvancementType = ADV_ENHANCEMENTS;
                DataPointer = strstr(DataPointer, ",");
                DataPointer += 2;
                strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                if (strstr(DataPointer, ",") != NULL)
                    Data[strstr(DataPointer, ",") - DataPointer] = '\0';
                NewAdvancement.Instruction = Data;
                DataPointer += NewAdvancement.Instruction.size();
                if (DataPointer[0] == ';')
                    {
                    NewAdvancement.Value = 0;
                    NewAdvancement.Automatic = false;
                    }
                else
                    {
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    NewAdvancement.Value = atoi(Data);
                    if (strstr(Data, "AUTOMATIC") != NULL)
                        NewAdvancement.Automatic = true;
                    else
                        NewAdvancement.Automatic = false;
                    }
                Class[Index].Advancement.push_back(NewAdvancement);
                break;
                }
			case 11: //Starting Destiny Sphere
				{
				if (strstr(Data, "Arcane") != NULL)
                    Class[Index].StartingDestinySphere = DS_ARCANE;
                if (strstr(Data, "Divine") != NULL)
                    Class[Index].StartingDestinySphere = DS_DIVINE;
                if (strstr(Data, "Martial") != NULL)
                    Class[Index].StartingDestinySphere = DS_MARTIAL;
                if (strstr(Data, "Primal") != NULL)
                    Class[Index].StartingDestinySphere = DS_PRIMAL;
                break;
				}
            }
        }

    FileData = OriginalPointer;
    delete[] FileData;

    DataFilesLoaded[CLASSFILE] = true;

	return FILELOADED;
    #undef NUMKEYWORDS
    }

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadFeatFile()
    {
    char FileName[MAX_PATH];
    HANDLE FileHandle;
    char *FileData;
    DWORD FileSize;
    DWORD BytesRead;
	string FullFileString;
	string FeatDataString;
	FeatDataClass DummyFeat;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\FeatsFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    CloseHandle(FileHandle);

	//drop the entire character field into a string for easier manipulation
	FullFileString = FileData;
	while (FullFileString.find("FEATNAME: ") != string::npos)
		{
		FeatDataString = FullFileString;
		//delete everything after the last semicolon in the ICON keyword line (note that this means
		//the ICON line MUST be the last line in each feat field)
		FeatDataString.erase(FeatDataString.find(";", FeatDataString.find("ICON: "))+1, FeatDataString.size());
		//create a new feat entry and send the string over to the feat class for initialization
		FeatData.push_back(DummyFeat);
		FeatData[FeatData.size()-1].InitializeFeat(FeatDataString);
		//remove this feat from the full file string so we can move on to the next one 
		FullFileString.erase(0, FeatDataString.size());
		}

    delete[] FileData;

    DataFilesLoaded[FEATFILE] = true;

    return FILELOADED;
    }
    
//---------------------------------------------------------------------------
FILESTATE DataClass::LoadSkillFile()
    {
    #define NUMKEYWORDS 6
    char FileName[MAX_PATH];
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
    char Data[4096];
    SkillStruct NewSkill;
    int Index;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\SkillFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    OriginalPointer = FileData;
    CloseHandle(FileHandle);

    //parse the file data
	StringCbCopy(KeywordString[0], 256, "SKILLNAME: ");
	StringCbCopy(KeywordString[1], 256, "DESCRIPTION: ");
	StringCbCopy(KeywordString[2], 256, "KEYABILITY: ");
	StringCbCopy(KeywordString[3], 256, "PRIMARY: ");
	StringCbCopy(KeywordString[4], 256, "CROSS: ");
	StringCbCopy(KeywordString[5], 256, "ICON: ");
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
        strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
        Data[strstr(DataPointer, ";") - DataPointer] = '\0';
        switch (Keyword[i])
            {
            case 0:     //the skill name
                {
                Skill.push_back(NewSkill);
                Index = Skill.size()-1;
                Skill[Index].Name = Data;
                break;
                }
            case 1:     //the skill description
                {
                Skill[Index].Description = Data;
                break;
                }
            case 2:     //The Key Ability
                {
                if (strstr(Data, "Str") != NULL)
					Skill[Index].KeyAbility = STRENGTH;
                if (strstr(Data, "Dex") != NULL)
					Skill[Index].KeyAbility = DEXTERITY;
                if (strstr(Data, "Con") != NULL)
					Skill[Index].KeyAbility = CONSTITUTION;
                if (strstr(Data, "Int") != NULL)
					Skill[Index].KeyAbility = INTELLIGENCE;
                if (strstr(Data, "Wis") != NULL)
					Skill[Index].KeyAbility = WISDOM;
                if (strstr(Data, "Cha") != NULL)
                    Skill[Index].KeyAbility = CHARISMA;
                break;
                }
            case 3:     //primary class list
                {
                while (strstr(Data, ",") != NULL)
                    {
                    Data[strstr(DataPointer, ",") - DataPointer] = '\0';
                    if (strstr(Data, "Fighter") != NULL)
                        Skill[Index].PrimaryClass.push_back(FIGHTER);
                    if (strstr(Data, "Paladin") != NULL)
                        Skill[Index].PrimaryClass.push_back(PALADIN);
                    if (strstr(Data, "Barbarian") != NULL)
                        Skill[Index].PrimaryClass.push_back(BARBARIAN);
					if (strstr(Data, "Monk") != NULL)
						Skill[Index].PrimaryClass.push_back(MONK);
					if (strstr(Data, "Rogue") != NULL)
						Skill[Index].PrimaryClass.push_back(ROGUE);
					if (strstr(Data, "Ranger") != NULL)
                        Skill[Index].PrimaryClass.push_back(RANGER);
                    if (strstr(Data, "Cleric") != NULL)
                        Skill[Index].PrimaryClass.push_back(CLERIC);
                    if (strstr(Data, "Wizard") != NULL)
                        Skill[Index].PrimaryClass.push_back(WIZARD);
                    if (strstr(Data, "Sorcerer") != NULL)
                        Skill[Index].PrimaryClass.push_back(SORCERER);
                    if (strstr(Data, "Bard") != NULL)
                        Skill[Index].PrimaryClass.push_back(BARD);
                    if (strstr(Data, "Favored Soul") != NULL)
                        Skill[Index].PrimaryClass.push_back(FAVORED_SOUL);
                    if (strstr(Data, "Artificer") != NULL)
                        Skill[Index].PrimaryClass.push_back(ARTIFICER);
                    if (strstr(Data, "Druid") != NULL)
                        Skill[Index].PrimaryClass.push_back(DRUID);
					if (strstr(Data, "Warlock") != NULL)
						Skill[Index].PrimaryClass.push_back(WARLOCK);
					DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                if (strstr(Data, "Fighter") != NULL)
                    Skill[Index].PrimaryClass.push_back(FIGHTER);
                if (strstr(Data, "Paladin") != NULL)
                    Skill[Index].PrimaryClass.push_back(PALADIN);
                if (strstr(Data, "Barbarian") != NULL)
					Skill[Index].PrimaryClass.push_back(BARBARIAN);
				if (strstr(Data, "Monk") != NULL)
					Skill[Index].PrimaryClass.push_back(MONK);
				if (strstr(Data, "Rogue") != NULL)
					Skill[Index].PrimaryClass.push_back(ROGUE);
				if (strstr(Data, "Ranger") != NULL)
                    Skill[Index].PrimaryClass.push_back(RANGER);
                if (strstr(Data, "Cleric") != NULL)
                    Skill[Index].PrimaryClass.push_back(CLERIC);
                if (strstr(Data, "Wizard") != NULL)
                    Skill[Index].PrimaryClass.push_back(WIZARD);
                if (strstr(Data, "Sorcerer") != NULL)
                    Skill[Index].PrimaryClass.push_back(SORCERER);
                if (strstr(Data, "Bard") != NULL)
                    Skill[Index].PrimaryClass.push_back(BARD);
                if (strstr(Data, "Favored Soul") != NULL)
                    Skill[Index].PrimaryClass.push_back(FAVORED_SOUL);
                if (strstr(Data, "Artificer") != NULL)
                    Skill[Index].PrimaryClass.push_back(ARTIFICER);
                if (strstr(Data, "Druid") != NULL)
                    Skill[Index].PrimaryClass.push_back(DRUID);
				if (strstr(Data, "Warlock") != NULL)
					Skill[Index].PrimaryClass.push_back(WARLOCK);
                break;
                }
            case 4:     //Cross class list
                {
                while (strstr(Data, ",") != NULL)
                    {
                    Data[strstr(DataPointer, ",") - DataPointer] = '\0';
                    if (strstr(Data, "Fighter") != NULL)
                        Skill[Index].CrossClass.push_back(FIGHTER);
                    if (strstr(Data, "Paladin") != NULL)
                        Skill[Index].CrossClass.push_back(PALADIN);
                    if (strstr(Data, "Barbarian") != NULL)
                        Skill[Index].CrossClass.push_back(BARBARIAN);
					if (strstr(Data, "Monk") != NULL)
						Skill[Index].CrossClass.push_back(MONK);
					if (strstr(Data, "Rogue") != NULL)
						Skill[Index].CrossClass.push_back(ROGUE);
					if (strstr(Data, "Ranger") != NULL)
                        Skill[Index].CrossClass.push_back(RANGER);
                    if (strstr(Data, "Cleric") != NULL)
                        Skill[Index].CrossClass.push_back(CLERIC);
                    if (strstr(Data, "Wizard") != NULL)
						Skill[Index].CrossClass.push_back(WIZARD);
                    if (strstr(Data, "Sorcerer") != NULL)
                        Skill[Index].CrossClass.push_back(SORCERER);
                    if (strstr(Data, "Bard") != NULL)
                        Skill[Index].CrossClass.push_back(BARD);
                    if (strstr(Data, "Favored Soul") != NULL)
                        Skill[Index].CrossClass.push_back(FAVORED_SOUL);
                    if (strstr(Data, "Artificer") != NULL)
                        Skill[Index].CrossClass.push_back(ARTIFICER);
                    if (strstr(Data, "Druid") != NULL)
                        Skill[Index].CrossClass.push_back(DRUID);
					if (strstr(Data, "Warlock") != NULL)
						Skill[Index].CrossClass.push_back(WARLOCK);
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                if (strstr(Data, "Fighter") != NULL)
                    Skill[Index].CrossClass.push_back(FIGHTER);
                if (strstr(Data, "Paladin") != NULL)
                    Skill[Index].CrossClass.push_back(PALADIN);
                if (strstr(Data, "Barbarian") != NULL)
					Skill[Index].CrossClass.push_back(BARBARIAN);
				if (strstr(Data, "Monk") != NULL)
					Skill[Index].CrossClass.push_back(MONK);
				if (strstr(Data, "Rogue") != NULL)
					Skill[Index].CrossClass.push_back(ROGUE);
				if (strstr(Data, "Ranger") != NULL)
					Skill[Index].CrossClass.push_back(RANGER);
				if (strstr(Data, "Cleric") != NULL)
					Skill[Index].CrossClass.push_back(CLERIC);
				if (strstr(Data, "Wizard") != NULL)
                    Skill[Index].CrossClass.push_back(WIZARD);
                if (strstr(Data, "Sorcerer") != NULL)
                    Skill[Index].CrossClass.push_back(SORCERER);
                if (strstr(Data, "Bard") != NULL)
                    Skill[Index].CrossClass.push_back(BARD);
                if (strstr(Data, "Favored Soul") != NULL)
                    Skill[Index].CrossClass.push_back(FAVORED_SOUL);
                if (strstr(Data, "Artificer") != NULL)
                    Skill[Index].CrossClass.push_back(ARTIFICER);
                if (strstr(Data, "Druid") != NULL)
                    Skill[Index].CrossClass.push_back(DRUID);
				if (strstr(Data, "Warlock") != NULL)
					Skill[Index].CrossClass.push_back(WARLOCK);
                break;
                }
            case 5:     //the graphic icon
                {
                InterfaceManager.LoadIcon(SKILLICON, Data);
                break;
                }
            }
        }

    FileData = OriginalPointer;
    delete[] FileData;

    DataFilesLoaded[SKILLFILE] = true;

    return FILELOADED;
    #undef NUMKEYWORDS
    }

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadDestinyFile()
	{
	char FileName[MAX_PATH];
	HANDLE FileHandle;
	char *FileData;
	DWORD FileSize;
	DWORD BytesRead;
	string FullFileString;
	string DestinyDataString;
	string Tree;
	size_t StartLoc;
	size_t EndLoc;
	DESTINY_TREE DTreeIndex;
	Data_Destiny_Class DummyDestiny;
	Data_Destiny_MultiSelector_Class DummyMulti;

	//Set up our Initial Destiny Trees.
	InitializeDestinyTrees();

	//open the Destiny.txt file
	StringCbCopy(FileName, MAX_PATH, "\0");
	GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat(FileName, MAX_PATH, "\\DataFiles\\DestinyFile.txt");
	FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE)
		return FILEERROR;

	//get the file size and make room for the data
	FileSize = GetFileSize(FileHandle, NULL);
	FileData = new char[FileSize+1];

	//read in the data in it's entirety, set up the pointer, and close the file
	SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
	ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
	FileData[BytesRead] = '\0';
	CloseHandle(FileHandle);

	//drop the entire character field into a string for  easier manipulation
	FullFileString = FileData;
	//delete the template data
	if (FullFileString.find("[MULTIPLE DESTINY SELECTOR]", 0) != string::npos)
		FullFileString.erase(FullFileString.begin(), FullFileString.begin()+FullFileString.find("[MULTIPLE DESTINY SELECTOR]"));
	while (FullFileString.find("NAME: ") != string::npos)
		{
		DestinyDataString = FullFileString;
		//there are 2 sections to the Destiny data file, the multi-selectors and the destinies
		if (DestinyDataString.find("[ENDOFMULTI]", 0) != string::npos)
			{
			//delete everything past the next Name Marker.
			if (DestinyDataString.find("NAME: ", 1) != string::npos)
				DestinyDataString.erase(DestinyDataString.find("NAME: ", 1), DestinyDataString.size());
			//Create a new multi Entry and send the string over to the Destiny_MultiSelector Class for initialization
			DestinyMultiSelector.push_back(DummyMulti);
			DestinyMultiSelector[DestinyMultiSelector.size()-1].InitializeMultiSelector(DestinyDataString);
			//remove this multi selector from the full file string so we can move on to the next one
			FullFileString.erase(0, DestinyDataString.size());
			}
		else
			{
			DestinyDataString = FullFileString;
			//delete everything pas the next Name marker.
			//delete everything after the last semicolon in the ICON keyword line (note this means
			//the ICON line MUST be the last line in each feat field).
			DestinyDataString.erase(DestinyDataString.find(";", DestinyDataString.find("ICON: "))+1, DestinyDataString.size());
			//we now have to determine which tree we are working with
			Tree = DestinyDataString;
			if (Tree.find("TREE: ", 0) !=string::npos)
				{
				StartLoc = Tree.find("TREE: ");
				EndLoc = Tree.find(";", StartLoc);
				Tree = Tree.substr(Tree.find("TREE: "), EndLoc-StartLoc);
				//drop the keyword from the line string, we dont' need it now
				Tree.erase(0,6);
				//get the tree Index
				DTreeIndex = GetDestinyTreeIndex(Tree);
				if (DTreeIndex != DT_UNKNOWN)
					{
					//Add a new Destiny entry
					DestinyTreeData[DTreeIndex].AddNewDestiny(DestinyDataString);
					}
				}
			else
				{
				OutputDebugString ("Warning: Destiny Entry is missing the Destiny TREE: field (");
				OutputDebugString (Tree.c_str());
				OutputDebugString (" )\r\n");
				}

			
			//remove this destiny from the full file string so we can move on to the next one
			FullFileString.erase (0, DestinyDataString.size());
			}
		}
	delete[] FileData;
	DataFilesLoaded[DESTINYFILE] = true;
	return FILELOADED;
	}

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadEnhancementFile()
    {
    char FileName[MAX_PATH];
    HANDLE FileHandle;
    char *FileData;
    DWORD FileSize;
    DWORD BytesRead;
	string FullFileString;
	string EnhancementDataString;
	string Tree;
	size_t StartLoc;
	size_t EndLoc;
	ENHANCEMENT_TREE TreeIndex;
	Data_Enhancement_Class DummyEnhancement;
	Data_Enhancement_MultiSelector_Class DummyMulti;

	//Set up our Initial Enhancement Trees.
	InitializeEnhancementTrees();

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\EnhancementFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    CloseHandle(FileHandle);

	//drop the entire character field into a string for easier manipulation
	FullFileString = FileData;
	//delete the template data
	if (FullFileString.find("[MULTIPLE ENHANCEMENT SELECTORS]", 0) != string::npos)
	{
		FullFileString.erase(FullFileString.begin(), FullFileString.begin() + FullFileString.find("[MULTIPLE ENHANCEMENT SELECTORS]"));
		FullFileString.erase(FullFileString.begin(), FullFileString.begin() + FullFileString.find("NAME: "));

	}

	while (FullFileString.find("NAME: ") != string::npos)
		{
		EnhancementDataString = FullFileString;
		//there are two sections to the enhancement data file, the multiselectors and the enhancements
		if (EnhancementDataString.find("[ENDOFMULTI]", 0) != string::npos)
			{
			//delete everything past the next Name marker.
			if (EnhancementDataString.find("NAME: ", 1) != string::npos)
				EnhancementDataString.erase(EnhancementDataString.find("NAME: ", 1), EnhancementDataString.size());
			//create a new enhancement entry and send the string over to the enhancement class for initialization
			EnhancementMultiSelector.push_back(DummyMulti);
			EnhancementMultiSelector[EnhancementMultiSelector.size()-1].InitializeMultiSelector(EnhancementDataString);
			//remove this enhancement from the full file string so we can move on to the next one 
			FullFileString.erase(0, EnhancementDataString.size());
			}
		else
			{
			EnhancementDataString = FullFileString;
			//delete everything past the next Name marker.
			//delete everything after the last semicolon in the ICON keyword line (note that this means
			//the ICON line MUST be the last line in each feat field)
			EnhancementDataString.erase(EnhancementDataString.find(";", EnhancementDataString.find("ICON: "))+1, EnhancementDataString.size());
			//we now have to determine which tree we are working with
			Tree = EnhancementDataString;
			StartLoc = Tree.find("TREE: ");
			EndLoc = Tree.find(";", StartLoc); 
			Tree = Tree.substr(Tree.find("TREE: "), EndLoc-StartLoc);
			//drop the keyword from the line string, we don't need it now
			Tree.erase(0, 6);
			//get an index
			TreeIndex = GetEnhTreeIndex(Tree);
			if (TreeIndex != ENHT_UNKNOWN)
				{
				//Add a new Enhancement entry
				EnhancementTreeData[TreeIndex].AddNewEnhancement(EnhancementDataString); 
				//create a new enhancement entry and send the string over to the enhancement class for initialization
				//EnhancementData[TreeIndex].push_back(DummyEnhancement);
				//EnhancementData[TreeIndex][EnhancementData[TreeIndex].size()-1].InitializeEnhancement(EnhancementDataString, TreeIndex, EnhancementData[TreeIndex].size()-1);
				}
			//remove this enhancement from the full file string so we can move on to the next one 
			FullFileString.erase(0, EnhancementDataString.size());
			}
		}

    delete[] FileData;

    DataFilesLoaded[ENHANCEMENTFILE] = true;

    return FILELOADED;
    }

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadSpellFile()
    {
    #define NUMKEYWORDS 16
    char FileName[MAX_PATH];
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
    char Data[4096];
    SpellStruct NewSpell;
    int Index;
    int Value;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\SpellFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    OriginalPointer = FileData;
    CloseHandle(FileHandle);

    //parse the file data
	StringCbCopy(KeywordString[0], 256, "SPELLNAME: ");
	StringCbCopy(KeywordString[1], 256, "DESCRIPTION: ");
	StringCbCopy(KeywordString[2], 256, "CLASSLIST: ");
	StringCbCopy(KeywordString[3], 256, "LEVEL: ");
	StringCbCopy(KeywordString[4], 256, "TARGET: ");
	StringCbCopy(KeywordString[5], 256, "COOLDOWN: ");
	StringCbCopy(KeywordString[6], 256, "DURATION: ");
	StringCbCopy(KeywordString[7], 256, "COST: ");
	StringCbCopy(KeywordString[8], 256, "COMPONENTS: ");
	StringCbCopy(KeywordString[9], 256, "SCHOOL: ");
	StringCbCopy(KeywordString[10], 256, "META: ");
	StringCbCopy(KeywordString[11], 256, "RANGE: ");
	StringCbCopy(KeywordString[12], 256, "SAVING: ");
	StringCbCopy(KeywordString[13], 256, "RESIST: ");
	StringCbCopy(KeywordString[14], 256, "RARE: ");
	StringCbCopy(KeywordString[15], 256, "ICON: ");
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
        strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
        Data[strstr(DataPointer, ";") - DataPointer] = '\0';
        switch (Keyword[i])
            {
            case 0:     //the spell name
                {
                Spell.push_back(NewSpell);
                Index = Spell.size()-1;
                Spell[Index].Name = Data;
				break;
                }
            case 1:     //spell description
                {
                Spell[Index].Description = Data;
                break;
                }
            case 2:     //the class list
                {
                if (strstr(Data, "Fighter") != NULL)
                    Spell[Index].ClassType.push_back(FIGHTER);
                if (strstr(Data, "Paladin") != NULL)
                    Spell[Index].ClassType.push_back(PALADIN);
                if (strstr(Data, "Barbarian") != NULL)
					Spell[Index].ClassType.push_back(BARBARIAN);
				if (strstr(Data, "Monk") != NULL)
					Spell[Index].ClassType.push_back(MONK);
				if (strstr(Data, "Rogue") != NULL)
					Spell[Index].ClassType.push_back(ROGUE);
				if (strstr(Data, "Ranger") != NULL)
                    Spell[Index].ClassType.push_back(RANGER);
                if (strstr(Data, "Cleric") != NULL)
                    Spell[Index].ClassType.push_back(CLERIC);
                if (strstr(Data, "Wizard") != NULL)
                    Spell[Index].ClassType.push_back(WIZARD);
                if (strstr(Data, "Sorcerer") != NULL)
                    Spell[Index].ClassType.push_back(SORCERER);
                if (strstr(Data, "Bard") != NULL)
                    Spell[Index].ClassType.push_back(BARD);
                if (strstr(Data, "Favored Soul") != NULL)
                    Spell[Index].ClassType.push_back(FAVORED_SOUL);
                if (strstr(Data, "Artificer") != NULL)
                    Spell[Index].ClassType.push_back(ARTIFICER);
                if (strstr(Data, "Druid") != NULL)
                    Spell[Index].ClassType.push_back(DRUID);
				if (strstr(Data, "Warlock") != NULL)
					Spell[Index].ClassType.push_back(WARLOCK);
                break;
                }
            case 3:     //spell level list
                {
                while (1)
                    {
                    Value = atoi(Data);
                    Spell[Index].Level.push_back(Value);
                    if (strstr(Data, ",") == NULL)
                        break;
                    DataPointer = strstr(DataPointer, ",");
                    DataPointer += 2;
                    strncpy_s (Data, DataPointer, strstr(DataPointer, ";") - DataPointer);
                    Data[strstr(DataPointer, ";") - DataPointer] = '\0';
                    }
                break;
                }
            case 4:     //target
				{
				Spell[Index].Target = Data;
                break;
				}
            case 5:     //cooldown time
				{
                Spell[Index].Cooldown = Data;
                break;
				}
            case 6:     //spell duration
				{
                Spell[Index].Duration = Data;
                break;
				}
            case 7:     //spell cost
				{
                Spell[Index].Cost = Data;
                break;
				}
            case 8:     //spell components
				{
				Spell[Index].Components = Data;
                break;
				}
            case 9:     //spell school
				{
				Spell[Index].School = Data;
                break;
				}
            case 10:     //spell meta list
				{
				Spell[Index].Meta = Data;
                break;
				}
            case 11:     //spell range
				{
                Spell[Index].Range = Data;
                break;
				}
            case 12:     //spell save
				{
				Spell[Index].Save = Data;
                break;
				}
            case 13:     //spell resist
				{
				Spell[Index].Resist = Data;
                break;
				}
			case 14:     //spell rare
			{
					Spell[Index].Rare = *Data != '0';

				break;
			}
            case 15:     //the graphic icon
                {
                Spell[Index].GraphicIconIndex = InterfaceManager.LoadIcon(SPELLICON, Data);
                break;
                }
            }
        }

    FileData = OriginalPointer;
    delete[] FileData;

    DataFilesLoaded[SPELLFILE] = true;

    return FILELOADED;
    #undef NUMKEYWORDS
    }

//---------------------------------------------------------------------------
FILESTATE DataClass::LoadItemClickyEffectFile()
	{
	char FileName[MAX_PATH];
    HANDLE FileHandle;
    char *FileData;
    DWORD FileSize;
    DWORD BytesRead;
	string FullFileString;
	string ItemClickyEffectDataString;
	ItemClickyEffectClass DummyClickyItemEffect;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\ItemClickyEffectsFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    CloseHandle(FileHandle);

	//drop the entire character field into a string for easier manipulation
	FullFileString = FileData;
	while (FullFileString.find("EFFECTNAME: ") != string::npos)
		{
		ItemClickyEffectDataString = FullFileString;
		//delete everything after the ENDOFEFFECT statement including the ENDOFEFFECT statement (note that this means
		//ENDOFEFFECT must be at the end of each effect.)
		ItemClickyEffectDataString.erase(ItemClickyEffectDataString.find("ENDOFEFFECT", 0), ItemClickyEffectDataString.size());
		//create a new itemeffect entry and send the string over to the itemeffect class for initialization
		ItemClickyEffect.push_back(DummyClickyItemEffect);
		ItemClickyEffect[ItemClickyEffect.size()-1].InitializeItemClickyEffect(ItemClickyEffectDataString);
		//remove this effect from the full file string so we can move on to the next one (add 11 to also remove the prior
		//ENDOFEFFECT tag 
		FullFileString.erase(0, ItemClickyEffectDataString.size()+11);
		}

    delete[] FileData;

    DataFilesLoaded[ITEMCLICKYEFFECTFILE] = true;

    return FILELOADED;
	}
	
//---------------------------------------------------------------------------
FILESTATE DataClass::LoadItemEffectFile()
	{
	char FileName[MAX_PATH];
    HANDLE FileHandle;
    char *FileData;
    DWORD FileSize;
    DWORD BytesRead;
	string FullFileString;
	string ItemEffectDataString;
	ItemEffectClass DummyItemEffect;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\ItemEffectsFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    CloseHandle(FileHandle);

	//drop the entire character field into a string for easier manipulation
	FullFileString = FileData;
	while (FullFileString.find("EFFECTNAME: ") != string::npos)
		{
		ItemEffectDataString = FullFileString;
		//delete everything after the ENDOFEFFECT statement including the ENDOFEFFECT statement (note that this means
		//ENDOFEFFECT must be at the end of each effect.)
		ItemEffectDataString.erase(ItemEffectDataString.find("ENDOFEFFECT", 0), ItemEffectDataString.size());
		//create a new itemeffect entry and send the string over to the itemeffect class for initialization
		ItemEffect.push_back(DummyItemEffect);
		int index = ItemEffect.size()-1;
		ItemEffect[index].InitializeItemEffect(ItemEffectDataString);

		// Create an hash table based of Name+Subname to speed up loading
		ItemEffectIndex.emplace(pair<string, int>(ItemEffect[index].GetItemEffectName()+ItemEffect[index].GetItemEffectSubName(), index));

		//remove this effect from the full file string so we can move on to the next one (add 11 to also remove the prior
		//ENDOFEFFECT tag 
		FullFileString.erase(0, ItemEffectDataString.size()+11);
		}

    delete[] FileData;

    DataFilesLoaded[ITEMEFFECTFILE] = true;

    return FILELOADED;
	}
	
//---------------------------------------------------------------------------
FILESTATE DataClass::LoadItemFile()
	{
	char FileName[MAX_PATH];
    HANDLE FileHandle;
    char *FileData;
    DWORD FileSize;
    DWORD BytesRead;
	string FullFileString;
	string ItemDataString;
	ItemClass DummyItem;

    //open the file
	StringCbCopy(FileName, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, FileName);
	StringCbCat (FileName, MAX_PATH, "\\DataFiles\\ItemsFile.txt");
    FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return FILEERROR;

    //get the file size and make room for the data
    FileSize = GetFileSize(FileHandle, NULL);
    FileData = new char[FileSize+1];

    //read in the data in it's entirety, set up the pointer, and close the file
    SetFilePointer(FileHandle, 0, NULL, FILE_BEGIN);
    ReadFile(FileHandle, FileData, FileSize, &BytesRead, NULL);
    FileData[BytesRead] = '\0';
    CloseHandle(FileHandle);
	FullFileString = FileData;

	//drop the entire character field into a string for easier manipulation
	size_t EndLoc = 0;
	size_t StartLoc = FullFileString.find("ITEMNAME: ");
	while (StartLoc != string::npos)
		{
		//delete everything after the ENDOFITEM statement including the ENDOFEFFECT statement (note that this means
		//ENDOFEFFECT must be at the end of each effect.)
		EndLoc = FullFileString.find("ENDOFITEM", StartLoc+10);
		ItemDataString = FullFileString.substr(StartLoc, EndLoc-StartLoc);

		//create a new itemeffect entry and send the string over to the itemeffect class for initialization
		Item.push_back(DummyItem);
		Item[Item.size()-1].InitializeItem(ItemDataString);

		StartLoc = FullFileString.find("ITEMNAME: ", EndLoc+9);
		}

    delete[] FileData;

    DataFilesLoaded[ITEMFILE] = true;

    return FILELOADED;
	}
	
//---------------------------------------------------------------------------
FILESTATE DataClass::LoadTemplateFiles()
	{
    DataFilesLoaded[TEMPLATEFILE] = true;
    return FILELOADED;
	}

//---------------------------------------------------------------------------
int DataClass::GetNumRaces()
    {
    return Race.size();
    }

//---------------------------------------------------------------------------
string DataClass::GetRaceName(int Index)
    {
    return Race[Index].Name;
    }

//---------------------------------------------------------------------------
string DataClass::GetRaceDescription(int Index)
    {
    return Race[Index].Description;
    }

//---------------------------------------------------------------------------
void DataClass::GetRaceBaseStats(int Index, int *Stats)
    {
    Stats[0] = Race[Index].BaseStr;
    Stats[1] = Race[Index].BaseDex;
    Stats[2] = Race[Index].BaseCon;
    Stats[3] = Race[Index].BaseInt;
    Stats[4] = Race[Index].BaseWis;
    Stats[5] = Race[Index].BaseCha;

    return;
    }

//---------------------------------------------------------------------------
string DataClass::GetAlignmentString(ALIGNMENT Alignment)
    {
    switch (Alignment)
        {
        case LAWFULGOOD:
            return "Lawful Good";
        case LAWFULNEUTRAL:
            return "Lawful Neutral";
        case NEUTRALGOOD:
            return "Neutral Good";
        case TRUENEUTRAL:
            return "True Neutral";
        case CHAOTICGOOD:
            return "Chaotic Good";
        case CHAOTICNEUTRAL:
            return "Chaotic Neutral";
        }
    return "Unknown Alignment?";
    }

//---------------------------------------------------------------------------
bool DataClass::IsAlignmentCompatable(CLASS ClassType, ALIGNMENT Alignment)
    {
    for (unsigned int i=0; i<Class[ClassType].Alignment.size(); i++)
        {
        if (Class[ClassType].Alignment[i] == Alignment)
            return true;
        }
    return false;
    }

//---------------------------------------------------------------------------
int DataClass::GetNumClasses()
    {
    return Class.size();
    }

//---------------------------------------------------------------------------
string DataClass::GetClassName(int Index)
	{
	if (Index == CLASSNONE)
		return "None";
    return Class[Index].Name;
    }

//---------------------------------------------------------------------------
CLASS DataClass::GetClassIndex(string ClassName)
	{
	for (unsigned int i=0; i<Class.size(); i++)
		if (Class[i].Name == ClassName)
			return (CLASS)i;

	return CLASSNONE;
	}

//---------------------------------------------------------------------------
string DataClass::GetClassDescription(int Index)
    {
    return Class[Index].Description;
    }

//---------------------------------------------------------------------------
string DataClass::GetInstructionString(unsigned int Level, unsigned int RaceNum, unsigned int ClassNum, unsigned int Index, int *Value)
    {
    unsigned int Count;

    Count = 0;
    for (unsigned int i=0; i<Race[RaceNum].Advancement.size(); i++)
        {
        if (Race[RaceNum].Advancement[i].Level == Level)
            {
            if (Count == Index)
                {
                *Value = Race[RaceNum].Advancement[i].Value;
                return Race[RaceNum].Advancement[i].Instruction;
                }
            Count++;
            }
        }
    for (unsigned int i=0; i<Class[ClassNum].Advancement.size(); i++)
        {
        if (Class[ClassNum].Advancement[i].Level == Level)
            {
            if (Count == Index)
                {
                *Value = Class[ClassNum].Advancement[i].Value;
                return Class[ClassNum].Advancement[i].Instruction;
                }
            Count++;
            }
        }
    return "";
    }

//---------------------------------------------------------------------------
ADVANCEMENTTYPE DataClass::GetAdvancementType(unsigned int Level, unsigned int RaceNum, unsigned int ClassNum, unsigned int Index, int *Value)
    {
    unsigned int Count;
    FEATSLOTTYPE F1, F2, F3;
    int SpellLevel[3];
    int NumSpells[3];

    if (Race.size() == 0)
        return ADV_UNKNOWN;

    Count = 0;
    for (unsigned int i=0; i<Race[RaceNum].Advancement.size(); i++)
        {
        if (Race[RaceNum].Advancement[i].Level == Level)
            {
            if (Count == Index)
                {
                *Value = Race[RaceNum].Advancement[i].Value;
                return Race[RaceNum].Advancement[i].AdvancementType;
                }
            Count++;
            }
        }

    if (Class.size() == 0)
        return ADV_UNKNOWN;

    for (unsigned int i=0; i<Class[ClassNum].Advancement.size(); i++)
        {
        if (Class[ClassNum].Advancement[i].Level == Level)
            {
            //skip the feat entry if we have nixed it
            if (Class[ClassNum].Advancement[i].AdvancementType == ADV_FEATS)
                {
                Character.DetermineFeatSlots(Level, &F1, &F2, &F3);
                if (F1 == FEATNONE)
                    continue;
                }
            //skip the spell entry if we have nixed it
            if (Class[ClassNum].Advancement[i].AdvancementType == ADV_SPELLS)
                {
                Character.GetSpellSelectionSlots(Level, SpellLevel, NumSpells);
                if (SpellLevel[0] == 0)
                    continue;
                }
            if (Count == Index)
                {
                *Value = Class[ClassNum].Advancement[i].Value;
                return Class[ClassNum].Advancement[i].AdvancementType;
                }
            Count++;
            }
        }
    return ADV_UNKNOWN;
    }

//---------------------------------------------------------------------------
string DataClass::GetAbilityString(ABILITIES Ability, bool Full)
    {
    switch (Ability)
        {
        case STRENGTH:
            {
            if (Full == true)
                return "Strength";
            else
                return "STR";
            }
        case DEXTERITY:
            {
            if (Full == true)
                return "Dexterity";
            else
                return "DEX";
            }
        case CONSTITUTION:
            {
            if (Full == true)
                return "Constitution";
            else
                return "CON";
            }
        case INTELLIGENCE:
            {
            if (Full == true)
                return "Intelligence";
            else
                return "INT";
            }
        case WISDOM:
            {
            if (Full == true)
                return "Wisdom";
            else
                return "WIS";
            }
        case CHARISMA:
            {
            if (Full == true)
                return "Charisma";
            else
                return "CHA";
            }
        default:
            return "UNKNOWN";
        }
    }

//---------------------------------------------------------------------------
int DataClass::CalculateAbilityModifier(int AbilityValue)
    {
		int value;
		if (AbilityValue <=1)
        return -5;
		value = AbilityValue / 2 - 5;
    return value;
    }

//---------------------------------------------------------------------------
int DataClass::GetHitDice(int ClassType)
    {
    return Class[ClassType].HitDice;
    }

//---------------------------------------------------------------------------
int DataClass::GetSpellPoints(CLASS ClassType, int Level)
    {
    if (Level == 0)
        return 0;
	if (ClassType == FIGHTER || ClassType == BARBARIAN || ClassType == ROGUE)
        return 0;
    return Class[(int)ClassType].SpellPoints[Level-1];
    }

//---------------------------------------------------------------------------
bool DataClass::IsSkillPrimary(CLASS ClassType, int SkillIndex)
    {
    for (unsigned int i=0; i<Skill[SkillIndex].PrimaryClass.size(); i++)
        {
        if (Skill[SkillIndex].PrimaryClass[i] == ClassType)
            return true;
        }
    return false;
    }

//---------------------------------------------------------------------------
bool DataClass::IsSkillCross(CLASS ClassType, int SkillIndex)
    {
    for (unsigned int i=0; i<Skill[SkillIndex].CrossClass.size(); i++)
        {
        if (Skill[SkillIndex].CrossClass[i] == ClassType)
            return true;
        }
    return false;
    }

//---------------------------------------------------------------------------
void DataClass::GetSkillData(int SkillIndex, string *Name, ABILITIES *KeyAbility)
    {
    *Name = Skill[SkillIndex].Name;
    *KeyAbility = Skill[SkillIndex].KeyAbility;
    }

//---------------------------------------------------------------------------
string DataClass::GetSkillName (int SkillIndex)
    {
    return Skill[SkillIndex].Name;
    }

//---------------------------------------------------------------------------
string DataClass::GetSkillDescription (int SkillIndex)
    {
    return Skill[SkillIndex].Description;
    }

//---------------------------------------------------------------------------
int DataClass::GetRaceAutoFeat(RACE RaceType, unsigned int AtLevel, unsigned int StartFeat)
    {
    FeatDataClass *pFeat;

    for (unsigned int i=StartFeat; i<FeatData.size(); i++)
        {
        pFeat = GetFeatPointer(i);
        if (pFeat->HasRace(RaceType, AtLevel) == FEATAQUIREAUTONOPREREQ)
			return i;
        if (pFeat->HasRace(RaceType, AtLevel) == FEATAQUIREAUTOMATIC)
	        {
            if (pFeat->HaveAllFeatPrereqs(AtLevel) == PREREQ_PASS)
		        return i;
	        }
	    }
		
    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetRaceFeat(RACE RaceType, unsigned int Level, unsigned int StartFeat)
    {
    FeatDataClass *pFeat;

    for (unsigned int i=StartFeat; i<FeatData.size(); i++)
        {
        pFeat = GetFeatPointer(i);
        if (pFeat->HasRace(RaceType, Level) != FEATNOAQUIRE)
			return i;
        }

    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetClassAutoFeat(CLASS ClassType, unsigned int Level, unsigned int StartFeat)
    {
    int ClassLevel;
    FeatDataClass *pFeat;

	ClassLevel = Character.GetClassLevel(ClassType, Level);
    for (unsigned int i=StartFeat; i<FeatData.size(); i++)
        {
        pFeat = GetFeatPointer(i);
        if (pFeat->HasClass(ClassType, ClassLevel, FEATAQUIREAUTONOPREREQ) == true)
			return i;
        if (pFeat->HasClass(ClassType, ClassLevel, FEATAQUIREAUTOMATIC) == true)
	        {
		    if (FeatData[i].HaveAllFeatPrereqs(Level) == PREREQ_PASS)
			    return i;
			}
		}

    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetClassFeat(CLASS ClassType, unsigned int Level, unsigned int StartFeat)
    {
    int ClassLevel;
    FeatDataClass *pFeat;

	ClassLevel = Character.GetClassLevel(ClassType, Level);
    for (unsigned int i=StartFeat; i<FeatData.size(); i++)
        {
        pFeat = GetFeatPointer(i);
        if (pFeat->HasClass(ClassType, ClassLevel, FEATAQUIREANY) == true)
			return i;
		}

    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetFeatIndex(string FeatName)
    {
    FeatDataClass *pFeat;
    
    if (FeatName.find(":") != string::npos)
        {
        for (unsigned int i=0; i<FeatData.size(); i++)
            {
            pFeat = GetFeatPointer(i);
			if (i == 156)
				i = 156;
			string CurrentFeatName = pFeat->GetFeatName(true);
			if (CurrentFeatName.find(" Sphere:") != string::npos && FeatName.find(" Destiny:") != string::npos)
			{
				int CurrentLen = CurrentFeatName.size();
				CurrentFeatName = "Epic Destiny:" + CurrentFeatName.substr(CurrentFeatName.find(":") + 1, CurrentLen - CurrentFeatName.find(":") + 1);



			}


            if (CurrentFeatName == FeatName)
                return i;
            }
        }
    else
        {
        for (unsigned int i=0; i<FeatData.size(); i++)
            {
            pFeat = GetFeatPointer(i);
            if (pFeat->GetFeatName(false) == FeatName)
                return i;
            }
        }

    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetFeatWithParentHeading(string ParentHeading, int StartFeat)
    {
    int Count;

    Count = 0;
    for (unsigned int i=StartFeat; i<FeatData.size(); i++)
        {
        if (FeatData[i].GetFeatParentHeading() == ParentHeading)
            return i;
        }
    return -1;
    }
    
//---------------------------------------------------------------------------
SpellStruct* DataClass::GetSpellData(int Index)
	{
	return &Spell[Index];
	}

//---------------------------------------------------------------------------
string DataClass::GetSpellName(int Index)
    {
    return Spell[Index].Name;
    }
		
//---------------------------------------------------------------------------
bool DataClass::GetSpellRare(int Index)
{
	return Spell[Index].Rare;
}

//---------------------------------------------------------------------------
int DataClass::GetSpellIndex(CLASS ClassType, unsigned int Level, unsigned int Index)
    {
    unsigned int Count;
	ostringstream ss;

    Count = 0;
    for (unsigned int i=0; i<Spell.size(); i++)
        {
        for (unsigned int j=0; j<Spell[i].ClassType.size(); j++)
            {

			if (Spell[i].ClassType[j] == ClassType)
                {
				if (Spell[i].Level[j] == Level)
                    {
                    if (Index == Count)
                        return i;
                    else
                        Count++;
                    }
                }
            }
        }
    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetSpellIndex(string SpellName)
    {
    for (unsigned int i=0; i<Spell.size(); i++)
        {
        if (Spell[i].Name == SpellName)
            return i;
        }
    return -1;
    }

//---------------------------------------------------------------------------
int DataClass::GetSpellLevel(CLASS ClassType, unsigned int Index)
    {
    for (unsigned int i=0; i<Spell[Index].ClassType.size(); i++)
        {
        if (Spell[Index].ClassType[i] == ClassType)
            {
            return Spell[Index].Level[i];
            }
        }
    return 0;
    }

//---------------------------------------------------------------------------
unsigned int DataClass::GetSpellIconIndex(unsigned int Index)
    {
    return Spell[Index].GraphicIconIndex;
    }

//---------------------------------------------------------------------------
Data_Enhancement_Tree_Class* DataClass::GetEnhancementTreePointer(ENHANCEMENT_TREE Tree)
	{
	return EnhancementTreeData[Tree].GetEnhancementTreeAddress();
	}

//---------------------------------------------------------------------------
Data_Enhancement_Tree_Class* DataClass::GetEnhancementTreePointer(string TreeName)
	{
	for (int i=0; i<NUM_ENHANCEMENT_TREES; i++)
		{
		if (EnhancementTreeData[i].GetTreeName() == TreeName)
			return EnhancementTreeData[i].GetEnhancementTreeAddress();
		}
	//We should never get to this point, if so someone didn't name a tree correctly
	return EnhancementTreeData[ENHT_UNKNOWN].GetEnhancementTreeAddress();
	}

//---------------------------------------------------------------------------
DESTINY_SPHERE DataClass::GetDestinySphere(CLASS ClassIndex)
	{
	return Class[ClassIndex].StartingDestinySphere;
	}

//---------------------------------------------------------------------------
int DataClass::GetDestinyMultiSelectorIndex(string MultiName)
	{
	for (unsigned int i=0; i<DestinyMultiSelector.size(); i++)
		{
		if (MultiName == DestinyMultiSelector[i].GetName())
			return i;
		}
	OutputDebugString ("Warning: Unknown Destiny Multi Selector Name was requested: ");
	OutputDebugString (MultiName.c_str());
	OutputDebugString ("\r\n");
	return 0;
	}

//---------------------------------------------------------------------------
DESTINY_TREE DataClass::GetDestinyTreeIndex(string TreeName)
	{
	for (int x=0; x<NUM_DESTINY_TREES; x++)
		{
		if (DestinyTreeData[x].GetTreeName() == TreeName)
			return (DESTINY_TREE)x;
		}
	OutputDebugString ("Warning: Unknown Destiny Tree sent for indentification. Sent: ");
	OutputDebugString (TreeName.c_str());
	OutputDebugString (", returned: Unknown\r\n");
	return DT_UNKNOWN;
	}

//---------------------------------------------------------------------------
Data_Destiny_Tree_Class* DataClass::GetDestinyTreePointer(DESTINY_TREE DestinyTree)
	{
	return DestinyTreeData[DestinyTree].GetDestinyTreeAddress();
	}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE DataClass::GetEnhTreeIndex(string TreeName)
	{
	ENHANCEMENT_TREE Tree;

	Tree =  Data_Enhancement_Tree_Class::GetTreeIndex(TreeName);
	if (Tree == ENHT_UNKNOWN)
		{
		OutputDebugString ("Warning: Unknown Tree sent for identification. Sent: ");
		OutputDebugString (TreeName.c_str());
		OutputDebugString (" , returned: Unknown\r\n");
		}

	return Tree;
	}

//---------------------------------------------------------------------------
Data_Destiny_MultiSelector_Class* DataClass::GetMultiDestinyPointer (int MultiIndex)
	{
	//validatae the index
	if (static_cast<unsigned int>(MultiIndex) >= DestinyMultiSelector.size())
		return NULL;

	return DestinyMultiSelector[MultiIndex].GetMultiDestinyAddress();
	}

//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class* DataClass::GetMultiEnhancementPointer (int MultiIndex)
	{
	///validate the index
	if (static_cast<unsigned int>(MultiIndex) >= EnhancementMultiSelector.size())
		return NULL;
	
	return EnhancementMultiSelector[MultiIndex].GetMultiEnhancementAddress();	
	}

//---------------------------------------------------------------------------
string DataClass::GetEnhMultiName(int MultiIndex)
	{
	return EnhancementMultiSelector[MultiIndex].GetName();
	}

//---------------------------------------------------------------------------
string DataClass::GetEnhMultiDescription(int MultiIndex)
	{
	return EnhancementMultiSelector[MultiIndex].GetDescription();
	}

//---------------------------------------------------------------------------
int DataClass::GetEnhMultiSelectorIndex(string MultiName)
	{
	
	for (unsigned int i=0; i<EnhancementMultiSelector.size(); i++)
		{
		if (MultiName == EnhancementMultiSelector[i].GetName())
			return i;
		}
	return 0;
	}

//---------------------------------------------------------------------------
int DataClass::GetClassSkillPoints(CLASS ClassType)
    {
    return Class[ClassType].SkillPoints;
    }

//---------------------------------------------------------------------------
FeatDataClass* DataClass::GetFeatPointer(int FeatIndex)
	{
	///validate the index
	if (static_cast<unsigned int>(FeatIndex) >= FeatData.size())
		return NULL;
	
	return FeatData[FeatIndex].GetFeatAddress();	
	}

//---------------------------------------------------------------------------
FeatDataClass* DataClass::GetFeatPointer (string FeatName)
	{
	int FeatIndex;
	
	FeatIndex = GetFeatIndex(FeatName);
	if (FeatIndex == -1)
		return NULL;
	return GetFeatPointer(FeatIndex);
	}

//----------------------------------------------------------------------------
ItemClass* DataClass::GetItemPointer(int ItemIndex)
	{
	if (static_cast<unsigned int>(ItemIndex) >= Item.size())
		return NULL;
	return Item[ItemIndex].GetItemAddress();
	}
	
//---------------------------------------------------------------------------
ItemEffectClass* DataClass::GetItemEffectPointer(int ItemEffectIndex)
	{
	if (static_cast<unsigned int>(ItemEffectIndex) >= ItemEffect.size())
		return NULL;
	return ItemEffect[ItemEffectIndex].GetItemEffectAddress();
	}
	
//---------------------------------------------------------------------------
int DataClass::GetBaseSkillLevel(int SkillIndex, int AtLevel)
    {
    int Result;
    int Ability;

    Ability = Character.GetAbility(Skill[SkillIndex].KeyAbility, AtLevel, true, true, true);
    Result = CalculateAbilityModifier(Ability);

    return Result;
    }

//---------------------------------------------------------------------------
int DataClass::GetClassBAB(CLASS ClassType, int AtLevel)
    {
    if (AtLevel == 0)
        return 0;
    return Class[ClassType].BAB[AtLevel-1];
    }

//---------------------------------------------------------------------------
int DataClass::GetBaseSave(SAVETYPE SaveType, CLASS ClassType, int AtLevel)
    {
    if (AtLevel == 0)
        return 0;

    switch (SaveType)
        {
        case FORTITUDESAVE:
            return Class[ClassType].FortitudeSave[AtLevel-1];
        case REFLEXSAVE:
            return Class[ClassType].ReflexSave[AtLevel-1];
        case WILLSAVE:
            return Class[ClassType].WillSave[AtLevel-1];
        }

    return 0;
    }

//---------------------------------------------------------------------------	
int DataClass::GetItemIndex(string strItemName)
	{
	for (unsigned int i=0; i<Item.size(); i++)
		{
		if (strItemName == Item[i].GetItemName())
			return i;
		}
	return NONE;
	}

//---------------------------------------------------------------------------
int DataClass::GetItemSize()
	{
	return Item.size();
	}

//---------------------------------------------------------------------------
int DataClass::GetItemEffectSize()
	{
	return ItemEffect.size();
	}

//---------------------------------------------------------------------------
int DataClass::GetItemEffectIndex(string strCombinedEffectName)
	{
	string strEffectName;
	string strEffectSubName;

	size_t StartLoc;
	size_t EndLoc;
	int Value;

	// Check to see if a Subeffectname exists and if so seperate the string value.
	if (strCombinedEffectName.find("{") != string::npos)
		{
		StartLoc = strCombinedEffectName.find("{");
		EndLoc = strCombinedEffectName.size();
		strEffectName = strCombinedEffectName.substr(0, StartLoc);
		strEffectSubName = strCombinedEffectName.substr(StartLoc +1, EndLoc);
		}
	else
		{
		strEffectName = strCombinedEffectName;
		strEffectSubName = "";
		}
	Value = GetItemEffectIndex(strEffectName, strEffectSubName);
	return Value;
	}

//---------------------------------------------------------------------------
int DataClass::GetItemEffectIndex(string strEffectName, string strEffectSubName)
	{	
		int index = 0;

		try 
		{
		   index = ItemEffectIndex.at(strEffectName+strEffectSubName);
		}
		catch(...)
		{
		}
		return index;
	}

//---------------------------------------------------------------------------
void DataClass::InitializeDestinyTrees()
	{
	string Arrows;

	//UI Tree
	Arrows = "";
	DestinyTreeData[DT_UNKNOWN].InitializeDestinyTree(DT_UNKNOWN, "Unknown Tree", false, "", "", Arrows, DS_NONE);
	DestinyTreeData[DT_NONE].InitializeDestinyTree(DT_NONE, "No Tree", false, "", "", Arrows, DS_NONE);

	//CharacterTrees
	Arrows = "1-0-U-1, 1-1-U-2, 1-2-U-1, 2-0-U-2, 3-2-U-1, 4-0-U-2, 4-2-U-1, 4-2-L-1, 4-2-R-1, 5-2-L-1, 5-2-R-1";
	DestinyTreeData[DT_DRACONIC_INCARNATION].InitializeDestinyTree(DT_DRACONIC_INCARNATION, "Draconic Incarnation", true, "DestinyBackgroundArcane", "DestinyIconDraconicIncarnationSmall", Arrows, DS_ARCANE, DT_FATESINGER, DT_MAGISTER, DT_NONE);
	Arrows = "1-0-U-1, 1-1-U-1, 3-O-U-1, 5-0-U-1";
	DestinyTreeData[DT_FATESINGER].InitializeDestinyTree(DT_FATESINGER, "Fatesinger", true, "DestinyBackgroundArcane", "DestinyIconFatesingerSmall", Arrows, DS_ARCANE, DT_DRACONIC_INCARNATION, DT_MAGISTER, DT_SHADOWDANCER);
	Arrows = "1-1-U-1, 2-3-U-1, 3-0-R-1, 3-3-U-1, 4-0-U-2, 4-1-U-1, 4-2-U-1, 4-3-U-1, 4-3-L-1, 5-1-U-1";
	DestinyTreeData[DT_MAGISTER].InitializeDestinyTree(DT_MAGISTER, "Magister", true, "DestinyBackgroundArcane", "DestinyIconMagisterSmall", Arrows, DS_ARCANE, DT_DRACONIC_INCARNATION, DT_FATESINGER, DT_NONE);
	Arrows = "1-1-U-1, 1-1-R-1, 1-3-L-1, 1-3-U-1, 2-0-U-1, 3-0-U-1, 3-2-R-1, 4-1-U-2, 4-2-L-1, 4-2-R-1, 4-2-U-2, 4-3-U-2";
	DestinyTreeData[DT_EXALTED_ANGEL].InitializeDestinyTree(DT_EXALTED_ANGEL, "Exalted Angel", true, "DestinyBackgroundDivine", "DestinyIconExaltedAngelSmall", Arrows, DS_DIVINE, DT_UNYIELDING_SENTINEL, DT_NONE, DT_NONE);
	Arrows = "1-3-U-1, 4-3-U-1, 5-2-R-1";
	DestinyTreeData[DT_UNYIELDING_SENTINEL].InitializeDestinyTree(DT_UNYIELDING_SENTINEL, "Unyielding Sentinel", true, "DestinyBackgroundDivine", "DestinyIconUnyieldingSentinelSmall", Arrows, DS_DIVINE, DT_EXALTED_ANGEL, DT_NONE, DT_NONE);
	Arrows = "1-0-U-2, 1-3-U-1, 3-0-U-2, 4-0-U-1";
	DestinyTreeData[DT_GRANDMASTER_OF_FLOWERS].InitializeDestinyTree(DT_GRANDMASTER_OF_FLOWERS, "Grandmaster of Flowers", true, "DestinyBackgroundMartial", "DestinyIconGrandmasterofFlowersSmall", Arrows, DS_MARTIAL, DT_LEGENDARY_DREADNAUGHT, DT_SHADOWDANCER, DT_UNYIELDING_SENTINEL);
	Arrows = "2-0-U-1, 5-3-U-1";
	DestinyTreeData[DT_LEGENDARY_DREADNAUGHT].InitializeDestinyTree(DT_LEGENDARY_DREADNAUGHT, "Legendary Dreadnought", true, "DestinyBackgroundMartial", "DestinyIconLegendaryDreadnoughtSmall", Arrows, DS_MARTIAL, DT_GRANDMASTER_OF_FLOWERS, DT_SHADOWDANCER, DT_SHIRADI_CHAMPION);
	Arrows = "1-3-U-1, 3-0-U-2, 3-1-L-1, 3-1-U-1, 3-3-U-1, 4-1-U-1, 5-0-U-1, 5-1-U-1, 6-1-R-1";
	DestinyTreeData[DT_SHADOWDANCER].InitializeDestinyTree(DT_SHADOWDANCER, "Shadowdancer", true, "DestinyBackgroundMartial", "DestinyIconShadowdancerSmall", Arrows, DS_MARTIAL, DT_GRANDMASTER_OF_FLOWERS, DT_LEGENDARY_DREADNAUGHT, DT_FATESINGER);
	Arrows = "2-0-U-1, 2-2-U-2, 3-1-U-1";
	DestinyTreeData[DT_FURY_OF_THE_WILD].InitializeDestinyTree(DT_FURY_OF_THE_WILD, "Fury of the Wild", true, "DestinyBackgroundPrimal", "DestinyIconFuryoftheWildSmall", Arrows, DS_PRIMAL, DT_SHIRADI_CHAMPION, DT_PRIMAL_AVATAR, DT_NONE);
	Arrows = "2-0-U-1, 2-3-U-1, 3-0-U-1, 4-0-U-2";
	DestinyTreeData[DT_PRIMAL_AVATAR].InitializeDestinyTree(DT_PRIMAL_AVATAR, "Primal Avatar", true, "DestinyBackgroundPrimal", "DestinyIconPrimalAvatarSmall", Arrows, DS_PRIMAL, DT_FURY_OF_THE_WILD, DT_SHIRADI_CHAMPION, DT_NONE);
	Arrows = "1-2-U-1, 1-2-R-1, 2-0-U-1, 2-3-L-1, 2-3-U-2, 3-0-U-1";
	DestinyTreeData[DT_SHIRADI_CHAMPION].InitializeDestinyTree(DT_SHIRADI_CHAMPION, "Shiradi Champion", true, "DestinyBackgroundPrimal", "DestinyIconShiradiChampionSmall", Arrows, DS_PRIMAL, DT_FURY_OF_THE_WILD, DT_PRIMAL_AVATAR, DT_LEGENDARY_DREADNAUGHT);
	}

//---------------------------------------------------------------------------
void DataClass::InitializeEnhancementTrees()
	{
	string Arrows;

	//UI Trees (4)
	Arrows = "";
	EnhancementTreeData[ENHT_NOTREE].InitializeEnhancementTree(ENHT_NOTREE, ENHTT_UI, RACENONE, CLASSNONE, "NoTree", false, "NoTreeBackground", Arrows);
	EnhancementTreeData[ENHT_UNSET].InitializeEnhancementTree(ENHT_UNSET, ENHTT_UI, RACENONE, CLASSNONE, "Unset", false, "UnsetBackground", Arrows);
	EnhancementTreeData[ENHT_UNKNOWN].InitializeEnhancementTree(ENHT_UNKNOWN, ENHTT_UI, RACENONE, CLASSNONE, "Unknown Tree", false, "UnknownTreeBackground", Arrows);
	EnhancementTreeData[ENHT_FUTURETREE].InitializeEnhancementTree(ENHT_FUTURETREE, ENHTT_UI, RACENONE, CLASSNONE, "Future Tree", false, "FutureTreeBackground", Arrows);

	//Race Trees (15)
	Arrows = "4-1-L-1";
	EnhancementTreeData[ENHT_BLADEFORGED].InitializeEnhancementTree(ENHT_BLADEFORGED, ENHTT_RACE, BLADEFORGED, CLASSNONE, "Bladeforged", true, "BladeforgedBackground", Arrows);
	Arrows = "1-2-U-1, 1-3-U-1, 2-1-U-2, 2-3-U-1, 3-3-U-1";
	EnhancementTreeData[ENHT_DROW].InitializeEnhancementTree(ENHT_DROW, ENHTT_RACE, DROW, CLASSNONE, "Drow", true, "DrowBackground", Arrows);
	Arrows = "1-0-U-1, 1-3-U-1, 1-4-U-1, 2-0-U-1, 2-2-U-1, 2-3-U-1, 3-0-U-1, 3-2-U-1, 3-3-U-1, 4-3-R-1";
	EnhancementTreeData[ENHT_DWARF].InitializeEnhancementTree(ENHT_DWARF, ENHTT_RACE, DWARF, CLASSNONE, "Dwarf", true, "DwarfBackground", Arrows);
	Arrows = "1-0-U-1, 1-2-U-1, 1-3-U-1, 2-0-U-1, 2-1-U-1, 2-3-U-1, 2-4-U-1, 3-0-U-1, 3-1-R-1, 3-3-U-1, 4-3-R-1, 4-3-L-1";
	EnhancementTreeData[ENHT_ELF].InitializeEnhancementTree(ENHT_ELF, ENHTT_RACE, ELF, CLASSNONE, "Elf", true, "ElfBackground", Arrows);
	Arrows = "1-0-U-1, 1-2-U-1,1-3-U-1, 2-0-U-1, 2-0-R-1, 2-2-U-1, 2-3-U-1, 3-1-U-1, 3-2-U-1, 3-3-U-1";
	EnhancementTreeData[ENHT_HALFLING].InitializeEnhancementTree(ENHT_HALFLING, ENHTT_RACE, HALFLING, CLASSNONE, "Halfling", true, "HalflingBackground", Arrows);
	Arrows = "1-0-U-1, 1-3-U-1, 2-0-U-1, 2-1-U-2, 2-3-U-1, 2-3-L-1, 2-4-U-1, 3-0-U-1, 3-3-U-1, 4-3-L-1";
	EnhancementTreeData[ENHT_HALF_ELF].InitializeEnhancementTree(ENHT_HALF_ELF, ENHTT_RACE, HALFELF, CLASSNONE, "Half Elf", true, "HalfElfBackground", Arrows);// Added a space in "Half-Elf" to allow for lockouts in enhancment trees
	Arrows = "1-0-U-1, 1-3-U-1, 2-0-U-1, 2-3-U-1, 3-3-U-1, 4-3-L-1";
	EnhancementTreeData[ENHT_HALF_ORC].InitializeEnhancementTree(ENHT_HALF_ORC, ENHTT_RACE, HALFORC, CLASSNONE, "Half Orc", true, "HalfOrcBackground", Arrows);// Added a space in "Half-Orc" to allow for lockouts in enhancment trees
	Arrows = "1-0-U-1, 1-1-U-1, 1-2-U-1, 1-3-U-2, 2-0-U-1, 2-1-U-1, 2-2-U-1, 3-2-U-1, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_HUMAN].InitializeEnhancementTree(ENHT_HUMAN, ENHTT_RACE, HUMAN, CLASSNONE, "Human", true, "HumanBackground", Arrows);
	Arrows = "1-2-U-1, 1-3-U-1, 2-1-U-1, 2-3-U-1, 2-4-U-1, 3-0-U-1, 3-1-R-1, 3-3-U-1, 4-1-L-1, 4-3-L-1, 4-3-R-1";
	EnhancementTreeData[ENHT_MORNINGLORD].InitializeEnhancementTree(ENHT_MORNINGLORD, ENHTT_RACE, MORNINGLORD, CLASSNONE, "Morninglord", true, "ElfBackground", Arrows);
	Arrows = "1-2-U-1, 1-3-U-2, 2-0-U-1, 2-0-R-1, 2-3-U-1, 3-0-U-1, 3-2-U-1, 3-3-U-1, 3-4-U-1, 4-0-R-1";
	EnhancementTreeData[ENHT_PURPLE_DRAGON_KNIGHT].InitializeEnhancementTree(ENHT_PURPLE_DRAGON_KNIGHT, ENHTT_RACE, PURPLEDRAGONKNIGHT, CLASSNONE, "Purple Dragon Knight", true, "HumanBackground", Arrows);
	Arrows = "1-0-U-1, 1-4-U-1, 2-0-U-1, 2-2-U-1, 2-3-U-1, 3-0-U-1, 3-0-R-1";
	EnhancementTreeData[ENHT_SHADAR_KAI].InitializeEnhancementTree(ENHT_SHADAR_KAI, ENHTT_RACE, SHADARKAI, CLASSNONE, "Shadar Kai", true, "ShadarKaiBackground", Arrows);// Added a space in "Shadar-Kai" to allow for lockouts in enhancment trees
	Arrows = "1-0-U-1, 1-3-U-1, 2-3-U-1, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_WARFORGED].InitializeEnhancementTree(ENHT_WARFORGED, ENHTT_RACE, WARFORGED, CLASSNONE, "Warforged", true, "WarforgedBackground", Arrows);
	Arrows = "1-0-U-1, 1-4-U-1, 2-0-U-1, 2-4-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_GNOME].InitializeEnhancementTree(ENHT_GNOME, ENHTT_RACE, GNOME, CLASSNONE, "Gnome", true, "GnomeBackground", Arrows);
	Arrows = "1-4-U-1, 2-4-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_DEEPGNOME].InitializeEnhancementTree(ENHT_DEEPGNOME, ENHTT_RACE, DEEPGNOME, CLASSNONE, "Deep Gnome", true, "DeepGnomeBackground", Arrows);// Added a space in "Deep-Gnome" to allow for lockouts in enhancement trees
	Arrows = "1-0-U-1, 1-1-U-1, 2-0-U-1, 3-0-U-1, 3-2-L-1, 3-2-U-1, 3-2-R-1, 3-3-U-1";
	EnhancementTreeData[ENHT_DRAGONBORN].InitializeEnhancementTree(ENHT_DRAGONBORN, ENHTT_RACE, DRAGONBORN, CLASSNONE, "Dragonborn", true, "DeepGnomeBackground", Arrows);
	Arrows = "1-0-U-1, 1-4-U-2, 2-0-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_AASIMAR].InitializeEnhancementTree(ENHT_AASIMAR, ENHTT_RACE, AASIMAR, CLASSNONE, "Aasimar", true, "ElfBackground", Arrows);
	Arrows = "1-0-U-1, 1-4-U-2, 2-0-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_SCOURGE].InitializeEnhancementTree(ENHT_SCOURGE, ENHTT_RACE, SCOURGE, CLASSNONE, "Scourge", true, "ElfBackground", Arrows);

	//Class Trees (33) sorted by Class
	//Artificer
	Arrows = "1-0-U-2, 1-3-U-1, 2-1-U-1, 2-3-U-1, 3-0-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1";
	EnhancementTreeData[ENHT_ARCANOTECHNICIAN_ART].InitializeEnhancementTree(ENHT_ARCANOTECHNICIAN_ART, ENHTT_CLASS, RACENONE, ARTIFICER, "Arcanotechnician (Art)", true, "ArtificerBackground", Arrows);
	Arrows = "1-0-U-1, 2-0-U-1, 2-2-U-2, 3-0-U-1, 3-4-U-1, 4-0-U-1, 4-0-R-1, 4-2-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_BATTLE_ENGINEER_ART].InitializeEnhancementTree(ENHT_BATTLE_ENGINEER_ART, ENHTT_CLASS, RACENONE, ARTIFICER, "Battle Engineer (Art)", true, "ArtificerBackground", Arrows);
	//Barbarian
	Arrows = "1-1-U-1, 2-0-U-1, 2-1-U-2, 2-2-U-1, 3-0-U-2, 3-3-U-1, 3-3-L-1, 3-4-U-1";
	EnhancementTreeData[ENHT_FRENZIED_BERSERKER_BAR].InitializeEnhancementTree(ENHT_FRENZIED_BERSERKER_BAR, ENHTT_CLASS, RACENONE, BARBARIAN, "Frenzied Berserker (Bar)", true, "BarbarianBackground", Arrows);
	Arrows = "1-1-U-1, 1-2-U-1, 2-3-U-1, 3-0-U-2, 3-1-U-2, 3-2-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_OCCULT_SLAYER_BAR].InitializeEnhancementTree(ENHT_OCCULT_SLAYER_BAR, ENHTT_CLASS, RACENONE, BARBARIAN, "Occult Slayer (Bar)", true, "BarbarianBackground", Arrows);
	Arrows = "1-0-U-1, 1-1-U-1, 1-2-U-1, 2-2-U-2, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_RAVAGER_BAR].InitializeEnhancementTree(ENHT_RAVAGER_BAR, ENHTT_CLASS, RACENONE, BARBARIAN, "Ravager (Bar)", true, "BarbarianBackground", Arrows);
	//Bard
	Arrows = "3-3-U-1, 4-0-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_SPELLSINGER_BRD].InitializeEnhancementTree(ENHT_SPELLSINGER_BRD, ENHTT_CLASS, RACENONE, BARD, "Spellsinger (Brd)", true, "BardBackground", Arrows);
	Arrows = "3-1-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_SWASHBUCKLER_BRD].InitializeEnhancementTree(ENHT_SWASHBUCKLER_BRD, ENHTT_CLASS, RACENONE, BARD, "Swashbuckler (Brd)", true, "BardBackground", Arrows);
	Arrows = "1-0-U-1, 2-3-U-1, 3-3-U-1, 3-4-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_WARCHANTER_BRD].InitializeEnhancementTree(ENHT_WARCHANTER_BRD, ENHTT_CLASS, RACENONE, BARD, "Warchanter (Brd)", true, "BardBackground", Arrows);
	//Cleric
	Arrows = "1-3-U-1, 2-2-U-1, 2-3-U-1, 3-2-U-1, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_DIVINE_DISCIPLE_CLR].InitializeEnhancementTree(ENHT_DIVINE_DISCIPLE_CLR, ENHTT_CLASS, RACENONE, CLERIC, "Divine Disciple (Clr)", true, "ClericBackground", Arrows);
	Arrows = "1-2-U-1, 2-2-U-1, 2-3-U-1, 2-3-R-1, 3-1-U-1, 3-2-U-1, 3-4-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_WARPRIEST_CLR].InitializeEnhancementTree(ENHT_WARPRIEST_CLR, ENHTT_CLASS, RACENONE, CLERIC, "Warpriest (Clr)", true, "ClericBackground", Arrows);
	Arrows = "1-0-U-1, 1-2-U-1, 2-0-U-2, 2-0-R-1, 2-3-U-1, 3-1-U-1, 3-3-U-2, 3-4-U-1, 4-1-U-1";
	EnhancementTreeData[ENHT_RADIANT_SERVANT_CLR].InitializeEnhancementTree(ENHT_RADIANT_SERVANT_CLR, ENHTT_CLASS, RACENONE, CLERIC, "Radiant Servant (Clr)", true, "ClericBackground", Arrows);
	//Druid
	Arrows = "2-0-U-1, 3-0-U-2, 3-2-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_NATURES_WARRIOR_DRD].InitializeEnhancementTree(ENHT_NATURES_WARRIOR_DRD, ENHTT_CLASS, RACENONE, DRUID, "Nature's Warrior (Drd)", true, "DruidBackground", Arrows);
	Arrows = "1-2-U-1, 1-3-U-1, 2-2-U-1, 2-3-U-1, 3-2-U-1, 3-3-U-1, 3-4-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_SEASONS_HERALD_DRD].InitializeEnhancementTree(ENHT_SEASONS_HERALD_DRD, ENHTT_CLASS, RACENONE, DRUID, "Season's Herald (Drd)", true, "DruidBackground", Arrows);
	//Favored Soul
	Arrows = "1-0-U-1, 1-0-R-1, 1-2-U-1, 1-4-L-1, 2-1-U-1, 2-2-U-1, 3-1-U-1, 3-2-U-1, 3-4-U-1, 4-2-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_ANGEL_OF_VENGEANCE_FVS].InitializeEnhancementTree(ENHT_ANGEL_OF_VENGEANCE_FVS, ENHTT_CLASS, RACENONE, FAVORED_SOUL, "Angel of Vengeance (Fvs)", true, "FavoredSoulBackground", Arrows);
	Arrows = "1-2-U-1, 2-2-U-1, 2-3-U-1, 2-3-R-1, 3-1-U-1, 3-2-U-1, 3-4-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_WARPRIEST_FVS].InitializeEnhancementTree(ENHT_WARPRIEST_FVS, ENHTT_CLASS, RACENONE, FAVORED_SOUL, "Warpriest (Fvs)", true, "FavoredSoulBackground", Arrows);
	//Fighter
	Arrows = "1-1-U-1, 1-1-R-1, 2-1-U-1, 2-2-U-1, 3-1-U-1, 3-4-U-1, 4-1-U-1";
	EnhancementTreeData[ENHT_KENSEI_FTR].InitializeEnhancementTree(ENHT_KENSEI_FTR, ENHTT_CLASS, RACENONE, FIGHTER, "Kensei (Ftr)", true, "FighterBackground", Arrows);
	Arrows = "1-1-U-1, 1-2-U-1, 2-1-U-1, 2-3-U-1, 3-2-U-1, 3-4-U-1, 4-2-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_STALWART_DEFENDER_FTR].InitializeEnhancementTree(ENHT_STALWART_DEFENDER_FTR, ENHTT_CLASS, RACENONE, FIGHTER, "Stalwart Defender (Ftr)", true, "FighterBackground", Arrows);
	Arrows = "1-0-U-1, 2-0-U-1, 3-0-U-1";
	EnhancementTreeData[ENHT_VANGUARD_FTR].InitializeEnhancementTree(ENHT_VANGUARD_FTR, ENHTT_CLASS, RACENONE, FIGHTER, "Vanguard (Ftr)", true, "FighterBackground", Arrows);
	//Monk
	Arrows = "1-0-U-1, 1-1-U-1, 2-0-U-1, 2-1-U-1, 3-0-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1, 4-1-U-1";
	EnhancementTreeData[ENHT_HENSHIN_MYSTIC_MNK].InitializeEnhancementTree(ENHT_HENSHIN_MYSTIC_MNK, ENHTT_CLASS, RACENONE, MONK, "Henshin Mystic (Mnk)", true, "MonkBackground", Arrows);
	Arrows = "1-0-U-1, 1-2-U-1, 2-0-U-1, 2-2-U-1, 3-0-U-1, 3-2-U-1, 3-4-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_NINJA_SPY_MNK].InitializeEnhancementTree(ENHT_NINJA_SPY_MNK, ENHTT_CLASS, RACENONE, MONK, "Ninja Spy (Mnk)", true, "MonkBackground", Arrows);
	Arrows = "1-0-U-1, 2-0-U-1, 2-1-U-1, 2-2-U-2, 3-0-U-1, 3-1-U-1, 3-4-U-1, 4-0-U-1, 4-1-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_SHINTAO_MNK].InitializeEnhancementTree(ENHT_SHINTAO_MNK, ENHTT_CLASS, RACENONE, MONK, "Shintao (Mnk)", true, "MonkBackground", Arrows);
	//Paladin
	Arrows = "1-0-U-1, 3-1-U-1, 3-2-U-1, 3-4-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_KNIGHT_OF_THE_CHALICE_PAL].InitializeEnhancementTree(ENHT_KNIGHT_OF_THE_CHALICE_PAL, ENHTT_CLASS, RACENONE, PALADIN, "Knight of the Chalice (Pal)", true, "PaladinBackground", Arrows);
	Arrows = "1-2-U-1, 1-3-U-1, 2-1-U-1, 2-2-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_SACRED_DEFENDER_PAL].InitializeEnhancementTree(ENHT_SACRED_DEFENDER_PAL, ENHTT_CLASS, RACENONE, PALADIN, "Sacred Defender (Pal)", true, "PaladinBackground", Arrows);
	Arrows = "1-0-U-1, 2-0-U-1, 3-0-U-1";
	EnhancementTreeData[ENHT_VANGUARD_PAL].InitializeEnhancementTree(ENHT_VANGUARD_PAL, ENHTT_CLASS, RACENONE, PALADIN, "Vanguard (Pal)", true, "PaladinBackground", Arrows);
	//Ranger
	Arrows = "1-3-U-1, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-1-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_ARCANE_ARCHER_RNG].InitializeEnhancementTree(ENHT_ARCANE_ARCHER_RNG, ENHTT_CLASS, RACENONE, RANGER, "Arcane Archer (Rgr)", true, "RangerBackground", Arrows);
	Arrows = "1-1-U-1, 1-2-U-1, 1-2-R-1, 2-0-U-1, 3-0-U-1, 3-3-U-1, 3-4-U-1, 4-1-R-1";
	EnhancementTreeData[ENHT_DEEPWOOD_STALKER_RNG].InitializeEnhancementTree(ENHT_DEEPWOOD_STALKER_RNG, ENHTT_CLASS, RACENONE, RANGER, "Deepwood Stalker (Rgr)", true, "RangerBackground", Arrows);
	Arrows = "1-1-U-1, 1-3-U-1, 2-1-U-1, 2-3-U-1, 3-0-U-1, 3-3-U-1, 3-4-U-1, 4-1-U-1, 4-2-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_TEMPEST_RNG].InitializeEnhancementTree(ENHT_TEMPEST_RNG, ENHTT_CLASS, RACENONE, RANGER, "Tempest (Rgr)", true, "RangerBackground", Arrows);
	//Rogue
	Arrows = "1-3-U-1, 2-3-U-1, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_ASSASSIN_ROG].InitializeEnhancementTree(ENHT_ASSASSIN_ROG, ENHTT_CLASS, RACENONE, ROGUE, "Assassin (Rog)", true, "RogueBackground", Arrows);
	Arrows = "1-0-U-1, 1-2-U-2, 2-0-U-1, 3-0-U-1, 3-1-U-1, 4-0-U-1";
	EnhancementTreeData[ENHT_MECHANIC_ROG].InitializeEnhancementTree(ENHT_MECHANIC_ROG, ENHTT_CLASS, RACENONE, ROGUE, "Mechanic (Rog)", true, "RogueBackground", Arrows);
	Arrows = "1-0-U-1, 2-0-U-1, 2-3-U-1, 3-0-U-1, 3-3-U-1, 4-0-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_THIEF_ACROBAT_ROG].InitializeEnhancementTree(ENHT_THIEF_ACROBAT_ROG, ENHTT_CLASS, RACENONE, ROGUE, "Thief Acrobat (Rog)", true, "RogueBackground", Arrows);
	//Sorcerer
	Arrows = "1-0-U-3, 1-2-U-1, 1-3-U-1, 1-4-U-1, 2-1-U-1, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_AIR_SAVANT_SOR].InitializeEnhancementTree(ENHT_AIR_SAVANT_SOR, ENHTT_CLASS, RACENONE, SORCERER, "Air Savant (Sor)", true, "SorcererBackground", Arrows);
	Arrows = "1-0-U-3, 1-2-U-1, 1-3-U-1, 1-4-U-1, 2-1-U-1, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_EARTH_SAVANT_SOR].InitializeEnhancementTree(ENHT_EARTH_SAVANT_SOR, ENHTT_CLASS, RACENONE, SORCERER, "Earth Savant (Sor)", true, "SorcererBackground", Arrows);
	Arrows = "1-0-U-3, 1-2-U-1, 1-3-U-1, 1-4-U-1, 2-1-U-1, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_FIRE_SAVANT_SOR].InitializeEnhancementTree(ENHT_FIRE_SAVANT_SOR, ENHTT_CLASS, RACENONE, SORCERER, "Fire Savant (Sor)", true, "SorcererBackground", Arrows);
	Arrows = "1-0-U-3, 1-2-U-1, 1-3-U-1, 1-4-U-1, 2-1-U-1, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_WATER_SAVANT_SOR].InitializeEnhancementTree(ENHT_WATER_SAVANT_SOR, ENHTT_CLASS, RACENONE, SORCERER, "Water Savant (Sor)", true, "SorcererBackground", Arrows);
	//Wizard
	Arrows = "1-0-U-1, 2-2-U-2, 3-O-U-2, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_ELDRITCH_KNIGHT_SOR].InitializeEnhancementTree(ENHT_ELDRITCH_KNIGHT_SOR, ENHTT_CLASS, RACENONE, SORCERER, "Eldritch Knight (Sor)", true, "SorcererBackground", Arrows);
	Arrows = "1-3-U-1, 2-1-U-2, 2-1-L-1, 2-1-R-1, 2-3-U-1, 3-0-U-2, 3-3-U-1, 3-4-U-1, 4-2-U-1, 5-2-R-1";
	EnhancementTreeData[ENHT_ARCHMAGE_WIZ].InitializeEnhancementTree(ENHT_ARCHMAGE_WIZ, ENHTT_CLASS, RACENONE, WIZARD, "Archmage (Wiz)", true, "WizardBackground", Arrows);
	Arrows = "1-0-U-2, 1-2-U-1, 1-3-U-1, 2-2-U-1, 2-3-U-1, 3-0-U-2, 3-2-U-1, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_PALE_MASTER_WIZ].InitializeEnhancementTree(ENHT_PALE_MASTER_WIZ, ENHTT_CLASS, RACENONE, WIZARD, "Pale Master (Wiz)", true, "WizardBackground", Arrows);
	Arrows = "1-0-U-1, 2-2-U-2, 3-O-U-2, 3-3-U-1, 3-4-U-1";
	EnhancementTreeData[ENHT_ELDRITCH_KNIGHT_WIZ].InitializeEnhancementTree(ENHT_ELDRITCH_KNIGHT_WIZ, ENHTT_CLASS, RACENONE, WIZARD, "Eldritch Knight (Wiz)", true, "WizardBackground", Arrows);
	//Warlock
	Arrows = "1-4-U-1, 2-0-U-1, 3-0-U-1, 4-1-U-1";
	EnhancementTreeData[ENHT_SOULEATER_WLK].InitializeEnhancementTree(ENHT_SOULEATER_WLK, ENHTT_CLASS, RACENONE, WARLOCK, "Soul Eater (Wlk)", true, "WarlockBackground", Arrows);
	Arrows = "1-3-U-1, 2-0-U-1, 2-3-U-1, 3-0-U-1, 3-2-U-1, 3-3-U-1, 3-4-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_TANTEDSCHOLAR_WLK].InitializeEnhancementTree(ENHT_TANTEDSCHOLAR_WLK, ENHTT_CLASS, RACENONE, WARLOCK, "Tainted Scholar (Wlk)", true, "WarlockBackground", Arrows);
	Arrows = "1-1-U-1, 2-1-U-1, 2-2-U-1, 3-1-U-1, 3-3-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_ENLIGHTENEDSPIRIT_WLK].InitializeEnhancementTree(ENHT_ENLIGHTENEDSPIRIT_WLK, ENHTT_CLASS, RACENONE, WARLOCK, "Enlightened Spirit (Wlk)", true, "WarlockBackground", Arrows);



	//Special Trees (1)
	Arrows = "1-3-U-1, 2-3-U-1, 3-1-U-1, 3-3-U-1, 3-4-U-1, 4-1-U-1, 4-3-U-1";
	EnhancementTreeData[ENHT_ARCANE_ARCHER_ELF].InitializeEnhancementTree(ENHT_ARCANE_ARCHER_ELF, ENHTT_SPECIAL, ELF, CLASSNONE, "Arcane Archer (Elf)", true, "ElfBackground", Arrows);
	Arrows = "";
	EnhancementTreeData[ENHT_HARPER_AGENT].InitializeEnhancementTree(ENHT_HARPER_AGENT, ENHTT_SPECIAL, RACENONE, CLASSNONE, "Harper Agent", true, "SpecialBackground", Arrows);
	Arrows = "1-2-U-1, 2-0-U-1, 2-2-U-1, 3-0-U-1, 3-2-U-1, 4-0-U-1, 4-2-U-1";
	EnhancementTreeData[ENHT_VISTANIKNIFEFIGHTER].InitializeEnhancementTree(ENHT_VISTANIKNIFEFIGHTER, ENHTT_SPECIAL, RACENONE, CLASSNONE, "Vistani Knife Fighter", true, "SpecialBackground", Arrows);
}

//---------------------------------------------------------------------------
ENHANCEMENT_TREE DataClass::GetRacialTree(RACE CurrentRace)
	{
	for (int i=0; i<NUM_ENHANCEMENT_TREES; i++)
		{
		if (EnhancementTreeData[i].GetTreeRace() == CurrentRace && EnhancementTreeData[i].GetTreeType() == ENHTT_RACE)
			return EnhancementTreeData[i].GetTreeIndex();
		}
	return ENHT_NOTREE;
	}

//---------------------------------------------------------------------------
int DataClass::GetClassEnhancementTreeCount(CLASS CurrentClass)
	{
	int Count = 0;
	for (int i=0; i<NUM_ENHANCEMENT_TREES; i++)
		{
		if (EnhancementTreeData[i].GetTreeClass() == CurrentClass && EnhancementTreeData[i].GetTreeType() == ENHTT_CLASS)
			Count ++;
		}
	return Count;
	}

//---------------------------------------------------------------------------
void DataClass::GetClassTrees(vector <ENHANCEMENT_TREE>& rClassTrees, CLASS CurrentClass)
	{
	for (int i=0; i<NUM_ENHANCEMENT_TREES; i++)
		{
		if (EnhancementTreeData[i].GetTreeClass() == CurrentClass && EnhancementTreeData[i].GetTreeType() == ENHTT_CLASS)
			rClassTrees.push_back(EnhancementTreeData[i].GetTreeIndex());
		}
	}