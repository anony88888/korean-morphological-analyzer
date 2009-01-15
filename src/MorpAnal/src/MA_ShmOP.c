/*
 * Copyright (c) 2000
 * Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 * 
 *  #(MA_ShmOP.c)#  SPASIS System
 *
 *  #(Action)#
 *      - �����޸� ����� ���� �Լ���...
 */
#ifdef SHARED_MEMORY_DIC

#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <MA_ShmOP.h>
/*
 * �����޸� ����� ���ؼ� �޸� �Ҵ�..
 * ���� ���� Ű�� ���ؼ� �����޸𸮰� �����ϸ�...
 * �� �޸𸮸� ����.
 * �ƴϸ� ���ο� �����޸𸮸� ����.
 * ���ϰ� : ���ο� �����޸𸮰� �����Ǿ����� 1 �ƴϸ� 0
 */
int GetShMem(key_t sh_key, unsigned int size, void **ptr)
{
	int shmid;
	int ret_val;

	if ((shmid = shmget(sh_key, size, IPC_CREAT|IPC_EXCL|0666)) == -1) {
		/* �����޸𸮰� ������ ���� */
		/* �����ϴ� �����޸� ���̵� ������ */
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
			return -1;//exit(1); //2007.01.09 return�ϴ°����� ���� by mini
		}
		ret_val = 0;
	} else
		ret_val = 1;

	/* �����޸� attach */
	if (( *ptr = shmat(shmid, 0, 0)) == -1) {
		perror("shmat");
		exit(1);
	}

	return ret_val;
}

/* �����޸� detach */
/* ���� : 0, ���� : -1 */
int ClearShMem(void **ptr)
{
	int ret_val;

	ret_val = shmdt(*ptr);

	return ret_val;
}
#endif
