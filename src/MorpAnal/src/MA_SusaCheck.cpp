/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_SusaCheck.c)#  SPASIS System,     2000.04.20
 *
 *	#(Action)#
 *		- 수사 처리 모듈...
 *        수사 패턴 검사, 수사 처리, 수사 태깅....
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Token.h>
#include <MA_Func.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MADIC_Type.h>
#include <MADIC_Func.h>
#include <MA_Susa.h>

/* 
 * 수사 패턴 검사 모듈 
 * 수사로 예상되는 어절을 Detect... 
 * hword:조합형 한글, hword_len:조합형 한글 길이, word:완성형 한글 
 * "수전치사 + 수 + 단위"에서 "수" 패턴에 해당하는 글자가 존재하면
 * 무조건 수사 
 * - 숫자로 구성된 어절은...
 *   토큰 분리기에서 숫자로 시작되는 어절이 분리되어 나온다...
 */
DWORD CheckSusaWord(HANGUL *hword, DWORD hword_len, UBYTE *word, tMORP_RESULT *sMorpResult, UWORD *sMorpResult_Index)
{
	DWORD dic_ret[512];
	DWORD dic_ret_idx;
	DWORD ret_val;

	*sMorpResult_Index = 0;

	if (word[0] == '\0')
		return 0;

	/* 어절이 숫자로 시작하면 TRUE */
	if (isdigit(word[0])) {
		ret_val = CheckSusa(word, hword, hword_len, BEGIN_WITH_NUM, NULL, 0, sMorpResult, sMorpResult_Index);
		return ret_val;
	}

	/* 길이가 1 이하이면 FALSE */
	if (strlen((char*)word) <= 1)
		return 0;

	/* 만일 수사로 시작하면 OK */
	ret_val = SusaSearch(word, dic_ret, &dic_ret_idx);
	if ( ret_val == 1) {
		ret_val = CheckSusa(word, hword, hword_len, BEGIN_WITH_SUSA, dic_ret, dic_ret_idx, sMorpResult, sMorpResult_Index);
		return ret_val;
	} else if (ret_val == 2) {
		ret_val = CheckSusa(word, hword, hword_len, BEGIN_WITH_SGWAN, dic_ret, dic_ret_idx, sMorpResult, sMorpResult_Index);
		return ret_val;
	}

	return 0;
}

/*
 * 수사 사전 탐색 루틴 
 * 리턴 값은 SusaWord에서의 인덱스들...
 */
DWORD SusaSearch(UBYTE *word, DWORD *dic_ret, DWORD *dic_ret_idx)
{
	H_CHAR fChar;
	DWORD i, index, num;

	/* 한글이 아닌 글자로 시작하는 단어는 무조건 실패... */
	if ((word[0] & 0x80) == 0)
		return 0;
	
	*dic_ret_idx = 0;

	fChar.hl.high = word[0];
	fChar.hl.low = word[1];

	/* 개수가 얼마 안되므로 Linear 탐색으로 함... */
	/* 헤더를 탐색 */
	for (i = 0; i < SUSA_INDEX_NUM; i++)
		if (fChar.code == SusaWordsIndex[i].fChar.code) 
			break;

	if (i == SUSA_INDEX_NUM) {
		if (!strncmp((char*)word, "몇", 2)) {
			dic_ret[*dic_ret_idx] = 90;
			*dic_ret_idx = 1;

			return 2;
		}

		if (!strncmp((char*)word, "여러", 4)) {
			dic_ret[*dic_ret_idx] = 91;
			*dic_ret_idx = 1;

			return 2;
		}

		return 0;
	}

	/* 첫번째 글자로 시작하는 수사의 위치와 개수를 복사 */
	index = SusaWordsIndex[i].idx;
	num = SusaWordsIndex[i].num;

	/* 수사를 탐색 */
	for (i = index; i < index + num; i++) {
		if (!strncmp((char*)word, (char*)SusaWords[i].Str, SusaWords[i].len * 2)) {
			dic_ret[*dic_ret_idx] = i;
			(*dic_ret_idx)++;
		}
	}

	if (*dic_ret_idx == 0) {
		/* 수관형사 처리 : 수, 몇, 여러 */
/*
		if (!strncmp(word, "수", 2)) {
			dic_ret[*dic_ret_idx] = 89;
			*dic_ret_idx = 1;

			return 2;
		}
*/

		if (!strncmp((char*)word, "몇", 2)) {
			dic_ret[*dic_ret_idx] = 90;
			*dic_ret_idx = 1;

			return 2;
		}

		if (!strncmp((char*)word, "여러", 4)) {
			dic_ret[*dic_ret_idx] = 91;
			*dic_ret_idx = 1;

			return 2;
		}

		return 0;
	} else
		return 1;
}

/*
 * 수사 다음에 오는 단위명사 검색 루틴...
 * 최장 길이 일치 기법 적용...
 * 이건 최장길이 일치기법이 아니다...
 * 수정한다...뭔가 착각이 있었던 모양이다.
 */
DWORD SusaUnitSearch(HANGUL *hword, DWORD hword_len, UWORD *idx)
{
    DWORD i, j;

    for (i = SUSA_UNIT_NOUN_NUM-1; i >= 0; i--) {
	for (j = hword_len; j >= 1; j--) {
	    if (DanWiNoun[i].len == j && !strncmp((char*)DanWiNoun[i].jStr, (char*)hword, sizeof(HANGUL) * j))
		break;
	}
	if (j > 0)
	break;
    }

    if (i >= 0) {
	*idx = DanWiNoun[i].idx;
	return DanWiNoun[i].len;
    }

    return 0;
}

/*
 * 실제적인 수사 검사 모듈...
 * 모드에 따라서 숫자로 시작되는 어절, 수사로 시작되는 어절로 구분
 * word			: 한글 스트링(완성형)
 * hword		: 조합형 내부 한글 버퍼 
 * hword_len	: 조합형 한글의 길이
 * mode			: BEGIN_WITH_NUM/BEGIN_WITH_SUSA
 * dres			: 수사로 시작되었을 경우->사전 탐색 결과...
 * dres_idx		: 사전 탐색 결과의 수...
 */
DWORD CheckSusa(UBYTE *word, HANGUL *hword, DWORD hword_len, 
		DWORD mode, DWORD *dres, DWORD dres_idx, tMORP_RESULT *sMorpResult, UWORD *sMorpResult_Index)
{
	UBYTE *pSusaWord;
	tSTATSUSA SusaMorps[VS_BUFLEN];/* 수사 형태소 정의 */
	DWORD SM_index = 0;
	DWORD str_idx, SW_index;
	DWORD hword_index = 0;	/* 수사 분석이 진행됨에 따라서
								달라지는 hword의 현재 위치 */
	DWORD sDicRes[VS_BUFLEN];
	DWORD sDicRes_idx;
	/* 수사 사전 탐색 결과 */
	DWORD ret_val;
	DWORD unit_len;
	DWORD p_jong;
	DWORD yeo_flag, MI_idx;
	UWORD eujon_idx;
	HANGUL tmpHan;

	pSusaWord = word;
	*sMorpResult_Index = 0;

	if (mode == BEGIN_WITH_NUM) {
		/* 숫자를 수사 형태소 버퍼에 저장 */
		str_idx = 0;
		while (*pSusaWord != '\0' && isdigit(*pSusaWord)) {
			SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
			str_idx++;
			pSusaWord++;

			hword_index++;
		}
		SusaMorps[SM_index].Str[str_idx] = '\0';
		SusaMorps[SM_index].mode = NUMBER;
	} else if (mode == BEGIN_WITH_SUSA) {
		/* 수사를 수사 형태소 버퍼에 저장하고 정보를 표시 */
		SW_index = dres[dres_idx-1];
		for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
			SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
			pSusaWord++;
		}

		hword_index += SusaWords[SW_index].len;

		SusaMorps[SM_index].Str[str_idx] = '\0';
		SusaMorps[SM_index].mode = SusaWords[SW_index].info;
	} else if (mode == BEGIN_WITH_SGWAN) {
		/* 수관형사 뒤에는 십,백,천,만,억 단위명사만이 온다고 가정 */
		SW_index = dres[dres_idx-1];
		for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
			SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
			pSusaWord++;
		}

		hword_index += SusaWords[SW_index].len;

		SusaMorps[SM_index].Str[str_idx] = '\0';
		SusaMorps[SM_index].mode = SusaWords[SW_index].info;

		/* 수관형사로만 구성된 어절은 형태소분석 단계에서 처리 */
		if (*pSusaWord == '\0')
			return 0;

		/* '여러' 다음에는 무조건 단위명사만 온다 */
		if (strncmp((char*)word, "여러", 4)) {
			/* 십, 백, 천, 만, 억, 검색 */
			while (1) {
				if (*pSusaWord == '\0')
					break;

				ret_val = SusaSearch(pSusaWord, sDicRes, &sDicRes_idx);
				if (!ret_val || SusaWords[sDicRes[sDicRes_idx-1]].info != SUSA_INFO_7) {
					if (!strncmp((char*)pSusaWord, "십", 2)) {
						sDicRes[0] = 63;
						sDicRes_idx = 1;
					} else
						break;
				}

				SW_index = sDicRes[sDicRes_idx-1];

				/* 수사를 수사 형태소 버퍼에 저장하고 정보를 표시 */
				for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
					SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
					pSusaWord++;
				}

				hword_index += SusaWords[SW_index].len;

				SusaMorps[SM_index].Str[str_idx] = '\0';
				SusaMorps[SM_index].mode = SusaWords[SW_index].info;
				SM_index++;
			}
		}

		/* 단위명사 분석 */
		/* 
		 * 현재는 형태소분석 내에서 단위명사 처리를 하지 않고..
		 * 외부에서 처리를 하게 됨...
		 */
		unit_len = SusaUnitSearch(&hword[hword_index], (UWORD) (hword_len - hword_index), &eujon_idx);
		if (unit_len > 0) {
		    if ((hword_len - hword_index) == unit_len) {
			memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
			sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
			strcpy(sMorpResult[0].MI[0].info, "SUSA");
			sMorpResult[0].MI[0].ninfo = 1;

			if (eujon_idx == 0) {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
			    sMorpResult[0].MI[1].Morpheme[unit_len] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    sMorpResult[0].nMorp = 2;
			} else {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
			    sMorpResult[0].MI[1].Morpheme[eujon_idx] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    memcpy(sMorpResult[0].MI[2].Morpheme, (UWORD *) &hword[hword_index + eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
			    sMorpResult[0].MI[2].Morpheme[unit_len - eujon_idx] = 0;
			    sMorpResult[0].MI[2].info[0] = 30;
			    sMorpResult[0].MI[2].info[1] = 0;
			    sMorpResult[0].MI[2].ninfo = 1;

			    sMorpResult[0].nMorp = 3;
			}

			(*sMorpResult_Index)++;

			/*
			 * 기가, 년도, 동이, 주일 --> 이 단위명사들은 "단위명사 + 조사"로도 분석이 가능함...
			 * 일반 어절 분석을 하지 않고 이곳에서 형태소를 분리하여 결과를 출력...
			 */
			if (unit_len == 2) {
			    if (hword[hword_index].j_code == 0x8ba1 && hword[hword_index+1].j_code == 0x8861) {
				/* 기가 */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "J1");
				sMorpResult[1].MI[2].ninfo = 1;

				sMorpResult[1].nMorp = 3;

				(*sMorpResult_Index)++;
			    } else if (hword[hword_index].j_code == 0x9165 && hword[hword_index+1].j_code == 0x95a1) {
				/* 년도 */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "J6");
				sMorpResult[1].MI[2].ninfo = 1;

				sMorpResult[1].nMorp = 3;

				(*sMorpResult_Index)++;
			    } else if (hword[hword_index].j_code == 0x95b7 && hword[hword_index+1].j_code == 0xb7a1) {
				/* 동이 */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "J1");
				sMorpResult[1].MI[2].ninfo = 1;

				sMorpResult[1].nMorp = 3;

				(*sMorpResult_Index)++;
			    } else if (hword[hword_index].j_code == 0xba81 && hword[hword_index+1].j_code == 0xb7a9) {
				/* 주일 */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				tmpHan.j_code = hword[hword_index+1].j_code; /* 이 */
				tmpHan.j_han.jong = 0x01;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "IDA");
				sMorpResult[1].MI[2].ninfo = 1;

				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = 0x01;
				tmpHan.j_han.jung = 0x02;
				tmpHan.j_han.jong = 0x09;

				memcpy(sMorpResult[1].MI[3].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
				sMorpResult[1].MI[3].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[3].info, "E5");
				sMorpResult[1].MI[3].ninfo = 1;

				sMorpResult[1].nMorp = 4;

				(*sMorpResult_Index)++;
			    }
			}

			return 1;
		    } else { 
			memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
			sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
			strcpy(sMorpResult[0].MI[0].info, "SUSA");
			sMorpResult[0].MI[0].ninfo = 1;

			if (eujon_idx == 0) {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
			    sMorpResult[0].MI[1].Morpheme[unit_len] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    sMorpResult[0].nMorp = 2;
			} else {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
			    sMorpResult[0].MI[1].Morpheme[eujon_idx] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    memcpy(sMorpResult[0].MI[2].Morpheme, (UWORD *) &hword[hword_index + eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
			    sMorpResult[0].MI[2].Morpheme[unit_len-eujon_idx] = 0;
			    sMorpResult[0].MI[2].info[0] = 30;
			    sMorpResult[0].MI[2].info[1] = 0;
			    sMorpResult[0].MI[2].ninfo = 1;

			    sMorpResult[0].nMorp = 3;
			}

			hword_index += unit_len;
			p_jong = hword[hword_index-1].j_han.jong;
			ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
			if (ret_val) {
			    (*sMorpResult_Index)++;
			    return 1;
			}
		    }
		}

		/*
		ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_UNIT);
		if (ret_val) {
			memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
			sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
			strcpy(sMorpResult[0].MI[0].info, "SUSA");
			sMorpResult[0].MI[0].ninfo = 1;
			sMorpResult[0].nMorp = 1;
			(*sMorpResult_Index)++;

			return 1;
		}
		*/

		return 0;
	}

	SM_index++;

	/* 나머지 수사 처리 모듈 */
	while (1) {
		if (*pSusaWord == '\0')
			break;
		if (isdigit(*pSusaWord)) {
			str_idx = 0;
			while (*pSusaWord != '\0' && isdigit(*pSusaWord)) {
				SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
				str_idx++;
				pSusaWord++;

				hword_index++;
			}
			SusaMorps[SM_index].Str[str_idx] = '\0';
			SusaMorps[SM_index].mode = NUMBER;
			SM_index++;

			continue;
		}

		if (*pSusaWord & 0x80) {
			/* 나머지 부분(단위명사, 조사, 복합명사 분석) */
			if (SusaMorps[SM_index-1].mode == SUSA_INFO_3 ||
				SusaMorps[SM_index-1].mode == SUSA_INFO_5 ||
				SusaMorps[SM_index-1].mode == SUSA_INFO_6) {

				/* 수사 휴리스틱스 규칙 *
				 * - 수사 다음의 명사를 분석할 때,
				     이 수사형태소를 포함한 어절이 NORMAL 모드에서 분석 성공하면 명사 분석을 Skip한다. 
				   - 속도가 문제가 될 것 같다...
				   - 수정한다(2000/11/18) 주사전 검색만으로....
				*/
				if (hword_index == 1) {
					ret_val = TopicMorpAnal(hword, (UWORD) hword_len, SUSA_SEARCH_DIC, 0);
					if (ret_val > hword_index)
						return 0;
				}

				/* 단위명사 분석 */
				/* 
				 * 현재는 형태소분석 내에서 단위명사 처리를 하지 않고..
				 * 외부에서 처리를 하게 됨...
				 */

				/*
				 * 10여개...10여년...등 "여"에 대한 처리..
				 */
				yeo_flag = 0;
				MI_idx = 0;
				if (SusaMorps[SM_index-1].mode == SUSA_INFO_5 && hword[hword_index].j_code == 0xb561) {
				    yeo_flag = 1;
				    hword_index++;
				}

				unit_len = SusaUnitSearch(&hword[hword_index], (UWORD) (hword_len - hword_index), &eujon_idx);
				if (unit_len > 0) {
				    if ((hword_len - hword_index) == unit_len) {
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[(hword_index-1)] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					(*sMorpResult_Index)++;

					/*
					 * 기가, 년도, 동이, 주일 --> 이 단위명사들은 "단위명사 + 조사"로도 분석이 가능함...
					 * 일반 어절 분석을 하지 않고 이곳에서 형태소를 분리하여 결과를 출력...
					 */
					if (unit_len == 2) {
					    if (hword[hword_index].j_code == 0x8ba1 && hword[hword_index+1].j_code == 0x8861) {
						/* 기가 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x9165 && hword[hword_index+1].j_code == 0x95a1) {
						/* 년도 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J6");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x95b7 && hword[hword_index+1].j_code == 0xb7a1) {
						/* 동이 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0xba81 && hword[hword_index+1].j_code == 0xb7a9) {
						/* 주일 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_code = hword[hword_index+1].j_code; /* 이 */
						tmpHan.j_han.jong = 0x01;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "IDA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_han.sign = 1;
						tmpHan.j_han.cho = 0x01;
						tmpHan.j_han.jung = 0x02;
						tmpHan.j_han.jong = 0x09;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "E5");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    }
					}
					return 1;
				    } else { 
					MI_idx = 0;
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index-1] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					hword_index += unit_len;
					p_jong = hword[hword_index-1].j_han.jong;
					ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
					if (ret_val) {
					    (*sMorpResult_Index)++;
					    return 1;
					}

					hword_index -= unit_len;
				    }
				}

				if (yeo_flag)
				    hword_index--;

				/*
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_UNIT);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}
				*/

				p_jong = hword[hword_index-1].j_han.jong;
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_NOUN, 0);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				return 0;
			}

			if (SusaMorps[SM_index-1].mode == SUSA_INFO_4) {
				p_jong = hword[hword_index-1].j_han.jong;
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				} else
					return 0;
			}

			/* 수사 사전 탐색 */
			ret_val = SusaSearch(pSusaWord, sDicRes, &sDicRes_idx);
			if (ret_val) {
				SW_index = sDicRes[sDicRes_idx-1];
/**********************************************************/
				/* 각종 제약 조건 제시 */
				switch (SusaWords[SW_index].info) {
				case SUSA_INFO_1 :
					/* 한자형 수사 앞에는 한글 수사가 오지 않는 법이다. */
					if (SusaMorps[SM_index-1].mode == SUSA_INFO_2)
						goto CHECK_REMAIN;
					/* 한자형 수사 앞에는 숫자가 오지 않는다. */
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;

					break;

				case SUSA_INFO_2 :
					/* 한글 수사 앞에는 한자 수사가 오지 않는 법이다 */
					if (SusaMorps[SM_index-1].mode == SUSA_INFO_1)
						goto CHECK_REMAIN;

					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;

					break;

				case SUSA_INFO_3 :
					if (SusaMorps[SM_index-1].mode == NUMBER 
						|| SusaMorps[SM_index-1].mode == SUSA_INFO_7)
						goto CHECK_REMAIN;
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_4 :
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_5 :
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_6 :
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_7 :
					break;

				default :
					break;
				}
/**********************************************************/

				/* 수사를 수사 형태소 버퍼에 저장하고 정보를 표시 */
				for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
					SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
					pSusaWord++;
				}

				hword_index += SusaWords[SW_index].len;

				SusaMorps[SM_index].Str[str_idx] = '\0';
				SusaMorps[SM_index].mode = SusaWords[SW_index].info;
				SM_index++;

				continue;
			} else {
				/* 한자짜리 수사 다음의 단위명사를 분석할 때...
				   이 단어가 일반 형태소분석 모드에서 성공했으면.. SKIP..
				   사회를 --> 사(수사)+회(단위명사)+를(조사)
				   수정한다(2000/11/18) -- 사전 탐색으로...
				*/
				if (SusaMorps[SM_index-1].mode != NUMBER && hword_index == 1) {
					/* '이'로 시작하는 수사는 Fail */
					if (hword[0].j_code == 0xB7A1) /* 이 */
						return 0;
					ret_val = TopicMorpAnal(hword, (UWORD) hword_len, SUSA_SEARCH_DIC, 0);
					if (ret_val > hword_index)
						return 0;
				}
CHECK_REMAIN:
				/* 단위명사 분석 */
				/* 
				 * 현재는 형태소분석 내에서 단위명사 처리를 하지 않고..
				 * 외부에서 처리를 하게 됨...
				 */
				/*
				 * 10여개...10여년...등 "여"에 대한 처리..
				 */
				yeo_flag = 0;
				MI_idx = 0;
				if ((SusaMorps[SM_index-1].mode == SUSA_INFO_7 || SusaMorps[SM_index-1].mode == NUMBER) 
					&& hword[hword_index].j_code == 0xb561) {
				    yeo_flag = 1;
				    hword_index++;
				}

				unit_len = SusaUnitSearch(&hword[hword_index], (UWORD) (hword_len - hword_index), &eujon_idx);
				if (unit_len > 0) {
				    if ((hword_len - hword_index) == unit_len) {
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[(hword_index-1)] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					(*sMorpResult_Index)++;

					/*
					 * 기가, 년도, 동이, 주일 --> 이 단위명사들은 "단위명사 + 조사"로도 분석이 가능함...
					 * 일반 어절 분석을 하지 않고 이곳에서 형태소를 분리하여 결과를 출력...
					 */
					if (unit_len == 2) {
					    if (hword[hword_index].j_code == 0x8ba1 && hword[hword_index+1].j_code == 0x8861) {
						/* 기가 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x9165 && hword[hword_index+1].j_code == 0x95a1) {
						/* 년도 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J6");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x95b7 && hword[hword_index+1].j_code == 0xb7a1) {
						/* 동이 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0xba81 && hword[hword_index+1].j_code == 0xb7a9) {
						/* 주일 */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_code = hword[hword_index+1].j_code; /* 이 */
						tmpHan.j_han.jong = 0x01;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "IDA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_han.sign = 1;
						tmpHan.j_han.cho = 0x01;
						tmpHan.j_han.jung = 0x02;
						tmpHan.j_han.jong = 0x09;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "E5");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    }
					}
					return 1;
				    } else { 
					MI_idx = 0;
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index-1] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* 여 */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					hword_index += unit_len;
					p_jong = hword[hword_index-1].j_han.jong;
					ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
					if (ret_val) {
					    (*sMorpResult_Index)++;
					    return 1;
					}

					hword_index -= unit_len;
				    }
				}

				if (yeo_flag)
				    hword_index--;

				/*
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_UNIT);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}
				*/

				p_jong = hword[hword_index-1].j_han.jong;
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_NOUN, 0);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				return 0;
			}
		}

		pSusaWord++;
	}

	/* 여기까지 왔으면... 수사로만 구성된 어절이다... */

	/* '이'가 단독으로 사용되면 무조건 관형사로 판정한다. */
	if (hword_len == 1 && hword[0].j_code == 0xB7A1) /* 이 */
		return 0;

	memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_len);
	sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
	strcpy(sMorpResult[0].MI[0].info, "SUSA");
	sMorpResult[0].MI[0].ninfo = 1;
	sMorpResult[0].nMorp = 1;
	(*sMorpResult_Index)++;

	return 1;
}
