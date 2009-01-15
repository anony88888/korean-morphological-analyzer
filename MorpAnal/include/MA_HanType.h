/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(MA_HanType.h)#           SPASIS System, 29/OCT/1999
 *
 *	#(Action)#
 *		- The type of one character of hangul is defined.
 *		- This type provides multiple access 
 *			to hangul character both Johab and Wansung. 
 */

#ifndef _MA_HANTYPE_H_
#define _MA_HANTYPE_H_

/* Hangul Johab code Abstract type */
#ifdef WIN32
typedef struct {
	UWORD jong: 5;
	UWORD jung: 5;
	UWORD cho:  5;
	UWORD sign: 1;
} JOHAB;
#elif LINUX
typedef struct {
	UWORD jong: 5;
	UWORD jung: 5;
	UWORD cho:  5;
	UWORD sign: 1;
} JOHAB;
#else
typedef struct {
	UWORD sign: 1;		/* Hangul Detection Bit */
	UWORD cho:  5;		/* ChoSung Bits */
	UWORD jung: 5;		/* JungSung Bits */
	UWORD jong: 5;		/* JongSung Bits */
} JOHAB;                          
#endif

#ifdef WIN32
typedef struct {
	UBYTE low;
	UBYTE high;
} W_CHAR;
#elif LINUX
typedef struct {
	UBYTE low;
	UBYTE high;
} W_CHAR;
#else
typedef struct {
	UBYTE high;
	UBYTE low;
} W_CHAR;
#endif

typedef union {
	UWORD code;
	W_CHAR hl;
} H_CHAR;

/* Integrated Version of hangul code ADT : Johab */
typedef union {
	UWORD j_code;	/* 2-byte johab code */
	JOHAB j_han;	
	W_CHAR j_hl;
} HANGUL;                         

#endif /* _MA_HANTYPE_H_ */

