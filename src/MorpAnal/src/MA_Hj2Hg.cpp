/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_Hj2Hg.c)#  SPASIS System,     Mon May 02 13:40:13 2000
 *
 *	#(Action)#
 *		한자를 한글로 변환...
 *		
 */

#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Hj2Hg.h>

/* 입력 파라메터 hbyte, lbyte를 변환테이블을 이용하여 한글 코드로
   변환한다. 변환된 값은 그대로 hbyte와 lbyte에 저장된다.
*/
UWORD Hj2HgProc(H_CHAR *han_char)
{
	UDWORD offset;
	int h, l;
	
	h = (DWORD) (han_char->hl).high;
	l = (DWORD) (han_char->hl).low;

	if ( (0xCA <= h && h <= 0xFD) && (0xA1 <= l && l <= 0xFE) ) {
		/* 입력된 한자에대한 변환테이블에서의 옵셋을 구한다 */	
		offset = (UDWORD) ((h-202)*94+l-161);
		han_char->code = HanjaTbl[offset];

		return 1;
	} else
		return 0;
} /* Hj2HgProc */
