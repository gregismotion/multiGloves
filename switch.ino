const int SWITCH_DELAY = 500;

void switch0Changed() {
  switchS.flags[0] = digitalRead(switchS.pins[0]);
}
void switch1Changed() {
  switchS.flags[1] = digitalRead(switchS.pins[1]);
}

void setupSwitches() {
  pinMode(switchS.pins[0], INPUT);
  pinMode(switchS.pins[1], INPUT);
  attachInterrupt(digitalPinToInterrupt(switchS.pins[0]), switch0Changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(switchS.pins[1]), switch1Changed, CHANGE);
}

void handleSwitch() {
  unsigned long currentMillis = millis();
  if (currentMillis - switchS.lastPress >= SWITCH_DELAY) {
    switchS.lastPress = currentMillis;
    if (switchS.flags[0]) {
      switch (switchS.roles[0]) {
        case SECONDARY: {
          secondary.toggleSecondary = true;
          break;
        }
        case DOWN: {
          incrementSecondary();
          break;
        }
        case SET: {
          setTimer();
          break;
        }
        case MAIN: {
          resetStopwatch();
          page.currentPage = 0;
          page.toggleChange = true;
          break;
        }
        case RESET: {
          resetTimer();
          page.toggleChange = true;
          timer.toggleChange = true;
          break;
        }
      }
    }
    if (switchS.flags[1]) {
      switch (switchS.roles[1]) {
        case NEXT_PAGE: {
          incrementPage();
          break;
        }
        case SELECT: {
          selectSecondary();
          break;
        }
        case INCREASE: {
          incrementTimer();
          break;
        }
        case START_STOP: {
          startStopTimer();
          startStopStopwatch();
          break;
        }
      }
    }
  }
}

void checkSwitch() {
  if (switchS.flags[0] || switchS.flags[1]) {
    handleSwitch();
  }
}
