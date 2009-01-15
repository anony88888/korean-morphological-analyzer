#ifndef _MA_SEARCHTAILDIC_H_
#define _MA_SEARCHTAILDIC_H_

#define NTAIL_MODE		1     /* 체언형 형식형태소 모드 */
#define PTAIL_MODE		2     /* 용언형 형식형태소 모드 */
#define BTAIL_MODE		3     /* 체언형 실질-형식형태소 모드 */

typedef struct {
	UBYTE Morp[VS_BUFLEN];
	BYTE Tag[VS_BUFLEN];
} MORPHEME;

#endif /* _MA_SEARCHTAILDIC_H_ */
