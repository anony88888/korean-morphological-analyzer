/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_FileWrite.c)#  SPASIS System,     Mon Nov 22 15:34:26 1999
 *
 *	#(Action)#
 *		- 파일에 출력한다.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>

UDWORD UTIL_FileWrite(BYTE *buffer, DWORD nitem, DWORD item_size, FILE *fd)
{
	return(fwrite(buffer, item_size, nitem, fd));
} /* End of FileWrite */
