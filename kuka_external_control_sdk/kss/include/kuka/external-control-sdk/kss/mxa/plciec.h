/******************************************************************************
;// This material is the exclusive property of KUKA Roboter GmbH.
;// Except as expressly permitted by separate agreement, this material may only
;// be used by members of the development department of KUKA Roboter GmbH for
;// internal development purposes of KUKA Roboter GmbH.
;//
;// Copyright (C) 2013
;// KUKA Roboter GmbH, Germany. All Rights Reserved.
;//
;// Native cpp extensions for the MxA library.
;// Function-Blocks and Functions, that are basic PLC IEC
;// are reimplemented here as direct cpp code
;//
;//*****************************************************************************
;// Datum       Programmierer        Reviewer
;//             Beschreibung
;//-----------------------------------------------------------------------------
;// 01.09.2015  AFr
;//             mxAutmation2.1
;// 12.10.2016  HMz
;//             Windows support
;// 11.11.2016  RRolke
;//             Windows support
******************************************************************************/

// TODO check licensing

#ifndef PLCIEC_H
#define PLCIEC_H

#include <math.h>
#include <time.h>

#include <climits>
#include <string>


#define _IN     // NOOP
#define _OUT    // NOOP
#define _INOUT  // NOOP

// 12.10.2016  HMz added
#ifdef _MSC_VER
#undef IN     // used as a varibale name below
#undef ERROR  // used as a varibale name in mxAutomationVxx.h
#else
// 1 BOOL boolesche 1 h
typedef bool BOOL;
#define TRUE true
#define FALSE false
// 3 INT ganze Zahl(integer) 16 c
typedef short INT;
// 7 UINT vorzeichenlose ganze Zahl 16 d
typedef unsigned short UINT;
// 19 DWORD Bit - Folge 32 32 J, g
typedef unsigned int DWORD;
#endif
// 2 SINT kurze ganze Zahl(short integer) 8 c
typedef signed char SINT;
// 4 DINT doppelte ganze Zahl(double integer) 32 c
typedef int DINT;
// 5 LINT lange ganze Zahl(long integer) 64 c
typedef long LINT;
// 6 USINT vorzeichenlose kurze ganze Zahl(unsigned short integer) 8 d
typedef unsigned char USINT;
// 8 UDINT vorzeichenlose doppelte ganze Zahl 32 d
typedef unsigned int UDINT;
// 9 ULINT vorzeichenlose lange ganze Zahl 64 d
typedef unsigned long ULINT;
// 10 REAL reelle Zahl 32 e
typedef float REAL;
// 11 LREAL lange reelle Zahl 64 f
typedef double LREAL;
// 12 TIME Zeitdauer -- b
typedef int TIME;  // Milisecond timestamp. Must be signed!
/*
// 13 DATE Datum(nur) --b
typedef unsigned int DATE;
// 14 TIME_OF_DAY oder TOD Uhrzeit(nur) --b
typedef unsigned int TIME_OF_DAY;
typedef unsigned int TOD;
// 15 DATE_AND_TIME oder DT Datum und Uhrzeit -- b
typedef unsigned int DATE_AND_TIME;
typedef unsigned int DT;
*/
// 16 STRING variabel - lange Zeichenfolge 8 i, g
typedef std::string STRING;
// 17 BYTE Bit - Folge 8 8 J, g
typedef unsigned char BYTE;
// 18 WORD Bit - Folge 16 16 J, g
typedef unsigned short WORD;
// 20 LWORD Bit - Folge 64 64 J, g
typedef unsigned long LWORD;
// 21 WSTRING Variable lange Doppel - Byte - Zeichenfolge 16 i, g
typedef std::wstring WSTRING;

/* Set bit @ pos if val is true, clear bit @ pos if val is false */
#define ChBit(dw, idx, val) (dw) = (val) ? ((dw) | (1 << (idx))) : ((dw) & ~(1 << (idx)))

/* Return true if bit @ idx is set, otherwise false */
#define IsBitSet(dw, idx) (((dw) & (1 << (idx))) != 0)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#ifdef _MSC_VER
#pragma comment(lib, "winmm.lib")
extern "C" __declspec(dllimport) DWORD __stdcall timeGetTime(void);  // Link to winmm.lib
//__declspec(dllimport) DWORD __stdcall timeGetTime(void);
#define CURTIME() timeGetTime()
#elif defined(__linux__)
#include <sys/time.h>
#define CURTIME() getTimeInMilliseconds()
inline long long getTimeInMilliseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000LL + tv.tv_usec / 1000;  // convert tv_sec & tv_usec to millisecond
}
#endif

static inline TIME MKTIME(DINT sign, DINT mseconds, DINT seconds = 0, DINT minutes = 0,
                          DINT hours = 0, DINT days = 0) {
  /* sign is 1 for positive values, -1 for negative time... */
  DINT total_msecs = (((days * 24 + hours) * 60 + minutes) * 60 + seconds) * 1000 + mseconds;
  return sign >= 0 ? total_msecs : -total_msecs;
}

/**********************************************
 * FUNCTION_BLOCK
 *
 **********************************************/
class TON {
 public:
  // FB Interface - IN, OUT, IN_OUT variables
  _IN BOOL IN;
  _IN TIME PT;
  _OUT const BOOL &Q;
  _OUT const TIME &ET;

 private:
  _OUT BOOL _Q;
  _OUT TIME _ET;

  // FB private variables - TEMP, private and located variables
 private:
  BOOL m_PrevIn;     // previous state of IN for rising/falling edge recognigition
  DWORD m_PrevTime;  // previous time value
  BOOL m_Active;     // indicates active timer

 public:
  TON()
      : IN(FALSE)
      , PT(0)
      , Q(_Q)
      , ET(_ET)
      , _Q(FALSE)
      , _ET(0)
      , m_PrevIn(FALSE)
      , m_PrevTime(0)
      , m_Active(FALSE) {}

  void OnCycle() {
    // test if rising edge
    if (true == IN && false == m_PrevIn) {
      m_PrevTime = CURTIME();  // init previous time
      m_Active = true;
      m_PrevIn = IN;  // set previous state to current state
    }
    // test if falling edge
    else if (false == IN && true == m_PrevIn) {
      m_Active = _Q = false;
      _ET = 0;
      m_PrevIn = IN;  // set previous state to current state
    } else if (m_Active) {
      DWORD currentTime = CURTIME();
      _ET += currentTime - m_PrevTime;  // count up elapsed time
      m_PrevTime = currentTime;
      if (ET > PT) _Q = true;
    }
  }
};

/**********************************************
 * FUNCTION_BLOCK R_TRIG *
 **********************************************/
class R_TRIG {
 public:
  // FB Interface - IN, OUT, IN_OUT variables
  _IN BOOL CLK;
  _OUT const BOOL &Q;

 private:
  _OUT BOOL _Q;

  // FB private variables - TEMP, private and located variables
 private:
  BOOL M;

 public:
  R_TRIG() : CLK((BOOL)FALSE), Q(_Q), _Q((BOOL)FALSE), M((BOOL)FALSE) {}

  void OnCycle() {
    _Q = (CLK && !(M));
    M = CLK;
  }
};

/**********************************************
 * FUNCTION_BLOCK F_TRIG *
 **********************************************/
class F_TRIG {
 public:
  // FB Interface - IN, OUT, IN_OUT variables
  _IN BOOL CLK;
  _OUT const BOOL &Q;

 private:
  _OUT BOOL _Q;

  // FB private variables - TEMP, private and located variables
 private:
  BOOL M;

 public:
  F_TRIG() : CLK((BOOL)FALSE), Q(_Q), _Q((BOOL)FALSE), M((BOOL)FALSE) {}

  void OnCycle() {
    _Q = (!(CLK) && !(M));
    M = !(CLK);
  }
};

static inline INT DINT_TO_INT(DINT arg) { return (DINT)arg; }
static inline DWORD DINT_TO_DWORD(DINT arg) { return *(DWORD *)&arg; }
static inline TIME DINT_TO_TIME(DINT arg) { return (DINT)arg; }
static inline DINT DWORD_TO_DINT(DWORD arg) { return *(DINT *)&arg; }
static inline DINT INT_TO_DINT(INT arg) { return (DINT)arg; }
static inline BYTE INT_TO_BYTE(INT arg) { return (BYTE)arg; }
static inline INT WORD_TO_INT(WORD arg) { return (INT)arg; }
static inline DINT REAL_TO_DINT(REAL arg) { return (DINT)(floor(arg + 0.5)); }
static inline INT REAL_TO_INT(REAL arg) { return (INT)(floor(arg + 0.5)); }
static inline DWORD REAL_TO_DWORD(REAL arg) { return DINT_TO_DWORD((DINT)(floor(arg + 0.5))); }
static inline BOOL REAL_TO_BOOL(REAL arg) { return arg ? TRUE : FALSE; }
static inline INT BYTE_TO_INT(BYTE arg) { return (INT)arg; }
static inline SINT BYTE_TO_SINT(BYTE arg) { return (SINT)arg; }
// HMzstatic inline REAL LIMIT(REAL Min, REAL IN, REAL Max) { return MIN(MAX(IN, Min), Max); }

#endif  // PLCIEC_H
