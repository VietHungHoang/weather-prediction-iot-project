int w = tft.width(), h = tft.height();

void setupLCD() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(BLACK);
  printText("IoT va Ung Dung 04", CYAN, 10, 10, 1);
  printText("ThS. N.T.T.Thuy", YELLOW, 19, 22, 1);
  printText("NHOM 10", WHITE, 22, 37, 2);
  tft.drawRect(0, 65, 128, 25, MAGENTA);
  tft.drawBitmap(10, 114, temperature, 20, 20, CYAN);
  tft.drawBitmap(10, 136, humidity, 20, 20, CYAN);
}

void updateTimeLCD() {
  // Day of the week
  printTextWithBackground(Days[day], YELLOW, BLACK, -1, 100, 1);
  // Print complete date:
  String dateString = date < 10 ? "0" + String(date) : String(date);
  String monthString = month < 10 ? "0" + String(month) : String(month);
  String currentDate = dateString + "/" + monthString + "/" + String(year);
  printTextWithBackground(currentDate, CYAN, BLACK, -1, 110, 1);
  // Print time;
  printTextWithBackground(timeFormatted, WHITE, BLACK, 15, 70, 2);

}

void printText(String text, uint16_t color, int x, int y, int textSize) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.print(text);
}

void printTextWithBackground(String text, uint16_t textColor, uint16_t backgroundColor, int x, int y, int textSize) {
  tft.setTextColor(textColor, backgroundColor);
  tft.setTextSize(textSize);
  if(x == -1){
  int16_t xText, yText; // Vị trí
  uint16_t textWidth, textHeight; // Chiều rộng và chiều cao
  tft.getTextBounds(text.c_str(), 0, 0, &xText, &yText, &textWidth, &textHeight);
    x = (w - textWidth) / 2;
  }
  if(x == -1){
  int16_t xText, yText; // Vị trí
  uint16_t textWidth, textHeight; // Chiều rộng và chiều cao
  tft.getTextBounds(text.c_str(), 0, 0, &xText, &yText, &textWidth, &textHeight);
    y = (h - textHeight) / 2;
  }
  tft.setCursor(x, y);
  tft.print(text);
}

// void getWeather(){
//   http.begin("http://api.weatherbit.io/v2.0/current?&lat="+latitude+"&lon="+longitude+"&key="+key);
//   if(http.GET() == HTTP_CODE_OK) {
//     String data = http.getString();
//     DynamicJsonBuffer jsonBuffer(1200);
//     JsonObject& root  = jsonBuffer.parseObject((char*) data.c_str());
//     nhietdo    = root["data"][0]["temp"].as<int>();
//     doam       = root["data"][0]["rh"].as<int>();
//     thoitiet   = root["data"][0]["weather"]["code"].as<int>();
//   }
//   http.end();
//   Serial.println();
//   Serial.printf("Nhiệt độ: %d\nĐộ ẩm: %d\nThời tiêt:%d",nhietdo,doam,thoitiet);

//   tft.setCursor(35, 116);                   //Hien thi nhiet do
//   tft.setTextColor(YELLOW,BLACK);
//   tft.setTextSize(2);
//   tft.print(nhietdo);
//   tft.drawBitmap(57,116,icondo,10,20,YELLOW);
//   tft.setCursor(68, 116);
//   tft.print("C");

//   tft.setCursor(35, 140);                   //Hien thi do am
//   tft.setTextColor(GREEN,BLACK);
//   tft.setTextSize(2);
//   String do_am = String(doam) +"%";
//   tft.print(do_am);
//   tft.fillRect(78,116,50,40,BLACK);         //Hien thi icon thoi tiet
//   iconthoitiet(78,116,thoitiet);
// }
// void iconthoitiet(int x, int y,int code) {      //https://www.weatherbit.io/api/codes
//   switch(code) {
//     // Mua kem sam set
//     case 200:
//     case 201:
//     case 202:
//               tft.drawBitmap(x,y,lighting_rain,50,40,WHITE);
//               break;
//     // Sam set
//     case 230:
//     case 231:
//     case 232:
//     case 233:
//               tft.drawBitmap(x,y,lighting,50,40,WHITE);
//               break;
//     // May + mua
//     case 300:
//     case 301:
//     case 302:
//     case 500:
//     case 501:
//     case 502:
//     case 511:
//     case 520:
//     case 521:
//     case 522:
//     case 623:
//               tft.drawBitmap(x,y,rain,50,40,WHITE);
//               break;
//     // Clear Sky
//     case 800:
//               if(gio <18 && gio>5)
//                 tft.drawBitmap(x,y,clear_sky,50,40,WHITE);
//               else
//                 tft.drawBitmap(x,y,night,50,40,WHITE);
//               break;
//     case 700:
//     case 711:
//     case 721:
//     case 731:
//     case 741:
//     case 751:
//     case 801:
//     case 802:
//     case 803:
//               if(gio <18 && gio>5)
//                 tft.drawBitmap(x,y,clear_cloudy,50,40,WHITE);
//               else
//                 tft.drawBitmap(x,y,night_cloud,50,40,WHITE);
//               break;
//     // Trời nhiều mây
//     case 611:
//     case 612:
//     case 804:
//               tft.drawBitmap(x,y,cloudy,50,40,WHITE);
//               break;
//   }
// }

