/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.28
 *
 *	#(Action)#
 *         - �������� �����...
 *         - ��� ���¼� �м� ��⿡ �ʿ��� ���������� ���⿡ ����ȴ�.
 *         - ���� ���� ���������� ���� --> MADIC_Global.h
 */
#ifndef _MA_GLOBAL_H_
#define _MA_GLOBAL_H_

#include <MA_SysHeader.h>
#include <MA_GMacro.h>
#include <MA_Type.h>
#include <MA_HanType.h>

/* ���¼� �м� ����� ���� ������ �Լ��� ������ �ʴ´�.
   �� ������ �Լ� ȣ�⿡ ���� �ӵ� ���ϸ� ���� ���ؼ�     */
tMORP_RESULT MorpResult[MAX_MORP_LIST];			/* ���¼� �м� ��� ���� ���� */
UWORD MorpResult_Index;							/* ���¼� �м� ��� ���� ���� �ε��� */
UWORD Morpheme_Index;							/* ���¼� �ε��� */

/* �ΰ��� �߿��� ������ �����Ѵ�... */
/* �� ������ �̵�Ͼ� ó�������� ���Ǿ�� �Ѵ�.
 * ���� ���Ŀ� �ٸ� �κп��� ���� ���� ������...
 * �׷��� �ȴٸ� �� ���� �ݵ�� ǥ�ø� �� �ξ�� �Ѵ�.
 */
/***********************************************/
UWORD is_HanJa; /* ���ڰ� ���Ե� �����ΰ�? */
UWORD is_AlPha; /* ��� ���Ե� �����ΰ�? */
UWORD is_DiGit; /* ���ڰ� ���Ե� �����ΰ�? */
/***********************************************/

#define M_MORPRESULT_INDEX		MorpResult_Index
#define M_MORPHEME_INDEX		Morpheme_Index

#define M_MORPRESULT_MI_MORPHEME(i, j)		MorpResult[(i)].MI[(j)].Morpheme
#define M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)	MorpResult[(i)].MI[(j)].Morpheme[(k)]

#define M_MORPRESULT_NMORP(i)			MorpResult[(i)].nMorp

#define M_MORPRESULT_MI_NINFO(i, j)		MorpResult[(i)].MI[(j)].ninfo

#define M_MORPRESULT_MI_INFO(i, j)		MorpResult[(i)].MI[(j)].info
#define M_MORPRESULT_MI_INFO_ITEM(i, j, k)	MorpResult[(i)].MI[(j)].info[(k)]

#define M_MORPRESULT				MorpResult
#define M_MORPRESULT_ITEM(i)			MorpResult[(i)]

#define M_MORPRESULT_MI(i)			MorpResult[(i)].MI
#define M_MORPRESULT_MI_ITEM(i, j)		MorpResult[(i)].MI[(j)]

#define M_CUR_MORPRESULT			MorpResult[MorpResult_Index]
#define M_PREV_MORPRESULT			MorpResult[MorpResult_Index-1]
#define M_NEXT_MORPRESULT			MorpResult[MorpResult_Index+1]

#define M_CUR_MORPRESULT_MI			MorpResult[MorpResult_Index].MI
#define M_PREV_MORPRESULT_MI			MorpResult[MorpResult_Index-1].MI
#define M_NEXT_MORPRESULT_MI			MorpResult[MorpResult_Index+1].MI

#define M_CUR_MORPRESULT_NMORP				MorpResult[MorpResult_Index].nMorp
#define M_CUR_MORPRESULT_MI_MORPHEME			MorpResult[MorpResult_Index].MI[Morpheme_Index].Morpheme
#define M_CUR_MORPRESULT_MI_MORPHEME_ITEM(i)		MorpResult[MorpResult_Index].MI[Morpheme_Index].Morpheme[(i)]
#define M_CUR_MORPRESULT_MI_NINFO			MorpResult[MorpResult_Index].MI[Morpheme_Index].ninfo

#define M_CUR_MORPRESULT_MI_INFO			MorpResult[MorpResult_Index].MI[Morpheme_Index].info
#define M_CUR_MORPRESULT_MI_INFO_ITEM(i)		MorpResult[MorpResult_Index].MI[Morpheme_Index].info[(i)]

#endif

