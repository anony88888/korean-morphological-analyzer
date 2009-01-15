/*
 *	Copyright (c) 2000
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(MA_MorpAnal.c)#  SPASIS System,     2000.01.28
 *
 *	#(Action)#
 *		- 형태소 분석 모듈 선언
 */
#ifndef _MA_FUNC_H_
#define _MA_FUNC_H_

#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>
#include <MA_Interface.h>
#include <MA_StemProc.h>

DWORD AddInPreBuffer(UBYTE *word, UWORD token);
DWORD GetTokenFromPreBuffer(UBYTE *word);
tVOID InitPreBuffer(UBYTE *ma_buf);
tVOID InitPostBuffer();
DWORD NextWord(UBYTE *word);
tVOID AddInPostBuffer(HANGUL *hword, UWORD hword_len, UWORD flag, UWORD token);
DWORD Ref_PostWord(DWORD Offset, HANGUL *hword, DWORD *hword_len);
DWORD Ref_PreWord(DWORD Offset, HANGUL *hword, DWORD *hword_len);
DWORD GetNextToken(UBYTE *token);

#ifdef COMP_NOUN_DIC_CHECK
DWORD CheckCompNounWord(HANGUL *hword, UWORD hword_len, UWORD h_idx, tCNMORP_RESULT *CNMorpRes, UWORD *CNMorpRes_Index);
DWORD FilterCNIndexWord(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index, INDEX_WORD *IDX_words);
DWORD CNOutputMAResult(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index, DWORD outFlag, FILE *fd);
DWORD ConvertCNInfoToDicInfo(BYTE CNInfo, BYTE *DicInfo);
DWORD ConvertCNInfoToNewDicInfo(BYTE CNInfo, BYTE *DicInfo);
DWORD CopyCNMAResultToMorpResult(tCNMORP_RESULT *CNMorpRes, UWORD CNMorpRes_Index);
#endif

DWORD compare_word(const tVOID *item1, const tVOID *item2);
DWORD compare_code0(const tVOID *code1, const tVOID *code2);
DWORD compare_code1(const tVOID *code1, const tVOID *code2);
DWORD compare_code2(const tVOID *code1, const tVOID *code2);

DWORD CheckCompNoun(HANGUL *h_word, UWORD h_word_len, HANGUL pre_char, UWORD info);

DWORD LoadCorpusDic(FILE *fd_cordic);
tVOID *FindCorpusDic(UBYTE *key);
DWORD ClearCorpusDic();
UDWORD hash(UBYTE *key, UDWORD length);

DWORD CheckEomi(HANGUL *h_word, UWORD h_word_len, WORD first_jong_only);
DWORD IsFirstPreEomiChar(HANGUL one_char);
DWORD IsFirstAEomiChar(HANGUL one_char);
DWORD IsFirstEoEomiChar(HANGUL one_char);

#ifdef SUSA_AS_INDEX
DWORD FilterIndexWord(INDEX_WORD *index_words, tMORP_RESULT *sMorpResult, UWORD sMorpRes_Index);
#else
DWORD FilterIndexWord(INDEX_WORD *index_words);
#endif
DWORD compare_index_str(INDEX_ITEM *idx1, INDEX_ITEM *idx2);
tVOID ReGenMAResult(DWORD flag, FILE *fd, tMORP_RESULT *sMorpResult, UWORD sMorpResult_Index);

UWORD Hj2HgProc(H_CHAR *han_char);

DWORD CheckIda(HANGUL *h_word, UWORD h_word_len, UWORD jong);

DWORD S_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len);
DWORD D_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len);
DWORD B_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos, UWORD *jong);
DWORD H_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos, UWORD *jong);
DWORD RUE_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *s_pos);
DWORD EU_IrrProc(HANGUL *h_word, UWORD h_word_len, UWORD pre_morp_len, UWORD *jong, UWORD *new_len);

DWORD CheckJosa(HANGUL *h_word, UWORD j_pos, UWORD jong);
DWORD CheckJosaUnknown(HANGUL *h_word, UWORD j_pos, UWORD jong);

DWORD KAnalysisWord(HANGUL *h_word, UWORD h_word_len, DIC_RESULT *dic_result, UWORD dic_res_idx, DWORD mode);

#ifndef MADLL_EXPORTS
#ifndef VER_LIB
DWORD MainMAProc(UBYTE *ma_buf);
#endif
#endif

#ifdef MADLL_EXPORTS
DLLMA_API DWORD GetIndexWord(unsigned char *ma_buf, INDEX_WORD *idx_words);
#else
DWORD GetIndexWord(UBYTE *ma_buf, INDEX_WORD *idx_words);
#endif

#ifndef MADLL_EXPORTS
#ifndef VER_LIB
DWORD MorpAnal(UBYTE *word);
#endif
#endif
DWORD ExtractIndexWord(UBYTE *word, INDEX_WORD *Index);
DWORD ExtractEngIndexWord(BYTE *word, INDEX_WORD *Index);
DWORD TopicMorpAnal(HANGUL *hword, UWORD hword_len, DWORD mode, DWORD jong);

#ifdef COMP_NOUN_DIC_CHECK
DWORD GetCNContent(UDWORD s_idx, UBYTE len, UBYTE *Content);
DWORD SearchCNDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, CNDIC_RESULT *result, UWORD *res_idx);
WORD SearchCharInCurrentLevelCN(HANGUL one_char, DWORD g_idx, DWORD *index);
DWORD SearchWordInTrieDicCN(HANGUL *h_word, DWORD len, DWORD h_idx, CNDIC_RESULT *result, UWORD *res_idx);
tVOID InitCNDicHeader();
DWORD LoadCNDic(BYTE *dic_dir);
DWORD ClearCNDic();
#endif

#ifdef USER_ANSDIC_CHECK
DWORD CopyUserAnsDicResultToMorpResult(tUADMORP_RESULT *UADMorpRes, UWORD UADMorpRes_Index);
//DWORD CheckUserAnswerDic(HANGUL *hword, UWORD hword_len, UWORD h_idx, tUADMORP_RESULT *UADMorpRes, UWORD *UADMorpRes_Index);
//DWORD LoadUserAnsDic(BYTE *dic_dir);
#endif 


/*
DWORD SearchTailDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, TAIL_DIC_RESULT *result, UWORD *res_idx);
WORD SearchCharInCurrentLevelTail(HANGUL one_char, DWORD g_idx, DWORD *index);
DWORD SearchWordInTrieDicTail(HANGUL *h_word, DWORD len, DWORD h_idx, TAIL_DIC_RESULT *result, UWORD *res_idx);
*/

DWORD cons(DWORD i, tSTEMVAR *sv);
DWORD m(tSTEMVAR *sv);
DWORD vowelinstem(tSTEMVAR *sv);
DWORD doublec(DWORD i, tSTEMVAR *sv);
DWORD cvc(DWORD i, tSTEMVAR *sv);
DWORD ends(BYTE *str, tSTEMVAR *sv);
tVOID setto(BYTE *str, tSTEMVAR *sv);
tVOID r(BYTE *str, tSTEMVAR *sv);
tVOID step1ab(tSTEMVAR *sv);
tVOID step1c(tSTEMVAR *sv);
tVOID step2(tSTEMVAR *sv);
tVOID step3(tSTEMVAR *sv);
tVOID step4(tSTEMVAR *sv);
tVOID step5(tSTEMVAR *sv);
DWORD StemWord(BYTE *pWord, DWORD start_i, DWORD end_i);

DWORD CheckSusaWord(HANGUL *hword, DWORD hword_len, UBYTE *word, tMORP_RESULT *sMorpResult, UWORD *sMorpResult_Index);
DWORD SusaSearch(UBYTE *word, DWORD *dic_ret, DWORD *dic_ret_idx);
DWORD SusaUnitSearch(HANGUL *hword, DWORD hword_len, UWORD *idx);
DWORD CheckSusa(UBYTE *word, HANGUL *hword, DWORD hword_len,
                DWORD mode, DWORD *dres, DWORD dres_idx, tMORP_RESULT *sMorpResult, UWORD *sMorpResult_Index);

tVOID ReverseWord(HANGUL *dest, HANGUL *src, UWORD src_len);
DWORD GetIndexFromUnknownWord(HANGUL *h_word, UWORD h_word_len, INDEX_WORD *Index);

DWORD VAJubSaProc(HANGUL *h_word, UWORD h_word_len, UWORD info);
DWORD CheckDabDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);
DWORD CheckRobDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);
DWORD CheckSiKiDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);
DWORD CheckDangHaDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);
DWORD CheckDoiDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);
DWORD CheckHaDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);
DWORD CheckSeuRubDa(HANGUL *h_word, UWORD h_word_len, UWORD jong);

#endif

