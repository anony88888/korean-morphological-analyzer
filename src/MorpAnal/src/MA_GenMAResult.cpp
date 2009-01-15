/*
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.31
 * 
 *	#(Action)#
 *		- 형태소 분석 결과를 가공...및 출력...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Global.h>
#include <MA_Jo2Wan.h>
#include <MA_Interface.h>

int compare_index_str(const void *, const void *);
tVOID Convert_NumInfo(unsigned short int info, char *info_str);
tVOID Convert_StrInfo(char *info, char *info_str);
tVOID FilterMAResult(ITF_MA_RESULT *ma_result, tMORP_RESULT *sMorpResult, UWORD sMorpResult_Index);
#ifdef SUSA_AS_INDEX
DWORD FilterIndexWord(INDEX_WORD *index_words, tMORP_RESULT *sMorpResult, UWORD sMorpRes_Index)
#else
DWORD FilterIndexWord(INDEX_WORD *index_words)
#endif
{
    DWORD i, j, k, idx1, idx2;
    UBYTE han_str[VS_BUFLEN];
    H_CHAR one_han;
    DWORD ind = 0;
    INDEX_ITEM index_buf[S_BUFLEN];
    INDEX_ITEM total_index_buf[S_BUFLEN];
    DWORD tib_idx = 0, ib_idx = 0, old_ib_idx;
    UBYTE temp_index[VS_BUFLEN];
    UBYTE temp_loc;
    UWORD sPos;

    index_words->nIndex = 0;
#ifdef SUSA_AS_INDEX
    if (sMorpRes_Index > 0) {
	for (j = 0; j < sMorpRes_Index; j++) {
	    ind = 0;
	    for (i = 0; i < sMorpResult[j].nMorp; i++) {
		if (strcmp(sMorpResult[j].MI[i].info, "SUSA") && strcmp(sMorpResult[j].MI[i].info, "UNIT"))
		    break;
		k = 0;
		while (sMorpResult[j].MI[i].Morpheme[k] != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		    if (sMorpResult[j].MI[i].Morpheme[k] >= 0x8442 &&
			sMorpResult[j].MI[i].Morpheme[k] <= 0xd3b7) {	/* 조합형 한글이면 */
			one_han.code = jo2wan[sMorpResult[j].MI[i].Morpheme[k]-0x8442][1];
			han_str[ind++] = one_han.hl.high;
			han_str[ind++] = one_han.hl.low;
		    } else {		/* 한글이 아닌 아스키 코드 이면 */
			one_han.code = sMorpResult[j].MI[i].Morpheme[k];
			han_str[ind++] = one_han.hl.high;
		    }
		    k++;
		}
	    }
	    han_str[ind] = '\0';

	    strcpy((char*)total_index_buf[tib_idx].str, (char*)han_str);
	    total_index_buf[tib_idx].loc = 0;
	    tib_idx++;
	}
    }
#endif
    for (i = 0; i < M_MORPRESULT_INDEX; i++) {
	old_ib_idx = ib_idx;
	ib_idx = 0;
	sPos = 0;
	for (j = 0; j < M_MORPRESULT_NMORP(i); j++) {
	    if (32 <= M_MORPRESULT_MI_INFO_ITEM(i, j, 0) && M_MORPRESULT_MI_INFO_ITEM(i, j, 0) <= 40) {
		k = 0;
		ind = 0;

		while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD) 0) {
		    if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
			    M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) {	/* 조합형 한글이면 */
			one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)-0x8442][1];
			han_str[ind++] = one_han.hl.high;
			han_str[ind++] = one_han.hl.low;
		    } else {		/* 한글이 아닌 아스키 코드 이면 */
			one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k);
			han_str[ind++] = one_han.hl.high;
		    }
		    k++;
		}

		han_str[ind] = '\0';

		strcpy((char*)index_buf[ib_idx].str, (char*)han_str);
		index_buf[ib_idx].loc = sPos;
		ib_idx++;
		sPos += ind;
	    } else {
		ind = 0;
		k = 0;
		while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD) 0) {
		    if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
			    M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) /* 조합형 한글이면 */
			ind += 2;
		    else 
			ind++;
		    k++;
		}
		sPos += ind;
	    }
	}

#ifdef COMPOUND_NOUN_AS_ONE_INDEX
	/* 복합명사는 무조건 하나의 색인어로 가정 */
	if (ib_idx > 0) {
	    for (j = 1; j < ib_idx; j++)
		strcat(index_buf[0].str, index_buf[j]);
	    ib_idx = 1;
	}
#elif COMPOUND_NOUN_AS_INDEX
	/* 복합명사를 하나의 색인어로 가정하고 이를 추가... */
	if (ib_idx > 1) {
	    temp_index[0] = '\0';
	    for (j = 0; j < ib_idx; j++)
		strcat(temp_index, index_buf[j].str);
	    strcpy(index_buf[ib_idx].str, temp_index);
	    index_buf[ib_idx].loc = index_buf[0].loc;
	    ib_idx++;
	}
#endif

	/*
	 * 만일 현재 형태소결과가 명사로 끝나는 복합명사 형태로 구성되었을 때...
	 * 구체적인 --> 구체 + 적인 분석 방지.
	 * 오염물질의 --> 오염물 + 질의 분석 방지.
	 * 아황산소다와의 --> 아황산+소다+와의 분석 방지.
	 */

	if (i > 0) {
	    idx1 = M_MORPRESULT_NMORP(i-1) - 1;
	    idx2 = M_MORPRESULT_NMORP(i) - 1;
	    if (!IS_INDEX_INFO(M_MORPRESULT_MI_INFO_ITEM(i-1, idx1, 0)) &&
		    IS_INDEX_INFO(M_MORPRESULT_MI_INFO_ITEM(i, idx2, 0)))
		;
	    else {
		for (j = 0; j < ib_idx; j++) {
		    strcpy((char*)total_index_buf[tib_idx].str, (char*)index_buf[j].str);
		    total_index_buf[tib_idx].loc = index_buf[j].loc;
		    tib_idx++;
		}
	    }
	} else {
	    for (j = 0; j < ib_idx; j++) {
		strcpy((char*)total_index_buf[tib_idx].str, (char*)index_buf[j].str);
		total_index_buf[tib_idx].loc = index_buf[j].loc;
		tib_idx++;
	    }
	}
    }
    if (tib_idx) {
	qsort(total_index_buf, tib_idx, sizeof(INDEX_ITEM), compare_index_str);
	strcpy((char*)temp_index, (char*)total_index_buf[0].str);
	temp_loc = total_index_buf[0].loc;
	for (i = 1; i < tib_idx; i++) {
	    if (strcmp((char*)temp_index, (char*)total_index_buf[i].str)) {
		strcpy((char*)index_words->IDX[index_words->nIndex].str, (char*)temp_index);
		index_words->IDX[index_words->nIndex].loc = temp_loc;
		strcpy((char*)temp_index, (char*)total_index_buf[i].str);
		temp_loc = total_index_buf[i].loc;
		index_words->nIndex++;
	    }
	}

	strcpy((char*)index_words->IDX[index_words->nIndex].str, (char*)temp_index);
	index_words->IDX[index_words->nIndex].loc = temp_loc;
	index_words->nIndex++;
	return 1;
    } else
	return 0;

}

int compare_index_str(const void *p1, const void *p2)
{
	INDEX_ITEM *idx1 = (INDEX_ITEM *)p1;
	INDEX_ITEM *idx2 = (INDEX_ITEM *)p2;
    return (strcmp((char*)idx1->str, (char*)idx2->str));
}

/* flag : 0 -> 표준 출력, 1 -> 파일로 출력 */
tVOID ReGenMAResult(DWORD flag, FILE *fd, tMORP_RESULT *sMorpResult, UWORD sMorpResult_Index)
{
    DWORD i, j, k;
    UBYTE han_str[VS_BUFLEN];
    WORD index = 0;
    H_CHAR one_han;
#ifdef GET_TAIL_INFO
    extern FILE *fd_tail;
    UBYTE tail_word[VS_BUFLEN], tag_list[VS_BUFLEN];
    UBYTE temp_buf[VS_BUFLEN];
    DWORD POS[VS_BUFLEN]; /* 1 : 부사, 20 : 관형사, 30 - 41 : 명사, 50 : 형용사, 52 : 동사, 36 : 수사 */
    DWORD POS_num = 0;
#endif

#ifdef GET_TAIL_INFO
    tail_word[0] = '\0';
    tag_list[0] = '\0';
#endif

    if (M_MORPRESULT_INDEX == 0) {
	if (sMorpResult_Index > 0) {
	    if (flag) 
		fprintf(fd, "\t");
	    else
		printf("     ");

	    for (j = 0; j < sMorpResult[0].nMorp; j++) {
		k = 0;
		index = 0;
		while (sMorpResult[0].MI[j].Morpheme[k] != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		    if (sMorpResult[0].MI[j].Morpheme[k] >= 0x8442 &&
			    sMorpResult[0].MI[j].Morpheme[k] <= 0xd3b7) {	/* 조합형 한글이면 */
			one_han.code = jo2wan[sMorpResult[0].MI[j].Morpheme[k]-0x8442][1];
			han_str[index++] = one_han.hl.high;
			han_str[index++] = one_han.hl.low;
		    } else {		/* 한글이 아닌 아스키 코드 이면 */
			one_han.code = sMorpResult[0].MI[j].Morpheme[k];
			han_str[index++] = one_han.hl.high;
		    }
						
		    k++;
		}
		han_str[index] = '\0';

		if (sMorpResult[0].MI[j].ninfo == 1) {
		    if (strlen(sMorpResult[0].MI[j].info) == 1) {
			if (flag == 0)
			    printf("%s(%d) ", han_str, sMorpResult[0].MI[j].info[0]);
			else
			    fprintf(fd, "%s(%d) ", han_str, sMorpResult[0].MI[j].info[0]);
		    } else {
			if (flag == 0)
			    printf("%s(%s) ", han_str, sMorpResult[0].MI[j].info);
			else
			    fprintf(fd, "%s(%s) ", han_str, sMorpResult[0].MI[j].info);
		    }
		} else {
		    if (flag == 0) {
			printf("%s(%d", han_str, sMorpResult[0].MI[j].info[0]);
			for (k = 1; k < sMorpResult[0].MI[j].ninfo; k++)
			    printf(" %d", sMorpResult[0].MI[j].info[k]);
			printf(") ");
		    } else {
			fprintf(fd, "%s(%d", han_str, sMorpResult[0].MI[j].info[0]);
			for (k = 1; k < sMorpResult[0].MI[j].ninfo; k++)
			    fprintf(fd, " %d", sMorpResult[0].MI[j].info[k]);
			fprintf(fd, ") ");
		    }
		}
	    }

	    if (flag == 0)
		printf("\n");
	}
    }

    for (i = 0; i < M_MORPRESULT_INDEX; i++) {
	if (flag) 
	    fprintf(fd, "\t");
	else
	    printf("     ");

	if (sMorpResult_Index > 0) {
#ifdef GET_TAIL_INFO
	    POS_num = 0;
	    POS[POS_num++] = 36;
#endif
	    for (j = 0; j < sMorpResult[0].nMorp; j++) {
		k = 0;
		index = 0;
		while (sMorpResult[0].MI[j].Morpheme[k] != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		    if (sMorpResult[0].MI[j].Morpheme[k] >= 0x8442 &&
			    sMorpResult[0].MI[j].Morpheme[k] <= 0xd3b7) {	/* 조합형 한글이면 */
			one_han.code = jo2wan[sMorpResult[0].MI[j].Morpheme[k]-0x8442][1];
			han_str[index++] = one_han.hl.high;
			han_str[index++] = one_han.hl.low;
		    } else {		/* 한글이 아닌 아스키 코드 이면 */
			one_han.code = sMorpResult[0].MI[j].Morpheme[k];
			han_str[index++] = one_han.hl.high;
		    }

		    k++;
		}
		han_str[index] = '\0';
		if (sMorpResult[0].MI[j].ninfo == 1) {
		    if (strlen(sMorpResult[0].MI[j].info) == 1) {
			if (flag == 0)
			    printf("%s(%d) ", han_str, sMorpResult[0].MI[j].info[0]);
			else
			    fprintf(fd, "%s(%d) ", han_str, sMorpResult[0].MI[j].info[0]);
		    } else {
			if (flag == 0)
			    printf("%s(%s) ", han_str, sMorpResult[0].MI[j].info);
			else
			    fprintf(fd, "%s(%s) ", han_str, sMorpResult[0].MI[j].info);
		    }
		} else {
		    if (flag == 0) {
			printf("%s(%d", han_str, sMorpResult[0].MI[j].info[0]);
			for (k = 1; k < sMorpResult[0].MI[j].ninfo; k++)
			    printf(" %d", sMorpResult[0].MI[j].info[k]);
			printf(") ");
		    } else {
			fprintf(fd, "%s(%d", han_str, sMorpResult[0].MI[j].info[0]);
			for (k = 1; k < sMorpResult[0].MI[j].ninfo; k++)
			    fprintf(fd, " %d", sMorpResult[0].MI[j].info[k]);
			fprintf(fd, ") ");
		    }
		}
	    }
	}

	for (j = 0; j < M_MORPRESULT_NMORP(i); j++) {
	    k = 0;
	    index = 0;
	    while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
			M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) {	/* 조합형 한글이면 */
		    one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)-0x8442][1];
		    han_str[index++] = one_han.hl.high;
		    han_str[index++] = one_han.hl.low;
		} else {		/* 한글이 아닌 아스키 코드 이면 */
		    one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k);
		    han_str[index++] = one_han.hl.high;
		}
					
		k++;
	    }
	    han_str[index] = '\0';

	    if (M_MORPRESULT_MI_NINFO(i, j) == 1) {
		if (strlen(M_MORPRESULT_MI_INFO(i, j)) == 1) {
#ifdef GET_TAIL_INFO
		    /* 실질형태소 부분 */
		    POS_num = 0;
		    POS[POS_num++] = M_MORPRESULT_MI_INFO_ITEM(i, j, 0);
		    if (1 <= POS[POS_num-1] && POS[POS_num-1] >= 5)
			POS[POS_num-1] = 1;
		    else if (20 <= POS[POS_num-1] && POS[POS_num-1] >= 22)
			POS[POS_num-1] = 20;
		    else if (POS[POS_num-1] == 50 || POS[POS_num-1] == 51 ||
			    POS[POS_num-1] == 54 || POS[POS_num-1] == 57 ||
			    POS[POS_num-1] == 58 || POS[POS_num-1] == 59 ||
			    POS[POS_num-1] == 60 || POS[POS_num-1] == 61 ||
			    POS[POS_num-1] == 63 || POS[POS_num-1] == 66 ||
			    POS[POS_num-1] == 68 || POS[POS_num-1] == 69 ||
			    POS[POS_num-1] == 71 || POS[POS_num-1] == 74 ||
			    POS[POS_num-1] == 76)
			POS[POS_num-1] = 50;
		    else if (30 <= POS[POS_num-1] && POS[POS_num-1] <= 41) /* 명사 */
			;
		    else  /* 동사 */
			POS[POS_num-1] = 52;
#endif
		    if (flag == 0)
			printf("%s(%d) ", han_str, M_MORPRESULT_MI_INFO_ITEM(i, j, 0));
		    else
			fprintf(fd, "%s(%d) ", han_str, M_MORPRESULT_MI_INFO_ITEM(i, j, 0));
		} else {
		    if (flag == 0)
			printf("%s(%s) ", han_str, M_MORPRESULT_MI_INFO(i, j));
		    else
			fprintf(fd, "%s(%s) ", han_str, M_MORPRESULT_MI_INFO(i, j));
#ifdef GET_TAIL_INFO
		    /* 형식형태소 부분 */
		    strcat(tail_word, han_str);
		    sprintf(temp_buf, "%s_%s", han_str, sMorpResult[0].MI[j].info);
		    if (tag_list[0] != '\0')
			strcat(tag_list, "-");
		    strcat(tag_list, temp_buf);
#endif
		}
	    } else {
#ifdef GET_TAIL_INFO
		/* 실질형태소 부분 */
		POS_num = 0;
		for (k = 0; k < M_MORPRESULT_MI_NINFO(i, j); k++) {
		    POS[POS_num++] = M_MORPRESULT_MI_INFO_ITEM(i, j, k);
		}
#endif
		if (flag == 0) {
		    printf("%s(%d", han_str, M_MORPRESULT_MI_INFO_ITEM(i, j, 0));
		    for (k = 1; k < M_MORPRESULT_MI_NINFO(i, j); k++)
			printf(" %d", M_MORPRESULT_MI_INFO_ITEM(i, j, k));
		    printf(") ");
		} else {
		    fprintf(fd, "%s(%d", han_str, M_MORPRESULT_MI_INFO_ITEM(i, j, 0));
		    for (k = 1; k < M_MORPRESULT_MI_NINFO(i, j); k++)
			fprintf(fd, " %d", M_MORPRESULT_MI_INFO_ITEM(i, j, k));
		    fprintf(fd, ") ");
		}
	    }
	}
	if (flag == 0)
	    printf("\n");
    }

#ifdef GET_TAIL_INFO
    if (tag_list[0] != '\0' && tail_word[0] != '\0') {
	for (k = 0; k < POS_num; k++)
	    fprintf(fd_tail, "%s\t%s\t%d\n", tag_list, tail_word, POS[k]);
    }
#endif

    if (flag != 0)
	fprintf(fd, "\n");
}

/*
 * ma_result에 형태소 분석 결과를 저장한다.
 */
tVOID FilterMAResult(ITF_MA_RESULT *ma_result, tMORP_RESULT *sMorpResult, UWORD sMorpResult_Index)
{
    DWORD i, j, k, l_idx;
    UBYTE han_str[VS_BUFLEN];
    BYTE info_str[VS_BUFLEN];
    WORD index = 0;
    H_CHAR one_han;

    if (M_MORPRESULT_INDEX == 0) {
	if (sMorpResult_Index > 0) {
	    for (i = 0; i < sMorpResult_Index; i++) {
		for (j = 0; j < sMorpResult[i].nMorp; j++) {
		    k = 0;
		    index = 0;
		    while (sMorpResult[i].MI[j].Morpheme[k] != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
			if (sMorpResult[i].MI[j].Morpheme[k] >= 0x8442 &&
				sMorpResult[i].MI[j].Morpheme[k] <= 0xd3b7) {	/* 조합형 한글이면 */
			    one_han.code = jo2wan[sMorpResult[i].MI[j].Morpheme[k]-0x8442][1];
			    han_str[index++] = one_han.hl.high;
			    han_str[index++] = one_han.hl.low;
			} else {		/* 한글이 아닌 아스키 코드 이면 */
			    one_han.code = sMorpResult[i].MI[j].Morpheme[k];
			    han_str[index++] = one_han.hl.high;
			}
						    
			k++;
		    }
		    han_str[index] = '\0';

		    if (sMorpResult[i].MI[j].ninfo == 1) {
			if (strlen(sMorpResult[i].MI[j].info) == 1) {
			    strcpy((char*)ma_result->IMR[i].MI[j].Morpheme, (char*)han_str);
			    Convert_NumInfo(sMorpResult[i].MI[j].info[0], info_str);
			    strcpy((char*)ma_result->IMR[i].MI[j].info, (char*)info_str);
			} else {
			    strcpy((char*)ma_result->IMR[i].MI[j].Morpheme, (char*)han_str);
			    Convert_StrInfo(sMorpResult[i].MI[j].info, info_str);
			    strcpy((char*)ma_result->IMR[i].MI[j].info, (char*)info_str);
			}
		    } else {
			strcpy((char*)ma_result->IMR[i].MI[j].Morpheme, (char*)han_str);
			Convert_NumInfo(sMorpResult[i].MI[j].info[0], info_str);
			strcpy((char*)ma_result->IMR[i].MI[j].info, (char*)info_str);
			for (k = 1; k < sMorpResult[i].MI[j].ninfo; k++) {
			    Convert_NumInfo(sMorpResult[i].MI[j].info[k], info_str);
			    strcat((char*)ma_result->IMR[i].MI[j].info, " ");
			    strcat((char*)ma_result->IMR[i].MI[j].info, (char*)info_str);
			}
		    }
		}
		ma_result->IMR[i].nMorp = j;
	    }
	    ma_result->MARes_num = sMorpResult_Index;
	}
	return;
    }

    ma_result->MARes_num = M_MORPRESULT_INDEX;

    for (i = 0; i < M_MORPRESULT_INDEX; i++) {
	l_idx = 0;
	if (sMorpResult_Index > 0) {
	    for (j = 0; j < sMorpResult[0].nMorp; j++) {
		k = 0;
		index = 0;
		while (sMorpResult[0].MI[j].Morpheme[k] != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		    if (sMorpResult[0].MI[j].Morpheme[k] >= 0x8442 &&
			    sMorpResult[0].MI[j].Morpheme[k] <= 0xd3b7) {	/* 조합형 한글이면 */
			one_han.code = jo2wan[sMorpResult[0].MI[j].Morpheme[k]-0x8442][1];
			han_str[index++] = one_han.hl.high;
			han_str[index++] = one_han.hl.low;
		    } else {		/* 한글이 아닌 아스키 코드 이면 */
			one_han.code = sMorpResult[0].MI[j].Morpheme[k];
			han_str[index++] = one_han.hl.high;
		    }

		    k++;
		}
		han_str[index] = '\0';

		if (sMorpResult[0].MI[j].ninfo == 1) {
		    if (strlen(sMorpResult[0].MI[j].info) == 1) {
			strcpy((char*)ma_result->IMR[i].MI[l_idx].Morpheme, (char*)han_str);
			Convert_NumInfo(sMorpResult[0].MI[j].info[0], info_str);
			strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
		    } else {
			strcpy((char*)ma_result->IMR[i].MI[l_idx].Morpheme, (char*)han_str);
			Convert_StrInfo(sMorpResult[0].MI[j].info, info_str);
			strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
		    }
		} else {
		    strcpy((char*)ma_result->IMR[i].MI[l_idx].Morpheme, (char*)han_str);
		    Convert_NumInfo(sMorpResult[0].MI[j].info[0], info_str);
		    strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
		    for (k = 1; k < sMorpResult[0].MI[j].ninfo; k++) {
			Convert_NumInfo(sMorpResult[0].MI[j].info[k], info_str);
			strcat(ma_result->IMR[i].MI[l_idx].info, " ");
			strcat(ma_result->IMR[i].MI[l_idx].info, info_str);
		    }
		}
		l_idx++;
	    }
	}
	for (j = 0; j < M_MORPRESULT_NMORP(i); j++) {
	    k = 0;
	    index = 0;
	    while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
			M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) {	/* 조합형 한글이면 */
		    one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)-0x8442][1];
		    han_str[index++] = one_han.hl.high;
		    han_str[index++] = one_han.hl.low;
		} else {		/* 한글이 아닌 아스키 코드 이면 */
		    one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k);
		    han_str[index++] = one_han.hl.high;
		}
					
		k++;
	    }
	    han_str[index] = '\0';
	    if (M_MORPRESULT_MI_NINFO(i, j) == 1) {
		
		if (strlen(M_MORPRESULT_MI_INFO(i, j)) == 1) {
		    strcpy((char*)ma_result->IMR[i].MI[l_idx].Morpheme, (char*)han_str);
		    Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, 0), info_str);
		    strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
		} else {
		    strcpy((char*)ma_result->IMR[i].MI[l_idx].Morpheme, (char*)han_str);
		    Convert_StrInfo(M_MORPRESULT_MI_INFO(i, j), info_str);
		    strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
		}
	    } else {
		strcpy((char*)ma_result->IMR[i].MI[l_idx].Morpheme, (char*)han_str);
		Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, 0), info_str);
		strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
		for (k = 1; k < M_MORPRESULT_MI_NINFO(i, j); k++) {
		    Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, k), info_str);
		    strcat(ma_result->IMR[i].MI[l_idx].info, " ");
		    strcat(ma_result->IMR[i].MI[l_idx].info, info_str);
		}
	    }
	    l_idx++;
	}
	ma_result->IMR[i].nMorp = l_idx;
    }

}

/*
 * 수사로 분석이 끝난 어절에 대해서...
 * 형태소 분석을 다시 한번 시도해서...
 * 나온 형태소 분석 결과를 결과저장 버퍼에 추가...
 * 이는 수사 형태소 분석이 완전하지 않으므로...
 * 일반적인 형태소 분석을 다시한번 시도하기 위해서이다.
 */
tVOID Add_MorpResult(ITF_MA_RESULT *ma_result)
{
    DWORD sIdx = ma_result->MARes_num;
    DWORD i, j, k, index;
    UBYTE han_str[VS_BUFLEN];
    BYTE info_str[VS_BUFLEN];
    H_CHAR one_han;

    for (i = 0; i < M_MORPRESULT_INDEX; i++) {
	for (j = 0; j < M_MORPRESULT_NMORP(i); j++) {
	    k = 0;
	    index = 0;
	    while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD)0) {	/* 조합형 --> 완성형 변환 */
		if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
			M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) {	/* 조합형 한글이면 */
		    one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)-0x8442][1];
		    han_str[index++] = one_han.hl.high;
		    han_str[index++] = one_han.hl.low;
		} else {		/* 한글이 아닌 아스키 코드 이면 */
		    one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k);
		    han_str[index++] = one_han.hl.high;
		}
					
		k++;
	    }
	    han_str[index] = '\0';

	    if (M_MORPRESULT_MI_NINFO(i, j) == 1) {
		if (strlen(M_MORPRESULT_MI_INFO(i, j)) == 1) {
		    strcpy((char*)ma_result->IMR[sIdx].MI[j].Morpheme, (char*)han_str);
		    Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, 0), info_str);
		    strcpy(ma_result->IMR[sIdx].MI[j].info, info_str);
		} else {
		    strcpy((char*)ma_result->IMR[sIdx].MI[j].Morpheme, (char*)han_str);
		    Convert_StrInfo(M_MORPRESULT_MI_INFO(i, j), info_str);
		    strcpy(ma_result->IMR[sIdx].MI[j].info, info_str);
		}
	    } else {
		strcpy((char*)ma_result->IMR[sIdx].MI[j].Morpheme, (char*)han_str);
		Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, 0), info_str);
		strcpy(ma_result->IMR[sIdx].MI[j].info, info_str);
		for (k = 1; k < M_MORPRESULT_MI_NINFO(i, j); k++) {
		    Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, k), info_str);
		    strcat(ma_result->IMR[sIdx].MI[j].info, " ");
		    strcat(ma_result->IMR[sIdx].MI[j].info, info_str);
		}
	    }
	}
	ma_result->IMR[sIdx].nMorp = j;
	sIdx++;
    }

    ma_result->MARes_num = sIdx;
}

tVOID Convert_NumInfo(unsigned short int info, char *info_str)
{
    switch (info) {
	case 1:
	case 5:
	    strcpy(info_str, "mag");
	    break;
	case 2:
	    strcpy(info_str, "mad");
	    break;
	case 3:
	case 4:
	    strcpy(info_str, "maj");
	    break;
	case 10:
	    strcpy(info_str, "ii");
	    break;
	case 20:
	case 22:
	    strcpy(info_str, "mma");
	    break;
	case 21:
	    strcpy(info_str, "mmd");
	    break;
	case 31:
	    strcpy(info_str, "nbu");
	    break;
	case 30:
	    strcpy(info_str, "nbn");
	    break;
	case 32:
	case 35:
	    strcpy(info_str, "ncn");
	    break;
	case 36:
	    strcpy(info_str, "nn");
	    break;
	case 33:
	    strcpy(info_str, "ncpa");
	    break;
	case 37:
	    strcpy(info_str, "npd");
	    break;
	case 34 :
	    strcpy(info_str, "ncps");
	    break;
	case 38:
	    strcpy(info_str, "npp");
	    break;
	case 39:
		strcpy(info_str,"nq");
		break;
	case 40:
		strcpy(info_str,"pn");
		break;
	case 41:
	    strcpy(info_str, "pnf");
	    break;
	case 50:
	case 54:
	case 57:
	case 58:
	case 60:
	case 61:
	case 63:
	case 66:
	case 68:
	case 69:
	case 74:
	case 76:
	    strcpy(info_str, "paa");
	    break;
	case 51:
	case 59:
	case 71:
	    strcpy(info_str, "pad");
	    break;
	case 52:
	case 53:
	case 55:
	case 56:
	case 62:
	case 64:
	case 65:
	case 67:
	case 70:
	case 72:
	case 73:
	case 75:
	    strcpy(info_str, "pvg");
	    break;
	case 90:
		strcpy(info_str,"90");
		break;
	case 91:
		strcpy(info_str,"91");
		break;
	case 92:
		strcpy(info_str,"92");
		break;
	case 93:
		strcpy(info_str,"93");
		break;
	case 94:
	    strcpy(info_str, "94");
	    break;	
	default:
	    strcpy(info_str, "unknown");
	    break;
    }
}

tVOID Convert_StrInfo(char *info, char *info_str)
{
    BYTE *ptr;

    if (!strcmp(info, "UNIT"))
	strcpy(info_str, "nbu");
    else if (!strcmp(info, "PRE_UNIT"))
	strcpy(info_str, "xsn");
    else if (!strcmp(info, "SUSA"))
	strcpy(info_str, "nn");
    else if (!strcmp(info, "BOJOSA"))
	strcpy(info_str, "jx");
    else if (!strcmp(info, "JUBMISA"))
	strcpy(info_str, "xsn");
/*
    else if (!strcmp(info, "JOSA"))
	strcpy(info_str, "j");
    else if (!strcmp(info, "EOMI"))
	strcpy(info_str, "e");
*/
    else if (!strcmp(info, "MJUNSUNG"))
	strcpy(info_str, "xsn");
    else if (!strcmp(info, "BOJOEOMI"))
	strcpy(info_str, "ecx");
    else if (!strcmp(info, "BOJOYONG"))
	strcpy(info_str, "px");
    else if (!strcmp(info, "PRE_EOMI"))
	strcpy(info_str, "ep");
    else if (!strcmp(info, "ISSDA"))
	strcpy(info_str, "xsm"); 
    else if (!strcmp(info, "EUBSDA"))
	strcpy(info_str, "xsm"); 
    else if (!strcmp(info, "DABDA"))
	strcpy(info_str, "xsm"); 
    else if (!strcmp(info, "GATDA"))
	strcpy(info_str, "xsm"); 
    else if (!strcmp(info, "SRUBDA"))
	strcpy(info_str, "xsm"); 
    else if (!strcmp(info, "ROBDA"))
	strcpy(info_str, "xsm"); 
    else if (!strcmp(info, "HADA"))
	strcpy(info_str, "xsm xsv"); 
    else if (!strcmp(info, "SIKIDA"))
	strcpy(info_str, "xsm xsv"); 
    else if (!strcmp(info, "DANGHADA"))
	strcpy(info_str, "xsm xsv"); 
    else if (!strcmp(info, "DOIDA"))
	strcpy(info_str, "xsm xsv"); 
    else if (!strcmp(info, "IDA"))
	strcpy(info_str, "jp"); 
    else if (!strcmp(info, "JUBMISA JOSA"))
	strcpy(info_str, "j jx");
	//미등록어 분석 모듈 결과 수정 후 품사 추가 
	else if(!strcmp(info,"nuk"))
	strcpy(info_str,"nuk");
	
	else if(!strcmp(info,"jp"))
	strcpy(info_str,"jp");
	else if(!strcmp(info,"jca"))
	strcpy(info_str,"jca");
	else if(!strcmp(info,"jcs"))
	strcpy(info_str,"jcs");
	else if(!strcmp(info,"jcm"))
    strcpy(info_str,"jcm");
	else if(!strcmp(info,"jxc"))
    strcpy(info_str,"jxc");
	else if(!strcmp(info,"jcv"))
    strcpy(info_str,"jcv");
	else if(!strcmp(info,"jco"))
    strcpy(info_str,"jco");
	else if(!strcmp(info,"jcj"))
    strcpy(info_str,"jcj");
	else if(!strcmp(info,"jct"))
    strcpy(info_str,"jct");
	else if(!strcmp(info,"jcc"))
    strcpy(info_str,"jcc");
	else if(!strcmp(info,"ecs"))
	strcpy(info_str,"ecs");
	else if(!strcmp(info,"ecc"))
    strcpy(info_str,"ecc");
	else if(!strcmp(info,"ef"))
    strcpy(info_str,"ef");
	else if(!strcmp(info,"etm"))
    strcpy(info_str,"etm");
	else if(!strcmp(info,"ecx"))
    strcpy(info_str,"ecx");
	else if(!strcmp(info,"ep"))
    strcpy(info_str,"ep");
	else if(!strcmp(info,"pvg"))
    strcpy(info_str,"pvg");
	else if(!strcmp(info,"paa"))
    strcpy(info_str,"paa");
	else if(!strcmp(info,"xsn"))
    strcpy(info_str,"xsn");
	else if(!strcmp(info,"xsm"))
    strcpy(info_str,"xsm");
	else if(!strcmp(info,"xsv"))
    strcpy(info_str,"xsv");

	/////////////////////////

	else {
	ptr = info;

	if (*ptr == 'J') {
		/*
		printf("Josa:%s",ptr);
		*/
	    info_str[0] = '\0';
	    if (strstr(ptr, "JUBMISA ")) {
		strcat(info_str, "xsn ");
		ptr += strlen("JUBMISA ");
	    }
		if (strstr(ptr, "JN")) {
		strcat(info_str, "jn ");
		ptr += strlen("JN ");
	    }
		if(*ptr=='J')
			ptr++;		
	    while (*ptr != '\0') {
		switch (*ptr) {
		    case '1':
			strcat(info_str, "jcs ");
			break;
		    case '2':
			strcat(info_str, "jca ");
			break;
		    case '3':
			strcat(info_str, "jcm ");
			break;
		    case '4':
			strcat(info_str, "jcv ");
			break;
		    case '5':
			strcat(info_str, "jcj jct ");
			break;
		    case '6':
			strcat(info_str, "jxc ");
			break;
		    case '7':
			strcat(info_str, "jco ");
			break;
		    case '8':
			strcat(info_str, "jcc ");
			break;
		    default :
			strcat(info_str, "unknown ");
			break;
		}
		ptr++;
	    }
	    info_str[strlen(info_str)-1] = '\0';

	    return;
	} else if (*ptr == 'E') {
		/*
	    printf("Josa:%s\n",ptr);
		*/
		ptr++;
	    info_str[0] = '\0';
	
	    while (*ptr != '\0') {
		switch (*ptr) {
		    case '1':
			strcat(info_str, "ecs ");
			break;
		    case '2':
			strcat(info_str, "ecc ");
			break;
		    case '3':
			strcat(info_str, "ef ");
			break;
		    case '4':
			strcat(info_str, "ecs ");
			break;
		    case '5':
			strcat(info_str, "etm ");
			break;
		    case '6':
			strcat(info_str, "xsn ");
			break;
		    default :
			strcat(info_str, "unknown ");
			break;
		}
		ptr++;
	    }
	    info_str[strlen(info_str)-1] = '\0';

	    return;
	}

	strcpy(info_str, "unknown");
    }
}
