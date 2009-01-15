/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(LIB_CleanStr.c)#  SPASIS System,     Mon Nov 15 10:24:32 1999
 *
 *	#(Action)#
 *		Remove Control Character, Garbage Character in String.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>

tVOID UTIL_CleanStr(BYTE *str)
{
	BYTE *ptr;
	DWORD len = strlen(str);

	ptr = str; 		/* pre-space remove */
	while (*ptr != '\0' && *ptr == ' ')
		ptr++;
	strcpy(str, ptr);

	ptr = &str[len-1];	/* post-garbage remove */
	while (len >= 0 && (*ptr == ' ' || *ptr == 13 || *ptr == '\n'))
		ptr--;
	*(ptr+1) = '\0';
} /* End of CleanStr */
