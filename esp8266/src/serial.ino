#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Wire.h>
#include <Arduino.h>
#include "segmentDriver.h"

unsigned long previousMillis = 0;
unsigned long Seconds = 0;
int state = 1;

const long interval = 2;

const char* ssid = "";
const char* password = "";

String inputMessage;
String inputParam;
const char* PARAM_VALUE = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


void setup(){
  Initialilze();
  //Serial port for debugging purposes
  //Serial.begin(19200);
  WiFi.begin(ssid, password);
  //Serial.println("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    //Serial.print(".");
  }
  //Serial.println(" success!");
  //Serial.println(WiFi.localIP());

  if(!LittleFS.begin()){
    //Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

// What server do when client call a function
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("New client connected!");
    request->send(LittleFS, "/timer.html");
  });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });
    server.on("/timer.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/timer.js", "text/js");
  });
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){ //add a protection for
                                                                    //too much get request 
    if (request->hasParam(PARAM_VALUE)){
      inputMessage = request -> getParam(PARAM_VALUE) -> value();
      inputParam = PARAM_VALUE;
    }else{
      inputParam = "err";
      inputMessage = "err";
    }

    //Serial.println("Timer on");
    //Serial.print("Value: ");
    //Serial.println(inputMessage);
    CountDown(inputMessage.toInt());
    request->send(LittleFS, "/timer.html");
  });

  server.begin();
}

void CountDown(unsigned long inSeconds){
    delay(1900);
    Seconds = inSeconds;
}

void loop(){
/*  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if(state == 0){
      HoldDisplay();
      state = 1;
    }else{
      ClearDisplay();
      state = 0;
    }
  }*/
  if(Seconds != 0){
      int hours = floor(Seconds / 3600);
      int minutes = floor((Seconds % 3600) / 60);

      ShowNuberDec(hours * 100 + minutes);

      unsigned long countedSeconds = 0;
      while(1){ //while block all code! 
          if(countedSeconds >= 1100){
            break;
          }
          unsigned long currentMillis = millis();

           if (currentMillis - previousMillis >= interval) {
              previousMillis = currentMillis;
              countedSeconds = countedSeconds + 2;

              if(state == 0){
                HoldDisplay();
                state = 1;
              }else{
                ClearDisplay();
                state = 0;
              }
            }
        }
    Seconds--;
  }
}
//send current status if timer was set