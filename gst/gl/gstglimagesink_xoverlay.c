
#include <gst/interfaces/xoverlay.h>
#include "gstglimagesink.h"

static void gst_glimage_sink_xoverlay_init (GstXOverlayClass * iface);
static void gst_glimage_sink_set_window_handle (GstXOverlay * overlay,
    guintptr id);
static void gst_glimage_sink_expose (GstXOverlay * overlay);

static void gst_glimage_sink_add_display_interface_static(GType type) {

  static const GInterfaceInfo xoverlay_info = {
    (GInterfaceInitFunc) gst_glimage_sink_xoverlay_init,
    NULL,
    NULL,
  };

  g_type_add_interface_static (type, GST_TYPE_X_OVERLAY, &xoverlay_info);
}

void gst_glimage_sink_prepare_window_id(GstGLImageSink *glimage_sink) {
  gst_x_overlay_prepare_xwindow_id (GST_X_OVERLAY (glimage_sink));
}

static void
gst_glimage_sink_xoverlay_init (GstXOverlayClass * iface)
{
  iface->set_window_handle = gst_glimage_sink_set_window_handle;
  iface->expose = gst_glimage_sink_expose;
}


static void
gst_glimage_sink_set_window_handle (GstXOverlay * overlay, guintptr id)
{
  GstGLImageSink *glimage_sink = GST_GLIMAGE_SINK (overlay);
  gulong window_id = (gulong) id;

  g_return_if_fail (GST_IS_GLIMAGE_SINK (overlay));

  GST_DEBUG ("set_xwindow_id %ld", window_id);

  glimage_sink->new_window_id = window_id;
}


static void
gst_glimage_sink_expose (GstXOverlay * overlay)
{
  GstGLImageSink *glimage_sink = GST_GLIMAGE_SINK (overlay);

  //redisplay opengl scene
  if (glimage_sink->display && glimage_sink->window_id) {

    if (glimage_sink->window_id != glimage_sink->new_window_id) {
      glimage_sink->window_id = glimage_sink->new_window_id;
      gst_gl_display_set_window_id (glimage_sink->display,
          glimage_sink->window_id);
    }

    gst_gl_display_redisplay (glimage_sink->display, 0, 0, 0, 0, 0,
        glimage_sink->keep_aspect_ratio);
  }
}

static gooblean
gst_glimage_sink_display_interface_supported(GstImplementsInterface * iface,
    GType type) {
  return type == GST_TYPE_X_OVERLAY ? TRUE : FALSE;
}
