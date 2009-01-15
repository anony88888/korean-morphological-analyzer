#ifndef _MA_TOKEN_H_
#define _MA_TOKEN_H_

#include <MA_Type.h>

#define MAX_TOKEN_SIZE		64

/* 시스템에서 사용하는 delimiter 정의 */
static BYTE Delimiter[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \r\t\n\0";

/* 문장부호를 제외한 delimiter */
static BYTE OnlyDel[] = "#$%&*+-/<=>@[\\]^_`{|}~ \r\t\n\0";

/* 문장 부호 */
static BYTE SentMark[] = "!\"'(),.:;?";

#define NEUGGIM			101	/*!*/
#define BIGDDAOM		102	/*"*/
#define UMULJUNG		103	/*#*/
#define DALLA			104	/*$*/
#define PERCENT			105	/*%*/
#define AND			106	/*&*/
#define SMALLDDAOM		107	/*'*/
#define LPAREN			108	/*(*/
#define RPAREN			109	/*)*/
#define GOBHAGI			110	/***/
#define DUHAGI			111	/*+*/
#define SUIM			112	/*,*/
#define BBAEGI			113	/*-*/
#define MACHIM			114	/*.*/
#define SLASH			115	/**/
#define COLON			116	/*:*/
#define SEMICOLON		117	/*;*/
#define SMALLTHEN		118	/*<*/
#define EQUAL			119	/*=*/
#define LARGETHEN		120	/*>*/
#define QUESTION		121	/*?*/
#define GOLBANGI		122	/*@*/
#define GAGLPAREN		123	/*[*/
#define BACKSLASH		124	/*\*/
#define GAGRPAREN		125	/*]*/
#define USAN			126	/*^*/
#define DOWNBAR			127	/*_*/
#define BACKSDAOM		128	/*`*/
#define BIGLPAREN		129	/*{*/
#define PIPE			130	/*|*/
#define BIGRPAREN		131	/*}*/
#define WAVE			132	/*~*/
#define BACKR			133	/*\r*/
#define BACKN			134	/*\n*/
#define ENDBUF			135	/*\0*/

#define ONE_WORD		136
#define ENG_WORD		137	/* 알파벳으로 구성된 토큰 */

/* 내부 버퍼 포인터 */
//UBYTE *pBufferMA;

#endif

