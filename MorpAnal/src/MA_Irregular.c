/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_Irrgular.c)#  SPASIS System,     2000.02.08
 *
 *	#(Action)#
 *		- �ұ�Ģ ó�� ��ƾ ����...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_Func.h>

/* �� �ұ�Ģ ó�� ��ƾ...
   �Է����� ��� ������ �ѱ��ں��� �޴´� */
/* pre_morp_len : �������¼��� ���� */
DWORD S_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len)
{
	HANGUL tmpHan;

	/* ��/��/�� */
	if (h_word[1].j_han.cho == 0x0D 
		&& (h_word[1].j_han.jung == 0x03 
			|| h_word[1].j_han.jung == 0x07
			|| h_word[1].j_han.jung == 0x1B) ) {
		/* �������¼ҿ� Ż���� '��'�� �߰� */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x15;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		return 1;
	}

	return 0;
}

/* �� �ұ�Ģ ó�� ��ƾ...
   �Է����� ��� ������ �ѱ��ں��� �޴´� */
/* pre_morp_len : �������¼��� ���� */
DWORD
D_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len)
{
	HANGUL tmpHan;

	/* ��/��/�� */
	if (h_word[1].j_han.cho == 0x0D 
		&& (h_word[1].j_han.jung == 0x03 
			|| h_word[1].j_han.jung == 0x07
			|| h_word[1].j_han.jung == 0x1B) ) {
		/* �������¼ҿ� Ż���� '��'�� �߰� */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x08;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		return 1;
	}

	return 0;
}

/* �� �ұ�Ģ ó�� ��ƾ...
   �Է����� ��� ������ �ѱ��ں��� �޴´� */
/* pre_morp_len : �������¼��� ���� */
/* s_pos : ��̺ΰ� ���۵Ǵ� ��ġ */
/* jong : ��̺� ó�� �ÿ� �������� ó�� ���� */
DWORD B_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos, UWORD *jong)
{
	HANGUL tmpHan;

	if (h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x14) {
	    /* "�ܿ�" ���� �ý��� �״� ���� �ذ�, 2001/02/12 */
	    	if (h_word_len == 1 && h_word[1].j_han.jong == 0x01)
		    return 0;

		/* �� */
		/* �������¼ҿ� Ż���� '��'�� �߰� */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x13;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		/* ��� ���� : '��' skip */
		(*s_pos)++;
		if (h_word[1].j_han.jong != 0x01)
			*jong = 1;

		return 1;
	}

	if (h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x0E) {
		/* �� */
		/* �������¼ҿ� Ż���� '��'�� �߰� */
		if (pre_morp_len == 1 &&		/* ��-, ��- */
			((h_word[0].j_han.jung == 0x0D && h_word[0].j_han.cho == 0x05) ||
			  (h_word[0].j_han.jung == 0x0D && h_word[0].j_han.cho == 0x02)) ) {
			M_MORPHEME_INDEX--;
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jong = 0x13;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
			M_MORPHEME_INDEX++;

			/* ��� ���� : '��' --> '��' */
			h_word[1].j_han.jung = 0x03;

			return 1;
		} else
			return 0;
	}

	if (h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x15) {
		/* �� */
		/* �������¼ҿ� Ż���� '��'�� �߰� */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x13;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		/* ��� ���� : '��' --> '��' */
		h_word[1].j_han.jung = 0x07;

		return 1;
	}

	return 0;
}

/* �� �ұ�Ģ ó�� ��ƾ...
   �Է����� ��� ������ �ѱ��ں��� �޴´� */
/* pre_morp_len : �������¼��� ���� */
/* s_pos : ��̺ΰ� ���۵Ǵ� ��ġ */
/* jong : ��̺� ó�� �ÿ� �������� ó�� ���� */
DWORD H_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos, UWORD *jong)
{
	HANGUL tmpHan;

	/* ���� ���¼Ҵ� ������ ���̰� 2�̻��̾�� �Ѵ�. */
	if (pre_morp_len < 2)
		return 0;

	/* '��'�� ������ ���� �ܾ�� ������ Ʋ�� */
	if (h_word[0].j_han.jung != 0x04 && h_word[0].j_han.jong == 0x01 && h_word_len == 0)
		return 0;

	/* ������ --> ���� + �Ƽ� */
	if (h_word[0].j_han.jung == 0x04) {	/* �� */
		if (h_word[0].j_han.cho == 0x0D) /* �ʼ��� �� �̸� Ʋ�� */
			return 0;

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-2);

		/* ���׷� --> ���׶� + �� �� �и��� ��...
		   '��'�� ���� ������ ������ ������ ��ġ�� �ʴ´�...*/
		if (pre_morp_len > 2 &&
			(tmpHan.j_han.jung == 0x1B || tmpHan.j_han.jung == 0x1D))
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-3);

		if (YANGSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x03; /* �� */
			tmpHan.j_han.jong = 0x1D; /* �� */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* �� */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x03;

		} else if (EUMSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x07; /* �� */
			tmpHan.j_han.jong = 0x1D; /* �� */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* �� */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x07;
		}

		if (h_word[0].j_han.jong != 0x01 && h_word[0].j_han.jong != 0x16)
			*jong = 1;

		M_MORPHEME_INDEX++;

		return 1;
	}

	/* �Ͼ꼭 --> �Ͼ� + �Ƽ� */
	if (h_word[0].j_han.jung == 0x06 || h_word[0].j_han.jung == 0x0C) {	/* ��, �� */
		if (h_word[0].j_han.cho != 0x0D) /* �ʼ��� �� �� �ƴϸ� Ʋ�� */
			return 0;

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-2);

		/* ���̾� --> ���̾� + �� �� �и��� ��...
		   '��'�� ���� ������ ������ ������ ��ġ�� �ʴ´�...*/
		if (pre_morp_len > 2 &&
			(tmpHan.j_han.jung == 0x1B || tmpHan.j_han.jung == 0x1D))
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-3);

		if (YANGSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x05; /* �� */
			tmpHan.j_han.jong = 0x1D; /* �� */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* �� */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x03;
		} else if (EUMSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x0B; /* �� */
			tmpHan.j_han.jong = 0x1D; /* �� */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* �� */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x07;
		}

		if (h_word[0].j_han.jong != 0x01 && h_word[0].j_han.jong != 0x16)
			*jong = 1;

		M_MORPHEME_INDEX++;

		return 1;
	}

	if (h_word[0].j_han.jong == 0x01)
		return 0;

	M_MORPHEME_INDEX--;
	tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
	tmpHan.j_han.jong = 0x1D;	/* �� */
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
	M_MORPHEME_INDEX++;

	*jong = 1;
	(*s_pos)++;

	return 1;
}

DWORD RUE_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos)
{
	HANGUL tmpHan;

	if (pre_morp_len < 2)
		return 0;

	M_MORPHEME_INDEX--;
	/* �� --> �� */
	tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 2);
	tmpHan.j_han.jong = 0x01;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 2) = tmpHan.j_code;
	/* �� --> �� */
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 1) = 0x9F61; /* �� */

	M_MORPHEME_INDEX++;

	h_word[0].j_han.cho = 0x0D;

	return 1;
}

DWORD EU_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *jong, UWORD *new_len)
{
	HANGUL tmpHan;
	HANGUL tmp_h_word[VS_BUFLEN];

	if (h_word[0].j_han.jong != 0x01 && h_word[0].j_han.jong != 0x16)
		return 0;

	M_MORPHEME_INDEX--;

	tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 1);
	tmpHan.j_han.jung = 0x1B;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 1) = tmpHan.j_code;

	*jong = 0;

	M_MORPHEME_INDEX++;

	memcpy(tmp_h_word, &h_word[1], sizeof(HANGUL) * (h_word_len - 1));
	memcpy(&h_word[2], tmp_h_word, sizeof(HANGUL) * (h_word_len - 1));

	h_word[1].j_han.cho = 0x0D;
	h_word[1].j_han.jung = h_word[0].j_han.jung;
	h_word[1].j_han.jong = h_word[0].j_han.jong;

	(*new_len)++;

	return 1;
}
