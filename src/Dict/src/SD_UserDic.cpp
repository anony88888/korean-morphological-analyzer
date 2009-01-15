/*
 * 2003-06-30
 *
 * ����� ���� ���� ���
 * - ����� ���� ����
 * - ����� ���� �˻�
 *
 * - ����� ������ �Է� ������ �ϴ� �ϼ��� �ڵ�� ���صд�.
 * - ó������ ü��� ��ü������ �����ؼ� �Է��ϱ�� �Ͽ�����...
 *   �Ϲ� ����ڰ� ���⿡�� ����� �� ����.
 *   ���� �׳� ü�� �ִ� �ɷ� �Ѵ�.
 * - ������ [�ܾ�]\n[�ܾ�]\n......\n[�ܾ�]
 */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_InsertCharInTrieMiddle.c)#  SPASIS System,     Thu Nov 18 22:08:09 1999
 *
 *	#(Action)#
 *		- ���� ������ �� �������� �� ���� ��带 �߰��Ѵ�.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_ReturnCode.h>
#include <MA_Memory.h>
#include <MADIC_Type.h>
#include <MADIC_Func.h>
#include <MA_UtilLib.h>

#define USER_DIC_FILE		"USERDIC.DIC"				/* ����� ���� ���ϸ� */

#define WANSUNG_JASO_NUM 51
#define WANSUNG_CODE_NUM 2350
#define ALPHABET_CODE_NUM 26
#define NUMBER_NUM 10

#define HEADER_NUM (WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + NUMBER_NUM)


static DIC_HEADER		UserDic_Header[HEADER_NUM];		/* ����� ���� �޸� ��� */
static DIC_NODE			*UserDic_Roots[HEADER_NUM];		/* ����� ���� �޸� Trie */

static int				isDicExist;				/* ���� ����� ������ �޸𸮿� �ִ���? */

tVOID InitUserDicHeader()
{
	int i;

	for (i = 0; i < HEADER_NUM; i++) {
		UserDic_Header[i].size = 0;
		UserDic_Header[i].start = 0;
		UserDic_Header[i].items = 0;
		UserDic_Roots[i] = NULL;
	}

	isDicExist = 0;
}

DWORD LoadUserDic(BYTE *dic_dir)
{
	BYTE f_name[512];
	FILE *fd_dic;
	BYTE line[1024], h_str[1024];
	BYTE *ptr;
	DWORD ret_val;

	sprintf(f_name, "%s/%s", dic_dir, USER_DIC_FILE);
	fd_dic = fopen(f_name, "rt");
	if (fd_dic == NULL) {
		isDicExist = 0;
		return 0;
	}

	while (fgets(line, 1024, fd_dic)) {
		ptr = strtok(line, " \t\r\n");
		if (ptr == NULL)
			continue;
		strcpy(h_str, ptr);
		ret_val = UD_InsertWord(h_str, 39);		// ����� ���� ��Ʈ���� �ϴ� ������������� ����
		/*
		 * ���⿡�� ����ó�� ����� ��...
		 *
		 */
	}

	isDicExist = 1;

	fclose(fd_dic);

	return 1;
}

DWORD SearchUserDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
{
	DWORD ret_val;

	if (!isDicExist)
		return 0;

	*res_idx = 0;
	ret_val = UD_SearchWordInTrieDic(h_word, h_word_len, h_idx, result, res_idx);

	return ret_val;
}

DWORD UD_InsertCharInTrieMiddle(HANGUL h_char, DWORD g_idx, DIC_HEADER *header, UDWORD index)
{
	UDWORD alloc_size = sizeof(DIC_NODE);

	UserDic_Roots[g_idx] = (DIC_NODE *) MemoryAppend(UserDic_Roots[g_idx], alloc_size);
	/* �� ��� �߰��ϰ� */
	assert(UserDic_Roots[g_idx] != NULL);
	header->size += alloc_size;

	MemoryMove(&(UserDic_Roots[g_idx][index+1]), &(UserDic_Roots[g_idx][index]),
									 (header->items - index)*sizeof(DIC_NODE));
	/* index ������ ������ �� ��徿 �ڷ� �δ� */

	UserDic_Roots[g_idx][index].han = h_char;
	UserDic_Roots[g_idx][index].node_info.brk = FALSE;
	UserDic_Roots[g_idx][index].node_info.info = 0;
	UserDic_Roots[g_idx][index].node_info.next = 0; 			/* �ϴ� */
	UserDic_Roots[g_idx][index].node_info.jong = FALSE;

	header->items += 1;

	return index;
} /* End of InsertCharInTrieMiddle */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_InsertRemainStr.c)#  SPASIS System,     Thu Nov 18 21:17:58 1999
 *
 *	#(Action)#
 *		- �Է� ��Ʈ���� ���ؼ� Trie�� �� �������� ���ʷ� Append�Ѵ�.
 *		- ���� ���� �� �� ���� ����� ��ġ�̴�.
 */
DWORD UD_InsertStrInTrieEnd(HANGUL *han_str, DWORD len, DWORD g_idx, DIC_HEADER *header, BYTE info)
{
	DWORD alloc_size = sizeof(DIC_NODE) * len;
	DWORD start_idx = header->items, i;
	DWORD ret_val = start_idx;

	UserDic_Roots[g_idx] = (DIC_NODE *) MemoryAppend(UserDic_Roots[g_idx], alloc_size);
	header->size += alloc_size;

	assert(UserDic_Roots[g_idx] != NULL);

	i = 0;
	while (i < len) {
		UserDic_Roots[g_idx][start_idx].han = han_str[i];
		/* next ���� ���� ���� ��ǥ����� �Ÿ��̴�. */
		UserDic_Roots[g_idx][start_idx].node_info.next = 1;
		UserDic_Roots[g_idx][start_idx].node_info.info = 0;
		UserDic_Roots[g_idx][start_idx].node_info.jong = FALSE;
		UserDic_Roots[g_idx][start_idx].node_info.brk = TRUE;
		i++;
		start_idx++;
	}
	UserDic_Roots[g_idx][start_idx-1].node_info.next = 0;
	UserDic_Roots[g_idx][start_idx-1].node_info.info = info;

	header->items += len;

	return ret_val;
} /* End of InsertRemainStr */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_InsertWord.c)#  SPASIS System,     Mon Nov 15 13:14:01 1999
 *
 *	#(Action)#
 *		Trie ������ ǥ����� ������ ����.
 */
WORD UD_InsertWord(BYTE *word, BYTE info)
{
	HANGUL voca[MAX_VOCA_LEN];	/* �ѱ� �Է� ǥ���� */
	UWORD header_idx;
	DWORD voca_len;

	voca_len = MakeHanBuf((UBYTE*)word, voca, &header_idx);

	if (voca_len == 0)
		return 0;

	return (UD_InsertWordInTrieDic(voca, voca_len, header_idx, info));
} /* End of InsertItem */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_InsertWordInTrieDic.c)#  SPASIS System,  Mon Nov 15 21:01:00 1999
 *
 *	#(Action)#
 *		Ʈ���� ������ ǥ��� ����	
 */
DWORD UD_InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, BYTE info)
{
	UDWORD node_index = 0;	/* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD old_node_index = 0;	/* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;	/* ���� ���ڸ� ����Ű�� �ε��� */
	UDWORD remain_chars = len;	/* �����ִ� ���� �� */
	HANGUL one_char;
	UDWORD cl_idx;
	DWORD check_of;
	WORD ret_val;

	if (UserDic_Header[h_idx].size == 0) {
		assert(UserDic_Roots[h_idx] == NULL);

		node_index = UD_InsertStrInTrieEnd(h_word, len, h_idx, 
													&(UserDic_Header[h_idx]), info);
		char_index += len;

		return char_index;		/* �ѱ� ��Ʈ���� ���� ��ŭ ���� */
	} else {
		while (remain_chars > 0) {
			ret_val = UD_SearchCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
			if (ret_val == 1) {
				if (UserDic_Roots[h_idx][node_index].node_info.next == 0) {
					if (remain_chars == 1) {
						/* ���� ǥ��� ���ؼ� �ٸ� ������ �Է� */
						/* ����Ǵ� ���ڴ� 0 ���� ���� */
						/* �ٷ� ���� ��忡 ���� */
						one_char.j_code = 0;
						UD_InsertCharInTrieMiddle(one_char, h_idx,	&(UserDic_Header[h_idx]), node_index + 1);

						node_index++;

						UserDic_Roots[h_idx][node_index].node_info.info = info;
						/* ���� ���� ��尡 ���� Ʈ�� ���������� ������ ����� ���....
						   ���ԵǴ� ���ο� ���� brk ���� �°�޾ƾ� �Ѵ�...*/
						if (UserDic_Roots[h_idx][node_index-1].node_info.brk == 1) {
							UserDic_Roots[h_idx][node_index-1].node_info.brk = 0;
							UserDic_Roots[h_idx][node_index].node_info.brk = 1;
						} else
							UserDic_Roots[h_idx][node_index].node_info.brk = 0;

						UserDic_Roots[h_idx][node_index].node_info.next = 
										UserDic_Roots[h_idx][node_index-1].node_info.next;

						/* ���� �������� ��尡 �ϳ� �߰��Ǿ����Ƿ� 
						   ���� ������ next ���� �������־�� �Ѵ�. */

						/* ���� ����� ���� ���鿡 ���� next ���� */
						cl_idx = node_index - 1;
						while (1) {
							if (cl_idx == 0)
								break;
							/*
							if (UserDic_Roots[h_idx][cl_idx].node_info.brk == 1)
								break;
								*/
							if (UserDic_Roots[h_idx][cl_idx].node_info.next != 0 &&
								UserDic_Roots[h_idx][cl_idx].node_info.next + cl_idx > node_index-1)
								UserDic_Roots[h_idx][cl_idx].node_info.next++;
							cl_idx--;
						}

						return (len);
					} else {	
						old_node_index = node_index;
					/* ã�� ��尡 leaf ����� �� */
					/* �������� ��� trie�� ���� */
						char_index++;
						node_index = UD_InsertStrInTrieEnd(&(h_word[char_index]),
												len - char_index,
												h_idx,
												&(UserDic_Header[h_idx]),
												info);
						/* next�� ���� ���� ��ǥ ����� �Ÿ� */
						UserDic_Roots[h_idx][old_node_index].node_info.next	= node_index - old_node_index;

						return (len);
					}
				} else { /* ���� ���� ���� */
					if (remain_chars == 1) {
					/* ������ �ִ� ��Ʈ���� ���꽺Ʈ���� ���ԵǾ��� �� */
						if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
							/* ���� ǥ��� ���ؼ� �ٸ� ������ ���� */
							one_char.j_code = 0;
							UD_InsertCharInTrieMiddle(one_char, h_idx,		
													&(UserDic_Header[h_idx]), node_index + 1);

							node_index++;

							UserDic_Roots[h_idx][node_index].node_info.info = info;
							UserDic_Roots[h_idx][node_index].node_info.brk = 0;
							UserDic_Roots[h_idx][node_index].node_info.next = 
											UserDic_Roots[h_idx][node_index-1].node_info.next;

							/* ���� �������� ��尡 �ϳ� �߰��Ǿ����Ƿ� 
							   ���� ������ next ���� �������־�� �Ѵ�. */

							/* ���� ����� ���� ���鿡 ���� next ���� */
							cl_idx = node_index - 1;
							while (1) {
								if (cl_idx == 0)
									break;
								/*
								if (UserDic_Roots[h_idx][cl_idx].node_info.brk == 1)
									break;
									*/
								if (UserDic_Roots[h_idx][cl_idx].node_info.next != 0 &&
									UserDic_Roots[h_idx][cl_idx].node_info.next + cl_idx > node_index-1)
									UserDic_Roots[h_idx][cl_idx].node_info.next++;
								/*
								if (UserDic_Roots[h_idx][cl_idx].node_info.next != 0)
									UserDic_Roots[h_idx][cl_idx].node_info.next++;
									*/
								cl_idx--;
							}

							/* ���� ����� ���� ���鿡 ���� next ���� */
						} else {
							UserDic_Roots[h_idx][node_index].node_info.info = info;
						}

						return (char_index + 1);
					}
					node_index += UserDic_Roots[h_idx][node_index].node_info.next;
					char_index++;
					remain_chars--;
				}
			} else {
			/* ���� �������� ���ڰ� �������� ���� �� */
			/* ���� ������ �� ��� �߰� */
			/* node_index�� ���� ������ ���� ������ ����� ���� ��带 ���� */
				assert(node_index != 0);
				UD_InsertCharInTrieMiddle(h_word[char_index], h_idx,
											&(UserDic_Header[h_idx]), node_index);

				UserDic_Roots[h_idx][node_index-1].node_info.brk = 0;
				UserDic_Roots[h_idx][node_index].node_info.brk = 1;

				/* ���� �������� ��尡 �ϳ� �߰��Ǿ����Ƿ� 
				   ���� ������ next ���� �������־�� �Ѵ�. */

				/* ���� ����� ���� ���鿡 ���� next ���� */
				cl_idx = node_index - 1;
				while (1) {
					if (cl_idx == 0)
						break;
					/*
					if (UserDic_Roots[h_idx][cl_idx].node_info.brk == 1)
						break;
						*/
					if (UserDic_Roots[h_idx][cl_idx].node_info.next != 0 &&
						UserDic_Roots[h_idx][cl_idx].node_info.next + cl_idx > node_index-1)
						UserDic_Roots[h_idx][cl_idx].node_info.next++;
					/*
					if (UserDic_Roots[h_idx][cl_idx].node_info.next != 0)
						UserDic_Roots[h_idx][cl_idx].node_info.next++;
						*/
					cl_idx--;
				}

				char_index++;

				if (remain_chars == 1) {
					UserDic_Roots[h_idx][node_index].node_info.next = 0;
					UserDic_Roots[h_idx][node_index].node_info.info = info;
				} else {
/*
					UserDic_Roots[h_idx][node_index].node_info.info = info;
*/
					check_of = UD_InsertStrInTrieEnd(&h_word[char_index],
												len - char_index,
												h_idx,
												&(UserDic_Header[h_idx]),
												info);

					UserDic_Roots[h_idx][node_index].node_info.next = check_of - node_index;
				}
				return (char_index + 1);
			}
		}
	}

	return (char_index + 1);
} /* End of InsertWordInTrieDic */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_SearchCharInCurrentLevel.c)#  SPASIS System,  Thu Nov 18 20:23:19 1999
 *
 *	#(Action)#
 *		- Trie��  ���� �������� ������ ���ڸ� �˻�
 */
/*
 * �˻��� �����Ͽ�����...
 * ���� ������ ���� ������ ����� ���� ��带 ����...
 */
WORD UD_SearchCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index)
{
	DWORD node_index = *index;

	while (1) {
	    if (UserDic_Header[g_idx].items <= node_index)
			break;
		if (one_char.j_code == UserDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}
		if (UserDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	*index = node_index + 1;


	return FALSE;
} /* End of SearchCharInCurrentLevel */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_SearchWordInTrieDic.c)#  SPASIS System,     Thu Nov 25 15:34:56 1999
 *
 *	#(Action)#
 *		- �������� ���� Ž�� ���� 
 */
DWORD UD_SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;  /* ���� ���ڸ� ����Ű�� �ε��� */
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
	if (UserDic_Header[h_idx].size == 0) {
	    	if (h_word[0].j_han.sign == 0)
		    return 0;
	    	if (h_idx < WANSUNG_JASO_NUM) {
		    *res_idx = 0;
		    return 0;
		}
		h_idx = GetNoJongIndex(h_idx);
		/* ���� "��"�̶�� ���ڿ� ���� �������� ���ڴ� "��"(����ε��� 51) */
		if (UserDic_Header[h_idx].size == 0) {
			*res_idx = 0;
			return 0;
		}

		char_index = 0;
		one_char.j_han.cho = h_word[char_index].j_han.cho;
		one_char.j_han.jung = h_word[char_index].j_han.jung;
		one_char.j_han.jong = 1;

		ret_val = UD_SearchCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
				noun_info_cnt = 0;
				if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
					noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
				} else {
					result[*res_idx].len = char_index+1;
					result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
					result[*res_idx].info[1] = 0;
					result[(*res_idx)++].jong = TRUE;
				}
#else
				result[*res_idx].len = char_index+1;
				result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
				result[(*res_idx)++].jong = TRUE;
#endif

				/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
				if (UserDic_Roots[h_idx][node_index].node_info.brk == 0) {
					old_node_index1 = node_index;
					node_index++;
					while (UserDic_Roots[h_idx][node_index].han.j_code == 0) {
						if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
							if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
								noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
							} else {
								result[*res_idx].len = char_index+1;
								result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
								result[*res_idx].info[1] = 0;
								result[(*res_idx)++].jong = TRUE;
							}
#else
							result[*res_idx].len = char_index+1;
							result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
							result[(*res_idx)++].jong = TRUE;
#endif
						}
						if (UserDic_Roots[h_idx][node_index].node_info.brk == 1)
								break;
						node_index++;
					}
					node_index = old_node_index1;
				}

#ifdef MULTI_DIC_INFO
				if (noun_info_cnt > 0) {
					noun_info_buf[noun_info_cnt] = 0;
					result[*res_idx].len = char_index+1;
					strcpy((char*)result[*res_idx].info, (char*)noun_info_buf);
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
		ret_val = UD_SearchCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
				/* node_index�� ���ϹǷ� ���� ���� �����ؾ� �Ѵ�. */
				old_node_index2 = node_index;

			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				/* ù������ ��쿡 h_idx�� ���� �ٲپ���� �Ѵ�. */
				/* node_index�� char_index�� 0�̸� �翬�� 0�̹Ƿ� ���� ó���� �� �� �ʿ䰡 ����..*/
				if (char_index == 0) {
					old_h_idx = h_idx;
					if (h_idx < WANSUNG_JASO_NUM)
					    goto SKIP_CHECK1;

					h_idx = GetNoJongIndex(h_idx);
					/* ���� "��"�̶�� ���ڿ� ���� �������� ���ڴ� "��"(����ε��� 51) */
					if (UserDic_Header[h_idx].size == 0)
						goto SKIP_CHECK1;
				}

				node_index = cur_level_start_index;
				ret_val = UD_SearchCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
						noun_info_cnt = 0;
						if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
							noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
						} else {
							result[*res_idx].len = char_index+1;
							result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
							result[*res_idx].info[1] = 0;
							result[(*res_idx)++].jong = TRUE;
						}
#else
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;
#endif
						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (UserDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (UserDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
									if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
										noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
									} else {
										result[*res_idx].len = char_index+1;
										result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
										result[*res_idx].info[1] = 0;
										result[(*res_idx)++].jong = TRUE;
									}
#else
									result[*res_idx].len = char_index+1;
									result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
									result[(*res_idx)++].jong = TRUE;
#endif
								}
								if (UserDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
#ifdef MULTI_DIC_INFO
						if (noun_info_cnt > 0) {
							noun_info_buf[noun_info_cnt] = 0;
							result[*res_idx].len = char_index+1;
							strcpy((char*)result[*res_idx].info, (char*)noun_info_buf);
							result[(*res_idx)++].jong = TRUE;
						}
#endif
					}
				}

SKIP_CHECK1:;
				/* h_idx ���� ���� */
				if (char_index == 0)
					h_idx = old_h_idx;

				node_index = old_node_index2;
			}

			if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
				noun_info_cnt = 0;
				if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
					noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
				} else {
					result[*res_idx].len = char_index+1;
					result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
					result[*res_idx].info[1] = 0;
					result[(*res_idx)++].jong = FALSE;
				}
#else
				result[*res_idx].len = char_index+1;
				result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
				result[(*res_idx)++].jong = FALSE;
#endif

				/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
				if (UserDic_Roots[h_idx][node_index].node_info.brk == 0) {
					old_node_index1 = node_index;
					node_index++;
					while (UserDic_Roots[h_idx][node_index].han.j_code == 0) {
						if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
							if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
								noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
							} else {
								result[*res_idx].len = char_index+1;
								result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
								result[*res_idx].info[1] = 0;
								result[(*res_idx)++].jong = FALSE;
							}
#else
							result[*res_idx].len = char_index+1;
							result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
							result[(*res_idx)++].jong = FALSE;
#endif
						}
						if (UserDic_Roots[h_idx][node_index].node_info.brk == 1)
								break;
						node_index++;
					}
					node_index = old_node_index1;
				}

#ifdef MULTI_DIC_INFO
				if (noun_info_cnt > 0) {
					noun_info_buf[noun_info_cnt] = 0;
					result[*res_idx].len = char_index+1;
					strcpy((char*)result[*res_idx].info, (char*)noun_info_buf);
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
					return 1;
				}
			}

			if (UserDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += UserDic_Roots[h_idx][node_index].node_info.next;
			else
				return 1;

		} else {
			if (h_word[char_index].j_han.sign == 1 && h_word[char_index].j_han.jong != 1) { 
			    /* �ѱ��� ��츸 ������ �� ���� ��Ʈ���� ���ؼ� �˻��� �Ѵ� */
				/* ������ �ִ� ��� */
				one_char.j_han.cho = h_word[char_index].j_han.cho;
				one_char.j_han.jung = h_word[char_index].j_han.jung;
				one_char.j_han.jong = 1;

				/* ù������ ��쿡 h_idx�� ���� �ٲپ���� �Ѵ�. */
				/* node_index�� char_index�� 0�̸� �翬�� 0�̹Ƿ� ���� ó���� �� �� �ʿ䰡 ����..*/
				if (char_index == 0) {
					old_h_idx = h_idx;
					if (h_idx < WANSUNG_JASO_NUM)
					    goto SKIP_CHECK2;
					h_idx = GetNoJongIndex(h_idx);
					/* ���� "��"�̶�� ���ڿ� ���� �������� ���ڴ� "��"(����ε��� 51) */
					if (UserDic_Header[h_idx].size == 0)
						goto SKIP_CHECK2;
				}

				node_index = cur_level_start_index;
				ret_val = UD_SearchCharInCurrentLevel(one_char, h_idx, (DWORD*)&node_index);
				if (ret_val == 1) {
					if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
						noun_info_cnt = 0;
						if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
							noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
						} else {
							result[*res_idx].len = char_index+1;
							result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
							result[*res_idx].info[1] = 0;
							result[(*res_idx)++].jong = TRUE;
						}
#else
						result[*res_idx].len = char_index+1;
						result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
						result[(*res_idx)++].jong = TRUE;
#endif

						/* ���� ǥ�����̸鼭 ������ �ٸ� ǥ��� Ž�� */
						if (UserDic_Roots[h_idx][node_index].node_info.brk == 0) {
							old_node_index1 = node_index;
							node_index++;
							while (UserDic_Roots[h_idx][node_index].han.j_code == 0) {
								if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
#ifdef MULTI_DIC_INFO
									if (IS_NOUN(UserDic_Roots[h_idx][node_index].node_info.info)) {
										noun_info_buf[noun_info_cnt++] = UserDic_Roots[h_idx][node_index].node_info.info;
									} else {
										result[*res_idx].len = char_index+1;
										result[*res_idx].info[0] = UserDic_Roots[h_idx][node_index].node_info.info;
										result[*res_idx].info[1] = 0;
										result[(*res_idx)++].jong = TRUE;
									}
#else
									result[*res_idx].len = char_index+1;
									result[*res_idx].info = UserDic_Roots[h_idx][node_index].node_info.info;
									result[(*res_idx)++].jong = TRUE;
#endif
								}
								if (UserDic_Roots[h_idx][node_index].node_info.brk == 1)
										break;
								node_index++;
							}
							node_index = old_node_index1;
						}
#ifdef MULTI_DIC_INFO
						if (noun_info_cnt > 0) {
							noun_info_buf[noun_info_cnt] = 0;
							result[*res_idx].len = char_index+1;
							strcpy((char*)result[*res_idx].info, (char*)noun_info_buf);
							result[(*res_idx)++].jong = TRUE;
						}
#endif
					}
				}

SKIP_CHECK2:;
				/* h_idx ���� ���� */
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
