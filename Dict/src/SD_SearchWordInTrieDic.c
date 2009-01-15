/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_SearchWordInTrieDic.c)#  SPASIS System,     Thu Nov 25 15:34:56 1999
 *
 *	#(Action)#
 *		- 실제적인 사전 탐색 수행 
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MADIC_Func.h>

DWORD SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;  /* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;
	UDWORD old_node_index1; 
	UDWORD old_node_index2;
	UDWORD cur_level_start_index;
	HANGUL one_char;
	UWORD ret_val;
	UDWORD old_h_idx;
#ifdef MULTI_DIC_INFO
	UWORD noun_info_cnt;
	UBYTE noun_info_buf[50];
#endif

	one_char.j_han.sign = 1;
	if (Dic_Header[h_idx].size == 0) {
	    	if (h_word[0].j_han.sign == 0)
		    return 0;
	    	if (h_idx < WANSUNG_JASO_NUM) {
		    *res_idx = 0;
		    return 0;
		}
		h_idx = GetNoJongIndex(h_idx);
		/* 만약 "각"이라는 글자에 대한 종성없는 글자는 "가"(헤더인덱스 51) */
		if (Dic_Header[h_idx].size == 0) {
			*res_idx = 0;
			return 0;
		}

		char_index = 0;
		one_char.j_han.cho = h_word[char_index].j_han.cho;
		one_char.j_han.jung = h_word[char_index].j_han.jung;
		one_char.j_han.jong = 1;

		ret_val = SearchCharInCurrentLevel(one_char, h_idx, &node_index);
		if (ret_val == 1) {
			if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
				noun_info_cnt = 0;
				if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
					noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
				} else {
					result[*res_idx].len = char_index+1;
					result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
					result[*res_idx].info[1] = 0;
					result[(*res_idx)++].jong = TRUE;
				}
#else
				result[*res_idx].len = char_index+1;
				result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
				result[(*res_idx)++].jong = TRUE;
#endif

				/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
				if (Dic_Roots[h_idx][node_index].node_info.brk == 0) {
					old_node_index1 = node_index;
					node_index++;
					while (Dic_Roots[h_idx][node_index].han.j_code == 0) {
						if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
							if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
								noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
							} else {
								result[*res_idx].len = char_index+1;
								result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
								result[*res_idx].info[1] = 0;
								result[(*res_idx)++].jong = TRUE;
							}
#else
							result[*res_idx].len = char_index+1;
							result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
							result[(*res_idx)++].jong = TRUE;
#endif
						}
						if (Dic_Roots[h_idx][node_index].node_info.brk == 1)
								break;
						node_index++;
					}
					node_index = old_node_index1;
				}

#ifdef MULTI_DIC_INFO
				if (noun_info_cnt > 0) {
					noun_info_buf[noun_info_cnt] = 0;
					result[*res_idx].len = char_index+1;
					strcpy(result[*res_idx].info, noun_info_buf);
					result[(*res_idx)++].jong = TRUE;
				}
#endif
			}
			return 1;
		}

		return 0;
	}

	while (remain_chars > 0) {
		cur_level_start_index = node_index;
		ret_val = SearchCharInCurrentLevel(h_word[char_index], h_idx, &node_index);
		if (ret_val == 1) {
			if (h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
				/* node_index가 변하므로 이전 값을 저장해야 한다. */
				old_node_index2 = node_index;

			    /* 한글일 경우만 종성을 뺀 서브 스트링에 대해서 검색을 한다 */
				/* 종성이 있는 경우 */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				/* 첫글자일 경우에 h_idx의 값을 바꾸어줘야 한다. */
				/* node_index는 char_index가 0이면 당연히 0이므로 따로 처리를 해 줄 필요가 없다..*/
				if (char_index == 0) {
					old_h_idx = h_idx;
					if (h_idx < WANSUNG_JASO_NUM)
					    goto SKIP_CHECK1;

					h_idx = GetNoJongIndex(h_idx);
					/* 만약 "각"이라는 글자에 대한 종성없는 글자는 "가"(헤더인덱스 51) */
					if (Dic_Header[h_idx].size == 0)
						goto SKIP_CHECK1;
				}

				node_index = cur_level_start_index;
				ret_val = SearchCharInCurrentLevel(one_char, h_idx, &node_index);
				if (ret_val == 1) {
					if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
						noun_info_cnt = 0;
						if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
							noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
						} else {
							result[*res_idx].len = char_index+1;
							result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
							result[*res_idx].info[1] = 0;
							result[(*res_idx)++].jong = TRUE;
						}
#else
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;
#endif
						/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
						if (Dic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (Dic_Roots[h_idx][node_index].han.j_code == 0) {
								if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
									if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
										noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
									} else {
										result[*res_idx].len = char_index+1;
										result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
										result[*res_idx].info[1] = 0;
										result[(*res_idx)++].jong = TRUE;
									}
#else
									result[*res_idx].len = char_index+1;
									result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
									result[(*res_idx)++].jong = TRUE;
#endif
								}
								if (Dic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
#ifdef MULTI_DIC_INFO
						if (noun_info_cnt > 0) {
							noun_info_buf[noun_info_cnt] = 0;
							result[*res_idx].len = char_index+1;
							strcpy(result[*res_idx].info, noun_info_buf);
							result[(*res_idx)++].jong = TRUE;
						}
#endif
					}
				}

SKIP_CHECK1:;
				/* h_idx 원상 복원 */
				if (char_index == 0)
					h_idx = old_h_idx;

				node_index = old_node_index2;
			}

			if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
				noun_info_cnt = 0;
				if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
					noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
				} else {
					result[*res_idx].len = char_index+1;
					result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
					result[*res_idx].info[1] = 0;
					result[(*res_idx)++].jong = FALSE;
				}
#else
				result[*res_idx].len = char_index+1;
				result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
				result[(*res_idx)++].jong = FALSE;
#endif

				/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
				if (Dic_Roots[h_idx][node_index].node_info.brk == 0) {
					old_node_index1 = node_index;
					node_index++;
					while (Dic_Roots[h_idx][node_index].han.j_code == 0) {
						if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
							if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
								noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
							} else {
								result[*res_idx].len = char_index+1;
								result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
								result[*res_idx].info[1] = 0;
								result[(*res_idx)++].jong = FALSE;
							}
#else
							result[*res_idx].len = char_index+1;
							result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
							result[(*res_idx)++].jong = FALSE;
#endif
						}
						if (Dic_Roots[h_idx][node_index].node_info.brk == 1)
								break;
						node_index++;
					}
					node_index = old_node_index1;
				}

#ifdef MULTI_DIC_INFO
				if (noun_info_cnt > 0) {
					noun_info_buf[noun_info_cnt] = 0;
					result[*res_idx].len = char_index+1;
					strcpy(result[*res_idx].info, noun_info_buf);
					result[(*res_idx)++].jong = FALSE;
				}
#endif
			}

			remain_chars--;
			char_index++;

			if (remain_chars == 0) {
				if (*res_idx == 0)
					return 0;
				else {
					full_match = 1;
					return 1;
				}
			}

			if (Dic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += Dic_Roots[h_idx][node_index].node_info.next;
			else
				return 1;

		} else {
			if (h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
			    /* 한글일 경우만 종성을 뺀 서브 스트링에 대해서 검색을 한다 */
				/* 종성이 있는 경우 */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				/* 첫글자일 경우에 h_idx의 값을 바꾸어줘야 한다. */
				/* node_index는 char_index가 0이면 당연히 0이므로 따로 처리를 해 줄 필요가 없다..*/
				if (char_index == 0) {
					old_h_idx = h_idx;
					if (h_idx < WANSUNG_JASO_NUM)
					    goto SKIP_CHECK2;
					h_idx = GetNoJongIndex(h_idx);
					/* 만약 "각"이라는 글자에 대한 종성없는 글자는 "가"(헤더인덱스 51) */
					if (Dic_Header[h_idx].size == 0)
						goto SKIP_CHECK2;
				}

				node_index = cur_level_start_index;
				ret_val = SearchCharInCurrentLevel(one_char, h_idx, &node_index);
				if (ret_val == 1) {
					if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
						noun_info_cnt = 0;
						if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
							noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
						} else {
							result[*res_idx].len = char_index+1;
							result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
							result[*res_idx].info[1] = 0;
							result[(*res_idx)++].jong = TRUE;
						}
#else
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;
#endif

						/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
						if (Dic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (Dic_Roots[h_idx][node_index].han.j_code == 0) {
								if (Dic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
									if (IS_NOUN(Dic_Roots[h_idx][node_index].node_info.info)) {
										noun_info_buf[noun_info_cnt++] = Dic_Roots[h_idx][node_index].node_info.info;
									} else {
										result[*res_idx].len = char_index+1;
										result[*res_idx].info[0] = Dic_Roots[h_idx][node_index].node_info.info;
										result[*res_idx].info[1] = 0;
										result[(*res_idx)++].jong = TRUE;
									}
#else
									result[*res_idx].len = char_index+1;
									result[*res_idx].info = Dic_Roots[h_idx][node_index].node_info.info;
									result[(*res_idx)++].jong = TRUE;
#endif
								}
								if (Dic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
#ifdef MULTI_DIC_INFO
						if (noun_info_cnt > 0) {
							noun_info_buf[noun_info_cnt] = 0;
							result[*res_idx].len = char_index+1;
							strcpy(result[*res_idx].info, noun_info_buf);
							result[(*res_idx)++].jong = TRUE;
						}
#endif
					}
				}

SKIP_CHECK2:;
				/* h_idx 원상 복원 */
				if (char_index == 0)
					h_idx = old_h_idx;

			}

			if (*res_idx == 0)
				return 0;
			else 
				return 1;
		}
	}

	return 0;
} /* End of SearchWordInTrieDic */
