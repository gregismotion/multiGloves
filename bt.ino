const int BT_TIMEOUT = 60000 * 3;

AltSoftSerial btSerial;


void initBt() {
  btSerial.begin(9600);
}
void btSafeReadLine(char* outStr, int len) {
  btSerial.readString().toCharArray(outStr, len);
}
void btSafePrintln(String str) {
  btSerial.println(str);
}
void waitForBt() {
  unsigned long waitingStart = millis();
  while(btSerial.available() == 0 && millis() - waitingStart < BT_TIMEOUT) { }
}
void syncTimeBt() {
  btSafePrintln("TIME");
  waitForBt();
  char input[20];
  btSafeReadLine(input, 20);
  DateTime date;
  tokenizeDate(&date, input);
  setRtcTime(rtc, date);
}
bool isReceiving() {
  return btSerial.available();
}

void checkBt() {
  /*if (isReceiving()) {
  }*/
}
