#ifndef _MA_SEARCHTAILDIC_H_
#define _MA_SEARCHTAILDIC_H_

#define NTAIL_MODE		1     /* ü���� �������¼� ��� */
#define PTAIL_MODE		2     /* ����� �������¼� ��� */
#define BTAIL_MODE		3     /* ü���� ����-�������¼� ��� */

typedef struct {
	UBYTE Morp[VS_BUFLEN];
	BYTE Tag[VS_BUFLEN];
} MORPHEME;

tVOID InitTAILDicHeader();
DWORD LoadTAILDic(BYTE *dic_dir);
DWORD ClearTAILDic();
DWORD GetTAILContent(UDWORD s_idx, UBYTE len, UBYTE *Content, UWORD mode);
DWORD SearchTAILDic(HANGUL *h_word, UWORD h_word_len, DWORD h_idx
				, TAILDIC_RESULT *result, UWORD *res_idx, UWORD mode);

#endif /* _MA_SEARCHTAILDIC_H_ */
