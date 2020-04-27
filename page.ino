void incrementPage() {
  if (page.currentPage < page.maxPage) {
    page.currentPage++;
  } else {
    page.currentPage = 0; 
  }
  page.toggleChange = true;
}

void handlePage() {
  u8x8.clearDisplay();
  switchS.role0 = SECONDARY;
  switchS.role1 = NEXT_PAGE;
  page.refreshDateTime = false;
  switch (page.currentPage) {
    case 0: {
      page.refreshDateTime = true;
      drawDate(rtc.now());
      drawTime(rtc.now());
      drawBattery(100);
      break;  
    }
    case 1: {
      drawDate(rtc.now());
      break;
    }
  }
}
