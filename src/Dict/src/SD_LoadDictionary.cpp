/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_LoadDictionary.c)#  SPASIS System,     Thu Nov 25 13:26:34 1999
 *
 *	#(Action)#
 *		- 바이너리 사전 로딩 함수.
 */
#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_GMacro.h>
#include <MA_HanType.h>
#include <MA_Func.h>
#include <MA_ReturnCode.h>
#include <MADIC_Type.h>
#include <MADIC_Global.h>
#include <MADIC_Func.h>
#include <MA_UtilLib.h>
#include <MA_SearchTailDic.h>

#ifdef SHARED_MEMORY_DIC
#include <MA_ShmOP.h>
#endif

#define MAX_DIC_HEADER_SIZE 1000000
#define MAX_JDIC_HEADER_SIZE 1000
#define MAX_EDIC_HEADER_SIZE 1000
#define MAX_BDIC_HEADER_SIZE 1000

#ifdef SHARED_MEMORY_DIC
BYTE *sh_MAINDIC_ptr;
BYTE *dic_ptr;
DWORD dic_size;
#endif

/*
UBYTE StopList[STOPWORD_NUM][128];
UDWORD SL_Num;
*/

/* 주사전, 조사사전, 어미사전 로딩 함수 */
#ifdef MADLL_EXPORTS
DLLMA_API DWORD LoadDictionary(BYTE *dic_dir)
#else
DWORD LoadDictionary(BYTE *dic_dir)
#endif
{
	FILE *fd_dic;
	DWORD i, ret, ret_val;
	BYTE dic_files[S_BUFLEN];
	//BYTE line[S_BUFLEN];
	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, MAIN_DIC);
#else
	strcat(dic_files, "/");
	strcat(dic_files, MAIN_DIC);
#endif

	UTIL_FileOpen(dic_files, F_READ, EM_EXIT, F_BINARY, &fd_dic);
	ret = UTIL_FileRead(fd_dic, (BYTE *)Dic_Header, F_READ_BULK_PART, sizeof(DIC_HEADER)*HEADER_NUM);
	if (ret == 0)
		return 0;
#ifdef SHARED_MEMORY_DIC
	dic_size = 0;
	for (i = 0; i < HEADER_NUM; i++)
		dic_size += Dic_Header[i].size;

	ret_val = GetShMem(MAINDIC_KEY, dic_size, (BYTE **) &sh_MAINDIC_ptr);
	if (ret_val == -1){
		printf("Check the Dictionary version.\n");
		return 0;
				
	}
	else if (ret_val == 1) {
		/* 공유메모리가 새롭게 생성되었으면 ... */
		dic_ptr = sh_MAINDIC_ptr;
		for (i = 0; i < HEADER_NUM; i++) {
			if (Dic_Header[i].size != 0) {
				fseek(fd_dic, Dic_Header[i].start, SEEK_SET);
				ret_val = fread(dic_ptr, Dic_Header[i].size, 1, fd_dic);
				if (!feof(fd_dic) && ret_val == 0) {
					ClearDic();
					return 0;
				}
				Dic_Roots[i] = (DIC_NODE *) dic_ptr;
				dic_ptr += Dic_Header[i].size;
			}
		}
	} else {
		/* 기존에 공유메모리가 존재하면... */
		dic_ptr = sh_MAINDIC_ptr;
		for (i = 0; i < HEADER_NUM; i++) {
			Dic_Roots[i] = (DIC_NODE *) dic_ptr;
			dic_ptr += Dic_Header[i].size;
		}
	}
#else

	for (i = 0; i < HEADER_NUM; i++) {
		if (Dic_Header[i].size != 0 ) {
			if(Dic_Header[i].size>MAX_DIC_HEADER_SIZE){
				printf("Dic_Header[%d].size:%d\n",i,Dic_Header[i].size);
				printf("the limit value of Dic_Header[].size is %d\n",MAX_DIC_HEADER_SIZE);
				printf("Error:[DICMAIN]  ");
                printf("Check the Dictionary version.\n");
                exit(1);

			}
			Dic_Roots[i] = (DIC_NODE *)MemoryCreate(Dic_Header[i].size + sizeof(DIC_NODE) * 2, EM_EXIT);
			assert(Dic_Roots[i] != NULL);
			UTIL_FileSeek(fd_dic, Dic_Header[i].start, F_SEEK_START);
			ret = UTIL_FileRead(fd_dic, (BYTE *)Dic_Roots[i], F_READ_BULK_PART, Dic_Header[i].size);
			if (!feof(fd_dic) && ret == 0) {
				ClearDic();
				return 0;
			}
		}
	}

#endif

	UTIL_FileClose(fd_dic);
#ifndef VER_LIB
	printf("주사전 로딩 완료... \n");
#endif

	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, JOSA_DIC);
#else
	strcat(dic_files, "/");
	strcat(dic_files, JOSA_DIC);
#endif

	UTIL_FileOpen(dic_files, F_READ, EM_EXIT, F_BINARY, &fd_dic);
	ret = UTIL_FileRead(fd_dic, (BYTE *)JDic_Header, F_READ_BULK_PART, sizeof(DIC_HEADER)*HEADER_NUM);
	if (ret == 0)
		return 0;

	for (i = 0; i < HEADER_NUM; i++) {
		if (JDic_Header[i].size != 0 ) { 
			//2007.01.09
			// 리눅스 외에 로딩된 사전의 경우 Dic_Header[i].size가 매우 큰 수 로 잡혀 
 			// 메모리를 더 이상 잡을 수 없게 하는 오류 발생
			//ex)In MemoryCreate : allocation failure...
			//MAX_EDIC_HEADER_SIZE=500을 경계값으로 이상이 될 경우 비정상적 종료
			if(JDic_Header[i].size > MAX_JDIC_HEADER_SIZE){
				printf("JDic_Header[%d].size:%d\n", i, JDic_Header[i].size);
				printf("the limit value of JDic_Header[].size is %d",MAX_JDIC_HEADER_SIZE);
								
                printf("Error:[DICJOSA]  ");
                printf("Check the Dictionary version.\n");
                exit(1);
			}

			JDic_Roots[i] = (DIC_NODE *)MemoryCreate(JDic_Header[i].size + sizeof(DIC_NODE) * 2, EM_EXIT);
			assert(JDic_Roots[i] != NULL);
			UTIL_FileSeek(fd_dic, JDic_Header[i].start, F_SEEK_START);
			ret = UTIL_FileRead(fd_dic, (BYTE *)JDic_Roots[i], F_READ_BULK_PART, JDic_Header[i].size);
			if (!feof(fd_dic) && ret == 0) {
				ClearDic();
				return 0;
			}
		}
	}
	UTIL_FileClose(fd_dic);
#ifndef VER_LIB
	printf("조사사전 로딩 완료... \n");
#endif

	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, EOMI_DIC);
#else
	strcat(dic_files, "/");
	strcat(dic_files, EOMI_DIC);
#endif

	UTIL_FileOpen(dic_files, F_READ, EM_EXIT, F_BINARY, &fd_dic);
	ret = UTIL_FileRead(fd_dic, (BYTE *)EDic_Header, F_READ_BULK_PART, sizeof(DIC_HEADER)*HEADER_NUM);
	if (ret == 0)
		return 0;

	for (i = 0; i < HEADER_NUM; i++) {
		if (EDic_Header[i].size != 0 ) { 
			//2007.01.09
            // 리눅스 외에 로딩된 사전의 경우 Dic_Header[i].size가 매우 큰 수 로 잡혀 
            // 메모리를 더 이상 잡을 수 없게 하는 오류 발생
            //ex)In MemoryCreate : allocation failure...
			//MAX_EDIC_HEADER_SIZE=500을 경계값으로 이상이 될 경우 비정상적 종료
            if(EDic_Header[i].size > MAX_EDIC_HEADER_SIZE){
				printf("EDic_Header[%d].size:%d\n", i ,EDic_Header[i].size);
				printf("the limit value of EDic_Header[].size is %d",MAX_EDIC_HEADER_SIZE);				
                printf("Error:[DICEOMI]  ");
                printf("Check the Dictionary version.\n");
                exit(1);
            }

			EDic_Roots[i] = (DIC_NODE *)MemoryCreate(EDic_Header[i].size + sizeof(DIC_NODE) * 2, EM_EXIT);
			assert(EDic_Roots[i] != NULL);
			UTIL_FileSeek(fd_dic, EDic_Header[i].start, F_SEEK_START);
			ret = UTIL_FileRead(fd_dic, (BYTE *)EDic_Roots[i], F_READ_BULK_PART, EDic_Header[i].size);
			if (!feof(fd_dic) && ret == 0) {
				ClearDic();
				return 0;
			}
		}
	}
	UTIL_FileClose(fd_dic);
#ifndef VER_LIB
	printf("어미사전 로딩 완료... \n");
#endif
	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, BOJO_DIC);
#else
	strcat(dic_files, "/");
	strcat(dic_files, BOJO_DIC);
#endif

	UTIL_FileOpen(dic_files, F_READ, EM_EXIT, F_BINARY, &fd_dic);
	ret = UTIL_FileRead(fd_dic, (BYTE *)BDic_Header, F_READ_BULK_PART, sizeof(DIC_HEADER)*HEADER_NUM);
	
	if (ret == 0)
		return 0;

	for (i = 0; i < HEADER_NUM; i++) {
		if (BDic_Header[i].size != 0 ) { 
			if(BDic_Header[i].size > MAX_BDIC_HEADER_SIZE){
                printf("Error:[DICBOJO]  ");
                printf("Check the Dictionary version.\n");
                exit (1);
            }

			BDic_Roots[i] = (DIC_NODE *)MemoryCreate(BDic_Header[i].size + sizeof(DIC_NODE) * 2, EM_EXIT);
			assert(BDic_Roots[i] != NULL);
			UTIL_FileSeek(fd_dic, BDic_Header[i].start, F_SEEK_START);
			ret = UTIL_FileRead(fd_dic, (BYTE *)BDic_Roots[i], F_READ_BULK_PART, BDic_Header[i].size);
			if (!feof(fd_dic) && ret == 0) {
				ClearDic();
				return 0;
			}
		}
	}
	UTIL_FileClose(fd_dic);
#ifndef VER_LIB
	printf("보조용언사전 로딩 완료... \n");
#endif
	InitTAILDicHeader();
	ret = LoadTAILDic(dic_dir);
	if (ret == 0)
		return 0;
#ifndef VER_LIB
	printf("형식형태소 패턴사전 로딩 완료... \n");
#endif

/*
	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, TAIL_DIC);
#else
	strcat(dic_files, "/");
	strcat(dic_files, TAIL_DIC);
#endif

	UTIL_FileOpen(dic_files, F_READ, EM_EXIT, F_BINARY, &fd_dic);
	ret = UTIL_FileRead(fd_dic, (BYTE *)Tail_Dic_Header, F_READ_BULK_PART, sizeof(DIC_HEADER) * HEADER_NUM);
	if (ret == 0)
		return 0;

	for (i = 0; i < HEADER_NUM; i++) {
		if (Tail_Dic_Header[i].size != 0 ) { 
			Tail_Dic_Roots[i] = (TAIL_DIC_NODE *)MemoryCreate(Tail_Dic_Header[i].size + sizeof(TAIL_DIC_NODE) * 2, EM_EXIT);
			assert(Tail_Dic_Roots[i] != NULL);
			UTIL_FileSeek(fd_dic, Tail_Dic_Header[i].start, F_SEEK_START);
			ret = UTIL_FileRead(fd_dic, (BYTE *)Tail_Dic_Roots[i], F_READ_BULK_PART, Tail_Dic_Header[i].size);
			if (!feof(fd_dic) && ret == 0) {
				ClearDic();
				return 0;
			}
		}
	}
	UTIL_FileClose(fd_dic);
#ifndef VER_LIB
	printf("형식형태소 패턴사전 로딩 완료... \n");
#endif
*/

#ifdef CORPUS_DIC_SEARCH
	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, CORPUS_DIC);
#else
	strcat(dic_files, "/");
	strcat(dic_files, CORPUS_DIC);
#endif
	UTIL_FileOpen(dic_files, F_READ, EM_EXIT, F_BINARY, &fd_dic);
	ret = LoadCorpusDic(fd_dic);
	if (ret != 1)
	    return 0;
	UTIL_FileClose(fd_dic);
#ifndef VER_LIB
	printf("말뭉치 사전 로딩 완료...\n");
#endif
#endif
#ifndef KRISTAL_JOHAB_API
	if (InitStopCheck(dic_dir) == 0)
		return 0;
#endif
/*

	strcpy(dic_files, dic_dir);
#ifdef WIN32
	strcat(dic_files, "\\");
	strcat(dic_files, STOPWORD);
#else
	strcat(dic_files, "/");
	strcat(dic_files, STOPWORD);
#endif

	fd_dic = fopen(dic_files, "r");
	if (fd_dic == NULL) 
		return 0;
	SL_Num = 0;
	while (fgets(line, VS_BUFLEN, fd_dic)) {
		line[strlen(line)-1] = '\0';
		strcpy(StopList[SL_Num++], line);
	}
	fclose(fd_dic);
*/
#ifdef COMP_NOUN_DIC_CHECK
	/* 
	 * 복합명사 기분석 사전 로딩
	 */
	ret = LoadCNDic(dic_dir);
	if (ret != 1)
	    return 0;
#endif

	/*
	 * 사용자 사전 로팅
	 */
	ret = LoadUserDic(dic_dir);
	//사용자 기분석 사전 로딩
#ifdef USER_ANSDIC_CHECK
	ret = LoadUserAnsDic(dic_dir);
#endif
	return 1;
} /* End of LoadDictionary */
