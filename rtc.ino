
const char BT_DELIMITER[1] = ";";

void initRtc(RTC_DS3231 rtc) {
  rtc.begin();
  if (rtc.lostPower()) {
      //syncTime();
  }
}

void tokenizeDate(DateTime* date, char* in) { 
  char* token = strtok(in, BT_DELIMITER);
  int count = 0;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  while(token) {
    switch(count) {
      case 0: year = atoi(token); break;
      case 1: month = atoi(token); break;
      case 2: day = atoi(token); break;
      case 3: hour = atoi(token); break;
      case 4: minute = atoi(token); break;
      case 5: second = atoi(token); break;
    }
    token = strtok(NULL, BT_DELIMITER);
    count++;
  }
  *date = DateTime(year, month, day, hour, minute, second);
}
void setRtcTime(RTC_DS3231 rtc, DateTime date) {
  rtc.adjust(date);
}
