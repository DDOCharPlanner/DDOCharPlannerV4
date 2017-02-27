#include "PrintClass.h"
#include "CharacterClass.h"
#include "InterfaceManagerClass.h"
#include "DataClass.h"

//---------------------------------------------------------------------------
PrintClass::PrintClass()
	{
	}

//---------------------------------------------------------------------------
PrintClass::~PrintClass()
	{
	}

//---------------------------------------------------------------------------
void PrintClass::Print(HDC PrinterDC, int AtLevelSnapshot, int AtLevelGuideMin, int AtLevelGuideMax, bool SnapShot, bool LevelGuide)
	{
	if (SnapShot == false && LevelGuide == false)
		return;

	if (PrintSetup(PrinterDC) == false)
		return;
	
	if (SnapShot == true)
		PrintSnapshot(PrinterDC, AtLevelSnapshot);

	if (LevelGuide == true)
		PrintLevelGuide(PrinterDC, AtLevelGuideMin, AtLevelGuideMax);

	PrintCleanup(PrinterDC);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintSnapshot(HDC PrinterDC, int AtLevel)
	{
	//validate the level
	for (int i=0; i<AtLevel; i++)
		{
		if (Character.GetClass(i+1, false) == CLASSNONE)
			{
			AtLevel = i+1;
			break;
			}
		}	

	if (StartPage(PrinterDC) <= 0)
		{
		PrintCleanup(PrinterDC);
		return;
		}

	PrintHeader(PrinterDC, 0.0f, 0.0f);
	PrintClassBlock(PrinterDC, AtLevel, 0.7f, 8.7f);
	PrintAbilityScoresBlock(PrinterDC, AtLevel, 0.7f, 15.5f);
	PrintSavingThrows(PrinterDC, AtLevel, 0.7f, 37.0f);
	PrintDefense(PrinterDC, AtLevel, 48.7f, 15.5f);
	PrintOffense(PrinterDC, AtLevel, 41.7f, 37.0f);
	PrintRage(PrinterDC, AtLevel, 80.0f, 37.0f);
	PrintTurnUndead(PrinterDC, AtLevel, 80.0f, 48.5f);
	PrintItemsWorn(PrinterDC, AtLevel, 0.7f, 52.0f);
	PrintItemsNonWorn(PrinterDC, AtLevel, 0.7f, 75.5f);
	PrintSkillsBlock(PrinterDC, AtLevel, 41.7f, 55.2f);
	PrintNotesBlock(PrinterDC, 80.0f, 57.0f);

	EndPage(PrinterDC);

	if (StartPage(PrinterDC) <= 0)
		{
		PrintCleanup(PrinterDC);
		return;
		}

	PrintHeader(PrinterDC, 0.0f, 0.0f);
	PrintFeatBlock(PrinterDC, AtLevel, 0.7f, 8.7f);
	PrintEnhancementBlock(PrinterDC, AtLevel, 0.7f, 43.0f);

	EndPage(PrinterDC);

	if (StartPage(PrinterDC) <= 0)
		{
		PrintCleanup(PrinterDC);
		return;
		}

	PrintHeader(PrinterDC, 0.0f, 0.0f);
	PrintSpellBlock(PrinterDC, AtLevel, 0.7f, 8.7f);

	EndPage(PrinterDC);

	}

//---------------------------------------------------------------------------
void PrintClass::PrintLevelGuide(HDC PrinterDC, int AtLevelMin, int AtLevelMax)
	{
	ostringstream ss;
	int Column;
	int Row;

	//validate the level
	for (int i=0; i<AtLevelMax; i++)
		{
		if (Character.GetClass(i+1, false) == CLASSNONE)
			{
			AtLevelMax = i;
			break;
			}
		}	

	if (StartPage(PrinterDC) <= 0)
		{
		PrintCleanup(PrinterDC);
		return;
		}

	PrintHeader(PrinterDC, 0.0f, 0.0f);
	SelectObject(PrinterDC, PrintFontLabels);
	SetTextColor(PrinterDC, RGB(0, 0, 0));
	SetBkColor(PrinterDC, RGB(255, 255, 255));
	Column = 0;
	Row = 0;
	for (int i=AtLevelMin-1; i<AtLevelMax; i++)
		{
		PrintLevelGuideLevel(PrinterDC, i, &Column, &Row);
		}

	EndPage(PrinterDC);
	}

//---------------------------------------------------------------------------
bool PrintClass::PrintSetup(HDC hDC)
	{
	LOGFONT LogFont;

	//set up the doc info
	DocInfo.cbSize = sizeof(DOCINFO);
	DocInfo.lpszDocName = "DDO Character Plan Print";
	DocInfo.lpszOutput = (LPTSTR) NULL;
	DocInfo.lpszDatatype = (LPTSTR) NULL;
	DocInfo.fwType = 0;

	LogPelsX = GetDeviceCaps(hDC, HORZRES);
	LogPelsY = GetDeviceCaps(hDC, VERTRES);
    OnePercentX = (float)LogPelsX/100.0f;
    OnePercentY = (float)LogPelsY/100.0f;
	
	LogFont.lfHeight = -MulDiv(6, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	LogFont.lfWidth = 0;
	LogFont.lfEscapement =  0;
	LogFont.lfOrientation = 0;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfItalic = FALSE;
	LogFont.lfUnderline = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = ANSI_CHARSET;
	LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	LogFont.lfQuality = PROOF_QUALITY;
	LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	StringCbCopy (LogFont.lfFaceName, LF_FACESIZE, TEXT("Tahoma"));
	PrintFontLabels = CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	LogFont.lfWeight = FW_BOLD;
	PrintFontLabelBold = CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -MulDiv(6, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	PrintFontLabelBoldSmall = CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -MulDiv(4, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	LogFont.lfWeight = FW_NORMAL;
	PrintFontLabelTiny1 = CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -MulDiv(3, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	PrintFontLabelTiny2 = CreateFontIndirect(&LogFont);

	StringCbCopy (LogFont.lfFaceName, LF_FACESIZE, TEXT("Comic Sans MS"));
	LogFont.lfHeight = -MulDiv(30, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	PrintFontLarge = CreateFontIndirect(&LogFont);

	StringCbCopy (LogFont.lfFaceName, LF_FACESIZE, TEXT("Georgia"));
	LogFont.lfHeight = -MulDiv(11, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	PrintFontData = CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -MulDiv(6, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	PrintFontDataSmall = CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -MulDiv(5, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	PrintFontDataTiny = CreateFontIndirect(&LogFont);

	EntryLine = CreatePen(PS_SOLID, (int)(0.10*OnePercentX), RGB(0, 0, 0));

	BoldLine = CreatePen(PS_SOLID, (int)(25.0*OnePercentX), RGB(0, 0, 0));

	OriginalPen = (HPEN)SelectObject(hDC, EntryLine);
	OriginalFont = (HFONT)SelectObject(hDC, PrintFontLabels);

	//load needed graphics
	LoadBitmap("Logo", "UserInterface", &Logo);
	LoadBitmap("Swirl", "UserInterface", &Swirl);

	//start the document
	if (StartDoc(hDC, &DocInfo) > 0)
		return true;
	return false;
	}

//---------------------------------------------------------------------------
void PrintClass::PrintCleanup(HDC hDC)
	{
	SelectObject(hDC, OriginalFont);
	SelectObject(hDC, OriginalPen);
	DeleteObject(EntryLine);
	DeleteObject(BoldLine);
	DeleteObject(PrintFontLabels);
	DeleteObject(PrintFontLabelBold);
	DeleteObject(PrintFontLabelBoldSmall);
	DeleteObject(PrintFontLabelTiny1);
	DeleteObject(PrintFontLabelTiny2);
	DeleteObject(PrintFontLarge);
	DeleteObject(PrintFontData);
	DeleteObject(PrintFontDataSmall);
	DeleteObject(PrintFontDataTiny);
    DeleteObject(Logo.Graphic);
    DeleteObject(Swirl.Graphic);
	EndDoc(hDC);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintHeader(HDC hDC, float BaseX, float BaseY)
	{
	string Text;
	string FirstName;
	string SurName;
    ostringstream ss;

	PrintGraphic(hDC, &Logo, BaseX+70.0f, BaseY, 30.0f, 8.0f);
	PrintShaded(hDC, 0.0f, BaseX, BaseY, 70.0f, 8.0f);

	SelectObject(hDC, PrintFontLarge);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	//first print out the header
	Character.GetName(&FirstName, &SurName);
    ss.str("");
    ss << FirstName << " " << SurName;
    Text = ss.str();
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	SelectObject(hDC, PrintFontLabels);
    ss.str("");
    ss << "DDO Character Planner Version " << VERSION;
    Text = ss.str();
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+7.0f)), Text.c_str(), static_cast<int>(Text.size()));
	}

//---------------------------------------------------------------------------
void PrintClass::PrintClassBlock(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
    ostringstream ss;
	int MaxKi;
	int StableKi;

	SelectObject(hDC, PrintFontLabels);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));

	//first print out the labels
    Text = "CLASS AND LEVEL";
	TextOut(hDC, static_cast<int>(OnePercentX*BaseX), static_cast<int>(OnePercentY*(BaseY+1.8f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "RACE";
	TextOut(hDC, static_cast<int>(OnePercentX*BaseX), static_cast<int>(OnePercentY*(BaseY+4.8f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "GENDER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+26.8f)), static_cast<int>(OnePercentY*(BaseY+4.8f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "ALIGNMENT";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.8f)), static_cast<int>(OnePercentY*(BaseY+4.8f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "HIT POINTS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+52.0f)), static_cast<int>(OnePercentY*(BaseY+1.8f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "SPELL POINTS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+67.0f)), static_cast<int>(OnePercentY*(BaseY+1.8f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "KI (STABLE / MAX)";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+82.0f)), static_cast<int>(OnePercentY*(BaseY+1.8f)), Text.c_str(), static_cast<int>(Text.size()));
	
	//some lines
	PrintLine(hDC, EntryLine, BaseX, BaseY+1.7f, 50.0f);
	PrintLine(hDC, EntryLine, BaseX, BaseY+4.7f, 25.0f);
	PrintLine(hDC, EntryLine, BaseX+26.8f, BaseY+4.7f, 7.5f);
	PrintLine(hDC, EntryLine, BaseX+36.8f, BaseY+4.7f, 13.2f);
	PrintLine(hDC, EntryLine, BaseX+52.0f, BaseY+1.7f, 12.5f);
	PrintLine(hDC, EntryLine, BaseX+67.0f, BaseY+1.7f, 12.5f);
	PrintLine(hDC, EntryLine, BaseX+82.0f, BaseY+1.7f, 12.5f);

	//data output
	SelectObject(hDC, PrintFontData);
	Text = Character.GetClassString(AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.3f)), static_cast<int>(OnePercentY*BaseY), Text.c_str(), static_cast<int>(Text.size()));
	Text = Character.GetRaceString();
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.3f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	if (Character.GetSex() == MALE)
		Text = "Male";
	else
		Text = "Female";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+27.1f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = Data.GetAlignmentString(Character.GetAlignment());
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+37.1f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	ss << Character.GetHitPoints(AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+52.3f)), static_cast<int>(OnePercentY*BaseY), ss.str().c_str(), static_cast<int>(ss.str().size()));
 	ss.str("");
	ss << Character.GetSpellPoints(AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+67.3f)), static_cast<int>(OnePercentY*BaseY), ss.str().c_str(), static_cast<int>(ss.str().size()));
 	ss.str("");
	Character.GetKiPoints(AtLevel, &MaxKi, &StableKi);
	ss << StableKi << " / " << MaxKi;
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+82.3f)), static_cast<int>(OnePercentY*BaseY), ss.str().c_str(), static_cast<int>(ss.str().size()));
	}

//---------------------------------------------------------------------------
void PrintClass::PrintAbilityScoresBlock(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ostringstream ss;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 46.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "ABILITY SCORES";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));

	Text = "STR";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DEX";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+6.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CON";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+9.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "INT";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WIS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+15.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CHA";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+18.0f)), Text.c_str(), static_cast<int>(Text.size()));

	SelectObject(hDC, PrintFontLabelTiny2);
	Text = "STRENGTH";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DEXTERITY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+7.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CONSTITUTION";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+10.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "INTELLIGENCE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+13.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WISDOM";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+16.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CHARSIMA";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+19.2f)), Text.c_str(), static_cast<int>(Text.size()));
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	Text = "TOTAL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+4.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+7.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+10.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+13.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+16.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+19.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "BASE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "LEVEL UP";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "INHERENT";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "FEATS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ENHANCEMENT";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ENCHANTED";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "STRENGTH";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+4.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DEXTERITY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+7.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CONSTITUTION";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+10.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "INTELLIGENCE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+13.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WISDOM";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+16.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CHARSIMA";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+19.6f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "MODIFIER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+5.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+8.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+14.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+17.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+20.1f)), Text.c_str(), static_cast<int>(Text.size()));
	SelectObject(hDC, PrintFontLabelTiny1);
	Text = "=";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+9.25f)), static_cast<int>(OnePercentY*(BaseY+3.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+9.25f)), static_cast<int>(OnePercentY*22.0f), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+9.25f)), static_cast<int>(OnePercentY*25.0f), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+9.25f)), static_cast<int>(OnePercentY*28.0f), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+9.25f)), static_cast<int>(OnePercentY*31.0f), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+9.25f)), static_cast<int>(OnePercentY*34.0f), Text.c_str(), static_cast<int>(Text.size()));
	Text = "+";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.75f)), static_cast<int>(OnePercentY*(BaseY+3.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.75f)), static_cast<int>(OnePercentY*(BaseY+6.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.75f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.75f)), static_cast<int>(OnePercentY*(BaseY+12.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.75f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.75f)), static_cast<int>(OnePercentY*(BaseY+18.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.25f)), static_cast<int>(OnePercentY*(BaseY+3.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.25f)), static_cast<int>(OnePercentY*(BaseY+6.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.25f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.25f)), static_cast<int>(OnePercentY*(BaseY+12.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.25f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.25f)), static_cast<int>(OnePercentY*(BaseY+18.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+3.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+6.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+12.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+18.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+31.25f)), static_cast<int>(OnePercentY*(BaseY+3.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+31.25f)), static_cast<int>(OnePercentY*(BaseY+6.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+31.25f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+31.25f)), static_cast<int>(OnePercentY*(BaseY+12.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+31.25f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+31.25f)), static_cast<int>(OnePercentY*(BaseY+18.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.75f)), static_cast<int>(OnePercentY*(BaseY+3.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.75f)), static_cast<int>(OnePercentY*(BaseY+6.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.75f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.75f)), static_cast<int>(OnePercentY*(BaseY+12.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.75f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+36.75f)), static_cast<int>(OnePercentY*(BaseY+18.5f)), Text.c_str(), static_cast<int>(Text.size()));
	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	
	//lines
	PrintLine(hDC, EntryLine, BaseX+4.5f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+4.5f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+4.5f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+4.5f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+4.5f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+4.5f, BaseY+19.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+19.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+15.5f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+15.5f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+15.5f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+15.5f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+15.5f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+15.5f, BaseY+19.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+21.0f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+21.0f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+21.0f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+21.0f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+21.0f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+21.0f, BaseY+19.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+26.5f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+26.5f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+26.5f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+26.5f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+26.5f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+26.5f, BaseY+19.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.0f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.0f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.0f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.0f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.0f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.0f, BaseY+19.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+4.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+7.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+10.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+13.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+16.5f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+19.5f, 4.0f);

	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+4.5f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+7.5f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+10.5f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+13.5f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+16.5f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+19.5f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+2.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+5.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+8.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+11.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+14.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+17.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+46.0f, BaseY+2.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+46.0f, BaseY+5.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+46.0f, BaseY+8.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+46.0f, BaseY+11.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+46.0f, BaseY+14.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+46.0f, BaseY+17.7f, 1.8f, true);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+2.7f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+5.7f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+8.7f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+11.7f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+14.7f, 3.0f);
	PrintLine(hDC, EntryLine, BaseX+43.0f, BaseY+17.7f, 3.0f);

	//data output
	SelectObject(hDC, PrintFontData);
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	//total stat
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+6.5f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	//base ability
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+12.0f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	//level ups
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_LEVELUP, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_LEVELUP, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_LEVELUP, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_LEVELUP, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_LEVELUP, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_LEVELUP, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.5f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	//inherent modifier
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_INHERENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_INHERENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_INHERENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_INHERENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_INHERENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_INHERENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.0f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	//feats modifier
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.5f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	
	//enhancement modifier
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.0f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	//enchanted modifier
	ss.str("");
	ss << Character.GetAbilityMod(STRENGTH, ABMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(DEXTERITY, ABMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CONSTITUTION, ABMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(INTELLIGENCE, ABMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(WISDOM, ABMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetAbilityMod(CHARISMA, ABMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	//ability modifier
	ss.str("");
	if (Character.CalculateTotalAbilityMod(STRENGTH, AtLevel) > 0)
		ss << "+";
	ss << Character.CalculateTotalAbilityMod(STRENGTH, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	if (Character.CalculateTotalAbilityMod(DEXTERITY, AtLevel) > 0)
		ss << "+";
	ss << Character.CalculateTotalAbilityMod(DEXTERITY, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+5.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	if (Character.CalculateTotalAbilityMod(CONSTITUTION, AtLevel) > 0)
		ss << "+";
	ss << Character.CalculateTotalAbilityMod(CONSTITUTION, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+8.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	if (Character.CalculateTotalAbilityMod(INTELLIGENCE, AtLevel) > 0)
		ss << "+";
	ss << Character.CalculateTotalAbilityMod(INTELLIGENCE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+11.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	if (Character.CalculateTotalAbilityMod(WISDOM, AtLevel) > 0)
		ss << "+";
	ss << Character.CalculateTotalAbilityMod(WISDOM, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+14.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	if (Character.CalculateTotalAbilityMod(CHARISMA, AtLevel) > 0)
		ss << "+";
	ss << Character.CalculateTotalAbilityMod(CHARISMA, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+44.5f)), static_cast<int>(OnePercentY*(BaseY+17.8f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintOffense(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	string Text2;
	ostringstream ss;
	int Value;
	int Item;
	unsigned int Pos;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 37.0f, 2.0f);
	PrintShaded(hDC, 90.0f, BaseX, BaseY+5.0f, 37.0f, 5.7f);
	PrintShaded(hDC, 90.0f, BaseX, BaseY+12.0f, 37.0f, 5.7f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "OFFENSE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));

	Text = "BASE ATTACK BONUS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));

	SetBkColor(hDC, RGB(230, 230, 230));
	SelectObject(hDC, PrintFontLabelTiny1);
	Text = "WEAPON";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+7.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+14.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ATTACK BONUS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+10.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+17.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DAMAGE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+7.0f)), static_cast<int>(OnePercentY*(BaseY+10.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+7.0f)), static_cast<int>(OnePercentY*(BaseY+17.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CRITICAL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.0f)), static_cast<int>(OnePercentY*(BaseY+10.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+17.0f)), static_cast<int>(OnePercentY*(BaseY+17.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "TYPE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+27.0f)), static_cast<int>(OnePercentY*(BaseY+10.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+27.0f)), static_cast<int>(OnePercentY*(BaseY+17.0f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	PrintLine(hDC, EntryLine, BaseX+16.0f, BaseY+4.0f, 21.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+7.2f, 35.3f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+14.2f, 35.3f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+9.7f, 5.3f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+16.7f, 5.3f);
	PrintLine(hDC, EntryLine, BaseX+7.0f, BaseY+9.7f, 9.0f);
	PrintLine(hDC, EntryLine, BaseX+7.0f, BaseY+16.7f, 9.0f);
	PrintLine(hDC, EntryLine, BaseX+17.0f, BaseY+9.7f, 9.0f);
	PrintLine(hDC, EntryLine, BaseX+17.0f, BaseY+16.7f, 9.0f);
	PrintLine(hDC, EntryLine, BaseX+27.0f, BaseY+9.7f, 9.0f);
	PrintLine(hDC, EntryLine, BaseX+27.0f, BaseY+16.7f, 9.0f);

	//data output
	SelectObject(hDC, PrintFontData);
	//BAB
    ss.str("");
    Value = Character.CalculateBAB(AtLevel);
    ss << Value;
    if (Value > 0)
        {
        ss << "\\";
        ss << Value;
        }
    if (Value > 4)
        {
        ss << "\\";
        ss << (Value+5);
        }
    if (Value > 9)
        {
        ss << "\\";
        ss << (Value+10);
        }
    if (Value > 14)
        {
        ss << "\\";
        ss << (Value+10);
        }
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+16.5f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	SetBkColor(hDC, RGB(230, 230, 230));
	SelectObject(hDC, PrintFontDataSmall);
	Item = Character.GetActiveEquipment(RIGHTHANDSLOT);
	if (Item != -1)
		{
		Text = "";
		Text2 = Character.GetItemDisplayName(Item);
		if (Text2.size() > 65)
			{
			Pos = Text2.find_last_of(" ", 65);
			Text = Text2.substr(0, Pos);
			Text2 = Text2.substr(Pos, string::npos);
			}
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f)), static_cast<int>(OnePercentY*(BaseY+6.2f)), Text2.c_str(), static_cast<int>(Text2.size()));
		}
	Item = Character.GetActiveEquipment(LEFTHANDSLOT);
	if (Item != -1)
		{
		Text = "";
		Text2 = Character.GetItemDisplayName(Item);
		if (Text2.size() > 65)
			{
			Pos = Text2.find_last_of(" ", 65);
			Text = Text2.substr(0, Pos);
			Text2 = Text2.substr(Pos, string::npos);
			}
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f)), static_cast<int>(OnePercentY*(BaseY+12.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f)), static_cast<int>(OnePercentY*(BaseY+13.2f)), Text2.c_str(), static_cast<int>(Text2.size()));
		}

	SetBkColor(hDC, RGB(255, 255, 255));
	}

//---------------------------------------------------------------------------
void PrintClass::PrintSavingThrows(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ostringstream ss;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 39.0f, 2.0f);
	PrintShaded(hDC, 90.0f, BaseX, BaseY+2.5f, 39.0f, 12.0f);
	for (unsigned int i=0; i<3; i++)
		{
		for (unsigned int j=0; j<6; j++)
			{
			PrintShaded(hDC, 100.0f, (BaseX+9.0f)+j*5.0f, (BaseY+4.7f)+i*3.5f, 3.5f, 2.0f);
			}
		}

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "SAVING THROWS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(230, 230, 230));

	Text = "FORTITUDE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "REFLEX";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WILL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), Text.c_str(), static_cast<int>(Text.size()));
	SelectObject(hDC, PrintFontLabelTiny1);
	Text = "(CONSTITUTION)";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+6.1f)), Text.c_str(), static_cast<int>(Text.size()));
	if (Character.HasFeat("Insightful Reflexes", AtLevel) == true)	
		{
		if (Character.CalculateTotalAbilityMod(INTELLIGENCE, AtLevel) > Character.CalculateTotalAbilityMod(DEXTERITY, AtLevel))
			Text = "(INTELLIGENCE)";
		else
			Text = "(DEXTERITY)";
		}
	else
		Text = "(DEXTERITY)";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+9.7f)), Text.c_str(), static_cast<int>(Text.size()));
	if (Character.HasFeat("Force of Personality", AtLevel) == true)	
		{
		if (Character.CalculateTotalAbilityMod(CHARISMA, AtLevel) > Character.CalculateTotalAbilityMod(WISDOM, AtLevel))
			Text = "(CHARISMA)";
		else
			Text = "(WISDOM)";
		}
	else
		Text = "(WISDOM)";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+13.2f)), Text.c_str(), static_cast<int>(Text.size()));
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	Text = "TOTAL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.5f)), static_cast<int>(OnePercentY*(BaseY+3.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "BASE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.5f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ABILITY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.5f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "FEATS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.5f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ENHANCEMENTS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.5f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ENCHANTED";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.5f)), static_cast<int>(OnePercentY*(BaseY+3.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "SAVE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.5f)), static_cast<int>(OnePercentY*(BaseY+3.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "MODIFIER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.5f)), static_cast<int>(OnePercentY*(BaseY+3.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.5f)), static_cast<int>(OnePercentY*(BaseY+3.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.5f)), static_cast<int>(OnePercentY*(BaseY+3.7f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.5f)), static_cast<int>(OnePercentY*(BaseY+3.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "=";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.25f)), static_cast<int>(OnePercentY*(BaseY+5.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.25f)), static_cast<int>(OnePercentY*(BaseY+8.9f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.25f)), static_cast<int>(OnePercentY*(BaseY+12.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "+";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+18.25f)), static_cast<int>(OnePercentY*(BaseY+5.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+18.25f)), static_cast<int>(OnePercentY*(BaseY+8.9f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+18.25f)), static_cast<int>(OnePercentY*(BaseY+12.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.25f)), static_cast<int>(OnePercentY*(BaseY+5.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.25f)), static_cast<int>(OnePercentY*(BaseY+8.9f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+23.25f)), static_cast<int>(OnePercentY*(BaseY+12.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.25f)), static_cast<int>(OnePercentY*(BaseY+5.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.25f)), static_cast<int>(OnePercentY*(BaseY+8.9f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.25f)), static_cast<int>(OnePercentY*(BaseY+12.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+33.25f)), static_cast<int>(OnePercentY*(BaseY+5.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+33.25f)), static_cast<int>(OnePercentY*(BaseY+8.9f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+33.25f)), static_cast<int>(OnePercentY*(BaseY+12.4f)), Text.c_str(), static_cast<int>(Text.size()));

	//data output
	SelectObject(hDC, PrintFontData);
	SetBkColor(hDC, RGB(255, 255, 255));
	ss.str("");
	ss << Character.GetSaveMod(FORTITUDESAVE, SAVEMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.75f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(REFLEXSAVE, SAVEMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.75f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(WILLSAVE, SAVEMOD_TOTAL, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.75f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(FORTITUDESAVE, SAVEMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.75f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(REFLEXSAVE, SAVEMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.75f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(WILLSAVE, SAVEMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.75f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(FORTITUDESAVE, SAVEMOD_ABILITY, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.75f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(REFLEXSAVE, SAVEMOD_ABILITY, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.75f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(WILLSAVE, SAVEMOD_ABILITY, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.75f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(FORTITUDESAVE, SAVEMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(REFLEXSAVE, SAVEMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(WILLSAVE, SAVEMOD_FEATS, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.75f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(FORTITUDESAVE, SAVEMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.75f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(REFLEXSAVE, SAVEMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.75f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(WILLSAVE, SAVEMOD_ENHANCEMENT, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.75f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(FORTITUDESAVE, SAVEMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.75f)), static_cast<int>(OnePercentY*(BaseY+5.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(REFLEXSAVE, SAVEMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.75f)), static_cast<int>(OnePercentY*(BaseY+8.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetSaveMod(WILLSAVE, SAVEMOD_ENCHANTED, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.75f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));

	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintDefense(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ostringstream ss;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 44.5f, 2.0f);
	PrintShaded(hDC, 90.0f, BaseX, BaseY+2.5f, 44.5f, 18.1f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "DEFENSE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(230, 230, 230));
	SelectObject(hDC, PrintFontLabels);
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);

	Text = "AC";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.85f)), static_cast<int>(OnePercentY*(BaseY+4.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DODGE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.55f)), static_cast<int>(OnePercentY*(BaseY+4.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CONCEALMENT";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+22.25f)), static_cast<int>(OnePercentY*(BaseY+4.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "INCORPOREAL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.95f)), static_cast<int>(OnePercentY*(BaseY+4.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "PRR";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.65f)), static_cast<int>(OnePercentY*(BaseY+4.4f)), Text.c_str(), static_cast<int>(Text.size()));

	SelectObject(hDC, PrintFontLabelTiny1);
	Text = "BASE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.5f)), static_cast<int>(OnePercentY*(BaseY+7.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ARMOR";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+19.5f)), static_cast<int>(OnePercentY*(BaseY+7.4f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+8.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "SHIELD";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+24.5f)), static_cast<int>(OnePercentY*(BaseY+7.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DEXTERITY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+29.5f)), static_cast<int>(OnePercentY*(BaseY+7.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WISDOM";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.5f)), static_cast<int>(OnePercentY*(BaseY+7.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "NATURAL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+7.4f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "SIZE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.5f)), static_cast<int>(OnePercentY*(BaseY+10.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "LUCK";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+19.5f)), static_cast<int>(OnePercentY*(BaseY+10.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DEFLECTION";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+24.5f)), static_cast<int>(OnePercentY*(BaseY+10.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "INSIGHT";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+29.5f)), static_cast<int>(OnePercentY*(BaseY+10.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CENTERED";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.5f)), static_cast<int>(OnePercentY*(BaseY+10.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "MISC";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+10.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "BONUS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+19.5f)), static_cast<int>(OnePercentY*(BaseY+8.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+24.5f)), static_cast<int>(OnePercentY*(BaseY+8.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+19.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+24.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+29.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+39.5f)), static_cast<int>(OnePercentY*(BaseY+11.1f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "MODIFIER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+29.5f)), static_cast<int>(OnePercentY*(BaseY+8.0f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+34.5f)), static_cast<int>(OnePercentY*(BaseY+8.0f)), Text.c_str(), static_cast<int>(Text.size()));

	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);

	Text = "ARMOR WORN";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "SHIELD CARRIED";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+20.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "MAX DEX";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.0f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+28.0f)), static_cast<int>(OnePercentY*(BaseY+20.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "MAX DODGE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+33.0f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+33.0f)), static_cast<int>(OnePercentY*(BaseY+20.0f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ARCANE FAILURE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+38.0f)), static_cast<int>(OnePercentY*(BaseY+15.5f)), Text.c_str(), static_cast<int>(Text.size()));
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+38.0f)), static_cast<int>(OnePercentY*(BaseY+20.0f)), Text.c_str(), static_cast<int>(Text.size()));
	
	//lines
	PrintLine(hDC, EntryLine, BaseX+1.0f, BaseY+4.2f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+9.7f, BaseY+4.2f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+18.4f, BaseY+4.2f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+27.1f, BaseY+4.2f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+35.8f, BaseY+4.2f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+12.5f, BaseY+7.2f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+17.5f, BaseY+7.2f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+22.5f, BaseY+7.2f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+27.5f, BaseY+7.2f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.5f, BaseY+7.2f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+7.2f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+12.5f, BaseY+10.3f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+17.5f, BaseY+10.3f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+22.5f, BaseY+10.3f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+27.5f, BaseY+10.3f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+32.5f, BaseY+10.3f, 4.0f);
	PrintLine(hDC, EntryLine, BaseX+37.5f, BaseY+10.3f, 4.0f);

	//data
	SelectObject(hDC, PrintFontData);
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	ss.str("");
	ss << Character.GetACMod(ACMOD_BASE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.5f)), static_cast<int>(OnePercentY*(BaseY+5.5f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetACMod(ACMOD_SIZE, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.5f)), static_cast<int>(OnePercentY*(BaseY+8.6f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	ss.str("");
	ss << Character.GetACMod(ACMOD_LUCK, AtLevel);
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+19.5f)), static_cast<int>(OnePercentY*(BaseY+8.6f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintRage(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ostringstream ss;
	int RagesPerDay;
	int Duration;
	int StrBonus;
	int ConBonus;
	int WillBonus;
	int ACPenalty;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 18.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "RAGE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));
	SelectObject(hDC, PrintFontLabelTiny1);

	Text = "RAGES/DAY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DURATION";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.0f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "STR/CON BONUS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+7.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WILL SAVE BONUS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.0f)), static_cast<int>(OnePercentY*(BaseY+7.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "AC PENALTY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+10.2f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+4.0f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+4.0f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+7.0f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+7.0f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+10.0f, 7.7f);

	//data
	SelectObject(hDC, PrintFontData);
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	Character.GetRageData(AtLevel, &RagesPerDay, &Duration, &StrBonus, &ConBonus, &WillBonus, &ACPenalty);
	if (RagesPerDay == 0)
		{
		Text = "N/A";
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.85f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.85f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+8.2f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	else
		{
		ss.str("");
		ss << RagesPerDay;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		ss << Duration << " seconds";
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.85f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		ss << StrBonus << " \\ " << ConBonus;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.54f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		ss << WillBonus;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.85f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		ss << ACPenalty;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.54f)), static_cast<int>(OnePercentY*(BaseY+8.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		}
	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintTurnUndead(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ostringstream ss;
	int TurnsPerDay;
	int Check;
	int Damage;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 18.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "TURN UNDEAD";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));
	SelectObject(hDC, PrintFontLabelTiny1);

	Text = "TURNS/DAY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "CHECK";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+10.0f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "DAMAGE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+7.2f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+4.0f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+10.0f, BaseY+4.0f, 7.7f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+7.0f, 7.7f);

	//data
	SelectObject(hDC, PrintFontData);
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	Character.GetTurnData(AtLevel, &TurnsPerDay, &Check, &Damage);
	if (TurnsPerDay == 0)
		{
		Text = "N/A";
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.85f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	else
		{
		ss.str("");
		ss << TurnsPerDay;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		ss << "1D20";
		if (Check > 0)
			ss << " + " << Check;
		else if (Check < 0)
			ss << " - " << -Check;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+13.85f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		ss << "2D6";
		if (Damage > 0)
			ss << " + " << Damage;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+4.55f)), static_cast<int>(OnePercentY*(BaseY+5.2f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		}
	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintItemsWorn(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	int Item;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 39.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "ITEMS WORN";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));
	SelectObject(hDC, PrintFontLabelTiny2);

	Text = "RIGHT HAND";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "LEFT HAND";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+6.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "FACE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+9.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "ARMOR";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+11.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "BRACER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+14.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "RIGHT RING";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+16.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "LEFT RING";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+19.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "HEAD";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+21.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "FEET";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+4.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "NECK";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+6.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "GLOVE";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+9.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "TRINKET";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+11.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "BACK";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+14.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "WAIST";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+16.7f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "AMMO";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+19.2f)), Text.c_str(), static_cast<int>(Text.size()));
	Text = "QUIVER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+21.7f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+4.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+6.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+9.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+11.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+14.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+16.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+19.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+21.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+4.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+6.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+9.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+11.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+14.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+16.5f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+19.0f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+21.5f, 18.0f);

	//data
	SelectObject(hDC, PrintFontDataSmall);
	Item = Character.GetActiveEquipment(RIGHTHANDSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+2.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(LEFTHANDSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+4.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(FACESLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+7.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(ARMORSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(BRACERSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(RIGHTRINGSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+14.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(LEFTRINGSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+17.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(HEADSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+19.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(FEETSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+2.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(NECKSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+4.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(GLOVESSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+7.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(TRINKETSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+9.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(BACKSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+12.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(WAISTSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+14.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(AMMOSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+17.0f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	Item = Character.GetActiveEquipment(QUIVERSLOT);
	if (Item != -1)
		{
		Text = Character.GetItemDisplayName(Item);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+19.5f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	}

//---------------------------------------------------------------------------
void PrintClass::PrintItemsNonWorn(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	string Text2;
	unsigned int Count;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 39.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "OTHER ITEMS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+4.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+6.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+9.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+11.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+14.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+16.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+19.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+21.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+0.7f, BaseY+24.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+4.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+6.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+9.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+11.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+14.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+16.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+19.1f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+21.6f, 18.0f);
	PrintLine(hDC, EntryLine, BaseX+20.0f, BaseY+24.1f, 18.0f);

	//data
	SelectObject(hDC, PrintFontDataSmall);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));
	Count = 0;
	for (unsigned int i=0; i<Character.GetCharacterItemsSize(); i++)
		{
		if (Character.IsItemEquipped(i) == false)
			{
			SplitString(Character.GetItemDisplayName(i), 38, &Text, &Text2);
			if (Count < 9)
				{
				TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+2.1f+2.5*Count)), Text.c_str(), static_cast<int>(Text.size()));
				TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+3.1f+2.5*Count)), Text2.c_str(), static_cast<int>(Text2.size()));
				}
			else
				{
				TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+2.1f+2.5*(Count-9))), Text.c_str(), static_cast<int>(Text.size()));
				TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.0f)), static_cast<int>(OnePercentY*(BaseY+3.1f+2.5*(Count-9))), Text2.c_str(), static_cast<int>(Text2.size()));
				}
			Count++;
			if (Count > 17)
				break;
			}
		}
	}

//---------------------------------------------------------------------------
void PrintClass::PrintSkillsBlock(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ABILITIES KeyAbility;
	ostringstream ss;
	int Ability;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 37.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "SKILLS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));

	SelectObject(hDC, PrintFontLabels);
    Text = "SKILL NAME";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+3.2f)), Text.c_str(), static_cast<int>(Text.size()));
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
    Text = "KEY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.3f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "ABILITY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+15.3f)), static_cast<int>(OnePercentY*(BaseY+3.2f)), Text.c_str(), static_cast<int>(Text.size()));

    Text = "SKILL";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.3f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "MODIFIER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.3f)), static_cast<int>(OnePercentY*(BaseY+3.2f)), Text.c_str(), static_cast<int>(Text.size()));

    Text = "RANKS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.3f)), static_cast<int>(OnePercentY*(BaseY+3.2f)), Text.c_str(), static_cast<int>(Text.size()));

    Text = "ABILITY";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.3f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "MODIFIER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.3f)), static_cast<int>(OnePercentY*(BaseY+3.2f)), Text.c_str(), static_cast<int>(Text.size()));

    Text = "MISC";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.3f)), static_cast<int>(OnePercentY*(BaseY+2.2f)), Text.c_str(), static_cast<int>(Text.size()));
    Text = "MODIFIER";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.3f)), static_cast<int>(OnePercentY*(BaseY+3.2f)), Text.c_str(), static_cast<int>(Text.size()));

	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	SelectObject(hDC, PrintFontLabelBold);
	for (unsigned int i=0; i<NUMSKILLS; i++)
		{
		Data.GetSkillData(i, &Text, &KeyAbility);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f)), static_cast<int>(OnePercentY*(BaseY+4.6f+i*1.9f)), Text.c_str(), static_cast<int>(Text.size()));
		Text = Data.GetAbilityString(KeyAbility, false);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+14.0f)), static_cast<int>(OnePercentY*(BaseY+4.6f+i*1.9f)), Text.c_str(), static_cast<int>(Text.size()));
		}
	SelectObject(hDC, PrintFontLabelTiny1);
	for (unsigned int i=0; i<NUMSKILLS; i++)
		{
	    Text = "=";
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+22.7f)), static_cast<int>(OnePercentY*(BaseY+4.6f+i*1.9f)), Text.c_str(), static_cast<int>(Text.size()));
	    Text = "+";
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+27.7f)), static_cast<int>(OnePercentY*(BaseY+4.6f+i*1.9f)), Text.c_str(), static_cast<int>(Text.size()));
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+32.7f)), static_cast<int>(OnePercentY*(BaseY+4.6f+i*1.9f)), Text.c_str(), static_cast<int>(Text.size()));
		}

	//lines
	for (unsigned int i=0; i<NUMSKILLS; i++)
		{
		PrintLine(hDC, EntryLine, BaseX+18.5f, BaseY+5.7f+i*1.9f, 4.0f);
		PrintLine(hDC, EntryLine, BaseX+23.5f, BaseY+5.7f+i*1.9f, 4.0f);
		PrintLine(hDC, EntryLine, BaseX+28.5f, BaseY+5.7f+i*1.9f, 4.0f);
		PrintLine(hDC, EntryLine, BaseX+33.5f, BaseY+5.7f+i*1.9f, 4.0f);
		}

	//data
	SelectObject(hDC, PrintFontData);
	SetTextAlign(hDC, TA_CENTER | TA_TOP | TA_NOUPDATECP);
	for (unsigned int i=0; i<NUMSKILLS; i++)
		{
		ss.str("");
		//certain skills get an "N/A" if you have spent no points to rank them
		if ((i==DISABLEDEVICE || i==OPENLOCK || i==PERFORM || i==TUMBLE || i==UMD) && Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), AtLevel) == 0)
			ss << "N/A";
		else
			ss << Character.CalculateSkillLevel(static_cast<SKILLS>(i), AtLevel, true);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+20.3f)), static_cast<int>(OnePercentY*(BaseY+4.0f+i*1.9f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
        ss << Character.GetTotalSkillPointsSpent(static_cast<SKILLS>(i), AtLevel);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+25.3f)), static_cast<int>(OnePercentY*(BaseY+4.0f+i*1.9f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
		Data.GetSkillData(i, &Text, &KeyAbility);
        Ability = Character.GetAbility(KeyAbility, AtLevel, true, true, true);
        ss << Data.CalculateAbilityModifier(Ability);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+30.3f)), static_cast<int>(OnePercentY*(BaseY+4.0f+i*1.9f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		ss.str("");
        ss << Character.CalculateSkillMiscMod(static_cast<SKILLS>(i), AtLevel);
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+35.3f)), static_cast<int>(OnePercentY*(BaseY+4.0f+i*1.9f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		}
	SetTextAlign(hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintNotesBlock(HDC hDC, float BaseX, float BaseY)
	{
	string Text;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 18.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "NOTES";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));
	}

//---------------------------------------------------------------------------
void PrintClass::PrintFeatBlock(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	float XLoc;
	float YLoc;
	int Index;
	int FeatIndex;
	FeatDataClass *Feat;
	vector<int> FeatList;
	int LocIndex;
	string ParentHeading;
	string NewParentHeading;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 62.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "FEATS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	XLoc = 0.0f;
	YLoc = 1.5f;
	for (unsigned int j=0; j<4; j++)
		{
		for (unsigned int k=0; k<20; k++)
			{
			PrintLine(hDC, EntryLine, BaseX+2.2f+XLoc, BaseY+2.8f+YLoc, 14.0f);
			YLoc += 1.5f;
			}
		YLoc = 1.5f;
		XLoc += 15.5f;
		}

	//the data
	SelectObject(hDC, PrintFontDataSmall);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));
	Index = 0;
	FeatIndex = Character.GetFeat(AtLevel, Index);
	while (FeatIndex != -1)
		{
		FeatList.push_back(FeatIndex);
		Index++;
		FeatIndex = Character.GetFeat(AtLevel, Index);
		}
    sort(FeatList.begin(), FeatList.end(), FeatSort);
	LocIndex = 0;
	ParentHeading = "";
	for (unsigned int i=0; i<FeatList.size(); i++)
		{
		Feat = Data.GetFeatPointer(FeatList[i]);
		if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
			continue;
		XLoc = 15.5f*(LocIndex/20);
		YLoc = 1.5f*(LocIndex%20) + 1.5f;
		NewParentHeading = Feat->GetFeatParentHeading();
		if (NewParentHeading != "")
			{
			XLoc += 1.0f;
			if (NewParentHeading != ParentHeading)
				{
				ParentHeading = NewParentHeading;
				TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.2f+XLoc)), static_cast<int>(OnePercentY*(BaseY+1.8f+YLoc)), ParentHeading.c_str(), static_cast<int>(ParentHeading.size()));
				LocIndex++;
				XLoc = 15.5f*(LocIndex/20)+1.0f;
				YLoc = 1.5f*(LocIndex%20) + 1.5f;
				}
			}
		Text = Feat->GetFeatName();
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+2.2f+XLoc)), static_cast<int>(OnePercentY*(BaseY+1.8f+YLoc)), Text.c_str(), static_cast<int>(Text.size()));
		LocIndex++;
		}
	}

//---------------------------------------------------------------------------
void PrintClass::PrintEnhancementBlock(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	Character_Enhancements_Class *CharacaterEnhancements;
	Data_Enhancement_Tree_Class *Tree;
	Data_Enhancement_Class* Enhancement;
	int EnhancementIndex;
	ostringstream ss;
	int Column;
	int Row;
	string Text1;
	string Text2;
	int RankToPrint;
	int LevelTaken;

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 98.0f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "ENHANCEMENTS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));

	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));

	SelectObject(hDC, PrintFontLabelBoldSmall);
    Text = "TREE";
	for (unsigned int i=0; i<7; i++)
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+0.7f+i*14.0f)), static_cast<int>(OnePercentY*(BaseY+2.8f)), Text.c_str(), static_cast<int>(Text.size()));

	//lines
	for (unsigned int i=0; i<7; i++)
		PrintLine(hDC, EntryLine, BaseX+0.9f+i*14.0f, BaseY+5.0f, 13.5f);

	//data
	Column = 0;
	CharacaterEnhancements = Character.GetCharacterEnhancementsPointer();
	for (unsigned int i=0; i<7; i++)
		{
		SelectObject(hDC, PrintFontDataSmall);
		if (CharacaterEnhancements->GetRanksTaken(i, 0,0) == 0)
			continue;
		Tree = Data.GetEnhancementTreePointer (CharacaterEnhancements->GetTreeIndex(i));
		ss.str("");
		ss << Tree->GetTreeName();
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f+Column*14.0f)), static_cast<int>(OnePercentY*(BaseY+4.0f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		Row = 0;
		for (unsigned int Level=0; Level<6; Level++)
			{
			for (unsigned int Slot=0; Slot<6; Slot++)
				{
				SelectObject(hDC, PrintFontDataTiny);
				if (Tree->DoesSlotHaveEnhancement (Level, Slot) && CharacaterEnhancements->GetRanksTaken(i, Level, Slot) > 0)
					{
					//figure out what level to show the enhancement at
					RankToPrint = 0;
					for (unsigned int x=0; x<3; x++)
						{
						LevelTaken = CharacaterEnhancements->GetLevelTaken(i, Level, Slot, x);
						if (LevelTaken > 0 && LevelTaken <= AtLevel)
							RankToPrint = x+1;
						}
					if (RankToPrint == 0)
						continue;
					EnhancementIndex = CharacaterEnhancements->GetEnhancementIndex(i, Level, Slot, CharacaterEnhancements->GetEnhancementIndexChosen(i, Level, Slot));
					Enhancement = Tree->GetEnhancementPointer(EnhancementIndex);
					ss.str("");
					ss << Enhancement->GetEnhancementName() << " (Rank " << RankToPrint << ")";
					SplitString(ss.str(), 36, &Text1, &Text2);
					TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f+Column*14.0f)), static_cast<int>(OnePercentY*(BaseY+5.6f+Row*1.3f)), Text1.c_str(), static_cast<int>(Text1.size()));
					if (Text1.size() > 0)
						Row++;
					TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.0f+Column*14.0f)), static_cast<int>(OnePercentY*(BaseY+5.6f+Row*1.3f)), Text2.c_str(), static_cast<int>(Text2.size()));
					Row++;
					}
				}
			}
		Column++;
		}
	}

//---------------------------------------------------------------------------
void PrintClass::PrintSpellBlock(HDC hDC, int AtLevel, float BaseX, float BaseY)
	{
	string Text;
	ostringstream ss;
	unsigned int MaxSpellsByLevel[] = {52, 58, 44, 51, 29, 39, 23, 18, 11};
	float XLoc;
	float YLoc;
	int Spell;
	unsigned int NumSpells;
	int CharLevel;
	CLASS Class;
	int SpellLevel;

	vector <vector<int>>SpellByLevel;
	SpellByLevel.resize(9);

	//header
	SelectObject(hDC, PrintFontLabelBold);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 0, 0));

	PrintShaded(hDC, 0.0f, BaseX, BaseY, 96.5f, 2.0f);

	PrintGraphic(hDC, &Swirl, BaseX+0.5f, BaseY, 2.5f, 1.9f);
    Text = "SPELLS";
	TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+3.5f)), static_cast<int>(OnePercentY*(BaseY+0.5f)), Text.c_str(), static_cast<int>(Text.size()));
	
	//labels
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(230, 230, 230));

	XLoc = 0.0f;
	YLoc = 0.0f;
	PrintShaded(hDC, 90.0f, BaseX, BaseY+2.5f, 96.5f, 60.0f);
	SelectObject(hDC, PrintFontLabels);
	for (unsigned int j=0; j<NUMSPELLLEVELS; j++)
		{
		ss.str("");
		ss << "Level " << j+1;
		TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+1.7f+XLoc)), static_cast<int>(OnePercentY*(BaseY+2.6f)), ss.str().c_str(), static_cast<int>(ss.str().size()));
		YLoc += 1.5f;
		for (unsigned int k=0; k<MaxSpellsByLevel[j]; k++)
			{
			PrintLine(hDC, EntryLine, BaseX+2.2f+XLoc, BaseY+2.8f+YLoc, 9.0f);
			YLoc += 1.0f;
			}
		YLoc = 0.0f;
		XLoc += 10.5f;
		}

	//the data
	NumSpells = Character.GetTotalNumSpells();
	for (unsigned int i=0; i<NumSpells; i++)
		{
		//for each spell in the character's list, get the spell index, what level the character recieved that spell,
		//and what the character class is at that level. From there, we can determine the spell's level.
		Spell = Character.GetKnownSpell(i);
		CharLevel = Character.GetSpellLevelAquired(Spell);
		Class = Character.GetClass(CharLevel, false);
		SpellLevel = Data.GetSpellLevel(Class, Spell);
		//save it
		if (CharLevel <= AtLevel)
			SpellByLevel[SpellLevel-1].push_back(Spell);
		}
	SelectObject(hDC, PrintFontDataTiny);
	//sort the spells alphabetically
	for (unsigned int i=0; i<NUMSPELLLEVELS; i++)
	    sort(SpellByLevel[i].begin(), SpellByLevel[i].end(), SpellSort);
	for (unsigned int i=0; i<NUMSPELLLEVELS; i++)
		{
		XLoc = 10.5f*i;
		YLoc = 0.0f;
		for (unsigned int j=0; j<SpellByLevel[i].size(); j++)
			{
		    Text = Data.GetSpellName(SpellByLevel[i][j]);
			TextOut(hDC, static_cast<int>(OnePercentX*(BaseX+2.3f+XLoc)), static_cast<int>(OnePercentY*(BaseY+3.5f+YLoc)), Text.c_str(), static_cast<int>(Text.size()));
			YLoc += 1.0f;
			}
		}
	}

//---------------------------------------------------------------------------
void PrintClass::PrintLevelGuideLevel(HDC hDC, int AtLevel, int *Column, int *Row)
	{
	#define MAXROWS 50

	int InitialRow;
	int FinalRow;
	int InitialColumn;
	float BaseX, BaseY;
	ostringstream ss;
	int AbilityRaise;
	string Text;
	string LevelFragment;
	string TextFragment;
    string ParentHeading;
    vector <string> UsedParentHeadings;
    int Index;
    int FeatIndex;
    bool AlreadyDone;
    bool DoNormal;
    FEATSLOTTYPE AquireType;
    FeatDataClass *Feat;
	int SpellIndex;
	Character_Enhancements_Class *CharacterEnhancements;
	Data_Enhancement_Tree_Class* Tree;
	Data_Enhancement_Class* Enhancement;
	int EnhancementIndexChosen;
	int EnhancementIndex;
	string FirstName;
	string LastName;

	InitialRow = *Row;
	FinalRow = *Row;
	InitialColumn = *Column;

	BaseX = 5.0f;
	BaseY = 10.0f;

	//put together the string
	ss << "Level " << AtLevel+1 << "\r\n";
	FinalRow++;

	//stuff that is level 1 only
	if (AtLevel == 0)
		{
		Character.GetName(&FirstName, &LastName);
		ss << "Name: " << FirstName << " " << LastName << "\r\n";
		FinalRow++;
		if (Character.GetSex() == MALE)
			ss << "Male ";
	    else
		    ss << "Female ";
		ss << Character.GetRaceString();
		ss << "\r\n";
		FinalRow++;
		ss << "Alignment: " << Data.GetAlignmentString(Character.GetAlignment()) << "\r\n";
		FinalRow++;
		ss << "STR: " << Character.GetAbility(STRENGTH, 1) << "\r\n";
		ss << "DEX: " << Character.GetAbility(DEXTERITY, 1) << "\r\n";
		ss << "CON: " << Character.GetAbility(CONSTITUTION, 1) << "\r\n";
		ss << "INT: " << Character.GetAbility(INTELLIGENCE, 1) << "\r\n";
		ss << "WIS: " << Character.GetAbility(WISDOM, 1) << "\r\n";
		ss << "CHA: " << Character.GetAbility(CHARISMA, 1) << "\r\n";
		FinalRow+=6;
		}

	//class selection
	if (AtLevel < HEROICLEVELS)
		{
		ss << "Class: " << Data.GetClassName(Character.GetClass(AtLevel+1, false)) << "\r\n";
		FinalRow++;
		}

	//ability raises
    AbilityRaise = Character.GetAbilityIncrease(AtLevel+1);
	if (AbilityRaise !=  ABILITYNONE)
		{
		ss << "Ability Raise: ";
        if (AbilityRaise == STRENGTH)
			ss << "Strength +1";
        if (AbilityRaise == DEXTERITY)
            ss << "Dexterity +1";
        if (AbilityRaise == CONSTITUTION)
            ss << "Constitution +1";
        if (AbilityRaise == INTELLIGENCE)
			ss << "Intelligence +1";
        if (AbilityRaise == WISDOM)
            ss << "Wisdom +1";
        if (AbilityRaise == CHARISMA)
            ss << "Charisma +1";
		ss << "\r\n";
		FinalRow++;
		}

    //Skills
    for (unsigned int j=0; j<NUMSKILLS; j++)
        {
        if (Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), AtLevel+1) > 0)
			{
			ss << "Skill: " << Data.GetSkillName(j) << " (+" << Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(j), AtLevel+1) << ")\r\n";
			FinalRow++;
			}
        }

    //feats (selected)
    UsedParentHeadings.clear();
    Index = 0;
    FeatIndex = Character.GetFeat(AtLevel+1, FEATSELECTED, Index);
    while (FeatIndex != -1)
        {
        Feat = Data.GetFeatPointer(FeatIndex);
        ParentHeading = Feat->GetFeatParentHeading();
        AquireType = Character.GetFeatAquireType(FeatIndex, AtLevel+1);
        DoNormal = false;
        if (ParentHeading != "")
            {
            AlreadyDone = false;
            for (unsigned int k=0; k<UsedParentHeadings.size(); k++)
                {
                if (UsedParentHeadings[k] == ParentHeading)
                    AlreadyDone = true;
                }
            if (AlreadyDone == false)
                {
                if (Character.HasAllFeatParentHeadings(ParentHeading, AtLevel+1) == true)
                    {
                    ss << "Feat: ";
                    if (AquireType == FEATCHARACTER)
                        ss << "(Selected) ";
                    if (AquireType == FEATHUMANBONUS)
                        ss << "(Human Bonus) ";
                    if (AquireType == FEATHALFELFBONUS)
                        ss << "(Half-Elf Dilettante) ";
                    if (AquireType == FEATFIGHTERBONUS)
						ss << "(Fighter Bonus) ";
					if (AquireType == FEATWIZARDBONUS)
						ss << "(Wizard Bonus) ";
					if (AquireType == FEATARTIFICERBONUS)
						ss << "(Artificer Bonus) ";
					if (AquireType == FEATRANGERFAVOREDENEMY)
						ss << "(Favored Enemy) ";
					if (AquireType == FEATROGUEBONUS)
						ss << "(Rogue Bonus) ";
					if (AquireType == FEATMONKBONUS)
						ss << "(Monk Bonus) ";
					if (AquireType == FEATMONKPATH)
						ss << "(Monk Path) ";
					if (AquireType == FEATDEITY)
						ss << "(Deity) ";
					if (AquireType == FEATFAVOREDSOULBONUS)
						ss << "(Favored Soul Bonus) ";
                    if (AquireType == FEATDRUIDWILDSHAPE)
                        ss << "(Druid Wild Shape) ";
					if (AquireType == FEATWARLOCKPACT)
						ss << "(Warlock Pact) ";
					if (AquireType == FEATPASTLIFE)
						ss << "(Past Life) ";
					if (AquireType == FEATLEGENDARY)
						ss << "(Legendary) ";
					ss << ParentHeading << " (ALL)\r\n";
                        UsedParentHeadings.push_back(ParentHeading);
					FinalRow++;
                    }
                else
                    DoNormal = true;
				}
            }
        if (ParentHeading == "" || DoNormal == true)
            {
			ss << "Feat: ";
            if (AquireType == FEATCHARACTER)
				ss << "(Selected) ";
            if (AquireType == FEATHUMANBONUS)
                ss << "(Human Bonus) ";
            if (AquireType == FEATHALFELFBONUS)
                ss << "(Half-Elf Dilettante) ";
            if (AquireType == FEATFIGHTERBONUS)
				ss << "(Fighter Bonus) ";
			if (AquireType == FEATWIZARDBONUS)
				ss << "(Wizard Bonus) ";
			if (AquireType == FEATARTIFICERBONUS)
				ss << "(Artificer Bonus) ";
			if (AquireType == FEATRANGERFAVOREDENEMY)
				ss << "(Favored Enemy) ";
			if (AquireType == FEATROGUEBONUS)
				ss << "(Rogue Bonus) ";
			if (AquireType == FEATMONKBONUS)
				ss << "(Monk Bonus) ";
			if (AquireType == FEATMONKPATH)
				ss << "(Monk Path) ";
			if (AquireType == FEATDEITY)
				ss << "(Deity) ";
			if (AquireType == FEATFAVOREDSOULBONUS)
				ss << "(Favored Soul Bonus) ";
            if (AquireType == FEATDRUIDWILDSHAPE)
                ss << "(Druid Wild Shape) ";
			if (AquireType == FEATWARLOCKPACT)
				ss << "(Warlock Pact) ";
			if (AquireType == FEATPASTLIFE)
				ss << "(Past Life) ";
			if (AquireType == FEATLEGENDARY)
				ss << "(Legendary) ";
			ss << Feat->GetFeatName(true) << "\r\n";
			FinalRow++;
            }
        Index++;
        FeatIndex = Character.GetFeat(AtLevel+1, FEATSELECTED, Index);
        }

    //spells
    Index = 0;
    SpellIndex = Character.GetSpellByLevelAquired(AtLevel+1, Index);
    while (SpellIndex != -1)
        {
        if (Character.GetSpellLevelAquired(SpellIndex) == AtLevel+1)
            {
			if (Character.GetSpellAquireType(SpellIndex) == SPELLSELECTED)
				{
				ss << "Spell (" << Data.GetSpellLevel(Character.GetClass(AtLevel+1), SpellIndex) <<"): " << Data.GetSpellName(SpellIndex) << "\r\n";
				FinalRow++;
				}
	        }
        Index++;
        SpellIndex = Character.GetSpellByLevelAquired(AtLevel+1, Index);
        }

	//enhancements
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	for (unsigned int x=0; x<7; x++)
		{
		for (unsigned int j=0; j<6; j++)
			{
			for (unsigned int k=0; k<6; k++)
				{
				for (unsigned int Rank=0; Rank<3; Rank++)
					{
					if (CharacterEnhancements->GetLevelTaken(x, j, k, Rank) == AtLevel+1)
						{
						Tree = Data.GetEnhancementTreePointer(CharacterEnhancements->GetTreeIndex(x));
						ss << "Enhancement: " << Tree->GetTreeName() << " - ";
						EnhancementIndexChosen = CharacterEnhancements->GetEnhancementIndexChosen(x, j, k);
						EnhancementIndex = CharacterEnhancements->GetEnhancementIndex(x, j, k, EnhancementIndexChosen);
						Enhancement = Tree->GetEnhancementPointer(EnhancementIndex);
						ss << Enhancement->GetEnhancementName() << " (Rank " << Rank+1 << ")\r\n";
						FinalRow++;
						}
					}
				}
			}
		}


	//determine if the string fits
	if (FinalRow > MAXROWS)
		{
		FinalRow = FinalRow - InitialRow;
		InitialRow = 0;
		InitialColumn++;
		if (InitialColumn > 1)
			{
			//end the old page and begin a new one
			EndPage(hDC);
			StartPage(hDC);
			PrintHeader(hDC, 0.0f, 0.0f);
			SelectObject(hDC, PrintFontLabels);
			SetTextColor(hDC, RGB(0, 0, 0));
			SetBkColor(hDC, RGB(255, 255, 255));
			InitialColumn = 0;
			}
		}

	//print the level header in bold
	SelectObject(hDC, PrintFontLabelBoldSmall);
	Text = ss.str();
	LevelFragment = Text.substr(0, Text.find("\r\n"));
	TextOut(hDC, static_cast<int>(OnePercentX*(InitialColumn*50.0f+BaseX)), static_cast<int>(OnePercentY*(InitialRow*1.5f+BaseY)), LevelFragment.c_str(), static_cast<int>(LevelFragment.size()));
	SelectObject(hDC, BoldLine);
	PrintLine(hDC, EntryLine, InitialColumn*50.0f+BaseX, InitialRow*1.5f+BaseY+1.1f, 4.0f);
	//save the string in case we need it again
	LevelFragment += " (Cont.)";

	InitialRow++;
	Text = Text.substr(Text.find("\r\n")+2, string::npos);

	//print the string
	SelectObject(hDC, PrintFontDataSmall);
	while (Text.find("\r\n") != string::npos)
		{
		TextFragment = Text.substr(0, Text.find("\r\n"));
		TextOut(hDC, static_cast<int>(OnePercentX*(InitialColumn*50.0f+BaseX)), static_cast<int>(OnePercentY*(InitialRow*1.5f+BaseY)), TextFragment.c_str(), static_cast<int>(TextFragment.size()));
		InitialRow++;
		Text = Text.substr(Text.find("\r\n")+2, string::npos);
		//It is possible for one level to be too large to fit on the page. If so, split it up
		if (InitialRow > MAXROWS)
			{
			InitialRow = 0;
			InitialColumn++;
			if (InitialColumn > 1)
				{
				//end the old page and begin a new one
				EndPage(hDC);
				StartPage(hDC);
				PrintHeader(hDC, 0.0f, 0.0f);
				SelectObject(hDC, PrintFontLabels);
				SetTextColor(hDC, RGB(0, 0, 0));
				SetBkColor(hDC, RGB(255, 255, 255));
				InitialColumn = 0;
				}
			//print the level header in bold
			SelectObject(hDC, PrintFontLabelBoldSmall);
			TextOut(hDC, static_cast<int>(OnePercentX*(InitialColumn*50.0f+BaseX)), static_cast<int>(OnePercentY*(InitialRow*1.5f+BaseY)), LevelFragment.c_str(), static_cast<int>(LevelFragment.size()));
			SelectObject(hDC, BoldLine);
			PrintLine(hDC, EntryLine, InitialColumn*50.0f+BaseX, InitialRow*1.5f+BaseY+1.1f, 8.0f);
			InitialRow++;
			SelectObject(hDC, PrintFontDataSmall);
			}
		}

	SelectObject(hDC, OriginalFont);
	SelectObject(hDC, OriginalPen);

	//return the new values
	FinalRow+=2;
	*Row = FinalRow;
	*Column = InitialColumn;

	}

//---------------------------------------------------------------------------
void PrintClass::PrintGraphic(HDC hDC, GraphicStruct *Bitmap, float Percentx, float Percenty, float PercentWidth, float PercentHeight)
	{
    HDC Graphic;
	BITMAPINFOHEADER bi;
	byte *pBits;
	int x, y;
	int Width, Height;
	HBITMAP OldGraphic;

    Graphic = CreateCompatibleDC(hDC);
    OldGraphic = (HBITMAP)SelectObject(Graphic, Bitmap->Graphic);

	//convert percent to x and y
	x = (int)(Percentx*OnePercentX);
	y = (int)(Percenty*OnePercentY);
	Width = (int)(PercentWidth*OnePercentX);
	Height = (int)(PercentHeight*OnePercentY);

	// Fill the BITMAPINFOHEADER structure
	memset(&bi, 0, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biHeight = Bitmap->Height;
	bi.biWidth = Bitmap->Width;
	bi.biPlanes = 1;
	bi.biBitCount =  24;
	bi.biCompression = BI_RGB;

	// Retrieve the image data
	GetDIBits(Graphic, Bitmap->Graphic, 0, Bitmap->Height, nullptr, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
	pBits = new byte[bi.biSizeImage];
	GetDIBits(Graphic, Bitmap->Graphic, 0, Bitmap->Height, pBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    StretchDIBits(hDC, x, y, Width, Height, 0, 0, Bitmap->Width, Bitmap->Height, pBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS, SRCCOPY);

	delete []pBits;
    SelectObject(Graphic, OldGraphic);
    DeleteDC(Graphic);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintShaded(HDC hDC, float Shade, float Percentx, float Percenty, float PercentWidth, float PercentHeight)
	{
	//Note: The Shade input is expected as a percent of white. So 100.0 would be pure white, 0.0 would be pure black
	//      50.0f would be grey, 20.0 dark grey, 70.0 light grey
    HDC Graphic;
	BITMAPINFOHEADER bi;
	byte pBits[3];
	int x, y;
	int Width, Height;

    Graphic = CreateCompatibleDC(hDC);

	//convert percent to x and y
	x = (int)(Percentx*OnePercentX);
	y = (int)(Percenty*OnePercentY);
	Width = (int)(PercentWidth*OnePercentX);
	Height = (int)(PercentHeight*OnePercentY);

	// Fill the BITMAPINFOHEADER structure
	memset(&bi, 0, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biHeight = 1;
	bi.biWidth = 1;
	bi.biPlanes = 1;
	bi.biBitCount =  24;
	bi.biCompression = BI_RGB;

	for (unsigned int i=0; i<3; i++)
		pBits[i] = (byte)(255.0f*(Shade/100.0f));

    StretchDIBits(hDC, x, y, Width, Height, 0, 0, 1, 1, pBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS, SRCCOPY);
	}

//---------------------------------------------------------------------------
void PrintClass::PrintLine(HDC hDC, HPEN Pen, float Percentx, float Percenty, float PercentLength, bool Verticle)
	{
	HPEN StartPen;

	StartPen = (HPEN)SelectObject(hDC, Pen);
	
	MoveToEx(hDC, static_cast<int>(Percentx*OnePercentX), static_cast<int>(Percenty*OnePercentY), NULL);
	if (Verticle == true)
		LineTo(hDC, static_cast<int>(Percentx*OnePercentX), static_cast<int>((Percenty+PercentLength)*OnePercentY));
	else
		LineTo(hDC, static_cast<int>((Percentx+PercentLength)*OnePercentX), static_cast<int>(Percenty*OnePercentY));

	SelectObject(hDC, StartPen);
	}

//---------------------------------------------------------------------------
void PrintClass::LoadBitmap(string FileName, string Subdirectory, GraphicStruct *Bitmap, COLORREF TransColor, int TransPixelX, int TransPixelY)
    {
    string FullPathFile;
	char OriginalPath[MAX_PATH];
    char OutputString[MAX_PATH];
    BITMAP bm;

	//note: The user may have changed our directory, make sure we are in the correct place
	StringCbCopy(OriginalPath, MAX_PATH, "\0");
    GetCurrentDirectory(MAX_PATH, OriginalPath);
	FullPathFile = InterfaceManager.GetInitialDirectory();
    FullPathFile += "\\Graphics\\";
    if (Subdirectory != "")
        {
        FullPathFile += Subdirectory;
        FullPathFile += "\\";
        }
    FullPathFile += FileName;
    FullPathFile += ".bmp";

	Bitmap->Graphic = (HBITMAP)LoadImage(NULL, FullPathFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (Bitmap->Graphic == NULL)
		{
        GetCurrentDirectory(MAX_PATH, OutputString);
        FullPathFile = OutputString;
        FullPathFile += "\\Graphics\\";
        if (Subdirectory != "")
            {
            FullPathFile += Subdirectory;
            FullPathFile += "\\";
            }
        FullPathFile += "NoImage";
        FullPathFile += ".bmp";
        Bitmap->Graphic = (HBITMAP)LoadImage(NULL, FullPathFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
    GetObject(Bitmap->Graphic, sizeof(bm), &bm);
    Bitmap->Width = bm.bmWidth;
    Bitmap->Height = bm.bmHeight;

	//go back to what the user set
    SetCurrentDirectory(OriginalPath);
    }

//---------------------------------------------------------------------------
void PrintClass::SplitString(string InputString, unsigned int MaxChars, string *OutputString1, string *OutputString2)
	{
	int Pos;

	*OutputString2 = InputString;
	*OutputString1 = "";
	if (OutputString2->size() > MaxChars)
		{
		Pos = OutputString2->find_last_of(" ", MaxChars);
		*OutputString1 = InputString.substr(0, Pos);
		*OutputString2 = InputString.substr(Pos, string::npos);
		if (OutputString2->size() > MaxChars)
			{
			*OutputString2 = OutputString2->substr(0, MaxChars);
			OutputString2[MaxChars-3] = '.';
			OutputString2[MaxChars-2] = '.';
			OutputString2[MaxChars-1] = '.';
			}
		}
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool SpellSort(int F1, int F2)
    {
    return F1 < F2;
    }

//---------------------------------------------------------------------------
bool FeatSort(int F1, int F2)
    {
    return F1 < F2;
    }

