#include <IDX_common.h>
#include <IDX_user.h>
#include <MA_Interface.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>
#include <assert.h>
#include <boost/scoped_array.hpp>

/*
 * 색인 타입 : INDEX_BY_MA
 *
 * 토큰 분리가 문제가 될 수 있다.
 * 일단 현재는 색인기 내부의 토큰 분리기를 사용하고...
 * 나중에 이 토큰 분리기를 IDX로 올리는 작업을 수행해야 한다.
 */
#if 0
extern INDEX_WORD *IndexWords;

int IDX_IndexByMA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int PostInfoCnt = 0;
	int i, j;
	int wordNum = 0;
	int IW_num, ret_val;

	IW_num = GetIndexWord(SecVal, IndexWords);
	for (i = 0; i < IW_num ; i++) {
		for (j = 0; j < IndexWords[i].nIndex; j++) {
			PostInfo[PostInfoCnt].keyLen = strlen(IndexWords[i].IDX[j].str);
			if (PostInfo[PostInfoCnt].keyLen <= 0)
				continue;
			PostInfo[PostInfoCnt].wordNum = wordNum++;
			/*
			 * 복합명사 분석 결과에 대한 처리는 따로 한다.
			 * psgNum을 이용해서...
			 * 복합명사 분석의 결과가 한 어절에 대해서 여러개로 나올 수가 있으므로
			 * 예를 들면,
			 * 정보검색(1)+시스템(1), 정보(2)+검색(2)+시스템(2), ....
			 * 이 값은 색인기 내부에서 loc을 통해서 전달한다.
			 */
			strcpy(PostInfo[PostInfoCnt].key, IndexWords[i].IDX[j].str);
			PostInfo[PostInfoCnt].psgNum = IndexWords[i].IDX[j].loc;
			if (PostInfo[PostInfoCnt].keyLen > MAXKEYLEN)
				PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;

			PostInfoCnt++;
		}
	}

	return PostInfoCnt;
}
#endif

/* UTF-8 입력 */
int IDX_IndexByMA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int		ret_tok, PostInfoCnt = 0, org_PostInfoCnt;
	UTF32	token[MAXTOKENLEN], u32_str[MAXTOKENLEN], *u32_ptr;
	UTF32	hconv_tok[MAXTOKENLEN];
	UTF8	u8_str[MAXTOKENLEN], *u8_start_ptr, *u8_end_ptr;
	//UTF8	original_word[MAXTOKENLEN];
	boost::scoped_array<UTF8> original_word(new UTF8[MAXTOKENLEN]);
	int		u8str_len;
	int		token_len;
	JO_CHAR	j_hanstr[MAXTOKENLEN];
	int		j_hanstr_len;
	int		idx_num, i, j, k;
	JO_INDEX_WORD idx_words;
	ConversionResult cnvt_res;
	int		wordNum = 1, max_wordNum = 0, org_wordNum;
	int		old_psgNum, firstFlag = 1;

	extern int StemCheck;
	extern int HanjaFlag;
	extern int StartWordNum;

	if (0 == original_word)
		return 0;

	wordNum = StartWordNum;

	InitTokenizer((unsigned char *) SecVal);

	while ((ret_tok = GetNextToken(token, &token_len, 0)) != -1) {
		if (token_len > 42)
			continue;

		u32_ptr = token;
		u8_start_ptr = (UTF8 *) u8_str;
		u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN - 1]);
		cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
		u8_str[u8str_len] = '\0';
		
		/* 불용어 제거 */
		if (IDX_FindStopWord((char*)u8_str))
			continue;

		strcpy((char*)original_word.get(), (char*)u8_str);

		switch (ret_tok) {
			case T_HAN: /* 한글 */
				/* UCS4 --> Johab */
				j_hanstr_len = 0;
				for (i = 0; i < token_len; i++) {
					/*
					ucs2_to_johab((int) token[i], (int *) &(j_hanstr[j_hanstr_len].j_code));
					*/
					j_hanstr[j_hanstr_len].j_code = ucs2_to_johab((int) token[i]);
					j_hanstr[j_hanstr_len].j_han.sign = 1;
					j_hanstr_len++;
				}

				org_wordNum = wordNum;
				org_PostInfoCnt = PostInfoCnt;
				max_wordNum = 0;

				/* 조합형 어절 색인 수행 */
				idx_num = GetIndexFromOneWord(j_hanstr, j_hanstr_len, &idx_words, 1);
			//	printf("\nIDX_ByMa\n");
				if (idx_num > 0) {
					firstFlag = 1;
					for (j = 0; j < idx_words.nIndex; j++) {
						/* 중복 색인어 제거 과정에서 str_len값을 0으로 세팅하므로 이 부분을 꼭 넣어야 한다. */
						if (idx_words.IDX[j].str_len == 0)
							continue;


						/* Johab --> UCS4 */
						for (k = 0; k < idx_words.IDX[j].str_len; k++)
							u32_str[k] = johab_to_ucs2((int)(idx_words.IDX[j].str[k].j_code));

						/* UCS4 --> UTF-8 */
						u32_ptr = u32_str;
						u8_start_ptr = (UTF8 *) u8_str;
						u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
						cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(u32_str[k]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

						u8_str[u8str_len] = '\0';
						/*
						 * 2003-06-02 불용어 처리
						 * 형태소분석 결과에 대한 불용어 처리 추가
						 * 2음절이상인 단일명사에 대해서만 불용어 처리
						 */
						if (idx_words.IDX[j].str_len >= 2 && idx_words.nIndex == 1) {
							/* 불용어 제거 */
							if (IDX_FindStopWord((char*)u8_str))
								continue;
						}

						strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
						PostInfo[PostInfoCnt].keyLen = u8str_len;
						PostInfo[PostInfoCnt].psgNum = idx_words.IDX[j].loc;

						if (firstFlag) {
							firstFlag = 0;
							old_psgNum = PostInfo[PostInfoCnt].psgNum;
						} else {
							if (old_psgNum != PostInfo[PostInfoCnt].psgNum) {
								wordNum = org_wordNum;
								old_psgNum = PostInfo[PostInfoCnt].psgNum;
							}
						}

						if (max_wordNum < wordNum)
							max_wordNum = wordNum;

						PostInfo[PostInfoCnt].wordNum = wordNum++;
						PostInfoCnt++;

						if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
							return PostInfoCnt;
					}

					if (max_wordNum != 0)
						wordNum = max_wordNum + 1;

					/////////////////////////////////////////////////////////////////
					// 워드 자체도 색인어로 지정(2005/02/14)
					/////////////////////////////////////////////////////////////////
					for (k = org_PostInfoCnt; k < PostInfoCnt; k++)
						if (!strcmp((char*)original_word.get(), PostInfo[k].key))
							break;
					if (k == PostInfoCnt) {
						strcpy(PostInfo[PostInfoCnt].key, (char *) original_word.get());
						PostInfo[PostInfoCnt].keyLen = strlen((char*)original_word.get());
						PostInfo[PostInfoCnt].psgNum = 7777;
						PostInfo[PostInfoCnt].wordNum = org_wordNum;
						if (org_PostInfoCnt == PostInfoCnt) // 색인어가 없는 어절...
							wordNum++;
						PostInfoCnt++;
					}
					/////////////////////////////////////////////////////////////////
				}

				break;

			case T_CJK: /* 한자 */
				/* "한자는 그대로" 플래그가 세팅되지 않으면 한글로 변환 */
				/* 수정 : 한자 플래그 1 --> 변환 */
				if (HanjaFlag == 1) {
					Hanja2Hangul_UCS4(token, token_len, hconv_tok);

					/* 색인 수행 */

					/* UCS4 --> Johab */
					j_hanstr_len = 0;
					for (i = 0; i < token_len; i++) {
						/*
						ucs2_to_johab((int) hconv_tok[i], (int *) &(j_hanstr[j_hanstr_len].j_code));
						*/
						j_hanstr[j_hanstr_len].j_code = ucs2_to_johab((int) hconv_tok[i]);
						j_hanstr[j_hanstr_len].j_han.sign = 1;
						j_hanstr_len++;
					}

					org_wordNum = wordNum;
					max_wordNum = 0;

					/* 조합형 어절 색인 수행 */
					idx_num = GetIndexFromOneWord(j_hanstr, j_hanstr_len, &idx_words, 1);

					if (idx_num > 0) {
						firstFlag = 1;
						for (j = 0; j < idx_words.nIndex; j++) {
							/* 중복 색인어 제거 과정에서 str_len값을 0으로 세팅하므로 이 부분을 꼭 넣어야 한다. */
							if (idx_words.IDX[j].str_len == 0)
								continue;

							/* Johab --> UCS4 */
							for (k = 0; k < idx_words.IDX[j].str_len; k++)
								u32_str[k] = johab_to_ucs2((int)(idx_words.IDX[j].str[k].j_code));

							/* UCS4 --> UTF-8 */
							u32_ptr = u32_str;
							u8_start_ptr = (UTF8 *) u8_str;
							u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
							cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(u32_str[k]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

							u8_str[u8str_len] = '\0';
							strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
							PostInfo[PostInfoCnt].keyLen = u8str_len;
							PostInfo[PostInfoCnt].psgNum = idx_words.IDX[j].loc;

							if (firstFlag) {
								firstFlag = 0;
								old_psgNum = PostInfo[PostInfoCnt].psgNum;
							} else {
								if (old_psgNum != PostInfo[PostInfoCnt].psgNum) {
									wordNum = org_wordNum;
									old_psgNum = PostInfo[PostInfoCnt].psgNum;
								}
							}

							if (max_wordNum < wordNum)
								max_wordNum = wordNum;

							PostInfo[PostInfoCnt].wordNum = wordNum++;
							PostInfoCnt++;

							if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
								return PostInfoCnt;
						}
						if (max_wordNum != 0)
							wordNum = max_wordNum + 1;
					}
				} else {
					/* UCS4 --> UTF-8 */
					u32_ptr = token;
					u8_start_ptr = (UTF8 *) u8_str;
					u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
					cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

					u8_str[u8str_len] = '\0';

					if (strlen((char*)u8_str) > MAXKEYLEN)
						break;

					strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
					PostInfo[PostInfoCnt].keyLen = u8str_len;
					PostInfo[PostInfoCnt].psgNum = 1;
					PostInfo[PostInfoCnt].wordNum = wordNum++;

					PostInfoCnt++;

					if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
						return PostInfoCnt;
				}

				break;

			case T_DIG:	/* 숫자 */
			case T_CYR: /* 러시아어 */
				/* UCS4 --> UTF-8 */
				/*
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[1024]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

				u8_str[u8str_len] = '\0';
				*/
				if (strlen((char*)u8_str) > MAXKEYLEN)
					break;
				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
				PostInfo[PostInfoCnt].keyLen = strlen((char*)u8_str);
				PostInfo[PostInfoCnt].psgNum = 1;
				PostInfo[PostInfoCnt].wordNum = wordNum++;

				PostInfoCnt++;

				if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
					return PostInfoCnt;

				break;

			case T_LAT: /* 영어 */
				/* UCS4 --> UTF-8 */
				/*
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[1024]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
				u8_str[u8str_len] = '\0';
				*/
				if (strlen((char*)u8_str) > MAXKEYLEN)
					break;

				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);

				/* 영어 스태밍 */
				if (StemCheck == 1) {
					IDX_strip_affixes(PostInfo[PostInfoCnt].key, &u8str_len);
					if (u8str_len <= 0)
						break;
				}


				PostInfo[PostInfoCnt].key[u8str_len] = '\0';
				strlower(PostInfo[PostInfoCnt].key);

				PostInfo[PostInfoCnt].keyLen = u8str_len;
				PostInfo[PostInfoCnt].psgNum = 1;
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
