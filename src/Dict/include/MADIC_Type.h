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
	UWORD len;				/* ������ �����ϴ� ���꽺Ʈ���� ���� */
	UWORD jong;				/* ������ ���Ե��� ���� ä�� ���� �˻��� �Ǿ��� �� */
#ifdef MULTI_DIC_INFO
	UBYTE info[20];
#else
	BYTE info;				/* ���� ���� */
#endif
} DIC_RESULT;

#ifdef MULTI_DIC_INFO
typedef struct {
	UWORD len;				/* ������ �����ϴ� ���꽺Ʈ���� ���� */
	UWORD jong;				/* ������ ���Ե��� ���� ä�� ���� �˻��� �Ǿ��� �� */
	BYTE info;				/* ���� ���� */
} JEDIC_RESULT;
#endif

typedef struct {
	UWORD len;				/* ������ �����ϴ� ���꽺Ʈ���� ���� */
	UWORD jong;				/* ������ ���Ե��� ���� ä�� ���� �˻��� �Ǿ��� �� */
	BYTE info[50];			/* ���� ���� */
	UWORD ninfo;			/* ���� ���� ���� */
	UWORD idx;				/* ���ո�� ó������ ���Ǵ� ���� */
} CDIC_RESULT;

/**********************************************************
 * ����ġ���� ������ �������¼� ���� ���� ���� Ÿ��...
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
 * ����ġ���� ������ �������¼� ���� ���� ���� Ÿ��...
**********************************************************/
/* The Information Part of Dictionary Entry Node */
typedef struct {
	UDWORD next : 31;     /* Next Node Position : Array Index(0-256) */
	UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} TAILNODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
	TAILNODE_INFO node_info;  /* Dictionary Node Information Field */
	UDWORD InfoStart;         /* ��м� ��������� ������ġ        */
	UBYTE  InfoLen;           /* ��м� ��������� ����            */
	HANGUL han;               /* Hangul Data Field                 */
} TAILDIC_NODE;

/* Dictionary Search Result Structure */
typedef struct {
	UWORD len;      /* ������ �����ϴ� ���꽺Ʈ���� ���� */
	UDWORD InfoStart;
	UBYTE InfoLen;
} TAILDIC_RESULT;


/**********************************************************
 * ���ո�� ��м� ���� Ž���� �ڷ����� ����
 **********************************************************/
/* The Information Part of Dictionary Entry Node */
typedef struct {
    UDWORD next : 31;      /* Next Node Position : Array Index(0-256) */
    UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} CNNODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
    CNNODE_INFO node_info;      /* Dictionary Node Information Field */
    UDWORD InfoStart;         /* ��м� ��������� ������ġ        */
    UBYTE  InfoLen;           /* ��м� ��������� ����            */
    HANGUL han;               /* Hangul Data Field                 */
} CNDIC_NODE;

/* Dictionary Search Result Structure */
typedef struct {
    UWORD len;                              /* ������ �����ϴ� ���꽺Ʈ���� ���� */
    UDWORD InfoStart;
    UBYTE InfoLen;
} CNDIC_RESULT;

	
/**********************************************************
 * �����  ��м� ���� Ž���� �ڷ����� ����
 **********************************************************/
/* The Information Part of Dictionary Entry Node */
typedef struct {
    UDWORD next : 31;      /* Next Node Position : Array Index(0-256) */
    UDWORD brk  : 1;      /* Word Information Field(0-1)             */
} USERNODE_INFO;

/* The Integrated Dictionary Node : Information + Data */
typedef struct {
    USERNODE_INFO node_info;      /* Dictionary Node Information Field */
    UDWORD InfoStart;         /* ��м� ��������� ������ġ        */
    UBYTE  InfoLen;           /* ��м� ��������� ����            */
    HANGUL han;               /* Hangul Data Field                 */
} USERDIC_NODE;

/* Dictionary Search Result Structure */
typedef struct {
    UWORD len;                              /* ������ �����ϴ� ���꽺Ʈ���� ���� */
    UDWORD InfoStart;
    UBYTE InfoLen;
} USERDIC_RESULT;


#endif /* _MADIC_TYPE_H_ */

