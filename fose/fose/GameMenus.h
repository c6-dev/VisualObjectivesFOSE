#pragma once

#include "GameTiles.h"

enum MenuSpecialKeyboardInputCode
{
	kEnter_2 = -2,
	kUpArrow = 0x1,
	kDownArrow = 0x2,
	kRightArrow = 0x3,
	kLeftArrow = 0x4,
	kSpace = 0x9,
	kTab = 0xA,
	kShiftEnter = 0xB,
	kEnter_1 = 0xC,
	kShiftLeft = 0xD,
	kShiftRight = 0xE,
	kPageUp = 0xF,
	kPageDown = 0x10,
};

class TileExtra;
// 28
class Menu
{
public:
	Menu();
	~Menu();

	virtual void	Destructor(bool doFree);
	virtual void	SetTile(UInt32 idx, Tile* value); // can be used to determine how many Tile*s are in a Menu class
	virtual void	HandleLeftClickPress(UInt32 tileID, Tile* activeTile); // called when the mouse has moved and left click is pressed
	virtual void	HandleClick(SInt32 tileID, Tile* clickedTile);
	virtual void	HandleMouseover(UInt32 arg0, Tile* activeTile);	//	Called on mouseover, activeTile is moused-over Tile
	virtual void	HandleMouseoverTileAlt(UInt32 arg0, Tile* tile);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);  // unused?
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2); // unused?
	virtual void	HandleActiveMenuClick(UInt32 tileID, Tile* activeTile); // StartMenu, RaceSexMenu, VATSMenu, BookMenu
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1); // unused?
	virtual void	HandleMousewheel(UInt32 tileID, Tile* tile);
	virtual void	Update(void);	// Called every frame while the menu is active
	virtual bool	HandleKeyboardInput(UInt32 inputChar);	// Return false for handling keyboard shortcuts
	virtual UInt32	GetID(void);
	virtual bool	HandleSpecialKeyInput(MenuSpecialKeyboardInputCode code, UInt32 arg1);
	virtual bool	HandleControllerInput(int a2, Tile* tile);
	virtual void	Unk_10(void); // unused?
	virtual void	HandleControllerConnectOrDisconnect(bool isControllerConnected);

	// 14
	struct TemplateInstance
	{
		UInt32		unk00;		// 00
		float		flt04;		// 04
		String		tileName;	// 08
		Tile* tile;		// 10
	};

	// 14
	struct TemplateData
	{
		const char* templateName;	// 00
		TileExtra* tileExtra;		// 04
		DList<TemplateInstance>	instances;		// 08
	};

	TileMenu* tile;			// 04
	tList<TemplateData>	menuTemplates;	// 08
	UInt32				unk10;			// 10
	UInt32				unk14;			// 14	Same as id (20)
	UInt32				unk18;			// 18
	UInt8				byte1C;			// 1C
	UInt8				byte1D;			// 1D
	UInt8				byte1E;			// 1E
	UInt8				byte1F;			// 1F
	UInt32				id;				// 20
	UInt32				visibilityState;// 24 :: Initialised to 4
	// check 1 at 0xA0B174, 0x70D529, 0x70D592 :: set at 0x712224
	// check 2 at 0x711FF1 :: set 2 at 0xA1D987 (when closes menu), 0xA1DA41
	// check 4 at 0xA1D9EC (when closing menu) :: set at 0x7036A4, 0x71204D
	// check 8 at 0x712194 :: set 8 at 0xA1DB8F (when opening menu), 0x720B39

	Tile* AddTileFromTemplate(Tile* destTile, const char* templateName, UInt32 arg3);
};


template <typename Item> struct ListBoxItem
{
	Tile* tile;
	Item* object;
};

// 30
template <typename Item> class ListBox : public BSSimpleList<ListBoxItem<Item>>
{
public:
	Tile* parentTile;	// 0C
	Tile* selected;		// 10
	Tile* scrollBar;		// 14
	const char* templateName;	// 18
	UInt16			itemCount;		// 1C
	UInt16			pad1E;			// 1E
	float			unk20[3];		// 20
	UInt16			unk2C;			// 2C
	UInt16			pad2E;			// 2E

	Item* GetSelected()
	{
		ListNode<ListBoxItem<Item>>* iter = list.Head();
		ListBoxItem<Item>* item;
		do
		{
			item = iter->data;
			if (item && (item->tile == selected))
				return item->object;
		} while (iter = iter->next);
		return NULL;
	}

	Tile* GetNthTile(SInt32 index)
	{
		if (index >= 0)
		{
			ListNode<ListBoxItem<Item>>* iter = list.Head();
			ListBoxItem<Item>* item;

			do
			{
				if (!index)
				{
					return iter->data ? iter->data->tile : NULL;
				}
				index--;
			} while (iter = iter->next);
		}
		return NULL;
	}

	void Clear()
	{
		ListNode<ListBoxItem<Item>>* iter = list.Head();
		ListBoxItem<Item>* item;
		do
		{
			item = iter->data;
			if (!item) continue;
			if (item->tile)
				item->tile->Destroy(true);
			GameHeapFree(item);
		} while (iter = iter->next);
		list.RemoveAll();
		selected = NULL;
		itemCount = 0;
	}

	void Filter(bool(__cdecl* callback)(Item*))
	{
		ThisCall(0x729FE0, this, callback);
	}

	// Identical to Filter, but passing a value instead of a pointer
	void FilterVal(bool(__cdecl* callback)(Item))
	{
		ThisCall(0x633AF0, this, callback);
	}

	void ForEach(void(__cdecl* func)(void*, int), int maxIndex1 = -1, int maxIndex2 = 0x7FFFFFFF)
	{
		ThisCall(0x655800, this, func, maxIndex1, maxIndex2);
	}

	Tile* GetTileFromItem(Item** item)
	{
		return ThisCall<Tile*>(0x67C040, this, item);
	}
};
STATIC_ASSERT(sizeof(ListBox<UInt32>) == 0x30);

// 100
class InventoryMenu : public Menu
{
public:
	InventoryMenu();
	~InventoryMenu();

	// TODO: investigate these structs

	struct ItemInfo {
		void	* unk00;		// points to some struct which sometimes contains pointers to
								// ExtraDataList, Tile::Value
		UInt32	itemCount;
		TESForm	* item;
	};

	struct ItemChange {
		TileImage	* button;
		ItemInfo	* itemInfo;
		UInt32		unk08;		// only seen 1. Possibly bool for whether item is visible or not
	};

	TileRect		* caps;				// 28
	TileRect		* hitpoints;		// 2C
	TileRect		* damageRating;		// 30
	TileRect		* weight;			// 34
	TileImage		* inventoryList;	// 38
	TileRect		* hotkeyWheel;		// 3C
	TileImage		* equipButton;		// 40
	TileImage		* dropButton;		// 44
	TileImage		* repairButton;		// 48
	TileImage		* hotkeyButton;		// 4C
	TileImage		* cancelButton;		// 50
	TileImage		* itemIcon;			// 54
	TileRect		* itemInfo;			// 58
	TileRect		* tabLine;			// 5C
	UInt32			unk60[0x0D];		// 60 seen alternating sequence of (0, -1, 0, ...)
	ListBox<ItemChange>	items;			// 94 ListBox<ItemChange>
	TileRect		* hotkeyWheel_2;	// C4 again?
	TileRect		* hotkeyItems[8];	// C8
	UInt32			unkE8;				// E8
	UInt32			unkEC;				// EC
	UInt32			unkF0;				// F0
	UInt32			unkF4;				// F4
	UInt32			unkF8;				// F8
	UInt32			unkFC;				// FC
};

STATIC_ASSERT(sizeof(InventoryMenu) == 0x100);

// 6C
class MessageMenu : public Menu
{
public:
	MessageMenu();
	~MessageMenu();

	struct ButtonInfo {
		TileImage	* button;
		UInt32		index;
		// possibly one more, if so only seen zero
	};

	TileRect			* mainRect;		// 28
	TileText			* title;		// 2C
	TileImage			* icon;			// 30
	TileText			* text;			// 34
	TileImage			* buttonList;	// 38
	ListBox<ButtonInfo>	buttons;		// 40
};

STATIC_ASSERT(sizeof(MessageMenu) == 0x6C);

enum {
	kMenuType_Audio                 =	0x000003F9,
	kMenuType_Book                  =	0x00000402,
	kMenuType_CharGen               =	0x00000418,
	kMenuType_Container             =	0x000003F0,
	kMenuType_Dialog                =	0x000003F1,
	kMenuType_Gameplay              =	0x000003FC,
	kMenuType_HUDMain               =	0x000003EC,
	kMenuType_Inventory             =	0x000003EA,
	kMenuType_Loading               =	0x000003EF,
	kMenuType_LockPick              =	0x000003F6,
	kMenuType_Map                   =	0x000003FF,
	kMenuType_Message               =	0x000003E9,
	kMenuType_Tutorial              =	0x00000423,
	kMenuType_TextEdit              =	0x0000041B,
	kMenuType_Start                 =	0x000003F5,
	kMenuType_Quantity              =	0x000003F8,
	kMenuType_RaceSex               =	0x0000040C,
	kMenuType_SleepWait             =	0x000003F4,
	kMenuType_Stats                 =	0x000003EB,
	kMenuType_Video                 =	0x000003FA,
	kMenuType_LevelUp               =	0x00000403,
	kMenuType_Repair                =	0x0000040B,
	kMenuType_RepairServices        =	0x00000422,
	kMenuType_Credits               =	0x00000417,
	kMenuType_Barter                =	0x0000041D,
	kMenuType_Surgery               =	0x0000041E,
	kMenuType_Hacking               =	0x0000041F,
	kMenuType_Computers             =	0x00000421,
	kMenuType_VATS                  =	0x00000420,
	kMenuType_SPECIALBook           =	0x00000424,

	kMenuType_Min = kMenuType_Message,
	kMenuType_Max = kMenuType_SPECIALBook
};
