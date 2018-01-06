#ifndef CONTROL_BEHAVIOUR_H
#define CONTROL_BEHAVIOUR_H

#include "rb_plugin.h"

void Constructor(REALcontrolInstance ctl);
void OnOpen(REALcontrolInstance ctl);
void OnClose(REALcontrolInstance ctl);
void OnDrawOffscreen(REALcontrolInstance ctl, REALgraphics g);
void* OnControlHandleGetter(REALcontrolInstance ctl);

#endif // CONTROL_BEHAVIOUR_H
