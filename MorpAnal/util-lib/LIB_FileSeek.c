/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_FileSeek.c)#  SPASIS System,     Thu Nov 25 10:28:33 1999
 *
 *	#(Action)#
 *		_WRITE_FUNCTION_
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>

DWORD UTIL_FileSeek(FILE *fd, DWORD idx, WORD pos)
{
	switch (pos) {
	case F_SEEK_START:
		fseek(fd, idx, SEEK_SET);
		break;
	case F_SEEK_END:
		fseek(fd, idx, SEEK_END);
		break;
	case F_SEEK_CUR:
		fseek(fd, idx, SEEK_CUR);
		break;
	default:
		fseek(fd, idx, SEEK_SET);
		break;
	}

	return TRUE;
} /* End of FileSeek */
