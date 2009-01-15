/**********************************************************************
 *         The KRISTAL-2001 System, Version 1.0beta
 *
 * Developed by Sung Pil Choi (042-828-5107)
 ***********************************************************************/
#include <IDX_common.h>
#include <IDX_user.h>

/*
 * 색인 타입 : INDEX_AS_NUMERIC
 */
int IDX_IndexAsNumeric(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	/* 색인 대상 섹션 필터링 */
	IDX_FilterSecVal(SecVal);

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

		return 1;
	} else
		return 0;
}
