#ifndef _MA_BUFFERMGR_H_
#define _MA_BUFFERMGR_H_

#include <MA_Type.h>

#define TOKEN_BUF_SIZE		6
#define TOKEN_BUF_ITEM		(TOKEN_BUF_SIZE - 1)

/*************************************************************************/
/* ��ū ���� ���� �ڷᱸ�� : �̹� �м��� ������, ������ �м��� ������... */
/*************************************************************************/

/* ��м� ������ �����ϱ� ���� ���� �ڷᱸ�� */
typedef struct {
    /* 2001.02.23 : �ʿ䰡 ��� ���� */
	/* tMORP_RESULT morp[MAX_MORP_LIST];*/	/* ���¼� �м� ��� */
	/* DWORD nMorpRes;		*/	/* ���¼� �м� ��� ���� */
	HANGUL hword[MAX_VOCA_LEN];		/* �ѱ� ���� */
	UWORD hword_len;			/* ���� ���� : ���ڴ��� */
	DWORD token;				/* ��ū ���� */
	UWORD fRes;				/* �м� ���� ���� : ����->1, ����->0 */
} tPOST_TOKEN;

/* �м��� ������ �����ϱ� ���� ���� �ڷᱸ�� */
typedef struct {
	UBYTE word[VS_BUFLEN];			/* �ϼ��� �ѱ� */
	HANGUL hword[MAX_VOCA_LEN];		/* �ѱ� ���� */
	UWORD hword_len;			/* ���� ���� : ���ڴ��� */
	DWORD token;				/* ��ū ���� */
} tPRE_TOKEN;

/* �м� ��⿭ ���� ť... */
tPRE_TOKEN pre_words[TOKEN_BUF_SIZE];
UWORD pre_words_front = 0;
UWORD pre_words_rear = 0;

/* ��м� ���� ť... */
tPOST_TOKEN post_words[TOKEN_BUF_SIZE];
UWORD post_words_front = 0;
UWORD post_words_rear = 0;

#endif

