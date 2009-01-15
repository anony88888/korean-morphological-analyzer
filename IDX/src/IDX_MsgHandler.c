#include <IDX_common.h>
#include <IDX_user.h>
#include <MA_Interface.h>
#include <HanjaVariantDef.h>
#include <IDX_Hanja2Hangul.h>

#ifdef SHARED_MEMORY_IDX
#include <MA_ShmOP.h>
#endif

#ifdef TIME_CHECK
#include <time.h>

static int total_time;

#endif

int StopCheck;
int StemCheck;
int HanjaFlag;
int StartWordNum;
int IDX_HANJA_PROC_OPTION;
int IdxBigram = 1;
int HighLight;

char *dCode;			// 삭제할 코드
char *dels;				// 분리자로 지정할 코드 리스트

INDEX_OFFSET	*idx_offsets;
int off_num;

#if 0

#ifdef SHARED_MEMORY_IDX
static char *idx_words_ptr;
static INDEX_WORD       *IndexWords;
#else
static INDEX_WORD       IndexWords[MAXINDEXWORDS];
#endif

#endif

int IDX_InitIDX(char *KristalDir)
{
	int		ret_val;
	char	dic_dir[512];
	char	tempDir[1024];
	int		len;
#ifdef SHARED_MEMORY_IDX
	int		mem_size;
#endif

#ifdef TIME_CHECK
	total_time = 0;
#endif

#ifdef SHARED_MEMORY_IDX
	mem_size = sizeof(INDEX_WORD) * MAXINDEXWORDS;
	ret_val = GetShMem(INDEXBUF_KEY, mem_size, (void **) &idx_words_ptr);
	IndexWords = (INDEX_WORD *) idx_words_ptr;
#endif

	InitStopWordSet();

	InitDicHeader(); /* MA Dictionary Variable Clear */
	strcpy(tempDir, KristalDir);
	len = strlen(tempDir);
	if (tempDir[len-1] != '/') strcat (tempDir, "/");
	sprintf(dic_dir, "%s%s", tempDir, SYS_MADICTDIRECTORY);
	ret_val = LoadDictionary(dic_dir); /* MA Dictionary Open */
	if (ret_val == 0)
		return -5300; // 5300:DMeIDXNotInitialized 사전 빌딩 실패
	

	/* 이체자 색인 테이블 로딩 */
	sprintf(tempDir, "%s/%s", dic_dir, HANJA_VARIANT_TABLE);
	LoadHanjaVariantTable(tempDir);

	/* 한자 --> 한글 변환 테이블 로딩 */
	sprintf(tempDir, "%s/%s", dic_dir, HANJA2HANGUL_TABLE);
	LoadHanjaTable(tempDir);


#ifdef CD_PROC
	// 대역어 사전 로딩
	IDX_LoadCrossTermDic(dic_dir);
#endif
	 //2006.07.03 by mini 성공일경우 리턴값 0 으로 변경
	return 0;//사전 빌딩 성공
}

int IDX_CloseIDX()
{
#ifdef TIME_CHECK
	printf("Total IDX Time : %d\n", total_time / CLOCKS_PER_SEC);
#endif

	ClearDic();
	CloseStopWordSet();
#ifdef CD_PROC
	IDX_CloseCrossTermDic();
#endif

#ifdef SHARED_MEMORY_IDX
	ClearShMem((void **) &idx_words_ptr);
#endif

	return 0; //2006.07.03 by mini 성공일경우 리턴값 0 으로 변경
}

//int IDX_MainProc(unsigned char req, char *data, POSTINFO *PostInfo, int startWordNum, int stem_opt, int hanja_opt)
int IDX_MainProc(unsigned char req, char *data, POSTINFO *PostInfo, int startWordNum, STRUCT_OPTION_IDX opt)
{
	int				PostInfoCnt = 0;
	char			SWID[MAXSWIDLEN + 1];
	int				ret_val;
#ifdef TIME_CHECK
	int cl1, cl2, cl_tot;
#endif
	char			inner_buf[4096];
	char			*ptr;

	StemCheck = opt.stem;
	HanjaFlag = opt.hj_hg;
	IdxBigram = opt.idx_bigram;
	HighLight = opt.highlight;

	IDX_HANJA_PROC_OPTION = opt.hanja;

	StartWordNum = startWordNum;

	dels = opt.dels;
	dCode = opt.dCode;

	idx_offsets = opt.idx_offset;
	off_num = opt.off_num;

	if (req != INDEX_BY_TOKEN)		// 사용자 지정 분리자는 INDEX_BY_TOKEN이 아니면 의미가 없다 
		dels = NULL;
	if (req != INDEX_AS_IS) {			// 삭제대상 코드는 INDEX_AS_IS 아니면 의미가 없다.
	//	dCode = NULL;					// INDEX_BY_TOKEN에서도 사용
		idx_offsets = NULL;
		off_num = 0;
	}

	switch (req) {
		case DO_NOT_INDEX:
			return PostInfoCnt;

		case INDEX_AS_IS:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexAsIs(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

		case INDEX_AS_NUMERIC:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexAsNumeric(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

		case INDEX_BY_TOKEN:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
#ifdef DEBUG
			printf("INDEX_BY_TOKEN(StopCheck=%d)\n", StopCheck);
#endif
			PostInfoCnt = IDX_IndexByToken(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			if (IdxBigram) return IDX_AddIndexBigram(PostInfo, PostInfoCnt);
			else return PostInfoCnt;

		case INDEX_BY_CHAR:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexByChar(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			if (IdxBigram) return IDX_AddIndexBigram(PostInfo, PostInfoCnt);
			else return PostInfoCnt;

		case INDEX_BY_MA:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexByMA(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			if (IdxBigram) return IDX_AddIndexBigram(PostInfo, PostInfoCnt);
			else return PostInfoCnt;

		case INDEX_AS_IS_MA:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexAsIsMA(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

		case INDEX_BY_MIX_MA:
			PostInfoCnt = IDX_IndexByMixMA(data, PostInfo, StopCheck);
			if (IdxBigram) return IDX_AddIndexBigram(PostInfo, PostInfoCnt);
			else return PostInfoCnt;

		case INDEX_BY_MIX_CHAR:
			PostInfoCnt = IDX_IndexByMixChar(data, PostInfo, StopCheck);
			if (IdxBigram) return IDX_AddIndexBigram(PostInfo, PostInfoCnt);
			else return PostInfoCnt;

#ifdef CD_PROC
		case INDEX_BY_CD_MA:
			PostInfoCnt = IDX_IndexByCDMA(data, PostInfo, StopCheck);
			return PostInfoCnt;

		case INDEX_BY_CD_TOKEN:
			PostInfoCnt = IDX_IndexByCDToken(data, PostInfo, StopCheck);
			return PostInfoCnt;
#endif

		case INDEX_DNA:
			PostInfoCnt = IDX_IndexDNA(data, PostInfo, StopCheck);
			return PostInfoCnt;

		case INDEX_PROTEIN:
			PostInfoCnt = IDX_IndexProtein(data, PostInfo, StopCheck);
			return PostInfoCnt;

		case INDEX_TRDNA:
			PostInfoCnt = IDX_IndexTRDNA(data, PostInfo, StopCheck);
			return PostInfoCnt;

		case HANJA_2_HANGUL:
			Hanja2Hangul_UTF8(data, inner_buf);
			if (strlen(inner_buf) > MAXKEYLEN) {
				ptr = inner_buf;
				PostInfoCnt = 0;
				while (1) {
					if (strlen(ptr) < MAXKEYLEN) {
						strcpy(PostInfo[PostInfoCnt].key, ptr);
						PostInfo[PostInfoCnt].keyLen = strlen(ptr);
						PostInfo[PostInfoCnt].psgNum = 0;
						PostInfo[PostInfoCnt].wordNum = PostInfoCnt;
						break;
					} else {
						strncpy(PostInfo[PostInfoCnt].key, ptr, MAXKEYLEN);
						PostInfo[PostInfoCnt].key[MAXKEYLEN] = '\0';
						PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;
						PostInfo[PostInfoCnt].psgNum = 0;
						PostInfo[PostInfoCnt].wordNum = PostInfoCnt;

						ptr += MAXKEYLEN;
						PostInfoCnt++;
					}
				}

				return PostInfoCnt;
			} else {
				strcpy(PostInfo[0].key, inner_buf);
				PostInfo[0].keyLen = strlen(inner_buf);
				PostInfo[0].psgNum = 0;
				PostInfo[0].wordNum = 1;

				return 1;
			}


#if 0
		case INDEX_BY_TOKEN_HANJA:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexByTokenHanja(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

		case INDEX_BY_MA_HANJA:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexByMAHanja(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

		case INDEX_AS_IS_MA_HANJA:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexAsIsMAHanja(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

		case INDEX_BY_CHAR_HANJA:
#ifdef TIME_CHECK
			cl1 = clock();
#endif
			PostInfoCnt = IDX_IndexByCharHanja(data, PostInfo, StopCheck);
#ifdef TIME_CHECK
			cl2 = clock();
			total_time += (cl2 - cl1);
#endif
			return PostInfoCnt;

#endif

		case IDX_SW_REGISTER:
			strncpy(SWID, data, MAXSWIDLEN);
			ConvertSTRtoSWID(SWID);

			ret_val = RegisterStopWordSet(data + MAXSWIDLEN, SWID);
			if (!ret_val)
				return 0;
			return 1;

		case IDX_SW_DISCARD:
			strncpy(SWID, data, MAXSWIDLEN);
			ConvertSTRtoSWID(SWID);
			ret_val = DiscardStopWordSet(SWID);
			if (!ret_val)
				return 0;
			return 1;

		case IDX_SW_ACTIVATE:
			StopCheck = 1;
			strncpy(SWID, data, MAXSWIDLEN);
			ConvertSTRtoSWID(SWID);

			ret_val = ActivateStopWordSet(SWID);
			if (!ret_val)
				return 0;
			return 1;

		case IDX_SW_DEACTIVATE:
			StopCheck = 0;

			return 1;

		case IDX_SW_ID_LIST:
		default:
			return 0;
	}

	return 0;
}

int RegisterSWSet(char *SWID, char *SWSet[], int SWNum)
{
	int ret_val;

	ret_val = RegisterStopWordSetArr(SWID, SWSet, SWNum);
#ifdef DEBUG
	if (ret_val) {
		printf("불용어 등록 성공\n");
	}
#endif

	return ret_val;
}

int ActivateSWSet(char *SWIDs[], int SWIDNum)
{
	int ret_val;

	StopCheck = 1;
	ret_val = ActivateStopWordSets(SWIDs, SWIDNum);

	return ret_val;
}

int DeActivateSWSet()
{
	StopCheck = 0;
	DeActivateStopWordSets();

	return 1;
}

void ConvertSTRtoSWID(char *SWID)
{
	int i = 0;

	while (i < MAXSWIDLEN) {
		if (SWID[i] == ' ')
			break;
		i++;
	}
	SWID[i] = '\0';
}

#if 0

int IDX_ProcDIRE(unsigned char req, char *data, T_RESDATA *RES)
{
	POSTINFO		PostInfo[MAXPOSTINFOSIZE];
	char			ResStr[MAXRESBUFSIZE];
	char			SWID[MAXSWIDLEN];
	char			*OrgPtr = data;
	int			ret_val;
	int			PostInfoCnt = 0;
	int			StopCheck = 0;

	/* StopWordSet ID 분리 */
	if ( (DO_NOT_INDEX <= req && req <= INDEX_BY_CHAR_HANJA) 
			|| (req == IDX_SW_REGISTER || req == IDX_SW_DISCARD) ) {
		strncpy(SWID, data, MAXSWIDLEN);
		ConvertSTRtoSWID(SWID);

		data = data + MAXSWIDLEN;
		if (DO_NOT_INDEX <= req && req <= INDEX_BY_CHAR_HANJA) {
			StopCheck = 1;
			ActivateStopWordSet(SWID);
		}
	}

	switch (req) {
		case DO_NOT_INDEX:
			break;

		case INDEX_AS_IS:
			PostInfoCnt = IDX_IndexAsIs(data, PostInfo, StopCheck);
			break;

		case INDEX_AS_NUMERIC:
			PostInfoCnt = IDX_IndexAsNumeric(data, PostInfo, StopCheck);
			break;

		case INDEX_BY_TOKEN:
			PostInfoCnt = IDX_IndexByToken(data, PostInfo, StopCheck);
			break;

		case INDEX_BY_CHAR:
			PostInfoCnt = IDX_IndexByChar(data, PostInfo, StopCheck);
			break;

		case INDEX_BY_MA:
			PostInfoCnt = IDX_IndexByMA(data, PostInfo, StopCheck);
			break;

		case INDEX_AS_IS_MA:
			PostInfoCnt = IDX_IndexAsIsMA(data, PostInfo, StopCheck);
			break;

		case INDEX_BY_TOKEN_HANJA:
			PostInfoCnt = IDX_IndexByTokenHanja(data, PostInfo, StopCheck);
			break;

		case INDEX_BY_MA_HANJA:
			PostInfoCnt = IDX_IndexByMAHanja(data, PostInfo, StopCheck);
			break;

		case INDEX_AS_IS_MA_HANJA:
			PostInfoCnt = IDX_IndexAsIsMAHanja(data, PostInfo, StopCheck);
			break;

		case INDEX_BY_CHAR_HANJA:
			PostInfoCnt = IDX_IndexByCharHanja(data, PostInfo, StopCheck);
			break;

		case IDX_SW_REGISTER:
		case IDX_SW_DISCARD:
			if (req == IDX_SW_REGISTER)
				ret_val = RegisterStopWordSet(data, SWID);
			else
				ret_val = DiscardStopWordSet(SWID);

			sprintf(ResStr, "%d", ret_val);
			RES->RES_DataSize = strlen(ResStr) + 1;
			RES->RES_Data = strdup(ResStr);

			return ret_val;

		case IDX_SW_ID_LIST:
			ret_val = GetStopWordSetIDs(ResStr);

			if (ret_val) {
				RES->RES_DataSize = strlen(ResStr) + 1;
				RES->RES_Data = strdup(ResStr);
			} else {
				sprintf(ResStr, "%d", ret_val);
				RES->RES_DataSize = strlen(ResStr) + 1;
				RES->RES_Data = strdup(ResStr);
			}

			return ret_val;

		default:
			return 0;
	}

	if (PostInfoCnt) 
		Make_RES_Data_DIRE(PostInfo, PostInfoCnt, RES);
	else {
		sprintf(ResStr, "%d", PostInfoCnt);
		RES->RES_DataSize = strlen(ResStr) + 1;
		RES->RES_Data = strdup(ResStr);
	}

	return PostInfoCnt;
}

void Make_RES_Data_DIRE(POSTINFO *PostInfo, int PostInfoNum, T_RESDATA *RES)
{
	int i, j, old_psg_num;
	char TempData[MAXRESBUFSIZE];

	printf("PostInfoCnt=%d\n", PostInfoNum);

	i = 0;
	TempData[0] = '\0';

	while (i < PostInfoNum && PostInfo[i].psgNum == 0) {
		strcat(TempData, PostInfo[i].key);
		strcat(TempData, DEL_INTER_INDEX);
		strcat(TempData, DEL_INTER_INDEX);
		i++;
	}

	if (i == PostInfoNum) {
		RES->RES_DataSize = strlen(TempData) + 1;
		RES->RES_Data = (char *) strdup((const char *) TempData);

		return;
	}

	strcat(TempData, PostInfo[i].key);
	old_psg_num = PostInfo[i].psgNum;
	i++;
	while (i < PostInfoNum) {
		if (old_psg_num != PostInfo[i].psgNum || old_psg_num == 100) {
			strcat(TempData, DEL_INTER_INDEX);
			if (old_psg_num == 100)
				strcat(TempData, DEL_INTER_INDEX);
			strcat(TempData, PostInfo[i].key);
			old_psg_num = PostInfo[i].psgNum;
		} else {
			strcat(TempData, DEL_INTRA_INDEX);
			strcat(TempData, PostInfo[i].key);
		}
		i++;
	}

	RES->RES_DataSize = strlen(TempData) + 1;
	RES->RES_Data = (char *) strdup((const char *) TempData);
}
#endif

#if 0
/*
 * 색인 타입 : INDEX_BY_MA
 *
 * 토큰 분리가 문제가 될 수 있다.
 * 일단 현재는 색인기 내부의 토큰 분리기를 사용하고...
 * 나중에 이 토큰 분리기를 IDX로 올리는 작업을 수행해야 한다.
 */
int IDX_IndexByMA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int PostInfoCnt = 0;
	int i, j;
	int wordNum = 0;
	int IW_num, ret_val;

	IW_num = GetIndexWord(SecVal, IndexWords);
	for (i = 0; i < IW_num ; i++) {
		for (j = 0; j < IndexWords[i].nIndex; j++) {
			PostInfo[PostInfoCnt].keyLen = strlen(IndexWords[i].IDX[j].str);
			if (PostInfo[PostInfoCnt].keyLen <= 0)
				continue;
			PostInfo[PostInfoCnt].wordNum = wordNum++;
			/*
			 * 복합명사 분석 결과에 대한 처리는 따로 한다.
			 * psgNum을 이용해서...
			 * 복합명사 분석의 결과가 한 어절에 대해서 여러개로 나올 수가 있으므로
			 * 예를 들면,
			 * 정보검색(1)+시스템(1), 정보(2)+검색(2)+시스템(2), ....
			 * 이 값은 색인기 내부에서 loc을 통해서 전달한다.
			 */
			strcpy(PostInfo[PostInfoCnt].key, IndexWords[i].IDX[j].str);
			PostInfo[PostInfoCnt].psgNum = IndexWords[i].IDX[j].loc;
			if (PostInfo[PostInfoCnt].keyLen > MAXKEYLEN)
				PostInfo[PostInfoCnt].keyLen = MAXKEYLEN;

			PostInfoCnt++;
		}
	}

	return PostInfoCnt;
}
#endif
