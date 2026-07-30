//*****************************************************************************
// This material is the exclusive property of KUKA Roboter GmbH.
// Except as expressly permitted by separate agreement, this material may only
// be used by members of the development department of KUKA Roboter GmbH for
// internal development purposes of KUKA Roboter GmbH.
//
// Copyright (C) 2025
// KUKA Roboter GmbH, Germany. All Rights Reserved.
//
//*****************************************************************************
// Date        Programmer        Reviewer
//             Description
//-----------------------------------------------------------------------------
// 01.09.2015  AFr
//             mxAutomation.1
// 22.01.2016  AFr
//             mxAutomation.1 multiple improvements and fixes
// 15.02.2016  AFr
//             mxAutomation.1 multiple fixes
// 11.11.2016  RRolke
//             Windows support
// 09.05.2018  Jump Wu
//             Update to V3.0.2
// 09.15.2019  Jump Wu
//             Update to V3.1.0
// 20.07.2020  Jump Wu
//             Update to V3.2.0
// 10.03.2022  TBreitenauer
//             Update to V3.3.1
// 14.03.2022  SJ
//             add active signal for KRC_Abort
//             add Function block KRC_AbortAdvanced, KRC_ForwardAdvanced, KRC_InverseAdvanced, KRC_JogAdvanced, KRC_TechFunctionAdvanced
//             add capability to read the positionally accurate robot model in KRC_Initialize
// 02.06.2022  CCW
//             added KRC_LDDCONFIG, KRC_LDDSTART, KRC_LDDTEST & KRC_LDDWRITELOAD
// 22.06.2022  CCW
//             added KRC_ACTIVATEPOSCONVERSION & KRC_CONVDELWPS
// 07.07.2022  CCW
//             improvements and fixes
// 11.04.2023  SJ
//             Bugfixing 977033， 987045
// 28.06.2023  SJ
//             Bugfixing 1007278
// 18.03.2025  Svastits
//             mxAutomation 4.0
// 11.06.2025  Akos B.
//             mxAutomation 4.0 LDD and ConveyorTech API changes
// 01.08.2025  Daniel P.
//             Add OrderID to blocks
// 28.08.2025  Akos Gy., Gergely K.
//             Add collision detection blocks
// 2025-10-31  Aron S
//             Update to 6.0, remove JOG_SLIN
//             Bugfix: coordinate system reset for KRC_JOG
// 2025-11-12  Daniel P.
//             Add KRMsgNet blocks (KRC_GETALLMESSAGES, KRC_SETLANGUAGE, KRC_SETDATETIME)
// 2026-02-24  Kristof P
//             Fix incorrect serial number
// 2026-03-20  Kristof P
//             Switch KRC_GETALLMESSAGES and KRC_SETLANGUAGE BufferMode to DIRECT
//             Enable all buffer modes for KRC_SETDATETIME
// 2026-05-06  Kristof P
//             Make casts explicit
// 2026-06-10  Svastits
//             Update to 6.1
//*****************************************************************************
//

#ifndef MXA_V6_0_1_H
#define MXA_V6_0_1_H

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
   PLCIEC::BOOL MXA_GETIO_BYTE = static_cast<PLCIEC::BOOL>(FALSE);

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
   PLCIEC::BOOL MXA_GETIO_DINT = static_cast<PLCIEC::BOOL>(FALSE);

   PLCIEC::ChBit(DW, 0, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 0));
   PLCIEC::ChBit(DW, 1, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 1));
   PLCIEC::ChBit(DW, 2, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 2));
   PLCIEC::ChBit(DW, 3, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 3));
   PLCIEC::ChBit(DW, 4, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 4));
   PLCIEC::ChBit(DW, 5, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 5));
   PLCIEC::ChBit(DW, 6, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 6));
   PLCIEC::ChBit(DW, 7, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 0)], 7));
   PLCIEC::ChBit(DW, 8, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 0));
   PLCIEC::ChBit(DW, 9, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 1));
   PLCIEC::ChBit(DW, 10, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 2));
   PLCIEC::ChBit(DW, 11, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 3));
   PLCIEC::ChBit(DW, 12, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 4));
   PLCIEC::ChBit(DW, 13, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 5));
   PLCIEC::ChBit(DW, 14, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 6));
   PLCIEC::ChBit(DW, 15, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 7));
   PLCIEC::ChBit(DW, 16, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 0));
   PLCIEC::ChBit(DW, 17, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 1));
   PLCIEC::ChBit(DW, 18, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 2));
   PLCIEC::ChBit(DW, 19, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 3));
   PLCIEC::ChBit(DW, 20, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 4));
   PLCIEC::ChBit(DW, 21, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 5));
   PLCIEC::ChBit(DW, 22, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 6));
   PLCIEC::ChBit(DW, 23, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 2)], 7));
   PLCIEC::ChBit(DW, 24, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 0));
   PLCIEC::ChBit(DW, 25, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 1));
   PLCIEC::ChBit(DW, 26, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 2));
   PLCIEC::ChBit(DW, 27, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 3));
   PLCIEC::ChBit(DW, 28, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 4));
   PLCIEC::ChBit(DW, 29, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 5));
   PLCIEC::ChBit(DW, 30, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 6));
   PLCIEC::ChBit(DW, 31, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 3)], 7));
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
   PLCIEC::BOOL MXA_GETIO_INT = static_cast<PLCIEC::BOOL>(FALSE);

   PLCIEC::ChBit(W, 0, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 0));
   PLCIEC::ChBit(W, 1, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 1));
   PLCIEC::ChBit(W, 2, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 2));
   PLCIEC::ChBit(W, 3, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 3));
   PLCIEC::ChBit(W, 4, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 4));
   PLCIEC::ChBit(W, 5, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 5));
   PLCIEC::ChBit(W, 6, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 6));
   PLCIEC::ChBit(W, 7, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[BYTEPOS], 7));
   PLCIEC::ChBit(W, 8, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 0));
   PLCIEC::ChBit(W, 9, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 1));
   PLCIEC::ChBit(W, 10, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 2));
   PLCIEC::ChBit(W, 11, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 3));
   PLCIEC::ChBit(W, 12, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 4));
   PLCIEC::ChBit(W, 13, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 5));
   PLCIEC::ChBit(W, 14, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 6));
   PLCIEC::ChBit(W, 15, /* := */ PLCIEC::IsBitSet(KRC4_INPUT[(BYTEPOS + 1)], 7));
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
   PLCIEC::BOOL MXA_GETIO_NIBBLE = static_cast<PLCIEC::BOOL>(FALSE);

   B = KRC4_INPUT[BYTEPOS];
   PLCIEC::ChBit(B1, 0, /* := */ PLCIEC::IsBitSet(B, 0));
   PLCIEC::ChBit(B1, 1, /* := */ PLCIEC::IsBitSet(B, 1));
   PLCIEC::ChBit(B1, 2, /* := */ PLCIEC::IsBitSet(B, 2));
   PLCIEC::ChBit(B1, 3, /* := */ PLCIEC::IsBitSet(B, 3));
   PLCIEC::ChBit(B2, 0, /* := */ PLCIEC::IsBitSet(B, 4));
   PLCIEC::ChBit(B2, 1, /* := */ PLCIEC::IsBitSet(B, 5));
   PLCIEC::ChBit(B2, 2, /* := */ PLCIEC::IsBitSet(B, 6));
   PLCIEC::ChBit(B2, 3, /* := */ PLCIEC::IsBitSet(B, 7));
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
   PLCIEC::BOOL MXA_GETIO_REAL = static_cast<PLCIEC::BOOL>(FALSE);

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
   PLCIEC::BOOL MXA_GETIO_SINT = static_cast<PLCIEC::BOOL>(FALSE);

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
   PLCIEC::BOOL MXA_WRITEIO_BYTE = static_cast<PLCIEC::BOOL>(FALSE);

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
   PLCIEC::BOOL MXA_WRITEIO_DINT = static_cast<PLCIEC::BOOL>(FALSE);

   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 0, /* := */ PLCIEC::IsBitSet(VAL, 0));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 1, /* := */ PLCIEC::IsBitSet(VAL, 1));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 2, /* := */ PLCIEC::IsBitSet(VAL, 2));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 3, /* := */ PLCIEC::IsBitSet(VAL, 3));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 4, /* := */ PLCIEC::IsBitSet(VAL, 4));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 5, /* := */ PLCIEC::IsBitSet(VAL, 5));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 6, /* := */ PLCIEC::IsBitSet(VAL, 6));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 7, /* := */ PLCIEC::IsBitSet(VAL, 7));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 0, /* := */ PLCIEC::IsBitSet(VAL, 8));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 1, /* := */ PLCIEC::IsBitSet(VAL, 9));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 2, /* := */ PLCIEC::IsBitSet(VAL, 10));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 3, /* := */ PLCIEC::IsBitSet(VAL, 11));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 4, /* := */ PLCIEC::IsBitSet(VAL, 12));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 5, /* := */ PLCIEC::IsBitSet(VAL, 13));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 6, /* := */ PLCIEC::IsBitSet(VAL, 14));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 7, /* := */ PLCIEC::IsBitSet(VAL, 15));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 0, /* := */ PLCIEC::IsBitSet(VAL, 16));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 1, /* := */ PLCIEC::IsBitSet(VAL, 17));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 2, /* := */ PLCIEC::IsBitSet(VAL, 18));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 3, /* := */ PLCIEC::IsBitSet(VAL, 19));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 4, /* := */ PLCIEC::IsBitSet(VAL, 20));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 5, /* := */ PLCIEC::IsBitSet(VAL, 21));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 6, /* := */ PLCIEC::IsBitSet(VAL, 22));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 7, /* := */ PLCIEC::IsBitSet(VAL, 23));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 0, /* := */ PLCIEC::IsBitSet(VAL, 24));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 1, /* := */ PLCIEC::IsBitSet(VAL, 25));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 2, /* := */ PLCIEC::IsBitSet(VAL, 26));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 3, /* := */ PLCIEC::IsBitSet(VAL, 27));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 4, /* := */ PLCIEC::IsBitSet(VAL, 28));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 5, /* := */ PLCIEC::IsBitSet(VAL, 29));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 6, /* := */ PLCIEC::IsBitSet(VAL, 30));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 7, /* := */ PLCIEC::IsBitSet(VAL, 31));
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
   PLCIEC::BOOL MXA_WRITEIO_DWORD = static_cast<PLCIEC::BOOL>(FALSE);

   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 0, /* := */ PLCIEC::IsBitSet(VAL, 0));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 1, /* := */ PLCIEC::IsBitSet(VAL, 1));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 2, /* := */ PLCIEC::IsBitSet(VAL, 2));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 3, /* := */ PLCIEC::IsBitSet(VAL, 3));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 4, /* := */ PLCIEC::IsBitSet(VAL, 4));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 5, /* := */ PLCIEC::IsBitSet(VAL, 5));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 6, /* := */ PLCIEC::IsBitSet(VAL, 6));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 7, /* := */ PLCIEC::IsBitSet(VAL, 7));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 0, /* := */ PLCIEC::IsBitSet(VAL, 8));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 1, /* := */ PLCIEC::IsBitSet(VAL, 9));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 2, /* := */ PLCIEC::IsBitSet(VAL, 10));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 3, /* := */ PLCIEC::IsBitSet(VAL, 11));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 4, /* := */ PLCIEC::IsBitSet(VAL, 12));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 5, /* := */ PLCIEC::IsBitSet(VAL, 13));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 6, /* := */ PLCIEC::IsBitSet(VAL, 14));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 7, /* := */ PLCIEC::IsBitSet(VAL, 15));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 0, /* := */ PLCIEC::IsBitSet(VAL, 16));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 1, /* := */ PLCIEC::IsBitSet(VAL, 17));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 2, /* := */ PLCIEC::IsBitSet(VAL, 18));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 3, /* := */ PLCIEC::IsBitSet(VAL, 19));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 4, /* := */ PLCIEC::IsBitSet(VAL, 20));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 5, /* := */ PLCIEC::IsBitSet(VAL, 21));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 6, /* := */ PLCIEC::IsBitSet(VAL, 22));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 2)], 7, /* := */ PLCIEC::IsBitSet(VAL, 23));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 0, /* := */ PLCIEC::IsBitSet(VAL, 24));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 1, /* := */ PLCIEC::IsBitSet(VAL, 25));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 2, /* := */ PLCIEC::IsBitSet(VAL, 26));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 3, /* := */ PLCIEC::IsBitSet(VAL, 27));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 4, /* := */ PLCIEC::IsBitSet(VAL, 28));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 5, /* := */ PLCIEC::IsBitSet(VAL, 29));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 6, /* := */ PLCIEC::IsBitSet(VAL, 30));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 3)], 7, /* := */ PLCIEC::IsBitSet(VAL, 31));
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
   PLCIEC::BOOL MXA_WRITEIO_REAL = static_cast<PLCIEC::BOOL>(FALSE);

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
   PLCIEC::BOOL MXA_WRITEIO_WORD = static_cast<PLCIEC::BOOL>(FALSE);

   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 0, /* := */ PLCIEC::IsBitSet(VAL, 0));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 1, /* := */ PLCIEC::IsBitSet(VAL, 1));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 2, /* := */ PLCIEC::IsBitSet(VAL, 2));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 3, /* := */ PLCIEC::IsBitSet(VAL, 3));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 4, /* := */ PLCIEC::IsBitSet(VAL, 4));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 5, /* := */ PLCIEC::IsBitSet(VAL, 5));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 6, /* := */ PLCIEC::IsBitSet(VAL, 6));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 0)], 7, /* := */ PLCIEC::IsBitSet(VAL, 7));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 0, /* := */ PLCIEC::IsBitSet(VAL, 8));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 1, /* := */ PLCIEC::IsBitSet(VAL, 9));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 2, /* := */ PLCIEC::IsBitSet(VAL, 10));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 3, /* := */ PLCIEC::IsBitSet(VAL, 11));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 4, /* := */ PLCIEC::IsBitSet(VAL, 12));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 5, /* := */ PLCIEC::IsBitSet(VAL, 13));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 6, /* := */ PLCIEC::IsBitSet(VAL, 14));
   PLCIEC::ChBit(KRC4_OUTPUT[(BYTEPOS + 1)], 7, /* := */ PLCIEC::IsBitSet(VAL, 15));
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] = static_cast<PLCIEC::BOOL>(FALSE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I] = static_cast<PLCIEC::DINT>(0);
      };
      for (I = 1; I <= 100; I += 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = 0.0f;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = static_cast<PLCIEC::DINT>(0);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = static_cast<PLCIEC::DINT>(0);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = static_cast<PLCIEC::DINT>(0);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = static_cast<PLCIEC::INT>(0);
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
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), CMDID(0), BUFFERMODE(0), COMMANDSIZE(0), ENABLEDIRECTEXE(static_cast<PLCIEC::BOOL>(FALSE)), ENABLEQUEUEEXE(static_cast<PLCIEC::BOOL>(FALSE)), IGNOREINIT(static_cast<PLCIEC::BOOL>(FALSE)), WRITECMDPAR(_WRITECMDPAR), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), CMDSPECIFIC1(_CMDSPECIFIC1), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), READCMDDATARET(_READCMDDATARET), ORDERID(_ORDERID), _WRITECMDPAR(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _CMDSPECIFIC1(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _READCMDDATARET(static_cast<PLCIEC::BOOL>(FALSE)), _ORDERID(0), RESETCOMMAND_1(), GETORDERSTATE_1(), M_STATE(0), M_ORDERID(0), M_EXECUTELAST(static_cast<PLCIEC::BOOL>(FALSE)), M_RE_EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), M_COMMANDSIZE(0)
   {
   }

public:
   void OnCycle()
   {

      M_RE_EXECUTE = ((EXECUTE == static_cast<PLCIEC::BOOL>(TRUE)) && (M_EXECUTELAST == static_cast<PLCIEC::BOOL>(FALSE)));
      M_EXECUTELAST = EXECUTE;
      _WRITECMDPAR = static_cast<PLCIEC::BOOL>(FALSE);
      _READCMDDATARET = static_cast<PLCIEC::BOOL>(FALSE);
      if (!(EXECUTE))
      {
         M_STATE = 0;
         M_ORDERID = static_cast<PLCIEC::DINT>(0);
         _ERRORID = static_cast<PLCIEC::DINT>(0);
      };
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
      }
      else
      {
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(507);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(508);
         };
      };
      if ((M_RE_EXECUTE && (_ERRORID == static_cast<PLCIEC::DINT>(0))))
      {
         M_STATE = 1;
         if ((((BUFFERMODE == 0) && (ENABLEDIRECTEXE == static_cast<PLCIEC::BOOL>(FALSE))) || ((BUFFERMODE > 0) && (ENABLEQUEUEEXE == static_cast<PLCIEC::BOOL>(FALSE)))))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(502);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            if (!(IGNOREINIT))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(508);
            };
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(509);
         };
      };
      if (((M_STATE == 1) && (_ERRORID == static_cast<PLCIEC::DINT>(0))))
      {
         if (M_RE_EXECUTE)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID + static_cast<PLCIEC::DINT>(1));
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID >= static_cast<PLCIEC::DINT>(2147483647)))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = static_cast<PLCIEC::DINT>(1);
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
                     _READCMDDATARET = static_cast<PLCIEC::BOOL>(TRUE);
                  }
                  else
                  {
                     M_STATE = 5;
                  };
               }
               else
               {
                  _ERRORID = static_cast<PLCIEC::DINT>(512);
               };
            }
            else
            {
               _ERRORID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET * static_cast<PLCIEC::DINT>(-1));
            };
            // Call FB ResetCommand_1
            RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
            RESETCOMMAND_1.OnCycle();
         }
         else
         {
            if (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == static_cast<PLCIEC::DINT>(0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID == static_cast<PLCIEC::DINT>(0))) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED || IGNOREINIT)))
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
                     _ERRORID = static_cast<PLCIEC::DINT>(517);
                     M_COMMANDSIZE = 3;
                  };
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = M_COMMANDSIZE;
                  _WRITECMDPAR = static_cast<PLCIEC::BOOL>(TRUE);
               };
            };
         };
      };
      if ((((M_STATE > 1) && (M_STATE < 15)) && (_ERRORID == static_cast<PLCIEC::DINT>(0))))
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
      if ((_ERRORID != static_cast<PLCIEC::DINT>(0)))
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
 * FUNCTION_BLOCK KRC_ABORT
 ******************************************************************************/
class KRC_ABORT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_ABORT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(2);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ABORTACTIVE;
      _DONE = (MXA_EXECUTECOMMAND_1.DONE || MXA_EXECUTECOMMAND_1.ABORTED);
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ABORTADVANCED
 ******************************************************************************/
class KRC_ABORTADVANCED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BRAKEREACTION;
   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   PLCIEC::INT NSTATE;

public:
   KRC_ABORTADVANCED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BRAKEREACTION(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), NSTATE(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(58);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = BRAKEREACTION;
         NSTATE = 1;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ABORTACTIVE;
      _DONE = (MXA_EXECUTECOMMAND_1.DONE || MXA_EXECUTECOMMAND_1.ABORTED);
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ACTIVATEINTERRUPT
 ******************************************************************************/
class KRC_ACTIVATEINTERRUPT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT INTERRUPT;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_ACTIVATEINTERRUPT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), INTERRUPT(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(6);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(INTERRUPT);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
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
       : AXISGROUPIDX(0), MOVE_ENABLE(static_cast<PLCIEC::BOOL>(FALSE)), CONF_MESS(static_cast<PLCIEC::BOOL>(FALSE)), DRIVES_ON(static_cast<PLCIEC::BOOL>(FALSE)), DRIVES_OFF(static_cast<PLCIEC::BOOL>(FALSE)), EXT_START(static_cast<PLCIEC::BOOL>(FALSE)), RESET(static_cast<PLCIEC::BOOL>(FALSE)), ENABLE_T1(static_cast<PLCIEC::BOOL>(FALSE)), ENABLE_T2(static_cast<PLCIEC::BOOL>(FALSE)), ENABLE_AUT(static_cast<PLCIEC::BOOL>(FALSE)), ENABLE_EXT(static_cast<PLCIEC::BOOL>(FALSE)), VALID(_VALID), RC_RDY1(_RC_RDY1), ALARM_STOP(_ALARM_STOP), USER_SAFE(_USER_SAFE), PERI_RDY(_PERI_RDY), ROB_CAL(_ROB_CAL), IO_ACTCONF(_IO_ACTCONF), STOPMESS(_STOPMESS), INT_E_STOP(_INT_E_STOP), PRO_ACT(_PRO_ACT), APPL_RUN(_APPL_RUN), PRO_MOVE(_PRO_MOVE), ON_PATH(_ON_PATH), NEAR_POSRET(_NEAR_POSRET), ROB_STOPPED(_ROB_STOPPED), T1(_T1), T2(_T2), AUT(_AUT), EXT(_EXT), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _RC_RDY1(static_cast<PLCIEC::BOOL>(FALSE)), _ALARM_STOP(static_cast<PLCIEC::BOOL>(FALSE)), _USER_SAFE(static_cast<PLCIEC::BOOL>(FALSE)), _PERI_RDY(static_cast<PLCIEC::BOOL>(FALSE)), _ROB_CAL(static_cast<PLCIEC::BOOL>(FALSE)), _IO_ACTCONF(static_cast<PLCIEC::BOOL>(FALSE)), _STOPMESS(static_cast<PLCIEC::BOOL>(FALSE)), _INT_E_STOP(static_cast<PLCIEC::BOOL>(FALSE)), _PRO_ACT(static_cast<PLCIEC::BOOL>(FALSE)), _APPL_RUN(static_cast<PLCIEC::BOOL>(FALSE)), _PRO_MOVE(static_cast<PLCIEC::BOOL>(FALSE)), _ON_PATH(static_cast<PLCIEC::BOOL>(FALSE)), _NEAR_POSRET(static_cast<PLCIEC::BOOL>(FALSE)), _ROB_STOPPED(static_cast<PLCIEC::BOOL>(FALSE)), _T1(static_cast<PLCIEC::BOOL>(FALSE)), _T2(static_cast<PLCIEC::BOOL>(FALSE)), _AUT(static_cast<PLCIEC::BOOL>(FALSE)), _EXT(static_cast<PLCIEC::BOOL>(FALSE))
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = static_cast<PLCIEC::BOOL>(FALSE);
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = static_cast<PLCIEC::BOOL>(TRUE);
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESOFF = DRIVES_OFF;
      if (DRIVES_ON)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = static_cast<PLCIEC::BOOL>(TRUE);
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.EXT_START = EXT_START;
      if (RESET)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = static_cast<PLCIEC::BOOL>(TRUE);
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
       : AXISGROUPIDX(0), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID;
      if ((_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB;
      };
      if ((_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDPCOS;
      };
      if ((_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID;
      };
      if ((_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID;
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
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
       : AXISGROUPIDX(0), MESSAGERESET(static_cast<PLCIEC::BOOL>(FALSE)), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), I(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      if (MESSAGERESET)
      {
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == static_cast<PLCIEC::DINT>(565)))
         {
            for (I = 1; I <= 100; I += 1)
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = 0.0f;
            };
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET = MESSAGERESET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = static_cast<PLCIEC::DINT>(0);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = static_cast<PLCIEC::DINT>(0);
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
       : AXISGROUPIDX(0), EXECUTERESET(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), DONE(_DONE), DISPACTIVE(_DISPACTIVE), RESETVALID(_RESETVALID), ERROR(_ERROR), ERRORID(_ERRORID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _DISPACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _RESETVALID(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), M_STATE(0), M_CONFMESS(static_cast<PLCIEC::BOOL>(FALSE)), M_RESET(static_cast<PLCIEC::BOOL>(FALSE)), M_RE_EXECUTERESET(static_cast<PLCIEC::BOOL>(FALSE)), M_EXECUTERESETLAST(static_cast<PLCIEC::BOOL>(FALSE)), KRC_READMXAERROR_1(), KRC_MESSAGERESET_1(), TON_ON(), TON_OFF(), TON_1(), TON_2(), TON_3(), TON_4()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      _DISPACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT;
      _RESETVALID = (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && !(_DISPACTIVE)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP) && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE);
      if (!(EXECUTERESET))
      {
         M_STATE = 0;
         _ERRORID = static_cast<PLCIEC::DINT>(0);
      };
      M_RE_EXECUTERESET = ((EXECUTERESET == static_cast<PLCIEC::BOOL>(TRUE)) && (M_EXECUTERESETLAST == static_cast<PLCIEC::BOOL>(FALSE)));
      M_EXECUTERESETLAST = EXECUTERESET;
      // Call FB KRC_ReadMXAError_1
      KRC_READMXAERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_READMXAERROR_1.OnCycle();
      M_CONFMESS = static_cast<PLCIEC::BOOL>(FALSE);
      M_RESET = static_cast<PLCIEC::BOOL>(FALSE);
      _DONE = static_cast<PLCIEC::BOOL>(FALSE);
      switch (M_STATE)
      {
      case 0:
         if (M_RE_EXECUTERESET)
         {
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(508);
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(509);
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(523);
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(524);
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(525);
            };
            if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT)
            {
               _ERRORID = static_cast<PLCIEC::DINT>(526);
            };
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(532);
            };
            if ((_ERRORID == static_cast<PLCIEC::DINT>(0)))
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
         if ((KRC_READMXAERROR_1.ERRORID == static_cast<PLCIEC::DINT>(0)))
         {
            M_STATE = 2;
         };
         // Call FB KRC_MessageReset_1
         KRC_MESSAGERESET_1.AXISGROUPIDX = AXISGROUPIDX;
         KRC_MESSAGERESET_1.MESSAGERESET = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_MESSAGERESET_1.OnCycle();
         break;
      case 2:
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY)
         {
            M_STATE = 3;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = static_cast<PLCIEC::BOOL>(TRUE);
         };
         break;
      case 3:
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS)
         {
            M_CONFMESS = static_cast<PLCIEC::BOOL>(TRUE);
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
            M_RESET = static_cast<PLCIEC::BOOL>(TRUE);
         };
         break;
      case 5:
         _DONE = static_cast<PLCIEC::BOOL>(TRUE);
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((M_RESET && !(TON_ON.Q)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = static_cast<PLCIEC::BOOL>(TRUE);
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
         _ERRORID = static_cast<PLCIEC::DINT>(528);
      };
      if (TON_2.Q)
      {
         _ERRORID = static_cast<PLCIEC::DINT>(527);
      };
      if (TON_3.Q)
      {
         _ERRORID = static_cast<PLCIEC::DINT>(529);
      };
      if (TON_4.Q)
      {
         _ERRORID = static_cast<PLCIEC::DINT>(531);
      };
      if ((_ERRORID != static_cast<PLCIEC::DINT>(0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _BUSY = (M_STATE > 0) && (M_STATE < 5);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVE
 ******************************************************************************/
class KRC_MOVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::DINT CMDID;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT MOVETYPE;
   E6POS ACTPOSITION;
   E6AXIS AXISPOSITION;
   E6POS CIRCHP;
   PLCIEC::INT VELOCITY;
   PLCIEC::REAL ABSOLUTEVELOCITY;
   PLCIEC::INT ACCELERATION;
   PLCIEC::REAL ABSOLUTEACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   PLCIEC::INT CIRCTYPE;
   PLCIEC::REAL CIRCANGLE;
   APO APPROXIMATE;
   PLCIEC::BOOL POSVALIDX;
   PLCIEC::BOOL POSVALIDY;
   PLCIEC::BOOL POSVALIDZ;
   PLCIEC::BOOL POSVALIDA;
   PLCIEC::BOOL POSVALIDB;
   PLCIEC::BOOL POSVALIDC;
   PLCIEC::BOOL POSVALIDE1;
   PLCIEC::BOOL POSVALIDE2;
   PLCIEC::BOOL POSVALIDE3;
   PLCIEC::BOOL POSVALIDE4;
   PLCIEC::BOOL POSVALIDE5;
   PLCIEC::BOOL POSVALIDE6;
   PLCIEC::BOOL POSVALIDS;
   PLCIEC::BOOL POSVALIDT;
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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

   /* VAR_TEMP */

private:
   PLCIEC::INT COMMANDSIZE;
   PLCIEC::DINT M_VELOCITY;
   PLCIEC::DINT M_ACCELERATION;

public:
   KRC_MOVE()
       : AXISGROUPIDX(0), CMDID(static_cast<PLCIEC::DINT>(1)), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), MOVETYPE(0), ACTPOSITION(), AXISPOSITION(), CIRCHP(), VELOCITY(0), ABSOLUTEVELOCITY(0), ACCELERATION(0), ABSOLUTEACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), CIRCTYPE(0), CIRCANGLE(0), APPROXIMATE(), POSVALIDX(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDY(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDZ(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDA(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDB(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDC(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE1(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE2(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE3(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE4(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE5(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE6(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDS(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDT(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), COMMANDSIZE(0), M_VELOCITY(0), M_ACCELERATION(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (EXECUTECMD)
      {
         if (((VELOCITY > 0) && (ABSOLUTEVELOCITY > 0.0f)))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(520);
            _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            return;
         };
         M_VELOCITY = static_cast<PLCIEC::DINT>(VELOCITY);
         switch (MOVETYPE)
         {
         case 0:
         case 1:
         case 6:
         case 9:
         case 10:
         case 11:
         case 16:
         case 19:
         case 20:
         case 21:
            if ((ABSOLUTEVELOCITY > 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(519);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            }
            break;
         }
         if ((ABSOLUTEVELOCITY > 0.0f))
         {
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP <= 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(544);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            };
            M_VELOCITY = PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((ABSOLUTEVELOCITY * -100000.0f) / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP));
         };

         M_ACCELERATION = static_cast<PLCIEC::DINT>(ACCELERATION);
         switch (MOVETYPE)
         {
         case 0:
         case 1:
         case 6:
         case 9:
         case 10:
         case 11:
         case 16:
         case 19:
         case 20:
         case 21:
            if ((ABSOLUTEACCELERATION > 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(545);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            };
            break;
         };

         if ((ABSOLUTEACCELERATION > 0.0f))
         {
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP <= 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(546);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            }
            // Negative area is from 100.000% to 0.001% and positive area is for the integer percent
            M_ACCELERATION = static_cast<PLCIEC::DINT>((ABSOLUTEACCELERATION * -100000.0f / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP));
         };
      };
      if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
      {
         COMMANDSIZE = 2;
      }
      else
      {
         COMMANDSIZE = 1;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = CMDID;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = COMMANDSIZE;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = POSVALIDX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = POSVALIDY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[3] = POSVALIDZ;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[4] = POSVALIDA;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[5] = POSVALIDB;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[6] = POSVALIDC;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[7] = POSVALIDE1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[8] = POSVALIDE2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[9] = POSVALIDE3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[10] = POSVALIDE4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[11] = POSVALIDE5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[12] = POSVALIDE6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[13] = POSVALIDS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[14] = POSVALIDT;
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[15] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[16] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[17] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[18] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[19] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[20] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[21] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[22] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[23] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[24] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[25] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[26] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[27] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[28] = static_cast<PLCIEC::BOOL>(TRUE);
         };

         if (((((MOVETYPE == 0) || (MOVETYPE == 10)) || (MOVETYPE == 9)) || (MOVETYPE == 19)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(0);
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(ACTPOSITION.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(ACTPOSITION.TURN);
         };

         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6] = PLCIEC::INT_TO_DINT(MOVETYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[7] = M_VELOCITY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[8] = M_ACCELERATION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[9] = PLCIEC::INT_TO_DINT(APPROXIMATE.PTP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[10] = PLCIEC::INT_TO_DINT(APPROXIMATE.CP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[11] = PLCIEC::INT_TO_DINT(APPROXIMATE.CPTP);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[12] = PLCIEC::INT_TO_DINT(APPROXIMATE.CVEL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[13] = PLCIEC::INT_TO_DINT(ORITYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[14] = PLCIEC::INT_TO_DINT(CIRCTYPE);
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[15] = PLCIEC::INT_TO_DINT(CIRCHP.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[16] = PLCIEC::INT_TO_DINT(CIRCHP.TURN);
         };
         if (((((MOVETYPE == 0) || (MOVETYPE == 10)) || (MOVETYPE == 9)) || (MOVETYPE == 19)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = AXISPOSITION.A1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = AXISPOSITION.A2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = AXISPOSITION.A3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = AXISPOSITION.A4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = AXISPOSITION.A5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = AXISPOSITION.A6;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = AXISPOSITION.E1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = AXISPOSITION.E2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = AXISPOSITION.E3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = AXISPOSITION.E4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = AXISPOSITION.E5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = AXISPOSITION.E6;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = ACTPOSITION.X;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = ACTPOSITION.Y;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = ACTPOSITION.Z;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = ACTPOSITION.A;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = ACTPOSITION.B;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = ACTPOSITION.C;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = ACTPOSITION.E1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = ACTPOSITION.E2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = ACTPOSITION.E3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = ACTPOSITION.E4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = ACTPOSITION.E5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = ACTPOSITION.E6;
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13] = APPROXIMATE.CDIS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14] = APPROXIMATE.CORI;
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15] = CIRCHP.X;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16] = CIRCHP.Y;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17] = CIRCHP.Z;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18] = CIRCHP.A;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19] = CIRCHP.B;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20] = CIRCHP.C;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21] = CIRCHP.E1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22] = CIRCHP.E2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23] = CIRCHP.E3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24] = CIRCHP.E4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[25] = CIRCHP.E5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[26] = CIRCHP.E6;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[27] = CIRCANGLE;
         };
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_BRAKETEST
 ******************************************************************************/
class KRC_BRAKETEST
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS PARKPOSITION;
   PLCIEC::INT PARKVELOCITY;
   PLCIEC::INT PARKACCELERATION;
   COORDSYS PARKCOORDINATESYSTEM;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::DINT &RESULT;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::DINT _RESULT;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_BRAKETEST()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), PARKPOSITION(), PARKVELOCITY(0), PARKACCELERATION(0), PARKCOORDINATESYSTEM(), BUFFERMODE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), RESULT(_RESULT), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _RESULT(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _RESULT = static_cast<PLCIEC::DINT>(0);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(29);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 1;
      KRC_MOVE_1.ACTPOSITION = PARKPOSITION;
      KRC_MOVE_1.VELOCITY = PARKVELOCITY;
      KRC_MOVE_1.ACCELERATION = PARKACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = PARKCOORDINATESYSTEM;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKES_OK)
         {
            if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_WARN)
            {
               _RESULT = static_cast<PLCIEC::DINT>(1);
            }
            else
            {
               _RESULT = static_cast<PLCIEC::DINT>(2);
            };
         }
         else
         {
            _RESULT = static_cast<PLCIEC::DINT>(0);
         };
      }
      else
      {
         _RESULT = static_cast<PLCIEC::DINT>(0);
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDREADSTATUS
 ******************************************************************************/
class KRC_CDREADSTATUS
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;
   const PLCIEC::BOOL &ACTIVECOM;
   const PLCIEC::BOOL &ACTIVEPRO;
   const PLCIEC::BOOL &IMPROVEDCOLLMON;
   const PLCIEC::INT &ACTIVEDATASETINDEX;
   const PLCIEC::BOOL &COLLISIONOCCURRED;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;
   PLCIEC::BOOL _ACTIVECOM;
   PLCIEC::BOOL _ACTIVEPRO;
   PLCIEC::BOOL _IMPROVEDCOLLMON;
   PLCIEC::INT _ACTIVEDATASETINDEX;
   PLCIEC::BOOL _COLLISIONOCCURRED;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDREADSTATUS()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), ACTIVECOM(_ACTIVECOM), ACTIVEPRO(_ACTIVEPRO), IMPROVEDCOLLMON(_IMPROVEDCOLLMON), ACTIVEDATASETINDEX(_ACTIVEDATASETINDEX), COLLISIONOCCURRED(_COLLISIONOCCURRED), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), _ACTIVECOM(FALSE), _ACTIVEPRO(FALSE), _IMPROVEDCOLLMON(FALSE), _ACTIVEDATASETINDEX(0), _COLLISIONOCCURRED(FALSE), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(69);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _ACTIVECOM = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _ACTIVEPRO = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _IMPROVEDCOLLMON = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _ACTIVEDATASETINDEX = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _COLLISIONOCCURRED = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDACTIVATEDATASET
 ******************************************************************************/
class KRC_CDACTIVATEDATASET
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::INT DATASETINDEX;

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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDACTIVATEDATASET()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(2), DATASETINDEX(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(70);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = DATASETINDEX;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDREADDATASET
 ******************************************************************************/
class KRC_CDREADDATASET
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT DATASETINDEX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;
   const PLCIEC::INT &THRESHOLD_A1;
   const PLCIEC::INT &THRESHOLD_A2;
   const PLCIEC::INT &THRESHOLD_A3;
   const PLCIEC::INT &THRESHOLD_A4;
   const PLCIEC::INT &THRESHOLD_A5;
   const PLCIEC::INT &THRESHOLD_A6;
   const PLCIEC::INT &THRESHOLD_E1;
   const PLCIEC::INT &THRESHOLD_E2;
   const PLCIEC::INT &THRESHOLD_E3;
   const PLCIEC::INT &THRESHOLD_E4;
   const PLCIEC::INT &THRESHOLD_E5;
   const PLCIEC::INT &THRESHOLD_E6;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;
   PLCIEC::INT _THRESHOLD_A1;
   PLCIEC::INT _THRESHOLD_A2;
   PLCIEC::INT _THRESHOLD_A3;
   PLCIEC::INT _THRESHOLD_A4;
   PLCIEC::INT _THRESHOLD_A5;
   PLCIEC::INT _THRESHOLD_A6;
   PLCIEC::INT _THRESHOLD_E1;
   PLCIEC::INT _THRESHOLD_E2;
   PLCIEC::INT _THRESHOLD_E3;
   PLCIEC::INT _THRESHOLD_E4;
   PLCIEC::INT _THRESHOLD_E5;
   PLCIEC::INT _THRESHOLD_E6;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDREADDATASET()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DATASETINDEX(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), THRESHOLD_A1(_THRESHOLD_A1), THRESHOLD_A2(_THRESHOLD_A2), THRESHOLD_A3(_THRESHOLD_A3), THRESHOLD_A4(_THRESHOLD_A4), THRESHOLD_A5(_THRESHOLD_A5), THRESHOLD_A6(_THRESHOLD_A6), THRESHOLD_E1(_THRESHOLD_E1), THRESHOLD_E2(_THRESHOLD_E2), THRESHOLD_E3(_THRESHOLD_E3), THRESHOLD_E4(_THRESHOLD_E4), THRESHOLD_E5(_THRESHOLD_E5), THRESHOLD_E6(_THRESHOLD_E6), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), _THRESHOLD_A1(150), _THRESHOLD_A2(150), _THRESHOLD_A3(150), _THRESHOLD_A4(150), _THRESHOLD_A5(150), _THRESHOLD_A6(150), _THRESHOLD_E1(150), _THRESHOLD_E2(150), _THRESHOLD_E3(150), _THRESHOLD_E4(150), _THRESHOLD_E5(150), _THRESHOLD_E6(150), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(71);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = DATASETINDEX;
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _THRESHOLD_A1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _THRESHOLD_A2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _THRESHOLD_A3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _THRESHOLD_A4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _THRESHOLD_A5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _THRESHOLD_A6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _THRESHOLD_E1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _THRESHOLD_E2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _THRESHOLD_E3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _THRESHOLD_E4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _THRESHOLD_E5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
         _THRESHOLD_E6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12]);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDWRITEDATASET
 ******************************************************************************/
class KRC_CDWRITEDATASET
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::INT DATASETINDEX;
   PLCIEC::INT THRESHOLD_A1;
   PLCIEC::INT THRESHOLD_A2;
   PLCIEC::INT THRESHOLD_A3;
   PLCIEC::INT THRESHOLD_A4;
   PLCIEC::INT THRESHOLD_A5;
   PLCIEC::INT THRESHOLD_A6;
   PLCIEC::INT THRESHOLD_E1;
   PLCIEC::INT THRESHOLD_E2;
   PLCIEC::INT THRESHOLD_E3;
   PLCIEC::INT THRESHOLD_E4;
   PLCIEC::INT THRESHOLD_E5;
   PLCIEC::INT THRESHOLD_E6;

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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDWRITEDATASET()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(2), DATASETINDEX(0), THRESHOLD_A1(150), THRESHOLD_A2(150), THRESHOLD_A3(150), THRESHOLD_A4(150), THRESHOLD_A5(150), THRESHOLD_A6(150), THRESHOLD_E1(150), THRESHOLD_E2(150), THRESHOLD_E3(150), THRESHOLD_E4(150), THRESHOLD_E5(150), THRESHOLD_E6(150), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(72);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = DATASETINDEX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = THRESHOLD_A1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = THRESHOLD_A2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = THRESHOLD_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = THRESHOLD_A4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6] = THRESHOLD_A5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[7] = THRESHOLD_A6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[8] = THRESHOLD_E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[9] = THRESHOLD_E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[10] = THRESHOLD_E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[11] = THRESHOLD_E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[12] = THRESHOLD_E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[13] = THRESHOLD_E6;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDRESETMAXMEASURED
 ******************************************************************************/
class KRC_CDRESETMAXMEASURED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDRESETMAXMEASURED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(2), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(73);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDREADMAXMEASURED
 ******************************************************************************/
class KRC_CDREADMAXMEASURED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;
   const PLCIEC::INT &MAX_MEASURED_A1;
   const PLCIEC::INT &MAX_MEASURED_A2;
   const PLCIEC::INT &MAX_MEASURED_A3;
   const PLCIEC::INT &MAX_MEASURED_A4;
   const PLCIEC::INT &MAX_MEASURED_A5;
   const PLCIEC::INT &MAX_MEASURED_A6;
   const PLCIEC::INT &MAX_MEASURED_E1;
   const PLCIEC::INT &MAX_MEASURED_E2;
   const PLCIEC::INT &MAX_MEASURED_E3;
   const PLCIEC::INT &MAX_MEASURED_E4;
   const PLCIEC::INT &MAX_MEASURED_E5;
   const PLCIEC::INT &MAX_MEASURED_E6;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;
   PLCIEC::INT _MAX_MEASURED_A1;
   PLCIEC::INT _MAX_MEASURED_A2;
   PLCIEC::INT _MAX_MEASURED_A3;
   PLCIEC::INT _MAX_MEASURED_A4;
   PLCIEC::INT _MAX_MEASURED_A5;
   PLCIEC::INT _MAX_MEASURED_A6;
   PLCIEC::INT _MAX_MEASURED_E1;
   PLCIEC::INT _MAX_MEASURED_E2;
   PLCIEC::INT _MAX_MEASURED_E3;
   PLCIEC::INT _MAX_MEASURED_E4;
   PLCIEC::INT _MAX_MEASURED_E5;
   PLCIEC::INT _MAX_MEASURED_E6;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDREADMAXMEASURED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), MAX_MEASURED_A1(_MAX_MEASURED_A1), MAX_MEASURED_A2(_MAX_MEASURED_A2), MAX_MEASURED_A3(_MAX_MEASURED_A3), MAX_MEASURED_A4(_MAX_MEASURED_A4), MAX_MEASURED_A5(_MAX_MEASURED_A5), MAX_MEASURED_A6(_MAX_MEASURED_A6), MAX_MEASURED_E1(_MAX_MEASURED_E1), MAX_MEASURED_E2(_MAX_MEASURED_E2), MAX_MEASURED_E3(_MAX_MEASURED_E3), MAX_MEASURED_E4(_MAX_MEASURED_E4), MAX_MEASURED_E5(_MAX_MEASURED_E5), MAX_MEASURED_E6(_MAX_MEASURED_E6), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), _MAX_MEASURED_A1(500), _MAX_MEASURED_A2(500), _MAX_MEASURED_A3(500), _MAX_MEASURED_A4(500), _MAX_MEASURED_A5(500), _MAX_MEASURED_A6(500), _MAX_MEASURED_E1(500), _MAX_MEASURED_E2(500), _MAX_MEASURED_E3(500), _MAX_MEASURED_E4(500), _MAX_MEASURED_E5(500), _MAX_MEASURED_E6(500), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(74);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _MAX_MEASURED_A1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _MAX_MEASURED_A2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _MAX_MEASURED_A3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _MAX_MEASURED_A4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _MAX_MEASURED_A5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _MAX_MEASURED_A6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _MAX_MEASURED_E1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _MAX_MEASURED_E2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _MAX_MEASURED_E3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _MAX_MEASURED_E4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _MAX_MEASURED_E5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
         _MAX_MEASURED_E6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12]);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDSTARTTEACHING
 ******************************************************************************/
class KRC_CDSTARTTEACHING
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::INT DATASETINDEX;
   PLCIEC::INT TEACHINGOFFSET;

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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CDSTARTTEACHING()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(2), DATASETINDEX(0), TEACHINGOFFSET(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(75);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = DATASETINDEX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = TEACHINGOFFSET;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CDSTOPTEACHING
 ******************************************************************************/
class KRC_CDSTOPTEACHING
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL APPLY;
   PLCIEC::BOOL APPLYHIGHERONLY;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;
   const PLCIEC::INT &TEACHING_RESULT_A1;
   const PLCIEC::INT &TEACHING_RESULT_A2;
   const PLCIEC::INT &TEACHING_RESULT_A3;
   const PLCIEC::INT &TEACHING_RESULT_A4;
   const PLCIEC::INT &TEACHING_RESULT_A5;
   const PLCIEC::INT &TEACHING_RESULT_A6;
   const PLCIEC::INT &TEACHING_RESULT_E1;
   const PLCIEC::INT &TEACHING_RESULT_E2;
   const PLCIEC::INT &TEACHING_RESULT_E3;
   const PLCIEC::INT &TEACHING_RESULT_E4;
   const PLCIEC::INT &TEACHING_RESULT_E5;
   const PLCIEC::INT &TEACHING_RESULT_E6;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;
   PLCIEC::INT _TEACHING_RESULT_A1;
   PLCIEC::INT _TEACHING_RESULT_A2;
   PLCIEC::INT _TEACHING_RESULT_A3;
   PLCIEC::INT _TEACHING_RESULT_A4;
   PLCIEC::INT _TEACHING_RESULT_A5;
   PLCIEC::INT _TEACHING_RESULT_A6;
   PLCIEC::INT _TEACHING_RESULT_E1;
   PLCIEC::INT _TEACHING_RESULT_E2;
   PLCIEC::INT _TEACHING_RESULT_E3;
   PLCIEC::INT _TEACHING_RESULT_E4;
   PLCIEC::INT _TEACHING_RESULT_E5;
   PLCIEC::INT _TEACHING_RESULT_E6;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::INT NSTATE;

public:
   KRC_CDSTOPTEACHING()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(2), APPLY(FALSE), APPLYHIGHERONLY(FALSE), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), TEACHING_RESULT_A1(_TEACHING_RESULT_A1), TEACHING_RESULT_A2(_TEACHING_RESULT_A2), TEACHING_RESULT_A3(_TEACHING_RESULT_A3), TEACHING_RESULT_A4(_TEACHING_RESULT_A4), TEACHING_RESULT_A5(_TEACHING_RESULT_A5), TEACHING_RESULT_A6(_TEACHING_RESULT_A6), TEACHING_RESULT_E1(_TEACHING_RESULT_E1), TEACHING_RESULT_E2(_TEACHING_RESULT_E2), TEACHING_RESULT_E3(_TEACHING_RESULT_E3), TEACHING_RESULT_E4(_TEACHING_RESULT_E4), TEACHING_RESULT_E5(_TEACHING_RESULT_E5), TEACHING_RESULT_E6(_TEACHING_RESULT_E6), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), _TEACHING_RESULT_A1(500), _TEACHING_RESULT_A2(500), _TEACHING_RESULT_A3(500), _TEACHING_RESULT_A4(500), _TEACHING_RESULT_A5(500), _TEACHING_RESULT_A6(500), _TEACHING_RESULT_E1(500), _TEACHING_RESULT_E2(500), _TEACHING_RESULT_E3(500), _TEACHING_RESULT_E4(500), _TEACHING_RESULT_E5(500), _TEACHING_RESULT_E6(500), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), NSTATE(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };

      if (!(EXECUTECMD))
      {
         NSTATE = 0;
      }

      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(76);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = APPLY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = APPLYHIGHERONLY;
      };

      if ((MXA_EXECUTECOMMAND_1.DONE && (NSTATE == 0)))
      {
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };

      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = MXA_EXECUTECOMMAND_1.DONE;
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(77);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();
      if (MXA_EXECUTECOMMAND_2.READCMDDATARET)
      {
         _TEACHING_RESULT_A1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _TEACHING_RESULT_A2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _TEACHING_RESULT_A3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _TEACHING_RESULT_A4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _TEACHING_RESULT_A5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _TEACHING_RESULT_A6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _TEACHING_RESULT_E1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _TEACHING_RESULT_E2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _TEACHING_RESULT_E3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _TEACHING_RESULT_E4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _TEACHING_RESULT_E5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
         _TEACHING_RESULT_E6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12]);
      }

      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE || MXA_EXECUTECOMMAND_2.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_2.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED || MXA_EXECUTECOMMAND_2.ABORTED;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONTINUE
 ******************************************************************************/
class KRC_CONTINUE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL ENABLE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_CONTINUE()
       : AXISGROUPIDX(0), ENABLE(static_cast<PLCIEC::BOOL>(FALSE)), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (ENABLE)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RELEASEBRAKE = ENABLE;
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVINIT
 ******************************************************************************/
class KRC_CONVINIT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVINIT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(2), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(39);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVSCENEEXISTS
 ******************************************************************************/
class KRC_CONVSCENEEXISTS
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT CONVEYORINDEX;
   PLCIEC::INT SCENESELECTION;
   PLCIEC::INT SCENESTEPOFFSET;
   PLCIEC::INT SCENEABSOLUTEID;
   PLCIEC::REAL STARTOFWORKAREAOFFSET;
   PLCIEC::REAL ENDOFSYNCAREAOFFSET;
   PLCIEC::REAL ALARMDISTANCEOFFSET;
   PLCIEC::REAL ENDOFWORKAREAOFFSET;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &EXISTS;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _EXISTS;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVSCENEEXISTS()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), CONVEYORINDEX(0), SCENESELECTION(0), SCENESTEPOFFSET(0), SCENEABSOLUTEID(0), STARTOFWORKAREAOFFSET(0), ENDOFSYNCAREAOFFSET(0), ALARMDISTANCEOFFSET(0), ENDOFWORKAREAOFFSET(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), EXISTS(_EXISTS), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _EXISTS(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(40);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(CONVEYORINDEX);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(SCENESELECTION);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(SCENESTEPOFFSET);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(SCENEABSOLUTEID);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = STARTOFWORKAREAOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = ENDOFSYNCAREAOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = ALARMDISTANCEOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = ENDOFWORKAREAOFFSET;
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _EXISTS = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVTRACKINGON
 ******************************************************************************/
class KRC_CONVTRACKINGON
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT CONVEYORINDEX;
   PLCIEC::INT SCENESELECTION;
   PLCIEC::INT SCENESTEPOFFSET;
   PLCIEC::INT SCENEABSOLUTEID;
   PLCIEC::BOOL MOVETOSTANDBY;
   PLCIEC::REAL STARTOFWORKAREAOFFSET;
   PLCIEC::REAL ENDOFSYNCAREAOFFSET;
   PLCIEC::REAL ALARMDISTANCEOFFSET;
   PLCIEC::REAL ENDOFWORKAREAOFFSET;
   PLCIEC::REAL RETRACTMOTIONVELOCITY;
   PLCIEC::REAL RETRACTMOTIONACCELERATION;
   PLCIEC::REAL RETRACTMOTIONVECTORX;
   PLCIEC::REAL RETRACTMOTIONVECTORY;
   PLCIEC::REAL RETRACTMOTIONVECTORZ;
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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVTRACKINGON()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), CONVEYORINDEX(0), SCENESELECTION(0), SCENESTEPOFFSET(0), SCENEABSOLUTEID(0), MOVETOSTANDBY(static_cast<PLCIEC::BOOL>(FALSE)), STARTOFWORKAREAOFFSET(0), ENDOFSYNCAREAOFFSET(0), ALARMDISTANCEOFFSET(0), ENDOFWORKAREAOFFSET(0), RETRACTMOTIONVELOCITY(2.0), RETRACTMOTIONACCELERATION(100.0), RETRACTMOTIONVECTORX(0), RETRACTMOTIONVECTORY(0), RETRACTMOTIONVECTORZ(0), BUFFERMODE(2), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(41);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(CONVEYORINDEX);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(SCENESELECTION);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(SCENESTEPOFFSET);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(SCENEABSOLUTEID);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = MOVETOSTANDBY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = STARTOFWORKAREAOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = ENDOFSYNCAREAOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = ALARMDISTANCEOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = ENDOFWORKAREAOFFSET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = RETRACTMOTIONVELOCITY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = RETRACTMOTIONACCELERATION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = RETRACTMOTIONVECTORX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = RETRACTMOTIONVECTORY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = RETRACTMOTIONVECTORZ;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVTRACKINGOFF
 ******************************************************************************/
class KRC_CONVTRACKINGOFF
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT EXECUTIONTYPE;
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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVTRACKINGOFF()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), EXECUTIONTYPE(0), BUFFERMODE(2), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(42);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(EXECUTIONTYPE);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_GETCONVSPEED
 ******************************************************************************/
class KRC_GETCONVSPEED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT CONVEYORINDEX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::REAL &SPEED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::REAL _SPEED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_GETCONVSPEED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), CONVEYORINDEX(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), SPEED(_SPEED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _SPEED(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(43);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(CONVEYORINDEX);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _SPEED = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DEACTIVATEINTERRUPT
 ******************************************************************************/
class KRC_DEACTIVATEINTERRUPT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT INTERRUPT;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_DEACTIVATEINTERRUPT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), INTERRUPT(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(7);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(INTERRUPT);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DECLAREINTERRUPT
 ******************************************************************************/
class KRC_DECLAREINTERRUPT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT INTERRUPT;
   PLCIEC::INT INPUT;
   PLCIEC::BOOL INPUTVALUE;
   PLCIEC::INT REACTION;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_DECLAREINTERRUPT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), INTERRUPT(0), INPUT(0), INPUTVALUE(static_cast<PLCIEC::BOOL>(FALSE)), REACTION(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(5);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = INPUTVALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(INTERRUPT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(REACTION);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(INPUT);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DIAG
 ******************************************************************************/
class KRC_DIAG
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL SHOWTRACE;
   PLCIEC::INT MAXSUBMITCYCLE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::INT &QUEUECOUNT;
   const PLCIEC::BOOL &POSACTVALID;
   const PLCIEC::BOOL &BRAKEACTIVE;
   const PLCIEC::INT &SUBMITHEARTBEAT;
   const PLCIEC::INT &SUBMITCYC_ACT;
   const PLCIEC::INT &SUBMITCYC_MIN;
   const PLCIEC::INT &SUBMITCYC_MAX;
   const PLCIEC::INT &SUBMITCYC_AVG;
   const PLCIEC::DINT &ACTIVEPOSORDERID;
   const PLCIEC::DINT &ACTIVEORDERIDB;
   const PLCIEC::DINT &AVG_DURATION;
   const PLCIEC::INT &PROCONOSHEARTBEAT;
   const PLCIEC::INT &PROCONOSCYC_ACT;
   const PLCIEC::INT &PROCONOSCYC_MIN;
   const PLCIEC::INT &PROCONOSCYC_MAX;
   const PLCIEC::INT &PROCONOSCYC_AVG;
   const PLCIEC::DINT &ERRORID_RI;
   const PLCIEC::DINT &ERRORID_SI;
   const PLCIEC::DINT &ERRORID_PLC;
   const PLCIEC::DINT &ERRORID_PCOS;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::INT _QUEUECOUNT;
   PLCIEC::BOOL _POSACTVALID;
   PLCIEC::BOOL _BRAKEACTIVE;
   PLCIEC::INT _SUBMITHEARTBEAT;
   PLCIEC::INT _SUBMITCYC_ACT;
   PLCIEC::INT _SUBMITCYC_MIN;
   PLCIEC::INT _SUBMITCYC_MAX;
   PLCIEC::INT _SUBMITCYC_AVG;
   PLCIEC::DINT _ACTIVEPOSORDERID;
   PLCIEC::DINT _ACTIVEORDERIDB;
   PLCIEC::DINT _AVG_DURATION;
   PLCIEC::INT _PROCONOSHEARTBEAT;
   PLCIEC::INT _PROCONOSCYC_ACT;
   PLCIEC::INT _PROCONOSCYC_MIN;
   PLCIEC::INT _PROCONOSCYC_MAX;
   PLCIEC::INT _PROCONOSCYC_AVG;
   PLCIEC::DINT _ERRORID_RI;
   PLCIEC::DINT _ERRORID_SI;
   PLCIEC::DINT _ERRORID_PLC;
   PLCIEC::DINT _ERRORID_PCOS;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

   /* VAR */

private:
   PLCIEC::TON TON_1SEC;
   PLCIEC::INT HBLAST;
   PLCIEC::INT HBCYCDIFF;
   PLCIEC::DINT HBSUM;
   PLCIEC::DINT CYCLCNT;
   PLCIEC::DINT PCOSHBLAST;
   PLCIEC::DINT PCOSHBCYCDIFF;
   PLCIEC::DINT PCOSHBSUM;
   PLCIEC::DINT SECSUM;

   /* VAR_TEMP */

private:
   PLCIEC::DINT HBCYCDIFF1000;
   PLCIEC::DINT CYCLCNT1000;
   PLCIEC::DINT PCOSHBCYCDIFF1000;

public:
   KRC_DIAG()
       : AXISGROUPIDX(0), SHOWTRACE(static_cast<PLCIEC::BOOL>(FALSE)), MAXSUBMITCYCLE(0), VALID(_VALID), QUEUECOUNT(_QUEUECOUNT), POSACTVALID(_POSACTVALID), BRAKEACTIVE(_BRAKEACTIVE), SUBMITHEARTBEAT(_SUBMITHEARTBEAT), SUBMITCYC_ACT(_SUBMITCYC_ACT), SUBMITCYC_MIN(_SUBMITCYC_MIN), SUBMITCYC_MAX(_SUBMITCYC_MAX), SUBMITCYC_AVG(_SUBMITCYC_AVG), ACTIVEPOSORDERID(_ACTIVEPOSORDERID), ACTIVEORDERIDB(_ACTIVEORDERIDB), AVG_DURATION(_AVG_DURATION), PROCONOSHEARTBEAT(_PROCONOSHEARTBEAT), PROCONOSCYC_ACT(_PROCONOSCYC_ACT), PROCONOSCYC_MIN(_PROCONOSCYC_MIN), PROCONOSCYC_MAX(_PROCONOSCYC_MAX), PROCONOSCYC_AVG(_PROCONOSCYC_AVG), ERRORID_RI(_ERRORID_RI), ERRORID_SI(_ERRORID_SI), ERRORID_PLC(_ERRORID_PLC), ERRORID_PCOS(_ERRORID_PCOS), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _QUEUECOUNT(0), _POSACTVALID(static_cast<PLCIEC::BOOL>(FALSE)), _BRAKEACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _SUBMITHEARTBEAT(0), _SUBMITCYC_ACT(0), _SUBMITCYC_MIN(0), _SUBMITCYC_MAX(0), _SUBMITCYC_AVG(0), _ACTIVEPOSORDERID(0), _ACTIVEORDERIDB(0), _AVG_DURATION(0), _PROCONOSHEARTBEAT(0), _PROCONOSCYC_ACT(0), _PROCONOSCYC_MIN(0), _PROCONOSCYC_MAX(0), _PROCONOSCYC_AVG(0), _ERRORID_RI(0), _ERRORID_SI(0), _ERRORID_PLC(0), _ERRORID_PCOS(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), TON_1SEC(), HBLAST(0), HBCYCDIFF(0), HBSUM(0), CYCLCNT(0), PCOSHBLAST(0), PCOSHBCYCDIFF(0), PCOSHBSUM(0), SECSUM(0), HBCYCDIFF1000(0), CYCLCNT1000(0), PCOSHBCYCDIFF1000(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.SHOWTRACE = SHOWTRACE;
      if ((MAXSUBMITCYCLE > static_cast<PLCIEC::INT>(0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO = MAXSUBMITCYCLE;
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      _QUEUECOUNT = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.QUEUECOUNT;
      _POSACTVALID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACTVALID;
      _BRAKEACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.BRAKEACTIVE;
      _SUBMITHEARTBEAT = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      _PROCONOSHEARTBEAT = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS;
      _ACTIVEPOSORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ACTIVEPOSORDERID;
      _ACTIVEORDERIDB = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ACTIVEORDERIDB;
      _ERRORID_RI = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID;
      _ERRORID_SI = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB;
      _ERRORID_PCOS = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDPCOS;
      _ERRORID_PLC = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID;
      if ((_ERRORID_PCOS > 0))
      {
         _ERRORID_PCOS = (_ERRORID_PCOS + 700);
      };
      // Call FB TON_1Sec
      TON_1SEC.IN = (KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && !(TON_1SEC.Q));
      TON_1SEC.PT = PLCIEC::MKTIME(1, 0, 1);
      TON_1SEC.OnCycle();
      CYCLCNT = (CYCLCNT + 1);
      if ((HBLAST <= _SUBMITHEARTBEAT))
      {
         HBCYCDIFF = static_cast<PLCIEC::INT>(HBCYCDIFF + (_SUBMITHEARTBEAT - HBLAST));
      }
      else
      {
         HBCYCDIFF = static_cast<PLCIEC::INT>(HBCYCDIFF + ((255 - HBLAST) + _SUBMITHEARTBEAT));
      };
      HBLAST = _SUBMITHEARTBEAT;
      if ((PCOSHBLAST <= _PROCONOSHEARTBEAT))
      {
         PCOSHBCYCDIFF = (PCOSHBCYCDIFF + (_PROCONOSHEARTBEAT - PCOSHBLAST));
      }
      else
      {
         PCOSHBCYCDIFF = (PCOSHBCYCDIFF + ((255 - PCOSHBLAST) + _PROCONOSHEARTBEAT));
      };
      PCOSHBLAST = _PROCONOSHEARTBEAT;
      if (TON_1SEC.Q)
      {
         HBCYCDIFF1000 = HBCYCDIFF;
         PCOSHBCYCDIFF1000 = PCOSHBCYCDIFF;
         CYCLCNT1000 = CYCLCNT;
         if ((HBCYCDIFF > static_cast<PLCIEC::DINT>(0)))
         {
            _SUBMITCYC_ACT = (1000 / HBCYCDIFF);
         }
         else
         {
            _SUBMITCYC_ACT = -(1);
         };
         if ((_SUBMITCYC_MIN == 0))
         {
            _SUBMITCYC_MIN = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
         };
         if (((_SUBMITCYC_ACT < _SUBMITCYC_MIN) && (_SUBMITCYC_ACT > 0)))
         {
            _SUBMITCYC_MIN = _SUBMITCYC_ACT;
         };
         if ((_SUBMITCYC_ACT > _SUBMITCYC_MAX))
         {
            _SUBMITCYC_MAX = _SUBMITCYC_ACT;
         };
         if ((PCOSHBCYCDIFF > 0))
         {
            _PROCONOSCYC_ACT = PLCIEC::DINT_TO_INT(PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((1000 / PCOSHBCYCDIFF) + 0.5)));
         }
         else
         {
            _PROCONOSCYC_ACT = -(1);
         };
         if ((_PROCONOSCYC_MIN == 0))
         {
            _PROCONOSCYC_MIN = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
         };
         if (((_PROCONOSCYC_ACT < _PROCONOSCYC_MIN) && (_PROCONOSCYC_ACT > 0)))
         {
            _PROCONOSCYC_MIN = _PROCONOSCYC_ACT;
         };
         if ((_PROCONOSCYC_ACT > _PROCONOSCYC_MAX))
         {
            _PROCONOSCYC_MAX = _PROCONOSCYC_ACT;
         };
         HBSUM = (HBSUM + HBCYCDIFF);
         PCOSHBSUM = (PCOSHBSUM + PCOSHBCYCDIFF);
         SECSUM = (SECSUM + 1);
         _AVG_DURATION = (SECSUM * 1000);
         if ((HBSUM > 0))
         {
            _SUBMITCYC_AVG = PLCIEC::DINT_TO_INT(PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((_AVG_DURATION / HBSUM) + 0.5)));
         }
         else
         {
            _SUBMITCYC_AVG = -(1);
         };
         if ((PCOSHBSUM > static_cast<PLCIEC::DINT>(0)))
         {
            _PROCONOSCYC_AVG = PLCIEC::DINT_TO_INT((_AVG_DURATION / PCOSHBSUM));
         }
         else
         {
            _PROCONOSCYC_AVG = -(1);
         };
         if ((((SECSUM > 3600) || (_AVG_DURATION < HBSUM)) || (_AVG_DURATION < PCOSHBSUM)))
         {
            HBSUM = 0;
            PCOSHBSUM = 0;
            SECSUM = 0;
            _PROCONOSCYC_MIN = 0;
            _SUBMITCYC_MIN = 0;
         };
         CYCLCNT = 0;
         HBCYCDIFF = 0;
         PCOSHBCYCDIFF = 0;
      };
      if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         _SUBMITCYC_ACT = -(1);
         _SUBMITCYC_MIN = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
         _SUBMITCYC_MAX = -(1);
         _SUBMITCYC_AVG = -(1);
         _AVG_DURATION = static_cast<PLCIEC::DINT>(0);
         _PROCONOSCYC_ACT = -(1);
         _PROCONOSCYC_MIN = PLCIEC::DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
         _PROCONOSCYC_MAX = -(1);
         _PROCONOSCYC_AVG = -(1);
      };
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
       : AXISGROUPIDX(0), MESSAGERESET(static_cast<PLCIEC::BOOL>(FALSE)), ERROR(_ERROR), ERRORID(_ERRORID), NOHEARTBEATKRC(_NOHEARTBEATKRC), NOHEARTBEATPCOS(_NOHEARTBEATPCOS), NOTONLINE(_NOTONLINE), NOTINITIALIZED(_NOTINITIALIZED), NOOPMODEEXT(_NOOPMODEEXT), NOMOVEENABLE(_NOMOVEENABLE), USERSAFENOTOK(_USERSAFENOTOK), KRCERRORACTIVE(_KRCERRORACTIVE), DRIVESNOTREADY(_DRIVESNOTREADY), NOPROGACTIVE(_NOPROGACTIVE), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _NOHEARTBEATKRC(static_cast<PLCIEC::BOOL>(FALSE)), _NOHEARTBEATPCOS(static_cast<PLCIEC::BOOL>(FALSE)), _NOTONLINE(static_cast<PLCIEC::BOOL>(FALSE)), _NOTINITIALIZED(static_cast<PLCIEC::BOOL>(FALSE)), _NOOPMODEEXT(static_cast<PLCIEC::BOOL>(FALSE)), _NOMOVEENABLE(static_cast<PLCIEC::BOOL>(FALSE)), _USERSAFENOTOK(static_cast<PLCIEC::BOOL>(FALSE)), _KRCERRORACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DRIVESNOTREADY(static_cast<PLCIEC::BOOL>(FALSE)), _NOPROGACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), KRC_READMXAERROR_1(), KRC_MESSAGERESET_1(), TON_ON(), TON_OFF(), TON_HBSUB(), TON_HBPCOS(), ENABLETONSUBMIT(static_cast<PLCIEC::BOOL>(FALSE)), ENABLETONPCOS(static_cast<PLCIEC::BOOL>(FALSE)), M_HEARTBEATLAST(0), M_HEARTBEATLASTPCOS(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB KRC_MessageReset_1
      KRC_MESSAGERESET_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MESSAGERESET_1.MESSAGERESET = MESSAGERESET;
      KRC_MESSAGERESET_1.OnCycle();
      // Call FB KRC_ReadMXAError_1
      KRC_READMXAERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_READMXAERROR_1.OnCycle();
      _ERRORID = KRC_READMXAERROR_1.ERRORID;
      if ((_ERRORID == static_cast<PLCIEC::DINT>(0)))
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
            KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = static_cast<PLCIEC::BOOL>(TRUE);
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = static_cast<PLCIEC::BOOL>(TRUE);
            };
         };
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS)
         {
            _ERRORID = static_cast<PLCIEC::DINT>(801);
         };
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
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
 * FUNCTION_BLOCK KRC_FORWARD
 ******************************************************************************/
class KRC_FORWARD
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6AXIS AXIS_VALUES;
   PLCIEC::BOOL CHECKSOFTEND;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const E6POS &POSITION;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   E6POS _ACTPOSITION;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::DINT NORDERID;
   PLCIEC::REAL ERR_STATUS;
   E6POS M_POSITION;
   PLCIEC::INT NERR;

public:
   KRC_FORWARD()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), AXIS_VALUES(), CHECKSOFTEND(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), POSITION(_ACTPOSITION), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ACTPOSITION(), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), NSTATE(0), MXA_EXECUTECOMMAND_0(), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), NORDERID(0), ERR_STATUS(0), M_POSITION(), NERR(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = static_cast<PLCIEC::DINT>(0);
         M_POSITION.X = 0.0;
         M_POSITION.Y = 0.0;
         M_POSITION.Z = 0.0;
         M_POSITION.A = 0.0;
         M_POSITION.B = 0.0;
         M_POSITION.C = 0.0;
         M_POSITION.STATUS = 0;
         M_POSITION.TURN = 0;
         M_POSITION.E1 = 0.0;
         M_POSITION.E2 = 0.0;
         M_POSITION.E3 = 0.0;
         M_POSITION.E4 = 0.0;
         M_POSITION.E5 = 0.0;
         M_POSITION.E6 = 0.0;
         _ACTPOSITION = M_POSITION;
      };
      // Call FB mxA_ExecuteCommand_0
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = (EXECUTECMD && (NSTATE == 0));
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(52);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = CHECKSOFTEND;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = AXIS_VALUES.A1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = AXIS_VALUES.A2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = AXIS_VALUES.A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = AXIS_VALUES.A4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = AXIS_VALUES.A5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = AXIS_VALUES.A6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = AXIS_VALUES.E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = AXIS_VALUES.E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = AXIS_VALUES.E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = AXIS_VALUES.E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = AXIS_VALUES.E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = AXIS_VALUES.E6;
         NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      };
      if ((MXA_EXECUTECOMMAND_0.DONE && (NSTATE == 0)))
      {
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(53);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = static_cast<PLCIEC::DINT>(1);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      };
      if ((MXA_EXECUTECOMMAND_1.READCMDDATARET && (NSTATE == 1)))
      {
         M_POSITION.X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_POSITION.STATUS = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         M_POSITION.TURN = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 2) || (NSTATE == 3)));
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(53);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();
      if ((MXA_EXECUTECOMMAND_2.WRITECMDPAR && (NSTATE == 2)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = static_cast<PLCIEC::DINT>(2);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      };
      if ((MXA_EXECUTECOMMAND_2.READCMDDATARET && (NSTATE == 2)))
      {
         M_POSITION.E1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.E2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.E3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.E4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.E5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.E6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         NSTATE = 3;
      };
      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
      _BUSY = ((MXA_EXECUTECOMMAND_0.BUSY || MXA_EXECUTECOMMAND_1.BUSY) || MXA_EXECUTECOMMAND_2.BUSY);
      _DONE = MXA_EXECUTECOMMAND_2.DONE;
      if ((NSTATE == 3))
      {
         _ACTPOSITION = M_POSITION;
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -(1):
            _ERRORID = static_cast<PLCIEC::DINT>(533);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case -(3):
            _ERRORID = static_cast<PLCIEC::DINT>(534);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case -(4):
            _ERRORID = static_cast<PLCIEC::DINT>(535);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 1:
            _ERRORID = static_cast<PLCIEC::DINT>(536);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 2:
            _ERRORID = static_cast<PLCIEC::DINT>(537);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 0:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         };
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
      }
      else if (EXECUTECMD && (NSTATE == 1))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && ((NSTATE == 2) || (NSTATE == 3)))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_FORWARDADVANCED
 ******************************************************************************/
class KRC_FORWARDADVANCED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6AXIS AXIS_VALUES;
   PLCIEC::BOOL CHECKSOFTEND;
   COORDSYS COORDINATESYSTEM;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const E6POS &POSITION;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   E6POS _ACTPOSITION;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   PLCIEC::DINT NORDERID;
   PLCIEC::REAL ERR_STATUS;
   E6POS M_POSITION;
   PLCIEC::INT NERR;

public:
   KRC_FORWARDADVANCED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), AXIS_VALUES(), CHECKSOFTEND(static_cast<PLCIEC::BOOL>(FALSE)), COORDINATESYSTEM(), BUSY(_BUSY), DONE(_DONE), POSITION(_ACTPOSITION), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ACTPOSITION(), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), NSTATE(0), MXA_EXECUTECOMMAND_0(), NORDERID(0), ERR_STATUS(0), M_POSITION(), NERR(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = static_cast<PLCIEC::DINT>(0);
         M_POSITION.X = 0.0;
         M_POSITION.Y = 0.0;
         M_POSITION.Z = 0.0;
         M_POSITION.A = 0.0;
         M_POSITION.B = 0.0;
         M_POSITION.C = 0.0;
         M_POSITION.STATUS = 0;
         M_POSITION.TURN = 0;
         M_POSITION.E1 = 0.0;
         M_POSITION.E2 = 0.0;
         M_POSITION.E3 = 0.0;
         M_POSITION.E4 = 0.0;
         M_POSITION.E5 = 0.0;
         M_POSITION.E6 = 0.0;
         _ACTPOSITION = M_POSITION;
      };
      // Call FB mxA_ExecuteCommand_0
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(56);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = CHECKSOFTEND;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = AXIS_VALUES.A1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = AXIS_VALUES.A2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = AXIS_VALUES.A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = AXIS_VALUES.A4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = AXIS_VALUES.A5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = AXIS_VALUES.A6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = AXIS_VALUES.E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = AXIS_VALUES.E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = AXIS_VALUES.E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = AXIS_VALUES.E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = AXIS_VALUES.E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = AXIS_VALUES.E6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_POSITION.X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_POSITION.STATUS = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         M_POSITION.TURN = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         M_POSITION.E1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         M_POSITION.E2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         M_POSITION.E3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
         NSTATE = 1;
      };
      if ((MXA_EXECUTECOMMAND_0.DONE && (NSTATE == 1)))
      {
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      _BUSY = MXA_EXECUTECOMMAND_0.BUSY;
      _DONE = MXA_EXECUTECOMMAND_0.DONE;
      if ((NSTATE == 2))
      {
         _ACTPOSITION = M_POSITION;
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -(1):
            _ERRORID = static_cast<PLCIEC::DINT>(533);
            break;
         case -(3):
            _ERRORID = static_cast<PLCIEC::DINT>(534);
            break;
         case -(4):
            _ERRORID = static_cast<PLCIEC::DINT>(535);
            break;
         case 1:
            _ERRORID = static_cast<PLCIEC::DINT>(536);
            break;
         case 2:
            _ERRORID = static_cast<PLCIEC::DINT>(537);
            break;
         case 4:
            _ERRORID = static_cast<PLCIEC::DINT>(549);
            break;
         case 0:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         };
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_GETADVANCE
 ******************************************************************************/
class KRC_GETADVANCE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::INT &COUNT;
   const PLCIEC::INT &MAXWAITTIME;
   const PLCIEC::INT &MODE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::INT _COUNT;
   PLCIEC::INT _MAXWAITTIME;
   PLCIEC::INT _MODE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_GETADVANCE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DONE(_DONE), COUNT(_COUNT), MAXWAITTIME(_MAXWAITTIME), MODE(_MODE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COUNT(0), _MAXWAITTIME(0), _MODE(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(37);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _COUNT = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _MAXWAITTIME = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _MODE = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_GETALLMESSAGES
 ******************************************************************************/
class KRC_GETALLMESSAGES
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_GETALLMESSAGES()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(78);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0; // DIRECT
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
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
   PLCIEC::DINT NSTATE;

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;

public:
   KRC_INITIALIZE()
       : AXISGROUPIDX(0), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), KRC_SERIAL(_KRC_SERIAL), KRC_MAJOR(_KRC_MAJOR), KRC_MINOR(_KRC_MINOR), KRC_REVISION(_KRC_REVISION), KRC_ABSACCUR(_KRC_ABSACCUR), PLC_MAJOR(_PLC_MAJOR), PLC_MINOR(_PLC_MINOR), PLC_REVISION(_PLC_REVISION), KRC_INSTALLED_OPT(_KRC_INSTALLED_OPT), KRC_NUM_ROB_AXIS(_KRC_NUM_ROB_AXIS), KRC_NUM_EX_AXIS(_KRC_NUM_EX_AXIS), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _KRC_SERIAL(0), _KRC_MAJOR(0), _KRC_MINOR(0), _KRC_REVISION(0), _KRC_ABSACCUR(0), _PLC_MAJOR(0), _PLC_MINOR(0), _PLC_REVISION(0), _KRC_INSTALLED_OPT(0), _KRC_NUM_ROB_AXIS(0), _KRC_NUM_EX_AXIS(0), _ORDERID(0), MXA_EXECUTECOMMAND_0(), MXA_EXECUTECOMMAND_1(), MXA_RESETCOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _PLC_MAJOR = static_cast<PLCIEC::DINT>(6);
      _PLC_MINOR = static_cast<PLCIEC::DINT>(1);
      _PLC_REVISION = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MAJOR = _PLC_MAJOR;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MINOR = _PLC_MINOR;
      if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         NSTATE = 0;
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = static_cast<PLCIEC::BOOL>(FALSE);
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      if ((((KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED == static_cast<PLCIEC::BOOL>(FALSE)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > static_cast<PLCIEC::DINT>(0))) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID != static_cast<PLCIEC::DINT>(31))))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = 0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = 0;
      };

      // =========================
      // Part #1 (nPart = 0)
      // =========================
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (NSTATE == 0);
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(31);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.OnCycle();

      if (MXA_EXECUTECOMMAND_0.WRITECMDPAR && NSTATE == 0)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = 0;
      }

      if (MXA_EXECUTECOMMAND_0.READCMDDATARET && NSTATE == 0)
      {
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

         if (!((_KRC_MAJOR == _PLC_MAJOR) && (_KRC_MINOR >= _PLC_MINOR)))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(503);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
            NSTATE = 9;
         }
      }

      if (MXA_EXECUTECOMMAND_0.DONE && NSTATE == 0)
      {
         NSTATE = 1;
      }

      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      }

      // =========================
      // Part #2 (nPart = 1)
      // =========================
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = static_cast<PLCIEC::BOOL>(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(31);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = 1;
      }

      if (MXA_EXECUTECOMMAND_1.READCMDDATARET && NSTATE == 1)
      {
         auto &ret = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN;
         PLCIEC::DINT sn_1 = PLCIEC::REAL_TO_DINT(ret[1]);
         PLCIEC::DINT sn_2 = PLCIEC::REAL_TO_DINT(ret[2]);
         _KRC_SERIAL = static_cast<PLCIEC::DINT>((sn_1 & 0xFFFF) | ((sn_2 & 0xFFFF) << 16));
      }

      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      }

      if (NSTATE == 0)
      {
         _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
      }
      else if (NSTATE == 1)
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }

      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _DONE = MXA_EXECUTECOMMAND_1.DONE;

      if (_DONE)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = static_cast<PLCIEC::BOOL>(TRUE);
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INTERRUPT
 ******************************************************************************/
class KRC_INTERRUPT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   PLCIEC::BOOL FAST;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BRAKEACTIVE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BRAKEACTIVE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_INTERRUPT()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), FAST(static_cast<PLCIEC::BOOL>(FALSE)), BRAKEACTIVE(_BRAKEACTIVE), ERROR(_ERROR), ERRORID(_ERRORID), _BRAKEACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (EXECUTE)
      {
         if (FAST)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKEF = static_cast<PLCIEC::BOOL>(TRUE);
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKE = static_cast<PLCIEC::BOOL>(TRUE);
         };
      };
      _BRAKEACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.BRAKEACTIVE;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INVERSE
 ******************************************************************************/
class KRC_INVERSE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::BOOL POSVALIDS;
   PLCIEC::BOOL POSVALIDT;
   E6AXIS START_AXIS;
   PLCIEC::BOOL CHECKSOFTEND;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const E6AXIS &AXISPOSITION;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   E6AXIS _AXISPOSITION;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::DINT NORDERID;
   PLCIEC::REAL ERR_STATUS;
   E6AXIS M_POSITION;
   PLCIEC::INT NERR;

public:
   KRC_INVERSE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), POSVALIDS(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDT(static_cast<PLCIEC::BOOL>(FALSE)), START_AXIS(), CHECKSOFTEND(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), AXISPOSITION(_AXISPOSITION), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _AXISPOSITION(), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), NSTATE(0), MXA_EXECUTECOMMAND_0(), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), NORDERID(0), ERR_STATUS(0), M_POSITION(), NERR(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = static_cast<PLCIEC::DINT>(0);
         M_POSITION.A1 = 0.0;
         M_POSITION.A2 = 0.0;
         M_POSITION.A3 = 0.0;
         M_POSITION.A4 = 0.0;
         M_POSITION.A5 = 0.0;
         M_POSITION.A6 = 0.0;
         M_POSITION.E1 = 0.0;
         M_POSITION.E2 = 0.0;
         M_POSITION.E3 = 0.0;
         M_POSITION.E4 = 0.0;
         M_POSITION.E5 = 0.0;
         M_POSITION.E6 = 0.0;
         _AXISPOSITION = M_POSITION;
      };
      // Call FB mxA_ExecuteCommand_0
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = (EXECUTECMD && (NSTATE == 0));
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(54);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = CHECKSOFTEND;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = POSVALIDS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[3] = POSVALIDT;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = POSITION.STATUS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = POSITION.TURN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = POSITION.X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = POSITION.Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = POSITION.Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = POSITION.A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = POSITION.B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = POSITION.C;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = POSITION.E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = POSITION.E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = POSITION.E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = POSITION.E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = POSITION.E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = POSITION.E6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13] = START_AXIS.A1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14] = START_AXIS.A2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15] = START_AXIS.A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16] = START_AXIS.A4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17] = START_AXIS.A5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18] = START_AXIS.A6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19] = START_AXIS.E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20] = START_AXIS.E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21] = START_AXIS.E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22] = START_AXIS.E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23] = START_AXIS.E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24] = START_AXIS.E6;
         NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      };
      if ((MXA_EXECUTECOMMAND_0.DONE && (NSTATE == 0)))
      {
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(55);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = static_cast<PLCIEC::DINT>(1);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      };
      if ((MXA_EXECUTECOMMAND_1.READCMDDATARET && (NSTATE == 1)))
      {
         M_POSITION.A1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.A2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.A3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.A4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.A5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.A6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 2) || (NSTATE == 3)));
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(55);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();
      if ((MXA_EXECUTECOMMAND_2.WRITECMDPAR && (NSTATE == 2)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = static_cast<PLCIEC::DINT>(2);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      };
      if ((MXA_EXECUTECOMMAND_2.READCMDDATARET && (NSTATE == 2)))
      {
         M_POSITION.E1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.E2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.E3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.E4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.E5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.E6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         NSTATE = 3;
      };
      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
      if ((NSTATE == 3))
      {
         _AXISPOSITION = M_POSITION;
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -(1):
            _ERRORID = static_cast<PLCIEC::DINT>(538);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case -(3):
            _ERRORID = static_cast<PLCIEC::DINT>(539);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case -(4):
            _ERRORID = static_cast<PLCIEC::DINT>(540);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 1:
            _ERRORID = static_cast<PLCIEC::DINT>(541);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 2:
            _ERRORID = static_cast<PLCIEC::DINT>(542);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 3:
            _ERRORID = static_cast<PLCIEC::DINT>(547);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            break;
         case 0:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         };
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _BUSY = ((MXA_EXECUTECOMMAND_0.BUSY || MXA_EXECUTECOMMAND_1.BUSY) || MXA_EXECUTECOMMAND_2.BUSY);
      _DONE = MXA_EXECUTECOMMAND_2.DONE && !_ERROR;

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
      }
      else if (EXECUTECMD && (NSTATE == 1))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && ((NSTATE == 2) || (NSTATE == 3)))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INVERSEADVANCED
 ******************************************************************************/
class KRC_INVERSEADVANCED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::BOOL POSVALIDS;
   PLCIEC::BOOL POSVALIDT;
   E6AXIS START_AXIS;
   PLCIEC::BOOL CHECKSOFTEND;
   COORDSYS COORDINATESYSTEM;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const E6AXIS &AXISPOSITION;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   E6AXIS _AXISPOSITION;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   PLCIEC::DINT NORDERID;
   PLCIEC::REAL ERR_STATUS;
   E6AXIS M_POSITION;
   PLCIEC::INT NERR;

public:
   KRC_INVERSEADVANCED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), POSVALIDS(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDT(static_cast<PLCIEC::BOOL>(FALSE)), START_AXIS(), CHECKSOFTEND(static_cast<PLCIEC::BOOL>(FALSE)), COORDINATESYSTEM(), BUSY(_BUSY), DONE(_DONE), AXISPOSITION(_AXISPOSITION), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _AXISPOSITION(), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), NSTATE(0), MXA_EXECUTECOMMAND_0(), NORDERID(0), ERR_STATUS(0), M_POSITION(), NERR(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = static_cast<PLCIEC::DINT>(0);
         M_POSITION.A1 = 0.0;
         M_POSITION.A2 = 0.0;
         M_POSITION.A3 = 0.0;
         M_POSITION.A4 = 0.0;
         M_POSITION.A5 = 0.0;
         M_POSITION.A6 = 0.0;
         M_POSITION.E1 = 0.0;
         M_POSITION.E2 = 0.0;
         M_POSITION.E3 = 0.0;
         M_POSITION.E4 = 0.0;
         M_POSITION.E5 = 0.0;
         M_POSITION.E6 = 0.0;
         _AXISPOSITION = M_POSITION;
      };
      // Call FB mxA_ExecuteCommand_0
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(57);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = CHECKSOFTEND;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = POSVALIDS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[3] = POSVALIDT;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = POSITION.STATUS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = POSITION.TURN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = POSITION.X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = POSITION.Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = POSITION.Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = POSITION.A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = POSITION.B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = POSITION.C;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = POSITION.E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = POSITION.E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = POSITION.E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = POSITION.E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = POSITION.E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = POSITION.E6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13] = START_AXIS.A1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14] = START_AXIS.A2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15] = START_AXIS.A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16] = START_AXIS.A4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17] = START_AXIS.A5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18] = START_AXIS.A6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19] = START_AXIS.E1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20] = START_AXIS.E2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21] = START_AXIS.E3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22] = START_AXIS.E4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23] = START_AXIS.E5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24] = START_AXIS.E6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_POSITION.A1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.A2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.A3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.A4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.A5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.A6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_POSITION.E1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         M_POSITION.E2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         M_POSITION.E3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
         NSTATE = 1;
      };
      if ((MXA_EXECUTECOMMAND_0.DONE && (NSTATE == 1)))
      {
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      if ((NSTATE == 2))
      {
         _AXISPOSITION = M_POSITION;
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -(1):
            _ERRORID = static_cast<PLCIEC::DINT>(538);
            break;
         case -(3):
            _ERRORID = static_cast<PLCIEC::DINT>(539);
            break;
         case -(4):
            _ERRORID = static_cast<PLCIEC::DINT>(540);
            break;
         case 1:
            _ERRORID = static_cast<PLCIEC::DINT>(541);
            break;
         case 2:
            _ERRORID = static_cast<PLCIEC::DINT>(542);
            break;
         case 3:
            _ERRORID = static_cast<PLCIEC::DINT>(547);
            break;
         case 4:
            _ERRORID = static_cast<PLCIEC::DINT>(549);
            break;
         case 0:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         };
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _BUSY = MXA_EXECUTECOMMAND_0.BUSY;
      _DONE = MXA_EXECUTECOMMAND_0.DONE && !_ERROR;
      _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOG
 ******************************************************************************/
class KRC_JOG
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::INT MOVETYPE;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::REAL INCREMENT;
   PLCIEC::BOOL A1_X_P;
   PLCIEC::BOOL A1_X_M;
   PLCIEC::BOOL A2_Y_P;
   PLCIEC::BOOL A2_Y_M;
   PLCIEC::BOOL A3_Z_P;
   PLCIEC::BOOL A3_Z_M;
   PLCIEC::BOOL A4_A_P;
   PLCIEC::BOOL A4_A_M;
   PLCIEC::BOOL A5_B_P;
   PLCIEC::BOOL A5_B_M;
   PLCIEC::BOOL A6_C_P;
   PLCIEC::BOOL A6_C_M;
   PLCIEC::BOOL E1_P;
   PLCIEC::BOOL E1_M;
   PLCIEC::BOOL E2_P;
   PLCIEC::BOOL E2_M;
   PLCIEC::BOOL E3_P;
   PLCIEC::BOOL E3_M;
   PLCIEC::BOOL E4_P;
   PLCIEC::BOOL E4_M;
   PLCIEC::BOOL E5_P;
   PLCIEC::BOOL E5_M;
   PLCIEC::BOOL E6_P;
   PLCIEC::BOOL E6_M;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   KRC_ABORT KRC_ABORT_1;
   E6POS M_POSITION;
   E6AXIS M_AXISPOSITION;
   PLCIEC::INT M_MOVETYPE;
   PLCIEC::BOOL M_EXECUTECMD;
   PLCIEC::BOOL M_CMDINPUTACTIVE;
   PLCIEC::BOOL M_CMDINPUTACTIVELAST;
   PLCIEC::BOOL M_CMDINPUTACTIVECHANGED;
   PLCIEC::BOOL M_CMDINPUTCHANGED;
   PLCIEC::BOOL M_INCREMENTACTIVE;
   PLCIEC::REAL M_MAXDELTA;
   PLCIEC::BOOL M_EXECUTEABORT;
   PLCIEC::BOOL A1_X_P_LAST;
   PLCIEC::BOOL A1_X_M_LAST;
   PLCIEC::BOOL A2_Y_P_LAST;
   PLCIEC::BOOL A2_Y_M_LAST;
   PLCIEC::BOOL A3_Z_P_LAST;
   PLCIEC::BOOL A3_Z_M_LAST;
   PLCIEC::BOOL A4_A_P_LAST;
   PLCIEC::BOOL A4_A_M_LAST;
   PLCIEC::BOOL A5_B_P_LAST;
   PLCIEC::BOOL A5_B_M_LAST;
   PLCIEC::BOOL A6_C_P_LAST;
   PLCIEC::BOOL A6_C_M_LAST;
   PLCIEC::BOOL E1_P_LAST;
   PLCIEC::BOOL E1_M_LAST;
   PLCIEC::BOOL E2_P_LAST;
   PLCIEC::BOOL E2_M_LAST;
   PLCIEC::BOOL E3_P_LAST;
   PLCIEC::BOOL E3_M_LAST;
   PLCIEC::BOOL E4_P_LAST;
   PLCIEC::BOOL E4_M_LAST;
   PLCIEC::BOOL E5_P_LAST;
   PLCIEC::BOOL E5_M_LAST;
   PLCIEC::BOOL E6_P_LAST;
   PLCIEC::BOOL E6_M_LAST;
   // bugfix
   PLCIEC::BOOL M_EXECUTECMD_FINISHED;

public:
   KRC_JOG()
       : AXISGROUPIDX(0), MOVETYPE(0), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), INCREMENT(0), A1_X_P(static_cast<PLCIEC::BOOL>(FALSE)), A1_X_M(static_cast<PLCIEC::BOOL>(FALSE)), A2_Y_P(static_cast<PLCIEC::BOOL>(FALSE)), A2_Y_M(static_cast<PLCIEC::BOOL>(FALSE)), A3_Z_P(static_cast<PLCIEC::BOOL>(FALSE)), A3_Z_M(static_cast<PLCIEC::BOOL>(FALSE)), A4_A_P(static_cast<PLCIEC::BOOL>(FALSE)), A4_A_M(static_cast<PLCIEC::BOOL>(FALSE)), A5_B_P(static_cast<PLCIEC::BOOL>(FALSE)), A5_B_M(static_cast<PLCIEC::BOOL>(FALSE)), A6_C_P(static_cast<PLCIEC::BOOL>(FALSE)), A6_C_M(static_cast<PLCIEC::BOOL>(FALSE)), E1_P(static_cast<PLCIEC::BOOL>(FALSE)), E1_M(static_cast<PLCIEC::BOOL>(FALSE)), E2_P(static_cast<PLCIEC::BOOL>(FALSE)), E2_M(static_cast<PLCIEC::BOOL>(FALSE)), E3_P(static_cast<PLCIEC::BOOL>(FALSE)), E3_M(static_cast<PLCIEC::BOOL>(FALSE)), E4_P(static_cast<PLCIEC::BOOL>(FALSE)), E4_M(static_cast<PLCIEC::BOOL>(FALSE)), E5_P(static_cast<PLCIEC::BOOL>(FALSE)), E5_M(static_cast<PLCIEC::BOOL>(FALSE)), E6_P(static_cast<PLCIEC::BOOL>(FALSE)), E6_M(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), KRC_ABORT_1(), M_POSITION(), M_AXISPOSITION(), M_MOVETYPE(0), M_EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), M_CMDINPUTACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), M_CMDINPUTACTIVELAST(static_cast<PLCIEC::BOOL>(FALSE)), M_CMDINPUTACTIVECHANGED(static_cast<PLCIEC::BOOL>(FALSE)), M_CMDINPUTCHANGED(static_cast<PLCIEC::BOOL>(FALSE)), M_INCREMENTACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), M_MAXDELTA(0), M_EXECUTEABORT(static_cast<PLCIEC::BOOL>(FALSE)), A1_X_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A1_X_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A2_Y_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A2_Y_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A3_Z_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A3_Z_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A4_A_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A4_A_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A5_B_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A5_B_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A6_C_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), A6_C_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E1_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E1_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E2_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E2_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E3_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E3_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E4_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E4_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E5_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E5_M_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E6_P_LAST(static_cast<PLCIEC::BOOL>(FALSE)), E6_M_LAST(static_cast<PLCIEC::BOOL>(FALSE))
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (((((((((((((A1_X_P && A1_X_M) || (A2_Y_P && A2_Y_M)) || (A3_Z_P && A3_Z_M)) || (A4_A_P && A4_A_M)) || (A5_B_P && A5_B_M)) || (A6_C_P && A6_C_M)) || (E1_P && E1_M)) || (E2_P && E2_M)) || (E3_P && E3_M)) || (E4_P && E4_M)) || (E5_P && E5_M)) || (E6_P && E6_M)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(548);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      M_INCREMENTACTIVE = (INCREMENT > 0.0f);
      switch (MOVETYPE)
      {
      case 0:
         M_MOVETYPE = 9;
         break;
      case 1:
         M_MOVETYPE = 3;
         break;
      case 2:
         M_MOVETYPE = 19;
         break;
      default:
         _ERRORID = static_cast<PLCIEC::DINT>(590);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      M_CMDINPUTACTIVE = (((((((((((((((((((((((A1_X_P || A1_X_M) || A2_Y_P) || A2_Y_M) || A3_Z_P) || A3_Z_M) || A4_A_P) || A4_A_M) || A5_B_P) || A5_B_M) || A6_C_P) || A6_C_M) || E1_P) || E1_M) || E2_P) || E2_M) || E3_P) || E3_M) || E4_P) || E4_M) || E5_P) || E5_M) || E6_P) || E6_M);
      M_CMDINPUTACTIVECHANGED = (M_CMDINPUTACTIVELAST != M_CMDINPUTACTIVE);
      M_CMDINPUTACTIVELAST = M_CMDINPUTACTIVE;
      if ((M_CMDINPUTACTIVECHANGED && !(M_CMDINPUTACTIVE)))
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(TRUE);
      };
      M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(FALSE);
      if ((A1_X_P != A1_X_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A1_X_M != A1_X_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A2_Y_P != A2_Y_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A2_Y_M != A2_Y_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A3_Z_P != A3_Z_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A3_Z_M != A3_Z_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A4_A_P != A4_A_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A4_A_M != A4_A_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A5_B_P != A5_B_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A5_B_M != A5_B_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A6_C_P != A6_C_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((A6_C_M != A6_C_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E1_P != E1_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E1_M != E1_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E2_P != E2_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E2_M != E2_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E3_P != E3_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E3_M != E3_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E4_P != E4_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E4_M != E4_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E5_P != E5_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E5_M != E5_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E6_P != E6_P_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if ((E6_M != E6_M_LAST))
      {
         M_CMDINPUTCHANGED = static_cast<PLCIEC::BOOL>(TRUE);
      };
      A1_X_P_LAST = A1_X_P;
      A1_X_M_LAST = A1_X_M;
      A2_Y_P_LAST = A2_Y_P;
      A2_Y_M_LAST = A2_Y_M;
      A3_Z_P_LAST = A3_Z_P;
      A3_Z_M_LAST = A3_Z_M;
      A4_A_P_LAST = A4_A_P;
      A4_A_M_LAST = A4_A_M;
      A5_B_P_LAST = A5_B_P;
      A5_B_M_LAST = A5_B_M;
      A6_C_P_LAST = A6_C_P;
      A6_C_M_LAST = A6_C_M;
      E1_P_LAST = E1_P;
      E1_M_LAST = E1_M;
      E2_P_LAST = E2_P;
      E2_M_LAST = E2_M;
      E3_P_LAST = E3_P;
      E3_M_LAST = E3_M;
      E4_P_LAST = E4_P;
      E4_M_LAST = E4_M;
      E5_P_LAST = E5_P;
      E5_M_LAST = E5_M;
      E6_P_LAST = E6_P;
      E6_M_LAST = E6_M;
      M_EXECUTECMD = (M_CMDINPUTACTIVE && (!(M_CMDINPUTCHANGED) || M_CMDINPUTACTIVECHANGED));
      M_MAXDELTA = 100000.0;
      M_AXISPOSITION.A1 = 0.0;
      M_AXISPOSITION.A2 = 0.0;
      M_AXISPOSITION.A3 = 0.0;
      M_AXISPOSITION.A4 = 0.0;
      M_AXISPOSITION.A5 = 0.0;
      M_AXISPOSITION.A6 = 0.0;
      M_AXISPOSITION.E1 = 0.0;
      M_AXISPOSITION.E2 = 0.0;
      M_AXISPOSITION.E3 = 0.0;
      M_AXISPOSITION.E4 = 0.0;
      M_AXISPOSITION.E5 = 0.0;
      M_AXISPOSITION.E6 = 0.0;
      M_POSITION.X = 0.0;
      M_POSITION.Y = 0.0;
      M_POSITION.Z = 0.0;
      M_POSITION.A = 0.0;
      M_POSITION.B = 0.0;
      M_POSITION.C = 0.0;
      M_POSITION.E1 = 0.0;
      M_POSITION.E2 = 0.0;
      M_POSITION.E3 = 0.0;
      M_POSITION.E4 = 0.0;
      M_POSITION.E5 = 0.0;
      M_POSITION.E6 = 0.0;
      if (M_EXECUTECMD)
      {
         switch (MOVETYPE)
         {
         case 0:
         case 2:
            if (M_INCREMENTACTIVE)
            {
               if (A1_X_P)
               {
                  M_AXISPOSITION.A1 = INCREMENT;
               };
               if (A1_X_M)
               {
                  M_AXISPOSITION.A1 = (INCREMENT * -(1));
               };
               if (A2_Y_P)
               {
                  M_AXISPOSITION.A2 = INCREMENT;
               };
               if (A2_Y_M)
               {
                  M_AXISPOSITION.A2 = (INCREMENT * -(1));
               };
               if (A3_Z_P)
               {
                  M_AXISPOSITION.A3 = INCREMENT;
               };
               if (A3_Z_M)
               {
                  M_AXISPOSITION.A3 = (INCREMENT * -(1));
               };
               if (A4_A_P)
               {
                  M_AXISPOSITION.A4 = INCREMENT;
               };
               if (A4_A_M)
               {
                  M_AXISPOSITION.A4 = (INCREMENT * -(1));
               };
               if (A5_B_P)
               {
                  M_AXISPOSITION.A5 = INCREMENT;
               };
               if (A5_B_M)
               {
                  M_AXISPOSITION.A5 = (INCREMENT * -(1));
               };
               if (A6_C_P)
               {
                  M_AXISPOSITION.A6 = INCREMENT;
               };
               if (A6_C_M)
               {
                  M_AXISPOSITION.A6 = (INCREMENT * -(1));
               };
               if (E1_P)
               {
                  M_AXISPOSITION.E1 = INCREMENT;
               };
               if (E1_M)
               {
                  M_AXISPOSITION.E1 = (INCREMENT * -(1));
               };
               if (E2_P)
               {
                  M_AXISPOSITION.E2 = INCREMENT;
               };
               if (E2_M)
               {
                  M_AXISPOSITION.E2 = (INCREMENT * -(1));
               };
               if (E3_P)
               {
                  M_AXISPOSITION.E3 = INCREMENT;
               };
               if (E3_M)
               {
                  M_AXISPOSITION.E3 = (INCREMENT * -(1));
               };
               if (E4_P)
               {
                  M_AXISPOSITION.E4 = INCREMENT;
               };
               if (E4_M)
               {
                  M_AXISPOSITION.E4 = (INCREMENT * -(1));
               };
               if (E5_P)
               {
                  M_AXISPOSITION.E5 = INCREMENT;
               };
               if (E5_M)
               {
                  M_AXISPOSITION.E5 = (INCREMENT * -(1));
               };
               if (E6_P)
               {
                  M_AXISPOSITION.E6 = INCREMENT;
               };
               if (E6_M)
               {
                  M_AXISPOSITION.E6 = (INCREMENT * -(1));
               };
            }
            else
            {
               if (A1_X_P)
               {
                  M_AXISPOSITION.A1 = M_MAXDELTA;
               };
               if (A1_X_M)
               {
                  M_AXISPOSITION.A1 = (M_MAXDELTA * -(1));
               };
               if (A2_Y_P)
               {
                  M_AXISPOSITION.A2 = M_MAXDELTA;
               };
               if (A2_Y_M)
               {
                  M_AXISPOSITION.A2 = (M_MAXDELTA * -(1));
               };
               if (A3_Z_P)
               {
                  M_AXISPOSITION.A3 = M_MAXDELTA;
               };
               if (A3_Z_M)
               {
                  M_AXISPOSITION.A3 = (M_MAXDELTA * -(1));
               };
               if (A4_A_P)
               {
                  M_AXISPOSITION.A4 = M_MAXDELTA;
               };
               if (A4_A_M)
               {
                  M_AXISPOSITION.A4 = (M_MAXDELTA * -(1));
               };
               if (A5_B_P)
               {
                  M_AXISPOSITION.A5 = M_MAXDELTA;
               };
               if (A5_B_M)
               {
                  M_AXISPOSITION.A5 = (M_MAXDELTA * -(1));
               };
               if (A6_C_P)
               {
                  M_AXISPOSITION.A6 = M_MAXDELTA;
               };
               if (A6_C_M)
               {
                  M_AXISPOSITION.A6 = (M_MAXDELTA * -(1));
               };
               if (E1_P)
               {
                  M_AXISPOSITION.E1 = M_MAXDELTA;
               };
               if (E1_M)
               {
                  M_AXISPOSITION.E1 = (M_MAXDELTA * -(1));
               };
               if (E2_P)
               {
                  M_AXISPOSITION.E2 = M_MAXDELTA;
               };
               if (E2_M)
               {
                  M_AXISPOSITION.E2 = (M_MAXDELTA * -(1));
               };
               if (E3_P)
               {
                  M_AXISPOSITION.E3 = M_MAXDELTA;
               };
               if (E3_M)
               {
                  M_AXISPOSITION.E3 = (M_MAXDELTA * -(1));
               };
               if (E4_P)
               {
                  M_AXISPOSITION.E4 = M_MAXDELTA;
               };
               if (E4_M)
               {
                  M_AXISPOSITION.E4 = (M_MAXDELTA * -(1));
               };
               if (E5_P)
               {
                  M_AXISPOSITION.E5 = M_MAXDELTA;
               };
               if (E5_M)
               {
                  M_AXISPOSITION.E5 = (M_MAXDELTA * -(1));
               };
               if (E6_P)
               {
                  M_AXISPOSITION.E6 = M_MAXDELTA;
               };
               if (E6_M)
               {
                  M_AXISPOSITION.E6 = (M_MAXDELTA * -(1));
               };
            }
            break;
         case 1:
            if (M_INCREMENTACTIVE)
            {
               if (A1_X_P)
               {
                  M_POSITION.X = INCREMENT;
               };
               if (A1_X_M)
               {
                  M_POSITION.X = (INCREMENT * -(1));
               };
               if (A2_Y_P)
               {
                  M_POSITION.Y = INCREMENT;
               };
               if (A2_Y_M)
               {
                  M_POSITION.Y = (INCREMENT * -(1));
               };
               if (A3_Z_P)
               {
                  M_POSITION.Z = INCREMENT;
               };
               if (A3_Z_M)
               {
                  M_POSITION.Z = (INCREMENT * -(1));
               };
               if (A4_A_P)
               {
                  M_POSITION.A = INCREMENT;
               };
               if (A4_A_M)
               {
                  M_POSITION.A = (INCREMENT * -(1));
               };
               if (A5_B_P)
               {
                  M_POSITION.B = INCREMENT;
               };
               if (A5_B_M)
               {
                  M_POSITION.B = (INCREMENT * -(1));
               };
               if (A6_C_P)
               {
                  M_POSITION.C = INCREMENT;
               };
               if (A6_C_M)
               {
                  M_POSITION.C = (INCREMENT * -(1));
               };
               if (E1_P)
               {
                  M_POSITION.E1 = INCREMENT;
               };
               if (E1_M)
               {
                  M_POSITION.E1 = (INCREMENT * -(1));
               };
               if (E2_P)
               {
                  M_POSITION.E2 = INCREMENT;
               };
               if (E2_M)
               {
                  M_POSITION.E2 = (INCREMENT * -(1));
               };
               if (E3_P)
               {
                  M_POSITION.E3 = INCREMENT;
               };
               if (E3_M)
               {
                  M_POSITION.E3 = (INCREMENT * -(1));
               };
               if (E4_P)
               {
                  M_POSITION.E4 = INCREMENT;
               };
               if (E4_M)
               {
                  M_POSITION.E4 = (INCREMENT * -(1));
               };
               if (E5_P)
               {
                  M_POSITION.E5 = INCREMENT;
               };
               if (E5_M)
               {
                  M_POSITION.E5 = (INCREMENT * -(1));
               };
               if (E6_P)
               {
                  M_POSITION.E6 = INCREMENT;
               };
               if (E6_M)
               {
                  M_POSITION.E6 = (INCREMENT * -(1));
               };
            }
            else
            {
               if (A1_X_P)
               {
                  M_POSITION.X = M_MAXDELTA;
               };
               if (A1_X_M)
               {
                  M_POSITION.X = (M_MAXDELTA * -(1));
               };
               if (A2_Y_P)
               {
                  M_POSITION.Y = M_MAXDELTA;
               };
               if (A2_Y_M)
               {
                  M_POSITION.Y = (M_MAXDELTA * -(1));
               };
               if (A3_Z_P)
               {
                  M_POSITION.Z = M_MAXDELTA;
               };
               if (A3_Z_M)
               {
                  M_POSITION.Z = (M_MAXDELTA * -(1));
               };
               if (A4_A_P)
               {
                  M_POSITION.A = 90.0;
               };
               if (A4_A_M)
               {
                  M_POSITION.A = (90.0 * -(1));
               };
               if (A5_B_P)
               {
                  M_POSITION.B = 90.0;
               };
               if (A5_B_M)
               {
                  M_POSITION.B = (90.0 * -(1));
               };
               if (A6_C_P)
               {
                  M_POSITION.C = 90.0;
               };
               if (A6_C_M)
               {
                  M_POSITION.C = (90.0 * -(1));
               };
               if (E1_P)
               {
                  M_POSITION.E1 = M_MAXDELTA;
               };
               if (E1_M)
               {
                  M_POSITION.E1 = (M_MAXDELTA * -(1));
               };
               if (E2_P)
               {
                  M_POSITION.E2 = M_MAXDELTA;
               };
               if (E2_M)
               {
                  M_POSITION.E2 = (M_MAXDELTA * -(1));
               };
               if (E3_P)
               {
                  M_POSITION.E3 = M_MAXDELTA;
               };
               if (E3_M)
               {
                  M_POSITION.E3 = (M_MAXDELTA * -(1));
               };
               if (E4_P)
               {
                  M_POSITION.E4 = M_MAXDELTA;
               };
               if (E4_M)
               {
                  M_POSITION.E4 = (M_MAXDELTA * -(1));
               };
               if (E5_P)
               {
                  M_POSITION.E5 = M_MAXDELTA;
               };
               if (E5_M)
               {
                  M_POSITION.E5 = (M_MAXDELTA * -(1));
               };
               if (E6_P)
               {
                  M_POSITION.E6 = M_MAXDELTA;
               };
               if (E6_M)
               {
                  M_POSITION.E6 = (M_MAXDELTA * -(1));
               };
            };
            break;
         };
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = (M_EXECUTECMD && (_ERRORID == static_cast<PLCIEC::DINT>(0)) && !(M_EXECUTEABORT));
      KRC_MOVE_1.MOVETYPE = M_MOVETYPE;
      KRC_MOVE_1.ACTPOSITION = M_POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = 0;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();

      //_BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      //_DONE = KRC_MOVE_1.DONE;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      // Call FB KRC_Abort_1
      KRC_ABORT_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_ABORT_1.EXECUTECMD = M_EXECUTEABORT;
      KRC_ABORT_1.OnCycle();
      if ((KRC_ABORT_1.ERROR || KRC_ABORT_1.DONE))
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(FALSE);
      };
      _ERRORID = KRC_ABORT_1.ERRORID;

      // bugfix: krc jog done signal and busy robot stopped
      if (!M_CMDINPUTACTIVELAST && M_CMDINPUTACTIVE && M_EXECUTECMD)
      {
         _BUSY = true;
      }

      if (M_CMDINPUTACTIVELAST && !M_CMDINPUTACTIVE && (_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         M_EXECUTECMD_FINISHED = true;
      }

      if (M_EXECUTECMD_FINISHED && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ROB_STOPPED)
      {
         M_EXECUTECMD_FINISHED = false;
         _BUSY = false;
      }

      if (M_EXECUTEABORT)
      {
         _ORDERID = KRC_ABORT_1.ORDERID;
      }
      else if (M_EXECUTECMD && (_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         _ORDERID = KRC_MOVE_1.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOGADVANCED
 ******************************************************************************/
class KRC_JOGADVANCED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::INT MOVETYPE;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::BOOL JOGADVANCED;
   PLCIEC::BOOL B_A1_JA_P;
   PLCIEC::BOOL B_A1_JA_M;
   PLCIEC::BOOL B_A2_JA_P;
   PLCIEC::BOOL B_A2_JA_M;
   PLCIEC::BOOL B_A3_JA_P;
   PLCIEC::BOOL B_A3_JA_M;
   PLCIEC::BOOL B_A4_JA_P;
   PLCIEC::BOOL B_A4_JA_M;
   PLCIEC::BOOL B_A5_JA_P;
   PLCIEC::BOOL B_A5_JA_M;
   PLCIEC::BOOL B_A6_JA_P;
   PLCIEC::BOOL B_A6_JA_M;
   PLCIEC::BOOL B_E1_JA_P;
   PLCIEC::BOOL B_E1_JA_M;
   PLCIEC::BOOL B_E2_JA_P;
   PLCIEC::BOOL B_E2_JA_M;
   PLCIEC::BOOL B_E3_JA_P;
   PLCIEC::BOOL B_E3_JA_M;
   PLCIEC::BOOL B_E4_JA_P;
   PLCIEC::BOOL B_E4_JA_M;
   PLCIEC::BOOL B_E5_JA_P;
   PLCIEC::BOOL B_E5_JA_M;
   PLCIEC::BOOL B_E6_JA_P;
   PLCIEC::BOOL B_E6_JA_M;
   PLCIEC::BOOL B_X_JA_P;
   PLCIEC::BOOL B_X_JA_M;
   PLCIEC::BOOL B_Y_JA_P;
   PLCIEC::BOOL B_Y_JA_M;
   PLCIEC::BOOL B_Z_JA_P;
   PLCIEC::BOOL B_Z_JA_M;
   PLCIEC::BOOL B_A_JA_P;
   PLCIEC::BOOL B_A_JA_M;
   PLCIEC::BOOL B_B_JA_P;
   PLCIEC::BOOL B_B_JA_M;
   PLCIEC::BOOL B_C_JA_P;
   PLCIEC::BOOL B_C_JA_M;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT JA_STATE_VAL;
   KRC_MOVE KRC_MOVE_1;
   KRC_ABORT KRC_ABORT_1;
   E6POS M_POSITION;
   E6AXIS M_AXISPOSITION;
   PLCIEC::INT M_MOVETYPE;
   PLCIEC::BOOL M_EXECUTEABORT;
   PLCIEC::BOOL JA_BUTTONACTIVE;
   PLCIEC::BOOL JA_BUTTONCHANGED;
   PLCIEC::BOOL JA_BUTTONLAST;
   PLCIEC::INT JA_MOVETYPEACTIVE;
   PLCIEC::INT JA_MOVETYPELAST;
   PLCIEC::BOOL JA_MOVETYPECHANGED;
   PLCIEC::BOOL JA_BASECHANGED;
   COORDSYS JA_COORDSYSACTIVE;
   COORDSYS JA_COORDSYSLAST;
   PLCIEC::BOOL JA_TOOLCHANGED;
   PLCIEC::BOOL JA_IPOCHANGED;

public:
   KRC_JOGADVANCED()
       : AXISGROUPIDX(0), MOVETYPE(0), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), JOGADVANCED(static_cast<PLCIEC::BOOL>(FALSE)), B_A1_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A1_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_A2_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A2_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_A3_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A3_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_A4_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A4_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_A5_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A5_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_A6_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A6_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_E1_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_E1_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_E2_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_E2_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_E3_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_E3_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_E4_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_E4_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_E5_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_E5_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_E6_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_E6_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_X_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_X_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_Y_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_Y_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_Z_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_Z_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_A_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_A_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_B_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_B_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), B_C_JA_P(static_cast<PLCIEC::BOOL>(FALSE)), B_C_JA_M(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), JA_STATE_VAL(0), KRC_MOVE_1(), KRC_ABORT_1(), M_POSITION(), M_AXISPOSITION(), M_MOVETYPE(0), M_EXECUTEABORT(static_cast<PLCIEC::BOOL>(FALSE)), JA_BUTTONACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), JA_BUTTONCHANGED(static_cast<PLCIEC::BOOL>(FALSE)), JA_BUTTONLAST(static_cast<PLCIEC::BOOL>(FALSE)), JA_MOVETYPEACTIVE(0), JA_MOVETYPELAST(0), JA_MOVETYPECHANGED(static_cast<PLCIEC::BOOL>(FALSE)), JA_BASECHANGED(static_cast<PLCIEC::BOOL>(FALSE)), JA_COORDSYSACTIVE(), JA_COORDSYSLAST(), JA_TOOLCHANGED(static_cast<PLCIEC::BOOL>(FALSE)), JA_IPOCHANGED(static_cast<PLCIEC::BOOL>(FALSE))
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);

      JA_BUTTONACTIVE = static_cast<PLCIEC::BOOL>(FALSE);
      _BUSY = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_ACTIVE = JOGADVANCED;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_STATE_VAL = 0;

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (((((((((((((((((((B_A1_JA_P && B_A1_JA_M) || (B_A2_JA_P && B_A2_JA_M)) || (B_A3_JA_P && B_A3_JA_M)) || (B_A4_JA_P && B_A4_JA_M)) || (B_A5_JA_P && B_A5_JA_M)) || (B_A6_JA_P && B_A6_JA_M)) || (B_E1_JA_P && B_E1_JA_M)) || (B_E2_JA_P && B_E2_JA_M)) || (B_E3_JA_P && B_E3_JA_M)) || (B_E4_JA_P && B_E4_JA_M)) || (B_E5_JA_P && B_E5_JA_M)) || (B_E6_JA_P && B_E6_JA_M)) || (B_X_JA_P && B_X_JA_M)) || (B_Y_JA_P && B_Y_JA_M)) || (B_Z_JA_P && B_Z_JA_M)) || (B_A_JA_P && B_A_JA_M)) || (B_B_JA_P && B_B_JA_M)) || (B_C_JA_P && B_C_JA_M)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(548);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      switch (MOVETYPE)
      {
      case 1:
         M_MOVETYPE = 20;
         JA_MOVETYPEACTIVE = 1;
         break;
      case 2:
         M_MOVETYPE = 21;
         JA_MOVETYPEACTIVE = 2;
         break;
      default:
         _ERRORID = static_cast<PLCIEC::DINT>(590);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      JA_MOVETYPECHANGED = (JA_MOVETYPEACTIVE != JA_MOVETYPELAST);
      if (JA_MOVETYPECHANGED)
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(TRUE);
      }

      JA_COORDSYSACTIVE.BASE = COORDINATESYSTEM.BASE;
      JA_BASECHANGED = (JA_COORDSYSLAST.BASE != JA_COORDSYSACTIVE.BASE);
      if (JA_BASECHANGED)
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(TRUE);
      }

      JA_COORDSYSACTIVE.TOOL = COORDINATESYSTEM.TOOL;
      JA_TOOLCHANGED = (JA_COORDSYSLAST.TOOL != JA_COORDSYSACTIVE.TOOL);
      if (JA_TOOLCHANGED)
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(TRUE);
      }

      JA_COORDSYSACTIVE.IPO_MODE = COORDINATESYSTEM.IPO_MODE;
      JA_IPOCHANGED = (JA_COORDSYSLAST.IPO_MODE != JA_COORDSYSACTIVE.IPO_MODE);
      if (JA_IPOCHANGED)
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(TRUE);
      }

      if (JOGADVANCED)
      {
         JA_BUTTONACTIVE = ((((((((((((((((((((((((((((((((((((B_A1_JA_P) || B_A1_JA_M) || B_A2_JA_P) || B_A2_JA_M) || B_A3_JA_P) || B_A3_JA_M) || B_A4_JA_P) || B_A4_JA_M) || B_A5_JA_P) || B_A5_JA_M) || B_A6_JA_P) || B_A6_JA_M) || B_E1_JA_P) || B_E1_JA_M) || B_E2_JA_P) || B_E2_JA_M) || B_E3_JA_P) || B_E3_JA_M) || B_E4_JA_P) || B_E4_JA_M) || B_E5_JA_P) || B_E5_JA_M) || B_E6_JA_P) || B_E6_JA_M) || B_X_JA_P) || B_X_JA_M) || B_Y_JA_P) || B_Y_JA_M) || B_Z_JA_P) || B_Z_JA_M) || B_A_JA_P) || B_A_JA_M) || B_B_JA_P) || B_B_JA_M) || B_C_JA_P) || B_C_JA_M);

         if (JA_BUTTONACTIVE)
         {
            if (B_A1_JA_P)
            {
               JA_STATE_VAL = 1;
            }; // A1 +
            if (B_A1_JA_M)
            {
               JA_STATE_VAL = 2;
            }; // A1 -
            if (B_A2_JA_P)
            {
               JA_STATE_VAL = 3;
            }; // A2 +
            if (B_A2_JA_M)
            {
               JA_STATE_VAL = 4;
            }; // A2 -
            if (B_A3_JA_P)
            {
               JA_STATE_VAL = 5;
            }; // A3 +
            if (B_A3_JA_M)
            {
               JA_STATE_VAL = 6;
            }; // A3 -
            if (B_A4_JA_P)
            {
               JA_STATE_VAL = 7;
            }; // A4 +
            if (B_A4_JA_M)
            {
               JA_STATE_VAL = 8;
            }; // A4 -
            if (B_A5_JA_P)
            {
               JA_STATE_VAL = 9;
            }; // A5 +
            if (B_A5_JA_M)
            {
               JA_STATE_VAL = 10;
            }; // A5 -
            if (B_A6_JA_P)
            {
               JA_STATE_VAL = 11;
            }; // A6 +
            if (B_A6_JA_M)
            {
               JA_STATE_VAL = 12;
            }; // A6 -
            if (B_E1_JA_P)
            {
               JA_STATE_VAL = 13;
            }; // E1 +
            if (B_E1_JA_M)
            {
               JA_STATE_VAL = 14;
            }; // E1 -
            if (B_E2_JA_P)
            {
               JA_STATE_VAL = 15;
            }; // E2 +
            if (B_E2_JA_M)
            {
               JA_STATE_VAL = 16;
            }; // E2 -
            if (B_E3_JA_P)
            {
               JA_STATE_VAL = 17;
            }; // E3 +
            if (B_E3_JA_M)
            {
               JA_STATE_VAL = 18;
            }; // E3 -
            if (B_E4_JA_P)
            {
               JA_STATE_VAL = 19;
            }; // E4 +
            if (B_E4_JA_M)
            {
               JA_STATE_VAL = 20;
            }; // E4 -
            if (B_E5_JA_P)
            {
               JA_STATE_VAL = 21;
            }; // E5 +
            if (B_E5_JA_M)
            {
               JA_STATE_VAL = 22;
            }; // E5 -
            if (B_E6_JA_P)
            {
               JA_STATE_VAL = 23;
            }; // E6 +
            if (B_E6_JA_M)
            {
               JA_STATE_VAL = 24;
            }; // E6 -
            if (B_X_JA_P)
            {
               JA_STATE_VAL = 25;
            }; // X +
            if (B_X_JA_M)
            {
               JA_STATE_VAL = 26;
            }; // X -
            if (B_Y_JA_P)
            {
               JA_STATE_VAL = 27;
            }; // Y +
            if (B_Y_JA_M)
            {
               JA_STATE_VAL = 28;
            }; // Y -
            if (B_Z_JA_P)
            {
               JA_STATE_VAL = 29;
            }; // Z +
            if (B_Z_JA_M)
            {
               JA_STATE_VAL = 30;
            }; // Z -
            if (B_A_JA_P)
            {
               JA_STATE_VAL = 31;
            }; // A +
            if (B_A_JA_M)
            {
               JA_STATE_VAL = 32;
            }; // A -
            if (B_B_JA_P)
            {
               JA_STATE_VAL = 33;
            }; // B +
            if (B_B_JA_M)
            {
               JA_STATE_VAL = 34;
            }; // B -
            if (B_C_JA_P)
            {
               JA_STATE_VAL = 35;
            }; // C +
            if (B_C_JA_M)
            {
               JA_STATE_VAL = 36;
            }; // C -
         }
         else
         {
            JA_STATE_VAL = 0; // Roboter stopped
         }

         KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_STATE_VAL = JA_STATE_VAL;
         JA_BUTTONCHANGED = (JA_BUTTONLAST != JA_BUTTONACTIVE);
         JA_BUTTONLAST = JA_BUTTONACTIVE;

         if (JA_BUTTONCHANGED && !(JA_BUTTONACTIVE))
         {
            JA_STATE_VAL = 0; // roboter stopped
            KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_STATE_VAL = JA_STATE_VAL;
         }
      }
      else
      {
         // M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(TRUE); // Jog Advanced deactive-> mxa_Abort
      }
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = (JOGADVANCED && (_ERRORID == static_cast<PLCIEC::DINT>(0)) && !(M_EXECUTEABORT));
      KRC_MOVE_1.MOVETYPE = M_MOVETYPE;
      KRC_MOVE_1.ACTPOSITION = M_POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = 0;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();

      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      // Call FB KRC_Abort_1
      KRC_ABORT_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_ABORT_1.EXECUTECMD = M_EXECUTEABORT;
      KRC_ABORT_1.OnCycle();

      if ((KRC_ABORT_1.ERROR || KRC_ABORT_1.DONE))
      {
         M_EXECUTEABORT = static_cast<PLCIEC::BOOL>(FALSE);
      };
      _ERRORID = KRC_ABORT_1.ERRORID;

      // Abort -> program jumps out of mxA_Move returns to mxA_CommandDispatcher -> Busy output reset
      if (JOGADVANCED && !KRC_MOVE_1.ABORTED)
      {
         _BUSY = static_cast<PLCIEC::BOOL>(TRUE);
      }
      else if (JOGADVANCED && KRC_MOVE_1.ABORTED)
      {
         _BUSY = static_cast<PLCIEC::BOOL>(FALSE);
      }

      if (JOGADVANCED && ((MOVETYPE == 1) || (MOVETYPE == 2)) && _BUSY)
      {
         _ACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_MOVE;
      }

      JA_MOVETYPELAST = JA_MOVETYPEACTIVE;
      JA_COORDSYSLAST.BASE = JA_COORDSYSACTIVE.BASE;
      JA_COORDSYSLAST.TOOL = JA_COORDSYSACTIVE.TOOL;
      JA_COORDSYSLAST.IPO_MODE = JA_COORDSYSACTIVE.IPO_MODE;

      if (M_EXECUTEABORT)
      {
         _ORDERID = KRC_ABORT_1.ORDERID;
      }
      else if (JOGADVANCED && (_ERRORID == static_cast<PLCIEC::DINT>(0)))
      {
         _ORDERID = KRC_MOVE_1.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOGLINEARRELATIVE
 ******************************************************************************/
class KRC_JOGLINEARRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_JOGLINEARRELATIVE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 3;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOGTOOLRELATIVE
 ******************************************************************************/
class KRC_JOGTOOLRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_JOGTOOLRELATIVE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 4;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDCONFIG
 ******************************************************************************/

class KRC_LDDCONFIG
{
   /* VAR_INPUT*/

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT LOADA3SETTINGS;
   PLCIEC::REAL M_A3;
   PLCIEC::REAL X_A3;
   PLCIEC::REAL Y_A3;
   PLCIEC::REAL Z_A3;
   PLCIEC::REAL A_A3;
   PLCIEC::REAL B_A3;
   PLCIEC::REAL C_A3;
   PLCIEC::REAL JX_A3;
   PLCIEC::REAL JY_A3;
   PLCIEC::REAL JZ_A3;
   PLCIEC::REAL MASS;

   /* VAR_OUTPUT*/

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */
private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   PLCIEC::DINT NORDERID;
   PLCIEC::REAL ERR_STATUS;
   PLCIEC::DINT NERR;
   PLCIEC::DINT NSTATE;

public:
   KRC_LDDCONFIG()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), LOADA3SETTINGS(0), M_A3(0), X_A3(0), Y_A3(0), Z_A3(0), A_A3(0), B_A3(0), C_A3(0), JX_A3(0), JY_A3(0), JZ_A3(0), MASS(0), BUSY(_BUSY), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), NORDERID(0), ERR_STATUS(0), NERR(0), NSTATE(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);

      if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }

      if (!EXECUTECMD)
      {
         NSTATE = static_cast<PLCIEC::DINT>(0);
      }

      // Execute LDD config function
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(60);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(LOADA3SETTINGS);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = M_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = X_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = Y_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = Z_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = A_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = B_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = C_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = JX_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = JY_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = JZ_A3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = MASS;
         NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      }

      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = static_cast<PLCIEC::DINT>(1);
      }

      if (NSTATE == 1)
      {
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -108: // Internal: initializing LDD failed
            _ERRORID = static_cast<PLCIEC::DINT>(550);
            break;
         case -109: // Setting manual mass failed
            _ERRORID = static_cast<PLCIEC::DINT>(551);
            break;
         case -110: // Setting start position failed
            _ERRORID = static_cast<PLCIEC::DINT>(552);
            break;
         case -111: // Setting supplementary load failed
            _ERRORID = static_cast<PLCIEC::DINT>(553);
            break;
         case -112: // Internal: setting acceleration factor LDD failed
            _ERRORID = static_cast<PLCIEC::DINT>(554);
            break;
         case -113: // Internal: finalizing configuration failed
            _ERRORID = static_cast<PLCIEC::DINT>(555);
            break;
         case -114: // Invalid supplementary load option selected (LoadA3Settings)
            _ERRORID = static_cast<PLCIEC::DINT>(556);
            break;
         default:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         }
      }

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = (MXA_EXECUTECOMMAND_1.DONE && (NSTATE == 1));
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDSTART
 ******************************************************************************/

class KRC_LDDSTART
{
   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT TOOL;

   /* VAR_OUTPUT*/

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::DINT NORDERID;
   PLCIEC::DINT NSTATE;
   PLCIEC::DINT NERR;
   PLCIEC::REAL ERR_STATUS;

public:
   KRC_LDDSTART()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TOOL(0), BUSY(_BUSY), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), NORDERID(0), NSTATE(0), NERR(0), ERR_STATUS(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);

      if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!EXECUTECMD)
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         }
      }

      if (!EXECUTECMD)
      {
         NSTATE = static_cast<PLCIEC::DINT>(0);
         NORDERID = static_cast<PLCIEC::DINT>(0);
      }

      if (EXECUTECMD && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE < 100))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(557);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
         return;
      }

      // Execute LDD start function
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && NSTATE == 0);
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(64);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 0)
      {

         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(TOOL);
         NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      }

      if (MXA_EXECUTECOMMAND_1.DONE && NSTATE == 0)
      {
         NSTATE = static_cast<PLCIEC::DINT>(1);
      }

      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = static_cast<PLCIEC::DINT>(9);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      }

      // Get return values if error happens
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)));
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(65);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();

      if (MXA_EXECUTECOMMAND_2.WRITECMDPAR && NSTATE == 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      }

      if (MXA_EXECUTECOMMAND_2.READCMDDATARET && NSTATE == 1)
      {
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = static_cast<PLCIEC::DINT>(2);
      }

      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = static_cast<PLCIEC::DINT>(9);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      }

      _BUSY = (MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY);
      _DONE = MXA_EXECUTECOMMAND_2.DONE;

      if (NSTATE == 2)
      {
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -108: // Internal: initializing LDD failed
            _ERRORID = static_cast<PLCIEC::DINT>(550);
            break;
         case -109: // Setting manual mass failed
            _ERRORID = static_cast<PLCIEC::DINT>(551);
            break;
         case -110: // Setting start position failed
            _ERRORID = static_cast<PLCIEC::DINT>(552);
            break;
         case -111: // Setting supplementary load failed
            _ERRORID = static_cast<PLCIEC::DINT>(553);
            break;
         case -112: // Internal: setting acceleration factor LDD failed
            _ERRORID = static_cast<PLCIEC::DINT>(554);
            break;
         case -113: // Internal: finalizing configuration failed
            _ERRORID = static_cast<PLCIEC::DINT>(555);
            break;
         case -100: // Internal error: Setting run mode failed
            _ERRORID = static_cast<PLCIEC::DINT>(558);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -101: // Internal error: Getting number of identification runs failed
            _ERRORID = static_cast<PLCIEC::DINT>(559);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -102: // Internal error: Getting starting position for next movement failed
            _ERRORID = static_cast<PLCIEC::DINT>(560);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -105: // Internal error: Calculation step failed
            _ERRORID = static_cast<PLCIEC::DINT>(561);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -1: // Internal error: Getting identified load failed
            _ERRORID = static_cast<PLCIEC::DINT>(562);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         default:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         }
      }

      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDTESTRUN
 ******************************************************************************/

class KRC_LDDTESTRUN
{
   /* VAR_INPUT*/

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT*/

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::DINT NSTATE;
   PLCIEC::DINT NERR;
   PLCIEC::REAL ERR_STATUS;
   PLCIEC::DINT NORDERID;

public:
   KRC_LDDTESTRUN()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), NSTATE(0), NERR(0), ERR_STATUS(0), NORDERID(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);

      if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!EXECUTECMD)
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         }
      }

      if (!EXECUTECMD)
      {
         NSTATE = static_cast<PLCIEC::DINT>(0);
         NORDERID = static_cast<PLCIEC::DINT>(0);
      }

      if (EXECUTECMD && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE > 10))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(563);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
         return;
      }

      // Execute LDD test function
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && NSTATE == 0);
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(62);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 0)
      {

         NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      }

      if (MXA_EXECUTECOMMAND_1.DONE && NSTATE == 0)
      {
         NSTATE = static_cast<PLCIEC::DINT>(1);
      }

      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = static_cast<PLCIEC::DINT>(9);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      }

      // Get return values if error happens
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)));
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(63);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();

      if (MXA_EXECUTECOMMAND_2.WRITECMDPAR && NSTATE == 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      }

      if (MXA_EXECUTECOMMAND_2.READCMDDATARET && NSTATE == 1)
      {
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = 2;
      }

      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = static_cast<PLCIEC::DINT>(9);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      }

      _BUSY = (MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY);
      _DONE = MXA_EXECUTECOMMAND_2.DONE;

      if (NSTATE == 2)
      {
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -100: // Internal error: Setting run mode failed
            _ERRORID = static_cast<PLCIEC::DINT>(558);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -101: // Internal error: Getting number of identification runs failed
            _ERRORID = static_cast<PLCIEC::DINT>(559);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -102: // Internal error: Getting starting position for next movement failed
            _ERRORID = static_cast<PLCIEC::DINT>(560);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         case -105: // Internal error: Calculation step failed
            _ERRORID = static_cast<PLCIEC::DINT>(561);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         default:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         }
      }

      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDWRITELOAD
 ******************************************************************************/

class KRC_LDDWRITELOAD
{
   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::INT TOOL;

   /* VAR_OUTPUT*/

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::DINT NORDERID;
   PLCIEC::DINT NSTATE;
   PLCIEC::DINT COPY_OF_NSTATE;
   PLCIEC::DINT NERR;
   PLCIEC::REAL ERR_STATUS;

public:
   KRC_LDDWRITELOAD()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), TOOL(0), BUSY(_BUSY), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), NORDERID(0), NSTATE(0), COPY_OF_NSTATE(0), NERR(0), ERR_STATUS(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);

      if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         if (!EXECUTECMD)
         {
            _ERRORID = static_cast<PLCIEC::DINT>(0);
         }
      }

      if (!EXECUTECMD)
      {
         NSTATE = static_cast<PLCIEC::DINT>(0);
         NORDERID = static_cast<PLCIEC::DINT>(0);
      }

      // Execute LDD write load function
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && NSTATE == 0);
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(66);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 0)
      {

         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(TOOL);
         NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      }

      if (MXA_EXECUTECOMMAND_1.DONE && NSTATE == 0)
      {
         NSTATE = static_cast<PLCIEC::DINT>(1);
      }

      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = static_cast<PLCIEC::DINT>(9);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      }

      // Get return values if error happens
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)));
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(67);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();

      if (MXA_EXECUTECOMMAND_2.WRITECMDPAR && NSTATE == 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
      }

      if (MXA_EXECUTECOMMAND_2.READCMDDATARET && NSTATE == 1)
      {
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = static_cast<PLCIEC::DINT>(2);
      }

      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = static_cast<PLCIEC::DINT>(9);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      }

      _BUSY = (MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY);
      _DONE = MXA_EXECUTECOMMAND_2.DONE;

      if (NSTATE == 2)
      {
         NERR = PLCIEC::REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
         case -1:
            // Internal error: Getting identified load failed
            _ERRORID = static_cast<PLCIEC::DINT>(562);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            break;
         default:
            _ERRORID = static_cast<PLCIEC::DINT>(0);
            break;
         }
      }

      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MASREF
 ******************************************************************************/
class KRC_MASREF
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS ACTPOSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::BOOL &MASREFREQUEST;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::BOOL _MASREFREQUEST;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_MASREF()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), ACTPOSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), BUFFERMODE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), MASREFREQUEST(_MASREFREQUEST), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _MASREFREQUEST(static_cast<PLCIEC::BOOL>(FALSE)), _ORDERID(0), KRC_MOVE_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _MASREFREQUEST = static_cast<PLCIEC::BOOL>(FALSE);
         return;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(30);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 1;
      KRC_MOVE_1.ACTPOSITION = ACTPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _MASREFREQUEST = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.MASTERINGTEST_REQ_INT;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVEAXISABSOLUTE
 ******************************************************************************/
class KRC_MOVEAXISABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6AXIS AXISPOSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6POS M_POSITION;
   PLCIEC::INT M_ORITYPE;
   COORDSYS M_COORDINATESYSTEM;

public:
   KRC_MOVEAXISABSOLUTE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), AXISPOSITION(), VELOCITY(0), ACCELERATION(0), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_CIRCHP(), M_POSITION(), M_ORITYPE(0), M_COORDINATESYSTEM()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 10;
      }
      else
      {
         SWITCHMOVETYPE = 0;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.AXISPOSITION = AXISPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.ORITYPE = M_ORITYPE;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVECIRCABSOLUTE
 ******************************************************************************/
class KRC_MOVECIRCABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   E6POS CIRCHP;
   PLCIEC::REAL ANGLE;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   PLCIEC::INT CIRCTYPE;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVECIRCABSOLUTE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), CIRCHP(), ANGLE(0), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), CIRCTYPE(0), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_COORDINATESYSTEM(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 17;
      }
      else
      {
         SWITCHMOVETYPE = 7;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.CIRCHP = CIRCHP;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.CIRCTYPE = CIRCTYPE;
      KRC_MOVE_1.CIRCANGLE = ANGLE;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVECIRCRELATIVE
 ******************************************************************************/
class KRC_MOVECIRCRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   E6POS CIRCHP;
   PLCIEC::REAL ANGLE;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   PLCIEC::INT CIRCTYPE;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVECIRCRELATIVE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), CIRCHP(), ANGLE(0), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), CIRCTYPE(0), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_COORDINATESYSTEM(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 18;
      }
      else
      {
         SWITCHMOVETYPE = 8;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.CIRCHP = CIRCHP;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.CIRCTYPE = CIRCTYPE;
      KRC_MOVE_1.CIRCANGLE = ANGLE;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVEDIRECTABSOLUTE
 ******************************************************************************/
class KRC_MOVEDIRECTABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   PLCIEC::INT M_ORITYPE;

public:
   KRC_MOVEDIRECTABSOLUTE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_CIRCHP(), M_AXISPOSITION(), M_ORITYPE(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 11;
      }
      else
      {
         SWITCHMOVETYPE = 1;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.CIRCHP = M_CIRCHP;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = M_ORITYPE;
      KRC_MOVE_1.CIRCTYPE = 0;
      KRC_MOVE_1.CIRCANGLE = 0;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVEDIRECTRELATIVE
 ******************************************************************************/
class KRC_MOVEDIRECTRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS ACTPOSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   PLCIEC::INT M_ORITYPE;

public:
   KRC_MOVEDIRECTRELATIVE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), ACTPOSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_CIRCHP(), M_AXISPOSITION(), M_ORITYPE(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 16;
      }
      else
      {
         SWITCHMOVETYPE = 6;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.ACTPOSITION = ACTPOSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.CIRCHP = M_CIRCHP;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = M_ORITYPE;
      KRC_MOVE_1.CIRCTYPE = 0;
      KRC_MOVE_1.CIRCANGLE = 0;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVELINEARABSOLUTE
 ******************************************************************************/
class KRC_MOVELINEARABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;
   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVELINEARABSOLUTE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_CIRCHP(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 12;
      }
      else
      {
         SWITCHMOVETYPE = 2;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.CIRCHP = M_CIRCHP;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.CIRCTYPE = 0;
      KRC_MOVE_1.CIRCANGLE = 0;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVELINEARRELATIVE
 ******************************************************************************/
class KRC_MOVELINEARRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   E6POS POSITION;
   PLCIEC::INT VELOCITY;
   PLCIEC::INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   APO APPROXIMATE;
   PLCIEC::INT BUFFERMODE;
   PLCIEC::BOOL SPLINEMODE;

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

   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   PLCIEC::INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVELINEARRELATIVE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), POSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), APPROXIMATE(), BUFFERMODE(0), SPLINEMODE(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), KRC_MOVE_1(), SWITCHMOVETYPE(0), M_CIRCHP(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      if (SPLINEMODE)
      {
         SWITCHMOVETYPE = 15;
      }
      else
      {
         SWITCHMOVETYPE = 5;
      };

      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.CIRCHP = M_CIRCHP;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.CIRCTYPE = 0;
      KRC_MOVE_1.CIRCANGLE = 0;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = KRC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALACCELERATION
 ******************************************************************************/
class KRC_READACTUALACCELERATION
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::REAL &ACC_ABS;
   const PLCIEC::REAL &X;
   const PLCIEC::REAL &Y;
   const PLCIEC::REAL &Z;
   const PLCIEC::REAL &A;
   const PLCIEC::REAL &B;
   const PLCIEC::REAL &C;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::REAL _ACC_ABS;
   PLCIEC::REAL _X;
   PLCIEC::REAL _Y;
   PLCIEC::REAL _Z;
   PLCIEC::REAL _A;
   PLCIEC::REAL _B;
   PLCIEC::REAL _C;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READACTUALACCELERATION()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ACC_ABS(_ACC_ABS), X(_X), Y(_Y), Z(_Z), A(_A), B(_B), C(_C), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ACC_ABS(0), _X(0), _Y(0), _Z(0), _A(0), _B(0), _C(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(26);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _ACC_ABS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALAXISPOSITION
 ******************************************************************************/
class KRC_READACTUALAXISPOSITION
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const E6AXIS &AXISPOSITION;
   const PLCIEC::REAL &A1;
   const PLCIEC::REAL &A2;
   const PLCIEC::REAL &A3;
   const PLCIEC::REAL &A4;
   const PLCIEC::REAL &A5;
   const PLCIEC::REAL &A6;
   const PLCIEC::REAL &E1;
   const PLCIEC::REAL &E2;
   const PLCIEC::REAL &E3;
   const PLCIEC::REAL &E4;
   const PLCIEC::REAL &E5;
   const PLCIEC::REAL &E6;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   E6AXIS _AXISPOSITION;
   PLCIEC::REAL _A1;
   PLCIEC::REAL _A2;
   PLCIEC::REAL _A3;
   PLCIEC::REAL _A4;
   PLCIEC::REAL _A5;
   PLCIEC::REAL _A6;
   PLCIEC::REAL _E1;
   PLCIEC::REAL _E2;
   PLCIEC::REAL _E3;
   PLCIEC::REAL _E4;
   PLCIEC::REAL _E5;
   PLCIEC::REAL _E6;

public:
   KRC_READACTUALAXISPOSITION()
       : AXISGROUPIDX(0), VALID(_VALID), AXISPOSITION(_AXISPOSITION), A1(_A1), A2(_A2), A3(_A3), A4(_A4), A5(_A5), A6(_A6), E1(_E1), E2(_E2), E3(_E3), E4(_E4), E5(_E5), E6(_E6), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _AXISPOSITION(), _A1(0), _A2(0), _A3(0), _A4(0), _A5(0), _A6(0), _E1(0), _E2(0), _E3(0), _E4(0), _E5(0), _E6(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = static_cast<PLCIEC::BOOL>(FALSE);
         return;
      };
      _AXISPOSITION = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT;
      _A1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A1;
      _A2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A2;
      _A3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A3;
      _A4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A4;
      _A5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A5;
      _A6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.A6;
      _E1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E1;
      _E2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E2;
      _E3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E3;
      _E4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E4;
      _E5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E5;
      _E6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT.E6;
      _VALID = ((KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACTVALID && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALAXISVELOCITY
 ******************************************************************************/
class KRC_READACTUALAXISVELOCITY
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::INT &A1;
   const PLCIEC::INT &A2;
   const PLCIEC::INT &A3;
   const PLCIEC::INT &A4;
   const PLCIEC::INT &A5;
   const PLCIEC::INT &A6;
   const PLCIEC::INT &E1;
   const PLCIEC::INT &E2;
   const PLCIEC::INT &E3;
   const PLCIEC::INT &E4;
   const PLCIEC::INT &E5;
   const PLCIEC::INT &E6;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::INT _A1;
   PLCIEC::INT _A2;
   PLCIEC::INT _A3;
   PLCIEC::INT _A4;
   PLCIEC::INT _A5;
   PLCIEC::INT _A6;
   PLCIEC::INT _E1;
   PLCIEC::INT _E2;
   PLCIEC::INT _E3;
   PLCIEC::INT _E4;
   PLCIEC::INT _E5;
   PLCIEC::INT _E6;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READACTUALAXISVELOCITY()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), A1(_A1), A2(_A2), A3(_A3), A4(_A4), A5(_A5), A6(_A6), E1(_E1), E2(_E2), E3(_E3), E4(_E4), E5(_E5), E6(_E6), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _A1(0), _A2(0), _A3(0), _A4(0), _A5(0), _A6(0), _E1(0), _E2(0), _E3(0), _E4(0), _E5(0), _E6(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(25);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _A1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _A2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _A3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _A4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _A5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _A6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _E1 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _E2 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _E3 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _E4 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _E5 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
         _E6 = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALPOSITION
 ******************************************************************************/
class KRC_READACTUALPOSITION
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const E6POS &POSITION;
   const PLCIEC::REAL &X;
   const PLCIEC::REAL &Y;
   const PLCIEC::REAL &Z;
   const PLCIEC::REAL &A;
   const PLCIEC::REAL &B;
   const PLCIEC::REAL &C;
   const PLCIEC::INT &STATUS;
   const PLCIEC::INT &TURN;
   const PLCIEC::INT &TOOL;
   const PLCIEC::INT &BASE;
   const PLCIEC::INT &IPOMODE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   E6POS _ACTPOSITION;
   PLCIEC::REAL _X;
   PLCIEC::REAL _Y;
   PLCIEC::REAL _Z;
   PLCIEC::REAL _A;
   PLCIEC::REAL _B;
   PLCIEC::REAL _C;
   PLCIEC::INT _STATUS;
   PLCIEC::INT _TURN;
   PLCIEC::INT _TOOL;
   PLCIEC::INT _BASE;
   PLCIEC::INT _IPOMODE;

public:
   KRC_READACTUALPOSITION()
       : AXISGROUPIDX(0), VALID(_VALID), POSITION(_ACTPOSITION), X(_X), Y(_Y), Z(_Z), A(_A), B(_B), C(_C), STATUS(_STATUS), TURN(_TURN), TOOL(_TOOL), BASE(_BASE), IPOMODE(_IPOMODE), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _ACTPOSITION(), _X(0), _Y(0), _Z(0), _A(0), _B(0), _C(0), _STATUS(0), _TURN(0), _TOOL(0), _BASE(0), _IPOMODE(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = static_cast<PLCIEC::BOOL>(FALSE);
         return;
      };
      _ACTPOSITION = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT;
      _X = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.X;
      _Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.Y;
      _Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.Z;
      _A = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.A;
      _B = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.B;
      _C = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.C;
      _STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.STATUS;
      _TURN = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.TURN;
      _TOOL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOOLACT;
      _BASE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.BASEACT;
      _IPOMODE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IPOMODEACT;
      _VALID = ((KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACTVALID && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALVELOCITY
 ******************************************************************************/
class KRC_READACTUALVELOCITY
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::REAL &VALUE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::REAL _VALUE;

public:
   KRC_READACTUALVELOCITY()
       : AXISGROUPIDX(0), VALID(_VALID), VALUE(_VALUE), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = static_cast<PLCIEC::BOOL>(FALSE);
         return;
      };
      _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.VELACT;
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READANALOGINPUT
 ******************************************************************************/
class KRC_READANALOGINPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::REAL &VALUE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::REAL _VALUE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READANALOGINPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), DONE(_DONE), VALUE(_VALUE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(11);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READANALOGOUTPUT
 ******************************************************************************/
class KRC_READANALOGOUTPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::REAL &VALUE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::REAL _VALUE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READANALOGOUTPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), DONE(_DONE), VALUE(_VALUE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(12);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
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
       : KRC4_INPUT(), AXISGROUPIDX(0), HEARTBEAT(1000), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), M_AE_RC_RDY1(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_ALARM_STOP(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_USER_SAF(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_PERI_RDY(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_ROB_CAL(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_IO_ACTCONF(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_STOPMESS(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_PGNO_FBIT_REFL(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_INT_ESTOP(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_PRO_ACT(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_PGNO_REQ(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_APPL_RUN(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_PRO_MOVE(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_IN_HOME(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_ON_PATH(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_NEAR_POSRET(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_ROB_STOPPED(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_T1(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_T2(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_AUT(static_cast<PLCIEC::BOOL>(FALSE)), M_AE_EXT(static_cast<PLCIEC::BOOL>(FALSE)), M_BRAKETEST_MONTIME(static_cast<PLCIEC::BOOL>(FALSE)), M_BRAKETEST_REQ_INT(static_cast<PLCIEC::BOOL>(FALSE)), M_BRAKETEST_WORK(static_cast<PLCIEC::BOOL>(FALSE)), M_BRAKES_OK(static_cast<PLCIEC::BOOL>(FALSE)), M_BRAKETEST_WARN(static_cast<PLCIEC::BOOL>(FALSE)), M_ABORTACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), M_BRAKEACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), M_KCP_CONNECT(static_cast<PLCIEC::BOOL>(FALSE)), M_TOUCHUP(static_cast<PLCIEC::BOOL>(FALSE)), M_MASTEST_REQ_INT(static_cast<PLCIEC::BOOL>(FALSE)), M_MASTESTSWITCH_OK(static_cast<PLCIEC::BOOL>(FALSE)), M_POS_ACT_VALID(static_cast<PLCIEC::BOOL>(FALSE)), M_HEARTBEATSUBMIT(0), M_IN_VAL_1TO8(0), M_TOUCHUP_POSNO(0), M_SR_ORDER1_ID(0), M_SR_ORDER2_ID(0), M_SR_ORDER3_ID(0), M_SR_ORDER4_ID(0), M_SR_ORDER5_ID(0), M_SR_ORDER6_ID(0), M_SR_ORDER7_ID(0), M_SR_ORDER8_ID(0), M_SR_ORDER9_ID(0), M_SR_ORDER10_ID(0), M_SR_ORDER1_STATE(0), M_SR_ORDER2_STATE(0), M_SR_ORDER3_STATE(0), M_SR_ORDER4_STATE(0), M_SR_ORDER5_STATE(0), M_SR_ORDER6_STATE(0), M_SR_ORDER7_STATE(0), M_SR_ORDER8_STATE(0), M_SR_ORDER9_STATE(0), M_SR_ORDER10_STATE(0), M_HEARTBEATPCOS(0), M_OVERRIDE(0), M_POSACT_X(0), M_POSACT_Y(0), M_POSACT_Z(0), M_POSACT_A(0), M_POSACT_B(0), M_POSACT_C(0), M_POSACT_STATUS(0), M_POSACT_TURN(0), M_TOOLACT(0), M_BASEACT(0), M_IPOMODE(0), M_AXISACT_A1(0), M_AXISACT_A2(0), M_AXISACT_A3(0), M_AXISACT_A4(0), M_AXISACT_A5(0), M_AXISACT_A6(0), M_AXISACT_A7(0), M_AXISACT_A8(0), M_AXISACT_A9(0), M_AXISACT_A10(0), M_AXISACT_A11(0), M_AXISACT_A12(0), M_VELACT(0), M_WORKSTATES(0), M_AXWORKSTATES(0), M_GROUPSTATE(0), M_ERRORID(0), M_ERRORIDSUB(0), M_ACTIVEPOSORDERID(0), M_ACTIVEORDERIDB(0), M_QUEUECOUNT(0), M_IR_STATUS1(0), M_IR_STATUS2(0), M_IR_STATUS3(0), M_IR_STATUS4(0), M_IR_STATUS5(0), M_IR_STATUS6(0), M_IR_STATUS7(0), M_IR_STATUS8(0), M_ERRORIDPCOS(0), M_FREE_FOR_WOV(0), M_TRANSMISSIONNORET(0), M_ORDERIDRET(0), M_CMDIDRET(0), M_CMDDATARETCS(0), M_RESERVE190(0), M_CMDDATARET1(0), M_CMDDATARET2(0), M_CMDDATARET3(0), M_CMDDATARET4(0), M_CMDDATARET5(0), M_CMDDATARET6(0), M_CMDDATARET7(0), M_CMDDATARET8(0), M_CMDDATARET9(0), M_CMDDATARET10(0), M_CMDDATARET11(0), M_CMDDATARET12(0), M_RESERVE242(0), NCHECKSUM(0), FTMP(0), NTMP1(0), FTMP1(0), BTMP1(static_cast<PLCIEC::BOOL>(FALSE)), I(0), ONF_TRIG(static_cast<PLCIEC::BOOL>(FALSE)), ENABLETONSUBMIT(static_cast<PLCIEC::BOOL>(FALSE)), ENABLETONPCOS(static_cast<PLCIEC::BOOL>(FALSE)), M_INITOK(static_cast<PLCIEC::BOOL>(FALSE)), M_HEARTBEATLAST(0), M_HEARTBEATLASTPCOS(0), HEARTBEATTO(PLCIEC::MKTIME(1, 0, 0)), TON_1_PCOS(), TON_1_SUBMIT(), TON_2(), M_LASTORDERID(0), R_TRIG_1(), M_CONNECTIONOK(static_cast<PLCIEC::BOOL>(FALSE)), M_F_TRIG(static_cast<PLCIEC::BOOL>(FALSE)), M_FIRSTCYCLES(0), RETB(static_cast<PLCIEC::BOOL>(FALSE)), MXA_RESETCOMMAND_1()
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (!(M_INITOK))
      {
         M_INITOK = static_cast<PLCIEC::BOOL>(TRUE);
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT)
         {
            _ERRORID = static_cast<PLCIEC::DINT>(505);
            _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT = static_cast<PLCIEC::BOOL>(TRUE);
         };
      };
      if ((M_FIRSTCYCLES < 100))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = static_cast<PLCIEC::BOOL>(FALSE);
         M_HEARTBEATLAST = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT = static_cast<PLCIEC::BOOL>(TRUE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKEF = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKE = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RELEASEBRAKE = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.BRAKETEST_REQ_EXT = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MASTERINGTEST_REQ_EXT = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.WRITE_OUT_1TO8 = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE = static_cast<PLCIEC::BOOL>(TRUE);
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO <= static_cast<PLCIEC::DINT>(0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO = HEARTBEAT;
      };
      HEARTBEATTO = PLCIEC::DINT_TO_TIME(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
      ENABLETONSUBMIT = ((M_HEARTBEATLAST == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT > 0));
      ENABLETONPCOS = ((M_HEARTBEATLASTPCOS == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS > 0));
      if ((((M_HEARTBEATLAST != KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT > 0)) && ((M_HEARTBEATLASTPCOS != KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS > 0))))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = static_cast<PLCIEC::BOOL>(TRUE);
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = static_cast<PLCIEC::BOOL>(FALSE);
      };
      ONF_TRIG = (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && M_F_TRIG);
      M_F_TRIG = KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE;
      if (ONF_TRIG)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = static_cast<PLCIEC::DINT>(510);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = static_cast<PLCIEC::BOOL>(FALSE);
      };
      // Call FB TON_2
      TON_2.IN = (((KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > static_cast<PLCIEC::DINT>(0))) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == M_LASTORDERID)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET));
      TON_2.PT = PLCIEC::DINT_TO_TIME((KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO * static_cast<PLCIEC::DINT>(1)));
      TON_2.OnCycle();
      M_LASTORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      // Call FB R_TRIG_1
      R_TRIG_1.CLK = TON_2.Q;
      R_TRIG_1.OnCycle();
      if (R_TRIG_1.Q)
      {
         _ERRORID = static_cast<PLCIEC::DINT>(511);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
      };
      if ((TON_2.Q && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == static_cast<PLCIEC::DINT>(0))))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      M_AE_RC_RDY1 = PLCIEC::IsBitSet(KRC4_INPUT[0], 0);
      M_AE_ALARM_STOP = PLCIEC::IsBitSet(KRC4_INPUT[0], 1);
      M_AE_USER_SAF = PLCIEC::IsBitSet(KRC4_INPUT[0], 2);
      M_AE_PERI_RDY = PLCIEC::IsBitSet(KRC4_INPUT[0], 3);
      M_AE_ROB_CAL = PLCIEC::IsBitSet(KRC4_INPUT[0], 4);
      M_AE_IO_ACTCONF = PLCIEC::IsBitSet(KRC4_INPUT[0], 5);
      M_AE_STOPMESS = PLCIEC::IsBitSet(KRC4_INPUT[0], 6);
      M_AE_PGNO_FBIT_REFL = PLCIEC::IsBitSet(KRC4_INPUT[0], 7);
      M_AE_INT_ESTOP = PLCIEC::IsBitSet(KRC4_INPUT[1], 0);
      M_AE_PRO_ACT = PLCIEC::IsBitSet(KRC4_INPUT[1], 1);
      M_AE_PGNO_REQ = PLCIEC::IsBitSet(KRC4_INPUT[1], 2);
      M_AE_APPL_RUN = PLCIEC::IsBitSet(KRC4_INPUT[1], 3);
      M_AE_PRO_MOVE = PLCIEC::IsBitSet(KRC4_INPUT[1], 4);
      M_AE_IN_HOME = PLCIEC::IsBitSet(KRC4_INPUT[1], 5);
      M_AE_ON_PATH = PLCIEC::IsBitSet(KRC4_INPUT[1], 6);
      M_AE_NEAR_POSRET = PLCIEC::IsBitSet(KRC4_INPUT[1], 7);
      M_AE_ROB_STOPPED = PLCIEC::IsBitSet(KRC4_INPUT[2], 0);
      M_AE_T1 = PLCIEC::IsBitSet(KRC4_INPUT[2], 1);
      M_AE_T2 = PLCIEC::IsBitSet(KRC4_INPUT[2], 2);
      M_AE_AUT = PLCIEC::IsBitSet(KRC4_INPUT[2], 3);
      M_AE_EXT = PLCIEC::IsBitSet(KRC4_INPUT[2], 4);
      M_BRAKETEST_MONTIME = PLCIEC::IsBitSet(KRC4_INPUT[2], 5);
      M_BRAKETEST_REQ_INT = PLCIEC::IsBitSet(KRC4_INPUT[2], 6);
      M_BRAKETEST_WORK = PLCIEC::IsBitSet(KRC4_INPUT[2], 7);
      M_BRAKES_OK = PLCIEC::IsBitSet(KRC4_INPUT[3], 0);
      M_BRAKETEST_WARN = PLCIEC::IsBitSet(KRC4_INPUT[3], 1);
      M_ABORTACTIVE = PLCIEC::IsBitSet(KRC4_INPUT[3], 2);
      M_BRAKEACTIVE = PLCIEC::IsBitSet(KRC4_INPUT[3], 3);
      M_KCP_CONNECT = PLCIEC::IsBitSet(KRC4_INPUT[3], 4);
      M_TOUCHUP = PLCIEC::IsBitSet(KRC4_INPUT[3], 5);
      M_MASTEST_REQ_INT = PLCIEC::IsBitSet(KRC4_INPUT[3], 6);
      M_MASTESTSWITCH_OK = PLCIEC::IsBitSet(KRC4_INPUT[3], 7);
      M_POS_ACT_VALID = PLCIEC::IsBitSet(KRC4_INPUT[58], 0);
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
         NCHECKSUM = static_cast<PLCIEC::DWORD>(0);
         for (I = 1; I <= 12; I += 1)
         {
            FTMP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[I];
            NTMP1 = PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((FTMP - 0.5f) * 10.0f));
            FTMP1 = static_cast<PLCIEC::REAL>(NTMP1 / 10) + 0.5f;
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
            if (((FTMP > 2147483500.0f) || (FTMP < -(2147483500.0f))))
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
 * FUNCTION_BLOCK KRC_READAXWORKSPACE
 ******************************************************************************/
class KRC_READAXWORKSPACE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT WORKSPACENO;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::INT &WORKSPACEMODE;
   const AXBOX &WORKSPACEDATA;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::INT _WORKSPACEMODE;
   AXBOX _WORKSPACEDATA;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   PLCIEC::INT M_WORKSPACEMODE;
   AXBOX M_WORKSPACEDATA;

public:
   KRC_READAXWORKSPACE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), WORKSPACENO(0), DONE(_DONE), WORKSPACEMODE(_WORKSPACEMODE), WORKSPACEDATA(_WORKSPACEDATA), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSPACEMODE(0), _WORKSPACEDATA(), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), NSTATE(0), MXA_EXECUTECOMMAND_0(), MXA_EXECUTECOMMAND_1(), MXA_EXECUTECOMMAND_2(), M_WORKSPACEMODE(0), M_WORKSPACEDATA()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         M_WORKSPACEMODE = 0;
         M_WORKSPACEDATA.A1_N = 0.0;
         M_WORKSPACEDATA.A2_N = 0.0;
         M_WORKSPACEDATA.A3_N = 0.0;
         M_WORKSPACEDATA.A4_N = 0.0;
         M_WORKSPACEDATA.A5_N = 0.0;
         M_WORKSPACEDATA.A6_N = 0.0;
         M_WORKSPACEDATA.A1_P = 0.0;
         M_WORKSPACEDATA.A2_P = 0.0;
         M_WORKSPACEDATA.A3_P = 0.0;
         M_WORKSPACEDATA.A4_P = 0.0;
         M_WORKSPACEDATA.A5_P = 0.0;
         M_WORKSPACEDATA.A6_P = 0.0;
         M_WORKSPACEDATA.E1_N = 0.0;
         M_WORKSPACEDATA.E2_N = 0.0;
         M_WORKSPACEDATA.E3_N = 0.0;
         M_WORKSPACEDATA.E4_N = 0.0;
         M_WORKSPACEDATA.E5_N = 0.0;
         M_WORKSPACEDATA.E6_N = 0.0;
         M_WORKSPACEDATA.E1_P = 0.0;
         M_WORKSPACEDATA.E2_P = 0.0;
         M_WORKSPACEDATA.E3_P = 0.0;
         M_WORKSPACEDATA.E4_P = 0.0;
         M_WORKSPACEDATA.E5_P = 0.0;
         M_WORKSPACEDATA.E6_P = 0.0;
         _WORKSPACEDATA = M_WORKSPACEDATA;
      };
      // Call FB mxA_ExecuteCommand_0
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = (EXECUTECMD && (NSTATE == 0));
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(51);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = static_cast<PLCIEC::DINT>(1);
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_WORKSPACEMODE = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(51);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = static_cast<PLCIEC::DINT>(2);
      };
      if ((MXA_EXECUTECOMMAND_1.READCMDDATARET && (NSTATE == 1)))
      {
         M_WORKSPACEDATA.A1_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_WORKSPACEDATA.A2_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_WORKSPACEDATA.A3_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_WORKSPACEDATA.A4_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_WORKSPACEDATA.A5_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_WORKSPACEDATA.A6_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_WORKSPACEDATA.A1_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         M_WORKSPACEDATA.A2_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         M_WORKSPACEDATA.A3_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         M_WORKSPACEDATA.A4_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         M_WORKSPACEDATA.A5_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         M_WORKSPACEDATA.A6_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && (NSTATE == 2));
      MXA_EXECUTECOMMAND_2.CMDID = static_cast<PLCIEC::DINT>(51);
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_2.OnCycle();
      if ((MXA_EXECUTECOMMAND_2.WRITECMDPAR && (NSTATE == 2)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = static_cast<PLCIEC::DINT>(3);
      };
      if ((MXA_EXECUTECOMMAND_2.READCMDDATARET && (NSTATE == 2)))
      {
         M_WORKSPACEDATA.E1_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_WORKSPACEDATA.E2_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_WORKSPACEDATA.E3_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_WORKSPACEDATA.E4_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_WORKSPACEDATA.E5_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_WORKSPACEDATA.E6_N = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_WORKSPACEDATA.E1_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         M_WORKSPACEDATA.E2_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         M_WORKSPACEDATA.E3_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         M_WORKSPACEDATA.E4_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         M_WORKSPACEDATA.E5_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         M_WORKSPACEDATA.E6_P = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
         NSTATE = 3;
      };
      if (MXA_EXECUTECOMMAND_2.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
      _DONE = (NSTATE == 3);
      if ((NSTATE == 3))
      {
         _WORKSPACEMODE = M_WORKSPACEMODE;
         _WORKSPACEDATA = M_WORKSPACEDATA;
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
         _ERRORID = static_cast<PLCIEC::DINT>(0);
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
      }
      else if (EXECUTECMD && (NSTATE == 1))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
      else if (EXECUTECMD && (NSTATE == 2))
      {
         _ORDERID = MXA_EXECUTECOMMAND_2.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READBASEDATA
 ******************************************************************************/
class KRC_READBASEDATA
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BASENO;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const FRAME &BASEDATA;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   FRAME _BASEDATA;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READBASEDATA()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BASENO(0), DONE(_DONE), BASEDATA(_BASEDATA), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _BASEDATA(), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(22);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(BASENO);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _BASEDATA.X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _BASEDATA.Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _BASEDATA.Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _BASEDATA.A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _BASEDATA.B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _BASEDATA.C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALINPUT
 ******************************************************************************/
class KRC_READDIGITALINPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &VALUE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _VALUE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READDIGITALINPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), DONE(_DONE), VALUE(_VALUE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(8);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALINPUT1TO8
 ******************************************************************************/
class KRC_READDIGITALINPUT1TO8
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::BOOL &IN1;
   const PLCIEC::BOOL &IN2;
   const PLCIEC::BOOL &IN3;
   const PLCIEC::BOOL &IN4;
   const PLCIEC::BOOL &IN5;
   const PLCIEC::BOOL &IN6;
   const PLCIEC::BOOL &IN7;
   const PLCIEC::BOOL &IN8;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::BOOL _IN1;
   PLCIEC::BOOL _IN2;
   PLCIEC::BOOL _IN3;
   PLCIEC::BOOL _IN4;
   PLCIEC::BOOL _IN5;
   PLCIEC::BOOL _IN6;
   PLCIEC::BOOL _IN7;
   PLCIEC::BOOL _IN8;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READDIGITALINPUT1TO8()
       : AXISGROUPIDX(0), VALID(_VALID), IN1(_IN1), IN2(_IN2), IN3(_IN3), IN4(_IN4), IN5(_IN5), IN6(_IN6), IN7(_IN7), IN8(_IN8), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _IN1(static_cast<PLCIEC::BOOL>(FALSE)), _IN2(static_cast<PLCIEC::BOOL>(FALSE)), _IN3(static_cast<PLCIEC::BOOL>(FALSE)), _IN4(static_cast<PLCIEC::BOOL>(FALSE)), _IN5(static_cast<PLCIEC::BOOL>(FALSE)), _IN6(static_cast<PLCIEC::BOOL>(FALSE)), _IN7(static_cast<PLCIEC::BOOL>(FALSE)), _IN8(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED);
      _IN1 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 0);
      _IN2 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 1);
      _IN3 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 2);
      _IN4 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 3);
      _IN5 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 4);
      _IN6 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 5);
      _IN7 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 6);
      _IN8 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 7);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALINPUTARRAY
 ******************************************************************************/
class KRC_READDIGITALINPUTARRAY
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT STARTNUMBER;
   PLCIEC::INT LENGTH;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL *VALUES;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _VALUES[201];
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::DWORD DW1;
   PLCIEC::DWORD DW2;
   PLCIEC::DWORD DW3;
   PLCIEC::DWORD DW4;
   PLCIEC::DWORD DW5;
   PLCIEC::DWORD DW6;
   PLCIEC::DWORD DW7;
   PLCIEC::DWORD DW8;
   PLCIEC::DWORD DW9;
   PLCIEC::DWORD DW10;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READDIGITALINPUTARRAY()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), STARTNUMBER(0), LENGTH(0), DONE(_DONE), VALUES(_VALUES), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _VALUES(), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), DW1(0), DW2(0), DW3(0), DW4(0), DW5(0), DW6(0), DW7(0), DW8(0), DW9(0), DW10(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(38);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(STARTNUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(LENGTH);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         DW1 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         DW2 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         DW3 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         DW4 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         DW5 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         DW6 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         DW7 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         DW8 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         DW9 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         DW10 = PLCIEC::REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _VALUES[1] = PLCIEC::IsBitSet(DW1, 0);
         _VALUES[2] = PLCIEC::IsBitSet(DW1, 1);
         _VALUES[3] = PLCIEC::IsBitSet(DW1, 2);
         _VALUES[4] = PLCIEC::IsBitSet(DW1, 3);
         _VALUES[5] = PLCIEC::IsBitSet(DW1, 4);
         _VALUES[6] = PLCIEC::IsBitSet(DW1, 5);
         _VALUES[7] = PLCIEC::IsBitSet(DW1, 6);
         _VALUES[8] = PLCIEC::IsBitSet(DW1, 7);
         _VALUES[9] = PLCIEC::IsBitSet(DW1, 8);
         _VALUES[10] = PLCIEC::IsBitSet(DW1, 9);
         _VALUES[11] = PLCIEC::IsBitSet(DW1, 10);
         _VALUES[12] = PLCIEC::IsBitSet(DW1, 11);
         _VALUES[13] = PLCIEC::IsBitSet(DW1, 12);
         _VALUES[14] = PLCIEC::IsBitSet(DW1, 13);
         _VALUES[15] = PLCIEC::IsBitSet(DW1, 14);
         _VALUES[16] = PLCIEC::IsBitSet(DW1, 15);
         _VALUES[17] = PLCIEC::IsBitSet(DW1, 16);
         _VALUES[18] = PLCIEC::IsBitSet(DW1, 17);
         _VALUES[19] = PLCIEC::IsBitSet(DW1, 18);
         _VALUES[20] = PLCIEC::IsBitSet(DW1, 19);
         _VALUES[21] = PLCIEC::IsBitSet(DW2, 0);
         _VALUES[22] = PLCIEC::IsBitSet(DW2, 1);
         _VALUES[23] = PLCIEC::IsBitSet(DW2, 2);
         _VALUES[24] = PLCIEC::IsBitSet(DW2, 3);
         _VALUES[25] = PLCIEC::IsBitSet(DW2, 4);
         _VALUES[26] = PLCIEC::IsBitSet(DW2, 5);
         _VALUES[27] = PLCIEC::IsBitSet(DW2, 6);
         _VALUES[28] = PLCIEC::IsBitSet(DW2, 7);
         _VALUES[29] = PLCIEC::IsBitSet(DW2, 8);
         _VALUES[30] = PLCIEC::IsBitSet(DW2, 9);
         _VALUES[31] = PLCIEC::IsBitSet(DW2, 10);
         _VALUES[32] = PLCIEC::IsBitSet(DW2, 11);
         _VALUES[33] = PLCIEC::IsBitSet(DW2, 12);
         _VALUES[34] = PLCIEC::IsBitSet(DW2, 13);
         _VALUES[35] = PLCIEC::IsBitSet(DW2, 14);
         _VALUES[36] = PLCIEC::IsBitSet(DW2, 15);
         _VALUES[37] = PLCIEC::IsBitSet(DW2, 16);
         _VALUES[38] = PLCIEC::IsBitSet(DW2, 17);
         _VALUES[39] = PLCIEC::IsBitSet(DW2, 18);
         _VALUES[40] = PLCIEC::IsBitSet(DW2, 19);
         _VALUES[41] = PLCIEC::IsBitSet(DW3, 0);
         _VALUES[42] = PLCIEC::IsBitSet(DW3, 1);
         _VALUES[43] = PLCIEC::IsBitSet(DW3, 2);
         _VALUES[44] = PLCIEC::IsBitSet(DW3, 3);
         _VALUES[45] = PLCIEC::IsBitSet(DW3, 4);
         _VALUES[46] = PLCIEC::IsBitSet(DW3, 5);
         _VALUES[47] = PLCIEC::IsBitSet(DW3, 6);
         _VALUES[48] = PLCIEC::IsBitSet(DW3, 7);
         _VALUES[49] = PLCIEC::IsBitSet(DW3, 8);
         _VALUES[50] = PLCIEC::IsBitSet(DW3, 9);
         _VALUES[51] = PLCIEC::IsBitSet(DW3, 10);
         _VALUES[52] = PLCIEC::IsBitSet(DW3, 11);
         _VALUES[53] = PLCIEC::IsBitSet(DW3, 12);
         _VALUES[54] = PLCIEC::IsBitSet(DW3, 13);
         _VALUES[55] = PLCIEC::IsBitSet(DW3, 14);
         _VALUES[56] = PLCIEC::IsBitSet(DW3, 15);
         _VALUES[57] = PLCIEC::IsBitSet(DW3, 16);
         _VALUES[58] = PLCIEC::IsBitSet(DW3, 17);
         _VALUES[59] = PLCIEC::IsBitSet(DW3, 18);
         _VALUES[60] = PLCIEC::IsBitSet(DW3, 19);
         _VALUES[61] = PLCIEC::IsBitSet(DW4, 0);
         _VALUES[62] = PLCIEC::IsBitSet(DW4, 1);
         _VALUES[63] = PLCIEC::IsBitSet(DW4, 2);
         _VALUES[64] = PLCIEC::IsBitSet(DW4, 3);
         _VALUES[65] = PLCIEC::IsBitSet(DW4, 4);
         _VALUES[66] = PLCIEC::IsBitSet(DW4, 5);
         _VALUES[67] = PLCIEC::IsBitSet(DW4, 6);
         _VALUES[68] = PLCIEC::IsBitSet(DW4, 7);
         _VALUES[69] = PLCIEC::IsBitSet(DW4, 8);
         _VALUES[70] = PLCIEC::IsBitSet(DW4, 9);
         _VALUES[71] = PLCIEC::IsBitSet(DW4, 10);
         _VALUES[72] = PLCIEC::IsBitSet(DW4, 11);
         _VALUES[73] = PLCIEC::IsBitSet(DW4, 12);
         _VALUES[74] = PLCIEC::IsBitSet(DW4, 13);
         _VALUES[75] = PLCIEC::IsBitSet(DW4, 14);
         _VALUES[76] = PLCIEC::IsBitSet(DW4, 15);
         _VALUES[77] = PLCIEC::IsBitSet(DW4, 16);
         _VALUES[78] = PLCIEC::IsBitSet(DW4, 17);
         _VALUES[79] = PLCIEC::IsBitSet(DW4, 18);
         _VALUES[80] = PLCIEC::IsBitSet(DW4, 19);
         _VALUES[81] = PLCIEC::IsBitSet(DW5, 0);
         _VALUES[82] = PLCIEC::IsBitSet(DW5, 1);
         _VALUES[83] = PLCIEC::IsBitSet(DW5, 2);
         _VALUES[84] = PLCIEC::IsBitSet(DW5, 3);
         _VALUES[85] = PLCIEC::IsBitSet(DW5, 4);
         _VALUES[86] = PLCIEC::IsBitSet(DW5, 5);
         _VALUES[87] = PLCIEC::IsBitSet(DW5, 6);
         _VALUES[88] = PLCIEC::IsBitSet(DW5, 7);
         _VALUES[89] = PLCIEC::IsBitSet(DW5, 8);
         _VALUES[90] = PLCIEC::IsBitSet(DW5, 9);
         _VALUES[91] = PLCIEC::IsBitSet(DW5, 10);
         _VALUES[92] = PLCIEC::IsBitSet(DW5, 11);
         _VALUES[93] = PLCIEC::IsBitSet(DW5, 12);
         _VALUES[94] = PLCIEC::IsBitSet(DW5, 13);
         _VALUES[95] = PLCIEC::IsBitSet(DW5, 14);
         _VALUES[96] = PLCIEC::IsBitSet(DW5, 15);
         _VALUES[97] = PLCIEC::IsBitSet(DW5, 16);
         _VALUES[98] = PLCIEC::IsBitSet(DW5, 17);
         _VALUES[99] = PLCIEC::IsBitSet(DW5, 18);
         _VALUES[100] = PLCIEC::IsBitSet(DW5, 19);
         _VALUES[101] = PLCIEC::IsBitSet(DW6, 0);
         _VALUES[102] = PLCIEC::IsBitSet(DW6, 1);
         _VALUES[103] = PLCIEC::IsBitSet(DW6, 2);
         _VALUES[104] = PLCIEC::IsBitSet(DW6, 3);
         _VALUES[105] = PLCIEC::IsBitSet(DW6, 4);
         _VALUES[106] = PLCIEC::IsBitSet(DW6, 5);
         _VALUES[107] = PLCIEC::IsBitSet(DW6, 6);
         _VALUES[108] = PLCIEC::IsBitSet(DW6, 7);
         _VALUES[109] = PLCIEC::IsBitSet(DW6, 8);
         _VALUES[110] = PLCIEC::IsBitSet(DW6, 9);
         _VALUES[111] = PLCIEC::IsBitSet(DW6, 10);
         _VALUES[112] = PLCIEC::IsBitSet(DW6, 11);
         _VALUES[113] = PLCIEC::IsBitSet(DW6, 12);
         _VALUES[114] = PLCIEC::IsBitSet(DW6, 13);
         _VALUES[115] = PLCIEC::IsBitSet(DW6, 14);
         _VALUES[116] = PLCIEC::IsBitSet(DW6, 15);
         _VALUES[117] = PLCIEC::IsBitSet(DW6, 16);
         _VALUES[118] = PLCIEC::IsBitSet(DW6, 17);
         _VALUES[119] = PLCIEC::IsBitSet(DW6, 18);
         _VALUES[120] = PLCIEC::IsBitSet(DW6, 19);
         _VALUES[121] = PLCIEC::IsBitSet(DW7, 0);
         _VALUES[122] = PLCIEC::IsBitSet(DW7, 1);
         _VALUES[123] = PLCIEC::IsBitSet(DW7, 2);
         _VALUES[124] = PLCIEC::IsBitSet(DW7, 3);
         _VALUES[125] = PLCIEC::IsBitSet(DW7, 4);
         _VALUES[126] = PLCIEC::IsBitSet(DW7, 5);
         _VALUES[127] = PLCIEC::IsBitSet(DW7, 6);
         _VALUES[128] = PLCIEC::IsBitSet(DW7, 7);
         _VALUES[129] = PLCIEC::IsBitSet(DW7, 8);
         _VALUES[130] = PLCIEC::IsBitSet(DW7, 9);
         _VALUES[131] = PLCIEC::IsBitSet(DW7, 10);
         _VALUES[132] = PLCIEC::IsBitSet(DW7, 11);
         _VALUES[133] = PLCIEC::IsBitSet(DW7, 12);
         _VALUES[134] = PLCIEC::IsBitSet(DW7, 13);
         _VALUES[135] = PLCIEC::IsBitSet(DW7, 14);
         _VALUES[136] = PLCIEC::IsBitSet(DW7, 15);
         _VALUES[137] = PLCIEC::IsBitSet(DW7, 16);
         _VALUES[138] = PLCIEC::IsBitSet(DW7, 17);
         _VALUES[139] = PLCIEC::IsBitSet(DW7, 18);
         _VALUES[140] = PLCIEC::IsBitSet(DW7, 19);
         _VALUES[141] = PLCIEC::IsBitSet(DW8, 0);
         _VALUES[142] = PLCIEC::IsBitSet(DW8, 1);
         _VALUES[143] = PLCIEC::IsBitSet(DW8, 2);
         _VALUES[144] = PLCIEC::IsBitSet(DW8, 3);
         _VALUES[145] = PLCIEC::IsBitSet(DW8, 4);
         _VALUES[146] = PLCIEC::IsBitSet(DW8, 5);
         _VALUES[147] = PLCIEC::IsBitSet(DW8, 6);
         _VALUES[148] = PLCIEC::IsBitSet(DW8, 7);
         _VALUES[149] = PLCIEC::IsBitSet(DW8, 8);
         _VALUES[150] = PLCIEC::IsBitSet(DW8, 9);
         _VALUES[151] = PLCIEC::IsBitSet(DW8, 10);
         _VALUES[152] = PLCIEC::IsBitSet(DW8, 11);
         _VALUES[153] = PLCIEC::IsBitSet(DW8, 12);
         _VALUES[154] = PLCIEC::IsBitSet(DW8, 13);
         _VALUES[155] = PLCIEC::IsBitSet(DW8, 14);
         _VALUES[156] = PLCIEC::IsBitSet(DW8, 15);
         _VALUES[157] = PLCIEC::IsBitSet(DW8, 16);
         _VALUES[158] = PLCIEC::IsBitSet(DW8, 17);
         _VALUES[159] = PLCIEC::IsBitSet(DW8, 18);
         _VALUES[160] = PLCIEC::IsBitSet(DW8, 19);
         _VALUES[161] = PLCIEC::IsBitSet(DW9, 0);
         _VALUES[162] = PLCIEC::IsBitSet(DW9, 1);
         _VALUES[163] = PLCIEC::IsBitSet(DW9, 2);
         _VALUES[164] = PLCIEC::IsBitSet(DW9, 3);
         _VALUES[165] = PLCIEC::IsBitSet(DW9, 4);
         _VALUES[166] = PLCIEC::IsBitSet(DW9, 5);
         _VALUES[167] = PLCIEC::IsBitSet(DW9, 6);
         _VALUES[168] = PLCIEC::IsBitSet(DW9, 7);
         _VALUES[169] = PLCIEC::IsBitSet(DW9, 8);
         _VALUES[170] = PLCIEC::IsBitSet(DW9, 9);
         _VALUES[171] = PLCIEC::IsBitSet(DW9, 10);
         _VALUES[172] = PLCIEC::IsBitSet(DW9, 11);
         _VALUES[173] = PLCIEC::IsBitSet(DW9, 12);
         _VALUES[174] = PLCIEC::IsBitSet(DW9, 13);
         _VALUES[175] = PLCIEC::IsBitSet(DW9, 14);
         _VALUES[176] = PLCIEC::IsBitSet(DW9, 15);
         _VALUES[177] = PLCIEC::IsBitSet(DW9, 16);
         _VALUES[178] = PLCIEC::IsBitSet(DW9, 17);
         _VALUES[179] = PLCIEC::IsBitSet(DW9, 18);
         _VALUES[180] = PLCIEC::IsBitSet(DW9, 19);
         _VALUES[181] = PLCIEC::IsBitSet(DW10, 0);
         _VALUES[182] = PLCIEC::IsBitSet(DW10, 1);
         _VALUES[183] = PLCIEC::IsBitSet(DW10, 2);
         _VALUES[184] = PLCIEC::IsBitSet(DW10, 3);
         _VALUES[185] = PLCIEC::IsBitSet(DW10, 4);
         _VALUES[186] = PLCIEC::IsBitSet(DW10, 5);
         _VALUES[187] = PLCIEC::IsBitSet(DW10, 6);
         _VALUES[188] = PLCIEC::IsBitSet(DW10, 7);
         _VALUES[189] = PLCIEC::IsBitSet(DW10, 8);
         _VALUES[190] = PLCIEC::IsBitSet(DW10, 9);
         _VALUES[191] = PLCIEC::IsBitSet(DW10, 10);
         _VALUES[192] = PLCIEC::IsBitSet(DW10, 11);
         _VALUES[193] = PLCIEC::IsBitSet(DW10, 12);
         _VALUES[194] = PLCIEC::IsBitSet(DW10, 13);
         _VALUES[195] = PLCIEC::IsBitSet(DW10, 14);
         _VALUES[196] = PLCIEC::IsBitSet(DW10, 15);
         _VALUES[197] = PLCIEC::IsBitSet(DW10, 16);
         _VALUES[198] = PLCIEC::IsBitSet(DW10, 17);
         _VALUES[199] = PLCIEC::IsBitSet(DW10, 18);
         _VALUES[200] = PLCIEC::IsBitSet(DW10, 19);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALOUTPUT
 ******************************************************************************/
class KRC_READDIGITALOUTPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &VALUE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _VALUE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READDIGITALOUTPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), DONE(_DONE), VALUE(_VALUE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(9);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = PLCIEC::REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READINTERRUPTSTATE
 ******************************************************************************/
class KRC_READINTERRUPTSTATE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::INT INTERRUPT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::INT &VALUE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::INT _VALUE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READINTERRUPTSTATE()
       : AXISGROUPIDX(0), INTERRUPT(0), VALID(_VALID), VALUE(_VALUE), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (((INTERRUPT >= 1) && (INTERRUPT <= 8)))
      {
         _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[INTERRUPT];
         _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      }
      else
      {
         _VALUE = 0;
         _VALID = static_cast<PLCIEC::BOOL>(FALSE);
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READKRCERROR
 ******************************************************************************/
class KRC_READKRCERROR
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT OFFSET;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::BOOL &STOPMESS;
   const PLCIEC::INT &MESSAGECOUNT;
   const PLCIEC::DINT &MESSAGE1;
   const PLCIEC::DINT &MESSAGE2;
   const PLCIEC::DINT &MESSAGE3;
   const PLCIEC::DINT &MESSAGE4;
   const PLCIEC::DINT &MESSAGE5;
   const PLCIEC::DINT &MESSAGE6;
   const PLCIEC::DINT &MESSAGE7;
   const PLCIEC::DINT &MESSAGE8;
   const PLCIEC::DINT &MESSAGE9;
   const PLCIEC::DINT &MESSAGE10;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::BOOL _STOPMESS;
   PLCIEC::INT _MESSAGECOUNT;
   PLCIEC::DINT _MESSAGE1;
   PLCIEC::DINT _MESSAGE2;
   PLCIEC::DINT _MESSAGE3;
   PLCIEC::DINT _MESSAGE4;
   PLCIEC::DINT _MESSAGE5;
   PLCIEC::DINT _MESSAGE6;
   PLCIEC::DINT _MESSAGE7;
   PLCIEC::DINT _MESSAGE8;
   PLCIEC::DINT _MESSAGE9;
   PLCIEC::DINT _MESSAGE10;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READKRCERROR()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), OFFSET(0), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), STOPMESS(_STOPMESS), MESSAGECOUNT(_MESSAGECOUNT), MESSAGE1(_MESSAGE1), MESSAGE2(_MESSAGE2), MESSAGE3(_MESSAGE3), MESSAGE4(_MESSAGE4), MESSAGE5(_MESSAGE5), MESSAGE6(_MESSAGE6), MESSAGE7(_MESSAGE7), MESSAGE8(_MESSAGE8), MESSAGE9(_MESSAGE9), MESSAGE10(_MESSAGE10), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _STOPMESS(static_cast<PLCIEC::BOOL>(FALSE)), _MESSAGECOUNT(0), _MESSAGE1(0), _MESSAGE2(0), _MESSAGE3(0), _MESSAGE4(0), _MESSAGE5(0), _MESSAGE6(0), _MESSAGE7(0), _MESSAGE8(0), _MESSAGE9(0), _MESSAGE10(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(24);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(OFFSET);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _MESSAGECOUNT = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _MESSAGE1 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _MESSAGE2 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _MESSAGE3 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _MESSAGE4 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _MESSAGE5 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _MESSAGE6 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _MESSAGE7 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _MESSAGE8 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _MESSAGE9 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _MESSAGE10 = PLCIEC::REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _STOPMESS = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READLOADDATA
 ******************************************************************************/
class KRC_READLOADDATA
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT TOOL;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::REAL &M;
   const PLCIEC::REAL &X;
   const PLCIEC::REAL &Y;
   const PLCIEC::REAL &Z;
   const PLCIEC::REAL &A;
   const PLCIEC::REAL &B;
   const PLCIEC::REAL &C;
   const PLCIEC::REAL &JX;
   const PLCIEC::REAL &JY;
   const PLCIEC::REAL &JZ;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::REAL _M;
   PLCIEC::REAL _X;
   PLCIEC::REAL _Y;
   PLCIEC::REAL _Z;
   PLCIEC::REAL _A;
   PLCIEC::REAL _B;
   PLCIEC::REAL _C;
   PLCIEC::REAL _JX;
   PLCIEC::REAL _JY;
   PLCIEC::REAL _JZ;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READLOADDATA()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TOOL(0), DONE(_DONE), M(_M), X(_X), Y(_Y), Z(_Z), A(_A), B(_B), C(_C), JX(_JX), JY(_JY), JZ(_JZ), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _M(0), _X(0), _Y(0), _Z(0), _A(0), _B(0), _C(0), _JX(0), _JY(0), _JZ(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(14);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(TOOL);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _M = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         _JX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         _JY = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         _JZ = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
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
       : AXISGROUPIDX(0), STATUS(_STATUS), ERROR(_ERROR), ERRORID(_ERRORID), _STATUS(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
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
 * FUNCTION_BLOCK KRC_READSAFEOPSTATUS
 ******************************************************************************/
class KRC_READSAFEOPSTATUS
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL MASTERINGTEST_REQ_EXT;
   PLCIEC::BOOL BRAKETEST_REQ_EXT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::BOOL &BRAKETEST_REQ_INT;
   const PLCIEC::BOOL &MASTERINGTEST_REQ_INT;
   const PLCIEC::BOOL &BRAKETEST_MONTIME;
   const PLCIEC::BOOL &BRAKETEST_WORK;
   const PLCIEC::BOOL &BRAKES_OK;
   const PLCIEC::BOOL &BRAKETEST_WARN;
   const PLCIEC::BOOL &MASTERINGTESTSWITCH_OK;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::BOOL _BRAKETEST_REQ_INT;
   PLCIEC::BOOL _MASTERINGTEST_REQ_INT;
   PLCIEC::BOOL _BRAKETEST_MONTIME;
   PLCIEC::BOOL _BRAKETEST_WORK;
   PLCIEC::BOOL _BRAKES_OK;
   PLCIEC::BOOL _BRAKETEST_WARN;
   PLCIEC::BOOL _MASTERINGTESTSWITCH_OK;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READSAFEOPSTATUS()
       : AXISGROUPIDX(0), MASTERINGTEST_REQ_EXT(static_cast<PLCIEC::BOOL>(FALSE)), BRAKETEST_REQ_EXT(static_cast<PLCIEC::BOOL>(FALSE)), VALID(_VALID), BRAKETEST_REQ_INT(_BRAKETEST_REQ_INT), MASTERINGTEST_REQ_INT(_MASTERINGTEST_REQ_INT), BRAKETEST_MONTIME(_BRAKETEST_MONTIME), BRAKETEST_WORK(_BRAKETEST_WORK), BRAKES_OK(_BRAKES_OK), BRAKETEST_WARN(_BRAKETEST_WARN), MASTERINGTESTSWITCH_OK(_MASTERINGTESTSWITCH_OK), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _BRAKETEST_REQ_INT(static_cast<PLCIEC::BOOL>(FALSE)), _MASTERINGTEST_REQ_INT(static_cast<PLCIEC::BOOL>(FALSE)), _BRAKETEST_MONTIME(static_cast<PLCIEC::BOOL>(FALSE)), _BRAKETEST_WORK(static_cast<PLCIEC::BOOL>(FALSE)), _BRAKES_OK(static_cast<PLCIEC::BOOL>(FALSE)), _BRAKETEST_WARN(static_cast<PLCIEC::BOOL>(FALSE)), _MASTERINGTESTSWITCH_OK(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (MASTERINGTEST_REQ_EXT)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MASTERINGTEST_REQ_EXT = MASTERINGTEST_REQ_EXT;
      };
      if (BRAKETEST_REQ_EXT)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.BRAKETEST_REQ_EXT = BRAKETEST_REQ_EXT;
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      _BRAKES_OK = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKES_OK;
      _BRAKETEST_MONTIME = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_MONTIME;
      _BRAKETEST_REQ_INT = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_REQ_INT;
      _BRAKETEST_WARN = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_WARN;
      _BRAKETEST_WORK = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_WORK;
      _MASTERINGTEST_REQ_INT = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.MASTERINGTEST_REQ_INT;
      _MASTERINGTESTSWITCH_OK = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.MASTERINGTESTSWITCH_OK;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READSOFTEND
 ******************************************************************************/
class KRC_READSOFTEND
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::REAL &A1_MIN;
   const PLCIEC::REAL &A1_MAX;
   const PLCIEC::REAL &A2_MIN;
   const PLCIEC::REAL &A2_MAX;
   const PLCIEC::REAL &A3_MIN;
   const PLCIEC::REAL &A3_MAX;
   const PLCIEC::REAL &A4_MIN;
   const PLCIEC::REAL &A4_MAX;
   const PLCIEC::REAL &A5_MIN;
   const PLCIEC::REAL &A5_MAX;
   const PLCIEC::REAL &A6_MIN;
   const PLCIEC::REAL &A6_MAX;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::REAL _A1_MIN;
   PLCIEC::REAL _A1_MAX;
   PLCIEC::REAL _A2_MIN;
   PLCIEC::REAL _A2_MAX;
   PLCIEC::REAL _A3_MIN;
   PLCIEC::REAL _A3_MAX;
   PLCIEC::REAL _A4_MIN;
   PLCIEC::REAL _A4_MAX;
   PLCIEC::REAL _A5_MIN;
   PLCIEC::REAL _A5_MAX;
   PLCIEC::REAL _A6_MIN;
   PLCIEC::REAL _A6_MAX;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READSOFTEND()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DONE(_DONE), A1_MIN(_A1_MIN), A1_MAX(_A1_MAX), A2_MIN(_A2_MIN), A2_MAX(_A2_MAX), A3_MIN(_A3_MIN), A3_MAX(_A3_MAX), A4_MIN(_A4_MIN), A4_MAX(_A4_MAX), A5_MIN(_A5_MIN), A5_MAX(_A5_MAX), A6_MIN(_A6_MIN), A6_MAX(_A6_MAX), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _A1_MIN(0), _A1_MAX(0), _A2_MIN(0), _A2_MAX(0), _A3_MIN(0), _A3_MAX(0), _A4_MIN(0), _A4_MAX(0), _A5_MIN(0), _A5_MAX(0), _A6_MIN(0), _A6_MAX(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(16);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _A1_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _A1_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _A2_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _A2_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _A3_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _A3_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _A4_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         _A4_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         _A5_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         _A5_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         _A6_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         _A6_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READSOFTENDEXT
 ******************************************************************************/
class KRC_READSOFTENDEXT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::REAL &E1_MIN;
   const PLCIEC::REAL &E1_MAX;
   const PLCIEC::REAL &E2_MIN;
   const PLCIEC::REAL &E2_MAX;
   const PLCIEC::REAL &E3_MIN;
   const PLCIEC::REAL &E3_MAX;
   const PLCIEC::REAL &E4_MIN;
   const PLCIEC::REAL &E4_MAX;
   const PLCIEC::REAL &E5_MIN;
   const PLCIEC::REAL &E5_MAX;
   const PLCIEC::REAL &E6_MIN;
   const PLCIEC::REAL &E6_MAX;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::REAL _E1_MIN;
   PLCIEC::REAL _E1_MAX;
   PLCIEC::REAL _E2_MIN;
   PLCIEC::REAL _E2_MAX;
   PLCIEC::REAL _E3_MIN;
   PLCIEC::REAL _E3_MAX;
   PLCIEC::REAL _E4_MIN;
   PLCIEC::REAL _E4_MAX;
   PLCIEC::REAL _E5_MIN;
   PLCIEC::REAL _E5_MAX;
   PLCIEC::REAL _E6_MIN;
   PLCIEC::REAL _E6_MAX;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READSOFTENDEXT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DONE(_DONE), E1_MIN(_E1_MIN), E1_MAX(_E1_MAX), E2_MIN(_E2_MIN), E2_MAX(_E2_MAX), E3_MIN(_E3_MIN), E3_MAX(_E3_MAX), E4_MIN(_E4_MIN), E4_MAX(_E4_MAX), E5_MIN(_E5_MIN), E5_MAX(_E5_MAX), E6_MIN(_E6_MIN), E6_MAX(_E6_MAX), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _E1_MIN(0), _E1_MAX(0), _E2_MIN(0), _E2_MAX(0), _E3_MIN(0), _E3_MAX(0), _E4_MIN(0), _E4_MAX(0), _E5_MIN(0), _E5_MAX(0), _E6_MIN(0), _E6_MAX(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(18);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _E1_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _E1_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _E2_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _E2_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _E3_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _E3_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _E4_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         _E4_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         _E5_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         _E5_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         _E6_MIN = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         _E6_MAX = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READSYSVAR
 ******************************************************************************/
class KRC_READSYSVAR
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT INDEX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::REAL &VALUE1;
   const PLCIEC::REAL &VALUE2;
   const PLCIEC::REAL &VALUE3;
   const PLCIEC::REAL &VALUE4;
   const PLCIEC::REAL &VALUE5;
   const PLCIEC::REAL &VALUE6;
   const PLCIEC::REAL &VALUE7;
   const PLCIEC::REAL &VALUE8;
   const PLCIEC::REAL &VALUE9;
   const PLCIEC::REAL &VALUE10;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::REAL _VALUE1;
   PLCIEC::REAL _VALUE2;
   PLCIEC::REAL _VALUE3;
   PLCIEC::REAL _VALUE4;
   PLCIEC::REAL _VALUE5;
   PLCIEC::REAL _VALUE6;
   PLCIEC::REAL _VALUE7;
   PLCIEC::REAL _VALUE8;
   PLCIEC::REAL _VALUE9;
   PLCIEC::REAL _VALUE10;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READSYSVAR()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), INDEX(0), DONE(_DONE), VALUE1(_VALUE1), VALUE2(_VALUE2), VALUE3(_VALUE3), VALUE4(_VALUE4), VALUE5(_VALUE5), VALUE6(_VALUE6), VALUE7(_VALUE7), VALUE8(_VALUE8), VALUE9(_VALUE9), VALUE10(_VALUE10), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _VALUE1(0), _VALUE2(0), _VALUE3(0), _VALUE4(0), _VALUE5(0), _VALUE6(0), _VALUE7(0), _VALUE8(0), _VALUE9(0), _VALUE10(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(27);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(INDEX);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _VALUE2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _VALUE3 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _VALUE4 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _VALUE5 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _VALUE6 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _VALUE7 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         _VALUE8 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         _VALUE9 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         _VALUE10 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READTOOLDATA
 ******************************************************************************/
class KRC_READTOOLDATA
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT TOOLNO;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const FRAME &TOOLDATA;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   FRAME _TOOLDATA;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READTOOLDATA()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TOOLNO(0), DONE(_DONE), TOOLDATA(_TOOLDATA), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _TOOLDATA(), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(20);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(TOOLNO);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _TOOLDATA.X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         _TOOLDATA.Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         _TOOLDATA.Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         _TOOLDATA.A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         _TOOLDATA.B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         _TOOLDATA.C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READTOUCHUPSTATE
 ******************************************************************************/
class KRC_READTOUCHUPSTATE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::BOOL &TOUCHUP;
   const PLCIEC::INT &INDEX;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::BOOL _TOUCHUP;
   PLCIEC::INT _INDEX;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READTOUCHUPSTATE()
       : AXISGROUPIDX(0), VALID(_VALID), TOUCHUP(_TOUCHUP), INDEX(_INDEX), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _TOUCHUP(static_cast<PLCIEC::BOOL>(FALSE)), _INDEX(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      if (_VALID)
      {
         _TOUCHUP = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOUCHUP;
         _INDEX = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOUCHUP_INDEX;
      }
      else
      {
         _TOUCHUP = static_cast<PLCIEC::BOOL>(FALSE);
         _INDEX = 0;
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READWORKSPACE
 ******************************************************************************/
class KRC_READWORKSPACE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT WORKSPACENO;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::INT &WORKSPACEMODE;
   const BOX &WORKSPACEDATA;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::INT _WORKSPACEMODE;
   BOX _WORKSPACEDATA;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   PLCIEC::INT M_WORKSPACEMODE;
   BOX M_WORKSPACEDATA;

public:
   KRC_READWORKSPACE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), WORKSPACENO(0), DONE(_DONE), WORKSPACEMODE(_WORKSPACEMODE), WORKSPACEDATA(_WORKSPACEDATA), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSPACEMODE(0), _WORKSPACEDATA(), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), NSTATE(0), MXA_EXECUTECOMMAND_0(), MXA_EXECUTECOMMAND_1(), M_WORKSPACEMODE(0), M_WORKSPACEDATA()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         M_WORKSPACEMODE = 0;
         M_WORKSPACEDATA.X = 0.0;
         M_WORKSPACEDATA.Y = 0.0;
         M_WORKSPACEDATA.Z = 0.0;
         M_WORKSPACEDATA.A = 0.0;
         M_WORKSPACEDATA.B = 0.0;
         M_WORKSPACEDATA.C = 0.0;
         M_WORKSPACEDATA.X1 = 0.0;
         M_WORKSPACEDATA.X2 = 0.0;
         M_WORKSPACEDATA.Y1 = 0.0;
         M_WORKSPACEDATA.Y2 = 0.0;
         M_WORKSPACEDATA.Z1 = 0.0;
         M_WORKSPACEDATA.Z2 = 0.0;
         _WORKSPACEMODE = M_WORKSPACEMODE;
         _WORKSPACEDATA = M_WORKSPACEDATA;
      };
      // Call FB mxA_ExecuteCommand_0
      MXA_EXECUTECOMMAND_0.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_0.EXECUTE = (EXECUTECMD && (NSTATE == 0));
      MXA_EXECUTECOMMAND_0.CMDID = static_cast<PLCIEC::DINT>(49);
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = static_cast<PLCIEC::DINT>(1);
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_WORKSPACEMODE = PLCIEC::REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(49);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = static_cast<PLCIEC::DINT>(2);
      };
      if ((MXA_EXECUTECOMMAND_1.READCMDDATARET && (NSTATE == 1)))
      {
         M_WORKSPACEDATA.X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_WORKSPACEDATA.Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_WORKSPACEDATA.Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_WORKSPACEDATA.A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_WORKSPACEDATA.B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_WORKSPACEDATA.C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_WORKSPACEDATA.X1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7];
         M_WORKSPACEDATA.X2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8];
         M_WORKSPACEDATA.Y1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         M_WORKSPACEDATA.Y2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10];
         M_WORKSPACEDATA.Z1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11];
         M_WORKSPACEDATA.Z2 = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12];
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      _DONE = (NSTATE == 2);
      if ((NSTATE == 2))
      {
         _WORKSPACEMODE = M_WORKSPACEMODE;
         _WORKSPACEDATA = M_WORKSPACEDATA;
         _ERROR = 0;
         _ERRORID = static_cast<PLCIEC::DINT>(0);
      };
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));

      if (EXECUTECMD && (NSTATE == 0))
      {
         _ORDERID = MXA_EXECUTECOMMAND_0.ORDERID;
      }
      else if (EXECUTECMD && (NSTATE == 1))
      {
         _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
      }
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READWORKSTATES
 ******************************************************************************/
class KRC_READWORKSTATES
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &VALID;
   const PLCIEC::BOOL &WORKSTATE1;
   const PLCIEC::BOOL &WORKSTATE2;
   const PLCIEC::BOOL &WORKSTATE3;
   const PLCIEC::BOOL &WORKSTATE4;
   const PLCIEC::BOOL &WORKSTATE5;
   const PLCIEC::BOOL &WORKSTATE6;
   const PLCIEC::BOOL &WORKSTATE7;
   const PLCIEC::BOOL &WORKSTATE8;
   const PLCIEC::BOOL &AXWORKSTATE1;
   const PLCIEC::BOOL &AXWORKSTATE2;
   const PLCIEC::BOOL &AXWORKSTATE3;
   const PLCIEC::BOOL &AXWORKSTATE4;
   const PLCIEC::BOOL &AXWORKSTATE5;
   const PLCIEC::BOOL &AXWORKSTATE6;
   const PLCIEC::BOOL &AXWORKSTATE7;
   const PLCIEC::BOOL &AXWORKSTATE8;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _VALID;
   PLCIEC::BOOL _WORKSTATE1;
   PLCIEC::BOOL _WORKSTATE2;
   PLCIEC::BOOL _WORKSTATE3;
   PLCIEC::BOOL _WORKSTATE4;
   PLCIEC::BOOL _WORKSTATE5;
   PLCIEC::BOOL _WORKSTATE6;
   PLCIEC::BOOL _WORKSTATE7;
   PLCIEC::BOOL _WORKSTATE8;
   PLCIEC::BOOL _AXWORKSTATE1;
   PLCIEC::BOOL _AXWORKSTATE2;
   PLCIEC::BOOL _AXWORKSTATE3;
   PLCIEC::BOOL _AXWORKSTATE4;
   PLCIEC::BOOL _AXWORKSTATE5;
   PLCIEC::BOOL _AXWORKSTATE6;
   PLCIEC::BOOL _AXWORKSTATE7;
   PLCIEC::BOOL _AXWORKSTATE8;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_READWORKSTATES()
       : AXISGROUPIDX(0), VALID(_VALID), WORKSTATE1(_WORKSTATE1), WORKSTATE2(_WORKSTATE2), WORKSTATE3(_WORKSTATE3), WORKSTATE4(_WORKSTATE4), WORKSTATE5(_WORKSTATE5), WORKSTATE6(_WORKSTATE6), WORKSTATE7(_WORKSTATE7), WORKSTATE8(_WORKSTATE8), AXWORKSTATE1(_AXWORKSTATE1), AXWORKSTATE2(_AXWORKSTATE2), AXWORKSTATE3(_AXWORKSTATE3), AXWORKSTATE4(_AXWORKSTATE4), AXWORKSTATE5(_AXWORKSTATE5), AXWORKSTATE6(_AXWORKSTATE6), AXWORKSTATE7(_AXWORKSTATE7), AXWORKSTATE8(_AXWORKSTATE8), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE1(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE2(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE3(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE4(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE5(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE6(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE7(static_cast<PLCIEC::BOOL>(FALSE)), _WORKSTATE8(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE1(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE2(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE3(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE4(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE5(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE6(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE7(static_cast<PLCIEC::BOOL>(FALSE)), _AXWORKSTATE8(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED);
      _WORKSTATE1 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 0);
      _WORKSTATE2 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 1);
      _WORKSTATE3 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 2);
      _WORKSTATE4 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 3);
      _WORKSTATE5 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 4);
      _WORKSTATE6 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 5);
      _WORKSTATE7 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 6);
      _WORKSTATE8 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 7);
      _AXWORKSTATE1 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 0);
      _AXWORKSTATE2 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 1);
      _AXWORKSTATE3 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 2);
      _AXWORKSTATE4 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 3);
      _AXWORKSTATE5 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 4);
      _AXWORKSTATE6 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 5);
      _AXWORKSTATE7 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 6);
      _AXWORKSTATE8 = PLCIEC::IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 7);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETADVANCE
 ******************************************************************************/
class KRC_SETADVANCE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT COUNT;
   PLCIEC::INT MAXWAITTIME;
   PLCIEC::INT MODE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETADVANCE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), COUNT(0), MAXWAITTIME(0), MODE(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(36);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(COUNT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(MAXWAITTIME);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(MODE);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETCOORDSYS
 ******************************************************************************/
class KRC_SETCOORDSYS
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETCOORDSYS()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), COORDINATESYSTEM(), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(33);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETDATETIME
 ******************************************************************************/
class KRC_SETDATETIME
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT YEAR;
   PLCIEC::INT MONTH;
   PLCIEC::INT DAY;
   PLCIEC::INT HOUR;
   PLCIEC::INT MINUTE;
   PLCIEC::INT SECOND;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETDATETIME()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), YEAR(0), MONTH(0), DAY(0), HOUR(0), MINUTE(0), SECOND(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(80);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(YEAR);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(MONTH);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(DAY);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(HOUR);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(MINUTE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6] = PLCIEC::INT_TO_DINT(SECOND);
      };

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETDISTANCETRIGGER
 ******************************************************************************/
class KRC_SETDISTANCETRIGGER
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT DISTANCE;
   PLCIEC::INT DELAY;
   PLCIEC::INT OUTPUT;
   PLCIEC::BOOL VALUE;
   PLCIEC::REAL PULSE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETDISTANCETRIGGER()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), DISTANCE(0), DELAY(0), OUTPUT(0), VALUE(static_cast<PLCIEC::BOOL>(FALSE)), PULSE(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(3);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(DISTANCE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(DELAY);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(OUTPUT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = PULSE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETLANGUAGE
 ******************************************************************************/
class KRC_SETLANGUAGE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT LANGUAGE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETLANGUAGE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), LANGUAGE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };

      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(79);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0; // DIRECT
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(LANGUAGE);
      };

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
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
       : AXISGROUPIDX(0), OVERRIDE(0), VALID(_VALID), ACTUALOVERRIDE(_ACTUALOVERRIDE), ERROR(_ERROR), ERRORID(_ERRORID), _VALID(static_cast<PLCIEC::BOOL>(FALSE)), _ACTUALOVERRIDE(0), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (((OVERRIDE >= 0) && (OVERRIDE <= 100)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE = OVERRIDE;
         _ERRORID = static_cast<PLCIEC::DINT>(0);
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(504);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _ACTUALOVERRIDE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.OVPROACT;
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETPATHTRIGGER
 ******************************************************************************/
class KRC_SETPATHTRIGGER
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::REAL PATH;
   PLCIEC::INT DELAY;
   PLCIEC::INT OUTPUT;
   PLCIEC::BOOL VALUE;
   PLCIEC::REAL PULSE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETPATHTRIGGER()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), PATH(0), DELAY(0), OUTPUT(0), VALUE(static_cast<PLCIEC::BOOL>(FALSE)), PULSE(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(4);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(DELAY);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(OUTPUT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = PULSE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = PATH;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ACTIVATEPOSCONVERSION
 ******************************************************************************/
class KRC_ACTIVATEPOSCONVERSION
{
   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::BOOL ACTIVATECONVERSION;
   COORDSYS COORDSYSTODISPLAY;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_ACTIVATEPOSCONVERSION()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), ACTIVATECONVERSION(static_cast<PLCIEC::BOOL>(FALSE)), COORDSYSTODISPLAY(), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }

      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(68);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 2;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();

      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = ACTIVATECONVERSION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(COORDSYSTODISPLAY.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(COORDSYSTODISPLAY.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(COORDSYSTODISPLAY.IPO_MODE);
      }

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
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
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TECHFUNCTIONID(0), PARAMETERCOUNT(0), BUFFERMODE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), BOOL_DATA(), INT_DATA(), REAL_DATA(), I(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (((PARAMETERCOUNT < 1) || (PARAMETERCOUNT > 40)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(521);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         return;
      };
      for (I = (PARAMETERCOUNT + 1); I <= 40; I += 1)
      {
         if ((((BOOL_DATA[I] == static_cast<PLCIEC::BOOL>(TRUE)) || (INT_DATA[I] != 0)) || (REAL_DATA[I] != 0.0f)))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(522);
            _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
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
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
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
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TECHFUNCTIONADVANCED
 ******************************************************************************/
class KRC_TECHFUNCTIONADVANCED
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT TECHFUNCTIONID;
   PLCIEC::INT PARAMETERCOUNT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const REAL_ARRAY_12 &RETURNVALUE;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   REAL_ARRAY_12 _RETURNVALUE;
   PLCIEC::DINT _ORDERID;

   /* VAR_IN_OUT */

public:
   PLCIEC::BOOL *BOOL_DATA;
   PLCIEC::DINT *INT_DATA;
   PLCIEC::REAL *REAL_DATA;

   /* VAR */

private:
   PLCIEC::INT I;
   PLCIEC::INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_TECHFUNCTIONADVANCED()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TECHFUNCTIONID(0), PARAMETERCOUNT(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), RETURNVALUE(_RETURNVALUE), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _RETURNVALUE(), _ORDERID(0), BOOL_DATA(), INT_DATA(), REAL_DATA(), I(0), NSTATE(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (((PARAMETERCOUNT < 1) || (PARAMETERCOUNT > 40)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(521);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         return;
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
      };

      for (I = (PARAMETERCOUNT + 1); I <= 40; I += 1)
      {
         if ((((BOOL_DATA[I] == static_cast<PLCIEC::BOOL>(TRUE)) || (INT_DATA[I] != 0)) || (REAL_DATA[I] != 0.0f)))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(522);
            _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            return;
         };
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = 59;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 3;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
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
      if ((MXA_EXECUTECOMMAND_1.READCMDDATARET && (NSTATE == 0)))
      {
         for (I = 1; I <= 12; I += 1)
         {
            _RETURNVALUE[I] = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[I];
         };
         NSTATE = 1;
      };

      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = (MXA_EXECUTECOMMAND_1.DONE && (NSTATE == 1));
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TEST_TECHFUNCTION
 ******************************************************************************/
class KRC_TEST_TECHFUNCTION
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;

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

   /* VAR */

private:
   BOOL_ARRAY_40 BOOL_DATA;
   PLCIEC::INT I;
   INT32_ARRAY_40 INT_DATA;
   REAL_ARRAY_40 REAL_DATA;
   KRC_TECHFUNCTION KRC_TECHFUNCTION_1;

public:
   KRC_TEST_TECHFUNCTION()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), BOOL_DATA(), I(0), INT_DATA(), REAL_DATA(), KRC_TECHFUNCTION_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      for (I = 1; I <= 40; I += 2)
      {
         BOOL_DATA[I] = 1;
         BOOL_DATA[(I - 1)] = 0;
      };
      for (I = 1; I <= 40; I += 1)
      {
         INT_DATA[I] = I;
      };
      INT_DATA[2] = 0;
      INT_DATA[3] = INT_MIN; //-2147483648;
      INT_DATA[4] = -2147483647;
      INT_DATA[5] = INT_MAX; // 2147483647;
      REAL_DATA[1] = 1.0;
      REAL_DATA[2] = 0.0;
      REAL_DATA[3] = static_cast<PLCIEC::REAL>(-2147483500.0);
      REAL_DATA[4] = static_cast<PLCIEC::REAL>(-2147483499.0);
      REAL_DATA[5] = static_cast<PLCIEC::REAL>(2147483500.0);
      REAL_DATA[6] = static_cast<PLCIEC::REAL>(0.4);
      REAL_DATA[7] = static_cast<PLCIEC::REAL>(0.5);
      REAL_DATA[8] = static_cast<PLCIEC::REAL>(0.6);
      REAL_DATA[9] = static_cast<PLCIEC::REAL>(0.9);
      REAL_DATA[10] = static_cast<PLCIEC::REAL>(1.4000001);
      REAL_DATA[11] = static_cast<PLCIEC::REAL>(1.4999999);
      REAL_DATA[12] = static_cast<PLCIEC::REAL>(1.40000001);
      REAL_DATA[13] = static_cast<PLCIEC::REAL>(1.49999999);
      REAL_DATA[14] = static_cast<PLCIEC::REAL>(1.5000001);
      REAL_DATA[15] = static_cast<PLCIEC::REAL>(1.5000009);
      REAL_DATA[16] = static_cast<PLCIEC::REAL>(1.50000001);
      REAL_DATA[17] = static_cast<PLCIEC::REAL>(1.50000009);
      REAL_DATA[18] = static_cast<PLCIEC::REAL>(1.59999999);
      REAL_DATA[19] = static_cast<PLCIEC::REAL>(1.99999999);
      REAL_DATA[20] = static_cast<PLCIEC::REAL>(2.0);
      REAL_DATA[21] = static_cast<PLCIEC::REAL>(2.1);
      REAL_DATA[22] = static_cast<PLCIEC::REAL>(2.2);
      REAL_DATA[23] = static_cast<PLCIEC::REAL>(2.3);
      REAL_DATA[24] = static_cast<PLCIEC::REAL>(2.4);
      REAL_DATA[25] = static_cast<PLCIEC::REAL>(2.5);
      REAL_DATA[26] = static_cast<PLCIEC::REAL>(2.6);
      REAL_DATA[27] = static_cast<PLCIEC::REAL>(2.7);
      REAL_DATA[28] = static_cast<PLCIEC::REAL>(2.8);
      REAL_DATA[29] = static_cast<PLCIEC::REAL>(2.9);
      REAL_DATA[30] = static_cast<PLCIEC::REAL>(3.0);
      REAL_DATA[31] = static_cast<PLCIEC::REAL>(3.1);
      REAL_DATA[32] = static_cast<PLCIEC::REAL>(3.2);
      REAL_DATA[33] = static_cast<PLCIEC::REAL>(3.3);
      REAL_DATA[34] = static_cast<PLCIEC::REAL>(3.4);
      REAL_DATA[35] = static_cast<PLCIEC::REAL>(3.5);
      REAL_DATA[36] = static_cast<PLCIEC::REAL>(3.6);
      REAL_DATA[37] = static_cast<PLCIEC::REAL>(3.7);
      REAL_DATA[38] = static_cast<PLCIEC::REAL>(3.8);
      REAL_DATA[39] = static_cast<PLCIEC::REAL>(3.9);
      REAL_DATA[40] = static_cast<PLCIEC::REAL>(4.0);
      // Call FB KRC_Techfunction_1
      KRC_TECHFUNCTION_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_TECHFUNCTION_1.EXECUTECMD = EXECUTECMD;
      KRC_TECHFUNCTION_1.TECHFUNCTIONID = 999;
      KRC_TECHFUNCTION_1.PARAMETERCOUNT = 40;
      KRC_TECHFUNCTION_1.BUFFERMODE = 0;
      KRC_TECHFUNCTION_1.BOOL_DATA = BOOL_DATA;
      KRC_TECHFUNCTION_1.INT_DATA = INT_DATA;
      KRC_TECHFUNCTION_1.REAL_DATA = REAL_DATA;
      KRC_TECHFUNCTION_1.OnCycle();
      _BUSY = KRC_TECHFUNCTION_1.BUSY;
      _DONE = KRC_TECHFUNCTION_1.DONE;
      _ABORTED = KRC_TECHFUNCTION_1.ABORTED;
      _ERROR = KRC_TECHFUNCTION_1.ERROR;
      _ERRORID = KRC_TECHFUNCTION_1.ERRORID;
      _ORDERID = KRC_TECHFUNCTION_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TOUCHUP
 ******************************************************************************/
class KRC_TOUCHUP
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT INDEX;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR_IN_OUT */

public:
   POSITION1 *POSITIONARRAY;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   PLCIEC::R_TRIG R_TRIG_1;
   PLCIEC::INT M_POSINDEX;

public:
   KRC_TOUCHUP()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), INDEX(0), DONE(_DONE), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), POSITIONARRAY(), MXA_EXECUTECOMMAND_1(), R_TRIG_1(), M_POSINDEX(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (EXECUTECMD)
      {
         if (((INDEX < 1) || (INDEX > 100)))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(513);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(509);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(508);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACTVALID))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(514);
         };
      };
      if ((_ERRORID != static_cast<PLCIEC::DINT>(0)))
      {
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB R_TRIG_1
      R_TRIG_1.CLK = EXECUTECMD;
      R_TRIG_1.OnCycle();
      if (R_TRIG_1.Q)
      {
         POSITIONARRAY[INDEX].COORDSYS_1.TOOL = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOOLACT;
         POSITIONARRAY[INDEX].COORDSYS_1.BASE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.BASEACT;
         POSITIONARRAY[INDEX].COORDSYS_1.IPO_MODE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IPOMODEACT;
         POSITIONARRAY[INDEX].E6POS_1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT;
         POSITIONARRAY[INDEX].E6AXIS_1 = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXISACT;
         M_POSINDEX = INDEX;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(34);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(M_POSINDEX);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_VECTORMOVEOFF
 ******************************************************************************/
class KRC_VECTORMOVEOFF
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_VECTORMOVEOFF()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(45);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_VECTORMOVEON
 ******************************************************************************/
class KRC_VECTORMOVEON
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::REAL X;
   PLCIEC::REAL Y;
   PLCIEC::REAL Z;
   PLCIEC::REAL A;
   PLCIEC::REAL B;
   PLCIEC::REAL C;
   PLCIEC::REAL VECTORLIMIT;
   PLCIEC::REAL MAXDURATION;
   PLCIEC::REAL TORQUEOFFSETVALUE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_VECTORMOVEON()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), X(0), Y(0), Z(0), A(0), B(0), C(0), VECTORLIMIT(0), MAXDURATION(0), TORQUEOFFSETVALUE(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(44);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = C;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = VECTORLIMIT;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = MAXDURATION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = TORQUEOFFSETVALUE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WAITFORINPUT
 ******************************************************************************/
class KRC_WAITFORINPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;
   PLCIEC::BOOL VALUE;
   PLCIEC::BOOL BCONTINUE;
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

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WAITFORINPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), VALUE(static_cast<PLCIEC::BOOL>(FALSE)), BCONTINUE(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(32);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEANALOGOUTPUT
 ******************************************************************************/
class KRC_WRITEANALOGOUTPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;
   PLCIEC::REAL VALUE;
   PLCIEC::BOOL BCONTINUE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEANALOGOUTPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), VALUE(0), BCONTINUE(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(13);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = VALUE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
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
       : AXISGROUPIDX(0), KRC4_OUTPUT(), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), NCHECKSUM(0), I(0), LASTORDERID(0), LASTTGNUMBER(0), LASTTGTYPE(0), M_COMMANDID(0), M_ORDERID(0), M_PROFINETERR(static_cast<PLCIEC::BOOL>(FALSE)), M_PROFINETSTATUS(0), M_ANZTELEGRAMME(0), AE_PGNO_FBIT_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT1_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT2_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT3_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT4_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT5_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT6_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_BIT7_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_PARITY_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_PGNO_VALID_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_EXT_START_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_MOVE_ENABLE_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_CONF_MESS_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_DRIVES_OFF_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_DRIVES_ON_VAL(static_cast<PLCIEC::BOOL>(FALSE)), MASTEST_REQ_EXT_VAL(static_cast<PLCIEC::BOOL>(FALSE)), BRAKETEST_REQ_EXT_VAL(static_cast<PLCIEC::BOOL>(FALSE)), AE_RESET_VAL(static_cast<PLCIEC::BOOL>(FALSE)), BRAKE_VAL(static_cast<PLCIEC::BOOL>(FALSE)), BRAKE_F_VAL(static_cast<PLCIEC::BOOL>(FALSE)), RELEASE_BRAKE_VAL(static_cast<PLCIEC::BOOL>(FALSE)), SHOW_TRACE_VAL(static_cast<PLCIEC::BOOL>(FALSE)), MESSAGE_RESET_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_1_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_2_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_3_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_4_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_5_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_6_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_7_VAL(static_cast<PLCIEC::BOOL>(FALSE)), OUT_VAL_8_VAL(static_cast<PLCIEC::BOOL>(FALSE)), WRITE_OUT_1TO8_VAL(static_cast<PLCIEC::BOOL>(FALSE)), JOG_ADVANCED_VAL(static_cast<PLCIEC::BOOL>(FALSE)), ZW_JOG_AD_STATE_VAL(0), JOG_AD_STATE(0), HEARTBEAT_VAL(0), OVERRIDE_VAL(0), PLC_MAJOR_VAL(0), PLC_MINOR_VAL(0), SR_ORDER1_ID_VAL(0), SR_ORDER2_ID_VAL(0), SR_ORDER3_ID_VAL(0), SR_ORDER4_ID_VAL(0), SR_ORDER5_ID_VAL(0), SR_ORDER6_ID_VAL(0), SR_ORDER7_ID_VAL(0), SR_ORDER8_ID_VAL(0), SR_ORDER9_ID_VAL(0), SR_ORDER10_ID_VAL(0), SR_ORDER1_STATE_VAL(0), SR_ORDER2_STATE_VAL(0), SR_ORDER3_STATE_VAL(0), SR_ORDER4_STATE_VAL(0), SR_ORDER5_STATE_VAL(0), SR_ORDER6_STATE_VAL(0), SR_ORDER7_STATE_VAL(0), SR_ORDER8_STATE_VAL(0), SR_ORDER9_STATE_VAL(0), SR_ORDER10_STATE_VAL(0), CMDPAR_INT1_VAL(0), CMDPAR_INT2_VAL(0), CMDPAR_INT3_VAL(0), CMDPAR_INT4_VAL(0), CMDPAR_INT5_VAL(0), CMDPAR_INT6_VAL(0), CMDPAR_INT7_VAL(0), CMDPAR_INT8_VAL(0), CMDPAR_INT9_VAL(0), CMDPAR_INT10_VAL(0), CMDPAR_INT11_VAL(0), CMDPAR_INT12_VAL(0), CMDPAR_INT13_VAL(0), CMDPAR_INT14_VAL(0), CMDPAR_INT15_VAL(0), CMDPAR_REAL1_VAL(0), CMDPAR_REAL2_VAL(0), CMDPAR_REAL3_VAL(0), CMDPAR_REAL4_VAL(0), CMDPAR_REAL5_VAL(0), CMDPAR_REAL6_VAL(0), CMDPAR_REAL7_VAL(0), CMDPAR_REAL8_VAL(0), CMDPAR_REAL9_VAL(0), CMDPAR_REAL10_VAL(0), CMDPAR_REAL11_VAL(0), CMDPAR_REAL12_VAL(0), CMDPAR_REAL13_VAL(0), CMDPAR_REAL14_VAL(0), CMDPAR_REAL15_VAL(0), CHECKSUM_VAL(0), TRANSMISSIONNO1_VAL(0), TRANSMISSIONNO2_VAL(0), TRANSMISSIONTYPE_VAL(0), ORDERID_VAL(0), CMDID_VAL(0), BUFFERMODE_VAL(0), BOOLVALUES1(0), MXA_RESETCOMMAND_1(), DUMMY(static_cast<PLCIEC::BOOL>(FALSE)), FTMP(0), NTMP1(0), FTMP1(0), BTMP1(static_cast<PLCIEC::BOOL>(FALSE)), BMAXREALERR(static_cast<PLCIEC::BOOL>(FALSE))
   {
   }

public:
   void OnCycle()
   {

      _ERRORID = static_cast<PLCIEC::DINT>(0);
      NCHECKSUM = static_cast<PLCIEC::DWORD>(0);
      BMAXREALERR = static_cast<PLCIEC::BOOL>(FALSE);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      if (((KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > static_cast<PLCIEC::DINT>(0))) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET)))
      {
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE == static_cast<PLCIEC::BOOL>(FALSE)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(507);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
      }
      else
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE = static_cast<PLCIEC::BOOL>(FALSE);
      };
      AE_PGNO_FBIT_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT1_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT2_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT3_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT4_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT5_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT6_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_BIT7_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_PARITY_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_PGNO_VALID_VAL = static_cast<PLCIEC::BOOL>(FALSE);
      AE_EXT_START_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.EXT_START;
      AE_MOVE_ENABLE_VAL = ((((((KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE && !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_DISABLE)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID == static_cast<PLCIEC::DINT>(0))) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB == static_cast<PLCIEC::DINT>(0))) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == static_cast<PLCIEC::DINT>(0))) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID == static_cast<PLCIEC::DINT>(0)));
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
            PLCIEC::ChBit(BOOLVALUES1, 0, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1]);
            PLCIEC::ChBit(BOOLVALUES1, 1, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2]);
            PLCIEC::ChBit(BOOLVALUES1, 2, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[3]);
            PLCIEC::ChBit(BOOLVALUES1, 3, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[4]);
            PLCIEC::ChBit(BOOLVALUES1, 4, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[5]);
            PLCIEC::ChBit(BOOLVALUES1, 5, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[6]);
            PLCIEC::ChBit(BOOLVALUES1, 6, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[7]);
            PLCIEC::ChBit(BOOLVALUES1, 7, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[8]);
            PLCIEC::ChBit(BOOLVALUES1, 8, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[9]);
            PLCIEC::ChBit(BOOLVALUES1, 9, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[10]);
            PLCIEC::ChBit(BOOLVALUES1, 10, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[11]);
            PLCIEC::ChBit(BOOLVALUES1, 11, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[12]);
            PLCIEC::ChBit(BOOLVALUES1, 12, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[13]);
            PLCIEC::ChBit(BOOLVALUES1, 13, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[14]);
            PLCIEC::ChBit(BOOLVALUES1, 14, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[15]);
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
               if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] == static_cast<PLCIEC::BOOL>(TRUE)))
               {
                  NCHECKSUM = (NCHECKSUM ^ static_cast<PLCIEC::DWORD>(1));
               };
               NCHECKSUM = (NCHECKSUM ^ PLCIEC::DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I]));
               FTMP = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I];
               NTMP1 = PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((FTMP - 0.5f) * 10.0f));
               FTMP1 = static_cast<PLCIEC::REAL>(NTMP1 / 10) + 0.5f;
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
                  PLCIEC::ChBit(BOOLVALUES1, 0, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[16]);
                  PLCIEC::ChBit(BOOLVALUES1, 1, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[17]);
                  PLCIEC::ChBit(BOOLVALUES1, 2, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[18]);
                  PLCIEC::ChBit(BOOLVALUES1, 3, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[19]);
                  PLCIEC::ChBit(BOOLVALUES1, 4, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[20]);
                  PLCIEC::ChBit(BOOLVALUES1, 5, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[21]);
                  PLCIEC::ChBit(BOOLVALUES1, 6, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[22]);
                  PLCIEC::ChBit(BOOLVALUES1, 7, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[23]);
                  PLCIEC::ChBit(BOOLVALUES1, 8, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[24]);
                  PLCIEC::ChBit(BOOLVALUES1, 9, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[25]);
                  PLCIEC::ChBit(BOOLVALUES1, 10, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[26]);
                  PLCIEC::ChBit(BOOLVALUES1, 11, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[27]);
                  PLCIEC::ChBit(BOOLVALUES1, 12, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[28]);
                  PLCIEC::ChBit(BOOLVALUES1, 13, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[29]);
                  PLCIEC::ChBit(BOOLVALUES1, 14, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[30]);
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
                  PLCIEC::ChBit(BOOLVALUES1, 0, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[31]);
                  PLCIEC::ChBit(BOOLVALUES1, 1, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[32]);
                  PLCIEC::ChBit(BOOLVALUES1, 2, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[33]);
                  PLCIEC::ChBit(BOOLVALUES1, 3, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[34]);
                  PLCIEC::ChBit(BOOLVALUES1, 4, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[35]);
                  PLCIEC::ChBit(BOOLVALUES1, 5, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[36]);
                  PLCIEC::ChBit(BOOLVALUES1, 6, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[37]);
                  PLCIEC::ChBit(BOOLVALUES1, 7, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[38]);
                  PLCIEC::ChBit(BOOLVALUES1, 8, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[39]);
                  PLCIEC::ChBit(BOOLVALUES1, 9, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[40]);
                  PLCIEC::ChBit(BOOLVALUES1, 10, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[41]);
                  PLCIEC::ChBit(BOOLVALUES1, 11, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[42]);
                  PLCIEC::ChBit(BOOLVALUES1, 12, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[43]);
                  PLCIEC::ChBit(BOOLVALUES1, 13, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[44]);
                  PLCIEC::ChBit(BOOLVALUES1, 14, /* := */ KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[45]);
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
         CMDPAR_INT1_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT2_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT3_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT4_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT5_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT6_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT7_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT8_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT9_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT10_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT11_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT12_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT13_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT14_VAL = static_cast<PLCIEC::DINT>(0);
         CMDPAR_INT15_VAL = static_cast<PLCIEC::DINT>(0);
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
      PLCIEC::ChBit(KRC4_OUTPUT[0], 0, /* := */ AE_PGNO_FBIT_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 1, /* := */ AE_PGNO_BIT1_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 2, /* := */ AE_PGNO_BIT2_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 3, /* := */ AE_PGNO_BIT3_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 4, /* := */ AE_PGNO_BIT4_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 5, /* := */ AE_PGNO_BIT5_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 6, /* := */ AE_PGNO_BIT6_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[0], 7, /* := */ AE_PGNO_BIT7_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 0, /* := */ AE_PGNO_PARITY_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 1, /* := */ AE_PGNO_VALID_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 2, /* := */ AE_EXT_START_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 3, /* := */ AE_MOVE_ENABLE_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 4, /* := */ AE_CONF_MESS_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 5, /* := */ AE_DRIVES_OFF_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 6, /* := */ AE_DRIVES_ON_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[1], 7, /* := */ MASTEST_REQ_EXT_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[2], 0, /* := */ BRAKETEST_REQ_EXT_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 0, /* := */ AE_RESET_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 1, /* := */ BRAKE_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 2, /* := */ BRAKE_F_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 3, /* := */ RELEASE_BRAKE_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 4, /* := */ SHOW_TRACE_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 5, /* := */ MESSAGE_RESET_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[4], 7, /* := */ WRITE_OUT_1TO8_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 0, /* := */ OUT_VAL_1_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 1, /* := */ OUT_VAL_2_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 2, /* := */ OUT_VAL_3_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 3, /* := */ OUT_VAL_4_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 4, /* := */ OUT_VAL_5_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 5, /* := */ OUT_VAL_6_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 6, /* := */ OUT_VAL_7_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[5], 7, /* := */ OUT_VAL_8_VAL);
      PLCIEC::ChBit(KRC4_OUTPUT[2], 7, /* := */ JOG_ADVANCED_VAL);
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
 * FUNCTION_BLOCK KRC_WRITEAXWORKSPACE
 ******************************************************************************/
class KRC_WRITEAXWORKSPACE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT WORKSPACENO;
   PLCIEC::INT WORKSPACEMODE;
   AXBOX WORKSPACEDATA;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEAXWORKSPACE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), WORKSPACENO(0), WORKSPACEMODE(0), WORKSPACEDATA(), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(50);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = WORKSPACENO;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = WORKSPACEMODE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = WORKSPACEDATA.A1_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = WORKSPACEDATA.A2_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = WORKSPACEDATA.A3_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = WORKSPACEDATA.A4_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = WORKSPACEDATA.A5_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = WORKSPACEDATA.A6_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = WORKSPACEDATA.A1_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = WORKSPACEDATA.A2_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = WORKSPACEDATA.A3_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = WORKSPACEDATA.A4_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = WORKSPACEDATA.A5_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = WORKSPACEDATA.A6_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13] = WORKSPACEDATA.E1_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14] = WORKSPACEDATA.E2_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15] = WORKSPACEDATA.E3_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16] = WORKSPACEDATA.E4_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17] = WORKSPACEDATA.E5_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18] = WORKSPACEDATA.E6_N;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19] = WORKSPACEDATA.E1_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20] = WORKSPACEDATA.E2_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21] = WORKSPACEDATA.E3_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22] = WORKSPACEDATA.E4_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23] = WORKSPACEDATA.E5_P;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24] = WORKSPACEDATA.E6_P;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEBASEDATA
 ******************************************************************************/
class KRC_WRITEBASEDATA
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT BASENO;
   FRAME BASEDATA;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEBASEDATA()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), BASENO(0), BASEDATA(), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(23);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(BASENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = BASEDATA.X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = BASEDATA.Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = BASEDATA.Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = BASEDATA.A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = BASEDATA.B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = BASEDATA.C;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEDIGITALOUTPUT
 ******************************************************************************/
class KRC_WRITEDIGITALOUTPUT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT NUMBER;
   PLCIEC::BOOL VALUE;
   PLCIEC::REAL PULSE;
   PLCIEC::BOOL BCONTINUE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEDIGITALOUTPUT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), NUMBER(0), VALUE(static_cast<PLCIEC::BOOL>(FALSE)), PULSE(0), BCONTINUE(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(10);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(NUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = PULSE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEDIGITALOUTPUT1TO8
 ******************************************************************************/
class KRC_WRITEDIGITALOUTPUT1TO8
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL OUT1;
   PLCIEC::BOOL OUT2;
   PLCIEC::BOOL OUT3;
   PLCIEC::BOOL OUT4;
   PLCIEC::BOOL OUT5;
   PLCIEC::BOOL OUT6;
   PLCIEC::BOOL OUT7;
   PLCIEC::BOOL OUT8;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;

public:
   KRC_WRITEDIGITALOUTPUT1TO8()
       : AXISGROUPIDX(0), OUT1(static_cast<PLCIEC::BOOL>(FALSE)), OUT2(static_cast<PLCIEC::BOOL>(FALSE)), OUT3(static_cast<PLCIEC::BOOL>(FALSE)), OUT4(static_cast<PLCIEC::BOOL>(FALSE)), OUT5(static_cast<PLCIEC::BOOL>(FALSE)), OUT6(static_cast<PLCIEC::BOOL>(FALSE)), OUT7(static_cast<PLCIEC::BOOL>(FALSE)), OUT8(static_cast<PLCIEC::BOOL>(FALSE)), ERROR(_ERROR), ERRORID(_ERRORID), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0)
   {
   }

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      }
      else
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
         _ERROR = static_cast<PLCIEC::BOOL>(FALSE);
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_1 = OUT1;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_2 = OUT2;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_3 = OUT3;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_4 = OUT4;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_5 = OUT5;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_6 = OUT6;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_7 = OUT7;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_8 = OUT8;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.WRITE_OUT_1TO8 = static_cast<PLCIEC::BOOL>(TRUE);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITELOADDATA
 ******************************************************************************/
class KRC_WRITELOADDATA
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT TOOL;
   PLCIEC::REAL M;
   PLCIEC::REAL X;
   PLCIEC::REAL Y;
   PLCIEC::REAL Z;
   PLCIEC::REAL A;
   PLCIEC::REAL B;
   PLCIEC::REAL C;
   PLCIEC::REAL JX;
   PLCIEC::REAL JY;
   PLCIEC::REAL JZ;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITELOADDATA()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TOOL(0), M(0), X(0), Y(0), Z(0), A(0), B(0), C(0), JX(0), JY(0), JZ(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(15);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = M;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = C;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = JX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = JY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = JZ;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITESOFTEND
 ******************************************************************************/
class KRC_WRITESOFTEND
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::REAL A1_MIN;
   PLCIEC::REAL A1_MAX;
   PLCIEC::REAL A2_MIN;
   PLCIEC::REAL A2_MAX;
   PLCIEC::REAL A3_MIN;
   PLCIEC::REAL A3_MAX;
   PLCIEC::REAL A4_MIN;
   PLCIEC::REAL A4_MAX;
   PLCIEC::REAL A5_MIN;
   PLCIEC::REAL A5_MAX;
   PLCIEC::REAL A6_MIN;
   PLCIEC::REAL A6_MAX;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITESOFTEND()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), A1_MIN(0), A1_MAX(0), A2_MIN(0), A2_MAX(0), A3_MIN(0), A3_MAX(0), A4_MIN(0), A4_MAX(0), A5_MIN(0), A5_MAX(0), A6_MIN(0), A6_MAX(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(17);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = A1_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = A1_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = A2_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = A2_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = A3_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = A3_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = A4_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = A4_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = A5_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = A5_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = A6_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = A6_MAX;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITESOFTENDEXT
 ******************************************************************************/
class KRC_WRITESOFTENDEXT
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::REAL E1_MIN;
   PLCIEC::REAL E1_MAX;
   PLCIEC::REAL E2_MIN;
   PLCIEC::REAL E2_MAX;
   PLCIEC::REAL E3_MIN;
   PLCIEC::REAL E3_MAX;
   PLCIEC::REAL E4_MIN;
   PLCIEC::REAL E4_MAX;
   PLCIEC::REAL E5_MIN;
   PLCIEC::REAL E5_MAX;
   PLCIEC::REAL E6_MIN;
   PLCIEC::REAL E6_MAX;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITESOFTENDEXT()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), E1_MIN(0), E1_MAX(0), E2_MIN(0), E2_MAX(0), E3_MIN(0), E3_MAX(0), E4_MIN(0), E4_MAX(0), E5_MIN(0), E5_MAX(0), E6_MIN(0), E6_MAX(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(19);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13] = E1_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14] = E1_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15] = E2_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16] = E2_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17] = E3_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18] = E3_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19] = E4_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20] = E4_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21] = E5_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22] = E5_MAX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23] = E6_MIN;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24] = E6_MAX;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITESYSVAR
 ******************************************************************************/
class KRC_WRITESYSVAR
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT INDEX;
   PLCIEC::REAL VALUE1;
   PLCIEC::REAL VALUE2;
   PLCIEC::REAL VALUE3;
   PLCIEC::REAL VALUE4;
   PLCIEC::REAL VALUE5;
   PLCIEC::REAL VALUE6;
   PLCIEC::REAL VALUE7;
   PLCIEC::REAL VALUE8;
   PLCIEC::REAL VALUE9;
   PLCIEC::REAL VALUE10;
   PLCIEC::BOOL BCONTINUE;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITESYSVAR()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), INDEX(0), VALUE1(0), VALUE2(0), VALUE3(0), VALUE4(0), VALUE5(0), VALUE6(0), VALUE7(0), VALUE8(0), VALUE9(0), VALUE10(0), BCONTINUE(static_cast<PLCIEC::BOOL>(FALSE)), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(28);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(INDEX);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = VALUE1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = VALUE2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = VALUE3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = VALUE4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = VALUE5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = VALUE6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = VALUE7;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = VALUE8;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = VALUE9;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = VALUE10;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITETOOLDATA
 ******************************************************************************/
class KRC_WRITETOOLDATA
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   FRAME TOOLDATA;
   PLCIEC::INT TOOLNO;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITETOOLDATA()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), TOOLDATA(), TOOLNO(0), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(21);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(TOOLNO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = TOOLDATA.X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = TOOLDATA.Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = TOOLDATA.Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = TOOLDATA.A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = TOOLDATA.B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = TOOLDATA.C;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEWORKSPACE
 ******************************************************************************/
class KRC_WRITEWORKSPACE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTECMD;
   PLCIEC::INT WORKSPACENO;
   PLCIEC::INT WORKSPACEMODE;
   BOX WORKSPACEDATA;
   PLCIEC::INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &ABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _ABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEWORKSPACE()
       : AXISGROUPIDX(0), EXECUTECMD(static_cast<PLCIEC::BOOL>(FALSE)), WORKSPACENO(0), WORKSPACEMODE(0), WORKSPACEDATA(), BUFFERMODE(0), BUSY(_BUSY), DONE(_DONE), ABORTED(_ABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _ABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MXA_EXECUTECOMMAND_1()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      _ERRORID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = static_cast<PLCIEC::DINT>(48);
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MXA_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = WORKSPACENO;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = WORKSPACEMODE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = WORKSPACEDATA.X;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = WORKSPACEDATA.Y;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = WORKSPACEDATA.Z;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = WORKSPACEDATA.A;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = WORKSPACEDATA.B;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = WORKSPACEDATA.C;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = WORKSPACEDATA.X1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = WORKSPACEDATA.X2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = WORKSPACEDATA.Y1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = WORKSPACEDATA.Y2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = WORKSPACEDATA.Z1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = WORKSPACEDATA.Z2;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MXA_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_EXECUTECOMMAND
 ******************************************************************************/
class MC_EXECUTECOMMAND
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   PLCIEC::DINT CMDID;
   PLCIEC::INT QUEUEMODE;
   PLCIEC::INT COMMANDSIZE;
   PLCIEC::BOOL ENABLEDIRECTEXE;
   PLCIEC::BOOL ENABLEQUEUEEXE;
   PLCIEC::BOOL IGNOREINIT;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &WRITECMDPAR;
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::BOOL &READCMDDATARET;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _WRITECMDPAR;
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::BOOL _READCMDDATARET;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MXA_RESETCOMMAND RESETCOMMAND_1;
   MXA_GETORDERSTATE GETORDERSTATE_1;
   KRC_ERROR KRC_ERROR_1;
   PLCIEC::INT M_STATE;
   PLCIEC::DINT M_ORDERID;
   PLCIEC::BOOL M_EXECUTELAST;
   PLCIEC::BOOL M_RE_EXECUTE;
   PLCIEC::BOOL M_FE_EXECUTE;
   PLCIEC::INT M_COMMANDSIZE;
   PLCIEC::DINT M_INTERRORID;
   PLCIEC::DINT M_GLOBALERRORID;

public:
   MC_EXECUTECOMMAND()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), CMDID(0), QUEUEMODE(0), COMMANDSIZE(0), ENABLEDIRECTEXE(static_cast<PLCIEC::BOOL>(FALSE)), ENABLEQUEUEEXE(static_cast<PLCIEC::BOOL>(FALSE)), IGNOREINIT(static_cast<PLCIEC::BOOL>(FALSE)), WRITECMDPAR(_WRITECMDPAR), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), READCMDDATARET(_READCMDDATARET), ORDERID(_ORDERID), _WRITECMDPAR(static_cast<PLCIEC::BOOL>(FALSE)), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _READCMDDATARET(static_cast<PLCIEC::BOOL>(FALSE)), _ORDERID(0), RESETCOMMAND_1(), GETORDERSTATE_1(), KRC_ERROR_1(), M_STATE(0), M_ORDERID(0), M_EXECUTELAST(static_cast<PLCIEC::BOOL>(FALSE)), M_RE_EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), M_COMMANDSIZE(0), M_INTERRORID(0), M_GLOBALERRORID(0)
   {
   }

public:
   void OnCycle()
   {
      if (((EXECUTE == static_cast<PLCIEC::BOOL>(TRUE)) && (M_EXECUTELAST == static_cast<PLCIEC::BOOL>(FALSE))))
      {
         if ((M_STATE == 1))
         {
            M_INTERRORID = static_cast<PLCIEC::DINT>(543);
         }
         else
         {
            M_STATE = 0;
            M_ORDERID = static_cast<PLCIEC::DINT>(0);
            M_INTERRORID = static_cast<PLCIEC::DINT>(0);
         };
         M_RE_EXECUTE = static_cast<PLCIEC::BOOL>(TRUE);
      };
      if (((EXECUTE == static_cast<PLCIEC::BOOL>(FALSE)) && (M_EXECUTELAST == static_cast<PLCIEC::BOOL>(TRUE))))
      {
         M_FE_EXECUTE = static_cast<PLCIEC::BOOL>(TRUE);
      };
      M_EXECUTELAST = EXECUTE;
      _WRITECMDPAR = static_cast<PLCIEC::BOOL>(FALSE);
      _READCMDDATARET = static_cast<PLCIEC::BOOL>(FALSE);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         M_INTERRORID = static_cast<PLCIEC::DINT>(506);
      }
      else
      {
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE))
         {
            M_INTERRORID = static_cast<PLCIEC::DINT>(507);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT))
         {
            M_INTERRORID = static_cast<PLCIEC::DINT>(508);
         };
      };
      if ((M_RE_EXECUTE && (M_INTERRORID == static_cast<PLCIEC::DINT>(0))))
      {
         M_STATE = 1;
         if ((((QUEUEMODE == 0) && (ENABLEDIRECTEXE == static_cast<PLCIEC::BOOL>(FALSE))) || ((QUEUEMODE > 0) && (ENABLEQUEUEEXE == static_cast<PLCIEC::BOOL>(FALSE)))))
         {
            M_INTERRORID = static_cast<PLCIEC::DINT>(502);
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            if (!(IGNOREINIT))
            {
               M_INTERRORID = static_cast<PLCIEC::DINT>(508);
            };
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            M_INTERRORID = static_cast<PLCIEC::DINT>(509);
         };
      };
      if (((M_STATE == 1) && (M_INTERRORID == static_cast<PLCIEC::DINT>(0))))
      {
         if (M_RE_EXECUTE)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID + static_cast<PLCIEC::DINT>(1));
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID >= static_cast<PLCIEC::DINT>(2147483647)))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = static_cast<PLCIEC::DINT>(1);
            };
            M_ORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID;
         };
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET == M_ORDERID))
         {
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET == CMDID))
            {
               if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSPLC == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSKRC))
               {
                  if ((QUEUEMODE == 0))
                  {
                     M_STATE = 15;
                     _READCMDDATARET = static_cast<PLCIEC::BOOL>(TRUE);
                  }
                  else
                  {
                     M_STATE = 5;
                  };
               }
               else
               {
                  M_INTERRORID = static_cast<PLCIEC::DINT>(512);
               };
            }
            else
            {
               M_INTERRORID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET * static_cast<PLCIEC::DINT>(-1));
            };
            // Call FB ResetCommand_1
            RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
            RESETCOMMAND_1.OnCycle();
         }
         else
         {
            if (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == static_cast<PLCIEC::DINT>(0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID == static_cast<PLCIEC::DINT>(0))) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED || IGNOREINIT)))
            {
               if (((QUEUEMODE < 2) || (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.QUEUECOUNT < 80)))
               {
                  // Call FB ResetCommand_1
                  RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
                  RESETCOMMAND_1.OnCycle();
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = M_ORDERID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = CMDID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = PLCIEC::INT_TO_DINT(QUEUEMODE);
                  M_COMMANDSIZE = COMMANDSIZE;
                  if (((COMMANDSIZE < 1) || (COMMANDSIZE > 3)))
                  {
                     M_INTERRORID = 517;
                     M_COMMANDSIZE = 3;
                  };
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = M_COMMANDSIZE;
                  _WRITECMDPAR = static_cast<PLCIEC::BOOL>(TRUE);
               };
            };
         };
      };
      if ((((M_STATE > 1) && (M_STATE < 15)) && (M_INTERRORID == static_cast<PLCIEC::DINT>(0))))
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
         };
      };
      if ((M_INTERRORID != static_cast<PLCIEC::DINT>(0)))
      {
         M_STATE = (PLCIEC::DINT_TO_INT(M_INTERRORID) * -(1));
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = M_INTERRORID;
      };
      // Call FB KRC_ERROR_1
      KRC_ERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_ERROR_1.MESSAGERESET = static_cast<PLCIEC::BOOL>(FALSE);
      KRC_ERROR_1.OnCycle();
      M_GLOBALERRORID = KRC_ERROR_1.ERRORID;
      _ERRORID = M_INTERRORID;
      if ((((_ERRORID == static_cast<PLCIEC::DINT>(0)) && (M_STATE < 15)) && (M_GLOBALERRORID == static_cast<PLCIEC::DINT>(0))))
      {
         _ERRORID = M_GLOBALERRORID;
      };
      _BUSY = (((M_STATE > 0) && (M_STATE < 15)) && (_ERRORID == static_cast<PLCIEC::DINT>(0)));
      _ACTIVE = ((M_STATE == 10) && (_ERRORID == static_cast<PLCIEC::DINT>(0)));
      _DONE = (M_STATE == 15);
      _COMMANDABORTED = (M_STATE == 20);
      _COMBUSY = ((M_STATE > 1) && (M_STATE < 15));
      _COMACPT = (M_STATE > 1);
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      if ((((_DONE || _ERROR) || _COMMANDABORTED) && !(EXECUTE)))
      {
         M_STATE = 0;
         M_ORDERID = static_cast<PLCIEC::DINT>(0);
         M_INTERRORID = static_cast<PLCIEC::DINT>(0);
      };
      if (_DONE && M_FE_EXECUTE)
      {
         _DONE = false;
         _COMACPT = false;
      };
      if (_ERROR && M_FE_EXECUTE)
      {
         _ERROR = false;
      };
      if (_COMMANDABORTED && M_FE_EXECUTE)
      {
         _COMMANDABORTED = false;
      };
      if ((_ERRORID != static_cast<PLCIEC::DINT>(0)) && M_FE_EXECUTE)
      {
         _ERRORID = static_cast<PLCIEC::DINT>(0);
      };
      M_RE_EXECUTE = static_cast<PLCIEC::BOOL>(FALSE);
      M_FE_EXECUTE = static_cast<PLCIEC::BOOL>(FALSE);

      _ORDERID = M_ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVE
 ******************************************************************************/
class MC_MOVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::DINT CMDID;
   PLCIEC::BOOL EXECUTE;
   PLCIEC::INT MOVETYPE;
   E6POS ACTPOSITION;
   E6AXIS AXISPOSITION;
   E6POS CIRCHP;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ABSOLUTEVELOCITY;
   PLCIEC::REAL ACCELERATION;
   PLCIEC::REAL ABSOLUTEACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   PLCIEC::INT CIRCTYPE;
   PLCIEC::REAL CIRCANGLE;
   APO APPROXIMATE;
   PLCIEC::BOOL POSVALIDX;
   PLCIEC::BOOL POSVALIDY;
   PLCIEC::BOOL POSVALIDZ;
   PLCIEC::BOOL POSVALIDA;
   PLCIEC::BOOL POSVALIDB;
   PLCIEC::BOOL POSVALIDC;
   PLCIEC::BOOL POSVALIDE1;
   PLCIEC::BOOL POSVALIDE2;
   PLCIEC::BOOL POSVALIDE3;
   PLCIEC::BOOL POSVALIDE4;
   PLCIEC::BOOL POSVALIDE5;
   PLCIEC::BOOL POSVALIDE6;
   PLCIEC::BOOL POSVALIDS;
   PLCIEC::BOOL POSVALIDT;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_EXECUTECOMMAND MC_EXECUTECOMMAND_1;

   /* VAR_TEMP */

private:
   PLCIEC::INT COMMANDSIZE;
   PLCIEC::DINT M_VELOCITY;
   PLCIEC::DINT M_ACCELERATION;

public:
   MC_MOVE()
       : AXISGROUPIDX(0), CMDID(static_cast<PLCIEC::DINT>(1)), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), MOVETYPE(0), ACTPOSITION(), AXISPOSITION(), CIRCHP(), VELOCITY(0), ABSOLUTEVELOCITY(0), ACCELERATION(0), ABSOLUTEACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), CIRCTYPE(0), CIRCANGLE(0), APPROXIMATE(), POSVALIDX(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDY(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDZ(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDA(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDB(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDC(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE1(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE2(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE3(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE4(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE5(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDE6(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDS(static_cast<PLCIEC::BOOL>(FALSE)), POSVALIDT(static_cast<PLCIEC::BOOL>(FALSE)), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_EXECUTECOMMAND_1(), COMMANDSIZE(0), M_VELOCITY(0), M_ACCELERATION(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      if (EXECUTE)
      {
         if (((VELOCITY > 0) && (ABSOLUTEVELOCITY > 0.0f)))
         {
            _ERRORID = static_cast<PLCIEC::DINT>(520);
            _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            return;
         };
         M_VELOCITY = PLCIEC::REAL_TO_DINT(VELOCITY * (-1000.0f));
         switch (MOVETYPE)
         {
         case 0:
         case 1:
         case 6:
         case 9:
         case 10:
         case 11:
         case 16:
         case 19:
            if ((ABSOLUTEVELOCITY > 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(519);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            };
            break;
         };
         if (ABSOLUTEVELOCITY > 0.0f)
         {
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP <= 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(544);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            };
            M_VELOCITY = PLCIEC::REAL_TO_DINT(static_cast<PLCIEC::REAL>((ABSOLUTEVELOCITY * -100000.0f) / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP));
         };

         M_ACCELERATION = PLCIEC::REAL_TO_DINT(ACCELERATION * (-1000.0f));
         switch (MOVETYPE)
         {
         case 0:
         case 1:
         case 6:
         case 9:
         case 10:
         case 11:
         case 16:
         case 19:
            if ((ABSOLUTEACCELERATION > 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(545);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            };
            break;
         };
         if ((ABSOLUTEACCELERATION > 0.0f))
         {
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP <= 0.0f))
            {
               _ERRORID = static_cast<PLCIEC::DINT>(546);
               _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               return;
            };
            M_ACCELERATION = PLCIEC::REAL_TO_DINT(ABSOLUTEACCELERATION * -100000.0f / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP);
         };
      };
      if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
      {
         COMMANDSIZE = 2;
      }
      else
      {
         COMMANDSIZE = 1;
      };
      // Call FB mc_ExecuteCommand_1
      MC_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_EXECUTECOMMAND_1.EXECUTE = EXECUTE;
      MC_EXECUTECOMMAND_1.CMDID = CMDID;
      MC_EXECUTECOMMAND_1.QUEUEMODE = QUEUEMODE;
      MC_EXECUTECOMMAND_1.COMMANDSIZE = COMMANDSIZE;
      MC_EXECUTECOMMAND_1.ENABLEDIRECTEXE = static_cast<PLCIEC::BOOL>(FALSE);
      MC_EXECUTECOMMAND_1.ENABLEQUEUEEXE = static_cast<PLCIEC::BOOL>(TRUE);
      MC_EXECUTECOMMAND_1.IGNOREINIT = static_cast<PLCIEC::BOOL>(FALSE);
      MC_EXECUTECOMMAND_1.OnCycle();
      if (MC_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = POSVALIDX;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = POSVALIDY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[3] = POSVALIDZ;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[4] = POSVALIDA;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[5] = POSVALIDB;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[6] = POSVALIDC;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[7] = POSVALIDE1;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[8] = POSVALIDE2;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[9] = POSVALIDE3;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[10] = POSVALIDE4;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[11] = POSVALIDE5;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[12] = POSVALIDE6;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[13] = POSVALIDS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[14] = POSVALIDT;
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[15] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[16] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[17] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[18] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[19] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[20] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[21] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[22] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[23] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[24] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[25] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[26] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[27] = static_cast<PLCIEC::BOOL>(TRUE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[28] = static_cast<PLCIEC::BOOL>(TRUE);
         };
         if (((((MOVETYPE == 0) || (MOVETYPE == 10)) || (MOVETYPE == 9)) || (MOVETYPE == 19)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(0);
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = PLCIEC::INT_TO_DINT(ACTPOSITION.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = PLCIEC::INT_TO_DINT(ACTPOSITION.TURN);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.TOOL);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.BASE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = PLCIEC::INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6] = PLCIEC::INT_TO_DINT(MOVETYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[7] = M_VELOCITY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[8] = M_ACCELERATION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[9] = PLCIEC::INT_TO_DINT(APPROXIMATE.PTP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[10] = PLCIEC::INT_TO_DINT(APPROXIMATE.CP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[11] = PLCIEC::INT_TO_DINT(APPROXIMATE.CPTP);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[12] = PLCIEC::INT_TO_DINT(APPROXIMATE.CVEL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[13] = PLCIEC::INT_TO_DINT(ORITYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[14] = PLCIEC::INT_TO_DINT(CIRCTYPE);
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[15] = PLCIEC::INT_TO_DINT(CIRCHP.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[16] = PLCIEC::INT_TO_DINT(CIRCHP.TURN);
         };
         if (((((MOVETYPE == 0) || (MOVETYPE == 10)) || (MOVETYPE == 9)) || (MOVETYPE == 19)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = AXISPOSITION.A1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = AXISPOSITION.A2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = AXISPOSITION.A3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = AXISPOSITION.A4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = AXISPOSITION.A5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = AXISPOSITION.A6;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = AXISPOSITION.E1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = AXISPOSITION.E2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = AXISPOSITION.E3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = AXISPOSITION.E4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = AXISPOSITION.E5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = AXISPOSITION.E6;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = ACTPOSITION.X;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = ACTPOSITION.Y;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[3] = ACTPOSITION.Z;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[4] = ACTPOSITION.A;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[5] = ACTPOSITION.B;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[6] = ACTPOSITION.C;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[7] = ACTPOSITION.E1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[8] = ACTPOSITION.E2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[9] = ACTPOSITION.E3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[10] = ACTPOSITION.E4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[11] = ACTPOSITION.E5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[12] = ACTPOSITION.E6;
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[13] = APPROXIMATE.CDIS;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[14] = APPROXIMATE.CORI;
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[15] = CIRCHP.X;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[16] = CIRCHP.Y;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[17] = CIRCHP.Z;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[18] = CIRCHP.A;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[19] = CIRCHP.B;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[20] = CIRCHP.C;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[21] = CIRCHP.E1;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[22] = CIRCHP.E2;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[23] = CIRCHP.E3;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[24] = CIRCHP.E4;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[25] = CIRCHP.E5;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[26] = CIRCHP.E6;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[27] = CIRCANGLE;
         };
      };
      _COMACPT = MC_EXECUTECOMMAND_1.COMACPT;
      _COMBUSY = MC_EXECUTECOMMAND_1.COMBUSY;
      _BUSY = MC_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MC_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MC_EXECUTECOMMAND_1.DONE;
      _COMMANDABORTED = MC_EXECUTECOMMAND_1.COMMANDABORTED;
      _ERRORID = MC_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_EXECUTECOMMAND_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVEAXISABSOLUTE
 ******************************************************************************/
class MC_MOVEAXISABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6AXIS AXISPOSITION;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6POS M_POSITION;
   PLCIEC::INT M_ORITYPE;
   COORDSYS M_COORDINATESYSTEM;

public:
   MC_MOVEAXISABSOLUTE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), AXISPOSITION(), VELOCITY(0), ACCELERATION(0), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_CIRCHP(), M_POSITION(), M_ORITYPE(0), M_COORDINATESYSTEM()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 0;
      MC_MOVE_1.AXISPOSITION = AXISPOSITION;
      MC_MOVE_1.VELOCITY = VELOCITY;
      MC_MOVE_1.ACCELERATION = ACCELERATION;
      MC_MOVE_1.ORITYPE = M_ORITYPE;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVECIRCULARABSOLUTE
 ******************************************************************************/
class MC_MOVECIRCULARABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6POS ACTPOSITION;
   E6POS CIRCHP;
   PLCIEC::REAL ANGLE;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   PLCIEC::INT CIRCTYPE;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVECIRCULARABSOLUTE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), ACTPOSITION(), CIRCHP(), ANGLE(0), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), CIRCTYPE(0), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_COORDINATESYSTEM(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 7;
      MC_MOVE_1.ACTPOSITION = ACTPOSITION;
      MC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      MC_MOVE_1.CIRCHP = CIRCHP;
      MC_MOVE_1.ABSOLUTEVELOCITY = VELOCITY;
      MC_MOVE_1.ABSOLUTEACCELERATION = ACCELERATION;
      MC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      MC_MOVE_1.ORITYPE = ORITYPE;
      MC_MOVE_1.CIRCTYPE = CIRCTYPE;
      MC_MOVE_1.CIRCANGLE = ANGLE;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVECIRCULARRELATIVE
 ******************************************************************************/
class MC_MOVECIRCULARRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6POS DISTANCE;
   E6POS CIRCHP;
   PLCIEC::REAL ANGLE;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   PLCIEC::INT CIRCTYPE;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVECIRCULARRELATIVE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), DISTANCE(), CIRCHP(), ANGLE(0), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), CIRCTYPE(0), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_COORDINATESYSTEM(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 8;
      MC_MOVE_1.ACTPOSITION = DISTANCE;
      MC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      MC_MOVE_1.CIRCHP = CIRCHP;
      MC_MOVE_1.ABSOLUTEVELOCITY = VELOCITY;
      MC_MOVE_1.ABSOLUTEACCELERATION = ACCELERATION;
      MC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      MC_MOVE_1.ORITYPE = ORITYPE;
      MC_MOVE_1.CIRCTYPE = CIRCTYPE;
      MC_MOVE_1.CIRCANGLE = ANGLE;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVEDIRECTABSOLUTE
 ******************************************************************************/
class MC_MOVEDIRECTABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6POS ACTPOSITION;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   PLCIEC::INT M_ORITYPE;

public:
   MC_MOVEDIRECTABSOLUTE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), ACTPOSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_CIRCHP(), M_AXISPOSITION(), M_ORITYPE(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 1;
      MC_MOVE_1.ACTPOSITION = ACTPOSITION;
      MC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      MC_MOVE_1.CIRCHP = M_CIRCHP;
      MC_MOVE_1.VELOCITY = VELOCITY;
      MC_MOVE_1.ACCELERATION = ACCELERATION;
      MC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      MC_MOVE_1.ORITYPE = M_ORITYPE;
      MC_MOVE_1.CIRCTYPE = 0;
      MC_MOVE_1.CIRCANGLE = 0;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVEDIRECTRELATIVE
 ******************************************************************************/
class MC_MOVEDIRECTRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6POS DISTANCE;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   PLCIEC::INT M_ORITYPE;

public:
   MC_MOVEDIRECTRELATIVE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), DISTANCE(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_CIRCHP(), M_AXISPOSITION(), M_ORITYPE(0)
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 6;
      MC_MOVE_1.ACTPOSITION = DISTANCE;
      MC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      MC_MOVE_1.CIRCHP = M_CIRCHP;
      MC_MOVE_1.VELOCITY = VELOCITY;
      MC_MOVE_1.ACCELERATION = ACCELERATION;
      MC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      MC_MOVE_1.ORITYPE = M_ORITYPE;
      MC_MOVE_1.CIRCTYPE = 0;
      MC_MOVE_1.CIRCANGLE = 0;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(FALSE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(FALSE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVELINEARABSOLUTE
 ******************************************************************************/
class MC_MOVELINEARABSOLUTE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6POS ACTPOSITION;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVELINEARABSOLUTE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), ACTPOSITION(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_CIRCHP(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 2;
      MC_MOVE_1.ACTPOSITION = ACTPOSITION;
      MC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      MC_MOVE_1.CIRCHP = M_CIRCHP;
      MC_MOVE_1.ABSOLUTEVELOCITY = VELOCITY;
      MC_MOVE_1.ABSOLUTEACCELERATION = ACCELERATION;
      MC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      MC_MOVE_1.ORITYPE = ORITYPE;
      MC_MOVE_1.CIRCTYPE = 0;
      MC_MOVE_1.CIRCANGLE = 0;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVELINEARRELATIVE
 ******************************************************************************/
class MC_MOVELINEARRELATIVE
{

   /* VAR_INPUT */

public:
   PLCIEC::INT AXISGROUPIDX;
   PLCIEC::BOOL EXECUTE;
   E6POS DISTANCE;
   PLCIEC::REAL VELOCITY;
   PLCIEC::REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   PLCIEC::INT ORITYPE;
   APO APPROXIMATE;
   PLCIEC::INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const PLCIEC::BOOL &COMACPT;
   const PLCIEC::BOOL &COMBUSY;
   const PLCIEC::BOOL &BUSY;
   const PLCIEC::BOOL &ACTIVE;
   const PLCIEC::BOOL &DONE;
   const PLCIEC::BOOL &COMMANDABORTED;
   const PLCIEC::BOOL &ERROR;
   const PLCIEC::DINT &ERRORID;
   const PLCIEC::DINT &ORDERID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   PLCIEC::BOOL _COMACPT;
   PLCIEC::BOOL _COMBUSY;
   PLCIEC::BOOL _BUSY;
   PLCIEC::BOOL _ACTIVE;
   PLCIEC::BOOL _DONE;
   PLCIEC::BOOL _COMMANDABORTED;
   PLCIEC::BOOL _ERROR;
   PLCIEC::DINT _ERRORID;
   PLCIEC::DINT _ORDERID;

   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVELINEARRELATIVE()
       : AXISGROUPIDX(0), EXECUTE(static_cast<PLCIEC::BOOL>(FALSE)), DISTANCE(), VELOCITY(0), ACCELERATION(0), COORDINATESYSTEM(), ORITYPE(0), APPROXIMATE(), QUEUEMODE(0), COMACPT(_COMACPT), COMBUSY(_COMBUSY), BUSY(_BUSY), ACTIVE(_ACTIVE), DONE(_DONE), COMMANDABORTED(_COMMANDABORTED), ERROR(_ERROR), ERRORID(_ERRORID), ORDERID(_ORDERID), _COMACPT(static_cast<PLCIEC::BOOL>(FALSE)), _COMBUSY(static_cast<PLCIEC::BOOL>(FALSE)), _BUSY(static_cast<PLCIEC::BOOL>(FALSE)), _ACTIVE(static_cast<PLCIEC::BOOL>(FALSE)), _DONE(static_cast<PLCIEC::BOOL>(FALSE)), _COMMANDABORTED(static_cast<PLCIEC::BOOL>(FALSE)), _ERROR(static_cast<PLCIEC::BOOL>(FALSE)), _ERRORID(0), _ORDERID(0), MC_MOVE_1(), M_CIRCHP(), M_AXISPOSITION()
   {
   }

public:
   void OnCycle()
   {
      _ORDERID = static_cast<PLCIEC::DINT>(0);
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = static_cast<PLCIEC::DINT>(506);
         _ERROR = static_cast<PLCIEC::BOOL>(TRUE);
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = static_cast<PLCIEC::DINT>(1);
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 5;
      MC_MOVE_1.ACTPOSITION = DISTANCE;
      MC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      MC_MOVE_1.CIRCHP = M_CIRCHP;
      MC_MOVE_1.ABSOLUTEVELOCITY = VELOCITY;
      MC_MOVE_1.ABSOLUTEACCELERATION = ACCELERATION;
      MC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      MC_MOVE_1.ORITYPE = ORITYPE;
      MC_MOVE_1.CIRCTYPE = 0;
      MC_MOVE_1.CIRCANGLE = 0;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDY = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDZ = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDA = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDB = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDC = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE1 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE2 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE3 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE4 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE5 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDE6 = static_cast<PLCIEC::BOOL>(TRUE);
      MC_MOVE_1.POSVALIDS = static_cast<PLCIEC::BOOL>(FALSE);
      MC_MOVE_1.POSVALIDT = static_cast<PLCIEC::BOOL>(FALSE);
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != static_cast<PLCIEC::DINT>(0));
      _ORDERID = MC_MOVE_1.ORDERID;
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

/******************************************************************************
 * FUNCTION_BLOCK MXA_VALUESTOCOORDSYS
 ******************************************************************************/
class MXA_VALUESTOCOORDSYS
{

   /* VAR_INPUT */

public:
   PLCIEC::INT TOOL;
   PLCIEC::INT BASE;
   PLCIEC::INT IPO_MODE;

   /* VAR_OUTPUT */

public:
   const COORDSYS &COORDSYS_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   COORDSYS _COORDSYS_1;

public:
   MXA_VALUESTOCOORDSYS()
       : TOOL(0), BASE(0), IPO_MODE(0), COORDSYS_1(_COORDSYS_1), _COORDSYS_1()
   {
   }

public:
   void OnCycle()
   {

      _COORDSYS_1.TOOL = TOOL;
      _COORDSYS_1.BASE = BASE;
      _COORDSYS_1.IPO_MODE = IPO_MODE;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_VALUESTOE6AXIS
 ******************************************************************************/
class MXA_VALUESTOE6AXIS
{

   /* VAR_INPUT */

public:
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

   /* VAR_OUTPUT */

public:
   const E6AXIS &E6AXIS_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   E6AXIS _E6AXIS_1;

public:
   MXA_VALUESTOE6AXIS()
       : A1(0), A2(0), A3(0), A4(0), A5(0), A6(0), E1(0), E2(0), E3(0), E4(0), E5(0), E6(0), E6AXIS_1(_E6AXIS_1), _E6AXIS_1()
   {
   }

public:
   void OnCycle()
   {

      _E6AXIS_1.A1 = A1;
      _E6AXIS_1.A2 = A2;
      _E6AXIS_1.A3 = A3;
      _E6AXIS_1.A4 = A4;
      _E6AXIS_1.A5 = A5;
      _E6AXIS_1.A6 = A6;
      _E6AXIS_1.E1 = E1;
      _E6AXIS_1.E2 = E2;
      _E6AXIS_1.E3 = E3;
      _E6AXIS_1.E4 = E4;
      _E6AXIS_1.E5 = E5;
      _E6AXIS_1.E6 = E6;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_VALUESTOE6POS
 ******************************************************************************/
class MXA_VALUESTOE6POS
{

   /* VAR_INPUT */

public:
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

   /* VAR_OUTPUT */

public:
   const E6POS &E6POS_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   E6POS _E6POS_1;

public:
   MXA_VALUESTOE6POS()
       : X(0), Y(0), Z(0), A(0), B(0), C(0), STATUS(0), TURN(0), E1(0), E2(0), E3(0), E4(0), E5(0), E6(0), E6POS_1(_E6POS_1), _E6POS_1()
   {
   }

public:
   void OnCycle()
   {

      _E6POS_1.X = X;
      _E6POS_1.Y = Y;
      _E6POS_1.Z = Z;
      _E6POS_1.A = A;
      _E6POS_1.B = B;
      _E6POS_1.C = C;
      _E6POS_1.STATUS = STATUS;
      _E6POS_1.TURN = TURN;
      _E6POS_1.E1 = E1;
      _E6POS_1.E2 = E2;
      _E6POS_1.E3 = E3;
      _E6POS_1.E4 = E4;
      _E6POS_1.E5 = E5;
      _E6POS_1.E6 = E6;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_VALUESTOFRAME
 ******************************************************************************/
class MXA_VALUESTOFRAME
{

   /* VAR_INPUT */

public:
   PLCIEC::REAL X;
   PLCIEC::REAL Y;
   PLCIEC::REAL Z;
   PLCIEC::REAL A;
   PLCIEC::REAL B;
   PLCIEC::REAL C;

   /* VAR_OUTPUT */

public:
   const FRAME &FRAME_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   FRAME _FRAME_1;

public:
   MXA_VALUESTOFRAME()
       : X(0), Y(0), Z(0), A(0), B(0), C(0), FRAME_1(_FRAME_1), _FRAME_1()
   {
   }

public:
   void OnCycle()
   {
      _FRAME_1.X = X;
      _FRAME_1.Y = Y;
      _FRAME_1.Z = Z;
      _FRAME_1.A = A;
      _FRAME_1.B = B;
      _FRAME_1.C = C;
   }
};

#endif // MXA_V6_0_1_H
