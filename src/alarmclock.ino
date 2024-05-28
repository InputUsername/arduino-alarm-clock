/*
 * Arduino Alarm Clock
 * Version 1.2
 * Koen Bolhuis, 2016
 *
 * alarmclock.ino:
 *   Main program.
 */

#include "constants.h"
#include "display.h"
#include "functions.h"

/** Initialise global variables **/

// Used for timing and updating the current time
unsigned long timer, timerPrev;

// Used for timing the alarm buzzer
unsigned long alarmTimer, alarmTimerPrev;

/** Main program **/

void setup() {
  // Initialise a 16x2 character LCD display
  lcd.begin(16, 2);
  lcd.clear();
  
  // Designate the appropriate pins with the correct I/O mode
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTONS, INPUT);

  // Initialise the timer values
  timerPrev = millis();
  alarmTimerPrev = millis();
}

void loop() {
  /** Initialise static variables **/
  
  // Used to detect button presses
  static int button, buttonCheck, buttonPrev;
  
  // The time values for the two on-screen clocks
  static int currentTime[3] = {0, 0, 55};
  static int alarmTime[2] = {0, 1};
  
  /*
   * The current program state: STATE_CLOCK or STATE_ALARM,
   * depending on whether the alarm is buzzing.
   */
  static int state = STATE_CLOCK;
  
  // The currently selected time unit and clock that are to be changed
  static int selectedUnit = UNIT_H;
  static int selectedClock = CLOCK_CURRENT;
  
  static bool buzzer = false;

  /** Main loop code **/
  
  // Update the current time
  timer = millis();
  if (timer - timerPrev >= SECOND) {
    timerPrev = timer;

    updateCurrentTime(currentTime);
  }

  if (state == STATE_CLOCK) {
    // Check for input
    button = getButton();
    if (button != buttonPrev && button != BUTTON_NONE) {
      // Wait a bit to debounce the button
      delay(50);
  
      // Verify the button
      buttonCheck = getButton();
      if (buttonCheck == button && buttonCheck != BUTTON_NONE) {
        int timeDelta = 0;
        
        switch (buttonCheck) {
          case BUTTON_RIGHT:
            selectedClock = 1 - selectedClock;
            break;
          case BUTTON_LEFT:
            selectedUnit = 1 - selectedUnit;
            break;
          case BUTTON_UP:
            timeDelta = 1;
            break;
          case BUTTON_DOWN:
            timeDelta = -1;
            break;
        }

        // Update selection arrow if left or right was pressed
        clearLine(1);
        printSelection(selectedClock, selectedUnit);

        // Update time if up or down was pressed
        if (timeDelta != 0) {
          switch (selectedClock){
            case CLOCK_CURRENT:
              changeTime(currentTime, selectedUnit, timeDelta);
              break;
            case CLOCK_ALARM:
              changeTime(alarmTime, selectedUnit, timeDelta);
              break;
          }
        }
      }
    }
    buttonPrev = button;

    // Print time
    lcd.setCursor(0, 0);
    printTime(currentTime, true);
    lcd.setCursor(11, 0);
    printTime(alarmTime, false);

    printSelection(selectedClock, selectedUnit);

    // Check if alarm should go off
    if (currentTime[UNIT_H] == alarmTime[UNIT_H]
        && currentTime[UNIT_M] == alarmTime[UNIT_M]
        && currentTime[UNIT_S] == 0) {
      state = STATE_ALARM;
    }
  }
  else if (state == STATE_ALARM) {
    // Turn buzzer on or off periodically
    alarmTimer = millis();
    if (alarmTimer - alarmTimerPrev >= BUZZ_DURATION) {
      alarmTimerPrev = alarmTimer;

      buzzer = !buzzer;

      lcd.clear();

      if (buzzer) {
        tone(PIN_BUZZER, BUZZER_FREQ);

        lcd.setCursor(5, 0);
        lcd.print("ALARM!");
      }
      else {
        noTone(PIN_BUZZER);
      }
    }

    // End the alarm if the select button is pressed
    button = getButton();
    if (button == BUTTON_SELECT) {
      // Wait a bit to debounce the button
      delay(50);

      // Verify the button
      buttonCheck = getButton();
      if (buttonCheck == button && buttonCheck == BUTTON_SELECT) {
        buzzer = false;
        noTone(PIN_BUZZER);
        lcd.clear();
        
        state = STATE_CLOCK;
      }
    }
  }
}
