#include <stdio.h>
#include <string.h>
#include <IDX_common.h>
#include <IDX_Hanja2Hangul.h>
#include <HanjaHangulMap.h>

#include <iconv.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>

#define MAX_HANJA_TBL		70000

static unsigned char Hj2Hg_Table[MAX_HANJA_TBL][50];
static unsigned int TableSize;
static unsigned int Table_InitVal;


void ConvToCJK(unsigned int *hj_code)
{
#if 0
	unsigned int temp;

	if (*hj_code >= INIT_DUP_CODE && *hj_code <= INIT_DUP_CODE + DUP_TABLE_SIZE) {
		temp = DUP_TABLE[*hj_code - INIT_DUP_CODE];
		*hj_code = temp;
	}
#endif
}

int LoadHanjaTable(char *TableName)
{
	FILE *fd_in;
	char line[8192], code[5], str[512];
	char cvt_str[512];
	char *ptr;
	long int init_val, code_val;
	int i, res, first_flag;
	int str_len, cvt_str_len;
	UTF32 utf32_val[10], utf32_initval, *utf32_ptr;
	UTF16 utf16_val[10], *utf16_ptr;
	//iconv_t cd = (iconv_t)-1;

	/*
	cd = iconv_open("UTF-8", "EUC-KR");
	if (cd == (iconv_t)(-1)) {
		printf("iconv_open error...!!\n");
		return 0;
	}
	*/

	TableSize = 0;
	for (i = 0; i < MAX_HANJA_TBL; i++)
		Hj2Hg_Table[i][0] = '\0';

	fd_in = fopen(TableName, "rt");
	if (fd_in == NULL)
		return 0;

	first_flag = 1;
	while (fgets(line, 8192, fd_in)) {
		if (first_flag) {
			// 도스용 UTF-8 파일 헤더 처리
			if (line[0] != 'U' && line[1] != '+') {
				strncpy(code, &line[5], 4);
				code[4] = '\0';
				strcpy(str, &line[10]);
				str[strlen(str)-4] = '\0';
			} else {
				strncpy(code, &line[2], 4);
				code[4] = '\0';
				strcpy(str, &line[7]);
				str[strlen(str)-4] = '\0';
			}

			utf16_val[0] = strtol(code, NULL, 16);
			utf16_ptr = utf16_val;
			utf32_ptr = utf32_val;
			ConvertUTF16toUTF32(&utf16_ptr, &utf16_val[1], &utf32_ptr, &utf32_val[1], strictConversion);
			utf32_initval = utf32_val[0];

			Table_InitVal = utf32_initval;

			first_flag = 0;
		} else {
			strncpy(code, &line[2], 4);
			code[4] = '\0';
			strcpy(str, &line[7]);
			ptr = &str[strlen(str)-1];
			while (*ptr != '$' && ptr != str)
				ptr--;
			if (*ptr != '$')
				continue;
			*ptr = '\0';

			utf16_val[0] = strtol(code, NULL, 16);
			utf16_ptr = utf16_val;
			utf32_ptr = utf32_val;
			ConvertUTF16toUTF32(&utf16_ptr, &utf16_val[1], &utf32_ptr, &utf32_val[1], strictConversion);
		}

		/*
		str_len = strlen(str);
		cvt_str_len = str_len * 3;
		res = iconv(cd, (char **)&str, &str_len, (char **)&cvt_str, &cvt_str_len);

		cvt_str[cvt_str_len] = '\0';
		strcpy(Hj2Hg_Table[utf32_val[0]-utf32_initval], cvt_str);
		*/
		strcpy(Hj2Hg_Table[utf32_val[0]-utf32_initval], str);
	}
	TableSize = utf32_val[0]-utf32_initval;

	fclose(fd_in);

	/*
	iconv_close(cd);
	*/

	return 1;
}

int GetHangulChars(unsigned int hj_code, char *hg_buf)
{
	ConvToCJK(&hj_code);

	if (hj_code - Table_InitVal < 0)
		return 0;

	if (hj_code - Table_InitVal > TableSize)
		return 0;

	if (Hj2Hg_Table[hj_code-Table_InitVal][0] == '\0')
		return 0;


	strcpy(hg_buf, Hj2Hg_Table[hj_code-Table_InitVal]);
	//printf("0x%x:%s<p>\n", hj_code, hg_buf);

	return 1;
}


void Hanja2Hangul_UTF8(unsigned char *src, unsigned char *dest)
{
	unsigned char c;
	unsigned short unicode = 0x00000000;
    int i, j, len;

	strcpy(dest, src);

	len = strlen(dest);
	for (i = 0; i < len;) {
		c = dest[i] & 0xe0;
		if (c < 0x80) {
			i++;
			continue; /* no need to process chars in this area */
		} else if (c < 0xe0) {
			i+=2;
			continue; /* no need to process chars in this area */
		} else if (c < 0xf0) {
			unicode = (unsigned short) dest[i]&0x0f;
			i++;
			unicode = unicode << 6;
			unicode = unicode | ((unsigned short) dest[i] & 0x3f);
			i++;
			unicode = unicode << 6;
			unicode = unicode | ((unsigned short) dest[i] & 0x3f);
			i++;
		} /* from UTF-8 to UCS-2 */

		if (HjHgMap[unicode] != unicode ) { /* different ? hanja: non-CJK */
			unsigned char byte[4];

			unicode = HjHgMap[unicode];
			byte[2] = (unicode & 0x3f) | 0x80;
			byte[1] = (((unicode << 2) & 0x3f00) | 0x8000) >> 8;
			byte[0] = (((unicode << 4) & 0x3f0000) | 0xe00000) >> 16;

			for (j = 0; j < 3; j++) {
				dest[i-3+j] = byte[j];
			}

			continue;
		}
	}
}

/* 입력 : UCS4, 출력 : UCS4 */
void Hanja2Hangul_UCS4(UTF32 *src, int src_len, UTF32 *dest)
{
	int i;

	for (i = 0; i < src_len; i++) {
		if (HjHgMap[src[i]] != src[i]) {
			/* 한자 */
			dest[i] = HjHgMap[src[i]];
			/*
			if (src[i] == 0xf9d1)
				printf("0x%x ---> 0x%x<p>\n", src[i], dest[i]);
				*/
		} else {
			/* 기타 */
			dest[i] = src[i];
		}
	}
}

#if 0
void Hanja2Hangul(char *Buffer)
{
	int stringlen;
	unsigned int hidx, lidx;

	stringlen=strlen(Buffer);
	hidx = 0, lidx = 1;

	while(1) {
		if (stringlen<hidx+1 || stringlen<lidx+1)
			break;

		switch(CodeType(Buffer[hidx],Buffer[lidx]))
		{
		  case 0 : /* 아스키 */
			hidx++; lidx++;
			break;

		  case 1 : /* 한글 */
		  case 2 : /* '\241' */
		  case 3 : /* 한글 홀소리 글자 */
		  case 4 : /* 2-Byte Symbols */
		  case 6 : /* Other 2-Byte Characters */
			hidx+=2; lidx+=2;
			break;

		  case 5 : /* 한자 */
			Hj2HgCode(&Buffer[hidx],&Buffer[lidx]);
			hidx+=2; lidx+=2;
			break;
		}
	}

} /* Hanja2Hangul */


/****************************************************************/
/* ks 5601 완성형이 가질수 있는 코드값을 식별하는 함수		*/ 
/* 입력된 파라메터 hbyt, lbyte는 각각 상위, 하위바이트 이다.	*/
/* 리턴값이	0이면 아스키 코드,				*/
/*		1이면 한글 코드,				*/
/*		2이면 '\241' '\241',				*/
/*		3이면 한글 홀소리 코드,				*/
/*		4이면 2-Byte 심볼,				*/
/*		5이면 한자 코드,				*/
/*		6이면 기타 2 바이트 코드			*/
/****************************************************************/ 
int CodeType(unsigned char hbyte, unsigned char lbyte)
{
	int fst, snd;

	fst=(int)hbyte;
	snd=(int)lbyte;

	if(fst<128) /* 아스키 코드범위 */
		return 0;

	else if ((0xb0<= fst && fst<=0xc8) && (0xa1<= snd && snd<=0xfe)) /* 한글 */
		return 1;
/*
	else if (hbyte=='\241' && lbyte=='\241')
		return 2;
*/
	else if (fst<=0xa4 && (0xa1<= snd && snd<=0xfe)) /* 한글 홀소리 글자 */
		return 3;

	else if ((0xa1<= fst && fst<=0xac) && (0xa1<= snd && snd<=0xfe)) /* 2-byte Symbol */
		return 4;

	else if ((0xca<= fst && fst<=0xfd) && (0xa1<= snd && snd<=0xfe)) /* 한자 */
		return 5;

	else /* Other 2-Byte Chars */
		return 6;

} /* CodeType */


static unsigned char HanjaTbl[] = "\
가가가가가가가가가가가가가가가가가가가가가가가가가가가가가각각각각각각각각각각각간간간간간\
간간간간간간간간간간간간간간간간간간간갈갈갈갈갈갈갈갈갈갈감감감감감감감감감감감감감감감감\
감감감감갑갑갑갑갑갑강강강강강강강강강강강강강강강강강강강강강강강강개개개개개개개개개개개\
개개개개개개개개개객객갱갱갱갱갹거거거거거거거거거거거거거거거거거건건건건건건건건건건건건\
걸걸걸걸검검검검검검검겁겁겁게게게격격격격격격격견견견견견견견견견견견결결결결결결겸겸겸겸\
겸겸경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경경\
경경계계계계계계계계계계계계계계계계계계계계계계계계고고고고고고고고고고고고고고고고고고고\
고고고고고고고고고고고고고고고고고고고고곡곡곡곡곡곡곡곤곤곤곤곤곤곤곤곤곤골골골공공공공공\
공공공공공공공공공공공곶과과과과과과과과과과과과곽곽곽곽관관관관관관관관관관관관관관관관관\
괄괄괄괄광광광광광광광광광광광광광괘괘괘괴괴괴괴괴괴괴괴괴굉굉굉굉교교교교교교교교교교교교\
교교교교교교교교교교교교교구구구구구구구구구구구구구구구구구구구구구구구구구구구구구구구구\
구구구구구구구구구구구구구구구구구구구구구구국국국국국국군군군군군군굴굴굴굴궁궁궁궁궁궁권\
권권권권권권권권권궐궐궐궐궐궤궤궤궤궤궤귀귀귀귀귀귀규규규규규규규규규규규규규규규균균균균\
균균균귤극극극극극극극근근근근근근근근근근근근근근근글금금금금금금금금금금금금금금급급급급\
급급급긍긍긍긍기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기기\
기기기기기기기기기기기기기기기기기기기기기기기기기기긴길길길길김끽나나나나나나나나나나나나\
나나나낙낙낙낙낙낙낙낙난난난난난난난난난날날남남남남남남남남남납납납납납낭낭낭낭낭낭낭내내\
내내내내냉녀년년년념념념념녕녕노노노노노노노노노노노노노노노노노노녹녹녹녹녹녹논농농농농농\
농농뇌뇌뇌뇌뇌뇌뇨누누누누누누누누눈눌뉴뉴늑늑늠능능능능능능니니닉닉다다단단단단단단단단단\
단단단단단단단단단단단달달달달달담담담담담담담담담담담담담담담담담답답답답답당당당당당당당\
당당당당대대대대대대대대대대대대대대대대댁덕덕도도도도도도도도도도도도도도도도도도도도도도\
도도도도도도도도도도도도도도도도도도독독독독독독독독독독돈돈돈돈돈돈돈돈돈돈돌돌동동동동동\
동동동동동동동동동동동동두두두두두두두두두두두둔둔둔둔둔둔득등등등등등등등등등라라라라라라\
나라라락락락락락락락락락란란란란란란란란란랄랄람람람람람람람람람람랍랍랍랑랑랑랑랑랑랑랑래\
내래래랭략략량량량량량량량량량량량량량려려려려려려려려려려려려려려려려려려력력력력력력력련\
연련련련련련련련련련련열렬렬렬렬렬렴렴렴렴렴렵령령령령령령령령령령령령령령령령령령례례례례\
예로로로로로로로로로로로로로로로로로로록록록록록록록론롱롱롱롱롱롱롱뢰뢰뢰뢰뢰뢰뢰뢰료료료\
요료료료료료료료료룡루루루루루루루루루루루루루류류류류류류류류류류류류류류륙륙륙륜륜륜륜륜\
윤율률률률륭륵륵름릉릉릉릉릉릉리리리리리리리리리리리리리리리리리리리리리리리리리리린린린린\
인린린린린림림림림림립립립립마마마마마마마마막막막막막막만만만만만만만만만만만만만만만만만\
만만말말말말말말말망망망망망망망망망망망망매매매매매매매매매매매매매매맥맥맥맥맥맹맹맹맹맹\
맹멱멱면면면면면면면면면면면멸멸명명명명명명명명명명명명명명명몌모모모모모모모모모모모모모\
모모모모모모모모모모모목목목목목목목몰몰몽몽몽묘묘묘묘묘묘묘묘묘묘묘묘무무무무무무무무무무\
무무무무무무무무무무무무묵묵문문문문문문문문문문문문물물물미미미미미미미미미미미미미미미미\
미미미민민민민민민민민민민민민민밀밀밀박박박박박박박박박박박박박박박박박박박반반반반반반반\
반반반반반반반반반반반반반반반반반반발발발발발발발발발발발방방방방방방방방방방방방방방방방\
방방방방방방방방방방방방배배배배배배배배배배배배배배배배배배배배백백백백백백백백번번번번번\
번번번번번벌벌벌벌범범범범범범범범범법법벽벽벽벽벽벽벽벽벽벽벽변변변변변변변별별별별병병병\
병병병병병병병병병병병병병병보보보보보보보보보보보보보보보보복복복복복복복복복복복복복복복\
복복본볼봉봉봉봉봉봉봉봉봉봉봉봉봉봉봉봉부부부부부부부부부부부부부부부부부부부부부부부부부\
부부부부부부부부부부부부부부부부부부북분분분분분분분분분분분분분분분분분분분불불불불불붕붕\
붕붕붕붕비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비비\
비비빈빈빈빈빈빈빈빈빈빈빈빈빈빈빙빙빙빙사사사사사사사사사사사사사사사사사사사사사사사사사\
사사사사사사사사사사사사사사사사사사사사사사사사사사사사사사사사사사사삭삭삭삭산산산산산산\
산산산산산산살살살살살삼삼삼삼삼삼삼삼삽삽삽삽상상상상상상상상상상상상상상상상상상상상상상\
상상상상상상상상상새새새색색색색색생생생생생서서서서서서서서서서서서서서서서서서서서서서서\
서서서서서서서석석석석석석석석석석석석석석석선선선선선선선선선선선선선선선선선선선선선선선\
선선선선선선선선선설설설설설설설설설설설설설섬섬섬섬섬섬섬섬섭섭섭섭성성성성성성성성성성성\
성성성성성성성세세세세세세세세세소소소소소소소소소소소소소소소소소소소소소소소소소소소소소\
소소소소소소소소속속속속속속속속속손손손손손손솔송송송송송송송송쇄쇄쇄쇄쇄쇠쇠수수수수수수\
수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수수\
수수수수수수수수수수숙숙숙숙숙숙숙숙숙숙숙숙순순순순순순순순순순순순순순순순순순순순순순순\
순순순순술술술술숭숭숭슬슬슬습습습습습승승승승승승승승승승시시시시시시시시시시시시시시시시\
시시시시시시시시시시시시식식식식식식식식식식식식식식식신신신신신신신신신신신신신신신신신신\
신신신신신신실실실실심심심심심심심심심심십십십쌍씨아아아아아아아아아아아아아아아아아아악악\
악악악악악악악악악악악악안안안안안안안안안안알알알알암암암암암암암암압압압압앙앙앙앙앙앙앙\
애애애애애애애애애애애액액액액액액액앵앵앵앵야야야야야야야야야야야약약약약약약약약약양양양\
양양양양양양양양양양양양양양양양양양양양양양양양양양양양어어어어어어어어어어억억억억억언언\
언언언언얼얼엄엄엄엄엄엄업업엔여여여여여여여여여여여여여여여여여여여여여여여여역역역역역역\
역역역역역역역연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연연\
연연연연연열열열열열열열열열열염염염염염염염염염염염염염염염엽엽엽엽영영영영영영영영영영영\
영영영영영영영영영영영영영영영영영영영영영영영영영영영영영예예예예예예예예예예예예예예예예\
예예예예예예예예오오오오오오오오오오오오오오오오오오오오오오오오오오오오오오옥옥옥옥옥온온\
온온온온올옹옹옹옹옹옹옹옹옹와와와와와와와와완완완완완완완완완완완완완완완완완완왈왕왕왕왕\
왕왜왜왜왜외외외외외요요요요요요요요요요요요요요요요요요요요요요요요요요요요요요요요요요요\
요요요욕욕욕욕욕욕용용용용용용용용용용용용용용용용용용용용용용용용우우우우우우우우우우우우\
우우우우우우우우우우우우우우우우우우우우욱욱욱욱욱욱욱욱욱운운운운운운운운운운운운운울울울\
웅웅원원원원원원원원원원원원원원원원원원원원원원원원원원원월월월위위위위위위위위위위위위위\
위위위위위위위위위위위위유유유유유유유유유유유유유유유유유유유유유유유유유유유유유유유유유\
유유유유유유유유유유유유유유유유유유유유유유유육육육육육육육윤윤윤윤윤윤윤윤윤윤윤윤윤율율\
율율율융융융융융은은은은은은은을음음음음음음읍읍읍응응응응의의의의의의의의의의의의의의의의\
의의의이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이이익익익익\
익익익익인인인인인인인인인인인인인인인인인인인인인인인인일일일일일일일일일임임임임임임임임\
임임임입입입입입잉잉잉잉자자자자자자자자자자자자자자자자자자자자자자자자자자작작작작작작작\
작작작작작작잔잔잔잔잔잠잠잠잠잠잠잡장장장장장장장장장장장장장장장장장장장장장장장장장장장\
장장장장장장장장장장재재재재재재재재재재재재재재재재재쟁쟁쟁쟁저저저저저저저저저저저저저저\
저저저저저저저저저저저저저저적적적적적적적적적적적적적적적적적적적적적적적적적전전전전전전\
전전전전전전전전전전전전전전전전전전전전전전전전전전전전전전전전전전전절절절절절절절절점점\
점점점점점점점접접접정정정정정정정정정정정정정정정정정정정정정정정정정정정정정정정정정정정\
정정정정정정정정정정정정정정정정정정정정제제제제제제제제제제제제제제제제제제제제제제제조조\
조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조조족\
족족족존존졸졸졸종종종종종종종종종종종종종종종종종좌좌좌좌좌죄주주주주주주주주주주주주주주\
주주주주주주주주주주주주주주주주주주주주주주주주주주죽죽준준준준준준준준준준준준준준준준준\
준준줄중중중중즉즐즙즙즙증증증증증증증증증증증지지지지지지지지지지지지지지지지지지지지지지\
지지지지지지지지지지지지직직직직직진진진진진진진진진진진진진진진진진진진진진진진진진진진진\
진진진진진진진질질질질질질질질질질질질질질질짐짐집집집집집집집징징징차차차차차차차차차차차\
차차차차착착착착착착착찬찬찬찬찬찬찬찬찬찬찬찬찬찬찬찰찰찰찰찰참참참참참참참참참참창창창창\
창창창창창창창창창창창창창창창창창창채채채채채채채채채채채채책책책책처처처처척척척척척척척\
척척척척척척척척천천천천천천천천천천천천천천천천천천천철철철철철철철철철철첨첨첨첨첨첨첨첨\
첨첨첩첩첩첩첩첩첩첩첩첩청청청청청청청청체체체체체체체체체체초초초초초초초초초초초초초초초\
초초초초초초초초초초초초촉촉촉촉촉촉촌촌촌촌총총총총총총총총총총촬최최최추추추추추추추추추\
추추추추추추추추추추추추추추축축축축축축축축축축축축춘춘춘출출출충충충충충충췌췌췌취취취취\
취취취취취취취취취취취측측측측측층치치치치치치치치치치치치치치치치치치치치치치치치칙칙칙친\
칠칠칠침침침침침침침침침칩칭칭쾌타타타타타타타타타타타타타타탁탁탁탁탁탁탁탁탁탁탁탁탁탁탁\
탁탄탄탄탄탄탄탄탄탄탄탈탈탐탐탐탐탑탑탑탕탕탕탕탕태태태태태태태태태태태태태태택택택탱터토\
토토토통통통통통통통퇴퇴퇴퇴퇴퇴투투투투투투특특틈파파파파파파파파파파파파파파파파판판판판\
판판판판판팔팔팔패패패패패패패패패패패팽팽팽팽퍅편편편편편편편편편편폄평평평평평폐폐폐폐폐\
폐폐폐폐폐포포포포포포포포포포포포포포포포포포포포포포포포포포포포폭폭폭폭폭폭표표표표표표\
표표표표표표표표품품풍풍풍풍풍피피피피피피피필필필필필필필필필필핍핍하하하하하하하하하하하\
하하하학학학학학한한한한한한한한한한한한한한할할함함함함함함함함함함함함합합합합합합합항항\
항항항항항항항항항항항항항항항해해해해해해해해해해해해해해해해해해핵핵행행행행행향향향향향\
향향향향허허허허헌헌헌헌헐험험혁혁혁혁현현현현현현현현현현현현현현현현현현현현현혈혈혈혈혐\
협협협협협협협협협협협협형형형형형형형형형형형형형형형형형형형형혜혜혜혜혜혜혜혜혜호호호호\
호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호호혹혹혹혼혼혼혼혼\
혼홀홀홀홍홍홍홍홍홍홍홍홍홍화화화화화화화화화화화화화화확확확확확확환환환환환환환환환환환\
환환환환환환활활활활활황황황황황황황황황황황황황황황황황황황황황황황황회회회회회회회회회회\
회회회회회회회회회회획획횡횡횡효효효효효효효효효효효효효후후후후후후후후후후후후후훈훈훈훈\
훈훈훈훈훈훈훙훤훤훤훤훼훼훼휘휘휘휘휘휘휘휘휴휴휴휴휴휼휼휼흉흉흉흉흉흑흔흔흔흔흘흘흘흘흠\
흠흠흡흡흡흡흥희희희희희희희희희희희희희희희희희희희희힐";

/* 입력 파라메터 hbyte, lbyte를 변환테이블을 이용하여 한글 코드로
   변환한다. 변환된 값은 그대로 hbyte와 lbyte에 저장된다.
*/
void Hj2HgCode(unsigned char *hbyte, unsigned char *lbyte)
{
	unsigned int offset;
	int h, l;
	
	h=(int)*hbyte;
	l=(int)*lbyte;

	/* 입력된 한자에대한 변환테이블에서의 옵셋을 구한다 */	
	offset=(unsigned int)((h-202)*94+l-161)*2;  
	*hbyte=HanjaTbl[offset];
	*lbyte=HanjaTbl[offset+1];

} /* Hj2HgCode */
#endif
