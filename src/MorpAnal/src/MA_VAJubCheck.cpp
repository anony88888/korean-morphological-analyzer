/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_VAJubCheck.c)#  SPASIS System,     2000.02.15
 *
 *	#(Action)#
 *		- 체언 다음에 붙는 동사형/형용사형 접사 처리루틴...
 *		- 되다, 하다, 스럽다, 답다, 있다, 없다...
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MA_VAJubsa.h>
#include <MA_Func.h>

DWORD VAJubSaProc(HANGUL *h_word, UWORD h_word_len, UWORD info)
{
	DWORD i;
	UWORD old_char;
	DWORD ret_val;
	WORD chk_jong = 0, pre_chk_jong = 0;

	for (i = 0; i < VAJUBSA_NUM; i++) {
		if (h_word_len >= va_jubsa[i].len && !memcmp(&h_word[1], va_jubsa[i].word, sizeof(HANGUL)*va_jubsa[i].len))
			break;
		if (h_word_len >= va_jubsa[i].len && h_word[va_jubsa[i].len].j_han.jong != 0x01) {
			old_char = h_word[va_jubsa[i].len].j_code;
			h_word[va_jubsa[i].len].j_han.jong = 0x01;
			if (!memcmp(&h_word[1], va_jubsa[i].word, sizeof(HANGUL)*va_jubsa[i].len)) {
				h_word[va_jubsa[i].len].j_code = old_char;
				pre_chk_jong = 1;
				break;
			}
			h_word[va_jubsa[i].len].j_code = old_char;
		}
	}

	if (i < VAJUBSA_NUM) {
		switch (i) {
		case 0:
		case 1:
			if (info != 33 && info != 34)
				return 0;
			/* 당하/당해 */
			if (i != 1 && h_word_len == 2 && pre_chk_jong == 0)
				return 0;
			ret_val = CheckDangHaDa(h_word + 1, (UWORD) (h_word_len - 1), (WORD) 0);
			return ret_val;
		case 2:
		case 3:
			/* 시키/시켜 */
			if (i != 3 && h_word_len == 2 && pre_chk_jong == 0)
				return 0;
			ret_val = CheckSiKiDa(h_word + 1, (UWORD) (h_word_len - 1), (WORD) 0);
			return ret_val;
		case 4:
		case 5:
			if (info != 33 && info != 34)
				return 0;
			if (h_word_len == 2 && pre_chk_jong == 0)
				return 0;
			/* 스럽/스러 */
			ret_val = CheckSeuRubDa(h_word, h_word_len, 0);
			return ret_val;
		case 6:
		case 7:
			/* 하/해 */
			if (info != 33 && info != 34)
				return 0;
			if (i != 7 && h_word_len == 1 && pre_chk_jong == 0)
				return 0;
			ret_val = CheckHaDa(h_word, h_word_len, 0);
			return ret_val;
		case 8:
		case 9:
			/* 되/돼 */
			if (i != 9 && h_word_len == 1 && pre_chk_jong == 0)
				return 0;
			ret_val = CheckDoiDa(h_word, h_word_len, 0);
			return ret_val;
		case 10:
		case 11:
			/* 롭/로 */
			if (info != 34)
				return 0;
			if (h_word_len == 1)
				return 0;
			if (h_word[0].j_han.jong != 0x01)
				return 0;

			ret_val = CheckRobDa(h_word, h_word_len, 0);
			return ret_val;
		case 12:
		case 13:
			/* 답/다 */
			if (h_word_len == 1)
				return 0;
			ret_val = CheckDabDa(h_word, h_word_len, 0);
			return ret_val;
		case 14:
			/* 있 */
			if (h_word_len == 1)
				return 0;
			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xB7B6;	/*있*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "ISSDA");

			M_MORPHEME_INDEX++;
			/*********************************************************************/
			/* 으 매개 모음 처리 */
			chk_jong = 0;
			if (h_word[2].j_han.cho == 0x0D && h_word[2].j_han.jung == 0x1B) {
				if (h_word[2].j_han.jong != 0x01)
					chk_jong = 1;
				ret_val = CheckEomi(&h_word[2], (UWORD) (h_word_len - 2), chk_jong);
			} else 
				ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), 0);

			return (ret_val);
		case 15:
			/* 없 */
			if (h_word_len == 1)
				return 0;
			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xB4F4;	/*없*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "EUBSDA");

			M_MORPHEME_INDEX++;
			/*********************************************************************/
			/* 으 매개 모음 처리 */
			chk_jong = 0;
			if (h_word[2].j_han.cho == 0x0D && h_word[2].j_han.jung == 0x1B) {
				if (h_word[2].j_han.jong != 0x01)
					chk_jong = 1;
				ret_val = CheckEomi(&h_word[2], (UWORD) (h_word_len - 2), chk_jong);
			} else 
				ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), 0);

			return (ret_val);
		case 16:
			/* 같 */
			if (h_word_len == 1)
				return 0;
			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x887B;	/*같*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "GATDA");

			M_MORPHEME_INDEX++;
			/*********************************************************************/
			/* 으 매개 모음 처리 */
			chk_jong = 0;
			if (h_word[2].j_han.cho == 0x0D && h_word[2].j_han.jung == 0x1B) {
				if (h_word[2].j_han.jong != 0x01)
					chk_jong = 1;
				ret_val = CheckEomi(&h_word[2], (UWORD) (h_word_len - 2), chk_jong);
			} else 
				ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), (WORD) 0);

			return (ret_val);

		case 17:
			/* 치 */
			if (info != 33 && info != 34)
				return 0;
			if (h_word_len != 1)
				return 0;
			if (pre_chk_jong == 1)
			    return 0;

			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xD061;	/*하*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "HADA");

			M_MORPHEME_INDEX++;
			/*********************************************************************/

			/********************* 형태소 분석 정보 저장 *************************/
			M_CUR_MORPRESULT_NMORP++;
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xBBA1;	/*지*/
			M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
			M_CUR_MORPRESULT_MI_NINFO = 1;

			strcpy(M_CUR_MORPRESULT_MI_INFO, "E3");

			M_MORPHEME_INDEX++;
			/*********************************************************************/

			return 1;

		case 18:
			/* 키 */
			/* ~키로 만 처리 */
			if (info != 33)
				return 0;
			if (h_word_len == 2 && h_word[2].j_code == 0x9DA1 /* 로 */) {
				/********************* 형태소 분석 정보 저장 *************************/
				M_CUR_MORPRESULT_NMORP++;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xD061;	/*하*/
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;

				strcpy(M_CUR_MORPRESULT_MI_INFO, "HADA");

				M_MORPHEME_INDEX++;
				/*********************************************************************/

				/********************* 형태소 분석 정보 저장 *************************/
				M_CUR_MORPRESULT_NMORP++;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x8BA1;	/*기*/
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;

				strcpy(M_CUR_MORPRESULT_MI_INFO, "MJUNSUNG");

				M_MORPHEME_INDEX++;
				/*********************************************************************/

				/********************* 형태소 분석 정보 저장 *************************/
				M_CUR_MORPRESULT_NMORP++;
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9DA1;	/*로*/
				M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
				M_CUR_MORPRESULT_MI_NINFO = 1;

				strcpy(M_CUR_MORPRESULT_MI_INFO, "J12");

				M_MORPHEME_INDEX++;
				/*********************************************************************/

				return 1;
			} else
				return 0;
		default:
			break;
		} 
	}

	return 0;
}

DWORD CheckDabDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	UWORD sub_idx, chk_jong, ret_val;
	HANGUL tmp_h_word[VS_BUFLEN];

	if (h_word[1].j_han.jong == 0x13) {
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9473;	/*답*/
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "DABDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), (WORD) 0);

		return (ret_val);
	}

	/********************* 형태소 분석 정보 저장 *************************/
	M_CUR_MORPRESULT_NMORP++;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9473;	/*답*/
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
	M_CUR_MORPRESULT_MI_NINFO = 1;

	strcpy(M_CUR_MORPRESULT_MI_INFO, "DABDA");

	M_MORPHEME_INDEX++;
	/*********************************************************************/

	sub_idx = 1;
	chk_jong = 0;

	/* ㅂ 불규칙 처리 중에 어미부가 수정될 수 있으므로 */
	memcpy(tmp_h_word, h_word + 1, sizeof(HANGUL) * h_word_len);

	/* 'ㅂ' 불규칙 처리 루틴 호출 */
	ret_val = B_IrrProc(h_word + 1, (UWORD) (h_word_len - 1), (UWORD) 1, &sub_idx, &chk_jong);
	if (ret_val == 0) {
		memcpy(h_word + 1, tmp_h_word, sizeof(HANGUL) * h_word_len);

		return (ret_val);
	}

	/* 어미 분석 루틴 호출 */
	ret_val = CheckEomi(&h_word[sub_idx], (UWORD) (h_word_len - sub_idx), chk_jong);
	memcpy(h_word, tmp_h_word, sizeof(HANGUL) * h_word_len);

	return (ret_val);
}

DWORD CheckRobDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	UWORD sub_idx, chk_jong, ret_val;
	HANGUL tmp_h_word[VS_BUFLEN];

	if (h_word[1].j_han.jong == 0x13) {
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9DB3;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "ROBDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), (WORD)0);

		return (ret_val);
	}

	/********************* 형태소 분석 정보 저장 *************************/
	M_CUR_MORPRESULT_NMORP++;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9DB3;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
	M_CUR_MORPRESULT_MI_NINFO = 1;

	strcpy(M_CUR_MORPRESULT_MI_INFO, "ROBDA");

	M_MORPHEME_INDEX++;
	/*********************************************************************/

	sub_idx = 1;
	chk_jong = 0;

	/* ㅂ 불규칙 처리 중에 어미부가 수정될 수 있으므로 */
	memcpy(tmp_h_word, h_word + 1, sizeof(HANGUL) * h_word_len);

	/* 'ㅂ' 불규칙 처리 루틴 호출 */
	ret_val = B_IrrProc(h_word + 1, (UWORD) (h_word_len - 1), (UWORD) 1, &sub_idx, &chk_jong);
	if (ret_val == 0) {
		memcpy(h_word + 1, tmp_h_word, sizeof(HANGUL) * h_word_len);

		return (ret_val);
	}

	/* 어미 분석 루틴 호출 */
	ret_val = CheckEomi(&h_word[sub_idx], (UWORD) (h_word_len - sub_idx), chk_jong);
	memcpy(h_word, tmp_h_word, sizeof(HANGUL) * h_word_len);

	return (ret_val);
}

DWORD CheckSiKiDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	HANGUL tmp_h_word[VS_BUFLEN];
	UWORD tmp_h_word_len;
	UWORD chk_jong = 0;
	DWORD ret_val;

	if (h_word[1].j_han.jung == 0x1D) {
		if (h_word[1].j_han.jong == 0x01 && h_word_len <= 1)
			return 0;
		if (h_word[1].j_han.jong == 0x16)
			return 0;
		if (h_word[1].j_han.jong != 0x01)
			chk_jong = 1;

		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xafa1;	/*시*/
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0xc7a1;	/*키*/
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "SIKIDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/

		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), chk_jong);
		return (ret_val);
	}

	if (h_word[1].j_han.jung == 0x0B) {
		tmp_h_word[0].j_code = 0xc7a1;	/*키*/
		tmp_h_word[1].j_code = 0xb4e1;	/*어*/
		tmp_h_word[1].j_han.jong = h_word[1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[2], sizeof(HANGUL) * (h_word_len - 1));
		tmp_h_word_len = h_word_len;				/* 하나 추가되었다 */
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xafa1;	/*시*/
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0xc7a1;	/*키*/
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "SIKIDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(tmp_h_word, tmp_h_word_len, 0);
		return (ret_val);
	}

	return 0;
}

DWORD CheckDangHaDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	UWORD chk_jong = 0;
	UWORD f_ch = 0;
	HANGUL tmpHan;
	HANGUL tmp_h_word[VS_BUFLEN];
	UWORD tmp_h_word_len;
	UWORD ret_val;

	if (h_word[1].j_han.jung == 0x03) {
		if (h_word[1].j_han.jong == 0x01 && h_word_len <= 1)
			return 0;
		if (h_word[1].j_han.jong == 0x16)
			return 0;

		if (h_word[1].j_han.jong != 0x01)
			chk_jong = 1;
		if (h_word[2].j_han.cho == 0x0D && h_word[2].j_han.jung == 0x0B) {
			h_word[2].j_han.jung = 0x07;
			f_ch = 1;
		}
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9477;
		tmpHan.j_code = h_word[1].j_code;
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "DANGHADA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), chk_jong);

		if (f_ch == 1)
			h_word[2].j_han.jung = 0x0B;

		return ret_val;
	}

	if (h_word[1].j_han.jung == 0x04) {			/* ㅐ */
		tmp_h_word[0].j_code = 0xD061;			/* 하 */
		tmp_h_word[1].j_code = 0xB4E1;			/* 어 */
		tmp_h_word[1].j_han.jong = h_word[1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[2], sizeof(HANGUL) * (h_word_len - 1));
		tmp_h_word_len = h_word_len;				/* 하나 추가되었다 */
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0x9477;
		tmpHan.j_code = 0xD061;				/* 하 */
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "DANGHADA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(tmp_h_word, tmp_h_word_len, 0);
		return ret_val;
	}

	return 0;
}

DWORD CheckDoiDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	UWORD chk_jong = 0;
	HANGUL tmp_h_word[VS_BUFLEN];
	HANGUL tmpHan;
	UWORD tmp_h_word_len;
	DWORD ret_val;

	if (h_word[1].j_han.jung == 0x12) {				/* ㅚ */
		if (h_word[1].j_han.jong == 0x01 && h_word_len == 1)
			return 0;
		if (h_word[1].j_han.jong != 0x01)
			chk_jong = 1;
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		tmpHan.j_code = h_word[1].j_code;
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "DOIDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), chk_jong);

		return ret_val;
	} else if (h_word[1].j_han.jung == 0x0F) {		/* ㅙ */
		tmp_h_word[0].j_code = 0x9641;				/* 되 */
		tmp_h_word[1].j_code = 0xB4E1;				/* 어 */
		tmp_h_word[1].j_han.jong = h_word[1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[2], sizeof(HANGUL) * (h_word_len - 1));
		tmp_h_word_len = h_word_len;				/* 하나 추가되었다 */
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		tmpHan.j_code = 0x9641;				/* 되 */
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "DOIDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(tmp_h_word, tmp_h_word_len, 0);
		return ret_val;
	}

	return 0;
}

DWORD CheckHaDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	UWORD chk_jong = 0;
	UWORD f_ch = 0;
	HANGUL tmpHan;
	HANGUL tmp_h_word[VS_BUFLEN];
	UWORD tmp_h_word_len;
	UWORD ret_val;

	if (h_word[1].j_han.jung == 0x03) {
		if (h_word[1].j_han.jong == 0x01 && h_word_len <= 1)
			return 0;
		if (h_word[1].j_han.jong == 0x16)
			return 0;

		if (h_word[1].j_han.jong != 0x01)
			chk_jong = 1;
		if (h_word[2].j_han.cho == 0x0D && h_word[2].j_han.jung == 0x0B) {
			h_word[2].j_han.jung = 0x07;
			f_ch = 1;
		}
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		tmpHan.j_code = h_word[1].j_code;
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "HADA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(&h_word[1], (UWORD) (h_word_len - 1), chk_jong);

		if (f_ch == 1)
			h_word[2].j_han.jung = 0x0B;

		return ret_val;
	}

	if (h_word[1].j_han.jung == 0x04) {			/* ㅐ */
		tmp_h_word[0].j_code = 0xD061;			/* 하 */
		tmp_h_word[1].j_code = 0xB4E1;			/* 어 */
		tmp_h_word[1].j_han.jong = h_word[1].j_han.jong;
		memcpy(&tmp_h_word[2], &h_word[2], sizeof(HANGUL) * (h_word_len - 1));
		tmp_h_word_len = h_word_len;				/* 하나 추가되었다 */
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		tmpHan.j_code = 0xD061;				/* 하 */
		tmpHan.j_han.jong = 1;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmpHan.j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "HADA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(tmp_h_word, tmp_h_word_len, 0);
		return ret_val;
	}

	return 0;
}

DWORD CheckSeuRubDa(HANGUL *h_word, UWORD h_word_len, UWORD jong)
{
	UWORD sub_idx, chk_jong, ret_val;
	HANGUL tmp_h_word[VS_BUFLEN];
	HANGUL *pHan;

	/* 사랑스런, 자랑스런 처리... 2000.06.29 */
	if (h_word[2].j_han.jong == 0x05 && h_word_len == 2) {
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xAF61;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0x9CF3;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "SRUBDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		M_CUR_MORPRESULT_NMORP++;
		tmp_h_word[0].j_han.sign = 1;
		tmp_h_word[0].j_han.cho = 1;
		tmp_h_word[0].j_han.jung = 2;
		tmp_h_word[0].j_han.jong = h_word[2].j_han.jong;

		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = tmp_h_word[0].j_code;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "E5");

		M_MORPHEME_INDEX++;

		return 1;
	}

	if (h_word[2].j_han.jong == 0x13) {
		/********************* 형태소 분석 정보 저장 *************************/
		M_CUR_MORPRESULT_NMORP++;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xAF61;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0x9CF3;
		M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
		M_CUR_MORPRESULT_MI_NINFO = 1;

		strcpy(M_CUR_MORPRESULT_MI_INFO, "SRUBDA");

		M_MORPHEME_INDEX++;
		/*********************************************************************/
		ret_val = CheckEomi(&h_word[2], (UWORD) (h_word_len - 2), 0);

		return (ret_val);
	}

	/********************* 형태소 분석 정보 저장 *************************/
	M_CUR_MORPRESULT_NMORP++;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(0) = 0xAF61;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(1) = 0x9CF3;
	M_CUR_MORPRESULT_MI_MORPHEME_ITEM(2) = 0;
	M_CUR_MORPRESULT_MI_NINFO = 1;

	strcpy(M_CUR_MORPRESULT_MI_INFO, "SRUBDA");

	M_MORPHEME_INDEX++;
	/*********************************************************************/

	pHan = h_word + 1;
	sub_idx = 1;
	chk_jong = 0;

	/* ㅂ 불규칙 처리 중에 어미부가 수정될 수 있으므로 */
	memcpy(tmp_h_word, pHan, sizeof(HANGUL) * h_word_len);

	/* 'ㅂ' 불규칙 처리 루틴 호출 */
	ret_val = B_IrrProc(&pHan[sub_idx], (UWORD) (h_word_len - 2), (WORD) 2, &sub_idx, &chk_jong);
	if (ret_val == 0) {
		memcpy(pHan, tmp_h_word, sizeof(HANGUL) * h_word_len);

		return (ret_val);
	}

	/* 어미 분석 루틴 호출 */
	ret_val = CheckEomi(&pHan[sub_idx], (UWORD) (h_word_len - sub_idx - 1), chk_jong);
	memcpy(pHan, tmp_h_word, sizeof(HANGUL) * h_word_len);

	return (ret_val);
}
