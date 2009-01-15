/************************************************************************
 * Unicode��� ��ū �и� ����
 *
 * ������ : �ּ���
 ************************************************************************/
#include <IDX_common.h>
#include <IDX_user.h>
#include <ConvertUTF.h>
#include <UnicodeBlocks31.h>

int GetCodeType(UTF32 c);

//#define MAX_INTERNAL_BUF		300000
#define MAX_INTERNAL_BUF		1000000	// 2007.02.20 (modified)
#define MAX_DELS_NUM			100
/*
 * utf-8�� ��ȯ�� �ϸ� �ѱ� �� ���ڿ� ������ ���̰� �ٸ��� ������...
 * �ΰ��� ��츦 �и��ؼ� �����Ѵ�.
 */
//#define MAX_TWOBYTE_TOKEN_LEN		MAXKEYLEN/3
#define MAX_TWOBYTE_TOKEN_LEN		50000
#define MAX_ONEBYTE_TOKEN_LEN		MAXKEYLEN

// �ִ� 5�������� ���� ��ū ������ ������ �� �ִ� ���۸���� �߰�
typedef struct {
	int t_type;
} TOKEN_BUF;

static TOKEN_BUF _T_Buf[5];
static int _T_Buf_idx;

#if 0
/* �ý��ۿ��� ����ϴ� delimiter ���� */
static char Delimiter[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \r\t\n\0";
/* �����ȣ�� ������ delimiter */
static char OnlyDel[] = "#$%&*+-/<=>@[\\]^_`{|}~ \r\t\n\0";
/* ���� ��ȣ */
static char SentMark[] = "!\"'(),.:;?";
#endif

/* UFT-8�� �Է¹޾Ƽ� UTF-32�� ��ȯ�� ����� ���� */
/* UTF32�� �����ϴ� ������ ��ū �и��� ���ؼ��̴�. */
static UTF32 _UTF32_SecVal[MAX_INTERNAL_BUF];
static unsigned int _U_len;
static unsigned int _CurrPos;

static UTF32 _UTF32_Dels[MAX_DELS_NUM];		// ����� ���� �и��� 
static unsigned int _D_len;

int isUserDel(UTF32 c);

void insert_token_buf(int type);
int IDX_PrevToken(int idx);
int is_SJW_SpecialChar(UTF32 c);

void insert_token_buf(int type)
{
	int i;

	if (_T_Buf_idx == 4) {
		for (i = 0; i < 4; i++) {
			_T_Buf[i] = _T_Buf[i+1];
		}
		_T_Buf[4].t_type = type;
	} else {
		_T_Buf_idx++;
		_T_Buf[_T_Buf_idx].t_type = type;
	}
}

// ���翡�� ���� ��ū Ÿ���� ����
// �Ű������� ���̳ʽ���
int IDX_PrevToken(int idx)
{
	if (idx + _T_Buf_idx < 0)
		return -1;

	return _T_Buf[idx + _T_Buf_idx].t_type;
}

int IDX_UTF8toUTF32(unsigned char *utf8_val, unsigned int *utf32_val, unsigned int *utf32_len)
{
	UTF32 	u32_val[MAX_INTERNAL_BUF];
	int 	u32_len;
	UTF8	*u8_start, *u8_end;
	UTF32	*u32_start, *u32_end;
	int		u8_len = strlen((char*)utf8_val);
	int 	i;
	ConversionResult c_res;

	u8_start = (UTF8 *) utf8_val;
	u32_start = u32_val;

	u8_end = (UTF8 *) &utf8_val[u8_len];
	u32_end = &u32_val[MAX_INTERNAL_BUF];

	c_res = ConvertUTF8toUTF32(&u8_start, u8_end, &u32_start, u32_end, strictConversion, &u32_len);

	for (i = 0; i < u32_len; i++)
		utf32_val[i] = u32_val[i];
	*utf32_len = u32_len;

	return 1;
}

int IDX_UTF32toUTF8(unsigned int *utf32_val, unsigned int utf32_len, unsigned char *utf8_val)
{
	UTF8	*u8_start, *u8_end;
	UTF32	*u32_start, *u32_end;
	int		u8_len;
	ConversionResult c_res;

	u32_start = (UTF32 *) utf32_val;
	u32_end = (UTF32 *) &utf32_val[utf32_len];
	u8_start = (UTF8 *) utf8_val;
	u8_end = (UTF8 *) &utf8_val[1024]; // ����:utf8_val ���۴� 1024�̻� �Ǿ�� �Ѵ�.
	c_res = ConvertUTF32toUTF8(&u32_start, u32_end, &u8_start, u8_end, strictConversion, &u8_len);

	utf8_val[u8_len] = '\0';

	return 1;
}

/* UTF-32 ---> UTF-8 */

/*
 * UTF-8 ��Ʈ�� ���ο� ���ڰ� �ִ��� ���θ� �����ϴ� �Լ�
 */
int isHanjaExist(char *str)
{
	int ret_val;
	UTF32 token[512];

	InitTokenizer((unsigned char *)str);
	while ((ret_val = GetNextTokenChar(token)) != -1)
		if (ret_val == T_CJK)
			return 1;

	return 0;
}

/*
 * UTF-8 >> UTF-32 ��ȯ ����
 * ���� ������ ����
 */
void InitTokenizer(unsigned char *doc)
{
	ConversionResult cnvt_res;
	int doc_len = strlen((char*)doc);
	UTF8 *doc_start;
	UTF32 *u_start;
	extern char *dels;
	//int i;

	_U_len = 0;
	_CurrPos = 0;
	_T_Buf_idx = -1;

	doc_start = (UTF8 *) doc;
	u_start = (UTF32 *) _UTF32_SecVal;

	/* UTF-8 >> UTF-32 */
	cnvt_res = ConvertUTF8toUTF32(&doc_start, (UTF8*)&(doc[doc_len]), &u_start
		, &(_UTF32_SecVal[MAX_INTERNAL_BUF]), strictConversion, (int*)&_U_len);

	_D_len = 0;
	if (dels != NULL) {
		doc_len = strlen(dels);
		doc_start = (UTF8 *) dels;
		u_start = (UTF32 *) _UTF32_Dels;

		/* UTF-8 >> UTF-32 */
		cnvt_res = ConvertUTF8toUTF32(&doc_start, (UTF8*)&(dels[doc_len]), &u_start
			, &(_UTF32_Dels[MAX_DELS_NUM]), strictConversion, (int*)&_D_len);
	}
}

/* ������ �ѱ��ھ� ���� */
int GetNextTokenChar(UTF32 *tok)
{
	int code_type;

	if (_CurrPos >= _U_len)
		return -1;

   	code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
	*tok = _UTF32_SecVal[_CurrPos];
	_CurrPos++;

	return code_type;
}

int isUserDel(UTF32 c)
{
	int i;

	for (i = 0; i < _D_len; i++) {
		if (_UTF32_Dels[i] == c)
			return 1;
	}

	return 0;
}

int is_SJW_SpecialChar(UTF32 c)
{
	switch (c) {
		case 0x25cb:
		case 0x3002:
		case 0x00b7:
		case 0x002c:
		case 0x003f:
		case 0x005b:
		case 0x005d:
		case 0x3008:
		case 0x3009:
		case 0x25c6:
		case 0x007b:
		case 0x007d:
		case 0x0028:
		case 0x0029:
		case 0x002b:
		case 0x002f:
		case 0x2605:
		case 0x25bc:
			return 1;
		default:
			return 0;
	}
}

/* ���� ��ġ���� ���� ��ū�� �����ϰ� ��ġ �̵� */
/* �������̸� -1 ���� */
/* opt = 1 : ����, ���ڰ� ���� �����ϴ� ��ū�� �ϳ��� ��ū���� �ν�
 *     = 0 : ��� �и� */
/*     = 2 : INDEX_BY_MIX_CHAR���� Ư�����ڸ� ���� */
int GetNextToken(UTF32 *tok, int *len, int opt)
{
	int code_type = -1;
	int break_flag = 0;
	int curr_mode;
	int del_num;

	// ����� ���� �������Ͱ� �����ϸ�...
	if (_D_len > 0) {
		while (isUserDel(_UTF32_SecVal[_CurrPos]))
			_CurrPos++;
		if (_CurrPos >= _U_len)
			return -1;

		*len = 0;
		code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
		while (_CurrPos < _U_len && !isUserDel(_UTF32_SecVal[_CurrPos])) {
			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		if (_CurrPos == _U_len && *len == 0)
			return -1;

		insert_token_buf(T_CMP);

		return T_CMP;
	}

RETRY:
	/* �����ȣ�� ������ ������ delimiter skip... */
	del_num = 0;
	while (1) {
		if (_CurrPos >= _U_len)
			break;

		code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
		switch (code_type) {
			case T_HAN: /* �ѱ� */
			case T_CJK: /* ���� */
			case T_LAT: /* Latin...(����) */
			case T_DIG: /* ���� */
			case T_PRI: /* ��� */
			case T_JPN: /* �Ϻ��� */
			case T_CYR: /* ���þƾ� */
				break_flag = 1;
				break;
			default:
				if ((opt == 2) && is_SJW_SpecialChar(_UTF32_SecVal[_CurrPos])) {
					code_type = T_SJW;
					break_flag = 1;
					break;
				}
				del_num++;
				break_flag = 0;
		}

		if (break_flag)
			break;

		_CurrPos++;
	}

	if (_CurrPos == _U_len)
		return -1;

	// �и��ڵ� �켱������ �ϳ��� ��ū(�������� �и��ڸ� �ϳ���)���� ����� ���Ͻ�Ų��.
	if (del_num > 0) { 
		insert_token_buf(T_DEL);
		return T_DEL;
	}

	if (code_type == T_SJW) { // ������ �ϱ�� Ư������
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;

		/* ��ū Ÿ�� ���� */
		insert_token_buf(T_SJW);
		return T_SJW;
	}

	if (code_type == T_PRI) { /* ��� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (code_type != T_PRI)
				break;

			if (*len > MAX_TWOBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_PRI) {
					_CurrPos++;
				}
				goto RETRY;
			}

			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		/* ��ū Ÿ�� ���� */
		insert_token_buf(T_PRI);
		return T_PRI;
	}

	if (code_type == T_CYR) { /* ���þƾ� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (code_type != T_CYR)
				break;

			if (*len > MAX_TWOBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_CYR) {
					_CurrPos++;
				}
				goto RETRY;
			}

			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		/* ��ū Ÿ�� ���� */
		insert_token_buf(T_CYR);
		return T_CYR;
	}

	if (code_type == T_JPN) { /* �Ϻ��� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (code_type != T_JPN)
				break;

			if (*len > MAX_TWOBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_JPN) {
					_CurrPos++;
				}
				goto RETRY;
			}

			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		/* ��ū Ÿ�� ���� */
		insert_token_buf(T_JPN);
		return T_JPN;
	}

	if (code_type == T_HAN) { /* �ѱ� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (code_type != T_HAN)
				break;

			if (*len > MAX_TWOBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_HAN) {
					_CurrPos++;
				}
				goto RETRY;
			}

			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		/* ��ū Ÿ�� ���� */
		insert_token_buf(T_HAN);
		return T_HAN;
	}

	if (code_type == T_CJK) { /* ���� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (code_type != T_CJK)
				break;

			if (*len > MAX_TWOBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_CJK) {
					_CurrPos++;
				}
				goto RETRY;
			}
			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		insert_token_buf(T_CJK);
		return T_CJK;
	}

	if (code_type == T_LAT) { /* ���� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (opt == 1) {
				if (code_type != T_LAT && code_type != T_DIG)
					break;
			} else {
				if (code_type != T_LAT)
					break;
			}

			if (*len > MAX_ONEBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_LAT) {
					_CurrPos++;
				}
				goto RETRY;
			}
			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		insert_token_buf(T_LAT);
		return T_LAT;
	}

	if (code_type == T_DIG) { /* ���� */
		*len = 0;
		tok[*len] = _UTF32_SecVal[_CurrPos];
		(*len)++;
		_CurrPos++;
		curr_mode = T_DIG;
		while (1) {
			if (_CurrPos >= _U_len)
				break;

			/* �� �κ��� ������ �ʿ��ϴ�... */
			code_type = GetCodeType(_UTF32_SecVal[_CurrPos]);
			if (opt == 1) {
				if (code_type != T_LAT && code_type != T_DIG)
					break;
			} else {
				if (code_type != T_DIG)
					break;
			}

			if (*len > MAX_ONEBYTE_TOKEN_LEN) {
				while ((code_type = GetCodeType(_UTF32_SecVal[_CurrPos])) == T_DIG) {
					_CurrPos++;
				}
				goto RETRY;
			}
			tok[*len] = _UTF32_SecVal[_CurrPos];
			(*len)++;
			_CurrPos++;
		}

		insert_token_buf(T_DIG);
		return T_DIG;
	}

	insert_token_buf(code_type);
	return code_type;
}
