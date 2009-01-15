/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_MemoryCreate.c)#  SPASIS System,     Wed Nov 17 12:44:13 1999
 *
 *	#(Action)#
 *		���ο� �޸� ���۸� �����Ѵ�.
 *		���Ǵ� �������� : Total_MemAlloc_Bytes
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MA_UtilLib.h>

tMEMORY * MemoryCreate(UDWORD bytes, DWORD mode)
{
	tMEMORY_HEADER *header;		/* �޸� ��� */
	tMEMORY *block;				/* �Ҵ�� �޸� ������ */

	if (bytes == 0)
		return NULL;

	header = (tMEMORY_HEADER *) malloc(sizeof(tMEMORY_HEADER) + bytes);
	if (header == NULL) {
		if (mode == EM_EXIT) {
			fprintf(stderr, "In MemoryCreate : allocation failure...\n");
			exit(1);
		} else if (mode == EM_RETURN) {
			return NULL;
		}
	}

	header->size = bytes;
	Total_MemAlloc_Bytes += bytes;

	block = (tMEMORY *)(header + 1);

	return (block);
} /* End of MemoryCreate */
