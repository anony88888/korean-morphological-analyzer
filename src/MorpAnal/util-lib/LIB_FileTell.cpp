/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_FileTell.c)#  SPASIS System,     Thu Nov 25 10:36:12 1999
 *
 *	#(Action)#
 *		_WRITE_FUNCTION_
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>

DWORD UTIL_FileTell(FILE *fd)
{
	return (ftell(fd));
} /* End of FileTell */
