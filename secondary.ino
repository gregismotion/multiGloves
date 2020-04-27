void resetSecondaryOptions() {
  for (int i = 0; i < secondary.maxOption; i++ ) {
    strcpy(secondary.options[i], "");
  } 
}

void setupSecondary() {
  page.refreshDateTime = false;
  switchS.role0 = DOWN;
  switchS.role1 = SELECT;
  resetSecondaryOptions();
  secondary.options[0] = "Back";
  secondary.maxOption = 1;
  switch (page.currentPage) {
    case 0: {
      secondary.options[1] = "Sync time (BT)";
      secondary.options[2] = "Timer";
      secondary.options[3] = "Stopwatch";
      secondary.maxOption += 3;
      break;
    }
  }
  secondary.drawAll = true;
  handleSecondary();
}

void handleSecondary() {
  if (secondary.drawAll) {
    u8x8.clearDisplay();
    drawTitle("Secondary");
    for (int i = 0; i < secondary.maxOption; i++) {
      drawOption(i, secondary.options[i], secondary.currentOption == i);
    }
    secondary.drawAll = false;
  } else {
    drawOption(secondary.currentOption, secondary.options[secondary.currentOption], true);
    drawOption(secondary.lastOption, secondary.options[secondary.lastOption], false);
  }
}

void selectSecondary() {
  if (secondary.currentOption == 0) {
    page.refreshDateTime = true;
    page.currentPage = 0;
    secondary.toggleSecondary = true;
    page.toggleChange = true;
  }
  switch(page.currentPage) {
    case 0: {
      switch(secondary.currentOption) {
        case 1: {
          drawSyncTime();
          syncTimeBt();
          break;
        }
      }
      break;
    }
  }
}

void incrementSecondary() {
  secondary.lastOption = secondary.currentOption;
  if (secondary.currentOption + 1 < secondary.maxOption) {
    secondary.currentOption++;
  } else {
    secondary.currentOption = 0; 
  }
  secondary.toggleChange = true;
}
