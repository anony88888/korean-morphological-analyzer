/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_CompoundNoun.c)#  SPASIS System,     2000.02.21
 *
 *	#(Action)#
 *		- 복합명사 분석 모듈
 *        사전 정보에 따른 어절 분석 route 설정...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_Func.h>
#include <MA_Jubmi.h>
#include <MADIC_Type.h>
#include <MADIC_DicInfo.h>
#include <MADIC_Func.h>
#include <MA_Jo2Wan.h>

#include <boost/scoped_array.hpp>

#define MAX_CN_RESULT		50 /* 복합명사 분석에서 나오는 형태소 분석 결과는 최대 50개 */

/*
DWORD comp_time;
*/
/* 복합명사 처리루틴 */
/* 루틴의 개념은 기본적으로 재귀적호출이다... */
/* 이것을 스택으로 처리한다 */
/* 속도저하가 문제될 것 같다 */
/* info : 이전에 사전 탐색에 성공한 체언의 세부 사전 정보 */
/* 여기에는 무조건 조합형 한글만 들어와야 한다. */
DWORD CheckCompNoun(HANGUL *h_word, UWORD h_word_len, HANGUL pre_char, UWORD info)
{
	DWORD i, j, k,l;
	//DWORD chk_93_info_idx;
	UWORD h_idx;
	DWORD ret_val, new_idx;
	DWORD cnt;
	DWORD DAdj[100][20];
	tSTACK comp_stack[100];
	//tSTACK Ns93_stack[100];
	//DWORD Ns93_idx;
	DWORD cs_idx;
	DWORD vert_idx, cur_node, cur_level;
	DWORD pre_Morpheme_Index, pre_MorpResult_Index, pre_CUR_MAR_ITEMS;
	DWORD old_Morpheme_Index, old_CUR_MAR_ITEMS;
	HANGUL tmpHan, tmp_h_word[VS_BUFLEN];
	UWORD cur_char_pos, sub_idx, chk_jong;
	UWORD chk_33_info, chk_34_info;
	//DWORD add_level;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT jdic_result[VS_BUFLEN];
#else
	DIC_RESULT jdic_result[VS_BUFLEN];
#endif
	UWORD jdic_res_idx = 0;
#ifdef MULTI_DIC_INFO
	UWORD info_cnt;
	UWORD fdr_info_cnt;
#endif
	UWORD jubmi_flag;
	BYTE temp_info[VS_BUFLEN];
	DWORD t_idx, tmp_val;


	DIC_RESULT DRES[DIC_RESULT_NUM];
	UWORD DRES_idx = 0;
	struct F_DRES_t {
	     CDIC_RESULT dic_result[DIC_RESULT_NUM];
	     UWORD dic_res_idx;
	};
	boost::scoped_array<F_DRES_t>  F_DRES( new F_DRES_t[50] );
	DWORD fdr_idx = 0;
	struct VERTEX_t {
	     CDIC_RESULT dic_result;
	     UWORD start_idx;
	};
	boost::scoped_array<VERTEX_t> VERTEX( new VERTEX_t[100] );
	DWORD vt_idx = 0;

	/*
	DWORD val1, val2;
	*/
	/* 복합명사처리부는 20자 이상은 처리 못한다.... */

	if (h_word[0].j_han.sign == 0)
	    return 0;

	h_idx = jo2wan[h_word[0].j_code - 0x8442][2];
	ret_val = SearchDic(h_word, h_word_len, h_idx, DRES, &DRES_idx);

	if (h_word_len == 2 && DRES[DRES_idx-1].len != 2)
		return 0;

	fdr_idx = vt_idx = 0;

	/*
	for (i = 0; i < 50; i++) {
		F_DRES[i].dic_res_idx = 0;
		DAdj[i][0] = -1;
		memset(F_DRES[i].dic_result, 0, sizeof(CDIC_RESULT) * DIC_RESULT_NUM);
		VERTEX[i].start_idx = 60000;
	}
	val1 = clock();
	*/
	cnt = 0;
	F_DRES[fdr_idx].dic_result[0].ninfo = 0;
	for (i = DRES_idx-1; i >= 0; i--) {
	//	if(DRES[i].info[0] == 93)
	//		chk_93_info=1;
	//	else 
	//		chk_93_info=0;
	//	for(chk_93_info_idx= 0 ;chk_93_info_idx <= chk_93_info ; chk_93_info_idx++){
		if (DRES[i].len < 2)
			break;
#ifdef MULTI_DIC_INFO
		if (IS_NOUN(DRES[i].info[0])) {
			info_cnt = 0;
			fdr_info_cnt = 0;
			while (1) {
				if (DRES[i].info[info_cnt] == 0)
					break;
				if (DRES[i].info[info_cnt] != 31 && DRES[i].info[info_cnt] != 32 && DRES[i].info[info_cnt] != 33 && DRES[i].info[info_cnt] != 34
					&& DRES[i].info[info_cnt] != 35 && DRES[i].info[info_cnt] != 39 && DRES[i].info[info_cnt] != 40 &&
					DRES[i].info[info_cnt] != 90&&DRES[i].info[info_cnt] != 91&&DRES[i].info[info_cnt] != 92&&DRES[i].info[info_cnt] != 93&&DRES[i].info[info_cnt] != 94) {// by mini(2005.08.30)
					info_cnt++;
					continue;
				}
				
					F_DRES[fdr_idx].dic_result[cnt].info[fdr_info_cnt++] = DRES[i].info[info_cnt];
				
				info_cnt++;
			}

			/* 얼마만큼은 --> 이상하게 분석되는 오류 수정 */
			if (fdr_info_cnt == 0)
				continue;
		
			F_DRES[fdr_idx].dic_result[cnt].ninfo = fdr_info_cnt;
			F_DRES[fdr_idx].dic_result[cnt].jong = DRES[i].jong;
			F_DRES[fdr_idx].dic_result[cnt].len = DRES[i].len;
			F_DRES[fdr_idx].dic_result[cnt].idx = vt_idx;
			VERTEX[vt_idx].start_idx = fdr_idx;
			VERTEX[vt_idx].dic_result = F_DRES[fdr_idx].dic_result[cnt];
			cnt++;
			vt_idx++;
		}
#else
		switch (DRES[i].info) {
		case 32:
		case 33:
		case 34:
		case 35:
		case 39:
		case 40:
		case 90:
		case 91:
		case 92:
		case 93:
		case 94:
			if (cnt > 0 
				&& F_DRES[fdr_idx].dic_result[cnt-1].len == DRES[i].len 
				&& F_DRES[fdr_idx].dic_result[cnt-1].jong == DRES[i].jong) {
				F_DRES[fdr_idx].dic_result[cnt-1].info[F_DRES[fdr_idx].dic_result[cnt-1].ninfo] = 
					DRES[i].info;
				F_DRES[fdr_idx].dic_result[cnt-1].ninfo++;
				VERTEX[vt_idx-1].dic_result.info[VERTEX[vt_idx-1].dic_result.ninfo] = DRES[i].info;
				VERTEX[vt_idx-1].dic_result.ninfo++;
			} else {
				F_DRES[fdr_idx].dic_result[cnt].info[F_DRES[fdr_idx].dic_result[cnt].ninfo] = 
					DRES[i].info;
				F_DRES[fdr_idx].dic_result[cnt].ninfo++;
				F_DRES[fdr_idx].dic_result[cnt].jong = DRES[i].jong;
				F_DRES[fdr_idx].dic_result[cnt].len = DRES[i].len;
				F_DRES[fdr_idx].dic_result[cnt].idx = vt_idx;
				VERTEX[vt_idx].start_idx = fdr_idx;
				VERTEX[vt_idx].dic_result = F_DRES[fdr_idx].dic_result[cnt];
				cnt++;
				F_DRES[fdr_idx].dic_result[cnt].ninfo = 0;
				vt_idx++;
			}
			break;
		}
#endif
	}
//	}
	F_DRES[fdr_idx].dic_res_idx = cnt;

	/* 두번째 위치와 마지막 위치에서 사전 탐색을 안하는 이유는...
	   복합명사는 무조건 2자 이상으로 구성되어야 하기 때문이다...*/
	fdr_idx = 2;
	for (i = 2; i < h_word_len-1; i++) {
	    	if (h_word[i].j_han.sign == 1) {
		    h_idx = jo2wan[h_word[i].j_code - 0x8442][2];
		    ret_val = SearchDic(&h_word[i], (UWORD) (h_word_len - i), h_idx, DRES, &DRES_idx);
		} else 
		    DRES_idx = 0;
		cnt = 0;
		F_DRES[fdr_idx].dic_result[cnt].ninfo = 0;
		for (j = DRES_idx-1; j >= 0; j--) {
			if (DRES[j].len < 2)
				break;
#ifdef MULTI_DIC_INFO
			if (IS_NOUN(DRES[j].info[0])) {
				info_cnt = 0;
				fdr_info_cnt = 0;
				while (1) {
					if (DRES[j].info[info_cnt] == 0)
						break;
					if (DRES[j].info[info_cnt] != 31 && DRES[j].info[info_cnt] != 32 && DRES[j].info[info_cnt] != 33 && DRES[j].info[info_cnt] != 34
						&& DRES[j].info[info_cnt] != 35 && DRES[j].info[info_cnt] != 39 && DRES[j].info[info_cnt] != 40 &&
						DRES[j].info[info_cnt] != 90&&DRES[j].info[info_cnt] != 91&&DRES[j].info[info_cnt] != 92&&DRES[j].info[info_cnt] != 93&&DRES[j].info[info_cnt] != 94) {// by mini(2005.08.30)

						info_cnt++;
						continue;
					}
					F_DRES[fdr_idx].dic_result[cnt].info[fdr_info_cnt++] = DRES[j].info[info_cnt];
					info_cnt++;
				}

				/* 얼마만큼은 --> 이상하게 분석되는 오류 수정 */
				if (fdr_info_cnt == 0)
					continue;
			
				F_DRES[fdr_idx].dic_result[cnt].ninfo = fdr_info_cnt;
				F_DRES[fdr_idx].dic_result[cnt].jong = DRES[j].jong;
				F_DRES[fdr_idx].dic_result[cnt].len = DRES[j].len;
				F_DRES[fdr_idx].dic_result[cnt].idx = vt_idx;
				VERTEX[vt_idx].start_idx = fdr_idx;
				VERTEX[vt_idx].dic_result = F_DRES[fdr_idx].dic_result[cnt];
				cnt++;
				vt_idx++;

			}
#else
			switch (DRES[j].info) {
			case 32:
			case 33:
			case 34:
			case 35:
			case 39:
			case 40:
		    case 90:
			case 91:
			case 92:
			case 93:
			case 94:
				if (cnt > 0 
					&& F_DRES[fdr_idx].dic_result[cnt-1].len == DRES[j].len 
					&& F_DRES[fdr_idx].dic_result[cnt-1].jong == DRES[j].jong) {
					F_DRES[fdr_idx].dic_result[cnt-1].info[F_DRES[fdr_idx].dic_result[cnt-1].ninfo] = 
						DRES[j].info;
					F_DRES[fdr_idx].dic_result[cnt-1].ninfo++;
					VERTEX[vt_idx-1].dic_result.info[VERTEX[vt_idx-1].dic_result.ninfo] = DRES[j].info;
					VERTEX[vt_idx-1].dic_result.ninfo++;
				} else {
					F_DRES[fdr_idx].dic_result[cnt].info[F_DRES[fdr_idx].dic_result[cnt].ninfo] = 
						DRES[j].info;
					F_DRES[fdr_idx].dic_result[cnt].ninfo++;
					F_DRES[fdr_idx].dic_result[cnt].jong = DRES[j].jong;
					F_DRES[fdr_idx].dic_result[cnt].len = DRES[j].len;
					F_DRES[fdr_idx].dic_result[cnt].idx = vt_idx;
					VERTEX[vt_idx].start_idx = fdr_idx;
					VERTEX[vt_idx].dic_result = F_DRES[fdr_idx].dic_result[cnt];
					cnt++;
					F_DRES[fdr_idx].dic_result[cnt].ninfo = 0;
					vt_idx++;
				}
				break;
			}
#endif
		}
		F_DRES[fdr_idx].dic_res_idx = cnt;
		fdr_idx++;
	}

	VERTEX[vt_idx].start_idx = 60000;
	if (h_word_len <= 2)
		F_DRES[2].dic_res_idx = 0;

	/* 사전 탐색 결과로 생성되는 명사 아이템 노드들을 Adjacency Graph로 구성 */
	for (i = 0; i < fdr_idx; i++) {
		if (i == 1)
			continue;
		for (j = 0; j < F_DRES[i].dic_res_idx; j++) {
			if ((F_DRES[i].dic_result[j].len + i < fdr_idx) && !F_DRES[i].dic_result[j].jong 
				&& F_DRES[F_DRES[i].dic_result[j].len + i].dic_res_idx > 0) {
				new_idx = F_DRES[i].dic_result[j].len + i;
				cnt = 0;
				for (k = 0; k < F_DRES[new_idx].dic_res_idx; k++)
					DAdj[F_DRES[i].dic_result[j].idx][cnt++] = F_DRES[new_idx].dic_result[k].idx;
				DAdj[F_DRES[i].dic_result[j].idx][cnt] = -1;
			} else
				DAdj[F_DRES[i].dic_result[j].idx][0] = -1;
		}
	}

	vert_idx = 0;

	pre_CUR_MAR_ITEMS = M_CUR_MORPRESULT_NMORP;//현재 어절의 현재까지 분석한 형태소 개수 
	pre_Morpheme_Index = M_MORPHEME_INDEX;
	pre_MorpResult_Index = M_MORPRESULT_INDEX;
	
	while (VERTEX[vert_idx].start_idx == 0) {
		cs_idx = 0;
		comp_stack[cs_idx].node = vert_idx;
		comp_stack[cs_idx].level = 0;
		
		while (cs_idx != -1) {

			cur_node = comp_stack[cs_idx].node;
			cur_level = comp_stack[cs_idx].level;
			cs_idx--;
			// by mini(2005.08.30)
		
			

			M_CUR_MORPRESULT_NMORP = pre_CUR_MAR_ITEMS + cur_level + 1;
			M_MORPHEME_INDEX = pre_Morpheme_Index + cur_level;

			if (VERTEX[cur_node].dic_result.jong) {
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[VERTEX[cur_node].start_idx], 
							sizeof(HANGUL) * (VERTEX[cur_node].dic_result.len-1));
				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = h_word[VERTEX[cur_node].start_idx+VERTEX[cur_node].dic_result.len-1].j_han.cho;
				tmpHan.j_han.jung = h_word[VERTEX[cur_node].start_idx+VERTEX[cur_node].dic_result.len-1].j_han.jung;
				tmpHan.j_han.jong = 1;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(VERTEX[cur_node].dic_result.len-1) = tmpHan.j_code;
			} 
			else{
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[VERTEX[cur_node].start_idx], 
					sizeof(HANGUL) * VERTEX[cur_node].dic_result.len);
			}
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(VERTEX[cur_node].dic_result.len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = VERTEX[cur_node].dic_result.ninfo;
			for (i = 0; i < VERTEX[cur_node].dic_result.ninfo; i++)
				M_CUR_MORPRESULT_MI_INFO_ITEM(i) = VERTEX[cur_node].dic_result.info[i];
			M_CUR_MORPRESULT_MI_INFO_ITEM(i) = 0;

			M_MORPHEME_INDEX = pre_Morpheme_Index + cur_level + 1;
			
			l=	M_MORPHEME_INDEX;
		
			//
			cnt = 0;
			
			while (DAdj[cur_node][cnt] != -1) {
				cs_idx++;
				comp_stack[cs_idx].node = DAdj[cur_node][cnt];
				comp_stack[cs_idx].level = cur_level + 1;
				cnt++;
			}
		//	printf("M_MORPHEME_INDEX:%d\n",M_MORPHEME_INDEX);
			//if(DAdj[cur_node][cnt] == -1)
			//	add_level=0;
			/* 사전에서 FULL로 검사되었을 경우 */
			if ((VERTEX[cur_node].start_idx + VERTEX[cur_node].dic_result.len) == h_word_len 
				&& VERTEX[cur_node].dic_result.jong == 0) {
				M_MORPRESULT_INDEX++;
		//		printf("M_MORPRESULT_INDEX:%d\n",M_MORPRESULT_INDEX);
				memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
				
				
	
				if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
					goto LOOP_OUT;
				continue;
			}
			
			cur_char_pos = VERTEX[cur_node].start_idx + VERTEX[cur_node].dic_result.len;

			/**********************************************************************************/
			/* 접미사 처리를 한다...(따로 함수를 만들지 않는다...(속도 때매)...               */
			jubmi_flag = 0;
			if (VERTEX[cur_node].dic_result.jong == 0) {
				for (k = 0; k < JUBMI_NUM; k++) {
					if (h_word[cur_char_pos].j_code == JUBMI[k])
						break;
				}
				if (k < JUBMI_NUM) {
					/* 접미사가 포함된 단어가 사전에 존재하면 SKIP */
					i = 0;
					while (VERTEX[i].start_idx != 60000) {
						if (VERTEX[i].start_idx == VERTEX[cur_node].start_idx &&
							VERTEX[i].dic_result.len == VERTEX[cur_node].dic_result.len + 1 &&
							!VERTEX[i].dic_result.jong)
							break;
						i++;
					}
					if (VERTEX[i].start_idx == 60000) {
						jubmi_flag = 1;
						old_Morpheme_Index = M_MORPHEME_INDEX;
						old_CUR_MAR_ITEMS = M_CUR_MORPRESULT_NMORP;
						M_CUR_MORPRESULT_NMORP++;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = h_word[cur_char_pos].j_code;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
						M_CUR_MORPRESULT_MI_NINFO = 1;
						strcpy(M_CUR_MORPRESULT_MI_INFO, "JUBMISA");
						M_MORPHEME_INDEX++;

						cur_char_pos++;
						if (cur_char_pos == h_word_len) {
							if (h_word[cur_char_pos-1].j_code == 0x89C1/*과*/) {
								M_MORPHEME_INDEX--;
								strcat(M_CUR_MORPRESULT_MI_INFO, " J25");
								M_MORPHEME_INDEX++;
							} else if (h_word[cur_char_pos-1].j_code == 0xAA85/*뿐*/) {
								M_MORPHEME_INDEX--;
								strcat(M_CUR_MORPRESULT_MI_INFO, " J6");
								M_MORPHEME_INDEX++;
							}
							M_MORPHEME_INDEX = 0;
							M_MORPRESULT_INDEX++;
							memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
							if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
								break;
							continue;
						} else if (cur_char_pos+1 == h_word_len &&
								h_word[cur_char_pos-1].j_code == 0xAA85/*뿐*/ &&
								h_word[cur_char_pos].j_code == 0xA065/*만*/) {
							M_MORPHEME_INDEX--;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = h_word[cur_char_pos].j_code;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
							strcpy(M_CUR_MORPRESULT_MI_INFO, "J6");
							M_MORPHEME_INDEX++;

							M_MORPHEME_INDEX = 0;
							M_MORPRESULT_INDEX++;
							memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
							if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
								goto LOOP_OUT;
							continue;
						}
					}
				}
			}
			/**********************************************************************************/

			/* '이다' 처리 */
			if (VERTEX[cur_node].dic_result.jong == 0) {
				if (h_word[cur_char_pos].j_han.cho == 0x0D && h_word[cur_char_pos].j_han.jung == 0x1D) {
					sub_idx = cur_char_pos - 1;
					chk_jong = VERTEX[cur_node].dic_result.jong;
					old_Morpheme_Index = M_MORPHEME_INDEX;
					old_CUR_MAR_ITEMS = M_CUR_MORPRESULT_NMORP;
					memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - cur_char_pos + 1));
					ret_val = CheckIda(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), chk_jong);
					if (ret_val == 1) {
						M_MORPRESULT_INDEX++;
						memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
						if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
							goto LOOP_OUT;
						continue;
					} else if (ret_val == 2)
						continue;
					M_MORPHEME_INDEX = old_Morpheme_Index;
					M_CUR_MORPRESULT_NMORP = old_CUR_MAR_ITEMS;
				} else if (h_word[cur_char_pos].j_code == 0x9461) {	/* 다 */
					if (h_word[cur_char_pos-1].j_han.jong == 0x01 && h_word_len == cur_char_pos + 1) {
						sub_idx = cur_char_pos - 1;
						chk_jong = VERTEX[cur_node].dic_result.jong;
						old_Morpheme_Index = M_MORPHEME_INDEX;
						old_CUR_MAR_ITEMS = M_CUR_MORPRESULT_NMORP;
						memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - cur_char_pos + 1));
						ret_val = CheckIda(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), chk_jong);
						if (ret_val == 1) {
							M_MORPRESULT_INDEX++;
							memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
							if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
								goto LOOP_OUT;
							continue;
						} else if (ret_val == 2)
							continue;
						M_MORPHEME_INDEX = old_Morpheme_Index;
						M_CUR_MORPRESULT_NMORP = old_CUR_MAR_ITEMS;
					}
				} else if (h_word[cur_char_pos].j_han.cho == 0x0D && h_word[cur_char_pos].j_han.jung == 0x0B) {	/* 여 */
					if (h_word[cur_char_pos-1].j_han.jong == 0x01 && h_word_len > cur_char_pos + 1) {
						sub_idx = cur_char_pos - 1;
						chk_jong = VERTEX[cur_node].dic_result.jong;
						old_Morpheme_Index = M_MORPHEME_INDEX;
						old_CUR_MAR_ITEMS = M_CUR_MORPRESULT_NMORP;
						memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - cur_char_pos + 1));
						ret_val = CheckIda(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), chk_jong);
						if (ret_val == 1) {
							M_MORPRESULT_INDEX++;
							memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
							if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
								goto LOOP_OUT;
							continue;
						} else if (ret_val == 2)
							continue;
						M_MORPHEME_INDEX = old_Morpheme_Index;
						M_CUR_MORPRESULT_NMORP = old_CUR_MAR_ITEMS;
					}
				}
			}

			if (VERTEX[cur_node].dic_result.jong == 0) {
				sub_idx = cur_char_pos - 1;
				chk_jong = VERTEX[cur_node].dic_result.jong;
				old_Morpheme_Index = M_MORPHEME_INDEX;
				old_CUR_MAR_ITEMS = M_CUR_MORPRESULT_NMORP;
				memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - cur_char_pos + 1));
				chk_33_info = chk_34_info = 0;
				for (i = 0; i < VERTEX[cur_node].dic_result.ninfo; i++) {
					if (VERTEX[cur_node].dic_result.info[i] == 33)
						chk_33_info = 1;
					else if (VERTEX[cur_node].dic_result.info[i] == 34)
						chk_34_info = 1;
				}

				if (chk_33_info && chk_34_info)
					ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), (UWORD) 34);
				else if (chk_33_info && !chk_34_info)
					ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), (UWORD) 33);
				else if (!chk_33_info && chk_34_info)
					ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), (UWORD) 34);
				else 
					ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - cur_char_pos), (UWORD) VERTEX[cur_node].dic_result.info[0]);

				if (ret_val == 1) {
					M_MORPRESULT_INDEX++;
					memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
					if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
						goto LOOP_OUT;
					continue;
				} else if (ret_val == 2) {
					continue;
				}
				M_MORPHEME_INDEX = old_Morpheme_Index;
				M_CUR_MORPRESULT_NMORP = old_CUR_MAR_ITEMS;
			}

			/* 조사 사전 탐색 */
			/* 기본적인 조사 결합 제약조건 검사 */
			/* 종성 검사를 위해서 조사탐색할 글자의 앞 단어를 넘겨준다 */
			ret_val = SearchJosaDic(&h_word[cur_char_pos-1], (UWORD)(h_word_len - cur_char_pos), 
							VERTEX[cur_node].dic_result.jong, jdic_result, &jdic_res_idx);
			if (ret_val == 1) {
				/* 조사가 full-match로 검색되었을 때 */
				/* 일단 조사 사전 탐색에서는 full-match된 경우를 올바른 것으로 본다 */
				ret_val = CheckJosa(h_word, cur_char_pos, VERTEX[cur_node].dic_result.jong);
				if (ret_val == 1) {
					/* 형태소 분석 성공... */
					/* 분석 결과 저장 */
					/********************* 형태소 분석 정보 저장 *************************/
					M_CUR_MORPRESULT_NMORP++;
					if (VERTEX[cur_node].dic_result.jong) {
						tmpHan.j_han.cho = 1;
						tmpHan.j_han.jung = 2;
						tmpHan.j_han.jong = h_word[cur_char_pos-1].j_han.jong;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
						memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), 
							&h_word[cur_char_pos], sizeof(HANGUL) * (jdic_result[jdic_res_idx-1].len-1));
					} else 
						memcpy(M_CUR_MORPRESULT_MI_MORPHEME,
							&h_word[cur_char_pos], sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
					M_CUR_MORPRESULT_MI_NINFO = 1;

					strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

					t_idx = jdic_res_idx-1;
					tmp_val = jdic_result[t_idx].len;
					while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
					    sprintf(temp_info, "%d", jdic_result[t_idx].info);
					    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
					    t_idx--;
					}


					M_MORPRESULT_INDEX++;
					memcpy(&M_CUR_MORPRESULT, &M_PREV_MORPRESULT, sizeof(tMORP_RESULT));
					if (M_MORPRESULT_INDEX > MAX_CN_RESULT - 1)
						goto LOOP_OUT;
					/*********************************************************************/
				}
			}
		}
		//}//by mini for: chk_93_info_idx
		
	vert_idx++;
	
	}
	
LOOP_OUT:

	if (pre_MorpResult_Index < M_MORPRESULT_INDEX)
	    return 1;

	return 0;
}

