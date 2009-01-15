/* 형태소 분석기와 상위 시스템과의 인터페이스를 위한 각종 
   자료유형, 변수 선언 */

#ifndef _MA_INTERFACE_H_
#define _MA_INTERFACE_H_

#define HANSTR_LEN		64
#define MAX_INDEX_NUM		256
#define MAX_STR_LEN		128
#define MAX_INDEX_LEN		128

/* Hangul Johab code Abstract type */
#ifdef WIN32
typedef struct {
	unsigned short int jong: 5;
	unsigned short int jung: 5;
	unsigned short int cho:  5;
	unsigned short int sign: 1;
} COMBINED_HAN;
#elif LINUX
typedef struct {
	unsigned short int jong: 5;
	unsigned short int jung: 5;
	unsigned short int cho:  5;
	unsigned short int sign: 1;
} COMBINED_HAN;
#else
typedef struct {
	unsigned short int sign: 1;		/* Hangul Detection Bit */
	unsigned short int cho:  5;		/* ChoSung Bits */
	unsigned short int jung: 5;		/* JungSung Bits */
	unsigned short int jong: 5;		/* JongSung Bits */
} COMBINED_HAN;                          
#endif

#ifdef WIN32
typedef struct {
	unsigned char low;
	unsigned char high;
} LH_CHAR;
#elif LINUX
typedef struct {
	unsigned char low;
	unsigned char high;
} LH_CHAR;
#else
typedef struct {
	unsigned char high;
	unsigned char low;
} LH_CHAR;
#endif

typedef union {
	unsigned short int	code;
	LH_CHAR				hl;
} TCHAR;

/* Integrated Version of hangul code ADT : Johab */
typedef union {
	unsigned short int		j_code;	/* 2-byte johab code */
	COMBINED_HAN			j_han;	
	LH_CHAR					j_hl;
} JO_CHAR;

typedef TCHAR WAN_CHAR;

typedef struct {
	JO_CHAR		h_word[HANSTR_LEN];
	int			len;
} JO_STR;

typedef struct {
	WAN_CHAR	h_word[HANSTR_LEN];
	unsigned char str[MAX_STR_LEN];
	int 		len;
} WAN_STR;

typedef struct {
    unsigned char	str[MAX_INDEX_LEN];		/* 실제 색인어 */
    unsigned char	loc;		/* 현재 단어 내에서의 색인어의 시작 위치 */
} INDEX_ITEM;

/* 한 어절에 대한 인덱스 추출 결과 저장 구조체 */
typedef struct {
	unsigned char		nIndex;
	unsigned char		org_str[MAX_STR_LEN];
	INDEX_ITEM		IDX[MAX_INDEX_NUM];
	unsigned char		uk_flag;
	unsigned int		location;
} INDEX_WORD;

/* 한 어절에 대한 형태소 분석 결과 저장 구조체 */
typedef struct {
    unsigned char		Morpheme[MAX_INDEX_LEN];
    char			info[32];
} ITF_MORP_ITEM;

typedef struct {
    unsigned short int		nMorp;
    ITF_MORP_ITEM		MI[32];
} ITF_MORP_RESULT;

typedef struct {
    unsigned char		org_word[128];
    ITF_MORP_RESULT		IMR[20];
    unsigned short int		MARes_num;
} ITF_MA_RESULT;

/* 태깅 결과 구조체 */
typedef struct {
    unsigned char		org_word[128]; /* 원래 단어 */
    ITF_MORP_RESULT		IMR[3]; /* 확률 순위로 나열된 태깅 결과 */
    unsigned short int		MARes_num; /* 태깅 결과 개수 */
    double			P[3]; /* 확률 */
} ITF_POSTAG_RESULT;

/*****************************************************************
 * 조합형 색인 결과 저장 자료구조
 *****************************************************************/
typedef struct {
	JO_CHAR				str[MAX_STR_LEN];
	unsigned char		str_len;
	unsigned char		loc;
} JO_INDEX_ITEM;

typedef struct {
	unsigned char		nIndex;
	JO_CHAR				org_str[MAX_STR_LEN];
	unsigned char		org_str_len;
	JO_INDEX_ITEM		IDX[MAX_INDEX_NUM];
	unsigned int		location;
} JO_INDEX_WORD;

/*****************************************************************/

/* 라이브러리에서 Export되는 함수들 proto-type */

void InitDicHeader();
int LoadDictionary(char *dic_dir);
int ClearDic();

#ifdef KRISTAL_JOHAB_API
int GetIndexFromOneWord(JO_CHAR *han_word, int hword_len, JO_INDEX_WORD *idx_words, int mode);
#else
int ITF_MainMAProc(unsigned char *ma_buf, ITF_MA_RESULT *ma_result);
int GetIndexWord(unsigned char *ma_buf, INDEX_WORD *idx_words);
#endif

#endif

