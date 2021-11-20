#include <stdio.h>
#include <stdlib.h>

#include <cairo.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gst/video/videooverlay.h>

#include "XojoGraphics.h"
#include "behaviour.h"
#include "tuxplayer.h"

// used to draw player interface when is not playing
bool player_expose_event(GtkWidget* widget, GdkEventExpose* event, ClassTuxPlayer* self)
{
    if(self->curState < GST_STATE_PAUSED) {
        GtkAllocation allocation;
        gtk_widget_get_allocation(widget, &allocation);

        cairo_t* cr = gdk_cairo_create(gtk_widget_get_window(widget));

        int color = 0x607D8B;

        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;

        cairo_set_source_rgb(cr, r / 0xFF, g / 0xFF, b / 0xFF);
        cairo_rectangle(cr, 0, 0, allocation.width, allocation.height);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_stroke(cr);
    }

    return FALSE;
}

void playbin_error(GstBus* bus, GstMessage* msg, ClassTuxPlayer* self)
{
    printf("playbin_error\n");

    GError* err;
    gchar* debug_info;

    /* Print error details on the screen */
    gst_message_parse_error(msg, &err, &debug_info);
    g_printerr("%s Error:\n %s\n", GST_OBJECT_NAME(msg->src), err->message);
    g_printerr("\n");
    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
    g_printerr("\n");
    g_clear_error(&err);
    g_free(debug_info);

    /* Set the pipeline to READY (which stops playback) */
    gst_element_set_state(self->playbin, GST_STATE_READY);
}

void playbin_eos(GstBus* bus, GstMessage* msg, ClassTuxPlayer* self)
{
    printf("playbin_eos\n");
}

void playbin_state_changed(GstBus* bus, GstMessage* msg, ClassTuxPlayer* self)
{
    printf("playbin_state_changed\n");

    GstState old_state, new_state, pending_state;
    gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
    if(GST_MESSAGE_SRC(msg) == GST_OBJECT(self->playbin)) {
        self->curState = new_state;
        g_print("State set to %s\n", gst_element_state_get_name(new_state));
        if(old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) {
            /* For extra responsiveness, we refresh the GUI as soon as we reach the PAUSED state */
            // refresh_ui(data);
        }
    }
}

void playbin_application(GstBus* bus, GstMessage* msg, ClassTuxPlayer* self)
{
    printf("playbin_application\n");
}

void Constructor(REALcontrolInstance ctl)
{
    ClassTuxPlayer* self = tux_getInstance(ctl);

    self->player = gtk_drawing_area_new();
    gtk_widget_set_double_buffered(self->player, FALSE);

    if(!REALinRuntime())
        return;

    g_signal_connect(self->player, "expose_event", G_CALLBACK(player_expose_event), self);

    gst_init(0, NULL);

    self->duration = GST_CLOCK_TIME_NONE;
    self->playbin = gst_element_factory_make("playbin", "playbin");
    if(!self->playbin) {
        REALobject exc = REALnewInstanceWithClass(REALGetClassRef("RuntimeException"));
        REALRaiseException(exc);
        REALUnlockObject(exc);
        return;
    }

    // GstElement* source;
    // GstElement* convert;
    // GstElement* sink;
}

void OnOpen(REALcontrolInstance ctl)
{
    if(!REALinRuntime())
        return;

    ClassTuxPlayer* self = tux_getInstance(ctl);

    GdkWindow* window = gtk_widget_get_window(self->player);
    if(!gdk_window_ensure_native(window)) {
        REALobject exc = REALnewInstanceWithClass(REALGetClassRef("RuntimeException"));
        REALRaiseException(exc);
        REALUnlockObject(exc);
        return;
    }

    // get window handle
    guintptr hwnd = GDK_WINDOW_XID(window);
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(self->playbin), hwnd);

    GstBus* bus = gst_element_get_bus(self->playbin);
    gst_bus_add_signal_watch(bus);
    g_signal_connect(G_OBJECT(bus), "message::error", G_CALLBACK(playbin_error), self);
    g_signal_connect(G_OBJECT(bus), "message::eos", G_CALLBACK(playbin_eos), self);
    g_signal_connect(G_OBJECT(bus), "message::state-changed", G_CALLBACK(playbin_state_changed), self);
    g_signal_connect(G_OBJECT(bus), "message::application", G_CALLBACK(playbin_application), self);
    gst_object_unref(bus);

    gst_element_set_state(self->playbin, GST_STATE_NULL);
}

void OnClose(REALcontrolInstance ctl)
{
}

void OnDrawOffscreen(REALcontrolInstance ctl, REALgraphics g)
{
    Rect r;
    REALGetControlBounds(ctl, &r);

    int width = r.right - r.left;
    int height = r.bottom - r.top;
    if(width <= 0 || height <= 0)
        return;

    graphics_SetForeColor(g, 0x607D8B);
    graphics_FillRect(g, r.left, r.top, width, height);
    graphics_SetForeColor(g, 0);
    graphics_DrawRect(g, r.left, r.top, width, height);
}

void* OnControlHandleGetter(REALcontrolInstance ctl)
{
    ClassTuxPlayer* data = tux_getInstance(ctl);
    return (void*)data->player;
}
