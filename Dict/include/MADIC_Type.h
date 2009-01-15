#ifndef _MADIC_TYPE_H_
#define _MADIC_TYPE_H_

/* The Information Part of Dictionary Entry Node */
typedef struct {
        UDWORD next : 20;      /* Next Node Position : Array Index(0-256) */
        UDWORD info : 10;      /* Word Information Field(0-64)            */
        UDWORD jong : 1;      /* Ommitting Jong-Sung Node Flag(0-1)      */
        UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} NODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
        NODE_INFO node_info;      /* Dictionary Node Information Field */
        HANGUL han;               /* Hangul Data Field                 */
} DIC_NODE;

/* Header Information */
typedef struct {
	UDWORD size;			/* the size of one block */
	UDWORD start;			/* the start position of one block */
	UDWORD items;			/* the number of item in one block */
} DIC_HEADER;

/* Dictionary Search Result Structure */
typedef struct {
	UWORD len;				/* 사전에 존재하는 서브스트링의 길이 */
	UWORD jong;				/* 종성이 포함되지 않은 채로 사전 검색이 되었을 때 */
#ifdef MULTI_DIC_INFO
	UBYTE info[20];
#else
	BYTE info;				/* 사전 정보 */
#endif
} DIC_RESULT;

#ifdef MULTI_DIC_INFO
typedef struct {
	UWORD len;				/* 사전에 존재하는 서브스트링의 길이 */
	UWORD jong;				/* 종성이 포함되지 않은 채로 사전 검색이 되었을 때 */
	BYTE info;				/* 사전 정보 */
} JEDIC_RESULT;
#endif

typedef struct {
	UWORD len;				/* 사전에 존재하는 서브스트링의 길이 */
	UWORD jong;				/* 종성이 포함되지 않은 채로 사전 검색이 되었을 때 */
	BYTE info[50];			/* 사전 정보 */
	UWORD ninfo;			/* 사전 정보 개수 */
	UWORD idx;				/* 복합명사 처리에서 사용되는 변수 */
} CDIC_RESULT;

/**********************************************************
 * 말뭉치에서 추출한 형식형태소 정보 사전 관련 타입...
typedef struct {
	UWORD next : 14;
	UWORD jong : 1;
	UWORD brk  : 1;
} TAIL_NODE_INFO;

typedef struct {
	TAIL_NODE_INFO node_info;
	UWORD info_noun_freq;
	UWORD info_else_freq;
	HANGUL han;
} TAIL_DIC_NODE;

typedef struct {
	UWORD len;
	UDWORD info_noun_freq;
	UDWORD info_else_freq;
} TAIL_DIC_RESULT;

typedef struct {
	UWORD len;
	TFLOAT prob_val;
	TFLOAT frq_prob;
} NOUN_PROB;
**********************************************************/

/**********************************************************
 * 말뭉치에서 추출한 형식형태소 정보 사전 관련 타입...
**********************************************************/
/* The Information Part of Dictionary Entry Node */
typedef struct {
	UDWORD next : 31;     /* Next Node Position : Array Index(0-256) */
	UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} TAILNODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
	TAILNODE_INFO node_info;  /* Dictionary Node Information Field */
	UDWORD InfoStart;         /* 기분석 결과정보의 시작위치        */
	UBYTE  InfoLen;           /* 기분석 결과정보의 길이            */
	HANGUL han;               /* Hangul Data Field                 */
} TAILDIC_NODE;

/* Dictionary Search Result Structure */
typedef struct {
	UWORD len;      /* 사전에 존재하는 서브스트링의 길이 */
	UDWORD InfoStart;
	UBYTE InfoLen;
} TAILDIC_RESULT;


/**********************************************************
 * 복합명사 기분석 사전 탐색용 자료유형 정의
 **********************************************************/
/* The Information Part of Dictionary Entry Node */
typedef struct {
    UDWORD next : 31;      /* Next Node Position : Array Index(0-256) */
    UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} CNNODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
    CNNODE_INFO node_info;      /* Dictionary Node Information Field */
    UDWORD InfoStart;         /* 기분석 결과정보의 시작위치        */
    UBYTE  InfoLen;           /* 기분석 결과정보의 길이            */
    HANGUL han;               /* Hangul Data Field                 */
} CNDIC_NODE;

/* Dictionary Search Result Structure */
typedef struct {
    UWORD len;                              /* 사전에 존재하는 서브스트링의 길이 */
    UDWORD InfoStart;
    UBYTE InfoLen;
} CNDIC_RESULT;

	
/**********************************************************
 * 사용자  기분석 사전 탐색용 자료유형 정의
 **********************************************************/
/* The Information Part of Dictionary Entry Node */
typedef struct {
    UDWORD next : 31;      /* Next Node Position : Array Index(0-256) */
    UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} USERNODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
    USERNODE_INFO node_info;      /* Dictionary Node Information Field */
    UDWORD InfoStart;         /* 기분석 결과정보의 시작위치        */
    UBYTE  InfoLen;           /* 기분석 결과정보의 길이            */
    HANGUL han;               /* Hangul Data Field                 */
} USERDIC_NODE;

/* Dictionary Search Result Structure */
typedef struct {
    UWORD len;                              /* 사전에 존재하는 서브스트링의 길이 */
    UDWORD InfoStart;
    UBYTE InfoLen;
} USERDIC_RESULT;


#endif /* _MADIC_TYPE_H_ */

