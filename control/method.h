#ifndef CONTROL_METHOD_H
#define CONTROL_METHOD_H

#include "rb_plugin.h"

void tuxm_setFile(REALcontrolInstance ctl, REALobject fi);
void tuxm_play(REALcontrolInstance ctl);
void tuxm_stop(REALcontrolInstance ctl);
void tuxm_pause(REALcontrolInstance ctl);

#endif // CONTROL_METHOD_H
