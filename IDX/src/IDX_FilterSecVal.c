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

	/* 토큰 앞에 있는 공란이나 새줄기호를 삭제 */
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


	/* 토큰 뒤에 있는 공란이나 새줄기호를 삭제 */
	while (1) {
		if (*pSec == ' ' || *pSec == '\n') {
			*pSec = '\0';
			pSec--;
		} else {
			break;
		}
	}

	/* 토큰 중간에 있는 새줄기호를 공란으로 치환 */
	pSec = SecVal;
	while (*pSec) {
		if (*pSec == '\n')
			*pSec = ' ';
		pSec++;
	}


	return 1;
}
