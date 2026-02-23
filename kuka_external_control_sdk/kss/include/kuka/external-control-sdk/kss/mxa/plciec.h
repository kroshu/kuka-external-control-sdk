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

#include <math.h>
#include <chrono>

#include <climits>
#include <string>

#define _IN     // NOOP
#define _OUT    // NOOP
#define _INOUT  // NOOP

// on windows in minwindef.h these identifiers are defined as macros thus sometimes causing problems
#undef IN
#undef OUT
#undef ERROR

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

namespace PLCIEC
{

// 1 BOOL boolean 1 h
typedef bool BOOL;
// 3 INT whole number (integer) 16 c
typedef short INT;
// 7 UINT unsigned whole number 16 d
typedef unsigned short UINT;
// 19 DWORD bit sequence 32 32 J, g
typedef unsigned int DWORD;

// 2 SINT short whole number (short integer) 8 c
typedef signed char SINT;
// 4 DINT double whole number (double integer) 32 c
typedef int DINT;
// 5 LINT long whole number (long integer) 64 c
typedef long LINT;
// 6 USINT unsigned short whole number (unsigned short integer) 8 d
typedef unsigned char USINT;
// 8 UDINT unsigned double whole number 32 d
typedef unsigned int UDINT;
// 9 ULINT unsigned long whole number 64 d
typedef unsigned long ULINT;
// 10 REAL real number 32 e
typedef float REAL;
// 11 LREAL long real number 64 f
typedef double LREAL;
// 12 TIME time duration -- b
typedef int TIME;  // Millisecond timestamp. Must be signed!
/*
// 13 DATE date (only) --b
typedef unsigned int DATE;
// 14 TIME_OF_DAY or TOD time of day --b
typedef unsigned int TIME_OF_DAY;
typedef unsigned int TOD;
// 15 DATE_AND_TIME or DT date and time -- b
typedef unsigned int DATE_AND_TIME;
typedef unsigned int DT;
*/
// 16 STRING variable-length string 8 i, g
typedef std::string STRING;
// 17 BYTE bit sequence 8 8 J, g
typedef unsigned char BYTE;
// 18 WORD bit sequence 16 16 J, g
typedef unsigned short WORD;
// 20 LWORD bit sequence 64 64 J, g
typedef unsigned long LWORD;
// 21 WSTRING variable-length double-byte string 16 i, g
typedef std::wstring WSTRING;

/* Set bit @ pos if val is true, clear bit @ pos if val is false */
#define ChBit(dw, idx, val) (dw) = (val) ? ((dw) | (1 << (idx))) : ((dw) & ~(1 << (idx)))

/* Return true if bit @ idx is set, otherwise false */
#define IsBitSet(dw, idx) (((dw) & (1 << (idx))) != 0)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))


inline int64_t getTimeInMilliseconds()
{
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

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
  int64_t m_PrevTime;  // previous time value
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
      m_PrevTime = getTimeInMilliseconds();  // init previous time
      m_Active = true;
      m_PrevIn = IN;  // set previous state to current state
    }
    // test if falling edge
    else if (false == IN && true == m_PrevIn) {
      m_Active = _Q = false;
      _ET = 0;
      m_PrevIn = IN;  // set previous state to current state
    } else if (m_Active) {
      int64_t currentTime = getTimeInMilliseconds();
      _ET += static_cast<TIME>(currentTime - m_PrevTime);  // count up elapsed time
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

static inline INT DINT_TO_INT(DINT arg) { return (INT)arg; }
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
}
