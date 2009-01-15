/*
 * Detect the specified code's block type
 *    Jinsuk Kim, http://www.jinsuk.pe.kr
 */

#include "ConvertUTF.h"
#include "UnicodeBlocks31.h"

/* returns the character type according to UnicodeBlocks31.h */
int getCodeType(UTF32 c) {
    if (c < 0) return T_ILL;	/* negative is illegal */

    /* character types for U+0000~U+00FF: defined in cType1[] */
    if (c < 0x0100) {
	return cType1[c];
    }
    /* U+0100 ~ U+07FF */
    if (c < 0x0800) {
	if      (c >= 0x0100 && c <= 0x017F)
	    return T_LAT;			/* Latin_Extended-A */
	else if (c >= 0x0180 && c <= 0x024F)
	    return T_LAT;			/* Latin_Extended-B */
	else if (c >= 0x0250 && c <= 0x02AF)
	    return T_IPA;			/* IPA_Extensions */
	else if (c >= 0x02B0 && c <= 0x02FF)
	    return T_SML;			/* Spacing_Modifier_Letters */
	else if (c >= 0x0300 && c <= 0x036F)
	    return T_CDM;			/* Combining_Diacritical_Marks */
	else if (c >= 0x0370 && c <= 0x03FF)
	    return T_GRE;			/* Greek */
	else if (c >= 0x0400 && c <= 0x04FF)
	    return T_CYR;			/* Cyrillic(Russian) */
	else if (c >= 0x0530 && c <= 0x058F)
	    return T_ARM;			/* Armenian */
	else if (c >= 0x0590 && c <= 0x05FF)
	    return T_HEB;			/* Hebrew */
	else if (c >= 0x0600 && c <= 0x06FF)
	    return T_ARA;			/* Arabic */
	else if (c >= 0x0700 && c <= 0x074F)
	    return T_SYR;			/* Syriac */
	else if (c >= 0x0780 && c <= 0x07BF)
	    return T_THN;			/* Thaana */
	else return T_RES;			/* not defined or reserved */
    }
    /* U+0800 ~ U+FFF */
    if (c < 0x1000) {
	if      (c >= 0x0900 && c <= 0x097F)
	    return T_DEV;			/* Devanagari */
	else if (c >= 0x0980 && c <= 0x09FF)
	    return T_BNG;			/* Bengali */
	else if (c >= 0x0A00 && c <= 0x0A7F)
	    return T_GUR;			/* Gurmukhi */
	else if (c >= 0x0A80 && c <= 0x0AFF)
	    return T_GUJ;			/* Gujarati */
	else if (c >= 0x0B00 && c <= 0x0B7F)
	    return T_ORI;			/* Oriya */
	else if (c >= 0x0B80 && c <= 0x0BFF)
	    return T_TAM;			/* Tamil */
	else if (c >= 0x0C00 && c <= 0x0C7F)
	    return T_TEL;			/* Telugu */
	else if (c >= 0x0C80 && c <= 0x0CFF)
	    return T_KAN;			/* Kannada */
	else if (c >= 0x0D00 && c <= 0x0D7F)
	    return T_MAL;			/* Malayalam */
	else if (c >= 0x0D80 && c <= 0x0DFF)
	    return T_SIN;			/* Sinhala */
	else if (c >= 0x0E00 && c <= 0x0E7F)
	    return T_THI;			/* Thai */
	else if (c >= 0x0E80 && c <= 0x0EFF)
	    return T_LAO;			/* Lao */
	else if (c >= 0x0F00 && c <= 0x0FFF)
	    return T_TIB;			/* Tibetan */
	else return T_RES;			/* reserved */
    }

    /* U+1000 ~ U+1FFF */
    if (c < 0x2000) {
	if      (c >= 0x1000 && c <= 0x109F)
	    return T_MYA;			/* Myanmar */
	else if (c >= 0x10A0 && c <= 0x10FF)
	    return T_GEO;			/* Georgian */
#if 0
	else if (c >= 0x1100 && c <= 0x11FF)
	    return T_HAN;			/* Hangul_Jamo */
#endif
	else if (c >= 0x1200 && c <= 0x137F)
	    return T_ETH;			/* Ethiopic */
	else if (c >= 0x13A0 && c <= 0x13FF)
	    return T_CHE;			/* Cherokee */
	else if (c >= 0x1400 && c <= 0x167F)
	    return T_CAN;			/* Unified_Canadian_Aboriginal_Syllabics */
	else if (c >= 0x1680 && c <= 0x169F)
	    return T_OGH;			/* Ogham */
	else if (c >= 0x16A0 && c <= 0x16FF)
	    return T_RUN;			/* Runic */
	else if (c >= 0x1780 && c <= 0x17FF)
	    return T_KHM;			/* Khmer */
	else if (c >= 0x1800 && c <= 0x18AF)
	    return T_MON;			/* Mongolian */
	else if (c >= 0x1E00 && c <= 0x1EFF)
	    return T_LAT;			/* Latin_Extended_Additional */
	else if (c >= 0x1F00 && c <= 0x1FFF)
	    return T_GRE;			/* Greek_Extended */
	else return T_RES;			/* reserved */
    }

    /* U+2000 ~ U+2FFF */
    if (c < 0x3000) {
	if      (c >= 0x2000 && c <= 0x206F)
	    return T_GPT;			/* General_Punctuation */
	else if (c >= 0x2070 && c <= 0x209F)
	    return T_SPB;			/* Superscripts_and_Subscripts */
	else if (c >= 0x20A0 && c <= 0x20CF)
	    return T_CUR;			/* Currency_Symbols */
	else if (c >= 0x20D0 && c <= 0x20FF)
	    return T_CMS;			/* Combining_Marks_for_Symbols */
	else if (c >= 0x2100 && c <= 0x214F)
	    return T_LLS;			/* Letterlike_Symbols */
	else if (c >= 0x2150 && c <= 0x218F)
	    return T_NUF;			/* Number_Forms */
	else if (c >= 0x2190 && c <= 0x21FF)
	    return T_ARW;			/* Arrows */
	else if (c >= 0x2200 && c <= 0x22FF)
	    return T_MOP;			/* Mathematical_Operators */
	else if (c >= 0x2300 && c <= 0x23FF)
	    return T_MST;			/* Miscellaneous_Technical */
	else if (c >= 0x2400 && c <= 0x243F)
	    return T_CPX;			/* Control_Pictures */
	else if (c >= 0x2440 && c <= 0x245F)
	    return T_OCR;			/* Optical_Character_Recognition */
	else if (c >= 0x2460 && c <= 0x24FF)
	    return T_EAN;			/* Enclosed_Alphanumerics */
	else if (c >= 0x2500 && c <= 0x257F)
	    return T_BXD;			/* Box_Drawing */
	else if (c >= 0x2580 && c <= 0x259F)
	    return T_BLM;			/* Block_Elements */
	else if (c >= 0x25A0 && c <= 0x25FF)
	    return T_GMS;			/* Geometric_Shapes */
	else if (c >= 0x2600 && c <= 0x26FF)
	    return T_MSS;			/* Miscellaneous_Symbols */
	else if (c >= 0x2700 && c <= 0x27BF)
	    return T_DBT;			/* Dingbats */
	else if (c >= 0x2800 && c <= 0x28FF)
	    return T_BRP;			/* Braille_Patterns */
	else if (c >= 0x2E80 && c <= 0x2EFF)
	    return T_CJK;			/* CJK_Radicals_Supplement */
	else if (c >= 0x2F00 && c <= 0x2FDF)
	    return T_CJK;			/* Kangxi_Radicals */
	else if (c >= 0x2FF0 && c <= 0x2FFF)
	    return T_IDC;			/* Ideographic_Description_Characters */
	else return T_RES;			/* reserved */
    }

    /* U+3000 ~ U+9FFF */
    if (c < 0xA000) {
	if      (c >= 0x3000 && c <= 0x303F)
	    return T_CSP;			/* CJK_Symbols_and_Punctuation */
	else if (c >= 0x3040 && c <= 0x309F)
	    return T_JHI;			/* Hiragana */
	else if (c >= 0x30A0 && c <= 0x30FF)
	    return T_JKA;			/* Katakana */
	else if (c >= 0x3100 && c <= 0x312F)
	    return T_BPM;			/* Bopomofo */
#if 0
	else if (c >= 0x3130 && c <= 0x318F)
	    return T_HAN;			/* Hangul_Compatibility_Jamo */
#endif
	else if (c >= 0x3190 && c <= 0x319F)
	    return T_KBN;			/* Kanbun */
	else if (c >= 0x31A0 && c <= 0x31BF)
	    return T_BPM;			/* Bopomofo_Extended */
	else if (c >= 0x3200 && c <= 0x32FF)
	    return T_ECL;			/* Enclosed_CJK_Letters_and_Months */
	else if (c >= 0x3300 && c <= 0x33FF)
	    return T_CCP;			/* CJK_Compatibility */
	else if (c >= 0x3400 && c <= 0x4DB5)
	    return T_CJK;			/* CJK_Unified_Ideographs_Extension_A */
	else if (c >= 0x4E00 && c <= 0x9FFF)
	    return T_CJK;			/* CJK_Unified_Ideographs */
	else return T_RES;			/* reserved */
    }

    /* U+A000 ~ U+FFFF */
    if (c < 0x10000) {
	if      (c >= 0xA000 && c <= 0xA48F)
	    return T_YIS;			/* Yi_Syllables */
	else if (c >= 0xA490 && c <= 0xA4CF)
	    return T_YIS;			/* Yi_Radicals */
	else if (c >= 0xAC00 && c <= 0xD7A3)
	    return T_HAN;			/* Hangul_Syllables */
	else if (c >= 0xD800 && c <= 0xDB7F)
	    return T_HSG;			/* High_Surrogates */
	else if (c >= 0xDB80 && c <= 0xDBFF)
	    return T_HSS;			/* High_Private_Use_Surrogates */
	else if (c >= 0xDC00 && c <= 0xDFFF)
	    return T_LSG;			/* Low_Surrogates */
	else if (c >= 0xE000 && c <= 0xF8FF)
	    return T_PRI;			/* Private_Use */
	else if (c >= 0xF900 && c <= 0xFAFF)
	    return T_CCI;			/* CJK_Compatibility_Ideographs */
	else if (c >= 0xFB00 && c <= 0xFB4F)
	    return T_APF;			/* Alphabetic_Presentation_Forms */
	else if (c >= 0xFB50 && c <= 0xFDFF)
	    return T_RPF;			/* Arabic_Presentation_Forms-A */
	else if (c >= 0xFE20 && c <= 0xFE2F)
	    return T_CHM;			/* Combining_Half_Marks */
	else if (c >= 0xFE30 && c <= 0xFE4F)
	    return T_CCP;			/* CJK_Compatibility_Forms */
	else if (c >= 0xFE50 && c <= 0xFE6F)
	    return T_SFV;			/* Small_Form_Variants */
	else if (c >= 0xFE70 && c <= 0xFEFE)
	    return T_RPF;			/* Arabic_Presentation_Forms-B */
	else if (c >= 0xFEFF && c <= 0xFEFF)
	    return T_CTK;			/* Specials */
	else if (c >= 0xFF00 && c <= 0xFFEF)
	    return T_HFF;			/* Halfwidth_and_Fullwidth_Forms */
	else if (c >= 0xFFF0 && c <= 0xFFFD)
	    return T_CTK;			/* Specials */
	else return T_RES;			/* reserved */
    }

    /* U+10000 ~ U+10FFFF */
    if (c < 0x110000) {
	if      (c >= 0x10300 && c <= 0x1032F)
	    return T_OIT;			/* Old_Italic */
	else if (c >= 0x10330 && c <= 0x1034F)
	    return T_GTH;			/* Gothic */
	else if (c >= 0x10400 && c <= 0x1044F)
	    return T_DSR;			/* Deseret */
	else if (c >= 0x1D000 && c <= 0x1D0FF)
	    return T_BMS;			/* Byzantine_Musical_Symbols */
	else if (c >= 0x1D100 && c <= 0x1D1FF)
	    return T_MUS;			/* Musical_Symbols */
	else if (c >= 0x1D400 && c <= 0x1D7FF)
	    return T_MAS;			/* Mathematical_Alphanumeric_Symbols */
	else if (c >= 0x20000 && c <= 0x2A6D6)
	    return T_CJK;			/* CJK_Unified_Ideographs_Extension_B */
	else if (c >= 0x2A700 && c <= 0x2AB0E)
	    return T_CJK;			/* ICT_Soft_Brand_New_Hanja 2005-12-26 */
	else if (c >= 0x2F800 && c <= 0x2FA1F)
	    return T_CCI;			/* CJK_Compatibility_Ideographs_Supplement */
	else if (c >= 0xE0000 && c <= 0xE007F)
	    return T_TAG;			/* Tags */
	else if (c >= 0xF0000 && c <= 0xFFFFD)
	    return T_PRI;			/* Private_Use */
	else if (c >= 0x100000 && c <= 0x10FFFD)
	    return T_PRI;			/* Private_Use */
	else return T_RES;			/* reserved */
    }
    return T_ILL;			/* out of Unicode 3.1 boundary */
}

int GetCodeType(UTF32 c) {
    int codeType;

    codeType = getCodeType(c);
    switch (codeType) {
	case T_LAT: return codeType;
	case T_BLN: return codeType;
	case T_SPC: return codeType;
	case T_CTK: return codeType;
	case T_DIG: return codeType;
	case T_HAN: return codeType;
	case T_CJK: return codeType;

	case T_CCI:	/* CJK Compatibility Ideographs */
	case T_KXR: 	/* Kaxi Radicals */
		    return T_CJK;

	case T_JHI: 	/* Japanese Hiragana */
	case T_JKA: 	/* Japanese Katakana */
		    return T_JPN;

	case T_APF:  	/* Alphabetic Presentation Forms */
	case T_ARW:  	/* Arrows */
	case T_BLM: 	/* Block Elements */
	case T_BPM:  	/* Bopomofo */
	case T_BRP:  	/* Braile Patterns */
	case T_BXD: 	/* Box Drawing */
	case T_CCP: 	/* CJK Compatibility */
	case T_CDM: 	/* Combining Diactrical Marks */
	case T_CHM: 	/* Combining Half Marks */
	case T_CMS: 	/* Combining Marks for Symbols */
	case T_CPX: 	/* Control Pictures */
	case T_CSP: 	/* CJK Symbols and Punctuation */
	case T_CUR: 	/* Currency Symbols */
	case T_DBT: 	/* Dingbats */
	case T_EAN: 	/* Enclosed Alphanumberics */
	case T_ECL: 	/* Enclosed CJK Letters and Months */
	case T_GMS: 	/* Geometric Shapes */
	case T_GPT: 	/* General Punctuations */
	case T_HFF: 	/* Halfwidth and Fullwidth Forms */
	case T_IDC: 	/* Ideographic Description Characters */
	case T_IPA: 	/* IPA Extensions */
	case T_KBN: 	/* Kanbun */
	case T_LLS: 	/* Letterlike Symbols */
	case T_MAS: 	/* Mathematical Alphanumeric Symbols */
	case T_MOP: 	/* Mathmematical Operators */
	case T_MSS: 	/* Miscellanous Symbols */
	case T_MST: 	/* Miscellanous Technical */
	case T_NUF: 	/* Number Forms */
	case T_OCR: 	/* Optical Character Recognition */
	case T_RPF: 	/* Arabic Presentation Forms */
	case T_SFV: 	/* Small Form Variants */
	case T_SML: 	/* Spacing Modifier Letters */
	case T_SPB: 	/* Superscripts and Subscripts */
	case T_TAG: 	/* Tags */
		    return T_SYM;	/* return as symbol */

	case T_SRG: 	/* Surrogates */
	case T_LSG: 	/* Low Surrogates */
	case T_HSG: 	/* High Surrogates */
	case T_HSS: 	/* High Special-purpose Surrogates */
	case T_RES: 	/* Reserved */
		    return T_ILL;	/* return as ill */
	default: 	/* default */
		    return codeType;
    }
    return T_ILL;
}

