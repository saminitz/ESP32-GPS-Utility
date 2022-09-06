#include "WebServer.h"

// Had to move the library into the cpp file due to poor implementation
#include <AsyncElegantOTA.h>

// Set these to your desired credentials.
const char *ssid = "Yamaha YZF-R3 GPS";
const char *password = "fff222ccc1234";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void WebServer::setup() {
    wifiSetup();
    otaSetup();

    server.on("/stats", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", myGPS.generateStats());
    });
}

void WebServer::loop() {
    static const unsigned long interval = 1000; // ms
	static unsigned long lastRefreshTime = 0;
    
    if(millis() - lastRefreshTime >= interval)
    {
        lastRefreshTime += interval;
        ws.textAll(myGPS.generateStats());
    }
}    

void WebServer::wifiSetup() {
    IPAddress myIP(192, 168, 4, 1);
    IPAddress subNet(255, 255, 255, 0);
    WiFi.softAPConfig(myIP, myIP, subNet);
    WiFi.softAP(ssid, password);

    server.begin();
}

// Start ElegantOTAs
void WebServer::otaSetup() {
    AsyncElegantOTA.begin(&server);
}