/*
 * Porter's Word Stemmer
 * main function : IDX_strip_affixes()
 */

#include <stdio.h>
#include <string.h>

#ifdef TRACETIME
	#include <time.h>	/* to use clock() function */
#endif


#define TRUE   1
#define FALSE  0
/* #define PREFIXES 1 */		/* strip prefixes */

#define cMAXKEYLEN			512

#define BIG_KEYWORDSIZE (cMAXKEYLEN+20)

/* functio declaration */
static int contains_vowel ( char*, int );
static int measure ( char * );
static int measure2( char *, int );
static int vowel ( char, char );
static int cvc ( char *, int );
static int has_suffix ( char *, char *, char * );
static int has_suffix2 ( char *, int, char *, int, char *, int * );
static void strip_suffixes ( char *, int * );
static int isvalid(char);
static void step_1 ( char *, int * );
static void step_2 ( char *, int * );
static void step_3 ( char *, int * );
static void step_4 ( char *, int * );
static void step_5 ( char *, int * );

static void	to_lower_case(),
	clean(),
#ifdef PREFIXES
	strip_prefixes(),
#endif
	strip_suffixes();

#ifdef TRACETIME
	double t1, t2;
	double g1, g2;
	double dPFClocks = 0.0; 
	double dSFClocks = 0.0; 
#endif

void IDX_strip_affixes ( char *string
						, int  *pLen )	/* length of this string */
{
/*	to_lower_case(string); */	/* processed previously */
/*	clean(string); */
#ifdef PREFIXES
	#ifdef TRACETIME
		t1 = (double)clock();
	#endif
	strip_prefixes(string, pLen);
	#ifdef TRACETIME
		t2 = (double)clock();
		dPFClocks += (double)(t2-t1);
	#endif
#endif
	#ifdef TRACETIME
		t1 = (double)clock();
	#endif
	strip_suffixes(string, pLen);
	#ifdef TRACETIME
		t2 = (double)clock();
		dSFClocks += (double)(t2-t1);
	#endif
/*
	string[cMAXKEYLEN] = '\0';
*/
}

static void to_lower_case ( char *kwd )
{
	int i;
	for ( i=0 ; i < strlen(kwd) ; i++ )
		if ( (kwd[i] >= 'A') && (kwd[i] <= 'Z') )
			kwd[i] += 'a' - 'A';
}

static void clean ( char *kwd )
{
	int i,j,last=strlen(kwd);
	for ( i=0 ; i < last ; i++ ) {
		if ( isvalid(kwd[i]) != 0 ) {
			for ( j = i ; j < last-1 ; j++ )
				kwd[j] = kwd[j+1];
			kwd[last-1] = '\0';
			last--;
			i--;
		}
	}
}

static int isvalid(char l)
{
	if ( (l >= 'a') && (l <= 'z') )
		return(0);
	if ( (l >= 'A') && (l <= 'Z') )
		return(0);
	if ( (l >= '0') && (l <= '9') )
		return(0);
	return(1);
}

#ifdef PREFIXES
static void strip_prefixes ( string, pLen )
	char *string;
	int  *pLen;
{
	switch(string[0]) {
	case 'k':
		if ( !strncmp("kilo", string, 4) ) { strcpy(string, string+4); *pLen -= 4; }
		break;
	case 'm':
		if ( !strncmp("micro", string, 5) ) { strcpy(string, string+5); *pLen -= 5; }
		else if ( !strncmp("milli", string, 5) ) { strcpy(string, string+5); *pLen -= 5; }
		else if ( !strncmp("mega", string, 4) ) { strcpy(string, string+4); *pLen -= 4; }
		break;
	case 'i':
		if ( !strncmp("intra", string, 5) ) { strcpy(string, string+5); *pLen -= 5; }
		break;
	case 'u':
		if ( !strncmp("ultra", string, 5) ) { strcpy(string, string+5); *pLen -= 5; }
		break;
	case 'n':
		if ( !strncmp("nano", string, 4) ) { strcpy(string, string+4); *pLen -= 4; }
		break;
	case 'p':
		if ( !strncmp("pico", string, 4) ) { strcpy(string, string+4); *pLen -= 4; }
		else if ( !strncmp("pseudo", string, 6) ) { strcpy(string, string+6); *pLen -= 6; }
		break;
	default:
		break;
	}
}
#endif

static void step_1 ( char *string, int  *pLen )
{
    char stem[BIG_KEYWORDSIZE];
    int stemlen;

    if ( string[(*pLen)-1] == 's' ) {
	if ( (has_suffix2(string, *pLen, "sses", 4, stem, &stemlen) )
	  || (has_suffix2(string, *pLen, "ies",  3, stem, &stemlen) ) )
	{
	    string[*pLen-2] = '\0';
	    *pLen -= 2;
	}
	else if ( string[*pLen-2] != 's' ) {
	    string[*pLen-1] = '\0';
	    (*pLen)--;
	}
    }
    if ( has_suffix2(string, *pLen, "eed", 3, stem, &stemlen) ) {
	if ( measure2(stem, stemlen) > 0 ) {
	    string[*pLen-1] = '\0';
	    (*pLen)--;
	}
    }
    else {
	if ( (has_suffix2(string, *pLen, "ed",  2, stem, &stemlen)
	   || has_suffix2(string, *pLen, "ing", 3, stem, &stemlen))
		&& contains_vowel(stem, stemlen) ) {
	    string[stemlen] = '\0';
	    *pLen = stemlen;
	    if (       has_suffix2(string, *pLen, "at", 2, stem, &stemlen)
		    || has_suffix2(string, *pLen, "bl", 2, stem, &stemlen)
		    || has_suffix2(string, *pLen, "iz", 2, stem, &stemlen) ) {
		string[*pLen+1] = '\0';
		string[(*pLen)++] = 'e';
	    }
	    else {
		if ( (string[*pLen-1] == string[*pLen-2])
			&& (string[*pLen-1] != 'l')
			&& (string[*pLen-1] != 's')
			&& (string[*pLen-1] != 'z') )
		{
		    string[*pLen-1] = '\0';
		    (*pLen)--;
		}
		else if ( measure2(string, *pLen) == 1 ) {
		    if ( cvc(string, *pLen) == TRUE ) {
			string[*pLen+1] = '\0';
			string[(*pLen)++] = 'e';
		    }
		}
	    }
	}
    }
    if ( has_suffix2(string, *pLen, "y", 1, stem, &stemlen) && contains_vowel(stem, stemlen) )
    {
	string[*pLen-1] = 'i';
    }
}

static void step_2 ( char *string, int *pLen )
{
    static char *suffixes[][2] =  { { "ational", "ate" },
				{ "tional",  "tion" },
				{ "enci",    "ence" },
				{ "anci",    "ance" },
				{ "izer",    "ize" },
				{ "iser",    "ize" },
				{ "abli",    "able" },
				{ "alli",    "al" },
				{ "entli",   "ent" },
				{ "eli",     "e" },
				{ "ousli",   "ous" },
				{ "ization", "ize" },
				{ "isation", "ize" },
				{ "ation",   "ate" },
				{ "ator",    "ate" },
				{ "alism",   "al" },
				{ "iveness", "ive" },
				{ "fulness", "ful" },
				{ "ousness", "ous" },
				{ "aliti",   "al" },
				{ "iviti",   "ive" },
				{ "biliti",  "ble" },
				{  0,        0     } };
    static int suffixlen[22][2] = {	{7,3}, {6,4}, {4,4}, {4,4}, {4,3},
				{4,3}, {4,4}, {4,2}, {5,3}, {3,1},
	  			{5,3}, {7,3}, {7,3}, {5,3}, {4,3},
				{5,2}, {7,3}, {7,3}, {7,3}, {5,2},
		    		{5,3}, {6,3} };
    char stem[BIG_KEYWORDSIZE];
    register int index;
    int stemlen;

    for ( index = 0 ; suffixes[index][0] != 0 ; index++ ) {
	if ( has_suffix2( string, *pLen, suffixes[index][0], suffixlen[index][0], stem, &stemlen ) ) {
	    if ( measure2( stem, stemlen ) > 0 ) {
		sprintf ( string, "%s%s", stem, suffixes[index][1] );
		(*pLen) = stemlen + suffixlen[index][1];
		return;
	    }
	}
    }
    return;
}

static void step_3 ( char *string, int  *pLen )
{
    static char *suffixes[][2] = { { "icate", "ic" },
				{ "ative", "" },
				{ "alize", "al" },
				{ "alise", "al" },
				{ "iciti", "ic" },
				{ "ical",  "ic" },
				{ "ful",   "" },
				{ "ness",  "" },
				{ 0,       0 } };
    static int suffixlen[8][2] = { {5,2}, {5,0}, {5,2}, {5,2}, {5,2}, {4,2}, {3,0}, {4,0} };
    char stem[BIG_KEYWORDSIZE];
    register int index;
    int stemlen;
    
    for ( index = 0 ; suffixes[index][0] != 0 ; index++ ) {
	if ( has_suffix2(string, *pLen, suffixes[index][0], suffixlen[index][0], stem, &stemlen) )
	    if ( measure2( stem, stemlen ) > 0 ) {
		sprintf ( string, "%s%s", stem, suffixes[index][1] );
		(*pLen) = stemlen + suffixlen[index][1];
		return;
	    }
    }
    return;
}

static void step_4 ( char *string, int *pLen )
{
    static char *suffixes[] = { "al", "ance", "ence", "er", "ic", "able",
	"ible", "ant", "ement", "ment", "ent", "sion", "tion",
	"ou", "ism", "ate", "iti", "ous", "ive", "ize", "ise", 0 };
    static int suffixlen[21] = { 2,    4,       4,     2,    2,     4,
	4,       3,     5,       4,      3,      4,     4,
	2,     3,     3,     3,     3,     3,     3,     3}; 
    char stem[BIG_KEYWORDSIZE];
    register int index;
    int stemlen;
    
    for ( index = 0 ; suffixes[index] != 0 ; index++ ) {
	if ( has_suffix2(string, *pLen, suffixes[index], suffixlen[index], stem, &stemlen) )
	    if ( measure2( stem, stemlen ) > 1 ) {
		strcpy( string, stem );
		*pLen = stemlen;
		return;
	    }
    }
    return;
}

static void step_5 ( char *string, int *pLen )
{
    if ( string[*pLen - 1] == 'e' ) {
	if ( measure2(string, *pLen) > 1 ) {
	    /* measure(string)==measure(stem) if ends in vowel */
	    string[*pLen - 1] = '\0';
	    (*pLen)--;
	}
	else if ( measure2(string, *pLen) == 1 ) {
	    char stem[BIG_KEYWORDSIZE];
	    strcpy(stem,"");
	    strncat( stem, string, *pLen - 1 );
	    if ( cvc(stem, *pLen-1) == FALSE ) {
		string[*pLen - 1] = '\0';
		(*pLen)--;
	    }
	}
    }
    if ( (string[*pLen - 1] == 'l') && (string[*pLen - 2] == 'l')
	    && (measure2(string, *pLen) > 1) ) {
	string[*pLen - 1] = '\0';
	(*pLen)--;
    }
}

static void strip_suffixes ( char *string
							, int  *pLen )	/* length of the string/modified by jskim 990829 */
{
	step_1 ( string, pLen );
	step_2 ( string, pLen );
	step_3 ( string, pLen );
	step_4 ( string, pLen );
	step_5 ( string, pLen );
}

static int has_suffix2 ( char *word, int wordlen, char *suffix, int suffixlen, char *stem, int *stemlen )
 {
    if (wordlen <= suffixlen) return(FALSE);
    /*
    if ( (suffixlen > 1) && (word[wordlen-2] != suffix[suffixlen-2]) )
	return(FALSE);
    */

    if (!strcmp(word+wordlen-suffixlen, suffix)) {
	strcpy(stem, word);
	stem[wordlen-suffixlen] = '\0';
	*stemlen = wordlen - suffixlen;
	return(TRUE);
    }
    return (FALSE);
}

static int has_suffix ( char *word, char *suffix, char *stem )
{
	char tmp[BIG_KEYWORDSIZE];
	if ( strlen(word) <= strlen(suffix) )
		return(FALSE);
	if ( (strlen(suffix) > 1) &&
			( word[strlen(word)-2] != suffix[strlen(suffix)-2] ) )
		return(FALSE);
	strcpy ( stem, "" );
	strncat ( stem, word, strlen(word) - strlen(suffix) );
	strcpy ( tmp, stem );
	strcat ( tmp, suffix );

	if ( strcmp (  tmp, word ) == 0 )
		return(TRUE);
	else
		return(FALSE);
}

static int cvc ( char *string, int Len )
{
    int length= Len;
    if ( length < 3 )
	return(FALSE);
    if ( (vowel(string[length-1],string[length-2]) == FALSE)
	    && (string[length-1] != 'w')
	    && (string[length-1] != 'x')
	    && (string[length-1] != 'y')
	    && (vowel(string[length-2],string[length-3]) == TRUE)
	    && ( ( (length==3) && (vowel(string[0],'a') == FALSE) )
		|| (vowel(string[length-3],string[length-4])==FALSE) ) )
	return(TRUE);
    else
	return(FALSE);
}

static int vowel ( char ch, char prev )
{
	switch ( ch ) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return(TRUE);
			  break;
		case 'y': return( vowel(prev,'?') == TRUE );
			  break;
		default : return(FALSE);
			  break;
	}
}

static int measure ( char *stem )
{
	register int i=0, count = 0;
	int length=strlen(stem);
	while ( i < length ) {
		for ( ; i < length ; i++ ) {
			if ( i > 0 ) {
				if ( vowel(stem[i],stem[i-1]) == TRUE )
					break;
			}
			else {	if ( vowel(stem[i],'a') == TRUE )
					break;
			}
		}
		for ( i++ ; i < length ; i++ ) {
			if ( i > 0 ) {
				if ( vowel(stem[i],stem[i-1]) == FALSE )
					break;
			}
			else {	if ( vowel(stem[i],'?') == FALSE )
					break;
			}
		}
		if ( i < length ) {
			count++;
			i++;
		}
	}
	return(count);
}

static int measure2( char *stem, int length )
{
    register int i=0, count = 0;
    while ( i < length ) {
	for ( ; i < length ; i++ ) {
	    if ( i > 0 ) {
		if ( vowel(stem[i],stem[i-1]) == TRUE )
		    break;
	    }
	    else {
		if ( vowel(stem[i],'a') == TRUE )
		    break;
	    }
	}
	for ( i++ ; i < length ; i++ ) {
	    if ( i > 0 ) {
		if ( vowel(stem[i],stem[i-1]) == FALSE )
		    break;
	    }
	    else {
		if ( vowel(stem[i],'?') == FALSE )
		    break;
	    }
	}
	if ( i < length ) {
	    count++;
	    i++;
	}
    }
    return(count);
}

static int contains_vowel ( char *word, int len )
{
    register int i;
    for ( i=0 ; i < len ; i++ )
	if ( i > 0 ) {
	    if ( vowel(word[i],word[i-1]) == TRUE )
		return(TRUE);
	}
	else {
	    if ( vowel(word[0],'a') == TRUE )
		return(TRUE);
	}
    return(FALSE);
}

