#include "GameBSExtraData.h"
#include "GameAPI.h"
#include "GameExtraData.h"

bool BaseExtraList::HasType(UInt32 type) const
{
	UInt32 index = (type >> 3);
	UInt8 bitMask = 1 << (type % 8);
	return (m_presenceBitfield[index] & bitMask) != 0;
}

BSExtraData * BaseExtraList::GetByType(UInt32 type) const
{
	if (!HasType(type)) return NULL;

	for(BSExtraData * traverse = m_data; traverse; traverse = traverse->next)
		if(traverse->type == type)
			return traverse;

#ifdef _DEBUG
	Console_Print("ExtraData HasType(%d) is true but it wasn't found!", type);
#endif
	return NULL;
}

void BaseExtraList::MarkType(UInt32 type, bool bCleared)
{
	UInt32 index = (type >> 3);
	UInt8 bitMask = 1 << (type % 8);
	UInt8& flag = m_presenceBitfield[index];
	if (bCleared) {
		flag &= ~bitMask;
	} else {
		flag |= bitMask;
	}
}

bool BaseExtraList::Remove(BSExtraData* toRemove)
{
	if (!toRemove) return false;

	if (HasType(toRemove->type)) {
		bool bRemoved = false;
		if (m_data == toRemove) {
			m_data = m_data->next;
			bRemoved = true;
		}

		for (BSExtraData* traverse = m_data; traverse; traverse = traverse->next) {
			if (traverse->next == toRemove) {
				traverse->next = toRemove->next;
				bRemoved = true;
				break;
			}
		}
		if (bRemoved) {
			MarkType(toRemove->type, true);
		}
		return true;
	}

	return false;
}

bool BaseExtraList::Add(BSExtraData* toAdd)
{
	if (!toAdd || HasType(toAdd->type)) return false;
	
	BSExtraData* next = m_data;
	m_data = toAdd;
	toAdd->next = next;
	MarkType(toAdd->type, false);
	return true;
}

__declspec(naked) ExtraCount *BaseExtraList::GetExtraCount() const
{
	__asm
	{
		xor		eax, eax
		test	byte ptr [ecx+0xC], 0x10
		jz		done
		mov		eax, [ecx+4]
	iterHead:
		cmp		byte ptr [eax+4], kExtraData_Count
		jnz		iterNext
		retn
	iterNext:
		mov		eax, [eax+8]
		test	eax, eax
		jnz		iterHead
	done:
		retn
	}
}

__declspec(naked) SInt32 BaseExtraList::GetCount() const
{
	__asm
	{
		test	byte ptr [ecx+0xC], 0x10
		jz		retn1
		mov		ecx, [ecx+4]
	iterHead:
		cmp		byte ptr [ecx+4], kExtraData_Count
		jnz		iterNext
		movsx	eax, word ptr [ecx+0xC]
		retn
	iterNext:
		mov		ecx, [ecx+8]
		test	ecx, ecx
		jnz		iterHead
	retn1:
		mov		eax, 1
		retn
	}
}

__declspec(naked) void BaseExtraList::RemoveByType(UInt32 type)
{
	static const UInt32 procAddr = 0x40A3F0;
	__asm	jmp		procAddr
}