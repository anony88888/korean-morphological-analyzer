/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_SearchDic.c)#  SPASIS System,     Thu Nov 25 14:53:31 1999
 *
 *	#(Action)#
 *		- ���� Ž�� ���� 
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>
#include <MADIC_Func.h>

/* �ֻ��� Ž�� ��ƾ */
/* return value 1 --> full match or substring match */
/*              0 --> not found */
DWORD SearchDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
{
	DWORD ret_val;

	*res_idx = 0;
	ret_val = SearchWordInTrieDic(h_word, h_word_len, h_idx, result, res_idx);

	return (ret_val);
} /* End of SearchDic */

/* ����� ��� ����Ž���� ���¼Һм� �������� �̷�����Ƿ� 
   ǥ��� ���� ��ȯ������ �ʿ����. ��� ù ���ڿ� ���� 
   ��� �ε����� ���ؾ��ϹǷ� FirstJosaIndex, FirstEomiIndex�� �̿��Ͽ�
   ù ���ڿ� ���� �ε����� ���Ѵ�. */
/* return value 1 --> full match or substring match */
/*              0 --> not found */
#ifdef MULTI_DIC_INFO
DWORD SearchJosaDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, JEDIC_RESULT *result, UWORD *res_idx)
#else
DWORD SearchJosaDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, DIC_RESULT *result, UWORD *res_idx)
#endif
{
	HANGUL one_han;
	DWORD header_idx;
	DWORD ret_val;

	*res_idx = 0;

	if (first_jong_only) {
		/* ù ������ �ʼ� �߼��� ���ش�... */
	    	if (h_word[0].j_han.sign == 0)
		    return 0;
		one_han.j_code = h_word[0].j_code;
		h_word[0].j_han.cho = 1;
		h_word[0].j_han.jung = 2;

		header_idx = GetJosaHeaderIndex(h_word[0].j_code);
		if (header_idx == -1) {
			h_word[0].j_code = one_han.j_code;
			return 0;
		}

		ret_val = SearchJosaInTrieDic(h_word, h_word_len + 1, header_idx, result, res_idx);

		h_word[0].j_code = one_han.j_code;
		/* ���� �ʼ� �߼� ���� */

		/* ���� ���� Ž������ full�� ��ġ�Ǵ� ���簡 ������ 1�� �����ϰ�,
		   �ƴϸ� 0 �� �����Ѵ�. */
		if (ret_val > 0 && result[*res_idx-1].len == h_word_len + 1 && result[*res_idx-1].jong == 0)
			ret_val = 1;
		else
			ret_val = 0;
	} else {
	    	if (h_word[1].j_han.sign == 0)
		    return 0;
		header_idx = GetJosaHeaderIndex(h_word[1].j_code);
		if (header_idx == -1)
			return 0;

		ret_val = SearchJosaInTrieDic(h_word + 1, h_word_len, header_idx, result, res_idx);

		/* ���� ���� Ž������ full�� ��ġ�Ǵ� ���簡 ������ 1�� �����ϰ�,
		   �ƴϸ� 0 �� �����Ѵ�. */
		if (ret_val > 0 && result[*res_idx-1].len == h_word_len && result[*res_idx-1].jong == 0)
			ret_val = 1;
		else
			ret_val = 0;
	}

	return (ret_val);
}

/* return value 1 --> full match or substring match */
/*              0 --> not found */
#ifdef MULTI_DIC_INFO
DWORD SearchEomiDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, JEDIC_RESULT *result, UWORD *res_idx)
#else
DWORD SearchEomiDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, DIC_RESULT *result, UWORD *res_idx)
#endif
{
	HANGUL one_han;
	DWORD header_idx;
	DWORD ret_val;

	*res_idx = 0;

	if (first_jong_only) {
		/* ù ������ �ʼ� �߼��� ���ش�... */
	    	if (h_word[0].j_han.sign == 0)
		    return 0;
		one_han.j_code = h_word[0].j_code;
		h_word[0].j_han.cho = 1;
		h_word[0].j_han.jung = 2;

		header_idx = GetEomiHeaderIndex(h_word[0].j_code);
		if (header_idx == -1) {
			h_word[0].j_code = one_han.j_code;
			return 0;
		}

		ret_val = SearchEomiInTrieDic(h_word, h_word_len + 1, header_idx, result, res_idx);

		h_word[0].j_code = one_han.j_code;
		/* ���� �ʼ� �߼� ���� */

		/* ��� ���� Ž������ full�� ��ġ�Ǵ� ���簡 ������ 1�� �����ϰ�,
		   �ƴϸ� 0 �� �����Ѵ�. */
		if (ret_val > 0 && result[*res_idx-1].len == h_word_len + 1 && result[*res_idx-1].jong == 0)
			ret_val = 1;
		else
			ret_val = 0;
	} else {
	    	if (h_word[1].j_han.sign == 0)
		    return 0;
		header_idx = GetEomiHeaderIndex(h_word[1].j_code);
		if (header_idx == -1)
			return 0;

		ret_val = SearchEomiInTrieDic(h_word + 1, h_word_len, header_idx, result, res_idx);

		/* ��� ���� Ž������ full�� ��ġ�Ǵ� ���簡 ������ 1�� �����ϰ�,
		   �ƴϸ� 0 �� �����Ѵ�. */
		if (ret_val > 0 && result[*res_idx-1].len == h_word_len && result[*res_idx-1].jong == 0)
			ret_val = 1;
		else
			ret_val = 0;
	}

	return (ret_val);
}

/* return value 1 --> full match or substring match */
/*              0 --> not found */
#ifdef MULTI_DIC_INFO
DWORD SearchBojoDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, JEDIC_RESULT *result, UWORD *res_idx)
#else
DWORD SearchBojoDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, DIC_RESULT *result, UWORD *res_idx)
#endif
{
	HANGUL one_han;
	DWORD header_idx;
	DWORD ret_val;

	*res_idx = 0;

	if (first_jong_only) {
		/* ù ������ �ʼ� �߼��� ���ش�... */
	    	if (h_word[0].j_han.sign == 0)
		    return 0;
		one_han.j_code = h_word[0].j_code;
		h_word[0].j_han.cho = 1;
		h_word[0].j_han.jung = 2;

		header_idx = GetBojoHeaderIndex(h_word[0].j_code);
		if (header_idx == -1) {
			h_word[0].j_code = one_han.j_code;
			return 0;
		}

		ret_val = SearchBojoInTrieDic(h_word, h_word_len + 1, header_idx, result, res_idx);

		h_word[0].j_code = one_han.j_code;
		/* ���� �ʼ� �߼� ���� */

		/* ������������ �ܵ����� �˻��� �����Ǹ� 1�� ����...
		   �����������̷� �˻��� �Ǿ��µ� ������ ������ �����ϸ� ����... */
		/* ���� ��ġ�Ǵ� ��������� �����Ѵ�... */
		if (ret_val) {
			if (result[*res_idx-1].info == 5) {
				/* ������ �����̷� Ž�� */
				if (result[*res_idx-1].len != h_word_len + 1 || result[*res_idx-1].jong != 0)
					ret_val = 0;
			} else {
				/* ������ ����������� Ž�� */
			}
		}
/*
		if (result[*res_idx-1].len == h_word_len + 1 && result[*res_idx-1].jong == 0)
			ret_val = 1;
		else
			ret_val = 0;
*/
	} else {
	    	if (h_word[1].j_han.sign == 0)
		    return 0;
		header_idx = GetBojoHeaderIndex(h_word[1].j_code);
		if (header_idx == -1)
			return 0;

		ret_val = SearchBojoInTrieDic(h_word + 1, h_word_len, header_idx, result, res_idx);

		/* ������������ �ܵ����� �˻��� �����Ǹ� 1�� ����...
		   �����������̷� �˻��� �Ǿ��µ� ������ ������ �����ϸ� ����... */
		/* ���� ��ġ�Ǵ� ��������� �����Ѵ�... */
		if (ret_val) {
			if (result[*res_idx-1].info == 5) {
				/* ������ �����̷� Ž�� */
				if (result[*res_idx-1].len != h_word_len || result[*res_idx-1].jong != 0)
					ret_val = 0;
			} else {
				/* ������ ����������� Ž�� */
			}
		}
	}

	return (ret_val);
}
