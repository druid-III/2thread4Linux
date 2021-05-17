#include "pro_go_bis.h"

/* !!! used as a "-Oarg" or (&& no ||) "--O=arg" !!! */

/*============================================================================*/
int fn_go_bis
(
    int   argc,
    char *argv[]
)
/*----------------------------------------------------------------------------*/
{
    char s_cntr = 0;
    unsigned int ui_oal;

    static struct option long_options[] =
    {
        {"freq",        optional_argument, 0,       'f'},
        {"record",      optional_argument, 0,       'r'},
        {"play",        optional_argument, 0,       'w'},
        {"append",      optional_argument, 0,       'a'},
        {"seek",        optional_argument, 0,       's'},
        {"circle",      no_argument,       0,       'c'},
        {"exitiferror", no_argument,       0,       'e'},
        {"help",        no_argument,       0,       'h'},
        {0,             0,                 0,         0}
    };

    /* getopt_long stores the option index here. */
    int option_index = -1;

    while ((s_cntr = getopt_long (
                         argc,
                         argv,
                         "f::r::w::a::s::ceh",
                         long_options,
                         &option_index)) != -1)
        {
            switch (s_cntr)
                {
                    /* -------------------------------------------------------------------------- */
                case 'f':
                    if(optarg!=NULL)
                        {
                            ui_oal = (unsigned int)strlen(optarg);
                            if((FRLMIN-1)>ui_oal>(FRLMAX-1))
                                {
                                    fprintf(FDE, "strange freq. +__+\n");
                                    break;
                                }
                            strcpy(o_GS.gsa_freqstr, optarg);
                            o_GS.gui_sfreq = (unsigned int)atoi(o_GS.gsa_freqstr);

                            switch(o_GS.gui_sfreq)
                                {
                                case 4000 :
                                    break;
                                case 8000 :
                                    break;
                                case 9600 :
                                    break;
                                case 11025 :
                                    break;
                                case 16000 :
                                    break;
                                case 22050 :
                                    break;
                                case 32000 :
                                    break;
                                case 44100 :
                                    break;
                                case 48000 :
                                    break;
                                case 88200 :
                                    break;
                                case 96000 :
                                    break;
                                case 176400 :
                                    break;
                                case 192000 :
                                    break;
                                default:
                                    o_GS.gui_sfreq = FS;
                                    fprintf(FDE, "strange freq. O__o\n");
                                    break;
                                }
                        }
                    break;
                    /* -------------------------------------------------------------------------- */
                case 'r':
                    if(optarg!=NULL)
                        {
                            ui_oal = (unsigned int)strlen(optarg);
                            if(ui_oal>(WAY-1))
                                {
                                    fprintf(FDE, "Oh, that way so long. +__+\n");
                                    break;
                                }
                            strcpy(o_GS.gsa_way2file, optarg);
                        }
                    o_GS.gb_RX = true;
                    break;
                    /* -------------------------------------------------------------------------- */
                case 'w':
                    if(optarg!=NULL)
                        {
                            ui_oal = (unsigned int)strlen(optarg);
                            if(ui_oal>(WAY-1))
                                {
                                    fprintf(FDE, "Oh, that way so long. +__+\n");
                                    break;
                                }
                            strcpy(o_GS.gsa_way2file, optarg);
                        }
                    o_GS.gb_RX = false;
                    break;
                    /* -------------------------------------------------------------------------- */
                case 'a':
                    o_GS.gb_append = true;
                    break;
                    /* -------------------------------------------------------------------------- */
                case 's':
                    if(optarg!=NULL)
                        {
                            ui_oal = (unsigned int)strlen(optarg);
                            if(ui_oal<SSEEKDN)
                                {
                                    o_GS.gui_timeseek = atoi(optarg);
                                }
                        }
                    break;
                    /* -------------------------------------------------------------------------- */
                case 'c':
                    o_GS.gb_circle = true;
                    break;
                    /* -------------------------------------------------------------------------- */
                case 'e':
                    o_GS.gb_exitIFerror = true;
                    break;
                    /* -------------------------------------------------------------------------- */
                case 'h':
                    printf (" Simple RAW audio player/recorder HELP \n");
                    printf ("\n");
                    printf (" -f --freq        -> sampling frequency\n");
                    printf (" -r --record      -> record sound to raw\n");
                    printf (" -w --play        -> play raw to sound\n");
                    printf (" -c --circle      -> play a circle loop\n");
                    printf (" -e --exitiferror -> exit if i/o audio system error\n");
                    printf (" -a --append      -> when recording - add to the end of another track\n");
                    printf (" -s --seek        -> skip N seconds from the start when playing\n");
                    printf (" -h --help        -> print this help\n");
                    printf ("\n");
                    _exit(NULL);
                    break;
                    /* -------------------------------------------------------------------------- */
                case '?':
                    printf ("    !!! unrecognized option !!!\n");
                    printf ("\n");
                    printf (" Please use the options from this list: \n");
                    printf ("\n");
                    printf (" -f --freq        -> sampling frequency\n");
                    printf (" -r --record      -> record sound to raw\n");
                    printf (" -w --play        -> play raw to sound\n");
                    printf (" -c --circle      -> play a circle loop\n");
                    printf (" -e --exitiferror -> exit if i/o audio system error\n");
                    printf (" -a --append      -> when recording - add to the end of another track\n");
                    printf (" -s --seek        -> skip N seconds from the start when playing\n");
                    printf (" -h --help        -> print this help\n");
                    printf ("\n");
                    break;
                    /* -------------------------------------------------------------------------- */
                default:
                    printf ("    !!! unrecognized option !!!\n");
                    printf ("\n");
                    printf (" Please use the options from this list: \n");
                    printf ("\n");
                    printf (" -f --freq        -> sampling frequency\n");
                    printf (" -r --record      -> record sound to raw\n");
                    printf (" -w --play        -> play raw to sound\n");
                    printf (" -c --circle      -> play a circle loop\n");
                    printf (" -e --exitiferror -> exit if i/o audio system error\n");
                    printf (" -a --append      -> when recording - add to the end of another track\n");
                    printf (" -s --seek        -> skip N seconds from the start when playing\n");
                    printf (" -h --help        -> print this help\n");
                    printf ("\n");
                    break;
                }
        }
    return(EXIT_SUCCESS);
}

