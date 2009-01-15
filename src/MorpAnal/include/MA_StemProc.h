#ifndef _MA_STEMPROC_H_
#define _MA_STEMPROC_H_

#include <MA_Type.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    BYTE *EWordBuffer;       /* buffer for word to be stemmed */
    DWORD loc_End;			/* 분석할 단어의 마지막 위치 */
    DWORD loc_Start;			/* 분석할 단어의 시작 위치 */
    DWORD GIndex;			/* a general offset into the string */
} tSTEMVAR;

#endif

