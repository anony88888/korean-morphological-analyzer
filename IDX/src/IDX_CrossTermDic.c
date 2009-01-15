/*
 * ��-�� ��ġ�� ���� ���� ��ƾ ���
 *
 * ������ ���Ǽ��� ���ؼ�...
 * 		= �ؽ�Ʈ ������ ������ ���� ���� ���縦 ���� �ʴ´�.
 * 		= ���簡 ���� �ʾ����� �˻��ص� �˻��� ���� �ʴ´�.
 *
 * �����޸𸮸� �̿�
 *
 * �ۼ��� : �ּ���
 * �ۼ��� : 2003-04-11
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
 * �˻� ��� ���(�����̸Ӹ� Ű)
 */
typedef struct {
	char term[MAX_TERM_LEN];		// �˻� ��� ���
	unsigned int start;		// ��� ����(��ġ��, �о�, ���) ���� ��ġ
	unsigned short int num;			// ��� ���� ����
} TERM;

/*
 * �˻� ��� ��� ����
 */
typedef struct {
	char term[MAX_TERM_LEN];		// ��ġ��
	char domain[MAX_DOMAIN_LEN];	// �о� ����
	char abbr[MAX_ABBR_LEN];		// ���
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
 * ��-�� ��ġ�� ���� �޸� ����
 * ���� ���� �״�� ��� --> ������ ���� --> ���߿��� �� ������ ���ڵ� �ؾ���
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
	 * �뿪�� ���� ������ ũ�⸦ ��� ���ؼ�,
	 * �����޸��� ù 16����Ʈ�� �д´�.
	 */
	ret_val = GetShMem(TERMS_DIC_SIZE_KEY, 16, (void **) &dic_size_ptr);
	if (ret_val == 1) { // �����޸𸮰� ���Ӱ� �����Ǿ����� --> ���� ���� �۾� ����
		/* �� <--> �� */
		sprintf(dic_file, "%s/%s", dic_dir, ENG_TO_KOR_DIC);
		fd_dic_ek = fopen(dic_file, "rt");
		if (fd_dic_ek == NULL) /* ������ ��� ������ �ƴ� */
			return 0;

		/* �� <--> �� */
		sprintf(dic_file, "%s/%s", dic_dir, KOR_TO_ENG_DIC);
		fd_dic_ke = fopen(dic_file, "rt");
		if (fd_dic_ke == NULL) /* ������ ��� ������ �ƴ� */
			return 0;

		/************************* �ε��� ������ ���� ���� ***************************/
		EK_TermInfoSetNum = 0;
		EK_TermSetNum = 0;
		while (fgets(line, 10000, fd_dic_ek)) {
			ret_val = GetTermInfo(line, &OneTerm, TermInfo, &TermInfoNum);
			if (ret_val == 0) /* ���� ���� */
				continue;
			EK_TermInfoSetNum += TermInfoNum;
			EK_TermSetNum++;
		}
		KE_TermInfoSetNum = 0;
		KE_TermSetNum = 0;
		while (fgets(line, 10000, fd_dic_ke)) {
			ret_val = GetTermInfo(line, &OneTerm, TermInfo, &TermInfoNum);
			if (ret_val == 0) /* ���� ���� */
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
			if (ret_val == 0) /* ���� ���� */
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
			if (ret_val == 0) /* ���� ���� */
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
		memcpy(&ek_dic_size, dic_size_ptr, 4);			// ���� ��� ����
		memcpy(&ek_dic_info_size, dic_size_ptr + 4, 4);	// ���� ��� ���� ����
		memcpy(&ke_dic_size, dic_size_ptr + 8, 4);		// �ѿ� ��� ����
		memcpy(&ke_dic_info_size, dic_size_ptr + 12, 4);	// �ѿ� ��� ���� ����

		ClearShMem((void **)&dic_size_ptr);					// ���� ũ�� �����޸� ����

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
// ���� �˻� + �� �ܾ� �˻� + PostInfo�� ����
// ������ UTF-8, �Է� �ܾ UTF-8
// wordNum�� ���� �ܾ ���� �ε����̴�.
// ���� prev_term�� �����ϰ� prev_term + term�� ������ �����ϸ� 
// �� ���ξ ���� wordNum�� 1�� �۾ƾ� �Ѵ�.
// ���� ���ξ�� �̹� PostInfo�� ����Ǿ� �ִٰ� ����
// ���⿡���� �뿪��� �����Ѵ�.
// flag�� ���� ���ξ ���ؼ� �뿪�� ���� Ž�� �����̴�.
// 		1 --> Ž�� ����
// 		0 --> Ž�� ���� ����
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
		// ���� �ܾ ���� ��...
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
				PostInfo[PostInfoCnt++].psgNum = 200;		// �뿪�� ��ȯ ���ξ� ���� ǥ�� (���Ͼ�)

				ptr = strtok(NULL, ",");
			}
		}
#ifdef TRACE
		printf("END\n");
#endif
	} else {
		// �� �ܾ ����� �˻�...
		sprintf(term_phrase, "%s %s", PrevIndex->key, CurrIndex->key);
#ifdef TRACE
		printf("(2) IDX_SearchCrossDic...");
#endif
		if (IDX_SearchCrossDic(term_phrase, result)) {
			// �� �ܾ�� ������ ���� ������ �����ϸ�...
			// �켱 �� �� �ܾ �ϳ��� ���ξ�� PostInfo�� �����Ѵ�.
#ifdef DUMP_CD_RESULT
			fprintf(fd_dump_cd, "[%s](TWO_WORDS) ------> %s\n", term_phrase, result);
#endif
			strcpy(PostInfo[PostInfoCnt].key, term_phrase);
			PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
			PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
			PostInfo[PostInfoCnt++].psgNum = 300;		// ���� �ܾ�� ������ ���� ���ξ� ���� ǥ��
			ptr = strtok(result, ",");
			while (ptr != NULL) {
				strcpy(PostInfo[PostInfoCnt].key, ptr);
				PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
				PostInfo[PostInfoCnt++].psgNum = 200;		// �뿪�� ��ȯ ���ξ� ���� ǥ�� (���Ͼ�)

				ptr = strtok(NULL, ",");
			}
		}

#ifdef TRACE
		printf("END\n");
#endif

#ifdef TRACE
		printf("(3) IDX_SearchCrossDic...");
#endif
		
		// �� �ܾ �ٿ��� �˻�...
		sprintf(term_phrase, "%s%s", PrevIndex->key, CurrIndex->key);
		if (IDX_SearchCrossDic(term_phrase, result)) {
			// �� �ܾ�� ������ ���� ������ �����ϸ�...
			// �켱 �� �� �ܾ �ϳ��� ���ξ�� PostInfo�� �����Ѵ�.
#ifdef DUMP_CD_RESULT
			fprintf(fd_dump_cd, "[%s](TWO_WORDS) ------> %s\n", term_phrase, result);
#endif
			strcpy(PostInfo[PostInfoCnt].key, term_phrase);
			PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
			PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
			PostInfo[PostInfoCnt++].psgNum = 300;		// ���� �ܾ�� ������ ���� ���ξ� ���� ǥ��
			ptr = strtok(result, ",");
			while (ptr != NULL) {
				strcpy(PostInfo[PostInfoCnt].key, ptr);
				PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
				PostInfo[PostInfoCnt].wordNum = PrevIndex->wordNum;
				PostInfo[PostInfoCnt++].psgNum = 200;		// �뿪�� ��ȯ ���ξ� ���� ǥ�� (���Ͼ�)

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
			// ���� �ܾ �˻�...
			if (IDX_SearchCrossDic(CurrIndex->key, result)) {
#ifdef DUMP_CD_RESULT
				fprintf(fd_dump_cd, "[%s](ONE_WORD) ------> %s\n", CurrIndex->key, result);
#endif
				ptr = strtok(result, ",");
				while (ptr != NULL) {
					strcpy(PostInfo[PostInfoCnt].key, ptr);
					PostInfo[PostInfoCnt].keyLen = strlen(PostInfo[PostInfoCnt].key);
					PostInfo[PostInfoCnt].wordNum = CurrIndex->wordNum;
					PostInfo[PostInfoCnt++].psgNum = 200;		// �뿪�� ��ȯ ���ξ� ���� ǥ�� (���Ͼ�)

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

// ���� �˻� : ��-��, ��-�� �Ѵ� �˻�
// ����� �޸� ������ ��Ʈ�� str1,str2,str3,........
int IDX_SearchCrossDic(char *term, char *result)
{
	int ret_val;

	if (isalpha(term[0]))
		ret_val = IDX_SearchCrossDicEng2Kor(term, result);
	else 
		ret_val = IDX_SearchCrossDicKor2Eng(term, result);

	return ret_val;
}

// �� --> ��
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

// �� --> ��
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



/* �Է� ��Ʈ������ ��� �� ��� ���� ���� */
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
