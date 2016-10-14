#pragma once

#include "stdafx.h"
#include "RichEditBitmapClass.h"
#include "UIComponentManager.h"
#include "IconClass.h"

class MultiSkillsWindowClass : public IconClass
{
public:

	MultiSkillsWindowClass();
	~MultiSkillsWindowClass();

	void Create(HINSTANCE Instance, HWND Parent);
	void Show(bool State);
	long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
	HWND GetHandle();
	HWND MultiSkillsHandle;
	void TrackMouse(HWND hwnd);

private:
	bool ErrorFound;
	HFONT TitleFontLarge;
	HFONT DefaultFont;
	HFONT SmallFont;
	HWND MultiSkillsLabel;
	HWND CancelButton;
	HWND AcceptButton;
	HWND SkillFrame;
	HWND SkillLabel;
	HWND TotalLabel;
	HWND SkillSpentLabel;
	HWND SKillAvalibleLabel;
	HWND AutoSkillFrame;
	HWND AutoFill;
	HWND ResetAuto;
	HWND ClassFirstCheckBox;
	HWND SetTotal;
	HWND Priority;
	HWND Reset;
	HPALETTE Palette;
	GraphicStruct SkillClassBox;
	GraphicStruct SkillNormalBox;
	GraphicStruct SkillErrorBox;
	GraphicStruct RightArrow;
	GraphicStruct LeftArrow;
	bool UseClassFirst;
	int PriorityValue[NUMSKILLS];
	int SetTotalValue[NUMSKILLS];
	bool UpdateAll;
	bool SkillChange;
	SKILLS CurrentSkill;
	int CurrentLevel;
	int CalculateAvailableSkillPoints(unsigned int AtLevel);
	int GetLevelSkillPointsSpent(SKILLS Skill, unsigned int AtLevel);
	int	GetLevelSkillPointsSpent(unsigned int AtLevel);
	float GetLevelSkillPointsSpentDisplay(SKILLS Skill, int AtLevel);
	int GetSkillPointsSpent(SKILLS Skill, unsigned int AtLevel);
	float GetTotalSkillPointsSpentDisplay(SKILLS Skill);
	float GetTotalSkillPointsSpentDisplay(SKILLS Skill, int AtLevel);
	bool CheckPointsSpent(SKILLS Skill, int AtLevel);
	bool CheckPointsSpent(int AtLevel);
	void SpendSkillPoint(SKILLS Skill, unsigned int Level, int Point);
	float GetSkillPointSpendLimit(SKILLS Skill, unsigned int AtLevel);
	void AcceptSkillPoints();
	void HandleLeftMouseButtonClick(int X, int Y);
	void HandleRightMouseButtonClick(int X, int Y);
	void HandleMouseHover(int x, int Y);
	void LoadGraphics(HWND Parent);
	void DrawSkillTable();
	void DrawAutoRank();
	void ClearSkillFrame(HDC hdc);
	void ClearSkillFrameTotals(HDC hdc);
	void ClearRect(HDC hdc, RECT rc);
	void DeleteGraphics();
	bool SkillsChanged;
	void AutoSetRanks();
	void ResetAutoValues();
	void DrawSkills(SKILLS Skill);
	void ResetSkillValues();
	void ClearAutoFillFrame(HDC hdc);
	int SkillsValue[NUMSKILLS][HEROICLEVELS];
	//do not implement these two functions, instance  control!!
	MultiSkillsWindowClass(const MultiSkillsWindowClass &source);
	MultiSkillsWindowClass& operator=(const MultiSkillsWindowClass &source);

};