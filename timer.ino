void startStopTimer() {
  if (page.currentPage == -1 && timer.mode == COUNTDOWN_T) {
    timer.isGoing = !timer.isGoing;
    timer.stopDiff = timer.targetTime - rtc.now();
    drawTimer(timer, true);
  }
  if (timer.isGoing) {
    switchS.role0 = MAIN;
  } else {
    switchS.role0 = RESET;
  }
}

void resetTimer() {
  DateTime now = rtc.now();
  timer.currentBlock = 0;
  timer.toggleChange = false;
  timer.mode = SET_T;
  timer.startTime = now;
  timer.targetTime = now;
  timer.firstRefresh = true;
  for (int i = 0; i < sizeof(timer.blocks) / sizeof(*(timer.blocks)); i++) {
    timer.blocks[i] = 0;
    timer.lastBlocks[i] = 0;
  }
  timer.isGoing = false;
}

void doCountdown() {
  if (timer.isGoing) {
    TimeSpan diff = timer.targetTime - rtc.now();
    if (diff.totalseconds() == 0) {
      timer.mode = FINISHED_T; 
    } else {
      timer.lastBlocks[0] = timer.blocks[0];
      timer.blocks[0] = diff.hours();
      timer.lastBlocks[1] = timer.blocks[1];
      timer.blocks[1] = diff.minutes(); 
      timer.lastBlocks[2] = timer.blocks[2];
      timer.blocks[2] = diff.seconds();
    }
    timer.toggleChange = true; 
  } else {
    timer.targetTime = rtc.now() + timer.stopDiff;
  }
}

void setupTimer() {
  timer.targetTime = rtc.now() + TimeSpan(0, timer.blocks[0], timer.blocks[1], timer.blocks[2]);
  timer.mode = COUNTDOWN_T;
  timer.isGoing = true;
  switchS.role0 = MAIN;
  switchS.role1 = START_STOP;
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
  int limit = 59;
  if (timer.currentBlock == 0) {
    limit = 99;
  }
  if (timer.blocks[timer.currentBlock] < limit) {
    timer.blocks[timer.currentBlock]++;
  } else {
    timer.blocks[timer.currentBlock] = 0;
  }
  timer.toggleChange = true;
}
