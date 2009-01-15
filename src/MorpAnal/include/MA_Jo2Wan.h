#ifndef _MA_JO2WAN_H_
#define _MA_JO2WAN_H_

DWORD ConvertJo2Wan(HANGUL *h_word, UWORD h_word_len, UBYTE *wan_str);
DWORD ConvertWan2Jo(UBYTE *w_str, HANGUL *j_str);

extern UWORD jo2wan[][3];

#endif

