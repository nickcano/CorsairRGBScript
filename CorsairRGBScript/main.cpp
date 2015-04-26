#include <Windows.h>
#include <tchar.h>

#include "utilities.h"
#include "keyboardScript.h"

int wmain(int argc, wchar_t *argv[]) 
{
	/* make sure Corsair's utility isn't running */
	auto check1 = findWindowByPartialTitle("Corsair Utility Engine");
	auto check2 = findWindowByPartialTitle("CorsairHID");
	if (check1 != NULL || check2 != NULL)
	{
		printf("Please close Corsair Utility Engine before using this application!\n");
		return 1;
	}

	/* make sure args are correct */
	if (argc != 2)
	{
		printf("Usage: me.exe script.lua\n");
		return 1;
	}

	/* hide me */
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	/* set up script paths */
	std::wstring workingDirectory = getWorkingDirectory();
	std::wstring libraryPath = workingDirectory  + L"\\library.lua";
	std::wstring scriptPath = argv[1];


	/* execute script */
	keyboardScript script;
	script.doFile(libraryPath.c_str());
	script.doFile(scriptPath.c_str());
	script.doMainLoop();
	

	return 0;
}