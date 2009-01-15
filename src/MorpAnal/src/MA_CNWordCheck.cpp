/*
 *      Copyright (c) 2001
 *      Choi Sung Pil(SPASIS Systems Co. LTD), All right reserved.
 *
 *      #(MA_CNWordCheck.c)#  SPASIS System,     2001.02.12
 *
 *      #(Action)#
 *              - ��м� ���ո�� ���� Ž���� ���� ���ո�� �и� �� 
 *                ���ξ� ���� ���
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Global.h>
#include <MA_GMacro.h>
#include <MA_Func.h>
#include <MADIC_Type.h>
#include <MA_Interface.h>

#ifdef COMP_NOUN_DIC_CHECK
#define MAX_DUP		10
/*
 * 1 --> �м� ����
 * 0 --> �м� ����
 */

DWORD CheckCompNounWord(HANGUL *hword, UWORD hword_len, UWORD h_idx, tCNMORP_RESULT *CNMorpRes, UWORD *CNMorpRes_Index)
{
    CNDIC_RESULT CN_Result[DIC_RESULT_NUM];
    UWORD CR_num;
    DWORD ret_val;
    UBYTE CN_Content[L_BUFLEN]; /* ���ո�� �м� ���� */
    /* ���ո�� ��м� �������� ���� ������ ���ؼ� ���� �ٸ� �������� �м� ����� ���� �� �ִ�. */
    //UBYTE CN_ItemContent[MAX_DUP][S_BUFLEN];
	//UBYTE tmpStr[VS_BUFLEN];
    UWORD DupCnt = 0;
    UWORD MR_num;
    UBYTE *pCont;
    UBYTE ItemStr[S_BUFLEN];
    UWORD idx, i, j;
    UWORD PostWordStartPos, PostWordLen;
   // by mini 2006.02.23
   	DWORD merge_flag=0;
	UBYTE merge_str[VS_BUFLEN];
		
	extern DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str);

    *CNMorpRes_Index = 0;
    MR_num = 0;

	if (hword_len < 4)
		return 0;

    /* ���ո�� �м����� Ž�� */
    ret_val = SearchCNDic(hword, hword_len, h_idx, CN_Result, &CR_num);
    if (ret_val == 0)
	return 0;

    /* ���� �������� �˻��Ǵ� ���꽺Ʈ���� ���ؼ��� �м� */
    /* ��м� ������ ������ */
    GetCNContent(CN_Result[CR_num-1].InfoStart, CN_Result[CR_num-1].InfoLen, CN_Content);

    PostWordStartPos = CN_Result[CR_num-1].len;
    PostWordLen = hword_len - CN_Result[CR_num-1].len;

    /*
     * ��м� ������ ���ո�� ���¼Һм� ��� ����ü�� ����
     */
    pCont = CN_Content;
    idx = 0;
    CNMorpRes[MR_num].nMorp = 0;
    while ( *pCont != '\0' ) {
	if (*pCont & 0x80) {
	    ItemStr[idx] = *pCont;
	    idx++; pCont++;
	    ItemStr[idx] = *pCont;
	    idx++; pCont++;

	    continue;
	}

	if (*pCont == '_') {
	    ItemStr[idx] = '\0';
	    strcpy((char*)CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].Morpheme, (char*)ItemStr);
	    idx = 0;
	    pCont++;

	    continue;
	}

	if (*pCont == ' ' || *pCont == '|') {
	    CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].info = ItemStr[0];
	    CNMorpRes[MR_num].nMorp++;
	    if (*pCont == '|') {
		MR_num++;
		CNMorpRes[MR_num].nMorp = 0;
	    }
	    idx = 0;
	    pCont++;

	    continue;
	}

	ItemStr[idx] = *pCont;
	if((CNMorpRes[MR_num].nMorp>0) && (ItemStr[0] == 57)) {//NN=78 SN=57 ex)��ǰ(NN)+����(NN)+��(SN)
		merge_flag++;					
	}
		
	idx++; pCont++;
    }
    CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].info = ItemStr[0];
    CNMorpRes[MR_num].nMorp++;

    MR_num++;
 	if(merge_flag>0){
		for (i = 0; i < MR_num; i++) {
			CNMorpRes[MR_num].nMorp=0;
			for(j = 0; j < CNMorpRes[i].nMorp; j++){
				if(CNMorpRes[i].MI[j+1].info == 57){
					sprintf((char*)merge_str,"%s%s", (char*)CNMorpRes[i].MI[j].Morpheme, (char*)CNMorpRes[i].MI[j+1].Morpheme);
					strcpy((char*)CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].Morpheme, (char*)merge_str);
					//ǰ��ο� A:90 B:91 C:92 D:93 E:94
                    if(CNMorpRes[i].MI[j].info=='A'||CNMorpRes[i].MI[j].info=='B'||CNMorpRes[i].MI[j].info=='C'||CNMorpRes[i].MI[j].info=='D'||CNMorpRes[i].MI[j].info=='E')
                        CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].info = 'N';
                    else
                        CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].info = CNMorpRes[i].MI[j].info;		
				    CNMorpRes[MR_num].nMorp++;
					j=j+2;
					merge_flag--;
					while(j<CNMorpRes[i].nMorp){
						strcpy((char*)CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].Morpheme, (char*)CNMorpRes[i].MI[j].Morpheme);
						CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].info = CNMorpRes[i].MI[j].info;
						CNMorpRes[MR_num].nMorp++;
						j++;
					}
					//memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
				}
				else{
					strcpy((char*)CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].Morpheme, (char*)CNMorpRes[i].MI[j].Morpheme);
					CNMorpRes[MR_num].MI[CNMorpRes[MR_num].nMorp].info = CNMorpRes[i].MI[j].info;
				    CNMorpRes[MR_num].nMorp++;
				}
				
			}
			MR_num++;
			if(merge_flag==0) 
				break;
		}
		
	}	

	
	
    /* Full Match... */
    if (CN_Result[CR_num-1].len == hword_len) {
	*CNMorpRes_Index = MR_num;
	M_MORPRESULT_INDEX = 0;
	return 1;
    }
	//2006.03.10 
	//Ȳ�켮������ �м� ��� ��� '��/nbn ��/xsn jn' �м� ��� �߻��Ͽ�
	//'��/nbn' �м��� �����ϰ� jn�� nbn���� �����Ͽ� ��.
	//
    /* �м��Ǵ� �Ĺ̾����� ��� ��ġ�ϹǷ� �ѹ��� ���¼� �м��� �ϸ� �ȴ�. */
    /* ���̻�� ������ ������ ���ؼ� ���̻� ó���� ������... �̰͵�...     */
    ret_val = TopicMorpAnal(&hword[PostWordStartPos], PostWordLen, COMPNOUN_POSTNOUN_P, hword[PostWordStartPos-1].j_han.jong);
    if (ret_val) {
	//	/* ���̻簡 �ٴ� ��쿡 �� ���̻簡 ���̸������ �Ǵ�... */
	//	/* �ڼ��� ������ MA_Jubmi.h��... */
	//	if (!strncmp(MorpResult[0].MI[0].info, "JUBMISA JN", 10)) {
	//		/* ���̸���̸� �̸� ���¼� �м� ����� �߰� */
	//		ConvertJo2Wan(&hword[PostWordStartPos], 1, tmpStr);
	//		for (i = 0; i < MR_num; i++) {
	//			strcpy(CNMorpRes[i].MI[CNMorpRes[i].nMorp].Morpheme, tmpStr);
	//			CNMorpRes[i].MI[CNMorpRes[i].nMorp].info = '9';
	//			CNMorpRes[i].nMorp++;
	//		}
	//	}

	*CNMorpRes_Index = MR_num;

	return 1;
    } else
	return 0;
}

/*
 * ���ξ� ���� ��ƾ...
 * �� �Լ��� ���ո�� �м� ���� �� ȣ��ȴ�.
 * Return Value : ���ξ� ����
 */
DWORD FilterCNIndexWord(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index, INDEX_WORD *IDX_words)
{
    DWORD i, j;
    DWORD i_cnt = 0;
    DWORD s_ind, e_ind;
    UWORD sPos;

    IDX_words->nIndex = 0;
    for (i = 0; i < CNMorpRes_Index; i++) {
	sPos = 0;
	for (j = 0; j < CNMorpRes[i].nMorp; j++) {
	    switch (CNMorpRes[i].MI[j].info) {
		case 'N':
		case '3':
		    /* �Ϲݸ��, ������� */
		    /* 1��¥�� ��縦 ���ξ�� ��Ͻ��ѵ� �ǳ�? */
		    strcpy((char*)IDX_words->IDX[i_cnt].str, (char*)CNMorpRes[i].MI[j].Morpheme);
		    IDX_words->IDX[i_cnt].loc = sPos;
		    i_cnt++;
		    break;

		case '1':
		case '2':
		    /* ������ ��翡 ���� ó���� �ϴ� ���� */
		    break;

		case '4':
		    /* ������� */
		    /* �� ���¼Ұ� �����̸�, �ΰ��� ���ļ� ���ξ�� ���� */
		    if (j > 0 && CNMorpRes[i].MI[j-1].info == '5') {
			sprintf((char*)IDX_words->IDX[i_cnt].str, "%s%s", (char*)CNMorpRes[i].MI[j-1].Morpheme, (char*)CNMorpRes[i].MI[j].Morpheme);
			IDX_words->IDX[i_cnt].loc = sPos- strlen((char*)CNMorpRes[i].MI[j-1].Morpheme);
			i_cnt++;
		    }
		    break;

		case '5':
		    /* ���� */
		    /* ����¥�� ����� ���ξ �� �� ����.(����) */
		    if (strlen((char*)CNMorpRes[i].MI[j].Morpheme) > 2) {
			strcpy((char*)IDX_words->IDX[i_cnt].str, (char*)CNMorpRes[i].MI[j].Morpheme);
			IDX_words->IDX[i_cnt].loc = sPos;
			i_cnt++;
		    }
		    break;

		case '6':
		    /* ���� ���̻� */
		    break;

		case '7':
		    /* ���λ� */
		    /* �ڿ� ���� ���� �����Ͽ� ���ξ ���� */
		    if (j < CNMorpRes[i].nMorp - 1 && 
			   (CNMorpRes[i].MI[j+1].info == 'N' || CNMorpRes[i].MI[j+1].info == '3')) {
			sprintf((char*)IDX_words->IDX[i_cnt].str, "%s%s", (char*)CNMorpRes[i].MI[j].Morpheme, (char*)CNMorpRes[i].MI[j+1].Morpheme);
			IDX_words->IDX[i_cnt].loc = sPos;
			i_cnt++;
		    }
			break;

		case '8':
		    /* ���̻� */
		    /* �� ������ ���� ǥ���� �м� ������ ��Ȯ���� �����Ƿ�, �ϴ� SKIP�Ѵ�. */
		    break;

		case '9':
		    /* ���̸�� */
		    /* �� ���� �����Ͽ� �ϳ��� ���ξ� ���� */
		    if (j > 0 && CNMorpRes[i].MI[j-1].info == 'N' || CNMorpRes[i].MI[j-1].info == '3') {
			sprintf((char*)IDX_words->IDX[i_cnt].str, "%s%s", (char*)CNMorpRes[i].MI[j-1].Morpheme, (char*)CNMorpRes[i].MI[j].Morpheme);
			IDX_words->IDX[i_cnt].loc = sPos - strlen((char*)CNMorpRes[i].MI[j-1].Morpheme);
			i_cnt++;
		    }
		    break;
		default :
		    break;
	    }

	    sPos += strlen((char*)CNMorpRes[i].MI[j].Morpheme);
	}

	/* ��Ҹ�縦 �ϳ��� ���ļ� ���� */
	/* ���ո�� ������ ���ξ ���Ե� �� �ִ� ǰ�� : ������, �������, ������, ���λ�, ���̸�� */
	s_ind = 0;
	sPos = 0;
	while (s_ind < CNMorpRes[i].nMorp) {
	    if (CNMorpRes[i].MI[s_ind].info == 'N'
		    || CNMorpRes[i].MI[s_ind].info == '3'
		    || CNMorpRes[i].MI[s_ind].info == '5'
		    || CNMorpRes[i].MI[s_ind].info == '7'
		    || CNMorpRes[i].MI[s_ind].info == '9')
		break;
	    s_ind++;
	    sPos = strlen((char*)CNMorpRes[i].MI[s_ind].Morpheme);
	}

	e_ind = CNMorpRes[i].nMorp - 1;
	while (e_ind >= 0) {
	    if (CNMorpRes[i].MI[e_ind].info == 'N'
		    || CNMorpRes[i].MI[e_ind].info == '3'
		    || CNMorpRes[i].MI[e_ind].info == '5'
		    || CNMorpRes[i].MI[e_ind].info == '7'
		    || CNMorpRes[i].MI[e_ind].info == '9')
		break;
	    e_ind--;
	}

	if (s_ind < e_ind) {
	    IDX_words->IDX[i_cnt].str[0] = '\0';
	    for (j = s_ind; j <= e_ind; j++)
		strcat((char*)IDX_words->IDX[i_cnt].str, (char*)CNMorpRes[i].MI[j].Morpheme);
	    IDX_words->IDX[i_cnt].loc = sPos;

	    /* �ߺ� �˻� */
	    for (j = 0; j < i_cnt; j++)
		if (!strcmp((char*)IDX_words->IDX[j].str, (char*)IDX_words->IDX[i_cnt].str))
		    break;

	    if (j == i_cnt)
		i_cnt++;
	}
    }

    IDX_words->nIndex = i_cnt;
    if (i_cnt > 0)
	return 1;

    return 0;
}

/*
 * ���¼� �м� ����� ���...
 * �� �Լ��� ���ո�� �м� ���� �� ȣ��ȴ�.
 * outFlag : 0 --> ǥ�����,
 *           1 --> �������
 */
DWORD CNOutputMAResult(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index, DWORD outFlag, FILE *fd)
{
    DWORD i, j, k, l, m, index;
    BYTE DicInfo[VS_BUFLEN];
    DWORD DicInfoValue;
    UBYTE han_str[VS_BUFLEN];
    H_CHAR one_han;
    extern UWORD jo2wan[][3];

    if (M_MORPRESULT_INDEX == 0) {
	for (i = 0; i < CNMorpRes_Index; i++) {
	    for (j = 0; j < CNMorpRes[i].nMorp; j++) {
		DicInfoValue = ConvertCNInfoToDicInfo(CNMorpRes[i].MI[j].info, DicInfo);
		if (outFlag)
		    fprintf(fd, "%s(%s) ", CNMorpRes[i].MI[j].Morpheme, DicInfo);
		else
		    printf("%s(%s) ", CNMorpRes[i].MI[j].Morpheme, DicInfo);
	    }
	}

	if (outFlag)
	    fprintf(fd, "\n");
	else
	    printf("\n");

	return 1;
    }

    for (i = 0; i < CNMorpRes_Index; i++) {
	for (k = 0; k < M_MORPRESULT_INDEX; k++) {
	    for (j = 0; j < CNMorpRes[i].nMorp; j++) {
		DicInfoValue = ConvertCNInfoToDicInfo(CNMorpRes[i].MI[j].info, DicInfo);
		if (outFlag)
		    fprintf(fd, "%s(%s) ", CNMorpRes[i].MI[j].Morpheme, DicInfo);
		else
		    printf("%s(%s) ", CNMorpRes[i].MI[j].Morpheme, DicInfo);
	    }

	    for (l = 0; l < M_MORPRESULT_NMORP(k); l++) {
		m = 0;
		index = 0;
		while (M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m) != (UWORD)0) {   /* ������ --> �ϼ��� ��ȯ */
		    if (M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m) >= 0x8442 &&
			M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m) <= 0xd3b7) {    /* ������ �ѱ��̸� */
			one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m)-0x8442][1];
			han_str[index++] = one_han.hl.high;
			han_str[index++] = one_han.hl.low;
		    } else {                /* �ѱ��� �ƴ� �ƽ�Ű �ڵ� �̸� */
			one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m);
			han_str[index++] = one_han.hl.high;
		    }

		    m++;
		}
		han_str[index] = '\0';

		if (M_MORPRESULT_MI_NINFO(k, l) == 1) {
		    if (strlen(M_MORPRESULT_MI_INFO(k, l)) == 1) {
			if (outFlag == 0)
			    printf("%s(%d) ", han_str, M_MORPRESULT_MI_INFO_ITEM(k, l, 0));
			else
			    fprintf(fd, "%s(%d) ", han_str, M_MORPRESULT_MI_INFO_ITEM(k, l, 0));
		    } else {
			if (outFlag == 0)
			    printf("%s(%s) ", han_str, M_MORPRESULT_MI_INFO(k, l));
			else
			    fprintf(fd, "%s(%s) ", han_str, M_MORPRESULT_MI_INFO(k, l));
		    }
		} else {
		    if (outFlag == 0) {
			printf("%s(%d", han_str, M_MORPRESULT_MI_INFO_ITEM(k, l, 0));
			for (m = 1; m < M_MORPRESULT_MI_NINFO(k, l); m++)
			    printf(" %d", M_MORPRESULT_MI_INFO_ITEM(k, l, m));
			printf(") ");
		    } else {
			fprintf(fd, "%s(%d", han_str, M_MORPRESULT_MI_INFO_ITEM(k, l, 0));
			for (m = 1; m < M_MORPRESULT_MI_NINFO(k, l); m++)
			    fprintf(fd, " %d", M_MORPRESULT_MI_INFO_ITEM(k, l, m));
			fprintf(fd, ") ");
		    }
		}
	    }
	}
    }

    if (outFlag)
	fprintf(fd, "\n");
    else
	printf("\n");

    return 1;
}

#ifdef NEVER_DEFINED
/*
 * ���ո�� �м� ����� ���� ���¼� �м� ���� ���ۿ� �����Ѵ�.
 * ����� �ϼ������� �����Ǿ� �����Ƿ� �̸� ���������� ��ȯ�ϴ� ������ �̷������ �Ѵ�.
 * ������ ��м� ������ �м� ����κ��� �ϼ������� ������ ����Ǿ� �����Ƿ�,
 * MorpResult���� ���������� ���¼Һм� ����� ���� ó���� �ϱ� ���ؼ��� �� �۾��� �ʿ��ϴ�.
 *
 * --> MA_MainIDXProc.c�� �Ű�����...
 */
DWORD CopyCNMAResultToMorpResult(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index)
{
	DWORD i, j, k;
	HANGUL jh_han[VS_BUFLEN];
	DWORD jh_han_len;
	DWORD mr_idx, mp_idx;
    DWORD DicInfoValue;
    BYTE DicInfo[VS_BUFLEN];

	MorpResult_Index = mr_idx = 0; /* �ʱ�ȭ... */
	for (i = 0; i < CNMorpRes_Index; i++) {
		mp_idx = 0;
		for (j = 0; j < CNMorpRes[i].nMorp; j++) {
			/* �ϼ��� --> ������ */
			jh_han_len = Wan2Jo(CNMorpRes[i].MI[j].Morpheme, jh_han);
			if (jh_han_len == 0) /* ��ȯ ���� --> ���� */
				return 0;

			/* MorpResult�� ���¼� ���� */
			for (k = 0; k < jh_han_len; k++)
				MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = jh_han[k].j_code;
			MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = 0;

			/* ���� ���� ���� */
			DicInfoValue = ConvertCNInfoToNewDicInfo(CNMorpRes[i].MI[j].info, DicInfo);
			MorpResult[mr_idx].MI[mp_idx].ninfo = 1;
			MorpResult[mr_idx].MI[mp_idx].info[0] = DicInfoValue;

			mp_idx++;
		}
		MorpResult[mr_idx].nMorp = mp_idx;
		mr_idx++;
	}
	MorpResult_Index = mr_idx;

	return 1;
}
#endif

DWORD CNFilterMAResult(ITF_MA_RESULT *ma_result, tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index)
{
    DWORD i, j, k, l, m, index, MR_idx1, MR_idx2;
    BYTE DicInfo[VS_BUFLEN];
    DWORD DicInfoValue;
    char/*UBYTE*/ han_str[VS_BUFLEN];
    H_CHAR one_han;
    extern UWORD jo2wan[][3];

    if (M_MORPRESULT_INDEX == 0) {
	for (i = 0; i < CNMorpRes_Index; i++) {
	    for (j = 0; j < CNMorpRes[i].nMorp; j++) {
		DicInfoValue = ConvertCNInfoToNewDicInfo(CNMorpRes[i].MI[j].info, DicInfo);
		strcpy((char*)ma_result->IMR[i].MI[j].Morpheme, (char*)CNMorpRes[i].MI[j].Morpheme);
		strcpy((char*)ma_result->IMR[i].MI[j].info, (char*)DicInfo);
	    }
	    ma_result->IMR[i].nMorp = CNMorpRes[i].nMorp;
	}
	ma_result->MARes_num = CNMorpRes_Index;

	return 1;
    }

    MR_idx1 = MR_idx2 = 0;
    ma_result->MARes_num = M_MORPRESULT_INDEX * CNMorpRes_Index;

    for (i = 0; i < CNMorpRes_Index; i++) {
	for (k = 0; k < M_MORPRESULT_INDEX; k++) {
	    for (j = 0; j < CNMorpRes[i].nMorp; j++) {
		DicInfoValue = ConvertCNInfoToNewDicInfo(CNMorpRes[i].MI[j].info, DicInfo);
		strcpy((char*)ma_result->IMR[MR_idx1].MI[MR_idx2].Morpheme, (char*)CNMorpRes[i].MI[j].Morpheme);
		strcpy((char*)ma_result->IMR[MR_idx1].MI[MR_idx2].info, (char*)DicInfo);
		MR_idx2++;
	    }

	    for (l = 0; l < M_MORPRESULT_NMORP(k); l++) {
		m = 0;
		index = 0;
		while (M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m) != (UWORD)0) {   /* ������ --> �ϼ��� ��ȯ */
		    if (M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m) >= 0x8442 &&
			M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m) <= 0xd3b7) {    /* ������ �ѱ��̸� */
			one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m)-0x8442][1];
			han_str[index++] = one_han.hl.high;
			han_str[index++] = one_han.hl.low;
		    } else {                /* �ѱ��� �ƴ� �ƽ�Ű �ڵ� �̸� */
			one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(k, l, m);
			han_str[index++] = one_han.hl.high;
		    }

		    m++;
		}
		han_str[index] = '\0';

		if (M_MORPRESULT_MI_NINFO(k, l) == 1) {
		    if (strlen(M_MORPRESULT_MI_INFO(k, l)) == 1) {
			strcpy((char*)ma_result->IMR[MR_idx1].MI[MR_idx2].Morpheme, (char*)han_str);
			Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(k, l, 0), DicInfo);
			strcpy(ma_result->IMR[MR_idx1].MI[MR_idx2].info, DicInfo);
		    } else {
			strcpy((char*)ma_result->IMR[MR_idx1].MI[MR_idx2].Morpheme, (char*)han_str);
			Convert_StrInfo(M_MORPRESULT_MI_INFO(k, l), DicInfo);
			strcpy(ma_result->IMR[MR_idx1].MI[MR_idx2].info, DicInfo);
		    }
		} else {
		    strcpy((char*)ma_result->IMR[MR_idx1].MI[MR_idx2].Morpheme, (char*)han_str);
		    Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(k, l, 0), DicInfo);
		    strcpy(ma_result->IMR[MR_idx1].MI[MR_idx2].info, DicInfo);
		    for (m = 1; m < M_MORPRESULT_MI_NINFO(k, l); m++) {
			Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(k, l, m), DicInfo);
			strcat(ma_result->IMR[MR_idx1].MI[MR_idx2].info, " ");
			strcat(ma_result->IMR[MR_idx1].MI[MR_idx2].info, DicInfo);
		    }
		}
		MR_idx2++;
	    }

	    ma_result->IMR[MR_idx1].nMorp = MR_idx2;
	    MR_idx2 = 0;
	    MR_idx1++;
	}
    }

    return 1;
}

/*
 * ���ո�� �м���� ���ο��� ����ϴ� ������ ���� ���������� ��ȯ.
 * �ΰ��� ����� �ִ�.
 * ���� �����δ� Integer Value�� ���ϵǰų�...
 * DicInfo���� ���ڿ� ���������� ���ϵȴ�.
 */
DWORD ConvertCNInfoToDicInfo(BYTE CNInfo, BYTE *DicInfo)
{
    switch (CNInfo) {
	case 'N' : /* NN : �Ϲݸ�� */
	    strcpy(DicInfo, "CNoun");
	    return 32;
	case '1' : /* NM : ������ ��� */
	case '2' : /* NP : ������ ���(����̸�, �����̸�) */
	    strcpy(DicInfo, "20");
	    return 20;
	case '3' : /* NR : ������� */
	    strcpy(DicInfo, "39");
	    return 39;
	case '4' : /* NT : ������� */
	    strcpy(DicInfo, "31");
	    return 31;
	case '5' : /* NU : ���� */
	    strcpy(DicInfo, "SUSA");
	    return 36;
	case '6' : /* NX : ���̻� */
	case '8' : /* SF : ���̻� */
	    /* ���̻� ������ 23 �̴� */
	    strcpy(DicInfo, "CJUBMI");
	    return 23;
	case '7' : /* PF : ���λ� */
	    /* ���λ� ������ 24 �̴� */
	    strcpy(DicInfo, "CJUBDU");
	    return 24;
	case '9' : /* SN : ���̸�� */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "CJUBMI_NOUN");
	    return 25;

	default :
	    return 0;
    }
}

DWORD ConvertCNInfoToNewDicInfo(BYTE CNInfo, BYTE *DicInfo)
{
    switch (CNInfo) {
	case 'N' : /* NN : �Ϲݸ�� */
	    strcpy(DicInfo, "ncn");
	    return 32;
	case '1' : /* NM : ������ ��� */
	case '2' : /* NP : ������ ���(����̸�, �����̸�) */
	    strcpy(DicInfo, "mma");
	    return 20;
	case '3' : /* NR : ������� */
	    strcpy(DicInfo, "nq");
	    return 39;
	case '4' : /* NT : ������� */
	    strcpy(DicInfo, "nbu");
	    return 31;
	case '5' : /* NU : ���� */
	    strcpy(DicInfo, "nn");
	    return 36;
	case '6' : /* NX : ���̻� */
	case '8' : /* SF : ���̻� */
	    /* ���̻� ������ 23 �̴� */
	    strcpy(DicInfo, "xsn");
	    return 23;
	case '7' : /* PF : ���λ� */
	    /* ���λ� ������ 24 �̴� */
	    strcpy(DicInfo, "xp");
	    return 24;
	case '9' : /* SN : ���̸�� */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "jn");
	    return 25;
	case 'A' : /* 90: ����_��� */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "90");
	    return 90;
	case 'B' : /* 91 : ���_���� */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "91");
	    return 91;

	case 'C' : /* 92 : 3������� */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "92");
	    return 92;
	case 'D' : /* 93 : 90+91 */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "93");
	    return 93;
	case 'E' : /* 94 : ����� */
	    /* ���̸�� ������ 25 �̴� */
	    strcpy(DicInfo, "94");
	
	default :
	    return 0;
    }
}

#endif
