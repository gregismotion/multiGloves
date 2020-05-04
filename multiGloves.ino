#include "RTClib.h"
#include <U8x8lib.h>
#include <AltSoftSerial.h>

struct PageState {
  int currentPage = 0;
  int maxPage = 1;
  bool toggleChange = false;
  unsigned long lastPress = 0;
  bool refreshDateTime = false;
  DateTime lastDateTimeRefresh;
};
enum SwitchRole { NEXT_PAGE, DOWN, SELECT, SECONDARY, SET, INCREASE, MAIN, START_STOP, RESET, LAP };
struct SwitchState {
  const int pins[2] = { 2, 3 };
  volatile int flags[2] = { LOW, LOW };
  int roles[2] = { SECONDARY, NEXT_PAGE };
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
struct StopwatchState {
	int blocks[3] = { 0, 0, 0 };
	int lastBlocks[3] = { 0, 0, 0 };
	bool firstRefresh = true;
	bool toggleChange = false;
	DateTime startTime;
	TimeSpan stopDiff;
	bool stopDiffSaved = true;
	bool stopDone = false;
	bool firstStart = true;
	bool isGoing = false;
};

RTC_DS3231 rtc;
PageState page;
SecondaryState secondary;
SwitchState switchS;
TimerState timer;
StopwatchState stopwatch;

void setup() {
  Serial.begin(9600);
  initScreen();
  initBt();
  initRtc(rtc);
  setupSwitches();
  page.toggleChange = true;
}

void loop() {
  checkBt();
  checkSwitch();
  checkPage();
  checkSecondary();
  checkTimer();
  checkStopwatch();
}
