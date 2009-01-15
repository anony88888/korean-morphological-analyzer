/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.27
 *
 *	#(Action)#
 *		- ���� ������������ �˻�
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_JosaConst.h>
#include <MA_Func.h>

DWORD CheckJosa(HANGUL *h_word, UWORD j_pos, UWORD jong)
/* �˻� ���� ���� */
/* ���簡 ���۵Ǵ� �ε��� */
/* ������ ���翡 ���ԵǾ����� ���� */
{
	tCONST_RULE key, *ret;

	if (jong == 0) {
		key.center = 0;		/* code�� 0��° ��ġ�� �˻��� ���ڰ� �� */
		key.code[0] = h_word[j_pos].j_code;

		ret = (tCONST_RULE *)bsearch(&key, JosaConst, JOSACONST_NUM, sizeof(tCONST_RULE), compare_code0);
		if (ret != NULL) {
			switch (ret->rule) {
			case NO_JONG :		/* ���� ���ڿ� ������ ����� ��... */
				if (h_word[j_pos-1].j_han.jong != 1)
					return 0;
				break;
			case YES_JONG :		/* ���� ���ڿ� ������ �־�� ��... */
				if (h_word[j_pos-1].j_han.jong == 1)
					return 0;
				break;
			default :
				break;
			}
		}
	}

	return 1;
}

/* �̵�Ͼ� ó������ ����ϴ� ���� üũ...
   �������� ���� üũ����Ʈ�� ���� ����� ������ ����...*/
DWORD
CheckJosaUnknown(HANGUL *h_word, UWORD j_pos, UWORD jong)
/* �˻� ���� ���� */
/* ���簡 ���۵Ǵ� �ε��� */
/* ������ ���翡 ���ԵǾ����� ���� */
{
	tCONST_RULE key, *ret;

	if (jong == 0) {
		key.center = 0;		/* code�� 0��° ��ġ�� �˻��� ���ڰ� �� */
		key.code[0] = h_word[j_pos].j_code;

		ret = (tCONST_RULE *)bsearch(&key, JosaConst, JOSACONST_NUM, sizeof(tCONST_RULE), compare_code0);
		if (ret != NULL) {
			switch (ret->rule) {
			case NO_JONG :		/* ���� ���ڿ� ������ ����� ��... */
				if (h_word[j_pos-1].j_han.jong != 1)
					return 0;
				break;
			case YES_JONG :		/* ���� ���ڿ� ������ �־�� ��... */
				if (h_word[j_pos-1].j_han.jong == 1)
					return 0;
				break;
			default :
				break;
			}
		} else
			return 0;
	}

	return 1;
}
