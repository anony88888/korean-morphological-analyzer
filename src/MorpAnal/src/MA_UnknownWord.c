/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_UnknownWord.c)#  SPASIS System,     2000.06.16
 *
 *	#(Action)#
 *		- �̵�Ͼ� ó�� ��ƾ...
 */

#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Global.h>
#include <MA_Func.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MADIC_Func.h>
#include <MA_SearchTailDic.h>
#include <MA_Interface.h>
#include <math.h>
//#include <MA_Jo2Wan.h>

/* �� ������ ������ �������¼� ���� ���� ����� �����ؾ� �Ѵ�. */
#define TOTAL_NTAIL_FREQ		17923452
#define TOTAL_PTAIL_FREQ		6977061
#define TOTAL_BTAIL_FREQ		17923452

#define UNKNOWN_NOUNS		"nuk"
#define UNKNOWN_VAS			"up"

#define R_BUL_NUM		54
#define B_BUL_NUM		45

#define LAMDA1			0.7 /* �������¼� ���̺��� ���� ��� */
#define LAMDA2			0.2 /* �������¼� ����Ȯ�� ���� ��� */
#define LAMDA3			0.1 /* �������¼� ��� bigram Ȯ�� ���� ��� */

#define THRESH_NOUN_UK		0.18

typedef struct {
	UBYTE WanStr[VS_BUFLEN];
	UWORD W_Code[VS_BUFLEN];
	UWORD J_Code[VS_BUFLEN];
	UWORD len;
} L_PATTERN;

/* �̵�� ���¼� �м� ��� ���� ����ü */
typedef struct {
	tMORP_RESULT UK_MorpResult[20];
	UWORD MorpRes_num;
} UK_MORP_RES;
/* �� Ż�� ����� ������ ���� Ȱ��� ���� */
L_PATTERN R_Bul_Last_Char[] = {
					{ "��", { 0xb0a1, }, { 0x8861, }, 1 }, /* 0 */
					{ "��", { 0xb0c5, }, { 0x88e1, }, 1 }, /* 1 */
					{ "��", { 0xb0ed, }, { 0x89a1, }, 1 }, /* 2 */
					{ "��", { 0xb1b8, }, { 0x8a81, }, 1 }, /* 3 */
					{ "��", { 0xb1d7, }, { 0x8b61, }, 1 }, /* 4 */
					{ "��", { 0xb1ee, }, { 0x8c61, }, 1 }, /* 5 */
					{ "��", { 0xb2bf, }, { 0x8da1, }, 1 }, /* 6 */
					{ "��", { 0xb2f4, }, { 0x8f61, }, 1 }, /* 7 */
					{ "��", { 0xb3aa, }, { 0x9061, }, 1 }, /* 8 */
					{ "��", { 0xb3ca, }, { 0x90e1, }, 1 }, /* 9 */
					{ "��", { 0xb3eb, }, { 0x91a1, }, 1 }, /* 10 */
					{ "��", { 0xb4a9, }, { 0x9281, }, 1 }, /* 11 */
					{ "��", { 0xb4c0, }, { 0x9361, }, 1 }, /* 12 */
					{ "��", { 0xb4cf, }, { 0x93a1, }, 1 }, /* 13 */
					{ "��", { 0xb4d9, }, { 0x9461, }, 1 }, /* 14 */
					{ "��", { 0xb4f5, }, { 0x94e1, }, 1 }, /* 15 */
					{ "��", { 0xb5b5, }, { 0x95a1, }, 1 }, /* 16 */
					{ "��", { 0xb5ce, }, { 0x9681, }, 1 }, /* 17 */
					{ "��", { 0xb5e5, }, { 0x9761, }, 1 }, /* 18 */
					{ "��", { 0xb5e9, }, { 0x9769, }, 1 }, /* 19 */
					{ "��", { 0xb6b0, }, { 0x98e1, }, 1 }, /* 20 */
					{ "��", { 0xb8b6, }, { 0xa061, }, 1 }, /* 21 */
					{ "��", { 0xb8d3, }, { 0xa0e1, }, 1 }, /* 22 */
					{ "��", { 0xb8f0, }, { 0xa1a1, }, 1 }, /* 23 */
					{ "��", { 0xb9ab, }, { 0xa281, }, 1 }, /* 24 */
					{ "��", { 0xb9cc, }, { 0xa3a1, }, 1 }, /* 25 */
					{ "��", { 0xb9f6, }, { 0xa4e1, }, 1 }, /* 26 */
					{ "��", { 0xbace, }, { 0xa681, }, 1 }, /* 27 */
					{ "��", { 0xbaf1, }, { 0xa7a1, }, 1 }, /* 28 */
					{ "��", { 0xbafc, }, { 0xa861, }, 1 }, /* 29 */
					{ "��", { 0xbbe7, }, { 0xac61, }, 1 }, /* 30 */
					{ "��", { 0xbbec, }, { 0xac69, }, 1 }, /* 31 */
					{ "��", { 0xbcad, }, { 0xace1, }, 1 }, /* 32 */
					{ "��", { 0xbcd2, }, { 0xada1, }, 1 }, /* 33 */
					{ "��", { 0xbdba, }, { 0xaf61, }, 1 }, /* 34 */
					{ "��", { 0xbde1, }, { 0xb0e1, }, 1 }, /* 35 */
					{ "��", { 0xbdee, }, { 0xb1a1, }, 1 }, /* 36 */
					{ "��", { 0xbeb2, }, { 0xb361, }, 1 }, /* 37 */
					{ "��", { 0xbec6, }, { 0xb461, }, 1 }, /* 38 */
					{ "��", { 0xbeee, }, { 0xb4e1, }, 1 }, /* 39 */
					{ "��", { 0xbfa9, }, { 0xb561, }, 1 }, /* 40 */
					{ "��", { 0xbfec, }, { 0xb681, }, 1 }, /* 41 */
					{ "��", { 0xc0b8, }, { 0xb761, }, 1 }, /* 42 */
					{ "��", { 0xc0cc, }, { 0xb7a1, }, 1 }, /* 43 */
					{ "��", { 0xc0fa, }, { 0xb8e1, }, 1 }, /* 44 */
					{ "��", { 0xc1b6, }, { 0xb9a1, }, 1 }, /* 45 */
					{ "��", { 0xc1d6, }, { 0xba81, }, 1 }, /* 46 */
					{ "¼", { 0xc2bc, }, { 0xbce1, }, 1 }, /* 47 */
					{ "ũ", { 0xc5a9, }, { 0xc761, }, 1 }, /* 48 */
					{ "��", { 0xc5cd, }, { 0xc8e1, }, 1 }, /* 49 */
					{ "Ʈ", { 0xc6ae, }, { 0xcb61, }, 1 }, /* 50 */
					{ "��", { 0xc6c4, }, { 0xcc61, }, 1 }, /* 51 */
					{ "Ǫ", { 0xc7aa, }, { 0xce81, }, 1 }, /* 52 */
					{ "��", { 0xc7e3, }, { 0xd0e1, }, 1 }, /* 53 */
};

L_PATTERN B_Bul_Last_Char[] = {
					{ "��", { 0xb0a1, }, { 0x8861, }, 1 }, /* 0 */
					{ "��", { 0xb0c5, }, { 0x88e1, }, 1 }, /* 1 */
					{ "��", { 0xb0dc, }, { 0x8961, }, 1 }, /* 2 */
					{ "��", { 0xb0ed, }, { 0x89a1, }, 1 }, /* 3 */
					{ "��", { 0xb1b8, }, { 0x8a81, }, 1 }, /* 4 */
					{ "��", { 0xb1e2, }, { 0x8ba1, }, 1 }, /* 5 */
					{ "��", { 0xb1ee, }, { 0x8c61, }, 1 }, /* 6 */
					{ "��", { 0xb2a8, }, { 0x8ce1, }, 1 }, /* 7 */
					{ "��", { 0xb2bf, }, { 0x8da1, }, 1 }, /* 8 */
					{ "��", { 0xb3aa, }, { 0x9061, }, 1 }, /* 9 */
					{ "��", { 0xb3bb, }, { 0x9081, }, 1 }, /* 10 */
					{ "��", { 0xb4a9, }, { 0x9281, }, 1 }, /* 11 */
					{ "��", { 0xb4d9, }, { 0x9461, }, 1 }, /* 12 */
					{ "��", { 0xb4f5, }, { 0x94e1, }, 1 }, /* 13 */
					{ "��", { 0xb5b5, }, { 0x95a1, }, 1 }, /* 14 */
					{ "��", { 0xb5ce, }, { 0x9681, }, 1 }, /* 15 */
					{ "��", { 0xb5fb, }, { 0x9861, }, 1 }, /* 16 */
					{ "��", { 0xb6b0, }, { 0x98e1, }, 1 }, /* 17 */
					{ "��", { 0xb6f3, }, { 0x9c61, }, 1 }, /* 18 */
					{ "��", { 0xb7af, }, { 0x9ce1, }, 1 }, /* 19 */
					{ "��", { 0xb7c1, }, { 0x9d61, }, 1 }, /* 20 */
					{ "��", { 0xb7ce, }, { 0x9da1, }, 1 }, /* 21 */
					{ "��", { 0xb8ae, }, { 0x9fa1, }, 1 }, /* 22 */
					{ "��", { 0xb8b6, }, { 0xa061, }, 1 }, /* 23 */
					{ "��", { 0xb8c5, }, { 0xa081, }, 1 }, /* 24 */
					{ "��", { 0xb9cc, }, { 0xa3a1, }, 1 }, /* 25 */
					{ "��", { 0xbaad, }, { 0xa561, }, 1 }, /* 26 */
					{ "��", { 0xbac6, }, { 0xa641, }, 1 }, /* 27 */
					{ "��", { 0xbbe7, }, { 0xac61, }, 1 }, /* 28 */
					{ "��", { 0xbcad, }, { 0xace1, }, 1 }, /* 29 */
					{ "��", { 0xbdac, }, { 0xaee1, }, 1 }, /* 30 */
					{ "��", { 0xbdba, }, { 0xaf61, }, 1 }, /* 31 */
					{ "��", { 0xbea5, }, { 0xb281, }, 1 }, /* 32 */
					{ "��", { 0xbfa9, }, { 0xb561, }, 1 }, /* 33 */
					{ "��", { 0xbfc0, }, { 0xb5a1, }, 1 }, /* 34 */
					{ "��", { 0xc0da, }, { 0xb861, }, 1 }, /* 35 */
					{ "��", { 0xc0fa, }, { 0xb8e1, }, 1 }, /* 36 */
					{ "��", { 0xc1d6, }, { 0xba81, }, 1 }, /* 37 */
					{ "¥", { 0xc2a5, }, { 0xbc61, }, 1 }, /* 38 */
					{ "¼", { 0xc2bc, }, { 0xbce1, }, 1 }, /* 39 */
					{ "��", { 0xc2de, }, { 0xbe81, }, 1 }, /* 40 */
					{ "��", { 0xc3df, }, { 0xc281, }, 1 }, /* 41 */
					{ "Ÿ", { 0xc5b8, }, { 0xc861, }, 1 }, /* 42 */
					{ "��", { 0xc5cd, }, { 0xc8e1, }, 1 }, /* 43 */
					{ "ȣ", { 0xc8a3, }, { 0xd1a1, }, 1 }, /* 44 */
};

typedef struct {
	double P;
	DWORD from;
	DWORD to;
} TAIL_PROB;

tVOID ReverseWord(HANGUL *dest, HANGUL *src, UWORD src_len);
DWORD KAnalysisUnknownWord(HANGUL *h_word, UWORD h_word_len, ITF_MA_RESULT *ma_result);
DWORD SaveUnknownMARes(UK_MORP_RES *morp_res, HANGUL *h_word, UWORD h_word_len, TAILDIC_RESULT t_dic_res, UBYTE *MARContent, UWORD mode);
//DWORD SaveUnknownMARes(ITF_MA_RESULT *ma_res, HANGUL *h_word, UWORD h_word_len, TAILDIC_RESULT t_dic_res, UBYTE *MARContent, UWORD mode);
DWORD is_B_bul(UWORD code);
DWORD is_EU_bul(UWORD code);
DWORD is_S_bul(UWORD code);
DWORD is_R_bul(UWORD code);
DWORD is_D_bul(UWORD code);
DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str);
DWORD ConvertWan2Jo(UBYTE *w_str, HANGUL *j_str);
DWORD ParseMorpStr(UBYTE *str, MORPHEME *morps);
DWORD GetIndexWordFromMAResult(INDEX_WORD *Index, ITF_MA_RESULT ma_result);
DWORD GetIndexFromUnknownWord(HANGUL *h_word, UWORD h_word_len, INDEX_WORD *Index);
DWORD compare_prob(TAIL_PROB *node1, TAIL_PROB *node2);
//DWORD CopyMorpResult();
DWORD CopyMorpResult(UK_MORP_RES *morp_result);
DWORD CopyMorpResultToMAResult(ITF_MA_RESULT *ma_result);

tVOID ReverseWord(HANGUL *dest, HANGUL *src, UWORD src_len)
{
	DWORD index1 = src_len - 1;
	DWORD index2 = 0;

	while (index1 >= 0) {
		dest[index2].j_code = src[index1].j_code;
		index2++;
		index1--;
	}
}

DWORD GetIndexFromUnknownWord(HANGUL *h_word, UWORD h_word_len, INDEX_WORD *Index)
{
	ITF_MA_RESULT ma_result;
	DWORD ret_val;

	KAnalysisUnknownWord(h_word, h_word_len, &ma_result);
	ret_val = GetIndexWordFromMAResult(Index, ma_result);
	
	if (ret_val)
		return 1;

	return 0;
}

DWORD GetIndexWordFromMAResult(INDEX_WORD *Index, ITF_MA_RESULT ma_result)
{
	DWORD i, j;
	DWORD loc = 0;
	UBYTE com_nouns[VS_BUFLEN];

	Index->nIndex = 0;
	for (i = 0; i < ma_result.MARes_num; i++) {
		com_nouns[0] = '\0';
		for (j = 0; j < ma_result.IMR[i].nMorp; j++) {
			if (ma_result.IMR[i].MI[j].info[0] == 'n') {
				strcpy(Index->IDX[Index->nIndex].str, ma_result.IMR[i].MI[j].Morpheme);
				Index->IDX[Index->nIndex].loc = loc;
				strcat(com_nouns, Index->IDX[Index->nIndex].str);
				Index->nIndex++;
			}
			loc += strlen(ma_result.IMR[i].MI[j].Morpheme);
		}
		
		strcpy(Index->IDX[Index->nIndex].str, com_nouns);
		Index->IDX[Index->nIndex].loc = 0;
		Index->nIndex++;
	}

	return Index->nIndex;
}

/*
 * �̵�Ͼ� ���¼� �ؼ�...
 * �ٷ� ma_result�� ����ȴ�.
 */
DWORD KAnalysisUnknownWord(HANGUL *h_word, UWORD h_word_len, ITF_MA_RESULT *ma_result)
{
	HANGUL rev_h_word[VS_BUFLEN];
	HANGUL BoundaryChars[2];
	TAILDIC_RESULT tail_dic_result[DIC_RESULT_NUM];
	UWORD dic_res_idx;
	TAILDIC_RESULT bnd_dic_result[DIC_RESULT_NUM];
	UWORD bdic_res_idx;
	DWORD h_idx;
	DWORD ret_val, i, j;
	//UBYTE WanStr[VS_BUFLEN];
	UBYTE MARContent[S_BUFLEN];
	UBYTE MARContent_org[S_BUFLEN];
	UBYTE *ptr;
	UDWORD freq_ntail, freq_btail, freq_ptail;
//	ITF_MA_RESULT local_ma_res;
	TAIL_PROB Prob[VS_BUFLEN];
	DWORD Prob_idx = 0;
	///DWORD VA_Flag;
	double P_Bigram, P_Tail;
	double TailLenRatio;
	//by mini
	UK_MORP_RES local_morp_res, morp_result;
//	UWORD MorpRes_num=0;
//	ma_result->MARes_num = 0;
//	local_ma_res.MARes_num = 0;
	local_morp_res.MorpRes_num = 0;
	morp_result.MorpRes_num=0;
	/* �߿��� ���� �߰� Prob�� �ʱ�ȭ ���Ѿ� �Ѵ�. */
	Prob[0].P = (double) 0.0;
	ReverseWord(rev_h_word, h_word, h_word_len);
	h_idx = GetTailHeaderIndex(rev_h_word[0].j_code);
/*
	if (h_idx == -1)
		goto SKIP_VA_CHECK;
*/
	/*
	 * ü���� �������¼� ���� Ž��...
	 */
	//printf("h_idx:%d\n",h_idx);
	ret_val = SearchTAILDic(rev_h_word, h_word_len, h_idx, tail_dic_result, &dic_res_idx, NTAIL_MODE);
	//printf("SearchTAILDi:%d\n",ret_val);

	if (ret_val && tail_dic_result[dic_res_idx-1].len < h_word_len) {
			//printf("dic_res_idx:%d\n",dic_res_idx);
		for (i = dic_res_idx-1; i >= 0; i--) {
			//printf("dic_res_idx [%d]\n",i);
			/* ü���� ����-�������¼� ��� ���̱׷� �˻� */
			memcpy(BoundaryChars, &rev_h_word[tail_dic_result[i].len-1], sizeof(HANGUL) * 2);
			h_idx = GetTailHeaderIndex(BoundaryChars[0].j_code);

			ret_val = SearchTAILDic(BoundaryChars, 2, h_idx, bnd_dic_result, &bdic_res_idx, BTAIL_MODE);
			/* �ϴ� ������ ������ SKIP �Ѵ�... */
			/* �ƴϴ�... Ȯ������ 0���� �����ǰ� ��� �����Ѵ�. */
			/*
			if (ret_val == 0)
				continue;
			*/
			if (ret_val != 0) {
				/* ��� ���̱׷� �� */
				GetTAILContent(bnd_dic_result[0].InfoStart, bnd_dic_result[0].InfoLen, MARContent_org, BTAIL_MODE);
				ptr = strtok(MARContent_org, "&");
				ptr = strtok(NULL, "&");

				freq_btail = atoi(ptr);
			} else
				freq_btail = 0;

			/* ü���� �������¼� �� */
			GetTAILContent(tail_dic_result[i].InfoStart, tail_dic_result[i].InfoLen, MARContent_org, NTAIL_MODE);
			ptr = strtok(MARContent_org, "&");
			//printf("MARContent_org%s\n",MARContent_org);
			strcpy(MARContent, ptr);
			ptr = strtok(NULL, "&");

			freq_ntail = atoi(ptr);

			/* 
			 * Ȯ���� ��� 
			 * �Ű����� : ��� ���̱׷� Ȯ��, �������¼� ����Ȯ��, �������¼� ����, �������¼��� ���¼� ����
			 */
			P_Bigram = (double)freq_btail / (double)TOTAL_BTAIL_FREQ;
			P_Tail = (double)freq_ntail / (double)TOTAL_NTAIL_FREQ;
			TailLenRatio = (double)tail_dic_result[i].len / (double)h_word_len;
			Prob[Prob_idx].P = (double)LAMDA1*TailLenRatio + (double)LAMDA2*P_Tail + (double)LAMDA3*P_Bigram;

			//Prob[Prob_idx].from = local_ma_res.MARes_num;
			Prob[Prob_idx].from = local_morp_res.MorpRes_num;
			SaveUnknownMARes(&local_morp_res, h_word, h_word_len, tail_dic_result[i], MARContent, NTAIL_MODE);
			//SaveUnknownMARes(&local_morp_res, &local_ma_res, h_word, h_word_len, tail_dic_result[i], MARContent, NTAIL_MODE);
		//	printf("local_ma_res.MARes_num:%d\n",local_ma_res.MARes_num);
//			printf("local_morp_res.MorpRes_num:%d\n",local_morp_res.MorpRes_num);
			Prob[Prob_idx].to = local_morp_res.MorpRes_num - 1;
		//	Prob[Prob_idx].to = local_ma_res.MARes_num - 1;
			
			//printf("Prob[%d].to:%d\n",Prob_idx,Prob[Prob_idx].to);
			//printf("Prob[%d].from:%d Prob[%d].to:%d %lf\n",Prob_idx,Prob[Prob_idx].from, Prob_idx,Prob[Prob_idx].to,Prob[Prob_idx].P);
			Prob_idx++;
			if(local_morp_res.MorpRes_num>13)
				break;
		}

		/* Ȯ���� ū ������� ���� */
		qsort (Prob, Prob_idx, sizeof(TAIL_PROB), compare_prob);
		/* Ȯ���� ���� ���� 2���� ����� ��� */
		for (i = 0; i < Prob_idx; i++) {
			if (i >= 2)
				break;
			for (j = Prob[i].from; j <= Prob[i].to; j++) {
			//	printf("%d\n",morp_result.MorpRes_num);
		//		memcpy(&(ma_result->IMR[ma_result->MARes_num]), &(local_ma_res.IMR[j]), sizeof(ITF_MORP_RESULT));
		//2006.06.12 by mini �̵�Ͼ� ������ ���¼� �м� ���� 
				memcpy(&(morp_result.UK_MorpResult[morp_result.MorpRes_num]), &(local_morp_res.UK_MorpResult[j]), sizeof(tMORP_RESULT));
		//		printf("MA:memcpy:%d nMorp:%d %s\n",ma_result->MARes_num,ma_result->IMR[0].nMorp,ma_result->IMR[0].MI[0].info);	
				//printf("MORP:memcpy:%d nMorp:%d %s\n",morp_result.MorpRes_num,morp_result.UK_MorpResult[j].nMorp,morp_result.UK_MorpResult[j].MI[0].info);
				//printf("MORP:memcpy:%d nMorp:%d %s\n",morp_result.MorpRes_num,morp_result.UK_MorpResult[j].nMorp,morp_result.UK_MorpResult[j].MI[1].info);
		//		ma_result->MARes_num++;
				morp_result.MorpRes_num++;
			}
		}
	}

	/* ���� ���� Ȯ������ �Ӱ谪�� ���� ���� ���˻縦 ���� �ʴ´�... */
	if (is_HanJa || is_DiGit || Prob[0].P > THRESH_NOUN_UK)
		goto SKIP_VA_CHECK;
	/*
	 * ����� �������¼� ���� Ž��...
	 */
	ret_val = SearchTAILDic(rev_h_word, h_word_len, h_idx, tail_dic_result, &dic_res_idx, PTAIL_MODE);
	//printf("PTAIL_MODE ret_val:%d\n",ret_val);
	//printf(" tail_dic_result[dic_res_idx-1].len:%d dic_res_idx:%d\n", tail_dic_result[dic_res_idx-1].len,dic_res_idx);
	if (ret_val && tail_dic_result[dic_res_idx-1].len < h_word_len) {
		for (i = dic_res_idx-1; i >= 0; i--) {
			/* ����� �������¼� �� */
			//printf("dic_res_idx[%d]\n",i);
			GetTAILContent(tail_dic_result[i].InfoStart, tail_dic_result[i].InfoLen, MARContent_org, PTAIL_MODE);
			//printf("%d %d\n",tail_dic_result[i].InfoStart,tail_dic_result[i].InfoLen);
			ptr = strtok(MARContent_org, "&");
			strcpy(MARContent, ptr);
			//printf("PTAIL_MODE:MARContent:%s\n",MARContent);
			ptr = strtok(NULL, "&");
			freq_ptail = atoi(ptr);
			SaveUnknownMARes(&morp_result, h_word, h_word_len, tail_dic_result[i], MARContent, PTAIL_MODE);
				
//			SaveUnknownMARes(&morp_result, ma_result, h_word, h_word_len, tail_dic_result[i], MARContent, PTAIL_MODE);
			//printf("PTAIL_MODE MARes_num:%d\n",morp_result.MorpRes_num);
		}
	}

SKIP_VA_CHECK:

	/* ���� ������ ��ü ������ �ϳ��� ���ξ�� ���� 2002-08-30 */
	/*
	if (ma_result->MARes_num)
		return 1;
	*/

	/* �������¼Ұ� �������� �ʴ� ������ �� ��ü�� �ϳ��� ü���� �̵�Ͼ��̴�... */
//	ConvertJo2Wan(h_word, h_word_len, WanStr);
//	strcpy(ma_result->IMR[ma_result->MARes_num].MI[0].Morpheme, WanStr);
//	strcpy(ma_result->IMR[ma_result->MARes_num].MI[0].info, "nuk");
//	ma_result->IMR[ma_result->MARes_num].nMorp = 1;
//	ma_result->MARes_num++;
	
	for(i=0;i<h_word_len;i++){
		//ma_result->IMR[ma_result->MARes_num].MI[0].Morpheme[i]=h_word[i].j_code;
		morp_result.UK_MorpResult[morp_result.MorpRes_num].MI[0].Morpheme[i]=h_word[i].j_code;
//		MorpResult[MorpResult_Index].MI[Morpheme_Index].Morpheme[i]=h_word[i].j_code;
	}
	morp_result.UK_MorpResult[morp_result.MorpRes_num].MI[0].Morpheme[i]='\0';
	strcpy(morp_result.UK_MorpResult[morp_result.MorpRes_num].MI[0].info,"nuk");
	morp_result.UK_MorpResult[morp_result.MorpRes_num].MI[0].ninfo=1;
	morp_result.UK_MorpResult[morp_result.MorpRes_num].nMorp=1;
	morp_result.MorpRes_num++;
	//printf("[%d]:morp_result.MorpRes_num",morp_result.MorpRes_num);
	CopyMorpResult(&morp_result);
				
	CopyMorpResultToMAResult(ma_result);
	//printf("[MorpResult_Index:%d]\n",MorpResult_Index);
	return 1;
}

//DWORD CopyMorpResult(){
DWORD CopyMorpResult(UK_MORP_RES *morp_result){
	DWORD i, j, k=-1;
//	printf("[%d]:morp_result.MorpRes_num",morp_result->MorpRes_num);
	for ( i = 0 ; i < morp_result->MorpRes_num ; i++){
		memcpy(&(MorpResult[MorpResult_Index]),&(morp_result->UK_MorpResult[i]),sizeof(tMORP_RESULT));
		/*printf("MorpResult_Index:%d MorpResult[MorpResult_Index].nMorp:%d\n",MorpResult_Index, MorpResult[MorpResult_Index].nMorp);
		for( j = 0 ; j < MorpResult[MorpResult_Index].nMorp ; j++ ){
			k=-1;
			//printf("\tMorpResult:(%d)",j);
			while(MorpResult[MorpResult_Index].MI[j].Morpheme[++k]!='\0'){
				printf("%d(str)",MorpResult[MorpResult_Index].MI[j].Morpheme[k]);
			}
			//printf("\n");
			printf("\tMorpResult:(%d)%s(info)\n",j,MorpResult[MorpResult_Index].MI[j].info);

		}*/
		
		MorpResult_Index++; 
	}
	return 1;
	
}
DWORD CopyMorpResultToMAResult(ITF_MA_RESULT *ma_result){
	DWORD i,j,k,l_idx=0;
	UBYTE han_str[VS_BUFLEN];
    BYTE info_str[VS_BUFLEN];
    WORD index = 0;
    H_CHAR one_han;
	extern UWORD jo2wan[][3];
	ma_result->MARes_num = MorpResult_Index;
	//printf("ma_result->MARes_num%d:\n",ma_result->MARes_num);
	//printf("MorpResult_Index:%d",MorpResult_Index);
	for (i = 0; i < MorpResult_Index; i++) {
		l_idx = 0;
	//	printf(" M_MORPRESULT_NMORP(i):%d\n", M_MORPRESULT_NMORP(i));
	  //  printf("l_idx=%d\n",l_idx);
    	for (j = 0; j < M_MORPRESULT_NMORP(i); j++) {
			 k = 0;
        	index = 0;
        	while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD)0) {    // ������ --> �ϼ��� ��ȯ 
        		if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
            	M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) { // ������ �ѱ��̸� 
            	one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)-0x8442][1];
            	han_str[index++] = one_han.hl.high;
            	han_str[index++] = one_han.hl.low;
        	} else {       // �ѱ��� �ƴ� �ƽ�Ű �ڵ� �̸� 
            	one_han.code = M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k);
            	han_str[index++] = one_han.hl.high;
        	}

        	k++;
        	}
       		han_str[index] = '\0';
      //  	printf("M_MORPRESULT_MI_NINFO(i, j):%d\n",M_MORPRESULT_MI_NINFO(i, j));
        	if (M_MORPRESULT_MI_NINFO(i, j) == 1) {

        		if (strlen(M_MORPRESULT_MI_INFO(i, j)) == 1) {
            		strcpy(ma_result->IMR[i].MI[l_idx].Morpheme, han_str);
            		Convert_NumInfo(M_MORPRESULT_MI_INFO_ITEM(i, j, 0), info_str);
            		strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
        		} else {
            		strcpy(ma_result->IMR[i].MI[l_idx].Morpheme, han_str);
            		Convert_StrInfo(M_MORPRESULT_MI_INFO(i, j), info_str);
          //  		printf("M_MORPRESULT_MI_INFO(i, j)%s %s\n",M_MORPRESULT_MI_INFO(i, j),info_str);
            		strcpy(ma_result->IMR[i].MI[l_idx].info, info_str);
        		}
        	}
			else {
        		strcpy(ma_result->IMR[i].MI[l_idx].Morpheme, han_str);
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
//		printf("ma_result->IMR[i].nMorp:%d\n",ma_result->IMR[i].nMorp);
	}
//	printf("ma_result->MARes_num:%d\n",ma_result->MARes_num);	
	return 1;	
}
DWORD compare_prob(TAIL_PROB *node1, TAIL_PROB *node2)
{
	if (node1->P > node2->P)
		return -1;
	else if (node1->P < node2->P)
		return 1;
	else
		return 0;
}

/*
 * �м� ��忡 ���� ���¼� �м� ����� �����Ѵ�.
 */
//DWORD SaveUnknownMARes(UK_MORP_RES *morp_res,  ITF_MA_RESULT *ma_res, HANGUL *h_word, UWORD h_word_len, TAILDIC_RESULT t_dic_res, UBYTE *MARContent, UWORD mode)
DWORD SaveUnknownMARes(UK_MORP_RES *morp_res, HANGUL *h_word, UWORD h_word_len, TAILDIC_RESULT t_dic_res, UBYTE *MARContent, UWORD mode)
{
	UBYTE *ptr, *ptr_in;
	UBYTE WanStr[VS_BUFLEN];
	MORPHEME Morps[VS_BUFLEN];
	DWORD MorpCnt;
//	DWORD MARes_num = ma_res->MARes_num;
	DWORD nMorp,nMorp2, i, j;
	HANGUL HanTail[VS_BUFLEN];
	HANGUL FirstMorpItem[VS_BUFLEN];
	HANGUL tmp_h_word[VS_BUFLEN];
	DWORD FMI_num;
	BYTE va_pos[VS_BUFLEN];
	UBYTE va_morp_list[VS_BUFLEN];
	UBYTE morp_list[VS_BUFLEN];
	//UDWORD freq;
//	double Prob[VS_BUFLEN];
	HANGUL jh_han[VS_BUFLEN];
	DWORD jh_han_len;
	UWORD MorpRes_num=morp_res->MorpRes_num;
	nMorp2=0;
	//printf("--MorpRes_num:%d\n",MorpRes_num);
	if (mode == NTAIL_MODE) {
		/*
		 * ü���� �������¼� ����...
		 */
		ConvertJo2Wan(h_word, h_word_len - t_dic_res.len, WanStr);
		//printf("h_word_len:%d\n",h_word_len);
		ptr = strtok(MARContent, "_");
		while (ptr != NULL) {
			MorpCnt = ParseMorpStr(ptr, Morps);
			nMorp = 0;
			//printf("MorpCnt:%d",MorpCnt);
			/* ���� �˻� */
			if (Morps[0].Tag[0] == 'j')
				if (!CheckJosa(h_word, h_word_len - t_dic_res.len, 0))
					return 0;

			/* �޸���ƽ�� ��Ģ �˻� */
			/* ������ ù������ �� �� ���� ���� */
			if (h_word[h_word_len-t_dic_res.len].j_code == 0xace1/*��*/
					||h_word[h_word_len-t_dic_res.len].j_code == 0x89a1/*��*/
					||h_word[h_word_len-t_dic_res.len].j_code == 0x9c61/*��*/)
				return 0;

			/* �޸���ƽ�� ��Ģ �˻� */
			/* ü���� ������ ������ �� �� ���� ���� */
			if (h_word[h_word_len-t_dic_res.len-1].j_code == 0xb761/*��*/
					||h_word[h_word_len-t_dic_res.len-1].j_code == 0xa361/*��*/
					||h_word[h_word_len-t_dic_res.len-1].j_code == 0x99a1/*��*/)
				return 0;

			/* �޸���ƽ�� ��Ģ �˻� */
			/* 3�� �̻�Ǵ� ������ ���� �������� ���� '��'�� '�̴�'�� �м����� �ʴ´�. */
			if (t_dic_res.len == 1 && h_word[h_word_len-1].j_code == 0x9461/*��*/
					&& h_word_len >= 4) {
				return 0;
			}

			/*
			 * �������¼� ����...�ϼ���
			 
			strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
			strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, UNKNOWN_NOUNS);
			nMorp++;	
			
			 * �������¼� ����...�ϼ���
			 
//			printf("MorpCnt:%d\n",MorpCnt);
			for (i = 0; i < MorpCnt; i++) {
				strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
				strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
				nMorp++;
			}
			ma_res->IMR[MARes_num].nMorp = nMorp;
			nMorp = 0;
			MARes_num++;
*/
			//2006.06.12 by mini	
			//���� ���¼� ����.... ������
			for (i=0;i<h_word_len-t_dic_res.len;i++){
                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
            }
            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,UNKNOWN_NOUNS);
			morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
            nMorp2++;
			/*
			 * �������¼� ����...������
			 */
			for(i = 0;i<MorpCnt;i++){
				jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
				for(j=0;j<jh_han_len;j++){
					morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
				}
				morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
	            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
				//printf("%s\n",morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info);
				morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
				nMorp2++;
			}
			morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
			nMorp2=0;
			MorpRes_num++;
			morp_res->MorpRes_num=MorpRes_num;
			//printf("MorpRes_num:%d\n",MorpRes_num);		
		//	if (MARes_num > 15)
		//		break;
			if(MorpRes_num >13){
				//printf("**MorpRes_num:%d\n",MorpRes_num);
				break;}
			ptr = strtok(NULL, "_");
		}
	} else if (mode == PTAIL_MODE) {
		/*
		 * ����� �������¼� ����
		 */
		memcpy(HanTail, &h_word[h_word_len - t_dic_res.len], sizeof(HANGUL) * t_dic_res.len);
		//printf("h_word_len:%d t_dic_res.len:%d\n",h_word_len,t_dic_res.len);
		ptr = strtok(MARContent, "_");
		while (ptr != NULL) {
			//	if (MARes_num > 29)
			//	break;
			if(MorpRes_num >13)
				break;
			strcpy(morp_list, ptr);
			ptr_in = strtok(morp_list, "|");
			strcpy(va_pos, ptr_in);
			ptr_in = strtok(NULL, "|");
			strcpy(va_morp_list, ptr_in);

			MorpCnt = ParseMorpStr(va_morp_list, Morps); 
			FMI_num = ConvertWan2Jo(Morps[0].Morp, FirstMorpItem);
			if (FMI_num == 0)
				return 0;

			nMorp = 0;
			nMorp2 = 0;
			/* ���� �������¼� �и� */
			/* 1�� ¥�� �������¼Ҵ� �ϴ� ó���� ���� �ʴ´�. */
			if (t_dic_res.len > 1) {
				//printf("%d %d\n",HanTail[1].j_code,FirstMorpItem[0].j_code);
				if (HanTail[1].j_code == FirstMorpItem[0].j_code) {
					/* �������¼Ұ� �������� �ʾ��� ��... */
					ConvertJo2Wan(h_word, h_word_len - t_dic_res.len + 1, WanStr);
					//printf("h_word_len:%d t_dic_res.len:%d\n",h_word_len,t_dic_res.len);
			//		strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
			//		strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);
			//		nMorp++;
			//		for (i = 0; i < MorpCnt; i++) {
			//			strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
			//			strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
			//			nMorp++;
			//		}
			//		ma_res->IMR[MARes_num].nMorp = nMorp;

			//		nMorp = 0;
			//		MARes_num++;
					
					//2006.06.12 by mini
					   
		            //���� ���¼� ����.... ������
        		    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
              			  morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
           			 }
           			 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
         			 strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
            	     nMorp2++;
    		        /*
    		         * �������¼� ����...������
            		 */
           			 for(i = 0;i<MorpCnt;i++){
                		jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
              		 	for(j=0;j<jh_han_len;j++){
                    		morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                		}
                		morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                		strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                		morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                		nMorp2++;
            		}
            		morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
           			nMorp2=0;
          			MorpRes_num++;
            		morp_res->MorpRes_num=MorpRes_num;
					
					if (FirstMorpItem[0].j_code == 0xb461 || FirstMorpItem[0].j_code == 0xb4e1 
							|| FirstMorpItem[0].j_code == 0xb4f6 || FirstMorpItem[0].j_code == 0xb476) {
						/* ��/��/��/�� */
						/* �ұ�Ģ ���� �˻� */
						if (is_S_bul(HanTail[0].j_code)) {
							memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
							tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x15; /* �� */

						//	ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

						//	strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
						//	strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

						//	nMorp++;
						//	for (i = 0; i < MorpCnt; i++) {
						//		strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						//		strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						//		nMorp++;
						//	}
						//	ma_res->IMR[MARes_num].nMorp = nMorp;

						//	nMorp = 0;
						//	MARes_num++;
						
							//2006.06.12 by mini
							//���� ���¼� ����.... ������
		                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
        	                 	 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
            		        }
                   			morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                    		strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
							morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                    		nMorp2++;
							/*
		                     * �������¼� ����...������
        		             */
		                    for(i=0;i<MorpCnt;i++){
        		                jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
               		        	for(j=0;j<jh_han_len;j++){
                     	        	morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        		}
                        		morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                       			strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        		morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        		nMorp2++;
                    		}
                    		morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    		nMorp2=0;
                    		MorpRes_num++;
                    		morp_res->MorpRes_num=MorpRes_num;

						} else if (is_D_bul(HanTail[0].j_code)) {
							memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
							tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x08; /* �� */

						/*	ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

							strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

							nMorp++;
							for (i = 0; i < MorpCnt; i++) {
								strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
								strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
								nMorp++;
							}
							ma_res->IMR[MARes_num].nMorp = nMorp;

							nMorp = 0;
							MARes_num++;
							*/
							//2006.06.12 by mini
                            //���� ���¼� ����.... ������
                            for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                                 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
							morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                            nMorp2++;
                            /*
                             * �������¼� ����...������
                             */
                            for(i=0;i<MorpCnt;i++){
                                jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                                for(j=0;j<jh_han_len;j++){
                                    morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                                }
                                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                                strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                                nMorp2++;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                            nMorp2=0;
                            MorpRes_num++;
                            morp_res->MorpRes_num=MorpRes_num;




						}
					}

					/* �� Ż�� Ȱ������ ���� */
					if (FirstMorpItem[0].j_han.cho == 0x04 && is_R_bul(HanTail[0].j_code)) {
						memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
						tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x09; /* �� */

						/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

						nMorp++;
						for (i = 0; i < MorpCnt; i++) {
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
							nMorp++;
						}
						ma_res->IMR[MARes_num].nMorp = nMorp;

						nMorp = 0;
						MARes_num++;
	*/
						//2006.06.12 by mini
                            //���� ���¼� ����.... ������
                            for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                                 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
							morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                            nMorp2++;
                            /*
                             * �������¼� ����...������
                             */
                            for(i=0;i<MorpCnt;i++){
                                jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                                for(j=0;j<jh_han_len;j++){
                                    morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                                }
                                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                                strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                                nMorp2++;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                            nMorp2=0;
                            MorpRes_num++;
                            morp_res->MorpRes_num=MorpRes_num;
	
					}

					ptr = strtok(NULL, "_");
					continue;
				}//if (HanTail[1].j_code == FirstMorpItem[0].j_code)

				if (/*HanTail[0].j_han.cho == 0x0D &&*/ HanTail[0].j_han.jung == 0x0E 
						&& FirstMorpItem[0].j_han.cho == 0x0D && FirstMorpItem[0].j_han.jung == 0x03) {
					/* �� --> ��+�� */
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x0D;
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;
					/*
					ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;
					*/
					//2006.06.12 by mini
                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){//h_word->tmp_h_word
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                     }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;


					ptr = strtok(NULL, "_");
					continue;
				}

				if (/*HanTail[0].j_han.cho == 0x0D && */HanTail[0].j_han.jung == 0x15 
						&& FirstMorpItem[0].j_han.cho == 0x0D && FirstMorpItem[0].j_han.jung == 0x07) {
					/* �� --> ��+�� */
		
			memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x14;
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

					/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;
					*/
					//2006.06.12 by mini
                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){//h_word->tmp_h_word
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                     }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;

					
					ptr = strtok(NULL, "_");
					continue;
				}

				if (/*HanTail[0].j_han.cho == 0x0D &&*/HanTail[0].j_han.jung == 0x0B 
						&& FirstMorpItem[0].j_han.cho == 0x0D && FirstMorpItem[0].j_han.jung == 0x07) {
					/* �� --> ��+�� */
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x1D;
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

				/*	ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);
					//�ϼ��� ��Ʈ�� ��ȯ 
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;*/
					
					//2006.06.12 by mini
   					//���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){//h_word->tmp_h_word
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                     }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;

					ptr = strtok(NULL, "_");
					continue;
				}

				if (HanTail[0].j_han.cho == 0x0D && HanTail[0].j_han.jung == 0x0F 
						&& FirstMorpItem[0].j_han.cho == 0x0D && FirstMorpItem[0].j_han.jung == 0x07) {
					/* �� --> ��+�� */
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x12;
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

					/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;*/

					 //2006.06.12 by mini

                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;

					ptr = strtok(NULL, "_");
					continue;
				}

				if (FirstMorpItem[0].j_code == 0x8445  /* �� */
						|| FirstMorpItem[0].j_code == 0x8449  /* �� */
						|| FirstMorpItem[0].j_code == 0x8451  /* �� */
						|| FirstMorpItem[0].j_code == 0x8453) { /* �� */
					if (HanTail[0].j_han.cho == 0x0D && HanTail[0].j_han.jung == 0x1B
							&& HanTail[0].j_han.jong != 0x01) { /* �� */
						/*ConvertJo2Wan(h_word, h_word_len-t_dic_res.len, WanStr);

						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

						nMorp++;
						for (i = 0; i < MorpCnt; i++) {
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
							nMorp++;
						}
						ma_res->IMR[MARes_num].nMorp = nMorp;

						nMorp = 0;
						MARes_num++;
						*/
						 //2006.06.12 by mini
		
        	            //���� ���¼� ����.... ������
            	        for (i=0;i<h_word_len-t_dic_res.len;i++){
                	         morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
                   		 }
                    	morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                   	    strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
						morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     	nMorp2++;
                    	/*
                     	* �������¼� ����...������ 
                     	*/
                     	for(i = 0;i<MorpCnt;i++){
                        	jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        	for(j=0;j<jh_han_len;j++){
                            	morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        	}
                        	morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        	strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        	morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        	nMorp2++;
                    	}
                    	morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    	nMorp2=0;
                    	MorpRes_num++;
                    	morp_res->MorpRes_num=MorpRes_num;

						ptr = strtok(NULL, "_");
						continue;
					} else {
						memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
						tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

						/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

						nMorp++;
						for (i = 0; i < MorpCnt; i++) {
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
							strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
							nMorp++;
						}
						ma_res->IMR[MARes_num].nMorp = nMorp;

						nMorp = 0;
						MARes_num++;*/
						//2006.06.12 by mini
        
                        //���� ���¼� ����.... ������
                        for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                             morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                         }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
						morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                        /*
                        * �������¼� ����...������ 
                        */
                        for(i = 0;i<MorpCnt;i++){
                            jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                            for(j=0;j<jh_han_len;j++){
                                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                            nMorp2++;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                        nMorp2=0;
                        MorpRes_num++;
                        morp_res->MorpRes_num=MorpRes_num;


						ptr = strtok(NULL, "_");
						continue;
					}
				}

				/* �� --> �Ͼ�, �� --> �Ͼ� */
				if ((HanTail[0].j_code == 0xd081 && FirstMorpItem[0].j_code == 0xb4e1) 
						|| (HanTail[0].j_code == 0xd096 && FirstMorpItem[0].j_code == 0xb4f6)) {
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x03;
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

					/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;
					*/
					//2006.06.12 by mini

                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;


					ptr = strtok(NULL, "_");
					continue;
				}
				if ((HanTail[0].j_code == 0xcce1/*��*/ && FirstMorpItem[0].j_code == 0xb4e1/*��*/)
						||(HanTail[0].j_code == 0xccf6/*��*/ && FirstMorpItem[0].j_code == 0xb4f6/*��*/)) {
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x14;/*��*/
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

					/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;*/
					//2006.06.12 by mini

                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;


					ptr = strtok(NULL, "_");
					continue;
				}

				/* �� �ұ�Ģ */
				tmp_h_word[0].j_code = HanTail[0].j_code;
				tmp_h_word[0].j_han.jong = 0x01;
				if (is_EU_bul(tmp_h_word[0].j_code)) {
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x1B;/*��*/
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

					/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;*/
					//2006.06.12 by mini

                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;


					ptr = strtok(NULL, "_");
					continue;
				}

				/* �� �ұ�Ģ */
				if (is_B_bul(HanTail[0].j_code)) {
					if ((HanTail[1].j_code == 0xb5c1 || HanTail[1].j_code == 0xb5d6) /* ��,�� */
							&& (HanTail[0].j_han.jung == 0x0D || HanTail[0].j_han.jung == 0x03) /* ��,�� */
							&& (FirstMorpItem[0].j_code == 0xb461 || FirstMorpItem[0].j_code == 0xb476)) { /* ��,�� */
						;
					} else if ((HanTail[1].j_code == 0xb6a1 || HanTail[1].j_code == 0xb6b6) /* ��,�� */
							&& (HanTail[0].j_han.jung == 0x0D || HanTail[0].j_han.jung == 0x03 ||
								HanTail[0].j_han.jung == 0x14 || HanTail[0].j_han.jung == 0x07) /* ��,��,��,�� */
							&& (FirstMorpItem[0].j_code == 0xb4e1 || FirstMorpItem[0].j_code == 0xb4f6)) { /* ��,�� */
						;
					} else if (HanTail[1].j_code == 0xb685 || HanTail[1].j_code == 0xb689
							|| HanTail[1].j_code == 0xb681 || HanTail[1].j_code == 0xb5a1) { /* ��,��,��,�� */
						;
					} else {
						ptr = strtok(NULL, "_");
						continue;
					}

					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x13;/*��*/

					/*ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);

					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

					nMorp++;
					for (i = 0; i < MorpCnt; i++) {
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
						strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
						nMorp++;
					}
					ma_res->IMR[MARes_num].nMorp = nMorp;

					nMorp = 0;
					MARes_num++;*/
					//2006.06.12 by mini

                    //���� ���¼� ����.... ������
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * �������¼� ����...������
                     */
                     for(i = 0;i<MorpCnt;i++){
                        jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                        for(j=0;j<jh_han_len;j++){
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                        }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                    nMorp2=0;
                    MorpRes_num++;
                    morp_res->MorpRes_num=MorpRes_num;


					ptr = strtok(NULL, "_");
					continue;
				}
				/*ConvertJo2Wan(h_word, h_word_len-t_dic_res.len+1, WanStr);

				strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
				strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, va_pos);

				nMorp++;
				for (i = 0; i < MorpCnt; i++) {
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, Morps[i].Morp);
					strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, Morps[i].Tag);
					nMorp++;
				}
				ma_res->IMR[MARes_num].nMorp = nMorp;

				nMorp = 0;
				MARes_num++;
				*/
				//2006.06.12 by mini

                //���� ���¼� ����.... ������
                for (i=0;i<h_word_len-t_dic_res.len+1;i++){
            	    morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
                }
                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
				nMorp2++;
                /*
                 * �������¼� ����...������
                */
                for(i = 0;i<MorpCnt;i++){
                    jh_han_len = Wan2Jo(Morps[i].Morp, jh_han);
                    for(j=0;j<jh_han_len;j++){
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]=jh_han[j].j_code;
                    }
                    morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[j]='\0';
                    strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,Morps[i].Tag);
                    morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                    nMorp2++; 
                }
                morp_res->UK_MorpResult[MorpRes_num].nMorp=nMorp2;
                nMorp2=0;
                MorpRes_num++;
                morp_res->MorpRes_num=MorpRes_num;

				ptr = strtok(NULL, "_");
				continue;
			}
			ptr = strtok(NULL, "_");
		}
	}

//	ma_res->MARes_num = MARes_num;

	return 1;
}

DWORD is_B_bul(UWORD code)
{
	DWORD i;

	for (i = 0; i < B_BUL_NUM; i++) 
		if (B_Bul_Last_Char[i].J_Code[0] == code)
			break;

	if (i < B_BUL_NUM)
		return 1;
	
	return 0;
}

/* �� �ұ�Ģ ������ ���� �׽�Ʈ */
/* ���Ų����ʶ��󷯺������Ŀ������ */
DWORD is_EU_bul(UWORD code)
{
	switch (code) {
		case 0x8861:
		case 0x88e1:
		case 0x8ce1:
		case 0x9061:
		case 0x90e1:
		case 0x98e1:
		case 0x9c61:
		case 0x9ce1:
		case 0xa861:
		case 0xa8e1:
		case 0xb0e1:
		case 0xb461:
		case 0xc4e1:
		case 0xc8e1:
		case 0xcc61:
		case 0xcce1:
			return 1;
		default :
			return 0;
	}

	return 0;
}

/* �� �ұ�Ģ ������ ���� �׽�Ʈ */
/*�ײ���������������*/
DWORD is_S_bul(UWORD code)
{
	switch (code) {
		case 0x8b61:
		case 0x8f61:
		case 0x9061:
		case 0xa281:
		case 0xa681:
		case 0xb7a1:
		case 0xb861:
		case 0xb8e1:
		case 0xbba1:
			return 1;
		default :
			return 0;
	}
}

/* �� �ұ�Ģ ������ ���� �׽�Ʈ */
DWORD is_R_bul(UWORD code)
{
	DWORD i;

	for (i = 0; i < R_BUL_NUM; i++) 
		if (R_Bul_Last_Char[i].J_Code[0] == code)
			break;

	if (i < R_BUL_NUM)
		return 1;
	
	return 0;
}

/* �� �ұ�Ģ ������ ���� �׽�Ʈ */
/* �ɰ�洭�޵鹰�ҽ��� */
DWORD is_D_bul(UWORD code)
{
	switch (code) {
		case 0x88e9:
		case 0x8969:
		case 0x8ba9:
		case 0x9289:
		case 0x9469:
		case 0x9769:
		case 0xa289:
		case 0xa689:
		case 0xafa9:
		case 0xc4e9:
			return 1;
		default:
			return 0;
	}

	return 0;
}

/*
 * �������� �ϼ�������...
 */
DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str)
{
	DWORD i, idx = 0;
	H_CHAR one_han;
	extern UWORD jo2wan[][3];

	for (i = 0; i < h_word_len; i++) {
		if (0x8442 <= h_word[i].j_code && h_word[i].j_code <= 0xd3b7) {
			one_han.code = jo2wan[h_word[i].j_code - 0x8442][1];
			if (one_han.code == 0x0) {
				wan_str[0] = '\0';
				return 0;
			}
			wan_str[idx++] = one_han.hl.high;
			wan_str[idx++] = one_han.hl.low;
		} else {
			one_han.code = h_word[i].j_code;
			wan_str[idx++] = one_han.hl.high;
		}
	}
	wan_str[idx] = '\0';

	return idx;
}

/*
 * �ϼ����� ����������...
 * ������ �ϼ��� �ѱ��� �ԷµǾ�� ��.
 */
DWORD ConvertWan2Jo(UBYTE *w_str, HANGUL *j_str)
{
	UBYTE *ptr = w_str;
	H_CHAR h_char;
	DWORD j_idx = 0, c_idx;
	extern UWORD conv_tbl[][2];
	extern UWORD cnvt_tbl_jaso[][2];

	while (*ptr != '\0') {
		if (*ptr & 0x80) {
			h_char.hl.high = *ptr;
			ptr++;
			h_char.hl.low = *ptr;
			ptr++;
			if ((0xB0 <= h_char.hl.high && h_char.hl.high <= 0xC8) && (0xA1 <= h_char.hl.low && h_char.hl.low <= 0xFE)) {
				/* �ϼ��� ���� */
				c_idx = (h_char.hl.high - 0xB0) * 94;
				c_idx += h_char.hl.low - 0xA1;
				j_str[j_idx++].j_code = conv_tbl[c_idx][1];
			} else if ((h_char.hl.high == 0xA4) && (0xA1 <= h_char.hl.low && h_char.hl.low <= 0xD3)) {
				/* �ϼ��� �ڼ� */
				j_str[j_idx++].j_code = cnvt_tbl_jaso[h_char.code - 0xA4A1][1];
			} else 
				return 0;
		} else {
			return 0;
		}
	}

	return j_idx;
}

/*
 * �������¼� ���¼� ��Ʈ���� ���� �������� ��ȯ...
 */
DWORD ParseMorpStr(UBYTE *str, MORPHEME *morps)
{
	UBYTE *pStr;
	DWORD cnt = 0, idx = 0;
	//UBYTE temp_line[S_BUFLEN];
	UBYTE token[S_BUFLEN];

	pStr = str;
	while (*pStr != '\0') {
		if (*pStr & 0x80) {
			token[idx] = *pStr;
			pStr++; idx++;
			token[idx] = *pStr;
			pStr++; idx++;

			continue;
		}

		if (*pStr == '/') {
			token[idx] = '\0';
			strcpy(morps[cnt].Morp, token);
			idx = 0;
			pStr++;

			continue;
		}

		if (*pStr == '+') {
			token[idx] = '\0';
			strcpy(morps[cnt].Tag, token);
			idx = 0;
			cnt++;
			pStr++;

			continue;
		}

		token[idx] = *pStr;
		idx++; pStr++;
	}

	token[idx] = '\0';
	strcpy(morps[cnt].Tag, token);
	cnt++;

	return cnt;
}

