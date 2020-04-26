void refreshTime() {
  DateTime now = rtc.now();
  if (now.hour() != lastRefresh.hour() || now.minute() != lastRefresh.minute()) {
    drawTime(now);
  }
}

void refreshDate() {
  DateTime now = rtc.now();
  if (now.year() != lastRefresh.year() || now.month() != lastRefresh.month() || now.day() != lastRefresh.day()) {
    drawDate(now);
  }
}
