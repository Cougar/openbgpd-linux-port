/*
 * $Id: uidswap.c,v 1.3 2004/07/13 10:07:48 dtucker Exp $
 * stripped-down uidswap.c from OpenSSH Portable 1.44
 */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 * Code for uid-swapping.
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#include "openbsd-compat.h"
/* $OpenBSD: uidswap.c,v 1.24 2003/05/29 16:58:45 deraadt Exp $ */

#include <sys/types.h>
#include <unistd.h>
#include "bgpd.h"	/* for fatal */

/*
 * Permanently sets all uids to the given uid.
 */
int
permanently_set_uid(struct passwd *pw)
{
	uid_t old_uid = getuid();
	gid_t old_gid = getgid();

#if defined(HAVE_SETRESGID) && !defined(BROKEN_SETRESGID)
	if (setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) < 0)
		fatal("setresgid failed");
#elif defined(HAVE_SETREGID) && !defined(BROKEN_SETREGID)
	if (setregid(pw->pw_gid, pw->pw_gid) < 0)
		fatal("setregid failed");
#else
	if (setegid(pw->pw_gid) < 0)
		fatal("setegid failed");
	if (setgid(pw->pw_gid) < 0)
		fatal("setgid failed");
#endif

#if defined(HAVE_SETRESUID) && !defined(BROKEN_SETRESUID)
	if (setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) < 0)
		fatal("setresuid failed");
#elif defined(HAVE_SETREUID) && !defined(BROKEN_SETREUID)
	if (setreuid(pw->pw_uid, pw->pw_uid) < 0)
		fatal("setreuid failed");
#else
# ifndef SETEUID_BREAKS_SETUID
	if (seteuid(pw->pw_uid) < 0)
		fatal("seteuid failed");
# endif
	if (setuid(pw->pw_uid) < 0)
		fatal("setuid failed");
#endif

	/* Try restoration of GID if changed (test clearing of saved gid) */
	if (old_gid != pw->pw_gid &&
	    (setgid(old_gid) != -1 || setegid(old_gid) != -1))
		fatal("was able to restore old [e]gid");

	/* Verify GID drop was successful */
	if (getgid() != pw->pw_gid || getegid() != pw->pw_gid)
		fatal("egid incorrect");

#ifndef HAVE_CYGWIN
	/* Try restoration of UID if changed (test clearing of saved uid) */
	if (old_uid != pw->pw_uid &&
	    (setuid(old_uid) != -1 || seteuid(old_uid) != -1))
		fatal("was able to restore old [e]uid");
#endif

	/* Verify UID drop was successful */
	if (getuid() != pw->pw_uid || geteuid() != pw->pw_uid)
		fatal("euid incorrect");

	return 1;
}
