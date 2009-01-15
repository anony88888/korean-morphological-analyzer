#include <IDX_common.h>
#include <IDX_user.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>

int IDX_IndexByChar(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	char TempSecVal[MAXTEMPBUFSIZE];
	int ret_tok, PostInfoCnt = 0;
	UTF32 token[MAXTOKENLEN], *u32_ptr;
	UTF8  u8_tok[MAXTOKENLEN], *u8_ptr;
	int u8_len;
	int token_len;
	int wordNum, i;
	extern int HanjaFlag;
	extern int StartWordNum;

	wordNum = StartWordNum;

	/* "한자는 그대로" 플래그가 세팅되지 않으면 한글로 변환 */
	/* 수정 : 한자 플래그 1 --> 변환 */
	if (HanjaFlag == 1) {
		Hanja2Hangul_UTF8(SecVal, TempSecVal);
		InitTokenizer(TempSecVal);
	} else {
		InitTokenizer(SecVal);
	}	

/*
 * 2002-11-14
 * IndexByChar의 기능을 수정한다.
 * 불용어 검사를 위해서 다음과 같이 색인 방법을 수정한다.
 * 1. 단어단위로 토큰분리 수행
 * 2. 불용어 검사
 * 3. 불용어가 아닌 단어에 대해서 글자 분리
 */
	while ((ret_tok = GetNextToken(token, &token_len, 0)) != -1) {
		switch (ret_tok) {
			case T_DEL:
				wordNum++;
				break;

			case T_HAN:	//한
			case T_LAT:	//영
			case T_CJK:	//한자
			case T_DIG:	//숫자
			case T_CYR:	//러시아어
				if (PostInfoCnt >= MAXPOSTINFOSIZE)
					return MAXPOSTINFOSIZE;
				u32_ptr = token;
				u8_ptr = u8_tok;
				ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_ptr, &(u8_tok[MAXTOKENLEN]), strictConversion, &u8_len);
				u8_tok[u8_len] = '\0';

				if (IDX_FindStopWord(u8_tok))
					break;

				for (i = 0; i < token_len; i++) {
					u32_ptr = &(token[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(token[i+1]), &u8_ptr, &(u8_tok[MAXTOKENLEN]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					if (ret_tok == T_LAT)
						strlower(PostInfo[PostInfoCnt].key);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum++;
					PostInfo[PostInfoCnt].psgNum = 0;
					if ( PostInfo[PostInfoCnt].keyLen > MAXKEYLEN )
						PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
					PostInfoCnt++;

					if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
						return PostInfoCnt;
				}

				break;

			default :
				break;
		}
	}

	return PostInfoCnt;
}
