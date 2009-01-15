/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_MemoryMove.c)#  SPASIS System,     Wed Nov 17 20:00:58 1999
 *
 *	#(Action)#
 *		- 데이터를 이동한다.
 *		- 겹치는 부분을 처리하기 위해서 메모리의 위치에 따른 데이터 이동 기법
 *        적용
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MA_UtilLib.h>

tMEMORY* MemoryMove(tMEMORY *dest, tMEMORY *src, UDWORD size)
{
	BYTE *dest_p;
	BYTE *src_p;

	assert(src != NULL);
	assert(dest != NULL);

	src_p = src;
	dest_p = dest;
	if (dest > src) {
		src_p += size;
		dest_p += size;
		while (size > 0) {
			size--;
			src_p--;
			dest_p--;
			*dest_p = *src_p;
		}
	} else if (dest < src) {
		while (size > 0) {
			*dest_p = *src_p;
			dest_p++;
			src_p++;
			size--;
		}
	}

	return dest;
} /* End of MemoryMove */
