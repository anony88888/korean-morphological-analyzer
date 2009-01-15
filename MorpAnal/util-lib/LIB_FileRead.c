/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_FileRead.c)#  SPASIS System,     Fri Nov 12 12:24:22 1999
 *
 *	#(Action)#
 *		File Read...(per line, per bulk...)
 *		Current File Position을 기준으로...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MA_UtilLib.h>

DWORD UTIL_FileRead(FILE *fd, BYTE *r_buf, WORD mode, DWORD size)
/* WORD mode;		F_READ_LINE, F_READ_BULK_ALL, F_READ_BULK_PART */
{
	DWORD ret_val;			/* Read Size */
	DDWORD file_size;		/* File Size : From Current Position */
	BYTE *ptr_return;		/* Return value of fgets(for exit) */

	switch (mode) {
	case F_READ_LINE:
		ptr_return = fgets(r_buf, size, fd);
		if (ptr_return != NULL) {
			UTIL_CleanStr(r_buf);
			ret_val = strlen(r_buf);
		} else
			ret_val = F_READ_EOF;
		break;

	case F_READ_BULK_ALL:
		fseek(fd, 0L, SEEK_END);
		file_size = ftell(fd);
		ret_val = fread(r_buf, file_size+1, 1, fd);
		fseek(fd, 0L, SEEK_SET);
		break;

	case F_READ_BULK_PART:
		ret_val = fread(r_buf, size, 1, fd);
		break;

	default:
		ret_val = -1;
		break;
	}

	return ret_val;
} /* End of FileRead */
