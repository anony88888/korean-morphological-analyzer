/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_JESearchWordInTrieDic.c)#  SPASIS System,     Thu Nov 25 15:34:56 1999
 *
 *	#(Action)#
 *		- ����/��� ���� ���� Ž�� ����
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MADIC_Func.h>

#ifdef MULTI_DIC_INFO
DWORD SearchJosaInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, JEDIC_RESULT *result, UWORD *res_idx)
#else
DWORD SearchJosaInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
#endif
{
	UDWORD node_index = 0;  /* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;  /* ���� ���ڸ� ����Ű�� �ε��� */
	UDWORD remain_chars = len;
	UDWORD old_node_index1; 
	UDWORD old_node_index2;
	UDWORD cur_level_start_idx;
	HANGUL one_char;
	UWORD ret_val;

	one_char.j_han.sign = 1;
	if (JDic_Header[h_idx].size == 0) {
		*res_idx = 0;
		return 0;
	}

	while (remain_chars > 0) {
		cur_level_start_idx = node_index;
		ret_val = SearchJosaCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			/* ����/��� ���� Ž���� ��쿡�� ù���ڿ� ���ؼ� ������ ������ ���ڿ� ���� Ž���� ���� �ʴ´� */
			if (char_index > 0 && h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
				/* node_index�� ���ϹǷ� ���� ���� �����ؾ� �Ѵ�. */
				old_node_index2 = node_index;

			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				node_index = cur_level_start_idx;
				ret_val = SearchJosaCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (JDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = JDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (JDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (JDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (JDic_Roots[h_idx][node_index].node_info.info != 0) {
									result[*res_idx].len = char_index+1;
									result[*res_idx].jong = TRUE;
									result[*res_idx].info = JDic_Roots[h_idx][node_index].node_info.info;
									(*res_idx)++;
								}
								if (JDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
					}
				}

				node_index = old_node_index2;
			}

			if (JDic_Roots[h_idx][node_index].node_info.info != 0) {
				result[*res_idx].len = char_index+1;
				result[*res_idx].jong = FALSE;
				result[*res_idx].info = JDic_Roots[h_idx][node_index].node_info.info;
				(*res_idx)++;
			}

			/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
			if (JDic_Roots[h_idx][node_index].node_info.brk == 0) {
				old_node_index1 = node_index;
				node_index++;
				while (JDic_Roots[h_idx][node_index].han.j_code == 0) {
					if (JDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].jong = FALSE;
						result[*res_idx].info = JDic_Roots[h_idx][node_index].node_info.info;
						(*res_idx)++;
					}
					if (JDic_Roots[h_idx][node_index].node_info.brk == 1)
							break;
					node_index++;
				}
				node_index = old_node_index1;
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

			if (JDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += JDic_Roots[h_idx][node_index].node_info.next;
			else
				return 1;

		} else {
			if (char_index > 0 && h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				node_index = cur_level_start_idx;
				ret_val = SearchJosaCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (JDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = JDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (JDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (JDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (JDic_Roots[h_idx][node_index].node_info.info != 0) {
									result[*res_idx].len = char_index+1;
									result[*res_idx].jong = TRUE;
									result[*res_idx].info = JDic_Roots[h_idx][node_index].node_info.info;
									(*res_idx)++;
								}
								if (JDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
					}
				}
			}

			if (*res_idx == 0)
				return 0;
			else 
				return 1;
		}
	}

	return 0;
} /* End of SearchWordInTrieDic */

#ifdef MULTI_DIC_INFO
DWORD SearchEomiInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, JEDIC_RESULT *result, UWORD *res_idx)
#else
DWORD SearchEomiInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
#endif
{
	UDWORD node_index = 0;  /* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;  /* ���� ���ڸ� ����Ű�� �ε��� */
	UDWORD remain_chars = len;
	UDWORD old_node_index1; 
	UDWORD old_node_index2;
	UDWORD cur_level_start_idx;
	HANGUL one_char;
	UWORD ret_val;

	one_char.j_han.sign = 1;
	if (EDic_Header[h_idx].size == 0) {
		*res_idx = 0;
		return 0;
	}

	while (remain_chars > 0) {
		cur_level_start_idx = node_index;
		ret_val = SearchEomiCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (char_index > 0 && h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
				/* node_index�� ���ϹǷ� ���� ���� �����ؾ� �Ѵ�. */
				old_node_index2 = node_index;

			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				node_index = cur_level_start_idx;
				ret_val = SearchEomiCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (EDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = EDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (EDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (EDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (EDic_Roots[h_idx][node_index].node_info.info != 0) {
									result[*res_idx].len = char_index+1;
									result[*res_idx].jong = TRUE;
									result[*res_idx].info = EDic_Roots[h_idx][node_index].node_info.info;
									(*res_idx)++;
								}
								if (EDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
					}
				}

				node_index = old_node_index2;
			}

			if (EDic_Roots[h_idx][node_index].node_info.info != 0) {
				result[*res_idx].len = char_index+1;
				result[*res_idx].jong = FALSE;
				result[*res_idx].info = EDic_Roots[h_idx][node_index].node_info.info;
				(*res_idx)++;
			}

			/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
			if (EDic_Roots[h_idx][node_index].node_info.brk == 0) {
				old_node_index1 = node_index;
				node_index++;
				while (EDic_Roots[h_idx][node_index].han.j_code == 0) {
					if (EDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].jong = FALSE;
						result[*res_idx].info = EDic_Roots[h_idx][node_index].node_info.info;
						(*res_idx)++;
					}
					if (EDic_Roots[h_idx][node_index].node_info.brk == 1)
							break;
					node_index++;
				}
				node_index = old_node_index1;
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

			if (EDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += EDic_Roots[h_idx][node_index].node_info.next;
			else
				return 1;

		} else {
			if (char_index > 0 && h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				node_index = cur_level_start_idx;
				ret_val = SearchEomiCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (EDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = EDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (EDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (EDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (EDic_Roots[h_idx][node_index].node_info.info != 0) {
									result[*res_idx].len = char_index+1;
									result[*res_idx].jong = TRUE;
									result[*res_idx].info = EDic_Roots[h_idx][node_index].node_info.info;
									(*res_idx)++;
								}
								if (EDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
					}
				}
			}

			if (*res_idx == 0)
				return 0;
			else 
				return 1;
		}
	}

	return 0;
} /* End of SearchWordInTrieDic */

#ifdef MULTI_DIC_INFO
DWORD SearchBojoInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, JEDIC_RESULT *result, UWORD *res_idx)
#else
DWORD SearchBojoInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
#endif
{
	UDWORD node_index = 0;  /* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;  /* ���� ���ڸ� ����Ű�� �ε��� */
	UDWORD remain_chars = len;
	UDWORD old_node_index1; 
	UDWORD old_node_index2;
	UDWORD cur_level_start_idx;
	HANGUL one_char;
	UWORD ret_val;

	one_char.j_han.sign = 1;
	if (BDic_Header[h_idx].size == 0) {
		*res_idx = 0;
		return 0;
	}

	while (remain_chars > 0) {
		cur_level_start_idx = node_index;
		ret_val = SearchBojoCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (char_index > 0 && h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
				/* node_index�� ���ϹǷ� ���� ���� �����ؾ� �Ѵ�. */
				old_node_index2 = node_index;

			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				node_index = cur_level_start_idx;
				ret_val = SearchBojoCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (BDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = BDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (BDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (BDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (BDic_Roots[h_idx][node_index].node_info.info != 0) {
									result[*res_idx].len = char_index+1;
									result[*res_idx].jong = TRUE;
									result[*res_idx].info = BDic_Roots[h_idx][node_index].node_info.info;
									(*res_idx)++;
								}
								if (BDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
					}
				}

				node_index = old_node_index2;
			}

			if (BDic_Roots[h_idx][node_index].node_info.info != 0) {
				result[*res_idx].len = char_index+1;
				result[*res_idx].jong = FALSE;
				result[*res_idx].info = BDic_Roots[h_idx][node_index].node_info.info;
				(*res_idx)++;
			}

			/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
			if (BDic_Roots[h_idx][node_index].node_info.brk == 0) {
				old_node_index1 = node_index;
				node_index++;
				while (BDic_Roots[h_idx][node_index].han.j_code == 0) {
					if (BDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].jong = FALSE;
						result[*res_idx].info = BDic_Roots[h_idx][node_index].node_info.info;
						(*res_idx)++;
					}
					if (BDic_Roots[h_idx][node_index].node_info.brk == 1)
							break;
					node_index++;
				}
				node_index = old_node_index1;
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

			if (BDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += BDic_Roots[h_idx][node_index].node_info.next;
			else
				return 1;

		} else {
			if (char_index > 0 && h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				node_index = cur_level_start_idx;
				ret_val = SearchBojoCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (BDic_Roots[h_idx][node_index].node_info.info != 0) {
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = BDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (BDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (BDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (BDic_Roots[h_idx][node_index].node_info.info != 0) {
									result[*res_idx].len = char_index+1;
									result[*res_idx].jong = TRUE;
									result[*res_idx].info = BDic_Roots[h_idx][node_index].node_info.info;
									(*res_idx)++;
								}
								if (BDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
					}
				}
			}

			if (*res_idx == 0)
				return 0;
			else 
				return 1;
		}
	}

	return 0;
} /* End of SearchWordInTrieDic */
