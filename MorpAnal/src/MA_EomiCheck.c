/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.02.07
 *
 *	#(Action)#
 *		- ��̺� ���¼� �߷� ����
 *		- ��� ��� �˻�, ��� ���� Ž��, ��̺� �������� �˻�
 *  #(Revision History)#
 *		- ��� ó����ƾ �߰� (2000.02.07)
 *		- ��� ���� Ž�� ��ƾ �߰� (2000.02.08)
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_PreEomi.h>
#include <MA_Func.h>
#include <MADIC_Func.h>

/* ��̺� �˻� ��ƾ */
/* h_word�� ��̺� �ѱ��� �տ�������... */
/* Return Value :
   1 --> ���̷� ���� �ܾ�..
   2 --> ���̰� �ƴ� �ٸ� ���¼ҷ� �������� �ùٸ� �ܾ� */
DWORD
CheckEomi(HANGUL *h_word, UWORD h_word_len, WORD first_jong_only)
{
	DWORD sub_idx = 0, bsub_idx;
	DWORD start_pos = 0;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT edic_result[VS_BUFLEN];
#else
	DIC_RESULT edic_result[VS_BUFLEN];
#endif
	UWORD edic_res_idx = 0;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT bdic_result[VS_BUFLEN];
#else
	DIC_RESULT bdic_result[VS_BUFLEN];
	DIC_RESULT tmp_bdic_result[VS_BUFLEN];
#endif
	UWORD bdic_res_idx = 0;
	UWORD tmp_bdic_res_idx = 0;
	DWORD binfo;
	DWORD ret_val, i;
	HANGUL tmpHan;
	HANGUL tmp_h_word[VS_BUFLEN], tmp_h_word2[VS_BUFLEN];
	UWORD tmp_h_word_len;
	UWORD old_nMorp, chk_jong;
	UWORD bojo_eomi_len, bojo_yong_len, tmp_sub_idx;
	UWORD old_Morpheme_Index, old_MorpResult_Index;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT jdic_result[VS_BUFLEN];
#else
	DIC_RESULT jdic_result[VS_BUFLEN];
#endif
	UWORD jdic_res_idx = 0;
	UWORD sia_chukyacc = 0;
        BYTE temp_info[VS_BUFLEN];
	DWORD t_idx, tmp_val;


	if (h_word_len == 0 && first_jong_only == 0)
	    return 0;

	tmpHan.j_han.sign = 1;

	old_MorpResult_Index = M_MORPRESULT_INDEX;
	/* ������� ���� �˻� */
	chk_jong = first_jong_only;
	ret_val = SearchBojoDic(h_word, (UWORD)h_word_len, first_jong_only, bdic_result, &bdic_res_idx);
	if (ret_val == 1) {
		/* ������� ���� �˻� ��� �� info�� �����̿� ��������� �����ġ�̴� */
		/* ������� �������� ������ �����̿� ���յ� ��������...
		   ������ �����̰� �����Ѵ�...
		   ������ �����̴� ���� ��ü�� �����������̷� ���� ���� �����Ƿ�...
		   �߰��Ͽ���. */
		old_nMorp = M_CUR_MORPRESULT_NMORP;
		old_Morpheme_Index = M_MORPHEME_INDEX;
		if (bdic_result[bdic_res_idx-1].info == 5) {
/* �پ����� ��ģ ������ ������ + ������� �������ǿ� ���� tagging ��� ���� */
/* 1. ���� ��ū�� ������ �ƴ� ���
   2. ���� ��ū�� ������ ��....
			- ���� ������ ���� ������ �Բ� ������� ������ ���ԵǾ� ������ ����������� �м�
			- �׷��� ������ �Ϲ� ��� �м� 
*/
#ifndef NO_HEURISTIC_RULE
/* 
	@ RULE(2)
	#TI=������� ���� ���� ����
	#SU=���¼������Ģ(1)
	#AB=1. ���� ��ū�� ������ �ƴ� ���
		2. ���� ��ū�� ������ ��....
			- ���� ������ ���� ������ �Բ� ������� ������ ���ԵǾ� ������ ����������� �м�
			- �׷��� ������ �Ϲ� ��� �м� 
	#TM=2000/05/03
			ret_val = Ref_PreWord(1, tmp_h_word, &tmp_h_word_len);
			if (ret_val != 136 && ret_val != 137)
				goto CHECK_FAIL;

			memcpy(&h_word[h_word_len + 1], tmp_h_word, sizeof(HANGUL) * tmp_h_word_len);
			ret_val = SearchBojoDic(h_word, (UWORD)(h_word_len + tmp_h_word_len), first_jong_only, tmp_bdic_result, &tmp_bdic_res_idx);
			if (ret_val && tmp_bdic_result[tmp_bdic_res_idx-1].len <= bdic_result[bdic_res_idx-1].len)
				goto CHECK_FAIL;
*/
#endif
			/* ���¼� �м� ����... */
			/* �м� ��� ���� */
			/* ��̷ε� �м��� �� �����Ƿ�...���¼� �м� ����� �ϳ��� �����... */
			memcpy(M_NEXT_MORPRESULT_MI, M_CUR_MORPRESULT_MI, sizeof(tMORP_ITEM) * M_CUR_MORPRESULT_NMORP);

			/********************* ���¼� �м� ���� ���� *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (first_jong_only) {
				tmpHan.j_han.cho = 1;
				tmpHan.j_han.jung = 2;
				tmpHan.j_han.jong = h_word[sub_idx].j_han.jong;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), 
					&h_word[sub_idx+1], sizeof(HANGUL) * (bdic_result[bdic_res_idx-1].len-1));
			} else 
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME,
					&h_word[sub_idx+1], sizeof(HANGUL) * bdic_result[bdic_res_idx-1].len);

			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bdic_result[bdic_res_idx-1].len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			/* �ϴ� ��� ���� ������ �������� ���� */
			strcpy(M_CUR_MORPRESULT_MI_INFO, "BOJOEOMI");
			M_MORPHEME_INDEX = 0;
			/* �����Ǿ����Ƿ� */
			/*********************************************************************/

			M_MORPRESULT_INDEX++;
		} else {
			/* ��̷� �м��� ���� �ְ�, '������������+�������' ���� �м��� ���� �ִ�. */
			/* ������� ���� �ұ�Ģ ó���� �˰����� ������ ����� �����Ѵ�. 
			   ���߿� ��������� ������ �ʿ��� ��� �̰��� �ұ�Ģ ó���� �߰��ϸ� �ȴ�... */
			/********************* ���¼� �м� ���� ���� *************************/
			bsub_idx = 0;
			/* ������� ���� ���� */
			if (bdic_result[bdic_res_idx-1].info > 10)
				bojo_eomi_len = bdic_result[bdic_res_idx-1].info % 10;
			else 
				bojo_eomi_len = bdic_result[bdic_res_idx-1].info;

			M_CUR_MORPRESULT_NMORP++;
			if (first_jong_only) {
				tmpHan.j_han.cho = 1;
				tmpHan.j_han.jung = 2;
				tmpHan.j_han.jong = h_word[bsub_idx].j_han.jong;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[bsub_idx+1], sizeof(HANGUL) * (bojo_eomi_len-1));
			} else 
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[bsub_idx+1], sizeof(HANGUL) * bojo_eomi_len);
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_eomi_len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			/* �ϴ� ��� ���� ������ �������� ���� */
			strcpy(M_CUR_MORPRESULT_MI_INFO, "BOJOEOMI");

			M_MORPHEME_INDEX++;
			/*********************************************************************/

			if (first_jong_only)
				bsub_idx += bojo_eomi_len;	/* ��������� ���۵Ǵ� ��ġ�� ���� */
			else
				bsub_idx += bojo_eomi_len + 1;

			bojo_yong_len = bdic_result[bdic_res_idx-1].len - bojo_eomi_len;
			binfo = bdic_result[bdic_res_idx-1].info / 10;
			chk_jong = bdic_result[bdic_res_idx-1].jong;

			/********************* ���¼� �м� ���� ���� *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (chk_jong) {
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[bsub_idx], sizeof(HANGUL) * bojo_yong_len);
				tmpHan.j_code = h_word[bsub_idx + bojo_yong_len - 1].j_code;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
			} else
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[bsub_idx], sizeof(HANGUL) * bojo_yong_len);
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			strcpy(M_CUR_MORPRESULT_MI_INFO, "BOJOYONG");

			M_MORPHEME_INDEX++;
			/*********************************************************************/

			bsub_idx += bojo_yong_len;

			/* ������� �ұ�Ģ ó�� */
			switch (binfo) {
			case 1:		/* �� */
				if (h_word[bsub_idx-1].j_han.jong != 0x01
					&& h_word[bsub_idx-1].j_han.jong != 0x16)
					goto CHECK_FAIL;
				if (h_word[bsub_idx-1].j_han.jong == 0x16 &&
					bsub_idx > h_word_len)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x1D;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB4E1;	/*��*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;

				break;

			case 2:		/* �� */
				if (h_word[bsub_idx-1].j_han.jong != 0x01
					&& h_word[bsub_idx-1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x0D;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB461;	/*��*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;

				break;

			case 3:		/* �� Ż�� */
				if (!chk_jong && bsub_idx > h_word_len)
					goto CHECK_FAIL;

				if (chk_jong) {
				/* ��, ���, ���� ���� ó���ϱ� ���ؼ� 2000.06.27 */
					if (h_word[bsub_idx-1].j_han.jong != 0x05 &&
						h_word[bsub_idx-1].j_han.jong != 0x09 &&
						h_word[bsub_idx-1].j_han.jong != 0x13)
						goto CHECK_FAIL;
				} else {
					if (h_word[bsub_idx].j_han.cho != 0x04 &&
						h_word[bsub_idx].j_han.cho != 0x09 &&
						h_word[bsub_idx].j_han.cho != 0x0B &&
						h_word[bsub_idx].j_code != 0xB5A1)
						goto CHECK_FAIL;
				}

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jong = 0x09;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				M_MORPHEME_INDEX++;

				/*
				tmp_h_word[0].j_code = tmpHan.j_code;
				*/
				tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
				tmp_h_word_len = h_word_len - bsub_idx + 1;
				memcpy(&tmp_h_word[1], &h_word[bsub_idx], sizeof(HANGUL) * tmp_h_word_len);
				break;

			case 4:		/* �� �ұ�Ģ */
				if (h_word[bsub_idx - 1].j_han.jong != 0x01 && 
					h_word[bsub_idx - 1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x12;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB4E1;	/*��*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;
				break;

			case 5:
			case 8:
				if (h_word[bsub_idx-1].j_han.jong != 0x01
					&& h_word[bsub_idx-1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x14;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB4E1;	/*��*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;
				break;

			case 6:
				/* �� --> �� */
				if (h_word[bsub_idx - 1].j_han.jong != 0x01 && 
					h_word[bsub_idx - 1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len - 1) = 0xD061;		/*��*/
				M_MORPHEME_INDEX++;
				tmp_h_word[0].j_code = 0xD061;
				tmp_h_word[1].j_code = 0xB4E1;
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				chk_jong = 0;
				break;

			case 7:
				if (bsub_idx > h_word_len)
					goto CHECK_FAIL;

				ret_val = D_IrrProc(&h_word[bsub_idx-1], (UWORD) (h_word_len - bsub_idx), bojo_yong_len);
				if (ret_val == 0)
					goto CHECK_FAIL;

				tmp_sub_idx = bsub_idx - 1;

				/* �Ű����� '��' ���� ��Ģ ó�� */
				if (chk_jong != 1 && h_word[tmp_sub_idx+1].j_han.cho == 0x0D
					&& h_word[tmp_sub_idx+1].j_han.jung == 0x1B) {		/* -��-*/
					if (h_word[tmp_sub_idx+1].j_han.jong != 0x01) { /* '��' �ؿ� ��ħ�� ���� �� */
						if (h_word[tmp_sub_idx+1].j_han.jong != 0x05		/* �� */
							&& h_word[tmp_sub_idx+1].j_han.jong != 0x09	/* �� */
							&& h_word[tmp_sub_idx+1].j_han.jong != 0x13	/* �� */
							&& h_word[tmp_sub_idx+1].j_han.jong != 0x11)	/* �� */
							goto CHECK_FAIL;
						chk_jong = 1;
						tmp_sub_idx++;		/* �� skip */
					} else {
						tmp_sub_idx++;		/* �� skip */
						if (h_word_len == tmp_sub_idx)
							goto CHECK_FAIL;
					}
				}

				tmp_h_word_len = h_word_len - tmp_sub_idx;
				memcpy(&tmp_h_word, &h_word[tmp_sub_idx], sizeof(HANGUL) * (tmp_h_word_len+1));

				break;

			default :
				/* ��, ����, �� ó��... */
				/* ���ư��� --> ó���� �ȵǼ�.. ����� */
			/* 
			   ��ü������ ó���Ѵ�...
			   �켱 ��� "��"�� "��"�� ������ ���� �߿��� "��"�� ������ ���� ������ ��󳻰�...
			   ���� � �ٷ� ���� ������ "��"�� "��"�� ���۵Ǵ� ����� �ٷ� ���� ������ 
			   "��", "��", "��", "��", "��", "��", "��", "��" �� ��쿡�� ������ "��"�� "��"�� �����Ѵ�...
			   �׷��� �� ���� �߿��� "��"�� "��"�� ��������� ù������ ���� �����Ƿ� �ι� �˻縦 �Ѵ�. 2000.06.29 
			*/
				if (!chk_jong &&
					(h_word[bsub_idx-1].j_han.jung == 0x03
					|| h_word[bsub_idx-1].j_han.jung == 0x04
					|| h_word[bsub_idx-1].j_han.jung == 0x07) 
					&& h_word[bsub_idx-1].j_code != 0xD061
					&& !IsFirstPreEomiChar(h_word[bsub_idx-1])) {
					if (bsub_idx > h_word_len ||
						(bsub_idx <= h_word_len && 
							(h_word[bsub_idx-1].j_han.jung == 0x03 && IsFirstAEomiChar(h_word[bsub_idx])) ||
							((h_word[bsub_idx-1].j_han.jung == 0x04 || h_word[bsub_idx-1].j_han.jung == 0x07)
							 && IsFirstEoEomiChar(h_word[bsub_idx])))) {
						tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
						tmp_h_word[0].j_han.jong = 0x01;
						if (h_word[bsub_idx-1].j_han.jung == 0x03)
							tmp_h_word[1].j_code = 0xb461; /* �� */
						else
							tmp_h_word[1].j_code = 0xb4e1; /* �� */
						tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;

						tmp_h_word_len = h_word_len - bsub_idx + 2;
						memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
						chk_jong = 0;
					} else
						goto NORMAL_PROC_BOJO_CHECK;
				} else if (chk_jong && h_word[bsub_idx-1].j_han.jong == 0x16) {
						tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
						tmp_h_word[0].j_han.jong = 0x01;
						if (YANGSUNG(h_word[bsub_idx-1].j_han.jung) && h_word[bsub_idx-1].j_han.jung != 0x04)
							tmp_h_word[1].j_code = 0xb461; /* �� */
						else
							tmp_h_word[1].j_code = 0xb4e1; /* �� */
						tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;

						tmp_h_word_len = h_word_len - bsub_idx + 2;
						memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
						chk_jong = 0;
				} else {
NORMAL_PROC_BOJO_CHECK:
					if (bsub_idx > h_word_len) {
						if (chk_jong && (bsub_idx - h_word_len) == 1)
							;
						/* ��, ���, ���� ���� ó���ϱ� ���ؼ� 2000.06.27 */
						else if (h_word[bsub_idx-1].j_han.jong == 0x09)
							chk_jong = 1;
						else
							goto CHECK_FAIL;
					}
					tmp_h_word_len = h_word_len - bsub_idx + 1;
					memcpy(tmp_h_word, &h_word[bsub_idx-1], sizeof(HANGUL) * (tmp_h_word_len+1));
				}
/*
				if (((h_word[bsub_idx-1].j_code == 0x8861 || h_word[bsub_idx-1].j_code == 0x9061) && !IsFirstPreEomiChar(h_word[bsub_idx-1]))
					|| (chk_jong && h_word[bsub_idx-1].j_han.jong == 0x16)) {
					tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
					tmp_h_word[0].j_han.jong = 0x01;
					if (YANGSUNG(h_word[bsub_idx-1].j_han.jung) && h_word[bsub_idx-1].j_han.jung != 0x04)
						tmp_h_word[1].j_code = 0xb461;
					else 
						tmp_h_word[1].j_code = 0xb4e1;
					tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
					
					tmp_h_word_len = h_word_len - bsub_idx + 2;
					memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
					chk_jong = 0;
				} else {
					if (bsub_idx > h_word_len) {
						if (chk_jong && (bsub_idx - h_word_len) == 1)
							;
						else if (h_word[bsub_idx-1].j_han.jong == 0x09)
							chk_jong = 1;
						else
							goto CHECK_FAIL;
					}
					tmp_h_word_len = h_word_len - bsub_idx + 1;
					memcpy(tmp_h_word, &h_word[bsub_idx-1], sizeof(HANGUL) * (tmp_h_word_len+1));
				}
*/
				break;
			}
			if (!chk_jong) {
				sub_idx = 0;
				/* ��� ��� �˻� */
				/* ���� : ���� ������ ���ؼ� ������ �˻簡 ������ ���...
						  �Ʒ� �κп��� �������� ���� �� �κп��� �ٷ� ��� Ž���Ͽ�...
						  �ٽ��ѹ� �˻��ؾ� �Ѵ�. */
				/* ��� ��̷� ������ �ܾ�� �����Ƿ�...
				   ���� ��̺δ� �˻��� �������� ���̺��ٴ� ���� �Ѵ� */
		/* 2007.06.07 : �����̰� � �ȵǹǷ�...�׳� ��ü �� �˻� */
				start_pos = 0;
#if 0
				if (tmp_h_word_len - 1 >= 5) /* ��� ��� �� ���� �� ���̺��� ���ų� ũ�� */
					start_pos = 0;
				else if (tmp_h_word_len - 1 > 1)	/* �׷��� ������ ��� ������ ���� */
					start_pos = len_start[tmp_h_word_len-2];
#endif

				for (i = start_pos; i < PRE_EOMI_LEN; i++) {
					/* 2007.06.07 : �߿��� ���� �߰�
					 * �񱳴����̰� �߸������Ǿ��� 
					 * ���� h_word ������ �������� �� ������ �����̷� �߸� �ν��� �� ���� */
					if (tmp_h_word_len < pre_eomi[i].len)
						continue;
					if (!memcmp(&tmp_h_word[1], pre_eomi[i].word, pre_eomi[i].len * 2))
						break;
				}

				if (i < PRE_EOMI_LEN) {
					M_CUR_MORPRESULT_NMORP++;
					memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[1], sizeof(HANGUL) * pre_eomi[i].len);
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_eomi[i].len) = 0;

					strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
					M_CUR_MORPRESULT_MI_NINFO = 1;

					M_MORPHEME_INDEX++;

					/* "��" ������ ��� "��"�� ���� ������ Ʋ�� �ܾ�... */
					if (pre_eomi[i].len == 1 && i == 36) { /* �� */
					    if (tmp_h_word[2].j_code == 0xb461) /* �� */
						goto CHECK_FAIL;
					}
					sub_idx += pre_eomi[i].len;

					/* �ϴ�, �����̷� ������ �ܾ�� ��̰˻縦 ���� �ʰ� 
					   Ʋ�� ������ �����Ѵ�. */
					if (sub_idx == tmp_h_word_len)
						goto CHECK_FAIL;
					

					/* �Ű����� '��' ���� ��Ģ ó�� */
					if (tmp_h_word[sub_idx+1].j_han.cho == 0x0D&& tmp_h_word[sub_idx+1].j_han.jung == 0x1B) { /* -��-*/
					    	if (tmp_h_word[sub_idx].j_han.jong != 0x01 && tmp_h_word[sub_idx].j_han.jong != 0x09) {
							/* ��� '��'�� �ƴ� ��ħ�� ���� �� */
							if (tmp_h_word[sub_idx+1].j_han.jong != 0x01) { /* '��' �ؿ� ��ħ�� ���� �� */
								if (tmp_h_word[sub_idx+1].j_han.jong != 0x05		/* �� */
									&& tmp_h_word[sub_idx+1].j_han.jong != 0x09	/* �� */
									&& tmp_h_word[sub_idx+1].j_han.jong != 0x13	/* �� */
									&& tmp_h_word[sub_idx+1].j_han.jong != 0x11) {	/* �� */
									goto CHECK_FAIL;
								}
								chk_jong = 1;
								sub_idx++;		/* �� skip */
							} else {
								sub_idx++;		/* �� skip */
								if (tmp_h_word_len == sub_idx)
									goto CHECK_FAIL;
							}
						}
					}
				} else {
					/* "��"�� �������� ��̰� ���� �� */
					if (tmp_h_word[1].j_han.cho == 0x0B && tmp_h_word[1].j_han.jung == 0x1D) {
						M_CUR_MORPRESULT_NMORP++;
						tmpHan.j_code = tmp_h_word[1].j_code;
						tmpHan.j_han.jong = 0x01;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
						strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
						M_CUR_MORPRESULT_MI_NINFO = 1;
						M_MORPHEME_INDEX++;

						sub_idx++;
						chk_jong = 1;
					} else if (tmp_h_word[1].j_code == 0xAD61 /* �� */ &&
						(tmp_h_word[2].j_code == 0xB4A1 /* �� */ ||
						 tmp_h_word[2].j_code == 0xACE1 /* �� */ ||
						 tmp_h_word[2].j_code == 0x95A1 /* �� */ ||
						 tmp_h_word[2].j_code == 0xB661 /* �� */)) {
						/* ����, ����... �� ó�� : ��� ó�� */
						/* �׻� ���� ������ ���� ���δ� */
						M_CUR_MORPRESULT_NMORP++;
						tmpHan.j_code = 0xAFA1; /* �� */
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
						strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
						M_CUR_MORPRESULT_MI_NINFO = 1;
						M_MORPHEME_INDEX++;

						sub_idx++;
						memcpy(tmp_h_word2, tmp_h_word, sizeof(HANGUL) * (tmp_h_word_len+1));
						tmp_h_word[1].j_code = 0xAFA1; /* �� */
						tmp_h_word[2].j_code = 0xB4E1; /* �� */
						memcpy(&tmp_h_word[3], &tmp_h_word2[2], sizeof(HANGUL) * (tmp_h_word_len-1));
						tmp_h_word_len++;
					}
				}
			}
/**********************************************************************/
			/* ����� ������� ó�� */
			/* ����� ������̴� �⺻�� ����/����翡 �ٴ´� */
			/* ��, �� */
			if (chk_jong && tmp_h_word[sub_idx].j_han.jong == 0x11) {
				chk_jong = 0;
				/* ����� ������̷� ���� ��� */
				if (tmp_h_word_len - sub_idx == 0) {
					/* ���¼� �м� ����... */
					/* �м� ��� ���� */
					/*********************************************************************/
					M_CUR_MORPRESULT_NMORP++;
					tmpHan.j_han.sign = 1;
					tmpHan.j_han.cho = 0x01;
					tmpHan.j_han.jung = 0x02;
					tmpHan.j_han.jong = 0x11;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
					strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
					M_CUR_MORPRESULT_MI_NINFO = 1;

					M_MORPHEME_INDEX = 0;
					M_MORPRESULT_INDEX++;
					/*********************************************************************/

					sub_idx = 0;
					M_MORPHEME_INDEX = old_Morpheme_Index;
					M_CUR_MORPRESULT_NMORP = old_nMorp;
					memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
				} else {
					/* ���� ���� Ž�� */
					/* �⺻���� ���� ���� �������� �˻� */
					/* ���� �˻縦 ���ؼ� ����Ž���� ������ �� �ܾ �Ѱ��ش� */
					ret_val = SearchJosaDic(&tmp_h_word[sub_idx], (UWORD)(tmp_h_word_len - sub_idx), 
									chk_jong, jdic_result, &jdic_res_idx);
					if (ret_val == 1) {		
						/* ���簡 full-match�� �˻��Ǿ��� �� */
						/* �ϴ� ���� ���� Ž�������� full-match�� ��츦 �ùٸ� ������ ���� */
						ret_val = CheckJosa(tmp_h_word, (UWORD) (sub_idx + 1), chk_jong);
						if (ret_val == 1) {
							/* ���¼� �м� ����... */
							/* �м� ��� ���� */
							M_CUR_MORPRESULT_NMORP++;
							tmpHan.j_han.sign = 1;
							tmpHan.j_han.cho = 0x01;
							tmpHan.j_han.jung = 0x02;
							tmpHan.j_han.jong = 0x11;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
							strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
							M_CUR_MORPRESULT_MI_NINFO = 1;
							M_MORPHEME_INDEX++;

							/********************* ���¼� �м� ���� ���� *************************/
							M_CUR_MORPRESULT_NMORP++;
							memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[sub_idx+1],
								sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
							M_CUR_MORPRESULT_MI_NINFO = 1;

							/* ���� ���� ���� ���� ���� */
							strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

							t_idx = jdic_res_idx-1;
							tmp_val = jdic_result[t_idx].len;
							while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
							    sprintf(temp_info, "%d", jdic_result[t_idx].info);
							    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
							    t_idx--;
							}

							M_MORPHEME_INDEX = 0;
							M_MORPRESULT_INDEX++;
							/*********************************************************************/

							sub_idx = 0;
							M_MORPHEME_INDEX = old_Morpheme_Index;
							M_CUR_MORPRESULT_NMORP = old_nMorp;
							memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
						}
					}
				}

				chk_jong = 1;
				goto CHECK_FAIL;
			} else if (!chk_jong && tmp_h_word[sub_idx+1].j_han.cho == 0x02 && tmp_h_word[sub_idx+1].j_han.jung == 0x1D) {
				sub_idx++;
				if (tmp_h_word[sub_idx].j_han.jong != 0x01)
					chk_jong = 1;

				/* ����� ������̷� ���� ��� */
				if (tmp_h_word_len - sub_idx == 0) {
					/* ���¼� �м� ����... */
					/* �м� ��� ���� */
					M_CUR_MORPRESULT_NMORP++;
					tmpHan.j_code = 0x8BA1;	/*��*/
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
					strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
					M_CUR_MORPRESULT_MI_NINFO = 1;

					M_MORPHEME_INDEX = 0;
					M_MORPRESULT_INDEX++;

					sub_idx = 0;
					M_MORPHEME_INDEX = old_Morpheme_Index;
					M_CUR_MORPRESULT_NMORP = old_nMorp;
					memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
				} else {
					/* ���� ���� Ž�� */
					/* �⺻���� ���� ���� �������� �˻� */
					/* ���� �˻縦 ���ؼ� ����Ž���� ������ �� �ܾ �Ѱ��ش� */
					ret_val = SearchJosaDic(&tmp_h_word[sub_idx], (UWORD)(tmp_h_word_len - sub_idx), 
									chk_jong, jdic_result, &jdic_res_idx);
					if (ret_val == 1) {		
						/* ���簡 full-match�� �˻��Ǿ��� �� */
						/* �ϴ� ���� ���� Ž�������� full-match�� ��츦 �ùٸ� ������ ���� */
						ret_val = CheckJosa(tmp_h_word, (UWORD) (sub_idx + 1), chk_jong);
						if (ret_val == 1) {
							/* ���¼� �м� ����... */
							/* �м� ��� ���� */
							M_CUR_MORPRESULT_NMORP++;
							tmpHan.j_code = 0x8BA1;	/*��*/
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
							strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
							M_CUR_MORPRESULT_MI_NINFO = 1;
							M_MORPHEME_INDEX++;

							/********************* ���¼� �м� ���� ���� *************************/
							M_CUR_MORPRESULT_NMORP++;
							if (chk_jong) {
								tmpHan.j_han.cho = 1;
								tmpHan.j_han.jung = 2;
								tmpHan.j_han.jong = tmp_h_word[sub_idx].j_han.jong;
								M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
								memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &tmp_h_word[sub_idx+1],
									sizeof(HANGUL) * (jdic_result[jdic_res_idx-1].len-1));
							} else 
								memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[sub_idx+1],
									sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
							M_CUR_MORPRESULT_MI_NINFO = 1;

							/* ���� ���� ���� ���� ���� */
							strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

							t_idx = jdic_res_idx-1;
							tmp_val = jdic_result[t_idx].len;
							while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
							    sprintf(temp_info, "%d", jdic_result[t_idx].info);
							    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
							    t_idx--;
							}

							M_MORPHEME_INDEX = 0;
							M_MORPRESULT_INDEX++;
							/*********************************************************************/

							sub_idx = 0;
							M_MORPHEME_INDEX = old_Morpheme_Index;
							M_CUR_MORPRESULT_NMORP = old_nMorp;
							memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);					
						}
					}
				}

				sub_idx--;
				chk_jong = 0;
				goto CHECK_FAIL;
			}

			/* �Ű����� '��' ���� ��Ģ ó�� */
			// 2006-08-02 : �߿��� ���� �߰�!!!
			// - tmp_h_word_len�� ������� �ʰ�, ������ �񱳸� �ϴϱ�...
			// - ������ tmp_h_word�� �����ִ� �����Ͱ� ������ �߻���Ű�� ����
			// - ���� sub_idx+1 ��ġ�� ���Һ񱳸� �� ��,
			// - tmp_h_word_len�� ����ؼ� ���ϵ��� ����
			if ((tmp_h_word_len > sub_idx) && tmp_h_word[sub_idx+1].j_han.cho == 0x0D && tmp_h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -��-*/
				if (tmp_h_word[sub_idx].j_han.jong != 0x01 && tmp_h_word[sub_idx].j_han.jong != 0x09) {
					/* ��� '��'�� �ƴ� ��ħ�� ���� �� */
					if (tmp_h_word[sub_idx+1].j_han.jong != 0x01) { /* '��' �ؿ� ��ħ�� ���� �� */
						if (tmp_h_word[sub_idx+1].j_han.jong != 0x05		/* �� */
							&& tmp_h_word[sub_idx+1].j_han.jong != 0x09	/* �� */
							&& tmp_h_word[sub_idx+1].j_han.jong != 0x13	/* �� */
							&& tmp_h_word[sub_idx+1].j_han.jong != 0x11) {	/* �� */
							goto CHECK_FAIL;
						}
						chk_jong = 1;
						sub_idx++;		/* �� skip */
					} else {
						sub_idx++;		/* �� skip */
						if (tmp_h_word_len == sub_idx)
							goto CHECK_FAIL;
					}
				}
			}

/**********************************************************************/
			/* ��� ���� Ž�� */
			ret_val = SearchEomiDic(&tmp_h_word[sub_idx], (UWORD)(tmp_h_word_len - sub_idx), 
						chk_jong, edic_result, &edic_res_idx);
			if (ret_val == 1) {		/* �������� ��̰� Full�� ������ �� */
				/* ���¼� �м� ����... */
				/* �м� ��� ���� */
				/********************* ���¼� �м� ���� ���� *************************/
				M_CUR_MORPRESULT_NMORP++;
				if (chk_jong) {
					tmpHan.j_han.sign = 1;
					tmpHan.j_han.cho = 1;
					tmpHan.j_han.jung = 2;
					tmpHan.j_han.jong = tmp_h_word[sub_idx].j_han.jong;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &tmp_h_word[sub_idx+1],
						sizeof(HANGUL) * (edic_result[edic_res_idx-1].len-1));
				} else 
					memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[sub_idx+1], 
						sizeof(HANGUL) * edic_result[edic_res_idx-1].len);

				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(edic_result[edic_res_idx-1].len) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;
				/* ���� ���� ���� ���� ���� */
				strcpy(M_CUR_MORPRESULT_MI_INFO, "E");

				t_idx = edic_res_idx-1;
				tmp_val = edic_result[t_idx].len;
				while (t_idx >= 0 && tmp_val == edic_result[t_idx].len) {
				    sprintf(temp_info, "%d", edic_result[t_idx].info);
				    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
				    t_idx--;
				}

				M_MORPRESULT_INDEX++;
				/*********************************************************************/

				sub_idx = 0;
				memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
			} else {
CHECK_FAIL:
				sub_idx = 0;
			}
		}
		M_MORPHEME_INDEX = old_Morpheme_Index;
		M_CUR_MORPRESULT_NMORP = old_nMorp;

	}

	if (!first_jong_only) {
		/* ��� ��� �˻� */
		/* ���� : ���� ������ ���ؼ� ������ �˻簡 ������ ���...
		          �Ʒ� �κп��� �������� ���� �� �κп��� �ٷ� ��� Ž���Ͽ�...
				  �ٽ��ѹ� �˻��ؾ� �Ѵ�. */
		/* ��� ��̷� ������ �ܾ�� �����Ƿ�...
		   ���� ��̺δ� �˻��� �������� ���̺��ٴ� ���� �Ѵ� */

		/* 2007.06.07 : �����̰� � �ȵǹǷ�...�׳� ��ü �� �˻� */
		start_pos = 0;
#if 0
		if (h_word_len - 1 >= 5) /* ��� ��� �� ���� �� ���̺��� ���ų� ũ�� */
			start_pos = 0;
		else if (h_word_len - 1 > 1)	/* �׷��� ������ ��� ������ ���� */
			start_pos = len_start[h_word_len-2];
#endif

		for (i = start_pos; i < PRE_EOMI_LEN; i++) {
			/* 2007.06.07 : �߿��� ���� �߰�
			 * �񱳴����̰� �߸������Ǿ��� 
			 * ���� h_word ������ �������� �� ������ �����̷� �߸� �ν��� �� ����*/
			if (h_word_len < pre_eomi[i].len)
				continue;
			if (!memcmp(&h_word[1], pre_eomi[i].word, pre_eomi[i].len * 2))
				break;
		}

		if (i < PRE_EOMI_LEN) {
			M_CUR_MORPRESULT_NMORP++;
			memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[1], sizeof(HANGUL) * pre_eomi[i].len);
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_eomi[i].len) = 0;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
			M_CUR_MORPRESULT_MI_NINFO = 1;

			M_MORPHEME_INDEX++;

			sub_idx += pre_eomi[i].len;


			/* �ϴ�, �����̷� ������ �ܾ�� ��̰˻縦 ���� �ʰ� 
			   Ʋ�� ������ �����Ѵ�. */
			if (sub_idx == h_word_len) {
				if (M_MORPRESULT_INDEX > old_MorpResult_Index)
					return 2;
				return 0;
			}
			/* "��" ������ ��� "��"�� ���� ������ Ʋ�� �ܾ�... */
			if (i == 36) { /* �� */
			    if (h_word[2].j_code == 0xb461) /* �� */
				return 0;
			}

			/* �Ű����� '��' ���� ��Ģ ó�� */
			if (h_word[sub_idx+1].j_han.cho == 0x0D	&& h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -��-*/
				if (h_word[sub_idx].j_han.jong != 0x01 && h_word[sub_idx].j_han.jong != 0x09) {
					/* ��� '��'�� �ƴ� ��ħ�� ���� �� */
					if (h_word[sub_idx+1].j_han.jong != 0x01) { /* '��' �ؿ� ��ħ�� ���� �� */
						if (h_word[sub_idx+1].j_han.jong != 0x05		/* �� */
							&& h_word[sub_idx+1].j_han.jong != 0x09	/* �� */
							&& h_word[sub_idx+1].j_han.jong != 0x13	/* �� */
							&& h_word[sub_idx+1].j_han.jong != 0x11) {	/* �� */
							if (M_MORPRESULT_INDEX > old_MorpResult_Index)
								return 2;
							return 0;
						}
						first_jong_only = 1;
						sub_idx++;		/* �� skip */
					} else {
						sub_idx++;		/* �� skip */
						if (h_word_len == sub_idx) {
							if (M_MORPRESULT_INDEX > old_MorpResult_Index)
								return 2;
							return 0;
						}
					}
				}
			}
		} else {
			/* "��"�� �������� ��̰� ���� �� */
			if (h_word[1].j_han.cho == 0x0B && h_word[1].j_han.jung == 0x1D) {
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_code = h_word[1].j_code;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;
				
				first_jong_only = 1;
				sub_idx++;
			}  else if (h_word[1].j_code == 0xAD61 /* �� */ &&
						(h_word_len == 1 ||
						 h_word[2].j_code == 0xB4A1 /* �� */ ||
						 h_word[2].j_code == 0xACE1 /* �� */ ||
						 h_word[2].j_code == 0x95A1 /* �� */ ||
						 h_word[2].j_code == 0xB661 /* �� */)) {
				/* ����, ����... �� ó�� : ��� ó�� */
				/* �׻� ���� ������ ���� ���δ� */
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_code = 0xAFA1; /* �� */
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;

				sub_idx++;
				memcpy(tmp_h_word2, h_word, sizeof(HANGUL) * (h_word_len+1));
				h_word[1].j_code = 0xAFA1; /* �� */
				h_word[2].j_code = 0xB4E1; /* �� */
				memcpy(&h_word[3], &tmp_h_word2[2], sizeof(HANGUL) * (h_word_len-1));
				h_word_len++;

				sia_chukyacc = 1;
			}
		}
	}

	/* ����� ������� ó�� */
	/* ����� ������̴� �⺻�� ����/����翡 �ٴ´� */
	/* ��, �� */
	chk_jong = first_jong_only;
	if (chk_jong && h_word[sub_idx].j_han.jong == 0x11) {
		chk_jong = 0;
		/* ����� ������̷� ���� ��� */
		if (h_word_len - sub_idx == 0) {
			/* ���¼� �м� ����... */
			/* �м� ��� ���� */
			M_CUR_MORPRESULT_NMORP++;
			tmpHan.j_han.sign = 1;
			tmpHan.j_han.cho = 0x01;
			tmpHan.j_han.jung = 0x02;
			tmpHan.j_han.jong = 0x11;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
			M_CUR_MORPRESULT_MI_NINFO = 1;
			M_MORPHEME_INDEX = 0;

			return 1;
		}
		/* ���� ���� Ž�� */
		/* �⺻���� ���� ���� �������� �˻� */
		/* ���� �˻縦 ���ؼ� ����Ž���� ������ �� �ܾ �Ѱ��ش� */
		ret_val = SearchJosaDic(&h_word[sub_idx], (UWORD)(h_word_len - sub_idx), 
						chk_jong, jdic_result, &jdic_res_idx);
		if (ret_val == 1) {		
			/* ���簡 full-match�� �˻��Ǿ��� �� */
			/* �ϴ� ���� ���� Ž�������� full-match�� ��츦 �ùٸ� ������ ���� */
			ret_val = CheckJosa(h_word, (UWORD) (sub_idx + 1), chk_jong);
			if (ret_val == 1) {
				/* ���¼� �м� ����... */
				/* �м� ��� ���� */
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = 0x01;
				tmpHan.j_han.jung = 0x02;
				tmpHan.j_han.jong = 0x11;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;

				/********************* ���¼� �м� ���� ���� *************************/
				M_CUR_MORPRESULT_NMORP++;
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[sub_idx+1], sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;
				/* ���� ���� ���� ���� ���� */
				strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

				t_idx = jdic_res_idx-1;
				tmp_val = jdic_result[t_idx].len;
				while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
				    sprintf(temp_info, "%d", jdic_result[t_idx].info);
				    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
				    t_idx--;
				}

				M_MORPHEME_INDEX = 0;
				/*********************************************************************/

				return 1;
			}
		}

		chk_jong = 1;
	} else if (!chk_jong && h_word[sub_idx+1].j_han.cho == 0x02 && h_word[sub_idx+1].j_han.jung == 0x1D) {
		sub_idx++;
		if (h_word[sub_idx].j_han.jong != 0x01)
			chk_jong = 1;

		/* ����� ������̷� ���� ��� */
		if (h_word_len - sub_idx == 0) {
			/* ���¼� �м� ����... */
			/* �м� ��� ���� */
			M_CUR_MORPRESULT_NMORP++;
			tmpHan.j_code = 0x8BA1;	/*��*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
			M_MORPHEME_INDEX = 0;

			return 1;
		}

		/* ���� ���� Ž�� */
		/* �⺻���� ���� ���� �������� �˻� */
		/* ���� �˻縦 ���ؼ� ����Ž���� ������ �� �ܾ �Ѱ��ش� */
		ret_val = SearchJosaDic(&h_word[sub_idx], (UWORD)(h_word_len - sub_idx), 
						chk_jong, jdic_result, &jdic_res_idx);
		if (ret_val == 1) {		
			/* ���簡 full-match�� �˻��Ǿ��� �� */
			/* �ϴ� ���� ���� Ž�������� full-match�� ��츦 �ùٸ� ������ ���� */
			ret_val = CheckJosa(h_word, (UWORD) (sub_idx + 1), chk_jong);
			if (ret_val == 1) {
				/* ���¼� �м� ����... */
				/* �м� ��� ���� */
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_code = 0x8BA1;	/*��*/
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;

				/********************* ���¼� �м� ���� ���� *************************/
				M_CUR_MORPRESULT_NMORP++;
				if (chk_jong) {
					tmpHan.j_han.cho = 1;
					tmpHan.j_han.jung = 2;
					tmpHan.j_han.jong = h_word[sub_idx].j_han.jong;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[sub_idx+1],
						sizeof(HANGUL) * (jdic_result[jdic_res_idx-1].len-1));
				} else 
					memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[sub_idx+1], 
						sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;

				/* ���� ���� ���� ���� ���� */
				strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

				t_idx = jdic_res_idx-1;
				tmp_val = jdic_result[t_idx].len;
				while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
				    sprintf(temp_info, "%d", jdic_result[t_idx].info);
				    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
				    t_idx--;
				}

				M_MORPHEME_INDEX = 0;
				/*********************************************************************/
				return 1;
			}
		}

		sub_idx--;
		chk_jong = 0;
	}

	/* ��� ���� Ž�� */
	ret_val = SearchEomiDic(&h_word[sub_idx], (UWORD)(h_word_len - sub_idx), 
				chk_jong, edic_result, &edic_res_idx);
	if (ret_val == 1) {		/* �������� ��̰� Full�� ������ �� */
			/* ���¼� �м� ����... */
			/* �м� ��� ���� */
			/********************* ���¼� �м� ���� ���� *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (chk_jong) {
				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = 1;
				tmpHan.j_han.jung = 2;
				tmpHan.j_han.jong = h_word[sub_idx].j_han.jong;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[sub_idx+1], 
					sizeof(HANGUL) * (edic_result[edic_res_idx-1].len-1));
			} else 
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[sub_idx+1],
					sizeof(HANGUL) * edic_result[edic_res_idx-1].len);

			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(edic_result[edic_res_idx-1].len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			/* ���� ���� ���� ���� ���� */
			strcpy(M_CUR_MORPRESULT_MI_INFO, "E");

			t_idx = edic_res_idx-1;
			tmp_val = edic_result[t_idx].len;
			while (t_idx >= 0 && tmp_val == edic_result[t_idx].len) {
			    sprintf(temp_info, "%d", edic_result[t_idx].info);
			    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
			    t_idx--;
			}
			/*********************************************************************/
			if (sia_chukyacc)
				memcpy(h_word, tmp_h_word2, sizeof(HANGUL)*h_word_len);


			return 1;
	}

	if (sia_chukyacc)
		memcpy(h_word, tmp_h_word2, sizeof(HANGUL)*h_word_len);

	if (M_MORPRESULT_INDEX > old_MorpResult_Index)
		return 2;

	return 0;
}

DWORD IsFirstPreEomiChar(HANGUL one_char)
{
	switch (one_char.j_code) {
		case 0xB761:
		case 0xAFA1:
		case 0xAD76:
		case 0xB476:
		case 0xB4E1:
		case 0xB4F6:
		case 0xB576:
		case 0x9C61:
		case 0xB5B3:
		case 0x8956:
		case 0x94E1:
			return 1;
		default :
			return 0;
	}

	return 0;
}

/* "��"�� ���۵Ǵ� ����� ���� �������� �˻� */
DWORD IsFirstAEomiChar(HANGUL one_char)
{
	switch (one_char.j_code) {
	case 0xd061: /*��*/
	case 0x95a1: /*��*/
	case 0x9c61: /*��*/
	case 0xace1: /*��*/
	case 0xb4a1: /*��*/
	case 0xb661: /*��*/
	case 0xb861: /*��*/
	case 0xbba1: /*��*/
		return 1;
	default :
		return 0;
	}

	return 0;
}

/* "��"�� ���۵Ǵ� ����� ���� �������� �˻� */
DWORD IsFirstEoEomiChar(HANGUL one_char)
{
	switch (one_char.j_code) {
	case 0xd061: /*��*/
	case 0x95a1: /*��*/
	case 0x9c61: /*��*/
	case 0xace1: /*��*/
	case 0xb4a1: /*��*/
	case 0xb661: /*��*/
	case 0xa165: /*��*/
	case 0xb3a2: /*��*/
		return 1;
	default :
		return 0;
	}

	return 0;
}
