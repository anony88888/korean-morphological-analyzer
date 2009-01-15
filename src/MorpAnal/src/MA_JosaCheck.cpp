/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.27
 *
 *	#(Action)#
 *		- 조사 결합제약조건 검사
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_JosaConst.h>
#include <MA_Func.h>

DWORD CheckJosa(HANGUL *h_word, UWORD j_pos, UWORD jong)
/* 검사 중인 어절 */
/* 조사가 시작되는 인덱스 */
/* 종성이 조사에 포함되었는지 여부 */
{
	tCONST_RULE key, *ret;

	if (jong == 0) {
		key.center = 0;		/* code의 0번째 위치에 검색할 글자가 들어감 */
		key.code[0] = h_word[j_pos].j_code;

		ret = (tCONST_RULE *)bsearch(&key, JosaConst, JOSACONST_NUM, sizeof(tCONST_RULE), compare_code0);
		if (ret != NULL) {
			switch (ret->rule) {
			case NO_JONG :		/* 이전 글자에 종성이 없어야 함... */
				if (h_word[j_pos-1].j_han.jong != 1)
					return 0;
				break;
			case YES_JONG :		/* 이전 글자에 종성이 있어야 함... */
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

/* 미등록어 처리에서 사용하는 조사 체크...
   차이점은 현재 체크리스트에 없는 조사는 무조건 실패...*/
DWORD
CheckJosaUnknown(HANGUL *h_word, UWORD j_pos, UWORD jong)
/* 검사 중인 어절 */
/* 조사가 시작되는 인덱스 */
/* 종성이 조사에 포함되었는지 여부 */
{
	tCONST_RULE key, *ret;

	if (jong == 0) {
		key.center = 0;		/* code의 0번째 위치에 검색할 글자가 들어감 */
		key.code[0] = h_word[j_pos].j_code;

		ret = (tCONST_RULE *)bsearch(&key, JosaConst, JOSACONST_NUM, sizeof(tCONST_RULE), compare_code0);
		if (ret != NULL) {
			switch (ret->rule) {
			case NO_JONG :		/* 이전 글자에 종성이 없어야 함... */
				if (h_word[j_pos-1].j_han.jong != 1)
					return 0;
				break;
			case YES_JONG :		/* 이전 글자에 종성이 있어야 함... */
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
