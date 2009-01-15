/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD),All right reserved.
 *
 *	#(SD_SearchWordInTrieDic.c)#  SPASIS System,     Thu Nov 25 15:34:56 1999
 *
 *	#(Action)#
 *		- ����� ��� ���� Ž������...
 *        �Է� ������ ù ���ڿ� ���� ����� ���ϴ� �Լ�...
 *        �ֻ������� �޸� ����/��� ������ ������ �Է��̹Ƿ�...
 *        ������ �Է����� ù���� ��� ���� ���ؾ� �Ѵ�.
 *        ���������� �߰�....(2000/02/16)
 */
#include <MA_SysHeader.h>
#include <MADIC_Func.h>
#include <MADIC_Josa.h>
#include <MADIC_Eomi.h>
#include <MADIC_Bojo.h>
#include <MA_Jo2Wan.h>

DWORD GetJosaHeaderIndex(UWORD one_char)
{
	DWORD idx;

	if (jo2wan[one_char-0x8442][1] == 0)
		return -1;
	idx = jo2wan[one_char - 0x8442][2];
	return (idx);
/*
	tJEHEADER_IDX *result, key;

	key.code = one_char;
	result = bsearch(&key, FirstJosaIndex, JOSA_INDEX_NUM, sizeof(tJEHEADER_IDX), compare_value);

	if (result)
		return result->idx;
	else
		return -1;
*/
}


DWORD GetEomiHeaderIndex(UWORD one_char)
{
	DWORD idx;

	if (jo2wan[one_char-0x8442][1] == 0)
		return -1;
	idx = jo2wan[one_char - 0x8442][2];
	return (idx);
/*	
	tJEHEADER_IDX *result, key;

	key.code = one_char;
	result = bsearch(&key, FirstEomiIndex, EOMI_INDEX_NUM, sizeof(tJEHEADER_IDX), compare_value);

	if (result)
		return result->idx;
	else
		return -1;
*/
}

DWORD GetBojoHeaderIndex(UWORD one_char)
{
	DWORD idx;

	if (jo2wan[one_char-0x8442][1] == 0)
		return -1;
	idx = jo2wan[one_char - 0x8442][2];
	return (idx);
/*
	tJEHEADER_IDX *result, key;

	key.code = one_char;
	result = bsearch(&key, FirstBojoIndex, BOJO_INDEX_NUM, sizeof(tJEHEADER_IDX), compare_value);

	if (result)
		return result->idx;
	else
		return -1;
*/
}

DWORD GetTailHeaderIndex(UWORD one_char)
{
	DWORD idx;

	if (one_char < 0x8442 || one_char > 0xd3d7)
		return -1;

	if (jo2wan[one_char-0x8442][1] == 0)
		return -1;
	idx = jo2wan[one_char - 0x8442][2];
	return (idx);
/*
	tJEHEADER_IDX *result, key;

	key.code = one_char;
	result = bsearch(&key, FirstBojoIndex, BOJO_INDEX_NUM, sizeof(tJEHEADER_IDX), compare_value);

	if (result)
		return result->idx;
	else
		return -1;
*/
}

DWORD compare_value(tJEHEADER_IDX *val1, tJEHEADER_IDX *val2)
{
	return (val1->code - val2->code);
}
