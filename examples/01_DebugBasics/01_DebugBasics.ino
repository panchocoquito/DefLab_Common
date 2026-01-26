#define DEBUG 1 // TODO: check formatting
#define DEBUG_MOTOR 1 // TODO: list all options

#include <DefLab_Common.h>

void setup() {
// Initiate debug and choose a baud rate
  DL_DEBUG_BEGIN(115200);
}

void loop() {
// Choose a category and print interval in ms
  DL_DEFINE_DEBUG_CATEGORY_LOCAL(MOTOR, 500);

  static int x = 0;
  x++;

  DL_DUMP_CAT(MOTOR, { // first param is your category
    debug("x=");       // debug prints without a new line
    debugln(x);        // debugln ends in a carriage return
  });
} // TODO: edit this in IDE 
