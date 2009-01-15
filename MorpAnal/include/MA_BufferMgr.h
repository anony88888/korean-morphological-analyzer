#ifndef _MA_BUFFERMGR_H_
#define _MA_BUFFERMGR_H_

#include <MA_Type.h>

#define TOKEN_BUF_SIZE		6
#define TOKEN_BUF_ITEM		(TOKEN_BUF_SIZE - 1)

/*************************************************************************/
/* 토큰 버퍼 관리 자료구조 : 이미 분석된 어절들, 앞으로 분석할 어절들... */
/*************************************************************************/

/* 기분석 어절을 저장하기 위한 버퍼 자료구조 */
typedef struct {
    /* 2001.02.23 : 필요가 없어서 막음 */
	/* tMORP_RESULT morp[MAX_MORP_LIST];*/	/* 형태소 분석 결과 */
	/* DWORD nMorpRes;		*/	/* 형태소 분석 결과 개수 */
	HANGUL hword[MAX_VOCA_LEN];		/* 한글 어절 */
	UWORD hword_len;			/* 어절 길이 : 글자단위 */
	DWORD token;				/* 토큰 종류 */
	UWORD fRes;				/* 분석 성공 여부 : 성공->1, 실패->0 */
} tPOST_TOKEN;

/* 분석할 어절을 저장하기 위한 버퍼 자료구조 */
typedef struct {
	UBYTE word[VS_BUFLEN];			/* 완성형 한글 */
	HANGUL hword[MAX_VOCA_LEN];		/* 한글 어절 */
	UWORD hword_len;			/* 어절 길이 : 글자단위 */
	DWORD token;				/* 토큰 종류 */
} tPRE_TOKEN;

/* 분석 대기열 버퍼 큐... */
tPRE_TOKEN pre_words[TOKEN_BUF_SIZE];
UWORD pre_words_front = 0;
UWORD pre_words_rear = 0;

/* 기분석 버퍼 큐... */
tPOST_TOKEN post_words[TOKEN_BUF_SIZE];
UWORD post_words_front = 0;
UWORD post_words_rear = 0;

#endif

