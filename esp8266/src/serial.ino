#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Wire.h>
#include <Arduino.h>
#include "segmentDriver.h"

unsigned long previousMillis = 0;
unsigned long countedSeconds = 0;
unsigned long Seconds = 0;
int state = 1;

const long interval = 2; //refresh display time in ms

const char* ssid = "";
const char* password = "";

String inputMessage;
String inputParam;
const char* PARAM_VALUE = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void ShowIPAddress(const IPAddress localIP){
  String ip = localIP.toString();

  String convertedString = "";
  for (unsigned int i = 0; i < ip.length() + 1; ++i)
  {
    if(ip.substring(i,i+1) != "." && ip.substring(i,i+1) != ""){ //divide ip address into segments
      convertedString += ip.substring(i,i+1); 
    }else{
      ShowNuberDec(convertedString.toInt());

      unsigned long countedSeconds = 0;
      while(1){
        if(countedSeconds >= 1000){ //show segment of ip address for 1s
          countedSeconds = 0;
          break;
        }
        delay(2);
        HoldDisplay();
        delay(2);
        ClearDisplay();
        countedSeconds += 2;
      }
      convertedString = "";
    }
  }
}


void setup(){
  Initialilze();
  //Serial port for debugging purposes
  //Serial.begin(19200);
  WiFi.begin(ssid, password);
  //Serial.println("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  LittleFS.begin();
  ShowIPAddress(WiFi.localIP());

// What server do when client send a request
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
      inputParam = "0";
      inputMessage = "9999";
    }

    CountDown(inputMessage.toInt());
    request->send(LittleFS, "/timer.html");
  });

    server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request){ 
                                                                    
    Seconds = 0;  
    request->send(LittleFS, "/timer.html");
  });

  server.begin();
}

void CountDown(unsigned long inSeconds){
    delay(8000);
    Seconds = inSeconds;
}

void loop(){
  if (Seconds == 0)
  {
    ClearDisplay();
  }

  if(Seconds != 0){
    int hours = floor(Seconds / 3600);
    int minutes = floor((Seconds % 3600) / 60);

    ShowNuberDec(hours * 100 + minutes);

    if(countedSeconds >= 1000){
      countedSeconds = 0;
      Seconds--;
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
}
//send current status if timer was setipn
//show ip address if timer was connected