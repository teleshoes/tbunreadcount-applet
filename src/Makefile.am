INCLUDES=-I. -I$(srcdir) \
	$(GNOME_APPLETS_CFLAGS) \
	-DGNOMEICONDIR=\""$(prefix)/share/pixmaps"\"
	-DGNOMELOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\"

bin_PROGRAMS=tbunreadcount-applet

tbunreadcount-applet_SOURCES=tbunreadcount-applet.c

tbunreadcount-applet_LDADD=$(GNOME_APPLETS_LIBS)
