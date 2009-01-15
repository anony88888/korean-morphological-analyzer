/*
 * 해쉬 함수 정의....
 * 작성자 : 최성필
 * 작성일 : 2000.05.18
 */

#include <MA_SysHeader.h>
#include <MA_Hash.h>
#include <MA_Type.h>

UDWORD hash(UBYTE *key, UDWORD length)
{
    UDWORD val1, val2, val3;
    UDWORD len;

    len = length;
    val1 = val2 = 0x9e3779b9;
    val3 = 0;

    while (len >= 12) {
	val1 = val1+(key[0]+((UDWORD)key[1]<<8)+((UDWORD)key[2]<<16)+((UDWORD)key[3]<<24));
	val2 = val2+(key[4]+((UDWORD)key[5]<<8)+((UDWORD)key[6]<<16)+((UDWORD)key[7]<<24));
	val3 = val3+(key[8]+((UDWORD)key[9]<<8)+((UDWORD)key[10]<<16)+((UDWORD)key[11]<<24));

	MIX(val1, val2, val3);
	key = key + 12;
	len = len - 12;
    }

    val3 = val3 + length;
    
    switch (len) {
	case 11 : val3 = val3 + ((UDWORD)key[10] << 24);
	case 10 : val3 = val3 + ((UDWORD)key[9]  << 16);
	case 9  : val3 = val3 + ((UDWORD)key[8]  << 8);
	case 8  : val2 = val2 + ((UDWORD)key[7]  << 24);
	case 7  : val2 = val2 + ((UDWORD)key[6]  << 16);
	case 6  : val2 = val2 + ((UDWORD)key[5]  << 8);
	case 5  : val2 = val2 + key[4];
	case 4  : val1 = val1 + ((UDWORD)key[3]  << 24);
	case 3  : val1 = val1 + ((UDWORD)key[2]  << 16);
	case 2  : val1 = val1 + ((UDWORD)key[1]  << 8);
	case 1  : val1 = val1 + key[0];
    }

    MIX(val1, val2, val3);

    return val3;
}
