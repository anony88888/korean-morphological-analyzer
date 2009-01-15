/*
 * IDX commmon variables, function declarations, types
 */
#ifndef _IDX_COMMON_H_
#define _IDX_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <IDX_user.h>
#include <ConvertUTF.h>

#define	SYS_MADICTDIRECTORY	"k_dic"

//#define MAXPOSTINFOSIZE		50000
//#define MAXPOSTINFOSIZE		100000
//#define MAXPOSTINFOSIZE		200000
//#define MAXPOSTINFOSIZE		500000
#define MAXPOSTINFOSIZE		1000000
#define MAXINDEXWORDS		4000
#define MAXRESBUFSIZE		10000
#define MAXTEMPBUFSIZE		100000
#define MAXTOKENLEN			50000

/* 색인 관련 */
int IDX_IndexAsIs(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexAsNumeric(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByChar(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByToken(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByMA(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexAsIsMA(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByTokenHanja(char *SecVal, POSTINFO *PostInfo, int StopCheck);
/*
int IDX_IndexByMAHanja(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexAsIsMAHanja(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByCharHanja(char *SecVal, POSTINFO *PostInfo, int StopCheck);
*/
int IDX_IndexByMixMA(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByMixChar(char *SecVal, POSTINFO *PostInfo, int StopCheck);

int IDX_IndexByCDMA(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexByCDToken(char *SecVal, POSTINFO *PostInfo, int StopCheck);

int IDX_IndexDNA(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexTRDNA(char *SecVal, POSTINFO *PostInfo, int StopCheck);
int IDX_IndexProtein(char *SecVal, POSTINFO *PostInfo, int StopCheck);

int IDX_FilterSecVal(char *SecVal);
int IDX_TokenIndexByToken(char **SecPtr, char *TokBuf);
int IDX_TokenIndexByChar(char **SecPtr, char *TokBuf);

/* 스태밍 관련 */
void IDX_strip_affixes (char *string, int *pLen );

/* 불용어 관리 모듈 */
int InitStopWordSet();
int CloseStopWordSet();
int RegisterStopWordSet(char *SWBuf, char *SWID);
int GetStopWordSetIDs(char *SWIDs);
int CountSW(char *buf);
int DiscardStopWordSet(char *ID);
int FindStopWordSet(char *ID);
int ReturnUnusedStopWordSetIndex();
int ActivateStopWordSet(char *ID);
int compare_switem(const void *i1, const void *i2);
int IDX_FindStopWord(char *word);
int RegisterStopWordSetArr(char *SWID, char *SWBuf[], int SWNum);
int ActivateStopWordSets(char *IDs[], int SWIDNum);
int DeActivateStopWordSets();

void ConvertSTRtoSWID(char *SWID);

/* 한글-한자 변환 관련 */
void Hanja2Hangul(char *Buffer);
void Hanja2Hangul_UTF8(unsigned char *src, unsigned char *dest);
void Hanja2Hangul_UCS4(UTF32 *src, int src_len, UTF32 *dest);
int CodeType(unsigned char hbyte, unsigned char lbyte);
void Hj2HgCode(unsigned char *hbyte, unsigned char *lbyte);
void strlower(char *string); /* small capitalize a string */

int DuemConv(char *src, char *dest);

/* 대역어 사전 변환 관련... */
int IDX_LoadCrossTermDic(char *dic_dir);
int IDX_CloseCrossTermDic();
int IDX_SearchCrossDic(char *term, char *result);
int IDX_SearchCrossDicEng2Kor(char *term, char *result);
int IDX_SearchCrossDicKor2Eng(char *term, char *result);
int compare_terms(void *t1, void *t2);
int IDX_CheckCrossDic(POSTINFO *PrevIndex, POSTINFO *CurrIndex, POSTINFO *PostInfo, int flag);

/* 토큰 관리 */
int isHanjaExist(char *str);
void InitTokenizer(unsigned char *doc);
int GetNextTokenChar(UTF32 *tok);
int GetNextToken(UTF32 *tok, int *len, int opt);

/* 유니코드 변환 관련 */
unsigned int ucs2_to_johab(unsigned int src);
unsigned int johab_to_ucs2(unsigned int src);
int IDX_UTF8toUTF32(unsigned char *utf8_val, unsigned int *utf32_val, unsigned int *utf32_len); /* UTF-8 ---> UTF-32 */
int IDX_UTF32toUTF8(unsigned int *utf32_val, unsigned int utf32_len, unsigned char *utf8_val); /* UTF-32 ---> UTF-8 */

/* 색인어 Bi-gram 추가 함수 */
int IDX_AddIndexBigram(POSTINFO *PostInfo, int PostInfoCnt);


#endif
