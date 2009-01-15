/*
 * Copyright (c) 2000
 * Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 * #(MADevMain.c)#  SPASIS System,     2000.04.14
 *
 * #(Action)#
 * 	-- KRISTAL�� ���ξ� ������ ���� �� ���(���¼� �м� ���� �и��Ͽ� �����Ѵ�.)
 * 	-- ��ū �и��⸦ ���α� �ܺη� ���� �� �ܾ ���� ���¼� �м����� ó���ϰԲ� �Ѵ�.
 * 	-- ������ ����� ���� �ϳ��� ��ū���� �и��� �Ǿ �ΰ� �̻��� �ܾ�� �νĵǾ�� �ϴ� �ܾ��...
 * 	-- �̰��� ��ü������ �ٽ� ó���Ѵ�.
 * 	-- ������ �Է�, ������ ���
 * 	-- KAnalysisWord�Լ� ȣ�� �������� ��� ����� �̰����� ���� �����Ѵ�.
 * 	-- KRISTAL�� ���ؼ� Ưȭ��Ų �����̴�.
 */
//�������� 2007/04/17
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

/* ���� ���¼� �м� ��� ���� ���� */
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
 * GetIndexFromOneWord -- �� �ܾ�� ���ξ� ����(������ �Է�)
 * Input 
 * 		- ������ �ѱ� �� ��Ÿ �ڵ�� ������ �и��� ��ū (han_word) -- ���ڴ� �Է� �Ұ�
 * 		- �� �ܾ ���� ���� ��� (idx_words)
 * 		- mode = 0 : �ѱ�, mode = 1 : ���� (mode)
 * Output
 * 		- ���������� �̷��� ���ΰ��
 */
DWORD GetIndexFromOneWord(JO_CHAR *han_word, int hword_len, JO_INDEX_WORD *idx_words, int mode)
{
	DWORD ret_val;

	SusaMorpResult_Index = 0;
	if (hword_len > MAX_INPUT_WORD_LEN)
		return 0;

	memcpy(idx_words->org_str, han_word, sizeof(JO_CHAR) * hword_len);
	idx_words->org_str_len = hword_len;

	/* ������ �˻� */
	ret_val = CheckJohabStr(han_word, hword_len);
//	ret_val=1;
//		printf("CheckJohabStr:ret_val=%d\n",ret_val);
	if (ret_val == 0)
		return 0;
	//printf("[debug]MorpAnal_J ȣ����\n");
	ret_val = MorpAnal_J(han_word, hword_len);
	//printf("[debug]MorpAnal_J ȣ����\n");
		 
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
 * JO_INDEX_WORD ����ü�� ������ ���ξ �����Ͽ� �����Ѵ�.
 *        KRISTAL�� ���ؼ� ����ȭ��Ű�� ���� ���ո�� ����� ����
 *        ���ո���� ��Ҹ��� 0���� ���۵Ǵ� �ε����� loc�� ����
 *        ��ü��糪 �Ϲݸ��� 100�� loc�� ����
 */
DWORD FilterJOIndexWord(JO_INDEX_WORD *idx_words)
{
    DWORD i, j, k, l, m, n;
    DWORD t1, t2, t3, t4;
    DWORD idx_word_len;
    DWORD idx_type = 1;
    DWORD idx_index_set[128]; /* �� ���¼� �м� ������� ���ξ�� �Ǻ��Ǵ� MI ��ġ */
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
    /* ���縦 ���ξ�� ���� */
    for (i = 0; i < SusaMorpResult_Index; i++) {
        iis_num = 0;
        IndexItems[nIndexItems].start = idx_words->nIndex;
        for (j = 0; j < SusaMorpResult[i].nMorp; j++) {
            /* ���糪 ������簡 �ƴϸ� skip */
            if (strcmp(SusaMorpResult[i].MI[j].info, "SUSA") && strcmp(SusaMorpResult[i].MI[j].info, "UNIT"))
                continue;

            /* ���� ��ġ�� ���� */
            idx_index_set[iis_num++] = j;
            /* ���ξ� ���ۿ� ���� */
            k = 0;
            while (SusaMorpResult[i].MI[j].Morpheme[k] != (UWORD) 0) {
                idx_words->IDX[idx_words->nIndex].str[k].j_code = SusaMorpResult[i].MI[j].Morpheme[k];
                k++;
            }
            idx_words->IDX[idx_words->nIndex].str_len = k;
            idx_words->IDX[idx_words->nIndex].loc = idx_type;
            idx_words->nIndex++;
        }

        /* ���� ���� �ε����� 2�� �̻� ������ ��, �� �ε����� �ϳ��� ��ģ �ε����� �ϳ��� ���� */
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
 /* ���¼� �м� ��� ��ü�� ��� ���ξ�� ���� + ���ո�� ��ü ���� */
    /* ���б������ --> ���� ��� ����
     *                  ���б�� ����
     *                  ���� �������
     *                  ���б������
     */
    /* �ƿ����д� --> �ƿ���/90 ��д�/91
     *                  �ƿ��� ��� ��
     *                  �ƿ� �� ��д�
     *                  �ƿ� �� ��� �� 
     * 90: 1_2 pattern : 1����(���λ�� ���) + 2�������
     * 91: 2_1 pattern : 2������� + 1����(���̻�,�������, �������, �Ϲݸ��)
     * 92: 3���� ���  
     * 93: 1_2 pattern 2_1 pattern : 90,91 ��� ������ ��� 
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
                     * 90,91,92,93,94 ǰ�� ����  �߰�   (2006/01/31 by mini... )
             **********************************************************************/

            if ((MorpResult[i].MI[j].info[0] < 32 || MorpResult[i].MI[j].info[0] > 40)
                    && MorpResult[i].MI[j].info[0] != 'n'
                    && strcmp(MorpResult[i].MI[j].info, "JUBMISA JN")
                    && strcmp(MorpResult[i].MI[j].info, "xsn jn")
                    && strcmp(MorpResult[i].MI[j].info, "xp")) {

                /* ���̸�絵 ���ξ ���� */
                /* ���λ絵 ���ξ ���� */
                //90,91,92,93,94 ǰ��� 3���� ���ó���� ���� Ư���� �ǹ̸� ����
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

			
			/* ���� ��ġ�� ���� */
            idx_index_set[iis_num++] = j;

            /*******************************************************************************************
             * 2005/02/03 
             * ���ո�� ��м������� �ִ� ���̸�縦 �ٷ� ���� ���� ��ģ��... */
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
            /* ���ξ� ���ۿ� ���� */
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
             2006/01/31      * 90,91,93 ǰ�� ���� ���ξ� ���� ����߰� by mini... */
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
                /* 1_2 ���� (���λ�_���)   : ���λ� ��� ��� ���ξ�� ����*/

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
                /* 2_1 ���� (���_����)   : ��縸 ���ξ�� ����*/
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
                /* 1_2 ���� (���λ�_���)   : ���λ� ��� ��� ���ξ�� ����*/
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
                /* 2_1 ���� (���_����)   : ��縸 ���ξ�� ����*/
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
		if(nList>0){//���ξ� ����Ʈ ���� ���ξ ������ 0
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
        /* ���� �ε����� 2�� �̻� ������ ��, �� �ε����� �ϳ��� ��ģ �ε����� �ϳ��� ���� */
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
            /* �ߺ� üũ */
            /*
             * ���¼� �м� ����� �������� ������ ��, �� ���¼� �м�������� ���ξ �����ϸ�...
             * �ߺ��� ���ξ ����� ���ɼ��� �ִ�.
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
                    if (t3 == IndexItems[l].end) /* ���� ����� ���� */
                        break;
                }
            }

            if (l < nIndexItems)
                idx_words->nIndex = IndexItems[nIndexItems].start; /* ���� */
            else {
                idx_type++;//2006.03.23 by mini
                nIndexItems++;
            }
        }

        /* 100 ���ξ� �ߺ� ���� */
        /* �ߺ��� 100 ���ξ�� 101���� ���� */
        /* �������� �̸� ���͸� */
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

    /* 100 ���ξ� �ߺ� ���� */
    /* str_len�� ���� 0���� �����Ѵ�. */
    for (i = 0; i < idx_words->nIndex; i++) {
        if (idx_words->IDX[i].loc == 101)
            idx_words->IDX[i].str_len = 0;
#ifdef CAN
        /* ���ո�� ��ü�� ���� */
        if (idx_words->IDX[i].loc == 100)
            idx_words->IDX[i].str_len = 0;
#endif
    }
return 1;
}











/*
 * ������ �ѱ� ��Ʈ�� ��
 * ������ 0 Ʋ���� 1
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
 * MorpAnal_J -- �������� �Է¹޾� ���¼� �м� ����
 * Input
 * 		- ������ �ѱ۾���
 * Output
 * 		- �������� MorpResult�� ���¼� �м� ��� ����
 *
 * - �� �Լ����� ���Ǵ� ���������� ��� ���� ������ KAIST���� ���� �±׸� ����Ѵ�.
 * - �ϼ��� �ڵ带 ����ϴ� ��ƾ��...
 * 		����ó��, �̵�Ͼ� ó��... --> ���������� �ϼ������� ��ȯ�� ���� �ʴ� �ܾ���� �� ���� �Էµ� �� ����.
 */
DWORD MorpAnal_J(JO_CHAR *han_word, DWORD hword_len)
{
	DWORD header_index;								/* ù������ ���������� ��� �ε��� */
	DWORD ret_val, r_val1, r_val2;					/* ��� ȣ�� ���ϰ� */
	tCNMORP_RESULT CNMorpRes[MAX_MORP_LIST];		/* ���ո�� ��м� ���� �м� ��� ���� ���� */
	UWORD CNMorpRes_Index;
	//tUADMORP_RESULT UserAnsRes[MAX_MORP_LIST];       /* �����  ��м� ���� �м� ��� ���� ���� */
	//UWORD UserAnsRes_Index;
	UBYTE wan_str[VS_BUFLEN];						/* ������ ������ ���� �ϼ��� ��Ʈ�� */
	DIC_RESULT dic_result[DIC_RESULT_NUM];			/* ���� Ž�� ��� ���� ���� */
	UWORD dic_res_idx;
	ITF_MA_RESULT ma_res;							/* �̵�Ͼ� �м��� ���� �ϼ��� ���¼� �м� ��� ���� ���� */
	DWORD conv_ret;
	UWORD i;

	
	extern DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str);

	/*
	 * ������ ������ �Ϻ��ϰ� ó���� �Ϸ���, ������ ������ �������� �°Բ� �ٲ��� �Ѵ�.
	 * ������ ������ �����Ϸ��� ���� 2350���� ���ѵǾ� �ִ� ���� ����� Ȯ���ؾ� �ϰ�,
	 * ��� �ε����� ���ϴ� ����� �޶����� �Ѵ�.
	 * �ϴ� ������ ������ �ٲٱ� ���� �ϼ��� ������ ����ϰ�,
	 * ��� �ε����� 2350���� �ϼ��� �ڵ� �������� ���Ѵ�.
	 * GetJosaHeaderIndex�� ���������� ���� ������ �ڵ带 �ϼ������� ��ȯ�ϰ� �ε����� ���ϴ� 
	 * �۾��� �ϹǷ� ������ ������ ������� ����� �� �ִ�.
	 */
	//������ �ϼ������� ��ȯ�� �ȵǴ� ������ �ϳ��� ������ ��� �̵�Ͼ� �м� ��� �ٷ� ����
	//�ϼ��� ������ �м��ϴ� ���ո�� �� ���� �м� ����� ��ġ�� �ʴ´�.
	M_MORPRESULT_INDEX=0;
	for(i=0;i<hword_len;i++){
		header_index = GetJosaHeaderIndex(han_word[i].j_code);
		if(header_index == -1)
			break;
	}
//	printf("%d\n",header_index);
	if (header_index == -1){ /* ���� ��� �ε����� ���ϴµ� �����ϸ� */
		//06.06.09
		r_val2 = KAnalysisUnknownWord((HANGUL *)han_word, hword_len, &ma_res);	// �̵�Ͼ� ���¼� �м� ����
	//	printf("KAnalysisUnknownWord:%d\n",r_val2);	
		if(r_val2) 
			return 1;
		else 
			return 0;
	}
	//���� �˻����� �ʿ��� ù������ header_index
	header_index = GetJosaHeaderIndex(han_word[0].j_code);
	
	//if (header_index == -1) /* ���� ��� �ε����� ���ϴµ� �����ϸ� */
	//	return 0;
#ifdef USER_ANSDIC_CHECK
	/*����� ��м� ���� Ž�� ����*/
	ret_val = CheckUserAnswerDic((HANGUL *)han_word, hword_len, header_index, UserAnsRes,&UserAnsRes_Index);
	if (ret_val){
		/* �м� �����ϸ� ���¼� �м� ��� ���� ������ ������ MorpResult ���۷� �����Ѵ�.*/
		ret_val = CopyUserAnsDicResultToMorpResult(UserAnsRes,UserAnsRes_Index);
		
		return ret_val;
	}
#endif
	
#ifdef USER_DIC_PRE_CHECK
	/************************************************************************************************************
	 *
	 * ����� ���� Ž�� ����
	 */
	M_MORPRESULT_INDEX = 0;
	ret_val = SearchUserDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx);
	if (ret_val)
		r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // ���¼� �м� ����
	else
		r_val2 = 0;	

	if (r_val2)
		return r_val2;
	/*************************************************************************************************************/
#endif

#ifdef COMP_NOUN_DIC_CHECK
	/*
	 * ���ո�� ��м� ���� Ž�� �� �м�
	 * ���ո�� ��м� ������ �м��� �����ϸ�, CNMorpRes�� ����� �м� �����
	 * MorpResult�� �����Ѵ�.
	 */
	ret_val = CheckCompNounWord((HANGUL *)han_word, hword_len, header_index, CNMorpRes, &CNMorpRes_Index);
	if (ret_val) {
		/*
		 * �м� �����ϸ� ���ո�� ���¼� �м� ��� ���� ������ ������
		 * MorpResult ���۷� �����Ѵ�.
		 */
		ret_val = CopyCNMAResultToMorpResult(CNMorpRes, CNMorpRes_Index);
		return ret_val;
	}
#endif

	/* ������ --> �ϼ��� ��ȯ */
	/* ���� ó�� ��� ���ο��� �ϼ��� ������ ����ϱ� �����̴�. */
	/* �� �Լ��� ����ó���� ���� �������� �ʴ�. */
	conv_ret = ConvertJo2Wan((HANGUL *)han_word, hword_len, wan_str);

	M_MORPRESULT_INDEX = 0;
	ret_val = CheckSusaWord((HANGUL *)han_word, hword_len, wan_str, SusaMorpResult, &SusaMorpResult_Index);
	// ���� �м��� �����ϵ� �����ϵ� ������ ���¼Һм��� ����

	r_val1 = SearchDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx); // �ֻ��� Ž�� 
//	printf("SearchDic%d\n",r_val1);
	if (r_val1) {		// ���� Ž�� ����
		r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // ���¼� �м� ����
//		printf("KAnalysisWord:%d\n",r_val2);
		if (!r_val2) {	// ���¼� �м� �����ϸ� �̵�Ͼ� ó�� ȣ��
#ifndef USER_DIC_PRE_CHECK
			/************************************************************************************************************
			 *
			 * ����� ���� Ž�� ����
			 */
			M_MORPRESULT_INDEX = 0;
			ret_val = SearchUserDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx);
			if (ret_val)
				r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // ���¼� �м� ����
			else
				r_val2 = 0;	
			/************************************************************************************************************/

			if (!r_val2) {
#endif
				r_val2 = KAnalysisUnknownWord((HANGUL *)han_word, hword_len, &ma_res);	// �̵�Ͼ� ���¼� �м� ����
//				if (r_val2)
	//				CopyITFMAResultToMorpResult(ma_res);	// �ϼ��� �м���� --> ������ �м����
#ifndef USER_DIC_PRE_CHECK
			}
#endif
		}
	} else {			// ���� Ž�� �����ϸ� �̵�Ͼ� ó�� ȣ��
#ifndef USER_DIC_PRE_CHECK
		/************************************************************************************************************
		 *
		 * ����� ���� Ž�� ����
		 */
		M_MORPRESULT_INDEX = 0;
		ret_val = SearchUserDic((HANGUL *)han_word, hword_len, header_index, dic_result, &dic_res_idx);
		if (ret_val)
			r_val2 = KAnalysisWord((HANGUL *)han_word, hword_len, dic_result, dic_res_idx, NORMAL); // ���¼� �м� ����
		else
			r_val2 = 0;	
		/************************************************************************************************************/

		if (!r_val2) {
#endif
			r_val2 = KAnalysisUnknownWord((HANGUL *)han_word, hword_len, &ma_res);	// �̵�Ͼ� ���¼� �м� ����
		//	if (r_val2)
		//		CopyITFMAResultToMorpResult(ma_res);	// �ϼ��� �м���� --> ������ �м����
#ifndef USER_DIC_PRE_CHECK
		}
#endif
	}

	return r_val2;
}

/*
 * ���ո�� �м� ����� ���� ���¼� �м� ���� ���ۿ� �����Ѵ�.
 * ����� �ϼ������� �����Ǿ� �����Ƿ� �̸� ���������� ��ȯ�ϴ� ������ �̷������ �Ѵ�.
 * ������ ��м� ������ �м� ����κ��� �ϼ������� ������ ����Ǿ� �����Ƿ�,
 * MorpResult���� ���������� ���¼Һм� ����� ���� ó���� �ϱ� ���ؼ��� �� �۾��� �ʿ��ϴ�.
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
			strcpy(MorpResult[mr_idx].MI[mp_idx].info, DicInfo);

			mp_idx++;
		}
		MorpResult[mr_idx].nMorp = mp_idx;
		mr_idx++;
	}
	MorpResult_Index = mr_idx;

	return 1;
}


/* ����ڰ� �Է��� ��м� ����� ���� ���¼� �м� ���� ����(MorpResult)�� �����Ѵ�.
 * ����ڰ� �Է��� ��м� �����  �ϼ������� �����Ǿ� �����Ƿ� �̸� ���������� ��ȯ�ϴ� ������ �ʿ��ϴ�.
*/
DWORD CopyUserAnsDicResultToMorpResult(tUADMORP_RESULT *UADMorpRes, UWORD UADMorpRes_Index){
	DWORD i, j, k;
    HANGUL jh_han[VS_BUFLEN];
    DWORD jh_han_len;
    DWORD mr_idx, mp_idx;
    DWORD DicInfoValue;
    BYTE DicInfo[VS_BUFLEN];
	MorpResult_Index = mr_idx = 0; /* �ʱ�ȭ... */

	for (i = 0; i < UADMorpRes_Index; i++) {
        mp_idx = 0;
        for (j = 0; j < UADMorpRes[i].nMorp; j++) {
            /* �ϼ��� --> ������ */
            jh_han_len = Wan2Jo(UADMorpRes[i].MI[j].Morpheme, jh_han);
            if (jh_han_len == 0) /* ��ȯ ���� --> ���� */
                return 0;

            /* MorpResult�� ���¼� ���� */
            for (k = 0; k < jh_han_len; k++)
                MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = jh_han[k].j_code;
            MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = 0;

            /* ���� ���� ���� */
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
 * �������̽��� ���ؼ� �����ε� �ϼ��� ���¼� �м� ��� ���� ���۴�...
 * �̵�Ͼ� ó������ �м� ����� �����ϴµ� ���ȴ�.
 * �׷��� ��� ���¼� �м� ����� MorpResult�� ��� ���ؼ���...
 * �� �м� ����� MorpResult�� �����ؾ� �Ѵ�.
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
			if (jh_han_len == 0) /* ��ȯ ���� --> ���� */
				return 0;

			/* MorpResult�� ���¼� ���� */
			for (k = 0; k < jh_han_len; k++)
				MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = jh_han[k].j_code;
			MorpResult[mr_idx].MI[mp_idx].Morpheme[k] = 0;

			/* ���� ���� ���� */
			/* MorpResult�� info �ʵ嵵 ���ڿ��̹Ƿ� �ϴ� kaist ǰ���±׸� �״�� �̰��� �����Ѵ�. */
			/* ���߿� ���ξ ������ �� ��ü������ ó���Ѵ�. */

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
