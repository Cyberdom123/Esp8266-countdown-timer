#include <TM1637Display.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Wire.h>
#include <Arduino.h>

#define CLK 1
#define DIO 2
TM1637Display display(CLK, DIO);

const char* ssid = "ZSP_Bud.A";
const char* password = "zbuntowananastolatka12Q";

String inputMessage;
String inputParam;
const char* PARAM_VALUE = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


void setup(){
    Serial.begin(19200);
// Serial port for debugging purposes
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

// What server do when client call a function
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("test!");
    request->send(LittleFS, "/timer.html");
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
      inputParam = "err";
      inputMessage = "err";
    }
    Serial.println("testGet!");
    request->send(LittleFS, "/timer.html");
  });

  server.begin();
}
void loop(){

}