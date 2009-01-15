/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_SearchCharInCurrentLevel.c)#  SPASIS System,  Thu Nov 18 20:23:19 1999
 *
 *	#(Action)#
 *		- Trie의  현재 레벨에서 지정된 글자를 검색
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>

/*
 * 검색에 실패하였으면...
 * 현재 레벨의 가장 마지막 노드의 다음 노드를 지정...
 */
WORD SearchCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index)
{
	DWORD node_index = *index;

	while (1) {
	    if (Dic_Header[g_idx].items <= node_index)
			break;
		if (one_char.j_code == Dic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}
		if (Dic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	*index = node_index + 1;


	return FALSE;
} /* End of SearchCharInCurrentLevel */
