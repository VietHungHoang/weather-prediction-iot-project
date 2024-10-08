void setupNTPClient(){
  timeClient.setPoolServerName(poolName);
  timeClient.setTimeOffset(timeOffset);
  timeClient.begin();
}

void getTime(){
  while(!timeClient.update()) timeClient.forceUpdate();
  // timeFormatted = timeClient.getFormattedTime();
  day = timeClient.getDay();
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.println(timeClient.getEpochTime());
  struct tm *ptm = gmtime((time_t *)&epochTime);
  date = ptm->tm_hour;
  month = ptm->tm_min;
  year = ptm->tm_year + 1900;
  // Serial.printf(timeClient.getDateTime());
  // Serial.printf(timeClient.getFormattedDateTime();
  Serial.printf("%s %s %d/%d/%d",timeFormatted, Days[day], date, month, year);
}

// void updateTime(){
//   giay++;
//   if(giay == 60) {
//     phut++;
//     giay = 0;
//   }
//   if(phut == 60) {
//     gio++;
//     phut = 0;
//   }
//   if(gio == 24) {                              // Sau 1 ngày cập nhật thời gian 1 lần
//     gio = 0;
//     getThoigian();
//   }
//   updateTimeLCD();
// }