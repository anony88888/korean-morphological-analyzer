#include <IDX_common.h>
#include <IDX_user.h>

// 이전 문단의 후보군: 이체자, 한한 변환 등에 따른 문단번호 지원
#define MAX_PSG_CANDIDATE_NUM 128

int IDX_AddIndexBigram(POSTINFO *PostInfo, int OrgPostCnt)
{
	int				PostInfoCnt = OrgPostCnt;
	int				i, j;

	// PostInfoCnt == 1이면 더이상 처리할 필요 없음.
	if (OrgPostCnt <2) return PostInfoCnt;

	// 이전 단어의 군... : PostInfo의 위치를 저장한다.
	int PrevWordPos[MAX_PSG_CANDIDATE_NUM];
	int prevWordPosCnt;
	PrevWordPos[0] = 0;
	prevWordPosCnt=1;

	for (i=1; i<OrgPostCnt; i++) {
		for (j=0; j<prevWordPosCnt; j++) {
			if (PostInfoCnt >= MAXPOSTINFOSIZE) return PostInfoCnt;
			if ( (PostInfo[PrevWordPos[j]].psgNum == PostInfo[i].psgNum) ||
					(PostInfo[PrevWordPos[j]].psgNum==0 && PostInfo[i].psgNum==1000) ||
					(PostInfo[PrevWordPos[j]].psgNum==1000 && PostInfo[i].psgNum==0) )	// MIX_CHAR에서 "아式"과 같이 한자+한글 또는 한글+한자의 바이그램 색인 지원... 2006.06.12. Jinsuk
			{
				if (PostInfo[PrevWordPos[j]].wordNum == PostInfo[i].wordNum-1) {
					strcpy(PostInfo[PostInfoCnt].key, PostInfo[PrevWordPos[j]].key);
					strcpy(PostInfo[PostInfoCnt].key+PostInfo[PrevWordPos[j]].keyLen, "^");
					strcpy(PostInfo[PostInfoCnt].key+PostInfo[PrevWordPos[j]].keyLen+1, PostInfo[i].key);
					PostInfo[PostInfoCnt].keyLen=PostInfo[PrevWordPos[j]].keyLen+PostInfo[i].keyLen+1;
					PostInfo[PostInfoCnt].psgNum = -1*PostInfo[i].psgNum-1;
					PostInfo[PostInfoCnt].wordNum = PostInfo[PrevWordPos[j]].wordNum;
					PostInfoCnt++;
				}
			}
		}
		// 이제 이전의 word num보다 작은 것은 제거한다...
		for (j=0; j<prevWordPosCnt; j++) {
			if (PostInfo[PrevWordPos[j]].psgNum == PostInfo[i].psgNum) {
				// wordNum이 2이상 차이나면 후보에서 버림...
				if (PostInfo[PrevWordPos[j]].wordNum+1 < PostInfo[i].wordNum) {
					if (j >= prevWordPosCnt-1) prevWordPosCnt--;
					else {
						PrevWordPos[j] = PrevWordPos[prevWordPosCnt-1];
						prevWordPosCnt--;
						j--;
					}
				}
			}
		}
		if (prevWordPosCnt < MAX_PSG_CANDIDATE_NUM) {
			PrevWordPos[prevWordPosCnt] = i;
			prevWordPosCnt++;
		}
	}
	// 예: "이명박 시장" --> "이","명","박","시","장","이^명","명^박", "시^장"
	// 예: "이명박 시장" --> "이명박","시장","이명박^시장"
	// 예: "정보검색" --> "정보","검색", "정보검색", "정보^검색"
	// 예: "雲雀" --> "雲", "云", "운", "雀", "작", "雲^雀", "云^雀", "운^작" (云은 雲의 이체자)
	
	return PostInfoCnt;
}
