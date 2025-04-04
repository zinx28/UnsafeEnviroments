#pragma once
#include "../framework.h"
// uh idk where this should go
void __fastcall RequestExit(char a1) {} // just make the function empty

__int64 __fastcall UnsafeEnvironment(__int64* a1, char a2, __int64 a3, char a4) {
	return 0;
}


// i like my utils a single header file
namespace Utils {
	
	/*
		Inits Console
	*/
	inline void InitConsole()
	{
		AllocConsole();
		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
	}
}