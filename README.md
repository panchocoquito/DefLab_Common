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

Debug flags must be defined **before** including the header. Enable the debug prints by defining at least one category above the include. 
Categories are meant to be self explanatory, but you can assign them any way you like. 

For a full list of available macros, see the source. 



```cpp
#define DEBUG_MOTOR 1  // see DefLab_Common.h for full macro list

#include <DefLab_Common.h>  // add this library after the macro

void setup() {
  // Initiate debug and choose a baud rate
  DL_DEBUG_BEGIN(115200);
}

void loop() {
  // Choose a category and print interval in ms
  DL_DEFINE_DEBUG_CATEGORY_LOCAL(MOTOR, 500);

  int x = analogRead(A0);

  // Call the function to print at the interval you provided
  DL_DUMP_CAT(      // DL_DUMP_CAT accesses any of the categories
    MOTOR,          // first param is your category
    {               // then whatever you want in the body
      debug("x=");  // 'debug' prints without a new line
      debugln(x);   // 'debugln' adds a carriage return
    });             // be sure to close parens and add ;
}
```

---

### Shared enums

`DefLab_Common` defines a small set of strongly-typed enums that are shared across Def Lab libraries.  
They exist here so multiple libraries can agree on **the same vocabulary** for inputs, outputs, and hardware routing.

These enums are:
- **Scoped** (`enum class`)
- **Type-safe**
- Intended for use in configuration structs, constructors, and mode selection logic

They do not implement behavior on their own.

#### Available enums

```cpp
DefLab::SensorInputMode
DefLab::RelayOutputMode
DefLab::ButtonInputMode
```

#### Available modes

```cpp
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
