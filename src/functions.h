/*
 * functions.h:
 *   Several miscellaneous functions.
 */

#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "constants.h"

/*
 * Reads an analog button value from analog pin A0,
 * and returns the corresponding button identifier.
 */
int getButton() {
  int value, i;
  
  value = analogRead(PIN_BUTTONS);

  for (i = 0; i < BUTTON_COUNT; i++) {
    if (value < BUTTON_VALUES[i]) {
      return i;
    }
  }

  return BUTTON_NONE;
}

void updateCurrentTime(int *timeArray) {
  timeArray[UNIT_S]++;
  if (timeArray[UNIT_S] >= 60) {
    timeArray[UNIT_S] = 0;
    timeArray[UNIT_M]++;
  }
  if (timeArray[UNIT_M] >= 60) {
    timeArray[UNIT_M] = 0;
    timeArray[UNIT_H]++;
  }
  if (timeArray[UNIT_H] >= 24) {
    timeArray[UNIT_H] = 0;
  }
}

void changeTime(int *timeArray, int unit, int change) {
  timeArray[unit] += change;

  switch (unit) {
    case UNIT_H:
      if (timeArray[UNIT_H] < 0) {
        timeArray[UNIT_H] = 23;
      }
      if (timeArray[UNIT_H] > 23) {
        timeArray[UNIT_H] = 0;
      }
      break;
    case UNIT_M:
      if (timeArray[UNIT_M] < 0) {
        timeArray[UNIT_M] = 59;
      }
      else if (timeArray[UNIT_M] > 59) {
        timeArray[UNIT_M] = 0;
      }
      break;
  }
}

#endif // __FUNCTIONS_H
