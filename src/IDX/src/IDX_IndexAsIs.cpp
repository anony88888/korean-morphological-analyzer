/**********************************************************************
 *         The KRISTAL-2001 System, Version 1.0beta
 *
 * Developed by Sung Pil Choi (042-828-5107)
 ***********************************************************************/
#include <IDX_common.h>
#include <IDX_user.h>

int RemoveDCode(char *data);
int isDCode(char c);
int RangeIndex(char *SecVal, POSTINFO *PostInfo);

// 특정 코드를 삭제
int RemoveDCode(char *data)
{
	extern char *dCode;
	int i, j;
	char temp[MAXTEMPBUFSIZE];
	int temp_idx;

	if (dCode == NULL)
		return 0;

	temp_idx = 0;
	for (i = 0; i < strlen(data); i++) {
		for (j = 0; j < strlen(dCode); j++) {
			if (data[i] == dCode[j])
				break;
		}

		if (j == strlen(dCode)) {
			temp[temp_idx] = data[i];
			temp_idx++;
		}
	}
	temp[temp_idx] = '\0';

	strcpy(data, temp);

	return 1;
}

int RangeIndex(char *SecVal, POSTINFO *PostInfo)
{
	extern INDEX_OFFSET *idx_offsets;
	extern int off_num;
	int i, PostInfoNum = 0;
	int start, len;

	unsigned int utf32_val[MAXTEMPBUFSIZE];
	unsigned int utf32_len;

	unsigned char Buf[MAXTEMPBUFSIZE];

	IDX_UTF8toUTF32((unsigned char*)SecVal, utf32_val, &utf32_len);
	for (i = 0; i < off_num; i++) {
		start = idx_offsets[i].start;
		len = idx_offsets[i].len;
		if (start + len >= utf32_len)
			continue;

		IDX_UTF32toUTF8(&utf32_val[start], len, Buf);

		PostInfo[PostInfoNum].keyLen = strlen((char*)Buf);
		if (PostInfo[PostInfoNum].keyLen > 0) {
			if (PostInfo[PostInfoNum].keyLen >= MAXKEYLEN) {
				strncpy(PostInfo[PostInfoNum].key, (char*)Buf, MAXKEYLEN - 1);
				PostInfo[PostInfoNum].keyLen = MAXKEYLEN - 1;
				PostInfo[PostInfoNum].key[MAXKEYLEN - 1] = '\0';
			} else 
				strcpy(PostInfo[PostInfoNum].key, (char*)Buf);

			strlower(PostInfo[PostInfoNum].key);
			PostInfo[PostInfoNum].psgNum = 0;
			PostInfo[PostInfoNum].wordNum = 0;

			PostInfoNum++;
		}
	}

	return PostInfoNum;
}

/*
 * 색인 타입 : INDEX_AS_IS
 */
int IDX_IndexAsIs(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int PostInfoNum = 0;
	char TempSecVal[MAXTEMPBUFSIZE];
	extern int HanjaFlag;
	extern int off_num;

	/* 색인 대상 섹션 필터링 */
	IDX_FilterSecVal(SecVal);
	RemoveDCode(SecVal);	// 지정 코드 삭제

	if (off_num > 0) {		// 영역색인이 지정되어 있으면 IndexAsIs는 수행하지 않음
		PostInfoNum = RangeIndex(SecVal, PostInfo);
		return PostInfoNum;
	}

	/* "한자는 그대로" 플래그가 세팅되지 않으면 한글로 변환 */
	/* 수정 : 한자 플래그가 1이면 한글로 변환 */
	if (HanjaFlag == 1) {
		Hanja2Hangul_UTF8((unsigned char*)SecVal, (unsigned char*)TempSecVal);

		PostInfo[0].keyLen = strlen(TempSecVal);
		if (PostInfo[0].keyLen > 0) {
			if (PostInfo[0].keyLen >= MAXKEYLEN) {
				strncpy(PostInfo[0].key, TempSecVal, MAXKEYLEN - 1);
				PostInfo[0].keyLen = MAXKEYLEN - 1;
				PostInfo[0].key[MAXKEYLEN - 1] = '\0';
			} else 
				strcpy(PostInfo[0].key, TempSecVal);

			strlower(PostInfo[0].key);
			PostInfo[0].psgNum = 0;
			PostInfo[0].wordNum = 0;

			PostInfoNum = RangeIndex(SecVal, &PostInfo[1]);
			return PostInfoNum+1;
		} else {
			PostInfoNum = RangeIndex(SecVal, PostInfo);
			return PostInfoNum;
		}
	} else {
		PostInfo[0].keyLen = strlen(SecVal);
		if (PostInfo[0].keyLen > 0) {
			if (PostInfo[0].keyLen >= MAXKEYLEN) {
				strncpy(PostInfo[0].key, SecVal, MAXKEYLEN - 1);
				PostInfo[0].keyLen = MAXKEYLEN - 1;
				PostInfo[0].key[MAXKEYLEN - 1] = '\0';
			} else 
				strcpy(PostInfo[0].key, SecVal);

			strlower(PostInfo[0].key);
			PostInfo[0].psgNum = 0;
			PostInfo[0].wordNum = 0;

			PostInfoNum = RangeIndex(SecVal, &PostInfo[1]);
			return PostInfoNum+1;
		} else {
			PostInfoNum = RangeIndex(SecVal, PostInfo);
			return PostInfoNum;
		}
	}
}
