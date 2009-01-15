/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.28
 *
 *	#(Action)#
 *         - 전역변수 선언부...
 *         - 모든 형태소 분석 모듈에 필요한 전역변수는 여기에 선언된다.
 *         - 사전 관련 전역변수는 제외 --> MADIC_Global.h
 */
#ifndef _MA_GLOBAL_H_
#define _MA_GLOBAL_H_

#include <MA_SysHeader.h>
#include <MA_GMacro.h>
#include <MA_Type.h>
#include <MA_HanType.h>

/* 형태소 분석 결과에 대한 저장은 함수로 만들지 않는다.
   그 이유는 함수 호출에 따른 속도 저하를 막기 위해서     */
tMORP_RESULT MorpResult[MAX_MORP_LIST];			/* 형태소 분석 결과 저장 버퍼 */
UWORD MorpResult_Index;							/* 형태소 분석 결과 저장 버퍼 인덱스 */
UWORD Morpheme_Index;							/* 형태소 인덱스 */

/* 두가지 중요한 변수를 셋팅한다... */
/* 이 변수는 미등록어 처리에서만 사용되어야 한다.
 * 물론 차후에 다른 부분에서 사용될 수도 있으나...
 * 그렇게 된다면 이 곳에 반드시 표시를 해 두어야 한다.
 */
/***********************************************/
UWORD is_HanJa; /* 한자가 포함된 어절인가? */
UWORD is_AlPha; /* 영어가 포함된 어절인가? */
UWORD is_DiGit; /* 숫자가 포함된 어절인가? */
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

