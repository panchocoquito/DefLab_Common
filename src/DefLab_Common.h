/*
  DefLab_Common.h — Unified Debug + Utils

  v0.6 2026-01-26
    • Added _HMI, _NEXTION
    • Removed lambda from DL_DUMP_CAT 
  v0.5 2025-09-16
    • Added debug helpers:
     - DL_debugGate (shared timer gate)
     - DL_DEFINE_DEBUG_CATEGORY_LOCAL(NAME, INTERVAL_MS)
     - DL_DUMP_CAT(NAME, { ... })
    • Keeps existing DEBUG rollup and print macros
*/

#pragma once  // safer than #ifndef/define

#include <Arduino.h>

namespace DefLab {

// ---------- Unified DEBUG Control ----------

// Debug macros are intentionally global (macros are not namespaced).
// Define DEBUG / DEBUG_<CATEGORY> in the sketch BEFORE including this header.
// If not defined, they default to 0 here and are compiled out.

#ifndef DEBUG
#define DEBUG 0
#endif
#ifndef DEBUG_MOTOR
#define DEBUG_MOTOR 0
#endif
#ifndef DEBUG_STATUS
#define DEBUG_STATUS 0
#endif
#ifndef DEBUG_TENSION
#define DEBUG_TENSION 0
#endif
#ifndef DEBUG_WIRE
#define DEBUG_WIRE 0
#endif
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif
#ifndef DEBUG_DIAMETER
#define DEBUG_DIAMETER 0
#endif
#ifndef DEBUG_BUTTONS
#define DEBUG_BUTTONS 0
#endif
#ifndef DEBUG_I2C
#define DEBUG_I2C 0
#endif
#ifndef DEBUG_HMI
#define DEBUG_HMI 0
#endif
#ifndef DEBUG_NEXTION
#define DEBUG_NEXTION 0
#endif

#if (DEBUG || DEBUG_MOTOR || DEBUG_STATUS || DEBUG_TENSION || DEBUG_WIRE || DEBUG_LEVEL \
     || DEBUG_DIAMETER || DEBUG_BUTTONS || DEBUG_I2C || DEBUG_HMI || DEBUG_NEXTION)
#define DL_HAVE_DEBUG 1
#else
#define DL_HAVE_DEBUG 0
#endif

// ---------- Print macros ----------
#if DL_HAVE_DEBUG
#define debug(...) Serial.print(__VA_ARGS__)
#define debugln(...) Serial.println(__VA_ARGS__)
// Optional helpers for PROGMEM literals:
#define debugF(s) Serial.print(F(s))
#define debuglnF(s) Serial.println(F(s))
#else
#define debug(...) ((void)0)
#define debugln(...) ((void)0)
#define debugF(s) ((void)0)
#define debuglnF(s) ((void)0)
#endif

// Start console only when any debug is on
#if DL_HAVE_DEBUG
#define DL_DEBUG_BEGIN(baud) \
  do { \
    Serial.begin((baud)); /* initialize Serial only when debug enabled */ \
  } while (0)
#else
#define DL_DEBUG_BEGIN(baud) \
  do { \
  } while (0) /* compiles to no-op when debug disabled */
#endif

// ---------- Common, reusable gate + category helpers ----------

// Shared non-blocking interval gate
#if DL_HAVE_DEBUG
static inline bool
DL_debugGate(uint32_t intervalMs, uint32_t& lastTick) {
  if (intervalMs == 0) return false;  // disabled
  const uint32_t now = millis();
  if (now - lastTick >= intervalMs) {
    lastTick = now;
    return true;
  }
  return false;
}
#else
static inline bool
DL_debugGate(uint32_t, uint32_t&) {
  return false;
}
#endif

// Declare a per-file category (creates local state & interval).
// Example in a .ino/.cpp: DL_DEFINE_DEBUG_CATEGORY_LOCAL(MOTOR, 500);
#define DL_DEFINE_DEBUG_CATEGORY_LOCAL(NAME, INTERVAL_MS) \
  static uint32_t DL_dbg_last_##NAME = 0; \
  static const uint32_t DL_dbg_interval_##NAME = (INTERVAL_MS)

// Category dump that compiles out when DEBUG_<NAME> == 0, and is interval-gated when on.
// Usage: DL_DUMP_CAT(MOTOR, { debug("x="); debug(x); debugln(); });
#define DL_DUMP_CAT(NAME, body) \
  do { \
    if ( \
      DEBUG_##NAME && /* category compile-time enable (0 = compiled out) */ \
      DefLab::DL_debugGate( \
        DL_dbg_interval_##NAME, /* per-category interval in milliseconds */ \
        DL_dbg_last_##NAME      /* per-category last execution timestamp */ \
        )                       /* returns true when interval has elapsed */ \
    ) { \
      body; /* user-provided debug statements */ \
    } \
  } while (0) /* macro safety: single-statement wrapper */

// ---------- Enums used by our libraries ----------
enum class SensorInputMode : uint8_t {
  GPIO,
  OPTA_CTL,
  EXP_DIG,
  EXP_ANA
};

enum class RelayOutputMode : uint8_t {
  GPIO,
  OPTA_CTL,
  EXP_DIG
};

enum class ButtonInputMode : uint8_t {
  GPIO,
  OPTA_CTL,
  EXP_DIG
};

}  // namespace DefLab
