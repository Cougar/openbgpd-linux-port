#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(Openbgp, 3.6, [http://www.openbsd.org/query-pr.html])
AM_INIT_AUTOMAKE(1.6)
## AC_CONFIG_SRCDIR([bgpctl/bgpctl.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
# AC_PROG_YACC
# ------------
AC_DEFUN([AC_PROG_YACC],
  [AC_CHECK_PROGS(YACC, yacc)])
AC_PROG_YACC
AC_PROG_RANLIB

case "$host" in
    *-linux*)
	opsys=gnu-linux
	AC_DEFINE(GNU_LINUX,,GNU Linux)
    ;;
esac

CFLAGS="-O2 -Wall" 

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h limits.h netdb.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/param.h sys/socket.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_TYPE_SIGNAL
AC_FUNC_STRFTIME
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([bzero endpwent inet_ntoa memmove memset socket strcasecmp strchr strdup strerror strrchr strtol strtoul tzset])

AC_DEFINE(__need_IOV_MAX, [], [Needed to get IOV_MAX from stdio.h on Linux])

AC_CHECK_HEADERS(arpa/inet.h ctype.h ifaddrs.h netdb.h paths.h stdarg.h \
        sys/bitypes.h sys/fcntl.h sys/queue.h sys/time.h sys/socket.h \
        sys/timex.h sys/types.h syslog.h)

AC_CHECK_DECLS(asprintf, ,
        [saved_CFLAGS="$CFLAGS"
         CFLAGS="$CFLAGS -D_GNU_SOURCE"
         unset ac_cv_have_decl_asprintf
         AC_CHECK_DECLS(asprintf, , CFLAGS="$saved_CFLAGS")
        ]
)

AC_CHECK_FUNCS(socketpair, ,
        [saved_LDFLAGS="$LDFLAGS"
         LDFLAGS="$LDFLAGS -lsocket -lnsl"
         unset ac_cv_func_socketpair
         AC_CHECK_FUNCS(socketpair, , LDFLAGS="$saved_LDFLAGS")
        ]
)

AC_CHECK_FUNCS(adjtimex arc4random asprintf bzero clock_getres daemon \
        getifaddrs inet_pton setproctitle snprintf strlcpy vsnprintf vsyslog)

dnl Check for uidswap functions
AC_CHECK_FUNCS(setuid setgid seteuid setegid setreuid setregid \
    setresuid setresgid)

dnl Check for getaddrinfo and friends.
AC_CHECK_FUNCS(getaddrinfo getnameinfo freeaddrinfo)

dnl IRIX has a const char return value for gai_strerror()
AC_CHECK_FUNCS(gai_strerror,[
        AC_DEFINE(HAVE_GAI_STRERROR)
        AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

const char *gai_strerror(int);],[
char *str;

str = gai_strerror(0);],[
                AC_DEFINE(HAVE_CONST_GAI_STRERROR_PROTO, 1,
                [Define if gai_strerror() returns const char *])])])

AC_CACHE_CHECK([for struct sockaddr_storage], ac_cv_have_struct_sockaddr_storage, [
        AC_TRY_COMPILE(
                [
#include <sys/types.h>
#include <sys/socket.h>
                ],
                [ struct sockaddr_storage s; ],
                [ ac_cv_have_struct_sockaddr_storage="yes" ],
                [ ac_cv_have_struct_sockaddr_storage="no" ]
        )
])
if test "x$ac_cv_have_struct_sockaddr_storage" = "xyes" ; then
        AC_DEFINE(HAVE_STRUCT_SOCKADDR_STORAGE, [], [Have struct sockaddr_storage])
fi

AC_CACHE_CHECK([for struct sockaddr_in6], ac_cv_have_struct_sockaddr_in6, [
        AC_TRY_COMPILE(
                [
#include <sys/types.h>
#include <netinet/in.h>
                ],
                [ struct sockaddr_in6 s; s.sin6_family = 0; ],
                [ ac_cv_have_struct_sockaddr_in6="yes" ],
                [ ac_cv_have_struct_sockaddr_in6="no" ]
        )
])
if test "x$ac_cv_have_struct_sockaddr_in6" = "xyes" ; then
        AC_DEFINE(HAVE_STRUCT_SOCKADDR_IN6, [], [Have struct sockaddr_in6])
fi

AC_CACHE_CHECK([for struct in6_addr], ac_cv_have_struct_in6_addr, [
        AC_TRY_COMPILE(
                [
#include <sys/types.h>
#include <netinet/in.h>
                ],
                [ struct in6_addr s; s.s6_addr[0] = 0; ],
                [ ac_cv_have_struct_in6_addr="yes" ],
                [ ac_cv_have_struct_in6_addr="no" ]
        )
])
if test "x$ac_cv_have_struct_in6_addr" = "xyes" ; then
        AC_DEFINE(HAVE_STRUCT_IN6_ADDR, [], [Have struct in6_addr])
fi

AC_CACHE_CHECK([for struct addrinfo], ac_cv_have_struct_addrinfo, [
        AC_TRY_COMPILE(
                [
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
                ],
                [ struct addrinfo s; s.ai_flags = AI_PASSIVE; ],
                [ ac_cv_have_struct_addrinfo="yes" ],
                [ ac_cv_have_struct_addrinfo="no" ]
        )
])
if test "x$ac_cv_have_struct_addrinfo" = "xyes" ; then
        AC_DEFINE(HAVE_STRUCT_ADDRINFO, [], [Have struct addrinfo])
fi



AC_SEARCH_LIBS(res_init, resolv)
AC_SEARCH_LIBS(res_9_init, resolv)

AC_CHECK_MEMBERS([struct sockaddr.sa_len,  struct sockaddr_in.sin_len,
        struct sockaddr_in6.sin6_len, struct sockaddr_in6.sin6_scope_id,
        struct sockaddr_storage.ss_family,
        struct sockaddr_storage.__ss_family], , ,
        [#include <sys/types.h>
         #include <sys/socket.h>
         #include <netinet/in.h>
         #include <netdb.h>]
)

AC_CACHE_CHECK([if libc defines __progname], ac_cv_libc_defines___progname, [
        AC_TRY_LINK([],
                [ extern char *__progname; printf("%s", __progname); ],
                [ ac_cv_libc_defines___progname="yes" ],
                [ ac_cv_libc_defines___progname="no" ]
        )
])
if test "x$ac_cv_libc_defines___progname" = "xyes" ; then
        AC_DEFINE(HAVE___PROGNAME, [], [libc defines __progname])
fi

dnl Does not support catman yet
mansubdir=man
AC_SUBST(mansubdir)

# Checks for data types
AC_CHECK_SIZEOF(char, 1)
AC_CHECK_SIZEOF(short int, 2)
AC_CHECK_SIZEOF(int, 4)
AC_CHECK_SIZEOF(long int, 4)
AC_CHECK_SIZEOF(long long int, 8)

# Sanity check long long for some platforms (AIX)
if test "x$ac_cv_sizeof_long_long_int" = "x4" ; then
        ac_cv_sizeof_long_long_int=0
fi

# More checks for data types
AC_CACHE_CHECK([for u_int type], ac_cv_have_u_int, [
        AC_TRY_COMPILE(
                [ #include <sys/types.h> ],
                [ u_int a; a = 1;],
                [ ac_cv_have_u_int="yes" ],
                [ ac_cv_have_u_int="no" ]
        )
])
if test "x$ac_cv_have_u_int" = "xyes" ; then
        AC_DEFINE(HAVE_U_INT, [], [Have u_int])
        have_u_int=1
fi

AC_CACHE_CHECK([for intXX_t types], ac_cv_have_intxx_t, [
        AC_TRY_COMPILE(
                [ #include <sys/types.h> ],
                [ int8_t a; int16_t b; int32_t c; a = b = c = 1;],
                [ ac_cv_have_intxx_t="yes" ],
                [ ac_cv_have_intxx_t="no" ]
        )
])
if test "x$ac_cv_have_intxx_t" = "xyes" ; then
        AC_DEFINE(HAVE_INTXX_T, [], [Have intXX_t types])
        have_intxx_t=1
fi

if (test -z "$have_intxx_t" && \
           test "x$ac_cv_header_stdint_h" = "xyes")
then
    AC_MSG_CHECKING([for intXX_t types in stdint.h])
        AC_TRY_COMPILE(
                [ #include <stdint.h> ],
                [ int8_t a; int16_t b; int32_t c; a = b = c = 1;],
                [
                        AC_DEFINE(HAVE_INTXX_T, [], [Have intXX_t types])
                        AC_MSG_RESULT(yes)
                ],
                [ AC_MSG_RESULT(no) ]
        )
fi

AC_CACHE_CHECK([for int64_t type], ac_cv_have_int64_t, [
        AC_TRY_COMPILE(
                [
#include <sys/types.h>
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif
#include <sys/socket.h>
#ifdef HAVE_SYS_BITYPES_H
# include <sys/bitypes.h>
#endif
                ],
                [ int64_t a; a = 1;],
                [ ac_cv_have_int64_t="yes" ],
                [ ac_cv_have_int64_t="no" ]
        )
])
if test "x$ac_cv_have_int64_t" = "xyes" ; then
        AC_DEFINE(HAVE_INT64_T, [], [Have int64_t type])
fi

AC_CACHE_CHECK([for u_intXX_t types], ac_cv_have_u_intxx_t, [
        AC_TRY_COMPILE(
                [ #include <sys/types.h> ],
                [ u_int8_t a; u_int16_t b; u_int32_t c; a = b = c = 1;],
                [ ac_cv_have_u_intxx_t="yes" ],
                [ ac_cv_have_u_intxx_t="no" ]
        )
])
if test "x$ac_cv_have_u_intxx_t" = "xyes" ; then
        AC_DEFINE(HAVE_U_INTXX_T, [], [Have u_intXX_t types])
        have_u_intxx_t=1
fi

if test -z "$have_u_intxx_t" ; then
    AC_MSG_CHECKING([for u_intXX_t types in sys/socket.h])
        AC_TRY_COMPILE(
                [ #include <sys/socket.h> ],
                [ u_int8_t a; u_int16_t b; u_int32_t c; a = b = c = 1;],
                [
                        AC_DEFINE(HAVE_U_INTXX_T, [], [Have u_intXX_t])
                        AC_MSG_RESULT(yes)
                ],
                [ AC_MSG_RESULT(no) ]
        )
fi

AC_CACHE_CHECK([for u_int64_t types], ac_cv_have_u_int64_t, [
        AC_TRY_COMPILE(
                [ #include <sys/types.h> ],
                [ u_int64_t a; a = 1;],
                [ ac_cv_have_u_int64_t="yes" ],
                [ ac_cv_have_u_int64_t="no" ]
        )
])
if test "x$ac_cv_have_u_int64_t" = "xyes" ; then
        AC_DEFINE(HAVE_U_INT64_T, [], [Have u_int64_t])
        have_u_int64_t=1
fi

if test -z "$have_u_int64_t" ; then
    AC_MSG_CHECKING([for u_int64_t type in sys/bitypes.h])
        AC_TRY_COMPILE(
                [ #include <sys/bitypes.h> ],
                [ u_int64_t a; a = 1],
                [
                        AC_DEFINE(HAVE_U_INT64_T, [], [Have u_int64_t])
                        AC_MSG_RESULT(yes)
                ],
                [ AC_MSG_RESULT(no) ]
        )
fi

if test -z "$have_u_intxx_t" ; then
        AC_CACHE_CHECK([for uintXX_t types], ac_cv_have_uintxx_t, [
                AC_TRY_COMPILE(
                        [
#include <sys/types.h>
                        ],
                        [ uint8_t a; uint16_t b; uint32_t c; a = b = c = 1; ],
                        [ ac_cv_have_uintxx_t="yes" ],
                        [ ac_cv_have_uintxx_t="no" ]
                )
        ])
        if test "x$ac_cv_have_uintxx_t" = "xyes" ; then
                AC_DEFINE(HAVE_UINTXX_T, [], [Have uintXX_t types])
        fi
fi

if test -z "$have_uintxx_t" ; then
    AC_MSG_CHECKING([for uintXX_t types in stdint.h])
        AC_TRY_COMPILE(
                [ #include <stdint.h> ],
                [ uint8_t a; uint16_t b; uint32_t c; a = b = c = 1;],
                [
                        AC_DEFINE(HAVE_UINTXX_T, [], [Have unitXX_t])
                        AC_MSG_RESULT(yes)
                ],
                [ AC_MSG_RESULT(no) ]
        )
fi

if (test -z "$have_u_intxx_t" || test -z "$have_intxx_t" && \
           test "x$ac_cv_header_sys_bitypes_h" = "xyes")
then
        AC_MSG_CHECKING([for intXX_t and u_intXX_t types in sys/bitypes.h])
        AC_TRY_COMPILE(
                [
#include <sys/bitypes.h>
                ],
                [
                        int8_t a; int16_t b; int32_t c;
                        u_int8_t e; u_int16_t f; u_int32_t g;
                        a = b = c = e = f = g = 1;
                ],
                [
                        AC_DEFINE(HAVE_U_INTXX_T, [], [Have u_intXX_t])
                        AC_DEFINE(HAVE_INTXX_T, [], [Have intXX_t])
                        AC_MSG_RESULT(yes)
                ],
                [AC_MSG_RESULT(no)]
        )
fi


AC_CACHE_CHECK([for u_char], ac_cv_have_u_char, [
        AC_TRY_COMPILE(
                [
#include <sys/types.h>
                ],
                [ u_char foo; foo = 125; ],
                [ ac_cv_have_u_char="yes" ],
                [ ac_cv_have_u_char="no" ]
        )
])
if test "x$ac_cv_have_u_char" = "xyes" ; then
        AC_DEFINE(HAVE_U_CHAR, [], [Have u_char type])
fi

AC_CHECK_TYPES(sig_atomic_t,,,[#include <signal.h>])

AC_CHECK_TYPES(socklen_t,,,[
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
])
# AC_CONFIG_FILES([openbsd-compat/Makefile])

AC_CONFIG_FILES([Makefile
		 openbsd-compat/Makefile
		 bgpctl/Makefile
                 bgpd/Makefile])
AC_OUTPUT
