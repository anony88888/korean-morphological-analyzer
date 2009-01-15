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
 * - 형식은 [단어]\t[기분석]\n[단어]\t[기분석]\n......\n[단어]\t[기분석]
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
#include <MA_Func.h>

#define USER_ANSDIC_FILE		"USERANSDIC.DIC"				/* 사용자 기분석 사전 파일명 */
#define MAX_UAD_CNT 10
#define MAX_USER_ANSDIC_CONS_SIZE 10000000
#define WANSUNG_JASO_NUM 51
#define WANSUNG_CODE_NUM 2350
#define ALPHABET_CODE_NUM 26
#define NUMBER_NUM 10

#define HEADER_NUM (WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + NUMBER_NUM)


static DIC_HEADER		UserAnsDic_Header[HEADER_NUM];		    /* 사용자 사전 메모리 헤더 */
static USERDIC_NODE			*UserAnsDic_Roots[HEADER_NUM];		/* 사용자 사전 메모리 Trie */
static UBYTE UserAnsDic_Cons[MAX_USER_ANSDIC_CONS_SIZE];                          /* 사용자 사전 크기 */
static int				isUserAnsDicExist;				        /* 현재 사용자 사전이 메모리에 있는지? */

tVOID InitUserAnsDicHeader()
{
	int i;

	for (i = 0; i < HEADER_NUM; i++) {
		UserAnsDic_Header[i].size = 0;
		UserAnsDic_Header[i].start = 0;
		UserAnsDic_Header[i].items = 0;
		UserAnsDic_Roots[i] = NULL;
	}

	isUserAnsDicExist = 0;
}

DWORD LoadUserAnsDic(BYTE *dic_dir)
{
	BYTE f_name[512];
	FILE *fd_dic;
	BYTE line[1024];
	//BYTE h_str[1024];
	BYTE *ptr;
	DWORD ret_val;
	BYTE word[1024], item_buf[1024];
	BYTE TotalInfoStr[S_BUFLEN];
	UDWORD StartIdx=0;   /* 형식형태소 분석 결과 위치 */
	UBYTE InfoLen;
	DWORD idx;
	int line_cnt=0;
	DWORD i,j;
	UserAnsDic_Cons[0]='\0';
	sprintf(f_name, "%s/%s", dic_dir, USER_ANSDIC_FILE);
	fd_dic = fopen(f_name, "rt");
	if (fd_dic == NULL) {
		isUserAnsDicExist = 0;
		return 0;
	}
	while (fgets(line, 1024, fd_dic)) {
		TotalInfoStr[0] = '\0';
		line_cnt++;
		
		idx =0;
        //USERANSDIC.DIC
        //성남시장애인정보    성남시_장애인_정보&성남_시_장애인_정보
        //단어 추가
        ptr = strtok(line, "\t\n");
		if(ptr == NULL)
			continue;
		strcpy(word,ptr); 
		ptr =strtok(NULL, "\n");
		
        while (*ptr != '\0' && *ptr != '\n') {
            if (*ptr & 0x80) {
                item_buf[idx] = *ptr;
                idx++; ptr++;
                item_buf[idx] = *ptr;
                idx++; ptr++;
                continue;
            }
			item_buf[idx]='\0';

            idx = 0;
            
            if (*ptr == '_'||*ptr == '&') {
			
                strcat(TotalInfoStr,item_buf);
                strcat(TotalInfoStr,"/N");
                if(*ptr == '&'){
					strcat(TotalInfoStr,"_");
				}  
				else 
					strcat(TotalInfoStr, "+");
					
                ptr++;
                item_buf[0]='\0';
				 
                continue;
            }
                
        }
		item_buf[idx]='\0';
		strcat(TotalInfoStr,item_buf);
        strcat(TotalInfoStr,"/N");
        InfoLen = strlen(TotalInfoStr);
        
        //if (ptr == NULL)
        //  continue;
		//strcat(UserAnsDic_Cons,TotalInfoStr);
		//strcat:속도문제로 인하여 구현/////////////////////
		j=0;i=0;
		i=StartIdx;
		while(TotalInfoStr[j]){
			UserAnsDic_Cons[i++]=TotalInfoStr[j++];
		}
		//////////////////////////////////////////////////
		if(StartIdx+InfoLen>MAX_USER_ANSDIC_CONS_SIZE){ //더이상 저장할 공간이 없음
			printf("StartIdx=%d\tMAX_USER_ANSDIC_CONS_SIZE overflow\n",StartIdx);
			return 0;}
		
	    ret_val = UAD_InsertWord(word, StartIdx, InfoLen);
		StartIdx += InfoLen;
		
       	/*
         * 여기에서 예외처리 해줘야 함...
         *
         */
    }	
	isUserAnsDicExist = 1;

	fclose(fd_dic);

	return 1;
}

DWORD SearchUserAnsDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, USERDIC_RESULT *result, UWORD *res_idx)
{
	DWORD ret_val;

	if (!isUserAnsDicExist)
		return 0;

	*res_idx = 0;
	ret_val = UAD_SearchWordInTrieDic(h_word, h_word_len, h_idx, result, res_idx);

	return ret_val;
}
WORD        /* 찾으면 : TRUE, 못 찾으면 : FALSE */
UAD_SearchCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index)
{
    DWORD node_index = *index;

    while (1) {
        if (UserAnsDic_Header[g_idx].items <= node_index)
            break;
        if (one_char.j_code == UserAnsDic_Roots[g_idx][node_index].han.j_code) {
            *index = node_index;
            return TRUE;
        }
        if (UserAnsDic_Roots[g_idx][node_index].node_info.brk == 1)
            break;
        else
            node_index++;
    }

    *index = node_index + 1;

    return FALSE;
} /* End of SearchCharInCurrentLevel */

DWORD UAD_SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, USERDIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;  /* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;
	UWORD ret_val;

	if (UserAnsDic_Header[h_idx].size == 0) {
		    *res_idx = 0;
		    return 0;
	}

	while (remain_chars > 0) {
		ret_val = UAD_SearchCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (UserAnsDic_Roots[h_idx][node_index].InfoStart != 0 ||
				UserAnsDic_Roots[h_idx][node_index].InfoLen != 0) {

				result[*res_idx].len = char_index + 1;
				result[*res_idx].InfoStart = UserAnsDic_Roots[h_idx][node_index].InfoStart;
				result[*res_idx].InfoLen = UserAnsDic_Roots[h_idx][node_index].InfoLen;

				(*res_idx)++;
			}

			remain_chars--;
			char_index++;

			if (remain_chars == 0) {
				if (*res_idx == 0)
					return 0;
				else
					return 1;
			}
			if (UserAnsDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += UserAnsDic_Roots[h_idx][node_index].node_info.next;
			else
				return 1;
		} else {
			if (*res_idx == 0)
				return 0;
			else 
				return 1;
		}
	}

	return 0;
} /* End of SearchWordInTrieDic */



DWORD UAD_InsertCharInTrieMiddle(HANGUL h_char, DWORD g_idx, DIC_HEADER *header, UDWORD index)
{
	UDWORD alloc_size = sizeof(USERDIC_NODE);

	UserAnsDic_Roots[g_idx] = (USERDIC_NODE *) MemoryAppend(UserAnsDic_Roots[g_idx], alloc_size);
	/* 한 노드 추가하고 */
	assert(UserAnsDic_Roots[g_idx] != NULL);
	header->size += alloc_size;

	MemoryMove(&(UserAnsDic_Roots[g_idx][index+1]), &(UserAnsDic_Roots[g_idx][index]),
									 (header->items - index)*sizeof(USERDIC_NODE));
	/* index 다음의 노드들은 한 노드씩 뒤로 민다 */

	UserAnsDic_Roots[g_idx][index].han = h_char;
	UserAnsDic_Roots[g_idx][index].node_info.brk = FALSE;
	UserAnsDic_Roots[g_idx][index].InfoStart = 0;
	UserAnsDic_Roots[g_idx][index].InfoLen = 0;
		
	UserAnsDic_Roots[g_idx][index].node_info.next = 0; 			/* 일단 */

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
DWORD UAD_InsertStrInTrieEnd(HANGUL *han_str, DWORD len, DWORD g_idx, DIC_HEADER *header, UDWORD StartIdx,UBYTE InfoLen)
{
	DWORD alloc_size = sizeof(USERDIC_NODE) * len;
	DWORD start_idx = header->items, i;
	DWORD ret_val = start_idx;

	UserAnsDic_Roots[g_idx] = (USERDIC_NODE *) MemoryAppend(UserAnsDic_Roots[g_idx], alloc_size);
	header->size += alloc_size;

	assert(UserAnsDic_Roots[g_idx] != NULL);

	i = 0;
	while (i < len) {
		UserAnsDic_Roots[g_idx][start_idx].han = han_str[i];
		/* next 값은 현재 노드와 목표노드의 거리이다. */
		UserAnsDic_Roots[g_idx][start_idx].node_info.next = 1;
		UserAnsDic_Roots[g_idx][start_idx].InfoStart = 0;
		UserAnsDic_Roots[g_idx][start_idx].InfoLen = 0;
				
		UserAnsDic_Roots[g_idx][start_idx].node_info.brk = TRUE;
		i++;
		start_idx++;
	}
	UserAnsDic_Roots[g_idx][start_idx-1].node_info.next = 0;
	UserAnsDic_Roots[g_idx][start_idx-1].InfoStart = StartIdx;
	UserAnsDic_Roots[g_idx][start_idx-1].InfoLen = InfoLen;
		
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
WORD UAD_InsertWord(BYTE *word, UDWORD StartIdx, UBYTE InfoLen)
{
	HANGUL voca[MAX_VOCA_LEN];	/* 한글 입력 표제어 */
	UWORD header_idx;
	DWORD voca_len;

	voca_len = MakeHanBuf((UBYTE*)word, voca, &header_idx);

	if (voca_len == 0)
		return 0;

	return (UAD_InsertWordInTrieDic(voca, voca_len, header_idx, StartIdx, InfoLen));
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
DWORD UAD_InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, UDWORD StartIdx, UBYTE InfoLen)
{
	UDWORD node_index = 0;	/* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD old_node_index = 0;	/* 이전 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;	/* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;	/* 남아있는 글자 수 */
	HANGUL one_char;
	UDWORD cl_idx;
	DWORD check_of;
	WORD ret_val;

	if (UserAnsDic_Header[h_idx].size == 0) {
		assert(UserAnsDic_Roots[h_idx] == NULL);

		node_index = UAD_InsertStrInTrieEnd(h_word, len, h_idx, 
													&(UserAnsDic_Header[h_idx]), StartIdx, InfoLen);
		char_index += len;

		return char_index;		/* 한글 스트링의 길이 만큼 리턴 */
	} else {
		while (remain_chars > 0) {
			ret_val = UAD_SearchCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
			if (ret_val == 1) {
				if (UserAnsDic_Roots[h_idx][node_index].node_info.next == 0) {
					if (remain_chars == 1) {
						/* 같은 표제어에 대해서 다른 정보가 입력 */
						/* 저장되는 글자는 0 으로 세팅 */
						/* 바로 다음 노드에 저장 */
						one_char.j_code = 0;
						UAD_InsertCharInTrieMiddle(one_char, h_idx,	&(UserAnsDic_Header[h_idx]), node_index + 1);

						node_index++;

						UserAnsDic_Roots[h_idx][node_index].InfoStart = StartIdx;
						UserAnsDic_Roots[h_idx][node_index].InfoLen = InfoLen;
						
						/* 만일 현재 노드가 현재 트리 레벨에서의 마지막 노드일 경우....
						   삽입되는 새로운 노드는 brk 값을 승계받아야 한다...*/
						if (UserAnsDic_Roots[h_idx][node_index-1].node_info.brk == 1) {
							UserAnsDic_Roots[h_idx][node_index-1].node_info.brk = 0;
							UserAnsDic_Roots[h_idx][node_index].node_info.brk = 1;
						} else
							UserAnsDic_Roots[h_idx][node_index].node_info.brk = 0;

						UserAnsDic_Roots[h_idx][node_index].node_info.next = 
										UserAnsDic_Roots[h_idx][node_index-1].node_info.next;

						/* 현재 레벨에서 노드가 하나 추가되었으므로 
						   현재 레벨의 next 값을 보정해주어야 한다. */

						/* 현재 노드의 이전 노드들에 대한 next 보정 */
						cl_idx = node_index - 1;
						while (1) {
							if (cl_idx == 0)
								break;
							/*
							if (UserAnsDic_Roots[h_idx][cl_idx].node_info.brk == 1)
								break;
								*/
							if (UserAnsDic_Roots[h_idx][cl_idx].node_info.next != 0 &&
								UserAnsDic_Roots[h_idx][cl_idx].node_info.next + cl_idx > node_index-1)
								UserAnsDic_Roots[h_idx][cl_idx].node_info.next++;
							cl_idx--;
						}

						return (len);
					} else {	
						old_node_index = node_index;
					/* 찾은 노드가 leaf 노드일 때 */
					/* 나머지를 모두 trie에 저장 */
						char_index++;
						node_index = UAD_InsertStrInTrieEnd(&(h_word[char_index]),
												len - char_index,
												h_idx,
												&(UserAnsDic_Header[h_idx]),
												StartIdx, InfoLen);
						/* next는 현재 노드와 목표 노드의 거리 */
						UserAnsDic_Roots[h_idx][old_node_index].node_info.next	= node_index - old_node_index;

						return (len);
					}
				} else { /* 다음 노드로 점프 */
					if (remain_chars == 1) {
					/* 기존에 있는 스트링의 서브스트링이 삽입되었을 때 */
						if (UserAnsDic_Roots[h_idx][node_index].InfoStart != 0 ||
							UserAnsDic_Roots[h_idx][node_index].InfoLen != 0) {
							
							/* 같은 표제어에 대해서 다른 정보가 삽입 */
							one_char.j_code = 0;
							UAD_InsertCharInTrieMiddle(one_char, h_idx,		
													&(UserAnsDic_Header[h_idx]), node_index + 1);

							node_index++;

							UserAnsDic_Roots[h_idx][node_index].InfoStart = StartIdx;
							UserAnsDic_Roots[h_idx][node_index].InfoLen = InfoLen;
											
							UserAnsDic_Roots[h_idx][node_index].node_info.brk = 0;
							UserAnsDic_Roots[h_idx][node_index].node_info.next = 
											UserAnsDic_Roots[h_idx][node_index-1].node_info.next;

							/* 현재 레벨에서 노드가 하나 추가되었으므로 
							   현재 레벨의 next 값을 보정해주어야 한다. */

							/* 현재 노드의 이전 노드들에 대한 next 보정 */
							cl_idx = node_index - 1;
							while (1) {
								if (cl_idx == 0)
									break;
								/*
								if (UserAnsDic_Roots[h_idx][cl_idx].node_info.brk == 1)
									break;
									*/
								if (UserAnsDic_Roots[h_idx][cl_idx].node_info.next != 0 &&
									UserAnsDic_Roots[h_idx][cl_idx].node_info.next + cl_idx > node_index-1)
									UserAnsDic_Roots[h_idx][cl_idx].node_info.next++;
								/*
								if (UserAnsDic_Roots[h_idx][cl_idx].node_info.next != 0)
									UserAnsDic_Roots[h_idx][cl_idx].node_info.next++;
									*/
								cl_idx--;
							}

							/* 현재 노드의 다음 노드들에 대한 next 보정 */
						} else {
							UserAnsDic_Roots[h_idx][node_index].InfoStart = StartIdx;
							UserAnsDic_Roots[h_idx][node_index].InfoLen = InfoLen;
														
						}

						return (char_index + 1);
					}
					node_index += UserAnsDic_Roots[h_idx][node_index].node_info.next;
					char_index++;
					remain_chars--;
				}
			} else {
			/* 현재 레벨에서 글자가 존재하지 않을 때 */
			/* 현재 레벨에 한 노드 추가 */
			/* node_index는 현재 레벨의 가장 마지막 노드의 다음 노드를 지정 */
				assert(node_index != 0);
				UAD_InsertCharInTrieMiddle(h_word[char_index], h_idx,
											&(UserAnsDic_Header[h_idx]), node_index);

				UserAnsDic_Roots[h_idx][node_index-1].node_info.brk = 0;
				UserAnsDic_Roots[h_idx][node_index].node_info.brk = 1;

				/* 현재 레벨에서 노드가 하나 추가되었으므로 
				   현재 레벨의 next 값을 보정해주어야 한다. */

				/* 현재 노드의 이전 노드들에 대한 next 보정 */
				cl_idx = node_index - 1;
				while (1) {
					if (cl_idx == 0)
						break;
					/*
					if (UserAnsDic_Roots[h_idx][cl_idx].node_info.brk == 1)
						break;
						*/
					if (UserAnsDic_Roots[h_idx][cl_idx].node_info.next != 0 &&
						UserAnsDic_Roots[h_idx][cl_idx].node_info.next + cl_idx > node_index-1)
						UserAnsDic_Roots[h_idx][cl_idx].node_info.next++;
					/*
					if (UserAnsDic_Roots[h_idx][cl_idx].node_info.next != 0)
						UserAnsDic_Roots[h_idx][cl_idx].node_info.next++;
						*/
					cl_idx--;
				}

				char_index++;

				if (remain_chars == 1) {
					UserAnsDic_Roots[h_idx][node_index].node_info.next = 0;
					UserAnsDic_Roots[h_idx][node_index].InfoStart = StartIdx;
					UserAnsDic_Roots[h_idx][node_index].InfoLen = InfoLen;
												
				} else {
/*
					UserAnsDic_Roots[h_idx][node_index].node_info.info = info;
*/
					check_of = UAD_InsertStrInTrieEnd(&h_word[char_index],
												len - char_index,
												h_idx,
												&(UserAnsDic_Header[h_idx]),
												StartIdx, InfoLen);

					UserAnsDic_Roots[h_idx][node_index].node_info.next = check_of - node_index;
				}
				return (char_index + 1);
			}
		}
	}

	return (char_index + 1);
} /* End of InsertWordInTrieDic */

DWORD CheckUserAnswerDic(HANGUL *hword, UWORD hword_len, UWORD h_idx, tUADMORP_RESULT *UADMorpRes, UWORD *UADMorpRes_Index)
{
	USERDIC_RESULT UAD_Result[DIC_RESULT_NUM];
    UWORD UAD_num;
    DWORD ret_val;
    UBYTE UAD_Content[L_BUFLEN]; /* 사용자 사전 기분석 내용 */
    /* 동일 어절에 대해서 서로 다른 여러개의 분석 결과가 나올 수 있다. */
    //UBYTE UAD_ItemContent[MAX_UAD_CNT][S_BUFLEN];
    //UBYTE tmpStr[VS_BUFLEN];
    //UWORD DupCnt = 0;
    UWORD MR_num;
    UBYTE *pCont;
    UBYTE ItemStr[S_BUFLEN];
    UWORD idx;
    UWORD PostWordStartPos, PostWordLen;

	extern DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str);
	*UADMorpRes_Index = 0;
    MR_num = 0;

    if (hword_len < 4)  //사용자 기분석 사전 길이 제한
        return 0;


	/*기분석 사전 탐색*/
	ret_val = SearchUserAnsDic(hword, hword_len, h_idx, UAD_Result, &UAD_num);

    if (ret_val == 0)
    return 0;
	/*가장 최장으로 검색되는 서브스트링에 대해서만 분석*/
   	GetUADContent(UAD_Result[UAD_num-1].InfoStart, UAD_Result[UAD_num-1].InfoLen, UAD_Content);

    PostWordStartPos = UAD_Result[UAD_num-1].len;
    PostWordLen = hword_len - UAD_Result[UAD_num-1].len;
	/* 사용자 기분석 결과 내용을 사용자 형태소 분석 결과에 저장*/
	pCont = UAD_Content;
	idx=0;
	UADMorpRes[MR_num].nMorp =0;
	
	while ( *pCont != '\0' ) {
		if (*pCont & 0x80) {
			ItemStr[idx] = *pCont;
			idx++; pCont++;
			ItemStr[idx] = *pCont;
			idx++; pCont++;

			continue;
		}

		if (*pCont == '/') {
			ItemStr[idx] = '\0';
			strcpy((char*)UADMorpRes[MR_num].MI[UADMorpRes[MR_num].nMorp].Morpheme, (char*)ItemStr);
			idx = 0;
			pCont++;

			continue;
		}

		if (*pCont == '+' || *pCont == '_') {
			UADMorpRes[MR_num].MI[UADMorpRes[MR_num].nMorp].info = ItemStr[0];
			UADMorpRes[MR_num].nMorp++;
			if (*pCont == '_') {
				MR_num++;
				UADMorpRes[MR_num].nMorp = 0;
			}
			idx = 0;
			pCont++;

			continue;
		}
		ItemStr[idx] = *pCont;
		idx++;pCont++;
	}
	UADMorpRes[MR_num].MI[UADMorpRes[MR_num].nMorp].info = ItemStr[0];
	UADMorpRes[MR_num].nMorp++;
	MR_num++;
	if(UAD_Result[UAD_num-1].len == hword_len){
		*UADMorpRes_Index = MR_num;
		return 1;
	}
	ret_val = TopicMorpAnal(&hword[PostWordStartPos], PostWordLen, COMPNOUN_POSTNOUN_P, hword[PostWordStartPos-1].j_han.jong);
	if(ret_val){
		*UADMorpRes_Index = MR_num;
		return 1;
	} else {
		return 0;
	}

}

DWORD GetUADContent(UDWORD s_idx, UBYTE len, UBYTE *Content)
{               
	if(s_idx+len >= MAX_USER_ANSDIC_CONS_SIZE)
		return 0;
	strncpy((char*)Content, (char*)&UserAnsDic_Cons[s_idx], len);
	Content[len] = '\0';
	return 1;
}  
