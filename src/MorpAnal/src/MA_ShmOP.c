/*
 * Copyright (c) 2000
 * Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 * 
 *  #(MA_ShmOP.c)#  SPASIS System
 *
 *  #(Action)#
 *      - 공유메모리 사용을 위한 함수들...
 */
#ifdef SHARED_MEMORY_DIC

#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <MA_ShmOP.h>
/*
 * 공유메모리 사용을 위해서 메모리 할당..
 * 만일 현재 키에 대해서 공유메모리가 존재하면...
 * 그 메모리를 리턴.
 * 아니면 새로운 공유메모리를 리턴.
 * 리턴값 : 새로운 공유메모리가 생성되었으면 1 아니면 0
 */
int GetShMem(key_t sh_key, unsigned int size, void **ptr)
{
	int shmid;
	int ret_val;

	if ((shmid = shmget(sh_key, size, IPC_CREAT|IPC_EXCL|0666)) == -1) {
		/* 공유메모리가 기존에 존재 */
		/* 존재하는 공유메모리 아이디를 가져옴 */
		if ((shmid = shmget(sh_key, size, 0)) == -1) {
			if(sh_key==MAINDIC_KEY) printf("Error:[DICMAIN.DIC]  ");
            else if(sh_key==CNDIC_KEY) printf("Error:[DICCN.DIC]  ");
            else if(sh_key==CNDICCON_KEY) printf("Error:[DICCN.CON]  ");
            else if(sh_key==NTAILDIC_KEY) printf("Error:[DICNTAIL.DIC]  ");
            else if(sh_key==PTAILDIC_KEY) printf("Error:[DICPTAIL.DIC]  ");
            else if(sh_key==BTAILDIC_KEY) printf("Error:[DICBTAIL.DIC]  ");
            else if(sh_key==NTAILDICCON_KEY) printf("Error:[DICNTAIL.CON]  ");
            else if(sh_key==PTAILDICCON_KEY) printf("Error:[DICPTAIL.CON]  ");
            else if(sh_key==BTAILDICCON_KEY) printf("Error:[DICBTAIL.CON]  ");
			else perror("shmget");			
			return -1;//exit(1); //2007.01.09 return하는것으로 변경 by mini
		}
		ret_val = 0;
	} else
		ret_val = 1;

	/* 공유메모리 attach */
	if (( *ptr = shmat(shmid, 0, 0)) == -1) {
		perror("shmat");
		exit(1);
	}

	return ret_val;
}

/* 공유메모리 detach */
/* 성공 : 0, 실패 : -1 */
int ClearShMem(void **ptr)
{
	int ret_val;

	ret_val = shmdt(*ptr);

	return ret_val;
}
#endif
