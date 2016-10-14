//---------------------------------------------------------------------------
#ifndef ItemBuilderClassH
#define ItemBuilderClassH

#include "stdafx.h"
#include "IconClass.h"

//---------------------------------------------------------------------------
class ItemBuilderClass : public IconClass
    {
    public:
        ItemBuilderClass();
        virtual ~ItemBuilderClass();

        void Create(HINSTANCE Instance, HWND Parent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        long HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void ActivateItemBuilderWindow();

    private:
		//Window, Controls and Graphics
        HWND ItemBuilderWindowHandle;
		HWND CloseButton;
		HWND AddButton;
		HWND RemoveButton;
		HWND TitleLabel;

		HWND SlotTypeFrame;
		HWND SlotTypeLabel;

		HWND CurrentItemsLabel;
		HWND CurrentItemsList;
		HWND CurrentItemsFrame;

		HWND BuildTypeFrame;
		HWND BuildTypeLabel;
		HWND GenericSelectBox;
		HWND NamedSelectBox;
		HWND GreenSteelSelectBox;
		HWND DragontouchedSelectBox;
		HWND ShavarathRingSelectBox;
		HWND EpicSelectBox;

		HWND BaseTypeFrame;
		HWND BaseTypeLabel;
		HWND BaseTypeList;

		HWND BonusEffectFrame;
		HWND BonusEffectLabel;
		HWND BonusEffectList;

		HWND PrefixEffectFrame;
		HWND PrefixEffectLabel;
		HWND PrefixEffectList;

		HWND MaterialEffectFrame;
		HWND MaterialEffectLabel;
		HWND MaterialEffectList;

		HWND SuffixEffectFrame;
		HWND SuffixEffectLabel;
		HWND SuffixEffectList;

		HWND EldritchEffectFrame;
		HWND EldritchEffectLabel;
		HWND EldritchEffectList;

		HWND GSInvasionElementFrame;
		HWND GSInvasionElementLabel;
		HWND GSInvasionElementList;
		HWND GSInvasionEffectFrame;
		HWND GSInvasionEffectLabel;
		HWND GSInvasionEffectList;
		HWND GSSubjugationElementFrame;
		HWND GSSubjugationElementLabel;
		HWND GSSubjugationElementList;
		HWND GSSubjugationEffectFrame;
		HWND GSSubjugationEffectLabel;
		HWND GSSubjugationEffectList;
		HWND GSDevastationElementFrame;
		HWND GSDevastationElementLabel;
		HWND GSDevastationElementList;
		HWND GSDevastationEffectFrame;
		HWND GSDevastationEffectLabel;
		HWND GSDevastationEffectList;

		HWND DTEldritchEffectFrame;
		HWND DTEldritchEffectLabel;
		HWND DTEldritchEffectList;
		HWND DTTempestEffectFrame;
		HWND DTTempestEffectLabel;
		HWND DTTempestEffectList;
		HWND DTSovereignEffectFrame;
		HWND DTSovereignEffectLabel;
		HWND DTSovereignEffectList;

		HWND ShavarathElementFrame;
		HWND ShavarathElementLabel;
		HWND ShavarathElementList;
		HWND ShavarathEffectFrame;
		HWND ShavarathEffectLabel;
		HWND ShavarathEffectList;

		HWND EpicFirstEffectFrame;
		HWND EpicFirstEffectLabel;
		HWND EpicFirstEffectList;
		HWND EpicSecondEffectFrame;
		HWND EpicSecondEffectLabel;
		HWND EpicSecondEffectList;
		
		HWND CurrentDescriptionWindow;
		HWND BuildDescriptionWindow;
   
        HPALETTE Palette;
        GraphicStruct CharacterDollPanel;
        GraphicStruct CharacterDollPanelHighlight;

		// Variables to hold Data
		EQUIPMENTSLOTTYPE CharacterDollPanelCurrentSelectedSlot;
		vector <CharacterItemStruct> CurrentItems;
		int ItemCurrentlySelected;
		int BaseTypeCurrentlySelected;
		int BonusEffectCurrentlySelected;
		int PrefixEffectCurrentlySelected;
		int MaterialEffectCurrentlySelected;
		int SuffixEffectCurrentlySelected;
		int EldritchEffectCurrentlySelected;
		int GSInvasionElementCurrentlySelected;
		int GSInvasionEffectCurrentlySelected;
		int GSSubjugationElementCurrentlySelected;
		int GSSubjugationEffectCurrentlySelected;
		int GSDevastationElementCurrentlySelected;
		int GSDevastationEffectCurrentlySelected;
		int DTEldritchEffectCurrentlySelected;
		int DTTempestEffectCurrentlySelected;
		int DTSovereignEffectCurrentlySelected;
		int ShavarathElementCurrentlySelected;
		int ShavarathEffectCurrentlySelected;
		int EpicFirstEffectCurrentlySelected;
		int EpicSecondEffectCurrentlySelected;

        vector <HWND> SubclassHWNDs;
        vector <WNDPROC> OriginalProcs;

		// Functions for controlling the windows and graphics
		void SubclassChildWindows();
        void DesubclassChildWindows();
        WNDPROC GetOriginalWinProc(HWND Window);
		
		void ShowEffectWindows(string strBuildType);

        void LoadGraphics(HWND Parent);
        void DeleteGraphics();
        void DrawGraphics(HDC hdc);
        void HandleLeftMouseButtonClick(int x, int y);
		void ChangeSlotTypeSelection();
		void ChangeItemCurrentlySelected(unsigned int NewItem);
		void ChangeBaseTypeCurrentlySelected(unsigned int NewItem);
		void ChangeBuildTypeSelection(unsigned int NewItem);
		void ChangeBonusEffectCurrentlySelected(unsigned int NewItem);
		void ChangePrefixEffectCurrentlySelected(unsigned int NewItem);
		void ChangeMaterialEffectCurrentlySelected(unsigned int NewItem);
		void ChangeSuffixEffectCurrentlySelected(unsigned int NewItem);
		void ChangeEldritchEffectCurrentlySelected(unsigned int NewItem);
		void ChangeGSInvasionElementCurrentlySelected(unsigned int NewItem);
		void ChangeGSInvasionEffectCurrentlySelected(unsigned int NewItem);
		void ChangeGSSubjugationElementCurrentlySelected(unsigned int NewItem);
		void ChangeGSSubjugationEffectCurrentlySelected(unsigned int NewItem);
		void ChangeGSDevastationElementCurrentlySelected(unsigned int NewItem);
		void ChangeGSDevastationEffectCurrentlySelected(unsigned int NewItem);
		void ChangeDTEldritchEffectCurrentlySelected(unsigned int NewItem);
		void ChangeDTTempestEffectCurrentlySelected(unsigned int NewItem);
		void ChangeDTSovereignEffectCurrentlySelected(unsigned int NewItem);
		void ChangeShavarathElementCurrentlySelected(unsigned int NewItem);
		void ChangeShavarathEffectCurrentlySelected(unsigned int NewItem);
		void ChangeEpicFirstEffectCurrentlySelected(unsigned int NewItem);
		void ChangeEpicSecondEffectCurrentlySelected(unsigned int NewItem);

		void GetCurrentItemsData();
		void FillCurrentItemsBox();
		void DrawCurrentItemsBoxItem(HDC hDC, DWORD Item, long top, long left);

		string GetItemDisplayName(unsigned int Item);
		string GetItemFlavorText(int ItemIndex);
		bool DoesItemFitSelectedSlot(unsigned int Item);
		
		string GetItemName(unsigned int Item);
		void FillBaseTypesBox();
		void DrawBaseTypesBoxItem(HDC hDC, DWORD Item, long top, long left);
		
		string GetEffectName(unsigned int Item);
		void FillBonusEffectBox();
		void DrawBonusEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillPrefixEffectBox();
		void DrawPrefixEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillMaterialEffectBox();
		void DrawMaterialEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillSuffixEffectBox();
		void DrawSuffixEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillEldritchEffectBox();
		void DrawEldritchEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillGSInvasionElementBox();
		void DrawGSInvasionElementBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillGSInvasionEffectBox();
		void DrawGSInvasionEffectBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillGSSubjugationElementBox();
		void DrawGSSubjugationElementBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillGSSubjugationEffectBox();
		void DrawGSSubjugationEffectBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillGSDevastationElementBox();
		void DrawGSDevastationElementBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillGSDevastationEffectBox();
		void DrawGSDevastationEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillDTEldritchEffectBox();
		void DrawDTEldritchEffectBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillDTTempestEffectBox();
		void DrawDTTempestEffectBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillDTSovereignEffectBox();
		void DrawDTSovereignEffectBoxItem(HDC hDC, DWORD Item, long top, long left);
		
		void FillShavarathElementBox();
		void DrawShavarathElementBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillShavarathEffectBox();
		void DrawShavarathEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillEpicFirstEffectBox();
		void DrawEpicFirstEffectBoxItem(HDC hDC, DWORD Item, long top, long left);
		void FillEpicSecondEffectBox();
		void DrawEpicSecondEffectBoxItem(HDC hDC, DWORD Item, long top, long left);

		void FillDescriptionBox(string DescriptionBox);
		string GetItemStaticEffectsDescription(int ItemIndex);
		string GetFullItemDescription(int CurrentItem);
		string GetEffectDescription(unsigned int EffectIndex);
		string GetItemChosenEffectsDescription(int CurrentItem);
		string GetBuildDisplayName();
		void SetAllEffectVariablesToZero();
		string GetBuildEffectNameAndDescription(int EffectIndex);
		void SendCurrentItemsData();
		void AddBuildItem();
		void RemoveCurrentItem();

        //do not implement these two functions, instance  control!!
        ItemBuilderClass(const ItemBuilderClass &source);
        ItemBuilderClass& operator=(const ItemBuilderClass &source);
    };

extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);

#endif
 