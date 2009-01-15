/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(MA_GMacro.h)#           SPASIS System, 09/NOV/1999
 *
 *	#(Action)#
 *		Global Macro Definition.
 */
#ifndef _MA_GMACRO_H_
#define _MA_GMACRO_H_

#define MAX_VOCA_LEN			128	/* 한글 입력 표제어 길이 */
#define VS_BUFLEN			128	/* Very Small Buffer Length */
#define S_BUFLEN			512	/* Small Buffer Length */
#define M_BUFLEN			1024	/* Middle Buffer Length */
#define L_BUFLEN			4096	/* Large Buffer Length */
#define DIC_RESULT_NUM		100	/* 사전 탐색 결과 개수 */

/* UTIL_FileOpen uses this MACRO */
#define F_READ				101 /* read only mode */
#define F_WRITE				102 /* write only mode */
#define F_APPEND			103 /* append only mode */

#define F_TEXT				105
#define F_BINARY			106

#define EM_EXIT				201 /* Exit Program when error */
#define EM_RETURN			202 /* Return Error Code when error */

/* UTIL_FileRead uses this MACRO */
#define F_READ_LINE				301 	/* read one line from file */
#define F_READ_BULK_ALL			302 	/* read bulk data from file */
#define F_READ_BULK_PART		303 	/* read bulk data from file */
#define F_READ_EOF				0 		/* End of file */

/* UTIL_FileSeek uses this MACRO */
#define F_SEEK_START			401		/* file position : start */
#define F_SEEK_END				402		/* file position : end */
#define F_SEEK_CUR				403		/* file position : current */

#define MAINDIC					"MAIN.DIC"	/* 주사전 */

#define MORP_LEN				41		/* 한 형태소의 길이 */
#define MORP_INFO				100		/* 한 형태소에 대한 정보 개수 */
#define MAX_MORP_LIST			100		/* 한 어절의 최대 형태소 개수 */
#define MAX_IDX_LIST            100     /* 최대 색인어 개수  2006.03.02 by mini*/
#define MAX_MORP_CAND			50		/* 최대 형태소 분석 결과 개수 */

/* 현재 형태소 분석 결과의 형태소 수 */
#define CUR_MAR_ITEMS			MorpResult[MorpResult_Index].nMorp

/* 현재 형태소 분석 결과의 형태소 리스트 */
#define CUR_MAR_MORP			MorpResult[MorpResult_Index].MI[Morpheme_Index].Morpheme

/* 현재 형태소 분석 결과의 정보 리스트 */
#define CUR_MAR_INFO			MorpResult[MorpResult_Index].MI[Morpheme_Index].info

/* 현재 형태소 분석 결과의 정보 개수 */
#define CUR_MAR_INFO_NUM		MorpResult[MorpResult_Index].MI[Morpheme_Index].ninfo


/* 양성모음과 음성모음 구분 */
#define YANGSUNG(v)				((v) == 0x03 || (v) == 0x04 || (v) == 0x05 || (v) == 0x06 \
								|| (v) == 0x0D || (v) == 0x0E || (v) == 0x0F || (v) == 0x12 \
								|| (v) == 0x13)
#define EUMSUNG(v)				((v) == 0x07 || (v) == 0x0A || (v) == 0x0B || (v) == 0x0C \
								|| (v) == 0x14 || (v) == 0x15 || (v) == 0x16 || (v) == 0x17 \
								|| (v) == 0x1A || (v) == 0x1B || (v) == 0x1C || (v) == 0x1D)
#ifdef MULTI_DIC_INFO
#define IS_NOUN(inf)			(((inf) >= 30 && (inf) <= 41) || ((inf) >= 90 && (inf) <= 94)) //by mini(2005.08.30)
#define NOUNS_INFO				120
#endif

#define IS_INDEX_INFO(inf)      ((inf) >= 32 && (inf) <= 40 || ((inf) >= 90 && (inf) <= 94))//by mini(2005.08.30)



/*************************************************
 *            형태소 분석 모드 지정              *
 *************************************************/
#define NORMAL					1000		/* 일반 형태소 분석 모드 */
#define SUSA_UNIT				1001		/* 단위명사 검사 */
#define SUSA_NOUN				1002		/* 수사 다음이 일반 명사인지를 검사한다... */
#define SUSA_POSTNOUN			1003		/* 명사 다음에 오는 형태소를 분석한다 */
#define SUSA_SEARCH_DIC         1004        /* 단순히 주사전 검색만 하여 가장 긴 일치 서브스트링의 길이를 리턴 */

#ifdef COMP_NOUN_DIC_CHECK
#define COMPNOUN_POSTNOUN_NP			1005		/* 접미사로 끝난 복합명사 */
#define COMPNOUN_POSTNOUN_P			1006		/* 명사로 끝난 복합명사 */
#endif

#endif /* _MA_GMACRO_H_ */

