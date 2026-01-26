# DefLab_Common

**DefLab_Common** is a small, header-only utility library shared across Def Lab Arduino projects.

It provides:
- A unified, category-based debug system that compiles out cleanly when disabled
- Lightweight print macros (`debug`, `debugln`, etc.)
- A reusable, non-blocking interval gate for throttled debug output
- A handful of shared enums used by Def Lab libraries

This library is intentionally simple and readable. It favors clarity and predictability over heavy automation or generated documentation.

---

## Installation

### Arduino IDE (manual)
1. Download this repository as a ZIP.
2. In the Arduino IDE:  
   **Sketch → Include Library → Add .ZIP Library…**
3. Restart the IDE if needed.

### From source
Clone or copy this folder into your Arduino libraries directory:

- **macOS:** `~/Documents/Arduino/libraries/DefLab_Common`
- **Windows:** `Documents/Arduino/libraries/DefLab_Common`
- **Linux:** `~/Arduino/libraries/DefLab_Common`

---

## Basic usage

### DEBUG flags

Debug flags must be defined **before** including the header.

```cpp
#define DEBUG 1
#define DEBUG_MOTOR 1

#include <DefLab_Common.h>

void setup() {
  DL_DEBUG_BEGIN(115200);
}

void loop() {
  DL_DEFINE_DEBUG_CATEGORY_LOCAL(MOTOR, 500);

  int x = analogRead(A0);

  DL_DUMP_CAT(MOTOR, {
    debug("x=");
    debugln(x);
  });
}
