/*
 * �ҿ�� ���� ���...
 *
 * �ҿ��� IDX�� ���޵Ǵ� �䱸�� ����...
 * ���/������ �����ϴ�.
 * ���� ����Ϸ��� �ϴ� �ҿ� ������ �� �ִ�...
 *
 * 1. �ҿ�� ���
 *    �ҿ�� ��Ͽ����� �Է����� �ҿ�� ���� ID, �ҿ�� ����Ʈ�� �޴´�.
 *    ���⼭ �ҿ�� ����Ʈ�� �� �ҿ� ���๮�� Ȥ�� ����, ������ �и��Ǿ� �־�� �Ѵ�. 
 *
 * 2. �ҿ�� ����
 *    �ҿ�� ���Ŵ� �Է����� ���� �ҿ�� ���� ID�� �̿��Ͽ� �ش�Ǵ� �ҿ� 
 *    �ҿ�� �����ڿ��� �����Ѵ�.
 *
 * 3. �ҿ�� �˻�
 *    �ҿ�� �˻��� �ش�Ǵ� �ҿ�� ���� ID�� ���� �ҿ�� �������� �Է� �ܾ �˻��ϴ� ����� �����Ѵ�.
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
