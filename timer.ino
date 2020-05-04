void startStopTimer() {
	if (page.currentPage == -1 && timer.mode == COUNTDOWN_T) {
    		timer.isGoing = !timer.isGoing;
    		timer.stopDiff = timer.targetTime - rtc.now();
    		switchS.roles[0] = timer.isGoing ? MAIN : RESET;
    		drawTimer(timer, true);
  	}
}

void resetTimer() {
	timer = TimerState();
}

void doCountdown() {
  DateTime now = rtc.now();
  if (timer.isGoing) {
    TimeSpan diff = timer.targetTime - now;
    if (diff.totalseconds() == 0) {
      timer.mode = FINISHED_T; 
    } else {
      int blocks[3] = { diff.hours(), diff.minutes(), diff.seconds() };
      for (int i = 0; i < sizeof(timer.blocks) / sizeof(*(timer.blocks)); i++) {
        timer.lastBlocks[i] = timer.blocks[i];
        timer.blocks[i] = blocks[i];
      }
    }
    timer.toggleChange = true;
  } else {
    timer.targetTime = now + timer.stopDiff;
  }
}

void setupTimer() {
  timer.targetTime = rtc.now() + TimeSpan(0, timer.blocks[0], timer.blocks[1], timer.blocks[2]);
  timer.mode = COUNTDOWN_T;
  timer.isGoing = true;
  switchS.roles[0] = MAIN;
  switchS.roles[1] = START_STOP;
}

void setTimer() {
  if (timer.currentBlock < (sizeof(timer.blocks) / sizeof(*(timer.blocks))) - 1) {
    timer.currentBlock++;
  } else {
    setupTimer();
  }
  timer.toggleChange = true;
}

void incrementTimer() {
  timer.blocks[timer.currentBlock] += timer.blocks[timer.currentBlock] < (timer.currentBlock == 0 ? 99 : 59) ? 1 : -timer.blocks[timer.currentBlock];
  timer.toggleChange = true;
}

void checkTimer() {
  if (timer.mode == COUNTDOWN_T) {
    doCountdown();
  } else if (timer.mode == FINISHED_T) {
    timer.toggleChange = true;
    resetTimer();
  }
  if (timer.toggleChange && page.currentPage == -1) {
    drawTimer(timer);
    timer.toggleChange = false;
  }
}
