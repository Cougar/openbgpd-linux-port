INCLUDES = -I. -I.. -I$(top_srcdir) -I$(top_srcdir)/openbsd-compat
bin_PROGRAMS = bgpd
bgpd_SOURCES = bgpd.c buffer.c session.c log.c parse.y config.c imsg.c \
	       rde.c rde_rib.c rde_decide.c rde_prefix.c mrt.c \
	       control.c rde_update.c rde_attr.c printconf.c \
	       rde_filter.c kroute.c
bgpd_LDADD = ../openbsd-compat/libopenbsdcompat.a -lresolv
