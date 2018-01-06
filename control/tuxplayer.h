#ifndef CONTROL_TUXPLAYER_H
#define CONTROL_TUXPLAYER_H

#include <gst/gst.h>
#include <gtk/gtk.h>

#include "rb_plugin.h"

REALcontrol tuxPlayerDef;

typedef struct {
    GtkWidget* player;
    GstElement* playbin;
    GstState curState;
    guint64 duration;
    bool isValid;
} ClassTuxPlayer;

ClassTuxPlayer* tux_getInstance(REALcontrolInstance ctl);

#endif // CONTROL_TUXPLAYER_H
