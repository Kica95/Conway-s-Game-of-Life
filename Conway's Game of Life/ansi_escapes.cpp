#ifdef _WIN32
#include<Windows.h>
#endif // _WIN32

#include <stdio.h>
#include "ansi_escapes.h"

#ifdef DEBUG




static HANDLE stdoutHandle;
static DWORD outModeIinit;

void setupConsole(void) 
{
	DWORD outMode = 0;
	stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (stdoutHandle == INVALID_HANDLE_VALUE)
	{
		exit(GetLastError());
	}

	if (!GetConsoleMode(stdoutHandle, &outMode)) 
	{
		exit(GetLastError());
	}

	outModeIinit = outMode;

	outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if (!SetConsoleMode(stdoutHandle,outMode))
	{
		exit(GetLastError());
	}
}

void restoreConsole(void) 
{
	//reset colors
	printf("\x1b[0m");
	//reset console mode

	if (!SetConsoleMode(stdoutHandle, outModeIinit)) 
	{
		exit(GetLastError());
	}
}

#else

void setupConsole(void) {}
void restoreConsole(void) 
{
	//reset colors
	//reset colors
	printf("\x1b[0m");
	//reset console mode
}

#endif // DEBUG