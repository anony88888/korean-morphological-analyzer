#include <IDX_common.h>
#include <IDX_user.h>
#include <MA_Interface.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>
#include "hj2hg.h"
#include <HanjaVariantDef.h>
#include <IDX_Hanja2Hangul.h>
#include <assert.h>

int IDX_PrevToken(int idx);

/*
 * 2003-05-28, ���� ���� �߰�
 * �Ϲ����� IndexByMA ���� ������ �����ϵ�...
 * ���ڿ� ���ؼ��� ���� ���� ����
 */
/* UTF-8 �Է� */
int IDX_IndexByMixMA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int		ret_tok, PostInfoCnt = 0, tempPostInfoCnt, org_PostInfoCnt;
	UTF32	token[MAXTOKENLEN+1], u32_str[MAXTOKENLEN+1], *u32_ptr;
	UTF8	u8_str[MAXTOKENLEN+1], *u8_start_ptr, *u8_end_ptr, *u8_ptr, u8_tok[MAXTOKENLEN+1];
	UTF8    original_word[MAXTOKENLEN+1];
	int		u8str_len, u8_len;
	int		token_len;
	JO_CHAR	j_hanstr[MAXTOKENLEN+1];
	int		j_hanstr_len;
	int		idx_num, i, j, k;
	JO_INDEX_WORD idx_words;
	ConversionResult cnvt_res;
	int		wordNum = 1, max_wordNum = 0, org_wordNum;
	int		old_psgNum, firstFlag = 1;
	/*unsigned*/ char TempVal[512], *ptr;
	char 	hg_buf[1024];

	extern int StemCheck;
	extern int StartWordNum;
	extern int IDX_HANJA_PROC_OPTION;

	wordNum = StartWordNum;

	InitTokenizer((unsigned char *) SecVal);

	while ((ret_tok = GetNextToken(token, &token_len, 0)) != -1) {
		u32_ptr = token;
		u8_start_ptr = (UTF8 *) u8_str;
		u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
		cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
		u8_str[u8str_len] = '\0';

		switch (ret_tok) {
			case T_DEL: /* �и��� ���� */
				wordNum++;  // ���⿡���� �и��ڵ� �ϳ��� �����̶�� �����ϰ� [���ξ�][�и���][���ξ�]�϶� 1 --> 3 �� �ǵ��� �Ѵ�.
				break;

			case T_HAN: /* �ѱ� */
				// [DEL]+[�ѱ�]+[DEL]+[�ѱ�](���� ��ū)
				// �� �� �� �ѱ���ū�� wordNum�� ���̴� 2�� �ƴ϶� 1�̴�.
				// �׷��� �ٸ� ���
				// [����]+[�ѱ�]+[DEL]+[�ѱ�] �϶��� 
				// �� �ѱ���ū�� wordNum ���̴� 2�̴�.
				if ((IDX_PrevToken(-1) == T_DEL) && (IDX_PrevToken(-2) == T_HAN) && ((IDX_PrevToken(-3) == T_DEL)||(IDX_PrevToken(-3) == -1)))
					wordNum--;

				if (token_len > 42)
					continue;

				/* �ҿ�� ���� */
				if (IDX_FindStopWord((char*)u8_str))
					continue;

				strcpy((char*)original_word, (char*)u8_str);

				/* UCS4 --> Johab */
				j_hanstr_len = 0;
				for (i = 0; i < token_len; i++) {
					/*
					ucs2_to_johab((int) token[i], (int *) &(j_hanstr[j_hanstr_len].j_code));
					*/
					j_hanstr[j_hanstr_len].j_code = ucs2_to_johab((unsigned int) token[i]);
					j_hanstr[j_hanstr_len].j_han.sign = 1;
					j_hanstr_len++;
				}

				org_wordNum = wordNum;
				org_PostInfoCnt = PostInfoCnt;
				max_wordNum = 0;

				/* ������ ���� ���� ���� */
				idx_num = GetIndexFromOneWord(j_hanstr, j_hanstr_len, &idx_words, 1);

				if (idx_num > 0) {
					firstFlag = 1;
					for (j = 0; j < idx_words.nIndex; j++) {
						/* �ߺ� ���ξ� ���� �������� str_len���� 0���� �����ϹǷ� �� �κ��� �� �־�� �Ѵ�. */
						if (idx_words.IDX[j].str_len == 0)
							continue;


						/* Johab --> UCS4 */
						for (k = 0; k < idx_words.IDX[j].str_len; k++)
							u32_str[k] = johab_to_ucs2((unsigned int)(idx_words.IDX[j].str[k].j_code));

						/* UCS4 --> UTF-8 */
						u32_ptr = u32_str;
						u8_start_ptr = (UTF8 *) u8_str;
						u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
						cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(u32_str[k]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

						u8_str[u8str_len] = '\0';

                        /*
						 * 2003-06-02 �ҿ�� ó��
						 * ���¼Һм� ����� ���� �ҿ�� ó�� �߰�
						 * 2�����̻��� ���ϸ�翡 ���ؼ��� �ҿ�� ó��
						 */
						if (idx_words.IDX[j].str_len >= 2 && idx_words.nIndex == 1) {
						/* �ҿ�� ���� */
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
					// ���� ��ü�� ���ξ�� ����(2005/02/14)
					/////////////////////////////////////////////////////////////////
					for (k = org_PostInfoCnt; k < PostInfoCnt; k++)
						if (!strcmp((char *)original_word, PostInfo[k].key))
							break;
					if (k == PostInfoCnt) {
						strcpy(PostInfo[PostInfoCnt].key, (char *) original_word);
						PostInfo[PostInfoCnt].keyLen = strlen((char *)original_word);
						PostInfo[PostInfoCnt].psgNum = 7777;
						PostInfo[PostInfoCnt].wordNum = org_wordNum;
						if (org_PostInfoCnt == PostInfoCnt) // ���ξ ���� ����...
							wordNum++;
						PostInfoCnt++;
					}
				}

				break;

			case T_CJK: /* ���� */
			case T_PRI:
			case T_JPN:
				for (i = 0; i < token_len; i++) {
					u32_ptr = &(token[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(token[i+1]), &u8_ptr, &(u8_tok[MAXTOKENLEN]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, (char *)u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen((char *)u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum++;
					PostInfo[PostInfoCnt].psgNum = 0;
					if ( PostInfo[PostInfoCnt].keyLen > MAXKEYLEN )
						PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
					PostInfoCnt++;

                    if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
					    return PostInfoCnt;


					// 2005-12-12 
					// T_PRI ������ Ȯ�����ڿ� ���ؼ��� ó��
					if (ret_tok == T_CJK || ret_tok == T_PRI) {
						// 2004-06-07 : �ѱ�-���� ��ȯ���̺��� �ܺη� �� 
						/*
					if (((token[i]-INIT_HANJA_CODE) >= 0 && (token[i]-INIT_HANJA_CODE)<HJ2HG_TABLE_SIZE) && (Hj2Hg_Table[token[i]-INIT_HANJA_CODE][0] != '\0')) {
					*/
						if (GetHangulChars(token[i], hg_buf)) {
						//strcpy(TempVal, Hj2Hg_Table[token[i]-INIT_HANJA_CODE]);
						strcpy((char*)TempVal, hg_buf);
						ptr = strtok((char*)TempVal, " ");
						while (ptr != NULL) {
							strcpy(PostInfo[PostInfoCnt].key, (char*)ptr);
							PostInfo[PostInfoCnt].keyLen = strlen((char*)ptr);
							PostInfo[PostInfoCnt].wordNum = wordNum - 1;
							PostInfo[PostInfoCnt].psgNum = 1000; /* �ѱۺ�ȯ���ڿ� ���ؼ��� ���� ����ǥ�� */
							PostInfoCnt++;

							if (DuemConv((char*)ptr, (char*)TempVal)) {
								strcpy(PostInfo[PostInfoCnt].key, TempVal);
								PostInfo[PostInfoCnt].keyLen = strlen(TempVal);
								PostInfo[PostInfoCnt].wordNum = wordNum - 1;
								PostInfo[PostInfoCnt].psgNum = 1000; /* �ѱۺ�ȯ���ڿ� ���ؼ��� ���� ����ǥ�� */
								PostInfoCnt++;
							}

							if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
								return PostInfoCnt;

							ptr = strtok(NULL, " ");
						}
					}

					/* ��ü�� ���� �߰� */
					if (IDX_HANJA_PROC_OPTION >= 10) {
						tempPostInfoCnt = AppendHanjaVariableToPostInfo(token[i], &PostInfo[PostInfoCnt], wordNum-1, IDX_HANJA_PROC_OPTION, PostInfoCnt);
						PostInfoCnt += tempPostInfoCnt;
					}
					}

				}
//				wordNum++;

				break;

				// UTF-8�� ��ȯ�ϰ� �ٷ� IDX_IndexByMixChar �Լ��� ȣ���Ѵ�.
				/*
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[1024]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
				u8_str[u8str_len] = '\0';

				StartWordNum = wordNum;
				localPostInfoCnt = IDX_IndexByMixChar(u8_str, &PostInfo[PostInfoCnt], StopCheck);
				PostInfoCnt += localPostInfoCnt;
				wordNum = PostInfo[PostInfoCnt-1].wordNum + 1;
				*/

			case T_DIG:	/* ���� */
			case T_CYR:	/* ���þ� */
				/* UCS4 --> UTF-8 */
				/*
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[1024]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

				u8_str[u8str_len] = '\0';
				*/
				
				/* �ҿ�� ���� */
				if (IDX_FindStopWord((char *)u8_str))
					continue;

				if (strlen((char *)u8_str) > MAXKEYLEN)
					continue;
				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
				PostInfo[PostInfoCnt].psgNum = 1;
				PostInfo[PostInfoCnt].keyLen = strlen((char *)u8_str);
				PostInfo[PostInfoCnt].wordNum = wordNum++;

				PostInfoCnt++;

				if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
					return PostInfoCnt;

				break;

			case T_LAT: /* ���� */
				/* UCS4 --> UTF-8 */
				/*
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[1024]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
				u8_str[u8str_len] = '\0';
				*/
				/* �ҿ�� ���� */
				if (IDX_FindStopWord((char *)u8_str))
					continue;
				if (strlen((char *)u8_str) > MAXKEYLEN)
					continue;
				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);

				/* ���� ���¹� */
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
