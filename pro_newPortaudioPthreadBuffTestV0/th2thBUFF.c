#include "th2thBUFF.h"

/*                                      implementation buffer between threads */
/* ========================================================================== */
void fn_L2Gbuff                                          /* data --->>> queue */
(
    struct TH2THbuff *T2Tbuff,
    BUFF_TYPE        *p2inp,
    unsigned int      ui_sizeByte
)
/* -------------------------------------------------------------------------- */
{
    memcpy(T2Tbuff->a_data, p2inp, ui_sizeByte);
    T2Tbuff->b_empty = false;
//    printf("Local buff -->> GLOBAL buff\n");
    return;
}
/* ========================================================================== */
void fn_G2Lbuff                                          /* data <<<--- queue */
(
    struct TH2THbuff *T2Tbuff,
    BUFF_TYPE        *p2out,
    unsigned int      ui_sizeByte
)
/* -------------------------------------------------------------------------- */
{
    memcpy(p2out, T2Tbuff->a_data, ui_sizeByte);
    T2Tbuff->b_empty = true;
//    printf("GLOBAL buff -->> Local buff\n");
    return;
}

