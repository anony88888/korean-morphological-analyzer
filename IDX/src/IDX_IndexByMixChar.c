#include <IDX_common.h>
#include <IDX_user.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>
#include "hj2hg.h"

int MixedHanjaProc(int code_value, int wordNum, POSTINFO* PostInfo, int hj_opt, int hjvar_opt, int CurrPICnt);
/*
 * 2003-05-28, ���� ���� �߰�
 * ��� ���� ������ �ϵ�...
 * ���ڿ� ���ؼ��� ������ �ѱ� ������ ��ȯ�Ͽ� ���ڿ� �Բ� PostInfo�� �߰�(WordNum ����...)
 * �̶� ������Ģ�� ����...
 * (��) ��(����) --> ��(����), ��(�ѱ�), ��(�ѱ�) --> �Բ� ����
 *
 * 2004-02-09, ��ü�� ���� �߰�
 */
int IDX_IndexByMixChar(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int ret_tok, PostInfoCnt = 0, tempPostInfoCnt;
	UTF32 token[MAXTOKENLEN], *u32_ptr;
	UTF8  u8_tok[MAXTOKENLEN], *u8_ptr;
	int u8_len;
	int token_len;
	int wordNum, i;
	int code_value;

	extern int StemCheck;
	extern int StartWordNum;
	extern int IDX_HANJA_PROC_OPTION;
	extern int HanjaFlag;
	extern int HighLight;

	wordNum = StartWordNum;

	InitTokenizer(SecVal);

	if (HighLight) {
		wordNum = 0;
		while ((ret_tok = GetNextTokenChar(token)) != -1) {
			IDX_UTF32toUTF8(token, 1, u8_tok);

			strcpy(PostInfo[PostInfoCnt].key, u8_tok);
			PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
			PostInfo[PostInfoCnt].wordNum = wordNum++;
			PostInfo[PostInfoCnt].psgNum = 0;
			PostInfo[PostInfoCnt].c_type = ret_tok;
			if ( PostInfo[PostInfoCnt].keyLen > MAXKEYLEN )
				PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
			PostInfoCnt++;
			if (PostInfoCnt > MAXPOSTINFOSIZE-1)
				return PostInfoCnt;

			// 2005-12-12
			// T_PRI ������ Ȯ�����ڿ� ���ؼ��� ó��
			if (ret_tok == T_CJK || ret_tok == T_PRI) 
				PostInfoCnt += MixedHanjaProc(token[0], wordNum, &PostInfo[PostInfoCnt], HanjaFlag, IDX_HANJA_PROC_OPTION, PostInfoCnt);
		}

		return PostInfoCnt;
	}

	while ((ret_tok = GetNextToken(token, &token_len, 2)) != -1) {
		switch (ret_tok) {
			case T_DEL:
				wordNum++;
				break;

			case T_LAT:
				if (PostInfoCnt >= MAXPOSTINFOSIZE)
					return MAXPOSTINFOSIZE;
				u32_ptr = token;
				u8_ptr = u8_tok;
				ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_ptr, &(u8_tok[MAXTOKENLEN]), strictConversion, &u8_len);
				u8_tok[u8_len] = '\0';

				if (strlen(u8_tok) > MAXKEYLEN)
					break;

				strcpy(PostInfo[PostInfoCnt].key, u8_tok);
				strlower(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
				PostInfo[PostInfoCnt].wordNum = wordNum++;
				PostInfo[PostInfoCnt].psgNum = 0;
				if ( PostInfo[PostInfoCnt].keyLen > MAXKEYLEN )
					PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
				PostInfoCnt++;

				break;

			case T_HAN:
			case T_CJK:
			case T_DIG:
			case T_JPN:
			case T_PRI:
			case T_SJW:
			case T_CYR:
				if (PostInfoCnt >= MAXPOSTINFOSIZE)
					return MAXPOSTINFOSIZE;
				/*
				u32_ptr = token;
				u8_ptr = u8_tok;
				ConvertUTF32toUTF8(&u32_ptr, &(token[token_len]), &u8_ptr, &(u8_tok[1023]), strictConversion, &u8_len);
				u8_tok[u8_len] = '\0';

				********** 2003-05-28 -- �� ���� ���������� �̷� ���� ��ū �߽� �ҿ�� ���Ű� �ʿ���� �� ����.
				if (IDX_FindStopWord(u8_tok))
					break;
				*/

				for (i = 0; i < token_len; i++) {
					u32_ptr = &(token[i]);
					u8_ptr = u8_tok;
					ConvertUTF32toUTF8(&u32_ptr, &(token[i+1]), &u8_ptr, &(u8_tok[MAXTOKENLEN]), strictConversion, &u8_len);
					u8_tok[u8_len] = '\0';

					strcpy(PostInfo[PostInfoCnt].key, u8_tok);
					PostInfo[PostInfoCnt].keyLen = strlen(u8_tok);
					PostInfo[PostInfoCnt].wordNum = wordNum++;
					PostInfo[PostInfoCnt].psgNum = 0;
					if ( PostInfo[PostInfoCnt].keyLen > MAXKEYLEN )
						PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
					PostInfoCnt++;

					if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
						return PostInfoCnt;

					// 2003-05-28
					// ������ ��쿡 ������ �ѱ۷� ��ȯ
					// 2004-10-28
					// ������ ��쿡 ���� �ɼǿ� ���� �ѱ۷� ��ȯ
					// 2005-12-12
					// T_PRI ������ Ȯ�����ڿ� ���ؼ��� ó��
					if (ret_tok == T_CJK || ret_tok == T_PRI) 
						PostInfoCnt += MixedHanjaProc(token[i], wordNum, &PostInfo[PostInfoCnt], HanjaFlag, IDX_HANJA_PROC_OPTION, PostInfoCnt);
				}
				break;

			default :
				break;
		}
	}

	return PostInfoCnt;
}

int MixedHanjaProc(int code_value, int wordNum, POSTINFO* PostInfo, int hj_opt, int hjvar_opt, int CurrPICnt)
{
	unsigned char TempVal[512], *ptr;
	char hg_buf[1024];
	int PostInfoCnt = 0;

	if (hj_opt && GetHangulChars(code_value, hg_buf)) {
		strcpy(TempVal, hg_buf);
		ptr = strtok(TempVal, " ");
		while (ptr != NULL) {
			strcpy(PostInfo[PostInfoCnt].key, ptr);
			PostInfo[PostInfoCnt].keyLen = strlen(ptr);
			PostInfo[PostInfoCnt].wordNum = wordNum - 1; 
			PostInfo[PostInfoCnt].psgNum = 1000; /* �ѱۺ�ȯ���ڿ� ���ؼ��� ���� ǥ�� */
			PostInfoCnt++;

			if (PostInfoCnt + CurrPICnt > MAXPOSTINFOSIZE)
				return PostInfoCnt;

			// ���� ���ڰ� ������Ģ�� ����Ǵ��� �˻�
			if (DuemConv(ptr, TempVal)) {
				strcpy(PostInfo[PostInfoCnt].key, TempVal);
				PostInfo[PostInfoCnt].keyLen = strlen(TempVal);
				PostInfo[PostInfoCnt].wordNum = wordNum - 1; 
				PostInfo[PostInfoCnt].psgNum = 1000; /* �ѱۺ�ȯ���ڿ� ���ؼ��� ���� ǥ�� */
				PostInfoCnt++;
				if (PostInfoCnt + CurrPICnt > MAXPOSTINFOSIZE)
					return PostInfoCnt;
			}

			ptr = strtok(NULL, " ");
		}
	}

	/* ��ü�� ���ξ� �߰� */
	if (hjvar_opt >= 10) {
		PostInfoCnt += AppendHanjaVariableToPostInfo(code_value, &PostInfo[PostInfoCnt], wordNum-1, hjvar_opt, PostInfoCnt);
	}

	return PostInfoCnt;
}


#if 0
int IDX_IndexByChar(char *SecVal, POSTINFO *PostInfo, int StopCheck)
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
		CharType = IDX_TokenIndexByChar(&SecPtr, TokBuf);
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
					/*
					if (StopCheck && IDX_FindStopWord(PostInfo[PostInfoCnt].key)) {;}
					*/
					if (0 && IDX_FindStopWord(PostInfo[PostInfoCnt].key)) {;}    /* do nothing */
					else {
						PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
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
				break;
			case  T_U2:
				++wordNum;
				break;
			default:
				break;
		}
	}

	return PostInfoCnt;
}
#endif
