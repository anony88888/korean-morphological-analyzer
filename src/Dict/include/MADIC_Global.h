#ifndef _MADIC_GLOBAL_H_
#define _MADIC_GLOBAL_H_

#define MAIN_DIC	"DICMAIN.DIC"		/* �ֻ��� ���̳ʸ� ���� */
#define JOSA_DIC	"DICJOSA.DIC"		/* ������� ���̳ʸ� ���� */
#define EOMI_DIC	"DICEOMI.DIC"		/* ��̻��� ���̳ʸ� ���� */
#define BOJO_DIC	"DICBOJO.DIC"		/* ���������� ���� ���� */
#define TAIL_DIC	"DICTAIL.DIC"		/* �������¼� ���� ���� ���� */

#ifdef CORPUS_DIC_SEARCH
#define CORPUS_DIC	"CORDIC.DIC"
#endif

#define RAW_MAIN_DIC	"DIC.MAIN"		/* �ֻ��� ���� ���� */
#define RAW_JOSA_DIC	"DIC.JOSA"		/* ������� ���� ���� */
#define RAW_EOMI_DIC	"DIC.EOMI"		/* ��̻��� ���� ���� */
#define RAW_BOJO_DIC	"DIC.BOJO"		/* ���������� �������� */
#define RAW_TAIL_DIC	"DIC.TAIL"		/* �������¼� ���� ���� ���� */

#define NTAIL_DIC       "DICNTAIL.DIC"      /* ����� �������¼� ���� */
#define NTAIL_CON       "DICNTAIL.CON"      /* ����� �������¼� ���¼Ұ�� */

#define PTAIL_DIC       "DICPTAIL.DIC"      /* ����� �������¼� ���� */
#define PTAIL_CON       "DICPTAIL.CON"      /* ����� �������¼� ���¼Ұ�� */

#define BTAIL_DIC       "DICBTAIL.DIC"      /* ����� ����-�������¼� Bigram ���� */
#define BTAIL_CON       "DICBTAIL.CON"      /* ����� ����-�������¼� Bigram ���¼Ұ�� */

#define RAW_NTAIL_DIC       "DIC.NTAIL"     /* ����� �������¼� ���û��� */
#define RAW_PTAIL_DIC       "DIC.PTAIL"     /* ����� �������¼� ���û��� */
#define RAW_BTAIL_DIC       "DIC.BTAIL"     /* ����� ����-�������¼� Bigram ���� */

#define STOPWORD	"STOPWORDS"			/* �ҿ�� ���� */
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

extern DIC_HEADER JDic_Header[HEADER_NUM];		/* ���� ���� ��� */
extern DIC_NODE *JDic_Roots[HEADER_NUM];		/* ���� ���� ���� */

extern DIC_HEADER EDic_Header[HEADER_NUM];		/* ��� ���� ��� */
extern DIC_NODE *EDic_Roots[HEADER_NUM];		/* ��� ���� ���� */

extern DIC_HEADER BDic_Header[HEADER_NUM];		/* ������� ���� ��� */
extern DIC_NODE *BDic_Roots[HEADER_NUM];		/* ������� ���� ���� */

/* DIC_HEADER Tail_Dic_Header[HEADER_NUM]; */		/* ����ġ���� ������ Tail ���� ���� ��� */
/* TAIL_DIC_NODE *Tail_Dic_Roots[HEADER_NUM]; */		/* ����ġ���� ������ Tail ���� ���� ���� */

#endif /* _MADIC_GLOBAL_H_ */

