/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_SearchDic.c)#  SPASIS System,     Thu Nov 25 14:53:31 1999
 *
 *	#(Action)#
 *		- 사전 탐색 수행 
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>
#include <MADIC_Func.h>

/* 주사전 탐색 루틴 */
/* return value 1 --> full match or substring match */
/*              0 --> not found */
DWORD SearchDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
{
	DWORD ret_val;

	*res_idx = 0;
	ret_val = SearchWordInTrieDic(h_word, h_word_len, h_idx, result, res_idx);

	return (ret_val);
} /* End of SearchDic */

/* 조사와 어미 사전탐색은 형태소분석 과정에서 이루어지므로 
   표제어에 대한 변환과정이 필요없다. 대신 첫 글자에 대한 
   헤더 인덱스를 구해야하므로 FirstJosaIndex, FirstEomiIndex를 이용하여
   첫 글자에 대한 인덱스를 구한다. */
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
		/* 첫 글자의 초성 중성을 없앤다... */
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
		/* 없앤 초성 중성 복귀 */

		/* 조사 사전 탐색에서 full로 매치되는 조사가 있으면 1을 리턴하고,
		   아니면 0 을 리턴한다. */
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

		/* 조사 사전 탐색에서 full로 매치되는 조사가 있으면 1을 리턴하고,
		   아니면 0 을 리턴한다. */
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
		/* 첫 글자의 초성 중성을 없앤다... */
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
		/* 없앤 초성 중성 복귀 */

		/* 어미 사전 탐색에서 full로 매치되는 조사가 있으면 1을 리턴하고,
		   아니면 0 을 리턴한다. */
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

		/* 어미 사전 탐색에서 full로 매치되는 조사가 있으면 1을 리턴하고,
		   아니면 0 을 리턴한다. */
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
		/* 첫 글자의 초성 중성을 없앤다... */
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
		/* 없앤 초성 중성 복귀 */

		/* 보조적연결어미 단독으로 검색이 성공되면 1을 리턴...
		   보조적연결어미로 검색이 되었는데 나머지 어절이 존재하면 실패... */
		/* 최장 일치되는 보조용언을 선택한다... */
		if (ret_val) {
			if (result[*res_idx-1].info == 5) {
				/* 보조적 연결어미로 탐색 */
				if (result[*res_idx-1].len != h_word_len + 1 || result[*res_idx-1].jong != 0)
					ret_val = 0;
			} else {
				/* 결합형 보조용언으로 탐색 */
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

		/* 보조적연결어미 단독으로 검색이 성공되면 1을 리턴...
		   보조적연결어미로 검색이 되었는데 나머지 어절이 존재하면 실패... */
		/* 최장 일치되는 보조용언을 선택한다... */
		if (ret_val) {
			if (result[*res_idx-1].info == 5) {
				/* 보조적 연결어미로 탐색 */
				if (result[*res_idx-1].len != h_word_len || result[*res_idx-1].jong != 0)
					ret_val = 0;
			} else {
				/* 결합형 보조용언으로 탐색 */
			}
		}
	}

	return (ret_val);
}
