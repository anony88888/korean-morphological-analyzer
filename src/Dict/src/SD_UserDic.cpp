/*
 * 2003-06-30
 *
 * 사용자 사전 관리 모듈
 * - 사용자 사전 적재
 * - 사용자 사전 검색
 *
 * - 사용자 사전의 입력 파일은 일단 완성형 코드로 정해둔다.
 * - 처음에는 체언과 비체언으로 구분해서 입력하기로 하였으나...
 *   일반 사용자가 쓰기에는 어려울 것 같다.
 *   따라서 그냥 체언만 넣는 걸로 한다.
 * - 형식은 [단어]\n[단어]\n......\n[단어]
 */

/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_InsertCharInTrieMiddle.c)#  SPASIS System,     Thu Nov 18 22:08:09 1999
 *
 *	#(Action)#
 *		- 현재 레벨의 맨 마지막에 한 글자 노드를 추가한다.
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

#define USER_DIC_FILE		"USERDIC.DIC"				/* 사용자 사전 파일명 */

#define WANSUNG_JASO_NUM 51
#define WANSUNG_CODE_NUM 2350
#define ALPHABET_CODE_NUM 26
#define NUMBER_NUM 10

#define HEADER_NUM (WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + NUMBER_NUM)


static DIC_HEADER		UserDic_Header[HEADER_NUM];		/* 사용자 사전 메모리 헤더 */
static DIC_NODE			*UserDic_Roots[HEADER_NUM];		/* 사용자 사전 메모리 Trie */

static int				isDicExist;				/* 현재 사용자 사전이 메모리에 있는지? */

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
		ret_val = UD_InsertWord(h_str, 39);		// 사용자 사전 엔트리는 일단 고유명사정보로 지정
		/*
		 * 여기에서 예외처리 해줘야 함...
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
	/* 한 노드 추가하고 */
	assert(UserDic_Roots[g_idx] != NULL);
	header->size += alloc_size;

	MemoryMove(&(UserDic_Roots[g_idx][index+1]), &(UserDic_Roots[g_idx][index]),
									 (header->items - index)*sizeof(DIC_NODE));
	/* index 다음의 노드들은 한 노드씩 뒤로 민다 */

	UserDic_Roots[g_idx][index].han = h_char;
	UserDic_Roots[g_idx][index].node_info.brk = FALSE;
	UserDic_Roots[g_idx][index].node_info.info = 0;
	UserDic_Roots[g_idx][index].node_info.next = 0; 			/* 일단 */
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
 *		- 입력 스트링에 대해서 Trie의 맨 마지막에 차례로 Append한다.
 *		- 리턴 값은 맨 앞 글자 노드의 위치이다.
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
		/* next 값은 현재 노드와 목표노드의 거리이다. */
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
 *		Trie 사전에 표제어와 정보를 삽입.
 */
WORD UD_InsertWord(BYTE *word, BYTE info)
{
	HANGUL voca[MAX_VOCA_LEN];	/* 한글 입력 표제어 */
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
 *		트라이 사전에 표제어를 저장	
 */
DWORD UD_InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, BYTE info)
{
	UDWORD node_index = 0;	/* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD old_node_index = 0;	/* 이전 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;	/* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;	/* 남아있는 글자 수 */
	HANGUL one_char;
	UDWORD cl_idx;
	DWORD check_of;
	WORD ret_val;

	if (UserDic_Header[h_idx].size == 0) {
		assert(UserDic_Roots[h_idx] == NULL);

		node_index = UD_InsertStrInTrieEnd(h_word, len, h_idx, 
													&(UserDic_Header[h_idx]), info);
		char_index += len;

		return char_index;		/* 한글 스트링의 길이 만큼 리턴 */
	} else {
		while (remain_chars > 0) {
			ret_val = UD_SearchCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
			if (ret_val == 1) {
				if (UserDic_Roots[h_idx][node_index].node_info.next == 0) {
					if (remain_chars == 1) {
						/* 같은 표제어에 대해서 다른 정보가 입력 */
						/* 저장되는 글자는 0 으로 세팅 */
						/* 바로 다음 노드에 저장 */
						one_char.j_code = 0;
						UD_InsertCharInTrieMiddle(one_char, h_idx,	&(UserDic_Header[h_idx]), node_index + 1);

						node_index++;

						UserDic_Roots[h_idx][node_index].node_info.info = info;
						/* 만일 현재 노드가 현재 트리 레벨에서의 마지막 노드일 경우....
						   삽입되는 새로운 노드는 brk 값을 승계받아야 한다...*/
						if (UserDic_Roots[h_idx][node_index-1].node_info.brk == 1) {
							UserDic_Roots[h_idx][node_index-1].node_info.brk = 0;
							UserDic_Roots[h_idx][node_index].node_info.brk = 1;
						} else
							UserDic_Roots[h_idx][node_index].node_info.brk = 0;

						UserDic_Roots[h_idx][node_index].node_info.next = 
										UserDic_Roots[h_idx][node_index-1].node_info.next;

						/* 현재 레벨에서 노드가 하나 추가되었으므로 
						   현재 레벨의 next 값을 보정해주어야 한다. */

						/* 현재 노드의 이전 노드들에 대한 next 보정 */
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
					/* 찾은 노드가 leaf 노드일 때 */
					/* 나머지를 모두 trie에 저장 */
						char_index++;
						node_index = UD_InsertStrInTrieEnd(&(h_word[char_index]),
												len - char_index,
												h_idx,
												&(UserDic_Header[h_idx]),
												info);
						/* next는 현재 노드와 목표 노드의 거리 */
						UserDic_Roots[h_idx][old_node_index].node_info.next	= node_index - old_node_index;

						return (len);
					}
				} else { /* 다음 노드로 점프 */
					if (remain_chars == 1) {
					/* 기존에 있는 스트링의 서브스트링이 삽입되었을 때 */
						if (UserDic_Roots[h_idx][node_index].node_info.info != 0) {
							/* 같은 표제어에 대해서 다른 정보가 삽입 */
							one_char.j_code = 0;
							UD_InsertCharInTrieMiddle(one_char, h_idx,		
													&(UserDic_Header[h_idx]), node_index + 1);

							node_index++;

							UserDic_Roots[h_idx][node_index].node_info.info = info;
							UserDic_Roots[h_idx][node_index].node_info.brk = 0;
							UserDic_Roots[h_idx][node_index].node_info.next = 
											UserDic_Roots[h_idx][node_index-1].node_info.next;

							/* 현재 레벨에서 노드가 하나 추가되었으므로 
							   현재 레벨의 next 값을 보정해주어야 한다. */

							/* 현재 노드의 이전 노드들에 대한 next 보정 */
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

							/* 현재 노드의 다음 노드들에 대한 next 보정 */
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
			/* 현재 레벨에서 글자가 존재하지 않을 때 */
			/* 현재 레벨에 한 노드 추가 */
			/* node_index는 현재 레벨의 가장 마지막 노드의 다음 노드를 지정 */
				assert(node_index != 0);
				UD_InsertCharInTrieMiddle(h_word[char_index], h_idx,
											&(UserDic_Header[h_idx]), node_index);

				UserDic_Roots[h_idx][node_index-1].node_info.brk = 0;
				UserDic_Roots[h_idx][node_index].node_info.brk = 1;

				/* 현재 레벨에서 노드가 하나 추가되었으므로 
				   현재 레벨의 next 값을 보정해주어야 한다. */

				/* 현재 노드의 이전 노드들에 대한 next 보정 */
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
 *		- Trie의  현재 레벨에서 지정된 글자를 검색
 */
/*
 * 검색에 실패하였으면...
 * 현재 레벨의 가장 마지막 노드의 다음 노드를 지정...
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
 *		- 실제적인 사전 탐색 수행 
 */
DWORD UD_SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx)
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
	if (UserDic_Header[h_idx].size == 0) {
	    	if (h_word[0].j_han.sign == 0)
		    return 0;
	    	if (h_idx < WANSUNG_JASO_NUM) {
		    *res_idx = 0;
		    return 0;
		}
		h_idx = GetNoJongIndex(h_idx);
		/* 만약 "각"이라는 글자에 대한 종성없는 글자는 "가"(헤더인덱스 51) */
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

				/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
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
						/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
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
				/* h_idx 원상 복원 */
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

				/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
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

						/* 같은 표제어이면서 정보가 다른 표제어를 탐색 */
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
