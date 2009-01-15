#ifndef _SYS_HEADER_H_
#define _SYS_HEADER_H_

#include <MA_CompileMode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifdef WIN32
#include <ctype.h>
#include <search.h>
#endif
#ifdef FCNTL_MOD
#include <fcntl.h>
#endif
#ifdef THREAD_PER_WORD
#include <pthread.h>
#endif

#ifdef MADLL_EXPORTS
#define DLLMA_API __declspec(dllexport)
#endif

#endif /* _SYS_HEADER_H_ */

