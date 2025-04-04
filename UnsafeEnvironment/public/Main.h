#pragma once

/*
	UnsafeEnvironment
*/

class Main {
private:
	Main() = default;
public:

	/*
		Patches UnsafeEnvironment
	*/
	static void PatchUnsafeEnvironment();
	static void Init(); 
};