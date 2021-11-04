#pragma once

#include <time.h>
#include "fose\PluginAPI.h"
#include "fose_common\SafeWrite.h"
#include "fose\GameAPI.h"
#include "fose\GameInterface.h"
#include "fose\GameObjects.h"
#include "fose/ParamInfos.h"
#include "fose/GameExtraData.h"
#include "fose/GameSettings.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>
#include <list>
#include "settings.h"
#define CALL_EAX(addr) __asm mov eax, addr __asm call eax
#define JMP_EAX(addr)  __asm mov eax, addr __asm jmp eax
#define JMP_EDX(addr)  __asm mov edx, addr __asm jmp edx
bool versionCheck(const FOSEInterface* fose);
void DeferredInit();
void DeferredUpdate();
TimeGlobal* timeGlobals = (TimeGlobal*)0x1090BA0;

HMODULE VOHandle;

PlayerCharacter* g_thePlayer = NULL;
DataHandler* g_dataHandler;
InterfaceManager* g_interfaceManager = NULL;
HUDMainMenu* hud;
TES* g_TES = NULL;
typedef void (*MainLoopAddCallbackEx)(void* cmdPtr, void* thisObj, UInt32 callCount, UInt32 callDelay);
bool __fastcall CheckMarkerWorldspace(TESWorldSpace* world) {
	MapMenu *g_mapMenu = *(MapMenu**)0x1076BB8;
	if (g_mapMenu && g_mapMenu->wspc10C && world && 
		( (world->parent && g_mapMenu->wspc10C->refID == world->parent->refID) || (g_mapMenu->wspc10C->refID == world->refID))) return true;
	return false;
}

__declspec(naked) void MarkerWorldspaceHook() {
	__asm {
		test al, al
		jz NO_MATCH
		mov ecx, esi
		call CheckMarkerWorldspace
		test al, al
		jz NO_MATCH
		mov [esp+0x14], esi
		JMP_EAX(0x65E144)
		NO_MATCH:
			JMP_EAX(0x65E144)
	}
}