/* GStreamer EGL-based Overlay
 * Copyright (C) 2003 Ronald Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2003 Julien Moutte <julien@moutte.net>
 * Copyright (C) 2012 Andreas Bergmeier <andreas.bergmeier@gmegl.net>
 *
 * egl-overlay.h: EGL-based overlay interface design
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_EGL_OVERLAY_H__
#define __GST_EGL_OVERLAY_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_EGL_OVERLAY \
  (gst_egl_overlay_get_type ())
#define GST_EGL_OVERLAY(obj) \
  (GST_IMPLEMENTS_INTERFACE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_EGL_OVERLAY, \
                                                 GstEGLOverlay))
#define GST_EGL_OVERLAY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_EGL_OVERLAY, GstEGLOverlayClass))
#define GST_IS_EGL_OVERLAY(obj) \
  (GST_IMPLEMENTS_INTERFACE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_EGL_OVERLAY))
#define GST_IS_EGL_OVERLAY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_EGL_OVERLAY))
#define GST_EGL_OVERLAY_GET_CLASS(inst) \
  (G_TYPE_INSTANCE_GET_INTERFACE ((inst), GST_TYPE_EGL_OVERLAY, GstEGLOverlayClass))

/**
 * GstEGLOverlay:
 *
 * Opaque #GstEGLOverlay data structure.
 */
typedef struct _GstEGLOverlay GstEGLOverlay;
typedef struct _GstEGLOverlayClass GstEGLOverlayClass;

/**
 * GstEGLOverlayClass:
 * @klass: parent interface type.
 * @expose: virtual method to handle expose events
 * @handle_events: virtual method to handle events
 * @set_render_rectangle: virtual method to set the render rectangle (since 0.10.29)
 * @set_window_handle: virtual method to configure the window handle
 *
 * #GstEGLOverlay interface
 */
struct _GstEGLOverlayClass {
  GTypeInterface klass;

  void (* expose)              (GstEGLOverlay *overlay);

  void (* handle_events)       (GstEGLOverlay *overlay,
                                gboolean     handle_events);

  void (* set_render_rectangle) (GstEGLOverlay *overlay,
                                 gint x, gint y,
                                 gint width, gint height);

  void (* set_window_handle)   (GstEGLOverlay *overlay,
                                guintptr    handle);
    /*< private >*/
  gpointer                 _gst_reserved[GST_PADDING - 3];
};

GType   gst_egl_overlay_get_type          (void);

gboolean gst_egl_overlay_set_render_rectangle (GstEGLOverlay *overlay,
                                             gint x, gint y,
                                             gint width, gint height);

void gst_egl_overlay_expose              (GstEGLOverlay *overlay);

void gst_egl_overlay_handle_events       (GstEGLOverlay *overlay,
                                        gboolean     handle_events);

void gst_egl_overlay_set_window_handle   (GstEGLOverlay *overlay,
                                        guintptr handle);

void gst_egl_overlay_got_window_handle  (GstEGLOverlay *overlay,
    guintptr handle);

void gst_egl_overlay_prepare_window_id (GstEGLOverlay *overlay);

G_END_DECLS

#endif /* __GST_EGL_OVERLAY_H__ */
