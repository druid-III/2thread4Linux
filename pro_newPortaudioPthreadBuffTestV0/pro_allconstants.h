#ifndef __ALLCONSTANTS_H__
#define __ALLCONSTANTS_H__
#pragma once

/*
--------------------------------------------------------------------------------
 possible sampling frequency - all sound cards must support:
  4000,
  8000,
  9600,
  11025,
  16000,
  22050,
  32000,
  44100,
  48000,
  88200,
  96000,
  176400,
  192000;
--------------------------------------------------------------------------------
*/

/*-------------------------------------------------------------------- GLOBAL */
#define BUFF_TYPE       float

#define WAIT            16384 /* 61 Hz */

#define FILE_NAME      "./dic_float32.raw"

#define BUFFL           256
/*---------------------------------------------------------------------- MAIN */
#define FS              16000
#define CH              1
#define SAMPLECONF      paFloat32
/*-------------------------------------------------------------- AUDIOIO_ALSA */
#define ALSA_DEV        "default"                                 //"plughw:0,0"

#define FDO             stdout
#define FDI             stdin
#define FDE             stderr

#define NUM_THREADS_NOW 2

#define WAY             256
#define FRLMIN          5
#define FRLMAX          7
#define SSEEKDN         6                                                       // digit numbers on seek in seconds
/*----------------------------------------------------------------------------*/

#endif /* __ALLCONSTANTS_H__ */

