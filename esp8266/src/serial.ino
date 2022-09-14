#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "SevenSegmentDriver.h"

unsigned long previousMillis = 0;
unsigned long countedSeconds = 0;
unsigned long Seconds = 0;
int state = 1;

//refresh display time in ms
const long interval = 2; 

const char* ssid = "106A";
const char* password = "uzrvhEK97dEKRJ";

String inputMessage;
String inputParam;
const char* PARAM_VALUE = "value";

Display display(16,5,4,0,2,14,12,12,1,3,15,13);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void ShowIPAddress(const IPAddress localIP){
  String ip = localIP.toString();

  String convertedString = "";
  //divide ip address into segments
  for (unsigned int i = 0; i < ip.length() + 1; ++i)
  {
    if(ip.substring(i,i+1) != "." && ip.substring(i,i+1) != ""){ 
      convertedString += ip.substring(i,i+1); 
    }else{
      display.ShowNuberDec(convertedString.toInt());

      unsigned long countedSeconds = 0;
      //show each segment of ip address for 1s      
      while(1){
        if(countedSeconds >= 1000){ 
          countedSeconds = 0;
          break;
        }
        delay(interval);
        display.HoldDisplay();
        delay(interval);
        display.ClearDisplay();
        countedSeconds += interval;
      }
      convertedString = "";
    }
  }
}


void setup(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  LittleFS.begin();
  ShowIPAddress(WiFi.localIP());

// What server do when client send a request
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/timer.html");
  });

//If timer was set, send current status
  server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(Seconds));
  });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });

    server.on("/timer.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/timer.js", "text/js");
  });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){ 
                                                                    
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
//light up the counter only if countdown is enabled
  if (Seconds == 0) 
  {
    display.ClearDisplay();
  }
//Timer logic
  if(Seconds != 0){
    int hours = floor(Seconds / 3600);
    int minutes = floor((Seconds % 3600) / 60);

    display.ShowNuberDec(hours * 100 + minutes);

    if(countedSeconds >= 1000){
      countedSeconds = 0;
      Seconds--;
    }
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      countedSeconds = countedSeconds + interval;

      if(state == 0){
        display.HoldDisplay();
        state = 1;
      }else{
        display.ClearDisplay();
        state = 0;
      }
    }
  }
}
//send response if time is up