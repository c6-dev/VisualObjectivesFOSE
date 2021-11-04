#include <string>
#include "code/internal/containers.h"
#include "utility.h"
#include "decoding.h"
#include "main.h"
#include "Version.h"
#include "WorldToScreen.h"
#include "VisualObjectives.h"

extern "C"
{
	BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpreserved)
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			VOHandle = hModule;
			DisableThreadLibraryCalls(hModule);
		}
		return TRUE;
	}

	bool FOSEPlugin_Query(const FOSEInterface* fose, PluginInfo* info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Visual Objectives";
		info->version = PLUGIN_VERSION;
		return versionCheck(fose);
	}

	bool FOSEPlugin_Load(const FOSEInterface* fose)
	{
		if (fose->isEditor) return false;
		handleIniOptions();
		auto commandExtender = GetModuleHandle("CommandExtender.dll");
		auto callbackEx = (MainLoopAddCallbackEx)GetProcAddress(commandExtender, "MainLoopAddCallbackEx");
		callbackEx(DeferredInit, NULL, 1, 1);
		callbackEx(DeferredUpdate, NULL, 0, 1);
		JGGameCamera.WorldMatrx = new JGWorldToScreenMatrix;
		JGGameCamera.CamPos = new JGCameraPosition;
		WriteRelJump(0xAAEDB6, (UInt32)NiCameraGetAltHook);
		WriteRelJump(0xAAEDC1, (UInt32)NiCameraGetAltHook);
		WriteRelJump(0xAAEB39, (UInt32)NiCameraGetAltHook);
		WriteRelJump(0x65E13C, (UInt32)MarkerWorldspaceHook);
		return true;
	}
};


void DeferredInit()
{
	g_thePlayer = PlayerCharacter::GetSingleton();
	hud = HUDMainMenu::GetSingleton();
	g_interfaceManager = InterfaceManager::GetSingleton();
	g_TES = *(TES**)0x107A0D8;
	VisualObjectives::Init();

}
void DeferredUpdate()
{
	if (VisualObjectives::initialized) VisualObjectives::Update();
}

bool versionCheck(const FOSEInterface* fose)
{
	if (fose->isEditor) return false;
	if (fose->foseVersion < FOSE_VERSION_INTEGER)
	{
		_ERROR("FOSE version too old (got %08X expected at least %08X)", fose->foseVersion, FOSE_VERSION_INTEGER);
		return false;
	}
	if (fose->runtimeVersion != FALLOUT_VERSION)
	{
		_ERROR("incorrect runtime version (got %08X need %08X)", fose->runtimeVersion, FALLOUT_VERSION);
		return false;
	}
	return true;
}