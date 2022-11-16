// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2005 Simon Howard
// Copyright(C) 2007-2012 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
//-----------------------------------------------------------------------------

#ifndef __W_FILE__
#define __W_FILE__

#include <stdio.h>
#include "doomtype.h"

typedef struct _wad_file_s wad_file_t;

typedef struct {
	// Open a file for reading.

	wad_file_t* (*OpenFile)(int8_t* path);

	// Close the specified file.

	void (*CloseFile)(wad_file_t* file);

	// Read data from the specified position in the file into the
	// provided buffer.  Returns the number of bytes read.

	size_t(*Read)(wad_file_t* file, uint32_t offset,
		void* buffer, size_t buffer_len);
} wad_file_class_t;

struct _wad_file_s {
	// Class of this file.

	wad_file_class_t* file_class;

	// If this is NULL, the file cannot be mapped into memory.  If this
	// is non-NULL, it is a pointer to the mapped file.

	byte* mapped;

	// Length of the file, in bytes.

	intptr_t length;
};

// Open the specified file. Returns a pointer to a new wad_file_t
// handle for the WAD file, or NULL if it could not be opened.

wad_file_t* W_OpenFile(int8_t* path);

// Close the specified WAD file.

void W_CloseFile(wad_file_t* wad);

// Read data from the specified file into the provided buffer.  The
// data is read from the specified offset from the start of the file.
// Returns the number of bytes read.

size_t W_Read(wad_file_t* wad, uint32_t offset,
	void* buffer, size_t buffer_len);

int8_t* W_FindWADByName(int8_t* filename);
int8_t* W_TryFindWADByName(int8_t* filename);
int8_t* W_FindIWAD(void);

#endif /*__W_FILE__*/