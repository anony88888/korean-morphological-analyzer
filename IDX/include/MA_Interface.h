/* ���¼� �м���� ���� �ý��۰��� �������̽��� ���� ���� 
   �ڷ�����, ���� ���� */

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
    unsigned char	str[MAX_INDEX_LEN];		/* ���� ���ξ� */
    unsigned char	loc;		/* ���� �ܾ� �������� ���ξ��� ���� ��ġ */
} INDEX_ITEM;

/* �� ������ ���� �ε��� ���� ��� ���� ����ü */
typedef struct {
	unsigned char		nIndex;
	unsigned char		org_str[MAX_STR_LEN];
	INDEX_ITEM		IDX[MAX_INDEX_NUM];
	unsigned char		uk_flag;
	unsigned int		location;
} INDEX_WORD;

/* �� ������ ���� ���¼� �м� ��� ���� ����ü */
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

/* �±� ��� ����ü */
typedef struct {
    unsigned char		org_word[128]; /* ���� �ܾ� */
    ITF_MORP_RESULT		IMR[3]; /* Ȯ�� ������ ������ �±� ��� */
    unsigned short int		MARes_num; /* �±� ��� ���� */
    double			P[3]; /* Ȯ�� */
} ITF_POSTAG_RESULT;

/*****************************************************************
 * ������ ���� ��� ���� �ڷᱸ��
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

/* ���̺귯������ Export�Ǵ� �Լ��� proto-type */

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

