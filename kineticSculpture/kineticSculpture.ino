
#include <WiFi.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial

#include "credentials.h"

const char *ssid_Router     = ROUTER; //Enter the router name
const char *password_Router = PWD; //Enter the router password

String address= "http://165.227.76.232:3000/YOUR-UNI/running";

// Sculpture Prep

int outPorts[] = {4, 0, 2, 15};

// ---

void setup(){
  
  USE_SERIAL.begin(115200);

  WiFi.begin(ssid_Router, password_Router);
  USE_SERIAL.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    USE_SERIAL.print(".");
  }
  USE_SERIAL.println("\nConnected, IP address: ");
  USE_SERIAL.println(WiFi.localIP());
  USE_SERIAL.println("Setup End");

  // Sculpture setup

  for(int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
}
 
void loop() {
  
  if((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(address);
 
    int httpCode = http.GET(); // start connection and send HTTP header
    if (httpCode == HTTP_CODE_OK) { 
        String response = http.getString();
        if (response.equals("false")) {
            delay(2000);
        }
        else if(response.equals("true")) {
            
            // 1/4 turn, medium pause
            moveSteps(true, 32 * 16, 1);
            delay(750);
            moveSteps(false, 32 * 16, 1);
            delay(750);
        }
        USE_SERIAL.println("Response was: " + response);
    } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(500); // sleep for half of a second
  }
}

void moveSteps(bool dir, int steps, byte ms) {
  for(unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir);
    delay(constrain(ms, 3, 20));
  }
}

void moveOneStep(bool dir) {

  static byte out = 0x01;

  if(dir) {
    out != 0x08 ? out = out << 1 : out = 0x01;
  } else {
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }

  for(int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

void moveAround(bool dir, int turns, byte ms) {

  for(int i = 0; i < turns; i++) {
    moveSteps(dir, 32*64, ms);
  }
}

void moveAngle(bool dir, int angle, byte ms) {
  moveSteps(dir, (angle*32*64/360), ms);
}
