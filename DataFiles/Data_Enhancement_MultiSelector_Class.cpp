#include "Data_Enhancement_MultiSelector_Class.h"
#include "InterfaceManagerClass.h"


//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class::Data_Enhancement_MultiSelector_Class()
	{
	Name = "";
	Description = "";
	MultiEnhancementIcon.Name = "";
	MultiEnhancementIcon.Graphic = nullptr;
	MultiEnhancementIcon.Mask = nullptr;
	MultiEnhancementIcon.Width = 0;
	MultiEnhancementIcon.Height = 0;
	}

//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class::~Data_Enhancement_MultiSelector_Class()
	{
	}

//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class::Data_Enhancement_MultiSelector_Class(const Data_Enhancement_MultiSelector_Class &source)
	{
	Name = source.Name;
	Description = source.Description;
	MultiEnhancementIcon.Name = source.MultiEnhancementIcon.Name;
	MultiEnhancementIcon.Graphic = (HBITMAP)CopyImage(source.MultiEnhancementIcon.Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	MultiEnhancementIcon.Mask = (HBITMAP)CopyImage(source.MultiEnhancementIcon.Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	MultiEnhancementIcon.Width = source.MultiEnhancementIcon.Width;
	MultiEnhancementIcon.Height = source.MultiEnhancementIcon.Height;
	}

//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class& Data_Enhancement_MultiSelector_Class::operator=(const Data_Enhancement_MultiSelector_Class &source)
	{
	Name = source.Name;
	Description = source.Description;
	MultiEnhancementIcon.Name = source.MultiEnhancementIcon.Name;
	MultiEnhancementIcon.Graphic = (HBITMAP)CopyImage(source.MultiEnhancementIcon.Graphic, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	MultiEnhancementIcon.Mask = (HBITMAP)CopyImage(source.MultiEnhancementIcon.Mask, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG); 
	MultiEnhancementIcon.Width = source.MultiEnhancementIcon.Width;
	MultiEnhancementIcon.Height = source.MultiEnhancementIcon.Height;

	return *this;
	}

//---------------------------------------------------------------------------
void Data_Enhancement_MultiSelector_Class::InitializeMultiSelector(string SelectorData)
	{
    #define NUMKEYWORDS 3

	string KeywordString[NUMKEYWORDS];
	string EnhancementLine[NUMKEYWORDS];
	size_t StartLoc;
	size_t EndLoc;
	
    //parse the SelectorData string, storing each line of the string
    //into its appropriate individual line
	KeywordString[0] = "NAME: ";
	KeywordString[1] = "DESC: ";
	KeywordString[2] = "ICON: ";

    for (unsigned int i=0; i<NUMKEYWORDS; i++)
		{
		EnhancementLine[i] = "";
		if (SelectorData.find(KeywordString[i]) != string::npos)
			{
			//find the first semicolon after our keyword. Store that as our individual line
			//(note that this function cuts off the ending semicolon, which is fine)
			StartLoc = SelectorData.find(KeywordString[i]);
			EndLoc = SelectorData.find(";", SelectorData.find(KeywordString[i])); 
			EnhancementLine[i] = SelectorData.substr(SelectorData.find(KeywordString[i]), EndLoc-StartLoc);
			//drop the keyword from the line string, we don't need it now
			EnhancementLine[i].erase(0, KeywordString[i].size());
			}
		}

	//alright, run through each line and store its data into member variables
    for (unsigned int i=0; i<NUMKEYWORDS; i++)
        {
        switch (i)
            {
            case 0:     //the name
				{
                Name = EnhancementLine[i];
				break;
				}
			case 1:		//the description
				{
                Description = EnhancementLine[i];
				break;
				}
			case 2:		//the Icon
				{
				LoadBitmap(EnhancementLine[i], "Enhancements", &MultiEnhancementIcon);
				break;
				}
			}
		}

    return;
    #undef NUMKEYWORDS
	}


//---------------------------------------------------------------------------
string Data_Enhancement_MultiSelector_Class::GetName()
	{
	return Name;
	}

//---------------------------------------------------------------------------
string Data_Enhancement_MultiSelector_Class::GetDescription()
	{
	return Description;
	}

//---------------------------------------------------------------------------
GraphicStruct Data_Enhancement_MultiSelector_Class::GetIcon()
	{
	return MultiEnhancementIcon;
	}

//---------------------------------------------------------------------------
Data_Enhancement_MultiSelector_Class* Data_Enhancement_MultiSelector_Class::GetMultiEnhancementAddress()
	{
	return this;
	}


