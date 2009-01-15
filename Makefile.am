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
KRISTAL_INCLUDE += -I./IDX.2001
KRISTAL_INCLUDE += -I./IDX.2001/include
KRISTAL_INCLUDE += -I./MorpAnal/include
KRISTAL_INCLUDE += -I./MorpAnal/dict/include
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
EXTRA_DIST = IDX.2001/*.h IDX.2001/include MorpAnal/include MorpAnal/dict/include dic
noinst_PROGRAMS = 
noinst_HEADERS = 
#lib_LIBRARIES = libidx.a
lib_LTLIBRARIES = libidx.la
include_HEADERS = IDX.2001/include/IDX_user.h MorpAnal/include/*.h \
				  MorpAnal/dict/include/*.h

IDX_SOURCES = IDX.2001/IDX_FilterSecVal.c           \
	IDX.2001/IDX_MsgHandler.c                        \
	IDX.2001/IDX_Hanja2Hangul.c                      \
	IDX.2001/IDX_IndexAsIs.c                         \
	IDX.2001/IDX_IndexAsIsMA.c                       \
	IDX.2001/IDX_IndexAsNumeric.c             	 \
	IDX.2001/IDX_IndexByChar.c                       \
	IDX.2001/IDX_IndexByMA.c                         \
	IDX.2001/IDX_IndexByMixChar.c                       \
	IDX.2001/IDX_IndexByMixMA.c                         \
	IDX.2001/IDX_HanjaVariant.c                         \
	IDX.2001/IDX_IndexByToken.c                      \
	IDX.2001/IDX_IndexByCDMA.c                      \
	IDX.2001/IDX_IndexByCDToken.c                      \
	IDX.2001/IDX_IndexDNA.c                      \
	IDX.2001/IDX_IndexProtein.c                      \
	IDX.2001/IDX_IndexTRDNA.c                      \
	IDX.2001/IDX_StopWord.c                          \
	IDX.2001/IDX_strlower.c                          \
	IDX.2001/IDX_AddIndexBigram.c                          \
	IDX.2001/ConvertUTF.c                            \
	IDX.2001/GetCodeType.c                           \
	IDX.2001/IDX_TokenProc.c                         \
	IDX.2001/unijohab.c        			 \
	IDX.2001/IDX_strip_affixes.c \
	IDX.2001/IDX_CrossTermDic.c \
	IDX.2001/IDX_duem_proc.c \
	MorpAnal/src/MA_CompareCode.c\
	MorpAnal/src/MA_CompoundNoun.c\
	MorpAnal/src/MA_Cordic.c\
	MorpAnal/src/MA_EomiCheck.c\
	MorpAnal/src/MA_GenMAResult.c\
	MorpAnal/src/MA_HashFunc.c\
	MorpAnal/src/MA_Hj2Hg.c\
	MorpAnal/src/MA_IdaCheck.c\
	MorpAnal/src/MA_Irregular.c\
	MorpAnal/src/MA_JosaCheck.c\
	MorpAnal/src/MA_KAnalysisWord.c\
	MorpAnal/src/MA_MainIDXProc.c\
	MorpAnal/src/MA_TopicMorpAnal.c\
	MorpAnal/src/MA_SearchTailDic.c\
	MorpAnal/src/MA_SusaCheck.c\
	MorpAnal/src/MA_UnknownWord.c\
	MorpAnal/src/MA_VAJubCheck.c\
	MorpAnal/src/MA_SearchCNDic.c\
	MorpAnal/src/MA_CNWordCheck.c\
	MorpAnal/src/MA_ShmOP.c\
	MorpAnal/dict/src/BD_ClearDic.c\
	MorpAnal/dict/src/BD_InitDicHeader.c\
	MorpAnal/dict/src/BD_MakeHanBuf.c\
	MorpAnal/dict/src/BD_SearchCharInCurrentLevel.c\
	MorpAnal/dict/src/SD_GetJEHeaderIndex.c\
	MorpAnal/dict/src/SD_JESearchWordInTrieDic.c\
	MorpAnal/dict/src/SD_LoadDictionary.c\
	MorpAnal/dict/src/SD_SearchDic.c\
	MorpAnal/dict/src/SD_SearchJECharInCurrentLevel.c\
	MorpAnal/dict/src/SD_SearchWordInTrieDic.c\
	MorpAnal/dict/src/SD_UserDic.c\
	MorpAnal/dict/src/SD_UserAnswerDic.c\
	MorpAnal/util-lib/LIB_FileOpen.c\
	MorpAnal/util-lib/LIB_FileClose.c\
	MorpAnal/util-lib/LIB_FileRead.c\
	MorpAnal/util-lib/LIB_CleanStr.c\
	MorpAnal/util-lib/LIB_MemoryCreate.c\
	MorpAnal/util-lib/LIB_MemoryDestroy.c\
	MorpAnal/util-lib/LIB_MemoryMove.c\
	MorpAnal/util-lib/LIB_MemoryReAlloc.c\
	MorpAnal/util-lib/LIB_FileWrite.c\
	MorpAnal/util-lib/LIB_FileSeek.c\
	MorpAnal/util-lib/LIB_FileTell.c
#libidx_a_SOURCES = $(IDX_SOURCES)
libidx_la_SOURCES = $(IDX_SOURCES)

$(bin_PROGRAMS): $(lib_LIBRARIES)
$(noinst_PROGRAMS): $(lib_LIBRARIES)

