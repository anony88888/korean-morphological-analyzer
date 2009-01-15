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
 * - ������ [�ܾ�]\t[��м�]\n[�ܾ�]\t[��м�]\n......\n[�ܾ�]\t[��м�]
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
#include <MA_Func.h>

#define USER_ANSDIC_FILE		"USERANSDIC.DIC"				/* ����� ��м� ���� ���ϸ� */
#define MAX_UAD_CNT 10
#define MAX_USER_ANSDIC_CONS_SIZE 10000000
#define WANSUNG_JASO_NUM 51
#define WANSUNG_CODE_NUM 2350
#define ALPHABET_CODE_NUM 26
#define NUMBER_NUM 10

#define HEADER_NUM (WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + NUMBER_NUM)


static DIC_HEADER		UserAnsDic_Header[HEADER_NUM];		    /* ����� ���� �޸� ��� */
static USERDIC_NODE			*UserAnsDic_Roots[HEADER_NUM];		/* ����� ���� �޸� Trie */
static UBYTE UserAnsDic_Cons[MAX_USER_ANSDIC_CONS_SIZE];                          /* ����� ���� ũ�� */
static int				isUserAnsDicExist;				        /* ���� ����� ������ �޸𸮿� �ִ���? */

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
	UDWORD StartIdx=0;   /* �������¼� �м� ��� ��ġ */
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
        //���������������    ������_�����_����&����_��_�����_����
        //�ܾ� �߰�
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
		//strcat:�ӵ������� ���Ͽ� ����/////////////////////
		j=0;i=0;
		i=StartIdx;
		while(TotalInfoStr[j]){
			UserAnsDic_Cons[i++]=TotalInfoStr[j++];
		}
		//////////////////////////////////////////////////
		if(StartIdx+InfoLen>MAX_USER_ANSDIC_CONS_SIZE){ //���̻� ������ ������ ����
			printf("StartIdx=%d\tMAX_USER_ANSDIC_CONS_SIZE overflow\n",StartIdx);
			return 0;}
		
	    ret_val = UAD_InsertWord(word, StartIdx, InfoLen);
		StartIdx += InfoLen;
		
       	/*
         * ���⿡�� ����ó�� ����� ��...
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
WORD        /* ã���� : TRUE, �� ã���� : FALSE */
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
	UDWORD node_index = 0;  /* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;  /* ���� ���ڸ� ����Ű�� �ε��� */
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
	/* �� ��� �߰��ϰ� */
	assert(UserAnsDic_Roots[g_idx] != NULL);
	header->size += alloc_size;

	MemoryMove(&(UserAnsDic_Roots[g_idx][index+1]), &(UserAnsDic_Roots[g_idx][index]),
									 (header->items - index)*sizeof(USERDIC_NODE));
	/* index ������ ������ �� ��徿 �ڷ� �δ� */

	UserAnsDic_Roots[g_idx][index].han = h_char;
	UserAnsDic_Roots[g_idx][index].node_info.brk = FALSE;
	UserAnsDic_Roots[g_idx][index].InfoStart = 0;
	UserAnsDic_Roots[g_idx][index].InfoLen = 0;
		
	UserAnsDic_Roots[g_idx][index].node_info.next = 0; 			/* �ϴ� */

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
		/* next ���� ���� ���� ��ǥ����� �Ÿ��̴�. */
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
 *		Trie ������ ǥ����� ������ ����.
 */
WORD UAD_InsertWord(BYTE *word, UDWORD StartIdx, UBYTE InfoLen)
{
	HANGUL voca[MAX_VOCA_LEN];	/* �ѱ� �Է� ǥ���� */
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
 *		Ʈ���� ������ ǥ��� ����	
 */
DWORD UAD_InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, UDWORD StartIdx, UBYTE InfoLen)
{
	UDWORD node_index = 0;	/* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD old_node_index = 0;	/* ���� Ʈ���� ��带 ����Ű�� �ε��� */
	UDWORD char_index = 0;	/* ���� ���ڸ� ����Ű�� �ε��� */
	UDWORD remain_chars = len;	/* �����ִ� ���� �� */
	HANGUL one_char;
	UDWORD cl_idx;
	DWORD check_of;
	WORD ret_val;

	if (UserAnsDic_Header[h_idx].size == 0) {
		assert(UserAnsDic_Roots[h_idx] == NULL);

		node_index = UAD_InsertStrInTrieEnd(h_word, len, h_idx, 
													&(UserAnsDic_Header[h_idx]), StartIdx, InfoLen);
		char_index += len;

		return char_index;		/* �ѱ� ��Ʈ���� ���� ��ŭ ���� */
	} else {
		while (remain_chars > 0) {
			ret_val = UAD_SearchCharInCurrentLevel(h_word[char_index], h_idx, (DWORD*)&node_index);
			if (ret_val == 1) {
				if (UserAnsDic_Roots[h_idx][node_index].node_info.next == 0) {
					if (remain_chars == 1) {
						/* ���� ǥ��� ���ؼ� �ٸ� ������ �Է� */
						/* ����Ǵ� ���ڴ� 0 ���� ���� */
						/* �ٷ� ���� ��忡 ���� */
						one_char.j_code = 0;
						UAD_InsertCharInTrieMiddle(one_char, h_idx,	&(UserAnsDic_Header[h_idx]), node_index + 1);

						node_index++;

						UserAnsDic_Roots[h_idx][node_index].InfoStart = StartIdx;
						UserAnsDic_Roots[h_idx][node_index].InfoLen = InfoLen;
						
						/* ���� ���� ��尡 ���� Ʈ�� ���������� ������ ����� ���....
						   ���ԵǴ� ���ο� ���� brk ���� �°�޾ƾ� �Ѵ�...*/
						if (UserAnsDic_Roots[h_idx][node_index-1].node_info.brk == 1) {
							UserAnsDic_Roots[h_idx][node_index-1].node_info.brk = 0;
							UserAnsDic_Roots[h_idx][node_index].node_info.brk = 1;
						} else
							UserAnsDic_Roots[h_idx][node_index].node_info.brk = 0;

						UserAnsDic_Roots[h_idx][node_index].node_info.next = 
										UserAnsDic_Roots[h_idx][node_index-1].node_info.next;

						/* ���� �������� ��尡 �ϳ� �߰��Ǿ����Ƿ� 
						   ���� ������ next ���� �������־�� �Ѵ�. */

						/* ���� ����� ���� ���鿡 ���� next ���� */
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
					/* ã�� ��尡 leaf ����� �� */
					/* �������� ��� trie�� ���� */
						char_index++;
						node_index = UAD_InsertStrInTrieEnd(&(h_word[char_index]),
												len - char_index,
												h_idx,
												&(UserAnsDic_Header[h_idx]),
												StartIdx, InfoLen);
						/* next�� ���� ���� ��ǥ ����� �Ÿ� */
						UserAnsDic_Roots[h_idx][old_node_index].node_info.next	= node_index - old_node_index;

						return (len);
					}
				} else { /* ���� ���� ���� */
					if (remain_chars == 1) {
					/* ������ �ִ� ��Ʈ���� ���꽺Ʈ���� ���ԵǾ��� �� */
						if (UserAnsDic_Roots[h_idx][node_index].InfoStart != 0 ||
							UserAnsDic_Roots[h_idx][node_index].InfoLen != 0) {
							
							/* ���� ǥ��� ���ؼ� �ٸ� ������ ���� */
							one_char.j_code = 0;
							UAD_InsertCharInTrieMiddle(one_char, h_idx,		
													&(UserAnsDic_Header[h_idx]), node_index + 1);

							node_index++;

							UserAnsDic_Roots[h_idx][node_index].InfoStart = StartIdx;
							UserAnsDic_Roots[h_idx][node_index].InfoLen = InfoLen;
											
							UserAnsDic_Roots[h_idx][node_index].node_info.brk = 0;
							UserAnsDic_Roots[h_idx][node_index].node_info.next = 
											UserAnsDic_Roots[h_idx][node_index-1].node_info.next;

							/* ���� �������� ��尡 �ϳ� �߰��Ǿ����Ƿ� 
							   ���� ������ next ���� �������־�� �Ѵ�. */

							/* ���� ����� ���� ���鿡 ���� next ���� */
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

							/* ���� ����� ���� ���鿡 ���� next ���� */
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
			/* ���� �������� ���ڰ� �������� ���� �� */
			/* ���� ������ �� ��� �߰� */
			/* node_index�� ���� ������ ���� ������ ����� ���� ��带 ���� */
				assert(node_index != 0);
				UAD_InsertCharInTrieMiddle(h_word[char_index], h_idx,
											&(UserAnsDic_Header[h_idx]), node_index);

				UserAnsDic_Roots[h_idx][node_index-1].node_info.brk = 0;
				UserAnsDic_Roots[h_idx][node_index].node_info.brk = 1;

				/* ���� �������� ��尡 �ϳ� �߰��Ǿ����Ƿ� 
				   ���� ������ next ���� �������־�� �Ѵ�. */

				/* ���� ����� ���� ���鿡 ���� next ���� */
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
    UBYTE UAD_Content[L_BUFLEN]; /* ����� ���� ��м� ���� */
    /* ���� ������ ���ؼ� ���� �ٸ� �������� �м� ����� ���� �� �ִ�. */
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

    if (hword_len < 4)  //����� ��м� ���� ���� ����
        return 0;


	/*��м� ���� Ž��*/
	ret_val = SearchUserAnsDic(hword, hword_len, h_idx, UAD_Result, &UAD_num);

    if (ret_val == 0)
    return 0;
	/*���� �������� �˻��Ǵ� ���꽺Ʈ���� ���ؼ��� �м�*/
   	GetUADContent(UAD_Result[UAD_num-1].InfoStart, UAD_Result[UAD_num-1].InfoLen, UAD_Content);

    PostWordStartPos = UAD_Result[UAD_num-1].len;
    PostWordLen = hword_len - UAD_Result[UAD_num-1].len;
	/* ����� ��м� ��� ������ ����� ���¼� �м� ����� ����*/
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
