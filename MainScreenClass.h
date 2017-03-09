//---------------------------------------------------------------------------
#ifndef MainScreenClassH
#define MainScreenClassH

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIComponentManager.h"
#include "IconClass.h"

//---------------------------------------------------------------------------
//struct ParentHeadingStruct
//    {
//    string ParentHeading;
//    bool Collapsed;
//    unsigned int ListIndex;
//    };

struct SpellListSortStruct
    {
    string SpellName;
    int SpellLevel;
    int SpellIndex;
    };

struct EnhancementSortStruct
    {
    string ParentHeading;
    int EnhancementIndex;
    int LevelTaken;
    };

struct ASListItemStruct
	{
	string ParentHeading;
	string ListItemName;
	};

struct SelectedEnhancementStruct
	{
	ENHANCEMENT_TREE TreeIndex;
	int EnhancementIndex;
	int EnhancementRank;
	};

struct SelectedEnhancementSortStruct
	{
	string ParentHeading;
	string EnhancementName;
	int SelectedEnhancementIndex;
	};

//---------------------------------------------------------------------------
class MainScreenClass : public IconClass
    {
    public:
        MainScreenClass();
        virtual ~MainScreenClass();

        void Create(HINSTANCE Instance, HWND Parent, bool UseDefaultFont, string FontName, long FontHeight, long FontWeight, UIComponentManager *UIComponent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        long HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void SetToDefault();
		void SetToRaceAndSex();
		void SetToReincarnation();
		void SetToNameAlignment();
		void SelectKnownPanel(int PanelType);
        unsigned int LoadIcon(ICONTYPE IconType, string Name);
		void ResetItemList();
		void ResetEnhancementList();
		void EnableErrorButton(bool State);
		void ResizeScreen(HWND Wnd);
		void RefreshMainScreen();
		void RefreshInstructionWindow();
		HWND ParentWindow;
		bool UsingSystemFont;
		void DrawSelectFeatControls(InterfaceComponentStruct Component, CHILDWINDOW Window);
		

    private:
		void CheckChildWindows();
		bool SetUp;
        //meta windows
        HWND NameLabel;
        HWND RaceClassLabel;
        HWND LoadButton;
        HWND SaveButton;
        HWND ClearButton;
        HWND PrintButton;
        HWND ForumExportButton;
        HWND AboutButton;
        HWND QuitButton;

        HWND EquipmentScreenButton;
		HWND ItemBuilderButton;
		HWND DisplayErrorsButton;

		//Side Menu
		HWND SideMenuTitle;
		HWND SideRaceSexButton;
		HWND SideClassButton;
		HWND NameAndAlignmentButton;
		HWND SideReincarnationButton;
		HWND SideAbilityButton;
		HWND SideSkillButton;
		HWND SideSpellButton;
		HWND SideFeatsButton;
		HWND SideDestinyButton;
		HWND SideEnhancementButton;

        //the ability box
        HWND AbilityBoxFrame;
        HWND AbilityLabel;
        HWND AbilityModifierLabel;
        HWND StrLabel;
        HWND DexLabel;
        HWND ConLabel;
        HWND IntLabel;
        HWND WisLabel;
        HWND ChaLabel;
        HWND StrLabel2;
        HWND DexLabel2;
        HWND ConLabel2;
        HWND IntLabel2;
        HWND WisLabel2;
        HWND ChaLabel2;
        HWND StrNumber;
        HWND DexNumber;
        HWND ConNumber;
        HWND IntNumber;
        HWND WisNumber;
        HWND ChaNumber;
        HWND StrModifier;
        HWND DexModifier;
        HWND ConModifier;
        HWND IntModifier;
        HWND WisModifier;
        HWND ChaModifier;
        //the ability stats box
        HWND AbilityStatBoxFrame;
        HWND AbilityStatBox;

        //the skills box
        HWND SkillBoxFrame;
        HWND SkillTitle;
        HWND KeyAbilityTitle;
        HWND TotalModTitle;
        HWND AbilityModTitle;
        HWND MiscModTitle;
        HWND SkillsList;
		//the instruction list box
		HWND InstructionWindowFrame;
		HWND InstructionWindowTitle;
		HWND InstructionWindowList;
		//Known Panel Box
		HWND DestinyPanelButton;
		HWND FeatsPanelButton;
		HWND SpellsPanelButton;
		HWND EnhPanelButton;
        //the feat box
        HWND FeatBoxFrame;
        HWND FeatListTitle;
        HWND FeatList;
		//the spell box
		HWND SpellBoxFrame;
		HWND SpellBoxTitle;
		HWND SpellList;
		//the Destiny box
		HWND DestinyBoxFrame;
		HWND DestinyBoxTitle;
		HWND DestinyList;
		//the enhancement box
		HWND EnhancementBoxFrame;

		HWND EnhancementTitle;
		HWND EnhancementList;
        //the advancement box
        HWND AdvancementWindowFrame;
        HWND AdvWinBonusAbilityPointsCheckBox;
        HWND AdvWinFeatList;
        HWND AdvWinFirstNameInput;
        HWND AdvWinSurnameInput;
        HWND AdvSkillPointSpendBox;
        HWND AdvWinSpellList;
		HWND AdvWinSpellClearButton;
		HWND HeroicClassRadioButton;
		HWND IconicClassRadioButton;
		HWND HeroicLevelRadioButton;
		HWND IconicLevelRadioButton;
		HWND HeroicPastRadioButton;
		HWND IconicPastRadioButton;
		HWND EpicPastRadioButton;
		int PastLifeRadioState;
        //the description box
        HWND DescriptionWindow;
        //equipment selection boxes
        HWND EquipmentDisplayTitle;
        HWND EquipmentDisplaySelectList;
		//Additional stat box
		HWND AdditionalStatsTitle;
		HWND AdditionalStatsList;
        
        HPALETTE Palette;
        HFONT ArielFontSmall;
        HFONT AbilityFontLarge;
        HFONT AbilityFontSmall;
        HFONT DefaultFont;
        HPEN HighlightPen;
		GraphicStruct PlusBox;
		GraphicStruct MinusBox;
		vector <ParentHeadingStruct> FeatListParentHeading;
        GraphicStruct LeftArrow;
        GraphicStruct RightArrow;
        GraphicStruct EmptyFeatSlot;
        GraphicStruct EmptySpellSlot;
        GraphicStruct MaleHumanOn;
        GraphicStruct MaleHumanOff;
        GraphicStruct FemaleHumanOn;
        GraphicStruct FemaleHumanOff;
        GraphicStruct MaleElfOn;
        GraphicStruct MaleElfOff;
        GraphicStruct FemaleElfOn;
        GraphicStruct FemaleElfOff;
        GraphicStruct MaleDwarfOn;
        GraphicStruct MaleDwarfOff;
        GraphicStruct FemaleDwarfOn;
        GraphicStruct FemaleDwarfOff;
        GraphicStruct MaleHalflingOn;
        GraphicStruct MaleHalflingOff;
        GraphicStruct FemaleHalflingOn;
        GraphicStruct FemaleHalflingOff;
        GraphicStruct MaleWarforgedOn;
        GraphicStruct MaleWarforgedOff;
        GraphicStruct FemaleWarforgedOn;
        GraphicStruct FemaleWarforgedOff;
		GraphicStruct MaleHalfelfOn;
		GraphicStruct MaleHalfelfOff;
		GraphicStruct FemaleHalfelfOn;
		GraphicStruct FemaleHalfelfOff;
		GraphicStruct MaleHalforcOn;
		GraphicStruct MaleHalforcOff;
		GraphicStruct FemaleHalforcOn;
		GraphicStruct FemaleHalforcOff;
        GraphicStruct MaleDrowOn;
        GraphicStruct MaleDrowOff;
        GraphicStruct FemaleDrowOn;
        GraphicStruct FemaleDrowOff;
		GraphicStruct MaleBladeforgedOn;
		GraphicStruct MaleBladeforgedOff;
		GraphicStruct FemaleBladeforgedOn;
		GraphicStruct FemaleBladeforgedOff;
		GraphicStruct MaleMorninglordOn;
		GraphicStruct MaleMorninglordOff;
		GraphicStruct FemaleMorninglordOn;
		GraphicStruct FemaleMorninglordOff;
		GraphicStruct MalePurpleDragonKnightOn;
		GraphicStruct MalePurpleDragonKnightOff;
		GraphicStruct FemalePurpleDragonKnightOn;
		GraphicStruct FemalePurpleDragonKnightOff;
		GraphicStruct MaleShadarKaiOn;
		GraphicStruct MaleShadarKaiOff;
		GraphicStruct FemaleShadarKaiOn;
		GraphicStruct FemaleShadarKaiOff;
		GraphicStruct MaleGnomeOn;
		GraphicStruct MaleGnomeOff;
		GraphicStruct FemaleGnomeOn;
		GraphicStruct FemaleGnomeOff;
		GraphicStruct MaleDeepGnomeOn;
		GraphicStruct MaleDeepGnomeOff;
		GraphicStruct FemaleDeepGnomeOn;
		GraphicStruct FemaleDeepGnomeOff;
		GraphicStruct MaleDragonbornOn;
		GraphicStruct MaleDragonbornOff;
		GraphicStruct FemaleDragonbornOn;
		GraphicStruct FemaleDragonbornOff;
		GraphicStruct MaleOn;
		GraphicStruct FemaleOn;
        GraphicStruct MaleOff;
        GraphicStruct FemaleOff;
        GraphicStruct BlueLevelBox;
        GraphicStruct GreenLevelBox;
        GraphicStruct RedLevelBox;
		GraphicStruct ClassIcon[NUMCLASSES];
		GraphicStruct IconicPastLifeIcon[ICONICPASTLIFEFEAT];
		GraphicStruct EpicPastLifeIcon[EPICPASTLIFESPHERE][2];
        GraphicStruct EquipmentScreen;
        GraphicStruct EquipmentSlotHighlight;
		GraphicStruct NoImage;
        vector <GraphicStruct> SkillIcon;
        vector <GraphicStruct> FeatIcon;
		vector <GraphicStruct> SpellIcon;
        unsigned int CurrentSelectedLevel;
        unsigned int CurrentInstructionSelection;
        unsigned int MaxInstructionSelection;
        bool Dragging;
        int IconDrag;
        HCURSOR Cursor;
        ALIGNMENT AlignmentSlot[6];
        CLASS ClassSlot[NUMCLASSES];
        FEATSLOTTYPE FeatSlot[3];
        vector <HWND> SubclassHWNDs;
        vector <WNDPROC> OriginalProcs;

        vector <ParentHeadingStruct> FeatListSelectParentHeading;
        vector <ParentHeadingStruct> SpellListParentHeading;
        vector <ParentHeadingStruct> SpellListSelectParentHeading;
        bool EquipmentScreenShown;
        EQUIPMENTSLOTTYPE EquipmentScreenCurrentSelectedSlot;
		vector <ParentHeadingStruct> ASListParentHeading;
		vector <ASListItemStruct> ASListItems;
		RichEditBitmapClass RichEditBitmap;
		string FontName;
		long FontHeight;
		long FontWeight;
		HDC hdcMem;
        HBITMAP hbmMem;
		//Used for Enhancement ListBox
		vector <SelectedEnhancementStruct> SelectedEnhancements;
		vector <ParentHeadingStruct> SelectedEnhancementsParentHeading;
		enum PanelType{Feats,Enh,Spells,Destiny};
        void SubclassChildWindows();
        void DesubclassChildWindows();
		void UpdateMetaWindows();
		void ChangeInstructionWindowSelection(int NewInstructionIndex);
        void FillAbilityBox();
        void FillAbilityStatBox();
        void DrawAbilityStatBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
        void FillSpellBox();
        void DrawSpellBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
        void FillSkillBox();
        void DrawSkillBoxItem(HDC hDC, DWORD Item, long top, long left);
        void FillFeatBox();
        void DrawFeatBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
        void FillFeatSelectBox();
        void DrawFeatSelectBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
        void FillSkillSpendBox();
        void DrawSkillSpendBoxItem(HDC hDC, DWORD Item, long top, long left);
        void FillSpellSelectBox();
        void DrawSpellSelectBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
        void FillEquipmentDisplaySelectBox();
        void DrawEquipmentDisplaySelectBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillAdditionalStatsBox();
		void DrawAdditionalStatsBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);
        void FillInstructionBox();
        void FillDescriptionBox(string Description, HBITMAP Bitmap = NULL);
        void LoadGraphics(HWND Parent);
        void DeleteGraphics();
        void DrawGraphics(HWND hWnd, LPPAINTSTRUCT lpPS);
		void DrawItems(HWND hWnd, LPPAINTSTRUCT lpPS, WPARAM wParam, LPARAM lParam);
        void DrawLevelBars(HDC hdc);
        void ClearAdvancementBox();
		void ClearKnownBox();
		void DrawAdvancementBoxGraphics(HDC hdc);
        void HandleLeftMouseButtonClick(int x, int y);
        void HandleLeftMouseButtonClickAdvancementBox(int x, int y);
        WNDPROC GetOriginalWinProc(HWND Window);
        void EndDragAndDropOperation(int x, int y);
        void ToggleEquipmentScreen();
        void ChangeEquipmentSelectType();
        void ChangeCurrentActiveEquipment(unsigned int NewItem);
        string ConvertOrdinalNumberToRoman(int Number);
        string ConvertOrdinalNumberToCardinal(int Number);
		void LoadASListItems();
		void HandleLeftMouseButtonClickAdvancementBoxTrueReincarnation(int x, int y);
		void ResizeWindow(string WindowName, HWND WindowID, int cx, int cy, UIComponentManager *UIComponent);
		void FitContent(string ContentWindowName, string DestWindowName, HWND DestWindowID, int cx, int cy, UIComponentManager *UIComponent, int OffsetLeft, int OffsetRight, int OffsetTop, int OffsetBottom);
		string CreateSpellDescription(unsigned int SpellIndex);
		void UpdateSelectedEnhancements();
		void FillEnhancementBox();
		void DrawEnhancementBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left);


        //do not implement these two functions, instance  control!!
        MainScreenClass(const MainScreenClass &source);
        MainScreenClass& operator=(const MainScreenClass &source);
    };

extern DWORD CALLBACK EditStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb);
extern long CALLBACK SubclassWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern bool SpellCompare(SpellListSortStruct S1, SpellListSortStruct S2);
extern bool EnhancementCompareName(EnhancementSortStruct E1, EnhancementSortStruct E2);
extern bool EnhancementCompareLevel(EnhancementSortStruct E1, EnhancementSortStruct E2);
extern bool SelectedEnhancementCompareName(SelectedEnhancementSortStruct E1, SelectedEnhancementSortStruct E2);

    
#endif
 