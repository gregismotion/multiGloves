#include "RTClib.h"
#include <U8x8lib.h>
#include <AltSoftSerial.h>

struct PageState {
  int currentPage = 0;
  int maxPage = 1;
  bool toggleChange = false;
  unsigned long lastPress = 0;
  bool refreshDateTime = false;
};
enum SwitchRole { NEXT_PAGE, DOWN, SELECT, SECONDARY, SET, INCREASE, MAIN, START_STOP, RESET };
struct SwitchState {
  const int pin0 = 2;
  const int pin1 = 3;
  volatile int flag0 = LOW;
  volatile int flag1 = LOW;
  int role0 = SECONDARY;
  int role1 = NEXT_PAGE;
  unsigned long lastPress = 0;
};
struct SecondaryState {
  char options[4][15];
  int maxOption = 4;
  int currentOption = 0;
  int lastOption = 0;
  bool toggleSecondary = false;
  bool isOn = false;
  bool toggleChange = false;
  bool drawAll = false;
};
enum TimerMode { SET_T, COUNTDOWN_T, FINISHED_T };
struct TimerState {
  int currentBlock = 0;
  bool toggleChange = false;
  int mode = SET_T;
  int blocks[3] = { 0, 0, 0 };
  int lastBlocks[3] = { 0, 0, 0 };
  DateTime startTime;
  DateTime targetTime;
  TimeSpan stopDiff;
  bool firstRefresh = true;
  bool isGoing = false;
};

void drawTimer(TimerState timer, bool fullRefresh = false); //AH GOD ARDUINO BUILD CANT CREATE IT'S PROTOTYPE COME ON

RTC_DS3231 rtc;
PageState page;
SecondaryState secondary;
SwitchState switchS;
TimerState timer;
DateTime lastRefresh;

void setup() {
  Serial.begin(9600);
  initScreen();
  initBt();
  initRtc(rtc);
  setupSwitches();
  page.toggleChange = true;
}

void loop() {
  if (isReceiving()) {
      //char notification[50];
      //btSafeReadLine(notification, 50);
      //Serial.println(notification);
  }
  if (page.refreshDateTime) {
    refreshTime();
    refreshDate();
  }
  if (switchS.flag0 || switchS.flag1) {
    handleSwitch();
  }
  if (page.toggleChange) {
    handlePage();
    page.toggleChange = false;
  }
  if (secondary.toggleSecondary) {
    secondary.isOn = !secondary.isOn;
    if (secondary.isOn) {
      setupSecondary();
    }
    secondary.toggleSecondary = false;
  }
  if (secondary.toggleChange && secondary.isOn) {
    handleSecondary();
    secondary.toggleChange = false;
  }
  if (timer.mode == COUNTDOWN_T) {
    doCountdown();
  } else if (timer.mode == FINISHED_T) {
    timer.toggleChange = true;
    resetTimer();
  }
  if (timer.toggleChange && page.currentPage == -1) {
    drawTimer(timer);
    timer.toggleChange = false;
  }
}
