/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.27
 *
 *	#(Action)#
 *		- ���� ������������ �˻�
 */
#ifndef _MA_JOSACONST_H_
#define _MA_JOSACONST_H_

#include <MA_SysHeader.h>
#include <MA_Type.h>

#define JOSACONST_NUM	12			/* ��Ģ ���� */

#define NO_JONG				1		/* �� ���ڿ� ������ ����� �� */
#define YES_JONG			2		/* �� ���ڿ� ������ �־�� �� */

tCONST_RULE JosaConst[JOSACONST_NUM] = {
	{1, 1, {0x8861, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0x89c1, 0, 0}, YES_JONG},				/* �� */
	{1, 1, {0x9365, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0x9da1, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0x9f69, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0xa165, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0xb461, 0, 0}, YES_JONG},				/* �� */
	{1, 1, {0xb4a1, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0xb5c1, 0, 0}, NO_JONG},				/* �� */
	{1, 1, {0xb765, 0, 0}, YES_JONG},				/* �� */
	{1, 1, {0xb769, 0, 0}, YES_JONG},				/* �� */
	{1, 1, {0xb7a1, 0, 0}, YES_JONG},				/* �� */
};

#endif

