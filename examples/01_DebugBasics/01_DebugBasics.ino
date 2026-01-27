#define DEBUG_MOTOR 1  // see DefLab_Common.h for full macro list

#include <DefLab_Common.h>  // add this library after the macro

void setup() {
  // Initiate debug and choose a baud rate
  DL_DEBUG_BEGIN(115200);
}

void loop() {
  // Choose a category and print interval in ms
  DL_DEFINE_DEBUG_CATEGORY_LOCAL(MOTOR, 500);

  static int x = 0;
  x++;

  // Call the function to print at the interval you provided
  DL_DUMP_CAT(      // DL_DUMP_CAT accesses any of the categories
    MOTOR,          // first param is your category
    {               // then whatever you want in the body
      debug("x=");  // 'debug' prints without a new line
      debugln(x);   // 'debugln' adds a carriage return
    });             // be sure to close parens and add ;
}
