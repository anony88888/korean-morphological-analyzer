/*
 *	Copyright (c) 1999
 *	Choi Sung Pil(SPASIS System Co. LTD), All right reserved.
 *
 *	#(MA_HanCode.h)#           SPASIS System, 29/OCT/1999
 *
 *	#(Action)#
 *		Hangul Code Mapping Array File
 *		WanSung type code : JoHab type code
 */

#ifndef _MA_HANCODE_H_
#define _MA_HANCODE_H_
/*
 *	Hangul Code Mapping Array
 *	WanSung type code : JoHab type code
 */

UWORD cnvt_tbl_jaso[][2] = {
				{ 0xA4A1, 0x8442 },		/*ㄱ*/
				{ 0xA4A2, 0x8443 },		/*ㄲ*/ 
				{ 0xA4A3, 0x8444 },		/*ㄳ*/ 
				{ 0xA4A4, 0x8445 },		/*ㄴ*/ 
				{ 0xA4A5, 0x8446 },		/*ㄵ*/ 
				{ 0xA4A6, 0x8447 },		/*ㄶ*/ 
				{ 0xA4A7, 0x8448 },		/*ㄷ*/ 
				{ 0xA4A8, 0x0 },		/*ㄸ*/ 
				{ 0xA4A9, 0x8449 },		/*ㄹ*/ 
				{ 0xA4AA, 0x844A },		/*ㄺ*/ 
				{ 0xA4AB, 0x844B },		/*ㄻ*/ 
				{ 0xA4AC, 0x844C },		/*ㄼ*/ 
				{ 0xA4AD, 0x844D },		/*ㄽ*/ 
				{ 0xA4AE, 0x844E },		/*ㄾ*/ 
				{ 0xA4AF, 0x844F },		/*ㄿ*/ 
				{ 0xA4B0, 0x8450 },		/*ㅀ*/ 
				{ 0xA4B1, 0x8451 },		/*ㅁ*/ 
				{ 0xA4B2, 0x8453 },		/*ㅂ*/ 
				{ 0xA4B3, 0x0 },		/*ㅃ*/ 
				{ 0xA4B4, 0x8454 },		/*ㅄ*/ 
				{ 0xA4B5, 0x8455 },		/*ㅅ*/ 
				{ 0xA4B6, 0x8456 },		/*ㅆ*/ 
				{ 0xA4B7, 0x8457 },		/*ㅇ*/ 
				{ 0xA4B8, 0x8458 },		/*ㅈ*/ 
				{ 0xA4B9, 0x0 },		/*ㅉ*/ 
				{ 0xA4BA, 0x8459 },		/*ㅊ*/ 
				{ 0xA4BB, 0x845A },		/*ㅋ*/ 
				{ 0xA4BC, 0x845B },		/*ㅌ*/ 
				{ 0xA4BD, 0x845C },		/*ㅍ*/ 
				{ 0xA4BE, 0x845D },		/*ㅎ*/ 
				{ 0xA4BF, 0x8461 },		/*ㅏ*/ 
				{ 0xA4C0, 0x8481 },		/*ㅐ*/ 
				{ 0xA4C1, 0x84A1 },		/*ㅑ*/ 
				{ 0xA4C2, 0x84C1 },		/*ㅒ*/ 
				{ 0xA4C3, 0x84E1 },		/*ㅓ*/ 
				{ 0xA4C4, 0x8541 },		/*ㅔ*/ 
				{ 0xA4C5, 0x8561 },		/*ㅕ*/ 
				{ 0xA4C6, 0x8581 },		/*ㅖ*/ 
				{ 0xA4C7, 0x85A1 },		/*ㅗ*/ 
				{ 0xA4C8, 0x85C1 },		/*ㅘ*/ 
				{ 0xA4C9, 0x85E1 },		/*ㅙ*/ 
				{ 0xA4CA, 0x8641 },		/*ㅚ*/ 
				{ 0xA4CB, 0x8661 },		/*ㅛ*/ 
				{ 0xA4CC, 0x8681 },		/*ㅜ*/ 
				{ 0xA4CD, 0x86A1 },		/*ㅝ*/ 
				{ 0xA4CE, 0x86C1 },		/*ㅞ*/ 
				{ 0xA4CF, 0x86E1 },		/*ㅟ*/ 
				{ 0xA4D0, 0x8741 },		/*ㅠ*/ 
				{ 0xA4D1, 0x8761 },		/*ㅡ*/ 
				{ 0xA4D2, 0x8781 },		/*ㅢ*/ 
				{ 0xA4D3, 0x87A1 },		/*ㅣ*/ 
};

UWORD conv_tbl[][2] = {
                             { 0xB0A1, 0x8861 }, /* KIYEOK A */
                             { 0xB0A2, 0x8862 }, /* KIYEOK A KIYEOK */
                             { 0xB0A3, 0x8865 }, /* KIYEOK A NIEUN */
                             { 0xB0A4, 0x8868 }, /* KIYEOK A TIKEUT */
                             { 0xB0A5, 0x8869 }, /* KIYEOK A RIEUL */
                             { 0xB0A6, 0x886A }, /* KIYEOK A RIEULKIYEOK */
                             { 0xB0A7, 0x886B }, /* KIYEOK A RIEULMIEUM */
                             { 0xB0A8, 0x8871 }, /* KIYEOK A MIEUM */
                             { 0xB0A9, 0x8873 }, /* KIYEOK A PIEUP */
                             { 0xB0AA, 0x8874 }, /* KIYEOK A PIEUPSIOS */
                             { 0xB0AB, 0x8875 }, /* KIYEOK A SIOS */
                             { 0xB0AC, 0x8876 }, /* KIYEOK A SSANGSIOS */
                             { 0xB0AD, 0x8877 }, /* KIYEOK A IEUNG */
                             { 0xB0AE, 0x8878 }, /* KIYEOK A CIEUC */
                             { 0xB0AF, 0x8879 }, /* KIYEOK A CHIEUCH */
                             { 0xB0B0, 0x887B }, /* KIYEOK A THIEUTH */
                             { 0xB0B1, 0x887C }, /* KIYEOK A PHIEUPH */
                             { 0xB0B2, 0x887D }, /* KIYEOK A HIEUH */
                             { 0xB0B3, 0x8881 }, /* KIYEOK AE */
                             { 0xB0B4, 0x8882 }, /* KIYEOK AE KIYEOK */
                             { 0xB0B5, 0x8885 }, /* KIYEOK AE NIEUN */
                             { 0xB0B6, 0x8889 }, /* KIYEOK AE RIEUL */
                             { 0xB0B7, 0x8891 }, /* KIYEOK AE MIEUM */
                             { 0xB0B8, 0x8893 }, /* KIYEOK AE PIEUP */
                             { 0xB0B9, 0x8895 }, /* KIYEOK AE SIOS */
                             { 0xB0BA, 0x8896 }, /* KIYEOK AE SSANGSIOS */
                             { 0xB0BB, 0x8897 }, /* KIYEOK AE IEUNG */
                             { 0xB0BC, 0x88A1 }, /* KIYEOK YA */
                             { 0xB0BD, 0x88A2 }, /* KIYEOK YA KIYEOK */
                             { 0xB0BE, 0x88A5 }, /* KIYEOK YA NIEUN */
                             { 0xB0BF, 0x88A9 }, /* KIYEOK YA RIEUL */
                             { 0xB0C0, 0x88B5 }, /* KIYEOK YA SIOS */
                             { 0xB0C1, 0x88B7 }, /* KIYEOK YA IEUNG */
                             { 0xB0C2, 0x88C1 }, /* KIYEOK YAE */
                             { 0xB0C3, 0x88C5 }, /* KIYEOK YAE NIEUN */
                             { 0xB0C4, 0x88C9 }, /* KIYEOK YAE RIEUL */
                             { 0xB0C5, 0x88E1 }, /* KIYEOK EO */
                             { 0xB0C6, 0x88E2 }, /* KIYEOK EO KIYEOK */
                             { 0xB0C7, 0x88E5 }, /* KIYEOK EO NIEUN */
                             { 0xB0C8, 0x88E8 }, /* KIYEOK EO TIKEUT */
                             { 0xB0C9, 0x88E9 }, /* KIYEOK EO RIEUL */
                             { 0xB0CA, 0x88EB }, /* KIYEOK EO RIEULMIEUM */
                             { 0xB0CB, 0x88F1 }, /* KIYEOK EO MIEUM */
                             { 0xB0CC, 0x88F3 }, /* KIYEOK EO PIEUP */
                             { 0xB0CD, 0x88F5 }, /* KIYEOK EO SIOS */
                             { 0xB0CE, 0x88F6 }, /* KIYEOK EO SSANGSIOS */
                             { 0xB0CF, 0x88F7 }, /* KIYEOK EO IEUNG */
                             { 0xB0D0, 0x88F8 }, /* KIYEOK EO CIEUC */
                             { 0xB0D1, 0x88FB }, /* KIYEOK EO THIEUTH */
                             { 0xB0D2, 0x88FC }, /* KIYEOK EO PHIEUPH */
                             { 0xB0D3, 0x88FD }, /* KIYEOK EO HIEUH */
                             { 0xB0D4, 0x8941 }, /* KIYEOK E */
                             { 0xB0D5, 0x8945 }, /* KIYEOK E NIEUN */
                             { 0xB0D6, 0x8949 }, /* KIYEOK E RIEUL */
                             { 0xB0D7, 0x8951 }, /* KIYEOK E MIEUM */
                             { 0xB0D8, 0x8953 }, /* KIYEOK E PIEUP */
                             { 0xB0D9, 0x8955 }, /* KIYEOK E SIOS */
                             { 0xB0DA, 0x8956 }, /* KIYEOK E SSANGSIOS */
                             { 0xB0DB, 0x8957 }, /* KIYEOK E IEUNG */
                             { 0xB0DC, 0x8961 }, /* KIYEOK YEO */
                             { 0xB0DD, 0x8962 }, /* KIYEOK YEO KIYEOK */
                             { 0xB0DE, 0x8963 }, /* KIYEOK YEO SSANGKIYEOK */
                             { 0xB0DF, 0x8965 }, /* KIYEOK YEO NIEUN */
                             { 0xB0E0, 0x8968 }, /* KIYEOK YEO TIKEUT */
                             { 0xB0E1, 0x8969 }, /* KIYEOK YEO RIEUL */
                             { 0xB0E2, 0x8971 }, /* KIYEOK YEO MIEUM */
                             { 0xB0E3, 0x8973 }, /* KIYEOK YEO PIEUP */
                             { 0xB0E4, 0x8975 }, /* KIYEOK YEO SIOS */
                             { 0xB0E5, 0x8976 }, /* KIYEOK YEO SSANGSIOS */
                             { 0xB0E6, 0x8977 }, /* KIYEOK YEO IEUNG */
                             { 0xB0E7, 0x897B }, /* KIYEOK YEO THIEUTH */
                             { 0xB0E8, 0x8981 }, /* KIYEOK YE */
                             { 0xB0E9, 0x8985 }, /* KIYEOK YE NIEUN */
                             { 0xB0EA, 0x8989 }, /* KIYEOK YE RIEUL */
                             { 0xB0EB, 0x8993 }, /* KIYEOK YE PIEUP */
                             { 0xB0EC, 0x8995 }, /* KIYEOK YE SIOS */
                             { 0xB0ED, 0x89A1 }, /* KIYEOK O */
                             { 0xB0EE, 0x89A2 }, /* KIYEOK O KIYEOK */
                             { 0xB0EF, 0x89A5 }, /* KIYEOK O NIEUN */
                             { 0xB0F0, 0x89A8 }, /* KIYEOK O TIKEUT */
                             { 0xB0F1, 0x89A9 }, /* KIYEOK O RIEUL */
                             { 0xB0F2, 0x89AB }, /* KIYEOK O RIEULMIEUM */
                             { 0xB0F3, 0x89AD }, /* KIYEOK O RIEULSIOS */
                             { 0xB0F4, 0x89B0 }, /* KIYEOK O RIEULHIEUH */
                             { 0xB0F5, 0x89B1 }, /* KIYEOK O MIEUM */
                             { 0xB0F6, 0x89B3 }, /* KIYEOK O PIEUP */
                             { 0xB0F7, 0x89B5 }, /* KIYEOK O SIOS */
                             { 0xB0F8, 0x89B7 }, /* KIYEOK O IEUNG */
                             { 0xB0F9, 0x89B8 }, /* KIYEOK O CIEUC */
                             { 0xB0FA, 0x89C1 }, /* KIYEOK WA */
                             { 0xB0FB, 0x89C2 }, /* KIYEOK WA KIYEOK */
                             { 0xB0FC, 0x89C5 }, /* KIYEOK WA NIEUN */
                             { 0xB0FD, 0x89C9 }, /* KIYEOK WA RIEUL */
                             { 0xB0FE, 0x89CB }, /* KIYEOK WA RIEULMIEUM */
                             { 0xB1A1, 0x89D1 }, /* KIYEOK WA MIEUM */
                             { 0xB1A2, 0x89D3 }, /* KIYEOK WA PIEUP */
                             { 0xB1A3, 0x89D5 }, /* KIYEOK WA SIOS */
                             { 0xB1A4, 0x89D7 }, /* KIYEOK WA IEUNG */
                             { 0xB1A5, 0x89E1 }, /* KIYEOK WAE */
                             { 0xB1A6, 0x89E5 }, /* KIYEOK WAE NIEUN */
                             { 0xB1A7, 0x89E9 }, /* KIYEOK WAE RIEUL */
                             { 0xB1A8, 0x89F3 }, /* KIYEOK WAE PIEUP */
                             { 0xB1A9, 0x89F6 }, /* KIYEOK WAE SSANGSIOS */
                             { 0xB1AA, 0x89F7 }, /* KIYEOK WAE IEUNG */
                             { 0xB1AB, 0x8A41 }, /* KIYEOK OE */
                             { 0xB1AC, 0x8A42 }, /* KIYEOK OE KIYEOK */
                             { 0xB1AD, 0x8A45 }, /* KIYEOK OE NIEUN */
                             { 0xB1AE, 0x8A49 }, /* KIYEOK OE RIEUL */
                             { 0xB1AF, 0x8A51 }, /* KIYEOK OE MIEUM */
                             { 0xB1B0, 0x8A53 }, /* KIYEOK OE PIEUP */
                             { 0xB1B1, 0x8A55 }, /* KIYEOK OE SIOS */
                             { 0xB1B2, 0x8A57 }, /* KIYEOK OE IEUNG */
                             { 0xB1B3, 0x8A61 }, /* KIYEOK YO */
                             { 0xB1B4, 0x8A65 }, /* KIYEOK YO NIEUN */
                             { 0xB1B5, 0x8A69 }, /* KIYEOK YO RIEUL */
                             { 0xB1B6, 0x8A73 }, /* KIYEOK YO PIEUP */
                             { 0xB1B7, 0x8A75 }, /* KIYEOK YO SIOS */
                             { 0xB1B8, 0x8A81 }, /* KIYEOK U */
                             { 0xB1B9, 0x8A82 }, /* KIYEOK U KIYEOK */
                             { 0xB1BA, 0x8A85 }, /* KIYEOK U NIEUN */
                             { 0xB1BB, 0x8A88 }, /* KIYEOK U TIKEUT */
                             { 0xB1BC, 0x8A89 }, /* KIYEOK U RIEUL */
                             { 0xB1BD, 0x8A8A }, /* KIYEOK U RIEULKIYEOK */
                             { 0xB1BE, 0x8A8B }, /* KIYEOK U RIEULMIEUM */
                             { 0xB1BF, 0x8A90 }, /* KIYEOK U RIEULHIEUH */
                             { 0xB1C0, 0x8A91 }, /* KIYEOK U MIEUM */
                             { 0xB1C1, 0x8A93 }, /* KIYEOK U PIEUP */
                             { 0xB1C2, 0x8A95 }, /* KIYEOK U SIOS */
                             { 0xB1C3, 0x8A97 }, /* KIYEOK U IEUNG */
                             { 0xB1C4, 0x8A98 }, /* KIYEOK U CIEUC */
                             { 0xB1C5, 0x8AA1 }, /* KIYEOK WEO */
                             { 0xB1C6, 0x8AA2 }, /* KIYEOK WEO KIYEOK */
                             { 0xB1C7, 0x8AA5 }, /* KIYEOK WEO NIEUN */
                             { 0xB1C8, 0x8AA9 }, /* KIYEOK WEO RIEUL */
                             { 0xB1C9, 0x8AB6 }, /* KIYEOK WEO SSANGSIOS */
                             { 0xB1CA, 0x8AB7 }, /* KIYEOK WEO IEUNG */
                             { 0xB1CB, 0x8AC1 }, /* KIYEOK WE */
                             { 0xB1CC, 0x8AD5 }, /* KIYEOK WE SIOS */
                             { 0xB1CD, 0x8AE1 }, /* KIYEOK WI */
                             { 0xB1CE, 0x8AE2 }, /* KIYEOK WI KIYEOK */
                             { 0xB1CF, 0x8AE5 }, /* KIYEOK WI NIEUN */
                             { 0xB1D0, 0x8AE9 }, /* KIYEOK WI RIEUL */
                             { 0xB1D1, 0x8AF1 }, /* KIYEOK WI MIEUM */
                             { 0xB1D2, 0x8AF3 }, /* KIYEOK WI PIEUP */
                             { 0xB1D3, 0x8AF5 }, /* KIYEOK WI SIOS */
                             { 0xB1D4, 0x8B41 }, /* KIYEOK YU */
                             { 0xB1D5, 0x8B45 }, /* KIYEOK YU NIEUN */
                             { 0xB1D6, 0x8B49 }, /* KIYEOK YU RIEUL */
                             { 0xB1D7, 0x8B61 }, /* KIYEOK EU */
                             { 0xB1D8, 0x8B62 }, /* KIYEOK EU KIYEOK */
                             { 0xB1D9, 0x8B65 }, /* KIYEOK EU NIEUN */
                             { 0xB1DA, 0x8B68 }, /* KIYEOK EU TIKEUT */
                             { 0xB1DB, 0x8B69 }, /* KIYEOK EU RIEUL */
                             { 0xB1DC, 0x8B6A }, /* KIYEOK EU RIEULKIYEOK */
                             { 0xB1DD, 0x8B71 }, /* KIYEOK EU MIEUM */
                             { 0xB1DE, 0x8B73 }, /* KIYEOK EU PIEUP */
                             { 0xB1DF, 0x8B75 }, /* KIYEOK EU SIOS */
                             { 0xB1E0, 0x8B77 }, /* KIYEOK EU IEUNG */
                             { 0xB1E1, 0x8B81 }, /* KIYEOK YI */
                             { 0xB1E2, 0x8BA1 }, /* KIYEOK I */
                             { 0xB1E3, 0x8BA2 }, /* KIYEOK I KIYEOK */
                             { 0xB1E4, 0x8BA5 }, /* KIYEOK I NIEUN */
                             { 0xB1E5, 0x8BA8 }, /* KIYEOK I TIKEUT */
                             { 0xB1E6, 0x8BA9 }, /* KIYEOK I RIEUL */
                             { 0xB1E7, 0x8BAB }, /* KIYEOK I RIEULMIEUM */
                             { 0xB1E8, 0x8BB1 }, /* KIYEOK I MIEUM */
                             { 0xB1E9, 0x8BB3 }, /* KIYEOK I PIEUP */
                             { 0xB1EA, 0x8BB5 }, /* KIYEOK I SIOS */
                             { 0xB1EB, 0x8BB7 }, /* KIYEOK I IEUNG */
                             { 0xB1EC, 0x8BB8 }, /* KIYEOK I CIEUC */
                             { 0xB1ED, 0x8BBC }, /* KIYEOK I PHIEUPH */
                             { 0xB1EE, 0x8C61 }, /* SSANGKIYEOK A */
                             { 0xB1EF, 0x8C62 }, /* SSANGKIYEOK A KIYEOK */
                             { 0xB1F0, 0x8C63 }, /* SSANGKIYEOK A SSANGKIYEOK */
                             { 0xB1F1, 0x8C65 }, /* SSANGKIYEOK A NIEUN */
                             { 0xB1F2, 0x8C69 }, /* SSANGKIYEOK A RIEUL */
                             { 0xB1F3, 0x8C6B }, /* SSANGKIYEOK A RIEULMIEUM */
                             { 0xB1F4, 0x8C71 }, /* SSANGKIYEOK A MIEUM */
                             { 0xB1F5, 0x8C73 }, /* SSANGKIYEOK A PIEUP */
                             { 0xB1F6, 0x8C75 }, /* SSANGKIYEOK A SIOS */
                             { 0xB1F7, 0x8C76 }, /* SSANGKIYEOK A SSANGSIOS */
                             { 0xB1F8, 0x8C77 }, /* SSANGKIYEOK A IEUNG */
                             { 0xB1F9, 0x8C7B }, /* SSANGKIYEOK A THIEUTH */
                             { 0xB1FA, 0x8C81 }, /* SSANGKIYEOK AE */
                             { 0xB1FB, 0x8C82 }, /* SSANGKIYEOK AE KIYEOK */
                             { 0xB1FC, 0x8C85 }, /* SSANGKIYEOK AE NIEUN */
                             { 0xB1FD, 0x8C89 }, /* SSANGKIYEOK AE RIEUL */
                             { 0xB1FE, 0x8C91 }, /* SSANGKIYEOK AE MIEUM */
                             { 0xB2A1, 0x8C93 }, /* SSANGKIYEOK AE PIEUP */
                             { 0xB2A2, 0x8C95 }, /* SSANGKIYEOK AE SIOS */
                             { 0xB2A3, 0x8C96 }, /* SSANGKIYEOK AE SSANGSIOS */
                             { 0xB2A4, 0x8C97 }, /* SSANGKIYEOK AE IEUNG */
                             { 0xB2A5, 0x8CA1 }, /* SSANGKIYEOK YA */
                             { 0xB2A6, 0x8CA2 }, /* SSANGKIYEOK YA KIYEOK */
                             { 0xB2A7, 0x8CA9 }, /* SSANGKIYEOK YA RIEUL */
                             { 0xB2A8, 0x8CE1 }, /* SSANGKIYEOK EO */
                             { 0xB2A9, 0x8CE2 }, /* SSANGKIYEOK EO KIYEOK */
                             { 0xB2AA, 0x8CE3 }, /* SSANGKIYEOK EO SSANGKIYEOK */
                             { 0xB2AB, 0x8CE5 }, /* SSANGKIYEOK EO NIEUN */
                             { 0xB2AC, 0x8CE9 }, /* SSANGKIYEOK EO RIEUL */
                             { 0xB2AD, 0x8CF1 }, /* SSANGKIYEOK EO MIEUM */
                             { 0xB2AE, 0x8CF3 }, /* SSANGKIYEOK EO PIEUP */
                             { 0xB2AF, 0x8CF5 }, /* SSANGKIYEOK EO SIOS */
                             { 0xB2B0, 0x8CF6 }, /* SSANGKIYEOK EO SSANGSIOS */
                             { 0xB2B1, 0x8CF7 }, /* SSANGKIYEOK EO IEUNG */
                             { 0xB2B2, 0x8D41 }, /* SSANGKIYEOK E */
                             { 0xB2B3, 0x8D42 }, /* SSANGKIYEOK E KIYEOK */
                             { 0xB2B4, 0x8D45 }, /* SSANGKIYEOK E NIEUN */
                             { 0xB2B5, 0x8D51 }, /* SSANGKIYEOK E MIEUM */
                             { 0xB2B6, 0x8D55 }, /* SSANGKIYEOK E SIOS */
                             { 0xB2B7, 0x8D57 }, /* SSANGKIYEOK E IEUNG */
                             { 0xB2B8, 0x8D61 }, /* SSANGKIYEOK YEO */
                             { 0xB2B9, 0x8D65 }, /* SSANGKIYEOK YEO NIEUN */
                             { 0xB2BA, 0x8D69 }, /* SSANGKIYEOK YEO RIEUL */
                             { 0xB2BB, 0x8D75 }, /* SSANGKIYEOK YEO SIOS */
                             { 0xB2BC, 0x8D76 }, /* SSANGKIYEOK YEO SSANGSIOS */
                             { 0xB2BD, 0x8D7B }, /* SSANGKIYEOK YEO THIEUTH */
                             { 0xB2BE, 0x8D81 }, /* SSANGKIYEOK YE */
                             { 0xB2BF, 0x8DA1 }, /* SSANGKIYEOK O */
                             { 0xB2C0, 0x8DA2 }, /* SSANGKIYEOK O KIYEOK */
                             { 0xB2C1, 0x8DA5 }, /* SSANGKIYEOK O NIEUN */
                             { 0xB2C2, 0x8DA7 }, /* SSANGKIYEOK O NIEUNHIEUH */
                             { 0xB2C3, 0x8DA9 }, /* SSANGKIYEOK O RIEUL */
                             { 0xB2C4, 0x8DB1 }, /* SSANGKIYEOK O MIEUM */
                             { 0xB2C5, 0x8DB3 }, /* SSANGKIYEOK O PIEUP */
                             { 0xB2C6, 0x8DB5 }, /* SSANGKIYEOK O SIOS */
                             { 0xB2C7, 0x8DB7 }, /* SSANGKIYEOK O IEUNG */
                             { 0xB2C8, 0x8DB8 }, /* SSANGKIYEOK O CIEUC */
                             { 0xB2C9, 0x8DB9 }, /* SSANGKIYEOK O CHIEUCH */
                             { 0xB2CA, 0x8DC1 }, /* SSANGKIYEOK WA */
                             { 0xB2CB, 0x8DC2 }, /* SSANGKIYEOK WA KIYEOK */
                             { 0xB2CC, 0x8DC9 }, /* SSANGKIYEOK WA RIEUL */
                             { 0xB2CD, 0x8DD6 }, /* SSANGKIYEOK WA SSANGSIOS */
                             { 0xB2CE, 0x8DD7 }, /* SSANGKIYEOK WA IEUNG */
                             { 0xB2CF, 0x8DE1 }, /* SSANGKIYEOK WAE */
                             { 0xB2D0, 0x8DE2 }, /* SSANGKIYEOK WAE KIYEOK */
                             { 0xB2D1, 0x8DF7 }, /* SSANGKIYEOK WAE IEUNG */
                             { 0xB2D2, 0x8E41 }, /* SSANGKIYEOK OE */
                             { 0xB2D3, 0x8E45 }, /* SSANGKIYEOK OE NIEUN */
                             { 0xB2D4, 0x8E49 }, /* SSANGKIYEOK OE RIEUL */
                             { 0xB2D5, 0x8E51 }, /* SSANGKIYEOK OE MIEUM */
                             { 0xB2D6, 0x8E53 }, /* SSANGKIYEOK OE PIEUP */
                             { 0xB2D7, 0x8E57 }, /* SSANGKIYEOK OE IEUNG */
                             { 0xB2D8, 0x8E61 }, /* SSANGKIYEOK YO */
                             { 0xB2D9, 0x8E81 }, /* SSANGKIYEOK U */
                             { 0xB2DA, 0x8E82 }, /* SSANGKIYEOK U KIYEOK */
                             { 0xB2DB, 0x8E85 }, /* SSANGKIYEOK U NIEUN */
                             { 0xB2DC, 0x8E89 }, /* SSANGKIYEOK U RIEUL */
                             { 0xB2DD, 0x8E90 }, /* SSANGKIYEOK U RIEULHIEUH */
                             { 0xB2DE, 0x8E91 }, /* SSANGKIYEOK U MIEUM */
                             { 0xB2DF, 0x8E93 }, /* SSANGKIYEOK U PIEUP */
                             { 0xB2E0, 0x8E95 }, /* SSANGKIYEOK U SIOS */
                             { 0xB2E1, 0x8E97 }, /* SSANGKIYEOK U IEUNG */
                             { 0xB2E2, 0x8E98 }, /* SSANGKIYEOK U CIEUC */
                             { 0xB2E3, 0x8EA1 }, /* SSANGKIYEOK WEO */
                             { 0xB2E4, 0x8EA9 }, /* SSANGKIYEOK WEO RIEUL */
                             { 0xB2E5, 0x8EB6 }, /* SSANGKIYEOK WEO SSANGSIOS */
                             { 0xB2E6, 0x8EB7 }, /* SSANGKIYEOK WEO IEUNG */
                             { 0xB2E7, 0x8EC1 }, /* SSANGKIYEOK WE */
                             { 0xB2E8, 0x8EC2 }, /* SSANGKIYEOK WE KIYEOK */
                             { 0xB2E9, 0x8EC5 }, /* SSANGKIYEOK WE NIEUN */
                             { 0xB2EA, 0x8EC9 }, /* SSANGKIYEOK WE RIEUL */
                             { 0xB2EB, 0x8ED1 }, /* SSANGKIYEOK WE MIEUM */
                             { 0xB2EC, 0x8ED3 }, /* SSANGKIYEOK WE PIEUP */
                             { 0xB2ED, 0x8ED6 }, /* SSANGKIYEOK WE SSANGSIOS */
                             { 0xB2EE, 0x8EE1 }, /* SSANGKIYEOK WI */
                             { 0xB2EF, 0x8EE5 }, /* SSANGKIYEOK WI NIEUN */
                             { 0xB2F0, 0x8EE9 }, /* SSANGKIYEOK WI RIEUL */
                             { 0xB2F1, 0x8EF1 }, /* SSANGKIYEOK WI MIEUM */
                             { 0xB2F2, 0x8EF3 }, /* SSANGKIYEOK WI PIEUP */
                             { 0xB2F3, 0x8F41 }, /* SSANGKIYEOK YU */
                             { 0xB2F4, 0x8F61 }, /* SSANGKIYEOK EU */
                             { 0xB2F5, 0x8F62 }, /* SSANGKIYEOK EU KIYEOK */
                             { 0xB2F6, 0x8F65 }, /* SSANGKIYEOK EU NIEUN */
                             { 0xB2F7, 0x8F67 }, /* SSANGKIYEOK EU NIEUNHIEUH */
                             { 0xB2F8, 0x8F69 }, /* SSANGKIYEOK EU RIEUL */
                             { 0xB2F9, 0x8F6B }, /* SSANGKIYEOK EU RIEULMIEUM */
                             { 0xB2FA, 0x8F70 }, /* SSANGKIYEOK EU RIEULHIEUH */
                             { 0xB2FB, 0x8F71 }, /* SSANGKIYEOK EU MIEUM */
                             { 0xB2FC, 0x8F73 }, /* SSANGKIYEOK EU PIEUP */
                             { 0xB2FD, 0x8F75 }, /* SSANGKIYEOK EU SIOS */
                             { 0xB2FE, 0x8F77 }, /* SSANGKIYEOK EU IEUNG */
                             { 0xB3A1, 0x8F7B }, /* SSANGKIYEOK EU THIEUTH */
                             { 0xB3A2, 0x8FA1 }, /* SSANGKIYEOK I */
                             { 0xB3A3, 0x8FA2 }, /* SSANGKIYEOK I KIYEOK */
                             { 0xB3A4, 0x8FA5 }, /* SSANGKIYEOK I NIEUN */
                             { 0xB3A5, 0x8FA9 }, /* SSANGKIYEOK I RIEUL */
                             { 0xB3A6, 0x8FB1 }, /* SSANGKIYEOK I MIEUM */
                             { 0xB3A7, 0x8FB3 }, /* SSANGKIYEOK I PIEUP */
                             { 0xB3A8, 0x8FB5 }, /* SSANGKIYEOK I SIOS */
                             { 0xB3A9, 0x8FB7 }, /* SSANGKIYEOK I IEUNG */
                             { 0xB3AA, 0x9061 }, /* NIEUN A */
                             { 0xB3AB, 0x9062 }, /* NIEUN A KIYEOK */
                             { 0xB3AC, 0x9063 }, /* NIEUN A SSANGKIYEOK */
                             { 0xB3AD, 0x9065 }, /* NIEUN A NIEUN */
                             { 0xB3AE, 0x9068 }, /* NIEUN A TIKEUT */
                             { 0xB3AF, 0x9069 }, /* NIEUN A RIEUL */
                             { 0xB3B0, 0x906A }, /* NIEUN A RIEULKIYEOK */
                             { 0xB3B1, 0x906B }, /* NIEUN A RIEULMIEUM */
                             { 0xB3B2, 0x9071 }, /* NIEUN A MIEUM */
                             { 0xB3B3, 0x9073 }, /* NIEUN A PIEUP */
                             { 0xB3B4, 0x9075 }, /* NIEUN A SIOS */
                             { 0xB3B5, 0x9076 }, /* NIEUN A SSANGSIOS */
                             { 0xB3B6, 0x9077 }, /* NIEUN A IEUNG */
                             { 0xB3B7, 0x9078 }, /* NIEUN A CIEUC */
                             { 0xB3B8, 0x9079 }, /* NIEUN A CHIEUCH */
                             { 0xB3B9, 0x907B }, /* NIEUN A THIEUTH */
                             { 0xB3BA, 0x907D }, /* NIEUN A HIEUH */
                             { 0xB3BB, 0x9081 }, /* NIEUN AE */
                             { 0xB3BC, 0x9082 }, /* NIEUN AE KIYEOK */
                             { 0xB3BD, 0x9085 }, /* NIEUN AE NIEUN */
                             { 0xB3BE, 0x9089 }, /* NIEUN AE RIEUL */
                             { 0xB3BF, 0x9091 }, /* NIEUN AE MIEUM */
                             { 0xB3C0, 0x9093 }, /* NIEUN AE PIEUP */
                             { 0xB3C1, 0x9095 }, /* NIEUN AE SIOS */
                             { 0xB3C2, 0x9096 }, /* NIEUN AE SSANGSIOS */
                             { 0xB3C3, 0x9097 }, /* NIEUN AE IEUNG */
                             { 0xB3C4, 0x90A1 }, /* NIEUN YA */
                             { 0xB3C5, 0x90A2 }, /* NIEUN YA KIYEOK */
                             { 0xB3C6, 0x90A5 }, /* NIEUN YA NIEUN */
                             { 0xB3C7, 0x90A9 }, /* NIEUN YA RIEUL */
                             { 0xB3C8, 0x90B1 }, /* NIEUN YA MIEUM */
                             { 0xB3C9, 0x90B7 }, /* NIEUN YA IEUNG */
                             { 0xB3CA, 0x90E1 }, /* NIEUN EO */
                             { 0xB3CB, 0x90E2 }, /* NIEUN EO KIYEOK */
                             { 0xB3CC, 0x90E4 }, /* NIEUN EO KIYEOKSIOS */
                             { 0xB3CD, 0x90E5 }, /* NIEUN EO NIEUN */
                             { 0xB3CE, 0x90E9 }, /* NIEUN EO RIEUL */
                             { 0xB3CF, 0x90EB }, /* NIEUN EO RIEULMIEUM */
                             { 0xB3D0, 0x90EC }, /* NIEUN EO RIEULPIEUP */
                             { 0xB3D1, 0x90F1 }, /* NIEUN EO MIEUM */
                             { 0xB3D2, 0x90F3 }, /* NIEUN EO PIEUP */
                             { 0xB3D3, 0x90F5 }, /* NIEUN EO SIOS */
                             { 0xB3D4, 0x90F6 }, /* NIEUN EO SSANGSIOS */
                             { 0xB3D5, 0x90F7 }, /* NIEUN EO IEUNG */
                             { 0xB3D6, 0x90FD }, /* NIEUN EO HIEUH */
                             { 0xB3D7, 0x9141 }, /* NIEUN E */
                             { 0xB3D8, 0x9142 }, /* NIEUN E KIYEOK */
                             { 0xB3D9, 0x9145 }, /* NIEUN E NIEUN */
                             { 0xB3DA, 0x9149 }, /* NIEUN E RIEUL */
                             { 0xB3DB, 0x9151 }, /* NIEUN E MIEUM */
                             { 0xB3DC, 0x9153 }, /* NIEUN E PIEUP */
                             { 0xB3DD, 0x9155 }, /* NIEUN E SIOS */
                             { 0xB3DE, 0x9156 }, /* NIEUN E SSANGSIOS */
                             { 0xB3DF, 0x9157 }, /* NIEUN E IEUNG */
                             { 0xB3E0, 0x9161 }, /* NIEUN YEO */
                             { 0xB3E1, 0x9162 }, /* NIEUN YEO KIYEOK */
                             { 0xB3E2, 0x9165 }, /* NIEUN YEO NIEUN */
                             { 0xB3E3, 0x9169 }, /* NIEUN YEO RIEUL */
                             { 0xB3E4, 0x9171 }, /* NIEUN YEO MIEUM */
                             { 0xB3E5, 0x9173 }, /* NIEUN YEO PIEUP */
                             { 0xB3E6, 0x9176 }, /* NIEUN YEO SSANGSIOS */
                             { 0xB3E7, 0x9177 }, /* NIEUN YEO IEUNG */
                             { 0xB3E8, 0x917A }, /* NIEUN YEO KHIEUKH */
                             { 0xB3E9, 0x9181 }, /* NIEUN YE */
                             { 0xB3EA, 0x9185 }, /* NIEUN YE NIEUN */
                             { 0xB3EB, 0x91A1 }, /* NIEUN O */
                             { 0xB3EC, 0x91A2 }, /* NIEUN O KIYEOK */
                             { 0xB3ED, 0x91A5 }, /* NIEUN O NIEUN */
                             { 0xB3EE, 0x91A9 }, /* NIEUN O RIEUL */
                             { 0xB3EF, 0x91AB }, /* NIEUN O RIEULMIEUM */
                             { 0xB3F0, 0x91B1 }, /* NIEUN O MIEUM */
                             { 0xB3F1, 0x91B3 }, /* NIEUN O PIEUP */
                             { 0xB3F2, 0x91B5 }, /* NIEUN O SIOS */
                             { 0xB3F3, 0x91B7 }, /* NIEUN O IEUNG */
                             { 0xB3F4, 0x91BC }, /* NIEUN O PHIEUPH */
                             { 0xB3F5, 0x91BD }, /* NIEUN O HIEUH */
                             { 0xB3F6, 0x91C1 }, /* NIEUN WA */
                             { 0xB3F7, 0x91C5 }, /* NIEUN WA NIEUN */
                             { 0xB3F8, 0x91C9 }, /* NIEUN WA RIEUL */
                             { 0xB3F9, 0x91D6 }, /* NIEUN WA SSANGSIOS */
                             { 0xB3FA, 0x9241 }, /* NIEUN OE */
                             { 0xB3FB, 0x9245 }, /* NIEUN OE NIEUN */
                             { 0xB3FC, 0x9249 }, /* NIEUN OE RIEUL */
                             { 0xB3FD, 0x9251 }, /* NIEUN OE MIEUM */
                             { 0xB3FE, 0x9253 }, /* NIEUN OE PIEUP */
                             { 0xB4A1, 0x9255 }, /* NIEUN OE SIOS */
                             { 0xB4A2, 0x9261 }, /* NIEUN YO */
                             { 0xB4A3, 0x9262 }, /* NIEUN YO KIYEOK */
                             { 0xB4A4, 0x9265 }, /* NIEUN YO NIEUN */
                             { 0xB4A5, 0x9269 }, /* NIEUN YO RIEUL */
                             { 0xB4A6, 0x9273 }, /* NIEUN YO PIEUP */
                             { 0xB4A7, 0x9275 }, /* NIEUN YO SIOS */
                             { 0xB4A8, 0x9277 }, /* NIEUN YO IEUNG */
                             { 0xB4A9, 0x9281 }, /* NIEUN U */
                             { 0xB4AA, 0x9282 }, /* NIEUN U KIYEOK */
                             { 0xB4AB, 0x9285 }, /* NIEUN U NIEUN */
                             { 0xB4AC, 0x9288 }, /* NIEUN U TIKEUT */
                             { 0xB4AD, 0x9289 }, /* NIEUN U RIEUL */
                             { 0xB4AE, 0x9291 }, /* NIEUN U MIEUM */
                             { 0xB4AF, 0x9293 }, /* NIEUN U PIEUP */
                             { 0xB4B0, 0x9295 }, /* NIEUN U SIOS */
                             { 0xB4B1, 0x9297 }, /* NIEUN U IEUNG */
                             { 0xB4B2, 0x92A1 }, /* NIEUN WEO */
                             { 0xB4B3, 0x92B6 }, /* NIEUN WEO SSANGSIOS */
                             { 0xB4B4, 0x92C1 }, /* NIEUN WE */
                             { 0xB4B5, 0x92E1 }, /* NIEUN WI */
                             { 0xB4B6, 0x92E5 }, /* NIEUN WI NIEUN */
                             { 0xB4B7, 0x92E9 }, /* NIEUN WI RIEUL */
                             { 0xB4B8, 0x92F1 }, /* NIEUN WI MIEUM */
                             { 0xB4B9, 0x92F3 }, /* NIEUN WI PIEUP */
                             { 0xB4BA, 0x9341 }, /* NIEUN YU */
                             { 0xB4BB, 0x9342 }, /* NIEUN YU KIYEOK */
                             { 0xB4BC, 0x9349 }, /* NIEUN YU RIEUL */
                             { 0xB4BD, 0x9351 }, /* NIEUN YU MIEUM */
                             { 0xB4BE, 0x9353 }, /* NIEUN YU PIEUP */
                             { 0xB4BF, 0x9357 }, /* NIEUN YU IEUNG */
                             { 0xB4C0, 0x9361 }, /* NIEUN EU */
                             { 0xB4C1, 0x9362 }, /* NIEUN EU KIYEOK */
                             { 0xB4C2, 0x9365 }, /* NIEUN EU NIEUN */
                             { 0xB4C3, 0x9369 }, /* NIEUN EU RIEUL */
                             { 0xB4C4, 0x936A }, /* NIEUN EU RIEULKIYEOK */
                             { 0xB4C5, 0x936B }, /* NIEUN EU RIEULMIEUM */
                             { 0xB4C6, 0x9371 }, /* NIEUN EU MIEUM */
                             { 0xB4C7, 0x9373 }, /* NIEUN EU PIEUP */
                             { 0xB4C8, 0x9375 }, /* NIEUN EU SIOS */
                             { 0xB4C9, 0x9377 }, /* NIEUN EU IEUNG */
                             { 0xB4CA, 0x9378 }, /* NIEUN EU CIEUC */
                             { 0xB4CB, 0x937C }, /* NIEUN EU PHIEUPH */
                             { 0xB4CC, 0x9381 }, /* NIEUN YI */
                             { 0xB4CD, 0x9385 }, /* NIEUN YI NIEUN */
                             { 0xB4CE, 0x9389 }, /* NIEUN YI RIEUL */
                             { 0xB4CF, 0x93A1 }, /* NIEUN I */
                             { 0xB4D0, 0x93A2 }, /* NIEUN I KIYEOK */
                             { 0xB4D1, 0x93A5 }, /* NIEUN I NIEUN */
                             { 0xB4D2, 0x93A9 }, /* NIEUN I RIEUL */
                             { 0xB4D3, 0x93AB }, /* NIEUN I RIEULMIEUM */
                             { 0xB4D4, 0x93B1 }, /* NIEUN I MIEUM */
                             { 0xB4D5, 0x93B3 }, /* NIEUN I PIEUP */
                             { 0xB4D6, 0x93B5 }, /* NIEUN I SIOS */
                             { 0xB4D7, 0x93B7 }, /* NIEUN I IEUNG */
                             { 0xB4D8, 0x93BC }, /* NIEUN I PHIEUPH */
                             { 0xB4D9, 0x9461 }, /* TIKEUT A */
                             { 0xB4DA, 0x9462 }, /* TIKEUT A KIYEOK */
                             { 0xB4DB, 0x9463 }, /* TIKEUT A SSANGKIYEOK */
                             { 0xB4DC, 0x9465 }, /* TIKEUT A NIEUN */
                             { 0xB4DD, 0x9468 }, /* TIKEUT A TIKEUT */
                             { 0xB4DE, 0x9469 }, /* TIKEUT A RIEUL */
                             { 0xB4DF, 0x946A }, /* TIKEUT A RIEULKIYEOK */
                             { 0xB4E0, 0x946B }, /* TIKEUT A RIEULMIEUM */
                             { 0xB4E1, 0x946C }, /* TIKEUT A RIEULPIEUP */
                             { 0xB4E2, 0x9470 }, /* TIKEUT A RIEULHIEUH */
                             { 0xB4E3, 0x9471 }, /* TIKEUT A MIEUM */
                             { 0xB4E4, 0x9473 }, /* TIKEUT A PIEUP */
                             { 0xB4E5, 0x9475 }, /* TIKEUT A SIOS */
                             { 0xB4E6, 0x9476 }, /* TIKEUT A SSANGSIOS */
                             { 0xB4E7, 0x9477 }, /* TIKEUT A IEUNG */
                             { 0xB4E8, 0x9478 }, /* TIKEUT A CIEUC */
                             { 0xB4E9, 0x9479 }, /* TIKEUT A CHIEUCH */
                             { 0xB4EA, 0x947D }, /* TIKEUT A HIEUH */
                             { 0xB4EB, 0x9481 }, /* TIKEUT AE */
                             { 0xB4EC, 0x9482 }, /* TIKEUT AE KIYEOK */
                             { 0xB4ED, 0x9485 }, /* TIKEUT AE NIEUN */
                             { 0xB4EE, 0x9489 }, /* TIKEUT AE RIEUL */
                             { 0xB4EF, 0x9491 }, /* TIKEUT AE MIEUM */
                             { 0xB4F0, 0x9493 }, /* TIKEUT AE PIEUP */
                             { 0xB4F1, 0x9495 }, /* TIKEUT AE SIOS */
                             { 0xB4F2, 0x9496 }, /* TIKEUT AE SSANGSIOS */
                             { 0xB4F3, 0x9497 }, /* TIKEUT AE IEUNG */
                             { 0xB4F4, 0x94A1 }, /* TIKEUT YA */
                             { 0xB4F5, 0x94E1 }, /* TIKEUT EO */
                             { 0xB4F6, 0x94E2 }, /* TIKEUT EO KIYEOK */
                             { 0xB4F7, 0x94E3 }, /* TIKEUT EO SSANGKIYEOK */
                             { 0xB4F8, 0x94E5 }, /* TIKEUT EO NIEUN */
                             { 0xB4F9, 0x94E8 }, /* TIKEUT EO TIKEUT */
                             { 0xB4FA, 0x94E9 }, /* TIKEUT EO RIEUL */
                             { 0xB4FB, 0x94EB }, /* TIKEUT EO RIEULMIEUM */
                             { 0xB4FC, 0x94EC }, /* TIKEUT EO RIEULPIEUP */
                             { 0xB4FD, 0x94F1 }, /* TIKEUT EO MIEUM */
                             { 0xB4FE, 0x94F3 }, /* TIKEUT EO PIEUP */
                             { 0xB5A1, 0x94F5 }, /* TIKEUT EO SIOS */
                             { 0xB5A2, 0x94F7 }, /* TIKEUT EO IEUNG */
                             { 0xB5A3, 0x94F9 }, /* TIKEUT EO CHIEUCH */
                             { 0xB5A4, 0x94FC }, /* TIKEUT EO PHIEUPH */
                             { 0xB5A5, 0x9541 }, /* TIKEUT E */
                             { 0xB5A6, 0x9542 }, /* TIKEUT E KIYEOK */
                             { 0xB5A7, 0x9545 }, /* TIKEUT E NIEUN */
                             { 0xB5A8, 0x9549 }, /* TIKEUT E RIEUL */
                             { 0xB5A9, 0x9551 }, /* TIKEUT E MIEUM */
                             { 0xB5AA, 0x9553 }, /* TIKEUT E PIEUP */
                             { 0xB5AB, 0x9555 }, /* TIKEUT E SIOS */
                             { 0xB5AC, 0x9556 }, /* TIKEUT E SSANGSIOS */
                             { 0xB5AD, 0x9557 }, /* TIKEUT E IEUNG */
                             { 0xB5AE, 0x9561 }, /* TIKEUT YEO */
                             { 0xB5AF, 0x9565 }, /* TIKEUT YEO NIEUN */
                             { 0xB5B0, 0x9569 }, /* TIKEUT YEO RIEUL */
                             { 0xB5B1, 0x9576 }, /* TIKEUT YEO SSANGSIOS */
                             { 0xB5B2, 0x9577 }, /* TIKEUT YEO IEUNG */
                             { 0xB5B3, 0x9581 }, /* TIKEUT YE */
                             { 0xB5B4, 0x9585 }, /* TIKEUT YE NIEUN */
                             { 0xB5B5, 0x95A1 }, /* TIKEUT O */
                             { 0xB5B6, 0x95A2 }, /* TIKEUT O KIYEOK */
                             { 0xB5B7, 0x95A5 }, /* TIKEUT O NIEUN */
                             { 0xB5B8, 0x95A8 }, /* TIKEUT O TIKEUT */
                             { 0xB5B9, 0x95A9 }, /* TIKEUT O RIEUL */
                             { 0xB5BA, 0x95AB }, /* TIKEUT O RIEULMIEUM */
                             { 0xB5BB, 0x95AD }, /* TIKEUT O RIEULSIOS */
                             { 0xB5BC, 0x95B1 }, /* TIKEUT O MIEUM */
                             { 0xB5BD, 0x95B3 }, /* TIKEUT O PIEUP */
                             { 0xB5BE, 0x95B5 }, /* TIKEUT O SIOS */
                             { 0xB5BF, 0x95B7 }, /* TIKEUT O IEUNG */
                             { 0xB5C0, 0x95B9 }, /* TIKEUT O CHIEUCH */
                             { 0xB5C1, 0x95BB }, /* TIKEUT O THIEUTH */
                             { 0xB5C2, 0x95C1 }, /* TIKEUT WA */
                             { 0xB5C3, 0x95C5 }, /* TIKEUT WA NIEUN */
                             { 0xB5C4, 0x95C9 }, /* TIKEUT WA RIEUL */
                             { 0xB5C5, 0x95E1 }, /* TIKEUT WAE */
                             { 0xB5C6, 0x95F6 }, /* TIKEUT WAE SSANGSIOS */
                             { 0xB5C7, 0x9641 }, /* TIKEUT OE */
                             { 0xB5C8, 0x9645 }, /* TIKEUT OE NIEUN */
                             { 0xB5C9, 0x9649 }, /* TIKEUT OE RIEUL */
                             { 0xB5CA, 0x9651 }, /* TIKEUT OE MIEUM */
                             { 0xB5CB, 0x9653 }, /* TIKEUT OE PIEUP */
                             { 0xB5CC, 0x9655 }, /* TIKEUT OE SIOS */
                             { 0xB5CD, 0x9661 }, /* TIKEUT YO */
                             { 0xB5CE, 0x9681 }, /* TIKEUT U */
                             { 0xB5CF, 0x9682 }, /* TIKEUT U KIYEOK */
                             { 0xB5D0, 0x9685 }, /* TIKEUT U NIEUN */
                             { 0xB5D1, 0x9689 }, /* TIKEUT U RIEUL */
                             { 0xB5D2, 0x9691 }, /* TIKEUT U MIEUM */
                             { 0xB5D3, 0x9693 }, /* TIKEUT U PIEUP */
                             { 0xB5D4, 0x9695 }, /* TIKEUT U SIOS */
                             { 0xB5D5, 0x9697 }, /* TIKEUT U IEUNG */
                             { 0xB5D6, 0x96A1 }, /* TIKEUT WEO */
                             { 0xB5D7, 0x96B6 }, /* TIKEUT WEO SSANGSIOS */
                             { 0xB5D8, 0x96C1 }, /* TIKEUT WE */
                             { 0xB5D9, 0x96D7 }, /* TIKEUT WE IEUNG */
                             { 0xB5DA, 0x96E1 }, /* TIKEUT WI */
                             { 0xB5DB, 0x96E5 }, /* TIKEUT WI NIEUN */
                             { 0xB5DC, 0x96E9 }, /* TIKEUT WI RIEUL */
                             { 0xB5DD, 0x96F3 }, /* TIKEUT WI PIEUP */
                             { 0xB5DE, 0x96F5 }, /* TIKEUT WI SIOS */
                             { 0xB5DF, 0x96F7 }, /* TIKEUT WI IEUNG */
                             { 0xB5E0, 0x9741 }, /* TIKEUT YU */
                             { 0xB5E1, 0x9745 }, /* TIKEUT YU NIEUN */
                             { 0xB5E2, 0x9749 }, /* TIKEUT YU RIEUL */
                             { 0xB5E3, 0x9751 }, /* TIKEUT YU MIEUM */
                             { 0xB5E4, 0x9757 }, /* TIKEUT YU IEUNG */
                             { 0xB5E5, 0x9761 }, /* TIKEUT EU */
                             { 0xB5E6, 0x9762 }, /* TIKEUT EU KIYEOK */
                             { 0xB5E7, 0x9765 }, /* TIKEUT EU NIEUN */
                             { 0xB5E8, 0x9768 }, /* TIKEUT EU TIKEUT */
                             { 0xB5E9, 0x9769 }, /* TIKEUT EU RIEUL */
                             { 0xB5EA, 0x976B }, /* TIKEUT EU RIEULMIEUM */
                             { 0xB5EB, 0x9771 }, /* TIKEUT EU MIEUM */
                             { 0xB5EC, 0x9773 }, /* TIKEUT EU PIEUP */
                             { 0xB5ED, 0x9775 }, /* TIKEUT EU SIOS */
                             { 0xB5EE, 0x9777 }, /* TIKEUT EU IEUNG */
                             { 0xB5EF, 0x9781 }, /* TIKEUT YI */
                             { 0xB5F0, 0x97A1 }, /* TIKEUT I */
                             { 0xB5F1, 0x97A2 }, /* TIKEUT I KIYEOK */
                             { 0xB5F2, 0x97A5 }, /* TIKEUT I NIEUN */
                             { 0xB5F3, 0x97A8 }, /* TIKEUT I TIKEUT */
                             { 0xB5F4, 0x97A9 }, /* TIKEUT I RIEUL */
                             { 0xB5F5, 0x97B1 }, /* TIKEUT I MIEUM */
                             { 0xB5F6, 0x97B3 }, /* TIKEUT I PIEUP */
                             { 0xB5F7, 0x97B5 }, /* TIKEUT I SIOS */
                             { 0xB5F8, 0x97B6 }, /* TIKEUT I SSANGSIOS */
                             { 0xB5F9, 0x97B7 }, /* TIKEUT I IEUNG */
                             { 0xB5FA, 0x97B8 }, /* TIKEUT I CIEUC */
                             { 0xB5FB, 0x9861 }, /* SSANGTIKEUT A */
                             { 0xB5FC, 0x9862 }, /* SSANGTIKEUT A KIYEOK */
                             { 0xB5FD, 0x9865 }, /* SSANGTIKEUT A NIEUN */
                             { 0xB5FE, 0x9869 }, /* SSANGTIKEUT A RIEUL */
                             { 0xB6A1, 0x9871 }, /* SSANGTIKEUT A MIEUM */
                             { 0xB6A2, 0x9873 }, /* SSANGTIKEUT A PIEUP */
                             { 0xB6A3, 0x9875 }, /* SSANGTIKEUT A SIOS */
                             { 0xB6A4, 0x9876 }, /* SSANGTIKEUT A SSANGSIOS */
                             { 0xB6A5, 0x9877 }, /* SSANGTIKEUT A IEUNG */
                             { 0xB6A6, 0x987D }, /* SSANGTIKEUT A HIEUH */
                             { 0xB6A7, 0x9881 }, /* SSANGTIKEUT AE */
                             { 0xB6A8, 0x9882 }, /* SSANGTIKEUT AE KIYEOK */
                             { 0xB6A9, 0x9885 }, /* SSANGTIKEUT AE NIEUN */
                             { 0xB6AA, 0x9889 }, /* SSANGTIKEUT AE RIEUL */
                             { 0xB6AB, 0x9891 }, /* SSANGTIKEUT AE MIEUM */
                             { 0xB6AC, 0x9893 }, /* SSANGTIKEUT AE PIEUP */
                             { 0xB6AD, 0x9895 }, /* SSANGTIKEUT AE SIOS */
                             { 0xB6AE, 0x9896 }, /* SSANGTIKEUT AE SSANGSIOS */
                             { 0xB6AF, 0x9897 }, /* SSANGTIKEUT AE IEUNG */
                             { 0xB6B0, 0x98E1 }, /* SSANGTIKEUT EO */
                             { 0xB6B1, 0x98E2 }, /* SSANGTIKEUT EO KIYEOK */
                             { 0xB6B2, 0x98E5 }, /* SSANGTIKEUT EO NIEUN */
                             { 0xB6B3, 0x98E9 }, /* SSANGTIKEUT EO RIEUL */
                             { 0xB6B4, 0x98EB }, /* SSANGTIKEUT EO RIEULMIEUM */
                             { 0xB6B5, 0x98EC }, /* SSANGTIKEUT EO RIEULPIEUP */
                             { 0xB6B6, 0x98F1 }, /* SSANGTIKEUT EO MIEUM */
                             { 0xB6B7, 0x98F3 }, /* SSANGTIKEUT EO PIEUP */
                             { 0xB6B8, 0x98F5 }, /* SSANGTIKEUT EO SIOS */
                             { 0xB6B9, 0x98F6 }, /* SSANGTIKEUT EO SSANGSIOS */
                             { 0xB6BA, 0x98F7 }, /* SSANGTIKEUT EO IEUNG */
                             { 0xB6BB, 0x98FD }, /* SSANGTIKEUT EO HIEUH */
                             { 0xB6BC, 0x9941 }, /* SSANGTIKEUT E */
                             { 0xB6BD, 0x9942 }, /* SSANGTIKEUT E KIYEOK */
                             { 0xB6BE, 0x9945 }, /* SSANGTIKEUT E NIEUN */
                             { 0xB6BF, 0x9949 }, /* SSANGTIKEUT E RIEUL */
                             { 0xB6C0, 0x9951 }, /* SSANGTIKEUT E MIEUM */
                             { 0xB6C1, 0x9953 }, /* SSANGTIKEUT E PIEUP */
                             { 0xB6C2, 0x9955 }, /* SSANGTIKEUT E SIOS */
                             { 0xB6C3, 0x9956 }, /* SSANGTIKEUT E SSANGSIOS */
                             { 0xB6C4, 0x9957 }, /* SSANGTIKEUT E IEUNG */
                             { 0xB6C5, 0x9961 }, /* SSANGTIKEUT YEO */
                             { 0xB6C6, 0x9976 }, /* SSANGTIKEUT YEO SSANGSIOS */
                             { 0xB6C7, 0x99A1 }, /* SSANGTIKEUT O */
                             { 0xB6C8, 0x99A2 }, /* SSANGTIKEUT O KIYEOK */
                             { 0xB6C9, 0x99A5 }, /* SSANGTIKEUT O NIEUN */
                             { 0xB6CA, 0x99A9 }, /* SSANGTIKEUT O RIEUL */
                             { 0xB6CB, 0x99B7 }, /* SSANGTIKEUT O IEUNG */
                             { 0xB6CC, 0x99C1 }, /* SSANGTIKEUT WA */
                             { 0xB6CD, 0x99C9 }, /* SSANGTIKEUT WA RIEUL */
                             { 0xB6CE, 0x99E1 }, /* SSANGTIKEUT WAE */
                             { 0xB6CF, 0x9A41 }, /* SSANGTIKEUT OE */
                             { 0xB6D0, 0x9A45 }, /* SSANGTIKEUT OE NIEUN */
                             { 0xB6D1, 0x9A81 }, /* SSANGTIKEUT U */
                             { 0xB6D2, 0x9A82 }, /* SSANGTIKEUT U KIYEOK */
                             { 0xB6D3, 0x9A85 }, /* SSANGTIKEUT U NIEUN */
                             { 0xB6D4, 0x9A89 }, /* SSANGTIKEUT U RIEUL */
                             { 0xB6D5, 0x9A90 }, /* SSANGTIKEUT U RIEULHIEUH */
                             { 0xB6D6, 0x9A91 }, /* SSANGTIKEUT U MIEUM */
                             { 0xB6D7, 0x9A97 }, /* SSANGTIKEUT U IEUNG */
                             { 0xB6D8, 0x9AC1 }, /* SSANGTIKEUT WE */
                             { 0xB6D9, 0x9AE1 }, /* SSANGTIKEUT WI */
                             { 0xB6DA, 0x9AE5 }, /* SSANGTIKEUT WI NIEUN */
                             { 0xB6DB, 0x9AE9 }, /* SSANGTIKEUT WI RIEUL */
                             { 0xB6DC, 0x9AF1 }, /* SSANGTIKEUT WI MIEUM */
                             { 0xB6DD, 0x9AF3 }, /* SSANGTIKEUT WI PIEUP */
                             { 0xB6DE, 0x9AF7 }, /* SSANGTIKEUT WI IEUNG */
                             { 0xB6DF, 0x9B61 }, /* SSANGTIKEUT EU */
                             { 0xB6E0, 0x9B62 }, /* SSANGTIKEUT EU KIYEOK */
                             { 0xB6E1, 0x9B65 }, /* SSANGTIKEUT EU NIEUN */
                             { 0xB6E2, 0x9B68 }, /* SSANGTIKEUT EU TIKEUT */
                             { 0xB6E3, 0x9B69 }, /* SSANGTIKEUT EU RIEUL */
                             { 0xB6E4, 0x9B71 }, /* SSANGTIKEUT EU MIEUM */
                             { 0xB6E5, 0x9B73 }, /* SSANGTIKEUT EU PIEUP */
                             { 0xB6E6, 0x9B75 }, /* SSANGTIKEUT EU SIOS */
                             { 0xB6E7, 0x9B81 }, /* SSANGTIKEUT YI */
                             { 0xB6E8, 0x9B85 }, /* SSANGTIKEUT YI NIEUN */
                             { 0xB6E9, 0x9B89 }, /* SSANGTIKEUT YI RIEUL */
                             { 0xB6EA, 0x9B91 }, /* SSANGTIKEUT YI MIEUM */
                             { 0xB6EB, 0x9B93 }, /* SSANGTIKEUT YI PIEUP */
                             { 0xB6EC, 0x9BA1 }, /* SSANGTIKEUT I */
                             { 0xB6ED, 0x9BA5 }, /* SSANGTIKEUT I NIEUN */
                             { 0xB6EE, 0x9BA9 }, /* SSANGTIKEUT I RIEUL */
                             { 0xB6EF, 0x9BB1 }, /* SSANGTIKEUT I MIEUM */
                             { 0xB6F0, 0x9BB3 }, /* SSANGTIKEUT I PIEUP */
                             { 0xB6F1, 0x9BB5 }, /* SSANGTIKEUT I SIOS */
                             { 0xB6F2, 0x9BB7 }, /* SSANGTIKEUT I IEUNG */
                             { 0xB6F3, 0x9C61 }, /* RIEUL A */
                             { 0xB6F4, 0x9C62 }, /* RIEUL A KIYEOK */
                             { 0xB6F5, 0x9C65 }, /* RIEUL A NIEUN */
                             { 0xB6F6, 0x9C69 }, /* RIEUL A RIEUL */
                             { 0xB6F7, 0x9C71 }, /* RIEUL A MIEUM */
                             { 0xB6F8, 0x9C73 }, /* RIEUL A PIEUP */
                             { 0xB6F9, 0x9C75 }, /* RIEUL A SIOS */
                             { 0xB6FA, 0x9C76 }, /* RIEUL A SSANGSIOS */
                             { 0xB6FB, 0x9C77 }, /* RIEUL A IEUNG */
                             { 0xB6FC, 0x9C78 }, /* RIEUL A CIEUC */
                             { 0xB6FD, 0x9C7C }, /* RIEUL A PHIEUPH */
                             { 0xB6FE, 0x9C7D }, /* RIEUL A HIEUH */
                             { 0xB7A1, 0x9C81 }, /* RIEUL AE */
                             { 0xB7A2, 0x9C82 }, /* RIEUL AE KIYEOK */
                             { 0xB7A3, 0x9C85 }, /* RIEUL AE NIEUN */
                             { 0xB7A4, 0x9C89 }, /* RIEUL AE RIEUL */
                             { 0xB7A5, 0x9C91 }, /* RIEUL AE MIEUM */
                             { 0xB7A6, 0x9C93 }, /* RIEUL AE PIEUP */
                             { 0xB7A7, 0x9C95 }, /* RIEUL AE SIOS */
                             { 0xB7A8, 0x9C96 }, /* RIEUL AE SSANGSIOS */
                             { 0xB7A9, 0x9C97 }, /* RIEUL AE IEUNG */
                             { 0xB7AA, 0x9CA1 }, /* RIEUL YA */
                             { 0xB7AB, 0x9CA2 }, /* RIEUL YA KIYEOK */
                             { 0xB7AC, 0x9CA5 }, /* RIEUL YA NIEUN */
                             { 0xB7AD, 0x9CB5 }, /* RIEUL YA SIOS */
                             { 0xB7AE, 0x9CB7 }, /* RIEUL YA IEUNG */
                             { 0xB7AF, 0x9CE1 }, /* RIEUL EO */
                             { 0xB7B0, 0x9CE2 }, /* RIEUL EO KIYEOK */
                             { 0xB7B1, 0x9CE5 }, /* RIEUL EO NIEUN */
                             { 0xB7B2, 0x9CE9 }, /* RIEUL EO RIEUL */
                             { 0xB7B3, 0x9CF1 }, /* RIEUL EO MIEUM */
                             { 0xB7B4, 0x9CF3 }, /* RIEUL EO PIEUP */
                             { 0xB7B5, 0x9CF5 }, /* RIEUL EO SIOS */
                             { 0xB7B6, 0x9CF6 }, /* RIEUL EO SSANGSIOS */
                             { 0xB7B7, 0x9CF7 }, /* RIEUL EO IEUNG */
                             { 0xB7B8, 0x9CFD }, /* RIEUL EO HIEUH */
                             { 0xB7B9, 0x9D41 }, /* RIEUL E */
                             { 0xB7BA, 0x9D42 }, /* RIEUL E KIYEOK */
                             { 0xB7BB, 0x9D45 }, /* RIEUL E NIEUN */
                             { 0xB7BC, 0x9D49 }, /* RIEUL E RIEUL */
                             { 0xB7BD, 0x9D51 }, /* RIEUL E MIEUM */
                             { 0xB7BE, 0x9D53 }, /* RIEUL E PIEUP */
                             { 0xB7BF, 0x9D55 }, /* RIEUL E SIOS */
                             { 0xB7C0, 0x9D57 }, /* RIEUL E IEUNG */
                             { 0xB7C1, 0x9D61 }, /* RIEUL YEO */
                             { 0xB7C2, 0x9D62 }, /* RIEUL YEO KIYEOK */
                             { 0xB7C3, 0x9D65 }, /* RIEUL YEO NIEUN */
                             { 0xB7C4, 0x9D69 }, /* RIEUL YEO RIEUL */
                             { 0xB7C5, 0x9D71 }, /* RIEUL YEO MIEUM */
                             { 0xB7C6, 0x9D73 }, /* RIEUL YEO PIEUP */
                             { 0xB7C7, 0x9D75 }, /* RIEUL YEO SIOS */
                             { 0xB7C8, 0x9D76 }, /* RIEUL YEO SSANGSIOS */
                             { 0xB7C9, 0x9D77 }, /* RIEUL YEO IEUNG */
                             { 0xB7CA, 0x9D81 }, /* RIEUL YE */
                             { 0xB7CB, 0x9D85 }, /* RIEUL YE NIEUN */
                             { 0xB7CC, 0x9D93 }, /* RIEUL YE PIEUP */
                             { 0xB7CD, 0x9D95 }, /* RIEUL YE SIOS */
                             { 0xB7CE, 0x9DA1 }, /* RIEUL O */
                             { 0xB7CF, 0x9DA2 }, /* RIEUL O KIYEOK */
                             { 0xB7D0, 0x9DA5 }, /* RIEUL O NIEUN */
                             { 0xB7D1, 0x9DA9 }, /* RIEUL O RIEUL */
                             { 0xB7D2, 0x9DB1 }, /* RIEUL O MIEUM */
                             { 0xB7D3, 0x9DB3 }, /* RIEUL O PIEUP */
                             { 0xB7D4, 0x9DB5 }, /* RIEUL O SIOS */
                             { 0xB7D5, 0x9DB7 }, /* RIEUL O IEUNG */
                             { 0xB7D6, 0x9DC1 }, /* RIEUL WA */
                             { 0xB7D7, 0x9DC5 }, /* RIEUL WA NIEUN */
                             { 0xB7D8, 0x9DD7 }, /* RIEUL WA IEUNG */
                             { 0xB7D9, 0x9DF6 }, /* RIEUL WAE SSANGSIOS */
                             { 0xB7DA, 0x9E41 }, /* RIEUL OE */
                             { 0xB7DB, 0x9E45 }, /* RIEUL OE NIEUN */
                             { 0xB7DC, 0x9E49 }, /* RIEUL OE RIEUL */
                             { 0xB7DD, 0x9E51 }, /* RIEUL OE MIEUM */
                             { 0xB7DE, 0x9E53 }, /* RIEUL OE PIEUP */
                             { 0xB7DF, 0x9E55 }, /* RIEUL OE SIOS */
                             { 0xB7E0, 0x9E57 }, /* RIEUL OE IEUNG */
                             { 0xB7E1, 0x9E61 }, /* RIEUL YO */
                             { 0xB7E2, 0x9E65 }, /* RIEUL YO NIEUN */
                             { 0xB7E3, 0x9E69 }, /* RIEUL YO RIEUL */
                             { 0xB7E4, 0x9E73 }, /* RIEUL YO PIEUP */
                             { 0xB7E5, 0x9E75 }, /* RIEUL YO SIOS */
                             { 0xB7E6, 0x9E77 }, /* RIEUL YO IEUNG */
                             { 0xB7E7, 0x9E81 }, /* RIEUL U */
                             { 0xB7E8, 0x9E82 }, /* RIEUL U KIYEOK */
                             { 0xB7E9, 0x9E85 }, /* RIEUL U NIEUN */
                             { 0xB7EA, 0x9E89 }, /* RIEUL U RIEUL */
                             { 0xB7EB, 0x9E91 }, /* RIEUL U MIEUM */
                             { 0xB7EC, 0x9E93 }, /* RIEUL U PIEUP */
                             { 0xB7ED, 0x9E95 }, /* RIEUL U SIOS */
                             { 0xB7EE, 0x9E97 }, /* RIEUL U IEUNG */
                             { 0xB7EF, 0x9EA1 }, /* RIEUL WEO */
                             { 0xB7F0, 0x9EB6 }, /* RIEUL WEO SSANGSIOS */
                             { 0xB7F1, 0x9EC1 }, /* RIEUL WE */
                             { 0xB7F2, 0x9EE1 }, /* RIEUL WI */
                             { 0xB7F3, 0x9EE2 }, /* RIEUL WI KIYEOK */
                             { 0xB7F4, 0x9EE5 }, /* RIEUL WI NIEUN */
                             { 0xB7F5, 0x9EE9 }, /* RIEUL WI RIEUL */
                             { 0xB7F6, 0x9EF1 }, /* RIEUL WI MIEUM */
                             { 0xB7F7, 0x9EF5 }, /* RIEUL WI SIOS */
                             { 0xB7F8, 0x9EF7 }, /* RIEUL WI IEUNG */
                             { 0xB7F9, 0x9F41 }, /* RIEUL YU */
                             { 0xB7FA, 0x9F42 }, /* RIEUL YU KIYEOK */
                             { 0xB7FB, 0x9F45 }, /* RIEUL YU NIEUN */
                             { 0xB7FC, 0x9F49 }, /* RIEUL YU RIEUL */
                             { 0xB7FD, 0x9F51 }, /* RIEUL YU MIEUM */
                             { 0xB7FE, 0x9F53 }, /* RIEUL YU PIEUP */
                             { 0xB8A1, 0x9F55 }, /* RIEUL YU SIOS */
                             { 0xB8A2, 0x9F57 }, /* RIEUL YU IEUNG */
                             { 0xB8A3, 0x9F61 }, /* RIEUL EU */
                             { 0xB8A4, 0x9F62 }, /* RIEUL EU KIYEOK */
                             { 0xB8A5, 0x9F65 }, /* RIEUL EU NIEUN */
                             { 0xB8A6, 0x9F69 }, /* RIEUL EU RIEUL */
                             { 0xB8A7, 0x9F71 }, /* RIEUL EU MIEUM */
                             { 0xB8A8, 0x9F73 }, /* RIEUL EU PIEUP */
                             { 0xB8A9, 0x9F75 }, /* RIEUL EU SIOS */
                             { 0xB8AA, 0x9F77 }, /* RIEUL EU IEUNG */
                             { 0xB8AB, 0x9F78 }, /* RIEUL EU CIEUC */
                             { 0xB8AC, 0x9F7B }, /* RIEUL EU THIEUTH */
                             { 0xB8AD, 0x9F7C }, /* RIEUL EU PHIEUPH */
                             { 0xB8AE, 0x9FA1 }, /* RIEUL I */
                             { 0xB8AF, 0x9FA2 }, /* RIEUL I KIYEOK */
                             { 0xB8B0, 0x9FA5 }, /* RIEUL I NIEUN */
                             { 0xB8B1, 0x9FA9 }, /* RIEUL I RIEUL */
                             { 0xB8B2, 0x9FB1 }, /* RIEUL I MIEUM */
                             { 0xB8B3, 0x9FB3 }, /* RIEUL I PIEUP */
                             { 0xB8B4, 0x9FB5 }, /* RIEUL I SIOS */
                             { 0xB8B5, 0x9FB7 }, /* RIEUL I IEUNG */
                             { 0xB8B6, 0xA061 }, /* MIEUM A */
                             { 0xB8B7, 0xA062 }, /* MIEUM A KIYEOK */
                             { 0xB8B8, 0xA065 }, /* MIEUM A NIEUN */
                             { 0xB8B9, 0xA067 }, /* MIEUM A NIEUNHIEUH */
                             { 0xB8BA, 0xA068 }, /* MIEUM A TIKEUT */
                             { 0xB8BB, 0xA069 }, /* MIEUM A RIEUL */
                             { 0xB8BC, 0xA06A }, /* MIEUM A RIEULKIYEOK */
                             { 0xB8BD, 0xA06B }, /* MIEUM A RIEULMIEUM */
                             { 0xB8BE, 0xA071 }, /* MIEUM A MIEUM */
                             { 0xB8BF, 0xA073 }, /* MIEUM A PIEUP */
                             { 0xB8C0, 0xA075 }, /* MIEUM A SIOS */
                             { 0xB8C1, 0xA077 }, /* MIEUM A IEUNG */
                             { 0xB8C2, 0xA078 }, /* MIEUM A CIEUC */
                             { 0xB8C3, 0xA07B }, /* MIEUM A THIEUTH */
                             { 0xB8C4, 0xA07D }, /* MIEUM A HIEUH */
                             { 0xB8C5, 0xA081 }, /* MIEUM AE */
                             { 0xB8C6, 0xA082 }, /* MIEUM AE KIYEOK */
                             { 0xB8C7, 0xA085 }, /* MIEUM AE NIEUN */
                             { 0xB8C8, 0xA089 }, /* MIEUM AE RIEUL */
                             { 0xB8C9, 0xA091 }, /* MIEUM AE MIEUM */
                             { 0xB8CA, 0xA093 }, /* MIEUM AE PIEUP */
                             { 0xB8CB, 0xA095 }, /* MIEUM AE SIOS */
                             { 0xB8CC, 0xA096 }, /* MIEUM AE SSANGSIOS */
                             { 0xB8CD, 0xA097 }, /* MIEUM AE IEUNG */
                             { 0xB8CE, 0xA098 }, /* MIEUM AE CIEUC */
                             { 0xB8CF, 0xA0A1 }, /* MIEUM YA */
                             { 0xB8D0, 0xA0A2 }, /* MIEUM YA KIYEOK */
                             { 0xB8D1, 0xA0A9 }, /* MIEUM YA RIEUL */
                             { 0xB8D2, 0xA0B7 }, /* MIEUM YA IEUNG */
                             { 0xB8D3, 0xA0E1 }, /* MIEUM EO */
                             { 0xB8D4, 0xA0E2 }, /* MIEUM EO KIYEOK */
                             { 0xB8D5, 0xA0E5 }, /* MIEUM EO NIEUN */
                             { 0xB8D6, 0xA0E9 }, /* MIEUM EO RIEUL */
                             { 0xB8D7, 0xA0EB }, /* MIEUM EO RIEULMIEUM */
                             { 0xB8D8, 0xA0F1 }, /* MIEUM EO MIEUM */
                             { 0xB8D9, 0xA0F3 }, /* MIEUM EO PIEUP */
                             { 0xB8DA, 0xA0F5 }, /* MIEUM EO SIOS */
                             { 0xB8DB, 0xA0F7 }, /* MIEUM EO IEUNG */
                             { 0xB8DC, 0xA0F8 }, /* MIEUM EO CIEUC */
                             { 0xB8DD, 0xA0FD }, /* MIEUM EO HIEUH */
                             { 0xB8DE, 0xA141 }, /* MIEUM E */
                             { 0xB8DF, 0xA142 }, /* MIEUM E KIYEOK */
                             { 0xB8E0, 0xA145 }, /* MIEUM E NIEUN */
                             { 0xB8E1, 0xA149 }, /* MIEUM E RIEUL */
                             { 0xB8E2, 0xA151 }, /* MIEUM E MIEUM */
                             { 0xB8E3, 0xA153 }, /* MIEUM E PIEUP */
                             { 0xB8E4, 0xA155 }, /* MIEUM E SIOS */
                             { 0xB8E5, 0xA156 }, /* MIEUM E SSANGSIOS */
                             { 0xB8E6, 0xA157 }, /* MIEUM E IEUNG */
                             { 0xB8E7, 0xA161 }, /* MIEUM YEO */
                             { 0xB8E8, 0xA162 }, /* MIEUM YEO KIYEOK */
                             { 0xB8E9, 0xA165 }, /* MIEUM YEO NIEUN */
                             { 0xB8EA, 0xA169 }, /* MIEUM YEO RIEUL */
                             { 0xB8EB, 0xA175 }, /* MIEUM YEO SIOS */
                             { 0xB8EC, 0xA176 }, /* MIEUM YEO SSANGSIOS */
                             { 0xB8ED, 0xA177 }, /* MIEUM YEO IEUNG */
                             { 0xB8EE, 0xA179 }, /* MIEUM YEO CHIEUCH */
                             { 0xB8EF, 0xA181 }, /* MIEUM YE */
                             { 0xB8F0, 0xA1A1 }, /* MIEUM O */
                             { 0xB8F1, 0xA1A2 }, /* MIEUM O KIYEOK */
                             { 0xB8F2, 0xA1A4 }, /* MIEUM O KIYEOKSIOS */
                             { 0xB8F3, 0xA1A5 }, /* MIEUM O NIEUN */
                             { 0xB8F4, 0xA1A9 }, /* MIEUM O RIEUL */
                             { 0xB8F5, 0xA1AB }, /* MIEUM O RIEULMIEUM */
                             { 0xB8F6, 0xA1B1 }, /* MIEUM O MIEUM */
                             { 0xB8F7, 0xA1B3 }, /* MIEUM O PIEUP */
                             { 0xB8F8, 0xA1B5 }, /* MIEUM O SIOS */
                             { 0xB8F9, 0xA1B7 }, /* MIEUM O IEUNG */
                             { 0xB8FA, 0xA1C1 }, /* MIEUM WA */
                             { 0xB8FB, 0xA1C5 }, /* MIEUM WA NIEUN */
                             { 0xB8FC, 0xA1D6 }, /* MIEUM WA SSANGSIOS */
                             { 0xB8FD, 0xA1D7 }, /* MIEUM WA IEUNG */
                             { 0xB8FE, 0xA241 }, /* MIEUM OE */
                             { 0xB9A1, 0xA245 }, /* MIEUM OE NIEUN */
                             { 0xB9A2, 0xA249 }, /* MIEUM OE RIEUL */
                             { 0xB9A3, 0xA253 }, /* MIEUM OE PIEUP */
                             { 0xB9A4, 0xA255 }, /* MIEUM OE SIOS */
                             { 0xB9A5, 0xA257 }, /* MIEUM OE IEUNG */
                             { 0xB9A6, 0xA261 }, /* MIEUM YO */
                             { 0xB9A7, 0xA265 }, /* MIEUM YO NIEUN */
                             { 0xB9A8, 0xA269 }, /* MIEUM YO RIEUL */
                             { 0xB9A9, 0xA273 }, /* MIEUM YO PIEUP */
                             { 0xB9AA, 0xA275 }, /* MIEUM YO SIOS */
                             { 0xB9AB, 0xA281 }, /* MIEUM U */
                             { 0xB9AC, 0xA282 }, /* MIEUM U KIYEOK */
                             { 0xB9AD, 0xA283 }, /* MIEUM U SSANGKIYEOK */
                             { 0xB9AE, 0xA285 }, /* MIEUM U NIEUN */
                             { 0xB9AF, 0xA288 }, /* MIEUM U TIKEUT */
                             { 0xB9B0, 0xA289 }, /* MIEUM U RIEUL */
                             { 0xB9B1, 0xA28A }, /* MIEUM U RIEULKIYEOK */
                             { 0xB9B2, 0xA28B }, /* MIEUM U RIEULMIEUM */
                             { 0xB9B3, 0xA291 }, /* MIEUM U MIEUM */
                             { 0xB9B4, 0xA293 }, /* MIEUM U PIEUP */
                             { 0xB9B5, 0xA295 }, /* MIEUM U SIOS */
                             { 0xB9B6, 0xA297 }, /* MIEUM U IEUNG */
                             { 0xB9B7, 0xA29B }, /* MIEUM U THIEUTH */
                             { 0xB9B8, 0xA29D }, /* MIEUM U HIEUH */
                             { 0xB9B9, 0xA2A1 }, /* MIEUM WEO */
                             { 0xB9BA, 0xA2A5 }, /* MIEUM WEO NIEUN */
                             { 0xB9BB, 0xA2A9 }, /* MIEUM WEO RIEUL */
                             { 0xB9BC, 0xA2B3 }, /* MIEUM WEO PIEUP */
                             { 0xB9BD, 0xA2B5 }, /* MIEUM WEO SIOS */
                             { 0xB9BE, 0xA2C1 }, /* MIEUM WE */
                             { 0xB9BF, 0xA2E1 }, /* MIEUM WI */
                             { 0xB9C0, 0xA2E5 }, /* MIEUM WI NIEUN */
                             { 0xB9C1, 0xA2E9 }, /* MIEUM WI RIEUL */
                             { 0xB9C2, 0xA341 }, /* MIEUM YU */
                             { 0xB9C3, 0xA345 }, /* MIEUM YU NIEUN */
                             { 0xB9C4, 0xA349 }, /* MIEUM YU RIEUL */
                             { 0xB9C5, 0xA351 }, /* MIEUM YU MIEUM */
                             { 0xB9C6, 0xA355 }, /* MIEUM YU SIOS */
                             { 0xB9C7, 0xA361 }, /* MIEUM EU */
                             { 0xB9C8, 0xA365 }, /* MIEUM EU NIEUN */
                             { 0xB9C9, 0xA369 }, /* MIEUM EU RIEUL */
                             { 0xB9CA, 0xA371 }, /* MIEUM EU MIEUM */
                             { 0xB9CB, 0xA375 }, /* MIEUM EU SIOS */
                             { 0xB9CC, 0xA3A1 }, /* MIEUM I */
                             { 0xB9CD, 0xA3A2 }, /* MIEUM I KIYEOK */
                             { 0xB9CE, 0xA3A5 }, /* MIEUM I NIEUN */
                             { 0xB9CF, 0xA3A8 }, /* MIEUM I TIKEUT */
                             { 0xB9D0, 0xA3A9 }, /* MIEUM I RIEUL */
                             { 0xB9D1, 0xA3AB }, /* MIEUM I RIEULMIEUM */
                             { 0xB9D2, 0xA3B1 }, /* MIEUM I MIEUM */
                             { 0xB9D3, 0xA3B3 }, /* MIEUM I PIEUP */
                             { 0xB9D4, 0xA3B5 }, /* MIEUM I SIOS */
                             { 0xB9D5, 0xA3B6 }, /* MIEUM I SSANGSIOS */
                             { 0xB9D6, 0xA3B7 }, /* MIEUM I IEUNG */
                             { 0xB9D7, 0xA3B9 }, /* MIEUM I CHIEUCH */
                             { 0xB9D8, 0xA3BB }, /* MIEUM I THIEUTH */
                             { 0xB9D9, 0xA461 }, /* PIEUP A */
                             { 0xB9DA, 0xA462 }, /* PIEUP A KIYEOK */
                             { 0xB9DB, 0xA463 }, /* PIEUP A SSANGKIYEOK */
                             { 0xB9DC, 0xA464 }, /* PIEUP A KIYEOKSIOS */
                             { 0xB9DD, 0xA465 }, /* PIEUP A NIEUN */
                             { 0xB9DE, 0xA468 }, /* PIEUP A TIKEUT */
                             { 0xB9DF, 0xA469 }, /* PIEUP A RIEUL */
                             { 0xB9E0, 0xA46A }, /* PIEUP A RIEULKIYEOK */
                             { 0xB9E1, 0xA46B }, /* PIEUP A RIEULMIEUM */
                             { 0xB9E2, 0xA46C }, /* PIEUP A RIEULPIEUP */
                             { 0xB9E3, 0xA471 }, /* PIEUP A MIEUM */
                             { 0xB9E4, 0xA473 }, /* PIEUP A PIEUP */
                             { 0xB9E5, 0xA475 }, /* PIEUP A SIOS */
                             { 0xB9E6, 0xA477 }, /* PIEUP A IEUNG */
                             { 0xB9E7, 0xA47B }, /* PIEUP A THIEUTH */
                             { 0xB9E8, 0xA481 }, /* PIEUP AE */
                             { 0xB9E9, 0xA482 }, /* PIEUP AE KIYEOK */
                             { 0xB9EA, 0xA485 }, /* PIEUP AE NIEUN */
                             { 0xB9EB, 0xA489 }, /* PIEUP AE RIEUL */
                             { 0xB9EC, 0xA491 }, /* PIEUP AE MIEUM */
                             { 0xB9ED, 0xA493 }, /* PIEUP AE PIEUP */
                             { 0xB9EE, 0xA495 }, /* PIEUP AE SIOS */
                             { 0xB9EF, 0xA496 }, /* PIEUP AE SSANGSIOS */
                             { 0xB9F0, 0xA497 }, /* PIEUP AE IEUNG */
                             { 0xB9F1, 0xA49B }, /* PIEUP AE THIEUTH */
                             { 0xB9F2, 0xA4A1 }, /* PIEUP YA */
                             { 0xB9F3, 0xA4A2 }, /* PIEUP YA KIYEOK */
                             { 0xB9F4, 0xA4A5 }, /* PIEUP YA NIEUN */
                             { 0xB9F5, 0xA4B3 }, /* PIEUP YA PIEUP */
                             { 0xB9F6, 0xA4E1 }, /* PIEUP EO */
                             { 0xB9F7, 0xA4E2 }, /* PIEUP EO KIYEOK */
                             { 0xB9F8, 0xA4E5 }, /* PIEUP EO NIEUN */
                             { 0xB9F9, 0xA4E8 }, /* PIEUP EO TIKEUT */
                             { 0xB9FA, 0xA4E9 }, /* PIEUP EO RIEUL */
                             { 0xB9FB, 0xA4EB }, /* PIEUP EO RIEULMIEUM */
                             { 0xB9FC, 0xA4F1 }, /* PIEUP EO MIEUM */
                             { 0xB9FD, 0xA4F3 }, /* PIEUP EO PIEUP */
                             { 0xB9FE, 0xA4F5 }, /* PIEUP EO SIOS */
                             { 0xBAA1, 0xA4F7 }, /* PIEUP EO IEUNG */
                             { 0xBAA2, 0xA4F8 }, /* PIEUP EO CIEUC */
                             { 0xBAA3, 0xA541 }, /* PIEUP E */
                             { 0xBAA4, 0xA542 }, /* PIEUP E KIYEOK */
                             { 0xBAA5, 0xA545 }, /* PIEUP E NIEUN */
                             { 0xBAA6, 0xA548 }, /* PIEUP E TIKEUT */
                             { 0xBAA7, 0xA549 }, /* PIEUP E RIEUL */
                             { 0xBAA8, 0xA551 }, /* PIEUP E MIEUM */
                             { 0xBAA9, 0xA553 }, /* PIEUP E PIEUP */
                             { 0xBAAA, 0xA555 }, /* PIEUP E SIOS */
                             { 0xBAAB, 0xA556 }, /* PIEUP E SSANGSIOS */
                             { 0xBAAC, 0xA557 }, /* PIEUP E IEUNG */
                             { 0xBAAD, 0xA561 }, /* PIEUP YEO */
                             { 0xBAAE, 0xA562 }, /* PIEUP YEO KIYEOK */
                             { 0xBAAF, 0xA565 }, /* PIEUP YEO NIEUN */
                             { 0xBAB0, 0xA569 }, /* PIEUP YEO RIEUL */
                             { 0xBAB1, 0xA573 }, /* PIEUP YEO PIEUP */
                             { 0xBAB2, 0xA575 }, /* PIEUP YEO SIOS */
                             { 0xBAB3, 0xA576 }, /* PIEUP YEO SSANGSIOS */
                             { 0xBAB4, 0xA577 }, /* PIEUP YEO IEUNG */
                             { 0xBAB5, 0xA57B }, /* PIEUP YEO THIEUTH */
                             { 0xBAB6, 0xA581 }, /* PIEUP YE */
                             { 0xBAB7, 0xA585 }, /* PIEUP YE NIEUN */
                             { 0xBAB8, 0xA5A1 }, /* PIEUP O */
                             { 0xBAB9, 0xA5A2 }, /* PIEUP O KIYEOK */
                             { 0xBABA, 0xA5A3 }, /* PIEUP O SSANGKIYEOK */
                             { 0xBABB, 0xA5A5 }, /* PIEUP O NIEUN */
                             { 0xBABC, 0xA5A9 }, /* PIEUP O RIEUL */
                             { 0xBABD, 0xA5B1 }, /* PIEUP O MIEUM */
                             { 0xBABE, 0xA5B3 }, /* PIEUP O PIEUP */
                             { 0xBABF, 0xA5B5 }, /* PIEUP O SIOS */
                             { 0xBAC0, 0xA5B7 }, /* PIEUP O IEUNG */
                             { 0xBAC1, 0xA5C1 }, /* PIEUP WA */
                             { 0xBAC2, 0xA5C5 }, /* PIEUP WA NIEUN */
                             { 0xBAC3, 0xA5D6 }, /* PIEUP WA SSANGSIOS */
                             { 0xBAC4, 0xA5E1 }, /* PIEUP WAE */
                             { 0xBAC5, 0xA5F6 }, /* PIEUP WAE SSANGSIOS */
                             { 0xBAC6, 0xA641 }, /* PIEUP OE */
                             { 0xBAC7, 0xA642 }, /* PIEUP OE KIYEOK */
                             { 0xBAC8, 0xA645 }, /* PIEUP OE NIEUN */
                             { 0xBAC9, 0xA649 }, /* PIEUP OE RIEUL */
                             { 0xBACA, 0xA651 }, /* PIEUP OE MIEUM */
                             { 0xBACB, 0xA653 }, /* PIEUP OE PIEUP */
                             { 0xBACC, 0xA661 }, /* PIEUP YO */
                             { 0xBACD, 0xA665 }, /* PIEUP YO NIEUN */
                             { 0xBACE, 0xA681 }, /* PIEUP U */
                             { 0xBACF, 0xA682 }, /* PIEUP U KIYEOK */
                             { 0xBAD0, 0xA685 }, /* PIEUP U NIEUN */
                             { 0xBAD1, 0xA688 }, /* PIEUP U TIKEUT */
                             { 0xBAD2, 0xA689 }, /* PIEUP U RIEUL */
                             { 0xBAD3, 0xA68A }, /* PIEUP U RIEULKIYEOK */
                             { 0xBAD4, 0xA68B }, /* PIEUP U RIEULMIEUM */
                             { 0xBAD5, 0xA691 }, /* PIEUP U MIEUM */
                             { 0xBAD6, 0xA693 }, /* PIEUP U PIEUP */
                             { 0xBAD7, 0xA695 }, /* PIEUP U SIOS */
                             { 0xBAD8, 0xA697 }, /* PIEUP U IEUNG */
                             { 0xBAD9, 0xA69B }, /* PIEUP U THIEUTH */
                             { 0xBADA, 0xA69C }, /* PIEUP U PHIEUPH */
                             { 0xBADB, 0xA6A1 }, /* PIEUP WEO */
                             { 0xBADC, 0xA6A9 }, /* PIEUP WEO RIEUL */
                             { 0xBADD, 0xA6B6 }, /* PIEUP WEO SSANGSIOS */
                             { 0xBADE, 0xA6C1 }, /* PIEUP WE */
                             { 0xBADF, 0xA6E1 }, /* PIEUP WI */
                             { 0xBAE0, 0xA6E2 }, /* PIEUP WI KIYEOK */
                             { 0xBAE1, 0xA6E5 }, /* PIEUP WI NIEUN */
                             { 0xBAE2, 0xA6E9 }, /* PIEUP WI RIEUL */
                             { 0xBAE3, 0xA6F7 }, /* PIEUP WI IEUNG */
                             { 0xBAE4, 0xA741 }, /* PIEUP YU */
                             { 0xBAE5, 0xA745 }, /* PIEUP YU NIEUN */
                             { 0xBAE6, 0xA749 }, /* PIEUP YU RIEUL */
                             { 0xBAE7, 0xA751 }, /* PIEUP YU MIEUM */
                             { 0xBAE8, 0xA755 }, /* PIEUP YU SIOS */
                             { 0xBAE9, 0xA757 }, /* PIEUP YU IEUNG */
                             { 0xBAEA, 0xA761 }, /* PIEUP EU */
                             { 0xBAEB, 0xA762 }, /* PIEUP EU KIYEOK */
                             { 0xBAEC, 0xA765 }, /* PIEUP EU NIEUN */
                             { 0xBAED, 0xA769 }, /* PIEUP EU RIEUL */
                             { 0xBAEE, 0xA771 }, /* PIEUP EU MIEUM */
                             { 0xBAEF, 0xA773 }, /* PIEUP EU PIEUP */
                             { 0xBAF0, 0xA775 }, /* PIEUP EU SIOS */
                             { 0xBAF1, 0xA7A1 }, /* PIEUP I */
                             { 0xBAF2, 0xA7A2 }, /* PIEUP I KIYEOK */
                             { 0xBAF3, 0xA7A5 }, /* PIEUP I NIEUN */
                             { 0xBAF4, 0xA7A9 }, /* PIEUP I RIEUL */
                             { 0xBAF5, 0xA7AB }, /* PIEUP I RIEULMIEUM */
                             { 0xBAF6, 0xA7B1 }, /* PIEUP I MIEUM */
                             { 0xBAF7, 0xA7B3 }, /* PIEUP I PIEUP */
                             { 0xBAF8, 0xA7B5 }, /* PIEUP I SIOS */
                             { 0xBAF9, 0xA7B7 }, /* PIEUP I IEUNG */
                             { 0xBAFA, 0xA7B8 }, /* PIEUP I CIEUC */
                             { 0xBAFB, 0xA7B9 }, /* PIEUP I CHIEUCH */
                             { 0xBAFC, 0xA861 }, /* SSANGPIEUP A */
                             { 0xBAFD, 0xA862 }, /* SSANGPIEUP A KIYEOK */
                             { 0xBAFE, 0xA865 }, /* SSANGPIEUP A NIEUN */
                             { 0xBBA1, 0xA869 }, /* SSANGPIEUP A RIEUL */
                             { 0xBBA2, 0xA86B }, /* SSANGPIEUP A RIEULMIEUM */
                             { 0xBBA3, 0xA871 }, /* SSANGPIEUP A MIEUM */
                             { 0xBBA4, 0xA873 }, /* SSANGPIEUP A PIEUP */
                             { 0xBBA5, 0xA875 }, /* SSANGPIEUP A SIOS */
                             { 0xBBA6, 0xA876 }, /* SSANGPIEUP A SSANGSIOS */
                             { 0xBBA7, 0xA877 }, /* SSANGPIEUP A IEUNG */
                             { 0xBBA8, 0xA87D }, /* SSANGPIEUP A HIEUH */
                             { 0xBBA9, 0xA881 }, /* SSANGPIEUP AE */
                             { 0xBBAA, 0xA882 }, /* SSANGPIEUP AE KIYEOK */
                             { 0xBBAB, 0xA885 }, /* SSANGPIEUP AE NIEUN */
                             { 0xBBAC, 0xA889 }, /* SSANGPIEUP AE RIEUL */
                             { 0xBBAD, 0xA891 }, /* SSANGPIEUP AE MIEUM */
                             { 0xBBAE, 0xA893 }, /* SSANGPIEUP AE PIEUP */
                             { 0xBBAF, 0xA895 }, /* SSANGPIEUP AE SIOS */
                             { 0xBBB0, 0xA896 }, /* SSANGPIEUP AE SSANGSIOS */
                             { 0xBBB1, 0xA897 }, /* SSANGPIEUP AE IEUNG */
                             { 0xBBB2, 0xA8A1 }, /* SSANGPIEUP YA */
                             { 0xBBB3, 0xA8A2 }, /* SSANGPIEUP YA KIYEOK */
                             { 0xBBB4, 0xA8B1 }, /* SSANGPIEUP YA MIEUM */
                             { 0xBBB5, 0xA8E1 }, /* SSANGPIEUP EO */
                             { 0xBBB6, 0xA8E2 }, /* SSANGPIEUP EO KIYEOK */
                             { 0xBBB7, 0xA8E5 }, /* SSANGPIEUP EO NIEUN */
                             { 0xBBB8, 0xA8E8 }, /* SSANGPIEUP EO TIKEUT */
                             { 0xBBB9, 0xA8E9 }, /* SSANGPIEUP EO RIEUL */
                             { 0xBBBA, 0xA8F1 }, /* SSANGPIEUP EO MIEUM */
                             { 0xBBBB, 0xA8F5 }, /* SSANGPIEUP EO SIOS */
                             { 0xBBBC, 0xA8F6 }, /* SSANGPIEUP EO SSANGSIOS */
                             { 0xBBBD, 0xA8F7 }, /* SSANGPIEUP EO IEUNG */
                             { 0xBBBE, 0xA941 }, /* SSANGPIEUP E */
                             { 0xBBBF, 0xA957 }, /* SSANGPIEUP E IEUNG */
                             { 0xBBC0, 0xA961 }, /* SSANGPIEUP YEO */
                             { 0xBBC1, 0xA962 }, /* SSANGPIEUP YEO KIYEOK */
                             { 0xBBC2, 0xA971 }, /* SSANGPIEUP YEO MIEUM */
                             { 0xBBC3, 0xA973 }, /* SSANGPIEUP YEO PIEUP */
                             { 0xBBC4, 0xA975 }, /* SSANGPIEUP YEO SIOS */
                             { 0xBBC5, 0xA976 }, /* SSANGPIEUP YEO SSANGSIOS */
                             { 0xBBC6, 0xA977 }, /* SSANGPIEUP YEO IEUNG */
                             { 0xBBC7, 0xA9A1 }, /* SSANGPIEUP O */
                             { 0xBBC8, 0xA9A2 }, /* SSANGPIEUP O KIYEOK */
                             { 0xBBC9, 0xA9A5 }, /* SSANGPIEUP O NIEUN */
                             { 0xBBCA, 0xA9A9 }, /* SSANGPIEUP O RIEUL */
                             { 0xBBCB, 0xA9B1 }, /* SSANGPIEUP O MIEUM */
                             { 0xBBCC, 0xA9B3 }, /* SSANGPIEUP O PIEUP */
                             { 0xBBCD, 0xA9B7 }, /* SSANGPIEUP O IEUNG */
                             { 0xBBCE, 0xAA41 }, /* SSANGPIEUP OE */
                             { 0xBBCF, 0xAA61 }, /* SSANGPIEUP YO */
                             { 0xBBD0, 0xAA77 }, /* SSANGPIEUP YO IEUNG */
                             { 0xBBD1, 0xAA81 }, /* SSANGPIEUP U */
                             { 0xBBD2, 0xAA82 }, /* SSANGPIEUP U KIYEOK */
                             { 0xBBD3, 0xAA85 }, /* SSANGPIEUP U NIEUN */
                             { 0xBBD4, 0xAA89 }, /* SSANGPIEUP U RIEUL */
                             { 0xBBD5, 0xAA91 }, /* SSANGPIEUP U MIEUM */
                             { 0xBBD6, 0xAA95 }, /* SSANGPIEUP U SIOS */
                             { 0xBBD7, 0xAA97 }, /* SSANGPIEUP U IEUNG */
                             { 0xBBD8, 0xAB41 }, /* SSANGPIEUP YU */
                             { 0xBBD9, 0xAB57 }, /* SSANGPIEUP YU IEUNG */
                             { 0xBBDA, 0xAB61 }, /* SSANGPIEUP EU */
                             { 0xBBDB, 0xAB65 }, /* SSANGPIEUP EU NIEUN */
                             { 0xBBDC, 0xAB69 }, /* SSANGPIEUP EU RIEUL */
                             { 0xBBDD, 0xAB71 }, /* SSANGPIEUP EU MIEUM */
                             { 0xBBDE, 0xAB73 }, /* SSANGPIEUP EU PIEUP */
                             { 0xBBDF, 0xABA1 }, /* SSANGPIEUP I */
                             { 0xBBE0, 0xABA2 }, /* SSANGPIEUP I KIYEOK */
                             { 0xBBE1, 0xABA5 }, /* SSANGPIEUP I NIEUN */
                             { 0xBBE2, 0xABA9 }, /* SSANGPIEUP I RIEUL */
                             { 0xBBE3, 0xABB1 }, /* SSANGPIEUP I MIEUM */
                             { 0xBBE4, 0xABB3 }, /* SSANGPIEUP I PIEUP */
                             { 0xBBE5, 0xABB5 }, /* SSANGPIEUP I SIOS */
                             { 0xBBE6, 0xABB7 }, /* SSANGPIEUP I IEUNG */
                             { 0xBBE7, 0xAC61 }, /* SIOS A */
                             { 0xBBE8, 0xAC62 }, /* SIOS A KIYEOK */
                             { 0xBBE9, 0xAC64 }, /* SIOS A KIYEOKSIOS */
                             { 0xBBEA, 0xAC65 }, /* SIOS A NIEUN */
                             { 0xBBEB, 0xAC68 }, /* SIOS A TIKEUT */
                             { 0xBBEC, 0xAC69 }, /* SIOS A RIEUL */
                             { 0xBBED, 0xAC6A }, /* SIOS A RIEULKIYEOK */
                             { 0xBBEE, 0xAC6B }, /* SIOS A RIEULMIEUM */
                             { 0xBBEF, 0xAC71 }, /* SIOS A MIEUM */
                             { 0xBBF0, 0xAC73 }, /* SIOS A PIEUP */
                             { 0xBBF1, 0xAC75 }, /* SIOS A SIOS */
                             { 0xBBF2, 0xAC76 }, /* SIOS A SSANGSIOS */
                             { 0xBBF3, 0xAC77 }, /* SIOS A IEUNG */
                             { 0xBBF4, 0xAC7B }, /* SIOS A THIEUTH */
                             { 0xBBF5, 0xAC81 }, /* SIOS AE */
                             { 0xBBF6, 0xAC82 }, /* SIOS AE KIYEOK */
                             { 0xBBF7, 0xAC85 }, /* SIOS AE NIEUN */
                             { 0xBBF8, 0xAC89 }, /* SIOS AE RIEUL */
                             { 0xBBF9, 0xAC91 }, /* SIOS AE MIEUM */
                             { 0xBBFA, 0xAC93 }, /* SIOS AE PIEUP */
                             { 0xBBFB, 0xAC95 }, /* SIOS AE SIOS */
                             { 0xBBFC, 0xAC96 }, /* SIOS AE SSANGSIOS */
                             { 0xBBFD, 0xAC97 }, /* SIOS AE IEUNG */
                             { 0xBBFE, 0xACA1 }, /* SIOS YA */
                             { 0xBCA1, 0xACA2 }, /* SIOS YA KIYEOK */
                             { 0xBCA2, 0xACA5 }, /* SIOS YA NIEUN */
                             { 0xBCA3, 0xACA9 }, /* SIOS YA RIEUL */
                             { 0xBCA4, 0xACB1 }, /* SIOS YA MIEUM */
                             { 0xBCA5, 0xACB3 }, /* SIOS YA PIEUP */
                             { 0xBCA6, 0xACB5 }, /* SIOS YA SIOS */
                             { 0xBCA7, 0xACB7 }, /* SIOS YA IEUNG */
                             { 0xBCA8, 0xACC1 }, /* SIOS YAE */
                             { 0xBCA9, 0xACC5 }, /* SIOS YAE NIEUN */
                             { 0xBCAA, 0xACC9 }, /* SIOS YAE RIEUL */
                             { 0xBCAB, 0xACD1 }, /* SIOS YAE MIEUM */
                             { 0xBCAC, 0xACD7 }, /* SIOS YAE IEUNG */
                             { 0xBCAD, 0xACE1 }, /* SIOS EO */
                             { 0xBCAE, 0xACE2 }, /* SIOS EO KIYEOK */
                             { 0xBCAF, 0xACE3 }, /* SIOS EO SSANGKIYEOK */
                             { 0xBCB0, 0xACE4 }, /* SIOS EO KIYEOKSIOS */
                             { 0xBCB1, 0xACE5 }, /* SIOS EO NIEUN */
                             { 0xBCB2, 0xACE8 }, /* SIOS EO TIKEUT */
                             { 0xBCB3, 0xACE9 }, /* SIOS EO RIEUL */
                             { 0xBCB4, 0xACEB }, /* SIOS EO RIEULMIEUM */
                             { 0xBCB5, 0xACEC }, /* SIOS EO RIEULPIEUP */
                             { 0xBCB6, 0xACF1 }, /* SIOS EO MIEUM */
                             { 0xBCB7, 0xACF3 }, /* SIOS EO PIEUP */
                             { 0xBCB8, 0xACF5 }, /* SIOS EO SIOS */
                             { 0xBCB9, 0xACF6 }, /* SIOS EO SSANGSIOS */
                             { 0xBCBA, 0xACF7 }, /* SIOS EO IEUNG */
                             { 0xBCBB, 0xACFC }, /* SIOS EO PHIEUPH */
                             { 0xBCBC, 0xAD41 }, /* SIOS E */
                             { 0xBCBD, 0xAD42 }, /* SIOS E KIYEOK */
                             { 0xBCBE, 0xAD45 }, /* SIOS E NIEUN */
                             { 0xBCBF, 0xAD49 }, /* SIOS E RIEUL */
                             { 0xBCC0, 0xAD51 }, /* SIOS E MIEUM */
                             { 0xBCC1, 0xAD53 }, /* SIOS E PIEUP */
                             { 0xBCC2, 0xAD55 }, /* SIOS E SIOS */
                             { 0xBCC3, 0xAD56 }, /* SIOS E SSANGSIOS */
                             { 0xBCC4, 0xAD57 }, /* SIOS E IEUNG */
                             { 0xBCC5, 0xAD61 }, /* SIOS YEO */
                             { 0xBCC6, 0xAD62 }, /* SIOS YEO KIYEOK */
                             { 0xBCC7, 0xAD65 }, /* SIOS YEO NIEUN */
                             { 0xBCC8, 0xAD69 }, /* SIOS YEO RIEUL */
                             { 0xBCC9, 0xAD71 }, /* SIOS YEO MIEUM */
                             { 0xBCCA, 0xAD73 }, /* SIOS YEO PIEUP */
                             { 0xBCCB, 0xAD75 }, /* SIOS YEO SIOS */
                             { 0xBCCC, 0xAD76 }, /* SIOS YEO SSANGSIOS */
                             { 0xBCCD, 0xAD77 }, /* SIOS YEO IEUNG */
                             { 0xBCCE, 0xAD81 }, /* SIOS YE */
                             { 0xBCCF, 0xAD85 }, /* SIOS YE NIEUN */
                             { 0xBCD0, 0xAD89 }, /* SIOS YE RIEUL */
                             { 0xBCD1, 0xAD97 }, /* SIOS YE IEUNG */
                             { 0xBCD2, 0xADA1 }, /* SIOS O */
                             { 0xBCD3, 0xADA2 }, /* SIOS O KIYEOK */
                             { 0xBCD4, 0xADA3 }, /* SIOS O SSANGKIYEOK */
                             { 0xBCD5, 0xADA5 }, /* SIOS O NIEUN */
                             { 0xBCD6, 0xADA9 }, /* SIOS O RIEUL */
                             { 0xBCD7, 0xADAB }, /* SIOS O RIEULMIEUM */
                             { 0xBCD8, 0xADB1 }, /* SIOS O MIEUM */
                             { 0xBCD9, 0xADB3 }, /* SIOS O PIEUP */
                             { 0xBCDA, 0xADB5 }, /* SIOS O SIOS */
                             { 0xBCDB, 0xADB7 }, /* SIOS O IEUNG */
                             { 0xBCDC, 0xADBB }, /* SIOS O THIEUTH */
                             { 0xBCDD, 0xADC1 }, /* SIOS WA */
                             { 0xBCDE, 0xADC2 }, /* SIOS WA KIYEOK */
                             { 0xBCDF, 0xADC5 }, /* SIOS WA NIEUN */
                             { 0xBCE0, 0xADC9 }, /* SIOS WA RIEUL */
                             { 0xBCE1, 0xADD7 }, /* SIOS WA IEUNG */
                             { 0xBCE2, 0xADE1 }, /* SIOS WAE */
                             { 0xBCE3, 0xADE5 }, /* SIOS WAE NIEUN */
                             { 0xBCE4, 0xADE9 }, /* SIOS WAE RIEUL */
                             { 0xBCE5, 0xADF1 }, /* SIOS WAE MIEUM */
                             { 0xBCE6, 0xADF5 }, /* SIOS WAE SIOS */
                             { 0xBCE7, 0xADF6 }, /* SIOS WAE SSANGSIOS */
                             { 0xBCE8, 0xAE41 }, /* SIOS OE */
                             { 0xBCE9, 0xAE45 }, /* SIOS OE NIEUN */
                             { 0xBCEA, 0xAE49 }, /* SIOS OE RIEUL */
                             { 0xBCEB, 0xAE51 }, /* SIOS OE MIEUM */
                             { 0xBCEC, 0xAE53 }, /* SIOS OE PIEUP */
                             { 0xBCED, 0xAE55 }, /* SIOS OE SIOS */
                             { 0xBCEE, 0xAE61 }, /* SIOS YO */
                             { 0xBCEF, 0xAE62 }, /* SIOS YO KIYEOK */
                             { 0xBCF0, 0xAE65 }, /* SIOS YO NIEUN */
                             { 0xBCF1, 0xAE69 }, /* SIOS YO RIEUL */
                             { 0xBCF2, 0xAE71 }, /* SIOS YO MIEUM */
                             { 0xBCF3, 0xAE73 }, /* SIOS YO PIEUP */
                             { 0xBCF4, 0xAE75 }, /* SIOS YO SIOS */
                             { 0xBCF5, 0xAE77 }, /* SIOS YO IEUNG */
                             { 0xBCF6, 0xAE81 }, /* SIOS U */
                             { 0xBCF7, 0xAE82 }, /* SIOS U KIYEOK */
                             { 0xBCF8, 0xAE85 }, /* SIOS U NIEUN */
                             { 0xBCF9, 0xAE88 }, /* SIOS U TIKEUT */
                             { 0xBCFA, 0xAE89 }, /* SIOS U RIEUL */
                             { 0xBCFB, 0xAE91 }, /* SIOS U MIEUM */
                             { 0xBCFC, 0xAE93 }, /* SIOS U PIEUP */
                             { 0xBCFD, 0xAE95 }, /* SIOS U SIOS */
                             { 0xBCFE, 0xAE97 }, /* SIOS U IEUNG */
                             { 0xBDA1, 0xAE99 }, /* SIOS U CHIEUCH */
                             { 0xBDA2, 0xAE9B }, /* SIOS U THIEUTH */
                             { 0xBDA3, 0xAE9C }, /* SIOS U PHIEUPH */
                             { 0xBDA4, 0xAEA1 }, /* SIOS WEO */
                             { 0xBDA5, 0xAEB6 }, /* SIOS WEO SSANGSIOS */
                             { 0xBDA6, 0xAEC1 }, /* SIOS WE */
                             { 0xBDA7, 0xAEC2 }, /* SIOS WE KIYEOK */
                             { 0xBDA8, 0xAEC5 }, /* SIOS WE NIEUN */
                             { 0xBDA9, 0xAEC9 }, /* SIOS WE RIEUL */
                             { 0xBDAA, 0xAED1 }, /* SIOS WE MIEUM */
                             { 0xBDAB, 0xAED7 }, /* SIOS WE IEUNG */
                             { 0xBDAC, 0xAEE1 }, /* SIOS WI */
                             { 0xBDAD, 0xAEE2 }, /* SIOS WI KIYEOK */
                             { 0xBDAE, 0xAEE5 }, /* SIOS WI NIEUN */
                             { 0xBDAF, 0xAEE9 }, /* SIOS WI RIEUL */
                             { 0xBDB0, 0xAEF1 }, /* SIOS WI MIEUM */
                             { 0xBDB1, 0xAEF3 }, /* SIOS WI PIEUP */
                             { 0xBDB2, 0xAEF5 }, /* SIOS WI SIOS */
                             { 0xBDB3, 0xAEF7 }, /* SIOS WI IEUNG */
                             { 0xBDB4, 0xAF41 }, /* SIOS YU */
                             { 0xBDB5, 0xAF42 }, /* SIOS YU KIYEOK */
                             { 0xBDB6, 0xAF49 }, /* SIOS YU RIEUL */
                             { 0xBDB7, 0xAF51 }, /* SIOS YU MIEUM */
                             { 0xBDB8, 0xAF55 }, /* SIOS YU SIOS */
                             { 0xBDB9, 0xAF57 }, /* SIOS YU IEUNG */
                             { 0xBDBA, 0xAF61 }, /* SIOS EU */
                             { 0xBDBB, 0xAF62 }, /* SIOS EU KIYEOK */
                             { 0xBDBC, 0xAF65 }, /* SIOS EU NIEUN */
                             { 0xBDBD, 0xAF69 }, /* SIOS EU RIEUL */
                             { 0xBDBE, 0xAF6A }, /* SIOS EU RIEULKIYEOK */
                             { 0xBDBF, 0xAF71 }, /* SIOS EU MIEUM */
                             { 0xBDC0, 0xAF73 }, /* SIOS EU PIEUP */
                             { 0xBDC1, 0xAF75 }, /* SIOS EU SIOS */
                             { 0xBDC2, 0xAF77 }, /* SIOS EU IEUNG */
                             { 0xBDC3, 0xAFA1 }, /* SIOS I */
                             { 0xBDC4, 0xAFA2 }, /* SIOS I KIYEOK */
                             { 0xBDC5, 0xAFA5 }, /* SIOS I NIEUN */
                             { 0xBDC6, 0xAFA8 }, /* SIOS I TIKEUT */
                             { 0xBDC7, 0xAFA9 }, /* SIOS I RIEUL */
                             { 0xBDC8, 0xAFB0 }, /* SIOS I RIEULHIEUH */
                             { 0xBDC9, 0xAFB1 }, /* SIOS I MIEUM */
                             { 0xBDCA, 0xAFB3 }, /* SIOS I PIEUP */
                             { 0xBDCB, 0xAFB5 }, /* SIOS I SIOS */
                             { 0xBDCC, 0xAFB7 }, /* SIOS I IEUNG */
                             { 0xBDCD, 0xAFBC }, /* SIOS I PHIEUPH */
                             { 0xBDCE, 0xB061 }, /* SSANGSIOS A */
                             { 0xBDCF, 0xB062 }, /* SSANGSIOS A KIYEOK */
                             { 0xBDD0, 0xB064 }, /* SSANGSIOS A KIYEOKSIOS */
                             { 0xBDD1, 0xB065 }, /* SSANGSIOS A NIEUN */
                             { 0xBDD2, 0xB069 }, /* SSANGSIOS A RIEUL */
                             { 0xBDD3, 0xB071 }, /* SSANGSIOS A MIEUM */
                             { 0xBDD4, 0xB073 }, /* SSANGSIOS A PIEUP */
                             { 0xBDD5, 0xB076 }, /* SSANGSIOS A SSANGSIOS */
                             { 0xBDD6, 0xB077 }, /* SSANGSIOS A IEUNG */
                             { 0xBDD7, 0xB07D }, /* SSANGSIOS A HIEUH */
                             { 0xBDD8, 0xB081 }, /* SSANGSIOS AE */
                             { 0xBDD9, 0xB082 }, /* SSANGSIOS AE KIYEOK */
                             { 0xBDDA, 0xB085 }, /* SSANGSIOS AE NIEUN */
                             { 0xBDDB, 0xB089 }, /* SSANGSIOS AE RIEUL */
                             { 0xBDDC, 0xB091 }, /* SSANGSIOS AE MIEUM */
                             { 0xBDDD, 0xB093 }, /* SSANGSIOS AE PIEUP */
                             { 0xBDDE, 0xB096 }, /* SSANGSIOS AE SSANGSIOS */
                             { 0xBDDF, 0xB097 }, /* SSANGSIOS AE IEUNG */
                             { 0xBDE0, 0xB0B7 }, /* SSANGSIOS YA IEUNG */
                             { 0xBDE1, 0xB0E1 }, /* SSANGSIOS EO */
                             { 0xBDE2, 0xB0E2 }, /* SSANGSIOS EO KIYEOK */
                             { 0xBDE3, 0xB0E5 }, /* SSANGSIOS EO NIEUN */
                             { 0xBDE4, 0xB0E9 }, /* SSANGSIOS EO RIEUL */
                             { 0xBDE5, 0xB0EB }, /* SSANGSIOS EO RIEULMIEUM */
                             { 0xBDE6, 0xB0F1 }, /* SSANGSIOS EO MIEUM */
                             { 0xBDE7, 0xB0F3 }, /* SSANGSIOS EO PIEUP */
                             { 0xBDE8, 0xB0F6 }, /* SSANGSIOS EO SSANGSIOS */
                             { 0xBDE9, 0xB0F7 }, /* SSANGSIOS EO IEUNG */
                             { 0xBDEA, 0xB141 }, /* SSANGSIOS E */
                             { 0xBDEB, 0xB145 }, /* SSANGSIOS E NIEUN */
                             { 0xBDEC, 0xB149 }, /* SSANGSIOS E RIEUL */
                             { 0xBDED, 0xB185 }, /* SSANGSIOS YE NIEUN */
                             { 0xBDEE, 0xB1A1 }, /* SSANGSIOS O */
                             { 0xBDEF, 0xB1A2 }, /* SSANGSIOS O KIYEOK */
                             { 0xBDF0, 0xB1A5 }, /* SSANGSIOS O NIEUN */
                             { 0xBDF1, 0xB1A8 }, /* SSANGSIOS O TIKEUT */
                             { 0xBDF2, 0xB1A9 }, /* SSANGSIOS O RIEUL */
                             { 0xBDF3, 0xB1AB }, /* SSANGSIOS O RIEULMIEUM */
                             { 0xBDF4, 0xB1B1 }, /* SSANGSIOS O MIEUM */
                             { 0xBDF5, 0xB1B3 }, /* SSANGSIOS O PIEUP */
                             { 0xBDF6, 0xB1B7 }, /* SSANGSIOS O IEUNG */
                             { 0xBDF7, 0xB1C1 }, /* SSANGSIOS WA */
                             { 0xBDF8, 0xB1C2 }, /* SSANGSIOS WA KIYEOK */
                             { 0xBDF9, 0xB1C5 }, /* SSANGSIOS WA NIEUN */
                             { 0xBDFA, 0xB1D6 }, /* SSANGSIOS WA SSANGSIOS */
                             { 0xBDFB, 0xB1E1 }, /* SSANGSIOS WAE */
                             { 0xBDFC, 0xB1F6 }, /* SSANGSIOS WAE SSANGSIOS */
                             { 0xBDFD, 0xB241 }, /* SSANGSIOS OE */
                             { 0xBDFE, 0xB245 }, /* SSANGSIOS OE NIEUN */
                             { 0xBEA1, 0xB249 }, /* SSANGSIOS OE RIEUL */
                             { 0xBEA2, 0xB251 }, /* SSANGSIOS OE MIEUM */
                             { 0xBEA3, 0xB253 }, /* SSANGSIOS OE PIEUP */
                             { 0xBEA4, 0xB261 }, /* SSANGSIOS YO */
                             { 0xBEA5, 0xB281 }, /* SSANGSIOS U */
                             { 0xBEA6, 0xB282 }, /* SSANGSIOS U KIYEOK */
                             { 0xBEA7, 0xB285 }, /* SSANGSIOS U NIEUN */
                             { 0xBEA8, 0xB289 }, /* SSANGSIOS U RIEUL */
                             { 0xBEA9, 0xB291 }, /* SSANGSIOS U MIEUM */
                             { 0xBEAA, 0xB293 }, /* SSANGSIOS U PIEUP */
                             { 0xBEAB, 0xB297 }, /* SSANGSIOS U IEUNG */
                             { 0xBEAC, 0xB2A1 }, /* SSANGSIOS WEO */
                             { 0xBEAD, 0xB2B6 }, /* SSANGSIOS WEO SSANGSIOS */
                             { 0xBEAE, 0xB2C1 }, /* SSANGSIOS WE */
                             { 0xBEAF, 0xB2E1 }, /* SSANGSIOS WI */
                             { 0xBEB0, 0xB2E5 }, /* SSANGSIOS WI NIEUN */
                             { 0xBEB1, 0xB357 }, /* SSANGSIOS YU IEUNG */
                             { 0xBEB2, 0xB361 }, /* SSANGSIOS EU */
                             { 0xBEB3, 0xB362 }, /* SSANGSIOS EU KIYEOK */
                             { 0xBEB4, 0xB365 }, /* SSANGSIOS EU NIEUN */
                             { 0xBEB5, 0xB369 }, /* SSANGSIOS EU RIEUL */
                             { 0xBEB6, 0xB36B }, /* SSANGSIOS EU RIEULMIEUM */
                             { 0xBEB7, 0xB370 }, /* SSANGSIOS EU RIEULHIEUH */
                             { 0xBEB8, 0xB371 }, /* SSANGSIOS EU MIEUM */
                             { 0xBEB9, 0xB373 }, /* SSANGSIOS EU PIEUP */
                             { 0xBEBA, 0xB381 }, /* SSANGSIOS YI */
                             { 0xBEBB, 0xB385 }, /* SSANGSIOS YI NIEUN */
                             { 0xBEBC, 0xB389 }, /* SSANGSIOS YI RIEUL */
                             { 0xBEBD, 0xB391 }, /* SSANGSIOS YI MIEUM */
                             { 0xBEBE, 0xB3A1 }, /* SSANGSIOS I */
                             { 0xBEBF, 0xB3A2 }, /* SSANGSIOS I KIYEOK */
                             { 0xBEC0, 0xB3A5 }, /* SSANGSIOS I NIEUN */
                             { 0xBEC1, 0xB3A9 }, /* SSANGSIOS I RIEUL */
                             { 0xBEC2, 0xB3B1 }, /* SSANGSIOS I MIEUM */
                             { 0xBEC3, 0xB3B3 }, /* SSANGSIOS I PIEUP */
                             { 0xBEC4, 0xB3B5 }, /* SSANGSIOS I SIOS */
                             { 0xBEC5, 0xB3B7 }, /* SSANGSIOS I IEUNG */
                             { 0xBEC6, 0xB461 }, /* IEUNG A */
                             { 0xBEC7, 0xB462 }, /* IEUNG A KIYEOK */
                             { 0xBEC8, 0xB465 }, /* IEUNG A NIEUN */
                             { 0xBEC9, 0xB466 }, /* IEUNG A NIEUNCIEUC */
                             { 0xBECA, 0xB467 }, /* IEUNG A NIEUNHIEUH */
                             { 0xBECB, 0xB469 }, /* IEUNG A RIEUL */
                             { 0xBECC, 0xB46A }, /* IEUNG A RIEULKIYEOK */
                             { 0xBECD, 0xB46B }, /* IEUNG A RIEULMIEUM */
                             { 0xBECE, 0xB470 }, /* IEUNG A RIEULHIEUH */
                             { 0xBECF, 0xB471 }, /* IEUNG A MIEUM */
                             { 0xBED0, 0xB473 }, /* IEUNG A PIEUP */
                             { 0xBED1, 0xB475 }, /* IEUNG A SIOS */
                             { 0xBED2, 0xB476 }, /* IEUNG A SSANGSIOS */
                             { 0xBED3, 0xB477 }, /* IEUNG A IEUNG */
                             { 0xBED4, 0xB47B }, /* IEUNG A THIEUTH */
                             { 0xBED5, 0xB47C }, /* IEUNG A PHIEUPH */
                             { 0xBED6, 0xB481 }, /* IEUNG AE */
                             { 0xBED7, 0xB482 }, /* IEUNG AE KIYEOK */
                             { 0xBED8, 0xB485 }, /* IEUNG AE NIEUN */
                             { 0xBED9, 0xB489 }, /* IEUNG AE RIEUL */
                             { 0xBEDA, 0xB491 }, /* IEUNG AE MIEUM */
                             { 0xBEDB, 0xB493 }, /* IEUNG AE PIEUP */
                             { 0xBEDC, 0xB495 }, /* IEUNG AE SIOS */
                             { 0xBEDD, 0xB496 }, /* IEUNG AE SSANGSIOS */
                             { 0xBEDE, 0xB497 }, /* IEUNG AE IEUNG */
                             { 0xBEDF, 0xB4A1 }, /* IEUNG YA */
                             { 0xBEE0, 0xB4A2 }, /* IEUNG YA KIYEOK */
                             { 0xBEE1, 0xB4A5 }, /* IEUNG YA NIEUN */
                             { 0xBEE2, 0xB4A9 }, /* IEUNG YA RIEUL */
                             { 0xBEE3, 0xB4AC }, /* IEUNG YA RIEULPIEUP */
                             { 0xBEE4, 0xB4B1 }, /* IEUNG YA MIEUM */
                             { 0xBEE5, 0xB4B3 }, /* IEUNG YA PIEUP */
                             { 0xBEE6, 0xB4B5 }, /* IEUNG YA SIOS */
                             { 0xBEE7, 0xB4B7 }, /* IEUNG YA IEUNG */
                             { 0xBEE8, 0xB4BB }, /* IEUNG YA THIEUTH */
                             { 0xBEE9, 0xB4BD }, /* IEUNG YA HIEUH */
                             { 0xBEEA, 0xB4C1 }, /* IEUNG YAE */
                             { 0xBEEB, 0xB4C5 }, /* IEUNG YAE NIEUN */
                             { 0xBEEC, 0xB4C9 }, /* IEUNG YAE RIEUL */
                             { 0xBEED, 0xB4D3 }, /* IEUNG YAE PIEUP */
                             { 0xBEEE, 0xB4E1 }, /* IEUNG EO */
                             { 0xBEEF, 0xB4E2 }, /* IEUNG EO KIYEOK */
                             { 0xBEF0, 0xB4E5 }, /* IEUNG EO NIEUN */
                             { 0xBEF1, 0xB4E6 }, /* IEUNG EO NIEUNCIEUC */
                             { 0xBEF2, 0xB4E8 }, /* IEUNG EO TIKEUT */
                             { 0xBEF3, 0xB4E9 }, /* IEUNG EO RIEUL */
                             { 0xBEF4, 0xB4EA }, /* IEUNG EO RIEULKIYEOK */
                             { 0xBEF5, 0xB4EB }, /* IEUNG EO RIEULMIEUM */
                             { 0xBEF6, 0xB4F1 }, /* IEUNG EO MIEUM */
                             { 0xBEF7, 0xB4F3 }, /* IEUNG EO PIEUP */
                             { 0xBEF8, 0xB4F4 }, /* IEUNG EO PIEUPSIOS */
                             { 0xBEF9, 0xB4F5 }, /* IEUNG EO SIOS */
                             { 0xBEFA, 0xB4F6 }, /* IEUNG EO SSANGSIOS */
                             { 0xBEFB, 0xB4F7 }, /* IEUNG EO IEUNG */
                             { 0xBEFC, 0xB4F8 }, /* IEUNG EO CIEUC */
                             { 0xBEFD, 0xB4FA }, /* IEUNG EO KHIEUKH */
                             { 0xBEFE, 0xB4FC }, /* IEUNG EO PHIEUPH */
                             { 0xBFA1, 0xB541 }, /* IEUNG E */
                             { 0xBFA2, 0xB542 }, /* IEUNG E KIYEOK */
                             { 0xBFA3, 0xB545 }, /* IEUNG E NIEUN */
                             { 0xBFA4, 0xB549 }, /* IEUNG E RIEUL */
                             { 0xBFA5, 0xB551 }, /* IEUNG E MIEUM */
                             { 0xBFA6, 0xB553 }, /* IEUNG E PIEUP */
                             { 0xBFA7, 0xB555 }, /* IEUNG E SIOS */
                             { 0xBFA8, 0xB557 }, /* IEUNG E IEUNG */
                             { 0xBFA9, 0xB561 }, /* IEUNG YEO */
                             { 0xBFAA, 0xB562 }, /* IEUNG YEO KIYEOK */
                             { 0xBFAB, 0xB563 }, /* IEUNG YEO SSANGKIYEOK */
                             { 0xBFAC, 0xB565 }, /* IEUNG YEO NIEUN */
                             { 0xBFAD, 0xB569 }, /* IEUNG YEO RIEUL */
                             { 0xBFAE, 0xB56B }, /* IEUNG YEO RIEULMIEUM */
                             { 0xBFAF, 0xB56C }, /* IEUNG YEO RIEULPIEUP */
                             { 0xBFB0, 0xB571 }, /* IEUNG YEO MIEUM */
                             { 0xBFB1, 0xB573 }, /* IEUNG YEO PIEUP */
                             { 0xBFB2, 0xB574 }, /* IEUNG YEO PIEUPSIOS */
                             { 0xBFB3, 0xB575 }, /* IEUNG YEO SIOS */
                             { 0xBFB4, 0xB576 }, /* IEUNG YEO SSANGSIOS */
                             { 0xBFB5, 0xB577 }, /* IEUNG YEO IEUNG */
                             { 0xBFB6, 0xB57B }, /* IEUNG YEO THIEUTH */
                             { 0xBFB7, 0xB57C }, /* IEUNG YEO PHIEUPH */
                             { 0xBFB8, 0xB57D }, /* IEUNG YEO HIEUH */
                             { 0xBFB9, 0xB581 }, /* IEUNG YE */
                             { 0xBFBA, 0xB585 }, /* IEUNG YE NIEUN */
                             { 0xBFBB, 0xB589 }, /* IEUNG YE RIEUL */
                             { 0xBFBC, 0xB591 }, /* IEUNG YE MIEUM */
                             { 0xBFBD, 0xB593 }, /* IEUNG YE PIEUP */
                             { 0xBFBE, 0xB595 }, /* IEUNG YE SIOS */
                             { 0xBFBF, 0xB596 }, /* IEUNG YE SSANGSIOS */
                             { 0xBFC0, 0xB5A1 }, /* IEUNG O */
                             { 0xBFC1, 0xB5A2 }, /* IEUNG O KIYEOK */
                             { 0xBFC2, 0xB5A5 }, /* IEUNG O NIEUN */
                             { 0xBFC3, 0xB5A9 }, /* IEUNG O RIEUL */
                             { 0xBFC4, 0xB5AA }, /* IEUNG O RIEULKIYEOK */
                             { 0xBFC5, 0xB5AB }, /* IEUNG O RIEULMIEUM */
                             { 0xBFC6, 0xB5AD }, /* IEUNG O RIEULSIOS */
                             { 0xBFC7, 0xB5B0 }, /* IEUNG O RIEULHIEUH */
                             { 0xBFC8, 0xB5B1 }, /* IEUNG O MIEUM */
                             { 0xBFC9, 0xB5B3 }, /* IEUNG O PIEUP */
                             { 0xBFCA, 0xB5B5 }, /* IEUNG O SIOS */
                             { 0xBFCB, 0xB5B7 }, /* IEUNG O IEUNG */
                             { 0xBFCC, 0xB5B9 }, /* IEUNG O CHIEUCH */
                             { 0xBFCD, 0xB5C1 }, /* IEUNG WA */
                             { 0xBFCE, 0xB5C2 }, /* IEUNG WA KIYEOK */
                             { 0xBFCF, 0xB5C5 }, /* IEUNG WA NIEUN */
                             { 0xBFD0, 0xB5C9 }, /* IEUNG WA RIEUL */
                             { 0xBFD1, 0xB5D1 }, /* IEUNG WA MIEUM */
                             { 0xBFD2, 0xB5D3 }, /* IEUNG WA PIEUP */
                             { 0xBFD3, 0xB5D5 }, /* IEUNG WA SIOS */
                             { 0xBFD4, 0xB5D6 }, /* IEUNG WA SSANGSIOS */
                             { 0xBFD5, 0xB5D7 }, /* IEUNG WA IEUNG */
                             { 0xBFD6, 0xB5E1 }, /* IEUNG WAE */
                             { 0xBFD7, 0xB5E2 }, /* IEUNG WAE KIYEOK */
                             { 0xBFD8, 0xB5E5 }, /* IEUNG WAE NIEUN */
                             { 0xBFD9, 0xB5F1 }, /* IEUNG WAE MIEUM */
                             { 0xBFDA, 0xB5F5 }, /* IEUNG WAE SIOS */
                             { 0xBFDB, 0xB5F7 }, /* IEUNG WAE IEUNG */
                             { 0xBFDC, 0xB641 }, /* IEUNG OE */
                             { 0xBFDD, 0xB642 }, /* IEUNG OE KIYEOK */
                             { 0xBFDE, 0xB645 }, /* IEUNG OE NIEUN */
                             { 0xBFDF, 0xB649 }, /* IEUNG OE RIEUL */
                             { 0xBFE0, 0xB651 }, /* IEUNG OE MIEUM */
                             { 0xBFE1, 0xB653 }, /* IEUNG OE PIEUP */
                             { 0xBFE2, 0xB655 }, /* IEUNG OE SIOS */
                             { 0xBFE3, 0xB657 }, /* IEUNG OE IEUNG */
                             { 0xBFE4, 0xB661 }, /* IEUNG YO */
                             { 0xBFE5, 0xB662 }, /* IEUNG YO KIYEOK */
                             { 0xBFE6, 0xB665 }, /* IEUNG YO NIEUN */
                             { 0xBFE7, 0xB669 }, /* IEUNG YO RIEUL */
                             { 0xBFE8, 0xB671 }, /* IEUNG YO MIEUM */
                             { 0xBFE9, 0xB673 }, /* IEUNG YO PIEUP */
                             { 0xBFEA, 0xB675 }, /* IEUNG YO SIOS */
                             { 0xBFEB, 0xB677 }, /* IEUNG YO IEUNG */
                             { 0xBFEC, 0xB681 }, /* IEUNG U */
                             { 0xBFED, 0xB682 }, /* IEUNG U KIYEOK */
                             { 0xBFEE, 0xB685 }, /* IEUNG U NIEUN */
                             { 0xBFEF, 0xB689 }, /* IEUNG U RIEUL */
                             { 0xBFF0, 0xB68A }, /* IEUNG U RIEULKIYEOK */
                             { 0xBFF1, 0xB68B }, /* IEUNG U RIEULMIEUM */
                             { 0xBFF2, 0xB691 }, /* IEUNG U MIEUM */
                             { 0xBFF3, 0xB693 }, /* IEUNG U PIEUP */
                             { 0xBFF4, 0xB695 }, /* IEUNG U SIOS */
                             { 0xBFF5, 0xB697 }, /* IEUNG U IEUNG */
                             { 0xBFF6, 0xB6A1 }, /* IEUNG WEO */
                             { 0xBFF7, 0xB6A2 }, /* IEUNG WEO KIYEOK */
                             { 0xBFF8, 0xB6A5 }, /* IEUNG WEO NIEUN */
                             { 0xBFF9, 0xB6A9 }, /* IEUNG WEO RIEUL */
                             { 0xBFFA, 0xB6B1 }, /* IEUNG WEO MIEUM */
                             { 0xBFFB, 0xB6B3 }, /* IEUNG WEO PIEUP */
                             { 0xBFFC, 0xB6B6 }, /* IEUNG WEO SSANGSIOS */
                             { 0xBFFD, 0xB6B7 }, /* IEUNG WEO IEUNG */
                             { 0xBFFE, 0xB6C1 }, /* IEUNG WE */
                             { 0xC0A1, 0xB6C2 }, /* IEUNG WE KIYEOK */
                             { 0xC0A2, 0xB6C5 }, /* IEUNG WE NIEUN */
                             { 0xC0A3, 0xB6C9 }, /* IEUNG WE RIEUL */
                             { 0xC0A4, 0xB6D1 }, /* IEUNG WE MIEUM */
                             { 0xC0A5, 0xB6D3 }, /* IEUNG WE PIEUP */
                             { 0xC0A6, 0xB6D7 }, /* IEUNG WE IEUNG */
                             { 0xC0A7, 0xB6E1 }, /* IEUNG WI */
                             { 0xC0A8, 0xB6E2 }, /* IEUNG WI KIYEOK */
                             { 0xC0A9, 0xB6E5 }, /* IEUNG WI NIEUN */
                             { 0xC0AA, 0xB6E9 }, /* IEUNG WI RIEUL */
                             { 0xC0AB, 0xB6F1 }, /* IEUNG WI MIEUM */
                             { 0xC0AC, 0xB6F3 }, /* IEUNG WI PIEUP */
                             { 0xC0AD, 0xB6F5 }, /* IEUNG WI SIOS */
                             { 0xC0AE, 0xB6F7 }, /* IEUNG WI IEUNG */
                             { 0xC0AF, 0xB741 }, /* IEUNG YU */
                             { 0xC0B0, 0xB742 }, /* IEUNG YU KIYEOK */
                             { 0xC0B1, 0xB745 }, /* IEUNG YU NIEUN */
                             { 0xC0B2, 0xB749 }, /* IEUNG YU RIEUL */
                             { 0xC0B3, 0xB751 }, /* IEUNG YU MIEUM */
                             { 0xC0B4, 0xB753 }, /* IEUNG YU PIEUP */
                             { 0xC0B5, 0xB755 }, /* IEUNG YU SIOS */
                             { 0xC0B6, 0xB757 }, /* IEUNG YU IEUNG */
                             { 0xC0B7, 0xB759 }, /* IEUNG YU CHIEUCH */
                             { 0xC0B8, 0xB761 }, /* IEUNG EU */
                             { 0xC0B9, 0xB762 }, /* IEUNG EU KIYEOK */
                             { 0xC0BA, 0xB765 }, /* IEUNG EU NIEUN */
                             { 0xC0BB, 0xB769 }, /* IEUNG EU RIEUL */
                             { 0xC0BC, 0xB76F }, /* IEUNG EU RIEULPHIEUPH */
                             { 0xC0BD, 0xB771 }, /* IEUNG EU MIEUM */
                             { 0xC0BE, 0xB773 }, /* IEUNG EU PIEUP */
                             { 0xC0BF, 0xB775 }, /* IEUNG EU SIOS */
                             { 0xC0C0, 0xB777 }, /* IEUNG EU IEUNG */
                             { 0xC0C1, 0xB778 }, /* IEUNG EU CIEUC */
                             { 0xC0C2, 0xB779 }, /* IEUNG EU CHIEUCH */
                             { 0xC0C3, 0xB77A }, /* IEUNG EU KHIEUKH */
                             { 0xC0C4, 0xB77B }, /* IEUNG EU THIEUTH */
                             { 0xC0C5, 0xB77C }, /* IEUNG EU PHIEUPH */
                             { 0xC0C6, 0xB77D }, /* IEUNG EU HIEUH */
                             { 0xC0C7, 0xB781 }, /* IEUNG YI */
                             { 0xC0C8, 0xB785 }, /* IEUNG YI NIEUN */
                             { 0xC0C9, 0xB789 }, /* IEUNG YI RIEUL */
                             { 0xC0CA, 0xB791 }, /* IEUNG YI MIEUM */
                             { 0xC0CB, 0xB795 }, /* IEUNG YI SIOS */
                             { 0xC0CC, 0xB7A1 }, /* IEUNG I */
                             { 0xC0CD, 0xB7A2 }, /* IEUNG I KIYEOK */
                             { 0xC0CE, 0xB7A5 }, /* IEUNG I NIEUN */
                             { 0xC0CF, 0xB7A9 }, /* IEUNG I RIEUL */
                             { 0xC0D0, 0xB7AA }, /* IEUNG I RIEULKIYEOK */
                             { 0xC0D1, 0xB7AB }, /* IEUNG I RIEULMIEUM */
                             { 0xC0D2, 0xB7B0 }, /* IEUNG I RIEULHIEUH */
                             { 0xC0D3, 0xB7B1 }, /* IEUNG I MIEUM */
                             { 0xC0D4, 0xB7B3 }, /* IEUNG I PIEUP */
                             { 0xC0D5, 0xB7B5 }, /* IEUNG I SIOS */
                             { 0xC0D6, 0xB7B6 }, /* IEUNG I SSANGSIOS */
                             { 0xC0D7, 0xB7B7 }, /* IEUNG I IEUNG */
                             { 0xC0D8, 0xB7B8 }, /* IEUNG I CIEUC */
                             { 0xC0D9, 0xB7BC }, /* IEUNG I PHIEUPH */
                             { 0xC0DA, 0xB861 }, /* CIEUC A */
                             { 0xC0DB, 0xB862 }, /* CIEUC A KIYEOK */
                             { 0xC0DC, 0xB865 }, /* CIEUC A NIEUN */
                             { 0xC0DD, 0xB867 }, /* CIEUC A NIEUNHIEUH */
                             { 0xC0DE, 0xB868 }, /* CIEUC A TIKEUT */
                             { 0xC0DF, 0xB869 }, /* CIEUC A RIEUL */
                             { 0xC0E0, 0xB86B }, /* CIEUC A RIEULMIEUM */
                             { 0xC0E1, 0xB871 }, /* CIEUC A MIEUM */
                             { 0xC0E2, 0xB873 }, /* CIEUC A PIEUP */
                             { 0xC0E3, 0xB875 }, /* CIEUC A SIOS */
                             { 0xC0E4, 0xB876 }, /* CIEUC A SSANGSIOS */
                             { 0xC0E5, 0xB877 }, /* CIEUC A IEUNG */
                             { 0xC0E6, 0xB878 }, /* CIEUC A CIEUC */
                             { 0xC0E7, 0xB881 }, /* CIEUC AE */
                             { 0xC0E8, 0xB882 }, /* CIEUC AE KIYEOK */
                             { 0xC0E9, 0xB885 }, /* CIEUC AE NIEUN */
                             { 0xC0EA, 0xB889 }, /* CIEUC AE RIEUL */
                             { 0xC0EB, 0xB891 }, /* CIEUC AE MIEUM */
                             { 0xC0EC, 0xB893 }, /* CIEUC AE PIEUP */
                             { 0xC0ED, 0xB895 }, /* CIEUC AE SIOS */
                             { 0xC0EE, 0xB896 }, /* CIEUC AE SSANGSIOS */
                             { 0xC0EF, 0xB897 }, /* CIEUC AE IEUNG */
                             { 0xC0F0, 0xB8A1 }, /* CIEUC YA */
                             { 0xC0F1, 0xB8A2 }, /* CIEUC YA KIYEOK */
                             { 0xC0F2, 0xB8A5 }, /* CIEUC YA NIEUN */
                             { 0xC0F3, 0xB8A7 }, /* CIEUC YA NIEUNHIEUH */
                             { 0xC0F4, 0xB8A9 }, /* CIEUC YA RIEUL */
                             { 0xC0F5, 0xB8B1 }, /* CIEUC YA MIEUM */
                             { 0xC0F6, 0xB8B7 }, /* CIEUC YA IEUNG */
                             { 0xC0F7, 0xB8C1 }, /* CIEUC YAE */
                             { 0xC0F8, 0xB8C5 }, /* CIEUC YAE NIEUN */
                             { 0xC0F9, 0xB8C9 }, /* CIEUC YAE RIEUL */
                             { 0xC0FA, 0xB8E1 }, /* CIEUC EO */
                             { 0xC0FB, 0xB8E2 }, /* CIEUC EO KIYEOK */
                             { 0xC0FC, 0xB8E5 }, /* CIEUC EO NIEUN */
                             { 0xC0FD, 0xB8E9 }, /* CIEUC EO RIEUL */
                             { 0xC0FE, 0xB8EB }, /* CIEUC EO RIEULMIEUM */
                             { 0xC1A1, 0xB8F1 }, /* CIEUC EO MIEUM */
                             { 0xC1A2, 0xB8F3 }, /* CIEUC EO PIEUP */
                             { 0xC1A3, 0xB8F5 }, /* CIEUC EO SIOS */
                             { 0xC1A4, 0xB8F7 }, /* CIEUC EO IEUNG */
                             { 0xC1A5, 0xB8F8 }, /* CIEUC EO CIEUC */
                             { 0xC1A6, 0xB941 }, /* CIEUC E */
                             { 0xC1A7, 0xB942 }, /* CIEUC E KIYEOK */
                             { 0xC1A8, 0xB945 }, /* CIEUC E NIEUN */
                             { 0xC1A9, 0xB949 }, /* CIEUC E RIEUL */
                             { 0xC1AA, 0xB951 }, /* CIEUC E MIEUM */
                             { 0xC1AB, 0xB953 }, /* CIEUC E PIEUP */
                             { 0xC1AC, 0xB955 }, /* CIEUC E SIOS */
                             { 0xC1AD, 0xB957 }, /* CIEUC E IEUNG */
                             { 0xC1AE, 0xB961 }, /* CIEUC YEO */
                             { 0xC1AF, 0xB965 }, /* CIEUC YEO NIEUN */
                             { 0xC1B0, 0xB969 }, /* CIEUC YEO RIEUL */
                             { 0xC1B1, 0xB971 }, /* CIEUC YEO MIEUM */
                             { 0xC1B2, 0xB973 }, /* CIEUC YEO PIEUP */
                             { 0xC1B3, 0xB976 }, /* CIEUC YEO SSANGSIOS */
                             { 0xC1B4, 0xB977 }, /* CIEUC YEO IEUNG */
                             { 0xC1B5, 0xB981 }, /* CIEUC YE */
                             { 0xC1B6, 0xB9A1 }, /* CIEUC O */
                             { 0xC1B7, 0xB9A2 }, /* CIEUC O KIYEOK */
                             { 0xC1B8, 0xB9A5 }, /* CIEUC O NIEUN */
                             { 0xC1B9, 0xB9A9 }, /* CIEUC O RIEUL */
                             { 0xC1BA, 0xB9AB }, /* CIEUC O RIEULMIEUM */
                             { 0xC1BB, 0xB9B1 }, /* CIEUC O MIEUM */
                             { 0xC1BC, 0xB9B3 }, /* CIEUC O PIEUP */
                             { 0xC1BD, 0xB9B5 }, /* CIEUC O SIOS */
                             { 0xC1BE, 0xB9B7 }, /* CIEUC O IEUNG */
                             { 0xC1BF, 0xB9B8 }, /* CIEUC O CIEUC */
                             { 0xC1C0, 0xB9B9 }, /* CIEUC O CHIEUCH */
                             { 0xC1C1, 0xB9BD }, /* CIEUC O HIEUH */
                             { 0xC1C2, 0xB9C1 }, /* CIEUC WA */
                             { 0xC1C3, 0xB9C2 }, /* CIEUC WA KIYEOK */
                             { 0xC1C4, 0xB9C9 }, /* CIEUC WA RIEUL */
                             { 0xC1C5, 0xB9D3 }, /* CIEUC WA PIEUP */
                             { 0xC1C6, 0xB9D5 }, /* CIEUC WA SIOS */
                             { 0xC1C7, 0xB9D7 }, /* CIEUC WA IEUNG */
                             { 0xC1C8, 0xB9E1 }, /* CIEUC WAE */
                             { 0xC1C9, 0xB9F6 }, /* CIEUC WAE SSANGSIOS */
                             { 0xC1CA, 0xB9F7 }, /* CIEUC WAE IEUNG */
                             { 0xC1CB, 0xBA41 }, /* CIEUC OE */
                             { 0xC1CC, 0xBA45 }, /* CIEUC OE NIEUN */
                             { 0xC1CD, 0xBA49 }, /* CIEUC OE RIEUL */
                             { 0xC1CE, 0xBA51 }, /* CIEUC OE MIEUM */
                             { 0xC1CF, 0xBA53 }, /* CIEUC OE PIEUP */
                             { 0xC1D0, 0xBA55 }, /* CIEUC OE SIOS */
                             { 0xC1D1, 0xBA57 }, /* CIEUC OE IEUNG */
                             { 0xC1D2, 0xBA61 }, /* CIEUC YO */
                             { 0xC1D3, 0xBA62 }, /* CIEUC YO KIYEOK */
                             { 0xC1D4, 0xBA65 }, /* CIEUC YO NIEUN */
                             { 0xC1D5, 0xBA77 }, /* CIEUC YO IEUNG */
                             { 0xC1D6, 0xBA81 }, /* CIEUC U */
                             { 0xC1D7, 0xBA82 }, /* CIEUC U KIYEOK */
                             { 0xC1D8, 0xBA85 }, /* CIEUC U NIEUN */
                             { 0xC1D9, 0xBA89 }, /* CIEUC U RIEUL */
                             { 0xC1DA, 0xBA8A }, /* CIEUC U RIEULKIYEOK */
                             { 0xC1DB, 0xBA8B }, /* CIEUC U RIEULMIEUM */
                             { 0xC1DC, 0xBA91 }, /* CIEUC U MIEUM */
                             { 0xC1DD, 0xBA93 }, /* CIEUC U PIEUP */
                             { 0xC1DE, 0xBA95 }, /* CIEUC U SIOS */
                             { 0xC1DF, 0xBA97 }, /* CIEUC U IEUNG */
                             { 0xC1E0, 0xBAA1 }, /* CIEUC WEO */
                             { 0xC1E1, 0xBAB6 }, /* CIEUC WEO SSANGSIOS */
                             { 0xC1E2, 0xBAC1 }, /* CIEUC WE */
                             { 0xC1E3, 0xBAE1 }, /* CIEUC WI */
                             { 0xC1E4, 0xBAE2 }, /* CIEUC WI KIYEOK */
                             { 0xC1E5, 0xBAE5 }, /* CIEUC WI NIEUN */
                             { 0xC1E6, 0xBAE9 }, /* CIEUC WI RIEUL */
                             { 0xC1E7, 0xBAF1 }, /* CIEUC WI MIEUM */
                             { 0xC1E8, 0xBAF3 }, /* CIEUC WI PIEUP */
                             { 0xC1E9, 0xBAF5 }, /* CIEUC WI SIOS */
                             { 0xC1EA, 0xBB41 }, /* CIEUC YU */
                             { 0xC1EB, 0xBB45 }, /* CIEUC YU NIEUN */
                             { 0xC1EC, 0xBB49 }, /* CIEUC YU RIEUL */
                             { 0xC1ED, 0xBB51 }, /* CIEUC YU MIEUM */
                             { 0xC1EE, 0xBB61 }, /* CIEUC EU */
                             { 0xC1EF, 0xBB62 }, /* CIEUC EU KIYEOK */
                             { 0xC1F0, 0xBB65 }, /* CIEUC EU NIEUN */
                             { 0xC1F1, 0xBB69 }, /* CIEUC EU RIEUL */
                             { 0xC1F2, 0xBB71 }, /* CIEUC EU MIEUM */
                             { 0xC1F3, 0xBB73 }, /* CIEUC EU PIEUP */
                             { 0xC1F4, 0xBB75 }, /* CIEUC EU SIOS */
                             { 0xC1F5, 0xBB77 }, /* CIEUC EU IEUNG */
                             { 0xC1F6, 0xBBA1 }, /* CIEUC I */
                             { 0xC1F7, 0xBBA2 }, /* CIEUC I KIYEOK */
                             { 0xC1F8, 0xBBA5 }, /* CIEUC I NIEUN */
                             { 0xC1F9, 0xBBA8 }, /* CIEUC I TIKEUT */
                             { 0xC1FA, 0xBBA9 }, /* CIEUC I RIEUL */
                             { 0xC1FB, 0xBBAB }, /* CIEUC I RIEULMIEUM */
                             { 0xC1FC, 0xBBB1 }, /* CIEUC I MIEUM */
                             { 0xC1FD, 0xBBB3 }, /* CIEUC I PIEUP */
                             { 0xC1FE, 0xBBB5 }, /* CIEUC I SIOS */
                             { 0xC2A1, 0xBBB7 }, /* CIEUC I IEUNG */
                             { 0xC2A2, 0xBBB8 }, /* CIEUC I CIEUC */
                             { 0xC2A3, 0xBBBB }, /* CIEUC I THIEUTH */
                             { 0xC2A4, 0xBBBC }, /* CIEUC I PHIEUPH */
                             { 0xC2A5, 0xBC61 }, /* SSANGCIEUC A */
                             { 0xC2A6, 0xBC62 }, /* SSANGCIEUC A KIYEOK */
                             { 0xC2A7, 0xBC65 }, /* SSANGCIEUC A NIEUN */
                             { 0xC2A8, 0xBC67 }, /* SSANGCIEUC A NIEUNHIEUH */
                             { 0xC2A9, 0xBC69 }, /* SSANGCIEUC A RIEUL */
                             { 0xC2AA, 0xBC6C }, /* SSANGCIEUC A RIEULPIEUP */
                             { 0xC2AB, 0xBC71 }, /* SSANGCIEUC A MIEUM */
                             { 0xC2AC, 0xBC73 }, /* SSANGCIEUC A PIEUP */
                             { 0xC2AD, 0xBC75 }, /* SSANGCIEUC A SIOS */
                             { 0xC2AE, 0xBC76 }, /* SSANGCIEUC A SSANGSIOS */
                             { 0xC2AF, 0xBC77 }, /* SSANGCIEUC A IEUNG */
                             { 0xC2B0, 0xBC81 }, /* SSANGCIEUC AE */
                             { 0xC2B1, 0xBC82 }, /* SSANGCIEUC AE KIYEOK */
                             { 0xC2B2, 0xBC85 }, /* SSANGCIEUC AE NIEUN */
                             { 0xC2B3, 0xBC89 }, /* SSANGCIEUC AE RIEUL */
                             { 0xC2B4, 0xBC91 }, /* SSANGCIEUC AE MIEUM */
                             { 0xC2B5, 0xBC93 }, /* SSANGCIEUC AE PIEUP */
                             { 0xC2B6, 0xBC95 }, /* SSANGCIEUC AE SIOS */
                             { 0xC2B7, 0xBC96 }, /* SSANGCIEUC AE SSANGSIOS */
                             { 0xC2B8, 0xBC97 }, /* SSANGCIEUC AE IEUNG */
                             { 0xC2B9, 0xBCA1 }, /* SSANGCIEUC YA */
                             { 0xC2BA, 0xBCA5 }, /* SSANGCIEUC YA NIEUN */
                             { 0xC2BB, 0xBCB7 }, /* SSANGCIEUC YA IEUNG */
                             { 0xC2BC, 0xBCE1 }, /* SSANGCIEUC EO */
                             { 0xC2BD, 0xBCE2 }, /* SSANGCIEUC EO KIYEOK */
                             { 0xC2BE, 0xBCE5 }, /* SSANGCIEUC EO NIEUN */
                             { 0xC2BF, 0xBCE9 }, /* SSANGCIEUC EO RIEUL */
                             { 0xC2C0, 0xBCF1 }, /* SSANGCIEUC EO MIEUM */
                             { 0xC2C1, 0xBCF3 }, /* SSANGCIEUC EO PIEUP */
                             { 0xC2C2, 0xBCF5 }, /* SSANGCIEUC EO SIOS */
                             { 0xC2C3, 0xBCF6 }, /* SSANGCIEUC EO SSANGSIOS */
                             { 0xC2C4, 0xBCF7 }, /* SSANGCIEUC EO IEUNG */
                             { 0xC2C5, 0xBD41 }, /* SSANGCIEUC E */
                             { 0xC2C6, 0xBD57 }, /* SSANGCIEUC E IEUNG */
                             { 0xC2C7, 0xBD61 }, /* SSANGCIEUC YEO */
                             { 0xC2C8, 0xBD76 }, /* SSANGCIEUC YEO SSANGSIOS */
                             { 0xC2C9, 0xBDA1 }, /* SSANGCIEUC O */
                             { 0xC2CA, 0xBDA2 }, /* SSANGCIEUC O KIYEOK */
                             { 0xC2CB, 0xBDA5 }, /* SSANGCIEUC O NIEUN */
                             { 0xC2CC, 0xBDA9 }, /* SSANGCIEUC O RIEUL */
                             { 0xC2CD, 0xBDB1 }, /* SSANGCIEUC O MIEUM */
                             { 0xC2CE, 0xBDB3 }, /* SSANGCIEUC O PIEUP */
                             { 0xC2CF, 0xBDB5 }, /* SSANGCIEUC O SIOS */
                             { 0xC2D0, 0xBDB7 }, /* SSANGCIEUC O IEUNG */
                             { 0xC2D1, 0xBDB9 }, /* SSANGCIEUC O CHIEUCH */
                             { 0xC2D2, 0xBDC1 }, /* SSANGCIEUC WA */
                             { 0xC2D3, 0xBDC2 }, /* SSANGCIEUC WA KIYEOK */
                             { 0xC2D4, 0xBDC9 }, /* SSANGCIEUC WA RIEUL */
                             { 0xC2D5, 0xBDD6 }, /* SSANGCIEUC WA SSANGSIOS */
                             { 0xC2D6, 0xBDE1 }, /* SSANGCIEUC WAE */
                             { 0xC2D7, 0xBDF6 }, /* SSANGCIEUC WAE SSANGSIOS */
                             { 0xC2D8, 0xBE41 }, /* SSANGCIEUC OE */
                             { 0xC2D9, 0xBE45 }, /* SSANGCIEUC OE NIEUN */
                             { 0xC2DA, 0xBE49 }, /* SSANGCIEUC OE RIEUL */
                             { 0xC2DB, 0xBE51 }, /* SSANGCIEUC OE MIEUM */
                             { 0xC2DC, 0xBE53 }, /* SSANGCIEUC OE PIEUP */
                             { 0xC2DD, 0xBE77 }, /* SSANGCIEUC YO IEUNG */
                             { 0xC2DE, 0xBE81 }, /* SSANGCIEUC U */
                             { 0xC2DF, 0xBE82 }, /* SSANGCIEUC U KIYEOK */
                             { 0xC2E0, 0xBE85 }, /* SSANGCIEUC U NIEUN */
                             { 0xC2E1, 0xBE89 }, /* SSANGCIEUC U RIEUL */
                             { 0xC2E2, 0xBE91 }, /* SSANGCIEUC U MIEUM */
                             { 0xC2E3, 0xBE93 }, /* SSANGCIEUC U PIEUP */
                             { 0xC2E4, 0xBE97 }, /* SSANGCIEUC U IEUNG */
                             { 0xC2E5, 0xBEA1 }, /* SSANGCIEUC WEO */
                             { 0xC2E6, 0xBEB6 }, /* SSANGCIEUC WEO SSANGSIOS */
                             { 0xC2E7, 0xBEB7 }, /* SSANGCIEUC WEO IEUNG */
                             { 0xC2E8, 0xBEE1 }, /* SSANGCIEUC WI */
                             { 0xC2E9, 0xBF41 }, /* SSANGCIEUC YU */
                             { 0xC2EA, 0xBF61 }, /* SSANGCIEUC EU */
                             { 0xC2EB, 0xBF71 }, /* SSANGCIEUC EU MIEUM */
                             { 0xC2EC, 0xBF75 }, /* SSANGCIEUC EU SIOS */
                             { 0xC2ED, 0xBF77 }, /* SSANGCIEUC EU IEUNG */
                             { 0xC2EE, 0xBFA1 }, /* SSANGCIEUC I */
                             { 0xC2EF, 0xBFA2 }, /* SSANGCIEUC I KIYEOK */
                             { 0xC2F0, 0xBFA5 }, /* SSANGCIEUC I NIEUN */
                             { 0xC2F1, 0xBFA9 }, /* SSANGCIEUC I RIEUL */
                             { 0xC2F2, 0xBFB1 }, /* SSANGCIEUC I MIEUM */
                             { 0xC2F3, 0xBFB3 }, /* SSANGCIEUC I PIEUP */
                             { 0xC2F4, 0xBFB7 }, /* SSANGCIEUC I IEUNG */
                             { 0xC2F5, 0xBFB8 }, /* SSANGCIEUC I CIEUC */
                             { 0xC2F6, 0xBFBD }, /* SSANGCIEUC I HIEUH */
                             { 0xC2F7, 0xC061 }, /* CHIEUCH A */
                             { 0xC2F8, 0xC062 }, /* CHIEUCH A KIYEOK */
                             { 0xC2F9, 0xC065 }, /* CHIEUCH A NIEUN */
                             { 0xC2FA, 0xC067 }, /* CHIEUCH A NIEUNHIEUH */
                             { 0xC2FB, 0xC069 }, /* CHIEUCH A RIEUL */
                             { 0xC2FC, 0xC071 }, /* CHIEUCH A MIEUM */
                             { 0xC2FD, 0xC073 }, /* CHIEUCH A PIEUP */
                             { 0xC2FE, 0xC075 }, /* CHIEUCH A SIOS */
                             { 0xC3A1, 0xC076 }, /* CHIEUCH A SSANGSIOS */
                             { 0xC3A2, 0xC077 }, /* CHIEUCH A IEUNG */
                             { 0xC3A3, 0xC078 }, /* CHIEUCH A CIEUC */
                             { 0xC3A4, 0xC081 }, /* CHIEUCH AE */
                             { 0xC3A5, 0xC082 }, /* CHIEUCH AE KIYEOK */
                             { 0xC3A6, 0xC085 }, /* CHIEUCH AE NIEUN */
                             { 0xC3A7, 0xC089 }, /* CHIEUCH AE RIEUL */
                             { 0xC3A8, 0xC091 }, /* CHIEUCH AE MIEUM */
                             { 0xC3A9, 0xC093 }, /* CHIEUCH AE PIEUP */
                             { 0xC3AA, 0xC095 }, /* CHIEUCH AE SIOS */
                             { 0xC3AB, 0xC096 }, /* CHIEUCH AE SSANGSIOS */
                             { 0xC3AC, 0xC097 }, /* CHIEUCH AE IEUNG */
                             { 0xC3AD, 0xC0A1 }, /* CHIEUCH YA */
                             { 0xC3AE, 0xC0A5 }, /* CHIEUCH YA NIEUN */
                             { 0xC3AF, 0xC0A7 }, /* CHIEUCH YA NIEUNHIEUH */
                             { 0xC3B0, 0xC0A9 }, /* CHIEUCH YA RIEUL */
                             { 0xC3B1, 0xC0B1 }, /* CHIEUCH YA MIEUM */
                             { 0xC3B2, 0xC0B7 }, /* CHIEUCH YA IEUNG */
                             { 0xC3B3, 0xC0E1 }, /* CHIEUCH EO */
                             { 0xC3B4, 0xC0E2 }, /* CHIEUCH EO KIYEOK */
                             { 0xC3B5, 0xC0E5 }, /* CHIEUCH EO NIEUN */
                             { 0xC3B6, 0xC0E9 }, /* CHIEUCH EO RIEUL */
                             { 0xC3B7, 0xC0F1 }, /* CHIEUCH EO MIEUM */
                             { 0xC3B8, 0xC0F3 }, /* CHIEUCH EO PIEUP */
                             { 0xC3B9, 0xC0F5 }, /* CHIEUCH EO SIOS */
                             { 0xC3BA, 0xC0F6 }, /* CHIEUCH EO SSANGSIOS */
                             { 0xC3BB, 0xC0F7 }, /* CHIEUCH EO IEUNG */
                             { 0xC3BC, 0xC141 }, /* CHIEUCH E */
                             { 0xC3BD, 0xC142 }, /* CHIEUCH E KIYEOK */
                             { 0xC3BE, 0xC145 }, /* CHIEUCH E NIEUN */
                             { 0xC3BF, 0xC149 }, /* CHIEUCH E RIEUL */
                             { 0xC3C0, 0xC151 }, /* CHIEUCH E MIEUM */
                             { 0xC3C1, 0xC153 }, /* CHIEUCH E PIEUP */
                             { 0xC3C2, 0xC155 }, /* CHIEUCH E SIOS */
                             { 0xC3C3, 0xC157 }, /* CHIEUCH E IEUNG */
                             { 0xC3C4, 0xC161 }, /* CHIEUCH YEO */
                             { 0xC3C5, 0xC165 }, /* CHIEUCH YEO NIEUN */
                             { 0xC3C6, 0xC176 }, /* CHIEUCH YEO SSANGSIOS */
                             { 0xC3C7, 0xC181 }, /* CHIEUCH YE */
                             { 0xC3C8, 0xC185 }, /* CHIEUCH YE NIEUN */
                             { 0xC3C9, 0xC197 }, /* CHIEUCH YE IEUNG */
                             { 0xC3CA, 0xC1A1 }, /* CHIEUCH O */
                             { 0xC3CB, 0xC1A2 }, /* CHIEUCH O KIYEOK */
                             { 0xC3CC, 0xC1A5 }, /* CHIEUCH O NIEUN */
                             { 0xC3CD, 0xC1A9 }, /* CHIEUCH O RIEUL */
                             { 0xC3CE, 0xC1B1 }, /* CHIEUCH O MIEUM */
                             { 0xC3CF, 0xC1B3 }, /* CHIEUCH O PIEUP */
                             { 0xC3D0, 0xC1B5 }, /* CHIEUCH O SIOS */
                             { 0xC3D1, 0xC1B7 }, /* CHIEUCH O IEUNG */
                             { 0xC3D2, 0xC1C1 }, /* CHIEUCH WA */
                             { 0xC3D3, 0xC1C5 }, /* CHIEUCH WA NIEUN */
                             { 0xC3D4, 0xC1C9 }, /* CHIEUCH WA RIEUL */
                             { 0xC3D5, 0xC1D7 }, /* CHIEUCH WA IEUNG */
                             { 0xC3D6, 0xC241 }, /* CHIEUCH OE */
                             { 0xC3D7, 0xC245 }, /* CHIEUCH OE NIEUN */
                             { 0xC3D8, 0xC249 }, /* CHIEUCH OE RIEUL */
                             { 0xC3D9, 0xC251 }, /* CHIEUCH OE MIEUM */
                             { 0xC3DA, 0xC253 }, /* CHIEUCH OE PIEUP */
                             { 0xC3DB, 0xC255 }, /* CHIEUCH OE SIOS */
                             { 0xC3DC, 0xC257 }, /* CHIEUCH OE IEUNG */
                             { 0xC3DD, 0xC261 }, /* CHIEUCH YO */
                             { 0xC3DE, 0xC271 }, /* CHIEUCH YO MIEUM */
                             { 0xC3DF, 0xC281 }, /* CHIEUCH U */
                             { 0xC3E0, 0xC282 }, /* CHIEUCH U KIYEOK */
                             { 0xC3E1, 0xC285 }, /* CHIEUCH U NIEUN */
                             { 0xC3E2, 0xC289 }, /* CHIEUCH U RIEUL */
                             { 0xC3E3, 0xC291 }, /* CHIEUCH U MIEUM */
                             { 0xC3E4, 0xC293 }, /* CHIEUCH U PIEUP */
                             { 0xC3E5, 0xC295 }, /* CHIEUCH U SIOS */
                             { 0xC3E6, 0xC297 }, /* CHIEUCH U IEUNG */
                             { 0xC3E7, 0xC2A1 }, /* CHIEUCH WEO */
                             { 0xC3E8, 0xC2B6 }, /* CHIEUCH WEO SSANGSIOS */
                             { 0xC3E9, 0xC2C1 }, /* CHIEUCH WE */
                             { 0xC3EA, 0xC2C5 }, /* CHIEUCH WE NIEUN */
                             { 0xC3EB, 0xC2E1 }, /* CHIEUCH WI */
                             { 0xC3EC, 0xC2E5 }, /* CHIEUCH WI NIEUN */
                             { 0xC3ED, 0xC2E9 }, /* CHIEUCH WI RIEUL */
                             { 0xC3EE, 0xC2F1 }, /* CHIEUCH WI MIEUM */
                             { 0xC3EF, 0xC2F3 }, /* CHIEUCH WI PIEUP */
                             { 0xC3F0, 0xC2F5 }, /* CHIEUCH WI SIOS */
                             { 0xC3F1, 0xC2F7 }, /* CHIEUCH WI IEUNG */
                             { 0xC3F2, 0xC341 }, /* CHIEUCH YU */
                             { 0xC3F3, 0xC345 }, /* CHIEUCH YU NIEUN */
                             { 0xC3F4, 0xC349 }, /* CHIEUCH YU RIEUL */
                             { 0xC3F5, 0xC351 }, /* CHIEUCH YU MIEUM */
                             { 0xC3F6, 0xC357 }, /* CHIEUCH YU IEUNG */
                             { 0xC3F7, 0xC361 }, /* CHIEUCH EU */
                             { 0xC3F8, 0xC362 }, /* CHIEUCH EU KIYEOK */
                             { 0xC3F9, 0xC365 }, /* CHIEUCH EU NIEUN */
                             { 0xC3FA, 0xC369 }, /* CHIEUCH EU RIEUL */
                             { 0xC3FB, 0xC371 }, /* CHIEUCH EU MIEUM */
                             { 0xC3FC, 0xC373 }, /* CHIEUCH EU PIEUP */
                             { 0xC3FD, 0xC375 }, /* CHIEUCH EU SIOS */
                             { 0xC3FE, 0xC377 }, /* CHIEUCH EU IEUNG */
                             { 0xC4A1, 0xC3A1 }, /* CHIEUCH I */
                             { 0xC4A2, 0xC3A2 }, /* CHIEUCH I KIYEOK */
                             { 0xC4A3, 0xC3A5 }, /* CHIEUCH I NIEUN */
                             { 0xC4A4, 0xC3A8 }, /* CHIEUCH I TIKEUT */
                             { 0xC4A5, 0xC3A9 }, /* CHIEUCH I RIEUL */
                             { 0xC4A6, 0xC3AA }, /* CHIEUCH I RIEULKIYEOK */
                             { 0xC4A7, 0xC3B1 }, /* CHIEUCH I MIEUM */
                             { 0xC4A8, 0xC3B3 }, /* CHIEUCH I PIEUP */
                             { 0xC4A9, 0xC3B5 }, /* CHIEUCH I SIOS */
                             { 0xC4AA, 0xC3B7 }, /* CHIEUCH I IEUNG */
                             { 0xC4AB, 0xC461 }, /* KHIEUKH A */
                             { 0xC4AC, 0xC462 }, /* KHIEUKH A KIYEOK */
                             { 0xC4AD, 0xC465 }, /* KHIEUKH A NIEUN */
                             { 0xC4AE, 0xC469 }, /* KHIEUKH A RIEUL */
                             { 0xC4AF, 0xC471 }, /* KHIEUKH A MIEUM */
                             { 0xC4B0, 0xC473 }, /* KHIEUKH A PIEUP */
                             { 0xC4B1, 0xC475 }, /* KHIEUKH A SIOS */
                             { 0xC4B2, 0xC477 }, /* KHIEUKH A IEUNG */
                             { 0xC4B3, 0xC481 }, /* KHIEUKH AE */
                             { 0xC4B4, 0xC482 }, /* KHIEUKH AE KIYEOK */
                             { 0xC4B5, 0xC485 }, /* KHIEUKH AE NIEUN */
                             { 0xC4B6, 0xC489 }, /* KHIEUKH AE RIEUL */
                             { 0xC4B7, 0xC491 }, /* KHIEUKH AE MIEUM */
                             { 0xC4B8, 0xC493 }, /* KHIEUKH AE PIEUP */
                             { 0xC4B9, 0xC495 }, /* KHIEUKH AE SIOS */
                             { 0xC4BA, 0xC496 }, /* KHIEUKH AE SSANGSIOS */
                             { 0xC4BB, 0xC497 }, /* KHIEUKH AE IEUNG */
                             { 0xC4BC, 0xC4A1 }, /* KHIEUKH YA */
                             { 0xC4BD, 0xC4A2 }, /* KHIEUKH YA KIYEOK */
                             { 0xC4BE, 0xC4B7 }, /* KHIEUKH YA IEUNG */
                             { 0xC4BF, 0xC4E1 }, /* KHIEUKH EO */
                             { 0xC4C0, 0xC4E2 }, /* KHIEUKH EO KIYEOK */
                             { 0xC4C1, 0xC4E5 }, /* KHIEUKH EO NIEUN */
                             { 0xC4C2, 0xC4E8 }, /* KHIEUKH EO TIKEUT */
                             { 0xC4C3, 0xC4E9 }, /* KHIEUKH EO RIEUL */
                             { 0xC4C4, 0xC4F1 }, /* KHIEUKH EO MIEUM */
                             { 0xC4C5, 0xC4F3 }, /* KHIEUKH EO PIEUP */
                             { 0xC4C6, 0xC4F5 }, /* KHIEUKH EO SIOS */
                             { 0xC4C7, 0xC4F6 }, /* KHIEUKH EO SSANGSIOS */
                             { 0xC4C8, 0xC4F7 }, /* KHIEUKH EO IEUNG */
                             { 0xC4C9, 0xC541 }, /* KHIEUKH E */
                             { 0xC4CA, 0xC542 }, /* KHIEUKH E KIYEOK */
                             { 0xC4CB, 0xC545 }, /* KHIEUKH E NIEUN */
                             { 0xC4CC, 0xC549 }, /* KHIEUKH E RIEUL */
                             { 0xC4CD, 0xC551 }, /* KHIEUKH E MIEUM */
                             { 0xC4CE, 0xC553 }, /* KHIEUKH E PIEUP */
                             { 0xC4CF, 0xC555 }, /* KHIEUKH E SIOS */
                             { 0xC4D0, 0xC557 }, /* KHIEUKH E IEUNG */
                             { 0xC4D1, 0xC561 }, /* KHIEUKH YEO */
                             { 0xC4D2, 0xC565 }, /* KHIEUKH YEO NIEUN */
                             { 0xC4D3, 0xC569 }, /* KHIEUKH YEO RIEUL */
                             { 0xC4D4, 0xC571 }, /* KHIEUKH YEO MIEUM */
                             { 0xC4D5, 0xC573 }, /* KHIEUKH YEO PIEUP */
                             { 0xC4D6, 0xC575 }, /* KHIEUKH YEO SIOS */
                             { 0xC4D7, 0xC576 }, /* KHIEUKH YEO SSANGSIOS */
                             { 0xC4D8, 0xC577 }, /* KHIEUKH YEO IEUNG */
                             { 0xC4D9, 0xC581 }, /* KHIEUKH YE */
                             { 0xC4DA, 0xC5A1 }, /* KHIEUKH O */
                             { 0xC4DB, 0xC5A2 }, /* KHIEUKH O KIYEOK */
                             { 0xC4DC, 0xC5A5 }, /* KHIEUKH O NIEUN */
                             { 0xC4DD, 0xC5A9 }, /* KHIEUKH O RIEUL */
                             { 0xC4DE, 0xC5B1 }, /* KHIEUKH O MIEUM */
                             { 0xC4DF, 0xC5B3 }, /* KHIEUKH O PIEUP */
                             { 0xC4E0, 0xC5B5 }, /* KHIEUKH O SIOS */
                             { 0xC4E1, 0xC5B7 }, /* KHIEUKH O IEUNG */
                             { 0xC4E2, 0xC5C1 }, /* KHIEUKH WA */
                             { 0xC4E3, 0xC5C2 }, /* KHIEUKH WA KIYEOK */
                             { 0xC4E4, 0xC5C5 }, /* KHIEUKH WA NIEUN */
                             { 0xC4E5, 0xC5C9 }, /* KHIEUKH WA RIEUL */
                             { 0xC4E6, 0xC5D1 }, /* KHIEUKH WA MIEUM */
                             { 0xC4E7, 0xC5D7 }, /* KHIEUKH WA IEUNG */
                             { 0xC4E8, 0xC5E1 }, /* KHIEUKH WAE */
                             { 0xC4E9, 0xC5F7 }, /* KHIEUKH WAE IEUNG */
                             { 0xC4EA, 0xC641 }, /* KHIEUKH OE */
                             { 0xC4EB, 0xC649 }, /* KHIEUKH OE RIEUL */
                             { 0xC4EC, 0xC661 }, /* KHIEUKH YO */
                             { 0xC4ED, 0xC681 }, /* KHIEUKH U */
                             { 0xC4EE, 0xC682 }, /* KHIEUKH U KIYEOK */
                             { 0xC4EF, 0xC685 }, /* KHIEUKH U NIEUN */
                             { 0xC4F0, 0xC689 }, /* KHIEUKH U RIEUL */
                             { 0xC4F1, 0xC691 }, /* KHIEUKH U MIEUM */
                             { 0xC4F2, 0xC693 }, /* KHIEUKH U PIEUP */
                             { 0xC4F3, 0xC695 }, /* KHIEUKH U SIOS */
                             { 0xC4F4, 0xC697 }, /* KHIEUKH U IEUNG */
                             { 0xC4F5, 0xC6A1 }, /* KHIEUKH WEO */
                             { 0xC4F6, 0xC6A5 }, /* KHIEUKH WEO NIEUN */
                             { 0xC4F7, 0xC6A9 }, /* KHIEUKH WEO RIEUL */
                             { 0xC4F8, 0xC6B7 }, /* KHIEUKH WEO IEUNG */
                             { 0xC4F9, 0xC6C1 }, /* KHIEUKH WE */
                             { 0xC4FA, 0xC6D7 }, /* KHIEUKH WE IEUNG */
                             { 0xC4FB, 0xC6E1 }, /* KHIEUKH WI */
                             { 0xC4FC, 0xC6E2 }, /* KHIEUKH WI KIYEOK */
                             { 0xC4FD, 0xC6E5 }, /* KHIEUKH WI NIEUN */
                             { 0xC4FE, 0xC6E9 }, /* KHIEUKH WI RIEUL */
                             { 0xC5A1, 0xC6F1 }, /* KHIEUKH WI MIEUM */
                             { 0xC5A2, 0xC6F3 }, /* KHIEUKH WI PIEUP */
                             { 0xC5A3, 0xC6F5 }, /* KHIEUKH WI SIOS */
                             { 0xC5A4, 0xC6F7 }, /* KHIEUKH WI IEUNG */
                             { 0xC5A5, 0xC741 }, /* KHIEUKH YU */
                             { 0xC5A6, 0xC745 }, /* KHIEUKH YU NIEUN */
                             { 0xC5A7, 0xC749 }, /* KHIEUKH YU RIEUL */
                             { 0xC5A8, 0xC751 }, /* KHIEUKH YU MIEUM */
                             { 0xC5A9, 0xC761 }, /* KHIEUKH EU */
                             { 0xC5AA, 0xC762 }, /* KHIEUKH EU KIYEOK */
                             { 0xC5AB, 0xC765 }, /* KHIEUKH EU NIEUN */
                             { 0xC5AC, 0xC769 }, /* KHIEUKH EU RIEUL */
                             { 0xC5AD, 0xC771 }, /* KHIEUKH EU MIEUM */
                             { 0xC5AE, 0xC773 }, /* KHIEUKH EU PIEUP */
                             { 0xC5AF, 0xC777 }, /* KHIEUKH EU IEUNG */
                             { 0xC5B0, 0xC7A1 }, /* KHIEUKH I */
                             { 0xC5B1, 0xC7A2 }, /* KHIEUKH I KIYEOK */
                             { 0xC5B2, 0xC7A5 }, /* KHIEUKH I NIEUN */
                             { 0xC5B3, 0xC7A9 }, /* KHIEUKH I RIEUL */
                             { 0xC5B4, 0xC7B1 }, /* KHIEUKH I MIEUM */
                             { 0xC5B5, 0xC7B3 }, /* KHIEUKH I PIEUP */
                             { 0xC5B6, 0xC7B5 }, /* KHIEUKH I SIOS */
                             { 0xC5B7, 0xC7B7 }, /* KHIEUKH I IEUNG */
                             { 0xC5B8, 0xC861 }, /* THIEUTH A */
                             { 0xC5B9, 0xC862 }, /* THIEUTH A KIYEOK */
                             { 0xC5BA, 0xC865 }, /* THIEUTH A NIEUN */
                             { 0xC5BB, 0xC869 }, /* THIEUTH A RIEUL */
                             { 0xC5BC, 0xC86A }, /* THIEUTH A RIEULKIYEOK */
                             { 0xC5BD, 0xC871 }, /* THIEUTH A MIEUM */
                             { 0xC5BE, 0xC873 }, /* THIEUTH A PIEUP */
                             { 0xC5BF, 0xC875 }, /* THIEUTH A SIOS */
                             { 0xC5C0, 0xC876 }, /* THIEUTH A SSANGSIOS */
                             { 0xC5C1, 0xC877 }, /* THIEUTH A IEUNG */
                             { 0xC5C2, 0xC881 }, /* THIEUTH AE */
                             { 0xC5C3, 0xC882 }, /* THIEUTH AE KIYEOK */
                             { 0xC5C4, 0xC885 }, /* THIEUTH AE NIEUN */
                             { 0xC5C5, 0xC889 }, /* THIEUTH AE RIEUL */
                             { 0xC5C6, 0xC891 }, /* THIEUTH AE MIEUM */
                             { 0xC5C7, 0xC893 }, /* THIEUTH AE PIEUP */
                             { 0xC5C8, 0xC895 }, /* THIEUTH AE SIOS */
                             { 0xC5C9, 0xC896 }, /* THIEUTH AE SSANGSIOS */
                             { 0xC5CA, 0xC897 }, /* THIEUTH AE IEUNG */
                             { 0xC5CB, 0xC8A1 }, /* THIEUTH YA */
                             { 0xC5CC, 0xC8B7 }, /* THIEUTH YA IEUNG */
                             { 0xC5CD, 0xC8E1 }, /* THIEUTH EO */
                             { 0xC5CE, 0xC8E2 }, /* THIEUTH EO KIYEOK */
                             { 0xC5CF, 0xC8E5 }, /* THIEUTH EO NIEUN */
                             { 0xC5D0, 0xC8E9 }, /* THIEUTH EO RIEUL */
                             { 0xC5D1, 0xC8EB }, /* THIEUTH EO RIEULMIEUM */
                             { 0xC5D2, 0xC8F1 }, /* THIEUTH EO MIEUM */
                             { 0xC5D3, 0xC8F3 }, /* THIEUTH EO PIEUP */
                             { 0xC5D4, 0xC8F5 }, /* THIEUTH EO SIOS */
                             { 0xC5D5, 0xC8F6 }, /* THIEUTH EO SSANGSIOS */
                             { 0xC5D6, 0xC8F7 }, /* THIEUTH EO IEUNG */
                             { 0xC5D7, 0xC941 }, /* THIEUTH E */
                             { 0xC5D8, 0xC942 }, /* THIEUTH E KIYEOK */
                             { 0xC5D9, 0xC945 }, /* THIEUTH E NIEUN */
                             { 0xC5DA, 0xC949 }, /* THIEUTH E RIEUL */
                             { 0xC5DB, 0xC951 }, /* THIEUTH E MIEUM */
                             { 0xC5DC, 0xC953 }, /* THIEUTH E PIEUP */
                             { 0xC5DD, 0xC955 }, /* THIEUTH E SIOS */
                             { 0xC5DE, 0xC957 }, /* THIEUTH E IEUNG */
                             { 0xC5DF, 0xC961 }, /* THIEUTH YEO */
                             { 0xC5E0, 0xC965 }, /* THIEUTH YEO NIEUN */
                             { 0xC5E1, 0xC976 }, /* THIEUTH YEO SSANGSIOS */
                             { 0xC5E2, 0xC981 }, /* THIEUTH YE */
                             { 0xC5E3, 0xC985 }, /* THIEUTH YE NIEUN */
                             { 0xC5E4, 0xC9A1 }, /* THIEUTH O */
                             { 0xC5E5, 0xC9A2 }, /* THIEUTH O KIYEOK */
                             { 0xC5E6, 0xC9A5 }, /* THIEUTH O NIEUN */
                             { 0xC5E7, 0xC9A9 }, /* THIEUTH O RIEUL */
                             { 0xC5E8, 0xC9B1 }, /* THIEUTH O MIEUM */
                             { 0xC5E9, 0xC9B3 }, /* THIEUTH O PIEUP */
                             { 0xC5EA, 0xC9B5 }, /* THIEUTH O SIOS */
                             { 0xC5EB, 0xC9B7 }, /* THIEUTH O IEUNG */
                             { 0xC5EC, 0xC9BC }, /* THIEUTH O PHIEUPH */
                             { 0xC5ED, 0xC9C1 }, /* THIEUTH WA */
                             { 0xC5EE, 0xC9C5 }, /* THIEUTH WA NIEUN */
                             { 0xC5EF, 0xC9E1 }, /* THIEUTH WAE */
                             { 0xC5F0, 0xCA41 }, /* THIEUTH OE */
                             { 0xC5F1, 0xCA45 }, /* THIEUTH OE NIEUN */
                             { 0xC5F2, 0xCA55 }, /* THIEUTH OE SIOS */
                             { 0xC5F3, 0xCA57 }, /* THIEUTH OE IEUNG */
                             { 0xC5F4, 0xCA61 }, /* THIEUTH YO */
                             { 0xC5F5, 0xCA81 }, /* THIEUTH U */
                             { 0xC5F6, 0xCA82 }, /* THIEUTH U KIYEOK */
                             { 0xC5F7, 0xCA85 }, /* THIEUTH U NIEUN */
                             { 0xC5F8, 0xCA89 }, /* THIEUTH U RIEUL */
                             { 0xC5F9, 0xCA91 }, /* THIEUTH U MIEUM */
                             { 0xC5FA, 0xCA93 }, /* THIEUTH U PIEUP */
                             { 0xC5FB, 0xCA95 }, /* THIEUTH U SIOS */
                             { 0xC5FC, 0xCA97 }, /* THIEUTH U IEUNG */
                             { 0xC5FD, 0xCAA1 }, /* THIEUTH WEO */
                             { 0xC5FE, 0xCAB6 }, /* THIEUTH WEO SSANGSIOS */
                             { 0xC6A1, 0xCAC1 }, /* THIEUTH WE */
                             { 0xC6A2, 0xCAE1 }, /* THIEUTH WI */
                             { 0xC6A3, 0xCAE2 }, /* THIEUTH WI KIYEOK */
                             { 0xC6A4, 0xCAE5 }, /* THIEUTH WI NIEUN */
                             { 0xC6A5, 0xCAE9 }, /* THIEUTH WI RIEUL */
                             { 0xC6A6, 0xCAF1 }, /* THIEUTH WI MIEUM */
                             { 0xC6A7, 0xCAF3 }, /* THIEUTH WI PIEUP */
                             { 0xC6A8, 0xCAF7 }, /* THIEUTH WI IEUNG */
                             { 0xC6A9, 0xCB41 }, /* THIEUTH YU */
                             { 0xC6AA, 0xCB45 }, /* THIEUTH YU NIEUN */
                             { 0xC6AB, 0xCB49 }, /* THIEUTH YU RIEUL */
                             { 0xC6AC, 0xCB51 }, /* THIEUTH YU MIEUM */
                             { 0xC6AD, 0xCB57 }, /* THIEUTH YU IEUNG */
                             { 0xC6AE, 0xCB61 }, /* THIEUTH EU */
                             { 0xC6AF, 0xCB62 }, /* THIEUTH EU KIYEOK */
                             { 0xC6B0, 0xCB65 }, /* THIEUTH EU NIEUN */
                             { 0xC6B1, 0xCB68 }, /* THIEUTH EU TIKEUT */
                             { 0xC6B2, 0xCB69 }, /* THIEUTH EU RIEUL */
                             { 0xC6B3, 0xCB6B }, /* THIEUTH EU RIEULMIEUM */
                             { 0xC6B4, 0xCB71 }, /* THIEUTH EU MIEUM */
                             { 0xC6B5, 0xCB73 }, /* THIEUTH EU PIEUP */
                             { 0xC6B6, 0xCB75 }, /* THIEUTH EU SIOS */
                             { 0xC6B7, 0xCB81 }, /* THIEUTH YI */
                             { 0xC6B8, 0xCB85 }, /* THIEUTH YI NIEUN */
                             { 0xC6B9, 0xCB89 }, /* THIEUTH YI RIEUL */
                             { 0xC6BA, 0xCB91 }, /* THIEUTH YI MIEUM */
                             { 0xC6BB, 0xCB93 }, /* THIEUTH YI PIEUP */
                             { 0xC6BC, 0xCBA1 }, /* THIEUTH I */
                             { 0xC6BD, 0xCBA2 }, /* THIEUTH I KIYEOK */
                             { 0xC6BE, 0xCBA5 }, /* THIEUTH I NIEUN */
                             { 0xC6BF, 0xCBA9 }, /* THIEUTH I RIEUL */
                             { 0xC6C0, 0xCBB1 }, /* THIEUTH I MIEUM */
                             { 0xC6C1, 0xCBB3 }, /* THIEUTH I PIEUP */
                             { 0xC6C2, 0xCBB5 }, /* THIEUTH I SIOS */
                             { 0xC6C3, 0xCBB7 }, /* THIEUTH I IEUNG */
                             { 0xC6C4, 0xCC61 }, /* PHIEUPH A */
                             { 0xC6C5, 0xCC62 }, /* PHIEUPH A KIYEOK */
                             { 0xC6C6, 0xCC63 }, /* PHIEUPH A SSANGKIYEOK */
                             { 0xC6C7, 0xCC65 }, /* PHIEUPH A NIEUN */
                             { 0xC6C8, 0xCC69 }, /* PHIEUPH A RIEUL */
                             { 0xC6C9, 0xCC6B }, /* PHIEUPH A RIEULMIEUM */
                             { 0xC6CA, 0xCC71 }, /* PHIEUPH A MIEUM */
                             { 0xC6CB, 0xCC73 }, /* PHIEUPH A PIEUP */
                             { 0xC6CC, 0xCC75 }, /* PHIEUPH A SIOS */
                             { 0xC6CD, 0xCC76 }, /* PHIEUPH A SSANGSIOS */
                             { 0xC6CE, 0xCC77 }, /* PHIEUPH A IEUNG */
                             { 0xC6CF, 0xCC7B }, /* PHIEUPH A THIEUTH */
                             { 0xC6D0, 0xCC81 }, /* PHIEUPH AE */
                             { 0xC6D1, 0xCC82 }, /* PHIEUPH AE KIYEOK */
                             { 0xC6D2, 0xCC85 }, /* PHIEUPH AE NIEUN */
                             { 0xC6D3, 0xCC89 }, /* PHIEUPH AE RIEUL */
                             { 0xC6D4, 0xCC91 }, /* PHIEUPH AE MIEUM */
                             { 0xC6D5, 0xCC93 }, /* PHIEUPH AE PIEUP */
                             { 0xC6D6, 0xCC95 }, /* PHIEUPH AE SIOS */
                             { 0xC6D7, 0xCC96 }, /* PHIEUPH AE SSANGSIOS */
                             { 0xC6D8, 0xCC97 }, /* PHIEUPH AE IEUNG */
                             { 0xC6D9, 0xCCA1 }, /* PHIEUPH YA */
                             { 0xC6DA, 0xCCA2 }, /* PHIEUPH YA KIYEOK */
                             { 0xC6DB, 0xCCE1 }, /* PHIEUPH EO */
                             { 0xC6DC, 0xCCE2 }, /* PHIEUPH EO KIYEOK */
                             { 0xC6DD, 0xCCE5 }, /* PHIEUPH EO NIEUN */
                             { 0xC6DE, 0xCCE9 }, /* PHIEUPH EO RIEUL */
                             { 0xC6DF, 0xCCF1 }, /* PHIEUPH EO MIEUM */
                             { 0xC6E0, 0xCCF3 }, /* PHIEUPH EO PIEUP */
                             { 0xC6E1, 0xCCF5 }, /* PHIEUPH EO SIOS */
                             { 0xC6E2, 0xCCF6 }, /* PHIEUPH EO SSANGSIOS */
                             { 0xC6E3, 0xCCF7 }, /* PHIEUPH EO IEUNG */
                             { 0xC6E4, 0xCD41 }, /* PHIEUPH E */
                             { 0xC6E5, 0xCD42 }, /* PHIEUPH E KIYEOK */
                             { 0xC6E6, 0xCD45 }, /* PHIEUPH E NIEUN */
                             { 0xC6E7, 0xCD49 }, /* PHIEUPH E RIEUL */
                             { 0xC6E8, 0xCD51 }, /* PHIEUPH E MIEUM */
                             { 0xC6E9, 0xCD53 }, /* PHIEUPH E PIEUP */
                             { 0xC6EA, 0xCD55 }, /* PHIEUPH E SIOS */
                             { 0xC6EB, 0xCD57 }, /* PHIEUPH E IEUNG */
                             { 0xC6EC, 0xCD61 }, /* PHIEUPH YEO */
                             { 0xC6ED, 0xCD65 }, /* PHIEUPH YEO NIEUN */
                             { 0xC6EE, 0xCD69 }, /* PHIEUPH YEO RIEUL */
                             { 0xC6EF, 0xCD71 }, /* PHIEUPH YEO MIEUM */
                             { 0xC6F0, 0xCD73 }, /* PHIEUPH YEO PIEUP */
                             { 0xC6F1, 0xCD76 }, /* PHIEUPH YEO SSANGSIOS */
                             { 0xC6F2, 0xCD77 }, /* PHIEUPH YEO IEUNG */
                             { 0xC6F3, 0xCD81 }, /* PHIEUPH YE */
                             { 0xC6F4, 0xCD89 }, /* PHIEUPH YE RIEUL */
                             { 0xC6F5, 0xCD93 }, /* PHIEUPH YE PIEUP */
                             { 0xC6F6, 0xCD95 }, /* PHIEUPH YE SIOS */
                             { 0xC6F7, 0xCDA1 }, /* PHIEUPH O */
                             { 0xC6F8, 0xCDA2 }, /* PHIEUPH O KIYEOK */
                             { 0xC6F9, 0xCDA5 }, /* PHIEUPH O NIEUN */
                             { 0xC6FA, 0xCDA9 }, /* PHIEUPH O RIEUL */
                             { 0xC6FB, 0xCDB1 }, /* PHIEUPH O MIEUM */
                             { 0xC6FC, 0xCDB3 }, /* PHIEUPH O PIEUP */
                             { 0xC6FD, 0xCDB5 }, /* PHIEUPH O SIOS */
                             { 0xC6FE, 0xCDB7 }, /* PHIEUPH O IEUNG */
                             { 0xC7A1, 0xCDC1 }, /* PHIEUPH WA */
                             { 0xC7A2, 0xCDD7 }, /* PHIEUPH WA IEUNG */
                             { 0xC7A3, 0xCE41 }, /* PHIEUPH OE */
                             { 0xC7A4, 0xCE45 }, /* PHIEUPH OE NIEUN */
                             { 0xC7A5, 0xCE61 }, /* PHIEUPH YO */
                             { 0xC7A6, 0xCE65 }, /* PHIEUPH YO NIEUN */
                             { 0xC7A7, 0xCE69 }, /* PHIEUPH YO RIEUL */
                             { 0xC7A8, 0xCE73 }, /* PHIEUPH YO PIEUP */
                             { 0xC7A9, 0xCE75 }, /* PHIEUPH YO SIOS */
                             { 0xC7AA, 0xCE81 }, /* PHIEUPH U */
                             { 0xC7AB, 0xCE82 }, /* PHIEUPH U KIYEOK */
                             { 0xC7AC, 0xCE85 }, /* PHIEUPH U NIEUN */
                             { 0xC7AD, 0xCE88 }, /* PHIEUPH U TIKEUT */
                             { 0xC7AE, 0xCE89 }, /* PHIEUPH U RIEUL */
                             { 0xC7AF, 0xCE8B }, /* PHIEUPH U RIEULMIEUM */
                             { 0xC7B0, 0xCE91 }, /* PHIEUPH U MIEUM */
                             { 0xC7B1, 0xCE93 }, /* PHIEUPH U PIEUP */
                             { 0xC7B2, 0xCE95 }, /* PHIEUPH U SIOS */
                             { 0xC7B3, 0xCE97 }, /* PHIEUPH U IEUNG */
                             { 0xC7B4, 0xCEA1 }, /* PHIEUPH WEO */
                             { 0xC7B5, 0xCEB7 }, /* PHIEUPH WEO IEUNG */
                             { 0xC7B6, 0xCEE1 }, /* PHIEUPH WI */
                             { 0xC7B7, 0xCEE5 }, /* PHIEUPH WI NIEUN */
                             { 0xC7B8, 0xCEE9 }, /* PHIEUPH WI RIEUL */
                             { 0xC7B9, 0xCEF1 }, /* PHIEUPH WI MIEUM */
                             { 0xC7BA, 0xCEF5 }, /* PHIEUPH WI SIOS */
                             { 0xC7BB, 0xCF41 }, /* PHIEUPH YU */
                             { 0xC7BC, 0xCF45 }, /* PHIEUPH YU NIEUN */
                             { 0xC7BD, 0xCF49 }, /* PHIEUPH YU RIEUL */
                             { 0xC7BE, 0xCF51 }, /* PHIEUPH YU MIEUM */
                             { 0xC7BF, 0xCF55 }, /* PHIEUPH YU SIOS */
                             { 0xC7C0, 0xCF57 }, /* PHIEUPH YU IEUNG */
                             { 0xC7C1, 0xCF61 }, /* PHIEUPH EU */
                             { 0xC7C2, 0xCF65 }, /* PHIEUPH EU NIEUN */
                             { 0xC7C3, 0xCF69 }, /* PHIEUPH EU RIEUL */
                             { 0xC7C4, 0xCF71 }, /* PHIEUPH EU MIEUM */
                             { 0xC7C5, 0xCF73 }, /* PHIEUPH EU PIEUP */
                             { 0xC7C6, 0xCF75 }, /* PHIEUPH EU SIOS */
                             { 0xC7C7, 0xCFA1 }, /* PHIEUPH I */
                             { 0xC7C8, 0xCFA2 }, /* PHIEUPH I KIYEOK */
                             { 0xC7C9, 0xCFA5 }, /* PHIEUPH I NIEUN */
                             { 0xC7CA, 0xCFA9 }, /* PHIEUPH I RIEUL */
                             { 0xC7CB, 0xCFB1 }, /* PHIEUPH I MIEUM */
                             { 0xC7CC, 0xCFB3 }, /* PHIEUPH I PIEUP */
                             { 0xC7CD, 0xCFB5 }, /* PHIEUPH I SIOS */
                             { 0xC7CE, 0xCFB7 }, /* PHIEUPH I IEUNG */
                             { 0xC7CF, 0xD061 }, /* HIEUH A */
                             { 0xC7D0, 0xD062 }, /* HIEUH A KIYEOK */
                             { 0xC7D1, 0xD065 }, /* HIEUH A NIEUN */
                             { 0xC7D2, 0xD069 }, /* HIEUH A RIEUL */
                             { 0xC7D3, 0xD06E }, /* HIEUH A RIEULTHIEUTH */
                             { 0xC7D4, 0xD071 }, /* HIEUH A MIEUM */
                             { 0xC7D5, 0xD073 }, /* HIEUH A PIEUP */
                             { 0xC7D6, 0xD075 }, /* HIEUH A SIOS */
                             { 0xC7D7, 0xD077 }, /* HIEUH A IEUNG */
                             { 0xC7D8, 0xD081 }, /* HIEUH AE */
                             { 0xC7D9, 0xD082 }, /* HIEUH AE KIYEOK */
                             { 0xC7DA, 0xD085 }, /* HIEUH AE NIEUN */
                             { 0xC7DB, 0xD089 }, /* HIEUH AE RIEUL */
                             { 0xC7DC, 0xD091 }, /* HIEUH AE MIEUM */
                             { 0xC7DD, 0xD093 }, /* HIEUH AE PIEUP */
                             { 0xC7DE, 0xD095 }, /* HIEUH AE SIOS */
                             { 0xC7DF, 0xD096 }, /* HIEUH AE SSANGSIOS */
                             { 0xC7E0, 0xD097 }, /* HIEUH AE IEUNG */
                             { 0xC7E1, 0xD0A1 }, /* HIEUH YA */
                             { 0xC7E2, 0xD0B7 }, /* HIEUH YA IEUNG */
                             { 0xC7E3, 0xD0E1 }, /* HIEUH EO */
                             { 0xC7E4, 0xD0E2 }, /* HIEUH EO KIYEOK */
                             { 0xC7E5, 0xD0E5 }, /* HIEUH EO NIEUN */
                             { 0xC7E6, 0xD0E9 }, /* HIEUH EO RIEUL */
                             { 0xC7E7, 0xD0EB }, /* HIEUH EO RIEULMIEUM */
                             { 0xC7E8, 0xD0F1 }, /* HIEUH EO MIEUM */
                             { 0xC7E9, 0xD0F3 }, /* HIEUH EO PIEUP */
                             { 0xC7EA, 0xD0F5 }, /* HIEUH EO SIOS */
                             { 0xC7EB, 0xD0F7 }, /* HIEUH EO IEUNG */
                             { 0xC7EC, 0xD141 }, /* HIEUH E */
                             { 0xC7ED, 0xD142 }, /* HIEUH E KIYEOK */
                             { 0xC7EE, 0xD145 }, /* HIEUH E NIEUN */
                             { 0xC7EF, 0xD149 }, /* HIEUH E RIEUL */
                             { 0xC7F0, 0xD151 }, /* HIEUH E MIEUM */
                             { 0xC7F1, 0xD153 }, /* HIEUH E PIEUP */
                             { 0xC7F2, 0xD155 }, /* HIEUH E SIOS */
                             { 0xC7F3, 0xD157 }, /* HIEUH E IEUNG */
                             { 0xC7F4, 0xD161 }, /* HIEUH YEO */
                             { 0xC7F5, 0xD162 }, /* HIEUH YEO KIYEOK */
                             { 0xC7F6, 0xD165 }, /* HIEUH YEO NIEUN */
                             { 0xC7F7, 0xD169 }, /* HIEUH YEO RIEUL */
                             { 0xC7F8, 0xD171 }, /* HIEUH YEO MIEUM */
                             { 0xC7F9, 0xD173 }, /* HIEUH YEO PIEUP */
                             { 0xC7FA, 0xD175 }, /* HIEUH YEO SIOS */
                             { 0xC7FB, 0xD176 }, /* HIEUH YEO SSANGSIOS */
                             { 0xC7FC, 0xD177 }, /* HIEUH YEO IEUNG */
                             { 0xC7FD, 0xD181 }, /* HIEUH YE */
                             { 0xC7FE, 0xD185 }, /* HIEUH YE NIEUN */
                             { 0xC8A1, 0xD189 }, /* HIEUH YE RIEUL */
                             { 0xC8A2, 0xD193 }, /* HIEUH YE PIEUP */
                             { 0xC8A3, 0xD1A1 }, /* HIEUH O */
                             { 0xC8A4, 0xD1A2 }, /* HIEUH O KIYEOK */
                             { 0xC8A5, 0xD1A5 }, /* HIEUH O NIEUN */
                             { 0xC8A6, 0xD1A9 }, /* HIEUH O RIEUL */
                             { 0xC8A7, 0xD1AE }, /* HIEUH O RIEULTHIEUTH */
                             { 0xC8A8, 0xD1B1 }, /* HIEUH O MIEUM */
                             { 0xC8A9, 0xD1B3 }, /* HIEUH O PIEUP */
                             { 0xC8AA, 0xD1B5 }, /* HIEUH O SIOS */
                             { 0xC8AB, 0xD1B7 }, /* HIEUH O IEUNG */
                             { 0xC8AC, 0xD1BB }, /* HIEUH O THIEUTH */
                             { 0xC8AD, 0xD1C1 }, /* HIEUH WA */
                             { 0xC8AE, 0xD1C2 }, /* HIEUH WA KIYEOK */
                             { 0xC8AF, 0xD1C5 }, /* HIEUH WA NIEUN */
                             { 0xC8B0, 0xD1C9 }, /* HIEUH WA RIEUL */
                             { 0xC8B1, 0xD1D5 }, /* HIEUH WA SIOS */
                             { 0xC8B2, 0xD1D7 }, /* HIEUH WA IEUNG */
                             { 0xC8B3, 0xD1E1 }, /* HIEUH WAE */
                             { 0xC8B4, 0xD1E2 }, /* HIEUH WAE KIYEOK */
                             { 0xC8B5, 0xD1E5 }, /* HIEUH WAE NIEUN */
                             { 0xC8B6, 0xD1F5 }, /* HIEUH WAE SIOS */
                             { 0xC8B7, 0xD1F7 }, /* HIEUH WAE IEUNG */
                             { 0xC8B8, 0xD241 }, /* HIEUH OE */
                             { 0xC8B9, 0xD242 }, /* HIEUH OE KIYEOK */
                             { 0xC8BA, 0xD245 }, /* HIEUH OE NIEUN */
                             { 0xC8BB, 0xD249 }, /* HIEUH OE RIEUL */
                             { 0xC8BC, 0xD253 }, /* HIEUH OE PIEUP */
                             { 0xC8BD, 0xD255 }, /* HIEUH OE SIOS */
                             { 0xC8BE, 0xD257 }, /* HIEUH OE IEUNG */
                             { 0xC8BF, 0xD261 }, /* HIEUH YO */
                             { 0xC8C0, 0xD265 }, /* HIEUH YO NIEUN */
                             { 0xC8C1, 0xD269 }, /* HIEUH YO RIEUL */
                             { 0xC8C2, 0xD273 }, /* HIEUH YO PIEUP */
                             { 0xC8C3, 0xD275 }, /* HIEUH YO SIOS */
                             { 0xC8C4, 0xD281 }, /* HIEUH U */
                             { 0xC8C5, 0xD282 }, /* HIEUH U KIYEOK */
                             { 0xC8C6, 0xD285 }, /* HIEUH U NIEUN */
                             { 0xC8C7, 0xD289 }, /* HIEUH U RIEUL */
                             { 0xC8C8, 0xD28E }, /* HIEUH U RIEULTHIEUTH */
                             { 0xC8C9, 0xD291 }, /* HIEUH U MIEUM */
                             { 0xC8CA, 0xD295 }, /* HIEUH U SIOS */
                             { 0xC8CB, 0xD297 }, /* HIEUH U IEUNG */
                             { 0xC8CC, 0xD2A1 }, /* HIEUH WEO */
                             { 0xC8CD, 0xD2A5 }, /* HIEUH WEO NIEUN */
                             { 0xC8CE, 0xD2A9 }, /* HIEUH WEO RIEUL */
                             { 0xC8CF, 0xD2B1 }, /* HIEUH WEO MIEUM */
                             { 0xC8D0, 0xD2B7 }, /* HIEUH WEO IEUNG */
                             { 0xC8D1, 0xD2C1 }, /* HIEUH WE */
                             { 0xC8D2, 0xD2C2 }, /* HIEUH WE KIYEOK */
                             { 0xC8D3, 0xD2C5 }, /* HIEUH WE NIEUN */
                             { 0xC8D4, 0xD2C9 }, /* HIEUH WE RIEUL */
                             { 0xC8D5, 0xD2D7 }, /* HIEUH WE IEUNG */
                             { 0xC8D6, 0xD2E1 }, /* HIEUH WI */
                             { 0xC8D7, 0xD2E2 }, /* HIEUH WI KIYEOK */
                             { 0xC8D8, 0xD2E5 }, /* HIEUH WI NIEUN */
                             { 0xC8D9, 0xD2E9 }, /* HIEUH WI RIEUL */
                             { 0xC8DA, 0xD2F1 }, /* HIEUH WI MIEUM */
                             { 0xC8DB, 0xD2F3 }, /* HIEUH WI PIEUP */
                             { 0xC8DC, 0xD2F5 }, /* HIEUH WI SIOS */
                             { 0xC8DD, 0xD2F7 }, /* HIEUH WI IEUNG */
                             { 0xC8DE, 0xD341 }, /* HIEUH YU */
                             { 0xC8DF, 0xD342 }, /* HIEUH YU KIYEOK */
                             { 0xC8E0, 0xD345 }, /* HIEUH YU NIEUN */
                             { 0xC8E1, 0xD349 }, /* HIEUH YU RIEUL */
                             { 0xC8E2, 0xD351 }, /* HIEUH YU MIEUM */
                             { 0xC8E3, 0xD355 }, /* HIEUH YU SIOS */
                             { 0xC8E4, 0xD357 }, /* HIEUH YU IEUNG */
                             { 0xC8E5, 0xD361 }, /* HIEUH EU */
                             { 0xC8E6, 0xD362 }, /* HIEUH EU KIYEOK */
                             { 0xC8E7, 0xD365 }, /* HIEUH EU NIEUN */
                             { 0xC8E8, 0xD367 }, /* HIEUH EU NIEUNHIEUH */
                             { 0xC8E9, 0xD368 }, /* HIEUH EU TIKEUT */
                             { 0xC8EA, 0xD369 }, /* HIEUH EU RIEUL */
                             { 0xC8EB, 0xD36A }, /* HIEUH EU RIEULKIYEOK */
                             { 0xC8EC, 0xD371 }, /* HIEUH EU MIEUM */
                             { 0xC8ED, 0xD373 }, /* HIEUH EU PIEUP */
                             { 0xC8EE, 0xD375 }, /* HIEUH EU SIOS */
                             { 0xC8EF, 0xD377 }, /* HIEUH EU IEUNG */
                             { 0xC8F0, 0xD37B }, /* HIEUH EU THIEUTH */
                             { 0xC8F1, 0xD381 }, /* HIEUH YI */
                             { 0xC8F2, 0xD385 }, /* HIEUH YI NIEUN */
                             { 0xC8F3, 0xD389 }, /* HIEUH YI RIEUL */
                             { 0xC8F4, 0xD391 }, /* HIEUH YI MIEUM */
                             { 0xC8F5, 0xD393 }, /* HIEUH YI PIEUP */
                             { 0xC8F6, 0xD397 }, /* HIEUH YI IEUNG */
                             { 0xC8F7, 0xD3A1 }, /* HIEUH I */
                             { 0xC8F8, 0xD3A2 }, /* HIEUH I KIYEOK */
                             { 0xC8F9, 0xD3A5 }, /* HIEUH I NIEUN */
                             { 0xC8FA, 0xD3A9 }, /* HIEUH I RIEUL */
                             { 0xC8FB, 0xD3B1 }, /* HIEUH I MIEUM */
                             { 0xC8FC, 0xD3B3 }, /* HIEUH I PIEUP */
                             { 0xC8FD, 0xD3B5 }, /* HIEUH I SIOS */
                             { 0xC8FE, 0xD3B7 }, /* HIEUH I IEUNG */
};

/* 종성이 있는 글자에서 종성을 뺀 글자가 있는 헤더 인덱스를 가리킴...
   (예) 각 ----> NoJongIdx[h_idx - WANSUNG_JASO_NUM] = 51 ---> 가 */
UWORD NoJongIdx[] = {
                     0,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     51,
                     0,
                     69,
                     69,
                     69,
                     69,
                     69,
                     69,
                     69,
                     69,
                     0,
                     78,
                     78,
                     78,
                     78,
                     78,
                     0,
                     84,
                     84,
                     0,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     87,
                     0,
                     102,
                     102,
                     102,
                     102,
                     102,
                     102,
                     102,
                     0,
                     110,
                     110,
                     110,
                     110,
                     110,
                     110,
                     110,
                     110,
                     110,
                     110,
                     110,
                     0,
                     122,
                     122,
                     122,
                     122,
                     0,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     127,
                     0,
                     140,
                     140,
                     140,
                     140,
                     140,
                     140,
                     140,
                     140,
                     0,
                     149,
                     149,
                     149,
                     149,
                     149,
                     0,
                     155,
                     155,
                     155,
                     155,
                     155,
                     155,
                     155,
                     0,
                     163,
                     163,
                     163,
                     163,
                     0,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     168,
                     0,
                     181,
                     181,
                     181,
                     181,
                     181,
                     0,
                     187,
                     0,
                     189,
                     189,
                     189,
                     189,
                     189,
                     189,
                     0,
                     196,
                     196,
                     0,
                     199,
                     199,
                     199,
                     199,
                     199,
                     199,
                     199,
                     199,
                     199,
                     0,
                     0,
                     210,
                     210,
                     210,
                     210,
                     210,
                     210,
                     210,
                     210,
                     210,
                     210,
                     210,
                     0,
                     222,
                     222,
                     222,
                     222,
                     222,
                     222,
                     222,
                     222,
                     222,
                     222,
                     222,
                     0,
                     234,
                     234,
                     234,
                     234,
                     234,
                     234,
                     234,
                     234,
                     0,
                     243,
                     243,
                     0,
                     246,
                     246,
                     246,
                     246,
                     246,
                     246,
                     246,
                     246,
                     246,
                     0,
                     256,
                     256,
                     256,
                     256,
                     256,
                     0,
                     262,
                     262,
                     262,
                     262,
                     262,
                     0,
                     0,
                     269,
                     269,
                     269,
                     269,
                     269,
                     269,
                     269,
                     269,
                     269,
                     269,
                     0,
                     280,
                     280,
                     280,
                     280,
                     0,
                     285,
                     285,
                     0,
                     288,
                     288,
                     288,
                     288,
                     288,
                     0,
                     0,
                     295,
                     295,
                     295,
                     295,
                     295,
                     295,
                     295,
                     295,
                     295,
                     0,
                     305,
                     305,
                     305,
                     0,
                     309,
                     309,
                     309,
                     309,
                     309,
                     309,
                     0,
                     316,
                     316,
                     316,
                     316,
                     0,
                     0,
                     322,
                     322,
                     322,
                     322,
                     322,
                     322,
                     322,
                     322,
                     322,
                     322,
                     322,
                     0,
                     334,
                     334,
                     334,
                     334,
                     334,
                     334,
                     334,
                     0,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     342,
                     0,
                     359,
                     359,
                     359,
                     359,
                     359,
                     359,
                     359,
                     359,
                     0,
                     368,
                     368,
                     368,
                     368,
                     368,
                     0,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     374,
                     0,
                     387,
                     387,
                     387,
                     387,
                     387,
                     387,
                     387,
                     387,
                     0,
                     396,
                     396,
                     396,
                     396,
                     396,
                     396,
                     396,
                     396,
                     0,
                     405,
                     0,
                     407,
                     407,
                     407,
                     407,
                     407,
                     407,
                     407,
                     407,
                     407,
                     407,
                     0,
                     418,
                     418,
                     418,
                     0,
                     422,
                     422,
                     422,
                     422,
                     422,
                     0,
                     428,
                     428,
                     428,
                     428,
                     428,
                     428,
                     0,
                     435,
                     435,
                     435,
                     435,
                     435,
                     435,
                     435,
                     435,
                     0,
                     444,
                     0,
                     0,
                     447,
                     447,
                     447,
                     447,
                     0,
                     452,
                     452,
                     452,
                     452,
                     452,
                     0,
                     458,
                     458,
                     458,
                     458,
                     458,
                     458,
                     458,
                     458,
                     458,
                     458,
                     458,
                     0,
                     470,
                     470,
                     0,
                     473,
                     473,
                     473,
                     473,
                     473,
                     473,
                     473,
                     473,
                     473,
                     0,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     483,
                     0,
                     501,
                     501,
                     501,
                     501,
                     501,
                     501,
                     501,
                     501,
                     0,
                     0,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     511,
                     0,
                     525,
                     525,
                     525,
                     525,
                     525,
                     525,
                     525,
                     525,
                     0,
                     534,
                     534,
                     534,
                     534,
                     0,
                     539,
                     0,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     541,
                     0,
                     554,
                     554,
                     0,
                     557,
                     0,
                     559,
                     559,
                     559,
                     559,
                     559,
                     0,
                     0,
                     566,
                     566,
                     566,
                     566,
                     566,
                     566,
                     566,
                     0,
                     574,
                     0,
                     576,
                     0,
                     578,
                     578,
                     578,
                     578,
                     578,
                     0,
                     584,
                     584,
                     584,
                     584,
                     0,
                     589,
                     589,
                     589,
                     589,
                     589,
                     589,
                     589,
                     589,
                     589,
                     0,
                     0,
                     600,
                     600,
                     600,
                     600,
                     600,
                     600,
                     600,
                     600,
                     600,
                     600,
                     0,
                     611,
                     611,
                     611,
                     611,
                     611,
                     611,
                     611,
                     611,
                     611,
                     0,
                     621,
                     621,
                     621,
                     621,
                     621,
                     621,
                     621,
                     621,
                     0,
                     630,
                     630,
                     630,
                     630,
                     630,
                     630,
                     630,
                     630,
                     630,
                     630,
                     630,
                     0,
                     642,
                     642,
                     642,
                     642,
                     642,
                     642,
                     642,
                     642,
                     0,
                     651,
                     0,
                     653,
                     653,
                     653,
                     653,
                     0,
                     658,
                     0,
                     0,
                     661,
                     0,
                     663,
                     663,
                     663,
                     663,
                     663,
                     663,
                     0,
                     0,
                     671,
                     671,
                     671,
                     671,
                     671,
                     0,
                     677,
                     677,
                     677,
                     677,
                     677,
                     677,
                     677,
                     0,
                     685,
                     685,
                     685,
                     685,
                     0,
                     690,
                     690,
                     690,
                     690,
                     690,
                     690,
                     0,
                     697,
                     697,
                     697,
                     697,
                     697,
                     697,
                     697,
                     697,
                     697,
                     697,
                     697,
                     0,
                     709,
                     709,
                     709,
                     709,
                     709,
                     709,
                     709,
                     709,
                     0,
                     718,
                     718,
                     718,
                     718,
                     0,
                     723,
                     723,
                     723,
                     723,
                     723,
                     723,
                     723,
                     723,
                     723,
                     0,
                     733,
                     733,
                     733,
                     733,
                     733,
                     733,
                     733,
                     0,
                     741,
                     741,
                     741,
                     741,
                     741,
                     741,
                     741,
                     741,
                     0,
                     750,
                     750,
                     750,
                     0,
                     754,
                     754,
                     754,
                     754,
                     754,
                     754,
                     754,
                     0,
                     762,
                     762,
                     762,
                     0,
                     766,
                     766,
                     766,
                     766,
                     766,
                     766,
                     0,
                     773,
                     773,
                     773,
                     773,
                     773,
                     0,
                     779,
                     779,
                     779,
                     779,
                     779,
                     779,
                     779,
                     0,
                     787,
                     0,
                     0,
                     790,
                     790,
                     790,
                     790,
                     790,
                     790,
                     0,
                     797,
                     797,
                     797,
                     797,
                     797,
                     797,
                     797,
                     0,
                     805,
                     805,
                     805,
                     805,
                     805,
                     805,
                     805,
                     805,
                     805,
                     805,
                     0,
                     816,
                     816,
                     816,
                     816,
                     816,
                     816,
                     816,
                     0,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     824,
                     0,
                     839,
                     839,
                     839,
                     839,
                     839,
                     839,
                     839,
                     839,
                     839,
                     0,
                     849,
                     849,
                     849,
                     0,
                     853,
                     853,
                     853,
                     853,
                     853,
                     853,
                     853,
                     853,
                     853,
                     853,
                     0,
                     864,
                     864,
                     864,
                     864,
                     864,
                     864,
                     864,
                     864,
                     0,
                     873,
                     873,
                     873,
                     873,
                     873,
                     873,
                     873,
                     0,
                     0,
                     882,
                     882,
                     882,
                     882,
                     882,
                     882,
                     882,
                     882,
                     882,
                     0,
                     892,
                     892,
                     892,
                     0,
                     896,
                     896,
                     896,
                     896,
                     896,
                     0,
                     902,
                     902,
                     902,
                     902,
                     0,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     907,
                     0,
                     921,
                     921,
                     921,
                     921,
                     0,
                     0,
                     927,
                     927,
                     0,
                     930,
                     930,
                     930,
                     930,
                     0,
                     935,
                     935,
                     935,
                     935,
                     0,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     940,
                     0,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     953,
                     0,
                     968,
                     968,
                     968,
                     968,
                     968,
                     968,
                     968,
                     968,
                     968,
                     0,
                     978,
                     978,
                     978,
                     0,
                     982,
                     982,
                     982,
                     982,
                     982,
                     982,
                     982,
                     982,
                     982,
                     982,
                     0,
                     993,
                     993,
                     993,
                     993,
                     993,
                     993,
                     993,
                     993,
                     993,
                     0,
                     1003,
                     1003,
                     1003,
                     1003,
                     1003,
                     1003,
                     1003,
                     1003,
                     0,
                     1012,
                     0,
                     1014,
                     1014,
                     1014,
                     1014,
                     1014,
                     1014,
                     1014,
                     1014,
                     0,
                     1023,
                     1023,
                     0,
                     1026,
                     0,
                     1028,
                     1028,
                     1028,
                     1028,
                     1028,
                     0,
                     1034,
                     0,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     1036,
                     0,
                     1049,
                     1049,
                     0,
                     0,
                     1053,
                     1053,
                     1053,
                     1053,
                     0,
                     1058,
                     1058,
                     1058,
                     1058,
                     1058,
                     0,
                     1064,
                     1064,
                     1064,
                     1064,
                     1064,
                     1064,
                     0,
                     1071,
                     1071,
                     1071,
                     1071,
                     1071,
                     1071,
                     1071,
                     1071,
                     1071,
                     1071,
                     0,
                     1082,
                     1082,
                     1082,
                     1082,
                     1082,
                     1082,
                     1082,
                     1082,
                     1082,
                     1082,
                     0,
                     1093,
                     1093,
                     1093,
                     1093,
                     1093,
                     1093,
                     1093,
                     1093,
                     0,
                     1102,
                     1102,
                     0,
                     1105,
                     1105,
                     1105,
                     1105,
                     1105,
                     1105,
                     1105,
                     1105,
                     0,
                     1114,
                     0,
                     1116,
                     1116,
                     1116,
                     1116,
                     1116,
                     1116,
                     0,
                     1123,
                     1123,
                     1123,
                     1123,
                     1123,
                     1123,
                     0,
                     0,
                     1131,
                     0,
                     1133,
                     1133,
                     1133,
                     1133,
                     1133,
                     1133,
                     0,
                     1140,
                     0,
                     1142,
                     1142,
                     1142,
                     1142,
                     0,
                     1147,
                     1147,
                     1147,
                     1147,
                     1147,
                     1147,
                     1147,
                     0,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     1155,
                     0,
                     1169,
                     1169,
                     1169,
                     1169,
                     1169,
                     1169,
                     1169,
                     1169,
                     0,
                     1178,
                     1178,
                     1178,
                     1178,
                     1178,
                     1178,
                     1178,
                     0,
                     1186,
                     1186,
                     1186,
                     1186,
                     0,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     1191,
                     0,
                     1206,
                     1206,
                     1206,
                     1206,
                     1206,
                     1206,
                     1206,
                     1206,
                     0,
                     1215,
                     1215,
                     1215,
                     1215,
                     1215,
                     1215,
                     1215,
                     1215,
                     0,
                     1224,
                     1224,
                     1224,
                     0,
                     1228,
                     1228,
                     1228,
                     1228,
                     1228,
                     1228,
                     1228,
                     1228,
                     1228,
                     1228,
                     0,
                     1239,
                     1239,
                     1239,
                     1239,
                     0,
                     1244,
                     1244,
                     1244,
                     1244,
                     1244,
                     0,
                     1250,
                     1250,
                     1250,
                     1250,
                     1250,
                     0,
                     1256,
                     1256,
                     1256,
                     1256,
                     1256,
                     1256,
                     1256,
                     0,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     1264,
                     0,
                     1276,
                     0,
                     1278,
                     1278,
                     1278,
                     1278,
                     1278,
                     0,
                     1284,
                     1284,
                     1284,
                     1284,
                     1284,
                     1284,
                     1284,
                     0,
                     1292,
                     1292,
                     1292,
                     1292,
                     1292,
                     0,
                     1298,
                     1298,
                     1298,
                     1298,
                     1298,
                     1298,
                     1298,
                     1298,
                     0,
                     1307,
                     1307,
                     1307,
                     1307,
                     1307,
                     1307,
                     1307,
                     1307,
                     1307,
                     1307,
                     0,
                     1318,
                     1318,
                     1318,
                     1318,
                     1318,
                     1318,
                     1318,
                     1318,
                     1318,
                     0,
                     1328,
                     1328,
                     1328,
                     1328,
                     1328,
                     1328,
                     1328,
                     1328,
                     0,
                     1337,
                     1337,
                     1337,
                     1337,
                     1337,
                     1337,
                     1337,
                     1337,
                     0,
                     1346,
                     1346,
                     1346,
                     0,
                     1350,
                     1350,
                     1350,
                     1350,
                     1350,
                     1350,
                     1350,
                     1350,
                     0,
                     1359,
                     1359,
                     1359,
                     0,
                     1363,
                     0,
                     1365,
                     1365,
                     1365,
                     1365,
                     0,
                     0,
                     1371,
                     1371,
                     1371,
                     1371,
                     1371,
                     1371,
                     0,
                     1378,
                     0,
                     0,
                     1381,
                     1381,
                     0,
                     1384,
                     1384,
                     1384,
                     1384,
                     1384,
                     1384,
                     1384,
                     0,
                     1392,
                     1392,
                     1392,
                     0,
                     1396,
                     1396,
                     1396,
                     1396,
                     1396,
                     1396,
                     1396,
                     0,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     1404,
                     0,
                     1420,
                     1420,
                     1420,
                     1420,
                     1420,
                     1420,
                     1420,
                     1420,
                     0,
                     1429,
                     1429,
                     1429,
                     1429,
                     1429,
                     1429,
                     1429,
                     1429,
                     1429,
                     1429,
                     0,
                     1440,
                     1440,
                     1440,
                     0,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     1444,
                     0,
                     1461,
                     1461,
                     1461,
                     1461,
                     1461,
                     1461,
                     1461,
                     0,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     1469,
                     0,
                     1485,
                     1485,
                     1485,
                     1485,
                     1485,
                     1485,
                     0,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     1492,
                     0,
                     1505,
                     1505,
                     1505,
                     1505,
                     1505,
                     1505,
                     1505,
                     1505,
                     0,
                     1514,
                     1514,
                     1514,
                     1514,
                     1514,
                     0,
                     1520,
                     1520,
                     1520,
                     1520,
                     1520,
                     1520,
                     1520,
                     0,
                     1528,
                     1528,
                     1528,
                     1528,
                     1528,
                     1528,
                     1528,
                     0,
                     1536,
                     1536,
                     1536,
                     1536,
                     1536,
                     1536,
                     1536,
                     1536,
                     1536,
                     0,
                     1546,
                     1546,
                     1546,
                     1546,
                     1546,
                     1546,
                     1546,
                     0,
                     1554,
                     1554,
                     1554,
                     1554,
                     1554,
                     1554,
                     0,
                     1561,
                     1561,
                     1561,
                     1561,
                     1561,
                     1561,
                     1561,
                     0,
                     1569,
                     1569,
                     1569,
                     1569,
                     1569,
                     1569,
                     1569,
                     1569,
                     0,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     1578,
                     0,
                     1593,
                     1593,
                     1593,
                     1593,
                     0,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     1598,
                     0,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     1612,
                     0,
                     1625,
                     1625,
                     1625,
                     1625,
                     1625,
                     1625,
                     1625,
                     1625,
                     0,
                     1634,
                     1634,
                     1634,
                     1634,
                     1634,
                     1634,
                     0,
                     1641,
                     1641,
                     0,
                     1644,
                     1644,
                     1644,
                     1644,
                     1644,
                     1644,
                     1644,
                     1644,
                     1644,
                     0,
                     1654,
                     1654,
                     1654,
                     1654,
                     1654,
                     1654,
                     1654,
                     0,
                     1662,
                     1662,
                     1662,
                     1662,
                     1662,
                     1662,
                     0,
                     0,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     1670,
                     0,
                     1682,
                     1682,
                     1682,
                     1682,
                     1682,
                     0,
                     1688,
                     1688,
                     0,
                     1691,
                     1691,
                     1691,
                     1691,
                     1691,
                     1691,
                     0,
                     1698,
                     1698,
                     1698,
                     0,
                     1702,
                     1702,
                     1702,
                     1702,
                     1702,
                     1702,
                     1702,
                     1702,
                     1702,
                     0,
                     1712,
                     0,
                     0,
                     1715,
                     1715,
                     1715,
                     1715,
                     1715,
                     1715,
                     0,
                     1722,
                     1722,
                     1722,
                     0,
                     1726,
                     1726,
                     1726,
                     1726,
                     1726,
                     1726,
                     1726,
                     0,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     1734,
                     0,
                     1747,
                     1747,
                     1747,
                     1747,
                     1747,
                     1747,
                     1747,
                     1747,
                     1747,
                     1747,
                     0,
                     1758,
                     1758,
                     1758,
                     1758,
                     1758,
                     1758,
                     1758,
                     1758,
                     0,
                     1767,
                     1767,
                     0,
                     1770,
                     1770,
                     1770,
                     1770,
                     1770,
                     1770,
                     1770,
                     1770,
                     0,
                     1779,
                     0,
                     1781,
                     0,
                     1783,
                     1783,
                     1783,
                     1783,
                     1783,
                     1783,
                     1783,
                     1783,
                     0,
                     1792,
                     1792,
                     1792,
                     0,
                     1796,
                     0,
                     1798,
                     1798,
                     1798,
                     1798,
                     1798,
                     0,
                     1804,
                     1804,
                     1804,
                     1804,
                     1804,
                     1804,
                     0,
                     1811,
                     1811,
                     0,
                     0,
                     0,
                     1816,
                     1816,
                     1816,
                     0,
                     1820,
                     1820,
                     1820,
                     1820,
                     1820,
                     1820,
                     1820,
                     1820,
                     0,
                     1829,
                     1829,
                     1829,
                     1829,
                     1829,
                     1829,
                     1829,
                     1829,
                     1829,
                     1829,
                     0,
                     1840,
                     1840,
                     1840,
                     1840,
                     1840,
                     1840,
                     1840,
                     1840,
                     0,
                     1849,
                     1849,
                     1849,
                     1849,
                     1849,
                     0,
                     1855,
                     1855,
                     1855,
                     1855,
                     1855,
                     1855,
                     1855,
                     1855,
                     0,
                     1864,
                     1864,
                     1864,
                     1864,
                     1864,
                     1864,
                     1864,
                     0,
                     1872,
                     1872,
                     0,
                     1875,
                     1875,
                     0,
                     1878,
                     1878,
                     1878,
                     1878,
                     1878,
                     1878,
                     1878,
                     0,
                     1886,
                     1886,
                     1886,
                     0,
                     1890,
                     1890,
                     1890,
                     1890,
                     1890,
                     1890,
                     0,
                     1897,
                     0,
                     1899,
                     1899,
                     1899,
                     1899,
                     1899,
                     1899,
                     1899,
                     0,
                     1907,
                     0,
                     1909,
                     0,
                     1911,
                     1911,
                     1911,
                     1911,
                     1911,
                     1911,
                     0,
                     1918,
                     1918,
                     1918,
                     1918,
                     0,
                     1923,
                     1923,
                     1923,
                     1923,
                     1923,
                     1923,
                     1923,
                     0,
                     1931,
                     1931,
                     1931,
                     1931,
                     1931,
                     1931,
                     1931,
                     1931,
                     1931,
                     0,
                     1941,
                     1941,
                     1941,
                     1941,
                     1941,
                     1941,
                     1941,
                     0,
                     1949,
                     1949,
                     1949,
                     1949,
                     1949,
                     1949,
                     1949,
                     1949,
                     0,
                     1958,
                     1958,
                     0,
                     1961,
                     1961,
                     1961,
                     1961,
                     1961,
                     1961,
                     1961,
                     1961,
                     1961,
                     0,
                     1971,
                     1971,
                     1971,
                     1971,
                     1971,
                     1971,
                     1971,
                     0,
                     1979,
                     1979,
                     1979,
                     1979,
                     1979,
                     1979,
                     1979,
                     0,
                     0,
                     1988,
                     1988,
                     1988,
                     1988,
                     1988,
                     1988,
                     1988,
                     0,
                     1996,
                     1996,
                     1996,
                     1996,
                     1996,
                     0,
                     2002,
                     0,
                     2004,
                     0,
                     0,
                     2007,
                     2007,
                     2007,
                     2007,
                     2007,
                     2007,
                     2007,
                     0,
                     2015,
                     2015,
                     2015,
                     0,
                     2019,
                     0,
                     2021,
                     2021,
                     2021,
                     2021,
                     2021,
                     2021,
                     2021,
                     0,
                     2029,
                     2029,
                     2029,
                     0,
                     2033,
                     2033,
                     2033,
                     2033,
                     2033,
                     2033,
                     0,
                     2040,
                     2040,
                     2040,
                     2040,
                     2040,
                     2040,
                     2040,
                     0,
                     2048,
                     2048,
                     2048,
                     2048,
                     2048,
                     2048,
                     2048,
                     2048,
                     2048,
                     0,
                     2058,
                     2058,
                     2058,
                     2058,
                     2058,
                     2058,
                     2058,
                     2058,
                     0,
                     2067,
                     0,
                     2069,
                     2069,
                     2069,
                     2069,
                     2069,
                     2069,
                     2069,
                     2069,
                     2069,
                     0,
                     2079,
                     2079,
                     2079,
                     2079,
                     2079,
                     2079,
                     2079,
                     0,
                     2087,
                     2087,
                     0,
                     2090,
                     0,
                     2092,
                     2092,
                     2092,
                     2092,
                     2092,
                     2092,
                     2092,
                     2092,
                     0,
                     2101,
                     0,
                     0,
                     2104,
                     2104,
                     2104,
                     0,
                     0,
                     2109,
                     2109,
                     2109,
                     2109,
                     2109,
                     2109,
                     2109,
                     0,
                     2117,
                     0,
                     0,
                     2120,
                     2120,
                     2120,
                     2120,
                     2120,
                     2120,
                     0,
                     2127,
                     2127,
                     2127,
                     2127,
                     0,
                     2132,
                     2132,
                     2132,
                     2132,
                     2132,
                     2132,
                     2132,
                     2132,
                     0,
                     2141,
                     2141,
                     2141,
                     2141,
                     0,
                     2146,
                     2146,
                     2146,
                     2146,
                     2146,
                     2146,
                     2146,
                     0,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     2154,
                     0,
                     2166,
                     2166,
                     2166,
                     2166,
                     2166,
                     2166,
                     2166,
                     2166,
                     0,
                     2175,
                     0,
                     2177,
                     2177,
                     2177,
                     2177,
                     2177,
                     2177,
                     2177,
                     2177,
                     0,
                     2186,
                     2186,
                     2186,
                     2186,
                     2186,
                     2186,
                     2186,
                     0,
                     2194,
                     2194,
                     2194,
                     2194,
                     2194,
                     2194,
                     0,
                     2201,
                     2201,
                     2201,
                     0,
                     2205,
                     2205,
                     2205,
                     2205,
                     2205,
                     2205,
                     2205,
                     0,
                     2213,
                     0,
                     2215,
                     0,
                     2217,
                     2217,
                     2217,
                     2217,
                     0,
                     2222,
                     2222,
                     2222,
                     2222,
                     2222,
                     2222,
                     2222,
                     2222,
                     2222,
                     0,
                     2232,
                     0,
                     2234,
                     2234,
                     2234,
                     2234,
                     0,
                     2239,
                     2239,
                     2239,
                     2239,
                     2239,
                     0,
                     2245,
                     2245,
                     2245,
                     2245,
                     2245,
                     0,
                     2251,
                     2251,
                     2251,
                     2251,
                     2251,
                     2251,
                     2251,
                     0,
                     2259,
                     2259,
                     2259,
                     2259,
                     2259,
                     2259,
                     2259,
                     2259,
                     0,
                     2268,
                     2268,
                     2268,
                     2268,
                     2268,
                     2268,
                     2268,
                     2268,
                     0,
                     2277,
                     0,
                     2279,
                     2279,
                     2279,
                     2279,
                     2279,
                     2279,
                     2279,
                     2279,
                     0,
                     2288,
                     2288,
                     2288,
                     2288,
                     2288,
                     2288,
                     2288,
                     0,
                     2296,
                     2296,
                     2296,
                     2296,
                     2296,
                     2296,
                     2296,
                     2296,
                     0,
                     2305,
                     2305,
                     2305,
                     0,
                     2309,
                     2309,
                     2309,
                     2309,
                     2309,
                     2309,
                     2309,
                     2309,
                     2309,
                     0,
                     2319,
                     2319,
                     2319,
                     2319,
                     2319,
                     0,
                     2325,
                     2325,
                     2325,
                     2325,
                     0,
                     2330,
                     2330,
                     2330,
                     2330,
                     2330,
                     2330,
                     0,
                     2337,
                     2337,
                     2337,
                     2337,
                     0,
                     2342,
                     2342,
                     2342,
                     2342,
                     2342,
                     2342,
                     2342,
                     0,
                     2350,
                     2350,
                     2350,
                     2350,
                     0,
                     2355,
                     2355,
                     2355,
                     2355,
                     0,
                     2360,
                     2360,
                     2360,
                     2360,
                     2360,
                     2360,
                     2360,
                     0,
                     2368,
                     2368,
                     2368,
                     2368,
                     2368,
                     2368,
                     0,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     2375,
                     0,
                     2387,
                     2387,
                     2387,
                     2387,
                     2387,
                     0,
                     2393,
                     2393,
                     2393,
                     2393,
                     2393,
                     2393,
                     2393 };

#endif /* _MA_HANCODE_H_ */

