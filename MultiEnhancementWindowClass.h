#pragma once

#include "stdafx.h"
#include "EnhancementWindowBaseClass.h"
#include "Data_Enhancement_Class.h"
#include "DataClass.h"
#include "EnhancementWindowClass.h"

class MultiEnhancementWindowClass : public EnhancementWindowBaseClass
	{
	public:
		MultiEnhancementWindowClass();
		~MultiEnhancementWindowClass();

		void Create(HINSTANCE Instance, HWND Parent);
		void Show(bool State);
		void ActivateMultiEnhancementWindow(int Tree, int Level, int Slot, int AvailableAP);
		long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		Data_Enhancement_Class* GetEnhancement(unsigned int Index);
		HWND GetHandle();
	private:
		HWND MultiEnhancementWindowHandle;
		HWND MultiEnhanceAcceptHandle;
		HWND MultiEnhanceCancelHandle;
		HWND ParentWindow;
		HWND MultiSelectionFrameHandle;
		EnhancementWindowClass *EnhancementWindow;
		Data_Enhancement_Class *ToolTipEnhancement;

		HPALETTE Palette;
		GraphicStruct IconPassiveBorder;
		GraphicStruct IconActiveBorder;
		GraphicStruct IconPassiveNotAvailable;
		GraphicStruct IconActiveNotAvailable;

		int CurrentTree;
		int CurrentLevel;
		int CurrentSlot;
		int APAvailable;
		//unsigned int CurrentStartingTree;
		unsigned int Num_Slots;
		unsigned int Selection;

		//for controlling the size of Window and icon placements
		unsigned int IconLeft;
		unsigned int IconTop;
		unsigned int Spacer;
		unsigned int IconWidth;
		unsigned int IconHeight;

		void HandleLeftMouseButtonClick(unsigned int x, unsigned int y);
		void HandleMouseHover(unsigned int x, unsigned int y);
		void LoadGraphics(HWND Parent);
		void DeleteGraphics();
		void DrawGraphics(HDC hdc);


		//do not implement these two functions, instance control!!!
		MultiEnhancementWindowClass(const MultiEnhancementWindowClass &source);
		MultiEnhancementWindowClass& operator=(const MultiEnhancementWindowClass &source);
	};