/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_Irrgular.c)#  SPASIS System,     2000.02.08
 *
 *	#(Action)#
 *		- 불규칙 처리 루틴 모음...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_Func.h>

/* ㅅ 불규칙 처리 루틴...
   입력으로 어간의 마지막 한글자부터 받는다 */
/* pre_morp_len : 실질형태소의 길이 */
DWORD S_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len)
{
	HANGUL tmpHan;

	/* 아/어/으 */
	if (h_word[1].j_han.cho == 0x0D 
		&& (h_word[1].j_han.jung == 0x03 
			|| h_word[1].j_han.jung == 0x07
			|| h_word[1].j_han.jung == 0x1B) ) {
		/* 실질형태소에 탈락된 'ㅅ'을 추가 */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x15;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		return 1;
	}

	return 0;
}

/* ㄷ 불규칙 처리 루틴...
   입력으로 어간의 마지막 한글자부터 받는다 */
/* pre_morp_len : 실질형태소의 길이 */
DWORD
D_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len)
{
	HANGUL tmpHan;

	/* 아/어/으 */
	if (h_word[1].j_han.cho == 0x0D 
		&& (h_word[1].j_han.jung == 0x03 
			|| h_word[1].j_han.jung == 0x07
			|| h_word[1].j_han.jung == 0x1B) ) {
		/* 실질형태소에 탈락된 'ㄷ'을 추가 */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x08;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		return 1;
	}

	return 0;
}

/* ㅂ 불규칙 처리 루틴...
   입력으로 어간의 마지막 한글자부터 받는다 */
/* pre_morp_len : 실질형태소의 길이 */
/* s_pos : 어미부가 시작되는 위치 */
/* jong : 어미부 처리 시에 종성부터 처리 여부 */
DWORD B_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos, UWORD *jong)
{
	HANGUL tmpHan;

	if (h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x14) {
	    /* "겨우" 에서 시스템 죽는 문제 해결, 2001/02/12 */
	    	if (h_word_len == 1 && h_word[1].j_han.jong == 0x01)
		    return 0;

		/* 우 */
		/* 실질형태소에 탈락된 'ㅂ'을 추가 */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x13;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		/* 어미 변형 : '우' skip */
		(*s_pos)++;
		if (h_word[1].j_han.jong != 0x01)
			*jong = 1;

		return 1;
	}

	if (h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x0E) {
		/* 와 */
		/* 실질형태소에 탈락된 'ㅂ'을 추가 */
		if (pre_morp_len == 1 &&		/* 돕-, 곱- */
			((h_word[0].j_han.jung == 0x0D && h_word[0].j_han.cho == 0x05) ||
			  (h_word[0].j_han.jung == 0x0D && h_word[0].j_han.cho == 0x02)) ) {
			M_MORPHEME_INDEX--;
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jong = 0x13;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
			M_MORPHEME_INDEX++;

			/* 어미 변형 : '와' --> '아' */
			h_word[1].j_han.jung = 0x03;

			return 1;
		} else
			return 0;
	}

	if (h_word[1].j_han.cho == 0x0D && h_word[1].j_han.jung == 0x15) {
		/* 워 */
		/* 실질형태소에 탈락된 'ㅂ'을 추가 */
		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
		tmpHan.j_han.jong = 0x13;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		/* 어미 변형 : '워' --> '어' */
		h_word[1].j_han.jung = 0x07;

		return 1;
	}

	return 0;
}

/* ㅎ 불규칙 처리 루틴...
   입력으로 어간의 마지막 한글자부터 받는다 */
/* pre_morp_len : 실질형태소의 길이 */
/* s_pos : 어미부가 시작되는 위치 */
/* jong : 어미부 처리 시에 종성부터 처리 여부 */
DWORD H_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos, UWORD *jong)
{
	HANGUL tmpHan;

	/* 이전 형태소는 무조건 길이가 2이상이어야 한다. */
	if (pre_morp_len < 2)
		return 0;

	/* 'ㅐ'로 끝나지 않은 단어는 무조건 틀림 */
	if (h_word[0].j_han.jung != 0x04 && h_word[0].j_han.jong == 0x01 && h_word_len == 0)
		return 0;

	/* 빨개서 --> 빨갛 + 아서 */
	if (h_word[0].j_han.jung == 0x04) {	/* ㅐ */
		if (h_word[0].j_han.cho == 0x0D) /* 초성이 ㅇ 이면 틀림 */
			return 0;

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-2);

		/* 동그래 --> 동그랗 + 아 로 분리할 때...
		   '그'는 다음 글자의 모음에 영향을 미치지 않는다...*/
		if (pre_morp_len > 2 &&
			(tmpHan.j_han.jung == 0x1B || tmpHan.j_han.jung == 0x1D))
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-3);

		if (YANGSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x03; /* ㅏ */
			tmpHan.j_han.jong = 0x1D; /* ㅎ */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* 아 */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x03;

		} else if (EUMSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x07; /* ㅓ */
			tmpHan.j_han.jong = 0x1D; /* ㅎ */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* 어 */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x07;
		}

		if (h_word[0].j_han.jong != 0x01 && h_word[0].j_han.jong != 0x16)
			*jong = 1;

		M_MORPHEME_INDEX++;

		return 1;
	}

	/* 하얘서 --> 하얗 + 아서 */
	if (h_word[0].j_han.jung == 0x06 || h_word[0].j_han.jung == 0x0C) {	/* ㅒ, ㅖ */
		if (h_word[0].j_han.cho != 0x0D) /* 초성이 ㅇ 이 아니면 틀림 */
			return 0;

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-2);

		/* 하이얘 --> 하이얗 + 아 로 분리할 때...
		   '이'는 다음 글자의 모음에 영향을 미치지 않는다...*/
		if (pre_morp_len > 2 &&
			(tmpHan.j_han.jung == 0x1B || tmpHan.j_han.jung == 0x1D))
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-3);

		if (YANGSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x05; /* ㅑ */
			tmpHan.j_han.jong = 0x1D; /* ㅎ */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* 아 */
			h_word[0].j_han.cho = 0x0D;
			h_word[0].j_han.jung = 0x03;
		} else if (EUMSUNG(tmpHan.j_han.jung)) {
			tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1);
			tmpHan.j_han.jung = 0x0B; /* ㅕ */
			tmpHan.j_han.jong = 0x1D; /* ㅎ */
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len-1) = tmpHan.j_code;

			/* 어 */
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
	tmpHan.j_han.jong = 0x1D;	/* ㅎ */
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
	/* 흘 --> 흐 */
	tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 2);
	tmpHan.j_han.jong = 0x01;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 2) = tmpHan.j_code;
	/* 러 --> 르 */
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_morp_len - 1) = 0x9F61; /* 르 */

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
