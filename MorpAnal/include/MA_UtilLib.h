#ifndef _MA_UTIL_LIB_H_
#define _MA_UTIL_LIB_H_

#include <MA_Memory.h>

tVOID UTIL_CleanStr(BYTE *str);
tVOID UTIL_FileClose(FILE *fd);
UWORD UTIL_FileOpen(BYTE *fname, UWORD mode, UWORD exec_mode, UWORD file_mode, FILE **fd);
DWORD UTIL_FileRead(FILE *fd, BYTE *r_buf, WORD mode, DWORD size);
DWORD UTIL_FileSeek(FILE *fd, DWORD idx, WORD pos);
DWORD UTIL_FileTell(FILE *fd);
UDWORD UTIL_FileWrite(BYTE *buffer, DWORD nitem, DWORD item_size, FILE *fd);
tMEMORY * MemoryCreate(UDWORD bytes, DWORD mode);
tVOID MemoryDestroy(tMEMORY *block);
tMEMORY* MemoryMove(tMEMORY *dest, tMEMORY *src, UDWORD size);
tMEMORY* MemoryAppend(tMEMORY *block, UDWORD bytes);
tMEMORY* MemoryDelete(tMEMORY *block, UDWORD bytes);

#endif /* _MA_UTIL_LIB_H_ */

