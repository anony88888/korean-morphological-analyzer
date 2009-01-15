/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_MemoryAppend.c)#  SPASIS System,     Wed Nov 17 16:22:31 1999
 *
 *	#(Action)#
 *		- 현재 메모리 블럭에 메모리를 bytes 만큼 추가 할당 한다.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MA_UtilLib.h>

tMEMORY* MemoryAppend(tMEMORY *block, UDWORD bytes)
{
	tMEMORY_HEADER *new_header = NULL, *old_header = NULL;
	tMEMORY *new_block;
	UDWORD old_size;

	if (block == NULL) 
		return (MemoryCreate(bytes, EM_EXIT));

	if (bytes <= 0)
		return (block);

	old_size = Memory_Bytes(block);
	old_header = Memory_Header(block);

	new_header = (tMEMORY_HEADER *)realloc(old_header, old_size + sizeof(tMEMORY_HEADER) + bytes);

	if (new_header == 0x0)
		printf("Memory Realloc Fail...\n");

	new_block = new_header + 1;
/*
	new_header->size = old_size + sizeof(tMEMORY_HEADER) + bytes;
*/
	new_header->size = old_size + bytes;

	Total_MemAlloc_Bytes += bytes;

	return new_block;
} /* End of MemoryAppend */

tMEMORY* MemoryDelete(tMEMORY *block, UDWORD bytes)
{
	tMEMORY_HEADER *new_header, *old_header;
	tMEMORY *new_block;
	UDWORD old_size;
	UDWORD new_size;

	if (block == NULL) 
		return NULL;

	if (bytes <= 0)
		return (block);

	old_size = Memory_Bytes(block);
	old_header = Memory_Header(block);
	if (old_size <= bytes) {
		new_header = (tMEMORY_HEADER *)realloc(old_header, sizeof(tMEMORY_HEADER));
		new_header->size = 0;
	} else {
		new_size = old_size + sizeof(tMEMORY_HEADER) - bytes;
		new_header = (tMEMORY_HEADER *)realloc(old_header, new_size);
		new_header->size = new_size;
	}
	new_block = new_header + 1;

	Total_MemAlloc_Bytes -= bytes;

	return new_block;
} /* End of MemoryDelete */
