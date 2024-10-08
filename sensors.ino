// DHT11
float getTemperatureDHT11() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) Serial.println("Cannot read temperature from DHT11");
  else Serial.printf("Temperature: %.2f°C\n", temperature);
  return temperature;
}

float getHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) Serial.println("Cannot read humidity from DHT11");
  else Serial.printf("Humidity: %.2f\%\n", humidity);
  return humidity;
}
//End DHT11

//BH1750
float getIntensity() {
  float lux = lightMeter.readLightLevel();
  if (isnan(lux)) Serial.print("Cannot read intensity from BH1750");
  else Serial.printf("Light intensity: %.2f lx\n", lux);
  return lux;
}
//End BH1750

//BMP180
float getTemperatureBMP180() {
  float temperature = bmp.readTemperature();
  if (isnan(temperature)) Serial.println("Cannot read temperature from BMP180");
  else Serial.printf("Temperature: %.2f°C\n", temperature);
  return temperature;
}

float getPressure() {
  float pressure = bmp.readPressure();
  if (isnan(pressure)) Serial.println("Cannot read pressure from BMP180");
  else Serial.printf("Pressure: %.2fPa\n", pressure);
  return pressure;
}

// Calculate altitude assuming 'standard' barometric pressure of 1013.25 millibar = 101325 Pascal
float getAltitude() {
  float altitude = bmp.readAltitude();
  if (isnan(altitude)) Serial.println("Cannot read altitude from BMP180");
  else Serial.printf("Altitude: %.2fmeters\n", altitude);
  return altitude;
}

// Get a more precise measurement of altitude if you know the current sea level pressure which will vary with weather and such. If it is 1015 millibars that is equal to 101500 Pascals.
float getAltitude(int pa) {
  float altitude = bmp.readAltitude(pa);
  if (isnan(altitude)) Serial.println("Cannot read altitude from BMP180");
  else Serial.printf("Altitude: %.2fmeters\n", altitude);
  return altitude;
}
//End BMP180

// Hall 3144
bool haveMagnet(){
  int hallState = digitalRead(HALL_PIN);
  if (hallState == LOW) {
    Serial.println("Magnet detected!");
    return true;
  } else {
    Serial.println("No magnet detected.");
    return false;
  }
}
//End Hall 3144

