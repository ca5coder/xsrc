/* $OpenBSD: wsfb_driver.c,v 1.18 2003/04/02 16:42:13 jason Exp $ */
/*
 * Copyright (c) 2001 Matthieu Herrb
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Based on fbdev.c written by:
 *
 * Authors:  Alan Hourihane, <alanh@fairlite.demon.co.uk>
 *	     Michel Dänzer, <michdaen@iiic.ethz.ch>
 */
 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <dev/wscons/wsconsio.h>

#include "xorgVersion.h"

#include "compat-api.h"

#include "xf86.h"
#include "xf86_OSproc.h"

#if ABI_VIDEODRV_VERSION < SET_ABI_VERSION(25, 2)
#include "xf86RamDac.h"
#else
#include "xf86Cursor.h"
#endif

#ifndef WSFB_H
#define WSFB_H

#if XORG_VERSION_CURRENT >= XORG_VERSION_NUMERIC(1,14,99,2,0)
#define HAVE_SHADOW_AFB
#endif

/* private data */
typedef struct {
	int			fd; /* file descriptor of open device */
	struct wsdisplayio_fbinfo fbi;
	unsigned char*		fbstart;
	unsigned char*		fbmem;
	size_t			fbmem_len;
	int			rotate;
	Bool			shadowFB;
	void *			shadow;
	Bool			HWCursor;
	Bool			useSwap32;
#ifdef HAVE_SHADOW_AFB
	Bool			planarAfb;
#endif
	CloseScreenProcPtr	CloseScreen;
	CreateScreenResourcesProcPtr CreateScreenResources;
	void                    (*PointerMoved)(SCRN_ARG_TYPE, int, int);
	EntityInfoPtr		pEnt;
	struct wsdisplay_cmap	saved_cmap;

	struct wsdisplay_cursor cursor;
	int			maskoffset;
	xf86CursorInfoPtr	CursorInfoRec;
#ifdef XFreeXDGA
	/* DGA info */
	DGAModePtr		pDGAMode;
	int			nDGAMode;
#endif
	OptionInfoPtr		Options;
} WsfbRec, *WsfbPtr;

#define WSFBPTR(p) ((WsfbPtr)((p)->driverPrivate))

Bool WsfbSetupCursor(ScreenPtr);

#endif
