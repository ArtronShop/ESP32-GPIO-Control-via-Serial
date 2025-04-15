#include <Arduino.h>
#include <gpio_viewer.h>
#include "_secrets.h"

GPIOViewer gpioViewer;

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);    // send ESP inbuilt log messages to Serial
  Serial.setTimeout(50);

  gpioViewer.connectToWifi(WIFI_SSID, WIFI_PASS);
  gpioViewer.setSamplingInterval(125);
  gpioViewer.begin();

  int pin_support_digital_write[] = { 2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33 };
  for (int pin : pin_support_digital_write) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  while(Serial.available()) {
    String command = Serial.readString();
    // Serial.print(command);
    if (command.startsWith("GET")) {
      int pin = 0;
      sscanf(command.c_str(), "GET %d", &pin);
      Serial.print(digitalRead(pin) ? "HIGH" : "LOW");
    } else if (command.startsWith("SET")) {
      int pin = 0, value = 0;
      sscanf(command.c_str(), "SET %d TO %d", &pin, &value);
      digitalWrite(pin, value);
      Serial.print("OK");
    }
  }
  delay(10);
}