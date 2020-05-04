void resetStopwatch() {
  stopwatch = StopwatchState();
}

void startStopStopwatch() {
	stopwatch.isGoing = !stopwatch.isGoing;
	if (!stopwatch.stopDiffSaved) {
		stopwatch.stopDiff = rtc.now() - stopwatch.startTime;
		stopwatch.stopDiffSaved = true;
	}
	stopwatch.startTime = rtc.now();
	if (!stopwatch.isGoing && !stopwatch.stopDone) {
		stopwatch.stopDiffSaved = false;
		stopwatch.stopDone = true;
	}   
	switchS.roles[0] = stopwatch.isGoing ? LAP : MAIN;
}

void doStopwatch() {
	if (stopwatch.isGoing) {
		stopwatch.stopDone = false;
	    	TimeSpan diff = rtc.now() - (stopwatch.startTime - stopwatch.stopDiff);
		int blocks[3] = { diff.hours(), diff.minutes(), diff.seconds() };
		for (int i = 0; i < sizeof(stopwatch.blocks) / sizeof(*(stopwatch.blocks)); i++) {
	   		stopwatch.lastBlocks[i] = stopwatch.blocks[i];
	    		stopwatch.blocks[i] = blocks[i];
	    	}
		stopwatch.toggleChange = true;
	}
}

void checkStopwatch() {
  if (page.currentPage == -2) {
    doStopwatch();
    if (stopwatch.toggleChange) {
      drawStopwatch(stopwatch);
      stopwatch.toggleChange = false;
    }
  }
}
