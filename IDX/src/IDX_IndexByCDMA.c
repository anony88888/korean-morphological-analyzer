#include <IDX_common.h>
#include <IDX_user.h>
#include <MA_Interface.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>

/*
 * ���� Ÿ�� : INDEX_BY_MA
 *
 * ��ū �и��� ������ �� �� �ִ�.
 * �ϴ� ����� ���α� ������ ��ū �и��⸦ ����ϰ�...
 * ���߿� �� ��ū �и��⸦ IDX�� �ø��� �۾��� �����ؾ� �Ѵ�.
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
			 * ���ո�� �м� ����� ���� ó���� ���� �Ѵ�.
			 * psgNum�� �̿��ؼ�...
			 * ���ո�� �м��� ����� �� ������ ���ؼ� �������� ���� ���� �����Ƿ�
			 * ���� ���,
			 * �����˻�(1)+�ý���(1), ����(2)+�˻�(2)+�ý���(2), ....
			 * �� ���� ���α� ���ο��� loc�� ���ؼ� �����Ѵ�.
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


/*
 * �뿪�� ���� ��ȯ ����� ���� IndexByMA
 * ���� �ܾ ����
 */
int IDX_IndexByCDMA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int		ret_tok, PostInfoCnt = 0, local_PostInfoCnt;
	UTF32	token[MAXTOKENLEN], u32_str[MAXTOKENLEN], *u32_ptr;
	UTF32	hconv_tok[MAXTOKENLEN];
	UTF8	u8_str[MAXTOKENLEN], *u8_start_ptr, *u8_end_ptr;
	int		u8str_len;
	int		token_len;
	JO_CHAR	j_hanstr[MAXTOKENLEN];
	int		j_hanstr_len;
	int		idx_num, i, j, k;
	JO_INDEX_WORD idx_words;
	ConversionResult cnvt_res;
	int		wordNum = 1, max_wordNum = 0, org_wordNum;
	int		psgNum = 1, old_psgNum, firstFlag = 1;

/////////////////////////////////////////////////////////////////////////////////
	int isCNWord;			// ���ո�� ����
	POSTINFO PrevIndex[50], CurrIndex[50];	
	int PrevIndexCnt = 0, CurrIndexCnt = 0;
	int initCheck = 1;

// ���� �ܾ��� �ٷ� ���� ���ξ�
// �� �ܾ���� wordNum �������� wordNum - 1��ġ�� �ִ� ���ξ���̴�.
// ���� �ܾ ���ո���� ��, �������� ������� PrevWord�� ���ξ ���� �� �ִ�.
// �ϴ� ����� ���ո�� ����(psgNum == 100)�� ���ξ�� ������� �Ѵ�.
// �׷��� �Ϲ� ������絵 ���� ���ξ �� �� �ִ�.
/////////////////////////////////////////////////////////////////////////////////

	extern int StemCheck;
	extern int HanjaFlag;
	extern int StartWordNum;

	wordNum = StartWordNum;

#ifdef TRACE
	printf("1.Start InitTokenizer...\n");
#endif

	InitTokenizer((unsigned char *) SecVal);

#ifdef TRACE
	printf("2.End InitTokenizer...\n");
#endif

	while ((ret_tok = GetNextToken(token, &token_len, 0)) != -1) {
#ifdef TRACE
		printf("3.1.END GetNextToken\n");
#endif
		if (token_len > 42)
			continue;

		u32_ptr = token;
		u8_start_ptr = (UTF8 *) u8_str;
		u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
		cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
		u8_str[u8str_len] = '\0';
		
		/* �ҿ�� ���� */
		if (IDX_FindStopWord(u8_str))
			continue;

		switch (ret_tok) {
			case T_HAN: /* �ѱ� */
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
				max_wordNum = 0;

#ifdef TRACE
				printf("3.2.START GetIndexFromOneWord...\n");
#endif
				/* ������ ���� ���� ���� */
				idx_num = GetIndexFromOneWord(j_hanstr, j_hanstr_len, &idx_words, 1);
#ifdef TRACE
				printf("3.2.END GetIndexFromOneWord...\n");
#endif

				if (idx_num > 0) {
					firstFlag = 1;

					CurrIndexCnt = 0;
					///////////////////////////////////////////
					// ���ո�� ���� ����
					for (j = 0; j < idx_words.nIndex; j++) {
						if (idx_words.IDX[j].loc == 100) 
							break;
					}

					if (j < idx_words.nIndex)
						isCNWord = 1;
					else
						isCNWord = 0;
					///////////////////////////////////////////

					for (j = 0; j < idx_words.nIndex; j++) {
						/* �ߺ� ���ξ� ���� �������� str_len���� 0���� �����ϹǷ� �� �κ��� �� �־�� �Ѵ�. */
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
						 * 2003-06-02 �ҿ�� ó��
						 * ���¼Һм� ����� ���� �ҿ�� ó�� �߰�
						 * 2�����̻��� ���ϸ�翡 ���ؼ��� �ҿ�� ó��
						 */
						if (idx_words.IDX[j].str_len >= 2 && idx_words.nIndex == 1) {
							/* �ҿ�� ���� */
							if (IDX_FindStopWord(u8_str))
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

						//////////////////////////////////////////////////////////////////
						// �뿪�� ���� �˻���� ���ξ� ����
#ifdef CD_ROOT_CN_CHECK
						// 1. ���ո�� --> ����, ���ϸ�� --> ��� ��� ���
						if (isCNWord) {
							// ���ո���̸� ���ո�� ������ CurrIndex�� ����
							if (PostInfo[PostInfoCnt-1].psgNum == 100) {
								strcpy(CurrIndex[0].key, PostInfo[PostInfoCnt-1].key);
								CurrIndex[0].wordNum = PostInfo[PostInfoCnt-1].wordNum;
								CurrIndexCnt = 1;
							}
						} else {
							// ���ϸ���̸� �׳� ����
							strcpy(CurrIndex[0].key, PostInfo[PostInfoCnt-1].key);
							CurrIndex[0].wordNum = PostInfo[PostInfoCnt-1].wordNum;
							CurrIndexCnt = 1;
						}
#elif CD_ALL_CN_CHECK
#ifdef TRACE
						printf("3.3.CurrIndex Generation...\n");
#endif
						// 2. ���ո�� --> ��� �������, ���ϸ�� --> ��� ��� ���
						for (k = 0; k < CurrIndexCnt; k++) {	// �ߺ� üũ
							if (!strcmp(CurrIndex[k].key, PostInfo[PostInfoCnt-1].key))
								break;
						}
						if (k == CurrIndexCnt) {				// ������ ����
							strcpy(CurrIndex[CurrIndexCnt].key, PostInfo[PostInfoCnt-1].key);
							CurrIndex[CurrIndexCnt].wordNum = PostInfo[PostInfoCnt-1].wordNum;
							CurrIndexCnt++;
						}
#ifdef TRACE
						printf("3.3.CurrIndex Generation...END\n");
#endif
#endif
						//////////////////////////////////////////////////////////////////

						if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
							return PostInfoCnt;
					}

					///////////////////////////////////////////////////////////////////////
					// �뿪�� ��ȯ...
					///////////////////////////////////////////////////////////////////////
#ifdef TRACE
					printf("3.4.IDX_CheckCrossDic...(CurrIndexCnt=%d, PrevIndexCnt=%d)\n", CurrIndexCnt, PrevIndexCnt);
#endif
					if (initCheck) {
						PrevIndex[0].key[0] = '\0';
						for (i = 0; i < CurrIndexCnt; i++) {
#ifdef TRACE
							printf("3.4.1.IDX_CheckCrossDic...(i = %d)\n", i);
#endif
							local_PostInfoCnt = IDX_CheckCrossDic(&PrevIndex[0], &CurrIndex[i], &PostInfo[PostInfoCnt], 1);
#ifdef TRACE
							printf("3.4.1.IDX_CheckCrossDic...END\n");
#endif
							PostInfoCnt += local_PostInfoCnt;
						}

						initCheck = 0;
					} else {
						for (i = 0; i < CurrIndexCnt; i++) {
							for (j = 0; j < PrevIndexCnt; j++) {
								if (j == 0) {
									local_PostInfoCnt = IDX_CheckCrossDic(&PrevIndex[j], &CurrIndex[i], &PostInfo[PostInfoCnt], 1);
								} else {
									local_PostInfoCnt = IDX_CheckCrossDic(&PrevIndex[j], &CurrIndex[i], &PostInfo[PostInfoCnt], 0);
								}
#ifdef TRACE_CD
							printf("3.4.2.IDX_CheckCrossDic...(PrevIndex[%d].key=(%s), CurrIndex[%d].key=(%s))\n", i, PrevIndex[i].key, j, CurrIndex[j].key);
#endif
#ifdef TRACE_CD
							printf("3.4.2.IDX_CheckCrossDic...END\n");
#endif
								PostInfoCnt += local_PostInfoCnt;
							}
						}
					}
					memcpy((void *)PrevIndex, (void *)CurrIndex, sizeof(POSTINFO) * CurrIndexCnt);
					PrevIndexCnt = CurrIndexCnt;
#ifdef TRACE
					printf("3.4.IDX_CheckCrossDic...END\n");
#endif

					if (max_wordNum != 0)
						wordNum = max_wordNum + 1;
				}

				break;

			case T_CJK: /* ���� */
				/* "���ڴ� �״��" �÷��װ� ���õ��� ������ �ѱ۷� ��ȯ */
				/* ���� : ���� �÷��� 1 --> ��ȯ */
				if (HanjaFlag == 1) {
					Hanja2Hangul_UCS4((int *)token, token_len, (int *)hconv_tok);

					/* ���� ���� */

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
					strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
					PostInfo[PostInfoCnt].keyLen = u8str_len;
					PostInfo[PostInfoCnt].psgNum = 1;
					PostInfo[PostInfoCnt].wordNum = wordNum++;

					PostInfoCnt++;

					if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
						return PostInfoCnt;
				}

				break;

			case T_DIG:	/* ���� */
				/* UCS4 --> UTF-8 */
				/*
				u32_ptr = token;
				u8_start_ptr = (UTF8 *) u8_str;
				u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);

				u8_str[u8str_len] = '\0';
				*/
				strcpy(PostInfo[PostInfoCnt].key, (char *) u8_str);
				PostInfo[PostInfoCnt].keyLen = strlen(u8_str);
				PostInfo[PostInfoCnt].psgNum = 1;
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
				u8_end_ptr = (UTF8 *) &(u8_str[MAXTOKENLEN]);
				cnvt_res = ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_start_ptr, u8_end_ptr, strictConversion, &u8str_len);
				u8_str[u8str_len] = '\0';
				*/

				// ��� ���� �뿪�� ��ȯ�� ���¹��� �������� ������ �������� ����
				//
#ifdef TRACE
				printf("IDX_CheckCrossDic(ENG)...\n");
#endif
				strcpy(CurrIndex[0].key, (char *) u8_str);
				strlower(CurrIndex[0].key);
				CurrIndex[0].wordNum = wordNum;
				CurrIndexCnt = 1;

				///////////////////////////////////////////////////////////////////////
				// �뿪�� ��ȯ...
				///////////////////////////////////////////////////////////////////////
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
				////////////////////////////////////////////////////////////////////////
#ifdef TRACE
				printf("IDX_CheckCrossDic(ENG)...END\n");
#endif

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
