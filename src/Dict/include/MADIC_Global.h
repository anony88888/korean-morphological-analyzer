#ifndef _MADIC_GLOBAL_H_
#define _MADIC_GLOBAL_H_

#define MAIN_DIC	"DICMAIN.DIC"		/* 주사전 바이너리 파일 */
#define JOSA_DIC	"DICJOSA.DIC"		/* 조사사전 바이너리 파일 */
#define EOMI_DIC	"DICEOMI.DIC"		/* 어미사전 바이너리 파일 */
#define BOJO_DIC	"DICBOJO.DIC"		/* 보조용언사전 이진 파일 */
#define TAIL_DIC	"DICTAIL.DIC"		/* 형식형태소 패턴 이진 파일 */

#ifdef CORPUS_DIC_SEARCH
#define CORPUS_DIC	"CORDIC.DIC"
#endif

#define RAW_MAIN_DIC	"DIC.MAIN"		/* 주사전 원시 파일 */
#define RAW_JOSA_DIC	"DIC.JOSA"		/* 조사사전 원시 파일 */
#define RAW_EOMI_DIC	"DIC.EOMI"		/* 어미사전 원시 파일 */
#define RAW_BOJO_DIC	"DIC.BOJO"		/* 보조용언사전 원시파일 */
#define RAW_TAIL_DIC	"DIC.TAIL"		/* 형식형태소 패턴 원시 파일 */

#define NTAIL_DIC       "DICNTAIL.DIC"      /* 명사형 형식형태소 사전 */
#define NTAIL_CON       "DICNTAIL.CON"      /* 명사형 형식형태소 형태소결과 */

#define PTAIL_DIC       "DICPTAIL.DIC"      /* 용언형 형식형태소 사전 */
#define PTAIL_CON       "DICPTAIL.CON"      /* 용언형 형식형태소 형태소결과 */

#define BTAIL_DIC       "DICBTAIL.DIC"      /* 명사형 실질-형식형태소 Bigram 사전 */
#define BTAIL_CON       "DICBTAIL.CON"      /* 명사형 실질-형식형태소 Bigram 형태소결과 */

#define RAW_NTAIL_DIC       "DIC.NTAIL"     /* 명사형 형식형태소 원시사전 */
#define RAW_PTAIL_DIC       "DIC.PTAIL"     /* 용언형 형식형태소 원시사전 */
#define RAW_BTAIL_DIC       "DIC.BTAIL"     /* 명사형 실질-형식형태소 Bigram 사전 */

#define STOPWORD	"STOPWORDS"			/* 불용어 파일 */
#define STOPWORD_NUM	3000

#define WANSUNG_JASO_NUM 51
#define WANSUNG_CODE_NUM 2350
#define ALPHABET_CODE_NUM 26
#define NUMBER_NUM 10

#define INIT_CHAR_INDEX	1
#define INIT_LEVEL 2

#define HEADER_NUM (WANSUNG_JASO_NUM + WANSUNG_CODE_NUM + ALPHABET_CODE_NUM + NUMBER_NUM)

extern DIC_HEADER Dic_Header[HEADER_NUM]; 
/*
   The Header Information for positioning the cursor according to hangul code 
   This information is the location where nodes of each hangul code exists 
*/

extern DIC_NODE *Dic_Roots[HEADER_NUM];
/*
   The root nodes --> 51+2350 wansung hangul code
*/
extern WORD full_match;

extern DIC_HEADER JDic_Header[HEADER_NUM];		/* 조사 사전 헤더 */
extern DIC_NODE *JDic_Roots[HEADER_NUM];		/* 조사 사전 버퍼 */

extern DIC_HEADER EDic_Header[HEADER_NUM];		/* 어미 사전 헤더 */
extern DIC_NODE *EDic_Roots[HEADER_NUM];		/* 어미 사전 버퍼 */

extern DIC_HEADER BDic_Header[HEADER_NUM];		/* 보조용언 사전 헤더 */
extern DIC_NODE *BDic_Roots[HEADER_NUM];		/* 보조용언 사전 버퍼 */

/* DIC_HEADER Tail_Dic_Header[HEADER_NUM]; */		/* 말뭉치에서 추출한 Tail 패턴 사전 헤더 */
/* TAIL_DIC_NODE *Tail_Dic_Roots[HEADER_NUM]; */		/* 말뭉치에서 추출한 Tail 패턴 사전 버퍼 */

#endif /* _MADIC_GLOBAL_H_ */

