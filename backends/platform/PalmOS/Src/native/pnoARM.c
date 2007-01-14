/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2006 The ScummVM project
 * Copyright (C) 2002-2006 Chris Apers - PalmOS Backend
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifdef COMPILE_OS5

#include <PalmOS.h>
#include <stdlib.h>
#include "pace.h"

// Linker still looks for ARMlet_Main as entry point, but the
// "ARMlet" name is now officially discouraged.  Compare an
// contrast to "PilotMain" for 68K applications.
#define PNO_Main ARMlet_Main

/* Prepare static initializers */
extern long __sinit__[];
extern void __ARMlet_Startup__();

/* simple function pointer	*/
typedef void (*StaticInitializer)(void);

unsigned long PNO_Main(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP) {
	global.emulStateP = (EmulStateType *)emulStateP;
	global.call68KFuncP = call68KFuncP;

	// handle static initializers
	if (__sinit__) {
		long base = (long)__ARMlet_Startup__;
		long s, *p;

		for (p = __sinit__; p && (s = *p) != 0; p++)
			((StaticInitializer)(s + base))();
	}

	return PilotMain(sysAppLaunchCmdNormalLaunch, userData68KP, 0);
}

 //
 // The following functions provide malloc/free support to Metrowerks
 // Standard Library (MSL). This feature requires the MSL library be
 // built with _MSL_OS_DIRECT_MALLOC enabled.
 //
void*
__sys_alloc(UInt32 size)
{
    void * ptr = malloc(size);
    ErrFatalDisplayIf(ptr == NULL, "out of memory");
    return ptr;
}

void
__sys_free(void* ptr)
{
    (void) MemPtrFree(ptr);
}

UInt32
__sys_pointer_size(void* ptr)
{
    return (UInt32) MemPtrSize(ptr);
}

#endif
