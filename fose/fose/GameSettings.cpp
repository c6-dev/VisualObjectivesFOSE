#include "GameTypes.h"
#include "GameSettings.h"
#include "utility.h"

	GameSettingCollection ** g_GameSettingCollection = (GameSettingCollection**)0x010701A8;
	IniSettingCollection ** g_IniSettingCollection = (IniSettingCollection**)0x0116D6F4;
	IniSettingCollection ** g_IniPrefCollection = (IniSettingCollection**)0x01179578;
	IniSettingCollection** g_INIBlendSettingCollection = (IniSettingCollection * *)0x1072B18;
	IniSettingCollection** g_INIRendererSettingCollection = (IniSettingCollection * *)0x117957C;

UInt32 Setting::GetType()
{
	if (name)
	{
		switch (*name | 0x20)
		{
		case 'b': return kSetting_Bool;
		case 'c': return kSetting_c;
		case 'i': return kSetting_Integer;
		case 'u': return kSetting_Unsigned;
		case 'f': return kSetting_Float;
		case 's':
			return kSetting_String;
		case 'r': return kSetting_r;
		case 'a': return kSetting_a;
		default:
			break;
		}
	}
	return kSetting_Other;
}

bool Setting::Get(double& out)
{
	switch (GetType())
	{
	case kSetting_Bool:
	case kSetting_Integer:
		out = data.i;
		return true;
	case kSetting_Unsigned:
		out = data.uint;
		return true;
	case kSetting_Float:
		out = data.f;
		return true;
	default:
		return false;
	}
}

bool Setting::Set(double newVal)
{
	switch (GetType())
	{
	case kSetting_Bool:
		data.i = newVal ? 1 : 0;
		return true;
	case kSetting_Integer:
		data.i = newVal;
		return true;
	case kSetting_Unsigned:
		data.uint = newVal;
		return true;
	case kSetting_Float:
		data.f = newVal;
		return true;
	default:
		return false;
	}
}

void Setting::Set(const char* strVal, bool doFree)
{
	if (doFree) GameHeapFree(data.str);
	data.str = (char*)GameHeapAlloc(StrLen(strVal) + 1);
	StrCopy(data.str, strVal);
}

bool Setting::ValidType()
{
	switch (*name | 0x20)
	{
	case 'b':
	case 'f':
	case 'i':
	case 's':
	case 'u':
		return true;
	default:
		return false;
	}
}

__declspec(naked) bool GameSettingCollection::GetGameSetting(const char* settingName, Setting** out)
{
	__asm
	{
		add		ecx, 0x10C
		jmp		kNiTMapLookupAddr
	}
}

GameSettingCollection * GameSettingCollection::GetSingleton()
{
	return *g_GameSettingCollection;
}

IniSettingCollection* IniSettingCollection::GetIniSettings()
{
	return *g_IniSettingCollection;
}

IniSettingCollection* IniSettingCollection::GetIniPrefs()
{
	return *g_IniPrefCollection;
}

IniSettingCollection* IniSettingCollection::GetIniRendererSettings()
{
	return *g_INIRendererSettingCollection;
}

IniSettingCollection* IniSettingCollection::GetIniBlendSettings()
{
	return *g_INIBlendSettingCollection;
}

class IniSettingFinder
{
public:
	const char* m_settingName;
	IniSettingFinder(const char* name) : m_settingName(name)
		{	}
	bool Accept(Setting* info)
	{
		if (!_stricmp(m_settingName, info->name))
			return true;
		else
			return false;
	}
};

bool GetIniSetting(const char* settingName, Setting** out)
{
	Setting* setting = NULL;
	IniSettingFinder finder(settingName);

	// check prefs first
	IniSettingCollection* coll = IniSettingCollection::GetIniPrefs();
	if (coll)
		setting = coll->settings.Find(finder);

	if (!setting)
	{
		coll = IniSettingCollection::GetIniSettings();
		setting = coll->settings.Find(finder);
	}

	if (setting)
	{
		*out = setting;
		return true;
	}

	return false;
}
