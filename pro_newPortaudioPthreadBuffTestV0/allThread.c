#include "allThread.h"

/*============================================================================*/
void fn_giveBrise4thread
(
    pthread_t     *threadArray,
    void         (*fooArray[NUM_THREADS_NOW])(void),
    unsigned int  ui_i
)
/*----------------------------------------------------------------------------*/
{
    if(ui_i!=0)                                                                 /* mandatory prerequisite */
        {
            --ui_i;

            if (pthread_create(&threadArray[ui_i], NULL, fooArray[ui_i], NULL) != 0)   /* recursive down actions */
                {
                    printf("threads init error - %i\n", ui_i);
                    exit(1);
                }
            printf("\\/ thread %i start\n", ui_i);

            fn_giveBrise4thread(threadArray, fooArray, ui_i);                   /* recursion */

             if (pthread_cancel(threadArray[ui_i]) != 0)                        /* recursive up actions */
                {
                    printf("thread cancel failed - %i\n", ui_i);
                    exit(1);
                }
            if (pthread_join(threadArray[ui_i], NULL) != 0)                     /* recursive up actions */
                {
                    printf("join threads error - %i\n", ui_i);
                    exit(1);
                }
            printf("/\\ thread %i close\n", ui_i);
        }
    else
        {
            while(!o_GS.gb_stopTreadFlag)
                {
                    usleep(WAIT);
                    signal(SIGINT, sig_handler);
                }
            return;                           /* out and gut the stack  (!!!) */
        }
}
/*============================================================================*/
void pfn_thread_rAudio(void *vptr_args)
/*----------------------------------------------------------------------------*/
{
    int i_i;
    BUFF_TYPE a_buffer[BUFFL];
    PaError err; 

    while (1)
        {
            err = Pa_ReadStream(o_GS.stream, a_buffer, BUFFL);                            // read in the local buffer
            if (err)
                {
                    fprintf(FDE, "bad portaudio read... \n");
                    if(o_GS.gb_exitIFerror)
                        {
                            raise(SIGINT);
                            sleep(1);
                            _exit(NULL);
                        }
                }
            /* -\/------------------------------------------------------------- lock -\/- */
            pthread_mutex_lock(&UT_mutex);
            if (!o_TH2THbuff.b_empty)
                {
                    pthread_cond_wait(&Empty, &UT_mutex);                       // wait until freed
                }
            fn_L2Gbuff(&o_TH2THbuff, a_buffer, o_TH2THbuff.ui_ByteInDBuff);     // local buffer to the global
            pthread_cond_signal(&Full);
            pthread_mutex_unlock(&UT_mutex);
            /* -/\----------------------------------------------------------- unlock -/\- */
        }
    pthread_exit(NULL);
}
/*============================================================================*/
void pfn_thread_wAudio(void *vptr_args)
/*----------------------------------------------------------------------------*/
{
    int i_i;
    BUFF_TYPE a_buffer[BUFFL];
    PaError err; 

    while (1)
        {
            err = Pa_WriteStream(o_GS.stream, a_buffer, BUFFL);                           // write from the local buffer
            if (err)
                {
                    fprintf(FDE, "bad portaudio write... \n");
                    if(o_GS.gb_exitIFerror)
                        {
                            raise(SIGINT);
                            sleep(1);
                            _exit(NULL);
                        }
                }
            /* -\/------------------------------------------------------------- lock -\/- */
            pthread_mutex_lock(&UT_mutex);
            if (o_TH2THbuff.b_empty)
                {
                    pthread_cond_wait(&Full, &UT_mutex);                        // wait until filled
                }
            fn_G2Lbuff(&o_TH2THbuff, a_buffer, o_TH2THbuff.ui_ByteInDBuff);     // global buffer to the local
            pthread_cond_signal(&Empty);
            pthread_mutex_unlock(&UT_mutex);
            /* -/\----------------------------------------------------------- unlock -/\- */

        }
    pthread_exit(NULL);
}
/*============================================================================*/
void pfn_thread_dspR(void *vptr_args)
/*----------------------------------------------------------------------------*/
{
    BUFF_TYPE a_buffer[BUFFL];
    PaError err;
    while (1)
        {
            /* -\/------------------------------------------------------------- lock -\/- */
            pthread_mutex_lock(&UT_mutex);
            if (o_TH2THbuff.b_empty)                                            // wait until empty
                {
                    pthread_cond_wait(&Full, &UT_mutex);                        // ...when filled
                }
            fn_G2Lbuff(&o_TH2THbuff, a_buffer, o_TH2THbuff.ui_ByteInDBuff);     // read in a local
            pthread_cond_signal(&Empty);
            pthread_mutex_unlock(&UT_mutex);
            /* -/\----------------------------------------------------------- unlock -/\- */
            fn_dsp_encode(&o_TH2THbuff, &o_GS, a_buffer, o_TH2THbuff.ui_ByteInDBuff);
        }
    pthread_exit(NULL);
}
/*============================================================================*/
void pfn_thread_dspW(void *vptr_args)
/*----------------------------------------------------------------------------*/
{
    BUFF_TYPE a_buffer[BUFFL];

    while (1)
        {
            fn_dsp_decode(&o_TH2THbuff, &o_GS, a_buffer, o_TH2THbuff.ui_ByteInDBuff);
            /* -\/------------------------------------------------------------- lock -\/- */
            pthread_mutex_lock(&UT_mutex);
            if (!o_TH2THbuff.b_empty)                                           // if not empty - wait
                {
                    pthread_cond_wait(&Empty, &UT_mutex);                       // forward when emptied
                }
            fn_L2Gbuff(&o_TH2THbuff, a_buffer, o_TH2THbuff.ui_ByteInDBuff);     // read in a global
            pthread_cond_signal(&Full);
            pthread_mutex_unlock(&UT_mutex);
            /* -/\----------------------------------------------------------- unlock -/\- */
        }
    pthread_exit(NULL);
}

