#include <IDX_common.h>
#include <IDX_user.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>


/*
 * 색인 타입 : INDEX_BY_TOKEN
 */
int IDX_IndexByCDToken(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int		ret_tok, PostInfoCnt = 0, local_PostInfoCnt;
	UTF32	token[MAXTOKENLEN], *u32_ptr;
	UTF32	hconv_tok[MAXTOKENLEN];
	UTF8	u8_str[MAXTOKENLEN], *u8_start_ptr, *u8_end_ptr;
	int		u8str_len;
	int		token_len;
	int		i, j;
	int		wordNum = 1;
	ConversionResult cnvt_res;

	//////////////////////////////////////////////////////
	// 대역어 변환용 변수 선언
	POSTINFO PrevIndex[50], CurrIndex[50];
	int PrevIndexCnt = 0, CurrIndexCnt = 0;
	int initCheck = 1;
	//////////////////////////////////////////////////////

	extern int HanjaFlag;
	extern int StartWordNum;

	wordNum = StartWordNum;

	InitTokenizer((unsigned char *) SecVal);

	while ((ret_tok = GetNextToken(token, &token_len, 0)) != -1) {
		if (token_len > 42)
			continue;
		switch (ret_tok) {
			case T_CJK: /* 한자 */
				/* "한자는 그대로" 플래그가 세팅되지 않으면 한글로 변환 */
				/* 한자 플래그 1 --> 변환 */
				if (HanjaFlag == 1) {
					Hanja2Hangul_UCS4((int *)token, token_len, (int *)hconv_tok);

					/* UCS4 --> UTF-8 */
					u32_ptr = hconv_tok;
					u8_start_ptr = (UTF8 *) u8_str;
					u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
					cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

					u8_str[u8str_len] = '\0';
					strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
					PostInfo[PostInfoCnt].keyLen = u8str_len;
					PostInfo[PostInfoCnt].psgNum = 0;
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
					strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
					PostInfo[PostInfoCnt].keyLen = u8str_len;
					PostInfo[PostInfoCnt].psgNum = 0;
					PostInfo[PostInfoCnt].wordNum = wordNum++;

					PostInfoCnt++;

					if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
						return PostInfoCnt;
				}

				break;

			case T_HAN: /* 한글 */
			case T_DIG:	/* 숫자 */
			case T_LAT: /* 영어 */
				/* UCS4 --> UTF-8 */
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

				u8_str[u8str_len] = '\0';
				if (IDX_FindStopWord(u8_str)) 
					break;
				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
				if (ret_tok == T_LAT) 
					strlower(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].keyLen = u8str_len;
				PostInfo[PostInfoCnt].psgNum = 0;
				PostInfo[PostInfoCnt].wordNum = wordNum++;
				PostInfoCnt++;

				//////////////////////////////////////////////////////////////////////////////////////////////////////
				// 대역어 사전 변환
				strcpy(CurrIndex[0].key, PostInfo[PostInfoCnt-1].key);
				CurrIndex[0].wordNum = wordNum - 1;
				CurrIndexCnt = 1;

				if (initCheck) {
					PrevIndex[0].key[0] = '\0';
					for (i = 0; i < CurrIndexCnt; i++) {
						local_PostInfoCnt = IDX_CheckCrossDic(&PrevIndex[0], &CurrIndex[i], &PostInfo[PostInfoCnt], 1);
						PostInfoCnt += local_PostInfoCnt;
					}

					initCheck = 0;
				} else {
					for (i = 0; i < CurrIndexCnt; i++) {
						for (j = 0; j < PrevIndexCnt; j++) {
							if (j == 0)
								local_PostInfoCnt = IDX_CheckCrossDic(&PrevIndex[j], &CurrIndex[i], &PostInfo[PostInfoCnt], 1);
							else
								local_PostInfoCnt = IDX_CheckCrossDic(&PrevIndex[j], &CurrIndex[i], &PostInfo[PostInfoCnt], 0);

							PostInfoCnt += local_PostInfoCnt;
						}
					}
				}
				memcpy((void *)PrevIndex, (void *)CurrIndex, sizeof(POSTINFO) * CurrIndexCnt);
				PrevIndexCnt = CurrIndexCnt;
				//////////////////////////////////////////////////////////////////////////////////////////////////////

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
			case  T_KO: /* 한글 */
			case  T_EN: /* 영어 */
			case  T_HJ: /* 한자 */
			case  T_JP: /* 일어 */
			case  T_DG: /* 숫자 */
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
