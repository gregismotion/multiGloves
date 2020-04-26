void handlePage(int page) {
  u8x8.clearDisplay();
  switch (page) {
    case 0: {
      drawTime(rtc.now());
      drawDate(rtc.now());
      drawBattery(100);
      break;  
    }
  }
}
