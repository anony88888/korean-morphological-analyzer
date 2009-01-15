#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char duem_org_sound[] = "00냥01녀02녁03년04녈05념06녑07녕08녜09뇨10뉴11뉵12니13닉14닌15닐16라17락18란19랄20람21랍22랑23래24랭25략26량27려28력29련30렬31렴32렵33령34례35로36록37론38롱39뢰40료41룡42루43류44륙45륜46률47륭48륵49름50릉51리52린53림54립";

static unsigned char duem_cnvt_sound[] = "00양01여02역03연04열05염06엽07영08예09요10유11육12이13익14인15일16나17낙18난19날20남21납22낭23내24냉25약26양27여28역29연30열31염32엽33영34예35노36녹37논38농39뇌40요41용42누43유44육45윤46율47융48늑49늠50능51이52인53임54입";

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

	ptr = strstr(duem_org_sound, src);
	if (ptr == NULL)
		return 0;

	strncpy(duem_index, ptr-2, 2);
	duem_index[2] = '\0';
	ptr = strstr(duem_cnvt_sound, duem_index);
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
