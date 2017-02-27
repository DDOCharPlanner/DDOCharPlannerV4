#pragma once

#include "stdafx.h"

class PrintClass
	{
	public:
		PrintClass();
		virtual ~PrintClass();

		void Print(HDC PrinterDC, int AtLevelSnapshot, int AtLevelGuideMin, int AtLevelGuideMax, bool SnapShot, bool LevelGuide);

	private:
		DOCINFO DocInfo;
		int LogPelsX;
		int LogPelsY;
		float OnePercentX;
		float OnePercentY;
		HPEN EntryLine;
		HPEN BoldLine;
		HPEN OriginalPen;
		HFONT PrintFontLabels;
		HFONT PrintFontLarge;
		HFONT PrintFontLabelBold;
		HFONT PrintFontLabelBoldSmall;
		HFONT PrintFontLabelTiny1;
		HFONT PrintFontLabelTiny2;
		HFONT PrintFontData;
		HFONT PrintFontDataSmall;
		HFONT PrintFontDataTiny;
		HFONT OriginalFont;
        GraphicStruct Logo;
		GraphicStruct Swirl;


		void PrintSnapshot(HDC PrinterDC, int AtLevel);
		void PrintLevelGuide(HDC PrinterDC, int AtLevelMin, int AtLevelMax);
		void PrintLevelGuideLevel(HDC hDC, int AtLevel, int *Column, int *Row);
		bool PrintSetup(HDC hDC);
		void PrintCleanup(HDC hDC);

		//sections to print (snapshot)
		void PrintHeader(HDC hDC, float BaseX, float BaseY);
		void PrintClassBlock(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintAbilityScoresBlock(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintOffense(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintSavingThrows(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintDefense(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintRage(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintTurnUndead(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintItemsWorn(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintItemsNonWorn(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintSkillsBlock(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintNotesBlock(HDC hDC, float BaseX, float BaseY);
		void PrintFeatBlock(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintEnhancementBlock(HDC hDC, int AtLevel, float BaseX, float BaseY);
		void PrintSpellBlock(HDC hDC, int AtLevel, float BaseX, float BaseY);

		//utility routines
		void PrintGraphic(HDC hDC, GraphicStruct *Bitmap, float Percentx, float Percenty, float PercentWidth, float PercentHeight);
        void PrintShaded(HDC hDC, float Shade, float Percentx, float Percenty, float PercentWidth, float PercentHeight);
		void PrintLine(HDC hDC, HPEN Pen, float Percentx, float Percenty, float PercentLength, bool Verticle = false);
        void LoadBitmap(string FileName, string Subdirectory, GraphicStruct *Bitmap, COLORREF TransColor = NULL, int TransPixelX = 0, int TransPixelY = 0);
		void SplitString(string InputString, unsigned int MaxChars, string *OutputString1, string *OutputString2);
	};

extern bool SpellSort(int F1, int F2);
extern bool FeatSort(int F1, int F2);
