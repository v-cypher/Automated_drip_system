float get_moisture(){

  value = analogRead(sense_Pin);
  value = value / 10;
  value = map(value,40, 102, 100, 1);
  return value;
}

float get_temperature() {

  return dht.readTemperature();
}

float get_humidity() {

  return dht.readHumidity();
  
}

String get_time(){

  int hour = timeClient.getHours();
  int minutes = timeClient.getMinutes();

  return String(hour) + String(" : ") + String(minutes);
}

int motor() {

  moist = get_moisture();
  if (moist < 30) {
    digitalWrite(motor_pin, HIGH);
    while ( get_moisture() < 80) {
      delay(1000);
      Serial.println("Motor is ON");

    }
    digitalWrite(motor_pin, LOW);
    return 1;
  }
  else{
    Serial.print("Motor is OFF");
    return 0;
  }
}
