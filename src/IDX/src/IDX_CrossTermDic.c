/*
 * 한-영 대치어 사전 접근 루틴 모듬
 *
 * 배포의 편의성을 위해서...
 * 		= 텍스트 사전이 없으면 에러 없이 적재를 하지 않는다.
 * 		= 적재가 되지 않았으면 검색해도 검색이 되지 않는다.
 *
 * 공유메모리를 이용
 *
 * 작성자 : 최성필
 * 작성일 : 2003-04-11
 */
#include <IDX_common.h>
#include <IDX_user.h>
#include <MA_ShmOP.h>

#define TERMS_DIC_SIZE_KEY		(key_t) 0x110
#define EK_TERMS_DIC_KEY		(key_t) 0x120
#define EK_TERMS_INFO_DIC_KEY	(key_t) 0x130
#define KE_TERMS_DIC_KEY		(key_t) 0x140
#define KE_TERMS_INFO_DIC_KEY	(key_t) 0x150

#define ENG_TO_KOR_DIC		"TERMS.EK"
#define KOR_TO_ENG_DIC		"TERMS.KE"

#define MAX_TERM_LEN		64
#define MAX_DOMAIN_LEN		16
#define MAX_ABBR_LEN		10

#define MAX_TERM_INFO		500

/*
 * 검색 대상 용어(프라이머리 키)
 */
typedef struct {
	char term[MAX_TERM_LEN];		// 검색 대상 용어
	unsigned int start;		// 용어 정보(대치어, 분야, 약어) 시작 위치
	unsigned short int num;			// 용어 정보 개수
} TERM;

/*
 * 검색 대상 용어 정보
 */
typedef struct {
	char term[MAX_TERM_LEN];		// 대치어
	char domain[MAX_DOMAIN_LEN];	// 분야 정보
	char abbr[MAX_ABBR_LEN];		// 약어
} TERM_INFO;

/*****************************/
static TERM *EK_TermSet;
static int EK_TermSetNum;

static TERM_INFO *EK_TermInfoSet;
static int EK_TermInfoSetNum;

static TERM *KE_TermSet;
static int KE_TermSetNum;

static TERM_INFO *KE_TermInfoSet;
static int KE_TermInfoSetNum;
/*****************************/

int GetTermInfo(char *line, TERM *OneTerm, TERM_INFO *TermInfo, int *TermInfoNum);

#ifdef DUMP_CD_RESULT
FILE *fd_dump_cd;
#endif

/*
 * 한-영 대치어 사전 메모리 적재
 * 원시 사전 그대로 사용 --> 문제가 있음 --> 나중에는 이 사전을 인코딩 해야함
 */
int IDX_LoadCrossTermDic(char *dic_dir)
{
	char dic_file[512];
	FILE *fd_dic_ek, *fd_dic_ke;
	char line[10000];
	TERM OneTerm, *pTermSet;
	TERM_INFO TermInfo[MAX_TERM_INFO], *pTermInfoSet;
	int TermInfoNum, StartPos;
	int ret_val;
	int ek_dic_size, ek_dic_info_size;
	int ke_dic_size, ke_dic_info_size;
	char *dic_size_ptr;

#ifdef DUMP_CD_RESULT
	fd_dump_cd = fopen("CD_RESULT.DUMP", "wt");
#endif

	EK_TermSet = NULL;
	EK_TermInfoSet = NULL;
	KE_TermSet = NULL;
	KE_TermInfoSet = NULL;

	/* 
	 * 대역어 사전 각각의 크기를 얻기 위해서,
	 * 공유메모리의 첫 16바이트를 읽는다.
	 */
	ret_val = GetShMem(TERMS_DIC_SIZE_KEY, 16, (void **) &dic_size_ptr);
	if (ret_val == 1) { // 공유메모리가 새롭게 생성되었으면 --> 사전 적재 작업 수행
		/* 영 <--> 한 */
		sprintf(dic_file, "%s/%s", dic_dir, ENG_TO_KOR_DIC);
		fd_dic_ek = fopen(dic_file, "rt");
		if (fd_dic_ek == NULL) /* 사전이 없어도 에러가 아님 */
			return 0;

		/* 한 <--> 영 */
		sprintf(dic_file, "%s/%s", dic_dir, KOR_TO_ENG_DIC);
		fd_dic_ke = fopen(dic_file, "rt");
		if (fd_dic_ke == NULL) /* 사전이 없어도 에러가 아님 */
			return 0;

		/************************* 로딩될 아이템 개수 조사 ***************************/
		EK_TermInfoSetNum = 0;
		EK_TermSetNum = 0;
		while (fgets(line, 10000, fd_dic_ek)) {
			ret_val = GetTermInfo(line, &OneTerm, TermInfo, &TermInfoNum);
			if (ret_val == 0) /* 포멧 에러 */
				continue;
			EK_TermInfoSetNum += TermInfoNum;
			EK_TermSetNum++;
		}
		KE_TermInfoSetNum = 0;
		KE_TermSetNum = 0;
		while (fgets(line, 10000, fd_dic_ke)) {
			ret_val = GetTermInfo(line, &OneTerm, TermInfo, &TermInfoNum);
			if (ret_val == 0) /* 포멧 에러 */
				continue;
			KE_TermInfoSetNum += TermInfoNum;
			KE_TermSetNum++;
		}
		fseek(fd_dic_ek, 0L, SEEK_SET);
		fseek(fd_dic_ke, 0L, SEEK_SET);
		/****************************************************************************/

		ek_dic_size = EK_TermSetNum * sizeof(TERM);
		ek_dic_info_size = EK_TermInfoSetNum * sizeof(TERM_INFO);
		ke_dic_size = KE_TermSetNum * sizeof(TERM);
		ke_dic_info_size = KE_TermInfoSetNum * sizeof(TERM_INFO);

		memcpy(dic_size_ptr, &ek_dic_size, sizeof(int));
		memcpy(dic_size_ptr + sizeof(int), &ek_dic_info_size, sizeof(int));
		memcpy(dic_size_ptr + (sizeof(int) * 2), &ke_dic_size, sizeof(int));
		memcpy(dic_size_ptr + (sizeof(int) * 3), &ke_dic_info_size, sizeof(int));

		ClearShMem((void **) &dic_size_ptr);

		printf("ek_dic_size = %d\n", ek_dic_size);
		printf("ek_dic_info_size = %d\n", ek_dic_info_size);
		printf("ke_dic_size = %d\n", ke_dic_size);
		printf("ke_dic_info_size = %d\n", ke_dic_info_size);

		ret_val = GetShMem(EK_TERMS_DIC_KEY, ek_dic_size, (void **) &EK_TermSet);
		ret_val = GetShMem(EK_TERMS_INFO_DIC_KEY, ek_dic_info_size, (void **) &EK_TermInfoSet);
		ret_val = GetShMem(KE_TERMS_DIC_KEY, ke_dic_size, (void **) &KE_TermSet);
		ret_val = GetShMem(KE_TERMS_INFO_DIC_KEY, ke_dic_info_size, (void **) &KE_TermInfoSet);

		pTermSet = EK_TermSet;
		pTermInfoSet = EK_TermInfoSet;
		StartPos = 0;
		while (fgets(line, 10000, fd_dic_ek)) {
			ret_val = GetTermInfo(line, pTermSet, pTermInfoSet, &TermInfoNum);
			if (ret_val == 0) /* 포멧 에러 */
				continue;

			pTermSet->start = StartPos;
			pTermSet->num = TermInfoNum;

			pTermSet++;
			pTermInfoSet += TermInfoNum;
			StartPos += TermInfoNum;
		}

		pTermSet = KE_TermSet;
		pTermInfoSet = KE_TermInfoSet;
		StartPos = 0;
		while (fgets(line, 10000, fd_dic_ke)) {
			ret_val = GetTermInfo(line, pTermSet, pTermInfoSet, &TermInfoNum);
			if (ret_val == 0) /* 포멧 에러 */
				continue;

			pTermSet->start = StartPos;
			pTermSet->num = TermInfoNum;

			pTermSet++;
			pTermInfoSet += TermInfoNum;
			StartPos += TermInfoNum;
		}

		qsort(EK_TermSet, EK_TermSetNum, sizeof(TERM), compare_terms);
		qsort(KE_TermSet, KE_TermSetNum, sizeof(TERM), compare_terms);

	} else {
		memcpy(&ek_dic_size, dic_size_ptr, 4);			// 영한 용어 개수
		memcpy(&ek_dic_info_size, dic_size_ptr + 4, 4);	// 영한 용어 정보 개수
		memcpy(&ke_dic_size, dic_size_ptr + 8, 4);		// 한영 용어 개수
		memcpy(&ke_dic_info_size, dic_size_ptr + 12, 4);	// 한영 용어 정보 개수

		ClearShMem((void **)&dic_size_ptr);					// 사전 크기 공유메모리 해제

		ret_val = GetShMem(EK_TERMS_DIC_KEY, ek_dic_size, (void **) &EK_TermSet);
		ret_val = GetShMem(EK_TERMS_INFO_DIC_KEY, ek_dic_info_size, (void **) &EK_TermInfoSet);
		ret_val = GetShMem(KE_TERMS_DIC_KEY, ke_dic_size, (void **) &KE_TermSet);
		ret_val = GetShMem(KE_TERMS_INFO_DIC_KEY, ke_dic_info_size, (void **) &KE_TermInfoSet);
		
		EK_TermSetNum = ek_dic_size / sizeof(TERM);
		EK_TermInfoSetNum = ek_dic_info_size / sizeof(TERM_INFO);
		KE_TermSetNum = ke_dic_size / sizeof(TERM);
		KE_TermInfoSetNum = ke_dic_info_size / sizeof(TERM_INFO);
	}

	return 1;
}

int IDX_CloseCrossTermDic()
{
	ClearShMem((void **) &EK_TermSet);
	ClearShMem((void **) &EK_TermInfoSet);
	ClearShMem((void **) &KE_TermSet);
	ClearShMem((void **) &KE_TermInfoSet);

#ifdef DUMP_CD_RESULT
	fclose(fd_dump_cd);
#endif

	return 1;
}

////////////////////////////////////////////////////////////////
// 통합 검색 + 두 단어 검색 + PostInfo에 저장
// 사전도 UTF-8, 입력 단어도 UTF-8
// wordNum은 현재 단어에 대한 인덱스이다.
// 만일 prev_term이 존재하고 prev_term + term이 사전에 존재하면 
// 이 색인어에 대한 wordNum은 1이 작아야 한다.
// 현재 색인어는 이미 PostInfo에 저장되어 있다고 가정
// 여기에서는 대역어만을 저장한다.
// flag는 현재 색인어에 대해서 대역어 사전 탐색 여부이다.
// 		1 --> 탐색 수행
// 		0 --> 탐색 하지 않음
////////////////////////////////////////////////////////////////
int IDX_CheckCrossDic(POSTINFO *PrevIndex, POSTINFO *CurrIndex, POSTINFO *PostInfo, int flag)
{
	int PostInfoCnt = 0;
	char term_phrase[1024];
	char result[10000];
	char *ptr;

#ifdef TRACE_CD
	printf("IN (IDX_SearchCrossDic)...\n");
#endif

	if (PrevIndex->key[0] == '\0') {
		// 이전 단어가 없을 때...
#ifdef TRACE
		printf("(1) IDX_SearchCrossDic...");
#endif
		if (IDX_SearchCrossDic(CurrIndex->key, result)) {
#ifdef DUMP_CD_RESULT
			fprintf(fd_dump_cd, "[%s](ONE_WORD) ------> %s\n", CurrIndex->key, result);
#endif
			ptr = strtok(result, ",");
			while (ptr != NULL) {
				strcpy(PostInfo[PostInfoCnt].key, ptr);
				PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].wordNum = CurrIndex->wordNum;
				PostInfo[PostInfoCnt++].psgNum = 200;		// 대역어 변환 색인어 정보 표시 (단일어)

				ptr = strtok(NULL, ",");
			}
		}
#ifdef TRACE
		printf("END\n");
#endif
	} else {
		// 두 단어를 띄워서 검색...
		sprintf(term_phrase, "%s %s", PrevIndex->key, CurrIndex->key);
#ifdef TRACE
		printf("(2) IDX_SearchCrossDic...");
#endif
		if (IDX_SearchCrossDic(term_phrase, result)) {
			// 두 단어로 구성된 절이 사전에 존재하면...
			// 우선 그 두 단어를 하나의 색인어로 PostInfo에 저장한다.
#ifdef DUMP_CD_RESULT
			fprintf(fd_dump_cd, "[%s](TWO_WORDS) ------> %s\n", term_phrase, result);
#endif
			strcpy(PostInfo[PostInfoCnt].key, term_phrase);
			PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
			PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
			PostInfo[PostInfoCnt++].psgNum = 300;		// 이전 단어와 합쳐진 구절 색인어 정보 표시
			ptr = strtok(result, ",");
			while (ptr != NULL) {
				strcpy(PostInfo[PostInfoCnt].key, ptr);
				PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
				PostInfo[PostInfoCnt++].psgNum = 200;		// 대역어 변환 색인어 정보 표시 (단일어)

				ptr = strtok(NULL, ",");
			}
		}

#ifdef TRACE
		printf("END\n");
#endif

#ifdef TRACE
		printf("(3) IDX_SearchCrossDic...");
#endif
		
		// 두 단어를 붙여서 검색...
		sprintf(term_phrase, "%s%s", PrevIndex->key, CurrIndex->key);
		if (IDX_SearchCrossDic(term_phrase, result)) {
			// 두 단어로 구성된 절이 사전에 존재하면...
			// 우선 그 두 단어를 하나의 색인어로 PostInfo에 저장한다.
#ifdef DUMP_CD_RESULT
			fprintf(fd_dump_cd, "[%s](TWO_WORDS) ------> %s\n", term_phrase, result);
#endif
			strcpy(PostInfo[PostInfoCnt].key, term_phrase);
			PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
			PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
			PostInfo[PostInfoCnt++].psgNum = 300;		// 이전 단어와 합쳐진 구절 색인어 정보 표시
			ptr = strtok(result, ",");
			while (ptr != NULL) {
				strcpy(PostInfo[PostInfoCnt].key, ptr);
				PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
				PostInfo[PostInfoCnt++].psgNum = 200;		// 대역어 변환 색인어 정보 표시 (단일어)

				ptr = strtok(NULL, ",");
			}
		}

#ifdef TRACE
		printf("END\n");
#endif
#ifdef TRACE
		printf("(4) IDX_SearchCrossDic...");
#endif
		if (flag) {
			// 현재 단어만 검색...
			if (IDX_SearchCrossDic(CurrIndex->key, result)) {
#ifdef DUMP_CD_RESULT
				fprintf(fd_dump_cd, "[%s](ONE_WORD) ------> %s\n", CurrIndex->key, result);
#endif
				ptr = strtok(result, ",");
				while (ptr != NULL) {
					strcpy(PostInfo[PostInfoCnt].key, ptr);
					PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
					PostInfo[PostInfoCnt].wordNum = CurrIndex->wordNum;
					PostInfo[PostInfoCnt++].psgNum = 200;		// 대역어 변환 색인어 정보 표시 (단일어)

					ptr = strtok(NULL, ",");
				}
			}
		}
#ifdef TRACE
		printf("END\n");
#endif
	}

	return PostInfoCnt;
}

// 통합 검색 : 한-영, 영-한 둘다 검색
// 결과는 콤마 단위의 스트링 str1,str2,str3,........
int IDX_SearchCrossDic(char *term, char *result)
{
	int ret_val;

	if (isalpha(term[0]))
		ret_val = IDX_SearchCrossDicEng2Kor(term, result);
	else 
		ret_val = IDX_SearchCrossDicKor2Eng(term, result);

	return ret_val;
}

// 영 --> 한
int IDX_SearchCrossDicEng2Kor(char *term, char *result)
{
	TERM ret, *res;
	int i;
	char prev_term[512];

	result[0] = '\0';
	if (EK_TermSet == NULL || EK_TermInfoSet == NULL)
		return 0;
	if (strlen(term) > MAX_TERM_LEN)
		return 0;
	strcpy(ret.term, term);
	res = (TERM *) bsearch(&ret, EK_TermSet, EK_TermSetNum, sizeof(TERM), compare_terms);
	if (res != NULL) {
		strcpy(prev_term, EK_TermInfoSet[res->start].term);
		strcpy(result, prev_term);
		strcat(result, ",");
		for (i = res->start + 1; i < res->start + res->num; i++) {
			if (strcmp(prev_term, EK_TermInfoSet[i].term)) {
				strcat(result, EK_TermInfoSet[i].term);
				strcat(result, ",");
				strcpy(prev_term, EK_TermInfoSet[i].term);
			}
		}
		return res->num;
	} else 
		return 0;
}

// 한 --> 영
int IDX_SearchCrossDicKor2Eng(char *term, char *result)
{
	TERM ret, *res;
	int i;
	char prev_term[512];

	result[0] = '\0';
	if (KE_TermSet == NULL || KE_TermInfoSet == NULL)
		return 0;
	if (strlen(term) > MAX_TERM_LEN)
		return 0;
	strcpy(ret.term, term);
	res = (TERM *) bsearch(&ret, KE_TermSet, KE_TermSetNum, sizeof(TERM), compare_terms);
	if (res != NULL) {
		strcpy(prev_term, KE_TermInfoSet[res->start].term);
		strcpy(result, prev_term);
		strcat(result, ",");
		for (i = res->start + 1; i < res->start + res->num; i++) {
			if (strcmp(prev_term, KE_TermInfoSet[i].term)) {
				strcat(result, KE_TermInfoSet[i].term);
				strcat(result, ",");
				strcpy(prev_term, KE_TermInfoSet[i].term);
			}
		}
		return res->num;
	} else 
		return 0;
}

int compare_terms(void *t1, void *t2)
{
	return (strcmp( ((TERM *) t1)->term, ((TERM *) t2)->term ));
}



/* 입력 스트링에서 용어 및 용어 정보 추출 */
int GetTermInfo(char *line, TERM *OneTerm, TERM_INFO *TermInfo, int *TermInfoNum)
{
	char *ptr, *ptr_inner;
	int idx, order;
	char temp[1024], item[512];

	*TermInfoNum = 0;

	ptr = strtok(line, "@");
	if (ptr == NULL)
		return 0;
	strcpy(OneTerm->term, ptr);

	while (1) {
		ptr = strtok(NULL, "@");
		if (ptr == NULL)
			break;
		strcpy(temp, ptr);
		ptr_inner = temp;
		idx = 0;
		order = 0;
		while (*ptr_inner != '\0') {
			/*
			if (*ptr_inner & 0x80) {
				item[idx++] = *ptr_inner;
				ptr_inner++;
				item[idx++] = *ptr_inner;
				ptr_inner++;

				continue;
			}
			*/
			if (*ptr_inner == '|') {
				item[idx] = '\0';
				order++;
				switch (order) {
					case 1:
						strcpy(TermInfo[*TermInfoNum].domain, item);
						break;
					case 2:
						strcpy(TermInfo[*TermInfoNum].term, item);
						break;
				}
				idx = 0;
				ptr_inner++;

				continue;
			}
			item[idx] = *ptr_inner;
			idx++; ptr_inner++;
		}
		item[idx] = '\0';
		strcpy(TermInfo[*TermInfoNum].abbr, item);
		(*TermInfoNum)++;
	}

	return 1;
}
