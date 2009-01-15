/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(MA_ReturnCode.h)#           SPASIS System, 09/NOV/1999
 *
 *	#(Action)#
 *		Global Macro Definition.
 */
#ifndef _MA_RETURNCODE_H_
#define _MA_RETURNCODE_H_

#define TRUE			1
#define FALSE			0

#define SUCCESS			1
#define FAIL			0

/* UTIL_FileOpen uses this MACRO */
#define F_READ			101 /* read only mode */
#define F_WRITE			102 /* write only mode */
#define F_APPEND		103 /* append only mode */

#define EM_EXIT			201 /* Exit Program when error */
#define EM_RETURN		202 /* Return Error Code when error */

#define DIC_NOTFOUND	301
#endif /* _MA_RETURNCODE_H_ */

