/********************************************************/
/*	The KRISTAL-II System, Version 1.6beta		*/
/*							*/
/*	COPYRIGHT (C) April, 1997			*/
/*	Group for Intelligent Information Systems	*/
/*	Korea R & D Information Center			*/
/*	P.O.Box 122, Yusong, Taejon 305-600, Korea	*/
/*							*/
/* 	Developed by Joon Ho Lee (042-828-5042)		*/
/* 		     Jeong Soo Ahn (042-828-5047)	*/
/* 		     Yun Soo Choi (042-828-5045)	*/
/* 		     Hwa Mook Yoon (042-828-5023)	*/
/* 		     Jinsuk Kim    (042-828-5061)	*/
/********************************************************/

#define		cMAXTOKENLEN		256		/* maximum token length  */

#define		T_EN		1  		/* English             */
#define		T_DG		2  		/* Digit               */
#define		T_SC		3  		/* Special Character   */
#define		T_CK		4  		/* Control key         */
#define		T_BL		5  		/* Blank               */
#define		T_KO		6  		/* Korean Code         */
#define		T_HJ		7  		/* Hanja  Code         */
#define		T_JP		8  		/* Japanse Code        */
#define		T_U1		9  		/* Unknown(1 byte)     */
#define		T_U2		0  		/* Unknown(2 byte)     */


typedef	struct {			/* 토큰 그룹 */
	char	*TokType;		/* token type */
	char	TokGrp;			/* token group */
	} TOKGRP;

/* 한글/한자/일어 2 바이트 코드 범위

     ----------------------------------------------------------------
     구분   첫번째 글자범위       두번째 글자 범위    테이블상의 이름
     ----------------------------------------------------------------
     한글   176(B0) - 200(C8)     161(A1) - 254(FE)        T_KO
     한자   202(CA) - 253(FD)     161(A1) - 254(FE)        T_HJ
     일어   170(AA)               161(A1) - 243(F3)        T_JP
            171(AB)               161(A1) - 246(F6)
     ----------------------------------------------------------------

*/

/*     Hexadecimal - Character  
      _______________________________________________________________
     | 00 NUL| 01 SOH| 02 STX| 03 ETX| 04 EOT| 05 ENQ| 06 ACK| 07 BEL|
     | 08 BS | 09 HT | 0A NL | 0B VT | 0C NP | 0D CR | 0E SO | 0F SI |
     | 10 DLE| 11 DC1| 12 DC2| 13 DC3| 14 DC4| 15 NAK| 16 SYN| 17 ETB|
     | 18 CAN| 19 EM | 1A SUB| 1B ESC| 1C FS | 1D GS | 1E RS | 1F US |
     | 20 SP | 21  ! | 22  " | 23  # | 24  $ | 25  % | 26  & | 27  ' |
     | 28  ( | 29  ) | 2A  * | 2B  + | 2C  , | 2D  - | 2E  . | 2F  / |
     | 30  0 | 31  1 | 32  2 | 33  3 | 34  4 | 35  5 | 36  6 | 37  7 |
     | 38  8 | 39  9 | 3A  : | 3B  ; | 3C  < | 3D  = | 3E  > | 3F  ? |
     | 40  @ | 41  A | 42  B | 43  C | 44  D | 45  E | 46  F | 47  G |
     | 48  H | 49  I | 4A  J | 4B  K | 4C  L | 4D  M | 4E  N | 4F  O |
     | 50  P | 51  Q | 52  R | 53  S | 54  T | 55  U | 56  V | 57  W |
     | 58  X | 59  Y | 5A  Z | 5B  [ | 5C  \ | 5D  ] | 5E  ^ | 5F  _ |
     | 60  ` | 61  a | 62  b | 63  c | 64  d | 65  e | 66  f | 67  g |
     | 68  h | 69  i | 6A  j | 6B  k | 6C  l | 6D  m | 6E  n | 6F  o |
     | 70  p | 71  q | 72  r | 73  s | 74  t | 75  u | 76  v | 77  w |
     | 78  x | 79  y | 7A  z | 7B  { | 7C  | | 7D  } | 7E  ~ | 7F DEL|
      ---------------------------------------------------------------
     | 80    | 81    | 82    | 83    | 84    | 85    | 86    | 87    |
     | 88    | 89    | 8A    | 8B    | 8C    | 8D    | 8E    | 8F    | 
     | 90    | 91    | 92    | 93    | 94    | 95    | 96    | 97    |
     | 98    | 99    | 9A    | 9B    | 9C    | 9D    | 9E    | 9F    |
     | A0    | A1    | A2    | A3    | A4    | A5    | A6    | A7    |
     | A8    | A9    | AA JP | AB JP | AC    | AD    | AE    | AF    |
     | B0 KO | B1 KO | B2 KO | B3 KO | B4 KO | B5 KO | B6 KO | B7 KO |
     | B8 KO | B9 KO | BA KO | BB KO | BC KO | BD KO | BE KO | BF KO |
     | C0 KO | C1 KO | C2 KO | C3 KO | C4 KO | C5 KO | C6 KO | C7 KO |
     | C8 KO | C9    | CA HJ | CB HJ | CC HJ | CD HJ | CE HJ | CF HJ |
     | D0 HJ | D1 HJ | D2 HJ | D3 HJ | D4 HJ | D5 HJ | D6 HJ | D7 HJ |
     | D8 HJ | D9 HJ | DA HJ | DB HJ | DC HJ | DD HJ | DE HJ | DF HJ |
     | E0 HJ | E1 HJ | E2 HJ | E3 HJ | E4 HJ | E5 HJ | E6 HJ | E7 HJ |
     | E8 HJ | E9 HJ | EA HJ | EB HJ | EC HJ | ED HJ | EE HJ | EF HJ |
     | F0 HJ | F1 HJ | F2 HJ | F3 HJ | F4 HJ | F5 HJ | F6 HJ | F7 HJ |
     | F8 HJ | F9 HJ | FA HJ | FB HJ | FC HJ | FD HJ | FE    | FF    |
      ---------------------------------------------------------------

*/

/* ASCII 코드 및 한글/한자/일어 첫번째 글자를 위한 테이블 */

static int cType1[] = 
       {
       T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,
       T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,
       T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,
       T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,   T_CK,
       T_BL,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,
       T_SC,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,
       T_DG,   T_DG,   T_DG,   T_DG,   T_DG,   T_DG,   T_DG,   T_DG,
       T_DG,   T_DG,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,
       T_SC,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,
       T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,
       T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,
       T_EN,   T_EN,   T_EN,   T_SC,   T_SC,   T_SC,   T_SC,   T_SC,
       T_SC,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,
       T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,
       T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,   T_EN,
       T_EN,   T_EN,   T_EN,   T_SC,   T_SC,   T_SC,   T_SC,   T_CK,

       T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,
       T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,
       T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,
       T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,   T_U1,
       T_U1,   T_U2,   T_U2,   T_U2,   T_U2,   T_U2,   T_U2,   T_U2,
       T_U2,   T_U2,   T_JP,   T_JP,   T_U2,   T_U1,   T_U1,   T_U1,
       T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,
       T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,
       T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,   T_KO,
       T_KO,   T_U1,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,
       T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,
       T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,
       T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,
       T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,
       T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,
       T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_HJ,   T_U1,   T_U1 
       };

/* Control Key를 출력하기 위한 테이블 */

static  char *CTRLTbl[] = 
        {
	"NUL",		"SOH",		"STX",		"ETX",		"EOT",
	"ENQ",		"ACK",		"BEL",		"BS",		"TAB",
	"LF",		"VT",		"FF",		"CR",		"SO",
	"SI",		"DLE",		"DC1",		"DC2",		"DC3",
	"DC4",		"NAK",		"SYN",		"ETB",		"CAN",
	"EM",		"SUB",		"ESC",		"FS",		"GS",
	"RS",		"US",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"",		"",		"",
	"",		"",		"DEL"   
	};

/* 색인어 형태 및 색인여부를 출력하기 위한 테이블 */

static  TOKGRP	 TokGrp[] = 
	{ {"",	      	'0'},	
	  {"English",  	'1'},	
	  {"Digit",		'1'},
	  {"Special",	'0'},	
	  {"Control",	'0'},	
	  {"Blank",		'0'},
	  {"Korea",		'1'},	
	  {"Chinese",	'1'},	
	  {"Japanese",	'1'},
	  {"Unknown",	'0'} };

