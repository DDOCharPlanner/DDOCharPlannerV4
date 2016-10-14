#pragma once

#include "stdafx.h"

class RichEditBitmapClass : IDataObject
	{	
	public:
		RichEditBitmapClass();
		virtual ~RichEditBitmapClass();
	
		static void InsertBitmap(HWND EditBox, HBITMAP Bitmap);

		//the IUnknown interface 
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppvObject);
		ULONG STDMETHODCALLTYPE AddRef();
		ULONG STDMETHODCALLTYPE Release();
		
		//the IDataObject Interface
		HRESULT STDMETHODCALLTYPE GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium);
		HRESULT STDMETHODCALLTYPE GetDataHere(FORMATETC*, STGMEDIUM*);
		HRESULT STDMETHODCALLTYPE QueryGetData(FORMATETC*);
		HRESULT STDMETHODCALLTYPE GetCanonicalFormatEtc(FORMATETC*, FORMATETC*);
		HRESULT STDMETHODCALLTYPE SetData(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL rlse);
		HRESULT STDMETHODCALLTYPE EnumFormatEtc(DWORD, IEnumFORMATETC**);
		HRESULT STDMETHODCALLTYPE DAdvise(FORMATETC*, DWORD, IAdviseSink*, DWORD*);
		HRESULT STDMETHODCALLTYPE DUnadvise(DWORD);
		HRESULT STDMETHODCALLTYPE EnumDAdvise(IEnumSTATDATA**);
		
	private:
		ULONG RefCnt;
		STGMEDIUM stgmed;
		FORMATETC fromat;
		BOOL release;
		
		void SetBitmap(HBITMAP Bitmap);
		IOleObject* GetOleObject(IOleClientSite *OleClientSite, IStorage *Storage);
	};
