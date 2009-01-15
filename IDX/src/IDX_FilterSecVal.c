/**********************************************************************
 *			The KRISTAL-2001 System, Version 1.0beta
 * 
 * Developed by Sung Pil Choi (042-828-5107)
 **********************************************************************/
#include <IDX_common.h>

int IDX_FilterSecVal(char *SecVal)
{
	char		*pSec = SecVal;
	int			SecLen;

	/* ��ū �տ� �ִ� �����̳� ���ٱ�ȣ�� ���� */
	while (1) {
		if (*pSec == ' ' || *pSec == '\n') {
			pSec++;
		} else {
			break;
		}
	}

	strcpy(SecVal, pSec);

	SecLen = strlen(SecVal);
	pSec = SecVal + SecLen - 1;


	/* ��ū �ڿ� �ִ� �����̳� ���ٱ�ȣ�� ���� */
	while (1) {
		if (*pSec == ' ' || *pSec == '\n') {
			*pSec = '\0';
			pSec--;
		} else {
			break;
		}
	}

	/* ��ū �߰��� �ִ� ���ٱ�ȣ�� �������� ġȯ */
	pSec = SecVal;
	while (*pSec) {
		if (*pSec == '\n')
			*pSec = ' ';
		pSec++;
	}


	return 1;
}
