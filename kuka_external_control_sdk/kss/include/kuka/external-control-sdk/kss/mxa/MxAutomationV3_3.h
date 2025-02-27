/******************************************************************************
;// This material is the exclusive property of KUKA Roboter GmbH.
;// Except as expressly permitted by separate agreement, this material may only
;// be used by members of the development department of KUKA Roboter GmbH for
;// internal development purposes of KUKA Roboter GmbH.
;//
;// Copyright (C) 2013
;// KUKA Roboter GmbH, Germany. All Rights Reserved.
;//
;//*****************************************************************************
;// Datum       Programmierer        Reviewer
;//             Beschreibung
;//-----------------------------------------------------------------------------
;// 01.09.2015  AFr
;//             mxAutmation2.1
;// 22.01.2016  AFr
;//             mxAutmation2.1 multiple improvements and fixes
;// 15.02.2016  AFr
;//             mxAutmation2.1 multiple fixes
;// 11.11.2016  RRolke
;//             Windows support
;// 09.05.2018  Jump Wu
;//				 Update to V3.0.2
;// 09.15.2019  Jump Wu
;//				 Update to V3.1.0
;// 20.07.2020  Jump Wu
;//				 Update to V3.2.0
;// 10.03.2022  TBreitenauer
;//             Update to V3.3.1
;// 14.03.2022  SJ
;//             add active signal for KRC_Abort
;//             add Function block KRC_AbortAdvanced, KRC_ForwardAdvanced, KRC_InverseAdvanced, KRC_JogAdvanced, KRC_TechFunctionAdvanced
;//             add capability to read the positionally accurate robot model in KRC_Initialize
;// 02.06.2022 CCW
;//             added KRC_LDDCONFIG, KRC_LDDSTART, KRC_LDDTEST & KRC_LDDWRITELOAD
;// 22.06.2022 CCW
;//             added KRC_ACTIVATEPOSCONVERSION & KRC_CONVDELWPS
;// 07.07.2022 CCW
;//             improvements and fixes
;// 11.04.2023 SJ
;//            Bugfixing 977033， 987045
;// 28.06.2023 SJ
;//            Bugfixing 1007278
 ******************************************************************************/

// TODO check licensing

#ifndef MXA_V331_H
#define MXA_V331_H

#include "plciec.h"


typedef REAL MXA_CMD_PAR_REAL[101];

typedef DINT MXA_CMD_PAR_INT[51];

typedef BOOL MXA_CMD_PAR_BOOL[51];

struct MXA_COMMAND
{
   DINT COMMANDID;

   DINT ORDERID;

   DINT BUFFERMODE;

   INT COMMANDSIZE;

   MXA_CMD_PAR_REAL CMDPARREAL;

   MXA_CMD_PAR_INT CMDPARINT;

   MXA_CMD_PAR_BOOL CMDPARBOOL;

};


struct MXA_CMD_STATE_RET
{
   DINT SR_ORDERID;

   INT SR_STATE;

};


typedef MXA_CMD_STATE_RET MXA_CMD_SR_ARR[11];

typedef REAL MXA_CMD_DATA_RET[13];

struct MXA_COMMAND_STATUS
{
   DINT CMDIDRET;

   DINT ORDERIDRET;

   INT TRANSMISSIONNORET;

   MXA_CMD_SR_ARR STATERETURN;

   MXA_CMD_DATA_RET CMDDATARETURN;

   DINT CMDDATARETCSKRC;

   DINT CMDDATARETCSPLC;

};


struct MXA_AUTEXT_CONTROL
{
   BYTE PGNO;

   BOOL PGNO_PARITY;

   BOOL PGNO_VALID;

   BOOL EXT_START;

   BOOL MOVE_ENABLE;

   BOOL MOVE_DISABLE;

   BOOL CONF_MESS;

   BOOL DRIVESON;

   BOOL DRIVESOFF;

   BOOL BRAKETEST_REQ_EXT;

   BOOL MASTERINGTEST_REQ_EXT;

};


struct MXA_AUTEXT_STATE
{
   BOOL RC_RDY1;

   BOOL ALARM_STOP;

   BOOL USER_SAFE;

   BOOL PERI_RDY;

   BOOL ROB_CAL;

   BOOL IO_ACTCONF;

   BOOL STOPMESS;

   BOOL PGNO_FBIT_REFL;

   BOOL INTNOTAUS;

   BOOL PRO_ACT;

   BOOL PGNO_REQ;

   BOOL APPL_RUN;

   BOOL PRO_MOVE;

   BOOL IN_HOME;

   BOOL ON_PATH;

   BOOL NEAR_POSRET;

   BOOL ROB_STOPPED;

   BOOL T1;

   BOOL T2;

   BOOL AUT;

   BOOL EXT;

   BOOL KCP_CONNECT;

   BOOL BRAKETEST_MONTIME;

   BOOL BRAKETEST_REQ_INT;

   BOOL BRAKETEST_WORK;

   BOOL BRAKES_OK;

   BOOL BRAKETEST_WARN;

   BOOL MASTERINGTEST_REQ_INT;

   BOOL MASTERINGTESTSWITCH_OK;

};


struct E6POS
{
   REAL X;

   REAL Y;

   REAL Z;

   REAL A;

   REAL B;

   REAL C;

   INT STATUS;

   INT TURN;

   REAL E1;

   REAL E2;

   REAL E3;

   REAL E4;

   REAL E5;

   REAL E6;

};


struct E6AXIS
{
   REAL A1;

   REAL A2;

   REAL A3;

   REAL A4;

   REAL A5;

   REAL A6;

   REAL E1;

   REAL E2;

   REAL E3;

   REAL E4;

   REAL E5;

   REAL E6;

};


typedef INT MXA_IR_STATE[9];

struct MXA_KRC_STATE
{
   E6POS POSACT;

   INT TOOLACT;

   INT BASEACT;

   INT IPOMODEACT;

   BOOL POSACTVALID;

   E6AXIS AXISACT;

   BOOL AXISACTVALID;

   INT OVPROACT;

   REAL VELACT;

   BOOL BRAKEACTIVE;

   INT WORKSTATES;

   INT AXWORKSTATES;

   INT GROUPSTATE;

   DINT ERRORID;

   DINT ERRORIDSUB;

   DINT ERRORIDPCOS;

   DINT ACTIVEPOSORDERID;

   DINT ACTIVEORDERIDB;

   INT HEARTBEAT;

   INT HEARTBEATPCOS;

   MXA_IR_STATE INTERRUPTSTATE;

   INT QUEUECOUNT;

   BOOL TOUCHUP;

   INT TOUCHUP_INDEX;

   INT IN_VAL_1TO8;

   BOOL ABORTACTIVE;

};

struct MXA_JOGADVANCED
{
   BOOL JOG_AD_ACTIVE;

   INT JOG_AD_STATE_VAL;

 };

struct MXA_KRC_CONTROL
{
   BOOL RESET;

   INT OVERRIDE;

   BOOL BRAKE;

   BOOL BRAKEF;

   BOOL RELEASEBRAKE;

   BOOL SHOWTRACE;

   BOOL MESSAGERESET;

   BOOL OUT_VAL_1;

   BOOL OUT_VAL_2;

   BOOL OUT_VAL_3;

   BOOL OUT_VAL_4;

   BOOL OUT_VAL_5;

   BOOL OUT_VAL_6;

   BOOL OUT_VAL_7;

   BOOL OUT_VAL_8;

   BOOL WRITE_OUT_1TO8;

};


struct AXIS_GROUP_REF
{
   BOOL INITIALIZED;

   BOOL ONLINE;

   DINT LASTORDERID;

   BOOL READAXISGROUPINIT;

   BOOL READDONE;

   DINT INTERRORID;

   DINT INTFBERRORID;

   DINT HEARTBEATTO;

   DINT PLC_MAJOR;

   DINT PLC_MINOR;

   REAL DEF_VEL_CP;

   REAL DEF_ACC_CP;

   MXA_COMMAND COMMAND;

   MXA_COMMAND_STATUS CMDSTATE;

   MXA_AUTEXT_CONTROL AUTEXTCONTROL;

   MXA_AUTEXT_STATE AUTEXTSTATE;

   MXA_KRC_STATE KRCSTATE;

   MXA_KRC_CONTROL KRCCONTROL;

   MXA_JOGADVANCED JOG_ADVANCED;

};


typedef AXIS_GROUP_REF AXIS_GROUP_REF_ARR[6];

/******************************************************************************
 * GLOBAL Variable List
 ******************************************************************************/
//AXIS_GROUP_REF_ARR KRC_AXISGROUPREFARR;
extern AXIS_GROUP_REF KRC_AXISGROUPREFARR[];

extern DINT TESTCNT;

extern DINT TESTCNTR;

extern DINT TESTCNTW;



struct APO
{
   INT PTP_MODE;

   INT CP_MODE;

   INT CPTP;

   REAL CDIS;

   REAL CORI;

   INT CVEL;

};


struct AXBOX
{
   REAL A1_N;

   REAL A2_N;

   REAL A3_N;

   REAL A4_N;

   REAL A5_N;

   REAL A6_N;

   REAL A1_P;

   REAL A2_P;

   REAL A3_P;

   REAL A4_P;

   REAL A5_P;

   REAL A6_P;

   REAL E1_N;

   REAL E2_N;

   REAL E3_N;

   REAL E4_N;

   REAL E5_N;

   REAL E6_N;

   REAL E1_P;

   REAL E2_P;

   REAL E3_P;

   REAL E4_P;

   REAL E5_P;

   REAL E6_P;

};


typedef INT AXIS_VEL[13];

typedef BOOL BOOL_ARRAY_40[41];

struct BOX
{
   REAL X;

   REAL Y;

   REAL Z;

   REAL A;

   REAL B;

   REAL C;

   REAL X1;

   REAL X2;

   REAL Y1;

   REAL Y2;

   REAL Z1;

   REAL Z2;

};


struct COORDSYS
{
   INT TOOL;

   INT BASE;

   INT IPO_MODE;

};


struct FRAME
{
   REAL X;

   REAL Y;

   REAL Z;

   REAL A;

   REAL B;

   REAL C;

};


typedef DINT INT32_ARRAY_40[41];

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


typedef BOOL MXA_SYNC_IO[2033];

struct POSITION1
{
   COORDSYS COORDSYS_1;

   E6POS E6POS_1;

   E6AXIS E6AXIS_1;

};


typedef POSITION1 POSITION_ARRAY[101];

typedef REAL REAL_ARRAY_40[41];

typedef REAL REAL_ARRAY_12[13];


/******************************************************************************
 * FUNCTION MXA_GETIO_BYTE
 ******************************************************************************/
inline BOOL MXA_GETIO_BYTE(
	_IN    INT BYTEPOS,
    _IN    BYTE* KRC4_INPUT,
    _OUT   INT & O)
{
   BOOL MXA_GETIO_BYTE = (BOOL)FALSE;


   O = BYTE_TO_INT(KRC4_INPUT[BYTEPOS]);
   return MXA_GETIO_BYTE;
}


/******************************************************************************
 * FUNCTION MXA_GETIO_DINT
 ******************************************************************************/
inline BOOL MXA_GETIO_DINT(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_INPUT,
    _OUT   DINT & O)
{
   DWORD DW = 0;
   BOOL MXA_GETIO_DINT = (BOOL)FALSE;


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
   O = DWORD_TO_DINT(DW);
   return MXA_GETIO_DINT;
}


/******************************************************************************
 * FUNCTION MXA_GETIO_INT
 ******************************************************************************/
inline BOOL MXA_GETIO_INT(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_INPUT,
    _OUT   INT & O)
{
   WORD W = 0;
   BOOL MXA_GETIO_INT = (BOOL)FALSE;


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
   O = WORD_TO_INT(W);
   return MXA_GETIO_INT;
}


/******************************************************************************
 * FUNCTION MXA_GETIO_NIBBLE
 ******************************************************************************/
inline BOOL MXA_GETIO_NIBBLE(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_INPUT,
    _OUT   INT & N1,
    _OUT   INT & N2)
{
   BYTE B = 0;
   BYTE B1 = 0;
   BYTE B2 = 0;
   BOOL MXA_GETIO_NIBBLE = (BOOL)FALSE;


   B = KRC4_INPUT[BYTEPOS];
   ChBit(B1, 0, /* := */ IsBitSet(B, 0));
   ChBit(B1, 1, /* := */ IsBitSet(B, 1));
   ChBit(B1, 2, /* := */ IsBitSet(B, 2));
   ChBit(B1, 3, /* := */ IsBitSet(B, 3));
   ChBit(B2, 0, /* := */ IsBitSet(B, 4));
   ChBit(B2, 1, /* := */ IsBitSet(B, 5));
   ChBit(B2, 2, /* := */ IsBitSet(B, 6));
   ChBit(B2, 3, /* := */ IsBitSet(B, 7));
   N1 = BYTE_TO_INT(B1);
   N2 = BYTE_TO_INT(B2);
   return MXA_GETIO_NIBBLE;
}


/******************************************************************************
 * FUNCTION MXA_GETIO_REAL
 ******************************************************************************/
inline BOOL MXA_GETIO_REAL(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_INPUT,
    _OUT   REAL & O)
{
   REAL* PDW;
   BOOL MXA_GETIO_REAL = (BOOL)FALSE;


   PDW = reinterpret_cast<REAL*>(&(KRC4_INPUT[BYTEPOS]));
   O = *PDW;
   return MXA_GETIO_REAL;
}


/******************************************************************************
 * FUNCTION MXA_GETIO_SINT
 ******************************************************************************/
inline BOOL MXA_GETIO_SINT(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_INPUT,
    _OUT   SINT & O)
{
   BYTE B = 0;
   BOOL MXA_GETIO_SINT = (BOOL)FALSE;


   B = KRC4_INPUT[BYTEPOS];
   O = BYTE_TO_SINT(B);
   return MXA_GETIO_SINT;
}


/******************************************************************************
 * FUNCTION MXA_WRITEIO_BYTE
 ******************************************************************************/
inline BOOL MXA_WRITEIO_BYTE(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_OUTPUT,
    _IN    INT VAL)
{
   BOOL MXA_WRITEIO_BYTE = (BOOL)FALSE;


   KRC4_OUTPUT[BYTEPOS] = INT_TO_BYTE(VAL);
   return MXA_WRITEIO_BYTE;
}


/******************************************************************************
 * FUNCTION MXA_WRITEIO_DINT
 ******************************************************************************/
inline BOOL MXA_WRITEIO_DINT(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_OUTPUT,
    _IN    DINT VAL)
{
   BOOL MXA_WRITEIO_DINT = (BOOL)FALSE;


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
inline BOOL MXA_WRITEIO_DWORD(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_OUTPUT,
    _IN    DWORD VAL)
{
   BOOL MXA_WRITEIO_DWORD = (BOOL)FALSE;


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
inline BOOL MXA_WRITEIO_REAL(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_OUTPUT,
    _IN    REAL VAL)
{
   REAL* PDW;
   BOOL MXA_WRITEIO_REAL = (BOOL)FALSE;


   PDW = reinterpret_cast<REAL*>(&(KRC4_OUTPUT[BYTEPOS]));
   *PDW = VAL;
   return MXA_WRITEIO_REAL;
}


/******************************************************************************
 * FUNCTION MXA_WRITEIO_WORD
 ******************************************************************************/
inline BOOL MXA_WRITEIO_WORD(
    _IN    INT BYTEPOS,
    _IN    BYTE* KRC4_OUTPUT,
    _IN    WORD VAL)
{
   BOOL MXA_WRITEIO_WORD = (BOOL)FALSE;


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
   INT AXISGROUPIDX;


   /* VAR */

private:
   INT I;

public:
   MXA_RESETCOMMAND()
      : I(0)
      , AXISGROUPIDX(0)
   {}

public:
   void OnCycle()
   {

      for (I = 1; I <= 50; I += 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] = (BOOL)FALSE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I] = (DINT)0;
      };
      for (I = 1; I <= 100; I += 1)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = 0.0;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = (DINT)0;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = (DINT)0;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = (DINT)0;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = (INT)0;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_GETORDERSTATE
 ******************************************************************************/
class MXA_GETORDERSTATE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   DINT ORDERID;

   /* VAR_OUTPUT */

public:
   const INT &ORDERSTATE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   INT _ORDERSTATE;


   /* VAR */

private:
   INT I;
   INT M_ORDERSTATE;

public:
   MXA_GETORDERSTATE()
      : I(0)
      , AXISGROUPIDX(0)
      , ORDERID(0)
      , ORDERSTATE(_ORDERSTATE)
      , _ORDERSTATE(0)
     , M_ORDERSTATE(0)
   {}

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
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   DINT CMDID;
   INT BUFFERMODE;
   INT COMMANDSIZE;
   BOOL ENABLEDIRECTEXE;
   BOOL ENABLEQUEUEEXE;
   BOOL IGNOREINIT;

   /* VAR_OUTPUT */

public:
   const BOOL &WRITECMDPAR;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &CMDSPECIFIC1;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const BOOL &READCMDDATARET;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _WRITECMDPAR;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _CMDSPECIFIC1;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;
   BOOL _READCMDDATARET;


   /* VAR */

private:
   MXA_RESETCOMMAND RESETCOMMAND_1;
   MXA_GETORDERSTATE GETORDERSTATE_1;
   INT M_STATE;
   DINT M_ORDERID;
   BOOL M_EXECUTELAST;
   BOOL M_RE_EXECUTE;
   INT M_COMMANDSIZE;

public:
   MXA_EXECUTECOMMAND()
      : RESETCOMMAND_1()
      , GETORDERSTATE_1()
      , M_STATE(0)
      , M_ORDERID(0)
      , M_EXECUTELAST((BOOL)FALSE)
      , M_RE_EXECUTE((BOOL)FALSE)
      , M_COMMANDSIZE(0)
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , CMDID(0)
      , BUFFERMODE(0)
      , COMMANDSIZE(0)
      , ENABLEDIRECTEXE((BOOL)FALSE)
      , ENABLEQUEUEEXE((BOOL)FALSE)
      , IGNOREINIT((BOOL)FALSE)
      , WRITECMDPAR(_WRITECMDPAR)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , CMDSPECIFIC1(_CMDSPECIFIC1)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , READCMDDATARET(_READCMDDATARET)
      , _WRITECMDPAR((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _CMDSPECIFIC1((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _READCMDDATARET((BOOL)FALSE)
   {}

public:
   void OnCycle()
   {

      M_RE_EXECUTE = ((EXECUTE == (BOOL)TRUE) && (M_EXECUTELAST == (BOOL)FALSE));
      M_EXECUTELAST = EXECUTE;
      _WRITECMDPAR = (BOOL)FALSE;
      _READCMDDATARET = (BOOL)FALSE;
      if (!(EXECUTE))
      {
         M_STATE = 0;
         M_ORDERID = (DINT)0;
         _ERRORID = (DINT)0;
      };
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
      }
      else
      {
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE))
         {
            _ERRORID = (DINT)507;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT))
         {
            _ERRORID = (DINT)508;
         };
      };
      if ((M_RE_EXECUTE && (_ERRORID == (DINT)0)))
      {
         M_STATE = 1;
         if ((((BUFFERMODE == 0) && (ENABLEDIRECTEXE == (BOOL)FALSE)) || ((BUFFERMODE > 0) && (ENABLEQUEUEEXE == (BOOL)FALSE))))
         {
            _ERRORID = (DINT)502;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            if (!(IGNOREINIT))
            {
               _ERRORID = (DINT)508;
            };
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            _ERRORID = (DINT)509;
         };
      };
      if (((M_STATE == 1) && (_ERRORID == (DINT)0)))
      {
         if (M_RE_EXECUTE)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID + (DINT)1);
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID >= (DINT)2147483647))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (DINT)1;
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
                     _READCMDDATARET = (BOOL)TRUE;
                  }
                  else
                  {
                     M_STATE = 5;
                  };
               }
               else
               {
                  _ERRORID = (DINT)512;
               };
            }
            else
            {
               _ERRORID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET * (DINT) -(1));
            };
            // Call FB ResetCommand_1
            RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
            RESETCOMMAND_1.OnCycle();
         }
         else
         {
            if (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == (DINT)0) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID == (DINT)0)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED || IGNOREINIT)))
            {
               if (((BUFFERMODE < 2) || (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.QUEUECOUNT < 80)))
               {
                  // Call FB ResetCommand_1
                  RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
                  RESETCOMMAND_1.OnCycle();
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = M_ORDERID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = CMDID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = INT_TO_DINT(BUFFERMODE);
                  M_COMMANDSIZE = COMMANDSIZE;
                  if (((COMMANDSIZE < 1) || (COMMANDSIZE > 3)))
                  {
                     _ERRORID = (DINT)517;
                     M_COMMANDSIZE = 3;
                  };
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = M_COMMANDSIZE;
                  _WRITECMDPAR = (BOOL)TRUE;
               };
            };
         };
      };
      if ((((M_STATE > 1) && (M_STATE < 15)) && (_ERRORID == (DINT)0)))
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
      if ((_ERRORID != (DINT)0))
      {
         M_STATE = (DINT_TO_INT(_ERRORID) *  -(1));
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _BUSY = (M_STATE > 1);
      _ACTIVE = (M_STATE == 10);
      _DONE = (M_STATE == 15);
      _CMDSPECIFIC1 = (M_STATE == 25);
      _ABORTED = (M_STATE == 20);
      _ERROR = (M_STATE < 0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ABORT
 ******************************************************************************/
class KRC_ABORT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_ABORT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)2;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ABORTACTIVE;
      _DONE = (MXA_EXECUTECOMMAND_1.DONE || MXA_EXECUTECOMMAND_1.ABORTED);
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ABORTADVANCED
 ******************************************************************************/
class KRC_ABORTADVANCED
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT BRAKEREACTION;
   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   INT NSTATE;
public:
   KRC_ABORTADVANCED()
      : MXA_EXECUTECOMMAND_1()
      , NSTATE(0)
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , BRAKEREACTION(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)58;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ACTIVATECONVINTERRUPT
 ******************************************************************************/
class KRC_ACTIVATECONVINTERRUPT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT CONVEYORNUMBER;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_ACTIVATECONVINTERRUPT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , CONVEYORNUMBER(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)46;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ACTIVATEINTERRUPT
 ******************************************************************************/
class KRC_ACTIVATEINTERRUPT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT INTERRUPT;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_ACTIVATEINTERRUPT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , INTERRUPT(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)6;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(INTERRUPT);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_AUTOMATICEXTERNAL
 ******************************************************************************/
class KRC_AUTOMATICEXTERNAL
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL MOVE_ENABLE;
   BOOL CONF_MESS;
   BOOL DRIVES_ON;
   BOOL DRIVES_OFF;
   BOOL EXT_START;
   BOOL RESET;
   BOOL ENABLE_T1;
   BOOL ENABLE_T2;
   BOOL ENABLE_AUT;
   BOOL ENABLE_EXT;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const BOOL &RC_RDY1;
   const BOOL &ALARM_STOP;
   const BOOL &USER_SAFE;
   const BOOL &PERI_RDY;
   const BOOL &ROB_CAL;
   const BOOL &IO_ACTCONF;
   const BOOL &STOPMESS;
   const BOOL &INT_E_STOP;
   const BOOL &PRO_ACT;
   const BOOL &APPL_RUN;
   const BOOL &PRO_MOVE;
   const BOOL &ON_PATH;
   const BOOL &NEAR_POSRET;
   const BOOL &ROB_STOPPED;
   const BOOL &T1;
   const BOOL &T2;
   const BOOL &AUT;
   const BOOL &EXT;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   BOOL _RC_RDY1;
   BOOL _ALARM_STOP;
   BOOL _USER_SAFE;
   BOOL _PERI_RDY;
   BOOL _ROB_CAL;
   BOOL _IO_ACTCONF;
   BOOL _STOPMESS;
   BOOL _INT_E_STOP;
   BOOL _PRO_ACT;
   BOOL _APPL_RUN;
   BOOL _PRO_MOVE;
   BOOL _ON_PATH;
   BOOL _NEAR_POSRET;
   BOOL _ROB_STOPPED;
   BOOL _T1;
   BOOL _T2;
   BOOL _AUT;
   BOOL _EXT;


public:
   KRC_AUTOMATICEXTERNAL()
      : AXISGROUPIDX(0)
      , MOVE_ENABLE((BOOL)FALSE)
      , CONF_MESS((BOOL)FALSE)
      , DRIVES_ON((BOOL)FALSE)
      , DRIVES_OFF((BOOL)FALSE)
      , EXT_START((BOOL)FALSE)
      , RESET((BOOL)FALSE)
      , ENABLE_T1((BOOL)FALSE)
      , ENABLE_T2((BOOL)FALSE)
      , ENABLE_AUT((BOOL)FALSE)
      , ENABLE_EXT((BOOL)FALSE)
      , VALID(_VALID)
      , RC_RDY1(_RC_RDY1)
      , ALARM_STOP(_ALARM_STOP)
      , USER_SAFE(_USER_SAFE)
      , PERI_RDY(_PERI_RDY)
      , ROB_CAL(_ROB_CAL)
      , IO_ACTCONF(_IO_ACTCONF)
      , STOPMESS(_STOPMESS)
      , INT_E_STOP(_INT_E_STOP)
      , PRO_ACT(_PRO_ACT)
      , APPL_RUN(_APPL_RUN)
      , PRO_MOVE(_PRO_MOVE)
      , ON_PATH(_ON_PATH)
      , NEAR_POSRET(_NEAR_POSRET)
      , ROB_STOPPED(_ROB_STOPPED)
      , T1(_T1)
      , T2(_T2)
      , AUT(_AUT)
      , EXT(_EXT)
      , _VALID((BOOL)FALSE)
      , _RC_RDY1((BOOL)FALSE)
      , _ALARM_STOP((BOOL)FALSE)
      , _USER_SAFE((BOOL)FALSE)
      , _PERI_RDY((BOOL)FALSE)
      , _ROB_CAL((BOOL)FALSE)
      , _IO_ACTCONF((BOOL)FALSE)
      , _STOPMESS((BOOL)FALSE)
      , _INT_E_STOP((BOOL)FALSE)
      , _PRO_ACT((BOOL)FALSE)
      , _APPL_RUN((BOOL)FALSE)
      , _PRO_MOVE((BOOL)FALSE)
      , _ON_PATH((BOOL)FALSE)
      , _NEAR_POSRET((BOOL)FALSE)
      , _ROB_STOPPED((BOOL)FALSE)
      , _T1((BOOL)FALSE)
      , _T2((BOOL)FALSE)
      , _AUT((BOOL)FALSE)
      , _EXT((BOOL)FALSE)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = (BOOL)FALSE;
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (BOOL)TRUE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESOFF = DRIVES_OFF;
      if (DRIVES_ON)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (BOOL)TRUE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.EXT_START = EXT_START;
      if (RESET)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = (BOOL)TRUE;
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
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READMXAERROR()
      : AXISGROUPIDX(0)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID;
      if ((_ERRORID == (DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB;
      };
      if ((_ERRORID == (DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDPCOS;
      };
      if ((_ERRORID == (DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID;
      };
      if ((_ERRORID == (DINT)0))
      {
         _ERRORID = KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID;
      };
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MESSAGERESET
 ******************************************************************************/
class KRC_MESSAGERESET
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL MESSAGERESET;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR_TEMP */

private:
   INT I;

public:
   KRC_MESSAGERESET()
      : AXISGROUPIDX(0)
      , MESSAGERESET((BOOL)FALSE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , I(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      _ERRORID = (DINT)0;
      _ERROR = (BOOL)FALSE;
      if (MESSAGERESET)
      {
         if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == (DINT)565))
         {
            for (I = 1; I <= 100; I += 1)
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I] = 0.0;
            };
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET = MESSAGERESET;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = (DINT)0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = (DINT)0;
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
   INT AXISGROUPIDX;
   BOOL EXECUTERESET;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &DISPACTIVE;
   const BOOL &RESETVALID;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _DISPACTIVE;
   BOOL _RESETVALID;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   DINT M_STATE;
   BOOL M_CONFMESS;
   BOOL M_RESET;
   BOOL M_RE_EXECUTERESET;
   BOOL M_EXECUTERESETLAST;
   KRC_READMXAERROR KRC_READMXAERROR_1;
   KRC_MESSAGERESET KRC_MESSAGERESET_1;
   TON TON_ON;
   TON TON_OFF;
   TON TON_1;
   TON TON_2;
   TON TON_3;
   TON TON_4;

public:
   KRC_AUTOSTART()
      : M_STATE(0)
      , M_CONFMESS((BOOL)FALSE)
      , M_RESET((BOOL)FALSE)
      , M_RE_EXECUTERESET((BOOL)FALSE)
      , M_EXECUTERESETLAST((BOOL)FALSE)
      , KRC_READMXAERROR_1()
      , KRC_MESSAGERESET_1()
      , TON_ON()
      , TON_OFF()
      , TON_1()
      , TON_2()
      , TON_3()
      , TON_4()
      , AXISGROUPIDX(0)
      , EXECUTERESET((BOOL)FALSE)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , DISPACTIVE(_DISPACTIVE)
      , RESETVALID(_RESETVALID)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _DISPACTIVE((BOOL)FALSE)
      , _RESETVALID((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      _DISPACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT;
      _RESETVALID = (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && !(_DISPACTIVE)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP) && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE);
      if (!(EXECUTERESET))
      {
         M_STATE = 0;
         _ERRORID = (DINT)0;
      };
      M_RE_EXECUTERESET = ((EXECUTERESET == (BOOL)TRUE) && (M_EXECUTERESETLAST == (BOOL)FALSE));
      M_EXECUTERESETLAST = EXECUTERESET;
      // Call FB KRC_ReadMXAError_1
      KRC_READMXAERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_READMXAERROR_1.OnCycle();
      M_CONFMESS = (BOOL)FALSE;
      M_RESET = (BOOL)FALSE;
      _DONE = (BOOL)FALSE;
      switch (M_STATE)
      {
         case 0:
            if (M_RE_EXECUTERESET)
            {
               if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
               {
                  _ERRORID = (DINT)508;
               };
               if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
               {
                  _ERRORID = (DINT)509;
               };
               if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.EXT))
               {
                  _ERRORID = (DINT)523;
               };
               if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.USER_SAFE))
               {
                  _ERRORID = (DINT)524;
               };
               if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ALARM_STOP))
               {
                  _ERRORID = (DINT)525;
               };
               if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_ACT)
               {
                  _ERRORID = (DINT)526;
               };
               if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE))
               {
                  _ERRORID = (DINT)532;
               };
               if ((_ERRORID == (DINT)0))
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
            if ((KRC_READMXAERROR_1.ERRORID == (DINT)0))
            {
               M_STATE = 2;
            };
            // Call FB KRC_MessageReset_1
            KRC_MESSAGERESET_1.AXISGROUPIDX = AXISGROUPIDX;
            KRC_MESSAGERESET_1.MESSAGERESET = (BOOL)TRUE;
            KRC_MESSAGERESET_1.OnCycle();
            break;
         case 2:
            if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY)
            {
               M_STATE = 3;
            }
            else
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (BOOL)TRUE;
            };
            break;
         case 3:
            if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS)
            {
               M_CONFMESS = (BOOL)TRUE;
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
               M_RESET = (BOOL)TRUE;
            };
            break;
         case 5:
            _DONE = (BOOL)TRUE;
            if (!(EXECUTERESET))
            {
               M_STATE = 0;
            };
            break;
      };
      // Call FB TON_ON
      TON_ON.IN = ((M_CONFMESS || M_RESET) && !(TON_OFF.Q));
      TON_ON.PT = MKTIME(1, 200);
      TON_ON.OnCycle();
      // Call FB TON_OFF
      TON_OFF.IN = ((M_CONFMESS || M_RESET) && TON_ON.Q);
      TON_OFF.PT = MKTIME(1, 100);
      TON_OFF.OnCycle();
      if ((M_CONFMESS && !(TON_ON.Q)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (BOOL)TRUE;
      };
      if ((M_RESET && !(TON_ON.Q)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = (BOOL)TRUE;
      };
      // Call FB TON_1
      TON_1.IN = (M_STATE == 1);
      TON_1.PT = MKTIME(1, 0, 5);
      TON_1.OnCycle();
      // Call FB TON_2
      TON_2.IN = (M_STATE == 2);
      TON_2.PT = MKTIME(1, 0, 5);
      TON_2.OnCycle();
      // Call FB TON_3
      TON_3.IN = (M_STATE == 3);
      TON_3.PT = MKTIME(1, 0, 5);
      TON_3.OnCycle();
      // Call FB TON_4
      TON_4.IN = (M_STATE == 4);
      TON_4.PT = MKTIME(1, 0, 5);
      TON_4.OnCycle();
      if (TON_1.Q)
      {
         _ERRORID = (DINT)528;
      };
      if (TON_2.Q)
      {
         _ERRORID = (DINT)527;
      };
      if (TON_3.Q)
      {
         _ERRORID = (DINT)529;
      };
      if (TON_4.Q)
      {
         _ERRORID = (DINT)531;
      };
      if ((_ERRORID != (DINT)0))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _ERROR = (_ERRORID != (DINT)0);
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
   INT AXISGROUPIDX;
   DINT CMDID;
   BOOL EXECUTECMD;
   INT MOVETYPE;
   E6POS ACTPOSITION;
   E6AXIS AXISPOSITION;
   E6POS CIRCHP;
   INT VELOCITY;
   REAL ABSOLUTEVELOCITY;
   INT ACCELERATION;
   REAL ABSOLUTEACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   INT CIRCTYPE;
   REAL CIRCANGLE;
   APO APPROXIMATE;
   BOOL POSVALIDX;
   BOOL POSVALIDY;
   BOOL POSVALIDZ;
   BOOL POSVALIDA;
   BOOL POSVALIDB;
   BOOL POSVALIDC;
   BOOL POSVALIDE1;
   BOOL POSVALIDE2;
   BOOL POSVALIDE3;
   BOOL POSVALIDE4;
   BOOL POSVALIDE5;
   BOOL POSVALIDE6;
   BOOL POSVALIDS;
   BOOL POSVALIDT;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

   /* VAR_TEMP */

private:
   INT COMMANDSIZE;
   DINT M_VELOCITY;
   DINT M_ACCELERATION;

public:
   KRC_MOVE()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , CMDID((DINT)1)
      , EXECUTECMD((BOOL)FALSE)
      , MOVETYPE(0)
      , ACTPOSITION()
      , AXISPOSITION()
      , CIRCHP()
      , VELOCITY(0)
      , ABSOLUTEVELOCITY(0)
      , ACCELERATION(0)
      , ABSOLUTEACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , CIRCTYPE(0)
      , CIRCANGLE(0)
      , APPROXIMATE()
      , POSVALIDX((BOOL)FALSE)
      , POSVALIDY((BOOL)FALSE)
      , POSVALIDZ((BOOL)FALSE)
      , POSVALIDA((BOOL)FALSE)
      , POSVALIDB((BOOL)FALSE)
      , POSVALIDC((BOOL)FALSE)
      , POSVALIDE1((BOOL)FALSE)
      , POSVALIDE2((BOOL)FALSE)
      , POSVALIDE3((BOOL)FALSE)
      , POSVALIDE4((BOOL)FALSE)
      , POSVALIDE5((BOOL)FALSE)
      , POSVALIDE6((BOOL)FALSE)
      , POSVALIDS((BOOL)FALSE)
      , POSVALIDT((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , COMMANDSIZE(0)
      , M_VELOCITY(0)
      , M_ACCELERATION(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (EXECUTECMD)
      {
         if (((VELOCITY > 0) && (ABSOLUTEVELOCITY > 0.0)))
         {
            _ERRORID = (DINT)520;
            _ERROR = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            return;
         };
       M_VELOCITY = (DINT)VELOCITY;
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
          if ((ABSOLUTEVELOCITY > 0.0))
          {
             _ERRORID = (DINT)519;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          }
          break;
       }
       if ((ABSOLUTEVELOCITY > 0.0))
       {
          if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP <= 0.0))
          {
             _ERRORID = (DINT)544;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          };
          M_VELOCITY = (DINT)REAL_TO_DINT(((ABSOLUTEVELOCITY * -100000.0) / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP));
       };

       M_ACCELERATION = (DINT)ACCELERATION;
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
          if ((ABSOLUTEACCELERATION > 0.0))
          {
             _ERRORID = (DINT)545;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          };
          break;
       };

       if ((ABSOLUTEACCELERATION > 0.0))
       {
          if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP <= 0.0))
          {
             _ERRORID = (DINT)546;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          }
          // Negative area is from 100.000% to 0.001% and positive area is for the integer percent
          M_ACCELERATION = (DINT)(ABSOLUTEACCELERATION * -100000.0 / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP);
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
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
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
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[15] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[16] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[17] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[18] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[19] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[20] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[21] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[22] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[23] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[24] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[25] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[26] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[27] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[28] = (BOOL)TRUE;
         };
         if (((((MOVETYPE == 0) || (MOVETYPE == 10)) || (MOVETYPE == 9)) || (MOVETYPE == 19)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(0);
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(ACTPOSITION.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(ACTPOSITION.TURN);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(COORDINATESYSTEM.TOOL);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(COORDINATESYSTEM.BASE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6] = INT_TO_DINT(MOVETYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[7] = M_VELOCITY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[8] = M_ACCELERATION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[9] = INT_TO_DINT(APPROXIMATE.PTP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[10] = INT_TO_DINT(APPROXIMATE.CP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[11] = INT_TO_DINT(APPROXIMATE.CPTP);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[12] = INT_TO_DINT(APPROXIMATE.CVEL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[13] = INT_TO_DINT(ORITYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[14] = INT_TO_DINT(CIRCTYPE);
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[15] = INT_TO_DINT(CIRCHP.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[16] = INT_TO_DINT(CIRCHP.TURN);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_BRAKETEST
 ******************************************************************************/
class KRC_BRAKETEST
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS PARKPOSITION;
   INT PARKVELOCITY;
   INT PARKACCELERATION;
   COORDSYS PARKCOORDINATESYSTEM;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const DINT &RESULT;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   DINT _RESULT;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_BRAKETEST()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , PARKPOSITION()
      , PARKVELOCITY(0)
      , PARKACCELERATION(0)
      , PARKCOORDINATESYSTEM()
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , RESULT(_RESULT)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _RESULT(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         _RESULT = (DINT)0;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = (DINT)29;
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 1;
      KRC_MOVE_1.ACTPOSITION = PARKPOSITION;
      KRC_MOVE_1.VELOCITY = PARKVELOCITY;
      KRC_MOVE_1.ACCELERATION = PARKACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = PARKCOORDINATESYSTEM;
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKES_OK)
         {
            if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.BRAKETEST_WARN)
            {
               _RESULT = (DINT)1;
            }
            else
            {
               _RESULT = (DINT)2;
            };
         }
         else
         {
            _RESULT = (DINT)0;
         };
      }
      else
      {
         _RESULT = (DINT)0;
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONTINUE
 ******************************************************************************/
class KRC_CONTINUE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL ENABLE;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_CONTINUE()
      : AXISGROUPIDX(0)
      , ENABLE((BOOL)FALSE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      if (ENABLE)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RELEASEBRAKE = ENABLE;
      };
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVDELWPS
 ******************************************************************************/
class KRC_CONVDELWPS
{
    /* VAR_INPUT */

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;
    INT CONVEYORNUMBER;
    INT PIECENUMBER;

    /* VAR_OUTPUT */

public:
    const BOOL& BUSY;
    const BOOL& ACTIVE;
    const BOOL& DONE;
    const BOOL& ABORTED;
    const BOOL& ERROR;
    const DINT& ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _ACTIVE;
    BOOL _DONE;
    BOOL _ABORTED;
    BOOL _ERROR;
    DINT _ERRORID;

    /* VAR */

private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
    KRC_CONVDELWPS()
        : MXA_EXECUTECOMMAND_1()
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , CONVEYORNUMBER(0)
        , PIECENUMBER(0)
        , BUSY(_BUSY)
        , ACTIVE(_ACTIVE)
        , DONE(_DONE)
        , ABORTED(_ABORTED)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _ACTIVE((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ABORTED((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {

        if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
        {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }
        else
        {
            _ERRORID = (DINT)0;
            _ERROR = (BOOL)FALSE;
        };
        // Call FB mxA_ExecuteCommand_1
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)69;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();
        if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
        {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(PIECENUMBER);
        };
        _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
        _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
        _DONE = MXA_EXECUTECOMMAND_1.DONE;
        _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
        _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
        _ERROR = (_ERRORID != (DINT)0);
    }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVFOLLOW
 ******************************************************************************/
class KRC_CONVFOLLOW
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT CONVEYORNUMBER;
   REAL STARTDISTANCE;
   REAL MAXDISTANCE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &MAXDISTANCEREACHED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _MAXDISTANCEREACHED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVFOLLOW()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , CONVEYORNUMBER(0)
      , STARTDISTANCE(0)
      , MAXDISTANCE(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , MAXDISTANCEREACHED(_MAXDISTANCEREACHED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _MAXDISTANCEREACHED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)42;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = STARTDISTANCE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = MAXDISTANCE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _MAXDISTANCEREACHED = MXA_EXECUTECOMMAND_1.CMDSPECIFIC1;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVINIOFF
 ******************************************************************************/
class KRC_CONVINIOFF
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT CONVEYORNUMBER;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVINIOFF()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , CONVEYORNUMBER(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)40;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVON
 ******************************************************************************/
class KRC_CONVON
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT CONVEYORNUMBER;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVON()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , CONVEYORNUMBER(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)41;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_CONVSKIP
 ******************************************************************************/
class KRC_CONVSKIP
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT CONVEYORNUMBER;
   INT PIECENUMBER;
   REAL STARTDISTANCE;
   REAL MAXDISTANCE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &MAXDISTANCEREACHED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _MAXDISTANCEREACHED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_CONVSKIP()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , CONVEYORNUMBER(0)
      , PIECENUMBER(0)
      , STARTDISTANCE(0)
      , MAXDISTANCE(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , MAXDISTANCEREACHED(_MAXDISTANCEREACHED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _MAXDISTANCEREACHED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)43;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(PIECENUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = STARTDISTANCE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = MAXDISTANCE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _MAXDISTANCEREACHED = MXA_EXECUTECOMMAND_1.CMDSPECIFIC1;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DEACTIVATECONVINTERRUPT
 ******************************************************************************/
class KRC_DEACTIVATECONVINTERRUPT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT CONVEYORNUMBER;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_DEACTIVATECONVINTERRUPT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , CONVEYORNUMBER(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)47;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(CONVEYORNUMBER);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DEACTIVATEINTERRUPT
 ******************************************************************************/
class KRC_DEACTIVATEINTERRUPT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT INTERRUPT;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_DEACTIVATEINTERRUPT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , INTERRUPT(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)7;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(INTERRUPT);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DECLAREINTERRUPT
 ******************************************************************************/
class KRC_DECLAREINTERRUPT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT INTERRUPT;
   INT INPUT;
   BOOL INPUTVALUE;
   INT REACTION;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_DECLAREINTERRUPT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , INTERRUPT(0)
      , INPUT(0)
      , INPUTVALUE((BOOL)FALSE)
      , REACTION(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)5;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = INPUTVALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(INTERRUPT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(REACTION);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(INPUT);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_DIAG
 ******************************************************************************/
class KRC_DIAG
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL SHOWTRACE;
   INT MAXSUBMITCYCLE;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const INT &QUEUECOUNT;
   const BOOL &POSACTVALID;
   const BOOL &BRAKEACTIVE;
   const INT &SUBMITHEARTBEAT;
   const INT &SUBMITCYC_ACT;
   const INT &SUBMITCYC_MIN;
   const INT &SUBMITCYC_MAX;
   const INT &SUBMITCYC_AVG;
   const DINT &ACTIVEPOSORDERID;
   const DINT &ACTIVEORDERIDB;
   const DINT &AVG_DURATION;
   const INT &PROCONOSHEARTBEAT;
   const INT &PROCONOSCYC_ACT;
   const INT &PROCONOSCYC_MIN;
   const INT &PROCONOSCYC_MAX;
   const INT &PROCONOSCYC_AVG;
   const DINT &ERRORID_RI;
   const DINT &ERRORID_SI;
   const DINT &ERRORID_PLC;
   const DINT &ERRORID_PCOS;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   INT _QUEUECOUNT;
   BOOL _POSACTVALID;
   BOOL _BRAKEACTIVE;
   INT _SUBMITHEARTBEAT;
   INT _SUBMITCYC_ACT;
   INT _SUBMITCYC_MIN;
   INT _SUBMITCYC_MAX;
   INT _SUBMITCYC_AVG;
   DINT _ACTIVEPOSORDERID;
   DINT _ACTIVEORDERIDB;
   DINT _AVG_DURATION;
   INT _PROCONOSHEARTBEAT;
   INT _PROCONOSCYC_ACT;
   INT _PROCONOSCYC_MIN;
   INT _PROCONOSCYC_MAX;
   INT _PROCONOSCYC_AVG;
   DINT _ERRORID_RI;
   DINT _ERRORID_SI;
   DINT _ERRORID_PLC;
   DINT _ERRORID_PCOS;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   TON TON_1SEC;
   INT HBLAST;
   INT HBCYCDIFF;
   DINT HBSUM;
   DINT CYCLCNT;
   DINT PCOSHBLAST;
   DINT PCOSHBCYCDIFF;
   DINT PCOSHBSUM;
   DINT SECSUM;

   /* VAR_TEMP */

private:
   DINT HBCYCDIFF1000;
   DINT CYCLCNT1000;
   DINT PCOSHBCYCDIFF1000;

public:
   KRC_DIAG()
      : TON_1SEC()
      , HBLAST(0)
      , HBCYCDIFF(0)
      , HBSUM(0)
      , CYCLCNT(0)
      , PCOSHBLAST(0)
      , PCOSHBCYCDIFF(0)
      , PCOSHBSUM(0)
      , SECSUM(0)
      , AXISGROUPIDX(0)
      , SHOWTRACE((BOOL)FALSE)
      , MAXSUBMITCYCLE(0)
      , VALID(_VALID)
      , QUEUECOUNT(_QUEUECOUNT)
      , POSACTVALID(_POSACTVALID)
      , BRAKEACTIVE(_BRAKEACTIVE)
      , SUBMITHEARTBEAT(_SUBMITHEARTBEAT)
      , SUBMITCYC_ACT(_SUBMITCYC_ACT)
      , SUBMITCYC_MIN(_SUBMITCYC_MIN)
      , SUBMITCYC_MAX(_SUBMITCYC_MAX)
      , SUBMITCYC_AVG(_SUBMITCYC_AVG)
      , ACTIVEPOSORDERID(_ACTIVEPOSORDERID)
      , ACTIVEORDERIDB(_ACTIVEORDERIDB)
      , AVG_DURATION(_AVG_DURATION)
      , PROCONOSHEARTBEAT(_PROCONOSHEARTBEAT)
      , PROCONOSCYC_ACT(_PROCONOSCYC_ACT)
      , PROCONOSCYC_MIN(_PROCONOSCYC_MIN)
      , PROCONOSCYC_MAX(_PROCONOSCYC_MAX)
      , PROCONOSCYC_AVG(_PROCONOSCYC_AVG)
      , ERRORID_RI(_ERRORID_RI)
      , ERRORID_SI(_ERRORID_SI)
      , ERRORID_PLC(_ERRORID_PLC)
      , ERRORID_PCOS(_ERRORID_PCOS)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _QUEUECOUNT(0)
      , _POSACTVALID((BOOL)FALSE)
      , _BRAKEACTIVE((BOOL)FALSE)
      , _SUBMITHEARTBEAT(0)
      , _SUBMITCYC_ACT(0)
      , _SUBMITCYC_MIN(0)
      , _SUBMITCYC_MAX(0)
      , _SUBMITCYC_AVG(0)
      , _ACTIVEPOSORDERID(0)
      , _ACTIVEORDERIDB(0)
      , _AVG_DURATION(0)
      , _PROCONOSHEARTBEAT(0)
      , _PROCONOSCYC_ACT(0)
      , _PROCONOSCYC_MIN(0)
      , _PROCONOSCYC_MAX(0)
      , _PROCONOSCYC_AVG(0)
      , _ERRORID_RI(0)
      , _ERRORID_SI(0)
      , _ERRORID_PLC(0)
      , _ERRORID_PCOS(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , HBCYCDIFF1000(0)
      , CYCLCNT1000(0)
      , PCOSHBCYCDIFF1000(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.SHOWTRACE = SHOWTRACE;
      if ((MAXSUBMITCYCLE > (INT)0))
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
      TON_1SEC.PT = MKTIME(1, 0, 1);
      TON_1SEC.OnCycle();
      CYCLCNT = (CYCLCNT + 1);
      if ((HBLAST <= _SUBMITHEARTBEAT))
      {
         HBCYCDIFF = (HBCYCDIFF + (_SUBMITHEARTBEAT - HBLAST));
      }
      else
      {
         HBCYCDIFF = (HBCYCDIFF + ((255 - HBLAST) + _SUBMITHEARTBEAT));
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
         if ((HBCYCDIFF > (DINT)0))
         {
            _SUBMITCYC_ACT = (1000 / HBCYCDIFF);
         }
         else
         {
            _SUBMITCYC_ACT =  -(1);
         };
         if ((_SUBMITCYC_MIN == 0))
         {
            _SUBMITCYC_MIN = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
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
            _PROCONOSCYC_ACT = DINT_TO_INT(REAL_TO_DINT(((1000 / PCOSHBCYCDIFF) + 0.5)));
         }
         else
         {
            _PROCONOSCYC_ACT =  -(1);
         };
         if ((_PROCONOSCYC_MIN == 0))
         {
            _PROCONOSCYC_MIN = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
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
            _SUBMITCYC_AVG = DINT_TO_INT(REAL_TO_DINT(((_AVG_DURATION / HBSUM) + 0.5)));
         }
         else
         {
            _SUBMITCYC_AVG =  -(1);
         };
         if ((PCOSHBSUM > (DINT)0))
         {
            _PROCONOSCYC_AVG = DINT_TO_INT((_AVG_DURATION / PCOSHBSUM));
         }
         else
         {
            _PROCONOSCYC_AVG =  -(1);
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
         _SUBMITCYC_ACT =  -(1);
         _SUBMITCYC_MIN = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
         _SUBMITCYC_MAX =  -(1);
         _SUBMITCYC_AVG =  -(1);
         _AVG_DURATION = (DINT)0;
         _PROCONOSCYC_ACT =  -(1);
         _PROCONOSCYC_MIN = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
         _PROCONOSCYC_MAX =  -(1);
         _PROCONOSCYC_AVG =  -(1);
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
   INT AXISGROUPIDX;
   BOOL MESSAGERESET;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;
   const BOOL &NOHEARTBEATKRC;
   const BOOL &NOHEARTBEATPCOS;
   const BOOL &NOTONLINE;
   const BOOL &NOTINITIALIZED;
   const BOOL &NOOPMODEEXT;
   const BOOL &NOMOVEENABLE;
   const BOOL &USERSAFENOTOK;
   const BOOL &KRCERRORACTIVE;
   const BOOL &DRIVESNOTREADY;
   const BOOL &NOPROGACTIVE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;
   BOOL _NOHEARTBEATKRC;
   BOOL _NOHEARTBEATPCOS;
   BOOL _NOTONLINE;
   BOOL _NOTINITIALIZED;
   BOOL _NOOPMODEEXT;
   BOOL _NOMOVEENABLE;
   BOOL _USERSAFENOTOK;
   BOOL _KRCERRORACTIVE;
   BOOL _DRIVESNOTREADY;
   BOOL _NOPROGACTIVE;


   /* VAR */

private:
   KRC_READMXAERROR KRC_READMXAERROR_1;
   KRC_MESSAGERESET KRC_MESSAGERESET_1;
   TON TON_ON;
   TON TON_OFF;
   TON TON_HBSUB;
   TON TON_HBPCOS;
   BOOL ENABLETONSUBMIT;
   BOOL ENABLETONPCOS;
   INT M_HEARTBEATLAST;
   INT M_HEARTBEATLASTPCOS;

public:
	KRC_ERROR()
      : KRC_READMXAERROR_1()
      , KRC_MESSAGERESET_1()
      , TON_ON()
      , TON_OFF()
      , TON_HBSUB()
      , TON_HBPCOS()
      , ENABLETONSUBMIT((BOOL)FALSE)
      , ENABLETONPCOS((BOOL)FALSE)
      , M_HEARTBEATLAST(0)
      , M_HEARTBEATLASTPCOS(0)
      , AXISGROUPIDX(0)
      , MESSAGERESET((BOOL)FALSE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , NOHEARTBEATKRC(_NOHEARTBEATKRC)
      , NOHEARTBEATPCOS(_NOHEARTBEATPCOS)
      , NOTONLINE(_NOTONLINE)
      , NOTINITIALIZED(_NOTINITIALIZED)
      , NOOPMODEEXT(_NOOPMODEEXT)
      , NOMOVEENABLE(_NOMOVEENABLE)
      , USERSAFENOTOK(_USERSAFENOTOK)
      , KRCERRORACTIVE(_KRCERRORACTIVE)
      , DRIVESNOTREADY(_DRIVESNOTREADY)
      , NOPROGACTIVE(_NOPROGACTIVE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _NOHEARTBEATKRC((BOOL)FALSE)
      , _NOHEARTBEATPCOS((BOOL)FALSE)
      , _NOTONLINE((BOOL)FALSE)
      , _NOTINITIALIZED((BOOL)FALSE)
      , _NOOPMODEEXT((BOOL)FALSE)
      , _NOMOVEENABLE((BOOL)FALSE)
      , _USERSAFENOTOK((BOOL)FALSE)
      , _KRCERRORACTIVE((BOOL)FALSE)
      , _DRIVESNOTREADY((BOOL)FALSE)
      , _NOPROGACTIVE((BOOL)FALSE)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      // Call FB KRC_MessageReset_1
      KRC_MESSAGERESET_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MESSAGERESET_1.MESSAGERESET = MESSAGERESET;
      KRC_MESSAGERESET_1.OnCycle();
      // Call FB KRC_ReadMXAError_1
      KRC_READMXAERROR_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_READMXAERROR_1.OnCycle();
      _ERRORID = KRC_READMXAERROR_1.ERRORID;
      if ((_ERRORID == (DINT)0))
      {
         // Call FB TON_ON
         TON_ON.IN = (MESSAGERESET && !(TON_OFF.Q));
         TON_ON.PT = MKTIME(1, 200);
         TON_ON.OnCycle();
         // Call FB TON_OFF
         TON_OFF.IN = (MESSAGERESET && TON_ON.Q);
         TON_OFF.PT = MKTIME(1, 100);
         TON_OFF.OnCycle();
         if ((MESSAGERESET && !(TON_ON.Q)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (BOOL)TRUE;
            if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PERI_RDY))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (BOOL)TRUE;
            };
         };
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS)
         {
            _ERRORID = (DINT)801;
         };
      };
      _ERROR = (_ERRORID != (DINT)0);
      ENABLETONSUBMIT = ((M_HEARTBEATLAST == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT >= 0));
      ENABLETONPCOS = ((M_HEARTBEATLASTPCOS == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS >= 0));
      // Call FB TON_HBSub
      TON_HBSUB.IN = ENABLETONSUBMIT;
      TON_HBSUB.PT = MKTIME(1, 0, 1);
      TON_HBSUB.OnCycle();
      // Call FB TON_HBPCOS
      TON_HBPCOS.IN = ENABLETONPCOS;
      TON_HBPCOS.PT = MKTIME(1, 0, 1);
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6AXIS AXIS_VALUES;
   BOOL CHECKSOFTEND;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const E6POS &POSITION;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   E6POS _ACTPOSITION;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   DINT NORDERID;
   REAL ERR_STATUS;
   E6POS M_POSITION;
   INT NERR;

public:
   KRC_FORWARD()
      : NSTATE(0)
      , MXA_EXECUTECOMMAND_0()
      , MXA_EXECUTECOMMAND_1()
      , MXA_EXECUTECOMMAND_2()
      , NORDERID(0)
      , ERR_STATUS(0)
      , M_POSITION()
      , NERR(0)
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , AXIS_VALUES()
      , CHECKSOFTEND((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , POSITION(_ACTPOSITION)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ACTPOSITION()
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = (DINT)0;
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = (DINT)0;
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
      MXA_EXECUTECOMMAND_0.CMDID = (DINT)52;
      MXA_EXECUTECOMMAND_0.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_0.IGNOREINIT = (BOOL)FALSE;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)53;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = (DINT)1;
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
         M_POSITION.STATUS = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         M_POSITION.TURN = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
         NSTATE = 2;
      };
      if (MXA_EXECUTECOMMAND_1.ERROR)
      {
         NSTATE = 9;
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 2) || (NSTATE == 3)));
      MXA_EXECUTECOMMAND_2.CMDID = (DINT)53;
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_2.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_2.OnCycle();
      if ((MXA_EXECUTECOMMAND_2.WRITECMDPAR && (NSTATE == 2)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = (DINT)2;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
      _BUSY = ((MXA_EXECUTECOMMAND_0.BUSY || MXA_EXECUTECOMMAND_1.BUSY) || MXA_EXECUTECOMMAND_2.BUSY);
      _DONE = MXA_EXECUTECOMMAND_2.DONE;
      if ((NSTATE == 3))
      {
         _ACTPOSITION = M_POSITION;
         NERR = REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
            case  -(1):
               _ERRORID = (DINT)533;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case  -(3):
               _ERRORID = (DINT)534;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case  -(4):
               _ERRORID = (DINT)535;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case 1:
               _ERRORID = (DINT)536;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case 2:
               _ERRORID = (DINT)537;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case 0:
               _ERRORID = (DINT)0;
               break;
         };
      };
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_FORWARDADVANCED
 ******************************************************************************/
class KRC_FORWARDADVANCED
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6AXIS AXIS_VALUES;
   BOOL CHECKSOFTEND;
   COORDSYS COORDINATESYSTEM;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const E6POS &POSITION;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   E6POS _ACTPOSITION;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   DINT NORDERID;
   REAL ERR_STATUS;
   E6POS M_POSITION;
   INT NERR;

public:
   KRC_FORWARDADVANCED()
      : NSTATE(0)
      , MXA_EXECUTECOMMAND_0()
      , NORDERID(0)
      , ERR_STATUS(0)
      , M_POSITION()
      , NERR(0)
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , AXIS_VALUES()
      , CHECKSOFTEND((BOOL)FALSE)
      , COORDINATESYSTEM()
      , BUSY(_BUSY)
      , DONE(_DONE)
      , POSITION(_ACTPOSITION)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ACTPOSITION()
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = (DINT)0;
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = (DINT)0;
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
      MXA_EXECUTECOMMAND_0.CMDID = (DINT)56;
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.IGNOREINIT = (BOOL)FALSE;
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_POSITION.X = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
         M_POSITION.Y = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2];
         M_POSITION.Z = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3];
         M_POSITION.A = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4];
         M_POSITION.B = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
         M_POSITION.C = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         M_POSITION.STATUS = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         M_POSITION.TURN = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      _BUSY = MXA_EXECUTECOMMAND_0.BUSY;
      _DONE = MXA_EXECUTECOMMAND_0.DONE;
      if ((NSTATE == 2))
      {
         _ACTPOSITION = M_POSITION;
         NERR = REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
            case  -(1):
               _ERRORID = (DINT)533;
               break;
            case  -(3):
               _ERRORID = (DINT)534;
               break;
            case  -(4):
               _ERRORID = (DINT)535;
               break;
            case 1:
               _ERRORID = (DINT)536;
               break;
            case 2:
               _ERRORID = (DINT)537;
               break;
            case 4:
               _ERRORID = (DINT)549;
               break;
            case 0:
               _ERRORID = (DINT)0;
               break;
         };
      };
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_GETADVANCE
 ******************************************************************************/
class KRC_GETADVANCE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const INT &COUNT;
   const INT &MAXWAITTIME;
   const INT &MODE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   INT _COUNT;
   INT _MAXWAITTIME;
   INT _MODE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_GETADVANCE()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , DONE(_DONE)
      , COUNT(_COUNT)
      , MAXWAITTIME(_MAXWAITTIME)
      , MODE(_MODE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _COUNT(0)
      , _MAXWAITTIME(0)
      , _MODE(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)37;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _COUNT = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _MAXWAITTIME = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _MODE = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INITIALIZE
 ******************************************************************************/
class KRC_INITIALIZE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const DINT &KRC_SERIAL;
   const DINT &KRC_MAJOR;
   const DINT &KRC_MINOR;
   const DINT &KRC_REVISION;
   const DINT &KRC_ABSACCUR;
   const DINT &PLC_MAJOR;
   const DINT &PLC_MINOR;
   const DINT &PLC_REVISION;


   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;
   DINT _KRC_SERIAL;
   DINT _KRC_MAJOR;
   DINT _KRC_MINOR;
   DINT _KRC_REVISION;
   DINT _KRC_ABSACCUR;
   DINT _PLC_MAJOR;
   DINT _PLC_MINOR;
   DINT _PLC_REVISION;



   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;

public:
   KRC_INITIALIZE()
      : MXA_EXECUTECOMMAND_1()
      , MXA_RESETCOMMAND_1()
      , AXISGROUPIDX(0)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , KRC_SERIAL(_KRC_SERIAL)
      , KRC_MAJOR(_KRC_MAJOR)
      , KRC_MINOR(_KRC_MINOR)
      , KRC_REVISION(_KRC_REVISION)
      , KRC_ABSACCUR(_KRC_ABSACCUR)
      , PLC_MAJOR(_PLC_MAJOR)
      , PLC_MINOR(_PLC_MINOR)
      , PLC_REVISION(_PLC_REVISION)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _KRC_SERIAL(0)
      , _KRC_MAJOR(0)
      , _KRC_MINOR(0)
      , _KRC_REVISION(0)
      , _PLC_MAJOR(0)
      , _PLC_MINOR(0)
      , _PLC_REVISION(0)
   {}

public:
   void OnCycle()
   {

      _PLC_MAJOR = (DINT)3;
      _PLC_MINOR = (DINT)3;
      _PLC_REVISION = (DINT)1;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MAJOR = _PLC_MAJOR;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].PLC_MINOR = _PLC_MINOR;
      if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
      {
         _ERRORID = (DINT)0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = (BOOL)FALSE;
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      if ((((KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED == (BOOL)FALSE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > (DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID != (DINT)31)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = 0;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = 0;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)31;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _KRC_SERIAL = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _KRC_MAJOR = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _KRC_MINOR = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _KRC_REVISION = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
       KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5];
       KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6];
         _KRC_ABSACCUR = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         if (((_KRC_MAJOR == _PLC_MAJOR) && (_KRC_MINOR == _PLC_MINOR)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = (BOOL)TRUE;
         }
         else
         {
            _ERRORID = (DINT)503;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
         };
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      if ((_ERRORID == (DINT)0))
      {
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INTERRUPT
 ******************************************************************************/
class KRC_INTERRUPT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   BOOL FAST;

   /* VAR_OUTPUT */

public:
   const BOOL &BRAKEACTIVE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BRAKEACTIVE;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_INTERRUPT()
      : AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , FAST((BOOL)FALSE)
      , BRAKEACTIVE(_BRAKEACTIVE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BRAKEACTIVE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      if (EXECUTE)
      {
         if (FAST)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKEF = (BOOL)TRUE;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKE = (BOOL)TRUE;
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   BOOL POSVALIDS;
   BOOL POSVALIDT;
   E6AXIS START_AXIS;
   BOOL CHECKSOFTEND;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const E6AXIS &AXISPOSITION;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   E6AXIS _AXISPOSITION;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   DINT NORDERID;
   REAL ERR_STATUS;
   E6AXIS M_POSITION;
   INT NERR;

public:
   KRC_INVERSE()
      : NSTATE(0)
      , MXA_EXECUTECOMMAND_0()
      , MXA_EXECUTECOMMAND_1()
      , MXA_EXECUTECOMMAND_2()
      , NORDERID(0)
      , ERR_STATUS(0)
      , M_POSITION()
      , NERR(0)
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , POSVALIDS((BOOL)FALSE)
      , POSVALIDT((BOOL)FALSE)
      , START_AXIS()
      , CHECKSOFTEND((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , AXISPOSITION(_AXISPOSITION)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _AXISPOSITION()
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = (DINT)0;
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = (DINT)0;
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
      MXA_EXECUTECOMMAND_0.CMDID = (DINT)54;
      MXA_EXECUTECOMMAND_0.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_0.IGNOREINIT = (BOOL)FALSE;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)55;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = (DINT)1;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 2) || (NSTATE == 3)));
      MXA_EXECUTECOMMAND_2.CMDID = (DINT)55;
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_2.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_2.OnCycle();
      if ((MXA_EXECUTECOMMAND_2.WRITECMDPAR && (NSTATE == 2)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = (DINT)2;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
      if ((NSTATE == 3))
      {
         _AXISPOSITION = M_POSITION;
         NERR = REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
            case  -(1):
               _ERRORID = (DINT)538;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case  -(3):
               _ERRORID = (DINT)539;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case  -(4):
               _ERRORID = (DINT)540;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case 1:
               _ERRORID = (DINT)541;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
            case 2:
               _ERRORID = (DINT)542;
               KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
               break;
			case 3:
				_ERRORID = (DINT)547;
				KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
				break;
            case 0:
               _ERRORID = (DINT)0;
               break;
         };
      };
     _ERROR = (_ERRORID != (DINT)0);
     _BUSY = ((MXA_EXECUTECOMMAND_0.BUSY || MXA_EXECUTECOMMAND_1.BUSY) || MXA_EXECUTECOMMAND_2.BUSY);
     _DONE = MXA_EXECUTECOMMAND_2.DONE && !_ERROR;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_INVERSEADVANCED
 ******************************************************************************/
class KRC_INVERSEADVANCED
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   BOOL POSVALIDS;
   BOOL POSVALIDT;
   E6AXIS START_AXIS;
   BOOL CHECKSOFTEND;
   COORDSYS COORDINATESYSTEM;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const E6AXIS &AXISPOSITION;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   E6AXIS _AXISPOSITION;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   DINT NORDERID;
   REAL ERR_STATUS;
   E6AXIS M_POSITION;
   INT NERR;

public:
   KRC_INVERSEADVANCED()
      : NSTATE(0)
      , MXA_EXECUTECOMMAND_0()
      , NORDERID(0)
      , ERR_STATUS(0)
      , M_POSITION()
      , NERR(0)
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , POSVALIDS((BOOL)FALSE)
      , POSVALIDT((BOOL)FALSE)
      , START_AXIS()
      , CHECKSOFTEND((BOOL)FALSE)
      , COORDINATESYSTEM()
      , BUSY(_BUSY)
      , DONE(_DONE)
      , AXISPOSITION(_AXISPOSITION)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _AXISPOSITION()
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         if (!(EXECUTECMD))
         {
            _ERRORID = (DINT)0;
         };
      };
      if (!(EXECUTECMD))
      {
         NSTATE = 0;
         NORDERID = (DINT)0;
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
      MXA_EXECUTECOMMAND_0.CMDID = (DINT)57;
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.IGNOREINIT = (BOOL)FALSE;
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
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      if ((NSTATE == 2))
      {
         _AXISPOSITION = M_POSITION;
         NERR = REAL_TO_INT(ERR_STATUS);
         switch (NERR)
         {
            case  -(1):
               _ERRORID = (DINT)538;
               break;
            case  -(3):
               _ERRORID = (DINT)539;
               break;
            case  -(4):
               _ERRORID = (DINT)540;
               break;
            case 1:
               _ERRORID = (DINT)541;
               break;
            case 2:
               _ERRORID = (DINT)542;
               break;
			   case 3:
				   _ERRORID = (DINT)547;
				   break;
			   case 4:
				   _ERRORID = (DINT)549;
				   break;
            case 0:
               _ERRORID = (DINT)0;
               break;
         };
      };
     _ERROR = (_ERRORID != (DINT)0);
     _BUSY = MXA_EXECUTECOMMAND_0.BUSY;
     _DONE = MXA_EXECUTECOMMAND_0.DONE && !_ERROR;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOG
 ******************************************************************************/
class KRC_JOG
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   INT MOVETYPE;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   REAL INCREMENT;
   BOOL A1_X_P;
   BOOL A1_X_M;
   BOOL A2_Y_P;
   BOOL A2_Y_M;
   BOOL A3_Z_P;
   BOOL A3_Z_M;
   BOOL A4_A_P;
   BOOL A4_A_M;
   BOOL A5_B_P;
   BOOL A5_B_M;
   BOOL A6_C_P;
   BOOL A6_C_M;
   BOOL E1_P;
   BOOL E1_M;
   BOOL E2_P;
   BOOL E2_M;
   BOOL E3_P;
   BOOL E3_M;
   BOOL E4_P;
   BOOL E4_M;
   BOOL E5_P;
   BOOL E5_M;
   BOOL E6_P;
   BOOL E6_M;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   KRC_ABORT KRC_ABORT_1;
   E6POS M_POSITION;
   E6AXIS M_AXISPOSITION;
   INT M_MOVETYPE;
   BOOL M_EXECUTECMD;
   BOOL M_CMDINPUTACTIVE;
   BOOL M_CMDINPUTACTIVELAST;
   BOOL M_CMDINPUTACTIVECHANGED;
   BOOL M_CMDINPUTCHANGED;
   BOOL M_INCREMENTACTIVE;
   REAL M_MAXDELTA;
   BOOL M_EXECUTEABORT;
   BOOL A1_X_P_LAST;
   BOOL A1_X_M_LAST;
   BOOL A2_Y_P_LAST;
   BOOL A2_Y_M_LAST;
   BOOL A3_Z_P_LAST;
   BOOL A3_Z_M_LAST;
   BOOL A4_A_P_LAST;
   BOOL A4_A_M_LAST;
   BOOL A5_B_P_LAST;
   BOOL A5_B_M_LAST;
   BOOL A6_C_P_LAST;
   BOOL A6_C_M_LAST;
   BOOL E1_P_LAST;
   BOOL E1_M_LAST;
   BOOL E2_P_LAST;
   BOOL E2_M_LAST;
   BOOL E3_P_LAST;
   BOOL E3_M_LAST;
   BOOL E4_P_LAST;
   BOOL E4_M_LAST;
   BOOL E5_P_LAST;
   BOOL E5_M_LAST;
   BOOL E6_P_LAST;
   BOOL E6_M_LAST;
   //bugfix
   BOOL M_EXECUTECMD_FINISHED;

public:
   KRC_JOG()
      : KRC_MOVE_1()
      , KRC_ABORT_1()
      , M_POSITION()
      , M_AXISPOSITION()
      , M_MOVETYPE(0)
      , M_EXECUTECMD((BOOL)FALSE)
      , M_CMDINPUTACTIVE((BOOL)FALSE)
      , M_CMDINPUTACTIVELAST((BOOL)FALSE)
      , M_CMDINPUTACTIVECHANGED((BOOL)FALSE)
      , M_CMDINPUTCHANGED((BOOL)FALSE)
      , M_INCREMENTACTIVE((BOOL)FALSE)
      , M_MAXDELTA(0)
      , M_EXECUTEABORT((BOOL)FALSE)
      , A1_X_P_LAST((BOOL)FALSE)
      , A1_X_M_LAST((BOOL)FALSE)
      , A2_Y_P_LAST((BOOL)FALSE)
      , A2_Y_M_LAST((BOOL)FALSE)
      , A3_Z_P_LAST((BOOL)FALSE)
      , A3_Z_M_LAST((BOOL)FALSE)
      , A4_A_P_LAST((BOOL)FALSE)
      , A4_A_M_LAST((BOOL)FALSE)
      , A5_B_P_LAST((BOOL)FALSE)
      , A5_B_M_LAST((BOOL)FALSE)
      , A6_C_P_LAST((BOOL)FALSE)
      , A6_C_M_LAST((BOOL)FALSE)
      , E1_P_LAST((BOOL)FALSE)
      , E1_M_LAST((BOOL)FALSE)
      , E2_P_LAST((BOOL)FALSE)
      , E2_M_LAST((BOOL)FALSE)
      , E3_P_LAST((BOOL)FALSE)
      , E3_M_LAST((BOOL)FALSE)
      , E4_P_LAST((BOOL)FALSE)
      , E4_M_LAST((BOOL)FALSE)
      , E5_P_LAST((BOOL)FALSE)
      , E5_M_LAST((BOOL)FALSE)
      , E6_P_LAST((BOOL)FALSE)
      , E6_M_LAST((BOOL)FALSE)
      , AXISGROUPIDX(0)
      , MOVETYPE(0)
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , INCREMENT(0)
      , A1_X_P((BOOL)FALSE)
      , A1_X_M((BOOL)FALSE)
      , A2_Y_P((BOOL)FALSE)
      , A2_Y_M((BOOL)FALSE)
      , A3_Z_P((BOOL)FALSE)
      , A3_Z_M((BOOL)FALSE)
      , A4_A_P((BOOL)FALSE)
      , A4_A_M((BOOL)FALSE)
      , A5_B_P((BOOL)FALSE)
      , A5_B_M((BOOL)FALSE)
      , A6_C_P((BOOL)FALSE)
      , A6_C_M((BOOL)FALSE)
      , E1_P((BOOL)FALSE)
      , E1_M((BOOL)FALSE)
      , E2_P((BOOL)FALSE)
      , E2_M((BOOL)FALSE)
      , E3_P((BOOL)FALSE)
      , E3_M((BOOL)FALSE)
      , E4_P((BOOL)FALSE)
      , E4_M((BOOL)FALSE)
      , E5_P((BOOL)FALSE)
      , E5_M((BOOL)FALSE)
      , E6_P((BOOL)FALSE)
      , E6_M((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (((((((((((((A1_X_P && A1_X_M) || (A2_Y_P && A2_Y_M)) || (A3_Z_P && A3_Z_M)) || (A4_A_P && A4_A_M)) || (A5_B_P && A5_B_M)) || (A6_C_P && A6_C_M)) || (E1_P && E1_M)) || (E2_P && E2_M)) || (E3_P && E3_M)) || (E4_P && E4_M)) || (E5_P && E5_M)) || (E6_P && E6_M)))
      {
         _ERRORID = (DINT)548;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         _ERROR = (BOOL)TRUE;
         return;
      };
      M_INCREMENTACTIVE = (INCREMENT > 0.0);
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
         case 3:
            M_MOVETYPE = 13;
            break;
         default:
            _ERRORID = (DINT)590;
            _ERROR = (BOOL)TRUE;
            return;
      };
      M_CMDINPUTACTIVE = (((((((((((((((((((((((A1_X_P || A1_X_M) || A2_Y_P) || A2_Y_M) || A3_Z_P) || A3_Z_M) || A4_A_P) || A4_A_M) || A5_B_P) || A5_B_M) || A6_C_P) || A6_C_M) || E1_P) || E1_M) || E2_P) || E2_M) || E3_P) || E3_M) || E4_P) || E4_M) || E5_P) || E5_M) || E6_P) || E6_M);
      M_CMDINPUTACTIVECHANGED = (M_CMDINPUTACTIVELAST != M_CMDINPUTACTIVE);
      M_CMDINPUTACTIVELAST = M_CMDINPUTACTIVE;
      if ((M_CMDINPUTACTIVECHANGED && !(M_CMDINPUTACTIVE)))
      {
         M_EXECUTEABORT = (BOOL)TRUE;
      };
      M_CMDINPUTCHANGED = (BOOL)FALSE;
      if ((A1_X_P != A1_X_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A1_X_M != A1_X_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A2_Y_P != A2_Y_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A2_Y_M != A2_Y_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A3_Z_P != A3_Z_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A3_Z_M != A3_Z_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A4_A_P != A4_A_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A4_A_M != A4_A_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A5_B_P != A5_B_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A5_B_M != A5_B_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A6_C_P != A6_C_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((A6_C_M != A6_C_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E1_P != E1_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E1_M != E1_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E2_P != E2_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E2_M != E2_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E3_P != E3_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E3_M != E3_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E4_P != E4_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E4_M != E4_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E5_P != E5_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E5_M != E5_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E6_P != E6_P_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
      };
      if ((E6_M != E6_M_LAST))
      {
         M_CMDINPUTCHANGED = (BOOL)TRUE;
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
					if (A1_X_P) { M_AXISPOSITION.A1 = INCREMENT; };
					if (A1_X_M) { M_AXISPOSITION.A1 = (INCREMENT *  -(1)); };
					if (A2_Y_P) { M_AXISPOSITION.A2 = INCREMENT; };
					if (A2_Y_M) { M_AXISPOSITION.A2 = (INCREMENT *  -(1)); };
					if (A3_Z_P) { M_AXISPOSITION.A3 = INCREMENT; };
					if (A3_Z_M) { M_AXISPOSITION.A3 = (INCREMENT *  -(1)); };
					if (A4_A_P) { M_AXISPOSITION.A4 = INCREMENT; };
					if (A4_A_M) { M_AXISPOSITION.A4 = (INCREMENT *  -(1)); };
					if (A5_B_P) { M_AXISPOSITION.A5 = INCREMENT; };
					if (A5_B_M) { M_AXISPOSITION.A5 = (INCREMENT *  -(1)); };
					if (A6_C_P) { M_AXISPOSITION.A6 = INCREMENT; };
					if (A6_C_M) { M_AXISPOSITION.A6 = (INCREMENT *  -(1)); };
					if (E1_P) { M_AXISPOSITION.E1 = INCREMENT; };
					if (E1_M) { M_AXISPOSITION.E1 = (INCREMENT *  -(1)); };
					if (E2_P) { M_AXISPOSITION.E2 = INCREMENT; };
					if (E2_M) { M_AXISPOSITION.E2 = (INCREMENT *  -(1)); };
					if (E3_P) { M_AXISPOSITION.E3 = INCREMENT; };
					if (E3_M) { M_AXISPOSITION.E3 = (INCREMENT *  -(1)); };
					if (E4_P) { M_AXISPOSITION.E4 = INCREMENT; };
					if (E4_M) { M_AXISPOSITION.E4 = (INCREMENT *  -(1)); };
					if (E5_P) { M_AXISPOSITION.E5 = INCREMENT; };
					if (E5_M) { M_AXISPOSITION.E5 = (INCREMENT *  -(1)); };
					if (E6_P) { M_AXISPOSITION.E6 = INCREMENT; };
					if (E6_M) { M_AXISPOSITION.E6 = (INCREMENT *  -(1)); };
				}
				else
				{
					if (A1_X_P) { M_AXISPOSITION.A1 = M_MAXDELTA; };
					if (A1_X_M) { M_AXISPOSITION.A1 = (M_MAXDELTA *  -(1)); };
					if (A2_Y_P) { M_AXISPOSITION.A2 = M_MAXDELTA; };
					if (A2_Y_M) { M_AXISPOSITION.A2 = (M_MAXDELTA *  -(1)); };
					if (A3_Z_P) { M_AXISPOSITION.A3 = M_MAXDELTA; };
					if (A3_Z_M) { M_AXISPOSITION.A3 = (M_MAXDELTA *  -(1)); };
					if (A4_A_P) { M_AXISPOSITION.A4 = M_MAXDELTA; };
					if (A4_A_M) { M_AXISPOSITION.A4 = (M_MAXDELTA *  -(1)); };
					if (A5_B_P) { M_AXISPOSITION.A5 = M_MAXDELTA; };
					if (A5_B_M) { M_AXISPOSITION.A5 = (M_MAXDELTA *  -(1)); };
					if (A6_C_P) { M_AXISPOSITION.A6 = M_MAXDELTA; };
					if (A6_C_M) { M_AXISPOSITION.A6 = (M_MAXDELTA *  -(1)); };
					if (E1_P) { M_AXISPOSITION.E1 = M_MAXDELTA; };
					if (E1_M) { M_AXISPOSITION.E1 = (M_MAXDELTA *  -(1)); };
					if (E2_P) { M_AXISPOSITION.E2 = M_MAXDELTA; };
					if (E2_M) { M_AXISPOSITION.E2 = (M_MAXDELTA *  -(1)); };
					if (E3_P) { M_AXISPOSITION.E3 = M_MAXDELTA; };
					if (E3_M) { M_AXISPOSITION.E3 = (M_MAXDELTA *  -(1)); };
					if (E4_P) { M_AXISPOSITION.E4 = M_MAXDELTA; };
					if (E4_M) { M_AXISPOSITION.E4 = (M_MAXDELTA *  -(1)); };
					if (E5_P) { M_AXISPOSITION.E5 = M_MAXDELTA; };
					if (E5_M) { M_AXISPOSITION.E5 = (M_MAXDELTA *  -(1)); };
					if (E6_P) { M_AXISPOSITION.E6 = M_MAXDELTA; };
					if (E6_M) { M_AXISPOSITION.E6 = (M_MAXDELTA *  -(1)); };
				}
               break;
            case 1:
            case 3:
               if (M_INCREMENTACTIVE)
               {
                  if (A1_X_P)
                  {
                     M_POSITION.X = INCREMENT;
                  };
                  if (A1_X_M)
                  {
                     M_POSITION.X = (INCREMENT *  -(1));
                  };
                  if (A2_Y_P)
                  {
                     M_POSITION.Y = INCREMENT;
                  };
                  if (A2_Y_M)
                  {
                     M_POSITION.Y = (INCREMENT *  -(1));
                  };
                  if (A3_Z_P)
                  {
                     M_POSITION.Z = INCREMENT;
                  };
                  if (A3_Z_M)
                  {
                     M_POSITION.Z = (INCREMENT *  -(1));
                  };
                  if (A4_A_P)
                  {
                     M_POSITION.A = INCREMENT;
                  };
                  if (A4_A_M)
                  {
                     M_POSITION.A = (INCREMENT *  -(1));
                  };
                  if (A5_B_P)
                  {
                     M_POSITION.B = INCREMENT;
                  };
                  if (A5_B_M)
                  {
                     M_POSITION.B = (INCREMENT *  -(1));
                  };
                  if (A6_C_P)
                  {
                     M_POSITION.C = INCREMENT;
                  };
                  if (A6_C_M)
                  {
                     M_POSITION.C = (INCREMENT *  -(1));
                  };
                  if (E1_P)
                  {
                     M_POSITION.E1 = INCREMENT;
                  };
                  if (E1_M)
                  {
                     M_POSITION.E1 = (INCREMENT *  -(1));
                  };
                  if (E2_P)
                  {
                     M_POSITION.E2 = INCREMENT;
                  };
                  if (E2_M)
                  {
                     M_POSITION.E2 = (INCREMENT *  -(1));
                  };
                  if (E3_P)
                  {
                     M_POSITION.E3 = INCREMENT;
                  };
                  if (E3_M)
                  {
                     M_POSITION.E3 = (INCREMENT *  -(1));
                  };
                  if (E4_P)
                  {
                     M_POSITION.E4 = INCREMENT;
                  };
                  if (E4_M)
                  {
                     M_POSITION.E4 = (INCREMENT *  -(1));
                  };
                  if (E5_P)
                  {
                     M_POSITION.E5 = INCREMENT;
                  };
                  if (E5_M)
                  {
                     M_POSITION.E5 = (INCREMENT *  -(1));
                  };
                  if (E6_P)
                  {
                     M_POSITION.E6 = INCREMENT;
                  };
                  if (E6_M)
                  {
                     M_POSITION.E6 = (INCREMENT *  -(1));
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
                     M_POSITION.X = (M_MAXDELTA *  -(1));
                  };
                  if (A2_Y_P)
                  {
                     M_POSITION.Y = M_MAXDELTA;
                  };
                  if (A2_Y_M)
                  {
                     M_POSITION.Y = (M_MAXDELTA *  -(1));
                  };
                  if (A3_Z_P)
                  {
                     M_POSITION.Z = M_MAXDELTA;
                  };
                  if (A3_Z_M)
                  {
                     M_POSITION.Z = (M_MAXDELTA *  -(1));
                  };
                  if (A4_A_P)
                  {
                     M_POSITION.A = 90.0;
                  };
                  if (A4_A_M)
                  {
                     M_POSITION.A = (90.0 *  -(1));
                  };
                  if (A5_B_P)
                  {
                     M_POSITION.B = 90.0;
                  };
                  if (A5_B_M)
                  {
                     M_POSITION.B = (90.0 *  -(1));
                  };
                  if (A6_C_P)
                  {
                     M_POSITION.C = 90.0;
                  };
                  if (A6_C_M)
                  {
                     M_POSITION.C = (90.0 *  -(1));
                  };
                  if (E1_P)
                  {
                     M_POSITION.E1 = M_MAXDELTA;
                  };
                  if (E1_M)
                  {
                     M_POSITION.E1 = (M_MAXDELTA *  -(1));
                  };
                  if (E2_P)
                  {
                     M_POSITION.E2 = M_MAXDELTA;
                  };
                  if (E2_M)
                  {
                     M_POSITION.E2 = (M_MAXDELTA *  -(1));
                  };
                  if (E3_P)
                  {
                     M_POSITION.E3 = M_MAXDELTA;
                  };
                  if (E3_M)
                  {
                     M_POSITION.E3 = (M_MAXDELTA *  -(1));
                  };
                  if (E4_P)
                  {
                     M_POSITION.E4 = M_MAXDELTA;
                  };
                  if (E4_M)
                  {
                     M_POSITION.E4 = (M_MAXDELTA *  -(1));
                  };
                  if (E5_P)
                  {
                     M_POSITION.E5 = M_MAXDELTA;
                  };
                  if (E5_M)
                  {
                     M_POSITION.E5 = (M_MAXDELTA *  -(1));
                  };
                  if (E6_P)
                  {
                     M_POSITION.E6 = M_MAXDELTA;
                  };
                  if (E6_M)
                  {
                     M_POSITION.E6 = (M_MAXDELTA *  -(1));
                  };
               };
               break;
         };
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = (DINT)1;
      KRC_MOVE_1.EXECUTECMD = (M_EXECUTECMD && (_ERRORID == (DINT)0) && !(M_EXECUTEABORT)) ;
      KRC_MOVE_1.MOVETYPE = M_MOVETYPE;
      KRC_MOVE_1.ACTPOSITION = M_POSITION;
      KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = 0;
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)FALSE;
      KRC_MOVE_1.POSVALIDT = (BOOL)FALSE;
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();

      //_BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      //_DONE = KRC_MOVE_1.DONE;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);

     // Call FB KRC_Abort_1
     KRC_ABORT_1.AXISGROUPIDX = AXISGROUPIDX;
     KRC_ABORT_1.EXECUTECMD = M_EXECUTEABORT;
     KRC_ABORT_1.OnCycle();
     if ((KRC_ABORT_1.ERROR || KRC_ABORT_1.DONE))
     {
      M_EXECUTEABORT = (BOOL)FALSE;
	  };
	  _ERRORID = KRC_ABORT_1.ERRORID;

	  //bugfix: krc jog done signal and busy robot stopped
	  if (!M_CMDINPUTACTIVELAST && M_CMDINPUTACTIVE && M_EXECUTECMD)
	  {
		  _BUSY = true;
	  }

	  if (M_CMDINPUTACTIVELAST && !M_CMDINPUTACTIVE && (_ERRORID == (DINT)0))
	  {
		  M_EXECUTECMD_FINISHED = true;
	  }

	  if(M_EXECUTECMD_FINISHED && KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.ROB_STOPPED)
	  {
		  M_EXECUTECMD_FINISHED = false;
		  _BUSY = false;
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
    INT AXISGROUPIDX;
    INT MOVETYPE;
    INT VELOCITY;
    INT ACCELERATION;
    COORDSYS COORDINATESYSTEM;
    BOOL JOGADVANCED;
    BOOL B_A1_JA_P;
    BOOL B_A1_JA_M;
    BOOL B_A2_JA_P;
    BOOL B_A2_JA_M;
    BOOL B_A3_JA_P;
    BOOL B_A3_JA_M;
    BOOL B_A4_JA_P;
    BOOL B_A4_JA_M;
    BOOL B_A5_JA_P;
    BOOL B_A5_JA_M;
    BOOL B_A6_JA_P;
    BOOL B_A6_JA_M;
    BOOL B_E1_JA_P;
    BOOL B_E1_JA_M;
    BOOL B_E2_JA_P;
    BOOL B_E2_JA_M;
    BOOL B_E3_JA_P;
    BOOL B_E3_JA_M;
    BOOL B_E4_JA_P;
    BOOL B_E4_JA_M;
    BOOL B_E5_JA_P;
    BOOL B_E5_JA_M;
    BOOL B_E6_JA_P;
    BOOL B_E6_JA_M;
    BOOL B_X_JA_P;
    BOOL B_X_JA_M;
    BOOL B_Y_JA_P;
    BOOL B_Y_JA_M;
    BOOL B_Z_JA_P;
    BOOL B_Z_JA_M;
    BOOL B_A_JA_P;
    BOOL B_A_JA_M;
    BOOL B_B_JA_P;
    BOOL B_B_JA_M;
    BOOL B_C_JA_P;
    BOOL B_C_JA_M;

    /* VAR_OUTPUT */

public:
    const BOOL& BUSY;
    const BOOL& ACTIVE;
    const BOOL& ERROR;
    const DINT& ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _ACTIVE;
    BOOL _ERROR;
    DINT _ERRORID;


    /* VAR */

private:
    INT JA_STATE_VAL;
    KRC_MOVE KRC_MOVE_1;
    KRC_ABORT KRC_ABORT_1;
    E6POS M_POSITION;
    E6AXIS M_AXISPOSITION;
    INT M_MOVETYPE;
    BOOL M_EXECUTEABORT;
    BOOL JA_BUTTONACTIVE;
    BOOL JA_BUTTONCHANGED;
    BOOL JA_BUTTONLAST;
    BOOL JA_MOVETYPEACTIVE;
    BOOL JA_MOVETYPELAST;
    BOOL JA_MOVETYPECHANGED;
    BOOL JA_BASECHANGED;
    COORDSYS JA_COORDSYSACTIVE;
    COORDSYS JA_COORDSYSLAST;
    BOOL JA_TOOLCHANGED;
    BOOL JA_IPOCHANGED;

public:
    KRC_JOGADVANCED()
        : JA_STATE_VAL(0)
        , KRC_MOVE_1()
        , KRC_ABORT_1()
        , M_POSITION()
        , M_AXISPOSITION()
        , M_MOVETYPE(0)
        , M_EXECUTEABORT((BOOL)FALSE)
        , JA_BUTTONACTIVE((BOOL)FALSE)
        , JA_BUTTONCHANGED((BOOL)FALSE)
        , JA_BUTTONLAST((BOOL)FALSE)
        , JA_MOVETYPEACTIVE((BOOL)FALSE)
        , JA_MOVETYPELAST((BOOL)FALSE)
        , JA_MOVETYPECHANGED((BOOL)FALSE)
        , JA_BASECHANGED((BOOL)FALSE)
        , JA_COORDSYSACTIVE()
        , JA_COORDSYSLAST()
        , JA_TOOLCHANGED((BOOL)FALSE)
        , JA_IPOCHANGED((BOOL)FALSE)
        , AXISGROUPIDX(0)
        , MOVETYPE(0)
        , VELOCITY(0)
        , ACCELERATION(0)
        , COORDINATESYSTEM()
        , JOGADVANCED((BOOL)FALSE)
        , B_A1_JA_P((BOOL)FALSE)
        , B_A1_JA_M((BOOL)FALSE)
        , B_A2_JA_P((BOOL)FALSE)
        , B_A2_JA_M((BOOL)FALSE)
        , B_A3_JA_P((BOOL)FALSE)
        , B_A3_JA_M((BOOL)FALSE)
        , B_A4_JA_P((BOOL)FALSE)
        , B_A4_JA_M((BOOL)FALSE)
        , B_A5_JA_P((BOOL)FALSE)
        , B_A5_JA_M((BOOL)FALSE)
        , B_A6_JA_P((BOOL)FALSE)
        , B_A6_JA_M((BOOL)FALSE)
        , B_E1_JA_P((BOOL)FALSE)
        , B_E1_JA_M((BOOL)FALSE)
        , B_E2_JA_P((BOOL)FALSE)
        , B_E2_JA_M((BOOL)FALSE)
        , B_E3_JA_P((BOOL)FALSE)
        , B_E3_JA_M((BOOL)FALSE)
        , B_E4_JA_P((BOOL)FALSE)
        , B_E4_JA_M((BOOL)FALSE)
        , B_E5_JA_P((BOOL)FALSE)
        , B_E5_JA_M((BOOL)FALSE)
        , B_E6_JA_P((BOOL)FALSE)
        , B_E6_JA_M((BOOL)FALSE)
        , B_X_JA_P((BOOL)FALSE)
        , B_X_JA_M((BOOL)FALSE)
        , B_Y_JA_P((BOOL)FALSE)
        , B_Y_JA_M((BOOL)FALSE)
        , B_Z_JA_P((BOOL)FALSE)
        , B_Z_JA_M((BOOL)FALSE)
        , B_A_JA_P((BOOL)FALSE)
        , B_A_JA_M((BOOL)FALSE)
        , B_B_JA_P((BOOL)FALSE)
        , B_B_JA_M((BOOL)FALSE)
        , B_C_JA_P((BOOL)FALSE)
        , B_C_JA_M((BOOL)FALSE)
        , BUSY(_BUSY)
        , ACTIVE(_ACTIVE)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _ACTIVE((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {

        _ERRORID = (DINT)0;

        JA_BUTTONACTIVE = (BOOL)FALSE;
        _BUSY = (BOOL)FALSE;
        KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_ACTIVE = JOGADVANCED;
        KRC_AXISGROUPREFARR[AXISGROUPIDX].JOG_ADVANCED.JOG_AD_STATE_VAL = 0;

        if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
        {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        };

        if (((((((((((((((((((B_A1_JA_P && B_A1_JA_M) || (B_A2_JA_P && B_A2_JA_M)) || (B_A3_JA_P && B_A3_JA_M)) || (B_A4_JA_P && B_A4_JA_M)) || (B_A5_JA_P && B_A5_JA_M)) || (B_A6_JA_P && B_A6_JA_M)) || (B_E1_JA_P && B_E1_JA_M)) || (B_E2_JA_P && B_E2_JA_M)) || (B_E3_JA_P && B_E3_JA_M)) || (B_E4_JA_P && B_E4_JA_M)) || (B_E5_JA_P && B_E5_JA_M)) || (B_E6_JA_P && B_E6_JA_M)) || (B_X_JA_P && B_X_JA_M)) || (B_Y_JA_P && B_Y_JA_M)) || (B_Z_JA_P && B_Z_JA_M)) || (B_A_JA_P && B_A_JA_M)) || (B_B_JA_P && B_B_JA_M)) || (B_C_JA_P && B_C_JA_M)))
        {
            _ERRORID = (DINT)548;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            _ERROR = (BOOL)TRUE;
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
            _ERRORID = (DINT)590;
            _ERROR = (BOOL)TRUE;
            return;
        };

        JA_MOVETYPECHANGED = (JA_MOVETYPEACTIVE != JA_MOVETYPELAST);
        if (JA_MOVETYPECHANGED)
        {
            M_EXECUTEABORT = (BOOL)TRUE;
        }

        JA_COORDSYSACTIVE.BASE = COORDINATESYSTEM.BASE;
        JA_BASECHANGED = (JA_COORDSYSLAST.BASE != JA_COORDSYSACTIVE.BASE);
        if (JA_BASECHANGED)
        {
            M_EXECUTEABORT = (BOOL)TRUE;
        }

        JA_COORDSYSACTIVE.TOOL = COORDINATESYSTEM.TOOL;
        JA_TOOLCHANGED = (JA_COORDSYSLAST.TOOL != JA_COORDSYSACTIVE.TOOL);
        if (JA_TOOLCHANGED)
        {
            M_EXECUTEABORT = (BOOL)TRUE;
        }

        JA_COORDSYSACTIVE.IPO_MODE = COORDINATESYSTEM.IPO_MODE;
        JA_IPOCHANGED = (JA_COORDSYSLAST.IPO_MODE != JA_COORDSYSACTIVE.IPO_MODE);
        if (JA_IPOCHANGED)
        {
            M_EXECUTEABORT = (BOOL)TRUE;
        }


        if (JOGADVANCED)
        {
            JA_BUTTONACTIVE = ((((((((((((((((((((((((((((((((((((B_A1_JA_P) || B_A1_JA_M) || B_A2_JA_P) || B_A2_JA_M) || B_A3_JA_P) || B_A3_JA_M) || B_A4_JA_P) || B_A4_JA_M) || B_A5_JA_P) || B_A5_JA_M) || B_A6_JA_P) || B_A6_JA_M) || B_E1_JA_P) || B_E1_JA_M) || B_E2_JA_P) || B_E2_JA_M) || B_E3_JA_P) || B_E3_JA_M) || B_E4_JA_P) || B_E4_JA_M) || B_E5_JA_P) || B_E5_JA_M) || B_E6_JA_P) || B_E6_JA_M) || B_X_JA_P) || B_X_JA_M) || B_Y_JA_P) || B_Y_JA_M) || B_Z_JA_P) || B_Z_JA_M) || B_A_JA_P) || B_A_JA_M) || B_B_JA_P) || B_B_JA_M) || B_C_JA_P) || B_C_JA_M);

            if (JA_BUTTONACTIVE)
            {
                if (B_A1_JA_P) { JA_STATE_VAL = 1; };  // A1 +
                if (B_A1_JA_M) { JA_STATE_VAL = 2; };  // A1 -
                if (B_A2_JA_P) { JA_STATE_VAL = 3; };  // A2 +
                if (B_A2_JA_M) { JA_STATE_VAL = 4; };  // A2 -
                if (B_A3_JA_P) { JA_STATE_VAL = 5; };  // A3 +
                if (B_A3_JA_M) { JA_STATE_VAL = 6; };  // A3 -
                if (B_A4_JA_P) { JA_STATE_VAL = 7; };  // A4 +
                if (B_A4_JA_M) { JA_STATE_VAL = 8; };  // A4 -
                if (B_A5_JA_P) { JA_STATE_VAL = 9; };  // A5 +
                if (B_A5_JA_M) { JA_STATE_VAL = 10; }; // A5 -
                if (B_A6_JA_P) { JA_STATE_VAL = 11; }; // A6 +
                if (B_A6_JA_M) { JA_STATE_VAL = 12; }; // A6 -
                if (B_E1_JA_P) { JA_STATE_VAL = 13; }; // E1 +
                if (B_E1_JA_M) { JA_STATE_VAL = 14; }; // E1 -
                if (B_E2_JA_P) { JA_STATE_VAL = 15; }; // E2 +
                if (B_E2_JA_M) { JA_STATE_VAL = 16; }; // E2 -
                if (B_E3_JA_P) { JA_STATE_VAL = 17; }; // E3 +
                if (B_E3_JA_M) { JA_STATE_VAL = 18; }; // E3 -
                if (B_E4_JA_P) { JA_STATE_VAL = 19; }; // E4 +
                if (B_E4_JA_M) { JA_STATE_VAL = 20; }; // E4 -
                if (B_E5_JA_P) { JA_STATE_VAL = 21; }; // E5 +
                if (B_E5_JA_M) { JA_STATE_VAL = 22; }; // E5 -
                if (B_E6_JA_P) { JA_STATE_VAL = 23; }; // E6 +
                if (B_E6_JA_M) { JA_STATE_VAL = 24; }; // E6 -
                if (B_X_JA_P) { JA_STATE_VAL = 25; }; // X +
                if (B_X_JA_M) { JA_STATE_VAL = 26; }; // X -
                if (B_Y_JA_P) { JA_STATE_VAL = 27; }; // Y +
                if (B_Y_JA_M) { JA_STATE_VAL = 28; }; // Y -
                if (B_Z_JA_P) { JA_STATE_VAL = 29; }; // Z +
                if (B_Z_JA_M) { JA_STATE_VAL = 30; }; // Z -
                if (B_A_JA_P) { JA_STATE_VAL = 31; }; // A +
                if (B_A_JA_M) { JA_STATE_VAL = 32; }; // A -
                if (B_B_JA_P) { JA_STATE_VAL = 33; }; // B +
                if (B_B_JA_M) { JA_STATE_VAL = 34; }; // B -
                if (B_C_JA_P) { JA_STATE_VAL = 35; }; // C +
                if (B_C_JA_M) { JA_STATE_VAL = 36; }; // C -
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
            //M_EXECUTEABORT = (BOOL)TRUE; // Jog Advanced deactive-> mxa_Abort
        }
        // Call FB KRC_Move_1
        KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
        KRC_MOVE_1.CMDID = (DINT)1;
        KRC_MOVE_1.EXECUTECMD = (JOGADVANCED && (_ERRORID == (DINT)0) && !(M_EXECUTEABORT));
        KRC_MOVE_1.MOVETYPE = M_MOVETYPE;
        KRC_MOVE_1.ACTPOSITION = M_POSITION;
        KRC_MOVE_1.AXISPOSITION = M_AXISPOSITION;
        KRC_MOVE_1.VELOCITY = VELOCITY;
        KRC_MOVE_1.ACCELERATION = ACCELERATION;
        KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
        KRC_MOVE_1.ORITYPE = 0;
        KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
        KRC_MOVE_1.POSVALIDS = (BOOL)FALSE;
        KRC_MOVE_1.POSVALIDT = (BOOL)FALSE;
        KRC_MOVE_1.BUFFERMODE = 1;
        KRC_MOVE_1.OnCycle();

        _ACTIVE = KRC_MOVE_1.ACTIVE;
        _ERRORID = KRC_MOVE_1.ERRORID;
        _ERROR = (_ERRORID != (DINT)0);

        // Call FB KRC_Abort_1
        KRC_ABORT_1.AXISGROUPIDX = AXISGROUPIDX;
        KRC_ABORT_1.EXECUTECMD = M_EXECUTEABORT;
        KRC_ABORT_1.OnCycle();

        if ((KRC_ABORT_1.ERROR || KRC_ABORT_1.DONE))
        {
            M_EXECUTEABORT = (BOOL)FALSE;
        };
        _ERRORID = KRC_ABORT_1.ERRORID;

        // Abort -> program jumps out of mxA_Move returns to mxA_CommandDispatcher -> Busy output reset
        if (JOGADVANCED && !KRC_MOVE_1.ABORTED)
        {
            _BUSY = (BOOL)TRUE;
        }
        else if (JOGADVANCED && KRC_MOVE_1.ABORTED)
        {
            _BUSY = (BOOL)FALSE;
        }

        if (JOGADVANCED && ((MOVETYPE == 1) || (MOVETYPE == 2)) && _BUSY)
        {
            _ACTIVE = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.PRO_MOVE;
        }

        JA_MOVETYPELAST = JA_MOVETYPEACTIVE;
        JA_COORDSYSLAST.BASE = JA_COORDSYSACTIVE.BASE;
        JA_COORDSYSLAST.TOOL = JA_COORDSYSACTIVE.TOOL;
        JA_COORDSYSLAST.IPO_MODE = JA_COORDSYSACTIVE.IPO_MODE;
    }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOGLINEARRELATIVE
 ******************************************************************************/
class KRC_JOGLINEARRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_JOGLINEARRELATIVE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = (DINT)1;
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 3;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_JOGTOOLRELATIVE
 ******************************************************************************/
class KRC_JOGTOOLRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_JOGTOOLRELATIVE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = (DINT)1;
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 4;
      KRC_MOVE_1.ACTPOSITION = POSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.ORITYPE = ORITYPE;
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = 1;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDcheckPos
 ******************************************************************************/

class KRC_LDDcheckPos
{
    /* VAR_INPUT*/

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;

    /* VAR_OUTPUT*/

public:
    const BOOL &BUSY;
    const BOOL &DONE;
    const BOOL &ERROR;
    const DINT &ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _DONE;
    BOOL _ERROR;
    DINT _ERRORID;

    /* VAR */
private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
    REAL ERR_STATUS;
    DINT NERR;
    DINT NSTATE;

public:
    KRC_LDDcheckPos()
        : MXA_EXECUTECOMMAND_1()
        , ERR_STATUS(0)
        , NERR(0)
        , NSTATE(0)
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , BUSY(_BUSY)
        , DONE(_DONE)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {
        _ERRORID = (DINT)0;

        if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5))
        {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }

        if (!EXECUTECMD)
        {
            NSTATE = (DINT)0;
        }

        // Execute LDD check pos function
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)61;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();

        if ((MXA_EXECUTECOMMAND_1.READCMDDATARET && (NSTATE == 0)))
        {
            ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
            NSTATE = (DINT)1;
        }

        if (MXA_EXECUTECOMMAND_1.ERROR)
        {
            NSTATE = 9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
        }

        if (NSTATE == 1)
        {
            NERR = REAL_TO_INT(ERR_STATUS);
            switch (NERR)
            {
            case -1: // Check of LDD Installation (LDD in EXT) failed (Err=-1)!
                _ERRORID = (DINT)550;
                break;
            case -2: // Check of LDD Installation (LDD in EXT) failed (Err=-2)!
                _ERRORID = (DINT)551;
                break;
            case -3: // Check of LDD Installation (LDD in EXT) failed (Err=-3)!
                _ERRORID = (DINT)552;
                break;
            case -40: // Default settings not correctly finished (Err=-40)!
                _ERRORID = (DINT)553;
                break;
            case -41: // Default settings not correctly finished (Err=-41)!
                _ERRORID = (DINT)554;
                break;
            case -42: // Default settings not correctly finished (Err=-42)!
                _ERRORID = (DINT)555;
                break;
            case -45: // A4 < 0.0 ... Move A4 to 0.0
                _ERRORID = (DINT)556;
                break;
            case -46: // A4 > 0.0 ... Move A4 to 0.0
                _ERRORID = (DINT)557;
                break;
            case -102: // Axis ranges: A2 / A3 not valid!
                _ERRORID = (DINT)558;
                break;
            case -103: // Axis ranges: A3 range not valid!
                _ERRORID = (DINT)559;
                break;
            case -104: // Axis position: A4 position not valid!
                _ERRORID = (DINT)560;
                break;
            case -105: // Axis ranges: A5 range not valid!
                _ERRORID = (DINT)561;
                break;
            case -106: // Axis ranges: A6 range not valid!
                _ERRORID = (DINT)562;
                break;
            case -111: // Axis ranges: A1 too close to the lower limit!
                _ERRORID = (DINT)563;
                break;
            case -112: // Axis ranges: A2 too close to the lower limit!
                _ERRORID = (DINT)564;
                break;
            case -113: // Axis ranges: A3 too close to the lower limit!
                _ERRORID = (DINT)565;
                break;
            case -115: // Axis ranges: A5 too close to the lower limit!
                _ERRORID = (DINT)566;
                break;
            case -116: // Axis ranges: A6 too close to the lower limit!
                _ERRORID = (DINT)567;
                break;
            case -121: // Axis ranges: A1 too close to the upper limit!
                _ERRORID = (DINT)568;
                break;
            case -122: // Axis ranges: A2 too close to the upper limit!
                _ERRORID = (DINT)569;
                break;
            case -123: // Axis ranges: A3 too close to the upper limit!
                _ERRORID = (DINT)570;
                break;
            case -125: // Axis ranges: A5 too close to the upper limit!
                _ERRORID = (DINT)571;
                break;
            case -126: // Axis ranges: A6 range not valid!
                _ERRORID = (DINT)572;
                break;
            default:
                _ERRORID = (DINT)0;
                break;
            }
        }

        _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
        _DONE = (MXA_EXECUTECOMMAND_1.DONE && (NSTATE == 1));
        _ERROR = (_ERRORID != (DINT)0);
    }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDCONFIG
 ******************************************************************************/

class KRC_LDDCONFIG
{
    /* VAR_INPUT*/

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;
    INT LOADA3SETTINGS;
    BOOL WARMUP;
    REAL M_A3;
    REAL X_A3;
    REAL Y_A3;
    REAL Z_A3;
    REAL A_A3;
    REAL B_A3;
    REAL C_A3;
    REAL JX_A3;
    REAL JY_A3;
    REAL JZ_A3;
    REAL MASS;

    /* VAR_OUTPUT*/

public:
    const BOOL &BUSY;
    const BOOL &DONE;
    const BOOL &ERROR;
    const DINT &ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _DONE;
    BOOL _ERROR;
    DINT _ERRORID;

    /* VAR */
private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
    DINT NORDERID;
    REAL ERR_STATUS;
    DINT NERR;
    DINT NSTATE;

public:
    KRC_LDDCONFIG()
        : MXA_EXECUTECOMMAND_1()
        , NORDERID(0)
        , ERR_STATUS(0)
        , NERR(0)
        , NSTATE(0)
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , LOADA3SETTINGS(0)
        , WARMUP((BOOL)FALSE)
        , M_A3(0)
        , X_A3(0)
        , Y_A3(0)
        , Z_A3(0)
        , A_A3(0)
        , B_A3(0)
        , C_A3(0)
        , JX_A3(0)
        , JY_A3(0)
        , JZ_A3(0)
        , MASS(0)
        , BUSY(_BUSY)
        , DONE(_DONE)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {
        _ERRORID = (DINT)0;

        if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5))
        {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }

        if (!EXECUTECMD)
        {
            NSTATE = (DINT)0;
        }

        //Execute LDD config function
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)60;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();

        if (MXA_EXECUTECOMMAND_1.WRITECMDPAR) {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(LOADA3SETTINGS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = WARMUP;
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
            NSTATE = (DINT)1;
        }

        if (NSTATE == 1)
        {
            NERR = REAL_TO_INT(ERR_STATUS);
            switch (NERR)
            {
            case -1: // Check of LDD Installation (LDD in EXT) failed (Err=-1)!
                _ERRORID = (DINT)550;
                break;
            case -2: // Check of LDD Installation (LDD in EXT) failed (Err=-2)!
                _ERRORID = (DINT)551;
                break;
            case -3: // Check of LDD Installation (LDD in EXT) failed (Err=-3)!
                _ERRORID = (DINT)552;
                break;
            case -40: // Default settings not correctly finished (Err=-40)!
                _ERRORID = (DINT)553;
                break;
            case -41: // Default settings not correctly finished (Err=-41)!
                _ERRORID = (DINT)554;
                break;
            case -42: // Default settings not correctly finished (Err=-42)!
                _ERRORID = (DINT)555;
                break;
            case -45: // A4 < 0.0 ... Move A4 to 0.0
                _ERRORID = (DINT)556;
                break;
            case -46: // A4 > 0.0 ... Move A4 to 0.0
                _ERRORID = (DINT)557;
                break;
            case -102: // Axis ranges: A2 / A3 not valid!
                _ERRORID = (DINT)558;
                break;
            case -103: // Axis ranges: A3 range not valid!
                _ERRORID = (DINT)559;
                break;
            case -104: // Axis position: A4 position not valid!
                _ERRORID = (DINT)560;
                break;
            case -105: // Axis ranges: A5 range not valid!
                _ERRORID = (DINT)561;
                break;
            case -106: // Axis ranges: A6 range not valid!
                _ERRORID = (DINT)562;
                break;
            case -111: // Axis ranges: A1 too close to the lower limit!
                _ERRORID = (DINT)563;
                break;
            case -112: // Axis ranges: A2 too close to the lower limit!
                _ERRORID = (DINT)564;
                break;
            case -113: // Axis ranges: A3 too close to the lower limit!
                _ERRORID = (DINT)565;
                break;
            case -115: // Axis ranges: A5 too close to the lower limit!
                _ERRORID = (DINT)566;
                break;
            case -116: // Axis ranges: A6 too close to the lower limit!
                _ERRORID = (DINT)567;
                break;
            case -121: // Axis ranges: A1 too close to the upper limit!
                _ERRORID = (DINT)568;
                break;
            case -122: // Axis ranges: A2 too close to the upper limit!
                _ERRORID = (DINT)569;
                break;
            case -123: // Axis ranges: A3 too close to the upper limit!
                _ERRORID = (DINT)570;
                break;
            case -125: // Axis ranges: A5 too close to the upper limit!
                _ERRORID = (DINT)571;
                break;
            case -126: // Axis ranges: A6 range not valid!
                _ERRORID = (DINT)572;
                break;
            default:
                _ERRORID = (DINT)0;
                break;
            }
        }

        _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
        _DONE = (MXA_EXECUTECOMMAND_1.DONE && (NSTATE == 1));
        _ERROR = (_ERRORID != (DINT)0);
    }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDSTART
 ******************************************************************************/

class KRC_LDDSTART
{
    /* VAR_INPUT */

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;
    INT TOOL;

    /* VAR_OUTPUT*/

public:
    const BOOL& BUSY;
    const BOOL& DONE;
    const BOOL& ERROR;
    const DINT& ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _DONE;
    BOOL _ERROR;
    DINT _ERRORID;

    /* VAR */

private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
    DINT NORDERID;
    DINT NSTATE;
    DINT NERR;
    REAL ERR_STATUS;

public:
    KRC_LDDSTART()
        : MXA_EXECUTECOMMAND_1()
        , MXA_EXECUTECOMMAND_2()
        , NORDERID(0)
        , ERR_STATUS(0)
        , NERR(0)
        , NSTATE(0)
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , TOOL(0)
        , BUSY(_BUSY)
        , DONE(_DONE)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {
        _ERRORID = (DINT)0;

        if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)) {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }
        else
        {
            if (!EXECUTECMD)
            {
                _ERRORID = (DINT)0;
            }
        }

        if (!EXECUTECMD)
        {
            NSTATE = (DINT)0;
            NORDERID = (DINT)0;
        }

        if (EXECUTECMD && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE < 100))
        {
            _ERRORID = (DINT)589;
            _ERROR = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            return;
        }

        //Execute LDD start function
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && NSTATE == 0);
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)64;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();

        if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 0) {

            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(TOOL);
            NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
        }

        if (MXA_EXECUTECOMMAND_1.DONE && NSTATE == 0)
        {
            NSTATE = (DINT)1;
        }

        if (MXA_EXECUTECOMMAND_1.ERROR)
        {
            NSTATE = (DINT)9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
        }

        //Get return values if error happens
        MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)));
        MXA_EXECUTECOMMAND_2.CMDID = (DINT)65;
        MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
        MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_2.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_2.OnCycle();

        if (MXA_EXECUTECOMMAND_2.WRITECMDPAR && NSTATE == 1)
        {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
        }

        if (MXA_EXECUTECOMMAND_2.READCMDDATARET && NSTATE == 1)
        {
            ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
            NSTATE = (DINT)2;
        }

        if (MXA_EXECUTECOMMAND_2.ERROR)
        {
            NSTATE = (DINT)9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
        }

        _BUSY = (MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY);
        _DONE = MXA_EXECUTECOMMAND_2.DONE;

        if (NSTATE == 2)
        {
            NERR = REAL_TO_INT(ERR_STATUS);
            switch (NERR)
            {
            case -1: // Check of LDD Installation (LDD in EXT) failed (Err=-1)!
                _ERRORID = (DINT)550;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -2: // Check of LDD Installation (LDD in EXT) failed (Err=-2)!
                _ERRORID = (DINT)551;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -3: // Check of LDD Installation (LDD in EXT) failed (Err=-3)!
                _ERRORID = (DINT)552;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -4: // LDD configuration not valid!
                _ERRORID = (DINT)574;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -5: // LDD KRL Program not correctly finished!
                _ERRORID = (DINT)575;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -6: // Kuka.Load 5 result unknown!
                _ERRORID = (DINT)576;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -40: // Default settings not correctly finished (Err=-40)!
                _ERRORID = (DINT)553;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -41: // Default settings not correctly finished (Err=-41)!
                _ERRORID = (DINT)554;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -42: // Default settings not correctly finished (Err=-42)!
                _ERRORID = (DINT)555;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -45: // A4 < 0.0 ... Move A4 to 0.0
                _ERRORID = (DINT)556;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -46: // A4 > 0.0 ... Move A4 to 0.0
                _ERRORID = (DINT)557;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -102: // Axis ranges: A2 / A3 not valid!
                _ERRORID = (DINT)558;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -103: // Axis ranges: A3 range not valid!
                _ERRORID = (DINT)559;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -104: // Axis position: A4 position not valid!
                _ERRORID = (DINT)560;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -105: // Axis ranges: A5 range not valid!
                _ERRORID = (DINT)561;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -106: // Axis ranges: A6 range not valid!
                _ERRORID = (DINT)562;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -111: // Axis ranges: A1 too close to the lower limit!
                _ERRORID = (DINT)563;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -112: // Axis ranges: A2 too close to the lower limit!
                _ERRORID = (DINT)564;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -113: // Axis ranges: A3 too close to the lower limit!
                _ERRORID = (DINT)565;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -115: // Axis ranges: A5 too close to the lower limit!
                _ERRORID = (DINT)566;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -116: // Axis ranges: A6 too close to the lower limit!
                _ERRORID = (DINT)567;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -121: // Axis ranges: A1 too close to the upper limit!
                _ERRORID = (DINT)568;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -122: // Axis ranges: A2 too close to the upper limit!
                _ERRORID = (DINT)569;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -123: // Axis ranges: A3 too close to the upper limit!
                _ERRORID = (DINT)570;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -125: // Axis ranges: A5 too close to the upper limit!
                _ERRORID = (DINT)571;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -126: // Axis ranges: A6 range not valid!
                _ERRORID = (DINT)572;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case 1: // LDD_LOAD_RESULT = #STATOVL
                _ERRORID = (DINT)577;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case 2: // LDD_LOAD_RESULT = #DYNOVL
                _ERRORID = (DINT)578;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case 3: // LDD_LOAD_RESULT = #OVL
                _ERRORID = (DINT)579;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case 4: // LDD_LOAD_RESULT = #SLOOR
                _ERRORID = (DINT)580;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case 5: // Tool Number=-1: $config.dat unchanged!
                _ERRORID = (DINT)581;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -11: // LDD_start not correctly finished!
                _ERRORID = (DINT)582;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -12: // Kuka.Load 5 not correctly finished!
                _ERRORID = (DINT)583;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -13: // Tool number not correct!
                _ERRORID = (DINT)584;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -10: // Internal Error
                _ERRORID = (DINT)587;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -20: // Internal Error
                _ERRORID = (DINT)588;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            default:
                _ERRORID = (DINT)0;
                break;
            }
        }

        _ERROR = (_ERRORID != (DINT)0);
    }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_LDDTESTRUN
 ******************************************************************************/

class KRC_LDDTESTRUN
{
    /* VAR_INPUT*/

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;

    /* VAR_OUTPUT*/

public:
    const BOOL& BUSY;
    const BOOL& DONE;
    const BOOL& ERROR;
    const DINT& ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _DONE;
    BOOL _ERROR;
    DINT _ERRORID;

    /* VAR */

private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
    DINT NSTATE;
    DINT NERR;
    REAL ERR_STATUS;
    DINT NORDERID;

public:
    KRC_LDDTESTRUN()
        : MXA_EXECUTECOMMAND_1()
        , MXA_EXECUTECOMMAND_2()
        , NORDERID(0)
        , ERR_STATUS(0)
        , NERR(0)
        , NSTATE(0)
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , BUSY(_BUSY)
        , DONE(_DONE)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {
        _ERRORID = (DINT)0;

        if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)) {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }
        else
        {
            if (!EXECUTECMD)
            {
                _ERRORID = (DINT)0;
            }
        }

        if (!EXECUTECMD)
        {
            NSTATE = (DINT)0;
            NORDERID = (DINT)0;
        }

        if (EXECUTECMD && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE > 10))
        {
            _ERRORID = (DINT)586;
            _ERROR = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
            return;
        }

        // Execute LDD test function
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && NSTATE == 0);
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)62;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = 1;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();

        if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 0)
        {

            NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
        }

        if (MXA_EXECUTECOMMAND_1.DONE && NSTATE == 0)
        {
            NSTATE = (DINT)1;
        }

        if (MXA_EXECUTECOMMAND_1.ERROR)
        {
            NSTATE = (DINT)9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
        }

        // Get return values if error happens
        MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)));
        MXA_EXECUTECOMMAND_2.CMDID = (DINT)63;
        MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
        MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_2.IGNOREINIT = (BOOL)FALSE;
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
            NSTATE = (DINT)9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
        }

        _BUSY = (MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY);
        _DONE = MXA_EXECUTECOMMAND_2.DONE;

        if (NSTATE == 2)
        {
            NERR = REAL_TO_INT(ERR_STATUS);
            switch (NERR)
            {
            case -4: // LDD configuration not valid!
                _ERRORID = (DINT)574;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -7: // LDD KRL Test run Program not correctly finished!
                _ERRORID = (DINT)585;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            default:
                _ERRORID = (DINT)0;
                break;
            }
        }

        _ERROR = (_ERRORID != (DINT)0);
    }
};

  /******************************************************************************
   * FUNCTION_BLOCK KRC_LDDWRITELOAD
   ******************************************************************************/

class KRC_LDDWRITELOAD
{
    /* VAR_INPUT */

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;
    INT BUFFERMODE;
    INT TOOL;

    /* VAR_OUTPUT*/

public:
    const BOOL& BUSY;
    const BOOL& DONE;
    const BOOL& ERROR;
    const DINT& ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _DONE;
    BOOL _ERROR;
    DINT _ERRORID;

    /* VAR */

private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
    DINT NORDERID;
    DINT NSTATE;
    DINT COPY_OF_NSTATE;
    DINT NERR;
    REAL ERR_STATUS;

public:
    KRC_LDDWRITELOAD()
        : MXA_EXECUTECOMMAND_1()
        , MXA_EXECUTECOMMAND_2()
        , NORDERID(0)
        , NSTATE(0)
        , COPY_OF_NSTATE(0)
        , NERR(0)
        , ERR_STATUS(0)
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , BUFFERMODE(0)
        , TOOL(0)
        , BUSY(_BUSY)
        , DONE(_DONE)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {
        _ERRORID = (DINT)0;

        if ((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)) {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }
        else
        {
            if (!EXECUTECMD)
            {
                _ERRORID = (DINT)0;
            }
        }

        if (!EXECUTECMD)
        {
            NSTATE = (DINT)0;
            NORDERID = (DINT)0;
        }

        // Execute LDD write load function
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && NSTATE == 0);
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)66;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();

        if (MXA_EXECUTECOMMAND_1.WRITECMDPAR && NSTATE == 0) {

            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(TOOL);
            NORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
        }

        if (MXA_EXECUTECOMMAND_1.DONE && NSTATE == 0)
        {
            NSTATE = (DINT)1;
        }

        if (MXA_EXECUTECOMMAND_1.ERROR)
        {
            NSTATE = (DINT)9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
        }

        // Get return values if error happens
        MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && ((NSTATE == 1) || (NSTATE == 2)));
        MXA_EXECUTECOMMAND_2.CMDID = (DINT)67;
        MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
        MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_2.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_2.OnCycle();

        if (MXA_EXECUTECOMMAND_2.WRITECMDPAR && NSTATE == 1)
        {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = NORDERID;
        }

        if (MXA_EXECUTECOMMAND_2.READCMDDATARET && NSTATE == 1)
        {
            ERR_STATUS = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9];
            NSTATE = (DINT)2;
        }

        if (MXA_EXECUTECOMMAND_2.ERROR)
        {
            NSTATE = (DINT)9;
            _ERROR = (BOOL)TRUE;
            _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
        }

        _BUSY = (MXA_EXECUTECOMMAND_1.BUSY || MXA_EXECUTECOMMAND_2.BUSY);
        _DONE = MXA_EXECUTECOMMAND_2.DONE;

        if (NSTATE == 2)
        {
            NERR = REAL_TO_INT(ERR_STATUS);
            switch (NERR)
            {
            case 5: // Tool Number=-1: $config.dat unchanged!
                _ERRORID = (DINT)581;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -11: // LDD_start not correctly finished!
                _ERRORID = (DINT)582;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -12: // Kuka.Load 5 not correctly finished!
                _ERRORID = (DINT)583;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -13: // Tool number not correct!
                _ERRORID = (DINT)584;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -10: // Internal Error
                _ERRORID = (DINT)587;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            case -20: // Internal Error
                _ERRORID = (DINT)587;
                KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = ERRORID;
                break;
            default:
                _ERRORID = (DINT)0;
                break;
            }
        }

        _ERROR = (_ERRORID != (DINT)0);
    }
};


/******************************************************************************
 * FUNCTION_BLOCK KRC_MASREF
 ******************************************************************************/
class KRC_MASREF
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS ACTPOSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const BOOL &MASREFREQUEST;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;
   BOOL _MASREFREQUEST;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;

public:
   KRC_MASREF()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , ACTPOSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , MASREFREQUEST(_MASREFREQUEST)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _MASREFREQUEST((BOOL)FALSE)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         _MASREFREQUEST = (BOOL)FALSE;
         return;
      };
      // Call FB KRC_Move_1
      KRC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      KRC_MOVE_1.CMDID = (DINT)30;
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = 1;
      KRC_MOVE_1.ACTPOSITION = ACTPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.COORDINATESYSTEM = COORDINATESYSTEM;
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _MASREFREQUEST = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.MASTERINGTEST_REQ_INT;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVEAXISABSOLUTE
 ******************************************************************************/
class KRC_MOVEAXISABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6AXIS AXISPOSITION;
   INT VELOCITY;
   INT ACCELERATION;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;


   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6POS M_POSITION;
   INT M_ORITYPE;
   COORDSYS M_COORDINATESYSTEM;

public:
   KRC_MOVEAXISABSOLUTE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , AXISPOSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_CIRCHP()
      , M_POSITION()
      , M_ORITYPE(0)
      , M_COORDINATESYSTEM()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
      KRC_MOVE_1.EXECUTECMD = EXECUTECMD;
      KRC_MOVE_1.MOVETYPE = SWITCHMOVETYPE;
      KRC_MOVE_1.AXISPOSITION = AXISPOSITION;
      KRC_MOVE_1.VELOCITY = VELOCITY;
      KRC_MOVE_1.ACCELERATION = ACCELERATION;
      KRC_MOVE_1.ORITYPE = M_ORITYPE;
      KRC_MOVE_1.APPROXIMATE = APPROXIMATE;
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVECIRCABSOLUTE
 ******************************************************************************/
class KRC_MOVECIRCABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   E6POS CIRCHP;
   REAL ANGLE;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   INT CIRCTYPE;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVECIRCABSOLUTE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , CIRCHP()
      , ANGLE(0)
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , CIRCTYPE(0)
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_COORDINATESYSTEM()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
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
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVECIRCRELATIVE
 ******************************************************************************/
class KRC_MOVECIRCRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   E6POS CIRCHP;
   REAL ANGLE;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   INT CIRCTYPE;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVECIRCRELATIVE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , CIRCHP()
      , ANGLE(0)
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , CIRCTYPE(0)
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_COORDINATESYSTEM()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
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
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVEDIRECTABSOLUTE
 ******************************************************************************/
class KRC_MOVEDIRECTABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   INT M_ORITYPE;

public:
   KRC_MOVEDIRECTABSOLUTE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
      , M_ORITYPE(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
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
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVEDIRECTRELATIVE
 ******************************************************************************/
class KRC_MOVEDIRECTRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS ACTPOSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   INT M_ORITYPE;

public:
   KRC_MOVEDIRECTRELATIVE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , ACTPOSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
      , M_ORITYPE(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
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
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)FALSE;
      KRC_MOVE_1.POSVALIDT = (BOOL)FALSE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVELINEARABSOLUTE
 ******************************************************************************/
class KRC_MOVELINEARABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;
   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVELINEARABSOLUTE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
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
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_MOVELINEARRELATIVE
 ******************************************************************************/
class KRC_MOVELINEARRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   E6POS POSITION;
   INT VELOCITY;
   INT ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   APO APPROXIMATE;
   INT BUFFERMODE;
   BOOL SPLINEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   KRC_MOVE KRC_MOVE_1;
   INT SWITCHMOVETYPE;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   KRC_MOVELINEARRELATIVE()
      : KRC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , POSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , APPROXIMATE()
      , BUFFERMODE(0)
      , SPLINEMODE((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , SWITCHMOVETYPE(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      KRC_MOVE_1.CMDID = (DINT)1;
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
      KRC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      KRC_MOVE_1.POSVALIDS = (BOOL)FALSE;
      KRC_MOVE_1.POSVALIDT = (BOOL)FALSE;
      KRC_MOVE_1.BUFFERMODE = BUFFERMODE;
      KRC_MOVE_1.OnCycle();
      _BUSY = KRC_MOVE_1.BUSY;
      _ACTIVE = KRC_MOVE_1.ACTIVE;
      _DONE = KRC_MOVE_1.DONE;
      _ABORTED = KRC_MOVE_1.ABORTED;
      _ERRORID = KRC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALACCELERATION
 ******************************************************************************/
class KRC_READACTUALACCELERATION
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const REAL &ACC_ABS;
   const REAL &X;
   const REAL &Y;
   const REAL &Z;
   const REAL &A;
   const REAL &B;
   const REAL &C;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;
   REAL _ACC_ABS;
   REAL _X;
   REAL _Y;
   REAL _Z;
   REAL _A;
   REAL _B;
   REAL _C;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READACTUALACCELERATION()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , ACC_ABS(_ACC_ABS)
      , X(_X)
      , Y(_Y)
      , Z(_Z)
      , A(_A)
      , B(_B)
      , C(_C)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _ACC_ABS(0)
      , _X(0)
      , _Y(0)
      , _Z(0)
      , _A(0)
      , _B(0)
      , _C(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)26;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALAXISPOSITION
 ******************************************************************************/
class KRC_READACTUALAXISPOSITION
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const E6AXIS &AXISPOSITION;
   const REAL &A1;
   const REAL &A2;
   const REAL &A3;
   const REAL &A4;
   const REAL &A5;
   const REAL &A6;
   const REAL &E1;
   const REAL &E2;
   const REAL &E3;
   const REAL &E4;
   const REAL &E5;
   const REAL &E6;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   E6AXIS _AXISPOSITION;
   REAL _A1;
   REAL _A2;
   REAL _A3;
   REAL _A4;
   REAL _A5;
   REAL _A6;
   REAL _E1;
   REAL _E2;
   REAL _E3;
   REAL _E4;
   REAL _E5;
   REAL _E6;


public:
   KRC_READACTUALAXISPOSITION()
      : AXISGROUPIDX(0)
      , VALID(_VALID)
      , AXISPOSITION(_AXISPOSITION)
      , A1(_A1)
      , A2(_A2)
      , A3(_A3)
      , A4(_A4)
      , A5(_A5)
      , A6(_A6)
      , E1(_E1)
      , E2(_E2)
      , E3(_E3)
      , E4(_E4)
      , E5(_E5)
      , E6(_E6)
      , _VALID((BOOL)FALSE)
      , _AXISPOSITION()
      , _A1(0)
      , _A2(0)
      , _A3(0)
      , _A4(0)
      , _A5(0)
      , _A6(0)
      , _E1(0)
      , _E2(0)
      , _E3(0)
      , _E4(0)
      , _E5(0)
      , _E6(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = (BOOL)FALSE;
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const INT &A1;
   const INT &A2;
   const INT &A3;
   const INT &A4;
   const INT &A5;
   const INT &A6;
   const INT &E1;
   const INT &E2;
   const INT &E3;
   const INT &E4;
   const INT &E5;
   const INT &E6;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;
   INT _A1;
   INT _A2;
   INT _A3;
   INT _A4;
   INT _A5;
   INT _A6;
   INT _E1;
   INT _E2;
   INT _E3;
   INT _E4;
   INT _E5;
   INT _E6;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READACTUALAXISVELOCITY()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , A1(_A1)
      , A2(_A2)
      , A3(_A3)
      , A4(_A4)
      , A5(_A5)
      , A6(_A6)
      , E1(_E1)
      , E2(_E2)
      , E3(_E3)
      , E4(_E4)
      , E5(_E5)
      , E6(_E6)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _A1(0)
      , _A2(0)
      , _A3(0)
      , _A4(0)
      , _A5(0)
      , _A6(0)
      , _E1(0)
      , _E2(0)
      , _E3(0)
      , _E4(0)
      , _E5(0)
      , _E6(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)25;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _A1 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _A2 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _A3 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _A4 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _A5 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _A6 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _E1 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _E2 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _E3 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _E4 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _E5 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
         _E6 = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[12]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READACTUALPOSITION
 ******************************************************************************/
class KRC_READACTUALPOSITION
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const E6POS &POSITION;
   const REAL &X;
   const REAL &Y;
   const REAL &Z;
   const REAL &A;
   const REAL &B;
   const REAL &C;
   const INT &STATUS;
   const INT &TURN;
   const INT &TOOL;
   const INT &BASE;
   const INT &IPOMODE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   E6POS _ACTPOSITION;
   REAL _X;
   REAL _Y;
   REAL _Z;
   REAL _A;
   REAL _B;
   REAL _C;
   INT _STATUS;
   INT _TURN;
   INT _TOOL;
   INT _BASE;
   INT _IPOMODE;


public:
   KRC_READACTUALPOSITION()
      : AXISGROUPIDX(0)
      , VALID(_VALID)
      , POSITION(_ACTPOSITION)
      , X(_X)
      , Y(_Y)
      , Z(_Z)
      , A(_A)
      , B(_B)
      , C(_C)
      , STATUS(_STATUS)
      , TURN(_TURN)
      , TOOL(_TOOL)
      , BASE(_BASE)
      , IPOMODE(_IPOMODE)
      , _VALID((BOOL)FALSE)
      , _ACTPOSITION()
      , _X(0)
      , _Y(0)
      , _Z(0)
      , _A(0)
      , _B(0)
      , _C(0)
      , _STATUS(0)
      , _TURN(0)
      , _TOOL(0)
      , _BASE(0)
      , _IPOMODE(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = (BOOL)FALSE;
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
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const REAL &VALUE;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   REAL _VALUE;


public:
   KRC_READACTUALVELOCITY()
      : AXISGROUPIDX(0)
      , VALID(_VALID)
      , VALUE(_VALUE)
      , _VALID((BOOL)FALSE)
      , _VALUE(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _VALID = (BOOL)FALSE;
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const REAL &VALUE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   REAL _VALUE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READANALOGINPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , DONE(_DONE)
      , VALUE(_VALUE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _VALUE(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)11;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READANALOGOUTPUT
 ******************************************************************************/
class KRC_READANALOGOUTPUT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const REAL &VALUE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   REAL _VALUE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READANALOGOUTPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , DONE(_DONE)
      , VALUE(_VALUE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _VALUE(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)12;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1];
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READAXISGROUP
 ******************************************************************************/
class KRC_READAXISGROUP
{

   /* VAR_INPUT */

public:
   BYTE* KRC4_INPUT;
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   BOOL M_AE_RC_RDY1;
   BOOL M_AE_ALARM_STOP;
   BOOL M_AE_USER_SAF;
   BOOL M_AE_PERI_RDY;
   BOOL M_AE_ROB_CAL;
   BOOL M_AE_IO_ACTCONF;
   BOOL M_AE_STOPMESS;
   BOOL M_AE_PGNO_FBIT_REFL;
   BOOL M_AE_INT_ESTOP;
   BOOL M_AE_PRO_ACT;
   BOOL M_AE_PGNO_REQ;
   BOOL M_AE_APPL_RUN;
   BOOL M_AE_PRO_MOVE;
   BOOL M_AE_IN_HOME;
   BOOL M_AE_ON_PATH;
   BOOL M_AE_NEAR_POSRET;
   BOOL M_AE_ROB_STOPPED;
   BOOL M_AE_T1;
   BOOL M_AE_T2;
   BOOL M_AE_AUT;
   BOOL M_AE_EXT;
   BOOL M_BRAKETEST_MONTIME;
   BOOL M_BRAKETEST_REQ_INT;
   BOOL M_BRAKETEST_WORK;
   BOOL M_BRAKES_OK;
   BOOL M_BRAKETEST_WARN;
   BOOL M_ABORTACTIVE;
   BOOL M_BRAKEACTIVE;
   BOOL M_KCP_CONNECT;
   BOOL M_TOUCHUP;
   BOOL M_MASTEST_REQ_INT;
   BOOL M_MASTESTSWITCH_OK;
   BOOL M_POS_ACT_VALID;
   INT M_HEARTBEATSUBMIT;
   INT M_IN_VAL_1TO8;
   INT M_TOUCHUP_POSNO;
   DINT M_SR_ORDER1_ID;
   DINT M_SR_ORDER2_ID;
   DINT M_SR_ORDER3_ID;
   DINT M_SR_ORDER4_ID;
   DINT M_SR_ORDER5_ID;
   DINT M_SR_ORDER6_ID;
   DINT M_SR_ORDER7_ID;
   DINT M_SR_ORDER8_ID;
   DINT M_SR_ORDER9_ID;
   DINT M_SR_ORDER10_ID;
   INT M_SR_ORDER1_STATE;
   INT M_SR_ORDER2_STATE;
   INT M_SR_ORDER3_STATE;
   INT M_SR_ORDER4_STATE;
   INT M_SR_ORDER5_STATE;
   INT M_SR_ORDER6_STATE;
   INT M_SR_ORDER7_STATE;
   INT M_SR_ORDER8_STATE;
   INT M_SR_ORDER9_STATE;
   INT M_SR_ORDER10_STATE;
   INT M_HEARTBEATPCOS;
   INT M_OVERRIDE;
   REAL M_POSACT_X;
   REAL M_POSACT_Y;
   REAL M_POSACT_Z;
   REAL M_POSACT_A;
   REAL M_POSACT_B;
   REAL M_POSACT_C;
   DINT M_POSACT_STATUS;
   INT M_POSACT_TURN;
   SINT M_TOOLACT;
   SINT M_BASEACT;
   INT M_IPOMODE;
   REAL M_AXISACT_A1;
   REAL M_AXISACT_A2;
   REAL M_AXISACT_A3;
   REAL M_AXISACT_A4;
   REAL M_AXISACT_A5;
   REAL M_AXISACT_A6;
   REAL M_AXISACT_A7;
   REAL M_AXISACT_A8;
   REAL M_AXISACT_A9;
   REAL M_AXISACT_A10;
   REAL M_AXISACT_A11;
   REAL M_AXISACT_A12;
   REAL M_VELACT;
   INT M_WORKSTATES;
   INT M_AXWORKSTATES;
   INT M_GROUPSTATE;
   INT M_ERRORID;
   INT M_ERRORIDSUB;
   DINT M_ACTIVEPOSORDERID;
   DINT M_ACTIVEORDERIDB;
   INT M_QUEUECOUNT;
   INT M_IR_STATUS1;
   INT M_IR_STATUS2;
   INT M_IR_STATUS3;
   INT M_IR_STATUS4;
   INT M_IR_STATUS5;
   INT M_IR_STATUS6;
   INT M_IR_STATUS7;
   INT M_IR_STATUS8;
   INT M_ERRORIDPCOS;
   INT M_FREE_FOR_WOV;
   INT M_TRANSMISSIONNORET;
   DINT M_ORDERIDRET;
   DINT M_CMDIDRET;
   DINT M_CMDDATARETCS;
   DINT M_RESERVE190;
   REAL M_CMDDATARET1;
   REAL M_CMDDATARET2;
   REAL M_CMDDATARET3;
   REAL M_CMDDATARET4;
   REAL M_CMDDATARET5;
   REAL M_CMDDATARET6;
   REAL M_CMDDATARET7;
   REAL M_CMDDATARET8;
   REAL M_CMDDATARET9;
   REAL M_CMDDATARET10;
   REAL M_CMDDATARET11;
   REAL M_CMDDATARET12;
   DINT M_RESERVE242;
   DWORD NCHECKSUM;
   REAL FTMP;
   DINT NTMP1;
   REAL FTMP1;
   BOOL BTMP1;
   INT I;
   BOOL ONF_TRIG;
   BOOL ENABLETONSUBMIT;
   BOOL ENABLETONPCOS;
   BOOL M_INITOK;
   INT M_HEARTBEATLAST;
   INT M_HEARTBEATLASTPCOS;
   TIME HEARTBEATTO;
   TON TON_1;
   TON TON_2;
   DINT M_LASTORDERID;
   R_TRIG R_TRIG_1;
   BOOL M_CONNECTIONOK;
   BOOL M_F_TRIG;
   INT M_FIRSTCYCLES;
   BOOL RETB;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;

public:
   KRC_READAXISGROUP()
      : M_AE_RC_RDY1((BOOL)FALSE)
      , M_AE_ALARM_STOP((BOOL)FALSE)
      , M_AE_USER_SAF((BOOL)FALSE)
      , M_AE_PERI_RDY((BOOL)FALSE)
      , M_AE_ROB_CAL((BOOL)FALSE)
      , M_AE_IO_ACTCONF((BOOL)FALSE)
      , M_AE_STOPMESS((BOOL)FALSE)
      , M_AE_PGNO_FBIT_REFL((BOOL)FALSE)
      , M_AE_INT_ESTOP((BOOL)FALSE)
      , M_AE_PRO_ACT((BOOL)FALSE)
      , M_AE_PGNO_REQ((BOOL)FALSE)
      , M_AE_APPL_RUN((BOOL)FALSE)
      , M_AE_PRO_MOVE((BOOL)FALSE)
      , M_AE_IN_HOME((BOOL)FALSE)
      , M_AE_ON_PATH((BOOL)FALSE)
      , M_AE_NEAR_POSRET((BOOL)FALSE)
      , M_AE_ROB_STOPPED((BOOL)FALSE)
      , M_AE_T1((BOOL)FALSE)
      , M_AE_T2((BOOL)FALSE)
      , M_AE_AUT((BOOL)FALSE)
      , M_AE_EXT((BOOL)FALSE)
      , M_BRAKETEST_MONTIME((BOOL)FALSE)
      , M_BRAKETEST_REQ_INT((BOOL)FALSE)
      , M_BRAKETEST_WORK((BOOL)FALSE)
      , M_BRAKES_OK((BOOL)FALSE)
      , M_BRAKETEST_WARN((BOOL)FALSE)
      , M_ABORTACTIVE((BOOL)FALSE)
      , M_BRAKEACTIVE((BOOL)FALSE)
      , M_KCP_CONNECT((BOOL)FALSE)
      , M_TOUCHUP((BOOL)FALSE)
      , M_MASTEST_REQ_INT((BOOL)FALSE)
      , M_MASTESTSWITCH_OK((BOOL)FALSE)
      , M_POS_ACT_VALID((BOOL)FALSE)
      , M_HEARTBEATSUBMIT(0)
      , M_IN_VAL_1TO8(0)
      , M_TOUCHUP_POSNO(0)
      , M_SR_ORDER1_ID(0)
      , M_SR_ORDER2_ID(0)
      , M_SR_ORDER3_ID(0)
      , M_SR_ORDER4_ID(0)
      , M_SR_ORDER5_ID(0)
      , M_SR_ORDER6_ID(0)
      , M_SR_ORDER7_ID(0)
      , M_SR_ORDER8_ID(0)
      , M_SR_ORDER9_ID(0)
      , M_SR_ORDER10_ID(0)
      , M_SR_ORDER1_STATE(0)
      , M_SR_ORDER2_STATE(0)
      , M_SR_ORDER3_STATE(0)
      , M_SR_ORDER4_STATE(0)
      , M_SR_ORDER5_STATE(0)
      , M_SR_ORDER6_STATE(0)
      , M_SR_ORDER7_STATE(0)
      , M_SR_ORDER8_STATE(0)
      , M_SR_ORDER9_STATE(0)
      , M_SR_ORDER10_STATE(0)
      , M_HEARTBEATPCOS(0)
      , M_OVERRIDE(0)
      , M_POSACT_X(0)
      , M_POSACT_Y(0)
      , M_POSACT_Z(0)
      , M_POSACT_A(0)
      , M_POSACT_B(0)
      , M_POSACT_C(0)
      , M_POSACT_STATUS(0)
      , M_POSACT_TURN(0)
      , M_TOOLACT(0)
      , M_BASEACT(0)
      , M_IPOMODE(0)
      , M_AXISACT_A1(0)
      , M_AXISACT_A2(0)
      , M_AXISACT_A3(0)
      , M_AXISACT_A4(0)
      , M_AXISACT_A5(0)
      , M_AXISACT_A6(0)
      , M_AXISACT_A7(0)
      , M_AXISACT_A8(0)
      , M_AXISACT_A9(0)
      , M_AXISACT_A10(0)
      , M_AXISACT_A11(0)
      , M_AXISACT_A12(0)
      , M_VELACT(0)
      , M_WORKSTATES(0)
      , M_AXWORKSTATES(0)
      , M_GROUPSTATE(0)
      , M_ERRORID(0)
      , M_ERRORIDSUB(0)
      , M_ACTIVEPOSORDERID(0)
      , M_ACTIVEORDERIDB(0)
      , M_QUEUECOUNT(0)
      , M_IR_STATUS1(0)
      , M_IR_STATUS2(0)
      , M_IR_STATUS3(0)
      , M_IR_STATUS4(0)
      , M_IR_STATUS5(0)
      , M_IR_STATUS6(0)
      , M_IR_STATUS7(0)
      , M_IR_STATUS8(0)
      , M_ERRORIDPCOS(0)
      , M_FREE_FOR_WOV(0)
      , M_TRANSMISSIONNORET(0)
      , M_ORDERIDRET(0)
      , M_CMDIDRET(0)
      , M_CMDDATARETCS(0)
      , M_RESERVE190(0)
      , M_CMDDATARET1(0)
      , M_CMDDATARET2(0)
      , M_CMDDATARET3(0)
      , M_CMDDATARET4(0)
      , M_CMDDATARET5(0)
      , M_CMDDATARET6(0)
      , M_CMDDATARET7(0)
      , M_CMDDATARET8(0)
      , M_CMDDATARET9(0)
      , M_CMDDATARET10(0)
      , M_CMDDATARET11(0)
      , M_CMDDATARET12(0)
      , M_RESERVE242(0)
      , NCHECKSUM(0)
      , FTMP(0)
      , NTMP1(0)
      , FTMP1(0)
      , BTMP1((BOOL)FALSE)
      , I(0)
      , ONF_TRIG((BOOL)FALSE)
      , ENABLETONSUBMIT((BOOL)FALSE)
      , ENABLETONPCOS((BOOL)FALSE)
      , M_INITOK((BOOL)FALSE)
      , M_HEARTBEATLAST(0)
      , M_HEARTBEATLASTPCOS(0)
      , HEARTBEATTO(MKTIME(1, 0, 0))
      , TON_1()
      , TON_2()
      , M_LASTORDERID(0)
      , R_TRIG_1()
      , M_CONNECTIONOK((BOOL)FALSE)
      , M_F_TRIG((BOOL)FALSE)
      , M_FIRSTCYCLES(0)
      , RETB((BOOL)FALSE)
      , MXA_RESETCOMMAND_1()
      , KRC4_INPUT()
      , AXISGROUPIDX(0)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      if (!(M_INITOK))
      {
         M_INITOK = (BOOL)TRUE;
         if (KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT)
         {
            _ERRORID = (DINT)505;
            _ERROR = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT = (BOOL)TRUE;
         };
      };
      if ((M_FIRSTCYCLES < 100))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = (BOOL)FALSE;
         M_HEARTBEATLAST = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT = (BOOL)TRUE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKEF = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.BRAKE = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RELEASEBRAKE = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.MESSAGERESET = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.BRAKETEST_REQ_EXT = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MASTERINGTEST_REQ_EXT = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.WRITE_OUT_1TO8 = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.CONF_MESS = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.RESET = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.DRIVESON = (BOOL)FALSE;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE = (BOOL)TRUE;
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO <= (DINT)0))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO = (DINT)1000;
      };
      HEARTBEATTO = DINT_TO_TIME(KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO);
      ENABLETONSUBMIT = ((M_HEARTBEATLAST == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT > 0));
      ENABLETONPCOS = ((M_HEARTBEATLASTPCOS == KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS > 0));
      if ((((M_HEARTBEATLAST != KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT > 0)) && ((M_HEARTBEATLASTPCOS != KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS > 0))))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = (BOOL)TRUE;
      };
      // Call FB TON_1
      TON_1.IN = (ENABLETONSUBMIT || ENABLETONPCOS);
      TON_1.PT = HEARTBEATTO;
      TON_1.OnCycle();
      M_HEARTBEATLAST = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT;
      M_HEARTBEATLASTPCOS = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEATPCOS;
      if (TON_1.Q)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE = (BOOL)FALSE;
      };
      ONF_TRIG = (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && M_F_TRIG);
      M_F_TRIG = KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE;
      if (ONF_TRIG)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = (DINT)510;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED = (BOOL)FALSE;
      };
      // Call FB TON_2
      TON_2.IN = (((KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > (DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == M_LASTORDERID)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET));
      TON_2.PT = DINT_TO_TIME((KRC_AXISGROUPREFARR[AXISGROUPIDX].HEARTBEATTO * (DINT)1));
      TON_2.OnCycle();
      M_LASTORDERID = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID;
      // Call FB R_TRIG_1
      R_TRIG_1.CLK = TON_2.Q;
      R_TRIG_1.OnCycle();
      if (R_TRIG_1.Q)
      {
         _ERRORID = (DINT)511;
         _ERROR = (BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
      };
      if ((TON_2.Q && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == (DINT)0)))
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
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
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACT.STATUS = DINT_TO_INT(M_POSACT_STATUS);
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
         NCHECKSUM = (DWORD)0;
         for (I = 1; I <= 12; I += 1)
         {
            FTMP = KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[I];
            NTMP1 = REAL_TO_DINT(((FTMP - 0.5) * 10.0));
            FTMP1 = ((NTMP1 / 10) + 0.5);
            BTMP1 = (FTMP == FTMP1);
            if (BTMP1)
            {
               if ((FTMP > 0))
               {
                  FTMP = (FTMP + 0.01);
               }
               else
               {
                  FTMP = (FTMP - 0.01);
               };
            };
            if (((FTMP > 2147483500.0) || (FTMP <  -(2147483500.0))))
            {
               NCHECKSUM = 0;
            };
            NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(REAL_TO_DINT(FTMP)));
         };
         NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET));
         NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET));
         KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETCSPLC = DWORD_TO_DINT(NCHECKSUM);
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT WORKSPACENO;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const INT &WORKSPACEMODE;
   const AXBOX &WORKSPACEDATA;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   INT _WORKSPACEMODE;
   AXBOX _WORKSPACEDATA;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_2;
   INT M_WORKSPACEMODE;
   AXBOX M_WORKSPACEDATA;

public:
   KRC_READAXWORKSPACE()
      : NSTATE(0)
      , MXA_EXECUTECOMMAND_0()
      , MXA_EXECUTECOMMAND_1()
      , MXA_EXECUTECOMMAND_2()
      , M_WORKSPACEMODE(0)
      , M_WORKSPACEDATA()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , WORKSPACENO(0)
      , DONE(_DONE)
      , WORKSPACEMODE(_WORKSPACEMODE)
      , WORKSPACEDATA(_WORKSPACEDATA)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _WORKSPACEMODE(0)
      , _WORKSPACEDATA()
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      MXA_EXECUTECOMMAND_0.CMDID = (DINT)51;
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = (DINT)1;
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_WORKSPACEMODE = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)51;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = (DINT)2;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_2
      MXA_EXECUTECOMMAND_2.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_2.EXECUTE = (EXECUTECMD && (NSTATE == 2));
      MXA_EXECUTECOMMAND_2.CMDID = (DINT)51;
      MXA_EXECUTECOMMAND_2.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_2.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_2.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_2.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_2.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_2.OnCycle();
      if ((MXA_EXECUTECOMMAND_2.WRITECMDPAR && (NSTATE == 2)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = (DINT)3;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_2.ERRORID;
      };
     _DONE = (NSTATE == 3);
      if ((NSTATE == 3))
      {
         _WORKSPACEMODE = M_WORKSPACEMODE;
         _WORKSPACEDATA = M_WORKSPACEDATA;
         _ERROR = (BOOL)FALSE;
         _ERRORID = (DINT)0;
      };
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READBASEDATA
 ******************************************************************************/
class KRC_READBASEDATA
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT BASENO;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const FRAME &BASEDATA;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   FRAME _BASEDATA;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READBASEDATA()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , BASENO(0)
      , DONE(_DONE)
      , BASEDATA(_BASEDATA)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _BASEDATA()
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)22;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(BASENO);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALINPUT
 ******************************************************************************/
class KRC_READDIGITALINPUT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &VALUE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _VALUE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READDIGITALINPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , DONE(_DONE)
      , VALUE(_VALUE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _VALUE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)8;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALINPUT1TO8
 ******************************************************************************/
class KRC_READDIGITALINPUT1TO8
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const BOOL &IN1;
   const BOOL &IN2;
   const BOOL &IN3;
   const BOOL &IN4;
   const BOOL &IN5;
   const BOOL &IN6;
   const BOOL &IN7;
   const BOOL &IN8;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   BOOL _IN1;
   BOOL _IN2;
   BOOL _IN3;
   BOOL _IN4;
   BOOL _IN5;
   BOOL _IN6;
   BOOL _IN7;
   BOOL _IN8;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READDIGITALINPUT1TO8()
      : AXISGROUPIDX(0)
      , VALID(_VALID)
      , IN1(_IN1)
      , IN2(_IN2)
      , IN3(_IN3)
      , IN4(_IN4)
      , IN5(_IN5)
      , IN6(_IN6)
      , IN7(_IN7)
      , IN8(_IN8)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _IN1((BOOL)FALSE)
      , _IN2((BOOL)FALSE)
      , _IN3((BOOL)FALSE)
      , _IN4((BOOL)FALSE)
      , _IN5((BOOL)FALSE)
      , _IN6((BOOL)FALSE)
      , _IN7((BOOL)FALSE)
      , _IN8((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED);
      _IN1 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 0);
      _IN2 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 1);
      _IN3 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 2);
      _IN4 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 3);
      _IN5 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 4);
      _IN6 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 5);
      _IN7 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 6);
      _IN8 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.IN_VAL_1TO8, 7);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALINPUTARRAY
 ******************************************************************************/
class KRC_READDIGITALINPUTARRAY
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT STARTNUMBER;
   INT LENGTH;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL *VALUES;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _VALUES[201];
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   DWORD DW1;
   DWORD DW2;
   DWORD DW3;
   DWORD DW4;
   DWORD DW5;
   DWORD DW6;
   DWORD DW7;
   DWORD DW8;
   DWORD DW9;
   DWORD DW10;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READDIGITALINPUTARRAY()
      : DW1(0)
      , DW2(0)
      , DW3(0)
      , DW4(0)
      , DW5(0)
      , DW6(0)
      , DW7(0)
      , DW8(0)
      , DW9(0)
      , DW10(0)
      , MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , STARTNUMBER(0)
      , LENGTH(0)
      , DONE(_DONE)
      , VALUES(_VALUES)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _VALUES()
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)38;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(STARTNUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(LENGTH);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         DW1 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         DW2 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         DW3 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         DW4 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         DW5 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         DW6 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         DW7 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         DW8 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         DW9 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         DW10 = REAL_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _VALUES[1] = IsBitSet(DW1, 0);
         _VALUES[2] = IsBitSet(DW1, 1);
         _VALUES[3] = IsBitSet(DW1, 2);
         _VALUES[4] = IsBitSet(DW1, 3);
         _VALUES[5] = IsBitSet(DW1, 4);
         _VALUES[6] = IsBitSet(DW1, 5);
         _VALUES[7] = IsBitSet(DW1, 6);
         _VALUES[8] = IsBitSet(DW1, 7);
         _VALUES[9] = IsBitSet(DW1, 8);
         _VALUES[10] = IsBitSet(DW1, 9);
         _VALUES[11] = IsBitSet(DW1, 10);
         _VALUES[12] = IsBitSet(DW1, 11);
         _VALUES[13] = IsBitSet(DW1, 12);
         _VALUES[14] = IsBitSet(DW1, 13);
         _VALUES[15] = IsBitSet(DW1, 14);
         _VALUES[16] = IsBitSet(DW1, 15);
         _VALUES[17] = IsBitSet(DW1, 16);
         _VALUES[18] = IsBitSet(DW1, 17);
         _VALUES[19] = IsBitSet(DW1, 18);
         _VALUES[20] = IsBitSet(DW1, 19);
         _VALUES[21] = IsBitSet(DW2, 0);
         _VALUES[22] = IsBitSet(DW2, 1);
         _VALUES[23] = IsBitSet(DW2, 2);
         _VALUES[24] = IsBitSet(DW2, 3);
         _VALUES[25] = IsBitSet(DW2, 4);
         _VALUES[26] = IsBitSet(DW2, 5);
         _VALUES[27] = IsBitSet(DW2, 6);
         _VALUES[28] = IsBitSet(DW2, 7);
         _VALUES[29] = IsBitSet(DW2, 8);
         _VALUES[30] = IsBitSet(DW2, 9);
         _VALUES[31] = IsBitSet(DW2, 10);
         _VALUES[32] = IsBitSet(DW2, 11);
         _VALUES[33] = IsBitSet(DW2, 12);
         _VALUES[34] = IsBitSet(DW2, 13);
         _VALUES[35] = IsBitSet(DW2, 14);
         _VALUES[36] = IsBitSet(DW2, 15);
         _VALUES[37] = IsBitSet(DW2, 16);
         _VALUES[38] = IsBitSet(DW2, 17);
         _VALUES[39] = IsBitSet(DW2, 18);
         _VALUES[40] = IsBitSet(DW2, 19);
         _VALUES[41] = IsBitSet(DW3, 0);
         _VALUES[42] = IsBitSet(DW3, 1);
         _VALUES[43] = IsBitSet(DW3, 2);
         _VALUES[44] = IsBitSet(DW3, 3);
         _VALUES[45] = IsBitSet(DW3, 4);
         _VALUES[46] = IsBitSet(DW3, 5);
         _VALUES[47] = IsBitSet(DW3, 6);
         _VALUES[48] = IsBitSet(DW3, 7);
         _VALUES[49] = IsBitSet(DW3, 8);
         _VALUES[50] = IsBitSet(DW3, 9);
         _VALUES[51] = IsBitSet(DW3, 10);
         _VALUES[52] = IsBitSet(DW3, 11);
         _VALUES[53] = IsBitSet(DW3, 12);
         _VALUES[54] = IsBitSet(DW3, 13);
         _VALUES[55] = IsBitSet(DW3, 14);
         _VALUES[56] = IsBitSet(DW3, 15);
         _VALUES[57] = IsBitSet(DW3, 16);
         _VALUES[58] = IsBitSet(DW3, 17);
         _VALUES[59] = IsBitSet(DW3, 18);
         _VALUES[60] = IsBitSet(DW3, 19);
         _VALUES[61] = IsBitSet(DW4, 0);
         _VALUES[62] = IsBitSet(DW4, 1);
         _VALUES[63] = IsBitSet(DW4, 2);
         _VALUES[64] = IsBitSet(DW4, 3);
         _VALUES[65] = IsBitSet(DW4, 4);
         _VALUES[66] = IsBitSet(DW4, 5);
         _VALUES[67] = IsBitSet(DW4, 6);
         _VALUES[68] = IsBitSet(DW4, 7);
         _VALUES[69] = IsBitSet(DW4, 8);
         _VALUES[70] = IsBitSet(DW4, 9);
         _VALUES[71] = IsBitSet(DW4, 10);
         _VALUES[72] = IsBitSet(DW4, 11);
         _VALUES[73] = IsBitSet(DW4, 12);
         _VALUES[74] = IsBitSet(DW4, 13);
         _VALUES[75] = IsBitSet(DW4, 14);
         _VALUES[76] = IsBitSet(DW4, 15);
         _VALUES[77] = IsBitSet(DW4, 16);
         _VALUES[78] = IsBitSet(DW4, 17);
         _VALUES[79] = IsBitSet(DW4, 18);
         _VALUES[80] = IsBitSet(DW4, 19);
         _VALUES[81] = IsBitSet(DW5, 0);
         _VALUES[82] = IsBitSet(DW5, 1);
         _VALUES[83] = IsBitSet(DW5, 2);
         _VALUES[84] = IsBitSet(DW5, 3);
         _VALUES[85] = IsBitSet(DW5, 4);
         _VALUES[86] = IsBitSet(DW5, 5);
         _VALUES[87] = IsBitSet(DW5, 6);
         _VALUES[88] = IsBitSet(DW5, 7);
         _VALUES[89] = IsBitSet(DW5, 8);
         _VALUES[90] = IsBitSet(DW5, 9);
         _VALUES[91] = IsBitSet(DW5, 10);
         _VALUES[92] = IsBitSet(DW5, 11);
         _VALUES[93] = IsBitSet(DW5, 12);
         _VALUES[94] = IsBitSet(DW5, 13);
         _VALUES[95] = IsBitSet(DW5, 14);
         _VALUES[96] = IsBitSet(DW5, 15);
         _VALUES[97] = IsBitSet(DW5, 16);
         _VALUES[98] = IsBitSet(DW5, 17);
         _VALUES[99] = IsBitSet(DW5, 18);
         _VALUES[100] = IsBitSet(DW5, 19);
         _VALUES[101] = IsBitSet(DW6, 0);
         _VALUES[102] = IsBitSet(DW6, 1);
         _VALUES[103] = IsBitSet(DW6, 2);
         _VALUES[104] = IsBitSet(DW6, 3);
         _VALUES[105] = IsBitSet(DW6, 4);
         _VALUES[106] = IsBitSet(DW6, 5);
         _VALUES[107] = IsBitSet(DW6, 6);
         _VALUES[108] = IsBitSet(DW6, 7);
         _VALUES[109] = IsBitSet(DW6, 8);
         _VALUES[110] = IsBitSet(DW6, 9);
         _VALUES[111] = IsBitSet(DW6, 10);
         _VALUES[112] = IsBitSet(DW6, 11);
         _VALUES[113] = IsBitSet(DW6, 12);
         _VALUES[114] = IsBitSet(DW6, 13);
         _VALUES[115] = IsBitSet(DW6, 14);
         _VALUES[116] = IsBitSet(DW6, 15);
         _VALUES[117] = IsBitSet(DW6, 16);
         _VALUES[118] = IsBitSet(DW6, 17);
         _VALUES[119] = IsBitSet(DW6, 18);
         _VALUES[120] = IsBitSet(DW6, 19);
         _VALUES[121] = IsBitSet(DW7, 0);
         _VALUES[122] = IsBitSet(DW7, 1);
         _VALUES[123] = IsBitSet(DW7, 2);
         _VALUES[124] = IsBitSet(DW7, 3);
         _VALUES[125] = IsBitSet(DW7, 4);
         _VALUES[126] = IsBitSet(DW7, 5);
         _VALUES[127] = IsBitSet(DW7, 6);
         _VALUES[128] = IsBitSet(DW7, 7);
         _VALUES[129] = IsBitSet(DW7, 8);
         _VALUES[130] = IsBitSet(DW7, 9);
         _VALUES[131] = IsBitSet(DW7, 10);
         _VALUES[132] = IsBitSet(DW7, 11);
         _VALUES[133] = IsBitSet(DW7, 12);
         _VALUES[134] = IsBitSet(DW7, 13);
         _VALUES[135] = IsBitSet(DW7, 14);
         _VALUES[136] = IsBitSet(DW7, 15);
         _VALUES[137] = IsBitSet(DW7, 16);
         _VALUES[138] = IsBitSet(DW7, 17);
         _VALUES[139] = IsBitSet(DW7, 18);
         _VALUES[140] = IsBitSet(DW7, 19);
         _VALUES[141] = IsBitSet(DW8, 0);
         _VALUES[142] = IsBitSet(DW8, 1);
         _VALUES[143] = IsBitSet(DW8, 2);
         _VALUES[144] = IsBitSet(DW8, 3);
         _VALUES[145] = IsBitSet(DW8, 4);
         _VALUES[146] = IsBitSet(DW8, 5);
         _VALUES[147] = IsBitSet(DW8, 6);
         _VALUES[148] = IsBitSet(DW8, 7);
         _VALUES[149] = IsBitSet(DW8, 8);
         _VALUES[150] = IsBitSet(DW8, 9);
         _VALUES[151] = IsBitSet(DW8, 10);
         _VALUES[152] = IsBitSet(DW8, 11);
         _VALUES[153] = IsBitSet(DW8, 12);
         _VALUES[154] = IsBitSet(DW8, 13);
         _VALUES[155] = IsBitSet(DW8, 14);
         _VALUES[156] = IsBitSet(DW8, 15);
         _VALUES[157] = IsBitSet(DW8, 16);
         _VALUES[158] = IsBitSet(DW8, 17);
         _VALUES[159] = IsBitSet(DW8, 18);
         _VALUES[160] = IsBitSet(DW8, 19);
         _VALUES[161] = IsBitSet(DW9, 0);
         _VALUES[162] = IsBitSet(DW9, 1);
         _VALUES[163] = IsBitSet(DW9, 2);
         _VALUES[164] = IsBitSet(DW9, 3);
         _VALUES[165] = IsBitSet(DW9, 4);
         _VALUES[166] = IsBitSet(DW9, 5);
         _VALUES[167] = IsBitSet(DW9, 6);
         _VALUES[168] = IsBitSet(DW9, 7);
         _VALUES[169] = IsBitSet(DW9, 8);
         _VALUES[170] = IsBitSet(DW9, 9);
         _VALUES[171] = IsBitSet(DW9, 10);
         _VALUES[172] = IsBitSet(DW9, 11);
         _VALUES[173] = IsBitSet(DW9, 12);
         _VALUES[174] = IsBitSet(DW9, 13);
         _VALUES[175] = IsBitSet(DW9, 14);
         _VALUES[176] = IsBitSet(DW9, 15);
         _VALUES[177] = IsBitSet(DW9, 16);
         _VALUES[178] = IsBitSet(DW9, 17);
         _VALUES[179] = IsBitSet(DW9, 18);
         _VALUES[180] = IsBitSet(DW9, 19);
         _VALUES[181] = IsBitSet(DW10, 0);
         _VALUES[182] = IsBitSet(DW10, 1);
         _VALUES[183] = IsBitSet(DW10, 2);
         _VALUES[184] = IsBitSet(DW10, 3);
         _VALUES[185] = IsBitSet(DW10, 4);
         _VALUES[186] = IsBitSet(DW10, 5);
         _VALUES[187] = IsBitSet(DW10, 6);
         _VALUES[188] = IsBitSet(DW10, 7);
         _VALUES[189] = IsBitSet(DW10, 8);
         _VALUES[190] = IsBitSet(DW10, 9);
         _VALUES[191] = IsBitSet(DW10, 10);
         _VALUES[192] = IsBitSet(DW10, 11);
         _VALUES[193] = IsBitSet(DW10, 12);
         _VALUES[194] = IsBitSet(DW10, 13);
         _VALUES[195] = IsBitSet(DW10, 14);
         _VALUES[196] = IsBitSet(DW10, 15);
         _VALUES[197] = IsBitSet(DW10, 16);
         _VALUES[198] = IsBitSet(DW10, 17);
         _VALUES[199] = IsBitSet(DW10, 18);
         _VALUES[200] = IsBitSet(DW10, 19);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READDIGITALOUTPUT
 ******************************************************************************/
class KRC_READDIGITALOUTPUT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &VALUE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _VALUE;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READDIGITALOUTPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , DONE(_DONE)
      , VALUE(_VALUE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _VALUE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)9;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _VALUE = REAL_TO_BOOL(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READINTERRUPTSTATE
 ******************************************************************************/
class KRC_READINTERRUPTSTATE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   INT INTERRUPT;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const INT &VALUE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   INT _VALUE;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READINTERRUPTSTATE()
      : AXISGROUPIDX(0)
      , INTERRUPT(0)
      , VALID(_VALID)
      , VALUE(_VALUE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _VALUE(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      if (((INTERRUPT >= 1) && (INTERRUPT <= 8)))
      {
         _VALUE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.INTERRUPTSTATE[INTERRUPT];
         _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      }
      else
      {
         _VALUE = 0;
         _VALID = (BOOL)FALSE;
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT OFFSET;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const BOOL &STOPMESS;
   const INT &MESSAGECOUNT;
   const DINT &MESSAGE1;
   const DINT &MESSAGE2;
   const DINT &MESSAGE3;
   const DINT &MESSAGE4;
   const DINT &MESSAGE5;
   const DINT &MESSAGE6;
   const DINT &MESSAGE7;
   const DINT &MESSAGE8;
   const DINT &MESSAGE9;
   const DINT &MESSAGE10;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;
   BOOL _STOPMESS;
   INT _MESSAGECOUNT;
   DINT _MESSAGE1;
   DINT _MESSAGE2;
   DINT _MESSAGE3;
   DINT _MESSAGE4;
   DINT _MESSAGE5;
   DINT _MESSAGE6;
   DINT _MESSAGE7;
   DINT _MESSAGE8;
   DINT _MESSAGE9;
   DINT _MESSAGE10;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READKRCERROR()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , OFFSET(0)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , STOPMESS(_STOPMESS)
      , MESSAGECOUNT(_MESSAGECOUNT)
      , MESSAGE1(_MESSAGE1)
      , MESSAGE2(_MESSAGE2)
      , MESSAGE3(_MESSAGE3)
      , MESSAGE4(_MESSAGE4)
      , MESSAGE5(_MESSAGE5)
      , MESSAGE6(_MESSAGE6)
      , MESSAGE7(_MESSAGE7)
      , MESSAGE8(_MESSAGE8)
      , MESSAGE9(_MESSAGE9)
      , MESSAGE10(_MESSAGE10)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _STOPMESS((BOOL)FALSE)
      , _MESSAGECOUNT(0)
      , _MESSAGE1(0)
      , _MESSAGE2(0)
      , _MESSAGE3(0)
      , _MESSAGE4(0)
      , _MESSAGE5(0)
      , _MESSAGE6(0)
      , _MESSAGE7(0)
      , _MESSAGE8(0)
      , _MESSAGE9(0)
      , _MESSAGE10(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)24;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(OFFSET);
      };
      if (MXA_EXECUTECOMMAND_1.READCMDDATARET)
      {
         _MESSAGECOUNT = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         _MESSAGE1 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[2]);
         _MESSAGE2 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[3]);
         _MESSAGE3 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[4]);
         _MESSAGE4 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[5]);
         _MESSAGE5 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[6]);
         _MESSAGE6 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[7]);
         _MESSAGE7 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[8]);
         _MESSAGE8 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[9]);
         _MESSAGE9 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[10]);
         _MESSAGE10 = REAL_TO_DINT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[11]);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _STOPMESS = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTSTATE.STOPMESS;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READLOADDATA
 ******************************************************************************/
class KRC_READLOADDATA
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT TOOL;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const REAL &M;
   const REAL &X;
   const REAL &Y;
   const REAL &Z;
   const REAL &A;
   const REAL &B;
   const REAL &C;
   const REAL &JX;
   const REAL &JY;
   const REAL &JZ;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   REAL _M;
   REAL _X;
   REAL _Y;
   REAL _Z;
   REAL _A;
   REAL _B;
   REAL _C;
   REAL _JX;
   REAL _JY;
   REAL _JZ;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READLOADDATA()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , TOOL(0)
      , DONE(_DONE)
      , M(_M)
      , X(_X)
      , Y(_Y)
      , Z(_Z)
      , A(_A)
      , B(_B)
      , C(_C)
      , JX(_JX)
      , JY(_JY)
      , JZ(_JZ)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _M(0)
      , _X(0)
      , _Y(0)
      , _Z(0)
      , _A(0)
      , _B(0)
      , _C(0)
      , _JX(0)
      , _JY(0)
      , _JZ(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)14;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(TOOL);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READMXASTATUS
 ******************************************************************************/
class KRC_READMXASTATUS
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const INT &STATUS;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   INT _STATUS;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READMXASTATUS()
      : AXISGROUPIDX(0)
      , STATUS(_STATUS)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _STATUS(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
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
   INT AXISGROUPIDX;
   BOOL MASTERINGTEST_REQ_EXT;
   BOOL BRAKETEST_REQ_EXT;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const BOOL &BRAKETEST_REQ_INT;
   const BOOL &MASTERINGTEST_REQ_INT;
   const BOOL &BRAKETEST_MONTIME;
   const BOOL &BRAKETEST_WORK;
   const BOOL &BRAKES_OK;
   const BOOL &BRAKETEST_WARN;
   const BOOL &MASTERINGTESTSWITCH_OK;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   BOOL _BRAKETEST_REQ_INT;
   BOOL _MASTERINGTEST_REQ_INT;
   BOOL _BRAKETEST_MONTIME;
   BOOL _BRAKETEST_WORK;
   BOOL _BRAKES_OK;
   BOOL _BRAKETEST_WARN;
   BOOL _MASTERINGTESTSWITCH_OK;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READSAFEOPSTATUS()
      : AXISGROUPIDX(0)
      , MASTERINGTEST_REQ_EXT((BOOL)FALSE)
      , BRAKETEST_REQ_EXT((BOOL)FALSE)
      , VALID(_VALID)
      , BRAKETEST_REQ_INT(_BRAKETEST_REQ_INT)
      , MASTERINGTEST_REQ_INT(_MASTERINGTEST_REQ_INT)
      , BRAKETEST_MONTIME(_BRAKETEST_MONTIME)
      , BRAKETEST_WORK(_BRAKETEST_WORK)
      , BRAKES_OK(_BRAKES_OK)
      , BRAKETEST_WARN(_BRAKETEST_WARN)
      , MASTERINGTESTSWITCH_OK(_MASTERINGTESTSWITCH_OK)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _BRAKETEST_REQ_INT((BOOL)FALSE)
      , _MASTERINGTEST_REQ_INT((BOOL)FALSE)
      , _BRAKETEST_MONTIME((BOOL)FALSE)
      , _BRAKETEST_WORK((BOOL)FALSE)
      , _BRAKES_OK((BOOL)FALSE)
      , _BRAKETEST_WARN((BOOL)FALSE)
      , _MASTERINGTESTSWITCH_OK((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const REAL &A1_MIN;
   const REAL &A1_MAX;
   const REAL &A2_MIN;
   const REAL &A2_MAX;
   const REAL &A3_MIN;
   const REAL &A3_MAX;
   const REAL &A4_MIN;
   const REAL &A4_MAX;
   const REAL &A5_MIN;
   const REAL &A5_MAX;
   const REAL &A6_MIN;
   const REAL &A6_MAX;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   REAL _A1_MIN;
   REAL _A1_MAX;
   REAL _A2_MIN;
   REAL _A2_MAX;
   REAL _A3_MIN;
   REAL _A3_MAX;
   REAL _A4_MIN;
   REAL _A4_MAX;
   REAL _A5_MIN;
   REAL _A5_MAX;
   REAL _A6_MIN;
   REAL _A6_MAX;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READSOFTEND()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , DONE(_DONE)
      , A1_MIN(_A1_MIN)
      , A1_MAX(_A1_MAX)
      , A2_MIN(_A2_MIN)
      , A2_MAX(_A2_MAX)
      , A3_MIN(_A3_MIN)
      , A3_MAX(_A3_MAX)
      , A4_MIN(_A4_MIN)
      , A4_MAX(_A4_MAX)
      , A5_MIN(_A5_MIN)
      , A5_MAX(_A5_MAX)
      , A6_MIN(_A6_MIN)
      , A6_MAX(_A6_MAX)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _A1_MIN(0)
      , _A1_MAX(0)
      , _A2_MIN(0)
      , _A2_MAX(0)
      , _A3_MIN(0)
      , _A3_MAX(0)
      , _A4_MIN(0)
      , _A4_MAX(0)
      , _A5_MIN(0)
      , _A5_MAX(0)
      , _A6_MIN(0)
      , _A6_MAX(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)16;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READSOFTENDEXT
 ******************************************************************************/
class KRC_READSOFTENDEXT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const REAL &E1_MIN;
   const REAL &E1_MAX;
   const REAL &E2_MIN;
   const REAL &E2_MAX;
   const REAL &E3_MIN;
   const REAL &E3_MAX;
   const REAL &E4_MIN;
   const REAL &E4_MAX;
   const REAL &E5_MIN;
   const REAL &E5_MAX;
   const REAL &E6_MIN;
   const REAL &E6_MAX;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   REAL _E1_MIN;
   REAL _E1_MAX;
   REAL _E2_MIN;
   REAL _E2_MAX;
   REAL _E3_MIN;
   REAL _E3_MAX;
   REAL _E4_MIN;
   REAL _E4_MAX;
   REAL _E5_MIN;
   REAL _E5_MAX;
   REAL _E6_MIN;
   REAL _E6_MAX;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READSOFTENDEXT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , DONE(_DONE)
      , E1_MIN(_E1_MIN)
      , E1_MAX(_E1_MAX)
      , E2_MIN(_E2_MIN)
      , E2_MAX(_E2_MAX)
      , E3_MIN(_E3_MIN)
      , E3_MAX(_E3_MAX)
      , E4_MIN(_E4_MIN)
      , E4_MAX(_E4_MAX)
      , E5_MIN(_E5_MIN)
      , E5_MAX(_E5_MAX)
      , E6_MIN(_E6_MIN)
      , E6_MAX(_E6_MAX)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _E1_MIN(0)
      , _E1_MAX(0)
      , _E2_MIN(0)
      , _E2_MAX(0)
      , _E3_MIN(0)
      , _E3_MAX(0)
      , _E4_MIN(0)
      , _E4_MAX(0)
      , _E5_MIN(0)
      , _E5_MAX(0)
      , _E6_MIN(0)
      , _E6_MAX(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)18;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READSYSVAR
 ******************************************************************************/
class KRC_READSYSVAR
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT INDEX;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const REAL &VALUE1;
   const REAL &VALUE2;
   const REAL &VALUE3;
   const REAL &VALUE4;
   const REAL &VALUE5;
   const REAL &VALUE6;
   const REAL &VALUE7;
   const REAL &VALUE8;
   const REAL &VALUE9;
   const REAL &VALUE10;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   REAL _VALUE1;
   REAL _VALUE2;
   REAL _VALUE3;
   REAL _VALUE4;
   REAL _VALUE5;
   REAL _VALUE6;
   REAL _VALUE7;
   REAL _VALUE8;
   REAL _VALUE9;
   REAL _VALUE10;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READSYSVAR()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , INDEX(0)
      , DONE(_DONE)
      , VALUE1(_VALUE1)
      , VALUE2(_VALUE2)
      , VALUE3(_VALUE3)
      , VALUE4(_VALUE4)
      , VALUE5(_VALUE5)
      , VALUE6(_VALUE6)
      , VALUE7(_VALUE7)
      , VALUE8(_VALUE8)
      , VALUE9(_VALUE9)
      , VALUE10(_VALUE10)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _VALUE1(0)
      , _VALUE2(0)
      , _VALUE3(0)
      , _VALUE4(0)
      , _VALUE5(0)
      , _VALUE6(0)
      , _VALUE7(0)
      , _VALUE8(0)
      , _VALUE9(0)
      , _VALUE10(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)27;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(INDEX);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READTOOLDATA
 ******************************************************************************/
class KRC_READTOOLDATA
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT TOOLNO;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const FRAME &TOOLDATA;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   FRAME _TOOLDATA;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_READTOOLDATA()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , TOOLNO(0)
      , DONE(_DONE)
      , TOOLDATA(_TOOLDATA)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _TOOLDATA()
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)20;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(TOOLNO);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READTOUCHUPSTATE
 ******************************************************************************/
class KRC_READTOUCHUPSTATE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const BOOL &TOUCHUP;
   const INT &INDEX;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   BOOL _TOUCHUP;
   INT _INDEX;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READTOUCHUPSTATE()
      : AXISGROUPIDX(0)
      , VALID(_VALID)
      , TOUCHUP(_TOUCHUP)
      , INDEX(_INDEX)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _TOUCHUP((BOOL)FALSE)
      , _INDEX(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      if (_VALID)
      {
         _TOUCHUP = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOUCHUP;
         _INDEX = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.TOUCHUP_INDEX;
      }
      else
      {
         _TOUCHUP = (BOOL)FALSE;
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT WORKSPACENO;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const INT &WORKSPACEMODE;
   const BOX &WORKSPACEDATA;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   INT _WORKSPACEMODE;
   BOX _WORKSPACEDATA;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_0;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   INT M_WORKSPACEMODE;
   BOX M_WORKSPACEDATA;

public:
   KRC_READWORKSPACE()
      : NSTATE(0)
      , MXA_EXECUTECOMMAND_0()
      , MXA_EXECUTECOMMAND_1()
      , M_WORKSPACEMODE(0)
      , M_WORKSPACEDATA()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , WORKSPACENO(0)
      , DONE(_DONE)
      , WORKSPACEMODE(_WORKSPACEMODE)
      , WORKSPACEDATA(_WORKSPACEDATA)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _WORKSPACEMODE(0)
      , _WORKSPACEDATA()
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      MXA_EXECUTECOMMAND_0.CMDID = (DINT)49;
      MXA_EXECUTECOMMAND_0.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_0.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_0.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_0.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_0.OnCycle();
      if ((MXA_EXECUTECOMMAND_0.WRITECMDPAR && (NSTATE == 0)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = (DINT)1;
      };
      if ((MXA_EXECUTECOMMAND_0.READCMDDATARET && (NSTATE == 0)))
      {
         M_WORKSPACEMODE = REAL_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDDATARETURN[1]);
         NSTATE = 1;
      };
      if (MXA_EXECUTECOMMAND_0.ERROR)
      {
         NSTATE = 9;
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_0.ERRORID;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = (EXECUTECMD && (NSTATE == 1));
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)49;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if ((MXA_EXECUTECOMMAND_1.WRITECMDPAR && (NSTATE == 1)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(WORKSPACENO);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = (DINT)2;
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
         _ERROR = (BOOL)TRUE;
         _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      };
     _DONE = (NSTATE == 2);
      if ((NSTATE == 2))
      {
         _WORKSPACEMODE = M_WORKSPACEMODE;
         _WORKSPACEDATA = M_WORKSPACEDATA;
         _ERROR = 0;
         _ERRORID = (DINT)0;
      };
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_READWORKSTATES
 ******************************************************************************/
class KRC_READWORKSTATES
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const BOOL &WORKSTATE1;
   const BOOL &WORKSTATE2;
   const BOOL &WORKSTATE3;
   const BOOL &WORKSTATE4;
   const BOOL &WORKSTATE5;
   const BOOL &WORKSTATE6;
   const BOOL &WORKSTATE7;
   const BOOL &WORKSTATE8;
   const BOOL &AXWORKSTATE1;
   const BOOL &AXWORKSTATE2;
   const BOOL &AXWORKSTATE3;
   const BOOL &AXWORKSTATE4;
   const BOOL &AXWORKSTATE5;
   const BOOL &AXWORKSTATE6;
   const BOOL &AXWORKSTATE7;
   const BOOL &AXWORKSTATE8;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   BOOL _WORKSTATE1;
   BOOL _WORKSTATE2;
   BOOL _WORKSTATE3;
   BOOL _WORKSTATE4;
   BOOL _WORKSTATE5;
   BOOL _WORKSTATE6;
   BOOL _WORKSTATE7;
   BOOL _WORKSTATE8;
   BOOL _AXWORKSTATE1;
   BOOL _AXWORKSTATE2;
   BOOL _AXWORKSTATE3;
   BOOL _AXWORKSTATE4;
   BOOL _AXWORKSTATE5;
   BOOL _AXWORKSTATE6;
   BOOL _AXWORKSTATE7;
   BOOL _AXWORKSTATE8;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_READWORKSTATES()
      : AXISGROUPIDX(0)
      , VALID(_VALID)
      , WORKSTATE1(_WORKSTATE1)
      , WORKSTATE2(_WORKSTATE2)
      , WORKSTATE3(_WORKSTATE3)
      , WORKSTATE4(_WORKSTATE4)
      , WORKSTATE5(_WORKSTATE5)
      , WORKSTATE6(_WORKSTATE6)
      , WORKSTATE7(_WORKSTATE7)
      , WORKSTATE8(_WORKSTATE8)
      , AXWORKSTATE1(_AXWORKSTATE1)
      , AXWORKSTATE2(_AXWORKSTATE2)
      , AXWORKSTATE3(_AXWORKSTATE3)
      , AXWORKSTATE4(_AXWORKSTATE4)
      , AXWORKSTATE5(_AXWORKSTATE5)
      , AXWORKSTATE6(_AXWORKSTATE6)
      , AXWORKSTATE7(_AXWORKSTATE7)
      , AXWORKSTATE8(_AXWORKSTATE8)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _WORKSTATE1((BOOL)FALSE)
      , _WORKSTATE2((BOOL)FALSE)
      , _WORKSTATE3((BOOL)FALSE)
      , _WORKSTATE4((BOOL)FALSE)
      , _WORKSTATE5((BOOL)FALSE)
      , _WORKSTATE6((BOOL)FALSE)
      , _WORKSTATE7((BOOL)FALSE)
      , _WORKSTATE8((BOOL)FALSE)
      , _AXWORKSTATE1((BOOL)FALSE)
      , _AXWORKSTATE2((BOOL)FALSE)
      , _AXWORKSTATE3((BOOL)FALSE)
      , _AXWORKSTATE4((BOOL)FALSE)
      , _AXWORKSTATE5((BOOL)FALSE)
      , _AXWORKSTATE6((BOOL)FALSE)
      , _AXWORKSTATE7((BOOL)FALSE)
      , _AXWORKSTATE8((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED);
      _WORKSTATE1 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 0);
      _WORKSTATE2 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 1);
      _WORKSTATE3 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 2);
      _WORKSTATE4 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 3);
      _WORKSTATE5 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 4);
      _WORKSTATE6 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 5);
      _WORKSTATE7 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 6);
      _WORKSTATE8 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.WORKSTATES, 7);
      _AXWORKSTATE1 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 0);
      _AXWORKSTATE2 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 1);
      _AXWORKSTATE3 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 2);
      _AXWORKSTATE4 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 3);
      _AXWORKSTATE5 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 4);
      _AXWORKSTATE6 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 5);
      _AXWORKSTATE7 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 6);
      _AXWORKSTATE8 = IsBitSet(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.AXWORKSTATES, 7);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETADVANCE
 ******************************************************************************/
class KRC_SETADVANCE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT COUNT;
   INT MAXWAITTIME;
   INT MODE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETADVANCE()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , COUNT(0)
      , MAXWAITTIME(0)
      , MODE(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)36;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(COUNT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(MAXWAITTIME);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(MODE);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETCOORDSYS
 ******************************************************************************/
class KRC_SETCOORDSYS
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   COORDSYS COORDINATESYSTEM;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETCOORDSYS()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , COORDINATESYSTEM()
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)33;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(COORDINATESYSTEM.TOOL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(COORDINATESYSTEM.BASE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETDISTANCETRIGGER
 ******************************************************************************/
class KRC_SETDISTANCETRIGGER
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT DISTANCE;
   INT DELAY;
   INT OUTPUT;
   BOOL VALUE;
   REAL PULSE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETDISTANCETRIGGER()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , DISTANCE(0)
      , DELAY(0)
      , OUTPUT(0)
      , VALUE((BOOL)FALSE)
      , PULSE(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)3;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(DISTANCE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(DELAY);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(OUTPUT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = PULSE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETOVERRIDE
 ******************************************************************************/
class KRC_SETOVERRIDE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   INT OVERRIDE;

   /* VAR_OUTPUT */

public:
   const BOOL &VALID;
   const INT &ACTUALOVERRIDE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _VALID;
   INT _ACTUALOVERRIDE;
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_SETOVERRIDE()
      : AXISGROUPIDX(0)
      , OVERRIDE(0)
      , VALID(_VALID)
      , ACTUALOVERRIDE(_ACTUALOVERRIDE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _VALID((BOOL)FALSE)
      , _ACTUALOVERRIDE(0)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (((OVERRIDE >= 0) && (OVERRIDE <= 100)))
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE = OVERRIDE;
         _ERRORID = (DINT)0;
      }
      else
      {
         _ERRORID = (DINT)504;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
      };
      _ACTUALOVERRIDE = KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.OVPROACT;
      _VALID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE);
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_SETPATHTRIGGER
 ******************************************************************************/
class KRC_SETPATHTRIGGER
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   REAL PATH;
   INT DELAY;
   INT OUTPUT;
   BOOL VALUE;
   REAL PULSE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_SETPATHTRIGGER()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , PATH(0)
      , DELAY(0)
      , OUTPUT(0)
      , VALUE((BOOL)FALSE)
      , PULSE(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)4;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(DELAY);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(OUTPUT);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = PULSE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[2] = PATH;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_ACTIVATEPOSCONVERSION
 ******************************************************************************/
class KRC_ACTIVATEPOSCONVERSION
{
    /* VAR_INPUT */

public:
    INT AXISGROUPIDX;
    BOOL EXECUTECMD;
    BOOL ACTIVATECONVERSION;
    COORDSYS COORDSYSTODISPLAY;

    /* VAR_OUTPUT */

public:
    const BOOL& BUSY;
    const BOOL& DONE;
    const BOOL& ABORTED;
    const BOOL& ERROR;
    const DINT& ERRORID;

    /* VAR_OUTPUT (Alias Variables) */

private:
    BOOL _BUSY;
    BOOL _DONE;
    BOOL _ABORTED;
    BOOL _ERROR;
    DINT _ERRORID;


    /* VAR */

private:
    MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
    KRC_ACTIVATEPOSCONVERSION()
        : MXA_EXECUTECOMMAND_1()
        , AXISGROUPIDX(0)
        , EXECUTECMD((BOOL)FALSE)
        , ACTIVATECONVERSION((BOOL)FALSE)
        , COORDSYSTODISPLAY()
        , BUSY(_BUSY)
        , DONE(_DONE)
        , ABORTED(_ABORTED)
        , ERROR(_ERROR)
        , ERRORID(_ERRORID)
        , _BUSY((BOOL)FALSE)
        , _DONE((BOOL)FALSE)
        , _ABORTED((BOOL)FALSE)
        , _ERROR((BOOL)FALSE)
        , _ERRORID(0)
    {}

public:
    void OnCycle()
    {

        _ERRORID = (DINT)0;
        if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
        {
            _ERRORID = (DINT)506;
            _ERROR = (BOOL)TRUE;
            return;
        }

        // Call FB mxa_ExecuteCommand_1
        MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
        MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
        MXA_EXECUTECOMMAND_1.CMDID = (DINT)68;
        MXA_EXECUTECOMMAND_1.BUFFERMODE = 2;
        MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
        MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
        MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
        MXA_EXECUTECOMMAND_1.OnCycle();

        if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
        {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = ACTIVATECONVERSION;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(COORDSYSTODISPLAY.TOOL);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(COORDSYSTODISPLAY.BASE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(COORDSYSTODISPLAY.IPO_MODE);
        }

        _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
        _DONE = MXA_EXECUTECOMMAND_1.DONE;
        _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
        _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
        _ERROR = (_ERRORID != (DINT)0);
    }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TECHFUNCTION
 ******************************************************************************/
class KRC_TECHFUNCTION
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT TECHFUNCTIONID;
   INT PARAMETERCOUNT;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;

   /* VAR_IN_OUT */

public:
   BOOL *BOOL_DATA;
   DINT *INT_DATA;
   REAL *REAL_DATA;


   /* VAR */

private:
   INT I;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_TECHFUNCTION()
      : I(0)
      , MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , TECHFUNCTIONID(0)
      , PARAMETERCOUNT(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , BOOL_DATA()
      , INT_DATA()
      , REAL_DATA()
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (((PARAMETERCOUNT < 1) || (PARAMETERCOUNT > 40)))
      {
         _ERRORID = (DINT)521;
         _ERROR = (BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         return;
      };
      for (I = (PARAMETERCOUNT + 1); I <= 40; I += 1)
      {
         if ((((BOOL_DATA[I] == (BOOL)TRUE) || (INT_DATA[I] != 0)) || (REAL_DATA[I] != 0.0)))
         {
            _ERRORID = (DINT)522;
            _ERROR = (BOOL)TRUE;
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
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[41] = INT_TO_DINT(TECHFUNCTIONID);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TECHFUNCTIONADVANCED
 ******************************************************************************/
class KRC_TECHFUNCTIONADVANCED
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT TECHFUNCTIONID;
   INT PARAMETERCOUNT;


   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const REAL_ARRAY_12 &RETURNVALUE;


   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;
   REAL_ARRAY_12 _RETURNVALUE;

   /* VAR_IN_OUT */

public:
   BOOL *BOOL_DATA;
   DINT *INT_DATA;
   REAL *REAL_DATA;


   /* VAR */

private:
   INT I;
   INT NSTATE;
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_TECHFUNCTIONADVANCED()
      : I(0)
      , NSTATE(0)
      , MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , TECHFUNCTIONID(0)
      , PARAMETERCOUNT(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , RETURNVALUE(_RETURNVALUE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _RETURNVALUE()
      , BOOL_DATA()
      , INT_DATA()
      , REAL_DATA()
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (((PARAMETERCOUNT < 1) || (PARAMETERCOUNT > 40)))
      {
         _ERRORID = (DINT)521;
         _ERROR = (BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
         return;
      };
      if (!(EXECUTECMD))
      {
          NSTATE = 0;
      };

      for (I = (PARAMETERCOUNT + 1); I <= 40; I += 1)
      {
         if ((((BOOL_DATA[I] == (BOOL)TRUE) || (INT_DATA[I] != 0)) || (REAL_DATA[I] != 0.0)))
         {
            _ERRORID = (DINT)522;
            _ERROR = (BOOL)TRUE;
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
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[41] = INT_TO_DINT(TECHFUNCTIONID);
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
      _DONE = (MXA_EXECUTECOMMAND_1.DONE && (NSTATE = 1));
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TEST_TECHFUNCTION
 ******************************************************************************/
class KRC_TEST_TECHFUNCTION
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   BOOL_ARRAY_40 BOOL_DATA;
   INT I;
   INT32_ARRAY_40 INT_DATA;
   REAL_ARRAY_40 REAL_DATA;
   KRC_TECHFUNCTION KRC_TECHFUNCTION_1;

public:
   KRC_TEST_TECHFUNCTION()
      : BOOL_DATA()
      , I(0)
      , INT_DATA()
      , REAL_DATA()
      , KRC_TECHFUNCTION_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
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
      INT_DATA[3] =  INT_MIN;//-2147483648;
      INT_DATA[4] =  -2147483647;
      INT_DATA[5] = INT_MAX;//2147483647;
      REAL_DATA[1] = 1.0;
      REAL_DATA[2] = 0.0;
      REAL_DATA[3] =  -2147483500.0;
      REAL_DATA[4] =  -2147483499.0;
      REAL_DATA[5] = 2147483500.0;
      REAL_DATA[6] = 0.4;
      REAL_DATA[7] = 0.5;
      REAL_DATA[8] = 0.6;
      REAL_DATA[9] = 0.9;
      REAL_DATA[10] = 1.4000001;
      REAL_DATA[11] = 1.4999999;
      REAL_DATA[12] = 1.40000001;
      REAL_DATA[13] = 1.49999999;
      REAL_DATA[14] = 1.5000001;
      REAL_DATA[15] = 1.5000009;
      REAL_DATA[16] = 1.50000001;
      REAL_DATA[17] = 1.50000009;
      REAL_DATA[18] = 1.59999999;
      REAL_DATA[19] = 1.99999999;
      REAL_DATA[20] = 2.0;
      REAL_DATA[21] = 2.1;
      REAL_DATA[22] = 2.2;
      REAL_DATA[23] = 2.3;
      REAL_DATA[24] = 2.4;
      REAL_DATA[25] = 2.5;
      REAL_DATA[26] = 2.6;
      REAL_DATA[27] = 2.7;
      REAL_DATA[28] = 2.8;
      REAL_DATA[29] = 2.9;
      REAL_DATA[30] = 3.0;
      REAL_DATA[31] = 3.1;
      REAL_DATA[32] = 3.2;
      REAL_DATA[33] = 3.3;
      REAL_DATA[34] = 3.4;
      REAL_DATA[35] = 3.5;
      REAL_DATA[36] = 3.6;
      REAL_DATA[37] = 3.7;
      REAL_DATA[38] = 3.8;
      REAL_DATA[39] = 3.9;
      REAL_DATA[40] = 4.0;
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
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_TOUCHUP
 ******************************************************************************/
class KRC_TOUCHUP
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT INDEX;

   /* VAR_OUTPUT */

public:
   const BOOL &DONE;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _DONE;
   BOOL _ERROR;
   DINT _ERRORID;

   /* VAR_IN_OUT */

public:
   POSITION1 *POSITIONARRAY;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;
   R_TRIG R_TRIG_1;
   INT M_POSINDEX;

public:
   KRC_TOUCHUP()
      : MXA_EXECUTECOMMAND_1()
      , R_TRIG_1()
      , M_POSINDEX(0)
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , INDEX(0)
      , DONE(_DONE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _DONE((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , POSITIONARRAY()
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      _ERROR = (BOOL)TRUE;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (EXECUTECMD)
      {
         if (((INDEX < 1) || (INDEX > 100)))
         {
            _ERRORID = (DINT)513;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            _ERRORID = (DINT)509;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            _ERRORID = (DINT)508;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.POSACTVALID))
         {
            _ERRORID = (DINT)514;
         };
      };
      if ((_ERRORID != (DINT)0))
      {
         _ERROR = (BOOL)TRUE;
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
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)34;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = 0;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(M_POSINDEX);
      };
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_VECTORMOVEOFF
 ******************************************************************************/
class KRC_VECTORMOVEOFF
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_VECTORMOVEOFF()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)45;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_VECTORMOVEON
 ******************************************************************************/
class KRC_VECTORMOVEON
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   REAL X;
   REAL Y;
   REAL Z;
   REAL A;
   REAL B;
   REAL C;
   REAL VECTORLIMIT;
   REAL MAXDURATION;
   REAL TORQUEOFFSETVALUE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_VECTORMOVEON()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , X(0)
      , Y(0)
      , Z(0)
      , A(0)
      , B(0)
      , C(0)
      , VECTORLIMIT(0)
      , MAXDURATION(0)
      , TORQUEOFFSETVALUE(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxA_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)44;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WAITFORINPUT
 ******************************************************************************/
class KRC_WAITFORINPUT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;
   BOOL VALUE;
   BOOL BCONTINUE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WAITFORINPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , VALUE((BOOL)FALSE)
      , BCONTINUE((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)32;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _ACTIVE = MXA_EXECUTECOMMAND_1.ACTIVE;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEANALOGOUTPUT
 ******************************************************************************/
class KRC_WRITEANALOGOUTPUT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;
   REAL VALUE;
   BOOL BCONTINUE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEANALOGOUTPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , VALUE(0)
      , BCONTINUE((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)13;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = VALUE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEAXISGROUP
 ******************************************************************************/
class KRC_WRITEAXISGROUP
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BYTE* KRC4_OUTPUT;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   DWORD NCHECKSUM;
   INT I;
   DINT LASTORDERID;
   INT LASTTGNUMBER;
   INT LASTTGTYPE;
   DINT M_COMMANDID;
   DINT M_ORDERID;
   BOOL M_PROFINETERR;
   DWORD M_PROFINETSTATUS;
   INT M_ANZTELEGRAMME;
   BOOL AE_PGNO_FBIT_VAL;
   BOOL AE_PGNO_BIT1_VAL;
   BOOL AE_PGNO_BIT2_VAL;
   BOOL AE_PGNO_BIT3_VAL;
   BOOL AE_PGNO_BIT4_VAL;
   BOOL AE_PGNO_BIT5_VAL;
   BOOL AE_PGNO_BIT6_VAL;
   BOOL AE_PGNO_BIT7_VAL;
   BOOL AE_PGNO_PARITY_VAL;
   BOOL AE_PGNO_VALID_VAL;
   BOOL AE_EXT_START_VAL;
   BOOL AE_MOVE_ENABLE_VAL;
   BOOL AE_CONF_MESS_VAL;
   BOOL AE_DRIVES_OFF_VAL;
   BOOL AE_DRIVES_ON_VAL;
   BOOL MASTEST_REQ_EXT_VAL;
   BOOL BRAKETEST_REQ_EXT_VAL;
   BOOL AE_RESET_VAL;
   BOOL BRAKE_VAL;
   BOOL BRAKE_F_VAL;
   BOOL RELEASE_BRAKE_VAL;
   BOOL SHOW_TRACE_VAL;
   BOOL MESSAGE_RESET_VAL;
   BOOL OUT_VAL_1_VAL;
   BOOL OUT_VAL_2_VAL;
   BOOL OUT_VAL_3_VAL;
   BOOL OUT_VAL_4_VAL;
   BOOL OUT_VAL_5_VAL;
   BOOL OUT_VAL_6_VAL;
   BOOL OUT_VAL_7_VAL;
   BOOL OUT_VAL_8_VAL;
   BOOL WRITE_OUT_1TO8_VAL;
   BOOL JOG_ADVANCED_VAL;
   INT ZW_JOG_AD_STATE_VAL;
   BYTE JOG_AD_STATE;
   BYTE HEARTBEAT_VAL;
   BYTE OVERRIDE_VAL;
   DINT PLC_MAJOR_VAL;
   DINT PLC_MINOR_VAL;
   DINT SR_ORDER1_ID_VAL;
   DINT SR_ORDER2_ID_VAL;
   DINT SR_ORDER3_ID_VAL;
   DINT SR_ORDER4_ID_VAL;
   DINT SR_ORDER5_ID_VAL;
   DINT SR_ORDER6_ID_VAL;
   DINT SR_ORDER7_ID_VAL;
   DINT SR_ORDER8_ID_VAL;
   DINT SR_ORDER9_ID_VAL;
   DINT SR_ORDER10_ID_VAL;
   BYTE SR_ORDER1_STATE_VAL;
   BYTE SR_ORDER2_STATE_VAL;
   BYTE SR_ORDER3_STATE_VAL;
   BYTE SR_ORDER4_STATE_VAL;
   BYTE SR_ORDER5_STATE_VAL;
   BYTE SR_ORDER6_STATE_VAL;
   BYTE SR_ORDER7_STATE_VAL;
   BYTE SR_ORDER8_STATE_VAL;
   BYTE SR_ORDER9_STATE_VAL;
   BYTE SR_ORDER10_STATE_VAL;
   DINT CMDPAR_INT1_VAL;
   DINT CMDPAR_INT2_VAL;
   DINT CMDPAR_INT3_VAL;
   DINT CMDPAR_INT4_VAL;
   DINT CMDPAR_INT5_VAL;
   DINT CMDPAR_INT6_VAL;
   DINT CMDPAR_INT7_VAL;
   DINT CMDPAR_INT8_VAL;
   DINT CMDPAR_INT9_VAL;
   DINT CMDPAR_INT10_VAL;
   DINT CMDPAR_INT11_VAL;
   DINT CMDPAR_INT12_VAL;
   DINT CMDPAR_INT13_VAL;
   DINT CMDPAR_INT14_VAL;
   DINT CMDPAR_INT15_VAL;
   REAL CMDPAR_REAL1_VAL;
   REAL CMDPAR_REAL2_VAL;
   REAL CMDPAR_REAL3_VAL;
   REAL CMDPAR_REAL4_VAL;
   REAL CMDPAR_REAL5_VAL;
   REAL CMDPAR_REAL6_VAL;
   REAL CMDPAR_REAL7_VAL;
   REAL CMDPAR_REAL8_VAL;
   REAL CMDPAR_REAL9_VAL;
   REAL CMDPAR_REAL10_VAL;
   REAL CMDPAR_REAL11_VAL;
   REAL CMDPAR_REAL12_VAL;
   REAL CMDPAR_REAL13_VAL;
   REAL CMDPAR_REAL14_VAL;
   REAL CMDPAR_REAL15_VAL;
   DWORD CHECKSUM_VAL;
   INT TRANSMISSIONNO1_VAL;
   INT TRANSMISSIONNO2_VAL;
   INT TRANSMISSIONTYPE_VAL;
   DINT ORDERID_VAL;
   INT CMDID_VAL;
   INT BUFFERMODE_VAL;
   WORD BOOLVALUES1;
   MXA_RESETCOMMAND MXA_RESETCOMMAND_1;
   BOOL DUMMY;

   /* VAR_TEMP */

private:
   REAL FTMP;
   DINT NTMP1;
   REAL FTMP1;
   BOOL BTMP1;
   BOOL BMAXREALERR;

public:
   KRC_WRITEAXISGROUP()
      : NCHECKSUM(0)
      , I(0)
      , LASTORDERID(0)
      , LASTTGNUMBER(0)
      , LASTTGTYPE(0)
      , M_COMMANDID(0)
      , M_ORDERID(0)
      , M_PROFINETERR((BOOL)FALSE)
      , M_PROFINETSTATUS(0)
      , M_ANZTELEGRAMME(0)
      , AE_PGNO_FBIT_VAL((BOOL)FALSE)
      , AE_PGNO_BIT1_VAL((BOOL)FALSE)
      , AE_PGNO_BIT2_VAL((BOOL)FALSE)
      , AE_PGNO_BIT3_VAL((BOOL)FALSE)
      , AE_PGNO_BIT4_VAL((BOOL)FALSE)
      , AE_PGNO_BIT5_VAL((BOOL)FALSE)
      , AE_PGNO_BIT6_VAL((BOOL)FALSE)
      , AE_PGNO_BIT7_VAL((BOOL)FALSE)
      , AE_PGNO_PARITY_VAL((BOOL)FALSE)
      , AE_PGNO_VALID_VAL((BOOL)FALSE)
      , AE_EXT_START_VAL((BOOL)FALSE)
      , AE_MOVE_ENABLE_VAL((BOOL)FALSE)
      , AE_CONF_MESS_VAL((BOOL)FALSE)
      , AE_DRIVES_OFF_VAL((BOOL)FALSE)
      , AE_DRIVES_ON_VAL((BOOL)FALSE)
      , MASTEST_REQ_EXT_VAL((BOOL)FALSE)
      , BRAKETEST_REQ_EXT_VAL((BOOL)FALSE)
      , AE_RESET_VAL((BOOL)FALSE)
      , BRAKE_VAL((BOOL)FALSE)
      , BRAKE_F_VAL((BOOL)FALSE)
      , RELEASE_BRAKE_VAL((BOOL)FALSE)
      , SHOW_TRACE_VAL((BOOL)FALSE)
      , MESSAGE_RESET_VAL((BOOL)FALSE)
      , OUT_VAL_1_VAL((BOOL)FALSE)
      , OUT_VAL_2_VAL((BOOL)FALSE)
      , OUT_VAL_3_VAL((BOOL)FALSE)
      , OUT_VAL_4_VAL((BOOL)FALSE)
      , OUT_VAL_5_VAL((BOOL)FALSE)
      , OUT_VAL_6_VAL((BOOL)FALSE)
      , OUT_VAL_7_VAL((BOOL)FALSE)
      , OUT_VAL_8_VAL((BOOL)FALSE)
      , WRITE_OUT_1TO8_VAL((BOOL)FALSE)
      , JOG_ADVANCED_VAL((BOOL)FALSE)
      , ZW_JOG_AD_STATE_VAL(0)
      , JOG_AD_STATE(0)
      , HEARTBEAT_VAL(0)
      , OVERRIDE_VAL(0)
      , PLC_MAJOR_VAL(0)
      , PLC_MINOR_VAL(0)
      , SR_ORDER1_ID_VAL(0)
      , SR_ORDER2_ID_VAL(0)
      , SR_ORDER3_ID_VAL(0)
      , SR_ORDER4_ID_VAL(0)
      , SR_ORDER5_ID_VAL(0)
      , SR_ORDER6_ID_VAL(0)
      , SR_ORDER7_ID_VAL(0)
      , SR_ORDER8_ID_VAL(0)
      , SR_ORDER9_ID_VAL(0)
      , SR_ORDER10_ID_VAL(0)
      , SR_ORDER1_STATE_VAL(0)
      , SR_ORDER2_STATE_VAL(0)
      , SR_ORDER3_STATE_VAL(0)
      , SR_ORDER4_STATE_VAL(0)
      , SR_ORDER5_STATE_VAL(0)
      , SR_ORDER6_STATE_VAL(0)
      , SR_ORDER7_STATE_VAL(0)
      , SR_ORDER8_STATE_VAL(0)
      , SR_ORDER9_STATE_VAL(0)
      , SR_ORDER10_STATE_VAL(0)
      , CMDPAR_INT1_VAL(0)
      , CMDPAR_INT2_VAL(0)
      , CMDPAR_INT3_VAL(0)
      , CMDPAR_INT4_VAL(0)
      , CMDPAR_INT5_VAL(0)
      , CMDPAR_INT6_VAL(0)
      , CMDPAR_INT7_VAL(0)
      , CMDPAR_INT8_VAL(0)
      , CMDPAR_INT9_VAL(0)
      , CMDPAR_INT10_VAL(0)
      , CMDPAR_INT11_VAL(0)
      , CMDPAR_INT12_VAL(0)
      , CMDPAR_INT13_VAL(0)
      , CMDPAR_INT14_VAL(0)
      , CMDPAR_INT15_VAL(0)
      , CMDPAR_REAL1_VAL(0)
      , CMDPAR_REAL2_VAL(0)
      , CMDPAR_REAL3_VAL(0)
      , CMDPAR_REAL4_VAL(0)
      , CMDPAR_REAL5_VAL(0)
      , CMDPAR_REAL6_VAL(0)
      , CMDPAR_REAL7_VAL(0)
      , CMDPAR_REAL8_VAL(0)
      , CMDPAR_REAL9_VAL(0)
      , CMDPAR_REAL10_VAL(0)
      , CMDPAR_REAL11_VAL(0)
      , CMDPAR_REAL12_VAL(0)
      , CMDPAR_REAL13_VAL(0)
      , CMDPAR_REAL14_VAL(0)
      , CMDPAR_REAL15_VAL(0)
      , CHECKSUM_VAL(0)
      , TRANSMISSIONNO1_VAL(0)
      , TRANSMISSIONNO2_VAL(0)
      , TRANSMISSIONTYPE_VAL(0)
      , ORDERID_VAL(0)
      , CMDID_VAL(0)
      , BUFFERMODE_VAL(0)
      , BOOLVALUES1(0)
      , MXA_RESETCOMMAND_1()
      , DUMMY((BOOL)FALSE)
      , AXISGROUPIDX(0)
      , KRC4_OUTPUT()
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , FTMP(0)
      , NTMP1(0)
      , FTMP1(0)
      , BTMP1((BOOL)FALSE)
      , BMAXREALERR((BOOL)FALSE)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      NCHECKSUM = (DWORD)0;
      BMAXREALERR = (BOOL)FALSE;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      if (((KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID > (DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.ORDERIDRET)))
      {
         // Call FB mxA_ResetCommand_1
         MXA_RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
         MXA_RESETCOMMAND_1.OnCycle();
      };
      if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE == (BOOL)FALSE))
      {
         _ERRORID = (DINT)507;
         _ERROR = (BOOL)TRUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID = _ERRORID;
      }
      else
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE = (BOOL)FALSE;
      };
      AE_PGNO_FBIT_VAL = (BOOL)FALSE;
      AE_PGNO_BIT1_VAL = (BOOL)FALSE;
      AE_PGNO_BIT2_VAL = (BOOL)FALSE;
      AE_PGNO_BIT3_VAL = (BOOL)FALSE;
      AE_PGNO_BIT4_VAL = (BOOL)FALSE;
      AE_PGNO_BIT5_VAL = (BOOL)FALSE;
      AE_PGNO_BIT6_VAL = (BOOL)FALSE;
      AE_PGNO_BIT7_VAL = (BOOL)FALSE;
      AE_PGNO_PARITY_VAL = (BOOL)FALSE;
      AE_PGNO_VALID_VAL = (BOOL)FALSE;
      AE_EXT_START_VAL = KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.EXT_START;
      AE_MOVE_ENABLE_VAL = ((((((KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_ENABLE && !(KRC_AXISGROUPREFARR[AXISGROUPIDX].AUTEXTCONTROL.MOVE_DISABLE)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORID == (DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.ERRORIDSUB == (DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTERRORID == (DINT)0)) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID == (DINT)0));
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
      HEARTBEAT_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.HEARTBEAT);
      OVERRIDE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OVERRIDE);
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
      SR_ORDER1_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[1].SR_STATE);
      SR_ORDER2_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[2].SR_STATE);
      SR_ORDER3_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[3].SR_STATE);
      SR_ORDER4_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[4].SR_STATE);
      SR_ORDER5_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[5].SR_STATE);
      SR_ORDER6_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[6].SR_STATE);
      SR_ORDER7_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[7].SR_STATE);
      SR_ORDER8_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[8].SR_STATE);
      SR_ORDER9_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[9].SR_STATE);
      SR_ORDER10_STATE_VAL = INT_TO_BYTE(KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.STATERETURN[10].SR_STATE);
      JOG_AD_STATE = INT_TO_BYTE(ZW_JOG_AD_STATE_VAL);
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
            CMDID_VAL = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
            BUFFERMODE_VAL = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE);
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
            NCHECKSUM = DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
            NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID));
            NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE));
            for (I = 1; I <= 45; I += 1)
            {
               if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[I] == (BOOL)TRUE))
               {
                  NCHECKSUM = (NCHECKSUM ^ (DWORD)1);
               };
               NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[I]));
               FTMP = KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[I];
               NTMP1 = REAL_TO_DINT(((FTMP - 0.5) * 10.0));
               FTMP1 = ((NTMP1 / 10) + 0.5);
               BTMP1 = (FTMP == FTMP1);
               if (BTMP1)
               {
                  if ((FTMP > 0))
                  {
                     FTMP = (FTMP + 0.01);
                  }
                  else
                  {
                     FTMP = (FTMP - 0.01);
                  };
               };
               NCHECKSUM = (NCHECKSUM ^ DINT_TO_DWORD(REAL_TO_DINT(FTMP)));
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
                  CMDID_VAL = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
                  BUFFERMODE_VAL = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE);
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
                  CMDID_VAL = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID);
                  BUFFERMODE_VAL = DINT_TO_INT(KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE);
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
         CMDPAR_INT1_VAL = (DINT)0;
         CMDPAR_INT2_VAL = (DINT)0;
         CMDPAR_INT3_VAL = (DINT)0;
         CMDPAR_INT4_VAL = (DINT)0;
         CMDPAR_INT5_VAL = (DINT)0;
         CMDPAR_INT6_VAL = (DINT)0;
         CMDPAR_INT7_VAL = (DINT)0;
         CMDPAR_INT8_VAL = (DINT)0;
         CMDPAR_INT9_VAL = (DINT)0;
         CMDPAR_INT10_VAL = (DINT)0;
         CMDPAR_INT11_VAL = (DINT)0;
         CMDPAR_INT12_VAL = (DINT)0;
         CMDPAR_INT13_VAL = (DINT)0;
         CMDPAR_INT14_VAL = (DINT)0;
         CMDPAR_INT15_VAL = (DINT)0;
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
      DUMMY = MXA_WRITEIO_BYTE(10, KRC4_OUTPUT, DINT_TO_INT(PLC_MAJOR_VAL));
      DUMMY = MXA_WRITEIO_BYTE(11, KRC4_OUTPUT, DINT_TO_INT(PLC_MINOR_VAL));
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
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT WORKSPACENO;
   INT WORKSPACEMODE;
   AXBOX WORKSPACEDATA;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEAXWORKSPACE()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , WORKSPACENO(0)
      , WORKSPACEMODE(0)
      , WORKSPACEDATA()
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)50;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEBASEDATA
 ******************************************************************************/
class KRC_WRITEBASEDATA
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT BASENO;
   FRAME BASEDATA;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEBASEDATA()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , BASENO(0)
      , BASEDATA()
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)23;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(BASENO);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEDIGITALOUTPUT
 ******************************************************************************/
class KRC_WRITEDIGITALOUTPUT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT NUMBER;
   BOOL VALUE;
   REAL PULSE;
   BOOL BCONTINUE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEDIGITALOUTPUT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , NUMBER(0)
      , VALUE((BOOL)FALSE)
      , PULSE(0)
      , BCONTINUE((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)10;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[2] = VALUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(NUMBER);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARREAL[1] = PULSE;
      };
      _BUSY = MXA_EXECUTECOMMAND_1.BUSY;
      _DONE = MXA_EXECUTECOMMAND_1.DONE;
      _ABORTED = MXA_EXECUTECOMMAND_1.ABORTED;
      _ERRORID = MXA_EXECUTECOMMAND_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEDIGITALOUTPUT1TO8
 ******************************************************************************/
class KRC_WRITEDIGITALOUTPUT1TO8
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL OUT1;
   BOOL OUT2;
   BOOL OUT3;
   BOOL OUT4;
   BOOL OUT5;
   BOOL OUT6;
   BOOL OUT7;
   BOOL OUT8;

   /* VAR_OUTPUT */

public:
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _ERROR;
   DINT _ERRORID;


public:
   KRC_WRITEDIGITALOUTPUT1TO8()
      : AXISGROUPIDX(0)
      , OUT1((BOOL)FALSE)
      , OUT2((BOOL)FALSE)
      , OUT3((BOOL)FALSE)
      , OUT4((BOOL)FALSE)
      , OUT5((BOOL)FALSE)
      , OUT6((BOOL)FALSE)
      , OUT7((BOOL)FALSE)
      , OUT8((BOOL)FALSE)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      }
      else
      {
         _ERRORID = (DINT)0;
         _ERROR = (BOOL)FALSE;
      };
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_1 = OUT1;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_2 = OUT2;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_3 = OUT3;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_4 = OUT4;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_5 = OUT5;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_6 = OUT6;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_7 = OUT7;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.OUT_VAL_8 = OUT8;
      KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCCONTROL.WRITE_OUT_1TO8 = (BOOL)TRUE;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITELOADDATA
 ******************************************************************************/
class KRC_WRITELOADDATA
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT TOOL;
   REAL M;
   REAL X;
   REAL Y;
   REAL Z;
   REAL A;
   REAL B;
   REAL C;
   REAL JX;
   REAL JY;
   REAL JZ;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITELOADDATA()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , TOOL(0)
      , M(0)
      , X(0)
      , Y(0)
      , Z(0)
      , A(0)
      , B(0)
      , C(0)
      , JX(0)
      , JY(0)
      , JZ(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)15;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(TOOL);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITESOFTEND
 ******************************************************************************/
class KRC_WRITESOFTEND
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   REAL A1_MIN;
   REAL A1_MAX;
   REAL A2_MIN;
   REAL A2_MAX;
   REAL A3_MIN;
   REAL A3_MAX;
   REAL A4_MIN;
   REAL A4_MAX;
   REAL A5_MIN;
   REAL A5_MAX;
   REAL A6_MIN;
   REAL A6_MAX;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITESOFTEND()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , A1_MIN(0)
      , A1_MAX(0)
      , A2_MIN(0)
      , A2_MAX(0)
      , A3_MIN(0)
      , A3_MAX(0)
      , A4_MIN(0)
      , A4_MAX(0)
      , A5_MIN(0)
      , A5_MAX(0)
      , A6_MIN(0)
      , A6_MAX(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)17;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITESOFTENDEXT
 ******************************************************************************/
class KRC_WRITESOFTENDEXT
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   REAL E1_MIN;
   REAL E1_MAX;
   REAL E2_MIN;
   REAL E2_MAX;
   REAL E3_MIN;
   REAL E3_MAX;
   REAL E4_MIN;
   REAL E4_MAX;
   REAL E5_MIN;
   REAL E5_MAX;
   REAL E6_MIN;
   REAL E6_MAX;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITESOFTENDEXT()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , E1_MIN(0)
      , E1_MAX(0)
      , E2_MIN(0)
      , E2_MAX(0)
      , E3_MIN(0)
      , E3_MAX(0)
      , E4_MIN(0)
      , E4_MAX(0)
      , E5_MIN(0)
      , E5_MAX(0)
      , E6_MIN(0)
      , E6_MAX(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)19;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 2;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITESYSVAR
 ******************************************************************************/
class KRC_WRITESYSVAR
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT INDEX;
   REAL VALUE1;
   REAL VALUE2;
   REAL VALUE3;
   REAL VALUE4;
   REAL VALUE5;
   REAL VALUE6;
   REAL VALUE7;
   REAL VALUE8;
   REAL VALUE9;
   REAL VALUE10;
   BOOL BCONTINUE;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITESYSVAR()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , INDEX(0)
      , VALUE1(0)
      , VALUE2(0)
      , VALUE3(0)
      , VALUE4(0)
      , VALUE5(0)
      , VALUE6(0)
      , VALUE7(0)
      , VALUE8(0)
      , VALUE9(0)
      , VALUE10(0)
      , BCONTINUE((BOOL)FALSE)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)28;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[1] = BCONTINUE;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(INDEX);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITETOOLDATA
 ******************************************************************************/
class KRC_WRITETOOLDATA
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   FRAME TOOLDATA;
   INT TOOLNO;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITETOOLDATA()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , TOOLDATA()
      , TOOLNO(0)
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)21;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
      MXA_EXECUTECOMMAND_1.OnCycle();
      if (MXA_EXECUTECOMMAND_1.WRITECMDPAR)
      {
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(TOOLNO);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK KRC_WRITEWORKSPACE
 ******************************************************************************/
class KRC_WRITEWORKSPACE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTECMD;
   INT WORKSPACENO;
   INT WORKSPACEMODE;
   BOX WORKSPACEDATA;
   INT BUFFERMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &BUSY;
   const BOOL &DONE;
   const BOOL &ABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _BUSY;
   BOOL _DONE;
   BOOL _ABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MXA_EXECUTECOMMAND MXA_EXECUTECOMMAND_1;

public:
   KRC_WRITEWORKSPACE()
      : MXA_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , EXECUTECMD((BOOL)FALSE)
      , WORKSPACENO(0)
      , WORKSPACEMODE(0)
      , WORKSPACEDATA()
      , BUFFERMODE(0)
      , BUSY(_BUSY)
      , DONE(_DONE)
      , ABORTED(_ABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _BUSY((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _ABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
   {}

public:
   void OnCycle()
   {

      _ERRORID = (DINT)0;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB mxa_ExecuteCommand_1
      MXA_EXECUTECOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
      MXA_EXECUTECOMMAND_1.EXECUTE = EXECUTECMD;
      MXA_EXECUTECOMMAND_1.CMDID = (DINT)48;
      MXA_EXECUTECOMMAND_1.BUFFERMODE = BUFFERMODE;
      MXA_EXECUTECOMMAND_1.COMMANDSIZE = 1;
      MXA_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MXA_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_EXECUTECOMMAND
 ******************************************************************************/
class MC_EXECUTECOMMAND
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   DINT CMDID;
   INT QUEUEMODE;
   INT COMMANDSIZE;
   BOOL ENABLEDIRECTEXE;
   BOOL ENABLEQUEUEEXE;
   BOOL IGNOREINIT;

   /* VAR_OUTPUT */

public:
   const BOOL &WRITECMDPAR;
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;
   const BOOL &READCMDDATARET;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _WRITECMDPAR;
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;
   BOOL _READCMDDATARET;


   /* VAR */

private:
   MXA_RESETCOMMAND RESETCOMMAND_1;
   MXA_GETORDERSTATE GETORDERSTATE_1;
   KRC_ERROR KRC_ERROR_1;
   INT M_STATE;
   DINT M_ORDERID;
   BOOL M_EXECUTELAST;
   BOOL M_RE_EXECUTE;
   BOOL M_FE_EXECUTE;
   INT M_COMMANDSIZE;
   DINT M_INTERRORID;
   DINT M_GLOBALERRORID;

public:
   MC_EXECUTECOMMAND()
      : RESETCOMMAND_1()
      , GETORDERSTATE_1()
      , KRC_ERROR_1()
      , M_STATE(0)
      , M_ORDERID(0)
      , M_EXECUTELAST((BOOL)FALSE)
      , M_RE_EXECUTE((BOOL)FALSE)
      , M_COMMANDSIZE(0)
      , M_INTERRORID(0)
      , M_GLOBALERRORID(0)
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , CMDID(0)
      , QUEUEMODE(0)
      , COMMANDSIZE(0)
      , ENABLEDIRECTEXE((BOOL)FALSE)
      , ENABLEQUEUEEXE((BOOL)FALSE)
      , IGNOREINIT((BOOL)FALSE)
      , WRITECMDPAR(_WRITECMDPAR)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , READCMDDATARET(_READCMDDATARET)
      , _WRITECMDPAR((BOOL)FALSE)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , _READCMDDATARET((BOOL)FALSE)
   {}

public:
   void OnCycle()
   {

      if (((EXECUTE == (BOOL)TRUE) && (M_EXECUTELAST == (BOOL)FALSE)))
      {
         if ((M_STATE == 1))
         {
            M_INTERRORID = (DINT)543;
		 }else{
            M_STATE = 0;
            M_ORDERID = (DINT)0;
            M_INTERRORID = (DINT)0;
         };
         M_RE_EXECUTE = (BOOL)TRUE;
      };
      if (((EXECUTE == (BOOL)FALSE) && (M_EXECUTELAST == (BOOL)TRUE)))
      {
         M_FE_EXECUTE = (BOOL)TRUE;
      };
      M_EXECUTELAST = EXECUTE;
      _WRITECMDPAR = (BOOL)FALSE;
      _READCMDDATARET = (BOOL)FALSE;
      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         M_INTERRORID = (DINT)506;
      }
      else
      {
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READDONE))
         {
            M_INTERRORID = (DINT)507;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].READAXISGROUPINIT))
         {
            M_INTERRORID = (DINT)508;
         };
      };
      if ((M_RE_EXECUTE && (M_INTERRORID == (DINT)0)))
      {
         M_STATE = 1;
         if ((((QUEUEMODE == 0) && (ENABLEDIRECTEXE == (BOOL)FALSE)) || ((QUEUEMODE > 0) && (ENABLEQUEUEEXE == (BOOL)FALSE))))
         {
            M_INTERRORID = (DINT)502;
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED))
         {
            if (!(IGNOREINIT))
            {
               M_INTERRORID = (DINT)508;
            };
         };
         if (!(KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE))
         {
            M_INTERRORID = (DINT)509;
         };
      };
      if (((M_STATE == 1) && (M_INTERRORID == (DINT)0)))
      {
         if (M_RE_EXECUTE)
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID + (DINT)1);
            if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID >= (DINT)2147483647))
            {
               KRC_AXISGROUPREFARR[AXISGROUPIDX].LASTORDERID = (DINT)1;
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
                     _READCMDDATARET = (BOOL)TRUE;
                  }
                  else
                  {
                     M_STATE = 5;
                  };
               }
               else
               {
                  M_INTERRORID = (DINT)512;
               };
            }
            else
            {
               M_INTERRORID = (KRC_AXISGROUPREFARR[AXISGROUPIDX].CMDSTATE.CMDIDRET * (DINT) -(1));
            };
            // Call FB ResetCommand_1
            RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
            RESETCOMMAND_1.OnCycle();
         }
         else
         {
            if (((((KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID == (DINT)0) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID == (DINT)0)) && KRC_AXISGROUPREFARR[AXISGROUPIDX].ONLINE) && (KRC_AXISGROUPREFARR[AXISGROUPIDX].INITIALIZED || IGNOREINIT)))
            {
               if (((QUEUEMODE < 2) || (KRC_AXISGROUPREFARR[AXISGROUPIDX].KRCSTATE.QUEUECOUNT < 80)))
               {
                  // Call FB ResetCommand_1
                  RESETCOMMAND_1.AXISGROUPIDX = AXISGROUPIDX;
                  RESETCOMMAND_1.OnCycle();
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.ORDERID = M_ORDERID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDID = CMDID;
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.BUFFERMODE = INT_TO_DINT(QUEUEMODE);
                  M_COMMANDSIZE = COMMANDSIZE;
                  if (((COMMANDSIZE < 1) || (COMMANDSIZE > 3)))
                  {
                     M_INTERRORID = 517;
                     M_COMMANDSIZE = 3;
                  };
                  KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.COMMANDSIZE = M_COMMANDSIZE;
                  _WRITECMDPAR = (BOOL)TRUE;
               };
            };
         };
      };
      if ((((M_STATE > 1) && (M_STATE < 15)) && (M_INTERRORID == (DINT)0)))
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
      if ((M_INTERRORID != (DINT)0))
      {
         M_STATE = (DINT_TO_INT(M_INTERRORID) *  -(1));
         KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = M_INTERRORID;
      };
      // Call FB KRC_ERROR_1
	  KRC_ERROR_1.AXISGROUPIDX = AXISGROUPIDX;
	  KRC_ERROR_1.MESSAGERESET = (BOOL)FALSE;
	  KRC_ERROR_1.OnCycle();
      M_GLOBALERRORID = KRC_ERROR_1.ERRORID;
      _ERRORID = M_INTERRORID;
      if ((((_ERRORID == (DINT)0) && (M_STATE < 15)) && (M_GLOBALERRORID == (DINT)0)))
      {
         _ERRORID = M_GLOBALERRORID;
      };
      _BUSY = (((M_STATE > 0) && (M_STATE < 15)) && (_ERRORID == (DINT)0));
      _ACTIVE = ((M_STATE == 10) && (_ERRORID == (DINT)0));
      _DONE = (M_STATE == 15);
      _COMMANDABORTED = (M_STATE == 20);
      _COMBUSY = ((M_STATE > 1) && (M_STATE < 15));
      _COMACPT = (M_STATE > 1);
      _ERROR = (_ERRORID != (DINT)0);
      if ((((_DONE || _ERROR) || _COMMANDABORTED) && !(EXECUTE)))
      {
         M_STATE = 0;
         M_ORDERID = (DINT)0;
         M_INTERRORID = (DINT)0;
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
      if ((_ERRORID != (int)0) && M_FE_EXECUTE)
      {
          _ERRORID = (int)0;
      };
      M_RE_EXECUTE = (BOOL)FALSE;
      M_FE_EXECUTE = (BOOL)FALSE;
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVE
 ******************************************************************************/
class MC_MOVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   DINT CMDID;
   BOOL EXECUTE;
   INT MOVETYPE;
   E6POS ACTPOSITION;
   E6AXIS AXISPOSITION;
   E6POS CIRCHP;
   REAL VELOCITY;
   REAL ABSOLUTEVELOCITY;
   REAL ACCELERATION;
   REAL ABSOLUTEACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   INT CIRCTYPE;
   REAL CIRCANGLE;
   APO APPROXIMATE;
   BOOL POSVALIDX;
   BOOL POSVALIDY;
   BOOL POSVALIDZ;
   BOOL POSVALIDA;
   BOOL POSVALIDB;
   BOOL POSVALIDC;
   BOOL POSVALIDE1;
   BOOL POSVALIDE2;
   BOOL POSVALIDE3;
   BOOL POSVALIDE4;
   BOOL POSVALIDE5;
   BOOL POSVALIDE6;
   BOOL POSVALIDS;
   BOOL POSVALIDT;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_EXECUTECOMMAND MC_EXECUTECOMMAND_1;

   /* VAR_TEMP */

private:
   INT COMMANDSIZE;
   DINT M_VELOCITY;
   DINT M_ACCELERATION;

public:
   MC_MOVE()
      : MC_EXECUTECOMMAND_1()
      , AXISGROUPIDX(0)
      , CMDID((DINT)1)
      , EXECUTE((BOOL)FALSE)
      , MOVETYPE(0)
      , ACTPOSITION()
      , AXISPOSITION()
      , CIRCHP()
      , VELOCITY(0)
      , ABSOLUTEVELOCITY(0)
      , ACCELERATION(0)
      , ABSOLUTEACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , CIRCTYPE(0)
      , CIRCANGLE(0)
      , APPROXIMATE()
      , POSVALIDX((BOOL)FALSE)
      , POSVALIDY((BOOL)FALSE)
      , POSVALIDZ((BOOL)FALSE)
      , POSVALIDA((BOOL)FALSE)
      , POSVALIDB((BOOL)FALSE)
      , POSVALIDC((BOOL)FALSE)
      , POSVALIDE1((BOOL)FALSE)
      , POSVALIDE2((BOOL)FALSE)
      , POSVALIDE3((BOOL)FALSE)
      , POSVALIDE4((BOOL)FALSE)
      , POSVALIDE5((BOOL)FALSE)
      , POSVALIDE6((BOOL)FALSE)
      , POSVALIDS((BOOL)FALSE)
      , POSVALIDT((BOOL)FALSE)
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , COMMANDSIZE(0)
      , M_VELOCITY(0)
      , M_ACCELERATION(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      if (EXECUTE)
      {
         if (((VELOCITY > 0) && (ABSOLUTEVELOCITY > 0.0)))
         {
            _ERRORID = (DINT)520;
            _ERROR = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
            return;
         };
       M_VELOCITY = (DINT)REAL_TO_DINT(VELOCITY * -1000.0f);
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
             _ERRORID = (DINT)519;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          };
          break;
       };
       if (ABSOLUTEVELOCITY > 0.0)
       {
          if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP <= 0.0))
          {
             _ERRORID = (DINT)544;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          };
          M_VELOCITY = (DINT)REAL_TO_DINT(((ABSOLUTEVELOCITY * -100000.0) / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_VEL_CP));
       };

       M_ACCELERATION = (DINT)REAL_TO_DINT(ACCELERATION * -1000.0);
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
          if ((ABSOLUTEACCELERATION > 0.0))
          {
             _ERRORID = (DINT)545;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          };
          break;
       };
       if ((ABSOLUTEACCELERATION > 0.0))
       {
          if ((KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP <= 0.0))
          {
             _ERRORID = (DINT)546;
             _ERROR = (BOOL)TRUE;
             KRC_AXISGROUPREFARR[AXISGROUPIDX].INTFBERRORID = _ERRORID;
             return;
          };
          M_ACCELERATION = (DINT)REAL_TO_DINT(ABSOLUTEACCELERATION * -100000.0 / KRC_AXISGROUPREFARR[AXISGROUPIDX].DEF_ACC_CP);
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
      MC_EXECUTECOMMAND_1.ENABLEDIRECTEXE = (BOOL)FALSE;
      MC_EXECUTECOMMAND_1.ENABLEQUEUEEXE = (BOOL)TRUE;
      MC_EXECUTECOMMAND_1.IGNOREINIT = (BOOL)FALSE;
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
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[15] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[16] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[17] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[18] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[19] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[20] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[21] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[22] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[23] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[24] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[25] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[26] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[27] = (BOOL)TRUE;
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARBOOL[28] = (BOOL)TRUE;
         };
         if (((((MOVETYPE == 0) || (MOVETYPE == 10)) || (MOVETYPE == 9)) || (MOVETYPE == 19)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(0);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(0);
         }
         else
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[1] = INT_TO_DINT(ACTPOSITION.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[2] = INT_TO_DINT(ACTPOSITION.TURN);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[3] = INT_TO_DINT(COORDINATESYSTEM.TOOL);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[4] = INT_TO_DINT(COORDINATESYSTEM.BASE);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[5] = INT_TO_DINT(COORDINATESYSTEM.IPO_MODE);
         };
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[6] = INT_TO_DINT(MOVETYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[7] = M_VELOCITY;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[8] = M_ACCELERATION;
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[9] = INT_TO_DINT(APPROXIMATE.PTP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[10] = INT_TO_DINT(APPROXIMATE.CP_MODE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[11] = INT_TO_DINT(APPROXIMATE.CPTP);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[12] = INT_TO_DINT(APPROXIMATE.CVEL);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[13] = INT_TO_DINT(ORITYPE);
         KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[14] = INT_TO_DINT(CIRCTYPE);
         if (((((MOVETYPE == 7) || (MOVETYPE == 8)) || (MOVETYPE == 17)) || (MOVETYPE == 18)))
         {
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[15] = INT_TO_DINT(CIRCHP.STATUS);
            KRC_AXISGROUPREFARR[AXISGROUPIDX].COMMAND.CMDPARINT[16] = INT_TO_DINT(CIRCHP.TURN);
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
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVEAXISABSOLUTE
 ******************************************************************************/
class MC_MOVEAXISABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6AXIS AXISPOSITION;
   REAL VELOCITY;
   REAL ACCELERATION;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6POS M_POSITION;
   INT M_ORITYPE;
   COORDSYS M_COORDINATESYSTEM;

public:
   MC_MOVEAXISABSOLUTE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , AXISPOSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_CIRCHP()
      , M_POSITION()
      , M_ORITYPE(0)
      , M_COORDINATESYSTEM()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
      MC_MOVE_1.EXECUTE = EXECUTE;
      MC_MOVE_1.MOVETYPE = 0;
      MC_MOVE_1.AXISPOSITION = AXISPOSITION;
      MC_MOVE_1.VELOCITY = VELOCITY;
      MC_MOVE_1.ACCELERATION = ACCELERATION;
      MC_MOVE_1.ORITYPE = M_ORITYPE;
      MC_MOVE_1.APPROXIMATE = APPROXIMATE;
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVECIRCULARABSOLUTE
 ******************************************************************************/
class MC_MOVECIRCULARABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6POS ACTPOSITION;
   E6POS CIRCHP;
   REAL ANGLE;
   REAL VELOCITY;
   REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   INT CIRCTYPE;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVECIRCULARABSOLUTE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , ACTPOSITION()
      , CIRCHP()
      , ANGLE(0)
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , CIRCTYPE(0)
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_COORDINATESYSTEM()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
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
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVECIRCULARRELATIVE
 ******************************************************************************/
class MC_MOVECIRCULARRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6POS DISTANCE;
   E6POS CIRCHP;
   REAL ANGLE;
   REAL VELOCITY;
   REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   INT CIRCTYPE;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   COORDSYS M_COORDINATESYSTEM;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVECIRCULARRELATIVE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , DISTANCE()
      , CIRCHP()
      , ANGLE(0)
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , CIRCTYPE(0)
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_COORDINATESYSTEM()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
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
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVEDIRECTABSOLUTE
 ******************************************************************************/
class MC_MOVEDIRECTABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6POS ACTPOSITION;
   REAL VELOCITY;
   REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   INT M_ORITYPE;

public:
   MC_MOVEDIRECTABSOLUTE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , ACTPOSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
      , M_ORITYPE(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
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
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVEDIRECTRELATIVE
 ******************************************************************************/
class MC_MOVEDIRECTRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6POS DISTANCE;
   REAL VELOCITY;
   REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;
   INT M_ORITYPE;

public:
   MC_MOVEDIRECTRELATIVE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , DISTANCE()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
      , M_ORITYPE(0)
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
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
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)FALSE;
      MC_MOVE_1.POSVALIDT = (BOOL)FALSE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVELINEARABSOLUTE
 ******************************************************************************/
class MC_MOVELINEARABSOLUTE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6POS ACTPOSITION;
   REAL VELOCITY;
   REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVELINEARABSOLUTE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , ACTPOSITION()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
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
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDT = (BOOL)TRUE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MC_MOVELINEARRELATIVE
 ******************************************************************************/
class MC_MOVELINEARRELATIVE
{

   /* VAR_INPUT */

public:
   INT AXISGROUPIDX;
   BOOL EXECUTE;
   E6POS DISTANCE;
   REAL VELOCITY;
   REAL ACCELERATION;
   COORDSYS COORDINATESYSTEM;
   INT ORITYPE;
   APO APPROXIMATE;
   INT QUEUEMODE;

   /* VAR_OUTPUT */

public:
   const BOOL &COMACPT;
   const BOOL &COMBUSY;
   const BOOL &BUSY;
   const BOOL &ACTIVE;
   const BOOL &DONE;
   const BOOL &COMMANDABORTED;
   const BOOL &ERROR;
   const DINT &ERRORID;

   /* VAR_OUTPUT (Alias Variables) */

private:
   BOOL _COMACPT;
   BOOL _COMBUSY;
   BOOL _BUSY;
   BOOL _ACTIVE;
   BOOL _DONE;
   BOOL _COMMANDABORTED;
   BOOL _ERROR;
   DINT _ERRORID;


   /* VAR */

private:
   MC_MOVE MC_MOVE_1;

   /* VAR_TEMP */

private:
   E6POS M_CIRCHP;
   E6AXIS M_AXISPOSITION;

public:
   MC_MOVELINEARRELATIVE()
      : MC_MOVE_1()
      , AXISGROUPIDX(0)
      , EXECUTE((BOOL)FALSE)
      , DISTANCE()
      , VELOCITY(0)
      , ACCELERATION(0)
      , COORDINATESYSTEM()
      , ORITYPE(0)
      , APPROXIMATE()
      , QUEUEMODE(0)
      , COMACPT(_COMACPT)
      , COMBUSY(_COMBUSY)
      , BUSY(_BUSY)
      , ACTIVE(_ACTIVE)
      , DONE(_DONE)
      , COMMANDABORTED(_COMMANDABORTED)
      , ERROR(_ERROR)
      , ERRORID(_ERRORID)
      , _COMACPT((BOOL)FALSE)
      , _COMBUSY((BOOL)FALSE)
      , _BUSY((BOOL)FALSE)
      , _ACTIVE((BOOL)FALSE)
      , _DONE((BOOL)FALSE)
      , _COMMANDABORTED((BOOL)FALSE)
      , _ERROR((BOOL)FALSE)
      , _ERRORID(0)
      , M_CIRCHP()
      , M_AXISPOSITION()
   {}

public:
   void OnCycle()
   {

      if (((AXISGROUPIDX < 1) || (AXISGROUPIDX > 5)))
      {
         _ERRORID = (DINT)506;
         _ERROR = (BOOL)TRUE;
         return;
      };
      // Call FB MC_Move_1
      MC_MOVE_1.AXISGROUPIDX = AXISGROUPIDX;
      MC_MOVE_1.CMDID = (DINT)1;
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
      MC_MOVE_1.POSVALIDX = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDY = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDZ = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDA = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDB = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDC = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE1 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE2 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE3 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE4 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE5 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDE6 = (BOOL)TRUE;
      MC_MOVE_1.POSVALIDS = (BOOL)FALSE;
      MC_MOVE_1.POSVALIDT = (BOOL)FALSE;
      MC_MOVE_1.QUEUEMODE = QUEUEMODE;
      MC_MOVE_1.OnCycle();
      _COMACPT = MC_MOVE_1.COMACPT;
      _COMBUSY = MC_MOVE_1.COMBUSY;
      _BUSY = MC_MOVE_1.BUSY;
      _ACTIVE = MC_MOVE_1.ACTIVE;
      _DONE = MC_MOVE_1.DONE;
      _COMMANDABORTED = MC_MOVE_1.COMMANDABORTED;
      _ERRORID = MC_MOVE_1.ERRORID;
      _ERROR = (_ERRORID != (DINT)0);
   }
};

/******************************************************************************
 * FUNCTION_BLOCK MXA_VALUESTOAPO
 ******************************************************************************/
class MXA_VALUESTOAPO
{

   /* VAR_INPUT */

public:
   INT PTP_MODE;
   INT CP_MODE;
   INT CPTP;
   REAL CDIS;
   REAL CORI;
   INT CVEL;

   /* VAR_OUTPUT */

public:
   const APO &APO_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   APO _APO_1;


public:
   MXA_VALUESTOAPO()
      : PTP_MODE(0)
      , CP_MODE(0)
      , CPTP(0)
      , CDIS(0)
      , CORI(0)
      , CVEL(0)
      , APO_1(_APO_1)
      , _APO_1()
   {}

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
   INT TOOL;
   INT BASE;
   INT IPO_MODE;

   /* VAR_OUTPUT */

public:
   const COORDSYS &COORDSYS_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   COORDSYS _COORDSYS_1;


public:
   MXA_VALUESTOCOORDSYS()
      : TOOL(0)
      , BASE(0)
      , IPO_MODE(0)
      , COORDSYS_1(_COORDSYS_1)
      , _COORDSYS_1()
   {}

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
   REAL A1;
   REAL A2;
   REAL A3;
   REAL A4;
   REAL A5;
   REAL A6;
   REAL E1;
   REAL E2;
   REAL E3;
   REAL E4;
   REAL E5;
   REAL E6;

   /* VAR_OUTPUT */

public:
   const E6AXIS &E6AXIS_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   E6AXIS _E6AXIS_1;


public:
   MXA_VALUESTOE6AXIS()
      : A1(0)
      , A2(0)
      , A3(0)
      , A4(0)
      , A5(0)
      , A6(0)
      , E1(0)
      , E2(0)
      , E3(0)
      , E4(0)
      , E5(0)
      , E6(0)
      , E6AXIS_1(_E6AXIS_1)
      , _E6AXIS_1()
   {}

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
   REAL X;
   REAL Y;
   REAL Z;
   REAL A;
   REAL B;
   REAL C;
   INT STATUS;
   INT TURN;
   REAL E1;
   REAL E2;
   REAL E3;
   REAL E4;
   REAL E5;
   REAL E6;

   /* VAR_OUTPUT */

public:
   const E6POS &E6POS_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   E6POS _E6POS_1;


public:
   MXA_VALUESTOE6POS()
      : X(0)
      , Y(0)
      , Z(0)
      , A(0)
      , B(0)
      , C(0)
      , STATUS(0)
      , TURN(0)
      , E1(0)
      , E2(0)
      , E3(0)
      , E4(0)
      , E5(0)
      , E6(0)
      , E6POS_1(_E6POS_1)
      , _E6POS_1()
   {}

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
   REAL X;
   REAL Y;
   REAL Z;
   REAL A;
   REAL B;
   REAL C;

   /* VAR_OUTPUT */

public:
   const FRAME &FRAME_1;

   /* VAR_OUTPUT (Alias Variables) */

private:
   FRAME _FRAME_1;


public:
   MXA_VALUESTOFRAME()
      : X(0)
      , Y(0)
      , Z(0)
      , A(0)
      , B(0)
      , C(0)
      , FRAME_1(_FRAME_1)
      , _FRAME_1()
   {}

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

#endif  // MXA_V331_H
