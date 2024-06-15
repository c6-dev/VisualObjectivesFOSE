#pragma once

#define GetShouldAttack(a, b, result)  CdeclCall<bool>(0x50FF60, (Actor*)a, (Actor*)b, 0, &result)
#define GetInFaction(a, b) ThisCall<bool>(0x6F8FF0, (Actor*)a, b)
#define GetQuestObjectives() ThisCall<tList<BGSQuestObjective::Target>*>(0x76CF30, g_thePlayer);
#define PlayerFaction 0x1B2A4
#define PlayerRef 0x7
#define VATSCameraMode *(UInt32*)0x108D0A0
namespace VisualObjectives
{
	bool Init();
	void Update();
	void SetDistanceText(Tile* tile, TESObjectREFR* ref, float distance);
	Tile* mainTile = nullptr;
	Tile* playerMarkerTile = nullptr;
	Tile* compassTile = nullptr;
	Tile* hudMenuTile = nullptr;
	Tile* jvoRect = nullptr;
	bool JVOVisible = false;
	bool initialized = false;
	int objectiveIndex = 0;
	int lastIndex = 0;
	char distanceText[50];
	char tileName[20];

	bool InjectMenuXML(Menu* menu)
	{
		if (menu == nullptr || menu->tile == nullptr) return false;
		hudMenuTile = menu->tile;
		mainTile = hudMenuTile->ReadXML("data\\menus\\prefabs\\JVO\\JVO.xml");
		return mainTile != nullptr;
	}

	float GetObjectDimensions(TESObjectREFR* ref, int axis) {	
		if (ref->IsActor())
		{
			Actor* actor = (Actor*)ref;
			if (actor->baseProcess && (actor->baseProcess->processLevel <= 1))
			{
				BSBound* bounds = ((MiddleHighProcess*)actor->baseProcess)->boundingBox;
				if (bounds) return (bounds->dimensions[axis] * 2 * ref->scale);
			}
		}
		else {
			TESBoundObject* object = DYNAMIC_CAST(ref->baseForm, TESForm, TESBoundObject);
			if (!object) return 0.0;
			return abs(object->bounds[axis + 3] - object->bounds[axis]) * ref->scale;
		}
		return 0.0;
	}

	bool Init() {
		if (!InjectMenuXML(hud))
		{
			MessageBoxA(nullptr, "Visual Objectives failed to initialize", "F3VisualObjectives", MB_ICONERROR);
			return false;
		}
		playerMarkerTile = mainTile->GetChild("JVOPlayerMarker");
		Tile* hpWrap = hudMenuTile->GetChild("HP_Wrap");
		Tile* hitPoints;
		if (hpWrap != nullptr) {
			hitPoints = hpWrap->GetChild("HitPoints");
		}
		else {
			hitPoints = hudMenuTile->GetChild("HitPoints");
		}
		compassTile = hitPoints->GetChild("compass_window");
		jvoRect = hud->AddTileFromTemplate(mainTile, "JVOTemp", 0); 
		SetTileComponentValue(mainTile, "_JVOWidthBase", width);
		SetTileComponentValue(mainTile, "_JVOHeightBase", height);
		SetTileComponentValue(mainTile, "_JVODistanceVisible", distanceTextMode);
		SetTileComponentValue(mainTile, "_JVOTextVisible", showNameMode);
		SetTileComponentValue(mainTile, "_JVOAlphaMult", alpha);
		initialized = true;
		return true;
	}
	void SetDistanceText(Tile* tile, TESObjectREFR* ref, float distance) {
		float inFocus = tile->GetComponentValue("_JVOInFocus")->num;
		if (inFocus + distanceTextMode > 1) {
			if (distance > 1000000) {
				strcpy(distanceText, "Far away");
			}
			else if (measurementSystem == 1) {
				sprintf(distanceText, "%.f m.", distance / 69.99104);
			}
			else if (measurementSystem == 2) {
				sprintf(distanceText, "%.f ft.", distance / 21.333);
			}
			else if (measurementSystem == 3) {
				sprintf(distanceText, "%.f un.", distance);
			}
		}
		SetTileComponentValue(tile, "_JVODistance", distanceText);
	}

	bool GetIsHostileColor(TESObjectREFR* ref) {

		double shouldAttack = 0;
		if (ref->baseForm->typeID == kFormType_Door) {
			ExtraLock* xLock = (ExtraLock*)ref->extraDataList.GetByType(kExtraData_Lock);
			if (!xLock || ((xLock->data->flags & 1) == 0)) return false;
		}
		if (ref->IsActor()) {
			Actor* actor = (Actor*)ref;
			if ((!actor->GetDead() && g_thePlayer->IsSneaking() && !ref->IsCreature())
			|| ((GetShouldAttack(ref, g_thePlayer, shouldAttack) && shouldAttack > 0) || actor->IsInCombatWith(g_thePlayer))
			|| (IsFactionEnemy(actor, g_thePlayer) || IsFactionEnemy(g_thePlayer, actor))) {
				return true;
			}
		}

		else if (ref->baseForm->typeID >= 0x15 && ref->baseForm->typeID < 0x29) {

			TESForm* owner = nullptr;
			ExtraOwnership* xOwn = (ExtraOwnership*)ref->extraDataList.GetByType(kExtraData_Ownership);
			if (xOwn) owner = xOwn->owner;
			if (!owner && ref->parentCell && ref->parentCell->IsInterior()) {
				xOwn = (ExtraOwnership*)ref->parentCell->extraDataList.GetByType(kExtraData_Ownership);
				if (xOwn) owner = xOwn->owner;
			}
			if (owner) {
				if ((owner->refID != PlayerFaction && owner->refID != PlayerRef) || (owner->typeID == kFormType_Faction && !GetInFaction(g_thePlayer, owner))) {
					return true;
				}
			}	
		}

		return false;
	}

	void AddVisualObjective(TESObjectREFR* ref) {

		sprintf(tileName, "JVOMarker%i", objectiveIndex);
		Tile* objectiveTile = jvoRect->GetChild(tileName);
		if (objectiveTile == nullptr) {
			objectiveTile = hud->AddTileFromTemplate(jvoRect, "JVOMarker", 0);
			objectiveTile->name.Set(tileName);
		}

		float distance = g_thePlayer->GetDistance(ref);
		int inDistance = (((minDistance == 0 || minDistance <= distance) && (maxDistance == 0 || maxDistance >= distance)) ? 1 : 0);
		SetTileComponentValue(objectiveTile, "_JVOInDistance", inDistance);
		objectiveTile->SetFloat(kTileValue_visible, inDistance);
		float dX = 0, dY = 0, dZ = 0;
		if (ref->IsActor()) {
			NiAVObject* niBlock = ref->GetNiBlock("Bip01 Head");
			if (niBlock && &niBlock->m_worldTranslate) {
				NiVector3& transltn = niBlock->m_worldTranslate;
				NiPoint3* pos = ref->GetPos();
				dX = transltn.x - pos->x;
				dY = transltn.y - pos->y;
				dZ = transltn.z - pos->z + 20;
			}
		}
		else {
			dX = 0;
			dY = 0;
			dZ = 0.5 * GetObjectDimensions(ref, 2) + 10;
		}

		NiPoint3 pos(ref->posX + dX, ref->posY + dY, ref->posZ + dZ);
		float x, y, z;
		bool isOnScreen = WorldToScreen(&pos, x, y, z, 2);
		if (!isOnScreen) {
			x = -1;
			y = -1;
		}

		SetTileComponentValue(objectiveTile, "_X", x);
		SetTileComponentValue(objectiveTile, "_Y", y);
		SetDistanceText(objectiveTile, ref, distance);
		SetTileComponentValue(objectiveTile, "_JVOText", ref->GetTheName());
		SetTileComponentValue(objectiveTile, "_JVOHostile", GetIsHostileColor(ref) ? 1 : 0);
		objectiveIndex++;

	}
	void AddCustomObjective(TESObjectREFR* customMarker) {
		float deltaZ = 0.0;

		if (!customMarker->GetNiNode()) {
			NiPoint3* pos = customMarker->GetPos();
			float posXY[2] = { pos->x, pos->y }; 
			g_TES->GetTerrainHeight(posXY, &deltaZ);
			if (deltaZ <= 0.0) deltaZ = g_thePlayer->GetPos()->z;
		}
		else {
			deltaZ = 0.5 * GetObjectDimensions(customMarker, 2) + 10;
		}

		NiPoint3 w2s(customMarker->posX, customMarker->posY, customMarker->posZ + deltaZ);
		float x, y, z;
		bool isOnScreen = WorldToScreen(&w2s, x, y, z, 2);
		if (!isOnScreen) {
			x = -1;
			y = -1;
		}

		SetTileComponentValue(playerMarkerTile, "_X", x);
		SetTileComponentValue(playerMarkerTile, "_Y", y);

		float distance = GetDistance2D(g_thePlayer, customMarker);
		int inDistance = (((minDistance == 0 || minDistance <= distance) && (maxDistance == 0 || maxDistance >= distance)) ? 1 : 0);
		SetTileComponentValue(playerMarkerTile, "_JVOInDistance", inDistance);
		playerMarkerTile->SetFloat(kTileValue_visible, inDistance);
		SetDistanceText(playerMarkerTile, customMarker, distance);
	}
	void Update() {
		SetTileComponentValue(mainTile, "_JVOInCombat", g_thePlayer->pcInCombat ? 1 : 0);
		SetTileComponentValue(mainTile, "_JVOAlphaCW", compassTile->GetValueFloat(kTileValue_alpha));

		TESObjectREFR* customMarker = g_thePlayer->unk66C ? *(g_thePlayer->unk668) : g_thePlayer->unk650;
		if (customMarker) {
			AddCustomObjective(customMarker);
		}
		else {
			playerMarkerTile->SetFloat(kTileValue_visible, 0);
		}

		tList <BGSQuestObjective::Target>* targets = GetQuestObjectives();

		if (targets != nullptr && !targets->Empty())
		{
			for (tList<BGSQuestObjective::Target>::Iterator iter = targets->Begin(); !iter.End(); ++iter)
			{
				BGSQuestObjective::Target* data = iter.Get();
				if (data)
				{
					BGSQuestObjective::Target::Data* objective = &data->data;
					if (objective->teleportLinks.size == 0) {
						AddVisualObjective(data->target);
					}
					else {
						AddVisualObjective(objective->teleportLinks.data[0].door);
					}
				}
			}
		}

		int i = targets == nullptr ? 0 : targets->Count();
		int j = jvoRect->children.Size();
		if (j > i) {
			for (j; j > i; j--) {
				auto child = jvoRect->GetNthChild(j - 1);
				if (child && child->data) {
					child->data->SetFloat(kTileValue_visible, 0);
				}
			}
		}

		objectiveIndex = 0;
	}
}

void __fastcall VOUpdate(void* a1)
{
	
	if (VisualObjectives::initialized) VisualObjectives::Update();
	return ThisCall<void>(0x61E380, a1);
}