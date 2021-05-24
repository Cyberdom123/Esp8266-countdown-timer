#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Wire.h>

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

//What server do when client call a function
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/timer.html");
  });

  server.begin();
}
void loop(){

}
