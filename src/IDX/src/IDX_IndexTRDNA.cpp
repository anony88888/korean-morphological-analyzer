#include <IDX_common.h>
#include <IDX_user.h>
#include <ctype.h>

#ifdef WORD_LENGTH
#undef WORD_LENGTH
#endif
#define WORD_LENGTH		11		// word size = 9, 10, 11, 12

// only deals with English alphabets
int IDX_IndexTRDNA(char *SecVal, POSTINFO *PostInfo, int StopCheck)
{
	int i;
	int PostInfoCnt = 0;
	int wordLen;				// growing length of word.
								// set 0 if reach WORD_LENGTH
	char Word[WORD_LENGTH+1];	// word to index
	char *SecPtr;				// pointer floating on Section value
	char c;

	wordLen = 0;				// initialize the current word length
	SecPtr = SecVal;			// get the first pointer of section
	Word[WORD_LENGTH] = '\0';	// initialize the string
	while ( *SecPtr ) {
		c = tolower(*SecPtr++);
		if ( !isalpha(c) ) continue;	// if not alphabet, just ignore
		Word[wordLen++] = c;
		if (wordLen == WORD_LENGTH) {
		   	strcpy(PostInfo[PostInfoCnt].key, Word);
		   	PostInfo[PostInfoCnt].keyLen = WORD_LENGTH;
		   	PostInfo[PostInfoCnt].wordNum = PostInfoCnt+1;	// weird?
		   	PostInfo[PostInfoCnt].psgNum = 0;
		   	PostInfoCnt++;
		   	if (PostInfoCnt > MAXPOSTINFOSIZE - 1)
			   	return PostInfoCnt;
			// shift one words
			for (i=1; i < WORD_LENGTH; i++) {
				Word[i-1] = Word[i];
			}
			wordLen = WORD_LENGTH-1;		// reinitialize the wordlen
		}
   	}

	return PostInfoCnt;
}

