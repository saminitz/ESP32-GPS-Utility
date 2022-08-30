#include <MyGPS.h>
#include <WebServer.h>

WebServer webServer;

void setup() {
    pinMode(12, PULLDOWN);
    Serial.begin(115200);
    
    webServer.setup();
    myGPS.setup();

    Serial.println("Main Done!");
}

void loop() {
    myGPS.loop();
}