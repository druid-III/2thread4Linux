#ifndef __SYS_H__
#define __SYS_H__
#pragma once
//----------------------------------------------------------------SYSTEM_HEADERS
//#define _GNU_SOURCE
#include <stdbool.h>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <portaudio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

//-----------------------------------------------------------------------THREADS
#include <time.h>                                                        /* ? */
#include <pthread.h>

#include <signal.h>
#include <getopt.h>

#include "pro_allconstants.h"

#include "pro_global.h"
#include "allThread.h"
#include "dsp.h"

#endif /* __SYS_H__ */
