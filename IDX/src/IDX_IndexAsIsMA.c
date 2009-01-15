#include <IDX_common.h>
#include <IDX_user.h>

/*
 * 색인 타입 : INDEX_AS_IS_MA --> INDEX_AS_IS + INDEX_BY_MA
 */
int IDX_IndexAsIsMA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int PostInfoCnt;

	PostInfoCnt = IDX_IndexAsIs(SecVal, PostInfo, StopCheck);
	if (PostInfoCnt == 0)
		return 0;

	PostInfoCnt += IDX_IndexByMA(SecVal, PostInfo + PostInfoCnt, StopCheck);

	return PostInfoCnt;
}
