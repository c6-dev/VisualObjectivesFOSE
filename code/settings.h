#pragma once
#define INI_NAME "F3VisualObjectives.ini"

int measurementSystem = 0;
extern HMODULE VOHandle;

void handleIniOptions()
{
	char iniPath[MAX_PATH];
	GetModuleFileNameA(VOHandle, iniPath, MAX_PATH);
	strcpy((strrchr(iniPath, '\\') + 1), INI_NAME);

	/*JLMItems = min(10, GetPrivateProfileInt("Main", "iNumDisplayedItems", 5, iniPath));
	JLMHidePrompt = GetPrivateProfileInt("Main", "bHidePrompt", 1, iniPath);
	JLMWeightVisible = GetPrivateProfileInt("Main", "bShowCarryWeight", 1, iniPath);
	JLMReloadKeyActivates = GetPrivateProfileInt("Main", "bReloadKeyActivates", 1, iniPath);
	JLMFont = GetPrivateProfileInt("Main", "iFont", 3, iniPath);
	JLMHeightMin = GetPrivateProfileInt("Main", "iHeightMin", 32, iniPath);
	JLMHeightMax = GetPrivateProfileInt("Main", "iHeightMax", 640, iniPath);
	JLMWidthMin = GetPrivateProfileInt("Main", "iWidthMin", 400, iniPath); 
	JLMWidthMax = GetPrivateProfileInt("Main", "iWidthMax", 640, iniPath);
	JLMOffsetX = GetPrivateProfileInt("Main", "iOffsetX", 60, iniPath) / 100.0F;
	JLMOffsetY = GetPrivateProfileInt("Main", "iOffsetY", 50, iniPath) / 100.0F;
	JLMItemIndent = GetPrivateProfileInt("Main", "iItemIndent", 8, iniPath);
	JLMIndentTextX = GetPrivateProfileInt("Main", "iIndentTextX", 10, iniPath);
	JLMIndentTextY = GetPrivateProfileInt("Main", "iIndentTextY", 10, iniPath);
	JLMTextAdjust = GetPrivateProfileInt("Main", "iTextAdjust", 8, iniPath);
	JLMJustifyX = GetPrivateProfileInt("Main", "iJustifyX", 0, iniPath);
	JLMJustifyY = GetPrivateProfileInt("Main", "iJustifyY", 1, iniPath);*/
	measurementSystem = GetPrivateProfileInt("Main", "iMeasurementSystem", 1, iniPath);
}
