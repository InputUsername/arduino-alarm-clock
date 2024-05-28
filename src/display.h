/*
 * display.h:
 *   Defines various functions related to printing to the LCD display.
 *   Also declares a global variable lcd that is used to access the display directly.
 */

#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <LiquidCrystal.h>
#include "constants.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void clearLine(int line) {
  // Print 16 spaces to clear the line
  lcd.setCursor(0, line);
  lcd.print("                ");
}

void printPadded(int n) {
  if (n < 10) {
    lcd.print("0");
  }
  lcd.print(n);
}

void printTime(int *timeArray, bool showSeconds) {
  printPadded(timeArray[UNIT_H]);
  lcd.print(":");
  printPadded(timeArray[UNIT_M]);

  if (showSeconds) {
    lcd.print(":");
    printPadded(timeArray[UNIT_S]);
  }
}

void printSelection(int selectedClock, int selectedUnit) {  
  int pos, i;
  
  lcd.setCursor(11*selectedClock + 3*selectedUnit + 1, 1);
  lcd.print("^");
}

#endif
