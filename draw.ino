U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);
int defaultFont = u8x8_font_amstrad_cpc_extended_r;

void initScreen() {
  u8x8.begin();
}

void formatTime(char* timeBuf, int hour, int minute) {
  snprintf(timeBuf, 7, "%02d:%02d", hour, minute);
}
void drawTime(DateTime date) {
  char timeBuf[6];
  formatTime(timeBuf, date.hour(), date.minute());
  u8x8.setFont(u8x8_font_courB24_3x4_n);
  u8x8.drawString(0, 2, timeBuf);
}

void formatDate(char* dateBuf, int year, int month, int day) {
  snprintf(dateBuf, 15, "%04d. %02d. %02d.", year, month, day);
}
void drawDate(DateTime date) {
  char dateBuf[14];
  formatDate(dateBuf, date.year(), date.month(), date.day());
  u8x8.setFont(defaultFont);
  u8x8.drawString(0, 7, dateBuf);
}

void formatBattery(char* batteryBuf, int percentage) {
  snprintf(batteryBuf, 6, "%d%%", percentage);
}
void drawBattery(int percentage) {
  char batteryBuf[5];
  formatBattery(batteryBuf, percentage);
  u8x8.setFont(defaultFont);
  u8x8.drawString(11, 0, batteryBuf);
}

void drawStatusLine() {
	drawBattery(100);
}

void drawSyncTime() {
  u8x8.clearDisplay();
  u8x8.setFont(defaultFont);
  u8x8.drawString(0, 0, "Sync time by BT");
}

void drawTitleF(__FlashStringHelper* output) {
  u8x8.setFont(defaultFont);
  u8x8.setInverseFont(1);
  u8x8.setCursor(0, 1);
  u8x8.print(output);
  u8x8.setInverseFont(0);
}

void drawOption(int pos, char* output, bool selected) {
  u8x8.setFont(defaultFont);
  u8x8.setInverseFont(selected);
  u8x8.drawString(0, pos + 2, output);
  u8x8.setInverseFont(0);
}

void formatTimerValue(char* out, int in) {
  snprintf(out, 3, "%02d", in);
}
void drawBlock(int block, char* out, int x = 0,  int y = 0, bool timer = true) {
  if (timer) {
    u8x8.setFont(u8x8_font_inb21_2x4_n);
    switch(block) {
      case -1: {
        u8x8.setCursor(x + 4, y);
        u8x8.print(out);
        u8x8.setCursor(x + 10, y);
        u8x8.print(out);
        break;
      }
      case 0: {
        u8x8.setCursor(x, y);
        u8x8.print(out);
        break;
      }
      case 1: {
        u8x8.setCursor(x + 6, y);
        u8x8.print(out);
        break;
      }
      case 2: {
        u8x8.setFont(u8x8_font_7x14B_1x2_n);
        u8x8.setCursor(x + 12, y + 2);
        u8x8.print(out); 
        break;
      }
    }
  } else {
    switch(block) {
      case -1: {
        u8x8.setCursor(x + 2, y);
        u8x8.print(out);
        u8x8.setCursor(x + 5, y);
        u8x8.print(out);
        break;
      }
      case 0: {
        u8x8.setCursor(x, y);
        u8x8.print(out);
        break;
      }
      case 1: {
        u8x8.setCursor(x + 3, y);
        u8x8.print(out);
        break;
      }
      case 2: {
        u8x8.setCursor(x + 6, y);
        u8x8.print(out); 
        break;
      }
    }
  }
}
void drawTimer(TimerState timer, bool fullRefresh = false); //AH GOD ARDUINO BUILD CANT CREATE IT'S PROTOTYPE COME ON
void drawTimer(TimerState timer, bool fullRefresh = false) {
  int x = 1;
  int y = 3;
  char delimiter[2] = ":";
  if (timer.firstRefresh) {
    drawBlock(-1, delimiter, x, y);
  }
  switch (timer.mode) {
    case SET_T: {
      char tempBuf[2];
      for (int i = 0; i < sizeof(timer.blocks) / sizeof(*(timer.blocks)); i++) {
        u8x8.setInverseFont(timer.currentBlock == i);
        formatTimerValue(tempBuf, timer.blocks[i]);
        drawBlock(i, tempBuf, x, y);  
      }
      u8x8.setInverseFont(0);
      break;
    }
    case COUNTDOWN_T: {
      char tempBuf[2];
      u8x8.setInverseFont(!timer.isGoing);
      for (int i = 0; i < sizeof(timer.blocks) / sizeof(*(timer.blocks)); i++) {
        if (timer.blocks[i] != timer.lastBlocks[i] || fullRefresh) {
          formatTimerValue(tempBuf, timer.blocks[i]);
          drawBlock(i, tempBuf, x, y);
        }   
      }
      u8x8.setInverseFont(0);
      break;
    }
    case FINISHED_T: {
      char finished[3] = "00";
      u8x8.setInverseFont(1);
      if (timer.firstRefresh) {
        drawBlock(-1, delimiter, x, y);
      }
      for (int i = 0; i < sizeof(timer.blocks) / sizeof(*(timer.blocks)); i++) {
        drawBlock(i, finished, x, y);
      }
      u8x8.setInverseFont(0);
      break;
    }
  }
}

void drawStopwatch(StopwatchState stopwatch) {
  int x = 4;
  int y = 2;
  char tempBuf[2];
  drawBlock(-1, ":", x, y, false);
  for (int i = 0; i < sizeof(stopwatch.blocks) / sizeof(*(stopwatch.blocks)); i++) {
    if (stopwatch.blocks[i] != stopwatch.lastBlocks[i] || stopwatch.firstRefresh) {
      formatTimerValue(tempBuf, stopwatch.blocks[i]); //EVIL: HAS WEIRD SIDE EFFECTS 
      drawBlock(i, tempBuf, x, y, false);
    }
  }
  stopwatch.firstRefresh = false;
}
