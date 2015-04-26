#include "utilities.h"
#include <direct.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;
bool initHighResTimer()
{
	LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
		return false;
    PCFreq = double(li.QuadPart) / 1000.0;
    if (!QueryPerformanceCounter(&li))
		return false;
    CounterStart = li.QuadPart;
	return true;
}

uint32_t timeGetHighResTime()
{
	if (PCFreq == 0.0)
		initHighResTimer();

	LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return uint32_t(double(li.QuadPart - CounterStart) / PCFreq);
}





struct enumWindowsInformation
{
	const char* title;
	HWND window;
};
BOOL CALLBACK enumWindowCallback(HWND hwnd, LPARAM lParam) {
    static char buffer[1024];

	auto info = (enumWindowsInformation*)lParam;

	GetWindowTextA(hwnd, buffer, 1024);
	if(strstr(buffer, info->title))
	{
        info->window = hwnd;
        return FALSE;
    }

    return TRUE;
}

HWND findWindowByPartialTitle(const char* title)
{
	enumWindowsInformation info;
	info.window = NULL;
	info.title = title;

	EnumWindows(enumWindowCallback, (LPARAM)&info);
	return info.window;
}



std::wstring getWorkingDirectory()
{
	wchar_t currentPath[MAX_PATH];
	if (!_wgetcwd(currentPath, MAX_PATH))
		return L"";
	return currentPath;
}