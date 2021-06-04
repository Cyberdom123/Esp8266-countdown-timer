#include <TM1637Display.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Wire.h>
#include <Arduino.h>

#define CLK 1
#define DIO 2
TM1637Display display(CLK, DIO);

const char* ssid = "Pentagon";
const char* password = "flatronslim";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//The processor() function attributes a value to the placeholders we’ve created on the HTML file.
//String processor(){

//}

void setup(){
    Serial.begin(115200);
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
    request->send(LittleFS, "/timer.html");
  });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });
    server.on("/timer.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/timer.js", "text/js");
  });

  server.begin();
  display.clear();
  display.setBrightness(0x0f);
}
void loop(){
  for (int i = 0; i < 9999; ++i)
  {
    display.showNumberDec(i);
    delay(500); 
  }

}