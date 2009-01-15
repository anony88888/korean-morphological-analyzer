#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static unsigned char duem_org_sound[] = "00��01��02��03��04��05��06��07��08��09��10��11��12��13��14��15��16��17��18��19��20��21��22��23��24��25��26��27��28��29��30��31��32��33��34��35��36��37��38��39��40��41��42��43��44��45��46��47��48��49��50��51��52��53��54��";

static unsigned char duem_cnvt_sound[] = "00��01��02��03��04��05��06��07��08��09��10��11��12��13��14��15��16��17��18��19��20��21��22��23��24��25��26��27��28��29��30��31��32��33��34��35��36��37��38��39��40��41��42��43��44��45��46��47��48��49��50��51��52��53��54��";

//
// 2003-05-28 ������Ģ ���� ���� �˻� �� ��ȯ
// �Է� : UTF-8(��ȯ �� �� ����)
// ��� : UTF-8(��ȯ ��), �ش���� ������ 0 , ��ȯ�Ǿ����� 1
//
int DuemConv(char *src, char *dest)
{
	char *ptr;
	char duem_index[3];
	char duem_dest[10];
	int i;

	ptr = strstr((char*)duem_org_sound, src);
	if (ptr == NULL)
		return 0;

	strncpy(duem_index, ptr-2, 2);
	duem_index[2] = '\0';
	ptr = strstr((char*)duem_cnvt_sound, duem_index);
	if (ptr == NULL)
		return 0;

	ptr++; ptr++;
	i = 0;
	while (*ptr != '\0' && !isdigit(*ptr)) {
		duem_dest[i] = *ptr;
		i++; ptr++;
	}
	duem_dest[i] = '\0';

	strcpy(dest, duem_dest);

	return 1;
}
