
#include <gst/interfaces/egloverlay.h>
#include "gstglimagesink.h"

static void gst_glimage_sink_egloverlay_init (GstEGLOverlayClass * iface);
static void gst_glimage_sink_expose (GstEGLOverlay * overlay);

void gst_glimage_sink_add_display_interface_static(GType type) {
  static const GInterfaceInfo egloverlay_info = {
    (GInterfaceInitFunc) gst_glimage_sink_egloverlay_init,
    NULL,
    NULL,
  };
  g_type_add_interface_static (type, GST_TYPE_EGL_OVERLAY, &egloverlay_info);
}

void gst_glimage_sink_prepare_window_id(GstGLImageSink *glimage_sink) {
  gst_egl_overlay_prepare_window_id (GST_EGL_OVERLAY (glimage_sink));
}

static void
gst_glimage_sink_egloverlay_init (GstEGLOverlayClass * iface)
{
  iface->set_window_handle = gst_glimage_sink_set_window_handle;
  iface->expose = gst_glimage_sink_expose;
}

static void
gst_glimage_sink_expose (GstEGLOverlay * overlay)
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
  return type == GST_TYPE_EGL_OVERLAY ? TRUE : FALSE;
}
