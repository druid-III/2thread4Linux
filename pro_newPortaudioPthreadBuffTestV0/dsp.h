#ifndef __DSP_AI_H__
#define __DSP_AI_H__

#include "pro_sys.h"


/* ========================================================================== */
int fn_dsp_encode
(
    struct TH2THbuff       *,
    struct GlobalSingleton *,
    BUFF_TYPE              *,
    const unsigned int
);
/* ========================================================================== */
int fn_dsp_decode
(
    struct TH2THbuff       *,
    struct GlobalSingleton *,
    BUFF_TYPE              *,
    const unsigned int
);

#endif /* __DSP_AI_H__ */

