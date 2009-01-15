#include <IDX_common.h>
#include <IDX_user.h>
#include <ctype.h>

#ifdef WORD_LENGTH
#undef WORD_LENGTH
#endif
#define WORD_LENGTH		5		// word size = 3, 4, 5, 6

// only deals with English alphabets
int IDX_IndexProtein(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int i, len;
	int PostInfoCnt = 0;
	int wordLen;				// growing length of word.
								// set 0 if reach WORD_LENGTH
	char Word[WORD_LENGTH+1];	// word to index
	char c;

	wordLen = 0;				// initialize the current word length
	Word[WORD_LENGTH] = '\0';	// initialize the string
	len = strlen(SecVal);
	for (i=0; i<len; i++) {
		if (wordLen == WORD_LENGTH) {
		   	strcpy(PostInfo[PostInfoCnt].key, Word);
// printf("%d=Word=%s\n", PostInfoCnt+1, Word);
		   	PostInfo[PostInfoCnt].keyLen = WORD_LENGTH;
		   	PostInfo[PostInfoCnt].wordNum = PostInfoCnt+1;	// weird?
		   	PostInfo[PostInfoCnt].psgNum = 1;
		   	PostInfoCnt++;
		   	if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
			   	return PostInfoCnt;
			// shift one words
			strcpy(Word, Word+1);
			wordLen = WORD_LENGTH-1;		// reinitialize the wordlen
		}
		c = (char)tolower((int)SecVal[i]);
		if ( !isalpha(c) ) continue;	// if not alphabet, just ignore
		Word[wordLen++] = c;
   	}

	return PostInfoCnt;
}

