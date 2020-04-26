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
  if (switchS.pin0) {
    switch (switchS.role0) {
      default: {
        break;
      }
    }
  }
  if (switchS.pin1) {
    switch (switchS.role1) {
      default: {
        break;
      }
    }
  }
}
