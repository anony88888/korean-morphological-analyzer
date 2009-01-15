/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_Irrgular.c)#  SPASIS System,     2000.02.08
 *
 *	#(Action)#
 *		- �̴� ó�� ��ƾ..
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_Func.h>

DWORD CheckIda(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	HANGUL tmp_h_word[VS_BUFLEN];
	UWORD chk_jong;
	HANGUL tmpHan;
	DWORD ret_val;

	if (!jong && h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x1D) {
		/* �̷� ������ ������ Ʋ���� */
		if (h_word[1].j_han.jong == 1 && h_word_len == 1)
			return 0;

		if (h_word_len > 1 && h_word[2].j_code == 0x9365) /* �� */
			return 0;

		/* ��- */
		/********************* ���¼� �м� ���� ���� *************************/
		M_CUR_MORPRESULT_NMORP++;
		tmpHan.j_code = h_word[1].j_code;
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "IDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		if (h_word[1].j_han.jong != 1)
			chk_jong = 1;
		else
			chk_jong = 0;

		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), chk_jong);
		if (ret_val == 1)
			return 1;
		else if (ret_val == 2) {
			M_MORPRESULT_INDEX--;
			return 1;
		}
	} else if (!jong && h_word[1].j_code == 0xB576) {
		/* ��- */
		/* '��'���� ������ ������ Ʋ���� */
		if (h_word[1].j_han.jong == 1 && h_word_len == 1)
			return 0;
		/********************* ���¼� �м� ���� ���� *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xB7A1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "IDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/

		/* ���� ������... */
		tmp_h_word[0].j_code = 0xB7A1;	/*��*/
		tmp_h_word[1].j_code = 0xB4F6;	/*��*/
		memcpy(&tmp_h_word[2], &h_word[2], sizeof(HANGUL) * (h_word_len - 1));

		ret_val = CheckEomi(tmp_h_word, h_word_len, 0);
		if (ret_val == 1)
			return 1;
		else if (ret_val == 2) {
			M_MORPRESULT_INDEX--;
			return 1;
		}

	} else if (!jong && h_word[1].j_code == 0x9461) {		/* �� */
		/* ������ '��'�� ������...*/
		/********************* ���¼� �м� ���� ���� *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xB7A1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "IDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/	

		/********************* ���¼� �м� ���� ���� *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9461;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "E13");

		M_MORPHEME_INDEX++;
		/*********************************************************************/	

		return 1;
	}

	return 0;
}
