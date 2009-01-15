#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <IDX_common.h>

void strlower(char *string) /* small capitalize a string */
{
	char *ptr = string;

	while (*ptr != '\0') {
		if (*ptr & 0x80) {
			ptr++; ptr++;
			continue;
		} else {
			if (isalpha(*ptr))
				*ptr = tolower(*ptr);
			ptr++;
		}
	}
}
