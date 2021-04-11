#pragma once

#include "internal/containers.h"
#include "GameForms.h"
#include "GameBSExtraData.h"
#include <GameProcess.h>
#include "GameExtraData.h"

static const UInt32 kTESObjectREFR_IsOffLimitsToPlayerAddr = 0x004DEBF0;
static const UInt32 kUpdateAppearanceAddr = 0x729880;

class HighProcess;
class bhkRagdollController;
class bhkRagdollPenetrationUtil;

class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;
class NiNode;

class TESObjectCELL;

class bhkRagdollController;
class bhkRagdollPenetrationUtil;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;

class PathingRequest;
class PathingSolution;
class DetailedActorPathHandler;
class ActorPathingMessageQueue;
struct NiPoint3;
// 28
class PathingLocation
{
public:
	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);

	UInt32			unk04[9];	// 04
};

class ActorMover
{
public:
	ActorMover();
	~ActorMover();

	virtual void		Destructor(bool doFree);
	virtual void		SetMovementFlags(UInt32 flags);
	virtual void		UnsetMovementFlags(UInt32 flags);
	virtual void		Unk_03(void);
	virtual void		Unk_04(void);
	virtual void		Unk_05(void);
	virtual void		Unk_06(void);
	virtual UInt32		GetMovementFlags(void);

	UInt32						unk04[6];			// 04
	PathingRequest* pathingRequest;	// 1C
	PathingSolution* pathingSolution;	// 20
	DetailedActorPathHandler* pathHandler;		// 24
	Actor* actor;				// 28
	UInt32						unk2C;				// 2C
	ActorPathingMessageQueue* pathingMsgQueue;	// 30
	UInt32						movementFlags1;		// 34
	UInt32						unk38;				// 38
	UInt32						movementFlags2;		// 3C
	UInt32						unk40;				// 40
	PathingLocation				pathingLocation;	// 44
	UInt32						unk6C;				// 6C
	UInt8						unk70[4];			// 70
	UInt32						unk74;				// 74
	UInt32						unk78;				// 78
	UInt32						unk7C;				// 7C
	UInt32						unk80;				// 80
	UInt32						unk84;				// 84
};

class PlayerMover : public ActorMover
{
public:
	PlayerMover();
	~PlayerMover();

	float			point88[3];			// 88
	UInt32			pcMovementFlags;	// 94
	UInt32			unk98;				// 98
	UInt32			unk9C;				// 9C
};

// 004?
class TESChildCell
{
public:
	TESChildCell();
	~TESChildCell();

	// no virtual destructor
	virtual TESObjectCELL *	GetChildCell(void);
};

struct InventoryItemData
{
	SInt32				count;
	ContChangesEntry* entry;

	InventoryItemData(SInt32 _count, ContChangesEntry* _entry) : count(_count), entry(_entry) {}
	InventoryItemData() {}
};

typedef UnorderedMap<TESForm*, InventoryItemData> InventoryItemsMap;
typedef Vector<InventoryItemData> InventoryItemsVec;
class NiAVObject;
class TESObjectREFR : public TESForm
{
public:
	MEMBER_FN_PREFIX(TESObjectREFR);
	DEFINE_MEMBER_FN(IsOffLimitsToPlayer, bool, kTESObjectREFR_IsOffLimitsToPlayerAddr);

	TESObjectREFR();
	~TESObjectREFR();

	virtual void		Unk_4E(void);	// GetStartingPosition(Position, Rotation, WorldOrCell)
	virtual void		Unk_4F(void);
	virtual void		Unk_50(void);
	virtual void		Unk_51(void);
	virtual bool		CastShadows();
	virtual void		Unk_53(void);
	virtual void		Unk_54(void);
	virtual void		Unk_55(void);
	virtual void		Unk_56(void);
	virtual bool		IsObstacle();
	virtual void		Unk_58(void);
	virtual void		Unk_59(void);
	virtual void		Unk_5A(void);
	virtual void		Unk_5B(void);
	virtual void		Unk_5C(void);
	virtual void		Unk_5D(void);
	virtual void		Unk_5E(void);
	virtual TESObjectREFR* RemoveItem(TESForm* toRemove, BaseExtraList* extraList, UInt32 quantity, bool keepOwner, bool drop, TESObjectREFR* destRef,
		UInt32 unk6, UInt32 unk7, bool unk8, bool unk9);
	virtual void		Unk_60(void);
	virtual bool		EquipObject(TESForm* item, UInt32 count, ExtraDataList* xData, bool lockEquip);
	virtual void		Unk_62(void);
	virtual void		Unk_63(void);
	virtual void		AddItem(TESForm* item, ExtraDataList* xDataList, UInt32 quantity);
	virtual void		Unk_65(void);
	virtual void		Unk_66(void);
	virtual void		Unk_67(void);					// Actor: GetMagicEffectList
	virtual bool		GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual UInt32		GetActorUnk0148();			// result can be interchanged with baseForm, so TESForm* ?
	virtual void		SetActorUnk0148(UInt32 arg0);
	virtual void		Unk_6B(void);
	virtual void		Unk_6C(void);	// REFR: GetBSFaceGenNiNodeSkinned
	virtual void		Unk_6D(void);	// REFR: calls 006C
	virtual void		Unk_6E(void);	// MobileActor: calls 006D then NiNode::Func0040
	virtual void		Unk_6F(void);
	virtual bool		Unload3D();
	virtual void		AnimateNiNode();
	virtual void		GenerateNiNode(bool arg1);
	virtual void		Set3D(NiNode* niNode, bool unloadArt);
	virtual NiNode* GetNiNode();
	virtual void		Unk_75(void);
	virtual void		Unk_76(void);
	virtual void		Unk_77(void);
	virtual void		Unk_78(void);
	virtual void* GetAnimData();			// 0079
	virtual void* GetValidBip01Names(void);	// 007A	Character only
	virtual void* CallGetValidBip01Names(void);
	virtual void		SetValidBip01Names(void* validBip01Names);
	virtual NiPoint3*	GetPos();				// GetPos or GetDistance
	virtual void		Unk_7E(UInt32 arg0);
	virtual void		Unk_7F(void);
	virtual void		Unk_80(UInt32 arg0);
	virtual void		Unk_81(UInt32 arg0);
	virtual void		Unk_82(void);
	virtual UInt32		Unk_83(void);
	virtual void		Unk_84(UInt32 arg0);
	virtual UInt32		Unk_85(void);
	virtual bool		IsCharacter();			// return false for Actor and Creature, true for character and PlayerCharacter
	virtual bool		IsCreature();
	virtual bool		IsExplosion();
	virtual bool		IsProjectile();
	virtual void		Unk_8A(void);			// SetParentCell (Interior only ?)
	virtual bool		IsDying(bool arg0);	// HasHealth (baseForm health > 0 or Flags bit23 set)
	virtual bool		Unk_8C(void);
	virtual bool		Unk_8D(void);
	virtual void		Unk_8E(void);
	virtual void		Unk_8F(void);

	enum {
		kFlags_Taken		= 0x00000022,		// 2 bits TODO: which bit does what?
		kFlags_Persistent	= 0x00000400,		//shared bit with kFormFlags_QuestItem
	};

	TESChildCell	childCell;				// 018
	TESForm*		baseForm;				// 01C
	
	float			rotX, rotY, rotZ;		// 020 - either public or accessed via simple inline accessor common to all child classes
	float			posX, posY, posZ;		// 02C - seems to be private
	float			scale;					// 038 

	TESObjectCELL*	parentCell;				// 03C
	ExtraDataList	extraDataList;			// 040
	// 054 ?

	ScriptEventList* GetEventList() const;

	bool IsTaken() const {  return ((flags & kFlags_Taken) == kFlags_Taken) ? true : false; } // Need to implement
	bool IsPersistent() const { return ((flags & kFlags_Persistent) == kFlags_Persistent) ? true : false; }
	void Update3D();
	float GetWaterImmersionPerc();
	void GetInventoryItems(InventoryItemsMap* map);
	TESContainer* GetContainer();
	ExtraContainerChanges::EntryDataList* GetContainerChangesList();
	SInt32 GetItemCount(TESForm* form);
	void RemoveItemTarget(TESForm* itemForm, TESObjectREFR* target, SInt32 quantity, bool keepOwner);
	ContChangesEntry* GetContainerChangesEntry(TESForm* itemForm);
	TESObjectREFR* ResolveAshpile();
	ExtraLock::Data* GetLockData();
	bool HasOpenCloseActivateScriptBlocks();
	void DisableScriptedActivate(bool disable);
	bool Activate(Actor* activator, char a2, int a3, int a4) { return ThisCall<bool>(0x4EE000, this, activator, a2, a3, a4); };
	void PlayGroup(const char* name);
	void RemoveOwnership();
	TESObjectCELL* GetParentCell();
	TESWorldSpace* GetParentWorld();
	bool __fastcall GetInSameCellOrWorld(TESObjectREFR* target);
	float __vectorcall GetDistance(TESObjectREFR* target);
	NiAVObject* GetNiBlock(const char* blockName);
	NiNode* GetNode(const char* nodeName);
};

STATIC_ASSERT(offsetof(TESObjectREFR, baseForm) == 0x01C);
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x054);

// 080
class MobileObject : public TESObjectREFR
{
public:
	MobileObject();
	~MobileObject();

	virtual void		Unk_91(void);
	virtual void		Unk_92(void);
	virtual void		Unk_93(void);
	virtual void		Jump(void);
	virtual void		Unk_95(void);
	virtual void		Unk_96(void);
	virtual void		Unk_97(void);
	virtual void		Unk_98(void);
	virtual void		Unk_99(void);
	virtual void		Unk_9A(void);
	virtual void		Unk_9B(void);
	virtual void		Unk_9C(void);
	virtual void		Unk_9D(void);
	virtual void		Unk_9E(void);
	virtual void		Unk_9F(void);
	virtual void		Unk_A0(void);
	virtual void		Unk_A1(void);
	virtual void		Unk_A2(void);
	virtual void		Unk_A3(void);
	virtual void		Unk_A4(void);
	virtual void		Unk_A5(void);
	virtual void		Unk_A6(void);
	virtual void		Unk_A7(void);
	virtual void		Unk_A8(void);
	virtual void		Unk_A9(void);
	virtual void		Unk_AA(void);
	virtual void		Unk_AB(void);
	virtual void		Unk_AC(void);
	virtual void		Unk_AD(void);
	virtual void		Unk_AE(void);
	virtual float		Unk_AF(UInt32 arg1);
	virtual void		Unk_B0(void);
	virtual void		Unk_B1(void);
	virtual void		Unk_B2(void);
	virtual void		Unk_B3(void);
	virtual void		Unk_B4(void);
	virtual void		Unk_B5(void);
	virtual void		Unk_B6(void);
	virtual void		Unk_B7(void);
	virtual void		Unk_B8(void);
	virtual void		Unk_B9(void);
	virtual void		Unk_BA(void);
	virtual void		Unk_BB(void);
	virtual void		Unk_BC(void);
	virtual void		Unk_BD(void);
	virtual void		Unk_BE(void);
	virtual void		Unk_BF(void);
	virtual void		Unk_C0(void);
	UInt32 unk054[3];						// 054
	BaseProcess*	 baseProcess;					// 060
	UInt32 unk064[(0x080 - 0x064) >> 2];	// 064
	// 080
};
STATIC_ASSERT(sizeof(MobileObject) == 0x080);

// 00C
class MagicCaster
{
public:
	MagicCaster();
	~MagicCaster();

	UInt32 vtabl;
	UInt32 unk004[2];	// 004
};

STATIC_ASSERT(sizeof(MagicCaster) == 0x00C);

// 010
class MagicTarget
{
public:
	MagicTarget();
	~MagicTarget();
	
	UInt32 vtabl;
	UInt32 unk004[3];	// 004
};

STATIC_ASSERT(sizeof(MagicTarget) == 0x010);

class Actor : public MobileObject
{
public:
	Actor();
	~Actor();
	virtual void		Unk_C1(void);
	virtual void		Unk_C2(void);
	virtual void		Unk_C3(void);
	virtual void		Unk_C4(void);
	virtual void		Unk_C5(void);
	virtual void		Unk_C6(void);
	virtual void		SetIgnoreCrime(bool ignoreCrime);
	virtual bool		GetIgnoreCrime(void);
	virtual void		Unk_C9(void);
	virtual void		Unk_CA(void);
	virtual void		Unk_CB(void);
	virtual void		Unk_CC(void);
	virtual void		Unk_CD(void);
	virtual void		Unk_CE(void);
	virtual void		Unk_CF(void);
	virtual void		DamageActionPoints(float amount);
	virtual void		Unk_D1(void);
	virtual void		Unk_D2(void);
	virtual void		Unk_D3(void);
	virtual void		Unk_D4(void);
	virtual void		Unk_D5(void);
	virtual void		Unk_D6(void);
	virtual void		Unk_D7(void);
	virtual bool		IsPlayerRef(void);
	virtual void		Unk_D9(void);
	virtual void		Unk_DA(void);
	virtual void		Unk_DB(void);
	virtual void		Unk_DC(void);
	virtual void		Unk_DD(void);
	virtual void		Unk_DE(void);
	virtual void		Unk_DF(void);
	virtual void		Unk_E0(void);
	virtual void		Unk_E1(void);
	virtual void		Unk_E2(void);
	virtual void		Unk_E3(void);
	virtual UInt32		GetActorType(void);	// Creature = 0, Character = 1, PlayerCharacter = 2
	virtual void		SetActorValue(UInt32 avCode, float value);
	virtual void		SetActorValueInt(UInt32 avCode, UInt32 value);
	virtual void		Unk_E5(void);
	virtual void		Unk_E6(void);
	virtual void		Unk_E7(void);
	virtual void		ModActorValue(UInt32 avCode, int modifier, UInt32 arg3);
	virtual void		DamageActorValue(UInt32 avCode, float damage, Actor* attacker);
	virtual void		Unk_EA(void);
	virtual void		Unk_EB(void);
	virtual void		Unk_EC(void);
	virtual void		Unk_ED(void);
	virtual void		Unk_EE(void);
	virtual void		Unk_EF(void);
	virtual void		Unk_F0(void);
	virtual void		Unk_F1(void);
	virtual void		HandlePickupItem(TESObjectREFR* pickedUp, int count, char a4);
	virtual void		Unk_F3(void);
	virtual void		Unk_F4(void);

	MagicCaster			magicCaster;			// 080
	MagicTarget			magicTarget;			// 08C
	ActorValueOwner		avOwner;				// 09C
	CachedValuesOwner	cvOwner;				// 0A0

	bhkRagdollController* ragDollController;			// 0A4
	bhkRagdollPenetrationUtil* ragDollPentrationUtil;	// 0A8
	UInt32				unk0AC[20];						// 0AC
	UInt32				lifeState;						// 0FC
	UInt32				unk100[14];						// 100
	bool				ignoreCrime;					// 138
	UInt8				byte139;						// 139
	UInt8				byte13A;						// 13A
	UInt8				byte13B;						// 13B
	UInt32				unk13C;							// 13C
	UInt8				inWater;						// 140
	UInt8				isSwimming;						// 141
	UInt16				unk142;							// 142
	UInt32				unk144[(0x184 - 0x144) >> 2];	// 144
	ActorMover*			actorMover;						// 184
	UInt32				unk188[(0x1C8 - 0x188) >> 2];	// 188

	TESActorBase* GetActorBase();
	void EquipItemAlt(void* itemEntry, bool noUnequip, bool noMessage);
	void TurnToFaceObject(TESObjectREFR* target);
	UInt16 Actor::GetLevel();
	double GetHealthPercent();
	bool IsInReloadAnim();
	double GetMaxCarryWeightPerkModified();
	void PlayPickupOrEquipSound(TESForm* item, bool pickUp, bool isEquip);
	void EquipRef(TESObjectREFR* item);
	bool IsInCombatWith(Actor* target);
	bool IsSneaking();
	bool GetDead() { return ((lifeState == 1) || (lifeState == 2)); }
};
STATIC_ASSERT(offsetof(Actor, lifeState) == 0xFC);
STATIC_ASSERT(offsetof(Actor, ignoreCrime) == 0x138);
STATIC_ASSERT(offsetof(Actor, cvOwner) == 0x0A0);

class Creature : public Actor
{
public:
	Creature();
	~Creature();

	virtual void	Unk_137(void);

	UInt32			unk1B4[3];			// 1B4
};

class Character : public Actor
{
public:
	Character();
	~Character();
};
//STATIC_ASSERT(sizeof(Character) == 0x1B0);

// 9BC
class PlayerCharacter : public Character
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	// used to flag controls as disabled in disabledControlFlags
	enum {
		kControlFlag_Movement		= 1 << 0,
		kControlFlag_Look			= 1 << 1,
		kControlFlag_Pipboy			= 1 << 2,
		kControlFlag_Fight			= 1 << 3,
		kControlFlag_POVSwitch		= 1 << 4,
		kControlFlag_RolloverText	= 1 << 5,
		kControlFlag_Sneak			= 1 << 6,
	};

	UInt32								unk188[(0x570-0x1C8) >> 2];		// 188
	BGSNote								* note;							// 570
	UInt32								unk574;							// 574
	ImageSpaceModifierInstanceDOF		* unk578;						// 578
	ImageSpaceModifierInstanceDOF		* unk57C;						// 57C
	ImageSpaceModifierInstanceDRB		* unk580;						// 580
	UInt32								unk584[(0x5A8 - 0x584) >> 2];	// 584
	bool								bThirdPerson;					// 5A8
	UInt8								isThirdPerson;					// 5A9	
	UInt8								unk5AA;							// 5AA
	UInt8								unk5AB;							// 5AB
	UInt8								unk5AC;							// 5AC
	UInt8								unk5AD;							// 5AD
	UInt8								unk5AE;							// 5AE
	UInt8								alwaysRun;						// 5AF
	UInt8								autoMove;						// 5B0
	UInt8								unk5B1;							// 5B1
	UInt8								unk5B2;							// 5B2
	UInt8								unk5B3;							// 5B3
	UInt32								unk5B4[(0x5D0 - 0x5B4) >> 2];	// 5B4
	float								worldFOV;						// 5D0
	UInt32								unk5D4[(0x5DC - 0x5D4) >> 2];	// 5D4
	UInt32								disabledControlFlags;			// 5DC
	UInt32								unk5E0;							// 5E0
	UInt32								unk5E4;							// 5E4
	UInt32								unk5E8;							// 5E8
	UInt32								unk5EC;							// 5EC
	NiNode								* playerNode;					// 5F0
	UInt32								unk5F4[(0x604-0x5F4) >> 2];		// 5F4
	TESTopic							* topic;						// 604
	UInt32								unk608[3];						// 608
	TESQuest							* activeQuest;					// 614
	BGSQuestObjective					* questObjective;				// 618
	UInt8								unk61C[50];						// 61C
	TESObjectREFR*						unk650;							// 650
	UInt32								unk654[5];						// 654
	TESObjectREFR**						unk668;							// 668					
	UInt32								unk66C;							// 66C
	UInt32								unk670[7];						// 670
	float								timeGrenadeHeld;				// 68C
	UInt8								unk690[(0x704 - 0x690)];		// 690
	UInt8								gameDifficulty;					// 704
	UInt8								byte705;						// 705
	UInt8								byte706;						// 706
	UInt8								byte707;						// 707
	UInt8								unk708[(0x718 - 0x708)];		// 708
	float								flycamZRot;						// 718
	float								flycamXRot;						// 71C
	float								flycamPosX;						// 720
	float								flycamPosY;						// 724
	float								flycamPosZ;						// 728
	UInt8								unk72C[(0x9A4 - 0x72C)];		// 72C
	bool								pcInCombat;						// 9A4
	bool								pcUnseen;						// 9A5
	UInt8								unk9A6[(0x9BC - 0x9A6)];		// 9A6

	bool IsThirdPerson() { return bThirdPerson ? true : false; }
	UInt32 GetMovementFlags() { return actorMover->GetMovementFlags(); }	// 11: IsSwimming, 9: IsSneaking, 8: IsRunning, 7: IsWalking, 0: keep moving
	bool IsPlayerSwimming() { return (GetMovementFlags() >> 11) & 1; }

	static PlayerCharacter*	GetSingleton();
	bool ToggleFirstPerson(bool toggleON);
	void SetActiveQuest(TESQuest* quest) { ThisCall(0x770580, this, quest); };
};

STATIC_ASSERT(sizeof(PlayerCharacter) == 0x9BC);
STATIC_ASSERT(offsetof(PlayerCharacter, questObjective) == 0x618);
STATIC_ASSERT(offsetof(PlayerCharacter, bThirdPerson) == 0x5A8);
STATIC_ASSERT(offsetof(PlayerCharacter, disabledControlFlags) == 0x5DC);
STATIC_ASSERT(offsetof(PlayerCharacter, unk650) == 0x650);
STATIC_ASSERT(offsetof(PlayerCharacter, unk66C) == 0x66C);
STATIC_ASSERT(offsetof(PlayerCharacter, unk668) == 0x668);