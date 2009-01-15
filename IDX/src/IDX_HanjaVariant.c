/*
 * 한자 이체자 변환...
 */
#include <IDX_common.h>
#include <IDX_user.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>
#include <HanjaVariantDef.h>
#include <IDX_Hanja2Hangul.h>

static HVARIANT HVariant_Tbl[MAX_ITEM_NUM];
static unsigned int VT_num = 0;

int LoadHanjaVariantTable(char *in_file)
{
	char line[8192];
	char *ptr;
	char temp[1024];
	FILE *fd_in;
	int cur_flag; // 1 --> S, 2 --> V, 3 --> T
	int T_idx, V_idx, S_idx;
	int i;
	UTF32 u32_str[100], *u32_ptr;
	UTF8 u8_str[100], *u8_ptr;
	int u8_str_len;

	fd_in = fopen(in_file, "rt");
	if (fd_in == NULL)
		return 0;

	while (fgets(line, 8192, fd_in)) {
		
		ptr = strtok(line, "\n\t ");
		if (ptr == NULL)
			break;

		strcpy(temp, ptr+2);
		HVariant_Tbl[VT_num].h_code = strtol(temp, NULL, 16);

		T_idx = V_idx = S_idx = 0;
		ptr = strtok(NULL, "\n\t ");
		while (ptr != NULL) {
			if (!strcmp(ptr, "$S")) {
				cur_flag = 1;
			} else if (!strcmp(ptr, "$V")) {
				cur_flag = 2;
			} else if (!strcmp(ptr, "$T")) {
				cur_flag = 3;
			} else {
				strcpy(temp, ptr+2);

				switch (cur_flag) {
					case 1:
						HVariant_Tbl[VT_num].S_val[S_idx] = strtol(temp, NULL, 16);
						S_idx++;
						break;
					case 2:
						HVariant_Tbl[VT_num].V_val[V_idx] = strtol(temp, NULL, 16);
						V_idx++;
						break;
					case 3:
						HVariant_Tbl[VT_num].T_val[T_idx] = strtol(temp, NULL, 16);
						T_idx++;
						break;
				}
			}

			ptr = strtok(NULL, "\n\t ");
		}

		HVariant_Tbl[VT_num].S_val[S_idx] = CARD_V;
		HVariant_Tbl[VT_num].V_val[V_idx] = CARD_V;
		HVariant_Tbl[VT_num].T_val[T_idx] = CARD_V;

		VT_num++;
	}

	fclose(fd_in);

	return 1;
}

int AppendHanjaVariableToPostInfo(unsigned int h_code, POSTINFO *PostInfo, int wordNum, int Option, int CurrPICnt)
{
	UTF32 *u32_ptr;
	UTF8  u8_tok[128], *u8_ptr;
	int u8_len;
	HVARIANT *hv, *hv2;
	int i, PostInfoCnt = 0;
	int temp, opt;
	int S_opt = 0, V_opt = 0, T_opt = 0;
	unsigned int h_code_T;

	ConvToCJK(&h_code);

	temp = Option / 10;

	S_opt = temp % 10;
	V_opt = (temp % 100)/10;
	T_opt = (temp % 1000)/100;

#if 0
	hv = GetHanjaVariantInfo(h_code);
	if (hv != NULL) {
		/* 정자가 아니면 일단 이 글자의 간체자 및 약자를 저장하고 정자를 이용하여 다시 검색 */
		if (hv->T_val[0] != CARD_V) {
			if (T_opt) { /* 정체자 색인 생성 */
				i = 0;
				while (hv->T_val[i] != CARD_V) {
					/* UTF32 --> UTF8 */
					u32_ptr = &(hv->T_val[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(hv->T_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum;
					PostInfo[PostInfoCnt].psgNum = 0;
					PostInfoCnt++;

					i++;
				}
			}

			if (S_opt) { /* 간체자 색인 생성 */
				i = 0;
				while (hv->S_val[i] != CARD_V) {
					/* UTF32 --> UTF8 */
					u32_ptr = &(hv->S_val[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(hv->S_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum;
					PostInfo[PostInfoCnt].psgNum = 0;
					PostInfoCnt++;

					i++;
				}
			}

			if (V_opt) { /* 약자 색인 생성 */
				i = 0;
				while (hv->V_val[i] != CARD_V) {
					/* UTF32 --> UTF8 */
					u32_ptr = &(hv->V_val[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(hv->V_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum;
					PostInfo[PostInfoCnt].psgNum = 0;
					PostInfoCnt++;

					i++;
				}
			}

			h_code_T = hv->T_val[0];
		} else { /* 정자이면 그대로 다시 변환 */
			h_code_T = h_code;
		}

		hv2 = GetHanjaVariantInfo(h_code_T);
		if (hv2 != NULL) {
			if (S_opt) { /* 간체자 색인 생성 */
				i = 0;
				while (hv2->S_val[i] != CARD_V) {
					if (hv2->S_val[i] == h_code) {
						i++;
						continue;
					}
					/* UTF32 --> UTF8 */
					u32_ptr = &(hv2->S_val[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(hv2->S_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum;
					PostInfo[PostInfoCnt].psgNum = 0;
					PostInfoCnt++;

					i++;
				}
			}

			if (V_opt) { /* 약자 색인 생성 */
				i = 0;
				while (hv2->V_val[i] != CARD_V) {
					if (hv2->V_val[i] == h_code) {
						i++;
						continue;
					}
					/* UTF32 --> UTF8 */
					u32_ptr = &(hv2->V_val[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(hv2->V_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum;
					PostInfo[PostInfoCnt].psgNum = 0;
					PostInfoCnt++;

					i++;
				}
			}
		}
	}

	return PostInfoCnt;
#endif

	hv = GetHanjaVariantInfo(h_code);
	if (hv != NULL) {
		temp = Option / 10;

		opt = temp % 10;
		if (opt) {
			i = 0;
			while (hv->S_val[i] != CARD_V) {
				/* UTF32 --> UTF8 */
				u32_ptr = &(hv->S_val[i]);
				u8_ptr = u8_tok;
				ConvertUTF32toUTF8(&u32_ptr, &(hv->S_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
				u8_tok[u8_len] = '\0';

				strcpy(PostInfo[PostInfoCnt].key, u8_tok);
				PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
				PostInfo[PostInfoCnt].wordNum = wordNum;
				PostInfo[PostInfoCnt].psgNum = 0;
				PostInfoCnt++;

				if (CurrPICnt + PostInfoCnt > MAXPOSTINFOSIZE)
					return PostInfoCnt;

				i++;
			}
		}

		opt = temp % 100;
		opt = opt / 10;
		if (opt) {
			i = 0;
			while (hv->V_val[i] != CARD_V) {
				/* UTF32 --> UTF8 */
				u32_ptr = &(hv->V_val[i]);
				u8_ptr = u8_tok;
				ConvertUTF32toUTF8(&u32_ptr, &(hv->V_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
				u8_tok[u8_len] = '\0';

				strcpy(PostInfo[PostInfoCnt].key, u8_tok);
				PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
				PostInfo[PostInfoCnt].wordNum = wordNum;
				PostInfo[PostInfoCnt].psgNum = 0;
				PostInfoCnt++;
				if (CurrPICnt + PostInfoCnt > MAXPOSTINFOSIZE)
					return PostInfoCnt;

				i++;
			}
		}

		opt = temp % 1000;
		opt = opt / 100;
		if (opt) {
			i = 0;
			while (hv->T_val[i] != CARD_V) {
				/* UTF32 --> UTF8 */
				u32_ptr = &(hv->T_val[i]);
				u8_ptr = u8_tok;
				ConvertUTF32toUTF8(&u32_ptr, &(hv->T_val[i+1]), &u8_ptr, &(u8_tok[127]), strictConversion, &u8_len);
				u8_tok[u8_len] = '\0';

				strcpy(PostInfo[PostInfoCnt].key, u8_tok);
				PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
				PostInfo[PostInfoCnt].wordNum = wordNum;
				PostInfo[PostInfoCnt].psgNum = 0;
				PostInfoCnt++;
				if (CurrPICnt + PostInfoCnt > MAXPOSTINFOSIZE)
					return PostInfoCnt;

				i++;
			}
		}
	}

	return PostInfoCnt;
}

/*
 * 이체자, 정자, 번체자, 약자 정보 제공
 */
HVARIANT *GetHanjaVariantInfo(unsigned int hcode)
{
	HVARIANT s, *r;

	s.h_code = hcode;

	r = (HVARIANT *) bsearch(&s, HVariant_Tbl, VT_num, sizeof(HVARIANT), compareHanjaCode);
	if (r != NULL) {
		return r;
	} else {
		return NULL;
	}
}

int compareHanjaCode(const void* hv1, const void* hv2)
{
	HVARIANT *p1, *p2;

	p1 = (HVARIANT *) hv1;
	p2 = (HVARIANT *) hv2;

	return (p1->h_code - p2->h_code);
}
