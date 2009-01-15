/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(BD_InitDicHeader.c)#           SPASIS System, 29/OCT/1999
 *	
 *	#(Action)#
 *		Initiate the header information of Dictionary
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Func.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MADIC_Func.h>

#ifdef MADLL_EXPORTS
DLLMA_API tVOID InitDicHeader()
#else
tVOID
InitDicHeader()
#endif
{
	UWORD i;

	for (i = 0; i < HEADER_NUM; i++) {
		Dic_Header[i].size = 0;
		Dic_Header[i].start = 0;
		Dic_Header[i].items = 0;
		Dic_Roots[i] = NULL;

		JDic_Header[i].size = 0;
		JDic_Header[i].start = 0;
		JDic_Header[i].items = 0;
		JDic_Roots[i] = NULL;

		EDic_Header[i].size = 0;
		EDic_Header[i].start = 0;
		EDic_Header[i].items = 0;
		EDic_Roots[i] = NULL;

		BDic_Header[i].size = 0;
		BDic_Header[i].start = 0;
		BDic_Header[i].items = 0;
		BDic_Roots[i] = NULL;
/*
		Tail_Dic_Header[i].size = 0;
		Tail_Dic_Header[i].start = 0;
		Tail_Dic_Header[i].items = 0;
		Tail_Dic_Roots[i] = NULL;
*/
	}
#ifdef COMP_NOUN_DIC_CHECK
	InitCNDicHeader();
#endif
#ifndef DIC_BUILD_MODE
	InitUserDicHeader();
#endif	
} 
