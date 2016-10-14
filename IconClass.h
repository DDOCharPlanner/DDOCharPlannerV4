#pragma once

#include "stdafx.h"

//this is a base class to be inherited by all classes that use icon graphics.

class IconClass
	{
	public:
		IconClass();
		virtual ~IconClass();
		//copy constructor and assignment operator
        IconClass(const IconClass &source);
        IconClass& operator=(const IconClass &source);

	protected:
        void LoadBitmap(string FileName, string Subdirectory, GraphicStruct *Bitmap, COLORREF TransColor = NULL, int TransPixelX = 0, int TransPixelY = 0);
		void LoadZipBitmap(string FileName, string Subdirectory, GraphicStruct *Bitmap, COLORREF TransColor = NULL, int TransPixelX = 0, int TransPixelY = 0);
		void CreateBitmapMask(GraphicStruct *Bitmap, COLORREF TransColor, int TransPixelX, int TransPixelY);
		void DrawGraphic(HDC hdc, GraphicStruct *Bitmap, int x, int y, int Width, int Height);
		void DrawGraphicGreyscale(HDC hdc, GraphicStruct *Bitmap, int x, int y, int Width, int Height);
		HCURSOR CreateCursorFromBitmap(HWND ParentWindow, HPALETTE Palette, GraphicStruct *Bitmap, COLORREF TransColor, int HotSpotX, int HotSpotY);
	};

