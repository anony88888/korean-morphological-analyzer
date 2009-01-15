/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_MemoryDestroy.c)#  SPASIS System,     Wed Nov 17 17:07:02 1999
 *
 *	#(Action)#
 *		- 할당된 메모리를 헤제
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MA_UtilLib.h>

tVOID MemoryDestroy(tMEMORY *block)
{
	tMEMORY_HEADER *header;

	if (block != NULL) {
		Total_MemAlloc_Bytes -= Memory_Bytes(block) - sizeof(tMEMORY_HEADER);

		header = Memory_Header(block);
		header->size = 0;

		free(header);
	}
} /* End of MemoryDestroy */
