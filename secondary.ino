void resetSecondaryOptions() {
  for (int i = 0; i < secondary.maxOption; i++ ) {
    strcpy(secondary.options[i], "");
  } 
}

void setupSecondary() {
  page.refreshDateTime = false;
  switchS.roles[0] = DOWN;
  switchS.roles[1] = SELECT;
  strcpy(secondary.options[0], "Back");
  secondary.maxOption = 1;
  switch (page.currentPage) {
    case 0: {
      strcpy(secondary.options[1], "Sync time (BT)");
      strcpy(secondary.options[2], "Timer");
      strcpy(secondary.options[3], "Stopwatch");
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
    drawTitleF(F("Secondary"));
    for (int i = 0; i < secondary.maxOption; i++) {
      drawOption(i, secondary.options[i], secondary.currentOption == i);
    }
    secondary.drawAll = false;
  } else {
    drawOption(secondary.currentOption, secondary.options[secondary.currentOption], true);
    drawOption(secondary.lastOption, secondary.options[secondary.lastOption], false);
  }
}

void resetSecondary() {
  secondary.currentOption = 0;
  resetSecondaryOptions();
  secondary.toggleSecondary = true;
}

void selectSecondary() {
  if (secondary.currentOption == 0) {
    page.refreshDateTime = true;
    page.currentPage = 0;
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
        case 2: {
          page.currentPage = -1;
          page.toggleChange = true;
          break;
        }
        case 3: {
          page.currentPage = -2;
          page.toggleChange = true;
        }
      }
      break;
    }
  }
  resetSecondary();
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

void checkSecondary() {
  if (secondary.toggleSecondary) {
    secondary.isOn = !secondary.isOn;
    if (secondary.isOn) {
      setupSecondary();
    }
    secondary.toggleSecondary = false;
  }
  if (secondary.toggleChange && secondary.isOn) {
    handleSecondary();
    secondary.toggleChange = false;
  }
}
