// test_idx.cpp : Defines the entry point for the console application.
//

#include <stdio.h> 
#include <cstring> 
#include <string>
#include <iostream>
#include <IDX_common.h> 
#include <IDX_user.h> 
//#include <iconv_str.h> 

//#define KRISTAL_DIR  "/raid1/k2000/K2000" 
#define KRISTAL_DIR  "..\\data" 

POSTINFO postInfo[MAXPOSTINFOSIZE]; 

void main(int argc, char **argv) 
{ 
	FILE *fd_in; 
	FILE *fd_out; 
	char line[10000]; 
	std::string src, dest; 
	int PostInfoNum; 

	if (argc != 2)
	{
		printf("CheckData <in_file>\n"); 
		exit(1); 
	}

	fd_in = fopen(argv[1], "rt"); 
	if (fd_in == NULL)  
	{ 
		exit(1); 
	} 

	fd_out = fopen("out.txt", "w"); 
	if (fd_out == NULL)  
	{ 
		exit(1); 
	} 

	int ret_val = IDX_InitIDX(KRISTAL_DIR); 

	if (ret_val != 0) exit(1); 

	// 이  중간에  불용어  관련  함수를  호출하면  됨. 
	// RegisterSWSet 
	// ActivateSWSet 

	STRUCT_OPTION_IDX opt;
	opt.highlight = 0;
	opt.stem = 1;
	opt.hanja = 1;
	opt.hj_hg = 0;
	opt.idx_bigram = 0;
	opt.dels = 0;
	opt.dCode = 0;

	while (fgets(line, 10000, fd_in))   
	{ 
		src = (const char *) line; 
		//EUCKR_TO_UTF8(src, dest);  // utf-8 로  변환 
		PostInfoNum = IDX_MainProc(INDEX_BY_MA, (char *) src.c_str(), postInfo, 0, opt); 
		//PostInfoNum = IDX_MainProc(INDEX_BY_MIX_MA, (char *) src.c_str(), postInfo, 0, opt); 
		for (int i = 0; i < PostInfoNum; i++)   
		{ 
			src = (const char *)postInfo[i].key; 
			//UTF8_TO_EUCKR(src, dest);  // 결과를  다시 euc-kr 로  변환 
			std::cout << src << "\n"; 
			fputs(src.c_str(), fd_out);
			fputs("\n", fd_out);
		} 
	} 
	fclose(fd_in); 
	fclose(fd_out); 

	// DeActivateSWSet
	IDX_CloseIDX(); 
} 

