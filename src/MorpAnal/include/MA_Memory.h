/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(MA_Memory.h)#           SPASIS System, 29/OCT/1999
 *
 *	#(Action)#
 *		- Variable for Memory Management Routine...
 */

#ifndef _MA_MEMORY_H_
#define _MA_MEMORY_H_

typedef tVOID		tMEMORY;
typedef struct {
		UDWORD size;
		UDWORD item_num;
} tMEMORY_HEADER;

extern DWORD Total_MemAlloc_Bytes;		/* 현재 할당된 메모리의 크기 */

#define Memory_Header(block)	(((tMEMORY_HEADER *)(block))-1)
#define Memory_Bytes(block)		((UDWORD)(((block) == NULL) ? 0 : \
											Memory_Header(block)->size))
#endif /* _MA_MEMORY_H_ */
    
