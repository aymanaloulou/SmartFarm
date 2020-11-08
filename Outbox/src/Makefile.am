## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = finalproject

finalproject_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	login.c login.h\
	espace_employee.c espace_employee.h \
	gestion_capteur.c gestion_capteur.h\
	gestion_equip.c gestion_equip.h\
	gestion_client.c gestion_client.h\
	gestion_troup.c gestion_troup.h\
	gestion_ouvrier.c gestion_ouvrier.h\
	gestion_plant.c gestion_plant.h \
	gestion_employee.c gestion_employee.h \
	admin.c admin.h\
	dashboard.c dashboard.h 

finalproject_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

