/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_SearchCNDic.c)#  SPASIS System
 *
 *	#(Action)#
 *		- 복합명사 분석 정보 사전 탐색 모듈...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_Func.h>
#include <MA_HanType.h>
#include <MA_ReturnCode.h>
#include <MADIC_Type.h>

#ifdef SHARED_MEMORY_DIC
#include <MA_ShmOP.h>
#endif

#ifdef COMP_NOUN_DIC_CHECK

#define WANSUNG_JASO_NUM		51
#define WANSUNG_CODE_NUM		2350
#define ALPHABET_CODE_NUM		26
#define NUMBER_NUM			10

#define HEADER_NUM (WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + NUMBER_NUM)

#define COMPNOUN_DIC		"DICCN.DIC"             /* 복합명사 기분석 사전 이진파일 */
#define COMPNOUN_CON		"DICCN.CON"             /* 복합명사 분석 컨텐츠 사전 이진파일 */

#define RAW_COMPNOUN_DIC	"DIC.CN"                /* 복합명사 기분석 사전 원시파일 */

#define MAX_CNDIC_HEADER_SIZE 1000000
#define MAX_CNDICCON_HEADER_SIZE 1000000

static DIC_HEADER CNDic_Header[HEADER_NUM];            /* 복합명사 기분석 사전 헤더 */
static CNDIC_NODE *CNDic_Roots[HEADER_NUM];            /* 복합명사 기분석 사전 버퍼 */

static UBYTE *CNDic_Cons;

#ifdef SHARED_MEMORY_DIC
static BYTE *sh_CNDIC_ptr;
static BYTE *sh_CNDICCON_ptr;
BYTE *dic_ptr;
DWORD dic_size;
#endif

DWORD GetCNContent(UDWORD s_idx, UBYTE len, UBYTE *Content)
{
    strncpy((char*)Content, (char*)&CNDic_Cons[s_idx], len);
    Content[len] = '\0';

    return 1;
}

DWORD SearchCNDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, CNDIC_RESULT *result, UWORD *res_idx)
{
	DWORD ret_val;

	*res_idx = 0;
	ret_val = SearchWordInTrieDicCN(h_word, h_word_len, h_idx, result, res_idx);

	return (ret_val);
}

WORD		/* 찾으면 : TRUE, 못 찾으면 : FALSE */
SearchCharInCurrentLevelCN(HANGUL one_char, DWORD g_idx, DWORD *index)
{
	DWORD node_index = *index;

	while (1) {
		if (CNDic_Header[g_idx].items <= node_index)
			break;
		if (one_char.j_code == CNDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}
		if (CNDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	*index = node_index + 1;

	return FALSE;
} /* End of SearchCharInCurrentLevel */

DWORD
SearchWordInTrieDicCN(HANGUL *h_word, DWORD len, DWORD h_idx, CNDIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;  /* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;
	UWORD ret_val;

	if (CNDic_Header[h_idx].size == 0) {
		    *res_idx = 0;
		    return 0;
	}

	while (remain_chars > 0) {
		ret_val = SearchCharInCurrentLevelCN(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (CNDic_Roots[h_idx][node_index].InfoStart != 0 ||
				CNDic_Roots[h_idx][node_index].InfoLen != 0) {

				result[*res_idx].len = char_index + 1;
				result[*res_idx].InfoStart = CNDic_Roots[h_idx][node_index].InfoStart;
				result[*res_idx].InfoLen = CNDic_Roots[h_idx][node_index].InfoLen;

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

			if (CNDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += CNDic_Roots[h_idx][node_index].node_info.next;
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

tVOID InitCNDicHeader()
{
    DWORD i;

    for (i = 0; i < HEADER_NUM; i++) {
	CNDic_Header[i].size = 0;
	CNDic_Header[i].start = 0;
	CNDic_Header[i].items = 0;
	CNDic_Roots[i] = NULL;
    }
}

DWORD LoadCNDic(BYTE *dic_dir)
{
    BYTE dic_file[VS_BUFLEN];
    BYTE con_file[VS_BUFLEN];
    FILE *fd_dic, *fd_con;
    DWORD ret_val, i, f_size, ret_val1;
    strcpy(dic_file, dic_dir);
    strcpy(con_file, dic_dir);
#ifdef WIN32
    strcat(dic_file, "\\");
    strcat(dic_file, COMPNOUN_DIC);
    strcat(con_file, "\\");
    strcat(con_file, COMPNOUN_CON);
#else
    strcat(dic_file, "/");
    strcat(dic_file, COMPNOUN_DIC);
    strcat(con_file, "/");
    strcat(con_file, COMPNOUN_CON);
#endif

    fd_dic = fopen(dic_file, "rb");
    if (fd_dic == NULL) 
		return 0;

    fd_con = fopen(con_file, "rb");
    if (fd_con == NULL)
		return 0;
    ret_val = fread((BYTE *) CNDic_Header, sizeof(DIC_HEADER) * HEADER_NUM, 1, fd_dic);
    if (ret_val == 0)
		return 0;

#ifdef SHARED_MEMORY_DIC
	dic_size = 0;
	for (i = 0; i < HEADER_NUM; i++)
		dic_size += CNDic_Header[i].size;

	ret_val = GetShMem(CNDIC_KEY, dic_size, (BYTE **) &sh_CNDIC_ptr);
	//2007.01.09 바이너리 사전과 공유메모리 사전 크기가 다른 경우 ret =-1
	if(ret_val == -1){
        printf("Check the Dictionary version.\n");
        exit(-1);
    }
    else if (ret_val == 1) {
		/* 공유메모리가 새롭게 생성되었으면 ... */
		dic_ptr = sh_CNDIC_ptr;
		for (i = 0; i < HEADER_NUM; i++) {
			if (CNDic_Header[i].size != 0) {
				fseek(fd_dic, CNDic_Header[i].start, SEEK_SET);
				ret_val = fread(dic_ptr, CNDic_Header[i].size, 1, fd_dic);
				if (!feof(fd_dic) && ret_val == 0) {
					ClearCNDic();
					return 0;
				}
				CNDic_Roots[i] = (CNDIC_NODE *) dic_ptr;
				dic_ptr += CNDic_Header[i].size;
			}
		}
	} else {
		/* 기존에 공유메모리가 존재하면... */
		dic_ptr = sh_CNDIC_ptr;
		for (i = 0; i < HEADER_NUM; i++) {
			CNDic_Roots[i] = (CNDIC_NODE *) dic_ptr;
			dic_ptr += CNDic_Header[i].size;
		}
	}
#else
    for (i = 0; i < HEADER_NUM; i++) {

		if(CNDic_Header[i].size <0){
			printf("CNDic_Header[%d].size:%d\n", i, CNDic_Header[i].size);
			printf("Error:[DICCN] overflow of CNDic_Header[].size\n");
			printf("Check the Dictionary version.\n");
			exit(1);

		}
		if (CNDic_Header[i].size != 0) {
		
			if(CNDic_Header[i].size>MAX_CNDIC_HEADER_SIZE){
                printf("CNDic_Header[%d].size:%d\n", i, CNDic_Header[i].size);
                printf("the limit value of CNDic_Header[].size is %d\n",MAX_CNDIC_HEADER_SIZE);
                printf("Error:[DICCN]  ");
                printf("Check the Dictionary version.\n");
                exit(1);

            }

			CNDic_Roots[i] = (CNDIC_NODE *) malloc(CNDic_Header[i].size + sizeof(CNDIC_NODE) * 2);
			assert(CNDic_Roots[i] != NULL);
			fseek(fd_dic, CNDic_Header[i].start, SEEK_SET);
			ret_val = fread((BYTE *) CNDic_Roots[i], CNDic_Header[i].size, 1, fd_dic);
			if (!feof(fd_dic) && ret_val == 0) {
				ClearCNDic();
				return 0;
			}
		}
    }
#endif
    fseek(fd_con, 0L, SEEK_END);
    f_size = ftell(fd_con);
    fseek(fd_con, 0L, SEEK_SET);
#ifdef SHARED_MEMORY_DIC
	ret_val = GetShMem(CNDICCON_KEY, f_size, (BYTE **) &sh_CNDICCON_ptr);
	if (ret_val == 1) {
		/* 공유메모리가 새롭게 생성되었으면 */
		ret_val1 = fread(sh_CNDICCON_ptr, f_size, 1, fd_con);
		if (ret_val == 0) {
			ClearCNDic();
			return 0;
		}
		CNDic_Cons = (UBYTE *) sh_CNDICCON_ptr;
	} else
		CNDic_Cons = (UBYTE *) sh_CNDICCON_ptr;
#else 
    CNDic_Cons = (UBYTE *) malloc(f_size + 1);
    assert(CNDic_Cons != NULL);
    ret_val = fread(CNDic_Cons, f_size, 1, fd_con);
    if (ret_val == 0)
		return 0;
#endif

    fclose(fd_dic);
    fclose(fd_con);

    return 1;
}

DWORD ClearCNDic()
{
    DWORD i;

#ifdef SHARED_MEMORY_DIC
	ClearShMem((void **) &sh_CNDIC_ptr);
	ClearShMem((void **) &sh_CNDICCON_ptr);
#else
    for (i = 0; i < HEADER_NUM; i++)
		if (CNDic_Roots[i] != NULL)
			free(CNDic_Roots[i]);

    free(CNDic_Cons);
#endif

    return 1;
}
#endif
