#ifndef _MA_SHMOP_H_
#define _MA_SHMOP_H_

#ifdef CD_PROC

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define CNDIC_KEY			(key_t) 0x10
#define CNDICCON_KEY		(key_t) 0x20
#define MAINDIC_KEY			(key_t) 0x30
#define INDEXBUF_KEY		(key_t) 0x40

#define NTAILDIC_KEY		(key_t) 0x50
#define PTAILDIC_KEY		(key_t) 0x60
#define BTAILDIC_KEY		(key_t) 0x70

#define NTAILDICCON_KEY		(key_t) 0x80
#define PTAILDICCON_KEY		(key_t) 0x90
#define BTAILDICCON_KEY		(key_t) 0x100

int GetShMem(key_t sh_key, unsigned int size, void **ptr);
int ClearShMem(void **ptr);

#endif

#endif
