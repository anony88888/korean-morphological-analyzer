#include <MA_SysHeader.h>
#include <MA_Type.h>
#include <MA_Hash.h>

static tDATUMINFO *_HashTable[HASHTABLESIZE];
static UDWORD *HashValueTable;

DWORD LoadCorpusDic(FILE *fd_cordic)
{
    UDWORD hash_cnt, hash_value;
    UWORD item_num;
    DWORD i;

    fread(&hash_cnt, sizeof(UDWORD), 1, fd_cordic);
    HashValueTable = (UDWORD *) malloc(sizeof(UDWORD) * hash_cnt);
    if (fread(HashValueTable, sizeof(UDWORD), hash_cnt, fd_cordic) != hash_cnt) {
	printf("Error...(1)\n");
	return -1;
    }

    for (i = 0; i < hash_cnt; i++) {
	hash_value = HashValueTable[i];

	_HashTable[hash_value] = (tDATUMINFO *) malloc(sizeof(tDATUMINFO));
	if (_HashTable[hash_value] == NULL) {
	    printf("Memory Allocation Error...(2)\n");
	    break;
	}
	fread(&item_num, sizeof(UWORD), 1, fd_cordic);

	_HashTable[hash_value]->Item = (tHASHITEM *) malloc(sizeof(tHASHITEM) * item_num);
	if (_HashTable[hash_value]->Item == NULL) {
	    printf("Memory Allocation Error...(3)\n");
	    break;
	}
	fread(_HashTable[hash_value]->Item, sizeof(tHASHITEM), item_num, fd_cordic);

	_HashTable[hash_value]->Item_num = item_num;
    }

    if (i < hash_cnt)
	return -1;

    return 1;
}

/*
 *  * Hash Table Å½»ö...
 *   */
tVOID *FindCorpusDic(UBYTE *key)
{
    UDWORD hash_val = hash(key, strlen(key));
    tHASHITEM *cur_item;
    int i;

    hash_val = hash_val & HASHMASK;
    if (hash_val >= HASHTABLESIZE)
	return (tVOID *) NULL;

    if (_HashTable[hash_val] == NULL)
	return (tVOID *) NULL;

    cur_item = _HashTable[hash_val]->Item;
    for (i = 0; i < _HashTable[hash_val]->Item_num; i++) {
	if (!strcmp(cur_item[i].key, key))
	    return (tVOID *) cur_item[i].data;
    }

    return (tVOID *) NULL;
}


DWORD ClearCorpusDic()
{
    DWORD i;

    free(HashValueTable);
    for (i = 0; i < HASHTABLESIZE; i++) {
	if (_HashTable[i] != NULL) {
	    free(_HashTable[i]->Item);
	    free(_HashTable[i]);
	}
    }

    return 1;
}
