#define DEBUG 1
#define DEBUG_MOTOR 1

#include <DefLab_Common.h>

void setup() {
  DL_DEBUG_BEGIN(115200);
}

void loop() {
  DL_DEFINE_DEBUG_CATEGORY_LOCAL(MOTOR, 500);

  static int x = 0;
  x++;

  DL_DUMP_CAT(MOTOR, {
    debug("x=");
    debugln(x);
  });
}
