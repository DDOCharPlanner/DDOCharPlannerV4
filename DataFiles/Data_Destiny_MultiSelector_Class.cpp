#include "Data_Destiny_MultiSelector_Class.h"
//#include "InterfaceManagerClass.h"

//-------------------------------------------------------------------------------------------------
Data_Destiny_MultiSelector_Class::Data_Destiny_MultiSelector_Class()
	{
	Name = "";
	Description.clear();
	MultiDestinyIcon.clear();
	/*MultiDestinyIcon.Name = "";
	MultiDestinyIcon.Graphic = nullptr;
	MultiDestinyIcon.Mask = nullptr;
	MultiDestinyIcon.Width = 0;
	MultiDestinyIcon.Height = 0;*/
	}

//--------------------------------------------------------------------------------------------------
Data_Destiny_MultiSelector_Class::~Data_Destiny_MultiSelector_Class()
	{

	}

//--------------------------------------------------------------------------------------------------
Data_Destiny_MultiSelector_Class::Data_Destiny_MultiSelector_Class(const Data_Destiny_MultiSelector_Class &source)
	{
	GraphicStruct DummyIcon;

	DummyIcon.Name = "";
	DummyIcon.Graphic = nullptr;
	DummyIcon.Mask = nullptr;
	DummyIcon.Width = 0;
	DummyIcon.Height = 0;

	Name = source.Name;
	for (unsigned int x=0; x<source.Description.size(); x++)
		Description.push_back(source.Description[x]);
		//Description[x] = source.Description[x];
	for (unsigned int x=0; x<source.MultiDestinyIcon.size(); x++)
		{
		MultiDestinyIcon.push_back(DummyIcon);
		MultiDestinyIcon[MultiDestinyIcon.size()-1].Name = source.MultiDestinyIcon[x].Name;
		MultiDestinyIcon[MultiDestinyIcon.size()-1].Graphic = (HBITMAP)CopyImage(source.MultiDestinyIcon[x].Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
		MultiDestinyIcon[MultiDestinyIcon.size()-1].Mask = (HBITMAP)CopyImage(source.MultiDestinyIcon[x].Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
		MultiDestinyIcon[MultiDestinyIcon.size()-1].Width = source.MultiDestinyIcon[x].Width;
		MultiDestinyIcon[MultiDestinyIcon.size()-1].Height = source.MultiDestinyIcon[x].Height;
		}
	}

//--------------------------------------------------------------------------------------------------
Data_Destiny_MultiSelector_Class& Data_Destiny_MultiSelector_Class::operator=(const Data_Destiny_MultiSelector_Class &source)
	{
	Name = source.Name;
	for (unsigned int x=0; x<Description.size(); x++)
		Description[x] = source.Description[x];
	for (unsigned int x=0; x<MultiDestinyIcon.size(); x++)
		{
		MultiDestinyIcon[x].Name = source.MultiDestinyIcon[x].Name;
		MultiDestinyIcon[x].Graphic = (HBITMAP)CopyImage(source.MultiDestinyIcon[x].Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
		MultiDestinyIcon[x].Mask = (HBITMAP)CopyImage(source.MultiDestinyIcon[x].Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
		MultiDestinyIcon[x].Width = source.MultiDestinyIcon[x].Width;
		MultiDestinyIcon[x].Height = source.MultiDestinyIcon[x].Height;
		}

	return *this;
	}

//-------------------------------------------------------------------------------------------------
void Data_Destiny_MultiSelector_Class::InitializeMultiSelector(string SelectorData)
	{
	#define NUMKEYWORDS 3

	string KeywordString[NUMKEYWORDS];
	string DestinyLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	string Substring;
	GraphicStruct NewIcon;

	NewIcon.Name = "";
	NewIcon.Graphic = nullptr;
	NewIcon.Mask = nullptr;
	NewIcon.Width = 0;
	NewIcon.Height = 0;
	
    //parse the SelectorData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "NAME: ";
	KeywordString[1] = "DESC: ";
	KeywordString[2] = "ICON: ";

    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		DestinyLine[i] = "";
		if (SelectorData.find(KeywordString[i]) != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = SelectorData.find(KeywordString[i]);
			EndLoc = SelectorData.find(";", SelectorData.find(KeywordString[i])); 
			DestinyLine[i] = SelectorData.substr(SelectorData.find(KeywordString[i]), EndLoc-StartLoc);
			//drop the keyword from the line string, we don't need it now
			DestinyLine[i].erase(0, KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
        {
        switch (i)
            {
            case 0:     //the name
				{
                Name = DestinyLine[i];
				break;
				}
			case 1:		//the description
				{
				while (DestinyLine[i].find(",,") != string::npos)
					{
					StripStringLeadingWhiteSpace(DestinyLine[i]);
					EndLoc = DestinyLine[i].find(",,");
					Substring = DestinyLine[i].substr(0, EndLoc);
					Description.push_back(Substring);
					DestinyLine[i].erase(0, EndLoc+2);
					}
				if (DestinyLine[i] != "")
					{
					Substring = DestinyLine[i];
					Description.push_back(Substring);
					}
				break;
				}
			case 2:		//the Icon
				{
				while (DestinyLine[i].find(",,") != string::npos)
					{
					StripStringLeadingWhiteSpace(DestinyLine[i]);
					EndLoc = DestinyLine[i].find(",,");
					Substring = DestinyLine[i].substr(0, EndLoc);
					MultiDestinyIcon.push_back(NewIcon);
					LoadBitmap(Substring, "Destinies", &MultiDestinyIcon[MultiDestinyIcon.size()-1]);
					DestinyLine[i].erase(0, EndLoc+2);
					}
				if (DestinyLine[i] != "")
					{
					Substring = DestinyLine[i];
					MultiDestinyIcon.push_back(NewIcon);
					LoadBitmap(Substring, "Destinies", &MultiDestinyIcon[MultiDestinyIcon.size()-1]);
					}
				break;
				}
			}
		}

    return;
    #undef NUMKEYWORDS
	}

//---------------------------------------------------------------------------
string Data_Destiny_MultiSelector_Class::GetName()
	{
	return Name;
	}

//---------------------------------------------------------------------------
string Data_Destiny_MultiSelector_Class::GetDescription(unsigned int Index)
	{
	return Description[Index];
	}

//---------------------------------------------------------------------------
GraphicStruct Data_Destiny_MultiSelector_Class::GetIcon(unsigned int Index)
	{
	return MultiDestinyIcon[Index];
	}

//---------------------------------------------------------------------------
Data_Destiny_MultiSelector_Class* Data_Destiny_MultiSelector_Class::GetMultiDestinyAddress()
	{
	return this;
	}

//---------------------------------------------------------------------------
void Data_Destiny_MultiSelector_Class::StripStringLeadingWhiteSpace(string &SourceString)
	{
	while (SourceString.size() > 0 && SourceString[0] == ' ')
		SourceString.erase(0, 1);
	}

