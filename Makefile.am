SUBDIRS=src

serverdir	= $(libdir)/bonobo/servers
server_in_files	= TBUnreadCountApplet_Factory.server.in
server_DATA	= $(server_in_files:.server.in=.server)
$(server_DATA):	$(server_in_files)
	sed -e "s|\@BINDIR\@|$(bindir)|" $< > $@

pixmapdir = $(datadir)/pixmaps
pixmap_DATA = myicon.svg

EXTRA_DIST = \
	$(pixmap_DATA) \
	TBUnreadCountApplet_Factory.server.in
