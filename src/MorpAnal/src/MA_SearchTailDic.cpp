/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_SearchTAILDic.c)#  SPASIS System
 *
 *	#(Action)#
 *		- 형식형태소 분석 정보 사전 탐색 모듈...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_ReturnCode.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MA_SearchTailDic.h>

#define MAX_NTAILDIC_HEADER_SIZE 100000
#define MAX_PTAILDIC_HEADER_SIZE 100000
#define MAX_BTAILDIC_HEADER_SIZE 100000

#ifdef SHARED_MEMORY_DIC
#include <MA_ShmOP.h>
#endif

WORD full_match;

/*
static DIC_HEADER *TAILDic_Header;
static TAILDIC_NODE **TAILDic_Roots;
*/

static DIC_HEADER NTAILDic_Header[HEADER_NUM];         /* 체언형 형식형태소 사전 헤더 */
static TAILDIC_NODE *NTAILDic_Roots[HEADER_NUM];       /* 체언형 형식형태소 사전 버퍼 */

static DIC_HEADER PTAILDic_Header[HEADER_NUM];         /* 용언형 형식형태소 사전 헤더 */
static TAILDIC_NODE *PTAILDic_Roots[HEADER_NUM];       /* 용언형 형식형태소 사전 버퍼 */

static DIC_HEADER BTAILDic_Header[HEADER_NUM];         /* 체언형 실질-형식형태소 사전 헤더 */
static TAILDIC_NODE *BTAILDic_Roots[HEADER_NUM];       /* 체언형 실질-형식형태소 사전 버퍼 */

static UBYTE *TAILDic_Cons;

static UBYTE *NTAILDic_Cons;
static UBYTE *PTAILDic_Cons;
static UBYTE *BTAILDic_Cons;

#ifdef SHARED_MEMORY_DIC
static BYTE *sh_NTAILDIC_ptr;
static BYTE *sh_PTAILDIC_ptr;
static BYTE *sh_BTAILDIC_ptr;

static BYTE *dic_ptr;

static BYTE *sh_NTAILDIC_Cons_ptr;
static BYTE *sh_PTAILDIC_Cons_ptr;
static BYTE *sh_BTAILDIC_Cons_ptr;
#endif


DWORD GetTAILContent(UDWORD s_idx, UBYTE len, UBYTE *Content, UWORD mode)
{
    switch (mode) {
		case 1:
			TAILDic_Cons = NTAILDic_Cons;
			break;
		case 2:
			TAILDic_Cons = PTAILDic_Cons;
			break;
		case 3:
			TAILDic_Cons = BTAILDic_Cons;
			break;
    }

	strncpy((char*)Content, (char*)&TAILDic_Cons[s_idx], len);
	Content[len] = '\0';

	return 1;
}

static DWORD SearchWordInTrieDicNTAIL(HANGUL *h_word, DWORD len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx);
static DWORD SearchWordInTrieDicPTAIL(HANGUL *h_word, DWORD len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx);
static DWORD SearchWordInTrieDicBTAIL(HANGUL *h_word, DWORD len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx);

DWORD SearchTAILDic(HANGUL *h_word, UWORD h_word_len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx, UWORD mode)
{
    DWORD ret_val;

	if (h_idx == -1)
		return 0;

    *res_idx = 0;
	switch (mode) {
		case 1:
			ret_val = SearchWordInTrieDicNTAIL(h_word, h_word_len, h_idx, result, res_idx);
			break;
		case 2:
			ret_val = SearchWordInTrieDicPTAIL(h_word, h_word_len, h_idx, result, res_idx);
			break;
		case 3:
			ret_val = SearchWordInTrieDicBTAIL(h_word, h_word_len, h_idx, result, res_idx);
			break;
	}

	if (mode == 3) {
		if (ret_val)
			if (result[*res_idx-1].len < h_word_len)
				return 0;
	}

    return (ret_val);
}

static WORD		/* 찾으면 : TRUE, 못 찾으면 : FALSE */
SearchCharInCurrentLevelNTAIL(HANGUL one_char, DWORD g_idx
							  , DWORD *index)	/* 찾았을 때 : 찾은 노드의 next 값을 리턴 */
												/* 못찾았을 때 : 변화없음... */
{
	DWORD node_index = *index;

	while (1) {
		if (NTAILDic_Header[g_idx].items <= node_index)
			break;

		if (one_char.j_code == NTAILDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}

		if (NTAILDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	return FALSE;
} /* End of SearchCharInCurrentLevel */

static DWORD SearchWordInTrieDicNTAIL(HANGUL *h_word, DWORD len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;  /* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;
	UWORD ret_val;

	if (NTAILDic_Header[h_idx].size == 0) {
		*res_idx = 0;
		return 0;
	}

	while (remain_chars > 0) {
		ret_val = SearchCharInCurrentLevelNTAIL(h_word[char_index], h_idx, (DWORD *)&node_index);
		if (ret_val == 1) {
			if (NTAILDic_Roots[h_idx][node_index].InfoStart != 0 ||
					NTAILDic_Roots[h_idx][node_index].InfoLen != 0) {
				result[*res_idx].len = char_index + 1;
				result[*res_idx].InfoStart = NTAILDic_Roots[h_idx][node_index].InfoStart;
				result[*res_idx].InfoLen = NTAILDic_Roots[h_idx][node_index].InfoLen;

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

			if (NTAILDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += NTAILDic_Roots[h_idx][node_index].node_info.next;
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

static WORD		/* 찾으면 : TRUE, 못 찾으면 : FALSE */
SearchCharInCurrentLevelPTAIL(HANGUL one_char, DWORD g_idx
							  , DWORD *index)	/* 찾았을 때 : 찾은 노드의 next 값을 리턴 */
												/* 못찾았을 때 : 변화없음... */
{
	DWORD node_index = *index;

	while (1) {
		if (PTAILDic_Header[g_idx].items <= node_index)
			break;

		if (one_char.j_code == PTAILDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}

		if (PTAILDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	return FALSE;
} /* End of SearchCharInCurrentLevel */

static DWORD SearchWordInTrieDicPTAIL(HANGUL *h_word, DWORD len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;  /* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;
	UWORD ret_val;

	if (PTAILDic_Header[h_idx].size == 0) {
		*res_idx = 0;
		return 0;
	}

	while (remain_chars > 0) {
		ret_val = SearchCharInCurrentLevelPTAIL(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (PTAILDic_Roots[h_idx][node_index].InfoStart != 0 ||
					PTAILDic_Roots[h_idx][node_index].InfoLen != 0) {
				result[*res_idx].len = char_index + 1;
				result[*res_idx].InfoStart = PTAILDic_Roots[h_idx][node_index].InfoStart;
				result[*res_idx].InfoLen = PTAILDic_Roots[h_idx][node_index].InfoLen;

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

			if (PTAILDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += PTAILDic_Roots[h_idx][node_index].node_info.next;
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

static WORD		/* 찾으면 : TRUE, 못 찾으면 : FALSE */
SearchCharInCurrentLevelBTAIL(HANGUL one_char
  , DWORD g_idx
  , DWORD *index)	/* 찾았을 때 : 찾은 노드의 next 값을 리턴 */
				/* 못찾았을 때 : 변화없음... */
{
	DWORD node_index = *index;

	while (1) {
		if (BTAILDic_Header[g_idx].items <= node_index)
			break;

		if (one_char.j_code == BTAILDic_Roots[g_idx][node_index].han.j_code) {
			*index = node_index;
			return TRUE;
		}

		if (BTAILDic_Roots[g_idx][node_index].node_info.brk == 1)
			break;
		else
			node_index++;
	}

	return FALSE;
} /* End of SearchCharInCurrentLevel */

static DWORD SearchWordInTrieDicBTAIL(HANGUL *h_word, DWORD len, DWORD h_idx, TAILDIC_RESULT *result, UWORD *res_idx)
{
	UDWORD node_index = 0;  /* 현재 트라이 노드를 가리키는 인덱스 */
	UDWORD char_index = 0;  /* 현재 글자를 가리키는 인덱스 */
	UDWORD remain_chars = len;
	UWORD ret_val;

	if (BTAILDic_Header[h_idx].size == 0) {
		*res_idx = 0;
		return 0;
	}

	while (remain_chars > 0) {
		ret_val = SearchCharInCurrentLevelBTAIL(h_word[char_index], h_idx, (DWORD*)&node_index);
		if (ret_val == 1) {
			if (BTAILDic_Roots[h_idx][node_index].InfoStart != 0 ||
					BTAILDic_Roots[h_idx][node_index].InfoLen != 0) {
				result[*res_idx].len = char_index + 1;
				result[*res_idx].InfoStart = BTAILDic_Roots[h_idx][node_index].InfoStart;
				result[*res_idx].InfoLen = BTAILDic_Roots[h_idx][node_index].InfoLen;

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

			if (BTAILDic_Roots[h_idx][node_index].node_info.next != 0)
				node_index += BTAILDic_Roots[h_idx][node_index].node_info.next;
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

tVOID InitTAILDicHeader()
{
	DWORD i;

	for (i = 0; i < HEADER_NUM; i++) {
		NTAILDic_Header[i].size = 0;
		NTAILDic_Header[i].start = 0;
		NTAILDic_Header[i].items = 0;
		NTAILDic_Roots[i] = NULL;

		PTAILDic_Header[i].size = 0;
		PTAILDic_Header[i].start = 0;
		PTAILDic_Header[i].items = 0;
		PTAILDic_Roots[i] = NULL;

		BTAILDic_Header[i].size = 0;
		BTAILDic_Header[i].start = 0;
		BTAILDic_Header[i].items = 0;
		BTAILDic_Roots[i] = NULL;
	}
}

DWORD LoadTAILDic(BYTE *dic_dir)
{
	BYTE dic_file[VS_BUFLEN];
	BYTE con_file[VS_BUFLEN];
	FILE *fd_dic, *fd_con;
	DWORD ret_val, i, f_size;
#ifdef SHARED_MEMORY_DIC
	DWORD dic_size;
	DWORD ret_val1;
#endif
	strcpy(dic_file, dic_dir);
	strcpy(con_file, dic_dir);
#ifdef WIN32
	strcat(dic_file, "\\");
	strcat(dic_file, NTAIL_DIC);
	strcat(con_file, "\\");
	strcat(con_file, NTAIL_CON);
#else
	strcat(dic_file, "/");
	strcat(dic_file, NTAIL_DIC);
	strcat(con_file, "/");
	strcat(con_file, NTAIL_CON);
#endif
	
	fd_dic = fopen(dic_file, "rb");
	if (fd_dic == NULL) 
		return 0;

	fd_con = fopen(con_file, "rb");
	if (fd_con == NULL)
		return 0;

	ret_val = fread((BYTE *) NTAILDic_Header, sizeof(DIC_HEADER) * HEADER_NUM, 1, fd_dic);
	if (ret_val == 0)
		return 0;

#ifdef SHARED_MEMORY_DIC
    dic_size = 0;
    for (i = 0; i < HEADER_NUM; i++)
        dic_size += NTAILDic_Header[i].size;

    ret_val = GetShMem(NTAILDIC_KEY, dic_size, (tVOID **) &sh_NTAILDIC_ptr);
   	//2007.01.09 바이너리 사전과 공유메모리 사전 크기가 다른 경우 ret =-1:q

    if(ret_val == -1){
        printf("Check the Dictionary version.\n");
        exit(-1);
    } else if (ret_val == 1) {
        /* 공유메모리가 새롭게 생성되었으면 ... */
        dic_ptr = sh_NTAILDIC_ptr;
        for (i = 0; i < HEADER_NUM; i++) {
            if (NTAILDic_Header[i].size != 0) {
                fseek(fd_dic, NTAILDic_Header[i].start, SEEK_SET);
                ret_val = fread(dic_ptr, NTAILDic_Header[i].size, 1, fd_dic);
                if (!feof(fd_dic) && ret_val == 0) {
                    ClearTAILDic();
                    return 0;
                }
                NTAILDic_Roots[i] = (TAILDIC_NODE *) dic_ptr;
                dic_ptr += NTAILDic_Header[i].size;
            }
        }
    } else {
        /* 기존에 공유메모리가 존재하면... */
        dic_ptr = sh_NTAILDIC_ptr;
        for (i = 0; i < HEADER_NUM; i++) {
            NTAILDic_Roots[i] = (TAILDIC_NODE *) dic_ptr;
            dic_ptr += NTAILDic_Header[i].size;
        }
    }
#else
	for (i = 0; i < HEADER_NUM; i++) {

		if (NTAILDic_Header[i].size != 0) {
			if(NTAILDic_Header[i].size>MAX_NTAILDIC_HEADER_SIZE){
                printf("NTAILDic_Header[%d].size:%d\n", i, NTAILDic_Header[i].size);
                printf("the limit value of NTAILDic_Header[].size is %d\n",MAX_NTAILDIC_HEADER_SIZE);
                printf("Error:[DICNTAIL]  ");
                printf("Check the Dictionary version.\n");
                exit(1);

            }
	
			 
			NTAILDic_Roots[i] = (TAILDIC_NODE *) malloc(NTAILDic_Header[i].size + sizeof(TAILDIC_NODE) * 2);
			assert(NTAILDic_Roots[i] != NULL);
			fseek(fd_dic, NTAILDic_Header[i].start, SEEK_SET);
			ret_val = fread((BYTE *) NTAILDic_Roots[i], NTAILDic_Header[i].size, 1, fd_dic);
			if (!feof(fd_dic) && ret_val == 0) {
				ClearTAILDic();
				return 0;
			}
		}
	}
#endif

	fseek(fd_con, 0L, SEEK_END);
	f_size = ftell(fd_con);
	fseek(fd_con, 0L, SEEK_SET);

#ifdef SHARED_MEMORY_DIC
	ret_val = GetShMem(NTAILDICCON_KEY, f_size, (tVOID **) &sh_NTAILDIC_Cons_ptr);
	//2007.01.09 바이너리 사전과 공유메모리 사전 크기가 다른 경우 ret =-1:q

    if(ret_val == -1){
        printf("Check the Dictionary version.\n");
        exit(-1);
    } else if (ret_val == 1) {
		ret_val1 = fread(sh_NTAILDIC_Cons_ptr, f_size, 1, fd_con);
		if (ret_val1 == 0) {
			ClearTAILDic();
			return 0;
		}
		NTAILDic_Cons = (UBYTE *) sh_NTAILDIC_Cons_ptr;
	} else
		NTAILDic_Cons = (UBYTE *) sh_NTAILDIC_Cons_ptr;

#else
	NTAILDic_Cons = (UBYTE *) malloc(f_size + 1);
	assert(NTAILDic_Cons != NULL);
	ret_val = fread(NTAILDic_Cons, f_size, 1, fd_con);
	if (ret_val == 0)
		return 0;
#endif

	fclose(fd_dic);
	fclose(fd_con);
	strcpy(dic_file, dic_dir);
	strcpy(con_file, dic_dir);
#ifdef WIN32
	strcat(dic_file, "\\");
	strcat(dic_file, PTAIL_DIC);
	strcat(con_file, "\\");
	strcat(con_file, PTAIL_CON);
#else
	strcat(dic_file, "/");
	strcat(dic_file, PTAIL_DIC);
	strcat(con_file, "/");
	strcat(con_file, PTAIL_CON);
#endif

	fd_dic = fopen(dic_file, "rb");
	if (fd_dic == NULL) 
		return 0;

	fd_con = fopen(con_file, "rb");
	if (fd_con == NULL)
		return 0;

	ret_val = fread((BYTE *) PTAILDic_Header, sizeof(DIC_HEADER) * HEADER_NUM, 1, fd_dic);
	if (ret_val == 0)
		return 0;

#ifdef SHARED_MEMORY_DIC
    dic_size = 0;
    for (i = 0; i < HEADER_NUM; i++)
        dic_size += PTAILDic_Header[i].size;

    ret_val = GetShMem(PTAILDIC_KEY, dic_size, (tVOID **) &sh_PTAILDIC_ptr);
    //2007.01.09 바이너리 사전과 공유메모리 사전 크기가 다른 경우 ret =-1:q

    if(ret_val == -1){
        printf("Check the Dictionary version.\n");
        exit(-1);
    }else if (ret_val == 1) {
        /* 공유메모리가 새롭게 생성되었으면 ... */
        dic_ptr = sh_PTAILDIC_ptr;
        for (i = 0; i < HEADER_NUM; i++) {
			
            if (PTAILDic_Header[i].size != 0){
                fseek(fd_dic, PTAILDic_Header[i].start, SEEK_SET);
                ret_val = fread(dic_ptr, PTAILDic_Header[i].size, 1, fd_dic);
                if (!feof(fd_dic) && ret_val == 0) {
                    ClearTAILDic();
                    return 0;
                }
                PTAILDic_Roots[i] = (TAILDIC_NODE *) dic_ptr;
                dic_ptr += PTAILDic_Header[i].size;
            }
        }
    } else {
        /* 기존에 공유메모리가 존재하면... */
        dic_ptr = sh_PTAILDIC_ptr;
        for (i = 0; i < HEADER_NUM; i++) {
            PTAILDic_Roots[i] = (TAILDIC_NODE *) dic_ptr;
            dic_ptr += PTAILDic_Header[i].size;
        }
    }
#else
	for (i = 0; i < HEADER_NUM; i++) {
		if (PTAILDic_Header[i].size != 0) {
			if(PTAILDic_Header[i].size>MAX_PTAILDIC_HEADER_SIZE){
                    printf("PTAILDic_Header[%d].size:%d\n", i, PTAILDic_Header[i].size);
                    printf("the limit value of PTAILDic_Header[].size is %d\n",MAX_PTAILDIC_HEADER_SIZE);
                    printf("Error:[DICPTAIL]  ");
                    printf("Check the Dictionary version.\n");
                    exit(1);

            }
 
			PTAILDic_Roots[i] = (TAILDIC_NODE *) malloc(PTAILDic_Header[i].size + sizeof(TAILDIC_NODE) * 2);
			assert(PTAILDic_Roots[i] != NULL);
			fseek(fd_dic, PTAILDic_Header[i].start, SEEK_SET);
			ret_val = fread((BYTE *) PTAILDic_Roots[i], PTAILDic_Header[i].size, 1, fd_dic);
			if (!feof(fd_dic) && ret_val == 0) {
				ClearTAILDic();
				return 0;
			}
		}
	}
#endif

	fseek(fd_con, 0L, SEEK_END);
	f_size = ftell(fd_con);
	fseek(fd_con, 0L, SEEK_SET);

#ifdef SHARED_MEMORY_DIC
	ret_val = GetShMem(PTAILDICCON_KEY, f_size, (tVOID **) &sh_PTAILDIC_Cons_ptr);
	if (ret_val == 1) {
		ret_val1 = fread(sh_PTAILDIC_Cons_ptr, f_size, 1, fd_con);
		if (ret_val1 == 0) {
			ClearTAILDic();
			return 0;
		}
		PTAILDic_Cons = (UBYTE *) sh_PTAILDIC_Cons_ptr;
	} else
		PTAILDic_Cons = (UBYTE *) sh_PTAILDIC_Cons_ptr;

#else
	PTAILDic_Cons = (UBYTE *) malloc(f_size + 1);
	assert(PTAILDic_Cons != NULL);
	ret_val = fread(PTAILDic_Cons, f_size, 1, fd_con);
	if (ret_val == 0)
		return 0;
#endif

	fclose(fd_dic);
	fclose(fd_con);

	strcpy(dic_file, dic_dir);
	strcpy(con_file, dic_dir);
#ifdef WIN32
	strcat(dic_file, "\\");
	strcat(dic_file, BTAIL_DIC);
	strcat(con_file, "\\");
	strcat(con_file, BTAIL_CON);
#else
	strcat(dic_file, "/");
	strcat(dic_file, BTAIL_DIC);
	strcat(con_file, "/");
	strcat(con_file, BTAIL_CON);
#endif
	fd_dic = fopen(dic_file, "rb");
	if (fd_dic == NULL) 
		return 0;

	fd_con = fopen(con_file, "rb");
	if (fd_con == NULL)
		return 0;

	ret_val = fread((BYTE *) BTAILDic_Header, sizeof(DIC_HEADER) * HEADER_NUM, 1, fd_dic);
	if (ret_val == 0)
		return 0;

#ifdef SHARED_MEMORY_DIC
    dic_size = 0;
    for (i = 0; i < HEADER_NUM; i++)
        dic_size += BTAILDic_Header[i].size;

    ret_val = GetShMem(BTAILDIC_KEY, dic_size, (tVOID **) &sh_BTAILDIC_ptr);
    if (ret_val == 1) {
        /* 공유메모리가 새롭게 생성되었으면 ... */
        dic_ptr = sh_BTAILDIC_ptr;
        for (i = 0; i < HEADER_NUM; i++) {
            if (BTAILDic_Header[i].size != 0) {
                fseek(fd_dic, BTAILDic_Header[i].start, SEEK_SET);
                ret_val = fread(dic_ptr, BTAILDic_Header[i].size, 1, fd_dic);
                if (!feof(fd_dic) && ret_val == 0) {
                    ClearTAILDic();
                    return 0;
                }
                BTAILDic_Roots[i] = (TAILDIC_NODE *) dic_ptr;
                dic_ptr += BTAILDic_Header[i].size;
            }
        }
    } else {
        /* 기존에 공유메모리가 존재하면... */
        dic_ptr = sh_BTAILDIC_ptr;
        for (i = 0; i < HEADER_NUM; i++) {
            BTAILDic_Roots[i] = (TAILDIC_NODE *) dic_ptr;
            dic_ptr += BTAILDic_Header[i].size;
        }
    }
#else
	for (i = 0; i < HEADER_NUM; i++) {
		if (BTAILDic_Header[i].size != 0) {
			if(BTAILDic_Header[i].size>MAX_BTAILDIC_HEADER_SIZE){
                    printf("BTAILDic_Header[%d].size:%d\n", i, BTAILDic_Header[i].size);
                    printf("the limit value of BTAILDic_Header[].size is %d\n",MAX_BTAILDIC_HEADER_SIZE);
                    printf("Error:[DICBTAIL]  ");
                    printf("Check the Dictionary version.\n");
                    exit(1);

            }

			BTAILDic_Roots[i] = (TAILDIC_NODE *) malloc(BTAILDic_Header[i].size + sizeof(TAILDIC_NODE) * 2);
			assert(BTAILDic_Roots[i] != NULL);
			fseek(fd_dic, BTAILDic_Header[i].start, SEEK_SET);
			ret_val = fread((BYTE *) BTAILDic_Roots[i], BTAILDic_Header[i].size, 1, fd_dic);
			if (!feof(fd_dic) && ret_val == 0) {
				ClearTAILDic();
				return 0;
			}
		}
	}
#endif

	fseek(fd_con, 0L, SEEK_END);
	f_size = ftell(fd_con);
	fseek(fd_con, 0L, SEEK_SET);

#ifdef SHARED_MEMORY_DIC
	ret_val = GetShMem(BTAILDICCON_KEY, f_size, (tVOID **) &sh_BTAILDIC_Cons_ptr);
	if (ret_val == 1) {
		ret_val1 = fread(sh_BTAILDIC_Cons_ptr, f_size, 1, fd_con);
		if (ret_val1 == 0) {
			ClearTAILDic();
			return 0;
		}
		BTAILDic_Cons = (UBYTE *) sh_BTAILDIC_Cons_ptr;
	} else
		BTAILDic_Cons = (UBYTE *) sh_BTAILDIC_Cons_ptr;

#else
	BTAILDic_Cons = (UBYTE *) malloc(f_size + 1);
	assert(BTAILDic_Cons != NULL);
	ret_val = fread(BTAILDic_Cons, f_size, 1, fd_con);
	if (ret_val == 0)
		return 0;
#endif

	fclose(fd_dic);
	fclose(fd_con);

	return 1;
}

DWORD ClearTAILDic()
{
	DWORD i;

#ifdef SHARED_MEMORY_DIC
	ClearShMem((void **) &sh_NTAILDIC_ptr);
	ClearShMem((void **) &sh_PTAILDIC_ptr);
	ClearShMem((void **) &sh_BTAILDIC_ptr);

	ClearShMem((void **) &sh_NTAILDIC_Cons_ptr);
	ClearShMem((void **) &sh_PTAILDIC_Cons_ptr);
	ClearShMem((void **) &sh_BTAILDIC_Cons_ptr);
#else
	for (i = 0; i < HEADER_NUM; i++) {
		if (NTAILDic_Roots[i] != NULL)
			free(NTAILDic_Roots[i]);
		if (PTAILDic_Roots[i] != NULL)
			free(PTAILDic_Roots[i]);
		if (BTAILDic_Roots[i] != NULL)
			free(BTAILDic_Roots[i]);
	}

	free(NTAILDic_Cons);
	free(PTAILDic_Cons);
	free(BTAILDic_Cons);
#endif

	return 1;
}
