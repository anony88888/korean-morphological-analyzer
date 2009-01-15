/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(LIB_FileClose.c)#		SPASIS System, 09/NOV/1999
 *	
 *	#(Action)#
 *		Close a File.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>

tVOID UTIL_FileClose(FILE *fd)
{
	fclose(fd);
}
