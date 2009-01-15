#ifndef _MADIC_FUNC_H_
#define _MADIC_FUNC_H_

#include <MA_Type.h>
#include <MA_HanType.h>
#include <MADIC_Type.h>

DWORD BuildDic(BYTE *dic_file, BYTE *dic_name);
#ifdef MADLL_EXPORTS
DLLMA_API DWORD ClearDic();
#else
DWORD ClearDic();
#endif
#ifdef MADLL_EXPORTS
DLLMA_API tVOID InitDicHeader();
#else
tVOID InitDicHeader();
#endif
DWORD InsertCharInTrieMiddle(HANGUL h_char, DWORD g_idx, DIC_HEADER *header, UDWORD index);
DWORD InsertStrInTrieEnd(HANGUL *han_str, DWORD len, DWORD g_idx, DIC_HEADER *header, BYTE info);
WORD InsertWord(BYTE *word, BYTE info);
DWORD InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, BYTE info);
DWORD MakeHanBuf(UBYTE *hangul_str, HANGUL *han_buf, UWORD *head_idx);
DWORD Wan2Jo(UBYTE *str, HANGUL *han_buf);
UWORD GetNoJongIndex(DWORD header_index);
DWORD OutputToFile(BYTE *outfname);
WORD SearchCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index);
DWORD GetJosaHeaderIndex(UWORD one_char);
DWORD GetEomiHeaderIndex(UWORD one_char);
DWORD GetBojoHeaderIndex(UWORD one_char);
DWORD GetTailHeaderIndex(UWORD one_char);
DWORD compare_value(tJEHEADER_IDX *val1, tJEHEADER_IDX *val2);
#ifdef MULTI_DIC_INFO
DWORD SearchJosaInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, JEDIC_RESULT *result, UWORD *res_idx);
#else
DWORD SearchJosaInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx);
#endif
#ifdef MULTI_DIC_INFO
DWORD SearchEomiInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, JEDIC_RESULT *result, UWORD *res_idx);
#else
DWORD SearchEomiInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx);
#endif
#ifdef MULTI_DIC_INFO
DWORD SearchBojoInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, JEDIC_RESULT *result, UWORD *res_idx);
#else
DWORD SearchBojoInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx);
#endif
#ifdef MADLL_EXPORTS
DLLMA_API DWORD LoadDictionary(BYTE *dic_dir);
#else
DWORD LoadDictionary(BYTE *dic_dir);

#endif
DWORD SearchDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, DIC_RESULT *result, UWORD *res_idx);
#ifdef MULTI_DIC_INFO
DWORD SearchJosaDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, JEDIC_RESULT *result, UWORD *res_idx);
#else
DWORD SearchJosaDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, DIC_RESULT *result, UWORD *res_idx);
#endif
#ifdef MULTI_DIC_INFO
DWORD SearchEomiDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, JEDIC_RESULT *result, UWORD *res_idx);
#else
DWORD SearchEomiDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, DIC_RESULT *result, UWORD *res_idx);
#endif
#ifdef MULTI_DIC_INFO
DWORD SearchBojoDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, JEDIC_RESULT *result, UWORD *res_idx);
#else
DWORD SearchBojoDic(HANGUL *h_word, UWORD h_word_len, UWORD first_jong_only, DIC_RESULT *result, UWORD *res_idx);
#endif
WORD SearchJosaCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index);
WORD SearchEomiCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index);
WORD SearchBojoCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index);
DWORD SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx);

/**********  사용자 사전 관련 함수 ************/
tVOID InitUserDicHeader();
DWORD LoadUserDic(BYTE *dic_dir);
DWORD UD_InsertCharInTrieMiddle(HANGUL h_char, DWORD g_idx, DIC_HEADER *header, UDWORD index);
DWORD UD_InsertStrInTrieEnd(HANGUL *han_str, DWORD len, DWORD g_idx, DIC_HEADER *header, BYTE info);
WORD  UD_InsertWord(BYTE *word, BYTE info);
DWORD UD_InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, BYTE info);
WORD  UD_SearchCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index);
DWORD UD_SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, DIC_RESULT *result, UWORD *res_idx);
DWORD SearchUserDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, DIC_RESULT *result, UWORD *res_idx);
/*********사용자 정답사전 관련 함수 *******/
tVOID InitUserAnsDicHeader();
DWORD LoadUserAnsDic(BYTE *dic_dir);
DWORD UAD_InsertCharInTrieMiddle(HANGUL h_char, DWORD g_idx, DIC_HEADER *header, UDWORD index);
DWORD UAD_InsertStrInTrieEnd(HANGUL *han_str, DWORD len, DWORD g_idx, DIC_HEADER *header, UDWORD StartIdx, UBYTE InfoLen);
WORD  UAD_InsertWord(BYTE *word,  UDWORD StartIdx, UBYTE InfoLen);
DWORD UAD_InsertWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx,  UDWORD StartIdx, UBYTE InfoLen);
WORD  UAD_SearchCharInCurrentLevel(HANGUL one_char, DWORD g_idx, DWORD *index);
DWORD UAD_SearchWordInTrieDic(HANGUL *h_word, DWORD len, DWORD h_idx, USERDIC_RESULT *result, UWORD *res_idx);
DWORD SearchUserAnsDic(HANGUL *h_word, UWORD h_word_len, UWORD h_idx, USERDIC_RESULT *result, UWORD *res_idx);	
DWORD CheckUserAnswerDic(HANGUL *hword, UWORD hword_len, UWORD h_idx, tUADMORP_RESULT *UADMorpRes, UWORD *UADMorpRes_Index);
DWORD GetUADContent(UDWORD s_idx, UBYTE len, UBYTE *Content);


#endif

