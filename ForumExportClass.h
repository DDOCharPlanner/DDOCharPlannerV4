//---------------------------------------------------------------------------
#ifndef ForumExportClassH
#define ForumExportClassH

#include "stdafx.h"
//---------------------------------------------------------------------------
class ForumExportClass
    {
    public:
        ForumExportClass();
        virtual ~ForumExportClass();

        void Create(HINSTANCE Instance, HWND Parent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void SetForumExportLevel(int NewLevel);

    private:
        HWND ForumExportWindowHandle;
        HWND LevelSelectLabel;
        HWND LevelSelect;
        HWND CloseButton;
        HWND CopyButton;
        HWND PresetsLabel;
        HWND Preset1;
        HWND Preset2;
        HWND ExampleOutputBox;
        HWND HeaderLabel;
        HWND NameCheckBox;
        HWND AbilityLabel;
        HWND StartingAbilityCheckBox;
        HWND EndingAbilityCheckBox;
        HWND ModifiedAbilityCheckBox;
        HWND SkillsLabel;
        HWND StartingSkillsCheckBox;
        HWND EndingSkillsCheckBox;
        HWND ModifiedSkillsCheckBox;
        HWND NotableEquipmentCheckBox;
        HWND LevelBreakdownLabel;
        HWND AbilityRaiseCheckBox;
        HWND SkillsListCheckBox;
        HWND FeatSelectedCheckBox;
        HWND FeatAutoCheckBox;
        HWND SpellsListCheckBox;
		HWND EnhancementsListCheckBox;
		HWND ForumBackgroundLabel;
		HWND ForumBackgroundDarkRadioButton;
		HWND ForumBackgroundLightRadioButton;
		HWND TemplateSelectionLabel;
		HWND TemplateSelectionBox;
		HWND TemplateDesignButton;
		int AtLevel;
		string ForumExportColor[6];

        void FillExampleExportBox();
        string FillExampleExportBoxHeader();
        string FillExampleExportBoxTitle();
        string FillExampleExportBoxAbilities();
        string FillExampleExportBoxSkills();
        string FillExampleExportBoxNotableEquipment();
        string FillExampleExportBoxLevelBreakdown();
		void HandleCharacterForumExport();
		void SetForumExportColors();
		string FillExportHeader();
        string FillExportTitle();
        string FillExportAbilities();
        string FillExportSkills();
        string FillExportNotableEquipment();
        string FillExportLevelBreakdown();
        string ConvertOrdinalNumberToRoman(int Number);

        //do not implement these two functions, instance  control!!
        ForumExportClass(const ForumExportClass &source);
        ForumExportClass& operator=(const ForumExportClass &source);
    };

extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern DWORD CALLBACK ExportExampleStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb);
#endif
