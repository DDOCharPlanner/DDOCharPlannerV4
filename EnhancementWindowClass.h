#pragma once

#include "stdafx.h"
#include "EnhancementWindowBaseClass.h"
#include "Data_Enhancement_Class.h"
#include "Character_Enhancements_Class.h"
#include "Data_Enhancement_Tree_Class.h"

class EnhancementWindowClass : public EnhancementWindowBaseClass
	{
	public:
		EnhancementWindowClass();
		~EnhancementWindowClass();

		void Create(HINSTANCE Instance, HWND Parent);
		void Show(bool State);
		void ActivateEnhancementWindow();
		void SetChildWindowFlag(bool State);

		//The following functions are also used by the MultiEnhancementWindowClass, so we need them public
		unsigned int GetCurrentStartingTree();
		EnhancementWindowClass* GetPointer();
		HWND GetHandle();
		unsigned int GetCurrentTreeSlotsEnhancementIndexSize(int tree, int level, int slot);
		ENHANCEMENT_TREE GetCurrentTreeEnhancementTree(int Tree);
		unsigned int GetCurrentTreeSlotsEnhancementIndex(int Tree, int Level, int Slot, unsigned int Index);
		void MultiEnhancementSelected(int Tree, int Level, int Slot, int Selection);
		EnhancementSlotStruct* GetEnhancementSlotData(int Tree, int Level, int Slot);

		//Functions for handling Window Messages.
		long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		long HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);

	private:
		HWND EnhancementWindowHandle;
		HWND AcceptButton;
		HWND CancelButton;
		HWND ResetAllTreesButton;
		HWND APRemainingLabel;
		HWND APSpentLabel;
		HWND TreeFrame1, TreeFrame2, TreeFrame3;
		HWND TreeAPSpentLabel1, TreeAPSpentLabel2, TreeAPSpentLabel3;
		HWND SelectTreeList;
		HWND ParentWindow;

		HFONT ArielFontSmall;

		HPALETTE Palette;
		GraphicStruct EmptyActiveCore;
		GraphicStruct EmptyPassiveCore;
		GraphicStruct EmptyActiveTree;
		GraphicStruct EmptyPassiveTree;
		GraphicStruct ScrollRight;
		GraphicStruct ScrollLeft;
		GraphicStruct IconActiveAvailable;
		GraphicStruct IconActiveUnavailable;
		GraphicStruct IconPassiveAvailable;
		GraphicStruct IconPassiveUnavailable;
		GraphicStruct SlotActiveNotAllowed;
		GraphicStruct SlotPassiveNotAllowed;
		GraphicStruct ArrowLeft;
		GraphicStruct ArrowRight;
		GraphicStruct ArrowUp1;
		GraphicStruct ArrowUp2;
		GraphicStruct DropDownFrame;
		GraphicStruct CoreEnhancementFrame;
		GraphicStruct ResetTreeButtonOn;
		GraphicStruct ResetTreeButtonOff;
		GraphicStruct BlueLevelBox;
		GraphicStruct GreenLevelBox;
		GraphicStruct RedLevelBox;

		bool MultiEnhancementWindowVisible;

		//These are for handling the placement of Graphics and icons.
		int BackgroundLeft[3];
		int BackgroundTop;
		int BackgroundWidth;
		int BackgroundHeight;
		int SlotCoreLeft[3][6];
		int SlotLeft[3][5];
		int SlotTop[6];
		int SlotWidth;
		int SlotHeight;
		int SlotCoreWidth;
		int SlotCoreHeight;
		int APSpentLeft[3];
		int APSpentTop;
		int TreeChanging;
		int	ToolTipTree;
		int ToolTipLevel;
		int ToolTipSlot;
		int EnhLevelX[30];
		int EnhLevelY[30];
		int EnhLevelWidth;
		int EnhLevelHeight;
		bool FirstTime;
		int TotalAP;
		int TotalAPAvailable;
		int TotalAPSpent;
		vector <CLASS> ClassProgression;
		vector <ENHANCEMENT_TREE> PossibleTrees;

		vector <HWND> SubclassHWNDs;
		vector <WNDPROC> OriginalProcs;

		void ResetEnhancementWindow();
		
		void CalculateAPSpentInTree(int Tree);	//Not used yet.
		bool IsChildWindowVisible();
		void UpdateCurrentTrees(string Direction);
		void UpdateAPAvailableLabel(int NewValue);
		void UpdateAPSpentLabel(int NewValue);
		bool IsSlotSelected(int x, int y, int *rTree, int *rLevel, int *rSlot);
		void Accept();
		bool FindPossibleTree(ENHANCEMENT_TREE EnhancementTree);
		void SaveCharacterEnhancementsNew();
		void SaveCharacterEnhancementsExisting();
		void SetChosenEnhancementsNew();
		void SetChosenEnhancementsExisting();
		void SetPossibleTrees();
		void ResetCurrentTree(int CurrentTree);
		void ResetAllTrees();
		void FillSelectTreeList(int Tree);
		void DrawSelectTreeListItem(HDC hdc, DWORD Item, long Top, long Left);
		void ChangeTree(int TreeIndex);
		void ClearCurrentTreeSlots(int Tree);
		void ClearChosenTreeSlots(int Tree);
		void RemoveSpecialTree(ENHANCEMENT_TREE ENHT_Tree);
		void LoadChosenTreeSlots(int Tree, bool NewLoad);
		void CopyChosenTreeSlots(int DestTree, int TreetoCopy);

		void HandleLeftMouseButtonClick(int x, int y);
		void HandleRightMouseButtonClick(int x, int y);
		void HandleMouseHover(int x, int y);

		void LoadGraphics(HWND Parent);
		void DeleteGraphics();
		void DrawGraphics(HDC hdc);
		void DrawTree(HDC hdc, int tree);
		void DrawLevelBars(HDC hdc);

		//Muli Enhancement Window Functions
		void ActivateMultiWindow(int Tree, int Level, int Slot);
	
		void SubclassChildWindows();
		void DeSubclassChildWindows();
		WNDPROC GetOriginalWinProc(HWND Window);

		//do not implement these two functions, instance  control!!
		EnhancementWindowClass(const EnhancementWindowClass &source);
	    EnhancementWindowClass& operator=(const EnhancementWindowClass &source);
	};
