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

// 2003-05-28 색인형태 추가
#define INDEX_BY_MIX_CHAR			112
#define INDEX_BY_MIX_MA				113

// 2003-07-03 색인타입 추가
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
	int highlight;		/* INDEX_BY_MIX_CHAR에서 하일라이팅을 위해 모든 글자를 다 리턴시키는 기능을 수행 */
	int stem;			/* 영어 스태밍 option */
	int hanja;			/* 한자 변환 옵션 */
	int hj_hg;			/* 한자를 한글로 변환할지 여부 0:한글변환추가안함 1:한글변환추가 */
	int idx_bigram;		
	char *dels;			/* 사용자 지정 분리자 리스트  UTF-8 */
						/* 이 분리자가 NULL이 아니면 IndexByToken에서 이 분리자 기준으로 토크나이징 수행 */
	char *dCode;		/* 제거대상 코드 -- [홍 길동] ==> [홍길동] : 일단은 IndexAsIs에서만 적용 */
						/* UTF-8 */
	INDEX_OFFSET idx_offset[10];
	unsigned short int off_num;
						/* IndexAsIs에서 옵셋을 지정하여 분리색인하는 옵션 */
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
 * 한자 옵션
 * hanja_opt
 *   0 ------> 한자변환 하지 않음
 *   1 ------> 한자변환 수행
 *
 *   1000 ----> 정자, 번체자 색인 생성 ---- (가)
 *   0100 ----> 약자 색인 생성         ---- (나)
 *   0010 ----> 간체자 색인 생성       ---- (다)
 *   1100 ----> (가) + (나)
 *   1010 ----> (가) + (다)
 *   0110 ----> (나) + (다)
 *   1110 ----> (가) + (나) + (다)
 *
 *   추가 변환 옵션은 혼합색인에만 국한되는 것이므로 기본 한자 변환하고는 상관없음
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
