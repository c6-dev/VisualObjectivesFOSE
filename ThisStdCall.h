#pragma once

__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(); } u = { _f };
	return ((T*)_t->*u.m)();
}

template <typename T1>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1); } u = { _f };
	return ((T*)_t->*u.m)(a1);
}

template <typename T1, typename T2>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2);
}

template <typename T1, typename T2, typename T3>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3);
}

template <typename T1, typename T2, typename T3, typename T4>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3, T4 a4)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3, a4);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3, a4, a5);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3, a4, a5, a6);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6, T7); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3, a4, a5, a6, a7);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6, T7, T8); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3, a4, a5, a6, a7, a8);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6, T7, T8, T9); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template <typename T01, typename T02, typename T03, typename T04, typename T05, typename T06, typename T07, typename T08, typename T09, typename T10>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T01 a01, T02 a02, T03 a03, T04 a04, T05 a05, T06 a06, T07 a07, T08 a08, T09 a09, T10 a10)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T01, T02, T03, T04, T05, T06, T07, T08, T09, T10); } u = { _f };
	return ((T*)_t->*u.m)(a01, a02, a03, a04, a05, a06, a07, a08, a09, a10);
}

template <typename T01, typename T02, typename T03, typename T04, typename T05, typename T06, typename T07, typename T08, typename T09, typename T10, typename T11>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T01 a01, T02 a02, T03 a03, T04 a04, T05 a05, T06 a06, T07 a07, T08 a08, T09 a09, T10 a10, T11 a11)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T01, T02, T03, T04, T05, T06, T07, T08, T09, T10, T11); } u = { _f };
	return ((T*)_t->*u.m)(a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11);
}

template <typename T01, typename T02, typename T03, typename T04, typename T05, typename T06, typename T07, typename T08, typename T09, typename T10, typename T11, typename T12>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T01 a01, T02 a02, T03 a03, T04 a04, T05 a05, T06 a06, T07 a07, T08 a08, T09 a09, T10 a10, T11 a11, T12 a12)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T01, T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12); } u = { _f };
	return ((T*)_t->*u.m)(a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11, a12);
}

template <typename T01, typename T02, typename T03, typename T04, typename T05, typename T06, typename T07, typename T08, typename T09, typename T10, typename T11, typename T12, typename T13>
__forceinline UInt32 ThisStdCall(UInt32 _f, void* _t, T01 a01, T02 a02, T03 a03, T04 a04, T05 a05, T06 a06, T07 a07, T08 a08, T09 a09, T10 a10, T11 a11, T12 a12, T13 a13)
{
	class T {}; union { UInt32 x; UInt32(T::* m)(T01, T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12, T13); } u = { _f };
	return ((T*)_t->*u.m)(a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11, a12, a13);
}

//	Templates for UInt8 return.

__forceinline UInt8 ThisStdCall_B(UInt32 _f, void* _t)
{
	class T {}; union { UInt32 x; UInt8(T::* m)(); } u = { _f };
	return ((T*)_t->*u.m)();
}

template <typename T1>
__forceinline UInt8 ThisStdCall_B(UInt32 _f, void* _t, T1 a1)
{
	class T {}; union { UInt32 x; UInt8(T::* m)(T1); } u = { _f };
	return ((T*)_t->*u.m)(a1);
}

template <typename T1, typename T2>
__forceinline UInt8 ThisStdCall_B(UInt32 _f, void* _t, T1 a1, T2 a2)
{
	class T {}; union { UInt32 x; UInt8(T::* m)(T1, T2); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2);
}

template <typename T1, typename T2, typename T3>
__forceinline UInt8 ThisStdCall_B(UInt32 _f, void* _t, T1 a1, T2 a2, T3 a3)
{
	class T {}; union { UInt32 x; UInt8(T::* m)(T1, T2, T3); } u = { _f };
	return ((T*)_t->*u.m)(a1, a2, a3);
}

//	Templates for float return.

__forceinline float ThisStdCall_F(UInt32 _f, void* _t)
{
	class T {}; union { UInt32 x; float (T::* m)(); } u = { _f };
	return ((T*)_t->*u.m)();
}

template <typename T1>
__forceinline float ThisStdCall_F(UInt32 _f, void* _t, T1 a1)
{
	class T {}; union { UInt32 x; float (T::* m)(T1); } u = { _f };
	return ((T*)_t->*u.m)(a1);
}