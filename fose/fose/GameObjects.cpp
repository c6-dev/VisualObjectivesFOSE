#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "GameTasks.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_7
static PlayerCharacter** g_thePlayer = (PlayerCharacter * *)0x0107A104;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
static PlayerCharacter** g_thePlayer = (PlayerCharacter * *)0x01077104;
#else
#error unsupported fallout version
#endif

PlayerCharacter* PlayerCharacter::GetSingleton()
{
	return *g_thePlayer;
}


ScriptEventList* TESObjectREFR::GetEventList() const
{
	BSExtraData* xData = extraDataList.GetByType(kExtraData_Script);
	if (xData)
	{
		ExtraScript* xScript = DYNAMIC_CAST(xData, BSExtraData, ExtraScript);
		if (xScript)
			return xScript->eventList;
	}

	return 0;
}

static ModelLoader** g_modelLoader = (ModelLoader**)0x106CA70;

void TESObjectREFR::Update3D()
{
	if (this == *g_thePlayer)
		ThisCall(kUpdateAppearanceAddr, this);
	else
	{
		Set3D(NULL, true);
		(*g_modelLoader)->QueueReference(this, 1, 0);
	}
}

__declspec(naked) TESContainer *TESObjectREFR::GetContainer()
{
	__asm
	{
		mov		eax, [ecx]
		mov		eax, [eax+0x100] // isActor
		call	eax
		test	al, al
		mov		eax, [ecx+0x1C] // baseForm
		jz		notActor
		add		eax, 0x64
		retn
	notActor:
		cmp		dword ptr [eax], kVtbl_TESObjectCONT
		jnz		notCONT
		add		eax, 0x30
		retn
	notCONT:
		xor		eax, eax
		retn
	}
}