#ifndef _IDX_USER_H_
#define _IDX_USER_H_

#define MAXKEYLEN			256
#define MAXSWIDLEN			256

#define DEL_INTER_INDEX		"\n"
#define DEL_INTRA_INDEX		"\t"

#define DO_NOT_INDEX				101
#define INDEX_AS_IS					102
#define INDEX_AS_NUMERIC			103
#define INDEX_BY_TOKEN				104
#define INDEX_BY_CHAR				105
#define INDEX_BY_MA					106
#define INDEX_AS_IS_MA				107
#define INDEX_BY_TOKEN_HANJA		108
#define INDEX_BY_MA_HANJA			109
#define INDEX_AS_IS_MA_HANJA		110
#define INDEX_BY_CHAR_HANJA			111

// 2003-05-28 �������� �߰�
#define INDEX_BY_MIX_CHAR			112
#define INDEX_BY_MIX_MA				113

// 2003-07-03 ����Ÿ�� �߰�
#define INDEX_BY_CD_MA				114
#define INDEX_BY_CD_TOKEN			115

// added to support biological sequence data by jinsuk on 20030102
#define INDEX_DNA					116
#define INDEX_TRDNA					117
#define INDEX_PROTEIN				118

// from 112 to 119 by jinsuk on 20030102
#define INDEX_AS_COUNT              119
#define BAD_KRISTAL_INDEX_TYPE		120

#define HANJA_2_HANGUL				130

#define IDX_SW_REGISTER				201
#define IDX_SW_DISCARD				202
#define IDX_SW_ACTIVATE				203
#define IDX_SW_DEACTIVATE			204
#define IDX_SW_ID_LIST				205

typedef struct {
	unsigned short int start;
	unsigned short int len;
} INDEX_OFFSET;

typedef struct {
	int highlight;		/* INDEX_BY_MIX_CHAR���� ���϶������� ���� ��� ���ڸ� �� ���Ͻ�Ű�� ����� ���� */
	int stem;			/* ���� ���¹� option */
	int hanja;			/* ���� ��ȯ �ɼ� */
	int hj_hg;			/* ���ڸ� �ѱ۷� ��ȯ���� ���� 0:�ѱۺ�ȯ�߰����� 1:�ѱۺ�ȯ�߰� */
	int idx_bigram;		
	char *dels;			/* ����� ���� �и��� ����Ʈ  UTF-8 */
						/* �� �и��ڰ� NULL�� �ƴϸ� IndexByToken���� �� �и��� �������� ��ũ����¡ ���� */
	char *dCode;		/* ���Ŵ�� �ڵ� -- [ȫ �浿] ==> [ȫ�浿] : �ϴ��� IndexAsIs������ ���� */
						/* UTF-8 */
	INDEX_OFFSET idx_offset[10];
	unsigned short int off_num;
						/* IndexAsIs���� �ɼ��� �����Ͽ� �и������ϴ� �ɼ� */
} STRUCT_OPTION_IDX;

typedef struct {
	char			key[MAXKEYLEN];
	unsigned int	keyLen;
	unsigned int	psgNum;
	unsigned int	wordNum;
	unsigned short int 	c_type;
} POSTINFO;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
int IDX_InitIDX(char *KristalDir);
int IDX_CloseIDX();

/********************************************************************/
//int IDX_MainProc(unsigned char req, char *data, POSTINFO *PostInfo, int startWordNum, int stem_opt, int hanja_opt);
int IDX_MainProc(unsigned char req, char *data, POSTINFO *PostInfo, int startWordNum, STRUCT_OPTION_IDX opt);
/*
 * ���� �ɼ�
 * hanja_opt
 *   0 ------> ���ں�ȯ ���� ����
 *   1 ------> ���ں�ȯ ����
 *
 *   1000 ----> ����, ��ü�� ���� ���� ---- (��)
 *   0100 ----> ���� ���� ����         ---- (��)
 *   0010 ----> ��ü�� ���� ����       ---- (��)
 *   1100 ----> (��) + (��)
 *   1010 ----> (��) + (��)
 *   0110 ----> (��) + (��)
 *   1110 ----> (��) + (��) + (��)
 *
 *   �߰� ��ȯ �ɼ��� ȥ�ջ��ο��� ���ѵǴ� ���̹Ƿ� �⺻ ���� ��ȯ�ϰ�� �������
 */
int RegisterSWSet(char *SWID, char *SWSet[], int SWNum);
int ActivateSWSet(char *SWIDs[], int SWIDNum);
int DeActivateSWSet();
int isHanjaExist(char *str);

int IDX_LoadCrossTermDic(char *dic_dir);
int IDX_CloseCrossTermDic();
int IDX_SearchCrossDic(char *term, char *result);

/********************************************************************/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
