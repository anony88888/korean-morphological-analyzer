/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_SearchJECharInCurrentLevel.c)#  SPASIS System,  Thu Nov 18 20:23:19 1999
 *
 *	#(Action)#
 *		- 조사/어미 Trie의 현재 레벨에서 지정된 글자를 검색
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>

WORD SearchJosaCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index)
{
	DWORD node_index = *index;

	while (1) {
		if (JDic_Header[g_idx].items <= node_index)
			break;
		if (one_char.j_code == JDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}
		if (JDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	*index = node_index+1;


	return FALSE;
} /* End of SearchCharInCurrentLevel */

WORD SearchEomiCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index)
{
	DWORD node_index = *index;

	while (1) {
		if (EDic_Header[g_idx].items <= node_index)
			break;
		if (one_char.j_code == EDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}
		if (EDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	*index = node_index+1;

	return FALSE;
} /* End of SearchCharInCurrentLevel */

WORD SearchBojoCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index)
{
	DWORD node_index = *index;

	while (1) {
		if (BDic_Header[g_idx].items <= node_index)
			break;
		if (one_char.j_code == BDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}
		if (BDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}
	*index = node_index+1;

	return FALSE;
} /* End of SearchCharInCurrentLevel */
