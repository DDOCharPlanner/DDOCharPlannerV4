#include "RichEditBitmapClass.h"
#include "InterfaceManagerClass.h"

//---------------------------------------------------------------------------
RichEditBitmapClass::RichEditBitmapClass()
	{
	RefCnt = 0;
	release = false;
	}

//---------------------------------------------------------------------------
RichEditBitmapClass::~RichEditBitmapClass()
	{
	if (release == TRUE)
		ReleaseStgMedium(&stgmed);
	}

//---------------------------------------------------------------------------
void RichEditBitmapClass::InsertBitmap(HWND EditBox, HBITMAP Bitmap)
	{
	IRichEditOle *RichEditOle;
	RichEditBitmapClass *ImageDataObject;
	IDataObject *DataObject;
	IOleClientSite *OleClientSite;	
	IStorage *Storage;	
	ILockBytes *LockBytes;
	HRESULT hr;
	IOleObject *OleObject; 
	REOBJECT reobject;
	CLSID clsid;
	
	//grab the IRichEditOle interface 
	SendMessage(EditBox, EM_GETOLEINTERFACE, 0, (LPARAM)&RichEditOle);	

	//Get the image data object
	ImageDataObject = new RichEditBitmapClass;
	hr = ImageDataObject->QueryInterface(IID_IDataObject, (void**)&DataObject);	
	if (hr != S_OK)
		{
		OutputDebugString("Error grabbing ole interface\r\n");
		return;
		}

	ImageDataObject->SetBitmap(Bitmap);

	//Get the RichEdit client site
	hr = RichEditOle->GetClientSite(&OleClientSite);
	if (hr != S_OK)
		{
		OutputDebugString("Error grabbing client site\r\n");
		DataObject->Release();
		RichEditOle->Release();
		return;
		}
	
	//Initialize a Storage Object
	LockBytes = NULL;
	hr = CreateILockBytesOnHGlobal(NULL, TRUE, &LockBytes);
	if (hr != S_OK || LockBytes == NULL)
		{
		OutputDebugString("Error creating locked bytes\r\n");
		OleClientSite->Release();
		DataObject->Release();
		RichEditOle->Release();
		return;
		}
	hr = StgCreateDocfileOnILockBytes(LockBytes, STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &Storage);
	if (hr != S_OK || Storage == NULL)
		{
		OutputDebugString("Error creating storage object\r\n");
		OleClientSite->Release();
		DataObject->Release();
		RichEditOle->Release();
		return;
		}

	// The final ole object which will be inserted in the richedit control
	OleObject = ImageDataObject->GetOleObject(OleClientSite, Storage);
	if (OleObject == NULL)
		{
		OutputDebugString("Error creating ole object\r\n");
		Storage->Release();
		OleClientSite->Release();
		DataObject->Release();
		RichEditOle->Release();
		return;
		}
	
	hr = OleSetContainedObject(OleObject, TRUE);
	if (hr != S_OK)
		{
		OutputDebugString("Error setting contained ole object\r\n");
		OleObject->Release();
		Storage->Release();
		OleClientSite->Release();
		DataObject->Release();
		RichEditOle->Release();
		return;
		}

	//Now Add the object to the RichEdit 
	ZeroMemory(&reobject, sizeof(REOBJECT));
	reobject.cbStruct = sizeof(REOBJECT);
	
	hr = OleObject->GetUserClassID(&clsid);
	if (hr != S_OK)
		{
		OutputDebugString("Error grabbing ole object class ID\r\n");
		OleObject->Release();
		Storage->Release();
		OleClientSite->Release();
		DataObject->Release();
		RichEditOle->Release();
		return;
		}

	reobject.clsid = clsid;
	reobject.cp = REO_CP_SELECTION;
	reobject.dvaspect = DVASPECT_CONTENT;
	reobject.poleobj = OleObject;
	reobject.polesite = OleClientSite;
	reobject.pstg = Storage;

	// Insert the bitmap at the current location in the richedit control
	hr = RichEditOle->InsertObject(&reobject);
	if (hr != S_OK)
		{
		OutputDebugString("Error Error Inserting object into ole\r\n");
		}
		
	//cleanup
	OleObject->Release();
	Storage->Release();
	OleClientSite->Release();
//	DataObject->Release();  //for some reason, if we release this here, it breaks the graphic (possible resource leak?)
	RichEditOle->Release();
	}
	
//---------------------------------------------------------------------------
void RichEditBitmapClass::SetBitmap(HBITMAP Bitmap)
	{
	STGMEDIUM stgm;
	FORMATETC fm;

	stgm.tymed = TYMED_GDI;					// Storage medium = HBITMAP handle		
	stgm.hBitmap = Bitmap;
	stgm.pUnkForRelease = NULL;				// Use ReleaseStgMedium

	fm.cfFormat = CF_BITMAP;				// Clipboard format = CF_BITMAP
	fm.ptd = NULL;							// Target Device = Screen
	fm.dwAspect = DVASPECT_CONTENT;			// Level of detail = Full content
	fm.lindex = -1;							// Index = Not applicaple
	fm.tymed = TYMED_GDI;					// Storage medium = HBITMAP handle

	SetData(&fm, &stgm, TRUE);		
	}
	
//---------------------------------------------------------------------------
IOleObject* RichEditBitmapClass::GetOleObject(IOleClientSite *OleClientSite, IStorage *Storage)
	{
	HRESULT hr;
	IOleObject *OleObject;

	if (stgmed.hBitmap == NULL)
		return NULL;

	hr = OleCreateStaticFromData(this, IID_IOleObject, OLERENDER_FORMAT, &fromat, OleClientSite, Storage, (void**)&OleObject);
	if (hr != S_OK)
		return NULL;

	return OleObject;
	}

	
//---------------------------------------------------------------------------
//----------------------IUnkown pure virtual functions-----------------------
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::QueryInterface(REFIID iid, void **ppvObject)
	{
	if (iid == IID_IUnknown || iid == IID_IDataObject)
		{
		*ppvObject = this;
		AddRef();
		return S_OK;
		}
	else
		return E_NOINTERFACE;
	}
	
//---------------------------------------------------------------------------
ULONG RichEditBitmapClass::AddRef()
	{
	RefCnt++;
	return RefCnt;
	}

//---------------------------------------------------------------------------
ULONG RichEditBitmapClass::Release()
	{
	RefCnt--;
	if (RefCnt == 0)
		delete this;

	return RefCnt;
	}

//---------------------------------------------------------------------------
//------------------IDataObject pure virtual functions-----------------------
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium) 
	{
	HANDLE Dest;
	
	Dest = OleDuplicateData(stgmed.hBitmap, CF_BITMAP, NULL);
	if (Dest == NULL)
		return E_HANDLE;

	pmedium->tymed = TYMED_GDI;
	pmedium->hBitmap = (HBITMAP)Dest;
	pmedium->pUnkForRelease = NULL;

	return S_OK;
	}

//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::GetDataHere(FORMATETC*, STGMEDIUM*) 
	{
	return E_NOTIMPL;
	}

//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::QueryGetData(FORMATETC*) 
	{
	return E_NOTIMPL;
	}
	
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::GetCanonicalFormatEtc(FORMATETC*, FORMATETC*) 	
	{
	return E_NOTIMPL;
	}
	
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::SetData(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL rlse) 
	{
	fromat = *pformatetc;
	stgmed = *pmedium;
	release = rlse;

	return S_OK;
	}

//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::EnumFormatEtc(DWORD, IEnumFORMATETC**) 
	{
	return E_NOTIMPL;
	}
	
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::DAdvise(FORMATETC*, DWORD, IAdviseSink*, DWORD *) 
	{
	return E_NOTIMPL;
	}
	
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::DUnadvise(DWORD) 
	{
	return E_NOTIMPL;
	}
	
//---------------------------------------------------------------------------
HRESULT RichEditBitmapClass::EnumDAdvise(IEnumSTATDATA**) 
	{
	return E_NOTIMPL;
	}
