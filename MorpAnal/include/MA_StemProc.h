#ifndef _MA_STEMPROC_H_
#define _MA_STEMPROC_H_

#include <MA_Type.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    BYTE *EWordBuffer;       /* buffer for word to be stemmed */
    DWORD loc_End;			/* �м��� �ܾ��� ������ ��ġ */
    DWORD loc_Start;			/* �м��� �ܾ��� ���� ��ġ */
    DWORD GIndex;			/* a general offset into the string */
} tSTEMVAR;

#endif

