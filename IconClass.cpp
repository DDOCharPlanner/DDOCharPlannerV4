#include "IconClass.h"
#include <filesystem>

//---------------------------------------------------------------------------
IconClass::IconClass()
	{
	}

//---------------------------------------------------------------------------
IconClass::~IconClass()
	{
	}

//---------------------------------------------------------------------------
IconClass::IconClass(const IconClass &source)
	{
	}

//---------------------------------------------------------------------------
IconClass& IconClass::operator=(const IconClass &source)
	{
	return *this;
	}

//---------------------------------------------------------------------------
void IconClass::LoadBitmap(string File, string Subdirectory, GraphicStruct *Bitmap, COLORREF TransColor, int TransPixelX, int TransPixelY)
    {
    string FullPathFile;
    char OutputString[MAX_PATH];
    BITMAP bm;
	
    GetCurrentDirectory(MAX_PATH, OutputString);
    FullPathFile = OutputString;
    FullPathFile += "\\Graphics\\";
    if (Subdirectory != "")
        {
        FullPathFile += Subdirectory;
        FullPathFile += "\\";
        }
    FullPathFile += File;
    FullPathFile += ".bmp";

    Bitmap->Graphic = (HBITMAP)LoadImage(0, FullPathFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (Bitmap->Graphic == NULL)
        {
		DEBUG("Missing Icon: " + FullPathFile);
        GetCurrentDirectory(MAX_PATH, OutputString);
        FullPathFile = OutputString;
        FullPathFile += "\\Graphics\\";
        if (Subdirectory != "")
            {
            FullPathFile += Subdirectory;
            FullPathFile += "\\";
            }
        FullPathFile += "NoImage";
        FullPathFile += ".bmp";
        Bitmap->Graphic = (HBITMAP)LoadImage(0, FullPathFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
    GetObject(Bitmap->Graphic, sizeof(bm), &bm);
    Bitmap->Width = bm.bmWidth;
    Bitmap->Height = bm.bmHeight;
	Bitmap->Name = File;
	CreateBitmapMask(Bitmap, TransColor, TransPixelX, TransPixelY);
    }
//---------------------------------------------------------------------------
void IconClass::CreateBitmapMask(GraphicStruct *Bitmap, COLORREF TransColor, int TransPixelX, int TransPixelY)
    {
    BITMAP bm;
    HDC Src;
    HDC Dst;
    COLORREF Trans;
    COLORREF SaveBk;
    COLORREF SaveDstText;
    HBITMAP SrcT;
    HBITMAP DstT;

    //Get the dimensions of the source bitmap
    GetObject(Bitmap->Graphic, sizeof(bm), &bm);

    //Create the mask bitmap
    DeleteObject(Bitmap->Mask);
    Bitmap->Mask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

    //We will need two DCs to work with. One to hold the Image
    //(the source), and one to hold the mask (destination).
    Src = CreateCompatibleDC(NULL);
    Dst = CreateCompatibleDC(NULL);

    //Load the bitmaps into memory DC
    SrcT = (HBITMAP)SelectObject(Src, Bitmap->Graphic);
    DstT = (HBITMAP)SelectObject(Dst, Bitmap->Mask);

     //Dynamically get the transparent color
     if (TransColor == NULL)
        Trans = GetPixel(Src, TransPixelX, TransPixelY);
     else
        Trans = TransColor;

    //Change the background to trans color
    SaveBk  = SetBkColor(Src, Trans);

    //create the monocrome mask bitmap
    BitBlt(Dst, 0, 0, bm.bmWidth, bm.bmHeight, Src, 0, 0, SRCCOPY);

    //Now, we need to paint onto the original image, making
    //sure that the "transparent" area is set to black.
    SaveDstText = SetTextColor(Src, RGB(255,255,255));
    SetBkColor(Src, RGB(0,0,0));
    BitBlt(Src, 0, 0, bm.bmWidth, bm.bmHeight, Dst, 0, 0, SRCAND);

    //Clean up by deselecting any objects, and delete the DC's.
    SetTextColor(Dst, SaveDstText);

    SetBkColor(Src, SaveBk);
    SelectObject(Src, SrcT);
    SelectObject(Dst, DstT);

    DeleteDC(Src);
    DeleteDC(Dst);

    return;
    }

//---------------------------------------------------------------------------
void IconClass::DrawGraphic(HDC hdc, GraphicStruct *Bitmap, int x, int y, int Width, int Height)
    {
    HDC Graphic;
    HDC Mask;
    HBITMAP OldGraphic;
    HBITMAP OldMask;

    Graphic = CreateCompatibleDC(hdc);
    Mask = CreateCompatibleDC(hdc);

    OldGraphic = (HBITMAP)SelectObject(Graphic, Bitmap->Graphic);
    OldMask = (HBITMAP)SelectObject(Mask, Bitmap->Mask);

	SetStretchBltMode(hdc, HALFTONE);

    StretchBlt(hdc, x, y, Width, Height, Mask, 0, 0,Bitmap->Width, Bitmap->Height, SRCAND);
    StretchBlt(hdc, x, y, Width, Height, Graphic, 0, 0, Bitmap->Width, Bitmap->Height, SRCPAINT);

    SelectObject(Graphic, OldGraphic);
    SelectObject(Mask, OldMask);

    DeleteDC(Graphic);
    DeleteDC(Mask);
    }

//---------------------------------------------------------------------------
void IconClass::DrawGraphicGreyscale(HDC hdc, GraphicStruct *Bitmap, int x, int y, int Width, int Height)
    {
    HDC Graphic;
    HDC Greyscale;
    HDC Mask;
    HBITMAP GreyscaleGraphic;
    HBITMAP OldGraphic;
    HBITMAP OldGreyscale;
    HBITMAP OldMask;
    COLORREF Pixel;
    BYTE Red;
    BYTE Green;
    BYTE Blue;
    BYTE Grey;

    Graphic = CreateCompatibleDC(hdc);
    Greyscale = CreateCompatibleDC(hdc);
    Mask = CreateCompatibleDC(hdc);

    GreyscaleGraphic = CreateCompatibleBitmap(hdc, Bitmap->Width, Bitmap->Height);
    OldGraphic = (HBITMAP)SelectObject(Graphic, Bitmap->Graphic);
    OldGreyscale = (HBITMAP)SelectObject(Greyscale, GreyscaleGraphic);
    OldMask = (HBITMAP)SelectObject(Mask, Bitmap->Mask);

    //create the greyscale graphic
    for (int i=0; i<Bitmap->Height; i++)
        {
        for (int j=0; j<Bitmap->Width; j++)
            {
            Pixel = GetPixel(Graphic, i, j);
            Red = GetRValue(Pixel);
            Green = GetGValue(Pixel);
            Blue = GetBValue(Pixel);
            Grey = 76*Red/255 + 150*Green/255 + 28*Blue/255;
            SetPixel(Greyscale, i, j, RGB(Grey, Grey, Grey));
            }
        }

    StretchBlt(hdc, x, y, Width, Height, Mask, 0, 0,Bitmap->Width, Bitmap->Height, SRCAND);
    StretchBlt(hdc, x, y, Width, Height, Greyscale, 0, 0, Bitmap->Width, Bitmap->Height, SRCPAINT);

    SelectObject(Graphic, OldGraphic);
    SelectObject(Greyscale, OldGreyscale);
    SelectObject(Mask, OldMask);

    DeleteObject(GreyscaleGraphic);

    DeleteDC(Graphic);
    DeleteDC(Greyscale);
    DeleteDC(Mask);
    }

//---------------------------------------------------------------------------
HCURSOR IconClass::CreateCursorFromBitmap(HWND ParentWindow, HPALETTE Palette, GraphicStruct *Bitmap, COLORREF TransColor, int HotSpotX, int HotSpotY)
    {
    HDC hDC;
    HDC hOriginalSource;
    HDC hShrunkSource;
    HDC hAndMaskDC;
    HDC hXorMaskDC;
    HBITMAP ShrunkSource;
    HBITMAP OldObject[4];
    COLORREF MainBitPixel;
    HBITMAP hAndMaskBitmap;
    HBITMAP hXorMaskBitmap;
    ICONINFO IconInfo;

    hDC = GetDC(ParentWindow);
    hOriginalSource = CreateCompatibleDC(hDC);
    hShrunkSource = CreateCompatibleDC(hDC);

    SelectPalette(hDC, Palette, false);
    RealizePalette(hDC);
    SetStretchBltMode(hDC, HALFTONE);
    SetBrushOrgEx(hDC, 0, 0, NULL);

    ShrunkSource = CreateCompatibleBitmap(hDC,32,32);

    OldObject[0] = (HBITMAP)SelectObject(hOriginalSource, Bitmap->Graphic);
    OldObject[1] = (HBITMAP)SelectObject(hShrunkSource, ShrunkSource);
    StretchBlt(hShrunkSource, 0, 0, 32, 32, hOriginalSource, 0, 0, Bitmap->Width, Bitmap->Height, SRCCOPY);

    SelectObject(hOriginalSource, OldObject[0]);
    DeleteDC(hOriginalSource);

    hAndMaskDC = CreateCompatibleDC(hDC);
    hXorMaskDC = CreateCompatibleDC(hDC);
    hAndMaskBitmap = CreateCompatibleBitmap(hDC,32,32);
    hXorMaskBitmap = CreateCompatibleBitmap(hDC,32,32);

    //Select the bitmaps to DC
    OldObject[2] = (HBITMAP)SelectObject(hAndMaskDC, hAndMaskBitmap);
    OldObject[3] = (HBITMAP)SelectObject(hXorMaskDC, hXorMaskBitmap);

    //Scan each pixel of the souce bitmap and create the masks
    for (int x=0; x<32; x++)
        {
        for (int y=0; y<32; y++)
            {
            MainBitPixel = GetPixel(hShrunkSource,x,y);
            if (MainBitPixel == TransColor)
                {
                SetPixel(hAndMaskDC, x, y, RGB(255,255,255));
                SetPixel(hXorMaskDC, x, y, RGB(0,0,0));
                }
            else
                {
                SetPixel(hAndMaskDC, x, y, RGB(0,0,0));
                SetPixel(hXorMaskDC, x, y, MainBitPixel);
                }
            }
        }
  
    IconInfo.fIcon = FALSE;
    IconInfo.xHotspot = HotSpotX;
    IconInfo.yHotspot = HotSpotY;
    IconInfo.hbmMask = hAndMaskBitmap;
    IconInfo.hbmColor = hXorMaskBitmap;

    SelectObject(hShrunkSource, OldObject[1]);
    SelectObject(hAndMaskDC, OldObject[2]);
    SelectObject(hXorMaskDC, OldObject[3]);

    DeleteDC(hXorMaskDC);
    DeleteDC(hAndMaskDC);
    DeleteDC(hShrunkSource);
    ReleaseDC(ParentWindow,hDC);

    return CreateIconIndirect(&IconInfo);
    }



