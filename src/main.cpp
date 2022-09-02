#include <MyGPS.h>
#include <WebServer.h>

WebServer webServer;

void setup() {
    Serial.begin(115200);
    
    webServer.setup();
    myGPS.setup();

    Serial.println("Main Done!");
}

void loop() {
    myGPS.loop();
}