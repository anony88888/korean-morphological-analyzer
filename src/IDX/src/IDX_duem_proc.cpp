#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static unsigned char duem_org_sound[] = "00³É01³à02³á03³â04³ã05³ä06³å07³ç08³é09´¢10´º11´»12´Ï13´Ð14´Ñ15´Ò16¶ó17¶ô18¶õ19¶ö20¶÷21¶ø22¶û23·¡24·©25·«26·®27·Á28·Â29·Ã30·Ä31·Å32·Æ33·É34·Ê35·Î36·Ï37·Ð38·Õ39·Ú40·á41·æ42·ç43·ù44·ú45·û46·ü47¸¢48¸¤49¸§50¸ª51¸®52¸°53¸²54¸³";

static unsigned char duem_cnvt_sound[] = "00¾ç01¿©02¿ª03¿¬04¿­05¿°06¿±07¿µ08¿¹09¿ä10À¯11À°12ÀÌ13ÀÍ14ÀÎ15ÀÏ16³ª17³«18³­19³¯20³²21³³22³¶23³»24³Ã25¾à26¾ç27¿©28¿ª29¿¬30¿­31¿°32¿±33¿µ34¿¹35³ë36³ì37³í38³ó39³ú40¿ä41¿ë42´©43À¯44À°45À±46À²47À¶48´Á49´Æ50´É51ÀÌ52ÀÎ53ÀÓ54ÀÔ";

//
// 2003-05-28 µÎÀ½¹ýÄ¢ Àû¿ë ¿©ºÎ °Ë»ç ¹× º¯È¯
// ÀÔ·Â : UTF-8(º¯È¯ Àü ÇÑ ±ÛÀÚ)
// Ãâ·Â : UTF-8(º¯È¯ ÈÄ), ÇØ´ç»çÇ× ¾øÀ¸¸é 0 , º¯È¯µÇ¾úÀ¸¸é 1
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
