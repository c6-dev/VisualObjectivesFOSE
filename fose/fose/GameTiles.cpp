#include <string>
#include "GameTiles.h"
#include "Utilities.h"
#include "GameAPI.h"
#include <fose\fose\GameForms.h>

typedef UInt32 (* _TraitNameToID)(const char* traitName);

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE52B0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE9BE0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE9FA0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE9F10;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BEAA90;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BEA9F0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BEA9E0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE7A10;
#else
#error unsupported fallout version
#endif

UInt32 Tile::TraitNameToID(const char* traitName)
{
	return ::TraitNameToID(traitName);
}

Tile::Value* Tile::GetValue(UInt32 typeID)
{
	Value* value;
	for (BSSimpleArray<Value*>::Iterator iter(values); !iter.End(); ++iter)
	{
		value = *iter;
		if (!value || (value->id > typeID)) break;
		if (value->id == typeID) return value;
	}
	return NULL;
}

Tile::Value* Tile::GetValue(const char* valueName)
{
	UInt32 typeID = TraitNameToID(valueName);
	return GetValue(typeID);
}

std::string Tile::GetQualifiedName()
{
	std::string qualifiedName;
	//if (parent && !parent->GetFloatValue(kTileValue_class, &parentClass))	// i.e., parent is not a menu
	if (parent)
		qualifiedName = parent->GetQualifiedName() + "\\";

	qualifiedName += name.m_data;

	return qualifiedName;
}


void Tile::DestroyAllChildren()
{
	DListNode<Tile>* node = children.Tail();
	Tile* child;
	while (node)
	{
		child = node->data;
		node = node->prev;
		if (child) child->Destroy(true);
	}
}

Tile* Tile::GetChild(const char* childName)
{
	int childIndex = 0;
	char* colon = FindChr(childName, ':');
	if (colon)
	{
		if (colon == childName) return NULL;
		*colon = 0;
		childIndex = StrToInt(colon + 1);
	}
	Tile* result = NULL;
	for (DListNode<Tile>* node = children.Head(); node; node = node->next)
	{
		if (node->data && ((*childName == '*') || StrEqualCI(node->data->name.m_data, childName)) && !childIndex--)
		{
			result = node->data;
			break;
		}
	}
	if (colon)* colon = ':';
	return result;
}

Tile* Tile::GetComponent(const char* componentPath, const char*& trait)
{
	Tile* parentTile = this;
	char* slashPos;
	while (slashPos = SlashPos(componentPath))
	{
		*slashPos = 0;
		parentTile = parentTile->GetChild(componentPath);
		if (!parentTile) return NULL;
		componentPath = slashPos + 1;
	}
	if (*componentPath)
	{
		Tile* result = parentTile->GetChild(componentPath);
		if (result) return result;
		trait = componentPath;
	}
	return parentTile;
}

Tile::Value* Tile::GetComponentValue(const char* componentPath)
{
	const char* trait = NULL;
	Tile* tile = GetComponent(componentPath, trait);
	return (tile && trait) ? tile->GetValueName(trait) : NULL;
}

Tile* Tile::GetComponentTile(const char* componentPath)
{
	const char* trait = NULL;
	Tile* tile = GetComponent(componentPath, trait);
	return (tile && !trait) ? tile : NULL;
}

Tile::Value* Tile::GetValueName(const char* valueName)
{
	return GetValue(TraitNameToID(valueName));
}

Menu* Tile::GetParentMenu()
{
	Tile* tile = this;
	do
	{
		if (IS_TYPE(tile, TileMenu))
			return ((TileMenu*)tile)->menu;
	} while (tile = tile->parent);
	return NULL;
}