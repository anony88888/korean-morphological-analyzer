/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.27
 *
 *	#(Action)#
 *		- 실제 어절 분석 모듈
 *        사전 정보에 따른 어절 분석 route 설정...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_Jubmi.h>
#include <MA_Func.h>
#include <MADIC_Type.h>
#include <MADIC_DicInfo.h>
#include <MADIC_Func.h>

DWORD
KAnalysisWord(HANGUL *h_word, UWORD h_word_len, DIC_RESULT *dic_result, UWORD dic_res_idx, DWORD mode)
{
    DWORD i, j, k;
	DWORD chk_93_info, chk_93_info_idx;
#ifdef MULTI_DIC_INFO
    JEDIC_RESULT jdic_result[VS_BUFLEN];
#else
    DIC_RESULT jdic_result[VS_BUFLEN];
#endif
    UWORD jdic_res_idx = 0;
    UWORD ret_val, sub_idx, chk_jong;
    HANGUL tmpHan;
    HANGUL tmp_h_word[VS_BUFLEN];
    UWORD tmp_h_word_len;
    UWORD f_ch = 0;
    UWORD old_char;
    UWORD old_M_MORPHEME_INDEX, old_nMorp;
#ifdef MULTI_DIC_INFO
    UBYTE info;
    UWORD chk_33_info, chk_34_info;
    UWORD chk_comp_noun;
    UWORD cnt;
#endif
    UWORD jubmi_flag;
    BYTE temp_info[VS_BUFLEN];
    DWORD t_idx, tmp_val;

    M_MORPRESULT_INDEX = 0;		/* 형태소 분석을 위한 인덱스 초기화 */
    M_MORPHEME_INDEX = 0;
    tmpHan.j_han.sign = 1;
    for (i = dic_res_idx-1; i >= 0; i--) {
	
/*	if(dic_result[i].info[0]==93)
		chk_93_info=1;
	else 
		chk_93_info=0;
	for(chk_93_info_idx= 0 ;chk_93_info_idx <= chk_93_info ; chk_93_info_idx++){*/
	/* 분석 모드에 따른 형태소 분석 방법 지정 */
	if (mode == SUSA_UNIT) {
	    /* 수사 뒤의 단위명사 분석 중일 때... 
	       나머지 정보에 대한 분석을 Skip... */
	    if (dic_result[i].info[0] != 31)
		continue;
	} 
	else if (mode == SUSA_NOUN) {
	    /* 수사 뒤의 명사 분석 중일 때 ...
	       명사 외의 정보에 대한 분석을 Skip... */
	    if (!IS_NOUN(dic_result[i].info[0]))
		continue;
	}
	/******************************************/
	//printf("%d\t",dic_result[i].info[0]);
	/********************* 형태소 분석 정보 저장 *************************/
	
	M_CUR_MORPRESULT_NMORP = 1;
	if (dic_result[i].jong) {
		memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[0], sizeof(HANGUL) * (dic_result[i].len-1));
		tmpHan.j_han.cho = h_word[dic_result[i].len-1].j_han.cho;
		tmpHan.j_han.jung = h_word[dic_result[i].len-1].j_han.jung;
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len-1) = tmpHan.j_code;
	} else{
		memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[0], sizeof(HANGUL) * dic_result[i].len);
	}
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len) = 0;//


	#ifdef MULTI_DIC_INFO
		// by mini(2005.08.30)	
			M_CUR_MORPRESULT_MI_NINFO = strlen(dic_result[i].info);
			strcpy(M_CUR_MORPRESULT_MI_INFO, dic_result[i].info);
	#else
		M_CUR_MORPRESULT_MI_NINFO = 1;
		M_CUR_MORPRESULT_MI_INFO_ITEM(0) = dic_result[i].info;
		M_CUR_MORPRESULT_MI_INFO_ITEM(1) = 0;
	#endif
	
	M_MORPHEME_INDEX++;
//	 printf("M_MORPHEME_INDEX:%d\n",M_MORPHEME_INDEX);
	/*********************************************************************/
	
#ifdef MULTI_DIC_INFO
	if (IS_NOUN(dic_result[i].info[0]))
	    info = NOUNS_INFO;
	else
	    info = dic_result[i].info[0];

	switch (info) {
#else
	switch (dic_result[i].info) {
#endif
	    case 1:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
		/* 사전에서 FULL로 검사되었을 경우 */
		if (dic_result[i].len == h_word_len && dic_result[i].jong == 0) {
		    M_MORPHEME_INDEX = 0;
		    M_MORPRESULT_INDEX++;
		    break;
		}

		if (dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		ret_val = SearchJosaDic(&h_word[dic_result[i].len-1], (UWORD)(h_word_len - dic_result[i].len), 
					dic_result[i].jong, jdic_result, &jdic_res_idx);

		/* 조사 정보가 여러개가 나왔을 때, 보조사 정보가 있는지 조사 */
		for (k = 0; k < jdic_res_idx; k++) {
		    if (jdic_result[k].info == 6)
			break;
		}

		if (ret_val == 1 && k < jdic_res_idx) {
/*
			if (ret_val == 1 && jdic_result[jdic_res_idx-1].info == 6) {
*/
		    /********************* 형태소 분석 정보 저장 *************************/
		    M_CUR_MORPRESULT_NMORP++;
		    memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[dic_result[i].len], sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
		    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
		    M_CUR_MORPRESULT_MI_NINFO = 1;
		    /* 일단 조사 세부 정보는 저장하지 않음 */
		    /* 다중 세부 정보를 저장 */

		    strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

		    t_idx = jdic_res_idx-1;
		    tmp_val = jdic_result[t_idx].len;
		    while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
			sprintf(temp_info, "%d", jdic_result[t_idx].info);
			strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
			t_idx--;
		    }

		    M_MORPHEME_INDEX = 0;
		    M_MORPRESULT_INDEX++;
		    /*********************************************************************/
		} else 
		    M_MORPHEME_INDEX = 0;

		break;

	    case 10:	/* 독립어 */
		if (dic_result[i].len == h_word_len && dic_result[i].jong == 0) {
		    M_MORPHEME_INDEX = 0;
		    M_MORPRESULT_INDEX++;
		    break;
		}

		M_MORPHEME_INDEX = 0;
		break;

	    case 20:
	    case 21:
	    case 22:
		if (dic_result[i].len == h_word_len && dic_result[i].jong == 0) {
		    M_MORPHEME_INDEX = 0;
		    M_MORPRESULT_INDEX++;
		    break;
		}

#ifndef NO_HEURISTIC_RULE
	/* 
	@ RULE(1)
	#TI=관형사 제약 조건
	#SU=형태소제약규칙(1)
	#AB=한자짜리 관형사가 명사와 결합할 때,
		관형사와 명사가 함께 사전에 존재하면,
		이를 분석하지 않고, FALSE를 리턴한다.
	#TM=2000/04/20
	*/
		/* 관형사 길이 : 1 */
		/* 사전에서 가장 길게 찾아진 SubString의 길이가 1보다 크면 */
		/* 일단, 사전 검색만으로 판단... 나중에는 형태소분석 결과를 가지고 판단할 수도 있겠다. */
		if (dic_result[i].len == 1 && dic_result[dic_res_idx-1].len > 1) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
#endif
			/* 관형사에 붙는 명사는 복합명사 처리부에서 처리 */
		if (dic_result[i].len >= 1 && h_word_len - dic_result[i].len >= 2 && !dic_result[i].jong)
#ifdef MULTI_DIC_INFO
		    ret_val = CheckCompNoun(&h_word[dic_result[i].len], (UWORD)(h_word_len - dic_result[i].len),
						h_word[dic_result[i].len-1], dic_result[i].info[0]);
#else
		    ret_val = CheckCompNoun(&h_word[dic_result[i].len], (UWORD)(h_word_len - dic_result[i].len),
						h_word[dic_result[i].len-1], dic_result[i].info);
#endif
		    M_MORPHEME_INDEX = 0;

		    break;
#ifdef MULTI_DIC_INFO
	    case NOUNS_INFO:
#else
	    case 30:
	    case 31:
	    case 32:
	    case 33:
	    case 34:
	    case 35:
	    case 36:
	    case 37:
	    case 38:
	    case 39:
	    case 40:
	    case 41:
		case 90: //3음절명사 추가 by mini(2005.08.30)
		case 91: 
		case 92:
		case 93:
		case 94:
#endif
		/* 사전에서 FULL로 검사되었을 경우 */
		if (dic_result[i].len == h_word_len && dic_result[i].jong == 0) {
		    M_MORPHEME_INDEX = 0;
		    M_MORPRESULT_INDEX++;
		    continue;
		}

		/**********************************************************************************/
		/* 접미사 처리를 한다...(따로 함수를 만들지 않는다...(속도 때매)...               */
		jubmi_flag = 0;
#ifdef COMP_NOUN_DIC_CHECK
		/* 복합명사 기분석사전 기반 어절 분석시에
		 * 복합명사가 접미사로 끝난 경우는 여기서 접미사 검사를 하지 않는다. */
		if (mode == COMPNOUN_POSTNOUN_NP)
		    goto SKIP_JUBMI_CHECK;
#endif
		if (dic_result[i].jong == 0) {
		    for (k = 0; k < JUBMI_NUM; k++) {
			if (h_word[dic_result[i].len].j_code == JUBMI[k]) //JUBMI_NUM 29
			    break;
		    }
		    if (k < JUBMI_NUM) {
			/* 접미사가 포함된 단어가 사전에 존재하면 SKIP */
			j = i;
			while (j < dic_res_idx) {
			    if (!dic_result[j].jong && dic_result[j].len == dic_result[i].len + 1)
				break;
			    j++;
			}
			if (j == dic_res_idx) {
			    jubmi_flag = 1;
			    old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			    old_nMorp = M_CUR_MORPRESULT_NMORP;
			    M_CUR_MORPRESULT_NMORP++;
			    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = h_word[dic_result[i].len].j_code;
			    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			    M_CUR_MORPRESULT_MI_NINFO = 1;
			    strcpy(M_CUR_MORPRESULT_MI_INFO, "JUBMISA");

				/* 일반 접미사와 접미명사를 구분 */
				/* 자세한 내용은 MA_Jubmi.h에... */
				if (JUBMI_Info[k])
					strcat(M_CUR_MORPRESULT_MI_INFO, " JN");

			    M_MORPHEME_INDEX++;

			    dic_result[i].len++;
			    if (dic_result[i].len == h_word_len) {
				if (h_word[dic_result[i].len-1].j_code == 0x89C1/*과*/) {
				    M_MORPHEME_INDEX--;
				    strcat(M_CUR_MORPRESULT_MI_INFO, " J25");
				    M_MORPHEME_INDEX++;
				} else if (h_word[dic_result[i].len-1].j_code == 0xAA85/*뿐*/) {
				    M_MORPHEME_INDEX--;
				    strcat(M_CUR_MORPRESULT_MI_INFO, " J6");
				    M_MORPHEME_INDEX++;
				}
				M_MORPHEME_INDEX = 0;
				M_MORPRESULT_INDEX++;

				continue;
			    } else if (dic_result[i].len+1 == h_word_len &&
					    h_word[dic_result[i].len-1].j_code == 0xAA85/*뿐*/ &&
					    h_word[dic_result[i].len].j_code == 0xA065/*만*/) {
				M_MORPHEME_INDEX--;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = h_word[dic_result[i].len].j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "J6");
				M_MORPHEME_INDEX++;

				M_MORPHEME_INDEX = 0;
				M_MORPRESULT_INDEX++;
				continue;
			    }
			}
		    }
		}
		/**********************************************************************************/
#ifdef COMP_NOUN_DIC_CHECK
SKIP_JUBMI_CHECK:;
#endif
		/* '이다' 처리 */
		if (dic_result[i].jong == 0) {
			if (h_word[dic_result[i].len].j_han.cho == 0x0D && h_word[dic_result[i].len].j_han.jung == 0x1D) { //ㅇ+ ㅣ
			sub_idx = dic_result[i].len - 1;
			chk_jong = dic_result[i].jong;
			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;
			memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - dic_result[i].len + 1));
			ret_val = CheckIda(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), chk_jong);
			if (ret_val == 1) {
			    M_MORPHEME_INDEX = 0;
			    M_MORPRESULT_INDEX++;
			    break;
			} else if (ret_val == 2) {
			    M_MORPHEME_INDEX = 0;
			    break;
			}
			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = old_nMorp;
		    }
			else if (h_word[dic_result[i].len].j_code == 0x9461) {	/* 다 */
			if (h_word[dic_result[i].len-1].j_han.jong == 0x01 && h_word_len == dic_result[i].len + 1) {
			    sub_idx = dic_result[i].len - 1;
			    chk_jong = dic_result[i].jong;
			    old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			    old_nMorp = M_CUR_MORPRESULT_NMORP;
			    memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - dic_result[i].len + 1));
			    ret_val = CheckIda(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), chk_jong);
			    if (ret_val == 1) {
				M_MORPHEME_INDEX = 0;
				M_MORPRESULT_INDEX++;
				break;
			    } else if (ret_val == 2) {
				M_MORPHEME_INDEX = 0;
				break;
			    }
			    M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			    M_CUR_MORPRESULT_NMORP = old_nMorp;
			}
		    } 
			else if (h_word[dic_result[i].len].j_han.cho == 0x0D && h_word[dic_result[i].len].j_han.jung == 0x0B) { /* 여 */
				if (h_word[dic_result[i].len-1].j_han.jong == 0x01 && h_word_len > dic_result[i].len + 1) {
					sub_idx = dic_result[i].len - 1;
					chk_jong = dic_result[i].jong;
					old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
					old_nMorp = M_CUR_MORPRESULT_NMORP;
					memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - dic_result[i].len + 1));
					ret_val = CheckIda(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), chk_jong);
					if (ret_val == 1) {
					M_MORPHEME_INDEX = 0;
					M_MORPRESULT_INDEX++;
					break;
					} else if (ret_val == 2) {
					M_MORPHEME_INDEX = 0;
					break;
					}
					M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
					M_CUR_MORPRESULT_NMORP = old_nMorp;
				}
		    }
		}

#ifdef COMP_NOUN_DIC_CHECK
		/* 복합명사 기분석사전 기반 어절 분석시에..
		 * 동사형/형용사형 접사 분석을 하지 않는다. */
		if (mode == COMPNOUN_POSTNOUN_NP || mode == COMPNOUN_POSTNOUN_P)
		    goto SKIP_VAJUBSA_CKECK;
#endif
		if (dic_result[i].jong == 0) {
		    sub_idx = dic_result[i].len - 1;
		    chk_jong = dic_result[i].jong;
		    old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;  //Morpheme_Index
		    old_nMorp = M_CUR_MORPRESULT_NMORP;
		    memcpy(tmp_h_word, &h_word[sub_idx], sizeof(HANGUL) * (h_word_len - dic_result[i].len + 1));
#ifdef MULTI_DIC_INFO
		    chk_33_info = chk_34_info = 0;
		    cnt = 0;
		    while (1) {
			if (dic_result[i].info[cnt] == 0)
			    break;
			if (dic_result[i].info[cnt] == 33)
			    chk_33_info = 1;
			if (dic_result[i].info[cnt] == 34)
			    chk_34_info = 1;
			cnt++;
		    }

		    if (chk_33_info && chk_34_info)
				ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), (UWORD) 34);
		    else if (chk_33_info && !chk_34_info)
				ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), (UWORD) 33);
		    else if (!chk_33_info && chk_34_info)
				ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), (UWORD) 34);
		    else 
				ret_val = VAJubSaProc(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len), dic_result[i].info[0]);
#else
		    ret_val = VAJubSaProc(tmp_h_word, h_word_len - dic_result[i].len, dic_result[i].info);
#endif
		    if (ret_val == 1) {
				M_MORPHEME_INDEX = 0;
				M_MORPRESULT_INDEX++;
				break;
		    } 
			else if (ret_val == 2) {
				M_MORPHEME_INDEX = 0;
				break;
		    }
		    M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
		    M_CUR_MORPRESULT_NMORP = old_nMorp;
		}

#ifdef COMP_NOUN_DIC_CHECK
SKIP_VAJUBSA_CKECK:
#endif

		/* 조사 사전 탐색 */
		/* 기본적인 조사 결합 제약조건 검사 */
		/* 종성 검사를 위해서 조사탐색할 글자의 앞 단어를 넘겨준다 */
		ret_val = SearchJosaDic(&h_word[dic_result[i].len-1], (UWORD)(h_word_len - dic_result[i].len), 
						dic_result[i].jong, jdic_result, &jdic_res_idx);
		if (ret_val == 1) {
		    /* 조사가 full-match로 검색되었을 때 */
		    /* 일단 조사 사전 탐색에서는 full-match된 경우를 올바른 것으로 본다 */
		    ret_val = CheckJosa(h_word, dic_result[i].len, dic_result[i].jong);
		    if (ret_val == 1) {
			/* 형태소 분석 성공... */
			/* 분석 결과 저장 */
			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (dic_result[i].jong) {
			    tmpHan.j_han.cho = 1;
			    tmpHan.j_han.jung = 2;
			    tmpHan.j_han.jong = h_word[dic_result[i].len-1].j_han.jong;
			    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
			    memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[dic_result[i].len], 
				    sizeof(HANGUL) * (jdic_result[jdic_res_idx-1].len-1));
			} else 
			    memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[dic_result[i].len], 
				    sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
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

			M_MORPHEME_INDEX = 0;
			M_MORPRESULT_INDEX++;
			/*********************************************************************/
			break;
		    }
		}

		/* 접미사가 붙는 명사는 복합명사로 될 수 없다는 가정하에...
		   조사 분석까지 실패했을 경우에는 원래대로 복원한다. */
		if (jubmi_flag) {
		    M_MORPHEME_INDEX--;
		    dic_result[i].len--;
		    M_CUR_MORPRESULT_NMORP--;
		}

#ifdef COMP_NOUN_DIC_CHECK
		/* 복합명사 기분석사전 기반 어절 분석시에..
		 * 복합명사 분석을 하지 않는다.*/
		if (mode == COMPNOUN_POSTNOUN_NP || mode == COMPNOUN_POSTNOUN_P)
		    goto SKIP_COMPNOUN_CKECK;
#endif

#ifdef MULTI_DIC_INFO
		cnt = 0;
		chk_comp_noun = 0;
		while (1) {
		    if (dic_result[i].info[cnt] == 0)
			break;
		    if (dic_result[i].info[cnt] != 30 && dic_result[i].info[cnt] != 31
			    && dic_result[i].info[cnt] != 36 && dic_result[i].info[cnt] != 37
			    && dic_result[i].info[cnt] != 38 && dic_result[i].info[cnt] != 41)
			chk_comp_noun = 1;
		    cnt++;
		}

		if (ret_val == 0 && chk_comp_noun)
		    if (dic_result[i].len >= 2 && h_word_len - dic_result[i].len >= 2 && !dic_result[i].jong)
			ret_val = CheckCompNoun(&h_word[dic_result[i].len], (UWORD)(h_word_len - dic_result[i].len),
						h_word[dic_result[i].len-1], dic_result[i].info[0]);
#else
		if (ret_val == 0 && jubmi_flag
			&& dic_result[i].info != 30 && dic_result[i].info != 31
			&& dic_result[i].info != 36 && dic_result[i].info != 37
			&& dic_result[i].info != 38 && dic_result[i].info != 41)
		    if (dic_result[i].len >= 2 && h_word_len - dic_result[i].len >= 2 && !dic_result[i].jong)
			ret_val = CheckCompNoun(&h_word[dic_result[i].len], (UWORD)(h_word_len - dic_result[i].len),
						h_word[dic_result[i].len-1], dic_result[i].info);
#endif

#ifdef COMP_NOUN_DIC_CHECK
SKIP_COMPNOUN_CKECK:
#endif
		M_MORPHEME_INDEX = 0;
		break;

	    case 50:
	    case 51:
	    case 52:
		sub_idx = dic_result[i].len - 1;
		chk_jong = dic_result[i].jong;

		if (dic_result[i].len == h_word_len && !dic_result[i].jong && h_word[h_word_len-1].j_han.jong == 0x01) {
		    /* 꺼내, 들어가... 등등... 어미 "아" 가 생략된 어절에 대한 처리... */
		    /* "하"로 끝나는 어절을 제외하고는 모두 "아"가 생략된 것으로 처리 2000.06.29 */
/*
		    if (h_word[sub_idx].j_code == 0x8861 || h_word[sub_idx].j_code == 0x9061) {
*/
		    if (h_word[sub_idx].j_han.jung == 0x03 && h_word[sub_idx].j_code != 0xD061) {
			tmp_h_word[0].j_code = h_word[sub_idx].j_code;
			tmp_h_word[1].j_han.sign = 1;
			tmp_h_word[1].j_han.cho = 0x0D;
			tmp_h_word[1].j_han.jung = 0x03;
			tmp_h_word[1].j_han.jong = 0x01;

			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;
			ret_val = CheckEomi(tmp_h_word, 1, 0);
			if (ret_val == 1) {
			    M_MORPHEME_INDEX = 0;
			    M_MORPRESULT_INDEX++;
			    break;
			} else if (ret_val == 2) {
			    M_MORPHEME_INDEX = 0;
			    break;
			}

			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = 1;
		    } else if (h_word[sub_idx].j_han.jung == 0x04) { /* ㅐ */
			tmp_h_word[0].j_code = h_word[sub_idx].j_code;
			tmp_h_word[1].j_han.sign = 1;
			tmp_h_word[1].j_han.cho = 0x0D;
			tmp_h_word[1].j_han.jung = 0x07;
			tmp_h_word[1].j_han.jong = 0x01;

			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;
			ret_val = CheckEomi(tmp_h_word, 1, 0);
			if (ret_val == 1) {
			    M_MORPHEME_INDEX = 0;
			    M_MORPRESULT_INDEX++;
			    break;
			} else if (ret_val == 2) {
			    M_MORPHEME_INDEX = 0;
			    break;
			}

			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = 1;
		    }

		    M_MORPHEME_INDEX = 0;
		    break;
		}

			/* 디버깅 : 2000/11/28
			   일반용언의 어간만이 왔을 경우에는 무조건 실패...
			   다시 수정: 일반용언의 마지막 어간이 종성으로 끝났을 경우에만...
			*/
		if (dic_result[i].len == h_word_len && h_word[sub_idx].j_han.jong != 0x01 && chk_jong == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 매개모음 '으' 삽입 규칙 처리 */
		if (dic_result[i].jong != 1 && h_word[sub_idx+1].j_han.cho == 0x0D
			&& h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -으-*/
		    if (h_word[sub_idx].j_han.jong != 0x01 && h_word[sub_idx].j_han.jong != 0x09) {
			/* 어간에 'ㄹ'이 아닌 받침이 있을 때 */
			if (h_word[sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
			    if (h_word[sub_idx+1].j_han.jong != 0x05		/* ㄴ */
				    && h_word[sub_idx+1].j_han.jong != 0x09	/* ㄹ */
				    && h_word[sub_idx+1].j_han.jong != 0x13	/* ㅂ */
				    && h_word[sub_idx+1].j_han.jong != 0x11) {	/* ㅁ */
				M_MORPHEME_INDEX = 0;
				break;
			    }
			    chk_jong = 1;
			    sub_idx++;		/* 으 skip */
			} else {
			    sub_idx++;		/* 으 skip */
			    if (h_word_len == sub_idx+1) {
				M_MORPHEME_INDEX = 0;
				break;
			    }
			}
		    }
		}

		/* 총체적으로 처리한다...
		   우선 어간이 "ㅏ"나 "ㅐ"로 끝나는 어절 중에서 "하"로 끝나지 않은 어절을 골라내고...
		   또한 어간 바로 다음 음절이 "아"나 "어"로 시작되는 어미의 바로 다음 음절인 
		   "도", "라", "서", "선", "야", "요", "자", "지" 일 경우에는 생략된 "아"나 "어"를 삽입한다...
		   그러나 이 음절 중에서 "도"와 "지"는 보조용언의 첫음절일 수도 있으므로 두번 검사를 한다. 2000.06.29 */
		/* 벗어나서...꺼내서... 등 처리 */
		if (h_word[sub_idx].j_han.jong == 0x01 && 
			(h_word[sub_idx].j_han.jung == 0x03 ||
			 h_word[sub_idx].j_han.jung == 0x04 ||
			 h_word[sub_idx].j_han.jung == 0x07) && h_word[sub_idx].j_code != 0xD061 /* 하 */) {
		    if ((h_word[sub_idx].j_han.jung == 0x03 && IsFirstAEomiChar(h_word[sub_idx+1])) ||
				((h_word[sub_idx].j_han.jung == 0x04 || h_word[sub_idx].j_han.jung == 0x07)
				 && IsFirstEoEomiChar(h_word[sub_idx+1]))) {
			tmp_h_word[0].j_code = h_word[sub_idx].j_code;
			if (h_word[sub_idx].j_han.jung == 0x03)
			    tmp_h_word[1].j_code = 0xb461; /* 아 */
			else
			    tmp_h_word[1].j_code = 0xb4e1; /* 아 */

			memcpy(&tmp_h_word[2], &h_word[sub_idx+1], sizeof(HANGUL) * (h_word_len - (sub_idx+1)));

			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;

			ret_val = CheckEomi(tmp_h_word, (UWORD) (h_word_len - sub_idx), (UWORD) 0);
			if (ret_val == 1) {
			    M_MORPHEME_INDEX = 0;
			    M_MORPRESULT_INDEX++;
			    break;
			} else if (ret_val == 2) {
			    M_MORPHEME_INDEX = 0;
			    break;
			}

			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = 1;
		    }
		}

/*
		if (h_word[sub_idx].j_code == 0x8861 || h_word[sub_idx].j_code == 0x9061) {
			tmp_h_word[0].j_code = h_word[sub_idx].j_code;
			tmp_h_word[1].j_code = 0xb461;

			memcpy(&tmp_h_word[2], &h_word[sub_idx+1], sizeof(HANGUL) * (h_word_len - (sub_idx+1)));

			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;

			ret_val = CheckEomi(tmp_h_word, h_word_len - sub_idx, 0);
			if (ret_val == 1) {
				M_MORPHEME_INDEX = 0;
				M_MORPRESULT_INDEX++;
				break;
			} else if (ret_val == 2) {
				M_MORPHEME_INDEX = 0;
				break;
			}

			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = 1;
		} else if (h_word[sub_idx].j_han.jung == 0x04 && !chk_jong) {
			tmp_h_word[0].j_code = h_word[sub_idx].j_code;
			tmp_h_word[1].j_code = 0xb4e1;

			memcpy(&tmp_h_word[2], &h_word[sub_idx+1], sizeof(HANGUL) * (h_word_len - (sub_idx+1)));

			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;

			ret_val = CheckEomi(tmp_h_word, h_word_len - sub_idx, 0);
			if (ret_val == 1) {
				M_MORPHEME_INDEX = 0;
				M_MORPRESULT_INDEX++;
				break;
			} else if (ret_val == 2) {
				M_MORPHEME_INDEX = 0;
				break;
			}

			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = 1;
		}
*/
		/* 갔다, 꺼냈다...아/어 탈락 현상 */
		if ((h_word[sub_idx].j_han.jung == 0x03 
			|| h_word[sub_idx].j_han.jung == 0x04
			|| h_word[sub_idx].j_han.jung == 0x07
			|| h_word[sub_idx].j_han.jung == 0x0A
			|| h_word[sub_idx].j_han.jung == 0x0B) && h_word[sub_idx].j_han.jong == 0x16) {
		    if ((chk_jong && h_word[sub_idx].j_han.jong == 0x16) || (h_word[sub_idx].j_han.jong == 0x01)) {
			tmp_h_word[0].j_code = h_word[sub_idx].j_code;
			tmp_h_word[0].j_han.jong = 0x01;
			tmp_h_word[1].j_han.sign = 1;
			tmp_h_word[1].j_han.cho = 0x0D;
			if (h_word[sub_idx].j_han.jung == 0x0B
				|| h_word[sub_idx].j_han.jung == 0x04
				|| h_word[sub_idx].j_han.jung == 0x0A)
			    tmp_h_word[1].j_han.jung = 0x07;
			else
			    tmp_h_word[1].j_han.jung = h_word[sub_idx].j_han.jung;
			tmp_h_word[1].j_han.jong = h_word[sub_idx].j_han.jong;
			memcpy(&tmp_h_word[2], &h_word[sub_idx+1], sizeof(HANGUL) * (h_word_len - (sub_idx+1)));
			old_M_MORPHEME_INDEX = M_MORPHEME_INDEX;
			old_nMorp = M_CUR_MORPRESULT_NMORP;
			ret_val = CheckEomi(tmp_h_word, (UWORD) (h_word_len - sub_idx), (UWORD) 0);
			if (ret_val == 1) {
			    M_MORPHEME_INDEX = 0;
			    M_MORPRESULT_INDEX++;
			    break;
			} else if (ret_val == 2) {
			    M_MORPHEME_INDEX = 0;
			    break;
			}

			M_MORPHEME_INDEX = old_M_MORPHEME_INDEX;
			M_CUR_MORPRESULT_NMORP = 1;
		    }
		}

		f_ch = 0;
		if (h_word[sub_idx].j_code == 0xD061	/* 하여- */
			&& h_word[sub_idx+1].j_han.cho == 0x0D && h_word[sub_idx+1].j_han.jung == 0x0B) {
		    f_ch = 1;
		    old_char = h_word[sub_idx+1].j_code;
		    h_word[sub_idx+1].j_han.jung = 0x07;
		} else if (h_word_len > sub_idx + 2 && h_word[sub_idx].j_code == 0xB5A1
			&& h_word[sub_idx+1].j_code == 0x90E1 && h_word[sub_idx+2].j_code == 0x9C61) {
		    /* 너라 처리 */
		    f_ch = 1;
		    old_char = h_word[sub_idx+1].j_code;
		    h_word[sub_idx+1].j_code = 0xB461;
		} else if (h_word_len > sub_idx + 2 && h_word[sub_idx].j_han.jung == 0x03
			&& h_word[sub_idx+1].j_code == 0x88E1 && h_word[sub_idx+2].j_code == 0x9C61) {
		    /* 거라 처리 */
		    f_ch = 1;
		    old_char = h_word[sub_idx+1].j_code;
		    h_word[sub_idx+1].j_han.cho = 0x0D;
		}
			
		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&h_word[sub_idx], (UWORD) (h_word_len - sub_idx - 1), chk_jong);
		if (f_ch)
		    h_word[sub_idx+1].j_code = old_char;

		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 53:
	    case 54:
		if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
		/* ㅅ 불규칙 용언 처리 */
		if (dic_result[i].jong == 1) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
		/* ㅅ 불규칙 처리 루틴 호출 */
		ret_val = S_IrrProc(&h_word[dic_result[i].len-1], (UWORD) (h_word_len - dic_result[i].len), dic_result[i].len);
		if (ret_val == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		sub_idx = dic_result[i].len - 1;
		chk_jong = dic_result[i].jong;

		/* 매개모음 '으' 삽입 규칙 처리 */
		if (dic_result[i].jong != 1 && h_word[sub_idx+1].j_han.cho == 0x0D
			&& h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -으-*/
		    if (h_word[sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
			if (h_word[sub_idx+1].j_han.jong != 0x05		/* ㄴ */
				&& h_word[sub_idx+1].j_han.jong != 0x09	/* ㄹ */
				&& h_word[sub_idx+1].j_han.jong != 0x13	/* ㅂ */
				&& h_word[sub_idx+1].j_han.jong != 0x11) {	/* ㅁ */
			    M_MORPHEME_INDEX = 0;
			    break;
			}
			chk_jong = 1;
			sub_idx++;		/* 으 skip */
		    } else {
			sub_idx++;		/* 으 skip */
			if (h_word_len == sub_idx+1) {
			    M_MORPHEME_INDEX = 0;
			    break;
			}
		    }
		}

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&h_word[sub_idx], (UWORD) (h_word_len - sub_idx - 1), chk_jong);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 55:
		if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
		/* ㄷ 불규칙 용언 처리 */
		if (dic_result[i].jong == 1) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
		/* ㄷ 불규칙 처리 루틴 호출 */
		ret_val = D_IrrProc(&h_word[dic_result[i].len-1], (UWORD) (h_word_len - dic_result[i].len), dic_result[i].len);
		if (ret_val == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		sub_idx = dic_result[i].len - 1;
		chk_jong = dic_result[i].jong;

		/* 매개모음 '으' 삽입 규칙 처리 */
		if (dic_result[i].jong != 1 && h_word[sub_idx+1].j_han.cho == 0x0D
			&& h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -으-*/
		    if (h_word[sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
			if (h_word[sub_idx+1].j_han.jong != 0x05		/* ㄴ */
				&& h_word[sub_idx+1].j_han.jong != 0x09	/* ㄹ */
				&& h_word[sub_idx+1].j_han.jong != 0x13	/* ㅂ */
				&& h_word[sub_idx+1].j_han.jong != 0x11) {	/* ㅁ */
			    M_MORPHEME_INDEX = 0;
			    break;
			}
			chk_jong = 1;
			sub_idx++;		/* 으 skip */
		    } else {
			sub_idx++;		/* 으 skip */
			if (h_word_len == sub_idx+1) {
				M_MORPHEME_INDEX = 0;
				break;
			}
		    }
		}

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&h_word[sub_idx], (UWORD) (h_word_len - sub_idx - 1), chk_jong);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 56:
	    case 57:
		if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 새삼스런, 갑작스런 문제 해결 2000.06.29 */
		if (dic_result[i].jong && h_word_len > 2 
			&& h_word[dic_result[i].len-2].j_code == 0xaf61 /* 스 */
			&& h_word[dic_result[i].len-1].j_code == 0x9ce5) /* 런 */ {

		    /*********************************************************************/
		    M_CUR_MORPRESULT_NMORP++;
		    tmp_h_word[0].j_han.sign = 1;
		    tmp_h_word[0].j_han.cho = 1;
		    tmp_h_word[0].j_han.jung = 2;
		    tmp_h_word[0].j_han.jong = 0x05;

		    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmp_h_word[0].j_code;
		    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		    M_CUR_MORPRESULT_MI_NINFO = 1;

		    strcpy(M_CUR_MORPRESULT_MI_INFO, "E5");

		    M_MORPHEME_INDEX = 0;
		    M_MORPRESULT_INDEX++;
		    break;
		}

		sub_idx = dic_result[i].len - 1;
		chk_jong = 0;

		/* ㅂ 불규칙 처리 중에 어미부가 수정될 수 있으므로 */
		memcpy(tmp_h_word, h_word, sizeof(HANGUL) * h_word_len);
		/* 'ㅂ' 불규칙 용언 처리 */
		if (dic_result[i].jong == 1) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 'ㅂ' 불규칙 처리 루틴 호출 */
		ret_val = B_IrrProc(&tmp_h_word[dic_result[i].len-1], (UWORD) (h_word_len - dic_result[i].len), 
								dic_result[i].len, &sub_idx, &chk_jong);
		if (ret_val == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&tmp_h_word[sub_idx], (UWORD) (h_word_len - sub_idx - 1), chk_jong);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    /* ㅎ 불규칙 용언 */
	    case 58:
	    case 59:
		if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
		/* 사전에 존재하는 ㅎ 불규칙 용언은 모두 길이가 2이상이다 */
		sub_idx = dic_result[i].len - 1;
		chk_jong = 0;

		/* ㅂ 불규칙 처리 중에 어미부가 수정될 수 있으므로 */
		/* 파래서 --> 파랗 + 아서 
		   파랍니다 --> 파랗 + ㅂ니다 */
		memcpy(tmp_h_word, h_word, sizeof(HANGUL) * h_word_len);
		tmp_h_word_len = h_word_len;

		/* 'ㅎ' 불규칙 처리 루틴 호출 */
		ret_val = H_IrrProc(&tmp_h_word[dic_result[i].len-1], (UWORD) (h_word_len - dic_result[i].len), 
								dic_result[i].len, &sub_idx, &chk_jong);

		if (ret_val == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&tmp_h_word[sub_idx-1], (UWORD) (h_word_len - sub_idx), chk_jong);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 60:
		/* 우 불규칙 "퍼" */
		if (h_word[dic_result[i].len-1].j_han.cho == 0x13 &&
			h_word[dic_result[i].len-1].j_han.jung == 0x07) {
		    chk_jong = dic_result[i].jong;

		    memcpy(tmp_h_word, h_word, sizeof(HANGUL) * h_word_len);
		    M_MORPHEME_INDEX--;
		    tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len-1);
		    tmpHan.j_han.jung = 0x14;
		    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len-1) = tmpHan.j_code;
		    M_MORPHEME_INDEX++;
		    memcpy(&h_word[dic_result[i].len+1], &h_word[dic_result[i].len], sizeof(HANGUL) * (h_word_len - 1));

		    /* '어' 삽입 */
		    h_word[dic_result[i].len].j_han.cho = 0x0D;
		    h_word[dic_result[i].len].j_han.jung = 0x07;
		    h_word[dic_result[i].len].j_han.jong = h_word[dic_result[i].len-1].j_han.jong;

		    if (h_word[dic_result[i].len-1].j_han.jong == 0x16)
			chk_jong = 0;

		    /* 어미 분석 루틴 호출 */
		    ret_val = CheckEomi(&h_word[dic_result[i].len-1], (UWORD) (h_word_len - dic_result[i].len + 1), chk_jong);
		    M_MORPHEME_INDEX = 0;
		    if (ret_val == 1)
			M_MORPRESULT_INDEX++;

		    memcpy(h_word, tmp_h_word, sizeof(HANGUL) * h_word_len);
		}

		M_MORPHEME_INDEX = 0;
		break;

	    case 61:
	    case 62:
		if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

/*
		if (dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
*/

		/* 러 불규칙 */
		sub_idx = dic_result[i].len;
		if (h_word[sub_idx].j_han.cho == 0x07 && h_word[sub_idx].j_han.jung == 0x07) {
		    memcpy(tmp_h_word, h_word, sizeof(HANGUL) * h_word_len);
		    tmp_h_word[sub_idx].j_han.cho = 0x0D;

		    /* 어미 분석 루틴 호출 */
		    ret_val = CheckEomi(&tmp_h_word[sub_idx-1], (UWORD) (h_word_len - sub_idx), (UWORD) 0);
		    M_MORPHEME_INDEX = 0;
		    if (ret_val == 1)
			M_MORPRESULT_INDEX++;
		} else {
		    ret_val = CheckEomi(&h_word[sub_idx-1], (UWORD) (h_word_len - sub_idx), dic_result[i].jong);
		    M_MORPHEME_INDEX = 0;
		    if (ret_val == 1)
			M_MORPRESULT_INDEX++;
		}

		M_MORPHEME_INDEX = 0;
		break;

	    case 63:
	    case 64:
		/*
			if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
				M_MORPHEME_INDEX = 0;
				break;
			}
		*/
		/* 르 불규칙 용언 */
		sub_idx = dic_result[i].len - 1;

		memcpy(tmp_h_word, h_word, sizeof(HANGUL) * h_word_len);
		
		ret_val = RUE_IrrProc(&tmp_h_word[sub_idx], (UWORD) (h_word_len - dic_result[i].len),
							dic_result[i].len, &sub_idx);
		if (ret_val == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&tmp_h_word[sub_idx-1], (UWORD) (h_word_len - sub_idx), (UWORD) 0);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 65:
	    case 66:
		/* 으 탈락 */
		sub_idx = dic_result[i].len - 1;
		chk_jong = dic_result[i].jong;
		tmp_h_word_len = h_word_len;

		memcpy(tmp_h_word, h_word, sizeof(HANGUL) * h_word_len);

		ret_val = EU_IrrProc(&tmp_h_word[sub_idx], (UWORD) (h_word_len - sub_idx),
							dic_result[i].len, &chk_jong, &h_word_len);
		if (ret_val == 0) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&tmp_h_word[sub_idx], (UWORD) (h_word_len - dic_result[i].len), 0);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		h_word_len = tmp_h_word_len;

		break;

	    case 67:
	    case 68:
		/* ㄹ 탈락 */
		if (dic_result[i].len == h_word_len && !dic_result[i].jong) {
		    M_MORPHEME_INDEX = 0;
		    break;
		}
		sub_idx = dic_result[i].len - 1;
	
		if (dic_result[i].jong == 1) {
		    /* 놀, 까불, 깨물 등을 처리하기 위해서 2000.06.27 */
		    if (h_word[sub_idx].j_han.jong != 0x05 &&
			    h_word[sub_idx].j_han.jong != 0x09 &&
			    h_word[sub_idx].j_han.jong != 0x13) {
			M_MORPHEME_INDEX = 0;
			break;
		    }
		} else {
		    if (h_word[sub_idx+1].j_han.cho != 0x04 &&
			    h_word[sub_idx+1].j_han.cho != 0x09 &&
			    h_word[sub_idx+1].j_han.cho != 0x0B &&
			    h_word[sub_idx+1].j_code != 0xB5A1) {
			M_MORPHEME_INDEX = 0;
			break;
		    }
		}

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1);
		tmpHan.j_han.jong = 0x09;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;

		/* 어미 분석 루틴 호출 */
		ret_val = CheckEomi(&h_word[sub_idx], (UWORD) (h_word_len - dic_result[i].len), dic_result[i].jong);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 69:
	    case 70:
	    case 71:
		/* 하 불규칙 : 해--- */
		if (h_word[dic_result[i].len - 1].j_han.jong != 0x01 && 
			h_word[dic_result[i].len - 1].j_han.jong != 0x16) {
		    M_MORPHEME_INDEX = 0; 
		    break;
		}

		M_MORPHEME_INDEX--;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1) = 0xD061;
		M_MORPHEME_INDEX++;
		tmp_h_word[0].j_code = 0xD061;
		tmp_h_word[1].j_code = 0xB4E1;
		tmp_h_word[1].j_han.jong = h_word[dic_result[i].len-1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[dic_result[i].len], sizeof(HANGUL) * (h_word_len - dic_result[i].len));

		ret_val = CheckEomi(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len + 1), (UWORD) 0);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 72:
		/* 와/워 축약 동사 */
		if (h_word[dic_result[i].len - 1].j_han.jong != 0x01 && 
			h_word[dic_result[i].len - 1].j_han.jong != 0x16) {
		    M_MORPHEME_INDEX = 0; 
		    break;
		}

		M_MORPHEME_INDEX--;
		if (h_word[dic_result[i].len-1].j_han.jung == 0x0E) {
		    tmpHan.j_code = 0xB5A1;	/* 오 */
		    tmpHan.j_han.cho = h_word[dic_result[i].len-1].j_han.cho;
		    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1) = tmpHan.j_code;
		} else if (h_word[dic_result[i].len-1].j_han.jung == 0x15) {
		    tmpHan.j_code = 0xB681;	/* 우 */
		    tmpHan.j_han.cho = h_word[dic_result[i].len-1].j_han.cho;
		    M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1) = tmpHan.j_code;
		}

		M_MORPHEME_INDEX++;

		if (h_word[dic_result[i].len-1].j_han.jung == 0x0E) {
		    tmp_h_word[0].j_code = 0xB5A1;
		    tmp_h_word[0].j_han.cho = h_word[dic_result[i].len-1].j_han.cho;
		    tmp_h_word[1].j_code = 0xB461;
		} else if (h_word[dic_result[i].len-1].j_han.jung == 0x15) {
		    tmp_h_word[0].j_code = 0xB681;
		    tmp_h_word[0].j_han.cho = h_word[dic_result[i].len-1].j_han.cho;
		    tmp_h_word[1].j_code = 0xB4E1;
		}
		tmp_h_word[1].j_han.jong = h_word[dic_result[i].len-1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[dic_result[i].len], sizeof(HANGUL) * (h_word_len - dic_result[i].len));

		ret_val = CheckEomi(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len + 1), (UWORD) 0);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 73:
	    case 74:
		/* 이 축약 --> 여 -> 이어 */
		if (h_word[dic_result[i].len - 1].j_han.jong != 0x01 && 
			h_word[dic_result[i].len - 1].j_han.jong != 0x16) {
		    M_MORPHEME_INDEX = 0; 
		    break;
		}

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1);
		tmpHan.j_han.jung = 0x1D;
		tmpHan.j_han.jong = 0x01;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;
		tmp_h_word[0].j_code = tmpHan.j_code;
		tmp_h_word[1].j_code = 0xB4E1;
		tmp_h_word[1].j_han.jong = h_word[dic_result[i].len-1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[dic_result[i].len], sizeof(HANGUL) * (h_word_len - dic_result[i].len));

		ret_val = CheckEomi(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len + 1), (UWORD) 0);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    case 75:
	    case 76:
		/* ㅚ 축약 --> ㅚ + 어 -> ㅙ */
		if (h_word[dic_result[i].len - 1].j_han.jong != 0x01 && 
			h_word[dic_result[i].len - 1].j_han.jong != 0x16) {
		    M_MORPHEME_INDEX = 0; 
		    break;
		}

		M_MORPHEME_INDEX--;
		tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1);
		tmpHan.j_han.jung = 0x12;		/* ㅚ */
		tmpHan.j_han.jong = 0x01;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(dic_result[i].len - 1) = tmpHan.j_code;
		M_MORPHEME_INDEX++;
		tmp_h_word[0].j_code = tmpHan.j_code;
		tmp_h_word[1].j_code = 0xB4E1;
		tmp_h_word[1].j_han.jong = h_word[dic_result[i].len-1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[dic_result[i].len], sizeof(HANGUL) * (h_word_len - dic_result[i].len));

		ret_val = CheckEomi(tmp_h_word, (UWORD) (h_word_len - dic_result[i].len + 1), (UWORD) 0);
		M_MORPHEME_INDEX = 0;
		if (ret_val == 1)
		    M_MORPRESULT_INDEX++;

		break;

	    default :
		M_MORPHEME_INDEX = 0;
		break;
	}
    }
	
    if (M_MORPRESULT_INDEX > 0) 
	return 1;
    else
	return 0;
}
