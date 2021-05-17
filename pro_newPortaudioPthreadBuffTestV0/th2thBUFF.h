#ifndef __RQUEUE_H__
#define __RQUEUE_H__

#include "pro_sys.h"

/* ========================================================================== */
void fn_L2Gbuff                                           /* data --->>> очередь */
(
    struct TH2THbuff *,
    BUFF_TYPE        *,
    unsigned int
);
/* ========================================================================== */
void fn_G2Lbuff                                           /* data <<<--- очередь */
(
    struct TH2THbuff *,
    BUFF_TYPE        *,
    unsigned int
);

#endif /* __RQUEUE_H__ */

