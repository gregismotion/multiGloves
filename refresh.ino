void refreshTime() {
  DateTime now = rtc.now();
  if (now.hour() != page.lastDateTimeRefresh.hour() || now.minute() != page.lastDateTimeRefresh.minute()) {
    drawTime(now);
  }
}

void refreshDate() {
  DateTime now = rtc.now();
  if (now.year() != page.lastDateTimeRefresh.year() || now.month() != page.lastDateTimeRefresh.month() || now.day() != page.lastDateTimeRefresh.day()) {
    drawDate(now);
  }
}
