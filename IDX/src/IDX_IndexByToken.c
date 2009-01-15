#include <IDX_common.h>
#include <IDX_user.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>


/*
 * ���� Ÿ�� : INDEX_BY_TOKEN
 */
int IDX_IndexByToken(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int		ret_tok, PostInfoCnt = 0;
	UTF32	token[MAXTOKENLEN], *u32_ptr;
	UTF32	hconv_tok[MAXTOKENLEN];
	UTF8	u8_str[MAXTOKENLEN], *u8_start_ptr, *u8_end_ptr;
	int		u8str_len;
	int		token_len;
	int		wordNum = 1;
	ConversionResult cnvt_res;

	extern int HanjaFlag;
	extern int StartWordNum;
	extern unsigned int SW_Set_Num;

	wordNum = StartWordNum;

	InitTokenizer((unsigned char *) SecVal);

	while ((ret_tok = GetNextToken(token, &token_len, 1)) != -1) {
		if (token_len > MAXKEYLEN/2)
			continue;
		switch (ret_tok) {
			case T_CJK: /* ���� */
				/* "���ڴ� �״��" �÷��װ� ���õ��� ������ �ѱ۷� ��ȯ */
				/* ���� �÷��� 1 --> ��ȯ */
				if (HanjaFlag == 1) {
					Hanja2Hangul_UCS4((unsigned int *)token, token_len, (unsigned int *)hconv_tok);

					/* UCS4 --> UTF-8 */
					u32_ptr = hconv_tok;
					u8_start_ptr = (UTF8 *) u8_str;
					u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
					cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(hconv_tok[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
					// 2006-07-18 :: �ι�° �μ��� hconv_tok�� �ƴ϶�, token�� �����Ǿ� �־���...
					// ���� �ɰ��� ���׿���... �����Ϸ�

					u8_str[u8str_len] = '\0';

					RemoveDCode(u8_str);

					strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
					PostInfo[PostInfoCnt].keyLen = u8str_len;
					PostInfo[PostInfoCnt].psgNum = ret_tok;
					PostInfo[PostInfoCnt].wordNum = wordNum++;

					PostInfoCnt++;
				} else {
					/* UCS4 --> UTF-8 */
					u32_ptr = token;
					u8_start_ptr = (UTF8 *) u8_str;
					u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
					cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

					u8_str[u8str_len] = '\0';

					if (IDX_FindStopWord(u8_str)) 
						break;

					RemoveDCode(u8_str);

					strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
					PostInfo[PostInfoCnt].keyLen = u8str_len;
					PostInfo[PostInfoCnt].psgNum = ret_tok;
					PostInfo[PostInfoCnt].wordNum = wordNum++;

					PostInfoCnt++;

					if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
						return PostInfoCnt;
				}

				break;

			case T_JPN:	/* �Ϻ��� */
			case T_PRI: /* ��� */
			case T_HAN: /* �ѱ� */
			case T_DIG:	/* ���� */
			case T_LAT: /* ���� */
			case T_CYR: /* ���þƾ� */
			case T_CMP: /* ������ū */
				/* UCS4 --> UTF-8 */
				if (HanjaFlag == 1) {
					Hanja2Hangul_UCS4((unsigned int *)token, token_len, (unsigned int *)hconv_tok);

					/* UCS4 --> UTF-8 */
					u32_ptr = hconv_tok;
					u8_start_ptr = (UTF8 *) u8_str;
					u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
					cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(hconv_tok[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
					// 2006-07-18 :: �ι�° �μ��� hconv_tok�� �ƴ϶�, token�� �����Ǿ� �־���...
					// ���� �ɰ��� ���׿���... �����Ϸ�

					u8_str[u8str_len] = '\0';
				} else {
					u32_ptr = token;
					u8_start_ptr = (UTF8 *) u8_str;
					u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
					cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

					u8_str[u8str_len] = '\0';
				}

				if (IDX_FindStopWord(u8_str)) 
					break;

				RemoveDCode(u8_str);

				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
				//if (ret_tok == T_LAT) 
					strlower(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].keyLen = u8str_len;
				PostInfo[PostInfoCnt].psgNum = ret_tok;
				PostInfo[PostInfoCnt].wordNum = wordNum++;

				PostInfoCnt++;

				if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
					return PostInfoCnt;

				break;

			default:
				break;
		}
	}

	return PostInfoCnt;
}

#if 0
int IDX_IndexByToken(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int			PostInfoCnt = 0;
	char		*SecPtrOrg;
	char		*TokPtrOrg;
	char		TokBuf[MAXKEYLEN];
	int			CharType;
	char		UseAsIndex;
	char		*SecPtr = SecVal;
	int		wordNum = 0;

	SecPtrOrg = SecPtr;
	while ( *SecPtr ) {
		TokPtrOrg = SecPtr;
		CharType = IDX_TokenIndexByToken(&SecPtr, TokBuf);
		if ( !strlen(TokBuf) ) continue;

		switch ( CharType ) {
			case  T_KO: /* �ѱ� */
			case  T_EN: /* ���� */
			case  T_HJ: /* ���� */
			case  T_JP: /* �Ͼ� */
			case  T_DG: /* ���� */
				if ( PostInfoCnt >= MAXPOSTINFOSIZE )
					return ( MAXPOSTINFOSIZE );

				UseAsIndex = TokGrp[CharType].TokGrp;
				if (UseAsIndex == '1') {
					strcpy(PostInfo[PostInfoCnt].key, TokBuf);
					if (CharType == T_EN) {
						strlower(PostInfo[PostInfoCnt].key);
					}
					if (StopCheck && IDX_FindStopWord(PostInfo[PostInfoCnt].key)) {
#ifdef DEBUG
						printf("Stopword : %s\n", PostInfo[PostInfoCnt].key);
#endif
					}    /* do nothing */
					else {
						PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
						if (PostInfo[PostInfoCnt].keyLen <= 0)
							break;
						PostInfo[PostInfoCnt].wordNum = ++wordNum;
						PostInfo[PostInfoCnt].psgNum = 0;
						if ( PostInfo[PostInfoCnt].keyLen > MAXKEYLEN )
							PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
						PostInfoCnt++;
					}
				}

				break;

			case  T_SC:
			case  T_CK:
			case  T_U1:
			case  T_U2:
				++wordNum;
		}
	}

	return PostInfoCnt;
}
#endif
