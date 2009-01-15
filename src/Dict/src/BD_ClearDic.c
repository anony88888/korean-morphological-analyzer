/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_ClearDic.c)#  SPASIS System,     Thu Nov 25 13:58:19 1999
 *
 *	#(Action)#
 *		- 사전에 할당된 메모리를 해제시킴.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MADIC_Func.h>
#include <MA_UtilLib.h>

#ifdef SHARED_MEMORY_DIC
#include <MA_ShmOP.h>

extern BYTE *sh_MAINDIC_ptr;
#endif

#ifdef MADLL_EXPORTS
DLLMA_API DWORD ClearDic()
#else
DWORD ClearDic()
#endif
{
	DWORD i;

#ifdef SHARED_MEMORY_DIC
	ClearShMem((void **) &sh_MAINDIC_ptr);
#endif

	for (i = 0; i < HEADER_NUM; i++) {
#ifndef SHARED_MEMORY_DIC
		if (Dic_Roots[i] != NULL) {
			MemoryDestroy(Dic_Roots[i]);
		}
#endif
		if (JDic_Roots[i] != NULL) {
			MemoryDestroy(JDic_Roots[i]);
		}
		if (EDic_Roots[i] != NULL) {
			MemoryDestroy(EDic_Roots[i]);
		}
		if (BDic_Roots[i] != NULL) {
			MemoryDestroy(BDic_Roots[i]);
		}
		/*
		if (Tail_Dic_Roots[i] != NULL) {
			MemoryDestroy(Tail_Dic_Roots[i]);
		}
		*/
	}

#ifdef CORPUS_DIC_SEARCH
	ClearCorpusDic();
#endif

#ifdef COMP_NOUN_DIC_CHECK
	ClearCNDic();
#endif
#ifndef DIC_BUILD_MODE
	ClearTAILDic();
#endif
	return TRUE;
} /* End of ClearDic */
