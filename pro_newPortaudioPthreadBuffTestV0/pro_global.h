#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#pragma once

#include "pro_sys.h"

/*GlobalGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG\/G*/
// static bool      gb_stopTreadFlag;
// extern snd_pcm_t     *pUT_handle;

struct GlobalSingleton
{
    PaStream    *stream;
    bool         gb_stopTreadFlag;
    unsigned int ui_ByteInDType;
    char         gsa_way2file[WAY];
    char         gsa_freqstr[FRLMIN];
    unsigned int gui_sfreq;
    unsigned int gui_timeseek;
    bool         gb_circle;
    bool         gb_exitIFerror;
    bool         gb_append;
    bool         gb_RX;
    int          i_fd;
} o_GS;

struct TH2THbuff
{
    unsigned int    b_empty;                                                    // BUFFL empty or not
    BUFF_TYPE       a_data[BUFFL];
    unsigned int    ui_ByteInDBuff;                                             /* how many byte in buffer data type */
} o_TH2THbuff;


static pthread_cond_t  Empty    = PTHREAD_COND_INITIALIZER;
static pthread_cond_t  Full     = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t UT_mutex = PTHREAD_MUTEX_INITIALIZER;

/* ========================================================================== */
static void gfn_globalini(void)
/* -------------------------------------------------------------------------- */
{
    unsigned int ui_i;

    memset(o_TH2THbuff.a_data, 0, sizeof(o_TH2THbuff.a_data));

    o_GS.ui_ByteInDType = sizeof(BUFF_TYPE);
    o_TH2THbuff.b_empty = true;

    /* .......................................................................... */
    o_TH2THbuff.ui_ByteInDBuff = o_GS.ui_ByteInDType*BUFFL;
    o_GS.gb_stopTreadFlag      = false;
    /* .......................................................................... */
    o_GS.gui_sfreq       = FS;
    o_GS.gui_timeseek    = 0;
    o_GS.gb_circle       = false;
    o_GS.gb_append       = false;
    o_GS.gb_RX           = true;
    o_GS.gb_exitIFerror  = false;

    memset(o_GS.gsa_way2file, 0, sizeof(o_GS.gsa_way2file));

    strcpy(o_GS.gsa_way2file, FILE_NAME);

    return;
}
/* ========================================================================== */
static void sig_handler(int signo)
/* -------------------------------------------------------------------------- */
{
    if (signo == SIGINT)
        {
            o_GS.gb_stopTreadFlag = true;
            printf("received SIGINT\n");

            return;
        }
}
/* ========================================================================== */
static void fn_allClose4Out(void)
/* -------------------------------------------------------------------------- */
{
    PaError       err;

    Pa_StopStream( o_GS.stream );
    if( paNoError != err)
        {
            fprintf(FDO, "portaudio stop error: %s\n", Pa_GetErrorText( err ) );
        }

    Pa_CloseStream( o_GS.stream );
    if( paNoError != err)
        {
            fprintf(FDO, "portaudio close error: %s\n", Pa_GetErrorText( err ) );
        }

    Pa_Terminate();
    if( paNoError != err)
        {
            fprintf(FDO, "portaudio terminate error: %s\n", Pa_GetErrorText( err ) );
        }

    if(0 != close( o_GS.i_fd ))
        {
            printf(FDO, "file close error\n" );
        }

    if(0 != pthread_mutex_destroy(&UT_mutex))
        {
            printf("mutex close error\n");
        }

    if(0 != pthread_cond_destroy(&Empty))
        {
            printf("condition variable close error\n");
        }

    if(0 != pthread_cond_destroy(&Full))
        {
            printf("condition variable close error\n");
        }

    return;
}
/* ========================================================================== */
static void fn_modePrint(void)
/* -------------------------------------------------------------------------- */
{
    const PaStreamInfo *psy_p = Pa_GetStreamInfo (o_GS.stream);

    fprintf(FDO, "\n");
    fprintf(FDO, "Version is: %s \n",           Pa_GetVersionText ());
    fprintf(FDO, "inputLatency is:      %f \n", psy_p->inputLatency);
    fprintf(FDO, "outputLatency:        %f \n", psy_p->outputLatency);
    fprintf(FDO, "sampleRate is:        %f \n", psy_p->sampleRate);
    fprintf(FDO, "\n");
    fprintf(FDO, "sampling frequency :  %i Hz\n", o_GS.gui_sfreq);
    fprintf(FDO, "ch number          -> %i\n",    CH);
    fprintf(FDO, "\n");

    return;
}
/* ========================================================================== */
static void gfn_portaudioiniRX(void)
/* -------------------------------------------------------------------------- */
{
    PaError err;

    err = Pa_Initialize();
    if( err != paNoError )
        {
            fprintf(FDE, "r portaudio ini error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }

    /* Open an audio I/O  o_GS.stream. */
    err = Pa_OpenDefaultStream( & o_GS.stream,
                                CH,
                                0,
                                SAMPLECONF,
                                FS,
                                BUFFL,                                          /* frames per buffer */
                                NULL,                                           /* no callback, use blocking API */
                                NULL );                                         /* no callback, so no callback userData */                                  /* This is a pointer that will be passed to your callback*/

    if( err != paNoError )
        {
            fprintf(FDE, "r portaudio open error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }

    err = Pa_StartStream( o_GS.stream );
    if( err != paNoError )
        {
            fprintf(FDE, "r portaudio start error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }
    return;
}
/* ========================================================================== */
static void gfn_portaudioiniTX(void)
/* -------------------------------------------------------------------------- */
{
    PaError err;

    err = Pa_Initialize();
    if( err != paNoError )
        {
            fprintf(FDE, "w portaudio ini error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }

    /* Open an audio I/O  o_GS.stream. */
    err = Pa_OpenDefaultStream( & o_GS.stream,
                                0,
                                CH,
                                SAMPLECONF,
                                FS,
                                BUFFL,                                          /* frames per buffer */
                                NULL,                                           /* no callback, use blocking API */
                                NULL );                                         /* no callback, so no callback userData */

    if( err != paNoError )
        {
            fprintf(FDE, "w portaudio open error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }

    err = Pa_StartStream( o_GS.stream );
    if( err != paNoError )
        {
            fprintf(FDE, "w portaudio start error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }
    return;
}
/* ========================================================================== */
static void gfn_portaudioiniTRX(void)
/* -------------------------------------------------------------------------- */
{
    PaError err;

    err = Pa_Initialize();
    if(err != paNoError)
        {
            fprintf(FDE, "rw portaudio ini error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }

    /* Open an audio I/O  o_GS.stream. */
    err = Pa_OpenDefaultStream( & o_GS.stream,
                                CH,
                                CH,
                                SAMPLECONF,
                                FS,
                                BUFFL,                                          /* frames per buffer */
                                NULL,                                           /* no callback, use blocking API */
                                NULL );                                         /* no callback, so no callback userData */

    if( err != paNoError )
        {
            fprintf(FDE, "rw portaudio open error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }

    err = Pa_StartStream(  o_GS.stream );
    if( err != paNoError )
        {
            fprintf(FDE, "rw portaudio start error: %s\n", Pa_GetErrorText( err ) );
            _exit(NULL);
        }
    return;
}
/*GlobalGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG/\G*/

#endif /* __GLOBAL_H__ */

