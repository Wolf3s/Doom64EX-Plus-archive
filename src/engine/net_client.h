// Emacs style mode select   -*- C -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2005 Simon Howard
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
// Network client code
//
//------------------------------------------------------------------------------

#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include "doomdef.h"
#include "doomtype.h"
#include "d_ticcmd.h"
#include "md5.h"
#include "net_defs.h"

#define MAXPLAYERNAME 30

dboolean NET_CL_Connect(net_addr_t* addr);
void NET_CL_Disconnect(void);
void NET_CL_Run(void);
void NET_CL_Init(void);
void NET_CL_StartGame(void);
void NET_CL_SendTiccmd(ticcmd_t* ticcmd, int maketic);
void NET_Init(void);
void NET_CL_SendCheat(int player, int type, char* buff);

extern dboolean net_client_connected;
extern dboolean net_client_received_wait_data;
extern dboolean net_client_controller;
extern uint32_t net_clients_in_game;
extern uint32_t net_drones_in_game;
extern dboolean net_waiting_for_start;
extern char net_player_names[MAXPLAYERS][MAXPLAYERNAME];
extern char net_player_addresses[MAXPLAYERS][MAXPLAYERNAME];
extern int net_player_number;
extern char* net_player_name;

extern md5_digest_t net_server_wad_md5sum;
extern md5_digest_t net_local_wad_md5sum;

#endif /* #ifndef NET_CLIENT_H */
