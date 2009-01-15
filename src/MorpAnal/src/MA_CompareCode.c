/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.28
 *
 *	#(Action)#
 *		- 제약 조건 규칙에 대한 바이너리 탐색시 필요한 비교함수들 
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_Func.h>

DWORD compare_word(const tVOID *item1, const tVOID *item2)
{
	return (strcmp((BYTE *) item1, (BYTE *) item2));
}

DWORD compare_code0(const tVOID *code1, const tVOID *code2)
{
	return ( ((tCONST_RULE *)code1)->code[0] - ((tCONST_RULE *)code2)->code[0] );
}

DWORD compare_code1(const tVOID *code1, const tVOID *code2)
{
	return ( ((tCONST_RULE *)code1)->code[1] - ((tCONST_RULE *)code2)->code[1] );
}

DWORD compare_code2(const tVOID *code1, const tVOID *code2)
{
	return ( ((tCONST_RULE *)code1)->code[2] - ((tCONST_RULE *)code2)->code[2] );
}
