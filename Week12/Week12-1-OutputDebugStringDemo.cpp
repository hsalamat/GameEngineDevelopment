//The Windows SDK function OutputDebugString() is great for printing debugging
//information to Visual Studio’s Debug Output window.However,
//unlike printf(), OutputDebugString() does not support formatted
//output—it can only print raw strings in the form of arrays.For this reason,
//most Windows game engines wrap it in a custom function, like this:


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // for va_list et al
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h> // for OutputDebugString()
typedef unsigned int U32;

int VDebugPrintF(const char* format, va_list argList)
{
	const U32 MAX_CHARS = 1024;
	static char s_buffer[MAX_CHARS];
	//int vsnprintf (char * s, size_t n, const char * format, va_list arg );
	//Write formatted data from variable argument list to sized buffer
	int charsWritten = vsnprintf(s_buffer, MAX_CHARS, format, argList);
	// Now that we have a formatted string, call the  Win32 API.
	OutputDebugStringA(s_buffer);
	return charsWritten;
}


//Notice that two functions are implemented : DebugPrintF() takes a variable - length argument list(specified via the ellipsis, …), 
//while VDebug - PrintF() takes a va_list argument.This is done so that programmers can
//build additional printing functions in terms of VDebugPrintF(). (It’s impossible to pass ellipses from one function to another, but it is possible to pass va_lists around.)
int DebugPrintF(const char* format, ...)
{
	va_list argList;  //This type is used as a parameter for the macros defined in <cstdarg> to retrieve the additional arguments of a function.
	va_start(argList, format); //Initialize a variable argument list
	int charsWritten = VDebugPrintF(format, argList);
	va_end(argList); //End using variable argument list
	return charsWritten;
}

int main(int argc, char* argv[])
{
	int gameLevel = 1, gameSpeed = 60;
	OutputDebugString(L"Testing Formmated OutputDebugString... this will produce output in the Output window of the VS Debugger");
	DebugPrintF("\nGameLevel: %d & GameSpeed: %d\n", gameLevel, gameSpeed);

	char buffer[50];
	int n, a = 5, b = 3;
	n = sprintf(buffer, "%d plus %d is %d", a, b, a + b);
	printf("[%s] is a string %d chars long. This is only good for Console applications and not Win32!\n", buffer, n);
	
	char buf[4096];
	char* msgbuf = buf;
	sprintf(buf, "My gameLevel is %d\n", gameLevel);
	OutputDebugStringA(buf);

	return 0;
}