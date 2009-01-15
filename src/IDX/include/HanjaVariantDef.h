#ifndef HANJA_VARIANT_DEF_H_
#define HANJA_VARIANT_DEF_H_

#define MAX_ITEM_NUM            11877
#define MAX_SUB_ITEM_NUM        10
#define CARD_V                  999999

#define HANJA_VARIANT_TABLE		"hv_table"

typedef struct {
	unsigned int h_code;
	unsigned int T_val[MAX_SUB_ITEM_NUM]; // 마지막을 나타내는 값은 TERMINAL_VALUE
	unsigned int V_val[MAX_SUB_ITEM_NUM];
	unsigned int S_val[MAX_SUB_ITEM_NUM];
} HVARIANT;

int LoadHanjaVariantTable(char *in_file);
int AppendHanjaVariableToPostInfo(unsigned int h_code, POSTINFO *PostInfo, int wordNum, int Option, int CurrPICnt);
HVARIANT *GetHanjaVariantInfo(unsigned int hcode);
int compareHanjaCode(const void* hv1, const void* hv2);

#endif
