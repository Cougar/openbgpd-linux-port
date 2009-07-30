INCLUDES = -I. -I.. -I$(top_srcdir) -I$(top_srcdir)/openbsd-compat \
	   -I$(top_srcdir)/bgpd
bin_PROGRAMS = bgpctl
bgpctl_SOURCES = bgpctl.c parser.c buffer.c imsg.c log.c util.c \
                 irrfilter.c whois.c irr_asset.c irr_prefix.c irr_output.c \
                 irr_parser.c timer.c
bgpctl_LDADD = ../openbsd-compat/libopenbsdcompat.a -lresolv -lrt
