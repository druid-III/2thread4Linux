#include "pro_sys.h"

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm */
int main (int argc, char *argv[])
/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm */
{
    pthread_t ga_threads[NUM_THREADS_NOW];

    /* \/---------------------------------------------------------------- DSP INI */
    void (*Fa_threadsFoo[NUM_THREADS_NOW])(void *vptr_args);

    gfn_globalini();
    atexit(fn_allClose4Out);                                                    /* register output handler */

    if(EXIT_SUCCESS != fn_go_bis(argc, &(*argv)))                               /* ! command line processing ! */
        {
            fprintf(FDE, "cl error");
        }

    if(o_GS.gb_RX)
        {
            Fa_threadsFoo[0] = pfn_thread_rAudio;
            Fa_threadsFoo[1] = pfn_thread_dspR;

            if(o_GS.gb_append)
                {
                    o_GS.i_fd =
                        open(o_GS.gsa_way2file,
                             O_WRONLY | O_APPEND ,
                             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH ); /* file for writing */
                }
            else
                {
                    o_GS.i_fd =
                        open(o_GS.gsa_way2file,
                             O_WRONLY | O_CREAT ,             /* O_SYNC | O_APPEND */
                             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH ); /* file for writing */
                }
            gfn_portaudioiniRX();
        }
    else
        {
            Fa_threadsFoo[0] = pfn_thread_wAudio;
            Fa_threadsFoo[1] = pfn_thread_dspW;

            o_GS.i_fd =
                open(o_GS.gsa_way2file,
                     O_RDONLY | O_SYNC,
                     NULL );                                                    /* file for reading */

            lseek(o_GS.i_fd, 
                  o_GS.gui_timeseek*o_GS.gui_sfreq*o_GS.ui_ByteInDType, 
                  SEEK_SET);

            gfn_portaudioiniTX();
        }

    fn_modePrint();

    fn_giveBrise4thread(ga_threads, Fa_threadsFoo, NUM_THREADS_NOW);

    /* if no atexit() -->> fn_allClose4Out(); */
    fprintf(FDO, "OUT OK\n");

    return (EXIT_SUCCESS);
}

