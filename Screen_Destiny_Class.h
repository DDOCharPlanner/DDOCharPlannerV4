#pragma once

#include "stdafx.h"
#include "Screen_Destiny_Base_Class.h"

struct GraphicPlacement
	{
	int Left;
	int Top;
	int Width;
	int Height;
	};

struct DestinySortStruct
	{
	string DestinyTreeName;
	int DestinyLevel;
	DESTINY_TREE DestinyTreeIndex;
	};

struct DestinyRankStruct
	{
	int DestinyRank;
	int DestinyLevel;
	int RankXP;
	int TotalAP;
	};

class Screen_Destiny_Class : public Screen_Destiny_Base_Class
	{
	public:
		Screen_Destiny_Class();
		~Screen_Destiny_Class();

		void Create(HINSTANCE Instance, HWND Parent);
		void Show(bool State);
		void ActivateDestinyWindow(int Level);

		//functions for handling Window messages
		long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		long HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		
		HWND GetHandle();
		HWND DestinyWindowHandle;

	private:
		HFONT ArielFontSmall;
		HFONT ArielFontNormal;

		
		HWND DestiniesLabelHandle;
		HWND DestiniesFrameHandle;
		HWND DestiniesListHandle;
		HWND EnforceLevelCheckBoxHandle;
		HWND EnforceDestinyProgressCheckBoxHandle;
		HWND AbilitiesLabelHandle;
		HWND AbilitiesFrameHandle;
		HWND AbilitiesListHandle;
		HWND ShowAllCheckBoxHandle;
		HWND TwistsofFateLabelHandle;
		HWND TwistsofFateFrameHandle;
		HWND AcceptButtonHandle;
		HWND CancelButtonHandle;
		
		HPALETTE Palette;
		GraphicStruct CoreSlotBackgroundActive;
		GraphicStruct CoreSlotBackgroundPassive;
		GraphicStruct TreeSlotBackgroundActive;
		GraphicStruct TreeSlotBackgroundPassive;
		GraphicStruct SlotBorderAvailableActive;
		GraphicStruct SlotBorderAvailablePassive;
		GraphicStruct SlotBorderNotAvailableActive;
		GraphicStruct SlotBorderNotAvailablePassive;
		GraphicStruct SlotBorderNotAllowedActive;
		GraphicStruct SlotBorderNotAllowedPassive;
		GraphicStruct ArrowLeft;
		GraphicStruct ArrowRight;
		GraphicStruct ArrowUp1;
		GraphicStruct ArrowUp2;
		GraphicStruct CoreDestinyFrame;
		GraphicStruct ResetTreeOn;
		GraphicStruct ResetTreeOff;
		GraphicStruct LevelArrowLeft;
		GraphicStruct LevelArrowRight;
		GraphicStruct ColorBarArcane;
		GraphicStruct ColorBarDivine;
		GraphicStruct ColorBarMartial;
		GraphicStruct ColorBarPrimal;
		GraphicStruct ColorBarArcaneSelected;
		GraphicStruct ColorBarDivineSelected;
		GraphicStruct ColorBarMartialSelected;
		GraphicStruct ColorBarPrimalSelected;
		GraphicStruct DestinyIconRingAvailable;
		GraphicStruct DestinyIconRingNotClaimed;
		GraphicStruct DestinyIconRingSelected;
		GraphicStruct DestinyHeader;
		GraphicStruct DestinyHeaderXP;
		GraphicStruct DestinyHeaderXPBlank;
		GraphicStruct DestinyHeaderRank;
		GraphicStruct DestinyHeaderRankBlank;
		GraphicStruct ClaimDestinyOn;
		GraphicStruct ClaimDestinyOff;
		GraphicStruct MakeActiveButton;
		GraphicStruct LevelCircle;

		//Variables for tracking placement of Graphics
		GraphicPlacement DestinyBackground;
		GraphicPlacement DestinyHeaderLocation;
		GraphicPlacement DestinyHeaderXPLocation;
		GraphicPlacement DestinyHeaderRank1Location;
		GraphicPlacement DestinyHeaderRank2Location;
		GraphicPlacement DestinyHeaderRank3Location;
		GraphicPlacement DestinyHeaderRank4Location;
		GraphicPlacement DestinyCoreFrame;
		GraphicPlacement SlotLocation[7][6];
		GraphicPlacement IconLocation[7][6];
		GraphicPlacement CoreBorderLocation[6];
		GraphicPlacement ResetTreeLocation;
		GraphicPlacement LevelSelectorLeft;
		GraphicPlacement LevelSelectorRight;
		GraphicPlacement ClaimDestinyLocation;
		GraphicPlacement MakeActiveLocation;

		//Rect's for clearing sections of graphics
		RECT rectHeader;
		RECT rectFooter;

		DESTINY_TREE SelectedDestiny;
		CLASS ClassID[3];
		int ClassLevel[3];
		bool MultiDestinyWindowvisible;
		bool ClaimDestinyFlag;
		bool ActivateDestinyFlag;
		int ToolTipTier;
		int ToolTipColumn;
		int XPPerRank[30];
		DestinyRankStruct DestinyTreeRanks[30];
		bool ClaimDestinyWindowVisible;

		//variables for subclassing child windows
		vector <HWND> SubclassHWNDs;
		vector <WNDPROC> OriginalProcs;

		void Accept();
		void Cancel();
		void ResetTree();
		void MakeActive();
		void UpdateScreenTree(DESTINY_TREE DTree);
		bool IsChildWindowVisible();
		bool IsSlotSelected(int x, int y, int *rTier, int *rColumn);
		void HandleMouseHover(int x, int y);
		void ClaimDestiny();
		void ActivateDestiny();
		void ChangeDestinyTreeRanks(bool flagIncrease);

		void DrawLevelSelectors(HDC hdc);
		void DrawDestinyListItem(HDC hdc, DWORD Item, long Top, long Left);
		void FillDestiniesList();
		void DrawScreenTree(HDC hdc);
		void HandleLeftMouseButtonClick(int x, int y);

		void LoadGraphics(HWND Parent);
		void DeleteGraphics();

		void SubclassChildWindows();
		void DeSubclassChildWindows();
		WNDPROC GetOriginalWinProc(HWND Window);

		//do not implement these two functions, instance control!!
		Screen_Destiny_Class(const Screen_Destiny_Class &source);
		Screen_Destiny_Class& operator=(const Screen_Destiny_Class &source);
	};

extern bool DestinyCompareLevel(DestinySortStruct E1, DestinySortStruct E2);