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