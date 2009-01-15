/* 이 헤더파일은 단지 HS_HashProc.c를 위해서 만들어진 것임 
 * 다른 모듈에는 절대로 Include 하지 말것...
 */

#ifndef _HS_HASH_H_
#define _HS_HASH_H_

#include <MA_Type.h>

#define MAXKEYSIZE		31
#define MAXDATASIZE		100

#define HASHTABLESIZE		1048576
#define HASHMASK		0x000fffff
/*
#define HASHTABLESIZE		524287
#define HASHMASK		0x0007ffff
*/

typedef struct hashitem {
    UBYTE key[MAXKEYSIZE];		/* Unique Key */
    UBYTE data[MAXDATASIZE];			/* Data */
} tHASHITEM;

typedef struct datuminfo {
    UWORD Item_num;
    tHASHITEM *Item;
} tDATUMINFO;

#define MIX(a,b,c)\
{\
    a=a-b;  a=a-c;  a=a^(c>>13);\
    b=b-c;  b=b-a;  b=b^(a<<8);\
    c=c-a;  c=c-b;  c=c^(b>>13);\
    a=a-b;  a=a-c;  a=a^(c>>12);\
    b=b-c;  b=b-a;  b=b^(a<<16);\
    c=c-a;  c=c-b;  c=c^(b>>5);\
    a=a-b;  a=a-c;  a=a^(c>>3);\
    b=b-c;  b=b-a;  b=b^(a<<10);\
    c=c-a;  c=c-b;  c=c^(b>>15);\
}

#endif

