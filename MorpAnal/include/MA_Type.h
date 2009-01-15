/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(MA_Type.h)#           SPASIS System, 29/OCT/1999
 *
 *	#(Action)#
 *		Base System type overloading for portability...
 */

#ifndef _MA_TYPE_H_
#define _MA_TYPE_H_

#include <MA_GMacro.h>

/* Numeric Code Type definition... */
typedef unsigned short int		UWORD;	/* unsigned 2-byte */
typedef unsigned int			UDWORD;	/* unsigned 4-byte */
typedef short int				WORD;	/* signed 2-byte */
typedef int						DWORD;	/* signed 4-byte */
typedef long					DDWORD;	/* signed 8-byte */
typedef unsigned long			UDDWORD; /* unsigned 8-byte */

typedef float					TFLOAT;

/* Character Code Type definition... */
typedef unsigned char			UBYTE;	/* unsigned 1-byte */
typedef char					BYTE;	/* signed 1-byte */

/* ETC... */
typedef void					tVOID;	/* void type */

/* 조사/어미에 대한 헤더 인덱스를 지정하는데 필요한 구조체 타입 */
typedef struct {
	UWORD code;
	UWORD idx;
} tJEHEADER_IDX;

/* 각종 제약 조건 및 결합 규칙베이스 구조체 타입 */
typedef struct {
	BYTE c_num;		/* 사용할 글자 개수 */
	BYTE center;	/* 중심 글자에 대한 code 인덱스 */
	UWORD code[3];	/* 검사할 글자에 대한 조합형 코드 */
	UWORD rule;		/* 수행되는 규칙 번호 */
} tCONST_RULE;

/* 형태소/정보 리스트 구조체 */
typedef struct {
	UWORD Morpheme[MORP_LEN];		/* 형태소, 최대 크기 20자 */
	UWORD ninfo;					/* 사전 정보 개수 */
	BYTE info[MORP_INFO];			/* 사전 정보 */
} tMORP_ITEM;

/* 형태소 분석 결과 저장 구조체 */
typedef struct {
	UWORD nMorp;						/* 한 어절에 대한 형태소 수 */
	tMORP_ITEM MI[MAX_MORP_LIST];		/* 형태소 리스트 */
	UWORD prev;
} tMORP_RESULT;

/* 선어말 어미 리스트 구조체 */
typedef struct {
	UWORD word[50];					/* 선어말 어미 */
	UWORD len;						/* 길이 */
} tPREEOMI;

typedef struct {					/* 동사/형용사형 접사 */
	UWORD word[5];
	UWORD len;
} tVAJUBSA;

typedef struct {					/* 복합명사처리루틴에서 사용하는 스택 */
	DWORD node;
	DWORD level;
	DWORD add_level;
} tSTACK;
/*
 * 2006.03.02 by mini
 * 
*/


typedef struct {
	UWORD nIDX;
	UWORD nCOLUMN;	
	tMORP_RESULT IDX_word[MAX_IDX_LIST];
	
} eIDX_RESULT;

#ifdef COMP_NOUN_DIC_CHECK
/*
 * 복합명사 기분석 사전에 의한 형태소 분석 결과 구조체
 */
typedef struct {
    UBYTE Morpheme[MORP_LEN];
    BYTE info;
} tCNMORP_ITEM;

typedef struct {
    UWORD nMorp;
    tCNMORP_ITEM MI[MAX_MORP_LIST];
} tCNMORP_RESULT;

#endif

typedef struct {
	UBYTE Morpheme[MORP_LEN];
	BYTE info;		
}tUADMORP_ITEM;
typedef struct {
	UWORD nMorp;
	tUADMORP_ITEM MI[MAX_MORP_LIST];
} tUADMORP_RESULT;


#endif /* _MA_TYPE_H_ */

