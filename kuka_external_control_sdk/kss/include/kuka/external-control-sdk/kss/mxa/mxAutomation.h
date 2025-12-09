/******************************************************************************
;// This material is the exclusive property of KUKA Roboter GmbH.
;// Except as expressly permitted by separate agreement, this material may only
;// be used by members of the development department of KUKA Roboter GmbH for
;// internal development purposes of KUKA Roboter GmbH.
;//
;// Copyright (C) 2025
;// KUKA Roboter GmbH, Germany. All Rights Reserved.
;//
;// Native cpp extensions for the MxA library.
;// Function-Blocks and Functions, that are basic PLC IEC
;// are reimplemented here as direct cpp code
******************************************************************************/

// This is part of the official client library provided by KUKA for mxAutomation

#pragma once

#include "plciec.h"

typedef PLCIEC::REAL MXA_CMD_PAR_REAL[101];

typedef PLCIEC::DINT MXA_CMD_PAR_INT[51];

typedef PLCIEC::BOOL MXA_CMD_PAR_BOOL[51];

struct MXA_COMMAND
{
   PLCIEC::DINT COMMANDID;

   PLCIEC::DINT ORDERID;

   PLCIEC::DINT BUFFERMODE;

   PLCIEC::INT COMMANDSIZE;

   MXA_CMD_PAR_REAL CMDPARREAL;

   MXA_CMD_PAR_INT CMDPARINT;

   MXA_CMD_PAR_BOOL CMDPARBOOL;
};

struct MXA_CMD_STATE_RET
{
   PLCIEC::DINT SR_ORDERID;

   PLCIEC::INT SR_STATE;
};

typedef MXA_CMD_STATE_RET MXA_CMD_SR_ARR[11];

typedef PLCIEC::REAL MXA_CMD_DATA_RET[13];

struct MXA_COMMAND_STATUS
{
   PLCIEC::DINT CMDIDRET;

   PLCIEC::DINT ORDERIDRET;

   PLCIEC::INT TRANSMISSIONNORET;

   MXA_CMD_SR_ARR STATERETURN;

   MXA_CMD_DATA_RET CMDDATARETURN;

   PLCIEC::DINT CMDDATARETCSKRC;

   PLCIEC::DINT CMDDATARETCSPLC;
};

struct MXA_AUTEXT_CONTROL
{
   PLCIEC::BYTE PGNO;

   PLCIEC::BOOL PGNO_PARITY;

   PLCIEC::BOOL PGNO_VALID;

   PLCIEC::BOOL EXT_START;

   PLCIEC::BOOL MOVE_ENABLE;

   PLCIEC::BOOL MOVE_DISABLE;

   PLCIEC::BOOL CONF_MESS;

   PLCIEC::BOOL DRIVESON;

   PLCIEC::BOOL DRIVESOFF;

   PLCIEC::BOOL BRAKETEST_REQ_EXT;

   PLCIEC::BOOL MASTERINGTEST_REQ_EXT;
};

struct MXA_AUTEXT_STATE
{
   PLCIEC::BOOL RC_RDY1;

   PLCIEC::BOOL ALARM_STOP;

   PLCIEC::BOOL USER_SAFE;

   PLCIEC::BOOL PERI_RDY;

   PLCIEC::BOOL ROB_CAL;

   PLCIEC::BOOL IO_ACTCONF;

   PLCIEC::BOOL STOPMESS;

   PLCIEC::BOOL PGNO_FBIT_REFL;

   PLCIEC::BOOL INTNOTAUS;

   PLCIEC::BOOL PRO_ACT;

   PLCIEC::BOOL PGNO_REQ;

   PLCIEC::BOOL APPL_RUN;

   PLCIEC::BOOL PRO_MOVE;

   PLCIEC::BOOL IN_HOME;

   PLCIEC::BOOL ON_PATH;

   PLCIEC::BOOL NEAR_POSRET;

   PLCIEC::BOOL ROB_STOPPED;

   PLCIEC::BOOL T1;

   PLCIEC::BOOL T2;

   PLCIEC::BOOL AUT;

   PLCIEC::BOOL EXT;

   PLCIEC::BOOL KCP_CONNECT;

   PLCIEC::BOOL BRAKETEST_MONTIME;

   PLCIEC::BOOL BRAKETEST_REQ_INT;

   PLCIEC::BOOL BRAKETEST_WORK;

   PLCIEC::BOOL BRAKES_OK;

   PLCIEC::BOOL BRAKETEST_WARN;

   PLCIEC::BOOL MASTERINGTEST_REQ_INT;

   PLCIEC::BOOL MASTERINGTESTSWITCH_OK;
};

struct E6POS
{
   PLCIEC::REAL X;

   PLCIEC::REAL Y;

   PLCIEC::REAL Z;

   PLCIEC::REAL A;

   PLCIEC::REAL B;

   PLCIEC::REAL C;

   PLCIEC::INT STATUS;

   PLCIEC::INT TURN;

   PLCIEC::REAL E1;

   PLCIEC::REAL E2;

   PLCIEC::REAL E3;

   PLCIEC::REAL E4;

   PLCIEC::REAL E5;

   PLCIEC::REAL E6;
};

struct E6AXIS
{
   PLCIEC::REAL A1;

   PLCIEC::REAL A2;

   PLCIEC::REAL A3;

   PLCIEC::REAL A4;

   PLCIEC::REAL A5;

   PLCIEC::REAL A6;

   PLCIEC::REAL E1;

   PLCIEC::REAL E2;

   PLCIEC::REAL E3;

   PLCIEC::REAL E4;

   PLCIEC::REAL E5;

   PLCIEC::REAL E6;
};

typedef PLCIEC::INT MXA_IR_STATE[9];

struct MXA_KRC_STATE
{
   E6POS POSACT;

   PLCIEC::INT TOOLACT;

   PLCIEC::INT BASEACT;

   PLCIEC::INT IPOMODEACT;

   PLCIEC::BOOL POSACTVALID;

   E6AXIS AXISACT;

   PLCIEC::BOOL AXISACTVALID;

   PLCIEC::INT OVPROACT;

   PLCIEC::REAL VELACT;

   PLCIEC::BOOL BRAKEACTIVE;

   PLCIEC::INT WORKSTATES;

   PLCIEC::INT AXWORKSTATES;

   PLCIEC::INT GROUPSTATE;

   PLCIEC::DINT ERRORID;

   PLCIEC::DINT ERRORIDSUB;

   PLCIEC::DINT ERRORIDPCOS;

   PLCIEC::DINT ACTIVEPOSORDERID;

   PLCIEC::DINT ACTIVEORDERIDB;

   PLCIEC::INT HEARTBEAT;

   PLCIEC::INT HEARTBEATPCOS;

   MXA_IR_STATE INTERRUPTSTATE;

   PLCIEC::INT QUEUECOUNT;

   PLCIEC::BOOL TOUCHUP;

   PLCIEC::INT TOUCHUP_INDEX;

   PLCIEC::INT IN_VAL_1TO8;

   PLCIEC::BOOL ABORTACTIVE;
};

struct MXA_JOGADVANCED
{
   PLCIEC::BOOL JOG_AD_ACTIVE;

   PLCIEC::INT JOG_AD_STATE_VAL;
};

struct MXA_KRC_CONTROL
{
   PLCIEC::BOOL RESET;

   PLCIEC::INT OVERRIDE;

   PLCIEC::BOOL BRAKE;

   PLCIEC::BOOL BRAKEF;

   PLCIEC::BOOL RELEASEBRAKE;

   PLCIEC::BOOL SHOWTRACE;

   PLCIEC::BOOL MESSAGERESET;

   PLCIEC::BOOL OUT_VAL_1;

   PLCIEC::BOOL OUT_VAL_2;

   PLCIEC::BOOL OUT_VAL_3;

   PLCIEC::BOOL OUT_VAL_4;

   PLCIEC::BOOL OUT_VAL_5;

   PLCIEC::BOOL OUT_VAL_6;

   PLCIEC::BOOL OUT_VAL_7;

   PLCIEC::BOOL OUT_VAL_8;

   PLCIEC::BOOL WRITE_OUT_1TO8;
};

struct AXIS_GROUP_REF
{
   PLCIEC::BOOL INITIALIZED;

   PLCIEC::BOOL ONLINE;

   PLCIEC::DINT LASTORDERID;

   PLCIEC::BOOL READAXISGROUPINIT;

   PLCIEC::BOOL READDONE;

   PLCIEC::DINT INTERRORID;

   PLCIEC::DINT INTFBERRORID;

   PLCIEC::DINT HEARTBEATTO;

   PLCIEC::DINT PLC_MAJOR;

   PLCIEC::DINT PLC_MINOR;

   PLCIEC::REAL DEF_VEL_CP;

   PLCIEC::REAL DEF_ACC_CP;

   MXA_COMMAND COMMAND;

   MXA_COMMAND_STATUS CMDSTATE;

   MXA_AUTEXT_CONTROL AUTEXTCONTROL;

   MXA_AUTEXT_STATE AUTEXTSTATE;

   MXA_KRC_STATE KRCSTATE;

   MXA_KRC_CONTROL KRCCONTROL;

   MXA_JOGADVANCED JOG_ADVANCED;

   PLCIEC::REAL VEL_MAX_CP;

   PLCIEC::REAL ACC_MAX_CP;
};

typedef AXIS_GROUP_REF AXIS_GROUP_REF_ARR[6];

/******************************************************************************
 * GLOBAL Variable List
 ******************************************************************************/
// AXIS_GROUP_REF_ARR KRC_AXISGROUPREFARR;
extern AXIS_GROUP_REF KRC_AXISGROUPREFARR[];

extern PLCIEC::DINT TESTCNT;

extern PLCIEC::DINT TESTCNTR;

extern PLCIEC::DINT TESTCNTW;

struct APO
{
   PLCIEC::INT PTP_MODE;

   PLCIEC::INT CP_MODE;

   PLCIEC::INT CPTP;

   PLCIEC::REAL CDIS;

   PLCIEC::REAL CORI;

   PLCIEC::INT CVEL;
};

struct AXBOX
{
   PLCIEC::REAL A1_N;

   PLCIEC::REAL A2_N;

   PLCIEC::REAL A3_N;

   PLCIEC::REAL A4_N;

   PLCIEC::REAL A5_N;

   PLCIEC::REAL A6_N;

   PLCIEC::REAL A1_P;

   PLCIEC::REAL A2_P;

   PLCIEC::REAL A3_P;

   PLCIEC::REAL A4_P;

   PLCIEC::REAL A5_P;

   PLCIEC::REAL A6_P;

   PLCIEC::REAL E1_N;

   PLCIEC::REAL E2_N;

   PLCIEC::REAL E3_N;

   PLCIEC::REAL E4_N;

   PLCIEC::REAL E5_N;

   PLCIEC::REAL E6_N;

   PLCIEC::REAL E1_P;

   PLCIEC::REAL E2_P;

   PLCIEC::REAL E3_P;

   PLCIEC::REAL E4_P;

   PLCIEC::REAL E5_P;

   PLCIEC::REAL E6_P;
};

typedef PLCIEC::INT AXIS_VEL[13];

typedef PLCIEC::BOOL BOOL_ARRAY_40[41];

struct BOX
{
   PLCIEC::REAL X;

   PLCIEC::REAL Y;

   PLCIEC::REAL Z;

   PLCIEC::REAL A;

   PLCIEC::REAL B;

   PLCIEC::REAL C;

   PLCIEC::REAL X1;

   PLCIEC::REAL X2;

   PLCIEC::REAL Y1;

   PLCIEC::REAL Y2;

   PLCIEC::REAL Z1;

   PLCIEC::REAL Z2;
};

struct COORDSYS
{
   PLCIEC::INT TOOL;

   PLCIEC::INT BASE;

   PLCIEC::INT IPO_MODE;
};

struct FRAME
{
   PLCIEC::REAL X;

   PLCIEC::REAL Y;

   PLCIEC::REAL Z;

   PLCIEC::REAL A;

   PLCIEC::REAL B;

   PLCIEC::REAL C;
};

typedef PLCIEC::DINT INT32_ARRAY_40[41];

enum MXA_BUFFERMODE
{
   MXA_DIRECT,
   MXA_ABORTING,
   MXA_BUFFERED
};

enum MXA_CIRC_TYPE
{
   MXA_BASE,
   MXA_PATH
};

enum MXA_CP_APO
{
   MXA_CP_NO_APO,
   MXA_C_DIS,
   MXA_C_ORI,
   MXA_C_VEL
};

enum MXA_ORI_TYPE
{
   MXA_VAR,
   MXA_CONSTANT,
   MXA_JOINT
};

enum MXA_PTP_APO
{
   MXA_NO_APO,
   MXA_C_PTP,
   MXA_C_PTP_C_DIS,
   MXA_C_PTP_C_ORI,
   MXA_C_PTP_C_VEL
};

typedef PLCIEC::BOOL MXA_SYNC_IO[2033];

struct POSITION1
{
   COORDSYS COORDSYS_1;

   E6POS E6POS_1;

   E6AXIS E6AXIS_1;
};

typedef POSITION1 POSITION_ARRAY[101];

typedef PLCIEC::REAL REAL_ARRAY_40[41];

typedef PLCIEC::REAL REAL_ARRAY_12[13];

/******************************************************************************
 * FUNCTION MXA_GETIO_BYTE
 ******************************************************************************/
inline PLCIEC::BOOL MXA_GETIO_BYTE(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_INPUT,
    _OUT PLCIEC::INT &O)
{
   PLCIEC::BOOL MXA_GETIO_BYTE = (PLCIEC::BOOL)FALSE;

   O = PLCIEC::BYTE_TO_INT(KRC4_INPUT[BYTEPOS]);
   return MXA_GETIO_BYTE;
}

/******************************************************************************
 * FUNCTION MXA_GETIO_DINT
 ******************************************************************************/
inline PLCIEC::BOOL MXA_GETIO_DINT(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_INPUT,
    _OUT PLCIEC::DINT &O)
{
   PLCIEC::DWORD DW = 0;
   PLCIEC::BOOL MXA_GETIO_DINT = (PLCIEC::BOOL)FALSE;

   ChBit(DW, 0, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 0));
   ChBit(DW, 1, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 1));
   ChBit(DW, 2, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 2));
   ChBit(DW, 3, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 3));
   ChBit(DW, 4, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 4));
   ChBit(DW, 5, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 5));
   ChBit(DW, 6, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 6));
   ChBit(DW, 7, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 7));
   ChBit(DW, 8, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 0));
   ChBit(DW, 9, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 1));
   ChBit(DW, 10, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 2));
   ChBit(DW, 11, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 3));
   ChBit(DW, 12, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 4));
   ChBit(DW, 13, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 5));
   ChBit(DW, 14, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 6));
   ChBit(DW, 15, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 7));
   ChBit(DW, 16, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 0));
   ChBit(DW, 17, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 1));
   ChBit(DW, 18, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 2));
   ChBit(DW, 19, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 3));
   ChBit(DW, 20, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 4));
   ChBit(DW, 21, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 5));
   ChBit(DW, 22, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 6));
   ChBit(DW, 23, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 7));
   ChBit(DW, 24, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 0));
   ChBit(DW, 25, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 1));
   ChBit(DW, 26, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 2));
   ChBit(DW, 27, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 3));
   ChBit(DW, 28, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 4));
   ChBit(DW, 29, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 5));
   ChBit(DW, 30, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 6));
   ChBit(DW, 31, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 7));
   O = PLCIEC::DWORD_TO_DINT(DW);
   return MXA_GETIO_DINT;
}

/******************************************************************************
 * FUNCTION MXA_GETIO_INT
 ******************************************************************************/
inline PLCIEC::BOOL MXA_GETIO_INT(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_INPUT,
    _OUT PLCIEC::INT &O)
{
   PLCIEC::WORD W = 0;
   PLCIEC::BOOL MXA_GETIO_INT = (PLCIEC::BOOL)FALSE;

   ChBit(W, 0, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 0));
   ChBit(W, 1, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 1));
   ChBit(W, 2, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 2));
   ChBit(W, 3, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 3));
   ChBit(W, 4, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 4));
   ChBit(W, 5, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 5));
   ChBit(W, 6, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 6));
   ChBit(W, 7, /* := */ IsBitSet(KRC4_INPUT[BYTEPOS], 7));
   ChBit(W, 8, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 0));
   ChBit(W, 9, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 1));
   ChBit(W, 10, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 2));
   ChBit(W, 11, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 3));
   ChBit(W, 12, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 4));
   ChBit(W, 13, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 5));
   ChBit(W, 14, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 6));
   ChBit(W, 15, /* := */ IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 7));
   O = PLCIEC::WORD_TO_INT(W);
   return MXA_GETIO_INT;
}

/******************************************************************************
 * FUNCTION MXA_GETIO_NIBBLE
 ******************************************************************************/
inline PLCIEC::BOOL MXA_GETIO_NIBBLE(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_INPUT,
    _OUT PLCIEC::INT &N1,
    _OUT PLCIEC::INT &N2)
{
   PLCIEC::BYTE B = 0;
   PLCIEC::BYTE B1 = 0;
   PLCIEC::BYTE B2 = 0;
   PLCIEC::BOOL MXA_GETIO_NIBBLE = (PLCIEC::BOOL)FALSE;

   B = KRC4_INPUT[BYTEPOS];
   ChBit(B1, 0, /* := */ IsBitSet(B, 0));
   ChBit(B1, 1, /* := */ IsBitSet(B, 1));
   ChBit(B1, 2, /* := */ IsBitSet(B, 2));
   ChBit(B1, 3, /* := */ IsBitSet(B, 3));
   ChBit(B2, 0, /* := */ IsBitSet(B, 4));
   ChBit(B2, 1, /* := */ IsBitSet(B, 5));
   ChBit(B2, 2, /* := */ IsBitSet(B, 6));
   ChBit(B2, 3, /* := */ IsBitSet(B, 7));
   N1 = PLCIEC::BYTE_TO_INT(B1);
   N2 = PLCIEC::BYTE_TO_INT(B2);
   return MXA_GETIO_NIBBLE;
}

/******************************************************************************
 * FUNCTION MXA_GETIO_REAL
 ******************************************************************************/
inline PLCIEC::BOOL MXA_GETIO_REAL(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_INPUT,
    _OUT PLCIEC::REAL &O)
{
   PLCIEC::REAL *PDW;
   PLCIEC::BOOL MXA_GETIO_REAL = (PLCIEC::BOOL)FALSE;

   PDW = reinterpret_cast<PLCIEC::REAL *>(&(KRC4_INPUT[BYTEPOS]));
   O = *PDW;
   return MXA_GETIO_REAL;
}

/******************************************************************************
 * FUNCTION MXA_GETIO_SINT
 ******************************************************************************/
inline PLCIEC::BOOL MXA_GETIO_SINT(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_INPUT,
    _OUT PLCIEC::SINT &O)
{
   PLCIEC::BYTE B = 0;
   PLCIEC::BOOL MXA_GETIO_SINT = (PLCIEC::BOOL)FALSE;

   B = KRC4_INPUT[BYTEPOS];
   O = PLCIEC::BYTE_TO_SINT(B);
   return MXA_GETIO_SINT;
}

/******************************************************************************
 * FUNCTION MXA_WRITEIO_BYTE
 ******************************************************************************/
inline PLCIEC::BOOL MXA_WRITEIO_BYTE(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_OUTPUT,
    _IN PLCIEC::INT VAL)
{
   PLCIEC::BOOL MXA_WRITEIO_BYTE = (PLCIEC::BOOL)FALSE;

   KRC4_OUTPUT[BYTEPOS] = PLCIEC::INT_TO_BYTE(VAL);
   return MXA_WRITEIO_BYTE;
}

/******************************************************************************
 * FUNCTION MXA_WRITEIO_DINT
 ******************************************************************************/
inline PLCIEC::BOOL MXA_WRITEIO_DINT(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_OUTPUT,
    _IN PLCIEC::DINT VAL)
{
   PLCIEC::BOOL MXA_WRITEIO_DINT = (PLCIEC::BOOL)FALSE;

   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 0, /* := */ IsBitSet(VAL, 0));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 1, /* := */ IsBitSet(VAL, 1));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 2, /* := */ IsBitSet(VAL, 2));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 3, /* := */ IsBitSet(VAL, 3));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 4, /* := */ IsBitSet(VAL, 4));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 5, /* := */ IsBitSet(VAL, 5));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 6, /* := */ IsBitSet(VAL, 6));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 7, /* := */ IsBitSet(VAL, 7));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 0, /* := */ IsBitSet(VAL, 8));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 1, /* := */ IsBitSet(VAL, 9));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 2, /* := */ IsBitSet(VAL, 10));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 3, /* := */ IsBitSet(VAL, 11));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 4, /* := */ IsBitSet(VAL, 12));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 5, /* := */ IsBitSet(VAL, 13));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 6, /* := */ IsBitSet(VAL, 14));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 7, /* := */ IsBitSet(VAL, 15));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 0, /* := */ IsBitSet(VAL, 16));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 1, /* := */ IsBitSet(VAL, 17));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 2, /* := */ IsBitSet(VAL, 18));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 3, /* := */ IsBitSet(VAL, 19));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 4, /* := */ IsBitSet(VAL, 20));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 5, /* := */ IsBitSet(VAL, 21));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 6, /* := */ IsBitSet(VAL, 22));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 7, /* := */ IsBitSet(VAL, 23));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 0, /* := */ IsBitSet(VAL, 24));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 1, /* := */ IsBitSet(VAL, 25));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 2, /* := */ IsBitSet(VAL, 26));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 3, /* := */ IsBitSet(VAL, 27));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 4, /* := */ IsBitSet(VAL, 28));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 5, /* := */ IsBitSet(VAL, 29));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 6, /* := */ IsBitSet(VAL, 30));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 7, /* := */ IsBitSet(VAL, 31));
   return MXA_WRITEIO_DINT;
}

/******************************************************************************
 * FUNCTION MXA_WRITEIO_DWORD
 ******************************************************************************/
inline PLCIEC::BOOL MXA_WRITEIO_DWORD(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_OUTPUT,
    _IN PLCIEC::DWORD VAL)
{
   PLCIEC::BOOL MXA_WRITEIO_DWORD = (PLCIEC::BOOL)FALSE;

   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 0, /* := */ IsBitSet(VAL, 0));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 1, /* := */ IsBitSet(VAL, 1));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 2, /* := */ IsBitSet(VAL, 2));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 3, /* := */ IsBitSet(VAL, 3));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 4, /* := */ IsBitSet(VAL, 4));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 5, /* := */ IsBitSet(VAL, 5));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 6, /* := */ IsBitSet(VAL, 6));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 7, /* := */ IsBitSet(VAL, 7));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 0, /* := */ IsBitSet(VAL, 8));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 1, /* := */ IsBitSet(VAL, 9));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 2, /* := */ IsBitSet(VAL, 10));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 3, /* := */ IsBitSet(VAL, 11));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 4, /* := */ IsBitSet(VAL, 12));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 5, /* := */ IsBitSet(VAL, 13));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 6, /* := */ IsBitSet(VAL, 14));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 7, /* := */ IsBitSet(VAL, 15));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 0, /* := */ IsBitSet(VAL, 16));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 1, /* := */ IsBitSet(VAL, 17));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 2, /* := */ IsBitSet(VAL, 18));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 3, /* := */ IsBitSet(VAL, 19));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 4, /* := */ IsBitSet(VAL, 20));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 5, /* := */ IsBitSet(VAL, 21));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 6, /* := */ IsBitSet(VAL, 22));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 7, /* := */ IsBitSet(VAL, 23));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 0, /* := */ IsBitSet(VAL, 24));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 1, /* := */ IsBitSet(VAL, 25));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 2, /* := */ IsBitSet(VAL, 26));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 3, /* := */ IsBitSet(VAL, 27));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 4, /* := */ IsBitSet(VAL, 28));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 5, /* := */ IsBitSet(VAL, 29));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 6, /* := */ IsBitSet(VAL, 30));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 7, /* := */ IsBitSet(VAL, 31));
   return MXA_WRITEIO_DWORD;
}

/******************************************************************************
 * FUNCTION MXA_WRITEIO_REAL
 ******************************************************************************/
inline PLCIEC::BOOL MXA_WRITEIO_REAL(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_OUTPUT,
    _IN PLCIEC::REAL VAL)
{
   PLCIEC::REAL *PDW;
   PLCIEC::BOOL MXA_WRITEIO_REAL = (PLCIEC::BOOL)FALSE;

   PDW = reinterpret_cast<PLCIEC::REAL *>(&(KRC4_OUTPUT[BYTEPOS]));
   *PDW = VAL;
   return MXA_WRITEIO_REAL;
}

/******************************************************************************
 * FUNCTION MXA_WRITEIO_WORD
 ******************************************************************************/
inline PLCIEC::BOOL MXA_WRITEIO_WORD(
    _IN PLCIEC::INT BYTEPOS,
    _IN PLCIEC::BYTE *KRC4_OUTPUT,
    _IN PLCIEC::WORD VAL)
{
   PLCIEC::BOOL MXA_WRITEIO_WORD = (PLCIEC::BOOL)FALSE;

   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 0, /* := */ IsBitSet(VAL, 0));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 1, /* := */ IsBitSet(VAL, 1));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 2, /* := */ IsBitSet(VAL, 2));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 3, /* := */ IsBitSet(VAL, 3));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 4, /* := */ IsBitSet(VAL, 4));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 5, /* := */ IsBitSet(VAL, 5));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 6, /* := */ IsBitSet(VAL, 6));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 7, /* := */ IsBitSet(VAL, 7));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 0, /* := */ IsBitSet(VAL, 8));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 1, /* := */ IsBitSet(VAL, 9));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 2, /* := */ IsBitSet(VAL, 10));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 3, /* := */ IsBitSet(VAL, 11));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 4, /* := */ IsBitSet(VAL, 12));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 5, /* := */ IsBitSet(VAL, 13));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 6, /* := */ IsBitSet(VAL, 14));
   ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 7, /* := */ IsBitSet(VAL, 15));
   return MXA_WRITEIO_WORD;
}

/******************************************************************************
 * FUNCTION_BLOCK MXA_RESETCOMMAND
 ******************************************************************************/
class MXA_RESETCOMMAND
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR */

private:
   PLCIEC::INT I;

public:
   MXA_RESETCOMMAND()
       : AXISGROUPIDX(0), I(0)
   {
   }

public:
   void OnCycle()
   {

      for (I = 1; I <= 50; I += 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] = (PLCIEC::BOOL)FALSE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I] = (PLCIEC::DINT)0;
      };
      for (I = 1; I <= 100; I += 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = 0.0;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = (PLCIEC::DINT)0;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = (PLCIEC::DINT)0;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = (PLCIEC::DINT)0;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = (PLCIEC::INT)0;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_GETORDERSTATE
 ******************************************************************************/
class MXA_GETORDERSTATE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::DINT ORDERID;

   /* VAR_OUTPUT */

public:
   const PLCIEC::INT &ORDERSTATE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::INT _ORDERSTATE;

   /* VAR */

private:
   PLCIEC::INT I;
   PLCIEC::INT M_ORDERSTATE;

public:
   MXA_GETORDERSTATE()
       : AXISGROUPIDX(0), ORDERID(0), ORDERSTATE(_ORDERSTATE), _ORDERSTATE(0), I(0), M_ORDERSTATE(0)
   {
   }

public:
   void OnCycle()
   {
      M_ORDERSTATE = 0;
      for (I = 1; I <= 10; I += 1)
      {
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[I].SR_ORDERID == ORDERID) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[I].SR_STATE > M_ORDERSTATE))
         {
            M_ORDERSTATE = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[I].SR_STATE;
         };
      };
      _ORDERSTATE = M_ORDERSTATE;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_EXECUTECOMMAND
 ******************************************************************************/
class MXA_EXECUTECOMMAND
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   PLCIEC::DINT CMDID;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::INT COMMANDSIZE;
   PLCIEC::BOOL ENABLEDIRECTEXE;
   PLCIEC::BOOL ENABLEQUEUEEXE;
   PLCIEC::BOOL IGNOREINIT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &WRITECMDPAR;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &CMDSPECIFIC1;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::BOOL &READCMDDATARET;
   const PLCIEC::DINT &ORDERID;
   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _WRITECMDPAR;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _CMDSPECIFIC1;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::BOOL _READCMDDATARET;
   PLCIEC::DINT _ORDERID;
   /* VAR */

private:
   MXA_RESETCOMMAND RESETCOMMAND_1;
   MXA_GETORDERSTATE GETORDERSTATE_1;
   PLCIEC::INT M_STATE;
   PLCIEC::DINT M_ORDERID;
   PLCIEC::BOOL M_EXECUTELAST;
   PLCIEC::BOOL M_RE_EXECUTE;
   PLCIEC::INT M_COMMANDSIZE;

public:
   MXA_EXECUTECOMMAND()
       : AXISGROUPIDX(0), EXECUTE((PLCIEC::BOOL)FALSE), CMDID(0), BUFFERMODE(0), COMMANDSIZE(0), ENABLEDIRECTEXE((PLCIEC::BOOL)FALSE), ENABLEQUEUEEXE((PLCIEC::BOOL)FALSE), IGNOREINIT((PLCIEC::BOOL)FALSE), WRITECMDPAR(_WRITECMDPAR), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), CMDSPECIFIC1(_CMDSPECIFIC1), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), READCMDDATARET(_READCMDDATARET), ORDERID(_ORDERID), _WRITECMDPAR((PLCIEC::BOOL)FALSE), _BUSY((PLCIEC::BOOL)FALSE), _ACTIVE((PLCIEC::BOOL)FALSE), _DONE((PLCIEC::BOOL)FALSE), _CMDSPECIFIC1((PLCIEC::BOOL)FALSE), _ABORTED((PLCIEC::BOOL)FALSE), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), _READCMDDATARET((PLCIEC::BOOL)FALSE), _ORDERID(0), RESETCOMMAND_1(), GETORDERSTATE_1(), M_STATE(0), M_ORDERID(0), M_EXECUTELAST((PLCIEC::BOOL)FALSE), M_RE_EXECUTE((PLCIEC::BOOL)FALSE), M_COMMANDSIZE(0)
   {
   }

public:
   void OnCycle()
   {

      M_RE_EXECUTE = ((EXECUTE == (PLCIEC::BOOL)TRUE) && (M_EXECUTELAST == (PLCIEC::BOOL)FALSE));
      M_EXECUTELAST = EXECUTE;
      _WRITECMDPAR = (PLCIEC::BOOL)FALSE;
      _READCMDDATARET = (PLCIEC::BOOL)FALSE;
      if (!(EXECUTE))
      {
         M_STATE = 0;
         M_ORDERID = (PLCIEC::DINT)0;
         _ERRORID = (PLCIEC::DINT)0;
      };
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
      }
      else
      {
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE))
         {
            _ERRORID = (PLCIEC::DINT)507;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT))
         {
            _ERRORID = (PLCIEC::DINT)508;
         };
      };
      if ((M_RE_EXECUTE && (_ERRORID == (PLCIEC::DINT)0)))
      {
         M_STATE = 1;
         if ((((BUFFERMODE == 0) && (ENABLEDIRECTEXE == (PLCIEC::BOOL)FALSE)) || ((BUFFERMODE > 0) && (ENABLEQUEUEEXE == (PLCIEC::BOOL)FALSE))))
         {
            _ERRORID = (PLCIEC::DINT)502;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            if (!(IGNOREINIT))
            {
               _ERRORID = (PLCIEC::DINT)508;
            };
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            _ERRORID = (PLCIEC::DINT)509;
         };
      };
      if (((M_STATE == 1) && (_ERRORID == (PLCIEC::DINT)0)))
      {
         if (M_RE_EXECUTE)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID + (PLCIEC::DINT)1);
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID >= (PLCIEC::DINT)2147483647))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (PLCIEC::DINT)1;
            };
            M_ORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID;
         };
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET == M_ORDERID))
         {
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET == CMDID))
            {
               if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSPLC == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSKRC))
               {
                  if ((BUFFERMODE == 0))
                  {
                     M_STATE = 15;
                     _READCMDDATARET = (PLCIEC::BOOL)TRUE;
                  }
                  else
                  {
                     M_STATE = 5;
                  };
               }
               else
               {
                  _ERRORID = (PLCIEC::DINT)512;
               };
            }
            else
            {
               _ERRORID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET * (PLCIEC::DINT) - (1));
            };
            // Call FB ResetCommand_1
            RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
            RESETCOMMAND_1.OnCycle();
         }
         else
         {
            if (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == (PLCIEC::DINT)0) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID == (PLCIEC::DINT)0)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED || IGNOREINIT)))
            {
               if (((BUFFERMODE < 2) || (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.QUEUECOUNT < 80)))
               {
                  // Call FB ResetCommand_1
                  RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
                  RESETCOMMAND_1.OnCycle();
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = M_ORDERID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = CMDID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = PLCIEC::INT_TO_DINT(BUFFERMODE);
                  M_COMMANDSIZE = COMMANDSIZE;
                  if (((COMMANDSIZE < 1) || (COMMANDSIZE > 3)))
                  {
                     _ERRORID = (PLCIEC::DINT)517;
                     M_COMMANDSIZE = 3;
                  };
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = M_COMMANDSIZE;
                  _WRITECMDPAR = (PLCIEC::BOOL)TRUE;
               };
            };
         };
      };
      if ((((M_STATE > 1) && (M_STATE < 15)) && (_ERRORID == (PLCIEC::DINT)0)))
      {
         // Call FB GetOrderState_1
         GETORDERSTATE_1.AXISGROUPIDX = AXISGROUPIDX;
         GETORDERSTATE_1.ORDERID = M_ORDERID;
         GETORDERSTATE_1.OnCycle();
         if ((GETORDERSTATE_1.ORDERSTATE > 0))
         {
            if ((GETORDERSTATE_1.ORDERSTATE == 5) && (M_STATE < 10))
            {
               M_STATE = 10;
            };
            if ((GETORDERSTATE_1.ORDERSTATE == 6) && (M_STATE < 15))
            {
               M_STATE = 15;
            };
            if ((GETORDERSTATE_1.ORDERSTATE == 8) && (M_STATE < 20))
            {
               M_STATE = 20;
            };
            if ((GETORDERSTATE_1.ORDERSTATE == 9) && (M_STATE < 25))
            {
               M_STATE = 25;
            };
         };
      };
      if ((_ERRORID != (PLCIEC::DINT)0))
      {
         M_STATE = (PLCIEC::DINT_TO_INT(_ERRORID) * -(1));
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _BUSY = (M_STATE > 1);
      _ACTIVE = (M_STATE == 10);
      _DONE = (M_STATE == 15);
      _CMDSPECIFIC1 = (M_STATE == 25);
      _ABORTED = (M_STATE == 20);
      _ERROR = (M_STATE < 0);
      _ORDERID = M_ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_AUTOMATICEXTERNAL
 ******************************************************************************/
class KRC_AUTOMATICEXTERNAL
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL MOVE_ENABLE;
   PLCIEC::BOOL CONF_MESS;
   PLCIEC::BOOL DRIVES_ON;
   PLCIEC::BOOL DRIVES_OFF;
   PLCIEC::BOOL EXT_START;
   PLCIEC::BOOL RESET;
   PLCIEC::BOOL ENABLE_T1;
   PLCIEC::BOOL ENABLE_T2;
   PLCIEC::BOOL ENABLE_AUT;
   PLCIEC::BOOL ENABLE_EXT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::BOOL &RC_RDY1;
   const PLCIEC::BOOL &ALARM_STOP;
   const PLCIEC::BOOL &USER_SAFE;
   const PLCIEC::BOOL &PERI_RDY;
   const PLCIEC::BOOL &ROB_CAL;
   const PLCIEC::BOOL &IO_ACTCONF;
   const PLCIEC::BOOL &STOPMESS;
   const PLCIEC::BOOL &INT_E_STOP;
   const PLCIEC::BOOL &PRO_ACT;
   const PLCIEC::BOOL &APPL_RUN;
   const PLCIEC::BOOL &PRO_MOVE;
   const PLCIEC::BOOL &ON_PATH;
   const PLCIEC::BOOL &NEAR_POSRET;
   const PLCIEC::BOOL &ROB_STOPPED;
   const PLCIEC::BOOL &T1;
   const PLCIEC::BOOL &T2;
   const PLCIEC::BOOL &AUT;
   const PLCIEC::BOOL &EXT;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::BOOL _RC_RDY1;
   PLCIEC::BOOL _ALARM_STOP;
   PLCIEC::BOOL _USER_SAFE;
   PLCIEC::BOOL _PERI_RDY;
   PLCIEC::BOOL _ROB_CAL;
   PLCIEC::BOOL _IO_ACTCONF;
   PLCIEC::BOOL _STOPMESS;
   PLCIEC::BOOL _INT_E_STOP;
   PLCIEC::BOOL _PRO_ACT;
   PLCIEC::BOOL _APPL_RUN;
   PLCIEC::BOOL _PRO_MOVE;
   PLCIEC::BOOL _ON_PATH;
   PLCIEC::BOOL _NEAR_POSRET;
   PLCIEC::BOOL _ROB_STOPPED;
   PLCIEC::BOOL _T1;
   PLCIEC::BOOL _T2;
   PLCIEC::BOOL _AUT;
   PLCIEC::BOOL _EXT;

public:
   KRC_AUTOMATICEXTERNAL()
       : AXISGROUPIDX(0), MOVE_ENABLE((PLCIEC::BOOL)FALSE), CONF_MESS((PLCIEC::BOOL)FALSE), DRIVES_ON((PLCIEC::BOOL)FALSE), DRIVES_OFF((PLCIEC::BOOL)FALSE), EXT_START((PLCIEC::BOOL)FALSE), RESET((PLCIEC::BOOL)FALSE), ENABLE_T1((PLCIEC::BOOL)FALSE), ENABLE_T2((PLCIEC::BOOL)FALSE), ENABLE_AUT((PLCIEC::BOOL)FALSE), ENABLE_EXT((PLCIEC::BOOL)FALSE), VALID(_VALID), RC_RDY1(_RC_RDY1), ALARM_STOP(_ALARM_STOP), USER_SAFE(_USER_SAFE), PERI_RDY(_PERI_RDY), ROB_CAL(_ROB_CAL), IO_ACTCONF(_IO_ACTCONF), STOPMESS(_STOPMESS), INT_E_STOP(_INT_E_STOP), PRO_ACT(_PRO_ACT), APPL_RUN(_APPL_RUN), PRO_MOVE(_PRO_MOVE), ON_PATH(_ON_PATH), NEAR_POSRET(_NEAR_POSRET), ROB_STOPPED(_ROB_STOPPED), T1(_T1), T2(_T2), AUT(_AUT), EXT(_EXT), _VALID((PLCIEC::BOOL)FALSE), _RC_RDY1((PLCIEC::BOOL)FALSE), _ALARM_STOP((PLCIEC::BOOL)FALSE), _USER_SAFE((PLCIEC::BOOL)FALSE), _PERI_RDY((PLCIEC::BOOL)FALSE), _ROB_CAL((PLCIEC::BOOL)FALSE), _IO_ACTCONF((PLCIEC::BOOL)FALSE), _STOPMESS((PLCIEC::BOOL)FALSE), _INT_E_STOP((PLCIEC::BOOL)FALSE), _PRO_ACT((PLCIEC::BOOL)FALSE), _APPL_RUN((PLCIEC::BOOL)FALSE), _PRO_MOVE((PLCIEC::BOOL)FALSE), _ON_PATH((PLCIEC::BOOL)FALSE), _NEAR_POSRET((PLCIEC::BOOL)FALSE), _ROB_STOPPED((PLCIEC::BOOL)FALSE), _T1((PLCIEC::BOOL)FALSE), _T2((PLCIEC::BOOL)FALSE), _AUT((PLCIEC::BOOL)FALSE), _EXT((PLCIEC::BOOL)FALSE)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = (PLCIEC::BOOL)FALSE;
         return;
      };
      _ALARM_STOP = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP;
      _APPL_RUN = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.APPL_RUN;
      _AUT = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.AUT;
      _EXT = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT;
      _INT_E_STOP = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.INTNOTAUS;
      _IO_ACTCONF = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.IO_ACTCONF;
      _NEAR_POSRET = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.NEAR_POSRET;
      _ON_PATH = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ON_PATH;
      _PERI_RDY = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY;
      _PRO_ACT = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT;
      _PRO_MOVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_MOVE;
      _RC_RDY1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.RC_RDY1;
      _ROB_CAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ROB_CAL;
      _ROB_STOPPED = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ROB_STOPPED;
      _STOPMESS = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS;
      _T1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.T1;
      _T2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.T2;
      _USER_SAFE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE;
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      if (CONF_MESS)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (PLCIEC::BOOL)TRUE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESOFF = DRIVES_OFF;
      if (DRIVES_ON)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (PLCIEC::BOOL)TRUE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.EXT_START = EXT_START;
      if (RESET)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = (PLCIEC::BOOL)TRUE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE = ((((MOVE_ENABLE && ((ENABLE_T1 && _T1) || !(_T1))) && ((ENABLE_T2 && _T2) || !(_T2))) && ((ENABLE_AUT && _AUT) || !(_AUT))) && ((ENABLE_EXT && _EXT) || !(_EXT)));
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READMXAERROR
 ******************************************************************************/
class KRC_READMXAERROR
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READMXAERROR()
       : AXISGROUPIDX(0), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = (PLCIEC::DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      };
      _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID;
      if ((_ERRORID == (PLCIEC::DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB;
      };
      if ((_ERRORID == (PLCIEC::DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDPCOS;
      };
      if ((_ERRORID == (PLCIEC::DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID;
      };
      if ((_ERRORID == (PLCIEC::DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID;
      };
      _ERROR = (_ERRORID != (PLCIEC::DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MESSAGERESET
 ******************************************************************************/
class KRC_MESSAGERESET
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL MESSAGERESET;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

   /* VAR_TEMP */

private:
   PLCIEC::INT I;

public:
   KRC_MESSAGERESET()
       : AXISGROUPIDX(0), MESSAGERESET((PLCIEC::BOOL)FALSE), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), I(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      };
      _ERRORID = (PLCIEC::DINT)0;
      _ERROR = (PLCIEC::BOOL)FALSE;
      if (MESSAGERESET)
      {
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == (PLCIEC::DINT)565))
         {
            for (I = 1; I <= 100; I += 1)
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = 0.0;
            };
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET = MESSAGERESET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = (PLCIEC::DINT)0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = (PLCIEC::DINT)0;
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_AUTOSTART
 ******************************************************************************/
class KRC_AUTOSTART
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTERESET;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &DISPACTIVE;
   const PLCIEC::BOOL &RESETVALID;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _DISPACTIVE;
   PLCIEC::BOOL _RESETVALID;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

   /* VAR */

private:
   PLCIEC::DINT M_STATE;
   PLCIEC::BOOL M_CONFMESS;
   PLCIEC::BOOL M_RESET;
   PLCIEC::BOOL M_RE_EXECUTERESET;
   PLCIEC::BOOL M_EXECUTERESETLAST;
   KRC_READMXAERROR KRC_READMXAERROR_1;
   KRC_MESSAGERESET KRC_MESSAGERESET_1;
   PLCIEC::TON TON_ON;
   PLCIEC::TON TON_OFF;
   PLCIEC::TON TON_1;
   PLCIEC::TON TON_2;
   PLCIEC::TON TON_3;
   PLCIEC::TON TON_4;

public:
   KRC_AUTOSTART()
       : AXISGROUPIDX(0), EXECUTERESET((PLCIEC::BOOL)FALSE), BUSY(_BUSY), DONE(_DONE), DISPACTIVE(_DISPACTIVE), RESETVALID(_RESETVALID), ERROR(_ERROR), ERRORID(_ERRORID), _BUSY((PLCIEC::BOOL)FALSE), _DONE((PLCIEC::BOOL)FALSE), _DISPACTIVE((PLCIEC::BOOL)FALSE), _RESETVALID((PLCIEC::BOOL)FALSE), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), M_STATE(0), M_CONFMESS((PLCIEC::BOOL)FALSE), M_RESET((PLCIEC::BOOL)FALSE), M_RE_EXECUTERESET((PLCIEC::BOOL)FALSE), M_EXECUTERESETLAST((PLCIEC::BOOL)FALSE), KRC_READMXAERROR_1(), KRC_MESSAGERESET_1(), TON_ON(), TON_OFF(), TON_1(), TON_2(), TON_3(), TON_4()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      };
      _DISPACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT;
      _RESETVALID = (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && !(_DISPACTIVE)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP) && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE);
      if (!(EXECUTERESET))
      {
         M_STATE = 0;
         _ERRORID = (PLCIEC::DINT)0;
      };
      M_RE_EXECUTERESET = ((EXECUTERESET == (PLCIEC::BOOL)TRUE) && (M_EXECUTERESETLAST == (PLCIEC::BOOL)FALSE));
      M_EXECUTERESETLAST = EXECUTERESET;
      // Call FB KRC_ReadMXAError_1
      KRC_READMXAERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_READMXAERROR_1.OnCycle();
      M_CONFMESS = (PLCIEC::BOOL)FALSE;
      M_RESET = (PLCIEC::BOOL)FALSE;
      _DONE = (PLCIEC::BOOL)FALSE;
      switch (M_STATE)
      {
      case 0:
         if (M_RE_EXECUTERESET)
         {
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
            {
               _ERRORID = (PLCIEC::DINT)508;
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
            {
               _ERRORID = (PLCIEC::DINT)509;
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT))
            {
               _ERRORID = (PLCIEC::DINT)523;
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE))
            {
               _ERRORID = (PLCIEC::DINT)524;
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP))
            {
               _ERRORID = (PLCIEC::DINT)525;
            };
            if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT)
            {
               _ERRORID = (PLCIEC::DINT)526;
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE))
            {
               _ERRORID = (PLCIEC::DINT)532;
            };
            if ((_ERRORID == (PLCIEC::DINT)0))
            {
               M_STATE = 1;
            }
            else
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            };
         };
         break;
      case 1:
         if ((KRC_READMXAERROR_1.ERRORID == (PLCIEC::DINT)0))
         {
            M_STATE = 2;
         };
         // Call FB KRC_MessageReset_1
         KRC_MESSAGERESET_1.AXISGROUPIDX = AXISGROUPIDX;
         KRC_MESSAGERESET_1.MESSAGERESET = (PLCIEC::BOOL)TRUE;
         KRC_MESSAGERESET_1.OnCycle();
         break;
      case 2:
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY)
         {
            M_STATE = 3;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (PLCIEC::BOOL)TRUE;
         };
         break;
      case 3:
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS)
         {
            M_CONFMESS = (PLCIEC::BOOL)TRUE;
         }
         else
         {
            M_STATE = 4;
         };
         break;
      case 4:
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT)
         {
            M_STATE = 5;
         }
         else
         {
            M_RESET = (PLCIEC::BOOL)TRUE;
         };
         break;
      case 5:
         _DONE = (PLCIEC::BOOL)TRUE;
         if (!(EXECUTERESET))
         {
            M_STATE = 0;
         };
         break;
      };
      // Call FB TON_ON
      TON_ON.IN = ((M_CONFMESS || M_RESET) && !(TON_OFF.Q));
      TON_ON.PT = PLCIEC::MKTIME(1, 200);
      TON_ON.OnCycle();
      // Call FB TON_OFF
      TON_OFF.IN = ((M_CONFMESS || M_RESET) && TON_ON.Q);
      TON_OFF.PT = PLCIEC::MKTIME(1, 100);
      TON_OFF.OnCycle();
      if ((M_CONFMESS && !(TON_ON.Q)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (PLCIEC::BOOL)TRUE;
      };
      if ((M_RESET && !(TON_ON.Q)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = (PLCIEC::BOOL)TRUE;
      };
      // Call FB TON_1
      TON_1.IN = (M_STATE == 1);
      TON_1.PT = PLCIEC::MKTIME(1, 0, 5);
      TON_1.OnCycle();
      // Call FB TON_2
      TON_2.IN = (M_STATE == 2);
      TON_2.PT = PLCIEC::MKTIME(1, 0, 5);
      TON_2.OnCycle();
      // Call FB TON_3
      TON_3.IN = (M_STATE == 3);
      TON_3.PT = PLCIEC::MKTIME(1, 0, 5);
      TON_3.OnCycle();
      // Call FB TON_4
      TON_4.IN = (M_STATE == 4);
      TON_4.PT = PLCIEC::MKTIME(1, 0, 5);
      TON_4.OnCycle();
      if (TON_1.Q)
      {
         _ERRORID = (PLCIEC::DINT)528;
      };
      if (TON_2.Q)
      {
         _ERRORID = (PLCIEC::DINT)527;
      };
      if (TON_3.Q)
      {
         _ERRORID = (PLCIEC::DINT)529;
      };
      if (TON_4.Q)
      {
         _ERRORID = (PLCIEC::DINT)531;
      };
      if ((_ERRORID != (PLCIEC::DINT)0))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _ERROR = (_ERRORID != (PLCIEC::DINT)0);
      _BUSY = (M_STATE > 0) && (M_STATE < 5);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ERROR
 ******************************************************************************/
class KRC_ERROR
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL MESSAGERESET;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::BOOL &NOHEARTBEATKRC;
   const PLCIEC::BOOL &NOHEARTBEATPCOS;
   const PLCIEC::BOOL &NOTONLINE;
   const PLCIEC::BOOL &NOTINITIALIZED;
   const PLCIEC::BOOL &NOOPMODEEXT;
   const PLCIEC::BOOL &NOMOVEENABLE;
   const PLCIEC::BOOL &USERSAFENOTOK;
   const PLCIEC::BOOL &KRCERRORACTIVE;
   const PLCIEC::BOOL &DRIVESNOTREADY;
   const PLCIEC::BOOL &NOPROGACTIVE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::BOOL _NOHEARTBEATKRC;
   PLCIEC::BOOL _NOHEARTBEATPCOS;
   PLCIEC::BOOL _NOTONLINE;
   PLCIEC::BOOL _NOTINITIALIZED;
   PLCIEC::BOOL _NOOPMODEEXT;
   PLCIEC::BOOL _NOMOVEENABLE;
   PLCIEC::BOOL _USERSAFENOTOK;
   PLCIEC::BOOL _KRCERRORACTIVE;
   PLCIEC::BOOL _DRIVESNOTREADY;
   PLCIEC::BOOL _NOPROGACTIVE;

   /* VAR */

private:
   KRC_READMXAERROR KRC_READMXAERROR_1;
   KRC_MESSAGERESET KRC_MESSAGERESET_1;
   PLCIEC::TON TON_ON;
   PLCIEC::TON TON_OFF;
   PLCIEC::TON TON_HBSUB;
   PLCIEC::TON TON_HBPCOS;
   PLCIEC::BOOL ENABLETONSUBMIT;
   PLCIEC::BOOL ENABLETONPCOS;
   PLCIEC::INT M_HEARTBEATLAST;
   PLCIEC::INT M_HEARTBEATLASTPCOS;

public:
   KRC_ERROR()
       : AXISGROUPIDX(0), MESSAGERESET((PLCIEC::BOOL)FALSE), ERROR(_ERROR), ERRORID(_ERRORID), NOHEARTBEATKRC(_NOHEARTBEATKRC), NOHEARTBEATPCOS(_NOHEARTBEATPCOS), NOTONLINE(_NOTONLINE), NOTINITIALIZED(_NOTINITIALIZED), NOOPMODEEXT(_NOOPMODEEXT), NOMOVEENABLE(_NOMOVEENABLE), USERSAFENOTOK(_USERSAFENOTOK), KRCERRORACTIVE(_KRCERRORACTIVE), DRIVESNOTREADY(_DRIVESNOTREADY), NOPROGACTIVE(_NOPROGACTIVE), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), _NOHEARTBEATKRC((PLCIEC::BOOL)FALSE), _NOHEARTBEATPCOS((PLCIEC::BOOL)FALSE), _NOTONLINE((PLCIEC::BOOL)FALSE), _NOTINITIALIZED((PLCIEC::BOOL)FALSE), _NOOPMODEEXT((PLCIEC::BOOL)FALSE), _NOMOVEENABLE((PLCIEC::BOOL)FALSE), _USERSAFENOTOK((PLCIEC::BOOL)FALSE), _KRCERRORACTIVE((PLCIEC::BOOL)FALSE), _DRIVESNOTREADY((PLCIEC::BOOL)FALSE), _NOPROGACTIVE((PLCIEC::BOOL)FALSE), KRC_READMXAERROR_1(), KRC_MESSAGERESET_1(), TON_ON(), TON_OFF(), TON_HBSUB(), TON_HBPCOS(), ENABLETONSUBMIT((PLCIEC::BOOL)FALSE), ENABLETONPCOS((PLCIEC::BOOL)FALSE), M_HEARTBEATLAST(0), M_HEARTBEATLASTPCOS(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (PLCIEC::DINT)0;
         _ERROR = (PLCIEC::BOOL)FALSE;
      };
      // Call FB KRC_MessageReset_1
      KRC_MESSAGERESET_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MESSAGERESET_1.MESSAGERESET = MESSAGERESET;
      KRC_MESSAGERESET_1.OnCycle();
      // Call FB KRC_ReadMXAError_1
      KRC_READMXAERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_READMXAERROR_1.OnCycle();
      _ERRORID = KRC_READMXAERROR_1.ERRORID;
      if ((_ERRORID == (PLCIEC::DINT)0))
      {
         // Call FB TON_ON
         TON_ON.IN = (MESSAGERESET && !(TON_OFF.Q));
         TON_ON.PT = PLCIEC::MKTIME(1, 200);
         TON_ON.OnCycle();
         // Call FB TON_OFF
         TON_OFF.IN = (MESSAGERESET && TON_ON.Q);
         TON_OFF.PT = PLCIEC::MKTIME(1, 100);
         TON_OFF.OnCycle();
         if ((MESSAGERESET && !(TON_ON.Q)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (PLCIEC::BOOL)TRUE;
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (PLCIEC::BOOL)TRUE;
            };
         };
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS)
         {
            _ERRORID = (PLCIEC::DINT)801;
         };
      };
      _ERROR = (_ERRORID != (PLCIEC::DINT)0);
      ENABLETONSUBMIT = ((M_HEARTBEATLAST == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT >= 0));
      ENABLETONPCOS = ((M_HEARTBEATLASTPCOS == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS >= 0));
      // Call FB TON_HBSub
      TON_HBSUB.IN = ENABLETONSUBMIT;
      TON_HBSUB.PT = PLCIEC::MKTIME(1, 0, 1);
      TON_HBSUB.OnCycle();
      // Call FB TON_HBPCOS
      TON_HBPCOS.IN = ENABLETONPCOS;
      TON_HBPCOS.PT = PLCIEC::MKTIME(1, 0, 1);
      TON_HBPCOS.OnCycle();
      M_HEARTBEATLAST = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      M_HEARTBEATLASTPCOS = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS;
      _NOHEARTBEATKRC = TON_HBSUB.Q;
      _NOHEARTBEATPCOS = TON_HBPCOS.Q;
      _NOTONLINE = !(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      _NOTINITIALIZED = !(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED);
      _NOOPMODEEXT = !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT);
      _NOMOVEENABLE = (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE) || KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_DISABLE);
      _USERSAFENOTOK = !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE);
      _KRCERRORACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS;
      _DRIVESNOTREADY = !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY);
      _NOPROGACTIVE = !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INITIALIZE
 ******************************************************************************/
class KRC_INITIALIZE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &KRC_SERIAL;
   const PLCIEC::DINT &KRC_MAJOR;
   const PLCIEC::DINT &KRC_MINOR;
   const PLCIEC::DINT &KRC_REVISION;
   const PLCIEC::DINT &KRC_ABSACCUR;
   const PLCIEC::DINT &PLC_MAJOR;
   const PLCIEC::DINT &PLC_MINOR;
   const PLCIEC::DINT &PLC_REVISION;
   const PLCIEC::DINT &KRC_INSTALLED_OPT;
   const PLCIEC::DINT &KRC_NUM_ROB_AXIS;
   const PLCIEC::DINT &KRC_NUM_EX_AXIS;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _KRC_SERIAL;
   PLCIEC::DINT _KRC_MAJOR;
   PLCIEC::DINT _KRC_MINOR;
   PLCIEC::DINT _KRC_REVISION;
   PLCIEC::DINT _KRC_ABSACCUR;
   PLCIEC::DINT _PLC_MAJOR;
   PLCIEC::DINT _PLC_MINOR;
   PLCIEC::DINT _PLC_REVISION;
   PLCIEC::DINT _KRC_INSTALLED_OPT;
   PLCIEC::DINT _KRC_NUM_ROB_AXIS;
   PLCIEC::DINT _KRC_NUM_EX_AXIS;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;

public:
   KRC_INITIALIZE()
       : AXISGROUPIDX(0), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), KRC_SERIAL(_KRC_SERIAL), KRC_MAJOR(_KRC_MAJOR), KRC_MINOR(_KRC_MINOR), KRC_REVISION(_KRC_REVISION), KRC_ABSACCUR(_KRC_ABSACCUR), PLC_MAJOR(_PLC_MAJOR), PLC_MINOR(_PLC_MINOR), PLC_REVISION(_PLC_REVISION), KRC_INSTALLED_OPT(_KRC_INSTALLED_OPT), KRC_NUM_ROB_AXIS(_KRC_NUM_ROB_AXIS), KRC_NUM_EX_AXIS(_KRC_NUM_EX_AXIS), ORDERID(_ORDERID), _DONE((PLCIEC::BOOL)FALSE), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), _KRC_SERIAL(0), _KRC_MAJOR(0), _KRC_MINOR(0), _KRC_REVISION(0), _KRC_ABSACCUR(0), _PLC_MAJOR(0), _PLC_MINOR(0), _PLC_REVISION(0), _KRC_INSTALLED_OPT(0), _KRC_NUM_ROB_AXIS(0), _KRC_NUM_EX_AXIS(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), MXA_RESETCOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = (PLCIEC::DINT)0;
      _PLC_MAJOR = (PLCIEC::DINT)3;
      _PLC_MINOR = (PLCIEC::DINT)0;
      _PLC_REVISION = (PLCIEC::DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MAJOR = _PLC_MAJOR;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MINOR = _PLC_MINOR;
      if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         _ERRORID = (PLCIEC::DINT)0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = (PLCIEC::BOOL)FALSE;
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      if ((((KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED == (PLCIEC::BOOL)FALSE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > (PLCIEC::DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID != (PLCIEC::DINT)31)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = 0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = 0;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE;
      MXA_EXECUTECOMMAND_1.CMDID = (PLCIEC::DINT)31;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (PLCIEC::BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (PLCIEC::BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (PLCIEC::BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _KRC_SERIAL = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _KRC_MAJOR = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _KRC_MINOR = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _KRC_REVISION = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _KRC_ABSACCUR = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _KRC_INSTALLED_OPT = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _KRC_NUM_ROB_AXIS = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _KRC_NUM_EX_AXIS = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].VEL_MAX_CP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ACC_MAX_CP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];

         if (((_KRC_MAJOR == _PLC_MAJOR) && (_KRC_MINOR >= _PLC_MINOR)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = (PLCIEC::BOOL)TRUE;
         }
         else
         {
            _ERRORID = (PLCIEC::DINT)503;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
         };
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      if ((_ERRORID == (PLCIEC::DINT)0))
      {
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      _ERROR = (_ERRORID != (PLCIEC::DINT)0);
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READAXISGROUP
 ******************************************************************************/
class KRC_READAXISGROUP
{

   /* VAR_INPUT */

public:
   PLCIEC::BYTE *KRC4_INPUT;
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::DINT HEARTBEAT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

   /* VAR */

private:
   PLCIEC::BOOL M_AE_RC_RDY1;
   PLCIEC::BOOL M_AE_ALARM_STOP;
   PLCIEC::BOOL M_AE_USER_SAF;
   PLCIEC::BOOL M_AE_PERI_RDY;
   PLCIEC::BOOL M_AE_ROB_CAL;
   PLCIEC::BOOL M_AE_IO_ACTCONF;
   PLCIEC::BOOL M_AE_STOPMESS;
   PLCIEC::BOOL M_AE_PGNO_FBIT_REFL;
   PLCIEC::BOOL M_AE_INT_ESTOP;
   PLCIEC::BOOL M_AE_PRO_ACT;
   PLCIEC::BOOL M_AE_PGNO_REQ;
   PLCIEC::BOOL M_AE_APPL_RUN;
   PLCIEC::BOOL M_AE_PRO_MOVE;
   PLCIEC::BOOL M_AE_IN_HOME;
   PLCIEC::BOOL M_AE_ON_PATH;
   PLCIEC::BOOL M_AE_NEAR_POSRET;
   PLCIEC::BOOL M_AE_ROB_STOPPED;
   PLCIEC::BOOL M_AE_T1;
   PLCIEC::BOOL M_AE_T2;
   PLCIEC::BOOL M_AE_AUT;
   PLCIEC::BOOL M_AE_EXT;
   PLCIEC::BOOL M_BRAKETEST_MONTIME;
   PLCIEC::BOOL M_BRAKETEST_REQ_INT;
   PLCIEC::BOOL M_BRAKETEST_WORK;
   PLCIEC::BOOL M_BRAKES_OK;
   PLCIEC::BOOL M_BRAKETEST_WARN;
   PLCIEC::BOOL M_ABORTACTIVE;
   PLCIEC::BOOL M_BRAKEACTIVE;
   PLCIEC::BOOL M_KCP_CONNECT;
   PLCIEC::BOOL M_TOUCHUP;
   PLCIEC::BOOL M_MASTEST_REQ_INT;
   PLCIEC::BOOL M_MASTESTSWITCH_OK;
   PLCIEC::BOOL M_POS_ACT_VALID;
   PLCIEC::INT M_HEARTBEATSUBMIT;
   PLCIEC::INT M_IN_VAL_1TO8;
   PLCIEC::INT M_TOUCHUP_POSNO;
   PLCIEC::DINT M_SR_ORDER1_ID;
   PLCIEC::DINT M_SR_ORDER2_ID;
   PLCIEC::DINT M_SR_ORDER3_ID;
   PLCIEC::DINT M_SR_ORDER4_ID;
   PLCIEC::DINT M_SR_ORDER5_ID;
   PLCIEC::DINT M_SR_ORDER6_ID;
   PLCIEC::DINT M_SR_ORDER7_ID;
   PLCIEC::DINT M_SR_ORDER8_ID;
   PLCIEC::DINT M_SR_ORDER9_ID;
   PLCIEC::DINT M_SR_ORDER10_ID;
   PLCIEC::INT M_SR_ORDER1_STATE;
   PLCIEC::INT M_SR_ORDER2_STATE;
   PLCIEC::INT M_SR_ORDER3_STATE;
   PLCIEC::INT M_SR_ORDER4_STATE;
   PLCIEC::INT M_SR_ORDER5_STATE;
   PLCIEC::INT M_SR_ORDER6_STATE;
   PLCIEC::INT M_SR_ORDER7_STATE;
   PLCIEC::INT M_SR_ORDER8_STATE;
   PLCIEC::INT M_SR_ORDER9_STATE;
   PLCIEC::INT M_SR_ORDER10_STATE;
   PLCIEC::INT M_HEARTBEATPCOS;
   PLCIEC::INT M_OVERRIDE;
   PLCIEC::REAL M_POSACT_X;
   PLCIEC::REAL M_POSACT_Y;
   PLCIEC::REAL M_POSACT_Z;
   PLCIEC::REAL M_POSACT_A;
   PLCIEC::REAL M_POSACT_B;
   PLCIEC::REAL M_POSACT_C;
   PLCIEC::DINT M_POSACT_STATUS;
   PLCIEC::INT M_POSACT_TURN;
   PLCIEC::SINT M_TOOLACT;
   PLCIEC::SINT M_BASEACT;
   PLCIEC::INT M_IPOMODE;
   PLCIEC::REAL M_AXISACT_A1;
   PLCIEC::REAL M_AXISACT_A2;
   PLCIEC::REAL M_AXISACT_A3;
   PLCIEC::REAL M_AXISACT_A4;
   PLCIEC::REAL M_AXISACT_A5;
   PLCIEC::REAL M_AXISACT_A6;
   PLCIEC::REAL M_AXISACT_A7;
   PLCIEC::REAL M_AXISACT_A8;
   PLCIEC::REAL M_AXISACT_A9;
   PLCIEC::REAL M_AXISACT_A10;
   PLCIEC::REAL M_AXISACT_A11;
   PLCIEC::REAL M_AXISACT_A12;
   PLCIEC::REAL M_VELACT;
   PLCIEC::INT M_WORKSTATES;
   PLCIEC::INT M_AXWORKSTATES;
   PLCIEC::INT M_GROUPSTATE;
   PLCIEC::INT M_ERRORID;
   PLCIEC::INT M_ERRORIDSUB;
   PLCIEC::DINT M_ACTIVEPOSORDERID;
   PLCIEC::DINT M_ACTIVEORDERIDB;
   PLCIEC::INT M_QUEUECOUNT;
   PLCIEC::INT M_IR_STATUS1;
   PLCIEC::INT M_IR_STATUS2;
   PLCIEC::INT M_IR_STATUS3;
   PLCIEC::INT M_IR_STATUS4;
   PLCIEC::INT M_IR_STATUS5;
   PLCIEC::INT M_IR_STATUS6;
   PLCIEC::INT M_IR_STATUS7;
   PLCIEC::INT M_IR_STATUS8;
   PLCIEC::INT M_ERRORIDPCOS;
   PLCIEC::INT M_FREE_FOR_WOV;
   PLCIEC::INT M_TRANSMISSIONNORET;
   PLCIEC::DINT M_ORDERIDRET;
   PLCIEC::DINT M_CMDIDRET;
   PLCIEC::DINT M_CMDDATARETCS;
   PLCIEC::DINT M_RESERVE190;
   PLCIEC::REAL M_CMDDATARET1;
   PLCIEC::REAL M_CMDDATARET2;
   PLCIEC::REAL M_CMDDATARET3;
   PLCIEC::REAL M_CMDDATARET4;
   PLCIEC::REAL M_CMDDATARET5;
   PLCIEC::REAL M_CMDDATARET6;
   PLCIEC::REAL M_CMDDATARET7;
   PLCIEC::REAL M_CMDDATARET8;
   PLCIEC::REAL M_CMDDATARET9;
   PLCIEC::REAL M_CMDDATARET10;
   PLCIEC::REAL M_CMDDATARET11;
   PLCIEC::REAL M_CMDDATARET12;
   PLCIEC::DINT M_RESERVE242;
   PLCIEC::DWORD NCHECKSUM;
   PLCIEC::REAL FTMP;
   PLCIEC::DINT NTMP1;
   PLCIEC::REAL FTMP1;
   PLCIEC::BOOL BTMP1;
   PLCIEC::INT I;
   PLCIEC::BOOL ONF_TRIG;
   PLCIEC::BOOL ENABLETONSUBMIT;
   PLCIEC::BOOL ENABLETONPCOS;
   PLCIEC::BOOL M_INITOK;
   PLCIEC::INT M_HEARTBEATLAST;
   PLCIEC::INT M_HEARTBEATLASTPCOS;
   PLCIEC::TIME HEARTBEATTO;
   PLCIEC::TON TON_1_PCOS;
   PLCIEC::TON TON_1_SUBMIT;
   PLCIEC::TON TON_2;
   PLCIEC::DINT M_LASTORDERID;
   PLCIEC::R_TRIG R_TRIG_1;
   PLCIEC::BOOL M_CONNECTIONOK;
   PLCIEC::BOOL M_F_TRIG;
   PLCIEC::INT M_FIRSTCYCLES;
   PLCIEC::BOOL RETB;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;

public:
   KRC_READAXISGROUP()
       : KRC4_INPUT(), AXISGROUPIDX(0), HEARTBEAT(1000), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), M_AE_RC_RDY1((PLCIEC::BOOL)FALSE), M_AE_ALARM_STOP((PLCIEC::BOOL)FALSE), M_AE_USER_SAF((PLCIEC::BOOL)FALSE), M_AE_PERI_RDY((PLCIEC::BOOL)FALSE), M_AE_ROB_CAL((PLCIEC::BOOL)FALSE), M_AE_IO_ACTCONF((PLCIEC::BOOL)FALSE), M_AE_STOPMESS((PLCIEC::BOOL)FALSE), M_AE_PGNO_FBIT_REFL((PLCIEC::BOOL)FALSE), M_AE_INT_ESTOP((PLCIEC::BOOL)FALSE), M_AE_PRO_ACT((PLCIEC::BOOL)FALSE), M_AE_PGNO_REQ((PLCIEC::BOOL)FALSE), M_AE_APPL_RUN((PLCIEC::BOOL)FALSE), M_AE_PRO_MOVE((PLCIEC::BOOL)FALSE), M_AE_IN_HOME((PLCIEC::BOOL)FALSE), M_AE_ON_PATH((PLCIEC::BOOL)FALSE), M_AE_NEAR_POSRET((PLCIEC::BOOL)FALSE), M_AE_ROB_STOPPED((PLCIEC::BOOL)FALSE), M_AE_T1((PLCIEC::BOOL)FALSE), M_AE_T2((PLCIEC::BOOL)FALSE), M_AE_AUT((PLCIEC::BOOL)FALSE), M_AE_EXT((PLCIEC::BOOL)FALSE), M_BRAKETEST_MONTIME((PLCIEC::BOOL)FALSE), M_BRAKETEST_REQ_INT((PLCIEC::BOOL)FALSE), M_BRAKETEST_WORK((PLCIEC::BOOL)FALSE), M_BRAKES_OK((PLCIEC::BOOL)FALSE), M_BRAKETEST_WARN((PLCIEC::BOOL)FALSE), M_ABORTACTIVE((PLCIEC::BOOL)FALSE), M_BRAKEACTIVE((PLCIEC::BOOL)FALSE), M_KCP_CONNECT((PLCIEC::BOOL)FALSE), M_TOUCHUP((PLCIEC::BOOL)FALSE), M_MASTEST_REQ_INT((PLCIEC::BOOL)FALSE), M_MASTESTSWITCH_OK((PLCIEC::BOOL)FALSE), M_POS_ACT_VALID((PLCIEC::BOOL)FALSE), M_HEARTBEATSUBMIT(0), M_IN_VAL_1TO8(0), M_TOUCHUP_POSNO(0), M_SR_ORDER1_ID(0), M_SR_ORDER2_ID(0), M_SR_ORDER3_ID(0), M_SR_ORDER4_ID(0), M_SR_ORDER5_ID(0), M_SR_ORDER6_ID(0), M_SR_ORDER7_ID(0), M_SR_ORDER8_ID(0), M_SR_ORDER9_ID(0), M_SR_ORDER10_ID(0), M_SR_ORDER1_STATE(0), M_SR_ORDER2_STATE(0), M_SR_ORDER3_STATE(0), M_SR_ORDER4_STATE(0), M_SR_ORDER5_STATE(0), M_SR_ORDER6_STATE(0), M_SR_ORDER7_STATE(0), M_SR_ORDER8_STATE(0), M_SR_ORDER9_STATE(0), M_SR_ORDER10_STATE(0), M_HEARTBEATPCOS(0), M_OVERRIDE(0), M_POSACT_X(0), M_POSACT_Y(0), M_POSACT_Z(0), M_POSACT_A(0), M_POSACT_B(0), M_POSACT_C(0), M_POSACT_STATUS(0), M_POSACT_TURN(0), M_TOOLACT(0), M_BASEACT(0), M_IPOMODE(0), M_AXISACT_A1(0), M_AXISACT_A2(0), M_AXISACT_A3(0), M_AXISACT_A4(0), M_AXISACT_A5(0), M_AXISACT_A6(0), M_AXISACT_A7(0), M_AXISACT_A8(0), M_AXISACT_A9(0), M_AXISACT_A10(0), M_AXISACT_A11(0), M_AXISACT_A12(0), M_VELACT(0), M_WORKSTATES(0), M_AXWORKSTATES(0), M_GROUPSTATE(0), M_ERRORID(0), M_ERRORIDSUB(0), M_ACTIVEPOSORDERID(0), M_ACTIVEORDERIDB(0), M_QUEUECOUNT(0), M_IR_STATUS1(0), M_IR_STATUS2(0), M_IR_STATUS3(0), M_IR_STATUS4(0), M_IR_STATUS5(0), M_IR_STATUS6(0), M_IR_STATUS7(0), M_IR_STATUS8(0), M_ERRORIDPCOS(0), M_FREE_FOR_WOV(0), M_TRANSMISSIONNORET(0), M_ORDERIDRET(0), M_CMDIDRET(0), M_CMDDATARETCS(0), M_RESERVE190(0), M_CMDDATARET1(0), M_CMDDATARET2(0), M_CMDDATARET3(0), M_CMDDATARET4(0), M_CMDDATARET5(0), M_CMDDATARET6(0), M_CMDDATARET7(0), M_CMDDATARET8(0), M_CMDDATARET9(0), M_CMDDATARET10(0), M_CMDDATARET11(0), M_CMDDATARET12(0), M_RESERVE242(0), NCHECKSUM(0), FTMP(0), NTMP1(0), FTMP1(0), BTMP1((PLCIEC::BOOL)FALSE), I(0), ONF_TRIG((PLCIEC::BOOL)FALSE), ENABLETONSUBMIT((PLCIEC::BOOL)FALSE), ENABLETONPCOS((PLCIEC::BOOL)FALSE), M_INITOK((PLCIEC::BOOL)FALSE), M_HEARTBEATLAST(0), M_HEARTBEATLASTPCOS(0), HEARTBEATTO(PLCIEC::MKTIME(1, 0, 0)), TON_1_PCOS(), TON_1_SUBMIT(), TON_2(), M_LASTORDERID(0), R_TRIG_1(), M_CONNECTIONOK((PLCIEC::BOOL)FALSE), M_F_TRIG((PLCIEC::BOOL)FALSE), M_FIRSTCYCLES(0), RETB((PLCIEC::BOOL)FALSE), MXA_RESETCOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (PLCIEC::DINT)0;
         _ERROR = (PLCIEC::BOOL)FALSE;
      };
      if (!(M_INITOK))
      {
         M_INITOK = (PLCIEC::BOOL)TRUE;
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT)
         {
            _ERRORID = (PLCIEC::DINT)505;
            _ERROR = (PLCIEC::BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT = (PLCIEC::BOOL)TRUE;
         };
      };
      if ((M_FIRSTCYCLES < 100))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = (PLCIEC::BOOL)FALSE;
         M_HEARTBEATLAST = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT = (PLCIEC::BOOL)TRUE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKEF = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKE = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RELEASEBRAKE = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.BRAKETEST_REQ_EXT = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MASTERINGTEST_REQ_EXT = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.WRITE_OUT_1TO8 = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (PLCIEC::BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE = (PLCIEC::BOOL)TRUE;
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO <= (PLCIEC::DINT)0))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO = HEARTBEAT;
      };
      HEARTBEATTO = PLCIEC::DINT_TO_TIME(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
      ENABLETONSUBMIT = ((M_HEARTBEATLAST == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT > 0));
      ENABLETONPCOS = ((M_HEARTBEATLASTPCOS == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS > 0));
      if ((((M_HEARTBEATLAST != KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT > 0)) && ((M_HEARTBEATLASTPCOS != KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS > 0))))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = (PLCIEC::BOOL)TRUE;
      };
      // Call FB TON_1
      TON_1_SUBMIT.IN = ENABLETONSUBMIT;
      TON_1_SUBMIT.PT = HEARTBEATTO;
      TON_1_SUBMIT.OnCycle();
      TON_1_PCOS.IN = ENABLETONPCOS;
      TON_1_PCOS.PT = HEARTBEATTO;
      TON_1_PCOS.OnCycle();
 
      M_HEARTBEATLAST = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      M_HEARTBEATLASTPCOS = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS;
      if (TON_1_SUBMIT.Q || TON_1_PCOS.Q)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = (PLCIEC::BOOL)FALSE;
      };
      ONF_TRIG = (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && M_F_TRIG);
      M_F_TRIG = KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE;
      if (ONF_TRIG)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = (PLCIEC::DINT)510;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = (PLCIEC::BOOL)FALSE;
      };
      // Call FB TON_2
      TON_2.IN = (((KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > (PLCIEC::DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == M_LASTORDERID)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET));
      TON_2.PT = PLCIEC::DINT_TO_TIME((KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO * (PLCIEC::DINT)1));
      TON_2.OnCycle();
      M_LASTORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      // Call FB R_TRIG_1
      R_TRIG_1.CLK = TON_2.Q;
      R_TRIG_1.OnCycle();
      if (R_TRIG_1.Q)
      {
         _ERRORID = (PLCIEC::DINT)511;
         _ERROR = (PLCIEC::BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
      };
      if ((TON_2.Q && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == (PLCIEC::DINT)0)))
      {
         _ERRORID = (PLCIEC::DINT)0;
         _ERROR = (PLCIEC::BOOL)FALSE;
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      M_AE_RC_RDY1 = IsBitSet(KRC4_INPUT[0], 0);
      M_AE_ALARM_STOP = IsBitSet(KRC4_INPUT[0], 1);
      M_AE_USER_SAF = IsBitSet(KRC4_INPUT[0], 2);
      M_AE_PERI_RDY = IsBitSet(KRC4_INPUT[0], 3);
      M_AE_ROB_CAL = IsBitSet(KRC4_INPUT[0], 4);
      M_AE_IO_ACTCONF = IsBitSet(KRC4_INPUT[0], 5);
      M_AE_STOPMESS = IsBitSet(KRC4_INPUT[0], 6);
      M_AE_PGNO_FBIT_REFL = IsBitSet(KRC4_INPUT[0], 7);
      M_AE_INT_ESTOP = IsBitSet(KRC4_INPUT[1], 0);
      M_AE_PRO_ACT = IsBitSet(KRC4_INPUT[1], 1);
      M_AE_PGNO_REQ = IsBitSet(KRC4_INPUT[1], 2);
      M_AE_APPL_RUN = IsBitSet(KRC4_INPUT[1], 3);
      M_AE_PRO_MOVE = IsBitSet(KRC4_INPUT[1], 4);
      M_AE_IN_HOME = IsBitSet(KRC4_INPUT[1], 5);
      M_AE_ON_PATH = IsBitSet(KRC4_INPUT[1], 6);
      M_AE_NEAR_POSRET = IsBitSet(KRC4_INPUT[1], 7);
      M_AE_ROB_STOPPED = IsBitSet(KRC4_INPUT[2], 0);
      M_AE_T1 = IsBitSet(KRC4_INPUT[2], 1);
      M_AE_T2 = IsBitSet(KRC4_INPUT[2], 2);
      M_AE_AUT = IsBitSet(KRC4_INPUT[2], 3);
      M_AE_EXT = IsBitSet(KRC4_INPUT[2], 4);
      M_BRAKETEST_MONTIME = IsBitSet(KRC4_INPUT[2], 5);
      M_BRAKETEST_REQ_INT = IsBitSet(KRC4_INPUT[2], 6);
      M_BRAKETEST_WORK = IsBitSet(KRC4_INPUT[2], 7);
      M_BRAKES_OK = IsBitSet(KRC4_INPUT[3], 0);
      M_BRAKETEST_WARN = IsBitSet(KRC4_INPUT[3], 1);
      M_ABORTACTIVE = IsBitSet(KRC4_INPUT[3], 2);
      M_BRAKEACTIVE = IsBitSet(KRC4_INPUT[3], 3);
      M_KCP_CONNECT = IsBitSet(KRC4_INPUT[3], 4);
      M_TOUCHUP = IsBitSet(KRC4_INPUT[3], 5);
      M_MASTEST_REQ_INT = IsBitSet(KRC4_INPUT[3], 6);
      M_MASTESTSWITCH_OK = IsBitSet(KRC4_INPUT[3], 7);
      M_POS_ACT_VALID = IsBitSet(KRC4_INPUT[58], 0);
      RETB = MXA_GETIO_BYTE(4, KRC4_INPUT, M_HEARTBEATSUBMIT);
      RETB = MXA_GETIO_BYTE(5, KRC4_INPUT, M_IN_VAL_1TO8);
      RETB = MXA_GETIO_INT(6, KRC4_INPUT, M_TOUCHUP_POSNO);
      RETB = MXA_GETIO_DINT(8, KRC4_INPUT, M_SR_ORDER1_ID);
      RETB = MXA_GETIO_DINT(12, KRC4_INPUT, M_SR_ORDER2_ID);
      RETB = MXA_GETIO_DINT(16, KRC4_INPUT, M_SR_ORDER3_ID);
      RETB = MXA_GETIO_DINT(20, KRC4_INPUT, M_SR_ORDER4_ID);
      RETB = MXA_GETIO_DINT(24, KRC4_INPUT, M_SR_ORDER5_ID);
      RETB = MXA_GETIO_DINT(28, KRC4_INPUT, M_SR_ORDER6_ID);
      RETB = MXA_GETIO_DINT(32, KRC4_INPUT, M_SR_ORDER7_ID);
      RETB = MXA_GETIO_DINT(36, KRC4_INPUT, M_SR_ORDER8_ID);
      RETB = MXA_GETIO_DINT(40, KRC4_INPUT, M_SR_ORDER9_ID);
      RETB = MXA_GETIO_DINT(44, KRC4_INPUT, M_SR_ORDER10_ID);
      RETB = MXA_GETIO_BYTE(48, KRC4_INPUT, M_SR_ORDER1_STATE);
      RETB = MXA_GETIO_BYTE(49, KRC4_INPUT, M_SR_ORDER2_STATE);
      RETB = MXA_GETIO_BYTE(50, KRC4_INPUT, M_SR_ORDER3_STATE);
      RETB = MXA_GETIO_BYTE(51, KRC4_INPUT, M_SR_ORDER4_STATE);
      RETB = MXA_GETIO_BYTE(52, KRC4_INPUT, M_SR_ORDER5_STATE);
      RETB = MXA_GETIO_BYTE(53, KRC4_INPUT, M_SR_ORDER6_STATE);
      RETB = MXA_GETIO_BYTE(54, KRC4_INPUT, M_SR_ORDER7_STATE);
      RETB = MXA_GETIO_BYTE(55, KRC4_INPUT, M_SR_ORDER8_STATE);
      RETB = MXA_GETIO_BYTE(56, KRC4_INPUT, M_SR_ORDER9_STATE);
      RETB = MXA_GETIO_BYTE(57, KRC4_INPUT, M_SR_ORDER10_STATE);
      RETB = MXA_GETIO_BYTE(59, KRC4_INPUT, M_HEARTBEATPCOS);
      RETB = MXA_GETIO_BYTE(60, KRC4_INPUT, M_OVERRIDE);
      RETB = MXA_GETIO_REAL(61, KRC4_INPUT, M_POSACT_X);
      RETB = MXA_GETIO_REAL(65, KRC4_INPUT, M_POSACT_Y);
      RETB = MXA_GETIO_REAL(69, KRC4_INPUT, M_POSACT_Z);
      RETB = MXA_GETIO_REAL(73, KRC4_INPUT, M_POSACT_A);
      RETB = MXA_GETIO_REAL(77, KRC4_INPUT, M_POSACT_B);
      RETB = MXA_GETIO_REAL(81, KRC4_INPUT, M_POSACT_C);
      RETB = MXA_GETIO_DINT(85, KRC4_INPUT, M_POSACT_STATUS);
      RETB = MXA_GETIO_BYTE(89, KRC4_INPUT, M_POSACT_TURN);
      RETB = MXA_GETIO_SINT(90, KRC4_INPUT, M_TOOLACT);
      RETB = MXA_GETIO_SINT(91, KRC4_INPUT, M_BASEACT);
      RETB = MXA_GETIO_BYTE(92, KRC4_INPUT, M_IPOMODE);
      RETB = MXA_GETIO_REAL(93, KRC4_INPUT, M_AXISACT_A1);
      RETB = MXA_GETIO_REAL(97, KRC4_INPUT, M_AXISACT_A2);
      RETB = MXA_GETIO_REAL(101, KRC4_INPUT, M_AXISACT_A3);
      RETB = MXA_GETIO_REAL(105, KRC4_INPUT, M_AXISACT_A4);
      RETB = MXA_GETIO_REAL(109, KRC4_INPUT, M_AXISACT_A5);
      RETB = MXA_GETIO_REAL(113, KRC4_INPUT, M_AXISACT_A6);
      RETB = MXA_GETIO_REAL(117, KRC4_INPUT, M_AXISACT_A7);
      RETB = MXA_GETIO_REAL(121, KRC4_INPUT, M_AXISACT_A8);
      RETB = MXA_GETIO_REAL(125, KRC4_INPUT, M_AXISACT_A9);
      RETB = MXA_GETIO_REAL(129, KRC4_INPUT, M_AXISACT_A10);
      RETB = MXA_GETIO_REAL(133, KRC4_INPUT, M_AXISACT_A11);
      RETB = MXA_GETIO_REAL(137, KRC4_INPUT, M_AXISACT_A12);
      RETB = MXA_GETIO_REAL(141, KRC4_INPUT, M_VELACT);
      RETB = MXA_GETIO_BYTE(155, KRC4_INPUT, M_WORKSTATES);
      RETB = MXA_GETIO_BYTE(156, KRC4_INPUT, M_AXWORKSTATES);
      RETB = MXA_GETIO_BYTE(157, KRC4_INPUT, M_GROUPSTATE);
      RETB = MXA_GETIO_INT(158, KRC4_INPUT, M_ERRORID);
      RETB = MXA_GETIO_INT(160, KRC4_INPUT, M_ERRORIDSUB);
      RETB = MXA_GETIO_DINT(162, KRC4_INPUT, M_ACTIVEPOSORDERID);
      RETB = MXA_GETIO_DINT(166, KRC4_INPUT, M_ACTIVEORDERIDB);
      RETB = MXA_GETIO_BYTE(170, KRC4_INPUT, M_QUEUECOUNT);
      RETB = MXA_GETIO_NIBBLE(171, KRC4_INPUT, M_IR_STATUS1, M_IR_STATUS2);
      RETB = MXA_GETIO_NIBBLE(172, KRC4_INPUT, M_IR_STATUS3, M_IR_STATUS4);
      RETB = MXA_GETIO_NIBBLE(173, KRC4_INPUT, M_IR_STATUS5, M_IR_STATUS6);
      RETB = MXA_GETIO_NIBBLE(174, KRC4_INPUT, M_IR_STATUS7, M_IR_STATUS8);
      RETB = MXA_GETIO_BYTE(175, KRC4_INPUT, M_ERRORIDPCOS);
      RETB = MXA_GETIO_BYTE(176, KRC4_INPUT, M_FREE_FOR_WOV);
      RETB = MXA_GETIO_BYTE(177, KRC4_INPUT, M_TRANSMISSIONNORET);
      RETB = MXA_GETIO_DINT(178, KRC4_INPUT, M_ORDERIDRET);
      RETB = MXA_GETIO_DINT(182, KRC4_INPUT, M_CMDIDRET);
      RETB = MXA_GETIO_DINT(186, KRC4_INPUT, M_CMDDATARETCS);
      RETB = MXA_GETIO_DINT(190, KRC4_INPUT, M_RESERVE190);
      RETB = MXA_GETIO_REAL(194, KRC4_INPUT, M_CMDDATARET1);
      RETB = MXA_GETIO_REAL(198, KRC4_INPUT, M_CMDDATARET2);
      RETB = MXA_GETIO_REAL(202, KRC4_INPUT, M_CMDDATARET3);
      RETB = MXA_GETIO_REAL(206, KRC4_INPUT, M_CMDDATARET4);
      RETB = MXA_GETIO_REAL(210, KRC4_INPUT, M_CMDDATARET5);
      RETB = MXA_GETIO_REAL(214, KRC4_INPUT, M_CMDDATARET6);
      RETB = MXA_GETIO_REAL(218, KRC4_INPUT, M_CMDDATARET7);
      RETB = MXA_GETIO_REAL(222, KRC4_INPUT, M_CMDDATARET8);
      RETB = MXA_GETIO_REAL(226, KRC4_INPUT, M_CMDDATARET9);
      RETB = MXA_GETIO_REAL(230, KRC4_INPUT, M_CMDDATARET10);
      RETB = MXA_GETIO_REAL(234, KRC4_INPUT, M_CMDDATARET11);
      RETB = MXA_GETIO_REAL(238, KRC4_INPUT, M_CMDDATARET12);
      RETB = MXA_GETIO_DINT(242, KRC4_INPUT, M_RESERVE242);
      M_CONNECTIONOK = (KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.RC_RDY1 = M_AE_RC_RDY1;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP = M_AE_ALARM_STOP;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE = M_AE_USER_SAF;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY = M_AE_PERI_RDY;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ROB_CAL = M_AE_ROB_CAL;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.IO_ACTCONF = M_AE_IO_ACTCONF;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS = M_AE_STOPMESS;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PGNO_FBIT_REFL = M_AE_PGNO_FBIT_REFL;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.INTNOTAUS = M_AE_INT_ESTOP;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT = M_AE_PRO_ACT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PGNO_REQ = M_AE_PGNO_REQ;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.APPL_RUN = M_AE_APPL_RUN;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_MOVE = M_AE_PRO_MOVE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.IN_HOME = M_AE_IN_HOME;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ON_PATH = M_AE_ON_PATH;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.NEAR_POSRET = M_AE_NEAR_POSRET;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ROB_STOPPED = M_AE_ROB_STOPPED;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.T1 = M_AE_T1;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.T2 = M_AE_T2;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.AUT = M_AE_AUT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT = M_AE_EXT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.KCP_CONNECT = M_KCP_CONNECT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_MONTIME = M_BRAKETEST_MONTIME;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_REQ_INT = M_BRAKETEST_REQ_INT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_WORK = M_BRAKETEST_WORK;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKES_OK = M_BRAKES_OK;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_WARN = M_BRAKETEST_WARN;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.MASTERINGTEST_REQ_INT = M_MASTEST_REQ_INT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.MASTERINGTESTSWITCH_OK = M_MASTESTSWITCH_OK;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACTVALID = (M_POS_ACT_VALID && M_CONNECTIONOK);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACTVALID = M_CONNECTIONOK;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.BRAKEACTIVE = M_BRAKEACTIVE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ABORTACTIVE = M_ABORTACTIVE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOUCHUP = M_TOUCHUP;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOUCHUP_INDEX = M_TOUCHUP_POSNO;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT = M_HEARTBEATSUBMIT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS = M_HEARTBEATPCOS;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.OVPROACT = M_OVERRIDE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.QUEUECOUNT = M_QUEUECOUNT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.X = M_POSACT_X;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.Y = M_POSACT_Y;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.Z = M_POSACT_Z;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.A = M_POSACT_A;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.B = M_POSACT_B;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.C = M_POSACT_C;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.E1 = M_AXISACT_A7;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.E2 = M_AXISACT_A8;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.E3 = M_AXISACT_A9;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.E4 = M_AXISACT_A10;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.E5 = M_AXISACT_A11;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.E6 = M_AXISACT_A12;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.STATUS = PLCIEC::DINT_TO_INT(M_POSACT_STATUS);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.TURN = M_POSACT_TURN;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOOLACT = M_TOOLACT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.BASEACT = M_BASEACT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IPOMODEACT = M_IPOMODE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A1 = M_AXISACT_A1;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A2 = M_AXISACT_A2;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A3 = M_AXISACT_A3;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A4 = M_AXISACT_A4;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A5 = M_AXISACT_A5;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A6 = M_AXISACT_A6;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E1 = M_AXISACT_A7;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E2 = M_AXISACT_A8;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E3 = M_AXISACT_A9;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E4 = M_AXISACT_A10;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E5 = M_AXISACT_A11;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E6 = M_AXISACT_A12;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.VELACT = M_VELACT;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES = M_WORKSTATES;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES = M_AXWORKSTATES;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.GROUPSTATE = M_GROUPSTATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID = M_ERRORID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB = M_ERRORIDSUB;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDPCOS = M_ERRORIDPCOS;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ACTIVEPOSORDERID = M_ACTIVEPOSORDERID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ACTIVEORDERIDB = M_ACTIVEORDERIDB;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8 = M_IN_VAL_1TO8;
      if ((M_FIRSTCYCLES < 100))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID = 0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = 0;
         M_FIRSTCYCLES = (M_FIRSTCYCLES + 1);
      };
      if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB = 0;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[1].SR_ORDERID = M_SR_ORDER1_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[2].SR_ORDERID = M_SR_ORDER2_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[3].SR_ORDERID = M_SR_ORDER3_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[4].SR_ORDERID = M_SR_ORDER4_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[5].SR_ORDERID = M_SR_ORDER5_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[6].SR_ORDERID = M_SR_ORDER6_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[7].SR_ORDERID = M_SR_ORDER7_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[8].SR_ORDERID = M_SR_ORDER8_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[9].SR_ORDERID = M_SR_ORDER9_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[10].SR_ORDERID = M_SR_ORDER10_ID;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[1].SR_STATE = M_SR_ORDER1_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[2].SR_STATE = M_SR_ORDER2_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[3].SR_STATE = M_SR_ORDER3_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[4].SR_STATE = M_SR_ORDER4_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[5].SR_STATE = M_SR_ORDER5_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[6].SR_STATE = M_SR_ORDER6_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[7].SR_STATE = M_SR_ORDER7_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[8].SR_STATE = M_SR_ORDER8_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[9].SR_STATE = M_SR_ORDER9_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[10].SR_STATE = M_SR_ORDER10_STATE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.TRANSMISSIONNORET = M_TRANSMISSIONNORET;
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == M_ORDERIDRET))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET = M_CMDIDRET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET = M_ORDERIDRET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSKRC = M_CMDDATARETCS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1] = M_CMDDATARET1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2] = M_CMDDATARET2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3] = M_CMDDATARET3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4] = M_CMDDATARET4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5] = M_CMDDATARET5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6] = M_CMDDATARET6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7] = M_CMDDATARET7;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8] = M_CMDDATARET8;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9] = M_CMDDATARET9;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10] = M_CMDDATARET10;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11] = M_CMDDATARET11;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12] = M_CMDDATARET12;
         NCHECKSUM = (PLCIEC::DWORD)0;
         for (I = 1; I <= 12; I += 1)
         {
            FTMP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[I];
            NTMP1 = PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((FTMP - 0.5) * 10.0));
            FTMP1 = static_cast<PLCIEC::REAL>((NTMP1 / 10) + 0.5);
            BTMP1 = (FTMP == FTMP1);
            if (BTMP1)
            {
               if ((FTMP > 0))
               {
                  FTMP = (FTMP + static_cast<PLCIEC::REAL>(0.01));
               }
               else
               {
                  FTMP = (FTMP - static_cast<PLCIEC::REAL>(0.01));
               };
            };
            if (((FTMP > 2147483500.0) || (FTMP < -(2147483500.0))))
            {
               NCHECKSUM = 0;
            };
            NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(PLCIEC::REAL_TO_DINT(FTMP)));
         };
         NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET));
         NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET));
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSPLC = PLCIEC::DWORD_TO_DINT(NCHECKSUM);
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[1] = M_IR_STATUS1;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[2] = M_IR_STATUS2;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[3] = M_IR_STATUS3;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[4] = M_IR_STATUS4;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[5] = M_IR_STATUS5;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[6] = M_IR_STATUS6;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[7] = M_IR_STATUS7;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[8] = M_IR_STATUS8;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READMXASTATUS
 ******************************************************************************/
class KRC_READMXASTATUS
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::INT &STATUS;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::INT _STATUS;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READMXASTATUS()
       : AXISGROUPIDX(0), STATUS(_STATUS), ERROR(_ERROR), ERRORID(_ERRORID), _STATUS(0), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = (PLCIEC::DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (PLCIEC::DINT)0;
         _ERROR = (PLCIEC::BOOL)FALSE;
      };
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         _STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.GROUPSTATE;
      }
      else
      {
         _STATUS = 0;
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETOVERRIDE
 ******************************************************************************/
class KRC_SETOVERRIDE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::INT OVERRIDE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::INT &ACTUALOVERRIDE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::INT _ACTUALOVERRIDE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_SETOVERRIDE()
       : AXISGROUPIDX(0), OVERRIDE(0), VALID(_VALID), ACTUALOVERRIDE(_ACTUALOVERRIDE), ERROR(_ERROR), ERRORID(_ERRORID), _VALID((PLCIEC::BOOL)FALSE), _ACTUALOVERRIDE(0), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = (PLCIEC::DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      };
      if (((OVERRIDE >= 0) && (OVERRIDE <= 100)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE = OVERRIDE;
         _ERRORID = (PLCIEC::DINT)0;
      }
      else
      {
         _ERRORID = (PLCIEC::DINT)504;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _ACTUALOVERRIDE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.OVPROACT;
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      _ERROR = (_ERRORID != (PLCIEC::DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TECHFUNCTION
 ******************************************************************************/
class KRC_TECHFUNCTION
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT TECHFUNCTIONID;
   PLCIEC::INT PARAMETERCOUNT;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR_IN_OUT */

public:
   PLCIEC::BOOL *BOOL_DATA;
   PLCIEC::DINT *INT_DATA;
   PLCIEC::REAL *REAL_DATA;

   /* VAR */

private:
   PLCIEC::INT I;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_TECHFUNCTION()
       : AXISGROUPIDX(0), EXECUTECMD((PLCIEC::BOOL)FALSE), TECHFUNCTIONID(0), PARAMETERCOUNT(0), BUFFERMODE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY((PLCIEC::BOOL)FALSE), _ACTIVE((PLCIEC::BOOL)FALSE), _DONE((PLCIEC::BOOL)FALSE), _ABORTED((PLCIEC::BOOL)FALSE), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), _ORDERID(0), BOOL_DATA(), INT_DATA(), REAL_DATA(), I(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = (PLCIEC::DINT)0;
      _ERRORID = (PLCIEC::DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      };
      if (((PARAMETERCOUNT < 1) || (PARAMETERCOUNT > 40)))
      {
         _ERRORID = (PLCIEC::DINT)521;
         _ERROR = (PLCIEC::BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         return;
      };
      for (I = (PARAMETERCOUNT + 1); I <= 40; I += 1)
      {
         if ((((BOOL_DATA[I] == (PLCIEC::BOOL)TRUE) || (INT_DATA[I] != 0)) || (REAL_DATA[I] != 0.0)))
         {
            _ERRORID = (PLCIEC::DINT)522;
            _ERROR = (PLCIEC::BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            return;
         };
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = 35;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 3;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (PLCIEC::BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (PLCIEC::BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[41] = PLCIEC::INT_TO_DINT(TECHFUNCTIONID);
         for (I = 1; I <= 40; I += 1)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] = BOOL_DATA[I];
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I] = INT_DATA[I];
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = REAL_DATA[I];
         };
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (PLCIEC::DINT)0);
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEAXISGROUP
 ******************************************************************************/
class KRC_WRITEAXISGROUP
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BYTE *KRC4_OUTPUT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

   /* VAR */

private:
   PLCIEC::DWORD NCHECKSUM;
   PLCIEC::INT I;
   PLCIEC::DINT LASTORDERID;
   PLCIEC::INT LASTTGNUMBER;
   PLCIEC::INT LASTTGTYPE;
   PLCIEC::DINT M_COMMANDID;
   PLCIEC::DINT M_ORDERID;
   PLCIEC::BOOL M_PROFINETERR;
   PLCIEC::DWORD M_PROFINETSTATUS;
   PLCIEC::INT M_ANZTELEGRAMME;
   PLCIEC::BOOL AE_PGNO_FBIT_VAL;
   PLCIEC::BOOL AE_PGNO_BIT1_VAL;
   PLCIEC::BOOL AE_PGNO_BIT2_VAL;
   PLCIEC::BOOL AE_PGNO_BIT3_VAL;
   PLCIEC::BOOL AE_PGNO_BIT4_VAL;
   PLCIEC::BOOL AE_PGNO_BIT5_VAL;
   PLCIEC::BOOL AE_PGNO_BIT6_VAL;
   PLCIEC::BOOL AE_PGNO_BIT7_VAL;
   PLCIEC::BOOL AE_PGNO_PARITY_VAL;
   PLCIEC::BOOL AE_PGNO_VALID_VAL;
   PLCIEC::BOOL AE_EXT_START_VAL;
   PLCIEC::BOOL AE_MOVE_ENABLE_VAL;
   PLCIEC::BOOL AE_CONF_MESS_VAL;
   PLCIEC::BOOL AE_DRIVES_OFF_VAL;
   PLCIEC::BOOL AE_DRIVES_ON_VAL;
   PLCIEC::BOOL MASTEST_REQ_EXT_VAL;
   PLCIEC::BOOL BRAKETEST_REQ_EXT_VAL;
   PLCIEC::BOOL AE_RESET_VAL;
   PLCIEC::BOOL BRAKE_VAL;
   PLCIEC::BOOL BRAKE_F_VAL;
   PLCIEC::BOOL RELEASE_BRAKE_VAL;
   PLCIEC::BOOL SHOW_TRACE_VAL;
   PLCIEC::BOOL MESSAGE_RESET_VAL;
   PLCIEC::BOOL OUT_VAL_1_VAL;
   PLCIEC::BOOL OUT_VAL_2_VAL;
   PLCIEC::BOOL OUT_VAL_3_VAL;
   PLCIEC::BOOL OUT_VAL_4_VAL;
   PLCIEC::BOOL OUT_VAL_5_VAL;
   PLCIEC::BOOL OUT_VAL_6_VAL;
   PLCIEC::BOOL OUT_VAL_7_VAL;
   PLCIEC::BOOL OUT_VAL_8_VAL;
   PLCIEC::BOOL WRITE_OUT_1TO8_VAL;
   PLCIEC::BOOL JOG_ADVANCED_VAL;
   PLCIEC::INT ZW_JOG_AD_STATE_VAL;
   PLCIEC::BYTE JOG_AD_STATE;
   PLCIEC::BYTE HEARTBEAT_VAL;
   PLCIEC::BYTE OVERRIDE_VAL;
   PLCIEC::DINT PLC_MAJOR_VAL;
   PLCIEC::DINT PLC_MINOR_VAL;
   PLCIEC::DINT SR_ORDER1_ID_VAL;
   PLCIEC::DINT SR_ORDER2_ID_VAL;
   PLCIEC::DINT SR_ORDER3_ID_VAL;
   PLCIEC::DINT SR_ORDER4_ID_VAL;
   PLCIEC::DINT SR_ORDER5_ID_VAL;
   PLCIEC::DINT SR_ORDER6_ID_VAL;
   PLCIEC::DINT SR_ORDER7_ID_VAL;
   PLCIEC::DINT SR_ORDER8_ID_VAL;
   PLCIEC::DINT SR_ORDER9_ID_VAL;
   PLCIEC::DINT SR_ORDER10_ID_VAL;
   PLCIEC::BYTE SR_ORDER1_STATE_VAL;
   PLCIEC::BYTE SR_ORDER2_STATE_VAL;
   PLCIEC::BYTE SR_ORDER3_STATE_VAL;
   PLCIEC::BYTE SR_ORDER4_STATE_VAL;
   PLCIEC::BYTE SR_ORDER5_STATE_VAL;
   PLCIEC::BYTE SR_ORDER6_STATE_VAL;
   PLCIEC::BYTE SR_ORDER7_STATE_VAL;
   PLCIEC::BYTE SR_ORDER8_STATE_VAL;
   PLCIEC::BYTE SR_ORDER9_STATE_VAL;
   PLCIEC::BYTE SR_ORDER10_STATE_VAL;
   PLCIEC::DINT CMDPAR_INT1_VAL;
   PLCIEC::DINT CMDPAR_INT2_VAL;
   PLCIEC::DINT CMDPAR_INT3_VAL;
   PLCIEC::DINT CMDPAR_INT4_VAL;
   PLCIEC::DINT CMDPAR_INT5_VAL;
   PLCIEC::DINT CMDPAR_INT6_VAL;
   PLCIEC::DINT CMDPAR_INT7_VAL;
   PLCIEC::DINT CMDPAR_INT8_VAL;
   PLCIEC::DINT CMDPAR_INT9_VAL;
   PLCIEC::DINT CMDPAR_INT10_VAL;
   PLCIEC::DINT CMDPAR_INT11_VAL;
   PLCIEC::DINT CMDPAR_INT12_VAL;
   PLCIEC::DINT CMDPAR_INT13_VAL;
   PLCIEC::DINT CMDPAR_INT14_VAL;
   PLCIEC::DINT CMDPAR_INT15_VAL;
   PLCIEC::REAL CMDPAR_REAL1_VAL;
   PLCIEC::REAL CMDPAR_REAL2_VAL;
   PLCIEC::REAL CMDPAR_REAL3_VAL;
   PLCIEC::REAL CMDPAR_REAL4_VAL;
   PLCIEC::REAL CMDPAR_REAL5_VAL;
   PLCIEC::REAL CMDPAR_REAL6_VAL;
   PLCIEC::REAL CMDPAR_REAL7_VAL;
   PLCIEC::REAL CMDPAR_REAL8_VAL;
   PLCIEC::REAL CMDPAR_REAL9_VAL;
   PLCIEC::REAL CMDPAR_REAL10_VAL;
   PLCIEC::REAL CMDPAR_REAL11_VAL;
   PLCIEC::REAL CMDPAR_REAL12_VAL;
   PLCIEC::REAL CMDPAR_REAL13_VAL;
   PLCIEC::REAL CMDPAR_REAL14_VAL;
   PLCIEC::REAL CMDPAR_REAL15_VAL;
   PLCIEC::DWORD CHECKSUM_VAL;
   PLCIEC::INT TRANSMISSIONNO1_VAL;
   PLCIEC::INT TRANSMISSIONNO2_VAL;
   PLCIEC::INT TRANSMISSIONTYPE_VAL;
   PLCIEC::DINT ORDERID_VAL;
   PLCIEC::INT CMDID_VAL;
   PLCIEC::INT BUFFERMODE_VAL;
   PLCIEC::WORD BOOLVALUES1;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;
   PLCIEC::BOOL DUMMY;

   /* VAR_TEMP */

private:
   PLCIEC::REAL FTMP;
   PLCIEC::DINT NTMP1;
   PLCIEC::REAL FTMP1;
   PLCIEC::BOOL BTMP1;
   PLCIEC::BOOL BMAXREALERR;

public:
   KRC_WRITEAXISGROUP()
       : AXISGROUPIDX(0), KRC4_OUTPUT(), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR((PLCIEC::BOOL)FALSE), _ERRORID(0), NCHECKSUM(0), I(0), LASTORDERID(0), LASTTGNUMBER(0), LASTTGTYPE(0), M_COMMANDID(0), M_ORDERID(0), M_PROFINETERR((PLCIEC::BOOL)FALSE), M_PROFINETSTATUS(0), M_ANZTELEGRAMME(0), AE_PGNO_FBIT_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT1_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT2_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT3_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT4_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT5_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT6_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_BIT7_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_PARITY_VAL((PLCIEC::BOOL)FALSE), AE_PGNO_VALID_VAL((PLCIEC::BOOL)FALSE), AE_EXT_START_VAL((PLCIEC::BOOL)FALSE), AE_MOVE_ENABLE_VAL((PLCIEC::BOOL)FALSE), AE_CONF_MESS_VAL((PLCIEC::BOOL)FALSE), AE_DRIVES_OFF_VAL((PLCIEC::BOOL)FALSE), AE_DRIVES_ON_VAL((PLCIEC::BOOL)FALSE), MASTEST_REQ_EXT_VAL((PLCIEC::BOOL)FALSE), BRAKETEST_REQ_EXT_VAL((PLCIEC::BOOL)FALSE), AE_RESET_VAL((PLCIEC::BOOL)FALSE), BRAKE_VAL((PLCIEC::BOOL)FALSE), BRAKE_F_VAL((PLCIEC::BOOL)FALSE), RELEASE_BRAKE_VAL((PLCIEC::BOOL)FALSE), SHOW_TRACE_VAL((PLCIEC::BOOL)FALSE), MESSAGE_RESET_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_1_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_2_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_3_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_4_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_5_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_6_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_7_VAL((PLCIEC::BOOL)FALSE), OUT_VAL_8_VAL((PLCIEC::BOOL)FALSE), WRITE_OUT_1TO8_VAL((PLCIEC::BOOL)FALSE), JOG_ADVANCED_VAL((PLCIEC::BOOL)FALSE), ZW_JOG_AD_STATE_VAL(0), JOG_AD_STATE(0), HEARTBEAT_VAL(0), OVERRIDE_VAL(0), PLC_MAJOR_VAL(0), PLC_MINOR_VAL(0), SR_ORDER1_ID_VAL(0), SR_ORDER2_ID_VAL(0), SR_ORDER3_ID_VAL(0), SR_ORDER4_ID_VAL(0), SR_ORDER5_ID_VAL(0), SR_ORDER6_ID_VAL(0), SR_ORDER7_ID_VAL(0), SR_ORDER8_ID_VAL(0), SR_ORDER9_ID_VAL(0), SR_ORDER10_ID_VAL(0), SR_ORDER1_STATE_VAL(0), SR_ORDER2_STATE_VAL(0), SR_ORDER3_STATE_VAL(0), SR_ORDER4_STATE_VAL(0), SR_ORDER5_STATE_VAL(0), SR_ORDER6_STATE_VAL(0), SR_ORDER7_STATE_VAL(0), SR_ORDER8_STATE_VAL(0), SR_ORDER9_STATE_VAL(0), SR_ORDER10_STATE_VAL(0), CMDPAR_INT1_VAL(0), CMDPAR_INT2_VAL(0), CMDPAR_INT3_VAL(0), CMDPAR_INT4_VAL(0), CMDPAR_INT5_VAL(0), CMDPAR_INT6_VAL(0), CMDPAR_INT7_VAL(0), CMDPAR_INT8_VAL(0), CMDPAR_INT9_VAL(0), CMDPAR_INT10_VAL(0), CMDPAR_INT11_VAL(0), CMDPAR_INT12_VAL(0), CMDPAR_INT13_VAL(0), CMDPAR_INT14_VAL(0), CMDPAR_INT15_VAL(0), CMDPAR_REAL1_VAL(0), CMDPAR_REAL2_VAL(0), CMDPAR_REAL3_VAL(0), CMDPAR_REAL4_VAL(0), CMDPAR_REAL5_VAL(0), CMDPAR_REAL6_VAL(0), CMDPAR_REAL7_VAL(0), CMDPAR_REAL8_VAL(0), CMDPAR_REAL9_VAL(0), CMDPAR_REAL10_VAL(0), CMDPAR_REAL11_VAL(0), CMDPAR_REAL12_VAL(0), CMDPAR_REAL13_VAL(0), CMDPAR_REAL14_VAL(0), CMDPAR_REAL15_VAL(0), CHECKSUM_VAL(0), TRANSMISSIONNO1_VAL(0), TRANSMISSIONNO2_VAL(0), TRANSMISSIONTYPE_VAL(0), ORDERID_VAL(0), CMDID_VAL(0), BUFFERMODE_VAL(0), BOOLVALUES1(0), MXA_RESETCOMMAND_1(), DUMMY((PLCIEC::BOOL)FALSE), FTMP(0), NTMP1(0), FTMP1(0), BTMP1((PLCIEC::BOOL)FALSE), BMAXREALERR((PLCIEC::BOOL)FALSE)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = (PLCIEC::DINT)0;
      NCHECKSUM = (PLCIEC::DWORD)0;
      BMAXREALERR = (PLCIEC::BOOL)FALSE;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (PLCIEC::DINT)506;
         _ERROR = (PLCIEC::BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (PLCIEC::DINT)0;
         _ERROR = (PLCIEC::BOOL)FALSE;
      };
      if (((KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > (PLCIEC::DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET)))
      {
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE == (PLCIEC::BOOL)FALSE))
      {
         _ERRORID = (PLCIEC::DINT)507;
         _ERROR = (PLCIEC::BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
      }
      else
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE = (PLCIEC::BOOL)FALSE;
      };
      AE_PGNO_FBIT_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT1_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT2_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT3_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT4_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT5_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT6_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_BIT7_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_PARITY_VAL = (PLCIEC::BOOL)FALSE;
      AE_PGNO_VALID_VAL = (PLCIEC::BOOL)FALSE;
      AE_EXT_START_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.EXT_START;
      AE_MOVE_ENABLE_VAL = ((((((KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE && !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_DISABLE)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID == (PLCIEC::DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB == (PLCIEC::DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == (PLCIEC::DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID == (PLCIEC::DINT)0));
      AE_CONF_MESS_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS;
      AE_DRIVES_OFF_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESOFF;
      AE_DRIVES_ON_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON;
      BRAKETEST_REQ_EXT_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.BRAKETEST_REQ_EXT;
      MASTEST_REQ_EXT_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MASTERINGTEST_REQ_EXT;
      AE_RESET_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET;
      BRAKE_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKE;
      BRAKE_F_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKEF;
      RELEASE_BRAKE_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RELEASEBRAKE;
      SHOW_TRACE_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.SHOWTRACE;
      MESSAGE_RESET_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET;
      OUT_VAL_1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_1;
      OUT_VAL_2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_2;
      OUT_VAL_3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_3;
      OUT_VAL_4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_4;
      OUT_VAL_5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_5;
      OUT_VAL_6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_6;
      OUT_VAL_7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_7;
      OUT_VAL_8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_8;
      WRITE_OUT_1TO8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.WRITE_OUT_1TO8;
      HEARTBEAT_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT);
      OVERRIDE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE);
      PLC_MAJOR_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MAJOR;
      PLC_MINOR_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MINOR;
      JOG_ADVANCED_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_ACTIVE;
      ZW_JOG_AD_STATE_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_STATE_VAL;
      SR_ORDER1_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[1].SR_ORDERID;
      SR_ORDER2_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[2].SR_ORDERID;
      SR_ORDER3_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[3].SR_ORDERID;
      SR_ORDER4_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[4].SR_ORDERID;
      SR_ORDER5_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[5].SR_ORDERID;
      SR_ORDER6_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[6].SR_ORDERID;
      SR_ORDER7_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[7].SR_ORDERID;
      SR_ORDER8_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[8].SR_ORDERID;
      SR_ORDER9_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[9].SR_ORDERID;
      SR_ORDER10_ID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[10].SR_ORDERID;
      SR_ORDER1_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[1].SR_STATE);
      SR_ORDER2_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[2].SR_STATE);
      SR_ORDER3_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[3].SR_STATE);
      SR_ORDER4_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[4].SR_STATE);
      SR_ORDER5_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[5].SR_STATE);
      SR_ORDER6_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[6].SR_STATE);
      SR_ORDER7_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[7].SR_STATE);
      SR_ORDER8_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[8].SR_STATE);
      SR_ORDER9_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[9].SR_STATE);
      SR_ORDER10_STATE_VAL = PLCIEC::INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[10].SR_STATE);
      JOG_AD_STATE = PLCIEC::INT_TO_BYTE(ZW_JOG_AD_STATE_VAL);
      if ((LASTORDERID != KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID))
      {
         LASTORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > 0))
         {
            LASTTGNUMBER = (LASTTGNUMBER + 1);
            if (((LASTTGNUMBER <= 0) || (LASTTGNUMBER >= 255)))
            {
               LASTTGNUMBER = 1;
            };
            TRANSMISSIONNO1_VAL = LASTTGNUMBER;
            switch (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE)
            {
            case 1:
               LASTTGTYPE = 1;
               break;
            case 2:
               LASTTGTYPE = 2;
               break;
            case 3:
               LASTTGTYPE = 4;
               break;
            };
            TRANSMISSIONTYPE_VAL = LASTTGTYPE;
            ORDERID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
            CMDID_VAL = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
            BUFFERMODE_VAL = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE);
            ChBit(BOOLVALUES1, 0, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1]);
            ChBit(BOOLVALUES1, 1, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2]);
            ChBit(BOOLVALUES1, 2, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[3]);
            ChBit(BOOLVALUES1, 3, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[4]);
            ChBit(BOOLVALUES1, 4, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[5]);
            ChBit(BOOLVALUES1, 5, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[6]);
            ChBit(BOOLVALUES1, 6, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[7]);
            ChBit(BOOLVALUES1, 7, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[8]);
            ChBit(BOOLVALUES1, 8, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[9]);
            ChBit(BOOLVALUES1, 9, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[10]);
            ChBit(BOOLVALUES1, 10, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[11]);
            ChBit(BOOLVALUES1, 11, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[12]);
            ChBit(BOOLVALUES1, 12, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[13]);
            ChBit(BOOLVALUES1, 13, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[14]);
            ChBit(BOOLVALUES1, 14, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[15]);
            CMDPAR_INT1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1];
            CMDPAR_INT2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2];
            CMDPAR_INT3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3];
            CMDPAR_INT4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4];
            CMDPAR_INT5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5];
            CMDPAR_INT6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6];
            CMDPAR_INT7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[7];
            CMDPAR_INT8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[8];
            CMDPAR_INT9_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[9];
            CMDPAR_INT10_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[10];
            CMDPAR_INT11_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[11];
            CMDPAR_INT12_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[12];
            CMDPAR_INT13_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[13];
            CMDPAR_INT14_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[14];
            CMDPAR_INT15_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[15];
            CMDPAR_REAL1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1];
            CMDPAR_REAL2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2];
            CMDPAR_REAL3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3];
            CMDPAR_REAL4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4];
            CMDPAR_REAL5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5];
            CMDPAR_REAL6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6];
            CMDPAR_REAL7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7];
            CMDPAR_REAL8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8];
            CMDPAR_REAL9_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9];
            CMDPAR_REAL10_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10];
            CMDPAR_REAL11_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11];
            CMDPAR_REAL12_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12];
            CMDPAR_REAL13_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13];
            CMDPAR_REAL14_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14];
            CMDPAR_REAL15_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15];
            NCHECKSUM = PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
            NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID));
            NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE));
            for (I = 1; I <= 45; I += 1)
            {
               if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] == (PLCIEC::BOOL)TRUE))
               {
                  NCHECKSUM = (NCHECKSUM ^ (PLCIEC::DWORD)1);
               };
               NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I]));
               FTMP = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I];
               NTMP1 = PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((FTMP - 0.5) * 10.0));
               FTMP1 = static_cast<PLCIEC::REAL>((NTMP1 / 10) + 0.5);
               BTMP1 = (FTMP == FTMP1);
               if (BTMP1)
               {
                  if ((FTMP > 0))
                  {
                     FTMP = (FTMP + static_cast<PLCIEC::REAL>(0.01));
                  }
                  else
                  {
                     FTMP = (FTMP - static_cast<PLCIEC::REAL>(0.01));
                  };
               };
               NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(PLCIEC::REAL_TO_DINT(FTMP)));
            };
            CHECKSUM_VAL = NCHECKSUM;
            TRANSMISSIONNO2_VAL = LASTTGNUMBER;
         };
      };
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > 0))
      {
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE > 1))
         {
            if (((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.TRANSMISSIONNORET == LASTTGNUMBER) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.TRANSMISSIONNORET == TRANSMISSIONNO1_VAL)))
            {
               LASTTGNUMBER = (LASTTGNUMBER + 1);
               if (((LASTTGNUMBER <= 0) || (LASTTGNUMBER >= 255)))
               {
                  LASTTGNUMBER = 1;
               };
               TRANSMISSIONNO1_VAL = LASTTGNUMBER;
               switch (LASTTGTYPE)
               {
               case 2:
                  LASTTGTYPE = 3;
                  break;
               case 4:
                  LASTTGTYPE = 5;
                  break;
               case 5:
                  LASTTGTYPE = 6;
                  break;
               };
               TRANSMISSIONTYPE_VAL = LASTTGTYPE;
               if (((LASTTGTYPE == 3) || (LASTTGTYPE == 5)))
               {
                  ORDERID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
                  CMDID_VAL = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
                  BUFFERMODE_VAL = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE);
                  ChBit(BOOLVALUES1, 0, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[16]);
                  ChBit(BOOLVALUES1, 1, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[17]);
                  ChBit(BOOLVALUES1, 2, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[18]);
                  ChBit(BOOLVALUES1, 3, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[19]);
                  ChBit(BOOLVALUES1, 4, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[20]);
                  ChBit(BOOLVALUES1, 5, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[21]);
                  ChBit(BOOLVALUES1, 6, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[22]);
                  ChBit(BOOLVALUES1, 7, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[23]);
                  ChBit(BOOLVALUES1, 8, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[24]);
                  ChBit(BOOLVALUES1, 9, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[25]);
                  ChBit(BOOLVALUES1, 10, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[26]);
                  ChBit(BOOLVALUES1, 11, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[27]);
                  ChBit(BOOLVALUES1, 12, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[28]);
                  ChBit(BOOLVALUES1, 13, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[29]);
                  ChBit(BOOLVALUES1, 14, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[30]);
                  CMDPAR_INT1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[16];
                  CMDPAR_INT2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[17];
                  CMDPAR_INT3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[18];
                  CMDPAR_INT4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[19];
                  CMDPAR_INT5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[20];
                  CMDPAR_INT6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[21];
                  CMDPAR_INT7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[22];
                  CMDPAR_INT8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[23];
                  CMDPAR_INT9_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[24];
                  CMDPAR_INT10_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[25];
                  CMDPAR_INT11_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[26];
                  CMDPAR_INT12_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[27];
                  CMDPAR_INT13_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[28];
                  CMDPAR_INT14_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[29];
                  CMDPAR_INT15_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[30];
                  CMDPAR_REAL1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16];
                  CMDPAR_REAL2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17];
                  CMDPAR_REAL3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18];
                  CMDPAR_REAL4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19];
                  CMDPAR_REAL5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20];
                  CMDPAR_REAL6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21];
                  CMDPAR_REAL7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22];
                  CMDPAR_REAL8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23];
                  CMDPAR_REAL9_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24];
                  CMDPAR_REAL10_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[25];
                  CMDPAR_REAL11_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[26];
                  CMDPAR_REAL12_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[27];
                  CMDPAR_REAL13_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[28];
                  CMDPAR_REAL14_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[29];
                  CMDPAR_REAL15_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[30];
               }
               else if ((LASTTGTYPE == 6))
               {
                  ORDERID_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
                  CMDID_VAL = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
                  BUFFERMODE_VAL = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE);
                  ChBit(BOOLVALUES1, 0, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[31]);
                  ChBit(BOOLVALUES1, 1, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[32]);
                  ChBit(BOOLVALUES1, 2, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[33]);
                  ChBit(BOOLVALUES1, 3, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[34]);
                  ChBit(BOOLVALUES1, 4, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[35]);
                  ChBit(BOOLVALUES1, 5, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[36]);
                  ChBit(BOOLVALUES1, 6, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[37]);
                  ChBit(BOOLVALUES1, 7, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[38]);
                  ChBit(BOOLVALUES1, 8, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[39]);
                  ChBit(BOOLVALUES1, 9, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[40]);
                  ChBit(BOOLVALUES1, 10, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[41]);
                  ChBit(BOOLVALUES1, 11, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[42]);
                  ChBit(BOOLVALUES1, 12, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[43]);
                  ChBit(BOOLVALUES1, 13, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[44]);
                  ChBit(BOOLVALUES1, 14, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[45]);
                  CMDPAR_INT1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[31];
                  CMDPAR_INT2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[32];
                  CMDPAR_INT3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[33];
                  CMDPAR_INT4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[34];
                  CMDPAR_INT5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[35];
                  CMDPAR_INT6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[36];
                  CMDPAR_INT7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[37];
                  CMDPAR_INT8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[38];
                  CMDPAR_INT9_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[39];
                  CMDPAR_INT10_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[40];
                  CMDPAR_INT11_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[41];
                  CMDPAR_INT12_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[42];
                  CMDPAR_INT13_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[43];
                  CMDPAR_INT14_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[44];
                  CMDPAR_INT15_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[45];
                  CMDPAR_REAL1_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[31];
                  CMDPAR_REAL2_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[32];
                  CMDPAR_REAL3_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[33];
                  CMDPAR_REAL4_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[34];
                  CMDPAR_REAL5_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[35];
                  CMDPAR_REAL6_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[36];
                  CMDPAR_REAL7_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[37];
                  CMDPAR_REAL8_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[38];
                  CMDPAR_REAL9_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[39];
                  CMDPAR_REAL10_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[40];
                  CMDPAR_REAL11_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[41];
                  CMDPAR_REAL12_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[42];
                  CMDPAR_REAL13_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[43];
                  CMDPAR_REAL14_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[44];
                  CMDPAR_REAL15_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[45];
               };
               TRANSMISSIONNO2_VAL = LASTTGNUMBER;
            };
         };
      }
      else
      {
         TRANSMISSIONNO1_VAL = 0;
         TRANSMISSIONTYPE_VAL = 0;
         ORDERID_VAL = 0;
         CMDID_VAL = 0;
         BUFFERMODE_VAL = 0;
         CHECKSUM_VAL = 0;
         BOOLVALUES1 = 0;
         CMDPAR_INT1_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT2_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT3_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT4_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT5_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT6_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT7_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT8_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT9_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT10_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT11_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT12_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT13_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT14_VAL = (PLCIEC::DINT)0;
         CMDPAR_INT15_VAL = (PLCIEC::DINT)0;
         CMDPAR_REAL1_VAL = 0.0;
         CMDPAR_REAL2_VAL = 0.0;
         CMDPAR_REAL3_VAL = 0.0;
         CMDPAR_REAL4_VAL = 0.0;
         CMDPAR_REAL5_VAL = 0.0;
         CMDPAR_REAL6_VAL = 0.0;
         CMDPAR_REAL7_VAL = 0.0;
         CMDPAR_REAL8_VAL = 0.0;
         CMDPAR_REAL9_VAL = 0.0;
         CMDPAR_REAL10_VAL = 0.0;
         CMDPAR_REAL11_VAL = 0.0;
         CMDPAR_REAL12_VAL = 0.0;
         CMDPAR_REAL13_VAL = 0.0;
         CMDPAR_REAL14_VAL = 0.0;
         CMDPAR_REAL15_VAL = 0.0;
         TRANSMISSIONNO2_VAL = 0;
      };
      ChBit(KRC4_OUTPUT[0], 0, /* := */ AE_PGNO_FBIT_VAL);
      ChBit(KRC4_OUTPUT[0], 1, /* := */ AE_PGNO_BIT1_VAL);
      ChBit(KRC4_OUTPUT[0], 2, /* := */ AE_PGNO_BIT2_VAL);
      ChBit(KRC4_OUTPUT[0], 3, /* := */ AE_PGNO_BIT3_VAL);
      ChBit(KRC4_OUTPUT[0], 4, /* := */ AE_PGNO_BIT4_VAL);
      ChBit(KRC4_OUTPUT[0], 5, /* := */ AE_PGNO_BIT5_VAL);
      ChBit(KRC4_OUTPUT[0], 6, /* := */ AE_PGNO_BIT6_VAL);
      ChBit(KRC4_OUTPUT[0], 7, /* := */ AE_PGNO_BIT7_VAL);
      ChBit(KRC4_OUTPUT[1], 0, /* := */ AE_PGNO_PARITY_VAL);
      ChBit(KRC4_OUTPUT[1], 1, /* := */ AE_PGNO_VALID_VAL);
      ChBit(KRC4_OUTPUT[1], 2, /* := */ AE_EXT_START_VAL);
      ChBit(KRC4_OUTPUT[1], 3, /* := */ AE_MOVE_ENABLE_VAL);
      ChBit(KRC4_OUTPUT[1], 4, /* := */ AE_CONF_MESS_VAL);
      ChBit(KRC4_OUTPUT[1], 5, /* := */ AE_DRIVES_OFF_VAL);
      ChBit(KRC4_OUTPUT[1], 6, /* := */ AE_DRIVES_ON_VAL);
      ChBit(KRC4_OUTPUT[1], 7, /* := */ MASTEST_REQ_EXT_VAL);
      ChBit(KRC4_OUTPUT[2], 0, /* := */ BRAKETEST_REQ_EXT_VAL);
      ChBit(KRC4_OUTPUT[4], 0, /* := */ AE_RESET_VAL);
      ChBit(KRC4_OUTPUT[4], 1, /* := */ BRAKE_VAL);
      ChBit(KRC4_OUTPUT[4], 2, /* := */ BRAKE_F_VAL);
      ChBit(KRC4_OUTPUT[4], 3, /* := */ RELEASE_BRAKE_VAL);
      ChBit(KRC4_OUTPUT[4], 4, /* := */ SHOW_TRACE_VAL);
      ChBit(KRC4_OUTPUT[4], 5, /* := */ MESSAGE_RESET_VAL);
      ChBit(KRC4_OUTPUT[4], 7, /* := */ WRITE_OUT_1TO8_VAL);
      ChBit(KRC4_OUTPUT[5], 0, /* := */ OUT_VAL_1_VAL);
      ChBit(KRC4_OUTPUT[5], 1, /* := */ OUT_VAL_2_VAL);
      ChBit(KRC4_OUTPUT[5], 2, /* := */ OUT_VAL_3_VAL);
      ChBit(KRC4_OUTPUT[5], 3, /* := */ OUT_VAL_4_VAL);
      ChBit(KRC4_OUTPUT[5], 4, /* := */ OUT_VAL_5_VAL);
      ChBit(KRC4_OUTPUT[5], 5, /* := */ OUT_VAL_6_VAL);
      ChBit(KRC4_OUTPUT[5], 6, /* := */ OUT_VAL_7_VAL);
      ChBit(KRC4_OUTPUT[5], 7, /* := */ OUT_VAL_8_VAL);
      ChBit(KRC4_OUTPUT[2], 7, /* := */ JOG_ADVANCED_VAL);
      DUMMY = MXA_WRITEIO_BYTE(8, KRC4_OUTPUT, HEARTBEAT_VAL);
      DUMMY = MXA_WRITEIO_BYTE(9, KRC4_OUTPUT, OVERRIDE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(10, KRC4_OUTPUT, PLCIEC::DINT_TO_INT(PLC_MAJOR_VAL));
      DUMMY = MXA_WRITEIO_BYTE(11, KRC4_OUTPUT, PLCIEC::DINT_TO_INT(PLC_MINOR_VAL));
      DUMMY = MXA_WRITEIO_DINT(12, KRC4_OUTPUT, SR_ORDER1_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(16, KRC4_OUTPUT, SR_ORDER2_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(20, KRC4_OUTPUT, SR_ORDER3_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(24, KRC4_OUTPUT, SR_ORDER4_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(28, KRC4_OUTPUT, SR_ORDER5_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(32, KRC4_OUTPUT, SR_ORDER6_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(36, KRC4_OUTPUT, SR_ORDER7_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(40, KRC4_OUTPUT, SR_ORDER8_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(44, KRC4_OUTPUT, SR_ORDER9_ID_VAL);
      DUMMY = MXA_WRITEIO_DINT(48, KRC4_OUTPUT, SR_ORDER10_ID_VAL);
      DUMMY = MXA_WRITEIO_BYTE(52, KRC4_OUTPUT, SR_ORDER1_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(53, KRC4_OUTPUT, SR_ORDER2_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(54, KRC4_OUTPUT, SR_ORDER3_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(55, KRC4_OUTPUT, SR_ORDER4_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(56, KRC4_OUTPUT, SR_ORDER5_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(57, KRC4_OUTPUT, SR_ORDER6_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(58, KRC4_OUTPUT, SR_ORDER7_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(59, KRC4_OUTPUT, SR_ORDER8_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(60, KRC4_OUTPUT, SR_ORDER9_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(61, KRC4_OUTPUT, SR_ORDER10_STATE_VAL);
      DUMMY = MXA_WRITEIO_BYTE(62, KRC4_OUTPUT, TRANSMISSIONNO1_VAL);
      DUMMY = MXA_WRITEIO_BYTE(63, KRC4_OUTPUT, TRANSMISSIONTYPE_VAL);
      DUMMY = MXA_WRITEIO_DINT(64, KRC4_OUTPUT, ORDERID_VAL);
      DUMMY = MXA_WRITEIO_BYTE(68, KRC4_OUTPUT, CMDID_VAL);
      DUMMY = MXA_WRITEIO_BYTE(69, KRC4_OUTPUT, BUFFERMODE_VAL);
      DUMMY = MXA_WRITEIO_DWORD(70, KRC4_OUTPUT, CHECKSUM_VAL);
      DUMMY = MXA_WRITEIO_WORD(74, KRC4_OUTPUT, BOOLVALUES1);
      DUMMY = MXA_WRITEIO_DINT(76, KRC4_OUTPUT, CMDPAR_INT1_VAL);
      DUMMY = MXA_WRITEIO_DINT(80, KRC4_OUTPUT, CMDPAR_INT2_VAL);
      DUMMY = MXA_WRITEIO_DINT(84, KRC4_OUTPUT, CMDPAR_INT3_VAL);
      DUMMY = MXA_WRITEIO_DINT(88, KRC4_OUTPUT, CMDPAR_INT4_VAL);
      DUMMY = MXA_WRITEIO_DINT(92, KRC4_OUTPUT, CMDPAR_INT5_VAL);
      DUMMY = MXA_WRITEIO_DINT(96, KRC4_OUTPUT, CMDPAR_INT6_VAL);
      DUMMY = MXA_WRITEIO_DINT(100, KRC4_OUTPUT, CMDPAR_INT7_VAL);
      DUMMY = MXA_WRITEIO_DINT(104, KRC4_OUTPUT, CMDPAR_INT8_VAL);
      DUMMY = MXA_WRITEIO_DINT(108, KRC4_OUTPUT, CMDPAR_INT9_VAL);
      DUMMY = MXA_WRITEIO_DINT(112, KRC4_OUTPUT, CMDPAR_INT10_VAL);
      DUMMY = MXA_WRITEIO_DINT(116, KRC4_OUTPUT, CMDPAR_INT11_VAL);
      DUMMY = MXA_WRITEIO_DINT(120, KRC4_OUTPUT, CMDPAR_INT12_VAL);
      DUMMY = MXA_WRITEIO_DINT(124, KRC4_OUTPUT, CMDPAR_INT13_VAL);
      DUMMY = MXA_WRITEIO_DINT(128, KRC4_OUTPUT, CMDPAR_INT14_VAL);
      DUMMY = MXA_WRITEIO_DINT(132, KRC4_OUTPUT, CMDPAR_INT15_VAL);
      DUMMY = MXA_WRITEIO_REAL(136, KRC4_OUTPUT, CMDPAR_REAL1_VAL);
      DUMMY = MXA_WRITEIO_REAL(140, KRC4_OUTPUT, CMDPAR_REAL2_VAL);
      DUMMY = MXA_WRITEIO_REAL(144, KRC4_OUTPUT, CMDPAR_REAL3_VAL);
      DUMMY = MXA_WRITEIO_REAL(148, KRC4_OUTPUT, CMDPAR_REAL4_VAL);
      DUMMY = MXA_WRITEIO_REAL(152, KRC4_OUTPUT, CMDPAR_REAL5_VAL);
      DUMMY = MXA_WRITEIO_REAL(156, KRC4_OUTPUT, CMDPAR_REAL6_VAL);
      DUMMY = MXA_WRITEIO_REAL(160, KRC4_OUTPUT, CMDPAR_REAL7_VAL);
      DUMMY = MXA_WRITEIO_REAL(164, KRC4_OUTPUT, CMDPAR_REAL8_VAL);
      DUMMY = MXA_WRITEIO_REAL(168, KRC4_OUTPUT, CMDPAR_REAL9_VAL);
      DUMMY = MXA_WRITEIO_REAL(172, KRC4_OUTPUT, CMDPAR_REAL10_VAL);
      DUMMY = MXA_WRITEIO_REAL(176, KRC4_OUTPUT, CMDPAR_REAL11_VAL);
      DUMMY = MXA_WRITEIO_REAL(180, KRC4_OUTPUT, CMDPAR_REAL12_VAL);
      DUMMY = MXA_WRITEIO_REAL(184, KRC4_OUTPUT, CMDPAR_REAL13_VAL);
      DUMMY = MXA_WRITEIO_REAL(188, KRC4_OUTPUT, CMDPAR_REAL14_VAL);
      DUMMY = MXA_WRITEIO_REAL(192, KRC4_OUTPUT, CMDPAR_REAL15_VAL);
      DUMMY = MXA_WRITEIO_BYTE(196, KRC4_OUTPUT, TRANSMISSIONNO2_VAL);
      DUMMY = MXA_WRITEIO_BYTE(3, KRC4_OUTPUT, JOG_AD_STATE);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_VALUESTOAPO
 ******************************************************************************/
class MXA_VALUESTOAPO
{

   /* VAR_INPUT */

public:
   PLCIEC::INT PTP_MODE;
   PLCIEC::INT CP_MODE;
   PLCIEC::INT CPTP;
   PLCIEC::REAL CDIS;
   PLCIEC::REAL CORI;
   PLCIEC::INT CVEL;

   /* VAR_OUTPUT */

public:
   const APO &APO_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   APO _APO_1;

public:
   MXA_VALUESTOAPO()
       : PTP_MODE(0), CP_MODE(0), CPTP(0), CDIS(0), CORI(0), CVEL(0), APO_1(_APO_1), _APO_1()
   {
   }

public:
   void OnCycle()
   {

      _APO_1.PTP_MODE = PTP_MODE;
      _APO_1.CP_MODE = CP_MODE;
      _APO_1.CPTP = CPTP;
      _APO_1.CDIS = CDIS;
      _APO_1.CORI = CORI;
      _APO_1.CVEL = CVEL;
   }
};
