/*
 * 불용어 관리 모듈...
 *
 * 작성자 : 최성필
 * 작성일 : 2001/09/17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IDX_common.h>
#include <IDX_StopWord.h>

#define MAX_ACTIVATE_NUM		100

//static SW_SET StopWordSet[MAX_STOPWORD_SETS];
SW_SET StopWordSet[MAX_STOPWORD_SETS];
//static unsigned int SW_Set_Num;
unsigned int SW_Set_Num; 			// 이상타....
//static unsigned int ActiveStopWordIdx[MAX_ACTIVATE_NUM];
//static unsigned int AS_Num;
unsigned int ActiveStopWordIdx[MAX_ACTIVATE_NUM];
unsigned int AS_Num;

char temp_buf[100000];

int FindStopWordID(char *SWID);

int InitStopWordSet()
{
	/*
	int i;

	for (i = 0; i < SW_Set_Num; i++) {
		if (StopWordSet[i].sw_item == NULL)
			continue;
		free(StopWordSet[i].sw_item);
	}
	*/

	SW_Set_Num = 0;
	AS_Num = 0;

	return 1;
}

int CloseStopWordSet()
{
	int i;

	for (i = 0; i < SW_Set_Num; i++) {
		if (StopWordSet[i].sw_item == NULL)
			continue;
		free(StopWordSet[i].sw_item);
	}

	SW_Set_Num = 0;
	AS_Num = 0;

	return 1;
}

int RegisterStopWordSet(char *SWBuf, char *SWID)
{
	int idx, sw_cnt, cnt;
	char *ptr;
 
	if (FindStopWordID(SWID))
		return 2;

	strcpy(temp_buf, SWBuf);
	idx = ReturnUnusedStopWordSetIndex();

	sw_cnt = CountSW(temp_buf);

	StopWordSet[idx].sw_item = (SW_ITEM *) malloc(sizeof(SW_ITEM) *(sw_cnt+1));
	if (StopWordSet[idx].sw_item == NULL)
		return 0;

	cnt = 0;
	ptr = strtok(temp_buf, " \t\n");
	if (ptr == NULL) 
		return 0;

	strcpy(StopWordSet[idx].sw_item[cnt].s_word, ptr);
	cnt++;

	while (1) {
		ptr = strtok(NULL, " \t\n");
		if (ptr == NULL)
			break;
		strcpy(StopWordSet[idx].sw_item[cnt].s_word, ptr);
		cnt++;
	}

	strcpy(StopWordSet[idx].ID, SWID);
	StopWordSet[idx].sw_item_num = cnt;

	if (idx == SW_Set_Num)
		SW_Set_Num++;

	return 1;
}

int RegisterStopWordSetArr(char *SWID, char *SWBuf[], int SWNum)
{
	int i, idx;
 
	if (FindStopWordID(SWID))
		return 2;

	idx = ReturnUnusedStopWordSetIndex();

	StopWordSet[idx].sw_item = (SW_ITEM *) malloc(sizeof(SW_ITEM) *(SWNum+1));
	if (StopWordSet[idx].sw_item == NULL)
		return 0;

	for (i = 0; i < SWNum; i++) {
		strcpy(StopWordSet[idx].sw_item[i].s_word, SWBuf[i]);
	}

	strcpy(StopWordSet[idx].ID, SWID);
	StopWordSet[idx].sw_item_num = SWNum;

	if (idx == SW_Set_Num)
		SW_Set_Num++;

	return 1;
}

int FindStopWordID(char *SWID)
{
	int i;

	for (i = 0; i < SW_Set_Num; i++) {
		/*
		if (StopWordSet[i].sw_item_num > 0) {
		*/
			if (!strcmp(StopWordSet[i].ID, SWID))
				break;
		/*
		}
		*/
	}
	if (i < SW_Set_Num)
		return 1;

	return 0;
}

int GetStopWordSetIDs(char *SWIDs)
{
	int i, cnt = 0;

	SWIDs[0] = '\0';
	for (i = 0; i < SW_Set_Num; i++) {
		if (StopWordSet[i].sw_item_num > 0) {
			strcat(SWIDs, StopWordSet[i].ID);
			strcat(SWIDs, " ");
			cnt++;
		}
	}
	SWIDs[strlen(SWIDs)-1] = '\0';

	return cnt;
}

int CountSW(char *buf)
{
	int i = 0, cnt = 0;
	int len = strlen(buf);

	while (i < len) {
		if (buf[i] & 0x80) {
			i += 2;
			continue;
		}

		if (buf[i] == '\n')
			cnt++;
		i++;
	}

	return cnt;
}

int DiscardStopWordSet(char *ID)
{
	int idx = FindStopWordSet(ID);

	if (idx == -1)
		return 0;

	free(StopWordSet[idx].sw_item);
	StopWordSet[idx].sw_item_num = 0;

	return 1;
}

int FindStopWordSet(char *ID)
{
	int i;

	for (i = 0; i < SW_Set_Num; i++){
		if (!strcmp(StopWordSet[i].ID, ID))
			return i;
	}

	return -1;
}

int ReturnUnusedStopWordSetIndex()
{
	int i;

	for (i = 0; i < SW_Set_Num; i++) {
		if (StopWordSet[i].sw_item == NULL)
			return i;
	}

	return SW_Set_Num;
}

int ActivateStopWordSet(char *ID)
{
	int idx = FindStopWordSet(ID);

	if (idx == -1)
		return 0;

	AS_Num = 1;

	ActiveStopWordIdx[0] = idx;

	return 1;
}

int ActivateStopWordSets(char *IDs[], int SWIDNum)
{
	int i, idx;

	AS_Num = 0;
	for (i = 0; i < SWIDNum; i++) {
		idx = FindStopWordSet(IDs[i]);
		if (idx == -1)
			continue;
		ActiveStopWordIdx[AS_Num++] = idx;
	}

	/*
#ifdef DEBUG
	printf("AS_Num = %d\n", AS_Num);
	printf("SW_Set_Num = %d\n", SW_Set_Num);
#endif
	*/

	return 1;
}

int DeActivateStopWordSets()
{
	AS_Num = 0;

	return 1;
}

int compare_switem(const void *i1, const void *i2)
{
	return (strcmp(((SW_ITEM *) i1)->s_word, ((SW_ITEM *) i2)->s_word));
}

int IDX_FindStopWord(char *word)
{
	int idx, i;
	SW_ITEM sItem, *rItem;

	for (i = 0; i < AS_Num; i++) {
		idx = ActiveStopWordIdx[i];

		strcpy(sItem.s_word, word);

		rItem = (SW_ITEM *) bsearch(&sItem, StopWordSet[idx].sw_item, StopWordSet[idx].sw_item_num, sizeof(SW_ITEM), compare_switem);
		/*
#ifdef DEBUG
		if (rItem != NULL)
			printf("Found Stopword...\n");
#endif
		*/
		if (rItem != NULL)
			return 1;
	}

	return 0;
}
