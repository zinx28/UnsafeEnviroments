#pragma once

/*
	UnsafeEnviroments
*/

void __fastcall sub_7FF6BAD8D030(char a1) {} // just make the function empty

__int64 __fastcall UnsafeEnvironment(__int64* a1, char a2, __int64 a3, char a4) {
	return 0;
}

DWORD WINAPI Main(LPVOID)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	MH_Initialize();

	//UnsafeEnvironment_Body
	auto AttemptFind = Memcury::Scanner::FindStringRef(L"UnsafeEnvironment_Title").ScanFor({ 0x4C, 0x8B, 0xDC, 0x55, 0x49, 0x8D, 0xAB }, false).Get();
	std::cout << "UNSAFE: " << std::hex << AttemptFind << std::endl;
	std::cout << "UNSAFENEW: " << std::hex << AttemptFind - __int64(GetModuleHandleW(0)) << std::endl;

	//FPlatformMisc::RequestExitWithStatus(%i, %d) - return code will be ignored by the generic implementation.
	//FPlatformMisc::RequestExit(%i)
	auto AttemptFind2 = Memcury::Scanner::FindStringRef(L"FPlatformMisc::RequestExit(%i)").ScanFor({ 0x40, 0x53, 0x48, 0x83, 0xEC, 0x30, 0x80, 0x3D }, false).Get();
	std::cout << "RequestExit: " << std::hex << AttemptFind2 << std::endl;
	std::cout << "RequestExitNEW: " << std::hex << AttemptFind2 - __int64(GetModuleHandleW(0)) << std::endl;
	
	MH_CreateHook(LPVOID(AttemptFind), UnsafeEnvironment, nullptr);
	MH_CreateHook(LPVOID(AttemptFind2), sub_7FF6BAD8D030, nullptr);
	
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		std::cout << "Failed to enable hooks" << std::endl;
	}
	return 0;
}