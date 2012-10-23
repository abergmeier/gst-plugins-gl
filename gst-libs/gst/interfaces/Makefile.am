
lib_LTLIBRARIES = libeglinterfaces-@GST_MAJORMINOR@.la

libeglinterfaces_@GST_MAJORMINOR@_la_SOURCES = \
	egloverlay.c

libeglinterfaces_@GST_MAJORMINOR@includedir = $(includedir)/gstreamer-@GST_MAJORMINOR@/gst/interfaces
libeglinterfaces_@GST_MAJORMINOR@include_HEADERS = \
	egloverlay.h

#libeglinterfaces_@GST_MAJORMINOR@_la_LIBADD = \
#	$(GST_PLUGINS_BASE_LIBS) -lgstvideo-$(GST_MAJORMINOR) -lgstcontroller-$(GST_MAJORMINOR) \
#	$(GST_BASE_LIBS) $(GST_LIBS) \
#	$(GL_LIBS)

libeglinterfaces_@GST_MAJORMINOR@_la_CFLAGS = \
	$(GL_CFLAGS) $(X_CFLAGS) \
	$(GST_PLUGINS_BASE_CFLAGS) $(GST_BASE_CFLAGS) $(GST_CFLAGS)
libeglinterfaces_@GST_MAJORMINOR@_la_OBJCFLAGS = \
	$(GL_CFLAGS) $(X_CFLAGS) \
	$(GST_PLUGINS_BASE_CFLAGS) $(GST_BASE_CFLAGS) $(GST_CFLAGS)

libeglinterfaces_@GST_MAJORMINOR@_la_LDFLAGS = \
	$(GST_LIB_LDFLAGS) $(GST_ALL_LDFLAGS) $(GST_LT_LDFLAGS)

libeglinterfaces_@GST_MAJORMINOR@_la_LIBTOOLFLAGS = --tag=CC

