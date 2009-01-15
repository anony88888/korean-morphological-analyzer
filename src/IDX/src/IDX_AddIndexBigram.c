#include <IDX_common.h>
#include <IDX_user.h>

// ���� ������ �ĺ���: ��ü��, ���� ��ȯ � ���� ���ܹ�ȣ ����
#define MAX_PSG_CANDIDATE_NUM 128

int IDX_AddIndexBigram(POSTINFO *PostInfo, int OrgPostCnt)
{
	int				PostInfoCnt = OrgPostCnt;
	int				i, j;

	// PostInfoCnt == 1�̸� ���̻� ó���� �ʿ� ����.
	if (OrgPostCnt <2) return PostInfoCnt;

	// ���� �ܾ��� ��... : PostInfo�� ��ġ�� �����Ѵ�.
	int PrevWordPos[MAX_PSG_CANDIDATE_NUM];
	int prevWordPosCnt;
	PrevWordPos[0] = 0;
	prevWordPosCnt=1;

	for (i=1; i<OrgPostCnt; i++) {
		for (j=0; j<prevWordPosCnt; j++) {
			if (PostInfoCnt >= MAXPOSTINFOSIZE) return PostInfoCnt;
			if ( (PostInfo[PrevWordPos[j]].psgNum == PostInfo[i].psgNum) ||
					(PostInfo[PrevWordPos[j]].psgNum==0 && PostInfo[i].psgNum==1000) ||
					(PostInfo[PrevWordPos[j]].psgNum==1000 && PostInfo[i].psgNum==0) )	// MIX_CHAR���� "����"�� ���� ����+�ѱ� �Ǵ� �ѱ�+������ ���̱׷� ���� ����... 2006.06.12. Jinsuk
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
		// ���� ������ word num���� ���� ���� �����Ѵ�...
		for (j=0; j<prevWordPosCnt; j++) {
			if (PostInfo[PrevWordPos[j]].psgNum == PostInfo[i].psgNum) {
				// wordNum�� 2�̻� ���̳��� �ĺ����� ����...
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
	// ��: "�̸�� ����" --> "��","��","��","��","��","��^��","��^��", "��^��"
	// ��: "�̸�� ����" --> "�̸��","����","�̸��^����"
	// ��: "�����˻�" --> "����","�˻�", "�����˻�", "����^�˻�"
	// ��: "���" --> "�", "��", "��", "��", "��", "�^��", "��^��", "��^��" (���� ��� ��ü��)
	
	return PostInfoCnt;
}
