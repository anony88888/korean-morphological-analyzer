/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_SusaCheck.c)#  SPASIS System,     2000.04.20
 *
 *	#(Action)#
 *		- ���� ó�� ���...
 *        ���� ���� �˻�, ���� ó��, ���� �±�....
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MA_Token.h>
#include <MA_Func.h>
#include <MA_GMacro.h>
#include <MA_Global.h>
#include <MADIC_Type.h>
#include <MADIC_Func.h>
#include <MA_Susa.h>

/* 
 * ���� ���� �˻� ��� 
 * ����� ����Ǵ� ������ Detect... 
 * hword:������ �ѱ�, hword_len:������ �ѱ� ����, word:�ϼ��� �ѱ� 
 * "����ġ�� + �� + ����"���� "��" ���Ͽ� �ش��ϴ� ���ڰ� �����ϸ�
 * ������ ���� 
 * - ���ڷ� ������ ������...
 *   ��ū �и��⿡�� ���ڷ� ���۵Ǵ� ������ �и��Ǿ� ���´�...
 */
DWORD CheckSusaWord(HANGUL *hword, DWORD hword_len, UBYTE *word, tMORP_RESULT *sMorpResult, UWORD *sMorpResult_Index)
{
	DWORD dic_ret[512];
	DWORD dic_ret_idx;
	DWORD ret_val;

	*sMorpResult_Index = 0;

	if (word[0] == '\0')
		return 0;

	/* ������ ���ڷ� �����ϸ� TRUE */
	if (isdigit(word[0])) {
		ret_val = CheckSusa(word, hword, hword_len, BEGIN_WITH_NUM, NULL, 0, sMorpResult, sMorpResult_Index);
		return ret_val;
	}

	/* ���̰� 1 �����̸� FALSE */
	if (strlen((char*)word) <= 1)
		return 0;

	/* ���� ����� �����ϸ� OK */
	ret_val = SusaSearch(word, dic_ret, &dic_ret_idx);
	if ( ret_val == 1) {
		ret_val = CheckSusa(word, hword, hword_len, BEGIN_WITH_SUSA, dic_ret, dic_ret_idx, sMorpResult, sMorpResult_Index);
		return ret_val;
	} else if (ret_val == 2) {
		ret_val = CheckSusa(word, hword, hword_len, BEGIN_WITH_SGWAN, dic_ret, dic_ret_idx, sMorpResult, sMorpResult_Index);
		return ret_val;
	}

	return 0;
}

/*
 * ���� ���� Ž�� ��ƾ 
 * ���� ���� SusaWord������ �ε�����...
 */
DWORD SusaSearch(UBYTE *word, DWORD *dic_ret, DWORD *dic_ret_idx)
{
	H_CHAR fChar;
	DWORD i, index, num;

	/* �ѱ��� �ƴ� ���ڷ� �����ϴ� �ܾ�� ������ ����... */
	if ((word[0] & 0x80) == 0)
		return 0;
	
	*dic_ret_idx = 0;

	fChar.hl.high = word[0];
	fChar.hl.low = word[1];

	/* ������ �� �ȵǹǷ� Linear Ž������ ��... */
	/* ����� Ž�� */
	for (i = 0; i < SUSA_INDEX_NUM; i++)
		if (fChar.code == SusaWordsIndex[i].fChar.code) 
			break;

	if (i == SUSA_INDEX_NUM) {
		if (!strncmp((char*)word, "��", 2)) {
			dic_ret[*dic_ret_idx] = 90;
			*dic_ret_idx = 1;

			return 2;
		}

		if (!strncmp((char*)word, "����", 4)) {
			dic_ret[*dic_ret_idx] = 91;
			*dic_ret_idx = 1;

			return 2;
		}

		return 0;
	}

	/* ù��° ���ڷ� �����ϴ� ������ ��ġ�� ������ ���� */
	index = SusaWordsIndex[i].idx;
	num = SusaWordsIndex[i].num;

	/* ���縦 Ž�� */
	for (i = index; i < index + num; i++) {
		if (!strncmp((char*)word, (char*)SusaWords[i].Str, SusaWords[i].len * 2)) {
			dic_ret[*dic_ret_idx] = i;
			(*dic_ret_idx)++;
		}
	}

	if (*dic_ret_idx == 0) {
		/* �������� ó�� : ��, ��, ���� */
/*
		if (!strncmp(word, "��", 2)) {
			dic_ret[*dic_ret_idx] = 89;
			*dic_ret_idx = 1;

			return 2;
		}
*/

		if (!strncmp((char*)word, "��", 2)) {
			dic_ret[*dic_ret_idx] = 90;
			*dic_ret_idx = 1;

			return 2;
		}

		if (!strncmp((char*)word, "����", 4)) {
			dic_ret[*dic_ret_idx] = 91;
			*dic_ret_idx = 1;

			return 2;
		}

		return 0;
	} else
		return 1;
}

/*
 * ���� ������ ���� ������� �˻� ��ƾ...
 * ���� ���� ��ġ ��� ����...
 * �̰� ������� ��ġ����� �ƴϴ�...
 * �����Ѵ�...���� ������ �־��� ����̴�.
 */
DWORD SusaUnitSearch(HANGUL *hword, DWORD hword_len, UWORD *idx)
{
    DWORD i, j;

    for (i = SUSA_UNIT_NOUN_NUM-1; i >= 0; i--) {
	for (j = hword_len; j >= 1; j--) {
	    if (DanWiNoun[i].len == j && !strncmp((char*)DanWiNoun[i].jStr, (char*)hword, sizeof(HANGUL) * j))
		break;
	}
	if (j > 0)
	break;
    }

    if (i >= 0) {
	*idx = DanWiNoun[i].idx;
	return DanWiNoun[i].len;
    }

    return 0;
}

/*
 * �������� ���� �˻� ���...
 * ��忡 ���� ���ڷ� ���۵Ǵ� ����, ����� ���۵Ǵ� ������ ����
 * word			: �ѱ� ��Ʈ��(�ϼ���)
 * hword		: ������ ���� �ѱ� ���� 
 * hword_len	: ������ �ѱ��� ����
 * mode			: BEGIN_WITH_NUM/BEGIN_WITH_SUSA
 * dres			: ����� ���۵Ǿ��� ���->���� Ž�� ���...
 * dres_idx		: ���� Ž�� ����� ��...
 */
DWORD CheckSusa(UBYTE *word, HANGUL *hword, DWORD hword_len, 
		DWORD mode, DWORD *dres, DWORD dres_idx, tMORP_RESULT *sMorpResult, UWORD *sMorpResult_Index)
{
	UBYTE *pSusaWord;
	tSTATSUSA SusaMorps[VS_BUFLEN];/* ���� ���¼� ���� */
	DWORD SM_index = 0;
	DWORD str_idx, SW_index;
	DWORD hword_index = 0;	/* ���� �м��� ����ʿ� ����
								�޶����� hword�� ���� ��ġ */
	DWORD sDicRes[VS_BUFLEN];
	DWORD sDicRes_idx;
	/* ���� ���� Ž�� ��� */
	DWORD ret_val;
	DWORD unit_len;
	DWORD p_jong;
	DWORD yeo_flag, MI_idx;
	UWORD eujon_idx;
	HANGUL tmpHan;

	pSusaWord = word;
	*sMorpResult_Index = 0;

	if (mode == BEGIN_WITH_NUM) {
		/* ���ڸ� ���� ���¼� ���ۿ� ���� */
		str_idx = 0;
		while (*pSusaWord != '\0' && isdigit(*pSusaWord)) {
			SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
			str_idx++;
			pSusaWord++;

			hword_index++;
		}
		SusaMorps[SM_index].Str[str_idx] = '\0';
		SusaMorps[SM_index].mode = NUMBER;
	} else if (mode == BEGIN_WITH_SUSA) {
		/* ���縦 ���� ���¼� ���ۿ� �����ϰ� ������ ǥ�� */
		SW_index = dres[dres_idx-1];
		for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
			SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
			pSusaWord++;
		}

		hword_index += SusaWords[SW_index].len;

		SusaMorps[SM_index].Str[str_idx] = '\0';
		SusaMorps[SM_index].mode = SusaWords[SW_index].info;
	} else if (mode == BEGIN_WITH_SGWAN) {
		/* �������� �ڿ��� ��,��,õ,��,�� ������縸�� �´ٰ� ���� */
		SW_index = dres[dres_idx-1];
		for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
			SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
			pSusaWord++;
		}

		hword_index += SusaWords[SW_index].len;

		SusaMorps[SM_index].Str[str_idx] = '\0';
		SusaMorps[SM_index].mode = SusaWords[SW_index].info;

		/* ��������θ� ������ ������ ���¼Һм� �ܰ迡�� ó�� */
		if (*pSusaWord == '\0')
			return 0;

		/* '����' �������� ������ ������縸 �´� */
		if (strncmp((char*)word, "����", 4)) {
			/* ��, ��, õ, ��, ��, �˻� */
			while (1) {
				if (*pSusaWord == '\0')
					break;

				ret_val = SusaSearch(pSusaWord, sDicRes, &sDicRes_idx);
				if (!ret_val || SusaWords[sDicRes[sDicRes_idx-1]].info != SUSA_INFO_7) {
					if (!strncmp((char*)pSusaWord, "��", 2)) {
						sDicRes[0] = 63;
						sDicRes_idx = 1;
					} else
						break;
				}

				SW_index = sDicRes[sDicRes_idx-1];

				/* ���縦 ���� ���¼� ���ۿ� �����ϰ� ������ ǥ�� */
				for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
					SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
					pSusaWord++;
				}

				hword_index += SusaWords[SW_index].len;

				SusaMorps[SM_index].Str[str_idx] = '\0';
				SusaMorps[SM_index].mode = SusaWords[SW_index].info;
				SM_index++;
			}
		}

		/* ������� �м� */
		/* 
		 * ����� ���¼Һм� ������ ������� ó���� ���� �ʰ�..
		 * �ܺο��� ó���� �ϰ� ��...
		 */
		unit_len = SusaUnitSearch(&hword[hword_index], (UWORD) (hword_len - hword_index), &eujon_idx);
		if (unit_len > 0) {
		    if ((hword_len - hword_index) == unit_len) {
			memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
			sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
			strcpy(sMorpResult[0].MI[0].info, "SUSA");
			sMorpResult[0].MI[0].ninfo = 1;

			if (eujon_idx == 0) {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
			    sMorpResult[0].MI[1].Morpheme[unit_len] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    sMorpResult[0].nMorp = 2;
			} else {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
			    sMorpResult[0].MI[1].Morpheme[eujon_idx] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    memcpy(sMorpResult[0].MI[2].Morpheme, (UWORD *) &hword[hword_index + eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
			    sMorpResult[0].MI[2].Morpheme[unit_len - eujon_idx] = 0;
			    sMorpResult[0].MI[2].info[0] = 30;
			    sMorpResult[0].MI[2].info[1] = 0;
			    sMorpResult[0].MI[2].ninfo = 1;

			    sMorpResult[0].nMorp = 3;
			}

			(*sMorpResult_Index)++;

			/*
			 * �Ⱑ, �⵵, ����, ���� --> �� ���������� "������� + ����"�ε� �м��� ������...
			 * �Ϲ� ���� �м��� ���� �ʰ� �̰����� ���¼Ҹ� �и��Ͽ� ����� ���...
			 */
			if (unit_len == 2) {
			    if (hword[hword_index].j_code == 0x8ba1 && hword[hword_index+1].j_code == 0x8861) {
				/* �Ⱑ */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "J1");
				sMorpResult[1].MI[2].ninfo = 1;

				sMorpResult[1].nMorp = 3;

				(*sMorpResult_Index)++;
			    } else if (hword[hword_index].j_code == 0x9165 && hword[hword_index+1].j_code == 0x95a1) {
				/* �⵵ */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "J6");
				sMorpResult[1].MI[2].ninfo = 1;

				sMorpResult[1].nMorp = 3;

				(*sMorpResult_Index)++;
			    } else if (hword[hword_index].j_code == 0x95b7 && hword[hword_index+1].j_code == 0xb7a1) {
				/* ���� */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "J1");
				sMorpResult[1].MI[2].ninfo = 1;

				sMorpResult[1].nMorp = 3;

				(*sMorpResult_Index)++;
			    } else if (hword[hword_index].j_code == 0xba81 && hword[hword_index+1].j_code == 0xb7a9) {
				/* ���� */
				memcpy(sMorpResult[1].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
				sMorpResult[1].MI[0].Morpheme[hword_index] = 0;
				strcpy(sMorpResult[1].MI[0].info, "SUSA");
				sMorpResult[1].MI[0].ninfo = 1;

				memcpy(sMorpResult[1].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
				sMorpResult[1].MI[1].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[1].info, "UNIT");
				sMorpResult[1].MI[1].ninfo = 1;

				tmpHan.j_code = hword[hword_index+1].j_code; /* �� */
				tmpHan.j_han.jong = 0x01;

				memcpy(sMorpResult[1].MI[2].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
				sMorpResult[1].MI[2].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[2].info, "IDA");
				sMorpResult[1].MI[2].ninfo = 1;

				tmpHan.j_han.sign = 1;
				tmpHan.j_han.cho = 0x01;
				tmpHan.j_han.jung = 0x02;
				tmpHan.j_han.jong = 0x09;

				memcpy(sMorpResult[1].MI[3].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
				sMorpResult[1].MI[3].Morpheme[1] = 0;
				strcpy(sMorpResult[1].MI[3].info, "E5");
				sMorpResult[1].MI[3].ninfo = 1;

				sMorpResult[1].nMorp = 4;

				(*sMorpResult_Index)++;
			    }
			}

			return 1;
		    } else { 
			memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
			sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
			strcpy(sMorpResult[0].MI[0].info, "SUSA");
			sMorpResult[0].MI[0].ninfo = 1;

			if (eujon_idx == 0) {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
			    sMorpResult[0].MI[1].Morpheme[unit_len] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    sMorpResult[0].nMorp = 2;
			} else {
			    memcpy(sMorpResult[0].MI[1].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
			    sMorpResult[0].MI[1].Morpheme[eujon_idx] = 0;
			    strcpy(sMorpResult[0].MI[1].info, "UNIT");
			    sMorpResult[0].MI[1].ninfo = 1;

			    memcpy(sMorpResult[0].MI[2].Morpheme, (UWORD *) &hword[hword_index + eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
			    sMorpResult[0].MI[2].Morpheme[unit_len-eujon_idx] = 0;
			    sMorpResult[0].MI[2].info[0] = 30;
			    sMorpResult[0].MI[2].info[1] = 0;
			    sMorpResult[0].MI[2].ninfo = 1;

			    sMorpResult[0].nMorp = 3;
			}

			hword_index += unit_len;
			p_jong = hword[hword_index-1].j_han.jong;
			ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
			if (ret_val) {
			    (*sMorpResult_Index)++;
			    return 1;
			}
		    }
		}

		/*
		ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_UNIT);
		if (ret_val) {
			memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
			sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
			strcpy(sMorpResult[0].MI[0].info, "SUSA");
			sMorpResult[0].MI[0].ninfo = 1;
			sMorpResult[0].nMorp = 1;
			(*sMorpResult_Index)++;

			return 1;
		}
		*/

		return 0;
	}

	SM_index++;

	/* ������ ���� ó�� ��� */
	while (1) {
		if (*pSusaWord == '\0')
			break;
		if (isdigit(*pSusaWord)) {
			str_idx = 0;
			while (*pSusaWord != '\0' && isdigit(*pSusaWord)) {
				SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
				str_idx++;
				pSusaWord++;

				hword_index++;
			}
			SusaMorps[SM_index].Str[str_idx] = '\0';
			SusaMorps[SM_index].mode = NUMBER;
			SM_index++;

			continue;
		}

		if (*pSusaWord & 0x80) {
			/* ������ �κ�(�������, ����, ���ո�� �м�) */
			if (SusaMorps[SM_index-1].mode == SUSA_INFO_3 ||
				SusaMorps[SM_index-1].mode == SUSA_INFO_5 ||
				SusaMorps[SM_index-1].mode == SUSA_INFO_6) {

				/* ���� �޸���ƽ�� ��Ģ *
				 * - ���� ������ ��縦 �м��� ��,
				     �� �������¼Ҹ� ������ ������ NORMAL ��忡�� �м� �����ϸ� ��� �м��� Skip�Ѵ�. 
				   - �ӵ��� ������ �� �� ����...
				   - �����Ѵ�(2000/11/18) �ֻ��� �˻�������....
				*/
				if (hword_index == 1) {
					ret_val = TopicMorpAnal(hword, (UWORD) hword_len, SUSA_SEARCH_DIC, 0);
					if (ret_val > hword_index)
						return 0;
				}

				/* ������� �м� */
				/* 
				 * ����� ���¼Һм� ������ ������� ó���� ���� �ʰ�..
				 * �ܺο��� ó���� �ϰ� ��...
				 */

				/*
				 * 10����...10����...�� "��"�� ���� ó��..
				 */
				yeo_flag = 0;
				MI_idx = 0;
				if (SusaMorps[SM_index-1].mode == SUSA_INFO_5 && hword[hword_index].j_code == 0xb561) {
				    yeo_flag = 1;
				    hword_index++;
				}

				unit_len = SusaUnitSearch(&hword[hword_index], (UWORD) (hword_len - hword_index), &eujon_idx);
				if (unit_len > 0) {
				    if ((hword_len - hword_index) == unit_len) {
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[(hword_index-1)] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					(*sMorpResult_Index)++;

					/*
					 * �Ⱑ, �⵵, ����, ���� --> �� ���������� "������� + ����"�ε� �м��� ������...
					 * �Ϲ� ���� �м��� ���� �ʰ� �̰����� ���¼Ҹ� �и��Ͽ� ����� ���...
					 */
					if (unit_len == 2) {
					    if (hword[hword_index].j_code == 0x8ba1 && hword[hword_index+1].j_code == 0x8861) {
						/* �Ⱑ */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x9165 && hword[hword_index+1].j_code == 0x95a1) {
						/* �⵵ */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J6");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x95b7 && hword[hword_index+1].j_code == 0xb7a1) {
						/* ���� */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0xba81 && hword[hword_index+1].j_code == 0xb7a9) {
						/* ���� */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_code = hword[hword_index+1].j_code; /* �� */
						tmpHan.j_han.jong = 0x01;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "IDA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_han.sign = 1;
						tmpHan.j_han.cho = 0x01;
						tmpHan.j_han.jung = 0x02;
						tmpHan.j_han.jong = 0x09;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "E5");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    }
					}
					return 1;
				    } else { 
					MI_idx = 0;
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index-1] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					hword_index += unit_len;
					p_jong = hword[hword_index-1].j_han.jong;
					ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
					if (ret_val) {
					    (*sMorpResult_Index)++;
					    return 1;
					}

					hword_index -= unit_len;
				    }
				}

				if (yeo_flag)
				    hword_index--;

				/*
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_UNIT);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}
				*/

				p_jong = hword[hword_index-1].j_han.jong;
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_NOUN, 0);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				return 0;
			}

			if (SusaMorps[SM_index-1].mode == SUSA_INFO_4) {
				p_jong = hword[hword_index-1].j_han.jong;
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				} else
					return 0;
			}

			/* ���� ���� Ž�� */
			ret_val = SusaSearch(pSusaWord, sDicRes, &sDicRes_idx);
			if (ret_val) {
				SW_index = sDicRes[sDicRes_idx-1];
/**********************************************************/
				/* ���� ���� ���� ���� */
				switch (SusaWords[SW_index].info) {
				case SUSA_INFO_1 :
					/* ������ ���� �տ��� �ѱ� ���簡 ���� �ʴ� ���̴�. */
					if (SusaMorps[SM_index-1].mode == SUSA_INFO_2)
						goto CHECK_REMAIN;
					/* ������ ���� �տ��� ���ڰ� ���� �ʴ´�. */
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;

					break;

				case SUSA_INFO_2 :
					/* �ѱ� ���� �տ��� ���� ���簡 ���� �ʴ� ���̴� */
					if (SusaMorps[SM_index-1].mode == SUSA_INFO_1)
						goto CHECK_REMAIN;

					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;

					break;

				case SUSA_INFO_3 :
					if (SusaMorps[SM_index-1].mode == NUMBER 
						|| SusaMorps[SM_index-1].mode == SUSA_INFO_7)
						goto CHECK_REMAIN;
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_4 :
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_5 :
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_6 :
					if (SusaMorps[SM_index-1].mode == NUMBER)
					    goto CHECK_REMAIN;
					break;

				case SUSA_INFO_7 :
					break;

				default :
					break;
				}
/**********************************************************/

				/* ���縦 ���� ���¼� ���ۿ� �����ϰ� ������ ǥ�� */
				for (str_idx = 0; str_idx < SusaWords[SW_index].len * 2; str_idx++) {
					SusaMorps[SM_index].Str[str_idx] = *pSusaWord;
					pSusaWord++;
				}

				hword_index += SusaWords[SW_index].len;

				SusaMorps[SM_index].Str[str_idx] = '\0';
				SusaMorps[SM_index].mode = SusaWords[SW_index].info;
				SM_index++;

				continue;
			} else {
				/* ����¥�� ���� ������ ������縦 �м��� ��...
				   �� �ܾ �Ϲ� ���¼Һм� ��忡�� ����������.. SKIP..
				   ��ȸ�� --> ��(����)+ȸ(�������)+��(����)
				   �����Ѵ�(2000/11/18) -- ���� Ž������...
				*/
				if (SusaMorps[SM_index-1].mode != NUMBER && hword_index == 1) {
					/* '��'�� �����ϴ� ����� Fail */
					if (hword[0].j_code == 0xB7A1) /* �� */
						return 0;
					ret_val = TopicMorpAnal(hword, (UWORD) hword_len, SUSA_SEARCH_DIC, 0);
					if (ret_val > hword_index)
						return 0;
				}
CHECK_REMAIN:
				/* ������� �м� */
				/* 
				 * ����� ���¼Һм� ������ ������� ó���� ���� �ʰ�..
				 * �ܺο��� ó���� �ϰ� ��...
				 */
				/*
				 * 10����...10����...�� "��"�� ���� ó��..
				 */
				yeo_flag = 0;
				MI_idx = 0;
				if ((SusaMorps[SM_index-1].mode == SUSA_INFO_7 || SusaMorps[SM_index-1].mode == NUMBER) 
					&& hword[hword_index].j_code == 0xb561) {
				    yeo_flag = 1;
				    hword_index++;
				}

				unit_len = SusaUnitSearch(&hword[hword_index], (UWORD) (hword_len - hword_index), &eujon_idx);
				if (unit_len > 0) {
				    if ((hword_len - hword_index) == unit_len) {
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[(hword_index-1)] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					(*sMorpResult_Index)++;

					/*
					 * �Ⱑ, �⵵, ����, ���� --> �� ���������� "������� + ����"�ε� �м��� ������...
					 * �Ϲ� ���� �м��� ���� �ʰ� �̰����� ���¼Ҹ� �и��Ͽ� ����� ���...
					 */
					if (unit_len == 2) {
					    if (hword[hword_index].j_code == 0x8ba1 && hword[hword_index+1].j_code == 0x8861) {
						/* �Ⱑ */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x9165 && hword[hword_index+1].j_code == 0x95a1) {
						/* �⵵ */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J6");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0x95b7 && hword[hword_index+1].j_code == 0xb7a1) {
						/* ���� */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+1], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "J1");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    } else if (hword[hword_index].j_code == 0xba81 && hword[hword_index+1].j_code == 0xb7a9) {
						/* ���� */
						MI_idx = 0;
						if (yeo_flag) {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index-1] = 0;
						} else {
						    memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
						    sMorpResult[1].MI[MI_idx].Morpheme[hword_index] = 0;
						}
						strcpy(sMorpResult[1].MI[MI_idx].info, "SUSA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						if (yeo_flag) {
						    sMorpResult[1].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
						    sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						    strcpy(sMorpResult[1].MI[MI_idx].info, "PRE_UNIT");
						    sMorpResult[1].MI[MI_idx].ninfo = 1;
						    MI_idx++;
						}

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "UNIT");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_code = hword[hword_index+1].j_code; /* �� */
						tmpHan.j_han.jong = 0x01;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "IDA");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						tmpHan.j_han.sign = 1;
						tmpHan.j_han.cho = 0x01;
						tmpHan.j_han.jung = 0x02;
						tmpHan.j_han.jong = 0x09;

						memcpy(sMorpResult[1].MI[MI_idx].Morpheme, (UWORD *) &tmpHan, sizeof(UWORD) * 1);
						sMorpResult[1].MI[MI_idx].Morpheme[1] = 0;
						strcpy(sMorpResult[1].MI[MI_idx].info, "E5");
						sMorpResult[1].MI[MI_idx].ninfo = 1;

						MI_idx++;

						sMorpResult[1].nMorp = MI_idx;

						(*sMorpResult_Index)++;
					    }
					}
					return 1;
				    } else { 
					MI_idx = 0;
					if (yeo_flag) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * (hword_index-1));
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index-1] = 0;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					    sMorpResult[0].MI[MI_idx].Morpheme[hword_index] = 0;
					}
					strcpy(sMorpResult[0].MI[MI_idx].info, "SUSA");
					sMorpResult[0].MI[MI_idx].ninfo = 1;

					MI_idx++;

					if (yeo_flag) {
					    sMorpResult[0].MI[MI_idx].Morpheme[0] = 0xb561; /* �� */
					    sMorpResult[0].MI[MI_idx].Morpheme[1] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "PRE_UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;
					    MI_idx++;
					}

					if (eujon_idx == 0) {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * unit_len);
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					} else {
					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index], sizeof(UWORD) * eujon_idx);
					    sMorpResult[0].MI[MI_idx].Morpheme[eujon_idx] = 0;
					    strcpy(sMorpResult[0].MI[MI_idx].info, "UNIT");
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    memcpy(sMorpResult[0].MI[MI_idx].Morpheme, (UWORD *) &hword[hword_index+eujon_idx], sizeof(UWORD) * (unit_len-eujon_idx));
					    sMorpResult[0].MI[MI_idx].Morpheme[unit_len-eujon_idx] = 0;
					    sMorpResult[0].MI[MI_idx].info[0] = 30;
					    sMorpResult[0].MI[MI_idx].info[1] = 0;
					    sMorpResult[0].MI[MI_idx].ninfo = 1;

					    MI_idx++;

					    sMorpResult[0].nMorp = MI_idx;
					}

					hword_index += unit_len;
					p_jong = hword[hword_index-1].j_han.jong;
					ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
					if (ret_val) {
					    (*sMorpResult_Index)++;
					    return 1;
					}

					hword_index -= unit_len;
				    }
				}

				if (yeo_flag)
				    hword_index--;

				/*
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_UNIT);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}
				*/

				p_jong = hword[hword_index-1].j_han.jong;
				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_POSTNOUN, p_jong);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				ret_val = TopicMorpAnal(&hword[hword_index], (UWORD) (hword_len - hword_index), SUSA_NOUN, 0);
				if (ret_val) {
					memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_index);
					sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
					strcpy(sMorpResult[0].MI[0].info, "SUSA");
					sMorpResult[0].MI[0].ninfo = 1;
					sMorpResult[0].nMorp = 1;
					(*sMorpResult_Index)++;

					return 1;
				}

				return 0;
			}
		}

		pSusaWord++;
	}

	/* ������� ������... ����θ� ������ �����̴�... */

	/* '��'�� �ܵ����� ���Ǹ� ������ ������� �����Ѵ�. */
	if (hword_len == 1 && hword[0].j_code == 0xB7A1) /* �� */
		return 0;

	memcpy(sMorpResult[0].MI[0].Morpheme, (UWORD *) hword, sizeof(UWORD) * hword_len);
	sMorpResult[0].MI[0].Morpheme[hword_index] = 0;
	strcpy(sMorpResult[0].MI[0].info, "SUSA");
	sMorpResult[0].MI[0].ninfo = 1;
	sMorpResult[0].nMorp = 1;
	(*sMorpResult_Index)++;

	return 1;
}
