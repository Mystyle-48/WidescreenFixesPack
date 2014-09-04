#include "stdafx.h"
#include "..\includes\CPatch.h"
#include "..\includes\IniReader.h"
HWND hWnd;

int res_x;
int res_y;
float fScale;

void Init()
{
	CIniReader iniReader("");
	res_x = iniReader.ReadInteger("MAIN", "X", 0);
	res_y = iniReader.ReadInteger("MAIN", "Y", 0);

	if (!res_x || !res_y) {
		HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO info;
		info.cbSize = sizeof(MONITORINFO);
		GetMonitorInfo(monitor, &info);
		res_x = info.rcMonitor.right - info.rcMonitor.left;
		res_y = info.rcMonitor.bottom - info.rcMonitor.top;
	}

	CPatch::Nop(0x444890 + 0x2, 5);//dword_A7793C,eax
	CPatch::Nop(0x4469F0 + 0x120, 6); //dword_A7793C,ecx
	//CPatch::Nop(0x427710 + 0x12, 10); //dword_A7793C,280h
	CPatch::Nop(0x4469F0 + 0x155, 6); //dword_A7793C,edx

	CPatch::Nop(0x4469F0 + 0x12C, 6); //dword_A77940,edx
	CPatch::Nop(0x4469F0 + 0x15B, 6); //dword_A77940,ecx
	//CPatch::Nop(0x427710 + 0x25, 10); //dword_A77940,1E0h
	CPatch::Nop(0x444890 + 0x7, 5); //dword_A77940,eax



	/*CPatch::Nop(0x657FF0 + 0x89B, 6); //dword_AA5140,edx
	CPatch::Nop(0x657FF0 + 0x4BC, 6); //dword_AA5140,eax
	CPatch::Nop(0x6565E0 + 0x803, 6); //dword_AA5140,edx
	CPatch::Nop(0x6565E0 + 0x424, 6); //dword_AA5140,eax
	CPatch::Nop(0x655EB0 + 0xB4, 6); //dword_AA5140,eax
	CPatch::Nop(0x655EB0 + 0x56, 6); //dword_AA5140,ecx

	CPatch::Nop(0x655EB0 + 0x5F, 6); //dword_AA5144,edx
	CPatch::Nop(0x655EB0 + 0xC4, 6); //dword_AA5144,ecx
	CPatch::Nop(0x6565E0 + 0x429, 6); //dword_AA5144,ecx
	CPatch::Nop(0x6565E0 + 0x7F9, 6); //dword_AA5144,eax
	CPatch::Nop(0x657FF0 + 0x4C1, 6); //dword_AA5144,ecx
	CPatch::Nop(0x657FF0 + 0x891, 6); //dword_AA5144,eax*/



	CPatch::Nop(0x657FF0 + 0xAFB, 5); //dword_AA5384,eax
	CPatch::Nop(0x657750 + 0x55A, 5); //dword_AA5384,eax
	CPatch::Nop(0x657750 + 0x2D7, 6); //dword_AA5384,edx
	CPatch::Nop(0x6565E0 + 0xA62, 5); //dword_AA5384,eax
	CPatch::Nop(0x6557A2, 6); //dword_AA5384,edx
	CPatch::Nop(0x65511B, 5); //dword_AA5384,eax

	CPatch::Nop(0x657FF0 + 0xB00, 6); //dword_AA5388,ecx
	CPatch::Nop(0x657750 + 0x55F, 6); //dword_AA5388,ecx
	CPatch::Nop(0x657750 + 0x2E0, 6); //dword_AA5388,edx
	CPatch::Nop(0x6565E0 + 0xA67, 6); //dword_AA5388,ecx
	CPatch::Nop(0x6557A8, 5); //dword_AA5388,eax
	CPatch::Nop(0x655123, 5); //dword_AA5388,eax

	//CPatch::SetUChar(0x6556B0+1, 0x48);

	CPatch::SetUInt(0xA7793C, 1920);
	CPatch::SetUInt(0xA77940, 1080);

	CPatch::SetUInt(0xAA5140, 1920);
	CPatch::SetUInt(0xA77944, 1080);

	CPatch::SetUInt(0xAA5384, 1920);
	CPatch::SetUInt(0xAA5388, 1080);

	//CPatch::SetUInt(0x427728, 1920);
	//CPatch::SetUInt(0x42773B, 1080);

	//stretching
	fScale = (1.0f * (4.0f / 3.0f)) / (static_cast<float>(res_x) / static_cast<float>(res_y));
	CPatch::SetPointer(0x64AC8B + 0x2, &fScale);

}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}
	return TRUE;
}