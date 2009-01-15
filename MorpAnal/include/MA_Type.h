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

/* ����/��̿� ���� ��� �ε����� �����ϴµ� �ʿ��� ����ü Ÿ�� */
typedef struct {
	UWORD code;
	UWORD idx;
} tJEHEADER_IDX;

/* ���� ���� ���� �� ���� ��Ģ���̽� ����ü Ÿ�� */
typedef struct {
	BYTE c_num;		/* ����� ���� ���� */
	BYTE center;	/* �߽� ���ڿ� ���� code �ε��� */
	UWORD code[3];	/* �˻��� ���ڿ� ���� ������ �ڵ� */
	UWORD rule;		/* ����Ǵ� ��Ģ ��ȣ */
} tCONST_RULE;

/* ���¼�/���� ����Ʈ ����ü */
typedef struct {
	UWORD Morpheme[MORP_LEN];		/* ���¼�, �ִ� ũ�� 20�� */
	UWORD ninfo;					/* ���� ���� ���� */
	BYTE info[MORP_INFO];			/* ���� ���� */
} tMORP_ITEM;

/* ���¼� �м� ��� ���� ����ü */
typedef struct {
	UWORD nMorp;						/* �� ������ ���� ���¼� �� */
	tMORP_ITEM MI[MAX_MORP_LIST];		/* ���¼� ����Ʈ */
	UWORD prev;
} tMORP_RESULT;

/* ��� ��� ����Ʈ ����ü */
typedef struct {
	UWORD word[50];					/* ��� ��� */
	UWORD len;						/* ���� */
} tPREEOMI;

typedef struct {					/* ����/������� ���� */
	UWORD word[5];
	UWORD len;
} tVAJUBSA;

typedef struct {					/* ���ո��ó����ƾ���� ����ϴ� ���� */
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
 * ���ո�� ��м� ������ ���� ���¼� �м� ��� ����ü
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

