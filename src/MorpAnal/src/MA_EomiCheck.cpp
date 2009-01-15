/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.02.07
 *
 *	#(Action)#
 *		- 어미부 형태소 추론 엔진
 *		- 선어말 어미 검사, 어미 사전 탐색, 어미부 제약조건 검사
 *  #(Revision History)#
 *		- 선어말 처리루틴 추가 (2000.02.07)
 *		- 어미 사전 탐색 루틴 추가 (2000.02.08)
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_PreEomi.h>
#include <MA_Func.h>
#include <MADIC_Func.h>

/* 어미부 검사 루틴 */
/* h_word는 어미부 한글자 앞에서부터... */
/* Return Value :
   1 --> 어말어미로 끝난 단어..
   2 --> 어말어미가 아닌 다른 형태소로 끝났으나 올바른 단어 */
DWORD
CheckEomi(HANGUL *h_word, UWORD h_word_len, WORD first_jong_only)
{
	DWORD sub_idx = 0, bsub_idx;
	DWORD start_pos = 0;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT edic_result[VS_BUFLEN];
#else
	DIC_RESULT edic_result[VS_BUFLEN];
#endif
	UWORD edic_res_idx = 0;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT bdic_result[VS_BUFLEN];
#else
	DIC_RESULT bdic_result[VS_BUFLEN];
	DIC_RESULT tmp_bdic_result[VS_BUFLEN];
#endif
	UWORD bdic_res_idx = 0;
	UWORD tmp_bdic_res_idx = 0;
	DWORD binfo;
	DWORD ret_val, i;
	HANGUL tmpHan;
	HANGUL tmp_h_word[VS_BUFLEN], tmp_h_word2[VS_BUFLEN];
	UWORD tmp_h_word_len;
	UWORD old_nMorp, chk_jong;
	UWORD bojo_eomi_len, bojo_yong_len, tmp_sub_idx;
	UWORD old_Morpheme_Index, old_MorpResult_Index;
#ifdef MULTI_DIC_INFO
	JEDIC_RESULT jdic_result[VS_BUFLEN];
#else
	DIC_RESULT jdic_result[VS_BUFLEN];
#endif
	UWORD jdic_res_idx = 0;
	UWORD sia_chukyacc = 0;
        BYTE temp_info[VS_BUFLEN];
	DWORD t_idx, tmp_val;


	if (h_word_len == 0 && first_jong_only == 0)
	    return 0;

	tmpHan.j_han.sign = 1;

	old_MorpResult_Index = M_MORPRESULT_INDEX;
	/* 보조용언 사전 검사 */
	chk_jong = first_jong_only;
	ret_val = SearchBojoDic(h_word, (UWORD)h_word_len, first_jong_only, bdic_result, &bdic_res_idx);
	if (ret_val == 1) {
		/* 보조용언 사전 검색 결과 중 info는 연결어미와 보조용언의 경계위치이다 */
		/* 보조용언 사전에는 보조적 연결어미와 결합된 보조용언과...
		   보조적 연결어미가 존재한다...
		   보조적 연결어미는 어절 자체가 보조적연결어미로 끝날 수도 있으므로...
		   추가하였다. */
		old_nMorp = M_CUR_MORPRESULT_NMORP;
		old_Morpheme_Index = M_MORPHEME_INDEX;
		if (bdic_result[bdic_res_idx-1].info == 5) {
/* 다어절에 걸친 보조적 연결어미 + 보조용언 제약조건에 의한 tagging 기능 구현 */
/* 1. 다음 토큰이 어절이 아닐 경우
   2. 다음 토큰이 어절일 때....
			- 다음 어절과 현재 어절이 함께 보조용언 사전에 포함되어 있으면 보조용언으로 분석
			- 그렇지 않으면 일반 어미 분석 
*/
#ifndef NO_HEURISTIC_RULE
/* 
	@ RULE(2)
	#TI=보조용언 결합 제약 조건
	#SU=형태소제약규칙(1)
	#AB=1. 다음 토큰이 어절이 아닐 경우
		2. 다음 토큰이 어절일 때....
			- 다음 어절과 현재 어절이 함께 보조용언 사전에 포함되어 있으면 보조용언으로 분석
			- 그렇지 않으면 일반 어미 분석 
	#TM=2000/05/03
			ret_val = Ref_PreWord(1, tmp_h_word, &tmp_h_word_len);
			if (ret_val != 136 && ret_val != 137)
				goto CHECK_FAIL;

			memcpy(&h_word[h_word_len + 1], tmp_h_word, sizeof(HANGUL) * tmp_h_word_len);
			ret_val = SearchBojoDic(h_word, (UWORD)(h_word_len + tmp_h_word_len), first_jong_only, tmp_bdic_result, &tmp_bdic_res_idx);
			if (ret_val && tmp_bdic_result[tmp_bdic_res_idx-1].len <= bdic_result[bdic_res_idx-1].len)
				goto CHECK_FAIL;
*/
#endif
			/* 형태소 분석 성공... */
			/* 분석 결과 저장 */
			/* 어미로도 분석될 수 있으므로...형태소 분석 결과를 하나더 만든다... */
			memcpy(M_NEXT_MORPRESULT_MI, M_CUR_MORPRESULT_MI, sizeof(tMORP_ITEM) * M_CUR_MORPRESULT_NMORP);

			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (first_jong_only) {
				tmpHan.j_han.cho = 1;
				tmpHan.j_han.jung = 2;
				tmpHan.j_han.jong = h_word[sub_idx].j_han.jong;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), 
					&h_word[sub_idx+1], sizeof(HANGUL) * (bdic_result[bdic_res_idx-1].len-1));
			} else 
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME,
					&h_word[sub_idx+1], sizeof(HANGUL) * bdic_result[bdic_res_idx-1].len);

			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bdic_result[bdic_res_idx-1].len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			/* 일단 어미 세부 정보는 저장하지 않음 */
			strcpy(M_CUR_MORPRESULT_MI_INFO, "BOJOEOMI");
			M_MORPHEME_INDEX = 0;
			/* 성공되었으므로 */
			/*********************************************************************/

			M_MORPRESULT_INDEX++;
		} else {
			/* 어미로 분석될 수도 있고, '보조적연결어미+보조용언' 으로 분석될 수도 있다. */
			/* 보조용언에 대한 불규칙 처리는 알고리즘이 복잡한 관계로 생략한다. 
			   나중에 보조용언의 원형이 필요할 경우 이곳에 불규칙 처리를 추가하면 된다... */
			/********************* 형태소 분석 정보 저장 *************************/
			bsub_idx = 0;
			/* 보조어미 길이 산출 */
			if (bdic_result[bdic_res_idx-1].info > 10)
				bojo_eomi_len = bdic_result[bdic_res_idx-1].info % 10;
			else 
				bojo_eomi_len = bdic_result[bdic_res_idx-1].info;

			M_CUR_MORPRESULT_NMORP++;
			if (first_jong_only) {
				tmpHan.j_han.cho = 1;
				tmpHan.j_han.jung = 2;
				tmpHan.j_han.jong = h_word[bsub_idx].j_han.jong;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[bsub_idx+1], sizeof(HANGUL) * (bojo_eomi_len-1));
			} else 
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[bsub_idx+1], sizeof(HANGUL) * bojo_eomi_len);
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_eomi_len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			/* 일단 어미 세부 정보는 저장하지 않음 */
			strcpy(M_CUR_MORPRESULT_MI_INFO, "BOJOEOMI");

			M_MORPHEME_INDEX++;
			/*********************************************************************/

			if (first_jong_only)
				bsub_idx += bojo_eomi_len;	/* 보조용언이 시작되는 위치를 지정 */
			else
				bsub_idx += bojo_eomi_len + 1;

			bojo_yong_len = bdic_result[bdic_res_idx-1].len - bojo_eomi_len;
			binfo = bdic_result[bdic_res_idx-1].info / 10;
			chk_jong = bdic_result[bdic_res_idx-1].jong;

			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (chk_jong) {
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[bsub_idx], sizeof(HANGUL) * bojo_yong_len);
				tmpHan.j_code = h_word[bsub_idx + bojo_yong_len - 1].j_code;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
			} else
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[bsub_idx], sizeof(HANGUL) * bojo_yong_len);
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			strcpy(M_CUR_MORPRESULT_MI_INFO, "BOJOYONG");

			M_MORPHEME_INDEX++;
			/*********************************************************************/

			bsub_idx += bojo_yong_len;

			/* 보조용언 불규칙 처리 */
			switch (binfo) {
			case 1:		/* 여 */
				if (h_word[bsub_idx-1].j_han.jong != 0x01
					&& h_word[bsub_idx-1].j_han.jong != 0x16)
					goto CHECK_FAIL;
				if (h_word[bsub_idx-1].j_han.jong == 0x16 &&
					bsub_idx > h_word_len)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x1D;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB4E1;	/*어*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;

				break;

			case 2:		/* 와 */
				if (h_word[bsub_idx-1].j_han.jong != 0x01
					&& h_word[bsub_idx-1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x0D;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB461;	/*아*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;

				break;

			case 3:		/* ㄹ 탈락 */
				if (!chk_jong && bsub_idx > h_word_len)
					goto CHECK_FAIL;

				if (chk_jong) {
				/* 놀, 까불, 깨물 등을 처리하기 위해서 2000.06.27 */
					if (h_word[bsub_idx-1].j_han.jong != 0x05 &&
						h_word[bsub_idx-1].j_han.jong != 0x09 &&
						h_word[bsub_idx-1].j_han.jong != 0x13)
						goto CHECK_FAIL;
				} else {
					if (h_word[bsub_idx].j_han.cho != 0x04 &&
						h_word[bsub_idx].j_han.cho != 0x09 &&
						h_word[bsub_idx].j_han.cho != 0x0B &&
						h_word[bsub_idx].j_code != 0xB5A1)
						goto CHECK_FAIL;
				}

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jong = 0x09;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				M_MORPHEME_INDEX++;

				/*
				tmp_h_word[0].j_code = tmpHan.j_code;
				*/
				tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
				tmp_h_word_len = h_word_len - bsub_idx + 1;
				memcpy(&tmp_h_word[1], &h_word[bsub_idx], sizeof(HANGUL) * tmp_h_word_len);
				break;

			case 4:		/* ㅙ 불규칙 */
				if (h_word[bsub_idx - 1].j_han.jong != 0x01 && 
					h_word[bsub_idx - 1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x12;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB4E1;	/*어*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;
				break;

			case 5:
			case 8:
				if (h_word[bsub_idx-1].j_han.jong != 0x01
					&& h_word[bsub_idx-1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				tmpHan.j_code = M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1);
				tmpHan.j_han.jung = 0x14;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len-1) = tmpHan.j_code;
				tmp_h_word[0].j_code = tmpHan.j_code;
				tmp_h_word[1].j_code = 0xB4E1;	/*어*/
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				M_MORPHEME_INDEX++;
				chk_jong = 0;
				break;

			case 6:
				/* 하 --> 해 */
				if (h_word[bsub_idx - 1].j_han.jong != 0x01 && 
					h_word[bsub_idx - 1].j_han.jong != 0x16)
					goto CHECK_FAIL;

				M_MORPHEME_INDEX--;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(bojo_yong_len - 1) = 0xD061;		/*하*/
				M_MORPHEME_INDEX++;
				tmp_h_word[0].j_code = 0xD061;
				tmp_h_word[1].j_code = 0xB4E1;
				tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
				tmp_h_word_len = h_word_len - bsub_idx + 2;
				memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
				chk_jong = 0;
				break;

			case 7:
				if (bsub_idx > h_word_len)
					goto CHECK_FAIL;

				ret_val = D_IrrProc(&h_word[bsub_idx-1], (UWORD) (h_word_len - bsub_idx), bojo_yong_len);
				if (ret_val == 0)
					goto CHECK_FAIL;

				tmp_sub_idx = bsub_idx - 1;

				/* 매개모음 '으' 삽입 규칙 처리 */
				if (chk_jong != 1 && h_word[tmp_sub_idx+1].j_han.cho == 0x0D
					&& h_word[tmp_sub_idx+1].j_han.jung == 0x1B) {		/* -으-*/
					if (h_word[tmp_sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
						if (h_word[tmp_sub_idx+1].j_han.jong != 0x05		/* ㄴ */
							&& h_word[tmp_sub_idx+1].j_han.jong != 0x09	/* ㄹ */
							&& h_word[tmp_sub_idx+1].j_han.jong != 0x13	/* ㅂ */
							&& h_word[tmp_sub_idx+1].j_han.jong != 0x11)	/* ㅁ */
							goto CHECK_FAIL;
						chk_jong = 1;
						tmp_sub_idx++;		/* 으 skip */
					} else {
						tmp_sub_idx++;		/* 으 skip */
						if (h_word_len == tmp_sub_idx)
							goto CHECK_FAIL;
					}
				}

				tmp_h_word_len = h_word_len - tmp_sub_idx;
				memcpy(&tmp_h_word, &h_word[tmp_sub_idx], sizeof(HANGUL) * (tmp_h_word_len+1));

				break;

			default :
				/* 들어가, 들어갔다, 등 처리... */
				/* 돌아가신 --> 처리가 안되서.. 디버깅 */
			/* 
			   총체적으로 처리한다...
			   우선 어간이 "ㅏ"나 "ㅐ"로 끝나는 어절 중에서 "하"로 끝나지 않은 어절을 골라내고...
			   또한 어간 바로 다음 음절이 "아"나 "어"로 시작되는 어미의 바로 다음 음절인 
			   "도", "라", "서", "선", "야", "요", "자", "지" 일 경우에는 생략된 "아"나 "어"를 삽입한다...
			   그러나 이 음절 중에서 "도"와 "지"는 보조용언의 첫음절일 수도 있으므로 두번 검사를 한다. 2000.06.29 
			*/
				if (!chk_jong &&
					(h_word[bsub_idx-1].j_han.jung == 0x03
					|| h_word[bsub_idx-1].j_han.jung == 0x04
					|| h_word[bsub_idx-1].j_han.jung == 0x07) 
					&& h_word[bsub_idx-1].j_code != 0xD061
					&& !IsFirstPreEomiChar(h_word[bsub_idx-1])) {
					if (bsub_idx > h_word_len ||
						(bsub_idx <= h_word_len && 
							(h_word[bsub_idx-1].j_han.jung == 0x03 && IsFirstAEomiChar(h_word[bsub_idx])) ||
							((h_word[bsub_idx-1].j_han.jung == 0x04 || h_word[bsub_idx-1].j_han.jung == 0x07)
							 && IsFirstEoEomiChar(h_word[bsub_idx])))) {
						tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
						tmp_h_word[0].j_han.jong = 0x01;
						if (h_word[bsub_idx-1].j_han.jung == 0x03)
							tmp_h_word[1].j_code = 0xb461; /* 아 */
						else
							tmp_h_word[1].j_code = 0xb4e1; /* 어 */
						tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;

						tmp_h_word_len = h_word_len - bsub_idx + 2;
						memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
						chk_jong = 0;
					} else
						goto NORMAL_PROC_BOJO_CHECK;
				} else if (chk_jong && h_word[bsub_idx-1].j_han.jong == 0x16) {
						tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
						tmp_h_word[0].j_han.jong = 0x01;
						if (YANGSUNG(h_word[bsub_idx-1].j_han.jung) && h_word[bsub_idx-1].j_han.jung != 0x04)
							tmp_h_word[1].j_code = 0xb461; /* 아 */
						else
							tmp_h_word[1].j_code = 0xb4e1; /* 어 */
						tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;

						tmp_h_word_len = h_word_len - bsub_idx + 2;
						memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
						chk_jong = 0;
				} else {
NORMAL_PROC_BOJO_CHECK:
					if (bsub_idx > h_word_len) {
						if (chk_jong && (bsub_idx - h_word_len) == 1)
							;
						/* 놀, 까불, 깨물 등을 처리하기 위해서 2000.06.27 */
						else if (h_word[bsub_idx-1].j_han.jong == 0x09)
							chk_jong = 1;
						else
							goto CHECK_FAIL;
					}
					tmp_h_word_len = h_word_len - bsub_idx + 1;
					memcpy(tmp_h_word, &h_word[bsub_idx-1], sizeof(HANGUL) * (tmp_h_word_len+1));
				}
/*
				if (((h_word[bsub_idx-1].j_code == 0x8861 || h_word[bsub_idx-1].j_code == 0x9061) && !IsFirstPreEomiChar(h_word[bsub_idx-1]))
					|| (chk_jong && h_word[bsub_idx-1].j_han.jong == 0x16)) {
					tmp_h_word[0].j_code = h_word[bsub_idx-1].j_code;
					tmp_h_word[0].j_han.jong = 0x01;
					if (YANGSUNG(h_word[bsub_idx-1].j_han.jung) && h_word[bsub_idx-1].j_han.jung != 0x04)
						tmp_h_word[1].j_code = 0xb461;
					else 
						tmp_h_word[1].j_code = 0xb4e1;
					tmp_h_word[1].j_han.jong = h_word[bsub_idx-1].j_han.jong;
					
					tmp_h_word_len = h_word_len - bsub_idx + 2;
					memcpy(&tmp_h_word[2], &h_word[bsub_idx], sizeof(HANGUL) * (tmp_h_word_len-1));
					chk_jong = 0;
				} else {
					if (bsub_idx > h_word_len) {
						if (chk_jong && (bsub_idx - h_word_len) == 1)
							;
						else if (h_word[bsub_idx-1].j_han.jong == 0x09)
							chk_jong = 1;
						else
							goto CHECK_FAIL;
					}
					tmp_h_word_len = h_word_len - bsub_idx + 1;
					memcpy(tmp_h_word, &h_word[bsub_idx-1], sizeof(HANGUL) * (tmp_h_word_len+1));
				}
*/
				break;
			}
			if (!chk_jong) {
				sub_idx = 0;
				/* 선어말 어미 검사 */
				/* 주의 : 현재 어절에 대해서 선어말어미 검사가 성공한 경우...
						  아래 부분에서 실패했을 때는 이 부분에서 바로 어미 탐색하여...
						  다시한번 검사해야 한다. */
				/* 선어말 어미로 끝나는 단어는 없으므로...
				   현재 어미부는 검색된 선어말어미의 길이보다는 길어야 한다 */
		/* 2007.06.07 : 선어말어미가 몇개 안되므로...그냥 전체 다 검색 */
				start_pos = 0;
#if 0
				if (tmp_h_word_len - 1 >= 5) /* 선어말 어미 중 가장 긴 길이보다 같거나 크면 */
					start_pos = 0;
				else if (tmp_h_word_len - 1 > 1)	/* 그렇지 않으면 출발 지점을 선택 */
					start_pos = len_start[tmp_h_word_len-2];
#endif

				for (i = start_pos; i < PRE_EOMI_LEN; i++) {
					/* 2007.06.07 : 중요한 버그 발견
					 * 비교대상길이가 잘못지정되었음 
					 * 만일 h_word 다음에 가비지가 들어가 있으면 선어말어미로 잘못 인식할 수 있음 */
					if (tmp_h_word_len < pre_eomi[i].len)
						continue;
					if (!memcmp(&tmp_h_word[1], pre_eomi[i].word, pre_eomi[i].len * 2))
						break;
				}

				if (i < PRE_EOMI_LEN) {
					M_CUR_MORPRESULT_NMORP++;
					memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[1], sizeof(HANGUL) * pre_eomi[i].len);
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_eomi[i].len) = 0;

					strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
					M_CUR_MORPRESULT_MI_NINFO = 1;

					M_MORPHEME_INDEX++;

					/* "시" 다음에 어미 "아"가 오면 무조건 틀린 단어... */
					if (pre_eomi[i].len == 1 && i == 36) { /* 시 */
					    if (tmp_h_word[2].j_code == 0xb461) /* 아 */
						goto CHECK_FAIL;
					}
					sub_idx += pre_eomi[i].len;

					/* 일단, 선어말어미로 끝나는 단어는 어미검사를 하지 않고 
					   틀린 어절로 간주한다. */
					if (sub_idx == tmp_h_word_len)
						goto CHECK_FAIL;
					

					/* 매개모음 '으' 삽입 규칙 처리 */
					if (tmp_h_word[sub_idx+1].j_han.cho == 0x0D&& tmp_h_word[sub_idx+1].j_han.jung == 0x1B) { /* -으-*/
					    	if (tmp_h_word[sub_idx].j_han.jong != 0x01 && tmp_h_word[sub_idx].j_han.jong != 0x09) {
							/* 어간에 'ㄹ'이 아닌 받침이 있을 때 */
							if (tmp_h_word[sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
								if (tmp_h_word[sub_idx+1].j_han.jong != 0x05		/* ㄴ */
									&& tmp_h_word[sub_idx+1].j_han.jong != 0x09	/* ㄹ */
									&& tmp_h_word[sub_idx+1].j_han.jong != 0x13	/* ㅂ */
									&& tmp_h_word[sub_idx+1].j_han.jong != 0x11) {	/* ㅁ */
									goto CHECK_FAIL;
								}
								chk_jong = 1;
								sub_idx++;		/* 으 skip */
							} else {
								sub_idx++;		/* 으 skip */
								if (tmp_h_word_len == sub_idx)
									goto CHECK_FAIL;
							}
						}
					}
				} else {
					/* "시"의 종성부터 어미가 붙을 때 */
					if (tmp_h_word[1].j_han.cho == 0x0B && tmp_h_word[1].j_han.jung == 0x1D) {
						M_CUR_MORPRESULT_NMORP++;
						tmpHan.j_code = tmp_h_word[1].j_code;
						tmpHan.j_han.jong = 0x01;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
						strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
						M_CUR_MORPRESULT_MI_NINFO = 1;
						M_MORPHEME_INDEX++;

						sub_idx++;
						chk_jong = 1;
					} else if (tmp_h_word[1].j_code == 0xAD61 /* 셔 */ &&
						(tmp_h_word[2].j_code == 0xB4A1 /* 야 */ ||
						 tmp_h_word[2].j_code == 0xACE1 /* 서 */ ||
						 tmp_h_word[2].j_code == 0x95A1 /* 도 */ ||
						 tmp_h_word[2].j_code == 0xB661 /* 요 */)) {
						/* 오셔, 가셔... 등 처리 : 축약 처리 */
						/* 항상 위의 음절과 같이 쓰인다 */
						M_CUR_MORPRESULT_NMORP++;
						tmpHan.j_code = 0xAFA1; /* 시 */
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
						M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
						strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
						M_CUR_MORPRESULT_MI_NINFO = 1;
						M_MORPHEME_INDEX++;

						sub_idx++;
						memcpy(tmp_h_word2, tmp_h_word, sizeof(HANGUL) * (tmp_h_word_len+1));
						tmp_h_word[1].j_code = 0xAFA1; /* 시 */
						tmp_h_word[2].j_code = 0xB4E1; /* 어 */
						memcpy(&tmp_h_word[3], &tmp_h_word2[2], sizeof(HANGUL) * (tmp_h_word_len-1));
						tmp_h_word_len++;
					}
				}
			}
/**********************************************************************/
			/* 명사형 전성어미 처리 */
			/* 명사형 전성어미는 기본형 동사/형용사에 붙는다 */
			/* ㅁ, 기 */
			if (chk_jong && tmp_h_word[sub_idx].j_han.jong == 0x11) {
				chk_jong = 0;
				/* 명사형 전성어미로 끝난 경우 */
				if (tmp_h_word_len - sub_idx == 0) {
					/* 형태소 분석 성공... */
					/* 분석 결과 저장 */
					/*********************************************************************/
					M_CUR_MORPRESULT_NMORP++;
					tmpHan.j_han.sign = 1;
					tmpHan.j_han.cho = 0x01;
					tmpHan.j_han.jung = 0x02;
					tmpHan.j_han.jong = 0x11;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
					strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
					M_CUR_MORPRESULT_MI_NINFO = 1;

					M_MORPHEME_INDEX = 0;
					M_MORPRESULT_INDEX++;
					/*********************************************************************/

					sub_idx = 0;
					M_MORPHEME_INDEX = old_Morpheme_Index;
					M_CUR_MORPRESULT_NMORP = old_nMorp;
					memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
				} else {
					/* 조사 사전 탐색 */
					/* 기본적인 조사 결합 제약조건 검사 */
					/* 종성 검사를 위해서 조사탐색할 글자의 앞 단어를 넘겨준다 */
					ret_val = SearchJosaDic(&tmp_h_word[sub_idx], (UWORD)(tmp_h_word_len - sub_idx), 
									chk_jong, jdic_result, &jdic_res_idx);
					if (ret_val == 1) {		
						/* 조사가 full-match로 검색되었을 때 */
						/* 일단 조사 사전 탐색에서는 full-match된 경우를 올바른 것으로 본다 */
						ret_val = CheckJosa(tmp_h_word, (UWORD) (sub_idx + 1), chk_jong);
						if (ret_val == 1) {
							/* 형태소 분석 성공... */
							/* 분석 결과 저장 */
							M_CUR_MORPRESULT_NMORP++;
							tmpHan.j_han.sign = 1;
							tmpHan.j_han.cho = 0x01;
							tmpHan.j_han.jung = 0x02;
							tmpHan.j_han.jong = 0x11;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
							strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
							M_CUR_MORPRESULT_MI_NINFO = 1;
							M_MORPHEME_INDEX++;

							/********************* 형태소 분석 정보 저장 *************************/
							M_CUR_MORPRESULT_NMORP++;
							memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[sub_idx+1],
								sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
							M_CUR_MORPRESULT_MI_NINFO = 1;

							/* 다중 조사 세부 정보 저장 */
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

							sub_idx = 0;
							M_MORPHEME_INDEX = old_Morpheme_Index;
							M_CUR_MORPRESULT_NMORP = old_nMorp;
							memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
						}
					}
				}

				chk_jong = 1;
				goto CHECK_FAIL;
			} else if (!chk_jong && tmp_h_word[sub_idx+1].j_han.cho == 0x02 && tmp_h_word[sub_idx+1].j_han.jung == 0x1D) {
				sub_idx++;
				if (tmp_h_word[sub_idx].j_han.jong != 0x01)
					chk_jong = 1;

				/* 명사형 전성어미로 끝난 경우 */
				if (tmp_h_word_len - sub_idx == 0) {
					/* 형태소 분석 성공... */
					/* 분석 결과 저장 */
					M_CUR_MORPRESULT_NMORP++;
					tmpHan.j_code = 0x8BA1;	/*기*/
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
					strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
					M_CUR_MORPRESULT_MI_NINFO = 1;

					M_MORPHEME_INDEX = 0;
					M_MORPRESULT_INDEX++;

					sub_idx = 0;
					M_MORPHEME_INDEX = old_Morpheme_Index;
					M_CUR_MORPRESULT_NMORP = old_nMorp;
					memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
				} else {
					/* 조사 사전 탐색 */
					/* 기본적인 조사 결합 제약조건 검사 */
					/* 종성 검사를 위해서 조사탐색할 글자의 앞 단어를 넘겨준다 */
					ret_val = SearchJosaDic(&tmp_h_word[sub_idx], (UWORD)(tmp_h_word_len - sub_idx), 
									chk_jong, jdic_result, &jdic_res_idx);
					if (ret_val == 1) {		
						/* 조사가 full-match로 검색되었을 때 */
						/* 일단 조사 사전 탐색에서는 full-match된 경우를 올바른 것으로 본다 */
						ret_val = CheckJosa(tmp_h_word, (UWORD) (sub_idx + 1), chk_jong);
						if (ret_val == 1) {
							/* 형태소 분석 성공... */
							/* 분석 결과 저장 */
							M_CUR_MORPRESULT_NMORP++;
							tmpHan.j_code = 0x8BA1;	/*기*/
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
							strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
							M_CUR_MORPRESULT_MI_NINFO = 1;
							M_MORPHEME_INDEX++;

							/********************* 형태소 분석 정보 저장 *************************/
							M_CUR_MORPRESULT_NMORP++;
							if (chk_jong) {
								tmpHan.j_han.cho = 1;
								tmpHan.j_han.jung = 2;
								tmpHan.j_han.jong = tmp_h_word[sub_idx].j_han.jong;
								M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
								memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &tmp_h_word[sub_idx+1],
									sizeof(HANGUL) * (jdic_result[jdic_res_idx-1].len-1));
							} else 
								memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[sub_idx+1],
									sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
							M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
							M_CUR_MORPRESULT_MI_NINFO = 1;

							/* 다중 조사 세부 정보 저장 */
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

							sub_idx = 0;
							M_MORPHEME_INDEX = old_Morpheme_Index;
							M_CUR_MORPRESULT_NMORP = old_nMorp;
							memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);					
						}
					}
				}

				sub_idx--;
				chk_jong = 0;
				goto CHECK_FAIL;
			}

			/* 매개모음 '으' 삽입 규칙 처리 */
			// 2006-08-02 : 중요한 버그 발견!!!
			// - tmp_h_word_len을 고려하지 않고, 무조건 비교를 하니까...
			// - 기존에 tmp_h_word에 남아있던 데이터가 문제를 발생시키고 있음
			// - 따라서 sub_idx+1 위치의 음소비교를 할 때,
			// - tmp_h_word_len을 고려해서 비교하도록 수정
			if ((tmp_h_word_len > sub_idx) && tmp_h_word[sub_idx+1].j_han.cho == 0x0D && tmp_h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -으-*/
				if (tmp_h_word[sub_idx].j_han.jong != 0x01 && tmp_h_word[sub_idx].j_han.jong != 0x09) {
					/* 어간에 'ㄹ'이 아닌 받침이 있을 때 */
					if (tmp_h_word[sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
						if (tmp_h_word[sub_idx+1].j_han.jong != 0x05		/* ㄴ */
							&& tmp_h_word[sub_idx+1].j_han.jong != 0x09	/* ㄹ */
							&& tmp_h_word[sub_idx+1].j_han.jong != 0x13	/* ㅂ */
							&& tmp_h_word[sub_idx+1].j_han.jong != 0x11) {	/* ㅁ */
							goto CHECK_FAIL;
						}
						chk_jong = 1;
						sub_idx++;		/* 으 skip */
					} else {
						sub_idx++;		/* 으 skip */
						if (tmp_h_word_len == sub_idx)
							goto CHECK_FAIL;
					}
				}
			}

/**********************************************************************/
			/* 어미 사전 탐색 */
			ret_val = SearchEomiDic(&tmp_h_word[sub_idx], (UWORD)(tmp_h_word_len - sub_idx), 
						chk_jong, edic_result, &edic_res_idx);
			if (ret_val == 1) {		/* 사전에서 어미가 Full로 존재할 때 */
				/* 형태소 분석 성공... */
				/* 분석 결과 저장 */
				/********************* 형태소 분석 정보 저장 *************************/
				M_CUR_MORPRESULT_NMORP++;
				if (chk_jong) {
					tmpHan.j_han.sign = 1;
					tmpHan.j_han.cho = 1;
					tmpHan.j_han.jung = 2;
					tmpHan.j_han.jong = tmp_h_word[sub_idx].j_han.jong;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &tmp_h_word[sub_idx+1],
						sizeof(HANGUL) * (edic_result[edic_res_idx-1].len-1));
				} else 
					memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &tmp_h_word[sub_idx+1], 
						sizeof(HANGUL) * edic_result[edic_res_idx-1].len);

				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(edic_result[edic_res_idx-1].len) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;
				/* 다중 조사 세부 정보 저장 */
				strcpy(M_CUR_MORPRESULT_MI_INFO, "E");

				t_idx = edic_res_idx-1;
				tmp_val = edic_result[t_idx].len;
				while (t_idx >= 0 && tmp_val == edic_result[t_idx].len) {
				    sprintf(temp_info, "%d", edic_result[t_idx].info);
				    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
				    t_idx--;
				}

				M_MORPRESULT_INDEX++;
				/*********************************************************************/

				sub_idx = 0;
				memcpy(M_CUR_MORPRESULT_MI, M_PREV_MORPRESULT_MI, sizeof(tMORP_ITEM) * old_nMorp);
			} else {
CHECK_FAIL:
				sub_idx = 0;
			}
		}
		M_MORPHEME_INDEX = old_Morpheme_Index;
		M_CUR_MORPRESULT_NMORP = old_nMorp;

	}

	if (!first_jong_only) {
		/* 선어말 어미 검사 */
		/* 주의 : 현재 어절에 대해서 선어말어미 검사가 성공한 경우...
		          아래 부분에서 실패했을 때는 이 부분에서 바로 어미 탐색하여...
				  다시한번 검사해야 한다. */
		/* 선어말 어미로 끝나는 단어는 없으므로...
		   현재 어미부는 검색된 선어말어미의 길이보다는 길어야 한다 */

		/* 2007.06.07 : 선어말어미가 몇개 안되므로...그냥 전체 다 검색 */
		start_pos = 0;
#if 0
		if (h_word_len - 1 >= 5) /* 선어말 어미 중 가장 긴 길이보다 같거나 크면 */
			start_pos = 0;
		else if (h_word_len - 1 > 1)	/* 그렇지 않으면 출발 지점을 선택 */
			start_pos = len_start[h_word_len-2];
#endif

		for (i = start_pos; i < PRE_EOMI_LEN; i++) {
			/* 2007.06.07 : 중요한 버그 발견
			 * 비교대상길이가 잘못지정되었음 
			 * 만일 h_word 다음에 가비지가 들어가 있으면 선어말어미로 잘못 인식할 수 있음*/
			if (h_word_len < pre_eomi[i].len)
				continue;
			if (!memcmp(&h_word[1], pre_eomi[i].word, pre_eomi[i].len * 2))
				break;
		}

		if (i < PRE_EOMI_LEN) {
			M_CUR_MORPRESULT_NMORP++;
			memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[1], sizeof(HANGUL) * pre_eomi[i].len);
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(pre_eomi[i].len) = 0;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
			M_CUR_MORPRESULT_MI_NINFO = 1;

			M_MORPHEME_INDEX++;

			sub_idx += pre_eomi[i].len;


			/* 일단, 선어말어미로 끝나는 단어는 어미검사를 하지 않고 
			   틀린 어절로 간주한다. */
			if (sub_idx == h_word_len) {
				if (M_MORPRESULT_INDEX > old_MorpResult_Index)
					return 2;
				return 0;
			}
			/* "시" 다음에 어미 "아"가 오면 무조건 틀린 단어... */
			if (i == 36) { /* 시 */
			    if (h_word[2].j_code == 0xb461) /* 아 */
				return 0;
			}

			/* 매개모음 '으' 삽입 규칙 처리 */
			if (h_word[sub_idx+1].j_han.cho == 0x0D	&& h_word[sub_idx+1].j_han.jung == 0x1B) {		/* -으-*/
				if (h_word[sub_idx].j_han.jong != 0x01 && h_word[sub_idx].j_han.jong != 0x09) {
					/* 어간에 'ㄹ'이 아닌 받침이 있을 때 */
					if (h_word[sub_idx+1].j_han.jong != 0x01) { /* '으' 밑에 받침이 있을 때 */
						if (h_word[sub_idx+1].j_han.jong != 0x05		/* ㄴ */
							&& h_word[sub_idx+1].j_han.jong != 0x09	/* ㄹ */
							&& h_word[sub_idx+1].j_han.jong != 0x13	/* ㅂ */
							&& h_word[sub_idx+1].j_han.jong != 0x11) {	/* ㅁ */
							if (M_MORPRESULT_INDEX > old_MorpResult_Index)
								return 2;
							return 0;
						}
						first_jong_only = 1;
						sub_idx++;		/* 으 skip */
					} else {
						sub_idx++;		/* 으 skip */
						if (h_word_len == sub_idx) {
							if (M_MORPRESULT_INDEX > old_MorpResult_Index)
								return 2;
							return 0;
						}
					}
				}
			}
		} else {
			/* "시"의 종성부터 어미가 붙을 때 */
			if (h_word[1].j_han.cho == 0x0B && h_word[1].j_han.jung == 0x1D) {
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_code = h_word[1].j_code;
				tmpHan.j_han.jong = 0x01;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;
				
				first_jong_only = 1;
				sub_idx++;
			}  else if (h_word[1].j_code == 0xAD61 /* 셔 */ &&
						(h_word_len == 1 ||
						 h_word[2].j_code == 0xB4A1 /* 야 */ ||
						 h_word[2].j_code == 0xACE1 /* 서 */ ||
						 h_word[2].j_code == 0x95A1 /* 도 */ ||
						 h_word[2].j_code == 0xB661 /* 요 */)) {
				/* 오셔, 가셔... 등 처리 : 축약 처리 */
				/* 항상 위의 음절과 같이 쓰인다 */
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_code = 0xAFA1; /* 시 */
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "PRE_EOMI");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;

				sub_idx++;
				memcpy(tmp_h_word2, h_word, sizeof(HANGUL) * (h_word_len+1));
				h_word[1].j_code = 0xAFA1; /* 시 */
				h_word[2].j_code = 0xB4E1; /* 어 */
				memcpy(&h_word[3], &tmp_h_word2[2], sizeof(HANGUL) * (h_word_len-1));
				h_word_len++;

				sia_chukyacc = 1;
			}
		}
	}

	/* 명사형 전성어미 처리 */
	/* 명사형 전성어미는 기본형 동사/형용사에 붙는다 */
	/* ㅁ, 기 */
	chk_jong = first_jong_only;
	if (chk_jong && h_word[sub_idx].j_han.jong == 0x11) {
		chk_jong = 0;
		/* 명사형 전성어미로 끝난 경우 */
		if (h_word_len - sub_idx == 0) {
			/* 형태소 분석 성공... */
			/* 분석 결과 저장 */
			M_CUR_MORPRESULT_NMORP++;
			tmpHan.j_han.sign = 1;
			tmpHan.j_han.cho = 0x01;
			tmpHan.j_han.jung = 0x02;
			tmpHan.j_han.jong = 0x11;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
			M_CUR_MORPRESULT_MI_NINFO = 1;
			M_MORPHEME_INDEX = 0;

			return 1;
		}
		/* 조사 사전 탐색 */
		/* 기본적인 조사 결합 제약조건 검사 */
		/* 종성 검사를 위해서 조사탐색할 글자의 앞 단어를 넘겨준다 */
		ret_val = SearchJosaDic(&h_word[sub_idx], (UWORD)(h_word_len - sub_idx), 
						chk_jong, jdic_result, &jdic_res_idx);
		if (ret_val == 1) {		
			/* 조사가 full-match로 검색되었을 때 */
			/* 일단 조사 사전 탐색에서는 full-match된 경우를 올바른 것으로 본다 */
			ret_val = CheckJosa(h_word, (UWORD) (sub_idx + 1), chk_jong);
			if (ret_val == 1) {
				/* 형태소 분석 성공... */
				/* 분석 결과 저장 */
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = 0x01;
				tmpHan.j_han.jung = 0x02;
				tmpHan.j_han.jong = 0x11;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;

				/********************* 형태소 분석 정보 저장 *************************/
				M_CUR_MORPRESULT_NMORP++;
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[sub_idx+1], sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;
				/* 다중 조사 세부 정보 저장 */
				strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

				t_idx = jdic_res_idx-1;
				tmp_val = jdic_result[t_idx].len;
				while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
				    sprintf(temp_info, "%d", jdic_result[t_idx].info);
				    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
				    t_idx--;
				}

				M_MORPHEME_INDEX = 0;
				/*********************************************************************/

				return 1;
			}
		}

		chk_jong = 1;
	} else if (!chk_jong && h_word[sub_idx+1].j_han.cho == 0x02 && h_word[sub_idx+1].j_han.jung == 0x1D) {
		sub_idx++;
		if (h_word[sub_idx].j_han.jong != 0x01)
			chk_jong = 1;

		/* 명사형 전성어미로 끝난 경우 */
		if (h_word_len - sub_idx == 0) {
			/* 형태소 분석 성공... */
			/* 분석 결과 저장 */
			M_CUR_MORPRESULT_NMORP++;
			tmpHan.j_code = 0x8BA1;	/*기*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;
			strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
			M_MORPHEME_INDEX = 0;

			return 1;
		}

		/* 조사 사전 탐색 */
		/* 기본적인 조사 결합 제약조건 검사 */
		/* 종성 검사를 위해서 조사탐색할 글자의 앞 단어를 넘겨준다 */
		ret_val = SearchJosaDic(&h_word[sub_idx], (UWORD)(h_word_len - sub_idx), 
						chk_jong, jdic_result, &jdic_res_idx);
		if (ret_val == 1) {		
			/* 조사가 full-match로 검색되었을 때 */
			/* 일단 조사 사전 탐색에서는 full-match된 경우를 올바른 것으로 본다 */
			ret_val = CheckJosa(h_word, (UWORD) (sub_idx + 1), chk_jong);
			if (ret_val == 1) {
				/* 형태소 분석 성공... */
				/* 분석 결과 저장 */
				M_CUR_MORPRESULT_NMORP++;
				tmpHan.j_code = 0x8BA1;	/*기*/
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");
				M_CUR_MORPRESULT_MI_NINFO = 1;
				M_MORPHEME_INDEX++;

				/********************* 형태소 분석 정보 저장 *************************/
				M_CUR_MORPRESULT_NMORP++;
				if (chk_jong) {
					tmpHan.j_han.cho = 1;
					tmpHan.j_han.jung = 2;
					tmpHan.j_han.jong = h_word[sub_idx].j_han.jong;
					M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
					memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[sub_idx+1],
						sizeof(HANGUL) * (jdic_result[jdic_res_idx-1].len-1));
				} else 
					memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[sub_idx+1], 
						sizeof(HANGUL) * jdic_result[jdic_res_idx-1].len);
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(jdic_result[jdic_res_idx-1].len) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;

				/* 다중 조사 세부 정보 저장 */
				strcpy(M_CUR_MORPRESULT_MI_INFO, "J");

				t_idx = jdic_res_idx-1;
				tmp_val = jdic_result[t_idx].len;
				while (t_idx >= 0 && tmp_val == jdic_result[t_idx].len) {
				    sprintf(temp_info, "%d", jdic_result[t_idx].info);
				    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
				    t_idx--;
				}

				M_MORPHEME_INDEX = 0;
				/*********************************************************************/
				return 1;
			}
		}

		sub_idx--;
		chk_jong = 0;
	}

	/* 어미 사전 탐색 */
	ret_val = SearchEomiDic(&h_word[sub_idx], (UWORD)(h_word_len - sub_idx), 
				chk_jong, edic_result, &edic_res_idx);
	if (ret_val == 1) {		/* 사전에서 어미가 Full로 존재할 때 */
			/* 형태소 분석 성공... */
			/* 분석 결과 저장 */
			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			if (chk_jong) {
				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = 1;
				tmpHan.j_han.jung = 2;
				tmpHan.j_han.jong = h_word[sub_idx].j_han.jong;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
				memcpy(&(M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1)), &h_word[sub_idx+1], 
					sizeof(HANGUL) * (edic_result[edic_res_idx-1].len-1));
			} else 
				memcpy(M_CUR_MORPRESULT_MI_MORPHEME, &h_word[sub_idx+1],
					sizeof(HANGUL) * edic_result[edic_res_idx-1].len);

			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(edic_result[edic_res_idx-1].len) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			/* 다중 조사 세부 정보 저장 */
			strcpy(M_CUR_MORPRESULT_MI_INFO, "E");

			t_idx = edic_res_idx-1;
			tmp_val = edic_result[t_idx].len;
			while (t_idx >= 0 && tmp_val == edic_result[t_idx].len) {
			    sprintf(temp_info, "%d", edic_result[t_idx].info);
			    strcat(M_CUR_MORPRESULT_MI_INFO, temp_info);
			    t_idx--;
			}
			/*********************************************************************/
			if (sia_chukyacc)
				memcpy(h_word, tmp_h_word2, sizeof(HANGUL)*h_word_len);


			return 1;
	}

	if (sia_chukyacc)
		memcpy(h_word, tmp_h_word2, sizeof(HANGUL)*h_word_len);

	if (M_MORPRESULT_INDEX > old_MorpResult_Index)
		return 2;

	return 0;
}

DWORD IsFirstPreEomiChar(HANGUL one_char)
{
	switch (one_char.j_code) {
		case 0xB761:
		case 0xAFA1:
		case 0xAD76:
		case 0xB476:
		case 0xB4E1:
		case 0xB4F6:
		case 0xB576:
		case 0x9C61:
		case 0xB5B3:
		case 0x8956:
		case 0x94E1:
			return 1;
		default :
			return 0;
	}

	return 0;
}

/* "아"로 시작되는 어미의 다음 글자인지 검사 */
DWORD IsFirstAEomiChar(HANGUL one_char)
{
	switch (one_char.j_code) {
	case 0xd061: /*도*/
	case 0x95a1: /*라*/
	case 0x9c61: /*서*/
	case 0xace1: /*선*/
	case 0xb4a1: /*야*/
	case 0xb661: /*요*/
	case 0xb861: /*자*/
	case 0xbba1: /*지*/
		return 1;
	default :
		return 0;
	}

	return 0;
}

/* "어"로 시작되는 어미의 다음 글자인지 검사 */
DWORD IsFirstEoEomiChar(HANGUL one_char)
{
	switch (one_char.j_code) {
	case 0xd061: /*도*/
	case 0x95a1: /*라*/
	case 0x9c61: /*서*/
	case 0xace1: /*선*/
	case 0xb4a1: /*야*/
	case 0xb661: /*요*/
	case 0xa165: /*면*/
	case 0xb3a2: /*씩*/
		return 1;
	default :
		return 0;
	}

	return 0;
}
