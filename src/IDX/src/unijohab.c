/*
 * Copyright (C) 2000 Bang Jun-Young
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THE AUTHOR ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION,
 * AND DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER
 * RESULTING FROM THE USE OF THIS SOFTWARE.
 */
#include <stdio.h>

#define UNI_HANGUL_FIRST 	0xac00
#define UNI_HANGUL_LAST		0xd7a3

#define NUM_CHOSEONG		19
#define NUM_JOONGSEONG		21
#define NUM_JONGSEONG		28

/* TODO: Return conversion result. */
/* 조합형 변환 모듈 수정 */
/* A6GUG| :/H/ 8p5b <vA$ */
/* Hangul Johab code Abstract type */
#ifdef WIN32
typedef struct {
	unsigned short int jong: 5;
	unsigned short int jung: 5;
	unsigned short int cho:  5;
	unsigned short int sign: 1;
} JOHAB_T;
#elif LINUX
typedef struct {
	unsigned short int jong: 5;
	unsigned short int jung: 5;
	unsigned short int cho:  5;
	unsigned short int sign: 1;
} JOHAB_T;
#else
typedef struct {
	unsigned short int sign: 1;
	unsigned short int cho:  5;
	unsigned short int jung: 5;
	unsigned short int jong: 5;
} JOHAB_T;
#endif

typedef union {
	unsigned short int code;
	JOHAB_T j_han;
} HANCHAR_T;


/*
int
ucs2_to_johab(int src, int *dest)
*/
unsigned int ucs2_to_johab(unsigned int src)
{
	int choseong, joongseong, jongseong;
	HANCHAR_T hangul;

	src -= UNI_HANGUL_FIRST;
	choseong = src / (NUM_JOONGSEONG * NUM_JONGSEONG);
	joongseong = (src % (NUM_JOONGSEONG * NUM_JONGSEONG)) / NUM_JONGSEONG;
	jongseong = src % NUM_JONGSEONG;

	choseong += 2;

	if (joongseong >= 0 && joongseong <= 4) {
		joongseong += 3;
	} else if (joongseong >= 5 && joongseong <= 10) {
		joongseong += 5;
	} else if (joongseong >= 11 && joongseong <= 16) {
		joongseong += 7;
	} else if (joongseong >= 17 && joongseong <= 20) {
		joongseong += 9;
	}

	if (jongseong >= 0 && jongseong <= 16) 
		jongseong += 1;
	else if (jongseong >= 17 && jongseong <= 27)
		jongseong += 2;

	hangul.j_han.cho = choseong;
	hangul.j_han.jung = joongseong;
	hangul.j_han.jong = jongseong;
	hangul.j_han.sign = 1;

/*
	*dest = hangul.code;
*/
	
/*
	*dest = (choseong << 10) | (joongseong << 5) | jongseong;
*/
	return hangul.code;
}

unsigned int johab_to_ucs2(unsigned int src)
{
	int choseong, joongseong, jongseong;
	int ret;

	choseong = (src >> 10) & 0x1f;
	joongseong = (src >> 5) & 0x1f;
	jongseong = src & 0x1f;

	choseong -= 2;

	if (joongseong >= 3 && joongseong <= 7) {
		joongseong -= 3;
	} else if (joongseong >= 10 && joongseong <= 15) {
		joongseong -= 5;
	} else if (joongseong >= 18 && joongseong <= 23) {
		joongseong -= 7;
	} else if (joongseong >= 26 && joongseong <= 29) {
		joongseong -= 9;
	}

	if (jongseong >= 1 && jongseong <= 17) 
		jongseong -= 1;
	else if (jongseong >= 19 && jongseong <= 29)
		jongseong -= 2;

	choseong *= (NUM_JOONGSEONG * NUM_JONGSEONG);
	joongseong *= NUM_JONGSEONG;

	ret = UNI_HANGUL_FIRST + choseong + joongseong + jongseong;

	return ret;
}

#if 0
main()
{
	int a, b;
	a = 0x20;		/* 00000 00001 00000 = G AE _ */
	johab_to_ucs2(a, &b);
	printf("U+0x%04X\n", b);
	a = 0x400;		/* 00001 00000 00000 = GG A _ */
	johab_to_ucs2(a, &b);
	printf("U+0x%04X\n", b);
}
#endif

