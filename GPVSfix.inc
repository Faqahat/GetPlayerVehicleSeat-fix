/*
    GetPlayerVehicleSeat fix - Developed using Pawn.RakNet by Cycle.
*/

#if defined _GPVS_included
    #endinput
#endif
#define _GPVS_included

#if !defined PAWNRAKNET_INC_
    #error You must have Pawn.RakNet include in order to use this one.
#endif

#define INVALID_SEAT_ID (-1)

/* Variable */
static GPVS_PlayerSeat[MAX_PLAYERS char];

/* Function */
stock GetPlayerVehicleSeat(playerid){
    if(!IsPlayerConnected(playerid) || !IsPlayerInAnyVehicle(playerid))
        return INVALID_SEAT_ID;
    else 
    	return GPVS_PlayerSeat{playerid};
}

/* Callback */
public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
    if(packetid == 0xC8) 
    	GPVS_PlayerSeat{playerid} = 0;
    if(packetid == 0xD3)
    {
        BS_SetReadOffset(bs, 26);
        BS_ReadValue(
            bs,
            PR_BITS, GPVS_PlayerSeat{playerid}, 6
        );
        BS_ResetReadPointer(bs);
    }
    #if defined GPVS_OnIncomingPacket
        return GPVS_OnIncomingPacket(playerid, packetid, bs);
    #else
        return true;
    #endif
}

/* Hook */
/*----------------------------------------------*/
#if defined _ALS_OnIncomingPacket
    #undef OnIncomingPacket
#else
    #define _ALS_OnIncomingPacket
#endif
#define OnIncomingPacket GPVS_OnIncomingPacket

#if defined GPVS_OnIncomingPacket
	forward GPVS_OnIncomingPacket(playerid, packetid, BitStream:bs);
#endif
/*----------------------------------------------*/
#if defined _ALS_GetSeatingOrder
    #undef GetPlayerVehicleSeat
#else
    #define _ALS_GetSeatingOrder
#endif
#define GetPlayerVehicleSeat GPVS_GetPlayerVehicleSeat
