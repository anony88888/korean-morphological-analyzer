/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_Hj2Hg.c)#  SPASIS System,     Mon May 02 13:40:13 2000
 *
 *	#(Action)#
 *		���ڸ� �ѱ۷� ��ȯ...
 *		
 */

#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Hj2Hg.h>

/* �Է� �Ķ���� hbyte, lbyte�� ��ȯ���̺��� �̿��Ͽ� �ѱ� �ڵ��
   ��ȯ�Ѵ�. ��ȯ�� ���� �״�� hbyte�� lbyte�� ����ȴ�.
*/
UWORD Hj2HgProc(H_CHAR *han_char)
{
	UDWORD offset;
	int h, l;
	
	h = (DWORD) (han_char->hl).high;
	l = (DWORD) (han_char->hl).low;

	if ( (0xCA <= h && h <= 0xFD) && (0xA1 <= l && l <= 0xFE) ) {
		/* �Էµ� ���ڿ����� ��ȯ���̺����� �ɼ��� ���Ѵ� */	
		offset = (UDWORD) ((h-202)*94+l-161);
		han_char->code = HanjaTbl[offset];

		return 1;
	} else
		return 0;
} /* Hj2HgProc */
