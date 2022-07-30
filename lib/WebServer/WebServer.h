#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Update.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

class WebServer {
   public:
    void setup();

   private:
    void wifiSetup();
    void otaSetup();
};
#endif  // __WEBSERVER_H__