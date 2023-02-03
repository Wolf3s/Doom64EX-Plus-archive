//
// Copyright(C) 2005-2014 Simon Howard
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
// DESCRIPTION:
//     Search for and locate an IWAD file, and initialize according
//     to the IWAD type.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "deh_str.h"
#include "i_system.h"
#include "m_misc.h"
#include "w_wad.h"
#include "z_zone.h"

// Array of locations to search for IWAD files
//
// "128 IWAD search directories should be enough for anybody".

#define MAX_IWAD_DIRS 128

static boolean iwad_dirs_built = false;
static char* iwad_dirs[MAX_IWAD_DIRS];
static int num_iwad_dirs = 0;

//
// Searches WAD search paths for an WAD with a specific filename.
// 

char* D_FindWADByName(char* name)
{
    char* path;
    char* probe;
    int i;

    // Absolute path?

    probe = (char*)M_FileExists(name);
    if (probe != NULL)
    {
        return probe;
    }

    // Search through all IWAD paths for a file with the given name.

    for (i = 0; i < num_iwad_dirs; ++i)
    {
        // As a special case, if this is in DOOMWADDIR or DOOMWADPATH,
        // the "directory" may actually refer directly to an IWAD
        // file.

        probe = (char*)M_FileExists(iwad_dirs[i]);
        //if (DirIsFile(iwad_dirs[i], name) && probe != NULL)
        {
            return probe;
        }

        // Construct a string for the full path

        //path = M_StringJoin(iwad_dirs[i], DIR_SEPARATOR, name, NULL);

        probe = (char*)M_FileExists(path);
        if (probe != NULL)
        {
            return probe;
        }

        free(path);
    }

    // File not found

    return NULL;
}

//
// D_TryWADByName
//
// Searches for a WAD by its filename, or passes through the filename
// if not found.
//

char* D_TryFindWADByName(char* filename)
{
    char* result;

    result = D_FindWADByName(filename);

    if (result != NULL)
    {
        return result;
    }
    else
    {
        return filename;
    }
}