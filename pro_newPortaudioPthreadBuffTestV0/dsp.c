#include "dsp.h"

/* ========================================================================== */
int fn_dsp_encode
(
    struct TH2THbuff       *p2th2th,
    struct GlobalSingleton *p2cla,
    BUFF_TYPE              *p_b,
    const unsigned int      ui_byte
)
/* -------------------------------------------------------------------------- */
{
    unsigned int ui_i;
    /* \/------------------------------------------------------------ блок запиан */
    ui_i = write(p2cla->i_fd, p_b, ui_byte);
    /* /\------------------------------------------------------------ блок запиан */
    if (ui_i != ui_byte)
        {
            fprintf(FDE, "bad write to file... \n");
            _exit(NULL);
        }
    return (EXIT_SUCCESS);
}
/* ========================================================================== */
int fn_dsp_decode
(
    struct TH2THbuff       *p2th2th,
    struct GlobalSingleton *p2cla,
    BUFF_TYPE              *p_b,
    const unsigned int      ui_byte
)
/* -------------------------------------------------------------------------- */
{
    unsigned int ui_i;
    /* \/------------------------------------------------------------ блок запиан */
    ui_i = read(p2cla->i_fd, p_b, ui_byte);
    /* /\------------------------------------------------------------ блок запиан */
    if (ui_i != ui_byte)
        {
            if((p2cla->gb_circle)&&(ui_i<0))
                {
                    lseek(p2cla->i_fd, 0L, SEEK_SET);
                }
            else
                {
                    fprintf(FDE, "bad read from file... \n");
                    p2cla->gb_stopTreadFlag = true;
                    raise(SIGINT);
                    //  raise(SIGTERM);
                    // _exit(NULL);
                }
        }
    return (EXIT_SUCCESS);
}
