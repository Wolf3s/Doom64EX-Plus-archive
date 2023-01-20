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
//
// Definitions for use in the dehacked code
//

#ifndef DEH_DEFS_H
#define DEH_DEFS_H

#include "i_w3swrapper.h"
#include "sha1.h"

typedef enum
{
    DEH_INPUT_FILE,
    DEH_INPUT_LUMP
} deh_input_type_t;

typedef struct deh_context_s
{
    deh_input_type_t type;
    char* filename;

    // If the input comes from a memory buffer, pointer to the memory
    // buffer.
    unsigned char* input_buffer;
    size_t input_buffer_len;
    unsigned int input_buffer_pos;
    int lumpnum;

    // If the input comes from a file, the file stream for reading
    // data.
    FILE* stream;

    // Current line number that we have reached:
    int linenum;

    // Used by DEH_ReadLine:
    boolean last_was_newline;
    char* readbuffer;
    int readbuffer_size;

    // Error handling.
    boolean had_error;
} deh_context_t;

typedef void (*deh_section_init_t)(void);
typedef void* (*deh_section_start_t)(deh_context_t* context, char* line);
typedef void (*deh_section_end_t)(deh_context_t* context, void* tag);
typedef void (*deh_line_parser_t)(deh_context_t* context, char* line, void* tag);
typedef void (*deh_sha1_hash_t)(sha1_context_t* context);

typedef struct deh_section_s
{
    char *name;

    // Called on startup to initialize code

    deh_section_init_t init;
    
    // This is called when a new section is started.  The pointer
    // returned is used as a tag for the following calls.

    deh_section_start_t start;

    // This is called for each line in the section

    deh_line_parser_t line_parser;

    // This is called at the end of the section for any cleanup

    deh_section_end_t end;

    // Called when generating an SHA1 sum of the dehacked state

    deh_sha1_hash_t sha1_hash;
} deh_section_t;



#endif /* #ifndef DEH_DEFS_H */

