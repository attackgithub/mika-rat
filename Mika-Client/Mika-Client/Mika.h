#include <Windows.h>
#include <lmcons.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <VersionHelpers.h>

#include "Utils.h"
#include "Observation.h"

namespace Mika {
	void __stdcall Mika() {
		MessageBoxA(NULL, Observation::Information::_GetRamLoad(), "Mika", MB_OK);
	}
}