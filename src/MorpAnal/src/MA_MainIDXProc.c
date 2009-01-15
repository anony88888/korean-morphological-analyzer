/*
 * Copyright (c) 2000
 * Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 * #(MADevMain.c)#  SPASIS System,     2000.04.14
 *
 * #(Action)#
 * 	-- KRISTAL용 색인어 추출을 위한 주 모듈(형태소 분석 모듈과 분리하여 구성한다.)
 * 	-- 토큰 분리기를 색인기 외부로 빼고 한 단어에 대한 형태소 분석만을 처리하게끔 한다.
 * 	-- 문제는 수사와 같은 하나의 토큰으로 분리가 되어도 두개 이상의 단어로 인식되어야 하는 단어들...
 * 	-- 이것을 총체적으로 다시 처리한다.
 * 	-- 조합형 입력, 조합형 출력
 * 	-- KAnalysisWord함수 호출 전까지의 모든 모듈을 이곳에서 새로 구성한다.
 * 	-- KRISTAL을 위해서 특화시킨 모듈들이다.
 */
//최종수정 2007/04/17
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Global.h>
#include <MA_GMacro.h>
#include <MA_Func.h>
#include <MADIC_Func.h>
#include <MADIC_Type.h>
#include <MA_Interface.h>

#define MAX_INPUT_WORD_LEN		40

/* 수사 형태소 분석 결과 저장 버퍼 */
static tMORP_RESULT SusaMorpResult[MAX_MORP_LIST];
static UWORD SusaMorpResult_Index = 0;
static eIDX_RESULT curloc_eIDX[50];


DWORD GetIndexFromOneWord(JO_CHAR *han_word, int hword_len, JO_INDEX_WORD *idx_words, int mode);
DWORD MorpAnal_J(JO_CHAR *han_word, DWORD hword_len);
DWORD CopyCNMAResultToMorpResult(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index);
DWORD CopyITFMAResultToMorpResult(ITF_MA_RESULT ma_res);
DWORD CompJStr(JO_CHAR *s1, DWORD s1_len, JO_CHAR *s2, DWORD s2_len);
DWORD CheckJohabStr(JO_CHAR *han_word, DWORD hword_len);

/*
 * GetIndexFromOneWord -- 한 단어에서 색인어 추출(조합형 입력)
 * Input 
 * 		- 조합형 한글 및 기타 코드로 구성된 분리된 토큰 (han_word) -- 한자는 입력 불가
 * 		- 한 단어에 대한 색인 결과 (idx_words)
 * 		- mode = 0 : 한글, mode = 1 : 영어 (mode)
 * Output
 * 		- 조합형으로 이뤄진 색인결과
 */
DWORD GetIndexFromOneWord(JO_CHAR *han_word, int hword_len, JO_INDEX_WORD *idx_words, int mode)
{
	DWORD ret_val;

	SusaMorpResult_Index = 0;
	if (hword_len > MAX_INPUT_WORD_LEN)
		return 0;

	memcpy(idx_words->org_str, han_word, sizeof(JO_CHAR) * hword_len);
	idx_words->org_str_len = hword_len;

	/* 조합형 검사 */
	ret_val = CheckJohabStr(han_word, hword_len);
//	ret_val=1;
//		printf("CheckJohabStr:ret_val=%d\n",ret_val);
	if (ret_val == 0)
		return 0;
	//printf("[debug]MorpAnal_J 호출전\n");
	ret_val = MorpAnal_J(han_word, hword_len);
	//printf("[debug]MorpAnal_J 호출후\n");
		 
	if (ret_val)
		FilterJOIndexWord(idx_words);

	return ret_val;
}

DWORD CheckJohabStr(JO_CHAR *han_word, DWORD hword_len)
{
	DWORD i;//, h_idx;
	//extern UWORD jo2wan[][3];

	for (i = 0; i < hword_len; i++) {
		if (han_word[i].j_han.sign == 0)
			break;

		if (han_word[i].j_han.cho < 1 || han_word[i].j_han.cho > 20)
			break;

		if (han_word[i].j_han.jung < 2 || han_word[i].j_han.jung == 8 || han_word[i].j_han.jung == 8 ||
				han_word[i].j_han.jung == 16 || han_word[i].j_han.jung == 17 || han_word[i].j_han.jung == 24 || han_word[i].j_han.jung == 25 ||
				han_word[i].j_han.jung > 29)
			break;

		if (han_word[i].j_han.jong < 1 || han_word[i].j_han.jong == 18 || han_word[i].j_han.jong > 29)
			break;
		if (han_word[i].j_han.cho == 1 || han_word[i].j_han.jung == 2)
			break;

//		h_idx = jo2wan[han_word[i].j_code - 0x8442][2];
//		if (h_idx == 50000)
//			break;
	}

	if (i < hword_len)
		return 0;

	return 1;
}

/*
 * JO_INDEX_WORD 구조체에 조합형 색인어를 추출하여 저장한다.
 *        KRISTAL을 위해서 단일화시키지 않은 복합명사 결과를 리턴
 *        복합명사의 요소명사는 0에서 시작되는 인덱스를 loc에 저장
 *        전체명사나 일반명사는 100을 loc에 저장
 */
DWORD FilterJOIndexWord(JO_INDEX_WORD *idx_words)
{
    DWORD i, j, k, l, m, n;
    DWORD t1, t2, t3, t4;
    DWORD idx_word_len;
    DWORD idx_type = 1;
    DWORD idx_index_set[128]; /* 한 형태소 분석 결과에서 색인어로 판별되는 MI 위치 */
    DWORD iis_num = 0;
    struct { DWORD start; DWORD end;} IndexItems[512];
    DWORD nIndexItems = 0;
    UWORD nList=0, nCOL=0;
    UWORD cur=0;
    //JO_INDEX_ITEM       temp_IDX[MAX_INDEX_NUM];
    UWORD IDX_list[MAX_INDEX_NUM];
    //UWORD NumList=0;
    //DWORD temp_IDX_cnt=0;
    UWORD cut_len=0;
	idx_words->nIndex=0;
#ifdef SUSA_AS_INDEX
    /* 수사를 색인어로 추출 */
    for (i = 0; i < SusaMorpResult_Index; i++) {
        iis_num = 0;
        IndexItems[nIndexItems].start = idx_words->nIndex;
        for (j = 0; j < SusaMorpResult[i].nMorp; j++) {
            /* 수사나 단위명사가 아니면 skip */
            if (strcmp(SusaMorpResult[i].MI[j].info, "SUSA") && strcmp(SusaMorpResult[i].MI[j].info, "UNIT"))
                continue;

            /* 현재 위치를 저장 */
            idx_index_set[iis_num++] = j;
            /* 색인어 버퍼에 복사 */
            k = 0;
            while (SusaMorpResult[i].MI[j].Morpheme[k] != (UWORD) 0) {
                idx_words->IDX[idx_words->nIndex].str[k].j_code = SusaMorpResult[i].MI[j].Morpheme[k];
                k++;
            }
            idx_words->IDX[idx_words->nIndex].str_len = k;
            idx_words->IDX[idx_words->nIndex].loc = idx_type;
            idx_words->nIndex++;
        }

        /* 만일 수사 인덱스가 2개 이상 존재할 때, 그 인덱스를 하나로 합친 인덱스를 하나더 생성 */
        if (iis_num > 1) {
            idx_word_len = 0;
            for (j = 0; j < iis_num; j++) {
                k = 0;
                while (SusaMorpResult[i].MI[idx_index_set[j]].Morpheme[k] != (UWORD) 0) {
                    idx_words->IDX[idx_words->nIndex].str[idx_word_len].j_code =
                                                    SusaMorpResult[i].MI[idx_index_set[j]].Morpheme[k];
                    k++;
                    idx_word_len++;
                }
            }
            idx_words->IDX[idx_words->nIndex].str_len = idx_word_len;
            idx_words->IDX[idx_words->nIndex].loc = 100;
            idx_words->nIndex++;
        }
        idx_type++;
        IndexItems[nIndexItems].end = idx_words->nIndex;
        nIndexItems++;
    }
#endif
 /* 형태소 분석 결과 자체를 모두 색인어로 포함 + 복합명사 자체 포함 */
    /* 과학기술연구 --> 과학 기술 연구
     *                  과학기술 연구
     *                  과학 기술연구
     *                  과학기술연구
     */
    /* 아열대고압대 --> 아열대/90 고압대/91
     *                  아열대 고압 대
     *                  아열 대 고압대
     *                  아열 대 고압 대 
     * 90: 1_2 pattern : 1음절(접두사및 명사) + 2음절명사
     * 91: 2_1 pattern : 2음절명사 + 1음절(접미사,수량명사, 의존명사, 일반명사)
     * 92: 3음절 명사  
     * 93: 1_2 pattern 2_1 pattern : 90,91 모두 가능한 명사 
    */

    for (i = 0; i < MorpResult_Index; i++) {
        iis_num = 0;
        IndexItems[nIndexItems].start = idx_words->nIndex;
        nList=0;

        for (j = 0; j < MorpResult[i].nMorp; j++) {
            nCOL=0;
            if (MorpResult[i].MI[j].ninfo == 1 && strlen(MorpResult[i].MI[j].info) > 3)
                continue;
            /*******************************************************************
                     * 90,91,92,93,94 품사 정보  추가   (2006/01/31 by mini... )
             **********************************************************************/

            if ((MorpResult[i].MI[j].info[0] < 32 || MorpResult[i].MI[j].info[0] > 40)
                    && MorpResult[i].MI[j].info[0] != 'n'
                    && strcmp(MorpResult[i].MI[j].info, "JUBMISA JN")
                    && strcmp(MorpResult[i].MI[j].info, "xsn jn")
                    && strcmp(MorpResult[i].MI[j].info, "xp")) {

                /* 접미명사도 색인어에 포함 */
                /* 접두사도 색인어에 포함 */
                //90,91,92,93,94 품사는 3음절 명사처리를 위한 특별한 의미를 가짐
                if ((strcmp(MorpResult[i].MI[j].info, "90") && strcmp(MorpResult[i].MI[j].info, "91") &&
                    strcmp(MorpResult[i].MI[j].info, "92") && strcmp(MorpResult[i].MI[j].info, "93") &&
                    strcmp(MorpResult[i].MI[j].info, "94")) &&
                    MorpResult[i].MI[j].info[0]!=90 && MorpResult[i].MI[j].info[0]!=91 && MorpResult[i].MI[j].info[0]!=92 &&
                    MorpResult[i].MI[j].info[0]!=93 &&MorpResult[i].MI[j].info[0]!=94 ){
                  continue;
                }
            }

            curloc_eIDX[nList].nCOLUMN=0;
            curloc_eIDX[nList].nIDX=0;
            curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;

			
			/* 현재 위치를 저장 */
            idx_index_set[iis_num++] = j;

            /*******************************************************************************************
             * 2005/02/03 
             * 복합명사 기분석사전에 있는 접미명사를 바로 앞의 명사와 합친다... */
            /*if (!strcmp(MorpResult[i].MI[j].info, "xsn jn")) {
                k = idx_words->IDX[idx_words->nIndex-1].str_len;
                m = 0;
                while (MorpResult[i].MI[j].Morpheme[m] != (UWORD) 0) {
                    idx_words->IDX[idx_words->nIndex-1].str[k].j_code = MorpResult[i].MI[j].Morpheme[m];
                    m++; k++;
                }
                idx_words->IDX[idx_words->nIndex-1].str_len = k;

                continue;
            }*/
            /*******************************************************************************************/
            /* 색인어 버퍼에 복사 */
            k = 0;

            m = 0;
            while (MorpResult[i].MI[j].Morpheme[m] != (UWORD) 0) {
                curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].MI[curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp].Morpheme[m]=MorpResult[i].MI[j].Morpheme[m];
                m++;
            }
            curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].MI[curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp].Morpheme[m]=MorpResult[i].MI[j].Morpheme[m];


            curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].prev=0;
            curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp++;
            curloc_eIDX[nList].nIDX++;
            curloc_eIDX[nList].nCOLUMN++;
            curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;
            if(nList>0) nCOL=curloc_eIDX[nList-1].nCOLUMN;
            for( m = 1 ; m < nCOL ; m++ ) {
                curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN]=curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN-1];
                curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].prev=m;
                curloc_eIDX[nList].nCOLUMN++;
                curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;
            }



/*************************************** 
             2006/01/31      * 90,91,93 품사 정보 색인어 추출 모듈추가 by mini... */
            k = 0;
            nCOL=curloc_eIDX[nList].nCOLUMN;
            if(MorpResult[i].MI[j].info[0]==90 || !strcmp(MorpResult[i].MI[j].info,"90")){
                k=0;
                while(MorpResult[i].MI[j].Morpheme[k]!=0){
                    k++;
                }
                if(k==3)
                    cut_len=k;
                else{
                    printf("(90)JUBDU_MI_N length error: length is limited 3");
				}
                /* 1_2 패턴 (접두사_명사)   : 접두사 명사 모두 색인어로 추출*/

                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[0]=MorpResult[i].MI[j].Morpheme[0];
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[1]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                k=1;
                while(k<cut_len){
                    curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k-1]=MorpResult[i].MI[j].Morpheme[k];
                    k++;
                }
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k-1]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                nCOL++;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp=0;
                curloc_eIDX[nList].nIDX++;



                curloc_eIDX[nList].nCOLUMN=nCOL;
                if(nList>0){
                    nCOL=curloc_eIDX[nList-1].nCOLUMN;

                    for( m = 1 ; m < nCOL ; m++ ) {
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN]=curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN-1];
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].prev=m;

                        curloc_eIDX[nList].nCOLUMN++;
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;
                    }
                }

            //}
            }
else if(MorpResult[i].MI[j].info[0]==91 || !strcmp(MorpResult[i].MI[j].info,"91")){         
                /* 2_1 패턴 (명사_접사)   : 명사만 색인어로 추출*/
                k=0;
                while(MorpResult[i].MI[j].Morpheme[k]!=0){
                    k++;
                }
                if(k==3)
                    cut_len=k-1;
                else{
                    printf("(91)JUBDU_MI_N length error: length is limited 3");
				}
                k=0;
                while(k<cut_len){
                    curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k]=MorpResult[i].MI[j].Morpheme[k];
                    k++;
                }
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[0]=MorpResult[i].MI[j].Morpheme[k];
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[1]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                nCOL++;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp=0;
                curloc_eIDX[nList].nIDX++;

                curloc_eIDX[nList].nCOLUMN=nCOL;

                if(nList>0){
                    nCOL=curloc_eIDX[nList-1].nCOLUMN;

                    for( m = 1 ; m < nCOL ; m++ ) {
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN]=curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN-1];
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].prev=m;
                        curloc_eIDX[nList].nCOLUMN++;
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;
                    }
                }



            }
            else if(MorpResult[i].MI[j].info[0]==93 || !strcmp(MorpResult[i].MI[j].info,"93")){
                k=0;
                while(MorpResult[i].MI[j].Morpheme[k]!=0){
                    k++;
                }
                if(k==3)
                    cut_len=k;
                else{
                    printf("(93_1)JUBDU_MI_N length error: length is limited 3");
				}
                /* 1_2 패턴 (접두사_명사)   : 접두사 명사 모두 색인어로 추출*/
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[0]=MorpResult[i].MI[j].Morpheme[0];
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[1]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                k=1;
                while(k<cut_len){
                    curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k-1]=MorpResult[i].MI[j].Morpheme[k];
                    k++;
                }
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k-1]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
 curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                nCOL++;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp=0;
                curloc_eIDX[nList].nIDX++;
                curloc_eIDX[nList].nCOLUMN=nCOL;

                if(nList>0){
                    nCOL=curloc_eIDX[nList-1].nCOLUMN;

                    for( m = 1 ; m < nCOL ; m++ ) {
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN]=curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN-1];
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].prev=m;
                        curloc_eIDX[nList].nCOLUMN++;
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;
                    }
                }

                k=0;
                while(MorpResult[i].MI[j].Morpheme[k]!=0){
                    k++;
                }
                if(k==3)
                    cut_len=k-1;
                else{
                    printf("(93_2)JUBDU_MI_N length error: length is limited 3");
				}
                k=0;
                nCOL=curloc_eIDX[nList].nCOLUMN;
                /* 2_1 패턴 (명사_접사)   : 명사만 색인어로 추출*/
                while(k<cut_len){
                    curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k]=MorpResult[i].MI[j].Morpheme[k];
                    k++;
                }
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[k]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[0]=MorpResult[i].MI[j].Morpheme[k];
                curloc_eIDX[nList].IDX_word[nCOL].MI[curloc_eIDX[nList].IDX_word[nCOL].nMorp].Morpheme[1]='\0';
                curloc_eIDX[nList].IDX_word[nCOL].prev=0;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp++;
                nCOL++;
                curloc_eIDX[nList].IDX_word[nCOL].nMorp=0;
                curloc_eIDX[nList].nIDX++;


                curloc_eIDX[nList].nCOLUMN=nCOL;

                if(nList>0){
                    nCOL=curloc_eIDX[nList-1].nCOLUMN;

                    for( m = 1 ; m < nCOL ; m++ ) {
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN]=curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN-1];
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].prev=m;
                        curloc_eIDX[nList].nCOLUMN++;
                        curloc_eIDX[nList].IDX_word[curloc_eIDX[nList].nCOLUMN].nMorp=0;
                    }
                }



            }
            nList++;

		}//end of for (j = 0; j < MorpResult[i].nMorp; j++) {
        cur=0;
		if(nList>0){//색인어 리스트 갯수 색인어가 없으면 0
        for ( n = 0 ; n < curloc_eIDX[nList-1].nCOLUMN ; n++){
            cur=n;
            for ( m = nList-1 ; m>=0 ; m--){
                IDX_list[nList-1-m]=cur;
                //idx_words->location++;
                cur=curloc_eIDX[m].IDX_word[cur].prev;
            }

            for ( m = 0 ; m < nList; m++ ){
                cur=IDX_list[nList-1-m];
                for( l = 0 ;l < curloc_eIDX[m].IDX_word[cur].nMorp ; l++){
                    k=0;
                    while(curloc_eIDX[m].IDX_word[cur].MI[l].Morpheme[k]!=0){
                        idx_words->IDX[idx_words->nIndex].str[k].j_code=curloc_eIDX[m].IDX_word[cur].MI[l].Morpheme[k];
                        idx_words->IDX[idx_words->nIndex].loc =idx_type;
                        k++;
                    }
                    idx_words->IDX[idx_words->nIndex].str_len=k;
                    idx_words->nIndex++;
                }

            }

            //idx_type++;   2007.01.15 by mini
            if(n<curloc_eIDX[nList-1].nCOLUMN-1){
                idx_type++;
                nIndexItems++;
                IndexItems[nIndexItems].end = idx_words->nIndex;
                IndexItems[nIndexItems].start = idx_words->nIndex;
            }
        }
		}
        /* 만일 인덱스가 2개 이상 존재할 때, 그 인덱스를 하나로 합친 인덱스를 하나더 생성 */
        if (iis_num > 1) {
            idx_word_len = 0;
            for (j = 0; j < iis_num; j++) {
                k = 0;
                while (MorpResult[i].MI[idx_index_set[j]].Morpheme[k] != (UWORD) 0) {
                    idx_words->IDX[idx_words->nIndex].str[idx_word_len].j_code =
                                                        MorpResult[i].MI[idx_index_set[j]].Morpheme[k];
                    k++;
                    idx_word_len++;
                }
            }

            idx_words->IDX[idx_words->nIndex].str_len = idx_word_len;
            idx_words->IDX[idx_words->nIndex].loc = 100;
            idx_words->nIndex++;
        }


        IndexItems[nIndexItems].end = idx_words->nIndex;
        if (IndexItems[nIndexItems].start < IndexItems[nIndexItems].end) {
            /* 중복 체크 */
            /*
             * 형태소 분석 결과가 여러개가 존재할 때, 각 형태소 분석결과별로 색인어를 추출하면...
             * 중복된 색인어가 추출될 가능성이 있다.
             */
            for (l = 0; l < nIndexItems; l++) {
                t1 = IndexItems[l].end - IndexItems[l].start;
                t2 = IndexItems[nIndexItems].end - IndexItems[nIndexItems].start;
                if (t1 == t2) {
                    t3 = IndexItems[l].start;
                    t4 = IndexItems[nIndexItems].start;
                    while (t3 < IndexItems[l].end) {
                        if (CompJStr(idx_words->IDX[t3].str, idx_words->IDX[t3].str_len,
                                            idx_words->IDX[t4].str, idx_words->IDX[t4].str_len))
                            break;
 t3++; t4++;
                    }
                    if (t3 == IndexItems[l].end) /* 같은 결과가 있음 */
                        break;
                }
            }

            if (l < nIndexItems)
                idx_words->nIndex = IndexItems[nIndexItems].start; /* 복원 */
            else {
                idx_type++;//2006.03.23 by mini
                nIndexItems++;
            }
        }

        /* 100 색인어 중복 제거 */
        /* 중복된 100 색인어는 101으로 변경 */
        /* 마지막에 이를 필터링 */
        if (iis_num > 1) {
            for (l = 0; l < idx_words->nIndex-1; l++) {
                if (idx_words->IDX[l].loc != 100)
                    continue;
                if (!CompJStr(idx_words->IDX[l].str, idx_words->IDX[l].str_len,
                            idx_words->IDX[idx_words->nIndex-1].str, idx_words->IDX[idx_words->nIndex-1].str_len))
                    break;
            }
            if (l < idx_words->nIndex-1)
                idx_words->IDX[idx_words->nIndex-1].loc = 101;
        }
    } // end of for (i = 0; i < MorpResult_Index; i++) {

    /* 100 색인어 중복 제거 */
    /* str_len의 값을 0으로 세팅한다. */
    for (i = 0; i < idx_words->nIndex; i++) {
        if (idx_words->IDX[i].loc == 101)
            idx_words->IDX[i].str_len = 0;
#ifdef CAN
        /* 복합명사 자체를 제거 */
        if (idx_words->IDX[i].loc == 100)
            idx_words->IDX[i].str_len = 0;
#endif
    }
return 1;
}











/*
 * 조합형 한글 스트링 비교
 * 같으면 0 틀리면 1
 */
DWORD CompJStr(JO_CHAR *s1, DWORD s1_len, JO_CHAR *s2, DWORD s2_len)
{
	DWORD i;

	if (s1_len != s2_len)
		return 1;

	for (i = 0; i < s1_len; i++)
		if (s1[i].j_code != s2[i].j_code)
			break;

	if (i == s1_len)
		return 0;

	return 1;
}

/*
 * MorpAnal_J -- 조합형을 입력받아 형태소 분석 수행
 * Input
 * 		- 조합형 한글어절
 * Output
 * 		- 전역변수 MorpResult에 형태소 분석 결과 저장
 *
 * - 이 함수에서 사용되는 사전정보는 모두 새로 구성한 KAIST사전 정보 태그를 사용한다.
 * - 완성형 코드를 사용하는 루틴들...
 * 		수사처리, 미등록어 처리... --> 조합형에서 완성형으로 변환이 되지 않는 단어들은 이 모듈로 입력될 수 없다.
 */
DWORD MorpAnal_J(JO_CHAR *han_word, DWORD hword_len)
{
	DWORD header_index;								/* 첫글자의 사전에서의 헤더 인덱스 */
	DWORD ret_val, r_val1, r_val2;					/* 모듈 호출 리턴값 */
	tCNMORP_RESULT CNMorpRes[MAX_MORP_LIST];		/* 복합명사 기분석 사전 분석 결과 저장 버퍼 */
	UWORD CNMorpRes_Index;
	//tUADMORP_RESULT UserAnsRes[MAX_MORP_LIST];       /* 사용자  기분석 사전 분석 결과 저장 버퍼 */
	//UWORD UserAnsRes_Index;
	UBYTE wan_str[VS_BUFLEN];						/* 조합형 어절에 대한 완성형 스트링 */
	DIC_RESULT dic_result[DIC_RESULT_NUM];			/* 사전 탐색 결과 저장 버퍼 */
	UWORD dic_res_idx;
	ITF_MA_RESULT ma_res;							/* 미등록어 분석을 위한 완성형 형태소 분석 결과 저장 버퍼 */
	DWORD conv_ret;
	UWORD i;

	
	extern DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str);

	/*
	 * 조합형 어절을 완벽하게 처리를 하려면, 사전의 구조도 조합형에 맞게끔 바뀌어야 한다.
	 * 조합형 사전을 구성하려면 현재 2350개로 제한되어 있는 사전 헤더를 확장해야 하고,
	 * 헤더 인덱스를 구하는 방법도 달라져야 한다.
	 * 일단 사전의 구조를 바꾸기 전에 완성형 사전을 사용하고,
	 * 헤더 인덱스도 2350개의 완성형 코드 기준으로 구한다.
	 * GetJosaHeaderIndex는 내부적으로 단지 조합형 코드를 완성형으로 변환하고 인덱스를 구하는 
	 * 작업을 하므로 사전의 종류에 상관없이 사용할 수 있다.
	 */
	//어절이 완성형으로 변환이 안되는 음절을 하나라도 포함할 경우 미등록어 분석 모듈 바로 수행
	//완성형 어절로 분석하는 복합명사 및 수사 분석 모듈을 거치지 않는다.
	M_MORPRESULT_INDEX=0;
	for(i=0;i<hword_len;i++){
		header_index = GetJosaHeaderIndex(han_word[i].j_code);
		if(header_index == -1)
			break;
	}
//	printf("%d\n",header_index);
	if (header_index == -1){ /* 사전 헤더 인덱스를 구하는데 실패하면 */
		//06.06.09
		r_val2 = KAnalysisUnknownWord((HANGUL *)han_word, hword_len, &ma_res);	// 미등록어 형태소 분석 수행
	//	printf("KAnalysisUnknownWord:%d\n",r_val2);	
		if(r_val2) 
			return 1;
		else 
			return 0;
	}
	//사전 검색에서 필요한 첫음절의 header_index
	header_index = GetJosaHeaderIndex(han_word[0].j_code);
	
	//if (header_index == -1) /* 사전 헤더 인덱스를 구하는데 실패하면 */
	//	return 0;
#ifdef USER_ANSDIC_CHECK
	/*사용자 기분석 사전 탐색 수행*/
	ret_val = CheckUserAnswerDic((HANGUL *)han_word, hword_len, header_index, UserAnsRes,&UserAnsRes_Index);
	if (ret_val){
		/* 분석 성공하면 형태소 분석 결과 저장 버퍼의 내용을 MorpResult 버퍼로 복사한다.*/
		ret_val = CopyUserAnsDicResultToMorpResult(UserAnsRes,UserAnsRes_Index);
		
		return ret_val;
	}
#endif
	
#ifdef USER_DIC_PRE_CHECK
	/************************************************************************************************************
	 *
	 * 사용자 사전 탐색 수행
	 */
	M_MORPRESULT_INDEX = 0;
	ret_val = SearchUserDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx);
	if (ret_val)
		r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // 형태소 분석 수행
	else
		r_val2 = 0;	

	if (r_val2)
		return r_val2;
	/*************************************************************************************************************/
#endif

#ifdef COMP_NOUN_DIC_CHECK
	/*
	 * 복합명사 기분석 사전 탐색 및 분석
	 * 복합명사 기분석 사전에 분석에 성공하면, CNMorpRes에 저장된 분석 결과를
	 * MorpResult로 복사한다.
	 */
	ret_val = CheckCompNounWord((HANGUL *)han_word, hword_len, header_index, CNMorpRes, &CNMorpRes_Index);
	if (ret_val) {
		/*
		 * 분석 성공하면 복합명사 형태소 분석 결과 저장 버퍼의 내용을
		 * MorpResult 버퍼로 복사한다.
		 */
		ret_val = CopyCNMAResultToMorpResult(CNMorpRes, CNMorpRes_Index);
		return ret_val;
	}
#endif

	/* 조합형 --> 완성형 변환 */
	/* 수사 처리 모듈 내부에서 완성형 어절을 사용하기 때문이다. */
	/* 이 함수의 예외처리가 아직 완전하지 않다. */
	conv_ret = ConvertJo2Wan((HANGUL *)han_word, hword_len, wan_str);

	M_MORPRESULT_INDEX = 0;
	ret_val = CheckSusaWord((HANGUL *)han_word, hword_len, wan_str, SusaMorpResult, &SusaMorpResult_Index);
	// 수사 분석이 성공하든 실패하든 무조건 형태소분석은 수행

	r_val1 = SearchDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx); // 주사전 탐색 
//	printf("SearchDic%d\n",r_val1);
	if (r_val1) {		// 사전 탐색 성공
		r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // 형태소 분석 수행
//		printf("KAnalysisWord:%d\n",r_val2);
		if (!r_val2) {	// 형태소 분석 실패하면 미등록어 처리 호출
#ifndef USER_DIC_PRE_CHECK
			/************************************************************************************************************
			 *
			 * 사용자 사전 탐색 수행
			 */
			M_MORPRESULT_INDEX = 0;
			ret_val = SearchUserDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx);
			if (ret_val)
				r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // 형태소 분석 수행
			else
				r_val2 = 0;	
			/************************************************************************************************************/

			if (!r_val2) {
#endif
				r_val2 = KAnalysisUnknownWord((HANGUL *)han_word, hword_len, &ma_res);	// 미등록어 형태소 분석 수행
//				if (r_val2)
	//				CopyITFMAResultToMorpResult(ma_res);	// 완성형 분석결과 --> 조합형 분석결과
#ifndef USER_DIC_PRE_CHECK
			}
#endif
		}
	} else {			// 사전 탐색 실패하면 미등록어 처리 호출
#ifndef USER_DIC_PRE_CHECK
		/************************************************************************************************************
		 *
		 * 사용자 사전 탐색 수행
		 */
		M_MORPRESULT_INDEX = 0;
		ret_val = SearchUserDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx);
		if (ret_val)
			r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // 형태소 분석 수행
		else
			r_val2 = 0;	
		/************************************************************************************************************/

		if (!r_val2) {
#endif
			r_val2 = KAnalysisUnknownWord((HANGUL *)han_word, hword_len, &ma_res);	// 미등록어 형태소 분석 수행
		//	if (r_val2)
		//		CopyITFMAResultToMorpResult(ma_res);	// 완성형 분석결과 --> 조합형 분석결과
#ifndef USER_DIC_PRE_CHECK
		}
#endif
	}

	return r_val2;
}

/*
 * 복합명사 분석 결과를 내부 형태소 분석 저장 버퍼에 복사한다.
 * 결과가 완성형으로 구성되어 있으므로 이를 조합형으로 변환하는 과정이 이루어져야 한다.
 * 이유는 기분석 사전의 분석 결과부분이 완성형으로 사전에 적재되어 있으므로,
 * MorpResult에서 종합적으로 형태소분석 결과에 대한 처리를 하기 위해서는 이 작업이 필요하다.
 */
DWORD CopyCNMAResultToMorpResult(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index)
{
	DWORD i, j, k;
	HANGUL jh_han[VS_BUFLEN];
	DWORD jh_han_len;
	DWORD mr_idx, mp_idx;
	DWORD DicInfoValue;
	BYTE DicInfo[VS_BUFLEN];

	MorpResult_Index = mr_idx = 0; /* 초기화... */
	for (i = 0; i < CNMorpRes_Index; i++) {
		mp_idx = 0;
		for (j = 0; j < CNMorpRes[i].nMorp; j++) {
			/* 완성형 --> 조합형 */
			jh_han_len = Wan2Jo(CNMorpRes[i].MI[j].Morpheme, jh_han);
			if (jh_han_len == 0) /* 변환 실패 --> 오류 */
				return 0;

			/* MorpResult에 형태소 복사 */
			for (k = 0; k < jh_han_len; k++)
				MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = jh_han[k].j_code;
			MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = 0;

			/* 사전 정보 복사 */
			DicInfoValue = ConvertCNInfoToNewDicInfo(CNMorpRes[i].MI[j].info, DicInfo);
			MorpResult[mr_idx].MI[mp_idx].ninfo = 1;
			strcpy(MorpResult[mr_idx].MI[mp_idx].info, DicInfo);

			mp_idx++;
		}
		MorpResult[mr_idx].nMorp = mp_idx;
		mr_idx++;
	}
	MorpResult_Index = mr_idx;

	return 1;
}


/* 사용자가 입력한 기분석 결과를 내부 형태소 분석 저장 버퍼(MorpResult)에 복사한다.
 * 사용자가 입력한 기분석 결과는  완성형으로 구성되어 있으므로 이를 조합형으로 변환하는 과정이 필요하다.
*/
DWORD CopyUserAnsDicResultToMorpResult(tUADMORP_RESULT *UADMorpRes, UWORD UADMorpRes_Index){
	DWORD i, j, k;
    HANGUL jh_han[VS_BUFLEN];
    DWORD jh_han_len;
    DWORD mr_idx, mp_idx;
    DWORD DicInfoValue;
    BYTE DicInfo[VS_BUFLEN];
	MorpResult_Index = mr_idx = 0; /* 초기화... */

	for (i = 0; i < UADMorpRes_Index; i++) {
        mp_idx = 0;
        for (j = 0; j < UADMorpRes[i].nMorp; j++) {
            /* 완성형 --> 조합형 */
            jh_han_len = Wan2Jo(UADMorpRes[i].MI[j].Morpheme, jh_han);
            if (jh_han_len == 0) /* 변환 실패 --> 오류 */
                return 0;

            /* MorpResult에 형태소 복사 */
            for (k = 0; k < jh_han_len; k++)
                MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = jh_han[k].j_code;
            MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = 0;

            /* 사전 정보 복사 */
			if(UADMorpRes[i].MI[j].info == 'N'){
				DicInfoValue =32;
				strcpy(DicInfo, "ncn");
			}
			else {
				strcpy(DicInfo, "nuk");
				DicInfoValue=0;
			}
            MorpResult[mr_idx].MI[mp_idx].ninfo = 1;
            strcpy(MorpResult[mr_idx].MI[mp_idx].info, DicInfo);

            mp_idx++;
        }
        MorpResult[mr_idx].nMorp = mp_idx;
        mr_idx++;
    }
    MorpResult_Index = mr_idx;

    return 1;
}







/*
 * CopyITFMAResultToMorpResult
 *
 * 인터페이스를 위해서 디자인된 완성형 형태소 분석 결과 저장 버퍼는...
 * 미등록어 처리에서 분석 결과를 저장하는데 사용된다.
 * 그러나 모든 형태소 분석 결과를 MorpResult에 담기 위해서는...
 * 이 분석 결과를 MorpResult에 복사해야 한다.
 */
DWORD CopyITFMAResultToMorpResult(ITF_MA_RESULT ma_res)
{
	DWORD i, j, k;
	HANGUL jh_han[VS_BUFLEN];
	DWORD jh_han_len;
	DWORD mr_idx, mp_idx;
	//DWORD DicInfoValue;
	//BYTE DicInfo[VS_BUFLEN];

	MorpResult_Index = mr_idx = 0;
	for (i = 0; i < ma_res.MARes_num; i++) {
		mp_idx = 0;
		for (j = 0; j < ma_res.IMR[i].nMorp; j++) {
			jh_han_len = Wan2Jo(ma_res.IMR[i].MI[j].Morpheme, jh_han);
			if (jh_han_len == 0) /* 변환 실패 --> 오류 */
				return 0;

			/* MorpResult에 형태소 복사 */
			for (k = 0; k < jh_han_len; k++)
				MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = jh_han[k].j_code;
			MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = 0;

			/* 사전 정보 복사 */
			/* MorpResult의 info 필드도 문자열이므로 일단 kaist 품사태그를 그대로 이곳에 복사한다. */
			/* 나중에 색인어를 추출할 때 전체적으로 처리한다. */

			/********************************************************************/
			strcpy(MorpResult[mr_idx].MI[mp_idx].info, ma_res.IMR[i].MI[j].info);
			MorpResult[mr_idx].MI[mp_idx].ninfo = 1;
			/********************************************************************/

			mp_idx++;
		}
		MorpResult[mr_idx].nMorp = mp_idx;
		mr_idx++;
	}
	MorpResult_Index = mr_idx;

	return 1;
}
