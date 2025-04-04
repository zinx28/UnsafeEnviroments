#include "../public/Main.h"
#include "../public/Utils.h"

void Main::PatchUnsafeEnvironment()
{
	Memcury::VEHHook::Init();

	auto UnsafeEnvironmentTitle = Memcury::Scanner::FindStringRef(L"UnsafeEnvironment_Title")
		.ScanFor({ 0x4C, 0x8B, 0xDC, 0x55, 0x49, 0x8D, 0xAB }, false);

	if (UnsafeEnvironmentTitle.IsValid())
		Memcury::VEHHook::AddHook(LPVOID(UnsafeEnvironmentTitle.Get()), UnsafeEnvironment);
	else
	{
		UnsafeEnvironmentTitle = Memcury::Scanner::FindStringRef(L"UnsafeEnvironment_Title")
			.ScanFor({ 0x48, 0x89, 0x5C, 0x24 }, false);
		if (UnsafeEnvironmentTitle.IsValid())
			Memcury::VEHHook::AddHook(LPVOID(UnsafeEnvironmentTitle.Get()), UnsafeEnvironment);
	}

	auto AttemptFind2 = Memcury::Scanner::FindStringRef(L"FPlatformMisc::RequestExit(%i)")
		.ScanFor({ 0x40, 0x53, 0x48, 0x83, 0xEC, 0x30, 0x80, 0x3D }, false); //todo shorten this

	if (AttemptFind2.IsValid())
	{
		std::cout << "addr: " << (void*)*reinterpret_cast<void**>(AttemptFind2.Get()) << std::endl;

		Memcury::VEHHook::AddHook(LPVOID(AttemptFind2.Get()), RequestExit);
		std::cout << "Successfully hooked function" << std::endl;
	}

	std::cout << "RequestExit: " << std::hex << AttemptFind2.Get() << std::endl;
	std::cout << "RequestExitNEW: " << std::hex << AttemptFind2.Get() - __int64(GetModuleHandleW(0)) << std::endl;

	//if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
	//	std::cout << "Failed to enable hooks" << std::endl;
	//}
}

void Main::Init()
{
	Utils::InitConsole();
	PatchUnsafeEnvironment();
}