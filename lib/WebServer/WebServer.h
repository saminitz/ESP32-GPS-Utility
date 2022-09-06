#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <ESPAsyncWebServer.h>
#include <MyGPS.h>
#include <SPIFFS.h>
#include <Update.h>
#include <WiFi.h>

class WebServer {
   public:
    void setup();
    void loop();

   private:
    void wifiSetup();
    void otaSetup();
};
#endif  // __WEBSERVER_H__