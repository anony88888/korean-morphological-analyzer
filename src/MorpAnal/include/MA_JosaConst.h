/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.27
 *
 *	#(Action)#
 *		- 조사 결합제약조건 검사
 */
#ifndef _MA_JOSACONST_H_
#define _MA_JOSACONST_H_

#include <MA_SysHeader.h>
#include <MA_Type.h>

#define JOSACONST_NUM	12			/* 규칙 개수 */

#define NO_JONG				1		/* 앞 글자에 종성이 없어야 함 */
#define YES_JONG			2		/* 앞 글자에 종성이 있어야 함 */

tCONST_RULE JosaConst[JOSACONST_NUM] = {
	{1, 1, {0x8861, 0, 0}, NO_JONG},				/* 가 */
	{1, 1, {0x89c1, 0, 0}, YES_JONG},				/* 과 */
	{1, 1, {0x9365, 0, 0}, NO_JONG},				/* 는 */
	{1, 1, {0x9da1, 0, 0}, NO_JONG},				/* 로 */
	{1, 1, {0x9f69, 0, 0}, NO_JONG},				/* 를 */
	{1, 1, {0xa165, 0, 0}, NO_JONG},				/* 면 */
	{1, 1, {0xb461, 0, 0}, YES_JONG},				/* 아 */
	{1, 1, {0xb4a1, 0, 0}, NO_JONG},				/* 야 */
	{1, 1, {0xb5c1, 0, 0}, NO_JONG},				/* 와 */
	{1, 1, {0xb765, 0, 0}, YES_JONG},				/* 은 */
	{1, 1, {0xb769, 0, 0}, YES_JONG},				/* 을 */
	{1, 1, {0xb7a1, 0, 0}, YES_JONG},				/* 이 */
};

#endif

