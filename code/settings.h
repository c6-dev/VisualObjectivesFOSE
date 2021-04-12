#pragma once
#define INI_NAME "F3VisualObjectives.ini"

int measurementSystem = 0;
int visibleSighting = 0;
int visibleScoped = 0;
int showNameMode = 0;
int distanceTextMode = 0;
int minDistance = 0;
int maxDistance = 0;
int width = 0;
int height = 0;
extern HMODULE VOHandle;

void handleIniOptions()
{
	char iniPath[MAX_PATH];
	GetModuleFileNameA(VOHandle, iniPath, MAX_PATH);
	strcpy((strrchr(iniPath, '\\') + 1), INI_NAME);

	measurementSystem = GetPrivateProfileInt("Main", "iMeasurementSystem", 1, iniPath);
	visibleSighting = GetPrivateProfileInt("Main", "bVisibleWhenSighting", 1, iniPath);
	visibleScoped = GetPrivateProfileInt("Main", "bVisibleWhenScoped", 1, iniPath);
	showNameMode = GetPrivateProfileInt("Main", "iObjectiveNameMode", 1, iniPath);
	distanceTextMode = GetPrivateProfileInt("Main", "iDistanceTextMode", 2, iniPath);
	minDistance = GetPrivateProfileInt("Main", "iMinDisplayDistance", 0, iniPath);
	maxDistance = GetPrivateProfileInt("Main", "iMaxDisplayDistance", 0, iniPath);
	width = GetPrivateProfileInt("Main", "iVisualObjectiveWidth", 24, iniPath);
	height = GetPrivateProfileInt("Main", "iVisualObjectiveHeight", 36, iniPath);
}
