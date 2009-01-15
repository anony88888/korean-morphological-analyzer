###############################################################################
# 기본적인 설정들
###############################################################################
bindir = $(top_srcdir)/bin
libdir = $(prefix)/lib
includedir = $(top_srcdir)/include/idx

#==============================================================================
# KRISTAL에서 포함하는 헤터 디렉토리 설정
#==============================================================================
KRISTAL_INCLUDE = -I.
KRISTAL_INCLUDE += -I./src/IDX/include
KRISTAL_INCLUDE += -I./include
KRISTAL_INCLUDE += -I./src/MorpAnal/include
KRISTAL_INCLUDE += -I./src/Dict/include
KRISTAL_INCLUDE += -I$(top_srcdir)/include/error
KRISTAL_INCLUDE += -I$(top_srcdir)/include/share
KRISTAL_INCLUDE += -I$(top_srcdir)/include/kernel
KRISTAL_INCLUDE += -I$(top_srcdir)/include/rose
KRISTAL_INCLUDE += -I$(top_srcdir)/include/idx
KRISTAL_INCLUDE += -I$(top_srcdir)/include/fire

#==============================================================================
# KRISTAL에서 사용하는 공용 라이브러리 설정
#==============================================================================
KRISTAL_LIB_NAME = -lshare -lkerror -liconv -lz
KRISTAL_LIB_DIR = -L. -L$(top_srcdir)/lib 
KRISTAL_LIB = $(KRISTAL_LIB_DIR) $(KRISTAL_LIB_NAME)

#==============================================================================
# 디버깅 관련 설정들
#==============================================================================
#DEBUGFLAG = -DDEBUG_QP -DUSE_UNICODE -DUSE_EUCKR_PRINT
#TRACEFLAG = -DTRACE_CD
DEBUGSYMBOLS = -g

#==============================================================================
# 부가적인 LDFLAGS설정. 기본적인 것은 시스템 내에서 생성
#==============================================================================
#KRISTAL_LDFLAGS2 = -finline-functions -fexpensive-optimizations

#==============================================================================
# 코드 최적화 부분제거를 위해 임시 삽입 - 나중에 제거해야 함
# 시스템 디폴트로 -g -O2 생성
#==============================================================================
#AM_CFLAGS = -DMULTI_DIC_INFO -DMA_MODE -DVER_LIB -DUNKNOWN_WORD_CONSTRAINT_UP -DSUSA_AS_INDEX -DCOMP_NOUN_DIC_CHECK -DFOR_KRISTAL -DCN_FOR_KRISTAL -DKRISTAL_NATIVE_STOPCHECK -DKRISTAL_JOHAB_API -DUSER_DIC_PRE_CHECK

AM_CFLAGS = -DMULTI_DIC_INFO -DMA_MODE -DVER_LIB -DUNKNOWN_WORD_CONSTRAINT_UP -DSUSA_AS_INDEX -DCOMP_NOUN_DIC_CHECK -DFOR_KRISTAL -DCN_FOR_KRISTAL -DKRISTAL_NATIVE_STOPCHECK -DSHARED_MEMORY_DIC -DKRISTAL_JOHAB_API -DUSER_DIC_PRE_CHECK 
#-DUSER_ANSDIC_CHECK
# -DCD_PROC
# -DCD_ALL_CN_CHECK
# -DDUMP_CD_RESULT

#==============================================================================
# KRISTAL C++ 컴파일 플래그. 단지 컴파일 시에만 사용됨. 
# 컴파일/링크시에 모두 활용할 경우에는 AM_CXXFLAGS 사용
#==============================================================================
AM_CPPFLAGS = $(KRISTAL_INCLUDE) $(DEBUGFLAG) $(TRACEFLAG) $(DEBUGSYMBOLS)

###############################################################################
# AUTOMAKE 
###############################################################################
AUTOMAKE_OPTIONS =
EXTRA_DIST = src/IDX/include/*.h include src/MorpAnal/include src/Dict/include src/Dict/data
noinst_PROGRAMS = 
noinst_HEADERS = 
#lib_LIBRARIES = lib/libidx.a
lib_LTLIBRARIES = lib/libidx.la
include_HEADERS = include/IDX_user.h src/MorpAnal/include/*.h \
				  src/Dict/include/*.h

IDX_SOURCES = src/IDX/src/IDX_FilterSecVal.c           \
	src/IDX/src/IDX_MsgHandler.c                        \
	src/IDX/src/IDX_Hanja2Hangul.c                      \
	src/IDX/src/IDX_IndexAsIs.c                         \
	src/IDX/src/IDX_IndexAsIsMA.c                       \
	src/IDX/src/IDX_IndexAsNumeric.c             	 \
	src/IDX/src/IDX_IndexByChar.c                       \
	src/IDX/src/IDX_IndexByMA.c                         \
	src/IDX/src/IDX_IndexByMixChar.c                       \
	src/IDX/src/IDX_IndexByMixMA.c                         \
	src/IDX/src/IDX_HanjaVariant.c                         \
	src/IDX/src/IDX_IndexByToken.c                      \
	src/IDX/src/IDX_IndexByCDMA.c                      \
	src/IDX/src/IDX_IndexByCDToken.c                      \
	src/IDX/src/IDX_IndexDNA.c                      \
	src/IDX/src/IDX_IndexProtein.c                      \
	src/IDX/src/IDX_IndexTRDNA.c                      \
	src/IDX/src/IDX_StopWord.c                          \
	src/IDX/src/IDX_strlower.c                          \
	src/IDX/src/IDX_AddIndexBigram.c                          \
	src/IDX/src/ConvertUTF.c                            \
	src/IDX/src/GetCodeType.c                           \
	src/IDX/src/IDX_TokenProc.c                         \
	src/IDX/src/unijohab.c        			 \
	src/IDX/src/IDX_strip_affixes.c \
	src/IDX/src/IDX_CrossTermDic.c \
	src/IDX/src/IDX_duem_proc.c \
	src/MorpAnal/src/MA_CompareCode.c\
	src/MorpAnal/src/MA_CompoundNoun.c\
	src/MorpAnal/src/MA_Cordic.c\
	src/MorpAnal/src/MA_EomiCheck.c\
	src/MorpAnal/src/MA_GenMAResult.c\
	src/MorpAnal/src/MA_HashFunc.c\
	src/MorpAnal/src/MA_Hj2Hg.c\
	src/MorpAnal/src/MA_IdaCheck.c\
	src/MorpAnal/src/MA_Irregular.c\
	src/MorpAnal/src/MA_JosaCheck.c\
	src/MorpAnal/src/MA_KAnalysisWord.c\
	src/MorpAnal/src/MA_MainIDXProc.c\
	src/MorpAnal/src/MA_TopicMorpAnal.c\
	src/MorpAnal/src/MA_SearchTailDic.c\
	src/MorpAnal/src/MA_SusaCheck.c\
	src/MorpAnal/src/MA_UnknownWord.c\
	src/MorpAnal/src/MA_VAJubCheck.c\
	src/MorpAnal/src/MA_SearchCNDic.c\
	src/MorpAnal/src/MA_CNWordCheck.c\
	src/MorpAnal/src/MA_ShmOP.c\
	src/Dict/src/BD_ClearDic.c\
	src/Dict/src/BD_InitDicHeader.c\
	src/Dict/src/BD_MakeHanBuf.c\
	src/Dict/src/BD_SearchCharInCurrentLevel.c\
	src/Dict/src/SD_GetJEHeaderIndex.c\
	src/Dict/src/SD_JESearchWordInTrieDic.c\
	src/Dict/src/SD_LoadDictionary.c\
	src/Dict/src/SD_SearchDic.c\
	src/Dict/src/SD_SearchJECharInCurrentLevel.c\
	src/Dict/src/SD_SearchWordInTrieDic.c\
	src/Dict/src/SD_UserDic.c\
	src/Dict/src/SD_UserAnswerDic.c\
	src/MorpAnal/util-lib/LIB_FileOpen.c\
	src/MorpAnal/util-lib/LIB_FileClose.c\
	src/MorpAnal/util-lib/LIB_FileRead.c\
	src/MorpAnal/util-lib/LIB_CleanStr.c\
	src/MorpAnal/util-lib/LIB_MemoryCreate.c\
	src/MorpAnal/util-lib/LIB_MemoryDestroy.c\
	src/MorpAnal/util-lib/LIB_MemoryMove.c\
	src/MorpAnal/util-lib/LIB_MemoryReAlloc.c\
	src/MorpAnal/util-lib/LIB_FileWrite.c\
	src/MorpAnal/util-lib/LIB_FileSeek.c\
	src/MorpAnal/util-lib/LIB_FileTell.c
#libidx_a_SOURCES = $(IDX_SOURCES)
libidx_la_SOURCES = $(IDX_SOURCES)

$(bin_PROGRAMS): $(lib_LIBRARIES)
$(noinst_PROGRAMS): $(lib_LIBRARIES)

