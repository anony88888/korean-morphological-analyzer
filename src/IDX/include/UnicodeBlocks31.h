/* by Jinsuk Kim, http://www.jinsuk.pe.kr */

/* code blocks based on Unicode Standard 3.1 */
#define T_APF  0	/* Alphabetic Presentation Forms */
#define T_ARA  1	/* Arabic */
#define T_ARM  2	/* Armenian */
#define T_ARW  3	/* Arrows */
#define T_BLM  4	/* Block Elements */
#define T_BLN  5	/* Spaces */
#define T_BMS  6	/* Byzantine Musical Symbols */
#define T_BNG  7	/* Bengali */
#define T_BPM  8	/* Bopomofo */
#define T_BRP  9	/* Braile Patterns */
#define T_BXD 10	/* Box Drawing */
#define T_CAN 11	/* Canadian Syllabics */
#define T_CCI 12	/* CJK Compatibility Ideographs */
#define T_CCP 13	/* CJK Compatibility */
#define T_CDM 14	/* Combining Diactrical Marks */
#define T_CHE 15	/* Cherokee */
#define T_CHM 16	/* Combining Half Marks */
#define T_CJK 17	/* CJK Ideographs */
#define T_CMS 18	/* Combining Marks for Symbols */
#define T_COP 19	/* Coptic */
#define T_CPX 20	/* Control Pictures */
#define T_CSP 21	/* CJK Symbols and Punctuation */
#define T_CTK 22	/* Control Characters */
#define T_CUR 23	/* Currency Symbols */
#define T_CYR 24	/* Cyrillic(Russian) */
#define T_DBT 25	/* Dingbats */
#define T_DEV 26	/* Devanagari */
#define T_DIG 27	/* Digits */
#define T_DSR 28	/* Deseret */
#define T_EAN 29	/* Enclosed Alphanumberics */
#define T_ECL 30	/* Enclosed CJK Letters and Months */
#define T_ETH 31	/* Ethiopic */
#define T_GEO 32	/* Georgian */
#define T_GMS 33	/* Geometric Shapes */
#define T_GPT 34	/* General Punctuations */
#define T_GRE 35	/* Greek */
#define T_GTH 36	/* Gothic */
#define T_GUJ 37	/* Gujarati */
#define T_GUR 38	/* Gurmukhi */
#define T_HAN 39	/* Hangul */
#define T_HEB 40	/* Hebrew */
#define T_HFF 41	/* Halfwidth and Fullwidth Forms */
#define T_HSG 42	/* High Surrogates */
#define T_HSS 43	/* High Special-purpose Surrogates */
#define T_IDC 44	/* Ideographic Description Characters */
#define T_ILL 45	/* Ill-formed or Ill-encoded */
#define T_IPA 46	/* IPA Extensions */
#define T_JHI 47	/* Japanese Hiragana */
#define T_JKA 48	/* Japanese Katakana */
#define T_JPN 49	/* Japanese */
#define T_KAN 50	/* Kannada */
#define T_KBN 51	/* Kanbun */
#define T_KHM 52	/* Khmer */
#define T_KXR 53	/* Kaxi Radicals */
#define T_LAO 54	/* Lao */
#define T_LAT 55	/* Latin */
#define T_LLS 56	/* Letterlike Symbols */
#define T_LSG 57	/* Low Surrogates */
#define T_MAL 58	/* Malayalam */
#define T_MAS 59	/* Mathematical Alphanumeric Symbols */
#define T_MON 60	/* Mongolian */
#define T_MOP 61	/* Mathmematical Operators */
#define T_MSS 62	/* Miscellanous Symbols */
#define T_MST 63	/* Miscellanous Technical */
#define T_MUS 64	/* Musical Symbols */
#define T_MYA 65	/* Myanmar */
#define T_NUF 66	/* Number Forms */
#define T_OCR 67	/* Optical Character Recognition */
#define T_OGH 68	/* Ogham */
#define T_OIT 69	/* Old Italic */
#define T_ORI 70	/* Oriya */
#define T_PRI 71	/* Private Use */
#define T_RES 72	/* Reserved */
#define T_RPF 73	/* Arabic Presentation Forms */
#define T_RUN 74	/* Runic */
#define T_SFV 75	/* Small Form Variants */
#define T_SIN 76	/* Sinhala */
#define T_SML 77	/* Spacing Modifier Letters */
#define T_SPB 78	/* Superscripts and Subscripts */
#define T_SPC 79	/* Special Characters */
#define T_SRG 80	/* Surrogates */
#define T_SYM 81	/* Symbols */
#define T_SYR 82	/* Syriac */
#define T_TAG 83	/* Tags */
#define T_TAM 84	/* Tamil */
#define T_TEL 85	/* Telugu */
#define T_THI 86	/* Thai */
#define T_THN 87	/* Thaana */
#define T_TIB 88	/* Tibetan */
#define T_YIS 89	/* Yi Syllables */

#define T_CMP 90	/* 복합토큰 */
#define T_DEL 91	/* 분리자 묶음 */
#define T_SJW 92	/* 승정원일기용 특수문자 */


typedef struct BlockNames {
    int idx;
    char *description;
} BLOCKNAMES_T;

static BLOCKNAMES_T BlockName[] = {
    {T_APF, "Alphabetic Presentation Forms"},
    {T_ARA, "Arabic"},
    {T_ARM, "Armenian"},
    {T_ARW, "Arrows"},
    {T_BLM, "Block Elements"},
    {T_BLN, "Spaces"},
    {T_BMS, "Byzantine Musical Symbols"},
    {T_BNG, "Bengali"},
    {T_BPM, "Bopomofo"},
    {T_BRP, "Braile Patterns"},
    {T_BXD, "Box Drawing"},
    {T_CAN, "Canadian Syllabics"},
    {T_CCI, "CJK Compatibility Ideographs"},
    {T_CCP, "CJK Compatibility"},
    {T_CDM, "Combining Diactrical Marks"},
    {T_CHE, "Cherokee"},
    {T_CHM, "Combining Half Marks"},
    {T_CJK, "CJK Ideographs"},
    {T_CMS, "Combining Marks for Symbols"},
    {T_COP, "Coptic"},
    {T_CPX, "Control Pictures"},
    {T_CSP, "CJK Symbols and Punctuation"},
    {T_CTK, "Control Characters"},
    {T_CUR, "Currency Symbols"},
    {T_CYR, "Cyrillic(Russian)"},
    {T_DBT, "Dingbats"},
    {T_DEV, "Devanagari"},
    {T_DIG, "Digits"},
    {T_DSR, "Deseret"},
    {T_EAN, "Enclosed Alphanumberics"},
    {T_ECL, "Enclosed CJK Letters and Months"},
    {T_ETH, "Ethiopic"},
    {T_GEO, "Georgian"},
    {T_GMS, "Geometric Shapes"},
    {T_GPT, "General Punctuations"},
    {T_GRE, "Greek"},
    {T_GTH, "Gothic"},
    {T_GUJ, "Gujarati"},
    {T_GUR, "Gurmukhi"},
    {T_HAN, "Hangul"},
    {T_HEB, "Hebrew"},
    {T_HFF, "Halfwidth and Fullwidth Forms"},
    {T_HSG, "High Surrogates"},
    {T_HSS, "High Special-purpose Surrogates"},
    {T_IDC, "Ideographic Description Characters"},
    {T_ILL, "Ill-formed or Ill-encoded"},
    {T_IPA, "IPA Extensions"},
    {T_JHI, "Japanese Hiragana"},
    {T_JKA, "Japanese Katakana"},
    {T_JPN, "Japanese"},
    {T_KAN, "Kannada"},
    {T_KBN, "Kanbun"},
    {T_KHM, "Khmer"},
    {T_KXR, "Kaxi Radicals"},
    {T_LAO, "Lao"},
    {T_LAT, "Latin"},
    {T_LLS, "Letterlike Symbols"},
    {T_LSG, "Low Surrogates"},
    {T_MAL, "Malayalam"},
    {T_MAS, "Mathematical Alphanumeric Symbols"},
    {T_MON, "Mongolian"},
    {T_MOP, "Mathmematical Operators"},
    {T_MSS, "Miscellanous Symbols"},
    {T_MST, "Miscellanous Technical"},
    {T_MUS, "Musical Symbols"},
    {T_MYA, "Myanmar"},
    {T_NUF, "Number Forms"},
    {T_OCR, "Optical Character Recognition"},
    {T_OGH, "Ogham"},
    {T_OIT, "Old Italic"},
    {T_ORI, "Oriya"},
    {T_PRI, "Private Use"},
    {T_RES, "Reserved"},
    {T_RPF, "Arabic Presentation Forms"},
    {T_RUN, "Runic"},
    {T_SFV, "Small Form Variants"},
    {T_SIN, "Sinhala"},
    {T_SML, "Spacing Modifier Letters"},
    {T_SPB, "Superscripts and Subscripts"},
    {T_SPC, "Special Characters"},
    {T_SRG, "Surrogates"},
    {T_SYM, "Symbols"},
    {T_SYR, "Syriac"},
    {T_TAG, "Tags"},
    {T_TAM, "Tamil"},
    {T_TEL, "Telugu"},
    {T_THI, "Thai"},
    {T_THN, "Thaana"},
    {T_TIB, "Tibetan"},
    {T_YIS, "Yi Syllables"}
};

static int cType1[] = {
  /* 0x0000 */
  T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_BLN,T_CTK,T_CTK,T_BLN,T_CTK,T_CTK,
  T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,
  T_BLN,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,
  T_DIG,T_DIG,T_DIG,T_DIG,T_DIG,T_DIG,T_DIG,T_DIG,T_DIG,T_DIG,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,
  T_SPC,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,
  T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,
  T_SPC,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,
  T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_SPC,T_SPC,T_SPC,T_SPC,T_CTK,
  /* 0x0080 */
  T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,
  T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,T_CTK,
  T_BLN,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,
  T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,T_SPC,
  T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,
  T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_SPC,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,
  T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,
  T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_SPC,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT,T_LAT
};

typedef struct Token {
    int type;
    int start;
    int len;
} TOKEN_T;

#define cMAXTOKENCNT	20000

