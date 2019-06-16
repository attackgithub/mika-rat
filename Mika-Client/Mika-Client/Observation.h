namespace Observation {
	namespace Information {
		const char* _GetUserHwid() {
			HW_PROFILE_INFO hwProfileInfo;
			GetCurrentHwProfile(&hwProfileInfo);
			return((const char*)hwProfileInfo.szHwProfileGuid);
		}

		const char* _GetUserName() {
			char Buffer[UNLEN+1];
			DWORD dwBuffer = UNLEN+1;
			GetUserNameA(Buffer, &dwBuffer);
			return((const char*)Buffer);
		}

		const char* _GetMachineName() {
			char Buffer[CNLEN + 1];
			DWORD dwBuffer = sizeof(char) * (CNLEN + 1);
			GetComputerNameA(Buffer, &dwBuffer);
			return((const char*)Buffer);
		}
		
		const char* _GetOperatingSystem() {	
			if (IsWindows10OrGreater()) {
				return("Windows 10");
			} else if (IsWindows8OrGreater()) {
				return("Windows 8");
			} else if (IsWindows7OrGreater()) {
				return("Windows 7");
			} else if (IsWindowsVistaOrGreater()) {
				return("Windows Vista");
			} else if (IsWindowsXPOrGreater()) {
				return("Windows XP");
			} else if (IsWindowsServer()) {
				return("Windows Server");
			} else {
				return("Unknown");
			}
		}

		const char* _GetRamCount() {
			MEMORYSTATUSEX st_MemoryInfo;
			st_MemoryInfo.dwLength = sizeof(st_MemoryInfo);
			GlobalMemoryStatusEx(&st_MemoryInfo);

			char memory[MAX_PATH];
			sprintf_s(memory, MAX_PATH, "%.0f GB", 
				st_MemoryInfo.ullTotalPhys / (1e+9));
			return(memory);
		}

		const char* _GetRamLoad() {
			MEMORYSTATUSEX st_MemoryInfo;
			st_MemoryInfo.dwLength = sizeof(st_MemoryInfo);
			GlobalMemoryStatusEx(&st_MemoryInfo);

			char memory[MAX_PATH];
			sprintf_s(memory, MAX_PATH, "%.2f GB",
				((float)st_MemoryInfo.ullTotalPhys / (1e+9)) - ((float)st_MemoryInfo.ullAvailPhys / (1e+9)));
			return((const char*)memory);
		}

		bool _IsEvaluated() {
			HANDLE hToken = NULL;
			if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
				TOKEN_ELEVATION Elevation;
				DWORD cbSize = sizeof(TOKEN_ELEVATION);
				if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
					CloseHandle(hToken);
					return(Elevation.TokenIsElevated);
				} CloseHandle(hToken);
			} return(false);
		}

		const char* _ProcessList() {
			
		}
	}
}