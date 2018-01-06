#include "tuxplayer.h"

ClassTuxPlayer* tux_getInstance(REALcontrolInstance ctl)
{
    return REALGetControlData(ctl, &tuxPlayerDef);
}
