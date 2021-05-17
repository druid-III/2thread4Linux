#ifndef __ALLTHREAD_H__
#define __ALLTHREAD_H__
#pragma once

#include "pro_sys.h"
//==============================================================================
void fn_giveBrise4thread
(
    pthread_t                              *,
    void (*fooArray[NUM_THREADS_NOW])(void) ,
    unsigned int
);
/*============================================================================*/
void pfn_thread_rAudio(void *vptr_args);
/*============================================================================*/
void pfn_thread_wAudio(void *vptr_args);
/*============================================================================*/
void pfn_thread_dspR(void *vptr_args);
/*============================================================================*/
void pfn_thread_dspW(void *vptr_args);
/*----------------------------------------------------------------------------*/

#endif /* __ALLTHREAD_H__ */

