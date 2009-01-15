#ifndef _MADIC_DICINFO_H_
#define _MADIC_DICINFO_H_

/* 품사 분류에 따른 사전 정보 */
/****************** 주사전 ********************************/
#define BS							1	/* 부사 */
#define JISI_BS						2	/* 지시부사 */
#define MJ_BS						3	/* 문장접속부사 */
#define DJ_BS						4	/* 단어접속부사 */
#define SIGAN_BS					5	/* 시간성부사 */

#define DOKRIB_A					10	/* 독립어 */

#define GHS							20	/* 관형사 */
#define JISI_GHS					21	/* 지시관형사 */
#define SU_GHS						22	/* 수관형사 */

#define BUL_MS						30	/* 불완전명사 */
#define DAN_MS						31	/* 단위명사 */
#define BO_MS						32	/* 보통명사 */
#define DONG_MS						33	/* 동작성명사 */
#define SANG_MS						34	/* 상태성명사 */
#define SIGAN_MS					35	/* 시간성명사 */
#define SUSA						36	/* 수사 */
#define JISI_DMS					37	/* 지시대명사 */
#define INC_DMS						38	/* 인칭대명사 */
#define GMS							39	/* 고유명사 */
#define INC_GMS						40	/* 인칭고유명사 */
#define SUNG_GMS					41	/* 성씨고유명사 */

#define HYS							42	/* 형용사 */
#define JISI_HYS					43	/* 지시형용사 */
#define DS							44	/* 동사 */

/****************** 조사사전 *******************************/
#define GYUCK_JOSA					1	/* 격조사 */
#define BUSAG_JOSA					2	/* 부사격조사 */
#define GHG_JOSA					3	/* 관형격조사 */
#define HG_JOSA						4	/* 호격조사 */
#define JSG_JOSA					5	/* 접속격조사 */
#define BJG_JOSA					6	/* 보조격조사 */

/****************** 어미사전 *******************************/
#define JSY_EOMI					1	/* 종속적연결어미 */
#define DDY_EOMI					2	/* 대등적연결어미 */
#define EM_EOMI						3	/* 어말어미 */
#define BSG_EOMI					4	/* 부사격어미 */
#define GHG_EOMI					5	/* 관형격어미 */
#define MJS_EOMI					6	/* 명사전성어미 */

#endif

