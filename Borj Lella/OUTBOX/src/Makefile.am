## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = outbox

outbox_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	ouvrier.c ouvrier.h \
	employee.c employee.h \
	gestion_clients.h gestion_clients.c \
	equipements.c equipements.h \
	entretiens.c entretiens.h \
	authentification.c authentification.h

outbox_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

