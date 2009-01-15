/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(BD_MakeHanBuf.c)#  SPASIS System,     Mon Nov 15 13:40:13 1999
 *
 *	#(Action)#
 *		입력으로 들어온 한글 스트링을 내부 버퍼에 저장
 *		알파벳은 1바이트이므로 같은 알파벳 2개가 저장 
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_HanCode.h>
#include <MA_Func.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>

/*
 * 순수하게 완성형 한글을 조합형으로 변환
 */
DWORD Wan2Jo(UBYTE *str, HANGUL *han_buf)
{
	H_CHAR han_char;	/* 한글 한글자 */
	UBYTE *pHan = str, tmp_Char;
	DWORD han_len = 0, code_index;

	han_char.code = 0;
	while (*pHan != '\0') {
		if (isalpha(*pHan)) {  /* 영어 1글자 */
			tmp_Char = *pHan;
			han_char.hl.high = tmp_Char;
			han_char.hl.low = tmp_Char;
			han_buf[han_len].j_hl.high = han_char.hl.high;
			han_buf[han_len++].j_hl.low = han_char.hl.low;

			pHan++;

			continue;
		}

		if (isdigit(*pHan)) {  /* 숫자 1글자 */
			han_char.hl.high = *pHan;
			han_char.hl.low = *pHan;
			han_buf[han_len].j_hl.high = han_char.hl.high;
			han_buf[han_len++].j_hl.low = han_char.hl.low;

			pHan++;

			continue;
		}

		if (*pHan & 0x80) {  /* 2-byte 코드일 경우 */
			han_char.hl.high = *pHan;
			pHan++;
			han_char.hl.low = *pHan;

			if ((0xB0 <= han_char.hl.high && han_char.hl.high <= 0xC8) &&
				(0xA1 <= han_char.hl.low  && han_char.hl.low  <= 0xFE)) { /* 완성형 1글자 */
				code_index = (han_char.hl.high - 0xB0) * 94;
				code_index += han_char.hl.low - 0xA1;
				han_buf[han_len++].j_code = conv_tbl[code_index][1];
				/* 변환 테이블에서 조합형 코드를 가져옴 */

				pHan++;
				continue;
			} 

			if ((han_char.hl.high == 0xA4) && /* 자소 1글자 */
				(0xA1 <= han_char.hl.low && han_char.hl.low <= 0xD3)) {
				han_buf[han_len++].j_code = cnvt_tbl_jaso[han_char.code - 0xA4A1][1];

				if (han_buf[han_len-1].j_code == 0)
					return 0;

				/* 자소변환테이블에서 조합형 코드를 가져옴 */

				pHan++;

				continue;
			}
		}

		return 0;
	}

	return han_len;
}

DWORD MakeHanBuf(UBYTE *hangul_str, HANGUL *han_buf, UWORD *head_idx)
{
	H_CHAR han_char;	/* 한글 한글자 */
	UBYTE *pHan = hangul_str;
	BYTE tmp_Char;
	WORD han_len = 0, ffirst = 1;
	WORD code_index;
#ifdef HANJA_RETURN
	DWORD is_hanja = 0;
#endif

#ifdef MA_MODE
	extern UWORD is_HanJa;
	extern UWORD is_AlPha;
	extern UWORD is_DiGit;
#endif

#ifdef MA_MODE
	/* 전역변수 사용 */
	/*****************/
	is_HanJa = 0;
	is_AlPha = 0;
	is_DiGit = 0;
	/*****************/
#endif

	han_char.code = 0;
	while (*pHan != '\0') {
		if (isalpha(*pHan)) {  /* 영어 1글자 */
			tmp_Char = toupper(*pHan);
			han_char.hl.high = tmp_Char;
			han_char.hl.low = tmp_Char;
			han_buf[han_len].j_hl.high = han_char.hl.high;
			han_buf[han_len++].j_hl.low = han_char.hl.low;
			if (ffirst) {
				*head_idx = WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + (tmp_Char - 'A');
				ffirst = 0;
			}
			pHan++;

#ifdef MA_MODE
			is_AlPha = 1;
#endif

			continue;
		}

		if (isdigit(*pHan)) {  /* 숫자 1글자 */
			han_char.hl.high = *pHan;
			han_char.hl.low = *pHan;
			han_buf[han_len].j_hl.high = han_char.hl.high;
			han_buf[han_len++].j_hl.low = han_char.hl.low;
			if (ffirst) {
				*head_idx = WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + (*pHan - '0');
				ffirst = 0;
			}
			pHan++;

#ifdef MA_MODE
			is_DiGit = 1;
#endif

			continue;
		}

		if (*pHan & 0x80) {  /* 2-byte 코드일 경우 */
			han_char.hl.high = *pHan;
			pHan++;
			han_char.hl.low = *pHan;


			if ((0xB0 <= han_char.hl.high && han_char.hl.high <= 0xC8) &&
				(0xA1 <= han_char.hl.low  && han_char.hl.low  <= 0xFE)) { /* 완성형 1글자 */
				code_index = (han_char.hl.high - 0xB0) * 94;
				code_index += han_char.hl.low - 0xA1;
				han_buf[han_len++].j_code = conv_tbl[code_index][1];
				/* 변환 테이블에서 조합형 코드를 가져옴 */
				if (ffirst) {
					*head_idx = code_index + WANSUNG_JASO_NUM;
					ffirst = 0;
				}
				pHan++;
				continue;
			} 

			if (han_char.hl.high == '\241' && han_char.hl.low == '\241') {
#ifndef BATCH_PROC
#ifndef VER_LIB
				printf("\nDetection of Strange 2-byte code...\n");
#endif
#endif
				return 0;
			}

			if ((han_char.hl.high == 0xA4) && /* 자소 1글자 */
				(0xA1 <= han_char.hl.low && han_char.hl.low <= 0xD3)) {
				han_buf[han_len++].j_code =
					cnvt_tbl_jaso[han_char.code - 0xA4A1][1];

				if (han_buf[han_len-1].j_code == 0)
					return 0;

				/* 자소변환테이블에서 조합형 코드를 가져옴 */
				if (ffirst) {
					*head_idx = han_char.code - 0xA4A1;
					ffirst = 0;
				}
				pHan++;
				continue;
			}

			/* 2-byte 심벌 */
			if ((0xA1 <= han_char.hl.high && han_char.hl.high <= 0xAC) &&
				(0xA1 <= han_char.hl.low  && han_char.hl.low <= 0xFE)) {
#ifndef BATCH_PROC
#ifndef VER_LIB
				printf("\nDetection of Strange 2-byte code...\n");
#endif
#endif
				return 0;
			}

#ifdef MA_MODE
/* 한자일 경우에는 한글로 변환 */
			/* 완성형 한자 */
			if ((0xCA <= han_char.hl.high && han_char.hl.high <= 0xFD) &&
				(0xA1 <= han_char.hl.low  && han_char.hl.low <= 0xFE)) {
				if (Hj2HgProc(&han_char) == 0) {
#ifndef BATCH_PROC
#ifndef VER_LIB
				printf("\nDetection of Strange 2-byte code...\n");
#endif
#endif
					return 0;
				}

#ifdef HANJA_RETURN
				is_hanja = 1;
#endif

				code_index = (han_char.hl.high - 0xB0) * 94;
				code_index += han_char.hl.low - 0xA1;
				han_buf[han_len++].j_code = conv_tbl[code_index][1];
				/* 변환 테이블에서 조합형 코드를 가져옴 */
				if (ffirst) {
					*head_idx = code_index + WANSUNG_JASO_NUM;
					ffirst = 0;
				}
				pHan++;

#ifdef MA_MODE
				is_HanJa = 1;
#endif

				continue;
			}
#endif
#ifndef BATCH_PROC
#ifndef VER_LIB
				printf("\nDetection of Strange 2-byte code...\n");
#endif
#endif
			return 0;
		}

#ifndef BATCH_PROC
#ifndef VER_LIB
				printf("\nDetection of Strange 2-byte code...\n");
#endif
#endif
		return 0;
	}

#ifdef HANJA_RETURN
	if (is_hanja)
	    return 1024;
	else
	    return han_len;
#else
	return han_len;
#endif
} /* End of MakeHanBuf */

UWORD GetNoJongIndex(DWORD header_index)
{
	return (NoJongIdx[header_index - WANSUNG_JASO_NUM]);
}
