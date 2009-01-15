/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_TopicMorpAnal.c)#  SPASIS System,     2000.01.27
 *
 *	#(Action)#
 *		- ��忡 ���� ���¼� �м� ����
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_Func.h>
#include <MA_Token.h>
#include <MA_Interface.h>
#include <MADIC_Type.h>
#include <MADIC_Func.h>

/* �м� ��忡 ���� ���¼� �м� ��� : Topic Analysis */
/* ������ �Է� ���� */
DWORD TopicMorpAnal(HANGUL *hword, UWORD hword_len, DWORD mode, DWORD jong)
{
	DWORD ret_val, i;
	DWORD header_idx;
	DIC_RESULT dic_result[DIC_RESULT_NUM];
	UWORD dic_res_idx;
	HANGUL temp_hword[VS_BUFLEN];

	if (hword_len == 0) {
	    if (mode == SUSA_NOUN)
		return 1;
	    else
		return 0;
	}

	header_idx = GetJosaHeaderIndex(hword[0].j_code);
	if (header_idx == -1)
		return 0;

	/* ���� ������ ���� ����¥�� ���� ������ Ʋ����. */
	if (mode == SUSA_NOUN) {
		if (hword_len == 1)
			return 0;
	}

	        /* mode == COMPNOUN_POSTNOUN_NP */
		/*************** ���̻�� ���� ���� �Է� **********************/
		/* ��м� ���ո�� ���� Ž�� �Ŀ� �������¼Ҹ� �м��ϱ� ���� ��� */
		/* ���̻� ó�� ����, ����/������� ���� ó�� ����, ���ո�� �м� ���� */
		/* ����ó��, '�̴�'ó���� �õ� */

	        /* mode == COMPNOUN_POSTNOUN_P) */
		/*************** �Ϲ���� ���� ���� �Է� **********************/
		/* ��м� ���ո�� ���� Ž�� �Ŀ� �������¼Ҹ� �м��ϱ� ���� ��� */
		/* ����/������� ���� ó�� ����, ���ո�� �м� ���� */
		/* ����ó��, '�̴�'ó��, ���̻� ó�� */
#ifdef COMP_NOUN_DIC_CHECK
	if (mode == SUSA_POSTNOUN || mode == COMPNOUN_POSTNOUN_NP || mode == COMPNOUN_POSTNOUN_P) {
#else
	if (mode == SUSA_POSTNOUN) {
#endif
		/* ��� ������ ���¼Һ��� �м��ϱ� ���ؼ��� 
		   ����Ž���� ���� �ʰ�... �Ϲ������� ��縦 dic_result�� �����Ѵ�.. */
		dic_res_idx = 1;
#ifdef MULTI_DIC_INFO
		dic_result[0].info[0] = 32;
		dic_result[0].info[1] = '\0';
#else
		dic_result[0].info = 32;
#endif
		dic_result[0].len = 2;
		dic_result[0].jong = 0;
		memcpy(temp_hword, hword, sizeof(HANGUL)*hword_len);
		memcpy(&hword[2], temp_hword, sizeof(HANGUL)*hword_len);
		/* ���Ƿ� ���κ��� ���� �ִ´� */
		hword[0].j_code = 0x8861;		/*��*/
		hword[1].j_code = 0x8861;		/*��*/
		hword[1].j_han.jong = jong;
		hword_len += 2;

		ret_val = KAnalysisWord(hword, hword_len, dic_result, dic_res_idx, mode);
		if (ret_val) {
			for (i = 0; i < M_MORPRESULT_INDEX; i++) {
				memcpy(&(M_MORPRESULT_MI_ITEM(i, 0)), &(M_MORPRESULT_MI_ITEM(i, 1)),
					sizeof(tMORP_ITEM) * (M_MORPRESULT_NMORP(i)-1));
				M_MORPRESULT_NMORP(i)--;
			}
		}
		memcpy(&hword[0], &hword[2], sizeof(HANGUL)*(hword_len-2));

		return (ret_val);
	}

	if (mode == SUSA_SEARCH_DIC) {
		ret_val = SearchDic(hword, hword_len, (UWORD) header_idx, dic_result, &dic_res_idx);
		if (ret_val == 0)
			return 0;
		else {
			if (dic_result[dic_res_idx-1].jong)
				return dic_result[dic_res_idx-1].len - 1;
			else
				return dic_result[dic_res_idx-1].len;
		}
	}

	ret_val = SearchDic(hword, hword_len, (UWORD) header_idx, dic_result, &dic_res_idx);
	if (ret_val == 0)
		return 0;

	if (mode == SUSA_UNIT) {
		/* ������� �˻�ÿ� ����Ž�� ��� ������� ������ ������ 
		   ������ Fail */
		for (i = 0; i < dic_res_idx; i++)
#ifdef MULTI_DIC_INFO
			if (strchr((char*)dic_result[i].info, (BYTE) 31)) {
				dic_result[i].info[0] = 31;
				dic_result[i].info[1] = '\0';
				break;
			}
#else
			if (dic_result[i].info[0] == 31)
				break;
#endif
		if (i == dic_res_idx)
			return 0;
	} else if (mode == SUSA_NOUN) {
		/* ������� ��縦 �м��� ��쿡��...
		   ����¥�� ���� �����Ѵ�. */
		for (i = 0; i < dic_res_idx; i++) {
			if (IS_NOUN(dic_result[i].info[0]) && dic_result[i].len <= 1)
				break;
		}
		dic_res_idx = i;
		if (dic_res_idx == 0)
			return 0;
	}

	ret_val = KAnalysisWord(hword, hword_len, dic_result, dic_res_idx, mode);

	if (ret_val)
		return 1;
	else
		return 0;
}
