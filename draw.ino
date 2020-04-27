U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

void initScreen() {
  u8x8.begin();
  u8x8.setBusClock(200000);
  u8x8.setContrast(0);
  u8x8.setPowerSave(0);
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
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.drawString(0, 7, dateBuf);
}

void formatBattery(char* batteryBuf, int percentage) {
  snprintf(batteryBuf, 6, "%d%%", percentage);
}
void drawBattery(int percentage) {
  char batteryBuf[5];
  formatBattery(batteryBuf, percentage);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.drawString(11, 0, batteryBuf);
}

void drawSyncTime() {
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.drawString(0, 0, "Sync time by BT");
}

void drawTitle(char* output) {
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setInverseFont(1);
  u8x8.drawString(0, 0, output);
  u8x8.setInverseFont(0);
}

void drawOption(int pos, char* output, bool selected) {
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setInverseFont(selected);
  u8x8.drawString(0, pos + 2, output);
  u8x8.setInverseFont(0);
}

void drawTimer(int selectedBlock) {
  u8x8.setFont(u8x8_font_courB18_2x3_n);
  u8x8.setInverseFont(selectedBlock == 0);
  u8x8.setCursor(0, 3);
  u8x8.print("00");
  u8x8.setInverseFont(0);
  u8x8.print(":");
  u8x8.setInverseFont(selectedBlock == 1);
  u8x8.print("00");
  u8x8.setInverseFont(0);
  u8x8.print(":");
  u8x8.setInverseFont(selectedBlock == 2);
  u8x8.print("00");
  u8x8.setInverseFont(0);
}
