#ifndef _MA_PREEOMI_H_
#define _MA_PREEOMI_H_

#include <MA_Type.h>

#define PRE_EOMI_LEN 40

UWORD len_start[5] = { 33, 16, 5, 1, 0 };
tPREEOMI pre_eomi[PRE_EOMI_LEN] = {
	{ { 0xb761, 0xafa1, 0xb4f6, 0xb4f6, 0x8956, }, 5 },
	{ { 0xafa1, 0xb4f6, 0xb4f6, 0x8956, }, 4 },
	{ { 0xb761, 0xad76, 0xb4f6, 0x8956, }, 4 },
	{ { 0xb761, 0xafa1, 0xb4f6, 0x8956, }, 4 },
	{ { 0xb761, 0xafa1, 0xb4f6, 0xb4f6, }, 4 },
	{ { 0xad76, 0xb4f6, 0x8956, }, 3 },
	{ { 0xafa1, 0xb4f6, 0x8956, }, 3 },
	{ { 0xafa1, 0xb4f6, 0xb4f6, }, 3 },
	{ { 0xb476, 0xb4f6, 0x8956, }, 3 },
	{ { 0xb4e1, 0xb4a1, 0x8956, }, 3 },
	{ { 0xb4f6, 0xb4f6, 0x8956, }, 3 },
	{ { 0xb576, 0xb4f6, 0x8956, }, 3 },
	{ { 0xb761, 0xad76, 0x8956, }, 3 },
	{ { 0xb761, 0xad76, 0xb4f6, }, 3 },
	{ { 0xb761, 0xafa1, 0x8956, }, 3 },
	{ { 0xb761, 0xafa1, 0xb4f6, }, 3 },
	{ { 0x9c61, 0x94e1, }, 2 },
	{ { 0xad76, 0x8956, }, 2 },
	{ { 0xad76, 0xb4f6, }, 2 },
	{ { 0xafa1, 0x8956, }, 2 },
	{ { 0xafa1, 0x94e1, }, 2 },
	{ { 0xafa1, 0xb4f6, }, 2 },
	{ { 0xb476, 0x8956, }, 2 },
	{ { 0xb476, 0x94e1, }, 2 },
	{ { 0xb476, 0xb4f6, }, 2 },
	{ { 0xb4f6, 0x8956, }, 2 },
	{ { 0xb4f6, 0x94e1, }, 2 },
	{ { 0xb4f6, 0xb4f6, }, 2 },
	{ { 0xb576, 0x8956, }, 2 },
	{ { 0xb576, 0xb4f6, }, 2 },
	{ { 0xb5b3, 0xafa1, }, 2 },
	{ { 0xb761, 0xad76, }, 2 },
	{ { 0xb761, 0xafa1, }, 2 },
	{ { 0x8956, }, 1 },
	{ { 0x94e1, }, 1 },
	{ { 0xad76, }, 1 },
	{ { 0xafa1, }, 1 },
	{ { 0xb476, }, 1 },
	{ { 0xb4f6, }, 1 },
	{ { 0xb576, }, 1 },
};
/*
	{"겠", 1},
	{"더", 1},
	{"라더", 2},
	{"셨", 1},
	{"셨겠", 2},
	{"셨었", 2},
	{"셨었겠", 3},
	{"시", 1},
	{"시겠", 2},
	{"시더", 2},
	{"시었", 2},
	{"시었겠", 3},
	{"시었었", 3},
	{"시었었겠", 4},
	{"았", 1},
	{"았겠", 2},
	{"았더", 2},
	{"았었", 2},
	{"았었겠", 3},
	{"어야겠", 3},
	{"었", 1},
	{"었겠", 2},
	{"었더", 2},
	{"었었", 2},
	{"었었겠", 3},
	{"였", 1},
	{"였겠", 2},
	{"였었", 2},
	{"였었겠", 3},
	{"옵시", 2},
	{"으셨", 2},
	{"으셨겠", 3},
	{"으셨었", 3},
	{"으셨었겠", 4},
	{"으시", 2},
	{"으시겠", 3},
	{"으시었", 3},
	{"으시었겠", 4},
	{"으시었었", 4},
	{"으시었었겠", 5}

tPREEOMI pre_eomi[PRE_EOMI_LEN] = {
	{ "8956", 1 },
	{ "94e1", 1 },
	{ "9c6194e1", 2 },
	{ "ad76", 1 },
	{ "ad768956", 2 },
	{ "ad76b4f6", 2 },
	{ "ad76b4f68956", 3 },
	{ "afa1", 1 },
	{ "afa18956", 2 },
	{ "afa194e1", 2 },
	{ "afa1b4f6", 2 },
	{ "afa1b4f68956", 3 },
	{ "afa1b4f6b4f6", 3 },
	{ "afa1b4f6b4f68956", 4 },
	{ "b476", 1 },
	{ "b4768956", 2 },
	{ "b47694e1", 2 },
	{ "b476b4f6", 2 },
	{ "b476b4f68956", 3 },
	{ "b4e1b4a18956", 3 },
	{ "b4f6", 1 },
	{ "b4f68956", 2 },
	{ "b4f694e1", 2 },
	{ "b4f6b4f6", 2 },
	{ "b4f6b4f68956", 3 },
	{ "b576", 1 },
	{ "b5768956", 2 },
	{ "b576b4f6", 2 },
	{ "b576b4f68956", 3 },
	{ "b5b3afa1", 2 },
	{ "b761ad76", 2 },
	{ "b761ad768956", 3 },
	{ "b761ad76b4f6", 3 },
	{ "b761ad76b4f68956", 4 },
	{ "b761afa1", 2 },
	{ "b761afa18956", 3 },
	{ "b761afa1b4f6", 3 },
	{ "b761afa1b4f68956", 4 },
	{ "b761afa1b4f6b4f6", 4 },
	{ "b761afa1b4f6b4f68956", 5 },
};
*/

#endif

