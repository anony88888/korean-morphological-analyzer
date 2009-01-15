/*
 * 불용어 관리 모듈...
 *
 * 불용어는 IDX에 전달되는 요구에 따라서...
 * 등록/삭제가 가능하다.
 * 또한 사용하려고 하는 불용어를 선택할 수 있다...
 *
 * 1. 불용어 등록
 *    불용어 등록에서는 입력으로 불용어 사전 ID, 불용어 리스트를 받는다.
 *    여기서 불용어 리스트는 각 불용어가 개행문자 혹은 공백, 탭으로 분리되어 있어야 한다. 
 *
 * 2. 불용어 제거
 *    불용어 제거는 입력으로 들어온 불용어 사전 ID를 이용하여 해당되는 불용어를 
 *    불용어 관리자에서 제거한다.
 *
 * 3. 불용어 검색
 *    불용어 검색은 해당되는 불용어 사전 ID에 대한 불용어 사전에서 입력 단어를 검색하는 기능을 수행한다.
 * 
 */

#ifndef _IDX_STOPWORD_H_
#define _IDX_STOPWORD_H_

#define MAX_STOPWORD_SETS		100
#define S_WORD_LEN				256
#define MAX_TEMP_BUF			10000
#define MAX_OUT_ID_BUF			256
#define MAX_ID_TABLE			1024

typedef struct {
	char s_word[S_WORD_LEN];
} SW_ITEM;

typedef struct {
	SW_ITEM *sw_item;
	int sw_item_num;
	char ID[MAX_OUT_ID_BUF];
} SW_SET;

#endif
