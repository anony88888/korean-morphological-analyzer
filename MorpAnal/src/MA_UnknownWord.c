/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_UnknownWord.c)#  SPASIS System,     2000.06.16
 *
 *	#(Action)#
 *		- 미등록어 처리 루틴...
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

/* 이 세개의 변수는 형식형태소 생성 툴의 결과를 참고해야 한다. */
#define TOTAL_NTAIL_FREQ		17923452
#define TOTAL_PTAIL_FREQ		6977061
#define TOTAL_BTAIL_FREQ		17923452

#define UNKNOWN_NOUNS		"nuk"
#define UNKNOWN_VAS			"up"

#define R_BUL_NUM		54
#define B_BUL_NUM		45

#define LAMDA1			0.7 /* 형식형태소 길이비율 관련 계수 */
#define LAMDA2			0.2 /* 형식형태소 출현확률 관련 계수 */
#define LAMDA3			0.1 /* 형식형태소 경계 bigram 확률 관련 계수 */

#define THRESH_NOUN_UK		0.18

typedef struct {
	UBYTE WanStr[VS_BUFLEN];
	UWORD W_Code[VS_BUFLEN];
	UWORD J_Code[VS_BUFLEN];
	UWORD len;
} L_PATTERN;

/* 미등록 형태소 분석 결과 저장 구조체 */
typedef struct {
	tMORP_RESULT UK_MorpResult[20];
	UWORD MorpRes_num;
} UK_MORP_RES;
/* ㄹ 탈락 용언의 마지막 음절 활용꼴 패턴 */
L_PATTERN R_Bul_Last_Char[] = {
					{ "가", { 0xb0a1, }, { 0x8861, }, 1 }, /* 0 */
					{ "거", { 0xb0c5, }, { 0x88e1, }, 1 }, /* 1 */
					{ "고", { 0xb0ed, }, { 0x89a1, }, 1 }, /* 2 */
					{ "구", { 0xb1b8, }, { 0x8a81, }, 1 }, /* 3 */
					{ "그", { 0xb1d7, }, { 0x8b61, }, 1 }, /* 4 */
					{ "까", { 0xb1ee, }, { 0x8c61, }, 1 }, /* 5 */
					{ "꼬", { 0xb2bf, }, { 0x8da1, }, 1 }, /* 6 */
					{ "끄", { 0xb2f4, }, { 0x8f61, }, 1 }, /* 7 */
					{ "나", { 0xb3aa, }, { 0x9061, }, 1 }, /* 8 */
					{ "너", { 0xb3ca, }, { 0x90e1, }, 1 }, /* 9 */
					{ "노", { 0xb3eb, }, { 0x91a1, }, 1 }, /* 10 */
					{ "누", { 0xb4a9, }, { 0x9281, }, 1 }, /* 11 */
					{ "느", { 0xb4c0, }, { 0x9361, }, 1 }, /* 12 */
					{ "니", { 0xb4cf, }, { 0x93a1, }, 1 }, /* 13 */
					{ "다", { 0xb4d9, }, { 0x9461, }, 1 }, /* 14 */
					{ "더", { 0xb4f5, }, { 0x94e1, }, 1 }, /* 15 */
					{ "도", { 0xb5b5, }, { 0x95a1, }, 1 }, /* 16 */
					{ "두", { 0xb5ce, }, { 0x9681, }, 1 }, /* 17 */
					{ "드", { 0xb5e5, }, { 0x9761, }, 1 }, /* 18 */
					{ "들", { 0xb5e9, }, { 0x9769, }, 1 }, /* 19 */
					{ "떠", { 0xb6b0, }, { 0x98e1, }, 1 }, /* 20 */
					{ "마", { 0xb8b6, }, { 0xa061, }, 1 }, /* 21 */
					{ "머", { 0xb8d3, }, { 0xa0e1, }, 1 }, /* 22 */
					{ "모", { 0xb8f0, }, { 0xa1a1, }, 1 }, /* 23 */
					{ "무", { 0xb9ab, }, { 0xa281, }, 1 }, /* 24 */
					{ "미", { 0xb9cc, }, { 0xa3a1, }, 1 }, /* 25 */
					{ "버", { 0xb9f6, }, { 0xa4e1, }, 1 }, /* 26 */
					{ "부", { 0xbace, }, { 0xa681, }, 1 }, /* 27 */
					{ "비", { 0xbaf1, }, { 0xa7a1, }, 1 }, /* 28 */
					{ "빠", { 0xbafc, }, { 0xa861, }, 1 }, /* 29 */
					{ "사", { 0xbbe7, }, { 0xac61, }, 1 }, /* 30 */
					{ "살", { 0xbbec, }, { 0xac69, }, 1 }, /* 31 */
					{ "서", { 0xbcad, }, { 0xace1, }, 1 }, /* 32 */
					{ "소", { 0xbcd2, }, { 0xada1, }, 1 }, /* 33 */
					{ "스", { 0xbdba, }, { 0xaf61, }, 1 }, /* 34 */
					{ "써", { 0xbde1, }, { 0xb0e1, }, 1 }, /* 35 */
					{ "쏘", { 0xbdee, }, { 0xb1a1, }, 1 }, /* 36 */
					{ "쓰", { 0xbeb2, }, { 0xb361, }, 1 }, /* 37 */
					{ "아", { 0xbec6, }, { 0xb461, }, 1 }, /* 38 */
					{ "어", { 0xbeee, }, { 0xb4e1, }, 1 }, /* 39 */
					{ "여", { 0xbfa9, }, { 0xb561, }, 1 }, /* 40 */
					{ "우", { 0xbfec, }, { 0xb681, }, 1 }, /* 41 */
					{ "으", { 0xc0b8, }, { 0xb761, }, 1 }, /* 42 */
					{ "이", { 0xc0cc, }, { 0xb7a1, }, 1 }, /* 43 */
					{ "저", { 0xc0fa, }, { 0xb8e1, }, 1 }, /* 44 */
					{ "조", { 0xc1b6, }, { 0xb9a1, }, 1 }, /* 45 */
					{ "주", { 0xc1d6, }, { 0xba81, }, 1 }, /* 46 */
					{ "쩌", { 0xc2bc, }, { 0xbce1, }, 1 }, /* 47 */
					{ "크", { 0xc5a9, }, { 0xc761, }, 1 }, /* 48 */
					{ "터", { 0xc5cd, }, { 0xc8e1, }, 1 }, /* 49 */
					{ "트", { 0xc6ae, }, { 0xcb61, }, 1 }, /* 50 */
					{ "파", { 0xc6c4, }, { 0xcc61, }, 1 }, /* 51 */
					{ "푸", { 0xc7aa, }, { 0xce81, }, 1 }, /* 52 */
					{ "허", { 0xc7e3, }, { 0xd0e1, }, 1 }, /* 53 */
};

L_PATTERN B_Bul_Last_Char[] = {
					{ "가", { 0xb0a1, }, { 0x8861, }, 1 }, /* 0 */
					{ "거", { 0xb0c5, }, { 0x88e1, }, 1 }, /* 1 */
					{ "겨", { 0xb0dc, }, { 0x8961, }, 1 }, /* 2 */
					{ "고", { 0xb0ed, }, { 0x89a1, }, 1 }, /* 3 */
					{ "구", { 0xb1b8, }, { 0x8a81, }, 1 }, /* 4 */
					{ "기", { 0xb1e2, }, { 0x8ba1, }, 1 }, /* 5 */
					{ "까", { 0xb1ee, }, { 0x8c61, }, 1 }, /* 6 */
					{ "꺼", { 0xb2a8, }, { 0x8ce1, }, 1 }, /* 7 */
					{ "꼬", { 0xb2bf, }, { 0x8da1, }, 1 }, /* 8 */
					{ "나", { 0xb3aa, }, { 0x9061, }, 1 }, /* 9 */
					{ "내", { 0xb3bb, }, { 0x9081, }, 1 }, /* 10 */
					{ "누", { 0xb4a9, }, { 0x9281, }, 1 }, /* 11 */
					{ "다", { 0xb4d9, }, { 0x9461, }, 1 }, /* 12 */
					{ "더", { 0xb4f5, }, { 0x94e1, }, 1 }, /* 13 */
					{ "도", { 0xb5b5, }, { 0x95a1, }, 1 }, /* 14 */
					{ "두", { 0xb5ce, }, { 0x9681, }, 1 }, /* 15 */
					{ "따", { 0xb5fb, }, { 0x9861, }, 1 }, /* 16 */
					{ "떠", { 0xb6b0, }, { 0x98e1, }, 1 }, /* 17 */
					{ "라", { 0xb6f3, }, { 0x9c61, }, 1 }, /* 18 */
					{ "러", { 0xb7af, }, { 0x9ce1, }, 1 }, /* 19 */
					{ "려", { 0xb7c1, }, { 0x9d61, }, 1 }, /* 20 */
					{ "로", { 0xb7ce, }, { 0x9da1, }, 1 }, /* 21 */
					{ "리", { 0xb8ae, }, { 0x9fa1, }, 1 }, /* 22 */
					{ "마", { 0xb8b6, }, { 0xa061, }, 1 }, /* 23 */
					{ "매", { 0xb8c5, }, { 0xa081, }, 1 }, /* 24 */
					{ "미", { 0xb9cc, }, { 0xa3a1, }, 1 }, /* 25 */
					{ "벼", { 0xbaad, }, { 0xa561, }, 1 }, /* 26 */
					{ "뵈", { 0xbac6, }, { 0xa641, }, 1 }, /* 27 */
					{ "사", { 0xbbe7, }, { 0xac61, }, 1 }, /* 28 */
					{ "서", { 0xbcad, }, { 0xace1, }, 1 }, /* 29 */
					{ "쉬", { 0xbdac, }, { 0xaee1, }, 1 }, /* 30 */
					{ "스", { 0xbdba, }, { 0xaf61, }, 1 }, /* 31 */
					{ "쑤", { 0xbea5, }, { 0xb281, }, 1 }, /* 32 */
					{ "여", { 0xbfa9, }, { 0xb561, }, 1 }, /* 33 */
					{ "오", { 0xbfc0, }, { 0xb5a1, }, 1 }, /* 34 */
					{ "자", { 0xc0da, }, { 0xb861, }, 1 }, /* 35 */
					{ "저", { 0xc0fa, }, { 0xb8e1, }, 1 }, /* 36 */
					{ "주", { 0xc1d6, }, { 0xba81, }, 1 }, /* 37 */
					{ "짜", { 0xc2a5, }, { 0xbc61, }, 1 }, /* 38 */
					{ "쩌", { 0xc2bc, }, { 0xbce1, }, 1 }, /* 39 */
					{ "쭈", { 0xc2de, }, { 0xbe81, }, 1 }, /* 40 */
					{ "추", { 0xc3df, }, { 0xc281, }, 1 }, /* 41 */
					{ "타", { 0xc5b8, }, { 0xc861, }, 1 }, /* 42 */
					{ "터", { 0xc5cd, }, { 0xc8e1, }, 1 }, /* 43 */
					{ "호", { 0xc8a3, }, { 0xd1a1, }, 1 }, /* 44 */
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
 * 미등록어 형태소 해석...
 * 바로 ma_result에 저장된다.
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
	/* 중요한 버그 발견 Prob을 초기화 시켜야 한다. */
	Prob[0].P = (double) 0.0;
	ReverseWord(rev_h_word, h_word, h_word_len);
	h_idx = GetTailHeaderIndex(rev_h_word[0].j_code);
/*
	if (h_idx == -1)
		goto SKIP_VA_CHECK;
*/
	/*
	 * 체언형 형식형태소 사전 탐색...
	 */
	//printf("h_idx:%d\n",h_idx);
	ret_val = SearchTAILDic(rev_h_word, h_word_len, h_idx, tail_dic_result, &dic_res_idx, NTAIL_MODE);
	//printf("SearchTAILDi:%d\n",ret_val);

	if (ret_val && tail_dic_result[dic_res_idx-1].len < h_word_len) {
			//printf("dic_res_idx:%d\n",dic_res_idx);
		for (i = dic_res_idx-1; i >= 0; i--) {
			//printf("dic_res_idx [%d]\n",i);
			/* 체언형 실질-형식형태소 경계 바이그램 검색 */
			memcpy(BoundaryChars, &rev_h_word[tail_dic_result[i].len-1], sizeof(HANGUL) * 2);
			h_idx = GetTailHeaderIndex(BoundaryChars[0].j_code);

			ret_val = SearchTAILDic(BoundaryChars, 2, h_idx, bnd_dic_result, &bdic_res_idx, BTAIL_MODE);
			/* 일단 없으면 무조건 SKIP 한다... */
			/* 아니다... 확률값이 0으로 지정되고 계속 수행한다. */
			/*
			if (ret_val == 0)
				continue;
			*/
			if (ret_val != 0) {
				/* 경계 바이그램 빈도 */
				GetTAILContent(bnd_dic_result[0].InfoStart, bnd_dic_result[0].InfoLen, MARContent_org, BTAIL_MODE);
				ptr = strtok(MARContent_org, "&");
				ptr = strtok(NULL, "&");

				freq_btail = atoi(ptr);
			} else
				freq_btail = 0;

			/* 체언형 형식형태소 빈도 */
			GetTAILContent(tail_dic_result[i].InfoStart, tail_dic_result[i].InfoLen, MARContent_org, NTAIL_MODE);
			ptr = strtok(MARContent_org, "&");
			//printf("MARContent_org%s\n",MARContent_org);
			strcpy(MARContent, ptr);
			ptr = strtok(NULL, "&");

			freq_ntail = atoi(ptr);

			/* 
			 * 확률값 계산 
			 * 매개변수 : 경계 바이그램 확률, 형식형태소 출현확률, 형식형태소 길이, 형식형태소의 형태소 개수
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

		/* 확률이 큰 순서대로 정렬 */
		qsort (Prob, Prob_idx, sizeof(TAIL_PROB), compare_prob);
		/* 확률이 가장 높은 2가지 결과를 출력 */
		for (i = 0; i < Prob_idx; i++) {
			if (i >= 2)
				break;
			for (j = Prob[i].from; j <= Prob[i].to; j++) {
			//	printf("%d\n",morp_result.MorpRes_num);
		//		memcpy(&(ma_result->IMR[ma_result->MARes_num]), &(local_ma_res.IMR[j]), sizeof(ITF_MORP_RESULT));
		//2006.06.12 by mini 미등록어 조합형 형태소 분석 저장 
				memcpy(&(morp_result.UK_MorpResult[morp_result.MorpRes_num]), &(local_morp_res.UK_MorpResult[j]), sizeof(tMORP_RESULT));
		//		printf("MA:memcpy:%d nMorp:%d %s\n",ma_result->MARes_num,ma_result->IMR[0].nMorp,ma_result->IMR[0].MI[0].info);	
				//printf("MORP:memcpy:%d nMorp:%d %s\n",morp_result.MorpRes_num,morp_result.UK_MorpResult[j].nMorp,morp_result.UK_MorpResult[j].MI[0].info);
				//printf("MORP:memcpy:%d nMorp:%d %s\n",morp_result.MorpRes_num,morp_result.UK_MorpResult[j].nMorp,morp_result.UK_MorpResult[j].MI[1].info);
		//		ma_result->MARes_num++;
				morp_result.MorpRes_num++;
			}
		}
	}

	/* 가장 높은 확률값이 임계값을 넘을 때는 용언검사를 하지 않는다... */
	if (is_HanJa || is_DiGit || Prob[0].P > THRESH_NOUN_UK)
		goto SKIP_VA_CHECK;
	/*
	 * 용언형 형식형태소 사전 탐색...
	 */
	ret_val = SearchTAILDic(rev_h_word, h_word_len, h_idx, tail_dic_result, &dic_res_idx, PTAIL_MODE);
	//printf("PTAIL_MODE ret_val:%d\n",ret_val);
	//printf(" tail_dic_result[dic_res_idx-1].len:%d dic_res_idx:%d\n", tail_dic_result[dic_res_idx-1].len,dic_res_idx);
	if (ret_val && tail_dic_result[dic_res_idx-1].len < h_word_len) {
		for (i = dic_res_idx-1; i >= 0; i--) {
			/* 용언형 형식형태소 빈도 */
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

	/* 수정 무조건 전체 어절을 하나의 색인어로 잡음 2002-08-30 */
	/*
	if (ma_result->MARes_num)
		return 1;
	*/

	/* 형식형태소가 존재하지 않는 어절은 그 자체가 하나의 체언형 미등록어이다... */
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
        	while (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) != (UWORD)0) {    // 조합형 --> 완성형 변환 
        		if (M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) >= 0x8442 &&
            	M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k) <= 0xd3b7) { // 조합형 한글이면 
            	one_han.code = jo2wan[M_MORPRESULT_MI_MORPHEME_ITEM(i, j, k)-0x8442][1];
            	han_str[index++] = one_han.hl.high;
            	han_str[index++] = one_han.hl.low;
        	} else {       // 한글이 아닌 아스키 코드 이면 
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
 * 분석 모드에 따른 형태소 분석 결과를 저장한다.
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
		 * 체언형 형식형태소 저장...
		 */
		ConvertJo2Wan(h_word, h_word_len - t_dic_res.len, WanStr);
		//printf("h_word_len:%d\n",h_word_len);
		ptr = strtok(MARContent, "_");
		while (ptr != NULL) {
			MorpCnt = ParseMorpStr(ptr, Morps);
			nMorp = 0;
			//printf("MorpCnt:%d",MorpCnt);
			/* 조사 검사 */
			if (Morps[0].Tag[0] == 'j')
				if (!CheckJosa(h_word, h_word_len - t_dic_res.len, 0))
					return 0;

			/* 휴리스틱스 규칙 검사 */
			/* 조사의 첫음절이 될 수 없은 음절 */
			if (h_word[h_word_len-t_dic_res.len].j_code == 0xace1/*서*/
					||h_word[h_word_len-t_dic_res.len].j_code == 0x89a1/*고*/
					||h_word[h_word_len-t_dic_res.len].j_code == 0x9c61/*라*/)
				return 0;

			/* 휴리스틱스 규칙 검사 */
			/* 체언의 마지막 음절이 될 수 없는 음절 */
			if (h_word[h_word_len-t_dic_res.len-1].j_code == 0xb761/*으*/
					||h_word[h_word_len-t_dic_res.len-1].j_code == 0xa361/*므*/
					||h_word[h_word_len-t_dic_res.len-1].j_code == 0x99a1/*또*/)
				return 0;

			/* 휴리스틱스 규칙 검사 */
			/* 3자 이상되는 어절의 가장 마지막에 붙은 '다'는 '이다'로 분석하지 않는다. */
			if (t_dic_res.len == 1 && h_word[h_word_len-1].j_code == 0x9461/*다*/
					&& h_word_len >= 4) {
				return 0;
			}

			/*
			 * 실질형태소 저장...완성형
			 
			strcpy(ma_res->IMR[MARes_num].MI[nMorp].Morpheme, WanStr);
			strcpy(ma_res->IMR[MARes_num].MI[nMorp].info, UNKNOWN_NOUNS);
			nMorp++;	
			
			 * 형식형태소 저장...완성형
			 
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
			//실질 형태소 저장.... 조합형
			for (i=0;i<h_word_len-t_dic_res.len;i++){
                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
            }
            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,UNKNOWN_NOUNS);
			morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
            nMorp2++;
			/*
			 * 형식형태소 저장...조합형
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
		 * 용언형 형식형태소 저장
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
			/* 용언과 형식형태소 분리 */
			/* 1자 짜리 형식형태소는 일단 처리를 하지 않는다. */
			if (t_dic_res.len > 1) {
				//printf("%d %d\n",HanTail[1].j_code,FirstMorpItem[0].j_code);
				if (HanTail[1].j_code == FirstMorpItem[0].j_code) {
					/* 형식형태소가 변형되지 않았을 때... */
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
					   
		            //실질 형태소 저장.... 조합형
        		    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
              			  morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
           			 }
           			 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
         			 strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
            	     nMorp2++;
    		        /*
    		         * 형식형태소 저장...조합형
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
						/* 어/아/었/았 */
						/* 불규칙 여부 검사 */
						if (is_S_bul(HanTail[0].j_code)) {
							memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
							tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x15; /* ㅅ */

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
							//실질 형태소 저장.... 조합형
		                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
        	                 	 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
            		        }
                   			morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                    		strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
							morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                    		nMorp2++;
							/*
		                     * 형식형태소 저장...조합형
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
							tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x08; /* ㄷ */

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
                            //실질 형태소 저장.... 조합형
                            for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                                 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
							morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                            nMorp2++;
                            /*
                             * 형식형태소 저장...조합형
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

					/* ㄹ 탈락 활용형태 복원 */
					if (FirstMorpItem[0].j_han.cho == 0x04 && is_R_bul(HanTail[0].j_code)) {
						memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
						tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x09; /* ㄹ */

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
                            //실질 형태소 저장.... 조합형
                            for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                                 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                            }
                            morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                            strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
							morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                            nMorp2++;
                            /*
                             * 형식형태소 저장...조합형
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
					/* 와 --> 오+아 */
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
                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){//h_word->tmp_h_word
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                     }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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
					/* 워 --> 우+어 */
		
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
                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){//h_word->tmp_h_word
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                     }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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
					/* 여 --> 이+어 */
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x1D;
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x01;

				/*	ConvertJo2Wan(tmp_h_word, h_word_len-t_dic_res.len+1, WanStr);
					//완성형 스트링 변환 
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
   					//실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){//h_word->tmp_h_word
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                     }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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
					/* 왜 --> 외+어 */
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

                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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

				if (FirstMorpItem[0].j_code == 0x8445  /* ㄴ */
						|| FirstMorpItem[0].j_code == 0x8449  /* ㄹ */
						|| FirstMorpItem[0].j_code == 0x8451  /* ㅁ */
						|| FirstMorpItem[0].j_code == 0x8453) { /* ㅂ */
					if (HanTail[0].j_han.cho == 0x0D && HanTail[0].j_han.jung == 0x1B
							&& HanTail[0].j_han.jong != 0x01) { /* 으 */
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
		
        	            //실질 형태소 저장.... 조합형
            	        for (i=0;i<h_word_len-t_dic_res.len;i++){
                	         morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
                   		 }
                    	morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                   	    strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
						morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     	nMorp2++;
                    	/*
                     	* 형식형태소 저장...조합형 
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
        
                        //실질 형태소 저장.... 조합형
                        for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                             morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                         }
                        morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                        strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
						morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                        nMorp2++;
                        /*
                        * 형식형태소 저장...조합형 
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

				/* 해 --> 하어, 했 --> 하었 */
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

                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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
				if ((HanTail[0].j_code == 0xcce1/*퍼*/ && FirstMorpItem[0].j_code == 0xb4e1/*어*/)
						||(HanTail[0].j_code == 0xccf6/*펐*/ && FirstMorpItem[0].j_code == 0xb4f6/*었*/)) {
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x14;/*ㅜ*/
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

                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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

				/* 으 불규칙 */
				tmp_h_word[0].j_code = HanTail[0].j_code;
				tmp_h_word[0].j_han.jong = 0x01;
				if (is_EU_bul(tmp_h_word[0].j_code)) {
					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jung = 0x1B;/*ㅡ*/
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

                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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

				/* ㅂ 불규칙 */
				if (is_B_bul(HanTail[0].j_code)) {
					if ((HanTail[1].j_code == 0xb5c1 || HanTail[1].j_code == 0xb5d6) /* 와,왔 */
							&& (HanTail[0].j_han.jung == 0x0D || HanTail[0].j_han.jung == 0x03) /* ㅗ,ㅏ */
							&& (FirstMorpItem[0].j_code == 0xb461 || FirstMorpItem[0].j_code == 0xb476)) { /* 아,았 */
						;
					} else if ((HanTail[1].j_code == 0xb6a1 || HanTail[1].j_code == 0xb6b6) /* 워,웠 */
							&& (HanTail[0].j_han.jung == 0x0D || HanTail[0].j_han.jung == 0x03 ||
								HanTail[0].j_han.jung == 0x14 || HanTail[0].j_han.jung == 0x07) /* ㅗ,ㅏ,ㅜ,ㅓ */
							&& (FirstMorpItem[0].j_code == 0xb4e1 || FirstMorpItem[0].j_code == 0xb4f6)) { /* 어,었 */
						;
					} else if (HanTail[1].j_code == 0xb685 || HanTail[1].j_code == 0xb689
							|| HanTail[1].j_code == 0xb681 || HanTail[1].j_code == 0xb5a1) { /* 운,울,우,오 */
						;
					} else {
						ptr = strtok(NULL, "_");
						continue;
					}

					memcpy(tmp_h_word, h_word, sizeof(HANGUL) * (h_word_len - t_dic_res.len + 1));
					tmp_h_word[h_word_len-t_dic_res.len].j_han.jong = 0x13;/*ㅂ*/

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

                    //실질 형태소 저장.... 조합형
                    for (i=0;i<h_word_len-t_dic_res.len+1;i++){
                          morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=tmp_h_word[i].j_code;
                    }
                     morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                     strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
					 morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
                     nMorp2++;
                    /*
                     * 형식형태소 저장...조합형
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

                //실질 형태소 저장.... 조합형
                for (i=0;i<h_word_len-t_dic_res.len+1;i++){
            	    morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]=h_word[i].j_code;
                }
                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].Morpheme[i]='\0';
                strcpy(morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].info,va_pos);
                morp_res->UK_MorpResult[MorpRes_num].MI[nMorp2].ninfo=1;
				nMorp2++;
                /*
                 * 형식형태소 저장...조합형
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

/* 으 불규칙 마지막 음절 테스트 */
/* 가거꺼나너떠라러빠뻐써아커터파퍼 */
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

/* ㅅ 불규칙 마지막 음절 테스트 */
/*그끄나무부이자저지*/
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

/* ㄹ 불규칙 마지막 음절 테스트 */
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

/* ㄷ 불규칙 마지막 음절 테스트 */
/* 걸결길눌달들물불실컬 */
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
 * 조합형을 완성형으로...
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
 * 완성형을 조합형으로...
 * 무조건 완성형 한글이 입력되어야 함.
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
				/* 완성형 글자 */
				c_idx = (h_char.hl.high - 0xB0) * 94;
				c_idx += h_char.hl.low - 0xA1;
				j_str[j_idx++].j_code = conv_tbl[c_idx][1];
			} else if ((h_char.hl.high == 0xA4) && (0xA1 <= h_char.hl.low && h_char.hl.low <= 0xD3)) {
				/* 완성형 자소 */
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
 * 형식형태소 형태소 스트링을 내부 포멧으로 변환...
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

