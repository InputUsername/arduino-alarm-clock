/*
 * constants.h:
 *   Various named constants.
 */

#ifndef __CONSTANTS_H
#define __CONSTANTS_H

const int PIN_BUZZER = 2;
const int PIN_BUTTONS = 0;

const int BUTTON_COUNT = 5;

/*
 * Button analog input values
 * These have been taken from http://www.okaphone.nl/files/LCD1602KEY%20V1.1.pdf
 */
const int BUTTON_VALUES[BUTTON_COUNT] = {
  30,  // Right
  150, // Up
  350, // Down
  535, // Left
  760  // Select
};

// Button identifiers
const int BUTTON_NONE = -1;
const int BUTTON_RIGHT = 0;
const int BUTTON_UP = 1;
const int BUTTON_DOWN = 2;
const int BUTTON_LEFT = 3;
const int BUTTON_SELECT = 4;

// 1000 milliseconds in one second
const int SECOND = 1000;

// Buzzer sound frequency & duration
int BUZZER_FREQ = 1000;
int BUZZ_DURATION = SECOND/4;

// State identifiers
const int STATE_CLOCK = 0;
const int STATE_ALARM = 1;

// Identifiers for the different units
// These also work as an index into an array storing a time
const int UNIT_H = 0;
const int UNIT_M = 1;
const int UNIT_S = 2;

// Identifiers for the two clocks (current time and alarm time)
const int CLOCK_CURRENT = 0;
const int CLOCK_ALARM = 1;

#endif // __CONSTANTS_H
