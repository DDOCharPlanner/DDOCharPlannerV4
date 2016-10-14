#pragma once

#include "stdafx.h"

//---------------------------------------------------------------------------
struct InterfaceComponentStruct
	{
	string ComponentName;
	string WindowType;
	string WindowLabel;
	double BaseLocationX;
	double BaseLocationY;
	double BaseWidth;
	double BaseHeight;
	DWORD Style;
	WINDOWID WindowID;
	string TooltipText;
	};

struct InterfaceGraphicStruct
	{
	string GraphicName;
	double BaseLocationX;
	double BaseLocationY;
	double BaseWidth;
	double BaseHeight;
	};

//---------------------------------------------------------------------------
class UIComponentManager
	{
	public:
		UIComponentManager();
		virtual ~UIComponentManager();

		void InitializeUI();
		InterfaceComponentStruct* GetComponentData(string ComponentName, CHILDWINDOW Screen);
		InterfaceGraphicStruct* GetGraphicData(string GraphicName, CHILDWINDOW Screen);
		string GetTooltipText(string ComponentName, CHILDWINDOW Screen);

	private:
		unordered_map<string,InterfaceComponentStruct> InterfaceComponentsMainScreen;
		unordered_map<string,InterfaceGraphicStruct> InterfaceGraphicsMainScreen;
		unordered_map<string, InterfaceGraphicStruct> InterfaceGraphicsFeatWindow;
		unordered_map<string, InterfaceComponentStruct> InterfaceComponentsMultiClassScreen;
		unordered_map<string, InterfaceGraphicStruct> InterfaceGraphicsMultiClassScreen;
		unordered_map<string, InterfaceComponentStruct> InterfaceComponentsMultiSkillWindow;
		unordered_map<string, InterfaceGraphicStruct> InterfaceGraphicsMultiSkillWindow;
		unordered_map<string, InterfaceComponentStruct> InterfaceComponentsMultiSpellsWindow;
		unordered_map<string, InterfaceGraphicStruct> InterfaceGraphicsMultiSpellsWindow;
		void InitializeUIComponent(string ComponentName, CHILDWINDOW Screen, string WindowType, string WindowLabel, DWORD Style, unsigned int BaseLocationX, unsigned int BaseLocationY, unsigned int BaseWidth, unsigned int BaseHeight, WINDOWID WindowID, string TooltipText="");
		void InitializeUIGraphic(string GraphicName, CHILDWINDOW Screen, unsigned int BaseLocationX, unsigned int BaseLocationY, unsigned int BaseWidth, unsigned int BaseHeight);
	};

