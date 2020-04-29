const int SWITCH_DELAY = 500;

void switch0Changed() {
  switchS.flag0 = digitalRead(switchS.pin0);
}
void switch1Changed() {
  switchS.flag1 = digitalRead(switchS.pin1);
}

void setupSwitches() {
  pinMode(switchS.pin0, INPUT);
  pinMode(switchS.pin1, INPUT);
  attachInterrupt(digitalPinToInterrupt(switchS.pin0), switch0Changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(switchS.pin1), switch1Changed, CHANGE);
}

void handleSwitch() {  
  if (millis() - switchS.lastPress >= SWITCH_DELAY) {
    switchS.lastPress = millis();
    if (switchS.flag0) {
      switch (switchS.role0) {
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
    if (switchS.flag1) {
      switch (switchS.role1) {
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
        }
      }
    }
  }
}
