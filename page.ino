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
  	switchS.roles[0] = SECONDARY;
	switchS.roles[1] = NEXT_PAGE;
	page.refreshDateTime = false;
      	drawStatusLine();
	switch (page.currentPage) {
		case -2: {
			switchS.roles[0] = MAIN;
			switchS.roles[1] = START_STOP;
			drawTitleF(F("Stopwatch"));
			drawStopwatch(stopwatch);
			break;
		}
		case -1: {
			switchS.roles[0] = timer.isGoing ? MAIN : SET;
			switchS.roles[1] = timer.isGoing ? START_STOP : INCREASE;
			drawTitleF(F("Timer"));
			drawTimer(timer, true);
			break;
		}
		case 0: {
			page.refreshDateTime = true;
			drawDate(rtc.now());
			drawTime(rtc.now());
			break;  
		}
		case 1: {
			drawDate(rtc.now());
			break;
		}
	}
}

void checkPage() {
  if (page.toggleChange) {
    handlePage();
    page.toggleChange = false;
  }
  if (page.refreshDateTime) {
    refreshTime();
    refreshDate();
  }
}
