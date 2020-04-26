#include "RTClib.h"
#include <U8x8lib.h>
const int SWITCH_DELAY = 500;

struct PageState {
  int currentPage = 0;
  bool toggleChange = false;
};
enum SwitchRole { NEXT_PAGE, DOWN, SELECT, SECONDARY, SET, INCREASE, MAIN, START_STOP };
struct SwitchState {
  const int pin0 = 2;
  const int pin1 = 3;
  volatile int flag0 = LOW;
  volatile int flag1 = LOW;
  int role0 = SECONDARY;
  int role1 = NEXT_PAGE;
  unsigned long lastPress = 0;
};

RTC_DS3231 rtc;
PageState page;
SwitchState switchS;
DateTime lastRefresh;

void setup() {
  initScreen();
  initRtc(rtc);
  setupSwitches();
  page.toggleChange = true;
}

void loop() {
  refreshTime();
  refreshDate();
  if (page.toggleChange) {
    handlePage(page.currentPage);
    page.toggleChange = false;
  }
  if (switchS.flag0 || switchS.flag1) {
    handleSwitch();  
  }
}
