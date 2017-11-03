#include "WindowsDialogClass.h"
#include "CharacterClass.h"
#include "time.h"


WindowsDialogClass WindowsDialog;

WindowsDialogClass::WindowsDialogClass()
{
	xptest = true;
}


WindowsDialogClass::~WindowsDialogClass()
{
}

bool WindowsDialogClass::LoadFileDialog(HWND hwnd)
{
	static char FileFilter[] = "Text Files\0*.txt\0All Files\0*.*\0";
	char InitDirectory[1024];
	static char TitleString[] = "Load Character";
	static char DefaultExtension[] = "txt";
	char FileName[1024];
	bool Error = false; //true is error or canceled
	OPENFILENAME FileOpen;
	int len;
	StringCbCopy(InitDirectory, 1024, "\0");
	GetCurrentDirectory(1024, InitDirectory);
	StringCbCat(InitDirectory, 1024, "\\SaveFiles\\");
	StringCbCopy(FileName, 1024, "\0");


	CoInitialize;
	IFileOpenDialog *pfd = NULL;
	HRESULT hr;
	hr = CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr) && xptest != true)
	{
		//HRESULT hr;

		// Create a new common open file dialog.

		//hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

		if (SUCCEEDED(hr))
		{
			DWORD dwOptions;
			hr = pfd->GetOptions(&dwOptions);
			if (SUCCEEDED(hr))
				hr = pfd->SetOptions(dwOptions | FOS_FORCEFILESYSTEM);

			// Set the title of the dialog.
			if (SUCCEEDED(hr))
			{
				LPCWSTR szTXT = L"Text File";
				hr = pfd->SetTitle(L"Select File");
				if (SUCCEEDED(hr))
				{
					COMDLG_FILTERSPEC rgSpec[] =
					{
						{ szTXT, L"*.txt" },
					};
					hr = pfd->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
				}
			}
			// Show the open file dialog.
			if (SUCCEEDED(hr))
			{
				hr = pfd->Show(hwnd);
				if (SUCCEEDED(hr))
				{  // Get the selection from the user.
					IShellItem *psiResult = NULL;
					hr = pfd->GetResult(&psiResult);
					if (SUCCEEDED(hr))
					{
						PWSTR pszPath = NULL;
						hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);

						if (SUCCEEDED(hr))
						{
							if (0 != (len = WideCharToMultiByte(CP_ACP, 0, pszPath, -1, FiletoOpen, MAX_PATH, NULL, NULL)))
							{
								Error = false;
								FiletoOpen[len] = '\0';

								
								//*FiletoOpen = NULL;
							}
							else
								Error = true;
								CoTaskMemFree(pszPath);
						}
						psiResult->Release();
					}
				}
				else
				{
					if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
						Error = true; // User cancelled the dialog...
				}
			}


		}
		pfd->Release();
	}
	else
	{
		// use GetOpenFileName() as needed...

		memset(&FileOpen, 0, sizeof(OPENFILENAME));
		FileOpen.lStructSize = sizeof(OPENFILENAME);
		FileOpen.hwndOwner = hwnd;
		FileOpen.hInstance = 0;
		FileOpen.lpstrFilter = FileFilter;
		FileOpen.lpstrCustomFilter = NULL;
		FileOpen.nMaxCustFilter = 0;
		FileOpen.nFilterIndex = 1;
		FileOpen.lpstrFile = FileName;
		FileOpen.nMaxFile = 1024;
		FileOpen.lpstrFileTitle = NULL;
		FileOpen.nMaxFileTitle = 512;
		FileOpen.lpstrInitialDir = InitDirectory;
		FileOpen.lpstrTitle = TitleString;
		FileOpen.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
		FileOpen.nFileOffset = 0;
		FileOpen.nFileExtension = 0;
		FileOpen.lpstrDefExt = DefaultExtension;
		FileOpen.lCustData = 0;
		FileOpen.lpfnHook = 0;
		FileOpen.lpTemplateName = NULL;


		if (GetOpenFileName(&FileOpen) == false)
			Error = true;
		//FileHandle = CreateFile(FileOpen.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//if (FileHandle == INVALID_HANDLE_VALUE)
		//return;
		if (Error == false)
		{
			strcpy_s(FiletoOpen, MAX_PATH, FileOpen.lpstrFile);

			len = strlen(FiletoOpen);
			if (0 != len)
			{
				Error = false;
				FiletoOpen[len] = '\0';

				//*FiletoOpen = NULL;
			}
			else
			{
				Error = true;
			}
		}
	}
	return Error;
}

bool WindowsDialogClass::SaveFileDialog(HWND hwnd, bool SaveAs)
{
	OPENFILENAME FileOpen;
	string NewCombinedName;
	int len;
	bool Error = false;
	char FileName[MAX_PATH];
	char InitDirectory[MAX_PATH];
	IShellItem *MyShellItem;
	string CombinedName;

	string FirstName;
	string SurName;
	ostringstream ss;
	static char FileFilter[] = "Text Files\0*.txt\0All Files\0*.*\0";



	static char TitleString[] = "Save Character";
	static char DefaultExtension[] = "txt";
	Character.GetName(&FirstName, &SurName);



	if (FirstName != "")
		CombinedName = FirstName;
	if (SurName != "")
		if (CombinedName != "")
			CombinedName += " " + SurName;
		else
			CombinedName = SurName;

	if (FiletoOpen[0] == 0 || SaveAs == true)
	{
		StringCbCopy(FileName, MAX_PATH, "\0");
		GetCurrentDirectory(MAX_PATH, InitDirectory);
		StringCbCat(InitDirectory, MAX_PATH, "\\SaveFiles\\");
		StringCbPrintf(FileName, MAX_PATH, "%s.txt", CombinedName.c_str());



		IFileDialog *pfd = NULL;
		LPCWSTR TxtStr = L".txt";

		//char *dir_org = NULL;
		HRESULT temphr;
		HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileSaveDialog, (void**)&pfd);
		if (SUCCEEDED(hr) && xptest != true)
		{
			HRESULT hr;
			// Create a new common open file dialog.
			IFileOpenDialog *pfd = NULL;
			hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileSaveDialog, (void**)&pfd);
			if (SUCCEEDED(hr))
			{
				DWORD dwOptions;
				hr = pfd->GetOptions(&dwOptions);
				if (SUCCEEDED(hr))
					hr = pfd->SetOptions(dwOptions | FOS_STRICTFILETYPES);
				// Set the title of the dialog.
				if (SUCCEEDED(hr))
				{
					LPCWSTR szTXT = L"Text File";
					hr = pfd->SetTitle(L"Select File");
					if (SUCCEEDED(hr))
					{
						COMDLG_FILTERSPEC rgSpec[] =
						{
							{ szTXT, L"*.txt" },
						};
						hr = pfd->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
						hr = pfd->SetDefaultExtension(L"txt");
					}

					hr = pfd->GetFolder(&MyShellItem);
					if (SUCCEEDED(hr))
					{

						PWSTR pszPath = NULL;
						hr = MyShellItem->GetDisplayName(SIGDN_NORMALDISPLAY, &pszPath);
						if (SUCCEEDED(hr))
						{

							if (CombinedName != "")
							{
								int CharCount = 0;
								char Pathstring[MAX_PATH];
								string TestString;
								do	{

									int nlength = wcslen(pszPath);
									//Gets converted length
									int nbytes = WideCharToMultiByte(0, 0, pszPath, nlength, NULL, 0, NULL, NULL);
									WideCharToMultiByte(0, 0, pszPath, nlength, Pathstring, nbytes, NULL, NULL);
									Pathstring[nbytes] = '\0';
									if (CharCount >= 0)
									{
										ss.str("");
										ss.clear();
										struct tm newtime;
										time_t now = time(0);   // get time now
										localtime_s(&newtime, &now);
										ss << ' ' << (newtime.tm_year + 1900) << '-'
											<< (newtime.tm_mon + 1) << '-'
											<< newtime.tm_mday;

										if (CharCount > 0)
										{
											ss << ' ' << CharCount;
										}

										ss << '\0';
										string str = ss.str();
										NewCombinedName = CombinedName + str.c_str();
										StringCbPrintf(FileName, MAX_PATH, "%s.txt", NewCombinedName.c_str());
									}
									ss.str("");
									ss.clear();
									ss << Pathstring;
									StringCbCat(Pathstring, MAX_PATH, "\0");
									ss << "\\";
									ss << FileName;
									TestString = ss.str();
									CharCount += 1;
								} while (File_Exists(TestString));

								std::wstring stemp = std::wstring(NewCombinedName.begin(), NewCombinedName.end());
								LPCWSTR  DefaultName = (LPCWSTR)stemp.c_str();
								hr = pfd->SetFileName(DefaultName);
								if (SUCCEEDED(hr))
								{
									DefaultName;
								}
								else
								{
									ostringstream msg;
									msg << "Set File Name Failed";
									string mymsg;
									mymsg = msg.str();
									MessageBox(0, mymsg.c_str(), "Save", MB_OK);
								}
							}

						}
						else
						{
							ostringstream msg;
							msg << "Get Display Name Failed";
							string mymsg;
							mymsg = msg.str();
							MessageBox(0, mymsg.c_str(), "Save", MB_OK);
						}





					}
					else
					{
						ostringstream msg;
						msg << "Get Folder Failed";
						string mymsg;
						mymsg = msg.str();
						MessageBox(0, mymsg.c_str(), "Save", MB_OK);
					}
				}
				// Show the open file dialog.
				if (SUCCEEDED(hr))
				{
					hr = pfd->Show(hwnd);
					if (SUCCEEDED(hr))
					{  // Get the selection from the user.
						IShellItem *psiResult = NULL;
						hr = pfd->GetResult(&psiResult);
						if (SUCCEEDED(hr))
						{
							PWSTR pszPath = NULL;
							hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);

							if (SUCCEEDED(hr))
							{
								if (0 != (len = WideCharToMultiByte(CP_ACP, 0, pszPath, -1, FiletoOpen, MAX_PATH, NULL, NULL)))
								{
									Error = false;
									FiletoOpen[len] = '\0';

									//FileHandle = CreateFile(FiletoOpen, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
									//if (FileHandle == INVALID_HANDLE_VALUE)
									//return;
									//*FiletoOpen = NULL;
								}
								else
									Error = true;
								CoTaskMemFree(pszPath);
							}
							psiResult->Release();
						}
					}
					else
					{
						if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
							Error = true; // User cancelled the dialog...
					}
				}
				pfd->Release();
			}

		}
		else
		{
			// use GetOpenFileName() as needed...

			memset(&FileOpen, 0, sizeof(OPENFILENAME));
			FileOpen.lStructSize = sizeof(OPENFILENAME);
			FileOpen.hwndOwner = hwnd;
			FileOpen.hInstance = 0;
			FileOpen.lpstrFilter = FileFilter;
			FileOpen.lpstrCustomFilter = NULL;
			FileOpen.nMaxCustFilter = 0;
			FileOpen.nFilterIndex = 1;
			FileOpen.lpstrFile = FileName;
			FileOpen.nMaxFile = 1024;
			FileOpen.lpstrFileTitle = NULL;
			FileOpen.nMaxFileTitle = 512;
			FileOpen.lpstrInitialDir = InitDirectory;
			FileOpen.lpstrTitle = TitleString;
			FileOpen.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
			FileOpen.nFileOffset = 0;
			FileOpen.nFileExtension = 0;
			FileOpen.lpstrDefExt = DefaultExtension;
			FileOpen.lCustData = 0;
			FileOpen.lpfnHook = 0;
			FileOpen.lpTemplateName = NULL;

			if (GetSaveFileName(&FileOpen) == false)
				Error = true;

			strcpy_s(FiletoOpen, MAX_PATH, FileOpen.lpstrFile);
			len = strlen(FiletoOpen);
			FiletoOpen[len] = '\0';
			Error = false;
			//FileHandle = CreateFile(FileOpen.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			//if (FileHandle == INVALID_HANDLE_VALUE)
			//return;
		}
	}
	return Error;
}

void WindowsDialogClass::ResetFiletoOpen()
{
	*FiletoOpen = NULL;
}

void WindowsDialogClass::ReturnFiletoOpen(char*& FiletoOpenin)
{
	FiletoOpenin = FiletoOpen;
}

bool WindowsDialogClass::File_Exists(const std::string& name)
{
	FILE *filepoint;
	errno_t err;
	if ((err = fopen_s(&filepoint, name.c_str(), "r")) != 0) {
		// File could not be opened. filepoint was set to NULL
		return false;
	}
	else {
		// File was opened, filepoint can be used to read the stream.
		fclose(filepoint);
		return true;
	}
}