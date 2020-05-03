void resetStopwatch() {
  stopwatch = StopwatchState();
}

void startStopStopwatch() {
	stopwatch.isGoing = !stopwatch.isGoing;
	if (!stopwatch.isGoing) {
		stopwatch.stopDiffSaved = false;
	}   
	switchS.roles[0] = stopwatch.isGoing ? LAP : MAIN;
}

void doStopwatch() {
	if (stopwatch.isGoing) {
	    	TimeSpan diff = rtc.now() - (stopwatch.startTime - stopwatch.stopDiff);
		int blocks[3] = { diff.hours(), diff.minutes(), diff.seconds() };
		for (int i = 0; i < sizeof(stopwatch.blocks) / sizeof(*(stopwatch.blocks)); i++) {
	   		stopwatch.lastBlocks[i] = stopwatch.blocks[i];
	    		stopwatch.blocks[i] = blocks[i];
	    	}
		stopwatch.toggleChange = true;
	} else {
		if (!stopwatch.stopDiffSaved) {
	      		stopwatch.stopDiff = rtc.now() - stopwatch.startTime;
	      		stopwatch.stopDiffSaved = true;
	    	}
	}
}

void checkStopwatch() {
  if (page.currentPage == -2) {
    doStopwatch();
    if (stopwatch.toggleChange) {
      drawStopwatch(stopwatch); //EVIL: HAS WEIRD SIDE EFFECTS
      stopwatch.toggleChange = false;
    }
  }
}
