#include <gdk/gdk.h>
#include <gst/gst.h>
#include <stdio.h>

#include "method.h"
#include "tuxplayer.h"

void tuxm_setFile(REALcontrolInstance ctl, REALobject fi)
{
    ClassTuxPlayer* self = tux_getInstance(ctl);

    bool isDirectory;
    REALGetPropValueBoolean(fi, "Directory", &isDirectory);
    if(isDirectory) {
        self->isValid = false;
        return;
    }

    REALstring native;
    REALGetPropValueString(fi, "NativePath", &native);
    // REALGetPropValueString(fi, "URLPath", &native);

    REALstring scheme = REALBuildStringWithEncoding("file://", 7, kREALTextEncodingUTF8);
    REALstring fullPath = REALAddStrings(scheme, native);

    size_t len;
    char* path = REALGetStringContents(fullPath, &len);

    REALUnlockString(scheme);
    REALUnlockString(native);
    REALUnlockString(fullPath);

    if(len <= 7) {
        self->isValid = false;
        return;
    }

    g_object_set(self->playbin, "uri", path, NULL);
}

void tuxm_play(REALcontrolInstance ctl)
{
    ClassTuxPlayer* self = tux_getInstance(ctl);

    GstStateChangeReturn ret;

    ret = gst_element_set_state(self->playbin, GST_STATE_PLAYING);
    if(ret == GST_STATE_CHANGE_FAILURE) {
        self->isValid = false;
        printf("GST_STATE_CHANGE_FAILURE\n");
        return;
    }
    printf("Playing\n");
}

void tuxm_stop(REALcontrolInstance ctl)
{
    ClassTuxPlayer* self = tux_getInstance(ctl);

    gst_element_set_state(self->playbin, GST_STATE_READY);

    printf("Stoped\n");
}

void tuxm_pause(REALcontrolInstance ctl)
{
    ClassTuxPlayer* self = tux_getInstance(ctl);

    gst_element_set_state(self->playbin, GST_STATE_PAUSED);

    printf("Paused\n");
}
