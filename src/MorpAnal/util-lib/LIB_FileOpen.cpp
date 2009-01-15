/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(LIB_FileOpen.c)#		SPASIS System, 09/NOV/1999
 *	
 *	#(Action)#
 *		Open a File, Handling Open Error.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>

/*
 * The result situation of Function Execution 
 *					Success : SUCCESS, Fail : FAIL
 * BYTE *fname;	File Name
 * UWORD mode;	Open Mode : F_READ, F_WRITE, F_APPEND
 * UWORD exec_mode;	Execution Mode : EM_EXIT, EM_RETURN
 *  					EM_EXIT : exit when error occur
 * 					EM_RETURN : return fail code when error occur
 * UWORD file_mode;	F_TEXT : Text mode file open
 * 					F_BINARY : Binary mode file open
 */
UWORD UTIL_FileOpen(BYTE *fname, UWORD mode, UWORD exec_mode, UWORD file_mode, FILE **fd)
{
	BYTE f_mode[VS_BUFLEN];
	switch (mode) {
	case F_READ:
		strcpy(f_mode, "r");
		if (file_mode == F_TEXT)
			strcat(f_mode, "t");
		else if (file_mode == F_BINARY)
			strcat(f_mode, "b");

		*fd = fopen(fname, f_mode);
		
		break;
	case F_WRITE:
		strcpy(f_mode, "w");
		if (file_mode == F_TEXT)
			strcat(f_mode, "t");
		else if (file_mode == F_BINARY)
			strcat(f_mode, "b");

		*fd = fopen(fname, f_mode);
		break;
	case F_APPEND:
		strcpy(f_mode, "a");
		if (file_mode == F_TEXT)
			strcat(f_mode, "t");
		else if (file_mode == F_BINARY)
			strcat(f_mode, "b");

		*fd = fopen(fname, f_mode);
		break;
	default:
		*fd = NULL;
	}

	if (*fd == NULL) {
		switch (exec_mode) {
		case EM_EXIT:
			exit(1);
		case EM_RETURN:
			return FAIL;
		default:
			return FAIL;
		}
	} else {
		return SUCCESS;
	}
}
